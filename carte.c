#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include"carte.h"

Carte* createCart(int nbr)
{

    Carte* jeux = (Carte*)malloc(sizeof(Carte)*nbr);
    if(jeux == NULL)
    {
        printf("echec de l'allocation");
        exit(0);
    }
    for( int i = 0; i<nbr; i++ )
    {
        jeux[i].type = (Type)rand()%4;
        jeux[i].value = (Valeur)rand()%8;
    }
    display(jeux,nbr);
    return jeux;
}

void display(Carte* jeux,int nbr)
{
    for(int i = 0; i<nbr; i++)
    {
        printf("le type de la carte %i est ",i);
        displayType(jeux[i].type);
        printf(" et sa valeur est ");
        displayValue(jeux[i].value);
    }

}

void displayType(Type type)
{
    if (type == Coeur )
    {
        printf("coeur");
    }
    else if (type == Pique)
    {
        printf("pique");
    }
    else if (type == Carreau)
    {
        printf("carreau");
    }
    else
    {
        printf("trefle");
    }
}


void displayValue(Valeur value)
{

    switch((int)value)
    {
        case 0 : printf("sept\n");
                    break;
        case 1 : printf("huit\n");
                    break;
        case 2 : printf("neuf\n");
                    break;
        case 3 : printf("dix\n");
                    break;
        case 4 : printf("valet\n");
                    break;
        case 5 : printf("dame\n");
                    break;
        case 6 : printf("roi\n");
                    break;
        case 7 : printf("as\n");
                    break;
        default : printf("erreur");

    }

}

Carte* sortJeux(Carte* jeux, int nbr) // trie par valeur puis couleur (trie par permutation)
{
    for( int i = 1; i<nbr; i++)
    {
        if(jeux[i].value < jeux[i-1].value)
        {
            int k = 0;
            while(jeux[k].value < jeux[i].value)
            {
                k++;
            }
            Carte temp;
            for (int j = (i-1); j >= k; j--)
            {
                temp.value = jeux[j+1].value;
                temp.type = jeux[j+1].type;
                jeux[j+1].value = jeux[j].value;
                jeux[j+1].type = jeux[j].type;
                jeux[j].value = temp.value;
                jeux[j].type = temp.type;
            }
        }
    }
    return sortType(jeux,nbr);
}

Carte* sortType(Carte *jeux, int nbr) // 1:Pique 2:Trefle 3:Carreau 4:Coeur
{
    int i = 0;
    int fluentIndice = 0;
    int nbrCarteParValeur = 0;
    while(i<8)
    {

        while(jeux[nbrCarteParValeur].value == jeux[nbrCarteParValeur+1].value && nbrCarteParValeur < nbr)
        {
                nbrCarteParValeur++;
        }
        nbrCarteParValeur++;

        for( int u = fluentIndice+1; u < (nbrCarteParValeur); u++)
        {
            if(jeux[u].type < jeux[u-1].type)
            {
                int k = fluentIndice;
                while(jeux[k].type < jeux[u].type)
                {
                    k++;
                }
                Type temp;
                for (int j = (u-1); j >= k; j--)
                {
                    temp = jeux[j+1].type;
                    jeux[j+1].type = jeux[j].type;
                    jeux[j].type = temp;
                }
            }
        }
        fluentIndice = nbrCarteParValeur;
        i++;
    }
    return jeux;
}


Jeux* deliverJeux(Carte* jeux,int nbr,int nbrJoueur)
{
    Jeux* mainPlayer = (Jeux*)malloc(sizeof(Jeux)*nbrJoueur);
    for(int i = 0; i<nbrJoueur; i++)
    {
        mainPlayer[i] = (Carte*)malloc(sizeof(Carte)*(nbr/nbrJoueur));
        int k = 0;
        for(int j = 0; j<nbr/nbrJoueur; j++)
        {
            k = i*(nbr/nbrJoueur)+j;
            mainPlayer[i][j] = jeux[k];
        }
    }
    return mainPlayer;
}


int winner(Jeux* mainPlayer,int nbrCarte,int nbrPlayer) // 1 : joueur qui a le plus de carte de la même couleur /si égalité / 2:
{
    int *nbrCarteMemeCouleurParJoueur = (int*)malloc(sizeof(int)*nbrPlayer); // // tableau qui contient le nombre de cartes de la même couleur qui réapparaient le plus de fois dans le paquet de chaque par joueur.
    for(int i = 0; i<nbrPlayer; i++)
    {
        int trefle = 0;
        int coeur = 0;
        int carreau = 0;
        int pique = 0;
        for(int j = 0; j<nbrCarte; j++)
        {
            switch((int)mainPlayer[i][j].type)
            {
                case 0 : pique++;
                    break;
                case 1 : trefle++;
                    break;
                case 2 : carreau++;
                    break;
                default : coeur++;
            }
        }
        int T[4] = {trefle,carreau,coeur,pique};
        nbrCarteMemeCouleurParJoueur[i] = max(T,4);
    }
    if(indexMaxWithoutEquality(nbrCarteMemeCouleurParJoueur,nbrPlayer) == -1)
    {
        free(nbrCarteMemeCouleurParJoueur);
        return winnerOnValue(mainPlayer,nbrCarte,nbrPlayer);
    }

    int result = indexMaxWithoutEquality(nbrCarteMemeCouleurParJoueur,nbrPlayer); // pour liberer nbrCarteMemeValeurParJoueur
    free(nbrCarteMemeCouleurParJoueur);
    return (result + 1);

}


int winnerOnValue(Jeux* mainPlayer,int nbrCarte,int nbrPlayer)
{

    int *nbrCarteMemeValeurParJoueur = (int*)malloc(sizeof(int)*nbrPlayer); // tableau qui contient le nombre de cartes de la même valeur qui réapparaient le plus de fois dans le paquet de chaque par joueur.
    for(int i = 0; i<nbrPlayer; i++)
    {
        int sept = 0;
        int huit = 0;
        int neuf = 0;
        int dix = 0;
        int valet = 0;
        int dame = 0;
        int roi = 0;
        int as = 0;
        for(int j = 0; j<nbrCarte; j++)
        {
            switch((int)mainPlayer[i][j].value)
            {
                case 0 : sept++;
                    break;
                case 1 : huit++;
                    break;
                case 2 : neuf++;
                    break;
                case 3 : dix++;
                    break;
                case 4 : valet++;
                    break;
                case 5 : dame++;
                    break;
                case 6 : roi++;
                    break;
                default : as++;
            }
        }
        int T[8] = {sept,huit,neuf,dix,valet,dame,roi,as};
        nbrCarteMemeValeurParJoueur[i] = max(T,8);
    }

    if(indexMaxWithoutEquality(nbrCarteMemeValeurParJoueur,nbrPlayer) == -1)
    {
        free(nbrCarteMemeValeurParJoueur);
        return -1;
    }

    int result = indexMaxWithoutEquality(nbrCarteMemeValeurParJoueur,nbrPlayer); // pour liberer nbrCarteMemeValeurParJoueur
    free(nbrCarteMemeValeurParJoueur);
    return (result + 1);

}


int max(int* array, int size)
{
    int maximum = array[0];
    for(int i = 1; i<size; i++)
    {
        if (maximum < array [i])
        {
            maximum = array[i];
        }
    }
    return maximum;
}



int indexMaxWithoutEquality(int* array, int size)
{
    int maximum = max(array,size);
    int counter = 0;
    for(int i = 0; i<size; i++)
    {
        if(maximum == array[i])
        {
            counter++;
        }
    }
    int temp;
    if(counter >= 2)
    {
        return (-1);
    }
    else
    {

        for(int i = 0; i<size; i++)
        {
            if(maximum == array[i])
            {
                temp = i;
            }
        }
    }
    return temp;
}














