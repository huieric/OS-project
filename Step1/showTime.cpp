#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;
char tmp[64];

int main()
{
    time_t t;
    while (1)
    {
        t = time(0);    
        strftime(tmp, sizeof(tmp), "%Y/%m/%d %A %X", localtime(&t));
        cout << tmp << endl;
        sleep(1);
    }
}