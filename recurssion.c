#include <stdio.h>

void abir(char eater, int turn) {
    if (turn > 5) {
        return;
    }

    if (eater == 'T') {
        printf("Tanvir eats\n");
        abir('H', turn + 1);
    } else {
        printf("Mushfiq eats\n");
        abir('T', turn + 1);
    }
}

int main(void) {
    char toss;
    scanf(" %c", &toss);

    abir(toss, 1);

    return 0;
}