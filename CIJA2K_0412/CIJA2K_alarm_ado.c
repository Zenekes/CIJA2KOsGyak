#include <sys/types.h>
#include <signal.h>

main(int argc, char **argv)
{
	int pid;

	if (argc < 1)
	{
		perror("Hiba!\n");
		exit(1);
	}

	pid = atoi(argv[1]);

	kill(pid, SIGALRM);

	return 0;
}
