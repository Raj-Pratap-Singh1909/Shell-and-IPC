#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int dexists(const char *inp)
{
    struct stat ret;
    stat(inp, &ret);
    return S_ISREG(ret.st_mode);
}

int main(int argc, char const *argv[])
{
    if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'i')
        {

            for (int i = 2; i < argc; i++)
            {
                char c;
                // char *file = argv[i];
                printf("rm : remove regular file '%s' ?(enter y for yes and any other character if you don't want to delete) ", argv[i]);
                scanf(" %c", &c);
                // printf("%s", c);
                if (c == 'y')
                {
                    if (remove(argv[i]))
                    {
                        printf("ERROR : cannot delete '%s' %d: %s\n", argv[i], errno, strerror(errno));
                    }
                }
            }
        }
        else if (argv[1][1] == 'v')
        {
            for (int i = 2; i < argc; i++)
            {
                // char *file = argv[i];
                if (remove(argv[i]))
                {
                    printf("ERROR : cannot delete '%s' %d: %s\n", argv[i], errno, strerror(errno));
                }
                else
                {
                    printf("removed '%s'\n", argv[i]);
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
        for (int i = 1; i < argc; i++)
        {
            // char *file = argv[i];
            if (dexists(argv[i]))
            {
                if (remove(argv[i]))
                {
                    printf("ERROR : cannot delete '%s' %d: %s\n", argv[i], errno, strerror(errno));
                }
            }
        }
    }
    return 0;
}
