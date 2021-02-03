#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (argc != 2) 
	{
		printf("sleep should be called with one arguement\n");
		exit(1);
	}
	int ticks = atoi(argv[1]);
	sleep(ticks);
	exit(0);
}
