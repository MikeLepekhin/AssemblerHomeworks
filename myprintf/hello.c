#include <stdio.h>

int main(int argc, char* argv[]) {
    extern myprintf();
    printf("I'm running the code in С\n");
   
    for (int i = 10; i < 12; ++i) {
        myprintf("Hello %d %b %x, %d %d %d %s! \n", i, i, i, i, i, i, "dear friends");
    }


    printf("\nI have finished\n");
    return 0;
}
