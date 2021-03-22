#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    system("date");
    // nem létezõ
    system("hello");

    return 0;
}
