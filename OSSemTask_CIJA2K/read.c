#include<stdio.h>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>

void handle_sigint(int sig) //A ctrl+c termin�l�sa
{
    signal(SIGTERM,SIG_IGN); //Jelek elkap�sa
    printf("%d jelet kaptam\n", sig); //Jelek ki�r�sa
    _exit(2);
}

int main()
{
    signal(SIGINT, handle_sigint); //F�ggv�nyh�v�s
    char s[1024]; //T�mb deklar�l�sa, m�retad�s
    int fd; //F�jl azonos�t�s
    int sorszam = 1; //List�z�s kezd��rt�k
    while(1) {
        fd=open("mentes",O_RDONLY); //A f�lj megnyitja, de csak olvassa
        if(fd == -1) { //A f�lj l�tez�s�t teszteli
            printf("Fajl nem letezik.\n"); //Ha nem l�tezik, akkor ki�rja
            return 1;
        }
        else {
        read(fd,s,sizeof(s)); //A f�jl t�mbj�t olvassa be
            for(sorszam = 1; sorszam == s[1024]; sorszam++) { //amennyi sz� van, addig sorsz�moz
            printf("%d. %s\n",sorszam, s); //A szavakat sorsz�mozza
            }
            return 0;
        }
        close(fd);
    }
}
