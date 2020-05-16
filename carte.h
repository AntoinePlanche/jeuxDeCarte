#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED
#include "define.h"

Carte* createCart(int nbr);
void display(Carte* jeux,int nbr);
void displayType(Type type);
void displayValue(Valeur value);
Carte* sortJeux(Carte* jeux, int nbr);
Carte* sortType(Carte *jeux, int nbr);
Jeux* deliverJeux(Carte *jeux,int nbr,int nbrJoueur);
int winner(Jeux* mainPlayer,int nbrCarte,int nbrPlayer);
int winnerOnValue(Jeux* mainPlayer,int nbrCarte,int nbrPlayer);
int max(int* array, int size);
int indexMaxWithoutEquality(int* array, int size);

#endif // CARTE_H_INCLUDED
