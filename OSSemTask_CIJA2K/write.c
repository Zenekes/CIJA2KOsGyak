#include<stdio.h>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<sys/stat.h> //Elnevezett csõt teszi speciálissá
#include<fcntl.h> //Fájl manipulását írja le
#include<signal.h> //Jelek használata

void sigkezelo(int sig) { //jelkezelõ függvény
    signal(SIGTERM,SIG_IGN); //Jelek elkapása, a SIG_INT a signal függvényt segíti, a SIG_IGN a jelet ne ignorálja és kapja el
    printf("\n%d jelet kaptam \n", sig); //Kapott jelek kiírása
    fflush(stdout); //Tisztítás, konzolba iratás
    signal(SIGTERM, SIG_DFL);
    _exit(2); //kilépés
}

int main(){
    int fd; // A nyitott fájlt azonosítja
    signal(SIGINT, sigkezelo); //Függvény hívás, a SIGINT-el a futtatás elõrehelyezése
    char szoveg[256]; //A tömb deklarálása 256 max hosszúságú karakterre
    mkfifo("mentes", S_IWUSR | S_IRUSR ); /*Létrehozzuk a "mentes" fájlt
                                         A S_IWUSR| S_IRUSR pedig írható-olvashatóvá teszi a fájlt*/
    while(1) {
        scanf("%s", szoveg); //Karakterek beolvasása
        fd=open("mentes",O_WRONLY); //fd=open megynitja a fájlt,
        write(fd, szoveg, 12); //Fájlba írás, azonosítása és szöveg felismerése, byteok olvasásas
        close(fd); //fájl bezárása
    }
}
