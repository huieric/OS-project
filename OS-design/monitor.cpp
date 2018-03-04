#include "monitor.h"

void WorkerThread_monitor::run()
{
    while(1)
    {
        int counter = 0;
        system("pidstat > p_cpu.txt");
        FILE *fc, *fm, *fn;
        char buf[256];
        char temp[30];
        fc = fopen("p_cpu.txt", "r");
        for(int i=0; i<3; ++i) fgets(buf, sizeof(buf), fc);
        while(!feof(fc))
        {
            p_State &p = ps[counter++];
            fgets(buf, sizeof(buf), fc);
            sscanf(buf, "%s%d%d%s%s%s%lf%s%s", temp, &p.uid, &p.pid, temp, temp, temp, &p.cpu_usage, temp, p.command);
            strcpy(p.u_name, getpwuid(p.uid)->pw_name);
        }
        fclose(fc);

        fm = fopen("/proc/meminfo", "r");
        fgets(buf, sizeof(buf), fm);
        sscanf(buf, "%s%lld%s", temp, &ms.memtotal, temp);
        fgets(buf, sizeof(buf), fm);
        fgets(buf, sizeof(buf), fm);
        sscanf(buf, "%s%lld%s", temp, &ms.memfree, temp);
        fclose(fm);

        fn = fopen("/proc/net/dev", "r");
        for(int i=0;i<2;++i) fgets(buf, sizeof(buf), fn);
        ns[0] = ns[1];
        for(int i=0;i<3;++i)
        {
            fscanf(fn, "%s", temp);
            if(strcmp(temp, "enp3s0:")==0) fscanf(fn, "%ld%s%s%s%s%s%s%s%ld%s%s%s%s%s%s%s", &ns[1].enp_receive, temp, temp, temp, temp, temp, temp, temp, &ns[1].enp_transmit, temp, temp, temp, temp, temp, temp, temp);
            else if(strcmp(temp, "wlp2s0:")==0) fscanf(fn, "%ld%s%s%s%s%s%s%s%ld%s%s%s%s%s%s%s", &ns[1].wlp_receive, temp, temp, temp, temp, temp, temp, temp, &ns[1].wlp_transmit, temp, temp, temp, temp, temp, temp, temp);
            else fgets(buf, sizeof(buf), fn);
        }
        fclose(fn);


        emit resultReady(counter);
        sleep(1);
    }
}
