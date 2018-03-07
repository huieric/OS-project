#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIZE 1024

int main() {
    char buf[MAX_SIZE];
    char in[MAX_SIZE];
    int fd = open("/dev/myDevice", O_RDWR | O_NONBLOCK);
    if(fd != -1) {
        read(fd, buf, sizeof(buf));
        printf("%s\n", buf);

        //printf("Input: ");
        fgets(in, sizeof(in), stdin);
        write(fd, in, sizeof(in));

        read(fd, buf, sizeof(buf));
        printf("%s\n", buf);

        close(fd);
        return 0;
    }
    else {
        printf("Open myDevice failed!\n");
        return -1;
    }
}