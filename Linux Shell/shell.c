#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void *run_c(void *data)
{
    char *arr = (char *)data;
    system(arr);
    return NULL;
}

void echo(char **get, int size)
{
    if (strcmp(get[1], "-n") == 0)
    {
        char *str1;
        for (int i = 2; i < size; i++)
        {
            str1 = get[i];
            printf(str1);
            printf(" ");
        }
    }
    else if (strcmp(get[1], "-E") == 0)
    {
        char *str1;
        for (int i = 2; i < size; i++)
        {
            str1 = get[i];
            printf(str1);
            printf(" ");
        }
        printf("\n");
    }
    else if (strcmp(get[1], "--help") == 0)
    {
        printf("Echo command prints the given text to the console");
        printf("\n");
    }
    else
    {

        char *str1;
        for (int i = 1; i < size; i++)
        {
            str1 = get[i];
            printf(str1);
            printf(" ");
        }
        printf("\n");
    }
}
void pwd(char **get, int size)
{
    if (size == 1)
    {
        char cur[500];
        if (getcwd(cur, sizeof(cur)) == NULL)
        {
            printf("ERROR %d,%s\n", errno, strerror(errno));
        }
        else
        {
            printf(cur);
            printf("\n");
        }
    }
    else if (size == 2)
    {
        if (strcmp(get[1], "-P") == 0)
        {
            char cur[500];
            if (getcwd(cur, sizeof(cur)) == NULL)
            {
                printf("ERROR %d,%s\n", errno, strerror(errno));
            }
            else
            {
                printf(cur);
                printf("\n");
            }
        }
        else if (strcmp(get[1], "-L") == 0)
        {
            char star[PATH_MAX];
            char cur[500];
            realpath(cur, star);
            if (getcwd(cur, sizeof(cur)) == NULL)
            {
                printf("ERROR %d,%s\n", errno, strerror(errno));
            }
            else
            {
                printf(cur);
                printf("\n");
            }
        }
        else
        {
            printf("Invalid option : No such command exists\n");
        }
    }
    else
    {
        printf("ERROR : INVALID COMMAND");
    }
}

void cd(char **get, int size)
{
    if (size == 2)
    {
        if (strcmp(get[1], "~") == 0)
        {
            chdir(getenv("HOME"));
        }
        else if (strcmp(get[1], "--") == 0)
        {
            chdir(getenv("HOME"));
        }
        else
        {
            char *pth = get[1];
            int vis = chdir(pth);
            if (vis)
            {
                perror(" ERROR");
            }
        }
    }
    else if (size == 1)
    {
        chdir(getenv("HOME"));
    }
}

int main()
{
    const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);

    printf("______________________________________MY SHELL________________________________________________\n\n");
    while (1)
    {
        int n = 100;
        char *inp;
        inp = (char *)malloc(n * sizeof(char));
        printf("  ");
        char current[500];
        getcwd(current, sizeof(current));
        printf(current);
        printf(" $");

        scanf("%[^\n]%*c", inp);
        char **get;
        get = (char **)malloc(10 * sizeof(char *));
        int size = 0;
        char *token = strtok(inp, " ");
        while (token != NULL)
        {
            get[size] = (char *)malloc(100 * sizeof(char));
            strcpy(get[size], token);
            size++;
            token = strtok(NULL, " ");
        }
        get[size] = NULL;
        if (strcmp(get[0], "echo") == 0)
        {
            echo(get, size);
        }
        else if (strcmp(get[0], "pwd") == 0)
        {
            // printf("Hi\n");
            pwd(get, size);
        }
        else if (strcmp(get[0], "cd") == 0)
        {
            // printf("Hi\n");
            cd(get, size);
        }

        else if (strcmp(get[0], "mkdir") == 0)
        {
            if (strcmp(get[size - 1], "&t") == 0)
            {
                char *data = (char *)malloc(100 * sizeof(char));
                strcat(data, "/home/raj/Files/Shell/./mkdir");
                for (int i = 1; i < size - 1; i++)
                {
                    // printf("HELLO");
                    strcat(data, " ");
                    strcat(data, get[i]);
                }
                pthread_t thread1;
                pthread_create(&thread1, NULL, run_c, data);
                pthread_join(thread1, NULL);
            }
            else
            {
                pid_t pid;
                pid = fork();
                if (pid == 0)
                {
                    execvp("/home/raj/Files/Shell/./mkdir", get);
                    exit(0);
                }
                else
                {
                    wait((int *)NULL);
                }
            }
        }

        else if (strcmp(get[0], "ls") == 0)
        {
            // printf("%d", size);
            if (strcmp(get[size - 1], "&t") == 0)
            {
                char *data = (char *)malloc(100 * sizeof(char));
                strcat(data, "/home/raj/Files/Shell/./ls");
                for (int i = 1; i < size - 1; i++)
                {
                    // printf("HELLO");
                    strcat(data, " ");
                    strcat(data, get[i]);
                }
                pthread_t thread1;
                pthread_create(&thread1, NULL, run_c, data);
                pthread_join(thread1, NULL);
            }
            else
            {
                pid_t pid;
                pid = fork();
                if (pid == 0)
                {
                    execvp("/home/raj/Files/Shell/./ls", get);
                    exit(0);
                }
                else
                {
                    wait((int *)NULL);
                }
            }
        }
        else if (strcmp(get[0], "rm") == 0)
        {
            if (strcmp(get[size - 1], "&t") == 0)
            {
                char *data = (char *)malloc(100 * sizeof(char));
                strcat(data, "/home/raj/Files/Shell/./rm");
                for (int i = 1; i < size - 1; i++)
                {
                    strcat(data, " ");
                    strcat(data, get[i]);
                }
                pthread_t thread1;
                pthread_create(&thread1, NULL, run_c, data);
                pthread_join(thread1, NULL);
            }
            else
            {
                pid_t pid;
                pid = fork();
                if (pid == 0)
                {
                    execvp("/home/raj/Files/Shell/./rm", get);
                    exit(0);
                }
                else
                {
                    wait((int *)NULL);
                }
            }
        }
        else if (strcmp(get[0], "date") == 0)
        {
            if (strcmp(get[size - 1], "&t") == 0)
            {
                char *data = (char *)malloc(100 * sizeof(char));
                strcat(data, "/home/raj/Files/Shell/./date");
                for (int i = 1; i < size - 1; i++)
                {
                    // printf("HELLO");
                    strcat(data, " ");
                    strcat(data, get[i]);
                }
                pthread_t thread1;
                pthread_create(&thread1, NULL, run_c, data);
                pthread_join(thread1, NULL);
            }
            else
            {
                pid_t pid;
                pid = fork();
                if (pid == 0)
                {
                    execvp("/home/raj/Files/Shell/./date", get);
                    exit(0);
                }
                else
                {
                    wait((int *)NULL);
                }
            }
        }
        else if (strcmp(get[0], "cat") == 0)
        {
            if (strcmp(get[size - 1], "&t") == 0)
            {
                char *data = (char *)malloc(100 * sizeof(char));
                strcat(data, "/home/raj/Files/Shell/./cat");
                for (int i = 1; i < size - 1; i++)
                {
                    // printf("HELLO");
                    strcat(data, " ");
                    strcat(data, get[i]);
                }
                pthread_t thread1;
                pthread_create(&thread1, NULL, run_c, data);
                pthread_join(thread1, NULL);
            }
            else
            {
                pid_t pid;
                pid = fork();
                if (pid == 0)
                {
                    execvp("/home/raj/Files/Shell/./cat", get);
                    exit(0);
                }
                else
                {
                    wait((int *)NULL);
                }
            }
        }
        else if (strcmp(get[0], "exit") == 0)
        {
            break;
        }
        else
        {
            printf("ERROR : There is no such command");
            printf("\n");
        }
    }
    return 0;
}