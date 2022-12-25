#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int resolution(int* tirage, int nb, int cible, char** operations);
int * intdup(int const * src, size_t len);


int main() {
    int nb = 6;
    int tirage[6] = {10, 1, 25, 9, 3, 6};
    int cible = 595;
//    int nb = 3;
//    int tirage[3] = {10, 1, 2};
//    int cible = 8;
//    int nb = 2;
//    int tirage[2] = {10, 2};
//    int cible = 20;

    char **operations = malloc((nb + 4) * sizeof *operations);
    int i;
    if (operations)
        for (i = 0; i < (nb+4); i++)
            operations[i] = malloc(256 * sizeof *operations[i]);
    operations[0] = "+";
    operations[1] = "-";
    operations[2] = "/";
    operations[3] = "*";

    int res = resolution(tirage, nb, cible, operations);
    for (i=nb + 4 - 1; i > 4; --i) {
        printf("%s\n", operations[i]);
    }
    return 0;
}

int resolution(int* tirage, int nb, int cible, char** operations) {
    int i, j, k;
    // tout les nombres tirage[i] Faire
    for (i=0; i < nb; ++i) {
        // Pour tout les nombres tirage[j] Faire
        for (j=0; j < nb; ++j) {
            // avec i! = j
            if (i == j) {
                continue;
            }

            // Pour tout les 4 op´erations
            for (k=0; k < 4; ++k) {
                // Sauvegarder l’´etat du tableau tirage
                int* backup = intdup(tirage, nb);

                int res;
                char op = operations[k][0];
                int val1 = tirage[i];
                int val2 = tirage[j];

                // Effectuer le calcul tirage[i] operation tirage[j]
                if (strcmp(operations[k],"+") == 0) {
                    res = tirage[i] + tirage[j];
                } else if (strcmp(operations[k],"-") == 0) {
                    res = tirage[i] - tirage[j];
                } else if (strcmp(operations[k],"/") == 0) {
                    res = tirage[i] / tirage[j];
                } else if (strcmp(operations[k],"*") == 0) {
                    res = tirage[i] * tirage[j];
                }

                // Mettre le r´esultat dans tirage[i]
                tirage[i] = res;

                // Mettre le dernier nombre non utilis´e tirage[nb − 1] `a la place de tirage[j]
                tirage[j] = tirage[nb - 1];

                // Si le r´esultat est la cible OU resolution(tirage, nb-1, cible, operations) == 0 Alors
                if (res == cible || resolution(tirage, nb-1, cible, operations) == 0) {
                    tirage = backup;
                    sprintf(operations[nb + 4 - 1], "%d %c %d = %d", val1, op, val2, res);
                    return 0;
                }

                tirage = backup;
            }
        }
        return 1;
    }
//    10: //On a trouv´e une solution, soit imm´ediatement (resultat=cible)
//    11: //soit en continuant les op´erations avec les nb-1 nombres restants
//    12: //On met l’operation et les nombres dans le tableau operations
//    13: Mettre les nombres, l’op´eration utilis´es et le r´esultat dans le tableau operations
//    14: Restaurer les valeurs du tableau tirage
//    15: return 0 ;
//    16: Fin Si
//    17: // tirage[i] operation tirage[j] ne mˆene pas `a une solution.
//    18: // On essaye une autre op´eration ou un autre couple i,j
//    19: Restaurer les valeurs du tableau tirage
//    20: Fin Pour
//    21: Fin Pour
//    22: Fin Pour
//    23: //Aucune solution possible si on arrive ici
//    24: return 1 ;
}

int * intdup(int const * src, size_t len)
{
    int * p = malloc(len * sizeof(int));
    memcpy(p, src, len * sizeof(int));
    return p;
}
