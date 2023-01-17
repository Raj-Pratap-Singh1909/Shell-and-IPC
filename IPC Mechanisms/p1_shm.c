#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    sem_t *gl1, *gl2;
    gl1 = sem_open("global1", O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO, 0);
    gl2 = sem_open("global2", O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO, 0);

    const int size = 500;
    int recv = -1;
    int start = -1;
    srand(time(0));
    // Making 50 random strings of size 4 each
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

    int desc = shm_open("IPC_SHM", O_CREAT | O_RDWR, 0666);
    ftruncate(desc, size);

    void *obj = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
    for (int i = 0; i < 10; i++)
    {
        start = recv + 1;
        for (int k = 0; k < 5; k++)
        {

            write(desc, &start, sizeof(int));
            write(desc, mat[start], sizeof(mat[start]));
            start++;

            sem_post(gl1);
        }
        sem_wait(gl2);
        read(desc, &recv, sizeof(int));
        printf("%d\n", recv);
    }
    return 0;
}
