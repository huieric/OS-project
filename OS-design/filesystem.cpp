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
        printf("Creating root directory...\n");
        iNode& inode=iTbl.i[iTbl.num++];
        inode.i_uid=0;
        inode.i_type=Dir;
        strcpy(inode.i_mode,"rwxr--r--");
        inode.i_ilink=1;
        inode.i_size=0;
        inode.i_addr[0]=getBlock(1);
        curDir=rootDir=&inode;
        path.cur=0;
        printf("done\n");
    }
    else
    {
        printf("Filesystem initialized...\n");
        fscanf(fs, "%d", &iTbl.num);
        for(int i=0;i<iTbl.num;++i)
        {
            iNode &inode=iTbl.i[i];
            fscanf(fs, "%hd%hd%s%hd%ld", &inode.i_uid, &inode.i_type, inode.i_mode, &inode.i_ilink, &inode.i_size);
            for(int j=0;j<8;++j) fscanf(fs,"%d", &inode.i_addr[j]);
        }
        long skip=1+(sizeof(iNode)+6)*(block_num-iTbl.num);
        fseek(fs,skip,SEEK_CUR);

        for(int i=0;i<bit_map_size;++i)
        {
            fscanf(fs,"%c",bitmapStartAddr+i);
        }

        fread(blockStartAddr, block_size, block_num, fs);
        fclose(fs);

        curDir=rootDir=&iTbl.i[0];
        path.cur=0;
    }
}

FileSystem::~FileSystem()
{
    FILE *fs=fopen("myfs", "w");
    printf("Filesystem saving changes...\n");
    fprintf(fs, "%d ", iTbl.num);
    for(int i=0;i<block_num;++i)
    {
        iNode &inode=iTbl.i[i];
        fprintf(fs, "%hd %hd %s %hd %ld ", inode.i_uid, inode.i_type, inode.i_mode, inode.i_ilink, inode.i_size);
        for(int j=0;j<8;++j) fprintf(fs, "%d ", inode.i_addr[j]);
    }
    for(int i=0;i<bit_map_size;++i)
    {
        fprintf(fs,"%c",bitmapStartAddr[i]);
    }
    fwrite(blockStartAddr, block_size, block_num, fs);
    fclose(fs);
    printf("done\n");
    printf("Filesystem closed\n");
    free(systemStartAddr);
}

//block distribution
int FileSystem::getBlock(int blockSize)
{
    int start = 0;
    int counter = 0;
    for(int i=1;i<=block_num;++i)
    {
        if(bitmapStartAddr[i-1]=='0')
        {
            if(counter==0)
                start=i;
            counter++;
            if(counter==blockSize)
            {
                for(int j=start;j<start+blockSize;++j)
                    bitmapStartAddr[j-1]='1';
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
    iNode& inode=iTbl.i[iTbl.num++];
    inode.i_uid=0;
    inode.i_type=File;
    strcpy(inode.i_mode, "rwxr--r--");
    inode.i_ilink=1;
    inode.i_size=0;
    inode.i_addr[0]=getBlock(1);
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(pe->inode_num==0)
            {
                strcpy(pe->fileName, fileName);
                pe->inode_num=iTbl.num-1;
                return 0;
            }
            pe++;
        }
    }
    return -1;
}

int FileSystem::deleteFile(const char *fileName)
{

}

int FileSystem::createDir(char *dirName)
{
    if(dirName[strlen(dirName)-1]=='/')
        dirName[strlen(dirName)-1]='\0';
    iNode& inode=iTbl.i[iTbl.num++];
    inode.i_uid=0;
    inode.i_type=Dir;
    strcpy(inode.i_mode, "rwxr--r--");
    inode.i_ilink=1;
    inode.i_size=0;
    inode.i_addr[0]=getBlock(1);
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(pe->inode_num==0)
            {
                strcpy(pe->fileName, dirName);
                pe->inode_num=iTbl.num-1;
                return 0;
            }
            pe++;
        }
    }
    return -1;
}

int FileSystem::deleteDir(const char *dirName)
{

}

int FileSystem::changeDir(const char *dirName)
{
    const char* p=dirName;
    const char* p1;
    if(strcmp(dirName,".")==0)
        return 0;
    if(strcmp(dirName,"..")==0)
    {
        path.cur--;
        curDir=&iTbl.i[path.pe[path.cur-1]->inode_num];
        return 0;
    }
    if(dirName[0]=='/')
    {
        curDir=rootDir;
        path.cur=0;
        p++;
        if(*p=='\0')
            return 0;
        goto LABEL1;
    }
    else
    {
        if(dirName[1]=='\0')
            return 0;
        if(strncmp(dirName,"./", 2)==0)
            p+=2;
LABEL1:
        p1=strchr(p, '/');
        if(p1==0)
        {
            p1=dirName+strlen(dirName);
        }
        for(int i=0;i<8;++i)
        {
           dirEntry* pe=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
           for(int j=0;j<32;++j)
           {
                if(pe->inode_num==0) return -1;
                if(strncmp(pe->fileName, p, p1-p)==0)
                {
                    path.pe[path.cur++]=pe;
                    curDir=&iTbl.i[pe->inode_num];
                    p=*p1? p1+1 : p1;
                    if(*p=='\0')
                    {
                        return 0;
                    }
                    goto LABEL1;
                }
                pe++;
           }
        }
    }
}

void FileSystem::pwd()
{
    QString pathStr="/";
    for(int i=0;i<path.cur;++i)
    {
        pathStr+=path.pe[i]->fileName;
    }
    qDebug()<<pathStr;
}

int FileSystem::changeName(const char *oldName, const char *newName)
{

}

void FileSystem::list()
{

}

int FileSystem::open(char *fileName)
{
    qDebug() << fileName;
    iNode* inode;
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(pe->inode_num==0)
                return -1;
            if(strcmp(pe->fileName,fileName)==0)
            {
                inode=&iTbl.i[pe->inode_num];
                goto Found;
            }
            pe++;
        }
    }
Found:
    qDebug() << fileName;
    FILE* ft=fopen(fileName, "w");
    long left=inode->i_size;
    if(inode->i_size<=8*512)
    {
        for(int i=0;i<8;++i)
        {
            if(left==0)
                break;
            if(left>=512)
            {
                fread(getBlockAddr(inode->i_addr[i]), 512, 1, ft);
                left-=512;
            }
            else
            {
                fread(getBlockAddr(inode->i_addr[i]), left, 1, ft);
                left=0;
            }
        }
    }
    fclose(ft);
    pid_t p;
    int status;
    qDebug() << fileName;
    char* arg[]={"gedit", fileName, 0};
    if((p=fork())==0)
    {
        execvp("gedit", arg);
    }
    waitpid(p, &status, 0);

    ft=fopen(fileName, "r");
    fseek(ft, 0, SEEK_END);
    left=ftell(ft);
    inode->i_size=left;
    qDebug()<<left;
    if(left<=8*512)
    {
        for(int i=0;i<8;++i)
        {
            if(left==0)
            {
                inode->i_addr[i]=0;
            }
            if(left>=512)
            {
                fwrite(getBlockAddr(inode->i_addr[i]), 512, 1, ft);
                left-=512;
            }
            else
            {
                fwrite(getBlockAddr(inode->i_addr[i]), left, 1, ft);
                left=0;
            }
        }
    }
    fclose(ft);
    return 0;
}

int FileSystem::close(char *fileName)
{

}
