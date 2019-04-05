#include <stdio.h>

int main(int argc, char* argv[]) {
    extern myprintf();
    printf("I'm running the code in С\n");
   
    for (int i = 0; i < 10; ++i) {
        myprintf("hello!");
        printf("\n");
    }

    printf("\nI have finished\n");
    return 0;
}
