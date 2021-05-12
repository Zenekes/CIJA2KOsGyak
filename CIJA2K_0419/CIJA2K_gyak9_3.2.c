#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_kezel();

int main() {
    int pid = getpid();
    printf("pid: %d\n", pid);
    printf("varakozas...\n");
    signal(SIGALRM, signal_kezel);
    pause();
    printf("kesz\n");
}
void signal_kezel() {
    printf("G2SKZ4\n");
}
