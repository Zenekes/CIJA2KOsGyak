
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int child;
	mkfifo("CIJA2K", S_IRUSR | S_IWUSR);
	child = fork();
	if (child > 0){
		char s[1024];
		int fd;
		fd = open("CIJA2K", O_RDONLY);
		read(fd, s, sizeof(s));
		printf("%s", s);

		close(fd);
		unlink("CIJA2K");
	}
	else if (child == 0){
		int fd;
		fd = open("CIJA2K", O_WRONLY);
		write(fd, "Énekes Zoltán\n", 100);
	}
	return 0;
}
