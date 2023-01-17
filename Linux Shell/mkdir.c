#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int size = argc;
    if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'v')
        {
            for (int i = 2; i < size; i++)
            {
                if (mkdir(argv[i], 0777))
                {
                    printf("ERROR cannot create %s %d :%s\n", argv[i], errno, strerror(errno));
                }
                else
                {
                    printf("mkdir: created directory '%s'\n", argv[i]);
                }
            }
        }

        else if (argv[1][1] == 'p')
        {
            char *str1 = (char *)argv[2];
            char *dir = strtok(str1, "/");
            char ans[100];
            strcpy(ans, dir);
            while (dir != NULL)
            {
                mkdir(ans, 0777);
                strcat(ans, "/");
                dir = strtok(NULL, "/");
                if (dir != NULL)
                {
                    strcat(ans, dir);
                }
            }
        }
        else
        {
            printf("ERROR : No such option exists\n");
        }
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            if (mkdir(argv[i], 0777))
            {
                printf("ERROR cannot create %s %d :%s\n", argv[i], errno, strerror(errno));
            }
        }
    }

    return 0;
}
