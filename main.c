#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int resolution(int *sample, int nb, int target, char **operations);
int resolutionBest(int *sample, int nb, int target, int minDistance, char **operations);
int* cloneIntArray(int const *src, size_t len);
int parseFile(char* fname, int *nb, int *target, int *sample);
int* randomSample(int nb);
void printProblem(int nb, int target, int* sample);
int compute(int a, int b, char* operator);

int main(int argc, char *argv[]) {
  int nb, target;
  int minDistance = 999999;
  int* sample = NULL;
  sample = malloc(sizeof(int));

  if( argc == 3 ) {
    nb = atoi(argv[1]);
    target = atoi(argv[2]);
    sample = randomSample(nb);
  }
  else if (argc == 2) {
    int ret = parseFile(argv[1], &nb, &target, sample);
    if (ret != 0) {
      fprintf(stderr, "Failed to parse %s", argv[1]);
      return 1;
    }
  } else {
    printf("Combien de cartes ?");
    fscanf (stdin, "%d", &nb);
    printf("Quelle valeur cible ?");
    fscanf (stdin, "%d", &target);
    sample = randomSample(nb);
  };

  char **operations = malloc((nb + 4) * sizeof *operations);
  int i;
  if (operations)
    for (i = 0; i < (nb + 4); i++)
      operations[i] = malloc(256 * sizeof *operations[i]);
  operations[0] = "+";
  operations[1] = "*";
  operations[2] = "/";
  operations[3] = "-";

  printProblem(nb, target, sample);
  int res = resolutionBest(sample, nb, target, minDistance, operations);
  if (res == 0) {
    printf("Une solution au problème a été trouvée !\n");
    for (i = nb + 4 - 1; i > 4; --i) {
      printf("%s\n", operations[i]);
    }
    return 0;
  }

  else if (res) {
    printf("Une solution approximative a été trouvée à une distance de %d:\n", res);
    for (i = nb + 4 - 1; i > 4; --i) {
      printf("%s\n", operations[i]);
    }
    return 0;
  }

  printf("Aucune solution trouvée au problème!\n");
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

        char op = operations[k][0];
        int val1 = sample[i];
        int val2 = sample[j];
        int res = compute(sample[i], sample[j], operations[k]);
        if (res < 0) {
          continue;
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
 * @param sample
 * @param nb
 * @param target
 * @param operations
 * @return int
 */
int resolutionBest(int *sample, int nb, int target, int minDistance, char **operations) {
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

        char op = operations[k][0];
        int val1 = sample[i];
        int val2 = sample[j];

        int res = compute(sample[i], sample[j], operations[k]);

        if (res < 0) {
          continue;
        }

        // Mettre le r´esultat dans sample[i]
        sample[i] = res;

        // Mettre le dernier nombre non utilis´e sample[nb − 1] `a la place de
        // sample[j]
        sample[j] = sample[nb - 1];

        if (minDistance > abs(target - res)) {
          minDistance = abs(target - res);
          sprintf(operations[nb + 4 - 1], "%d %c %d = %d", val1, op, val2, res);
        }

        // Si le r´esultat est la target OU resolution(sample, nb-1, target,
        // operations) == 0 Alors
        if (res == target) {
          sample = backup;
          sprintf(operations[nb + 4 - 1], "%d %c %d = %d", val1, op, val2, res);
          return 0;
        }

        int val;
        val = resolutionBest(sample, nb - 1, target, minDistance, operations);
        if (val == NULL) {
          sample = backup;
          sprintf(operations[nb + 4 - 1], "%d %c %d = %d", val1, op, val2, res);
          return 0;
        }

        if (abs(val) < abs(minDistance)) {
          minDistance = val;
        }

        sample = backup;
      }
    }
  }
  return minDistance;
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

int parseFile(char* fname, int *nb, int *target, int *sample) {
  if(fname == NULL || nb == NULL || target == NULL || sample == NULL) {
    return -1;
  }

  // Opening file in reading mode
  FILE *fp = fopen(fname, "r");
  if (NULL == fp) {
    printf("file %s can't be opened \n", fname);
    return -1;
  }

  if(fscanf(fp, "%d", nb) != 1)
  {
    fprintf(stderr, "Wrong format, expecting nb\n");
    fclose(fp);
    return -1;
  }

  int i;
  for (i=0; i < *nb; ++i) {
    fscanf(fp, "%d", &sample[i]);
  }

  if(fscanf(fp, "%d", target) != 1)
  {
    fprintf(stderr, "Wrong format, expecting target\n");
    fclose(fp);
    return -1;
  }
  fclose(fp);
  return 0;
}

int* randomSample(int nb) {
  int* sample = NULL;
  sample = malloc(sizeof(int));
  if (nb > 24) {
    fprintf(stderr, "Cannot provide a sample of more than 24 numbers, %d requested", nb);
    return sample;
  }

  int i, j;

  int items[24] = {
    1, 1, 2, 2, 3, 3,
    4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9,
    10, 10, 25, 50, 75, 100
  };

  srand(time(NULL));
  for (i=0; i<nb; ++i) {
    j = rand() % (24 - i);
    sample[i] = items[j];
    items[j] = items[23-i];
  }

  return sample;
}

void printProblem(int nb, int target, int* sample) {
  int i;
  printf("==============================\n");
  printf("Valeur à calculer: %d\n", target);
  printf("En utilisant %d valeurs: \n", nb);
  for (i=0; i<nb; i++) {
    printf("  - %d\n", sample[i]);
  }
  printf("==============================\n\n");
}

int compute(int a, int b, char* op) {
  if (strcmp(op, "+") == 0) {
    return a + b;
  }

  if (strcmp(op, "-") == 0) {
    return a - b;
  }

  if (strcmp(op, "/") == 0) {
    if (a % b != 0) {
      return -1;
    }

    if (a == 1 || b == 1) {
      return -1;
    }

    return a / b;
  }

  if (strcmp(op, "*") == 0) {
    if (b == 1 || a == 1) {
      return -1;
    }

    return a * b;
  }

  return -1;
}
