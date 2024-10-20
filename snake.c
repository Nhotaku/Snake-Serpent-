#include "snake.h"

Corps* creation_corps(int x,int y){
    Corps* nouveau_corps = (Corps*)malloc(sizeof (Corps));
    nouveau_corps->x = x;
    nouveau_corps->y = y;
    nouveau_corps->next = NULL;
    return nouveau_corps;
}

void ajouter_corps(Corps** tete,int x,int y){
    Corps* nouveau_corps = creation_corps (x,y);
    nouveau_corps->next = *tete;
    *tete = nouveau_corps;
}

void ajouter_taille(Corps* tete){
    Corps* suivi_tete=tete;
    while (suivi_tete->next != NULL)
    {
        suivi_tete = suivi_tete->next;
    }
    suivi_tete->next = creation_corps(suivi_tete->x,suivi_tete->y);
}

void deplacement_serpent(Corps** tete,deplacement direction){
    if(*tete == NULL) return;

    int ancienne_tete_x = (*tete)->x;
    int ancienne_tete_y = (*tete)->y;

    switch (direction)
    {
    case haut:
        (*tete)->y -= TAILLE_SERPENT;
        break;

    case bas:
        (*tete)->y += TAILLE_SERPENT;
        break;

    case droite:
        (*tete)->x += TAILLE_SERPENT;
        break;
     case gauche:
        (*tete)->x -= TAILLE_SERPENT;
        break;
    }
    Corps* suivi_tete = (*tete)->next;

    while (suivi_tete != NULL){
        int tmp_x = suivi_tete->x;
        int tmp_y = suivi_tete->y;
        suivi_tete->x = ancienne_tete_x;
        suivi_tete->y = ancienne_tete_y;
        ancienne_tete_x = tmp_x;
        ancienne_tete_y = tmp_y;
        suivi_tete = suivi_tete->next;
    }
}

void dessiner_snake(SDL_Renderer *renderer,Corps* tete){

    SDL_SetRenderDrawColor(renderer,0,15,75,255);
    Corps* suivi_tete = tete;
    while (suivi_tete != NULL){
        SDL_Rect rect = {suivi_tete->x, suivi_tete->y,TAILLE_SERPENT,TAILLE_SERPENT};
        SDL_RenderFillRect(renderer,&rect);
        suivi_tete = suivi_tete->next;
    }
}

void libere_snake (Corps* tete){
    Corps* suivi_tete = tete;
    while (suivi_tete != NULL)
    {
        Corps* next = suivi_tete->next;
        free (suivi_tete);
        suivi_tete = next;
    }  
}

void dessiner_bordure (SDL_Renderer *renderer){

    SDL_SetRenderDrawColor (renderer,255,0,0,255);

    SDL_Rect haut_bordure = {0,0,TAILLE_LONGUEUR,TAILLE_BORDURE};
    SDL_RenderFillRect (renderer, &haut_bordure);

    SDL_Rect bas_bordure = {0,TAILLE_LARGEUR - TAILLE_BORDURE,TAILLE_LONGUEUR,TAILLE_BORDURE};
    SDL_RenderFillRect (renderer, &bas_bordure);

    SDL_Rect droite_bordure = {TAILLE_LONGUEUR - TAILLE_BORDURE,0,TAILLE_BORDURE,TAILLE_LONGUEUR};
    SDL_RenderFillRect (renderer, &droite_bordure);

    SDL_Rect gauche_bordure = {0,0,TAILLE_BORDURE,TAILLE_LONGUEUR};
    SDL_RenderFillRect (renderer, &gauche_bordure);
}

bool frontiere (Corps* tete){
    if (tete->x < TAILLE_BORDURE || tete->x +TAILLE_SERPENT > TAILLE_LONGUEUR-TAILLE_BORDURE || 
        tete->y < TAILLE_BORDURE || tete->y +TAILLE_SERPENT > TAILLE_LARGEUR-TAILLE_BORDURE)
    {
        return true;
    }
    return false;
}

Fruit generation_fruit (Corps* serpent){
    Fruit fruit;
    bool validation = false;
    int essais = 0;

    while (!validation)
    {
        fruit.x = (rand() % ((TAILLE_LONGUEUR - 2 * TAILLE_BORDURE) / TAILLE_SERPENT)) * TAILLE_SERPENT + TAILLE_BORDURE;
        fruit.y = (rand() % ((TAILLE_LARGEUR - 2 * TAILLE_BORDURE) / TAILLE_SERPENT)) * TAILLE_SERPENT + TAILLE_BORDURE;

        validation = true;
        Corps* suivi_tete = serpent;
        while (suivi_tete != NULL)
        {
            if (suivi_tete->x == fruit.x && suivi_tete->y == fruit.y)
            {
                validation = false;
                break;
            }
            suivi_tete = suivi_tete->next;
        }
    }
}

void dessiner_fruit (SDL_Renderer *renderer, Fruit fruit){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_Rect rect = {fruit.x, fruit.y, TAILLE_SERPENT, TAILLE_SERPENT};
    SDL_RenderFillRect(renderer, &rect);
}

bool verifier_collision_fruit(Corps* tete, Fruit fruit){
return(tete->x == fruit.x && tete->y == fruit.y);
}