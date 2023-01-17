#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char *pth = "/tmp/comm";
    mkfifo(pth, 0666);
    int file_d;

    for (int k = 0; k < 10; k++)
    {

        file_d = open(pth, O_RDONLY);
        int idx;
        char data[5];
        for (int i = 0; i < 5; i++)
        {
            read(file_d, &idx, sizeof(int));
            read(file_d, data, sizeof(data));
            printf("ID %d : %s \n", idx, data);
        }
        close(file_d);
        printf("%d\n", idx);

        file_d = open(pth, O_WRONLY);
        write(file_d, &idx, sizeof(int));
        close(file_d);
    }
    unlink(pth);
    return 0;
}