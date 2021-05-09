#include<stdio.h>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<sys/stat.h> //Elnevezett cs�t teszi speci�liss�
#include<fcntl.h> //F�jl manipul�s�t �rja le
#include<signal.h> //Jelek haszn�lata

void sigkezelo(int sig) { //jelkezel� f�ggv�ny
    signal(SIGTERM,SIG_IGN); //Jelek elkap�sa, a SIG_INT a signal f�ggv�nyt seg�ti, a SIG_IGN a jelet ne ignor�lja �s kapja el
    printf("\n%d jelet kaptam \n", sig); //Kapott jelek ki�r�sa
    fflush(stdout); //Tiszt�t�s, konzolba irat�s
    signal(SIGTERM, SIG_DFL);
    _exit(2); //kil�p�s
}

int main(){
    int fd; // A nyitott f�jlt azonos�tja
    signal(SIGINT, sigkezelo); //F�ggv�ny h�v�s, a SIGINT-el a futtat�s el�rehelyez�se
    char szoveg[256]; //A t�mb deklar�l�sa 256 max hossz�s�g� karakterre
    mkfifo("mentes", S_IWUSR | S_IRUSR ); /*L�trehozzuk a "mentes" f�jlt
                                         A S_IWUSR| S_IRUSR pedig �rhat�-olvashat�v� teszi a f�jlt*/
    while(1) {
        scanf("%s", szoveg); //Karakterek beolvas�sa
        fd=open("mentes",O_WRONLY); //fd=open megynitja a f�jlt,
        write(fd, szoveg, 12); //F�jlba �r�s, azonos�t�sa �s sz�veg felismer�se, byteok olvas�sas
        close(fd); //f�jl bez�r�sa
    }
}
