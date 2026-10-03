#include "generateur.h"

#define VALEUR_INITIALE 1
#define PAS_PAR_DEFAUT 1

static int valeur_initiale = VALEUR_INITIALE;
static int valeur_courante = VALEUR_INITIALE;
static int pas          = PAS_PAR_DEFAUT;

void generateur_definir_premier(int valeur) { valeur_initiale = valeur; }
void generateur_definir_pas(int nouveau_pas) { pas = nouveau_pas; }
void generateur_aller_au_debut(void) { valeur_courante = valeur_initiale; }
int  generateur_suivant(void) {
    int n = valeur_courante;
    valeur_courante += pas;
    return n;
}