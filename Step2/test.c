#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, const char*argv[]) {
    if(argc == 3) {
        long int return_code = syscall(383, argv[1], argv[2]);
        printf("System call sys_copy returned %ld\n", return_code);        
    }
    else {
        printf("copy: arguments number incorrect\n");
        printf("copy [sourceFileName] [destinationFileName]\n");
    }
    return 0;
}