#include <stdio.h>
#include <stdlib.h>
#include "generateur.h"

static void usage(const char *prog) {
    fprintf(stderr, "Usage : %s <nombre> [<premier> <pas>]\n", prog);
    fprintf(stderr, "    <nombre>   nombre de symboles (>= 1)\n");
    fprintf(stderr, "    <premier>  valeur de depart (defaut : 1)\n");
    fprintf(stderr, "    <pas>      increment (defaut : 1, non nul)\n");
    fprintf(stderr, "    Exemples :\n");
    fprintf(stderr, "        %s 3\n", prog);
    fprintf(stderr, "        %s 3 10 5\n", prog);
}

int main(int argc, char *argv[]) {
    int n, i;
    int premier = 1, pas = 1;

    if (argc < 2 || argc > 4) { usage(argv[0]); return EXIT_FAILURE; }
    n = atoi(argv[1]);
    if (n <= 0) { usage(argv[0]); return EXIT_FAILURE; }
    if (argc >= 3) premier = atoi(argv[2]);
    if (argc >= 4) {
        pas = atoi(argv[3]);
        if (pas == 0) { usage(argv[0]); return EXIT_FAILURE; }
    }
    generateur_definir_premier(premier);
    generateur_definir_pas(pas);
    generateur_aller_au_debut();
    printf("*- Production de %d symbole%s :\n", n, n > 1 ? "s" : "");
    for (i = 0; i < n; i++)
        printf("\"__GLB_%d__\"\n", generateur_suivant());
    return EXIT_SUCCESS;
}