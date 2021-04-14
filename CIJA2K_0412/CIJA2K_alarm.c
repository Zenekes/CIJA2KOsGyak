#include <unistd.h>
#include <signal.h>
#define SECOND 1

void do_nothing();
void do_int();

main ()
{
	int i;
	unsigned sec=1;

	signal(SIGINT, do_int);

    for (i=1;i<8;i++) {
        alarm(sec);
        signal(SIGALRM, do_nothing);
        printf("  %d Varok de meddig?\n",i);
        pause();
    }
}
void do_nothing(){ ;}

void do_break(){
	printf("Megszakitas jott!\n");
	signal(SIGINT, SIG_IGN);
}
