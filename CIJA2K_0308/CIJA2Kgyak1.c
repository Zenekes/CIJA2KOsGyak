#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    system("date");
    // nem l�tez�
    system("hello");

    return 0;
}
