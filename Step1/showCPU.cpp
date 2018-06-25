#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

typedef struct //定义一个cpu occupy的结构体
{
    char cpu_name[20];    //cpu
    unsigned int user;    //从系统启动开始累计到当前时刻，用户态的CPU时间（单位：jiffies）
    unsigned int nice;    //从系统启动开始累计到当前时刻，nice值为负的进程所占用的CPU时间
    unsigned int system;  //从系统启动开始累计到当前时刻，核心时间
    unsigned int idle;    //从系统启动开始累计到当前时刻，除硬盘IO等待时间以外其它等待时间
    unsigned int iowait;  //从系统启动开始累计到当前时刻，硬盘IO等待时间
    unsigned int irq;     //从系统启动开始累计到当前时刻，硬中断时间
    unsigned int softirq; //从系统启动开始累计到当前时刻，软中断时间
} CPU_OCCUPY;

void getCPU_occupy(CPU_OCCUPY &cpu_occupy)
{
    char buf[1024];
    FILE *in = fopen("/proc/stat", "r");
    fgets(buf, sizeof(buf), in);
    sscanf(buf, "%s %d %d %d %d %d %d %d", cpu_occupy.cpu_name, &cpu_occupy.user, &cpu_occupy.nice, &cpu_occupy.system, &cpu_occupy.idle, &cpu_occupy.iowait, &cpu_occupy.irq, &cpu_occupy.softirq);
    fclose(in);
}

double calCPU_occupy(const CPU_OCCUPY &cpu1, const CPU_OCCUPY &cpu2)
{
    double total1 = cpu1.idle + cpu1.iowait + cpu1.irq + cpu1.nice + cpu1.softirq + cpu1.system + cpu1.user;
    double total2 = cpu2.idle + cpu2.iowait + cpu2.irq + cpu2.nice + cpu2.softirq + cpu2.system + cpu2.user;
    return ((cpu2.user + cpu2.system + cpu2.nice) - (cpu1.user + cpu1.system + cpu1.nice)) / (total2 - total1);
}

int main()
{
    CPU_OCCUPY cpu1, cpu2;
    while (1)
    {
        getCPU_occupy(cpu1);
        sleep(2);
        getCPU_occupy(cpu2);
        double rate = calCPU_occupy(cpu1, cpu2);
        cout << rate << endl;
    }
    return 0;
}