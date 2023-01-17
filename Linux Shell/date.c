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
#include <time.h>

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        time_t dt;
        time(&dt);
        printf("%s \n", ctime(&dt));
    }
    else if (argv[1][0] == '-')
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            printf("This command is used to print date and time \n");
            printf("It is also used to set date and time of the system \n");
        }
        else if (argv[1][1] == 'I')
        {
            time_t tim = time(NULL);
            struct tm given = *localtime(&tim);
            printf("%d-%d-%d\n", given.tm_year + 1900, given.tm_mon + 1, given.tm_mday);
        }
        else
        {
            printf("ERROR :No such options exist\n");
        }
    }
    return 0;
}
