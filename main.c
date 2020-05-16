#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"
#include "carte.h"


int main()
{
    srand(time(NULL));
    int nbr;
    int nbrJoueur;
    printf("Combien y a t-il de carte dans le jeu ?\n");
    scanf("%i",&nbr);
    Carte* jeux = createCart(nbr);
    printf("Combien y a t-il de joueur ?\n");
    scanf("%i",&nbrJoueur);
    Jeux* mainPlayer = NULL;
    mainPlayer = deliverJeux(jeux,nbr,nbrJoueur);
    free(jeux);
    printf("\n");
    for(int i = 0; i<nbrJoueur; i++)
    {
        printf("Main du joueur %i :\n\n",(i+1));
        sortJeux(mainPlayer[i],nbr/nbrJoueur);
        display(mainPlayer[i],nbr/nbrJoueur);
        printf("\n");
    }
    printf("le gagnant de ce jeux est le joueur numero : %i (si le numero est -1 alors il y a egalite)\n",winner(mainPlayer,nbr/nbrJoueur,nbrJoueur));
    return 0;
}
