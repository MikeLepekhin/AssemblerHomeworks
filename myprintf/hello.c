#include <stdio.h>

int main(int argc, char* argv[]) {
    extern myprintf();
    printf("I'm running the code in С\n");
   
    for (int i = 1; i <= 10; ++i) {
        myprintf("Hello %b!\n", i);
    }

    printf("\nI have finished\n");
    return 0;
}
