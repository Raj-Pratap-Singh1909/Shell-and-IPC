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
    if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'n')
        {
            int lno = 1;
            FILE *fil;
            int f = 1;
            for (int i = 2; i < argc; i++)
            {
                fil = fopen(argv[i], "r");
                char r;
                if (fil == NULL)
                {
                    printf("ERROR : %s : %d: %s\n", argv[i], errno, strerror(errno));
                }
                else
                {
                    while (1)
                    {
                        if (f)
                        {
                            printf("%d  ", lno);
                            lno++;
                            f = 0;
                        }
                        r = fgetc(fil);
                        if (r == '\n')
                        {
                            f = 1;
                        }
                        if (r == EOF)
                        {
                            break;
                        }
                        printf("%c", r);
                    }
                    fclose(fil);
                }
            }
        }
        else if (argv[1][1] == 'E')
        {
            FILE *fil;
            for (int i = 2; i < argc; i++)
            {
                fil = fopen(argv[i], "r");
                int f = 0;
                char r;
                if (fil == NULL)
                {
                    printf("ERROR : %s : %d: %s\n", argv[i], errno, strerror(errno));
                }
                else
                {
                    while (1)
                    {
                        r = fgetc(fil);
                        if (r == '\n')
                        {
                            printf("$");
                        }
                        if (r == EOF)
                        {
                            break;
                        }
                        printf("%c", r);
                    }
                    printf("$");
                    fclose(fil);
                }
            }
        }
        else
        {
            printf("ERROR : No such option exists");
        }
    }
    else
    {
        FILE *fil;
        for (int i = 1; i < argc; i++)
        {
            fil = fopen(argv[i], "r");
            char r;
            if (fil == NULL)
            {
                printf("ERROR : %s : %d: %s", argv[i], errno, strerror(errno));
            }
            else
            {
                while (1)
                {
                    r = fgetc(fil);
                    if (r == EOF)
                    {
                        break;
                    }
                    printf("%c", r);
                }
                fclose(fil);
            }
        }
    }
    return 0;
}
