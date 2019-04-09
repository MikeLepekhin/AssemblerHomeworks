#include <stdio.h>

int main(int argc, char* argv[]) {
    extern myprintf();
    printf("I'm running the code in С\n");
   
    for (int i = 0; i < 20; ++i) {
        myprintf("Hello %d %b %x!\n", i, i, i);
    }

    printf("\nI have finished\n");
    return 0;
}
