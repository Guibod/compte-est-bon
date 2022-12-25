#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int resolution(int *sample, int nb, int target, char **operations);
int *cloneIntArray(int const *src, size_t len);

int main() {
  int nb = 6;
  int sample[6] = {10, 1, 25, 9, 3, 6};
  int target = 595;

  char **operations = malloc((nb + 4) * sizeof *operations);
  int i;
  if (operations)
    for (i = 0; i < (nb + 4); i++)
      operations[i] = malloc(256 * sizeof *operations[i]);
  operations[0] = "+";
  operations[1] = "-";
  operations[2] = "/";
  operations[3] = "*";

  int res = resolution(sample, nb, target, operations);
  if (res == 0) {
    printf("A solution was found !\n");
    for (i = nb + 4 - 1; i > 4; --i) {
      printf("%s\n", operations[i]);
    }
    return 0;
  }

  printf("No solution was found!\n");
  return 1;
}

/**
 * @param sample
 * @param nb
 * @param target
 * @param operations
 * @return int
 */
int resolution(int *sample, int nb, int target, char **operations) {
  int i, j, k;
  // tout les nombres sample[i] Faire
  for (i = 0; i < nb; ++i) {
    // Pour tout les nombres sample[j] Faire
    for (j = 0; j < nb; ++j) {
      // avec i! = j
      if (i == j) {
        continue;
      }

      // Pour tout les 4 op´erations
      for (k = 0; k < 4; ++k) {
        // Sauvegarder l’´etat du tableau sample
        int *backup = cloneIntArray(sample, nb);

        int res = -1;
        char op = operations[k][0];
        int val1 = sample[i];
        int val2 = sample[j];

        // Effectuer le calcul sample[i] operation sample[j]
        if (strcmp(operations[k], "+") == 0) {
          res = sample[i] + sample[j];
        } else if (strcmp(operations[k], "-") == 0) {
          res = sample[i] - sample[j];
        } else if (strcmp(operations[k], "/") == 0) {
          res = sample[i] / sample[j];
        } else if (strcmp(operations[k], "*") == 0) {
          res = sample[i] * sample[j];
        }

        // Mettre le r´esultat dans sample[i]
        sample[i] = res;

        // Mettre le dernier nombre non utilis´e sample[nb − 1] `a la place de
        // sample[j]
        sample[j] = sample[nb - 1];

        // Si le r´esultat est la target OU resolution(sample, nb-1, target,
        // operations) == 0 Alors
        if (res == target ||
            resolution(sample, nb - 1, target, operations) == 0) {
          sample = backup;
          sprintf(operations[nb + 4 - 1], "%d %c %d = %d", val1, op, val2, res);
          return 0;
        }

        sample = backup;
      }
    }
  }
  return 1;
}

/**
 * clone an integer array
 *
 * @param src
 * @param len
 * @return
 */
int *cloneIntArray(int const *src, size_t len) {
  int *p = malloc(len * sizeof(int));
  memcpy(p, src, len * sizeof(int));
  return p;
}
