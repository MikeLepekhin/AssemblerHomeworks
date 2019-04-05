#include <stdio.h>

int main(int argc, char* argv[]) {
    extern myprintf();
    printf("I'm running the code in С\n");
    
    myprintf();

    printf("I have finished\n");
    return 0;
}
