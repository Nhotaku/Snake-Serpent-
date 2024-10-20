#ifndef _SNAKE_H
#define _SNAKE_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TAILLE_SERPENT 20
#define TAILLE_LONGUEUR 1000
#define TAILLE_LARGEUR 900
#define TAILLE_BORDURE 20

typedef enum{
    haut,
    bas,
    droite,
    gauche,
} deplacement;

typedef struct Corps
{
    int x,y;
    struct Corps* next;
}Corps;

typedef struct {
    int x,y;
}Fruit;

void dessiner_fruit (SDL_Renderer *renderer, Fruit fruit);
void ajouter_corps(Corps** tete,int x,int y);
void deplacement_serpent(Corps** tete,deplacement direction);
void dessiner_snake(SDL_Renderer *renderer,Corps* tete);
void libere_snake (Corps* tete);
void dessiner_bordure (SDL_Renderer *renderer);
bool frontiere (Corps* tete);
bool verifier_collision_fruit(Corps* tete, Fruit fruit);
void ajouter_taille(Corps* tete);
Fruit generation_fruit (Corps* serpent);
bool verifier_collision_fruit(Corps* tete, Fruit fruit);

#endif