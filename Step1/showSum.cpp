#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int sum = 0;
    for (int i = 1; i <= 100; ++i)
    {
        // printf("%d + %d = %d\n", sum, i, sum + i);
        cout << sum << " + " << i << " = " << sum+i << endl;
        sum += i;
        sleep(3);
    }
}