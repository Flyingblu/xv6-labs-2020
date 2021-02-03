#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{

	int pipefd[2];
	int pipefd2[2];
	pipe(pipefd);
	pipe(pipefd2);

	int pid;
	pid = fork();
	if (pid == 0)
	{
		pid = getpid();
		char byte = 50;
		int write_fd = dup(pipefd2[1]);
		int read_fd = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipefd2[0]);
		close(pipefd2[1]);
		read(read_fd, &byte, 1);
		printf("%d: received ping\n", pid);
		byte = 122;
		write(write_fd, &byte, 1);
	}
	else
	{
		pid = getpid();
		char byte = 233;
		int write_fd = dup(pipefd[1]);
		int read_fd = dup(pipefd2[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipefd2[0]);
		close(pipefd2[1]);
		write(write_fd, &byte, 1);
		read(read_fd, &byte, 1);
		printf("%d: received pong\n", pid);
		wait((int *)0);
	}
	exit(0);
}
