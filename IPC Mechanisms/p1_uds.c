#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    sem_t *gl1;
    gl1 = sem_open("global1", O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO, 0);

    int start = 0;
    int idx;
    const char *name = "/tmp/socket";

    struct sockaddr_un socket1;
    struct sockaddr_un socket2;

    int des = socket(AF_UNIX, SOCK_STREAM, 0);
    if (des == -1)
    {
        perror("Error in socket()");
    }
    memset(&socket1, 0, sizeof(struct sockaddr_un));
    memset(&socket2, 0, sizeof(struct sockaddr_un));

    char data[10];

    socket1.sun_family = AF_UNIX;
    strncpy(socket1.sun_path, name, sizeof(socket1.sun_path) - 1);

    unlink(name);

    int bind_ret = bind(des, (struct sockaddr *)&socket1, sizeof(socket1));
    if (bind_ret == -1)
    {
        perror("Error in bind()");
    }

    int lis_ret = listen(des, 10);
    if (lis_ret == -1)
    {
        printf("Error in listen");
    }

    printf("Reached here \n");

    int des_c = accept(des, NULL, NULL);
    if (des_c == -1)
    {
        perror("Error in accepting request");
    }
    struct timespec start_time1, stop_time1;
    double time_cal1;
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            // printf("Hello");
            if (i == 0 && k == 0)
            {
                clock_gettime(CLOCK_REALTIME, &start_time1);
            }
            recv(des_c, data, sizeof(data), 0);
            printf("%s \n", data);
            // start++;
            sem_post(gl1);
        }

        char snd[3];
        strncpy(snd, data, 2);
        snd[3] = '\0';
        send(des_c, snd, sizeof(snd), 0);
        printf("ID sent: %s\n", snd);
    }

    sem_close(gl1);
    sem_unlink("global1");

    clock_gettime(CLOCK_REALTIME, &stop_time1);
    time_cal1 = (stop_time1.tv_sec - start_time1.tv_sec) + ((stop_time1.tv_nsec - start_time1.tv_nsec) * 0.000000001);
    printf("Time for writing all 50 strings: %lf seconds\n", time_cal1);

    return 0;
}
