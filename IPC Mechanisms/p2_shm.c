#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    const int cap = 500;
    int idx;
    sem_t *gl1, *gl2;
    struct timespec start_time1, stop_time1;
    double time_cal1;
    gl1 = sem_open("global1", O_RDWR);
    
    gl2 = sem_open("global2", O_RDWR);
    char data[5];
    int desc = shm_open("IPC_SHM", O_RDWR, 0666);
    void *obj = mmap(0, cap, PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            sem_wait(gl1);
            if (i == 0 && k == 0)
            {
                clock_gettime(CLOCK_REALTIME, &start_time1);
            }
            read(desc, &idx, sizeof(int));
            printf("%d ", idx);
            read(desc, data, sizeof(data));
            printf("%s\n", data);
        }
        write(desc, &idx, sizeof(int));
        printf("%d \n", idx);
        sem_post(gl2);
    }
    clock_gettime(CLOCK_REALTIME, &stop_time1);
    time_cal1 = (stop_time1.tv_sec - start_time1.tv_sec) + ((stop_time1.tv_nsec - start_time1.tv_nsec) * 0.000000001);
    printf("Time for writing all 50 strings: %lf seconds\n", time_cal1);
    sem_close(gl1);
    sem_unlink("global1");
    sem_close(gl2);
    sem_unlink("global2");
    shm_unlink("IPC_SHM");
    close(desc);

    return 0;
}
