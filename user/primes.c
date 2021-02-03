#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime_filter(int);

int main(void)
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        prime_filter(p[0]);
    }
    else
    {
        close(p[0]);
        for (int i = 2; i <= 35; ++i)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}

void prime_filter(int left_pipe)
{
    int prime, num;
    read(left_pipe, &prime, sizeof(int));
    printf("prime %d\n", prime);
    int right_pipe[2] = {0};
    while (read(left_pipe, &num, sizeof(int)) == 4)
    {
        if (num % prime)
        {
            if (right_pipe[1])
            {
                write(right_pipe[1], &num, sizeof(int));
            }
            else
            {
                pipe(right_pipe);
                if (fork() == 0)
                {
                    close(right_pipe[1]);
                    prime_filter(right_pipe[0]);
                    exit(0);
                }
                else
                {
                    close(right_pipe[0]);
                    write(right_pipe[1], &num, sizeof(int));
                }
            }
        }
    }
    if (right_pipe[1])
    {
        close(right_pipe[1]);
        wait(0);
    }
}