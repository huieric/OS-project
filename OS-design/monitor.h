#ifndef MONITOR_H
#define MONITOR_H

#include <QThread>
#include <QDebug>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#define MAX_SIZE 1000

typedef struct
{
    int pid;
    int uid;
    double cpu_usage;
    char command[100];
    char u_name[50];
    double mem_usage;
}p_State;

typedef struct
{
    long long memtotal;
    long long memfree;
}mem_State;

typedef struct
{
    long enp_receive, enp_transmit;
    long wlp_receive, wlp_transmit;
}net_State;

class WorkerThread_monitor : public QThread
{
    Q_OBJECT

public:
    p_State ps[MAX_SIZE];
    mem_State ms;
    net_State ns[2];
    void run();

signals:
    void resultReady(int p_num);
};

typedef struct      //定义一个cpu occupy的结构体
{
char cpu_name[20];             //cpu
unsigned int user;        //从系统启动开始累计到当前时刻，用户态的CPU时间（单位：jiffies）
unsigned int nice;        //从系统启动开始累计到当前时刻，nice值为负的进程所占用的CPU时间
unsigned int system;    //从系统启动开始累计到当前时刻，核心时间
unsigned int idle;         //从系统启动开始累计到当前时刻，除硬盘IO等待时间以外其它等待时间
unsigned int iowait;   //从系统启动开始累计到当前时刻，硬盘IO等待时间
unsigned int irq;      //从系统启动开始累计到当前时刻，硬中断时间
unsigned int softirq;  //从系统启动开始累计到当前时刻，软中断时间
}CPU_OCCUPY;

class WorkerThread_cpu : public QThread
{
    Q_OBJECT

public:
    double rate[4];
    void run()
    {
        while(1)
        {
            getCPU_occupy(0);
            sleep(1);
            getCPU_occupy(1);
            calCPU_occupy();
            emit resultReady();
        }
    }

    void getCPU_occupy(int t)
    {
        char buf[1024];
        FILE* in = fopen("/proc/stat", "r");
        fgets(buf, sizeof(buf), in);
        for(int i=0;i<4;++i)
        {
            CPU_OCCUPY &cpu_occupy = cpu[i][t];
            fgets(buf, sizeof(buf), in);
            sscanf(buf, "%s %d %d %d %d %d %d %d", cpu_occupy.cpu_name, &cpu_occupy.user, &cpu_occupy.nice, &cpu_occupy.system, &cpu_occupy.idle, &cpu_occupy.iowait, &cpu_occupy.irq, &cpu_occupy.softirq);
        }
        fclose(in);
    }

    void calCPU_occupy()
    {
        for(int i=0;i<4;++i)
        {
            CPU_OCCUPY &cpu1 = cpu[i][0], &cpu2 = cpu[i][1];
            double total1 = cpu1.idle+cpu1.iowait+cpu1.irq+cpu1.nice+cpu1.softirq+cpu1.system+cpu1.user;
            double total2= cpu2.idle+cpu2.iowait+cpu2.irq+cpu2.nice+cpu2.softirq+cpu2.system+cpu2.user;
            rate[i] = ((cpu2.user+cpu2.system+cpu2.nice)-(cpu1.user+cpu1.system+cpu1.nice))/(total2-total1);
        }
    }

private:
    CPU_OCCUPY cpu[4][2];

signals:
    void resultReady();
};

#endif // MONITOR_H

