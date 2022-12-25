#include <stdio.h>

int resolution(int* tirage, int nb, int cible, char** operations);

int main() {
    int nb = 6;
    int tirage[6] = {10, 1, 25, 9, 3, 6};
    int cible = 595;
    char *operations[] = { "+", "-", "/", "*" };

    int res = resolution(tirage, nb, cible, operations);
    printf("%d", res);
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
                int* backup = tirage;
                int resultat;
                // Effectuer le calcul tirage[i] operation tirage[j]
                if (operations[k] == "+") {
                    resultat = tirage[i] + tirage[j];
                } else if (operations[k] == "-") {
                    resultat = tirage[i] - tirage[j];
                } else if (operations[k] == "/") {
                    resultat = tirage[i] / tirage[j];
                } else if (operations[k] == "*") {
                    resultat = tirage[i] * tirage[j];
                }
                // Mettre le r´esultat dans tirage[i]
                tirage[i] = resultat;

                // tirage[j] est utilis´e et maintenant interdit
                // Mettre le dernier nombre non utilis´e tirage[nb − 1] `a la place de tirage[j]
                tirage[j] = tirage[nb - 1];

                // Si le r´esultat est la cible OU resolution(tirage, nb-1, cible, operations) == 0 Alors
                if (resultat == cible || resolution(tirage, nb-1, cible, operations) == 0) {
                    tirage = backup;
                    operations += &"fufuu";
                    return 0;
                }
                tirage = backup;
                printf("%d %s %d\n", tirage[i], operations[k], tirage[j]);
            }
        }
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
