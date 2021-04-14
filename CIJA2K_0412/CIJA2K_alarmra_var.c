#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void do_nothing();

int main(){

    unsigned sec = 5;
    signal(SIGALRM, do_nothing);
    alarm(sec);


    printf("%d varok.\n",1);
    pause();

    printf("Megerkezett az alarm.\n");

 return 0;
}


void do_nothing(){;}
