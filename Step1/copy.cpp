#include <unistd.h>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <string>
#include <cstring>
#define SIZE 1024
#define NUM 10

using namespace std;

int readSem, writeSem;
int shmid[NUM];
pid_t readbuf, writebuf;
char *buf[NUM];
long totalBytes, readBytes, writeBytes;
FILE *outfile;
FILE *infile;

void readbufProcess();
void writebufProcess();
void P(int semid, int index);
void V(int semid, int index);

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    char *sourceFileName = argv[1];
    infile = fopen(sourceFileName, "rb");
    fseek(infile, 0, SEEK_END);
    totalBytes = ftell(infile);
    rewind(infile);
    char *destinationFileName = argv[2];
    outfile = fopen(destinationFileName, "wb");

    for (int i = 0; i < NUM; i++)
    {
      shmid[i] = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);
      buf[i] = (char *)shmat(shmid[i], 0, SHM_R | SHM_W);
    }

    readSem = semget(IPC_PRIVATE, NUM, IPC_CREAT | 0666);
    writeSem = semget(IPC_PRIVATE, NUM, IPC_CREAT | 0666);
    for (int i = 0; i < NUM; i++)
    {
      semctl(readSem, i, SETVAL, 0);
      semctl(writeSem, i, SETVAL, 1);
    }

    readbuf = fork();
    if (readbuf == 0)
    {
      readbufProcess();
    }
    writebuf = fork();
    if (writebuf == 0)
    {
      writebufProcess();
    }

    int readStatus, writeStatus;
    waitpid(readbuf, &readStatus, 0);
    waitpid(writebuf, &writeStatus, 0);

    semctl(readSem, 0, IPC_RMID);
    semctl(writeSem, 0, IPC_RMID);

    for (int i = 0; i < NUM; i++)
    {
      shmdt(buf[i]);
      buf[i] = 0;
      shmctl(shmid[i], IPC_RMID, 0);
    }
  }
  else
  {
    printf("copy: The number of parameters incorrect.\n");
    printf("      copy [sourceFileName] [destinationFIleName]");
  }
  return 0;
}

void readbufProcess()
{
  int i = 0;
  clock_t start, finish;
  start = clock();
  while (readBytes < totalBytes)
  {
    int unreadBytes = totalBytes - readBytes;
    int size = unreadBytes > SIZE ? SIZE : unreadBytes;
    P(readSem, i);
    int newBytes = fwrite(buf[i], sizeof(char), size, outfile);
    V(writeSem, i);
    readBytes += newBytes;
    i = (i + 1) % NUM;
  }
  fclose(outfile);
  finish = clock();
  double duration = (double)(finish - start) / CLOCKS_PER_SEC;
  printf("%ld\n", totalBytes);
  printf("%lf\n", duration);
  double rate = totalBytes / duration;
  if (rate > 1024.0 * 1024 * 1024)
    printf("Average speed: %.2lfGB/s\n", rate / (1024 * 1024 * 1024));
  else if (rate > 1024.0 * 1024)
    printf("Average speed: %.2lfMB/s\n", rate / (1024 * 1024));
  else if (rate > 1024.0)
    printf("Average speed: %.2lfKB/s\n", rate / 1024);
  else
    printf("Average speed: %.2lfB/s\n", rate);
  exit(0);
}

void writebufProcess()
{
  int i = 0;
  while (writeBytes < totalBytes)
  {
    P(writeSem, i);
    memset(buf[i], 0, sizeof(buf[i]));
    int newBytes = fread(buf[i], sizeof(char), SIZE, infile);
    V(readSem, i);
    writeBytes += newBytes;
    i = (i + 1) % NUM;
  }
  fclose(infile);
  exit(0);
}

void P(int semid, int index)
{
  struct sembuf sem;
  sem.sem_num = index;
  sem.sem_op = -1;
  sem.sem_flg = 0;
  semop(semid, &sem, 1);
}

void V(int semid, int index)
{
  struct sembuf sem;
  sem.sem_num = index;
  sem.sem_op = 1;
  sem.sem_flg = 0;
  semop(semid, &sem, 1);
}
