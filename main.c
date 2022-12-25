#include <stdio.h>

int resolution(int* tirage, int nb, int cible, char** operations) {
    return 1;
}

int main() {
    int nb = 6;
    int tirage[6] = {10, 1, 25, 9, 3, 6};
    int cible = 595;
    char *operations[4] = {"+", "-", "/", "*"};

    int res = resolution(tirage, nb, cible, operations);
    printf("%d", res);
    return 0;
}

