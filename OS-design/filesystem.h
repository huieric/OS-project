#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <bits/stdc++.h>
#define Dir 0
#define File 1

typedef struct
{
    char i_uid;
    char i_type;
    char i_mode[9];
    char i_ilink;
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
    iNode i[block_num];
}iNodeTable;

class FileSystem
{
private:
    char *const systemStartAddr;
    char *const bitmapStartAddr;
    char *const blockStartAddr;
    iNodeTable iTbl;

public:
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
