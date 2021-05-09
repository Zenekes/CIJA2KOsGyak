#include<stdio.h>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>

void handle_sigint(int sig) //A ctrl+c terminálása
{
    signal(SIGTERM,SIG_IGN); //Jelek elkapása
    printf("%d jelet kaptam\n", sig); //Jelek kiírása
    _exit(2);
}

int main()
{
    signal(SIGINT, handle_sigint); //Függvényhívás
    char s[1024]; //Tümb deklarálása, méretadás
    int fd; //Fájl azonosítás
    int sorszam = 1; //Listázás kezdõérték
    while(1) {
        fd=open("mentes",O_RDONLY); //A fálj megnyitja, de csak olvassa
        if(fd == -1) { //A fálj létezését teszteli
            printf("Fajl nem letezik.\n"); //Ha nem létezik, akkor kiírja
            return 1;
        }
        else {
        read(fd,s,sizeof(s)); //A fájl tömbjét olvassa be
            for(sorszam = 1; sorszam == s[1024]; sorszam++) { //amennyi szó van, addig sorszámoz
            printf("%d. %s\n",sorszam, s); //A szavakat sorszámozza
            }
            return 0;
        }
        close(fd);
    }
}
