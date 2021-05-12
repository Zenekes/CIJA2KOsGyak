#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

int main(int argc, char** argv)
{
    int pid;

    if (argc < 2) {
        perror("hibas parameter");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!isdigit(argv[1][i])) {
            perror("hibas pid");
            return 1;
        }
    }
    pid = atoi(argv[1]);
    kill(pid, SIGALRM);
    return 0;
}
