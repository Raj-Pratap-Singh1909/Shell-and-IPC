#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int start = -1;
    srand(time(0));
    char mat[50][5];
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat[i][j] = 'A' + rand() % 57;
        }
        mat[i][4] = '\0';
    }

    for (int i = 0; i < 50; i++)
    {
        printf("%s\n", mat[i]);
    }

    char *pth = "/tmp/comm";
    mkfifo(pth, 0666);
    int file_d;

    struct timespec start_time1, stop_time1;
    double time_cal1;

    for (int k = 0; k < 10; k++)
    {

        file_d = open(pth, O_WRONLY);
        start++;
        for (int i = 0; i < 5; i++)
        {
            write(file_d, &start, sizeof(int));
            if (i == 0 && k == 0)
            {
                clock_gettime(CLOCK_REALTIME, &start_time1);
            }
            write(file_d, mat[start], sizeof(mat[start]));
            start += 1;
        }
        close(file_d);

        file_d = open(pth, O_RDONLY);
        read(file_d, &start, sizeof(int));
        close(file_d);
        printf("%d\n", start);
    }
    clock_gettime(CLOCK_REALTIME, &stop_time1);
    time_cal1 = (stop_time1.tv_sec - start_time1.tv_sec) + ((stop_time1.tv_nsec - start_time1.tv_nsec) * 0.000000001);
    printf("Time for writing all 50 strings: %lf seconds\n", time_cal1);

    return 0;
}
