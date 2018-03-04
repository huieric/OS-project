#include "filesystem.h"

FileSystem::FileSystem() :
    systemStartAddr((char*)malloc(fs_size*sizeof(char))),
    bitmapStartAddr(systemStartAddr),
    blockStartAddr(systemStartAddr+bit_map_size)
{
    memset(systemStartAddr, 0, fs_size);
    FILE *fs=fopen("myfs", "r");
    if(fs==0)
    {
        printf("Filesystem first opened\n");
        for(int i=0;i<bit_map_size;++i)
            bitmapStartAddr[i]='0';
        iTbl.num=0;
    }
    else
    {
        printf("Filesystem initialized...\n");
        fscanf(fs, "%d", &iTbl.num);
        for(int i=0;i<iTbl.num;++i)
        {
            iNode &inode=iTbl.i[i];
            fscanf(fs, "%d%d%s%d%ld", &inode.i_uid, &inode.i_type, inode.i_mode, &inode.i_ilink, &inode.i_size);
            for(int j=0;j<8;++j) fscanf(fs,"%d", &inode.i_addr[j]);
        }
        long skip=1+(sizeof(iNode)+6)*(block_num-iTbl.num);
        fseek(fs,skip,SEEK_CUR);

        for(int i=0;i<bit_map_size;++i)
        {
            fscanf(fs,"%c",bitmapStartAddr+i);
        }

        fread(blockStartAddr, block_size, block_num, fs);
    }
    fclose(fs);
}

FileSystem::~FileSystem()
{
    FILE *fs=fopen("myfs", "w");
    printf("Filesystem saving changes...\n");
    fprintf(fs, "%d ", iTbl.num);
    for(int i=0;i<block_num;++i)
    {
        iNode &inode=iTbl.i[i];
        fprintf(fs, "%d %d %s %d %ld ", inode.i_uid, inode.i_type, inode.i_mode, inode.i_ilink, inode.i_size);
        for(int j=0;j<8;++j) fprintf(fs, "%d ", inode.i_addr[j]);
    }
    for(int i=0;i<bit_map_size;++i)
    {
        fprintf(fs,"%c",bitmapStartAddr+i);
    }
    fwrite(blockStartAddr, block_size, block_num, fs);
    fclose(fs);
    printf("done\n");
    printf("Filesystem closed\n";);
    free(systemStartAddr);
}

//block distribution
int FileSystem::getBlock(int blockSize)
{
    int start = 0;
    int counter = 0;
    for(int i=0;i<block_num;++i)
    {
        if(bitmapStartAddr[i]=='0')
        {
            if(counter==0)
                start=i;
            counter++;
            if(counter==blockSize)
            {
                for(int j=start;j<start+blockSize;++j)
                    bitmapStartAddr[j]='1';
                return start;
            }
        }
        else
            counter=0;
    }
    printf("No enough disk storage\n");
    return -1;
}

//
char* FileSystem::getBlockAddr(int blockNum)
{
    return blockStartAddr+blockNum*block_size;
}

//
int FileSystem::getAddrBlock(char* addr)
{
    return (addr-blockStartAddr)/block_size;
}

//
int FileSystem::releaseBlock(int blockNum, int blockSize)
{
    int endBlock = blockNum+blockSize;
    for(int i=blockNum;i<endBlock;++i)
        bitmapStartAddr[i]='0';
    return 0;
}

int FileSystem::createFile(const char *fileName)
{

}

int FileSystem::deleteFile(const char *fileName)
{

}

int FileSystem::createDir(const char *dirName)
{

}

int FileSystem::deleteDir(const char *dirName)
{

}

int FileSystem::changeDir(const char *dirName)
{

}

int FileSystem::changeName(const char *oldName, const char *newName)
{

}

void FileSystem::list()
{

}

int FileSystem::open(const char *fileName)
{

}

int FileSystem::close(const char *fileName)
{

}
