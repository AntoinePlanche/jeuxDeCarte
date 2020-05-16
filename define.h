#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED


typedef enum type {
Pique,
Trefle,
Carreau,
Coeur
} Type;

typedef enum valeur {
sept,
huit,
neuf,
dix,
valet,
dame,
roi,
as
} Valeur;

typedef struct carte {
Type type;
Valeur value;
} Carte;

typedef Carte* Jeux;


#endif // DEFINE_H_INCLUDED
