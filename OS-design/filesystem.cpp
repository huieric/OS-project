#include "filesystem.h"

FileSystem::FileSystem() :
    systemStartAddr((char*)malloc(fs_size*sizeof(char))),
    bitmapStartAddr(systemStartAddr),
    blockStartAddr(systemStartAddr+bit_map_size)
{
    memset(systemStartAddr, 0, fs_size);
    FILE *fs=fopen("myfs.txt", "r");
    if(fs==0)
    {
        qDebug() << "Filesystem first opened";
        for(int i=0;i<bit_map_size;++i)
            bitmapStartAddr[i]='0';
        qDebug()<<"Creating root directory...";
        iNode& inode=iTbl.i[iTbl.num++];
        inode.i_uid=0;
        inode.i_type=Dir;
        strcpy(inode.i_mode,"rwxr--r--");
        inode.i_ilink=1;
        inode.i_size=0;
        inode.i_addr[0]=getBlock(1);
        curDir=rootDir=&inode;
        path.cur=0;
        qDebug() << "done";
    }
    else
    {
        qDebug() << "Filesystem initialized...";
        fscanf(fs, "%d", &iTbl.num);
        for(int i=0;i<iTbl.num;++i)
        {
            iNode &inode=iTbl.i[i];
            fscanf(fs, "%hd%hd%s%hd%ld", &inode.i_uid, &inode.i_type, inode.i_mode, &inode.i_ilink, &inode.i_size);
            for(int j=0;j<8;++j) fscanf(fs,"%d", &inode.i_addr[j]);
        }
        fseek(fs,1,SEEK_CUR);
        for(int i=0;i<bit_map_size;++i)
        {
            fscanf(fs,"%c",bitmapStartAddr+i);
        }

        fread(blockStartAddr, block_size, block_num, fs);
        fclose(fs);

        curDir=rootDir=&iTbl.i[0];
        path.cur=0;
        qDebug() << "done";
    }
}

FileSystem::~FileSystem()
{
    FILE *fs=fopen("myfs.txt", "w");
    qDebug() << "Filesystem saving changes...";
    fprintf(fs, "%d ", iTbl.num);
    for(int i=0;i<iTbl.num;++i)
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
    qDebug() << "done";
    qDebug() << "Filesystem closed";
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
                {
                    bitmapStartAddr[j-1]='1';
                    memset(getBlockAddr(j),0,512);
                }
                //qDebug()<<start;
                return start;
            }
        }
    }
    qDebug() << "No enough disk storage\n";
    return -1;
}

//
char* FileSystem::getBlockAddr(int blockNum)
{
    return blockStartAddr+(blockNum-1)*block_size;
}

//
int FileSystem::getAddrBlock(char* addr)
{
    return (addr-blockStartAddr)/block_size+1;
}

//
int FileSystem::releaseBlock(int blockNum, int blockSize)
{
    int endBlock = blockNum+blockSize;
    for(int i=blockNum;i<endBlock;++i)
    {
        bitmapStartAddr[i-1]='0';
        //memset(getBlockAddr(i), 0, 512);
    }
    return 0;
}

int FileSystem::createFile(const char *fileName)
{
    iNode& inode=iTbl.i[iTbl.num++];
    inode.i_uid=0;
    inode.i_type=File;
    strcpy(inode.i_mode, "rwxr-xr-x");
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

int FileSystem::remove(const char *fileName)
{
    qDebug() << "Removing" << fileName;
    iNode* inode;
    dirEntry *pe, *pl, *p;
    for(int i=0;i<8;++i)
    {
        p=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(p->inode_num==0)
            {
                pl=p-1;
                goto Done;
            }
            if(strcmp(p->fileName,fileName)==0)
            {
                pe=p;
            }
            p++;
        }
    }
Done:
    inode=&iTbl.i[pe->inode_num];
    removeInode(inode);
    pe->inode_num=pl->inode_num;
    strcpy(pe->fileName, pl->fileName);
    pl->inode_num=0;
    return 0;
}

int FileSystem::removeInode(iNode *inode)
{
    dirEntry*p;
    if(inode->i_type==Dir)
    {
        for(int i=0;i<8;++i)
        {
            p=(dirEntry*)getBlockAddr(inode->i_addr[i]);
            for(int j=0;j<32;++j)
            {
                if(p->inode_num==0)
                {
                    goto LABEL2;
                }
                iNode* i1=&iTbl.i[p->inode_num];
                removeInode(i1);
                p++;
            }
        }
    }
LABEL2:
    for(int i=0;i<8;++i)
    {
        if(inode->i_addr[i]>0)
            releaseBlock(inode->i_addr[i],1);
        else
            break;
    }
    return 0;
}

int FileSystem::createDir(char *dirName)
{
    if(dirName[strlen(dirName)-1]=='/')
        dirName[strlen(dirName)-1]='\0';
    iNode& inode=iTbl.i[iTbl.num++];
    inode.i_uid=0;
    inode.i_type=Dir;
    strcpy(inode.i_mode, "rwxr-xr-x");
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

int FileSystem::changeDir(const char *dirName)
{
    qDebug()<<dirName;
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
//        if(strcmp(dirName,".")==0)
//            return 0;
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

int FileSystem::rename(const char *oldName, const char *newName)
{
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(pe->inode_num==0)
                return -1;
            if(strcmp(pe->fileName,oldName)==0)
            {
                strcpy(pe->fileName,newName);
                return 0;
            }
            pe++;
        }
    }
}

int FileSystem::open(char *fileName)
{
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
    long left=inode->i_size;
    char buf[513];
    hedit=new Edit;
    hedit->setWindowTitle(fileName);
    if(inode->i_size<=8*512)
    {
        for(int i=0;i<8;++i)
        {
            if(left==0)
            {
                break;
            }
            if(left>=512)
            {
                char* s=getBlockAddr(inode->i_addr[i]);
                strncpy(buf,getBlockAddr(inode->i_addr[i]), 512);
                hedit->setTextEdit(buf);
                left-=512;
            }
            else
            {
                char* s=getBlockAddr(inode->i_addr[i]);
                strncpy(buf,getBlockAddr(inode->i_addr[i]), left);
                hedit->setTextEdit(buf);
                buf[left]='\0';
                left=0;
            }
        }
    }

    if(hedit->exec()==QDialog::Accepted)
    {
        left=strlen(hedit->text);
        inode->i_size=left;
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
                    if(inode->i_addr[i]==0)
                        inode->i_addr[i]=getBlock(1);
                    strncpy(getBlockAddr(inode->i_addr[i]), hedit->text, 512);
                    left-=512;
                }
                else
                {
                    if(inode->i_addr[i]==0)
                        inode->i_addr[i]=getBlock(1);
                    strncpy(getBlockAddr(inode->i_addr[i]), hedit->text, left);
                    left=0;
                }
            }
        }
        free(hedit->text);
    }
    return 0;
}

int FileSystem::move(const char *fileName, const char *path)
{
    iNode* inode;
    dirEntry *pe, *pl, *p;
    for(int i=0;i<8;++i)
    {
        p=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(p->inode_num==0)
            {
                pl=p-1;
                goto Label1;
            }
            if(strcmp(p->fileName,fileName)==0)
            {
                pe=p;
            }
            p++;
        }
    }
Label1:
    int i_num=pe->inode_num;
    pe->inode_num=pl->inode_num;
    strcpy(pe->fileName, pl->fileName);
    pl->inode_num=0;
    changeDir(path);
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(pe->inode_num==0)
            {
                strcpy(pe->fileName, fileName);
                pe->inode_num=i_num;
                return 0;
            }
            pe++;
        }
    }
}
