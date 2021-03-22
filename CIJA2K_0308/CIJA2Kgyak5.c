#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int pid;
    int status;

    if ((pid = fork()) < 0)
        perror("fork hiba");
    else if (pid == 0) /* gyermek */
        exit(7);       /* befejez�dik   */
    if (wait(&status) != pid)
        perror("wait hiba"); /*sz�l� */
    if (WIFEXITED(status))
        printf("Norm�lis befejez�d�s, visszaadott �rt�k =%d\n", WEXITSTATUS(status));

    return 0;
}
