#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        struct dirent *cur;
        DIR *folder;
        // char curr[500];
        // getcwd(curr,sizeof(curr));
        folder = opendir(".");
        if (folder == NULL)
        {
            printf("ERROR %d: %s", errno, strerror(errno));
        }
        while ((cur = readdir(folder)) != NULL)
        {
            if (cur->d_name[0] != '.')
            {
                printf("%s  ", cur->d_name);
            }
        }
        printf("\n");
    }

    else if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'a')
        {
            struct dirent *cur;
            DIR *folder;
            folder = opendir(".");
            if (folder == NULL)
            {
                printf("ERROR %d: %s", errno, strerror(errno));
            }
            while ((cur = readdir(folder)) != NULL)
            {
                printf("%s  ", cur->d_name);
            }
            printf("\n");
        }
        else if (argv[1][1] == 'm')
        {
            struct dirent *cur;
            DIR *folder;
            folder = opendir(".");
            if (folder == NULL)
            {
                printf("ERROR %d: %s", errno, strerror(errno));
            }
            while ((cur = readdir(folder)) != NULL)
            {
                if (cur->d_name[0] != '.')
                {
                    printf("%s,  ", cur->d_name);
                }
            }
            printf("\n");
        }

        else
        {
            printf("ERROR : Given command has no such options\n");
        }
    }
    return 0;
}
