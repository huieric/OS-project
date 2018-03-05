#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <bits/stdc++.h>
#define Dir 0
#define File 1

typedef struct
{
    short i_uid;
    short i_type;
    char i_mode[9];
    short i_ilink;
    long i_size;
    int i_addr[8];
}iNode;

const int max_file_size = 100*1024*1024;
const int block_size = 512;
const int block_num = max_file_size/block_size;
const int bit_map_size = block_num;
const int fs_size = max_file_size + bit_map_size;

typedef struct
{
    int num;
    iNode i[100];
}iNodeTable;

typedef struct
{
    short inode_num;
    char fileName[14];
}dirEntry;

class FileSystem
{
private:
    char *const systemStartAddr;
    char *const bitmapStartAddr;
    char *const blockStartAddr;        

public:
    iNodeTable iTbl;
    iNode* rootDir;
    iNode* curDir;
    char path[200];

    FileSystem();
    virtual ~FileSystem();
    int getBlock(int blockSize);
    char* getBlockAddr(int blockNum);
    int getAddrBlock(char* addr);
    int releaseBlock(int blockNum, int blockSize);
    int createFile(const char *fileName);
    int deleteFile(const char *fileName);
    int createDir(const char *dirName);
    int deleteDir(const char *dirName);
    int changeDir(const char *dirName);
    int changeName(const char *oldName, const char *newName);
    void list();
    int open(const char *fileName);
    int close(const char *fileName);
};

#endif // FILESYSTEM_H
