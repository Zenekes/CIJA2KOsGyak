#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

int main() {
    int child = 0;

    if ((child = fork()) == 0) {
        int shmid;
        key_t key;
        int size=512;
        int shmflg;

        key = SHMKEY;
        shmflg = 0;
        if ((shmid=shmget( key, size, shmflg)) < 0) {
            printf("\n Nincs meg szegmens! Keszitsuk el!");
            shmflg = 00666 | IPC_CREAT;
            if ((shmid=shmget( key, size, shmflg)) < 0) {
                perror("\n Az shmget system-call sikertelen!");
                exit(-1);
            }
        } else printf("\n Van mar szegmens!");

        printf("  Az shmid azonositoja %d: \n", shmid);

        exit (0);
    }
    else {
        if (child = fork() == 0) {
            int shmid;
            key_t key;
            int size=512;
            int shmflg;
            struct vmi {
                int  hossz;
                char szoveg[512-sizeof(int)];
            } *segm;
            key = SHMKEY;
            shmflg = 0;
            if ((shmid=shmget( key, size, shmflg)) < 0) {
                perror("\n Az shmget system-call sikertelen!");
                exit(-1);
            }

            shmflg = 00666 | SHM_RND;
            segm = (struct vmi *)shmat(shmid, NULL, shmflg);
            if (segm == (void *)-1) {
                perror(" Sikertelen attach");
                exit (-1);
            }
            if (strlen(segm->szoveg) > 0)
                printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);

            printf("\n Uj szoveget kerek!\n");
            gets(segm->szoveg);
            printf("\n Az uj szoveg: %s\n",segm->szoveg);
            segm->hossz=strlen(segm->szoveg);

            shmdt(segm);

            exit(0);
        }
        else {
            int shmid;
            key_t key;
            int size=512;
            int shmflg;
            int rtn;
            int cmd;
            struct shmid_ds shmid_ds, *buf;
            buf = &shmid_ds;

            key = SHMKEY;
            shmflg = 0;
            if ((shmid=shmget( key, size, shmflg)) < 0) {
                perror("\n Az shmget system-call sikertelen!");
                exit(-1);
            }

        do {
            printf("\n Add meg a parancs szamat ");
            printf("\n 0 IPC_STAT (status) ");
            printf("\n 1 IPC_RMID (torles)   >  ");
            scanf("%d",&cmd);
            } while (cmd < 0 && cmd > 1);

            switch (cmd)
            {
            case 0: rtn = shmctl(shmid, IPC_STAT, buf);
                printf("\n  Segm. meret: %d",buf->shm_segsz);
                printf("\n  Utolso shmop-os proc. pid: %d\n ",buf->shm_lpid);
                break;
            case 1: rtn = shmctl(shmid, IPC_RMID, NULL);
                printf("\n Szegmens torolve\n");
            }
            exit(0);
        }
    }
}
