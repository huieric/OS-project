#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <QDebug>
#include "edit.h"
#define Dir 0
#define File 1

using namespace std;

typedef struct
{
    short i_uid;
    short i_type;
    char i_mode[9];
    short i_ilink;
    long i_size;
    int i_addr[8];
}iNode;

const int max_file_size = 1*1024*1024;
const int block_size = 512;
const int block_num = max_file_size/block_size;
const int bit_map_size = block_num;
const int fs_size = max_file_size + bit_map_size;

typedef struct
{
    int num;
    iNode i[block_num];
}iNodeTable;

typedef struct
{
    short inode_num;
    char fileName[14];
}dirEntry;

typedef struct
{
    dirEntry* pe[100];
    int cur;
}Path;

class FileSystem
{
private:
    char *const systemStartAddr;
    char *const bitmapStartAddr;
    char *const blockStartAddr;
    Edit* hedit;

public:
    iNodeTable iTbl;
    iNode* rootDir;
    iNode* curDir;
    Path path;

    FileSystem();
    virtual ~FileSystem();
    int getBlock(int blockSize);
    char* getBlockAddr(int blockNum);
    int getAddrBlock(char* addr);
    int releaseBlock(int blockNum, int blockSize);
    int createFile(const char *fileName);
    int remove(const char *fileName);
    int removeInode(iNode* inode);
    int createDir(char *dirName);
    int changeDir(const char *dirName);
    int rename(const char *oldName, const char *newName);
    int move(const char*fileName, const char*path);
    int open(char *fileName);
    void pwd();
};

#endif // FILESYSTEM_H
