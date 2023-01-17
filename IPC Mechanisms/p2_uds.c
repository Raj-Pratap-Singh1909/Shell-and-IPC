#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main()
{
    sem_t *gl1;
    gl1 = sem_open("global1", O_RDWR);

    int start = 0;
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
        printf(" %s\n", mat[i]);
    }

    const char *name = "/tmp/socket";

    struct sockaddr_un socket1;

    int des = socket(AF_UNIX, SOCK_STREAM, 0);
    if (des == -1)
    {
        perror("Error in socket()");
    }

    memset(&socket1, 0, sizeof(struct sockaddr_un));
    char *data;

    socket1.sun_family = AF_UNIX;
    strncpy(socket1.sun_path, name, sizeof(socket1.sun_path) - 1);

    int con_ret = connect(des, (const struct sockaddr *)&socket1, sizeof(struct sockaddr_un));
    if (con_ret == -1)
    {
        perror("Error in connect");
    }

    char *temp;
    char rcv[3];
    char temp2[50];
    char z[10];

    for (int i = 0; i < 10; i++)
    {
        // start +=  +1;
        for (int k = 0; k < 5; k++)
        {
            temp = mat[start];
            sprintf(temp2, "%d ", start);
            if (start < 10)
            {
                sprintf(temp2, "0%d ", start);
            }
            strcat(temp2, temp);
            send(des, temp2, strlen(temp2), 0);
            sem_wait(gl1);

            start++;
        }
        recv(des, rcv, sizeof(rcv), 0);
        int receive = atoi(rcv);
        printf("ID received :%d\n", receive);
    }

    sem_close(gl1);
    sem_unlink("global1");

    return 0;
}
