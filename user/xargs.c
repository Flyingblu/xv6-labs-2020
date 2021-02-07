#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define BUF_SIZE 512

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: xargs COMMAND [INITIAL_ARGS]");
        exit(0);
    }
    char buf[BUF_SIZE];
    while (1)
    {
        uint cnt = 0;
        char input;
        for (int read_res = read(0, &input, 1); input != '\n' && read_res != 0 && cnt < BUF_SIZE - 1; read_res = read(0, &input, 1))
        {
            buf[cnt++] = input;
        }
        buf[cnt] = 0;
        if (!cnt)
            break;
        if (fork() == 0)
        {
            char **args = malloc(sizeof(char *) * (argc + 1));
            args[0] = argv[1];
            memcpy(args + 1, argv + 2, sizeof(char *) * (argc - 2));
            args[argc - 1] = buf;
            args[argc] = 0;
            exec(argv[1], args);
            fprintf(2, "xargs: failed to exec");
        }
        else
        {
            wait((int *)0);
        }
    }
    exit(0);
}