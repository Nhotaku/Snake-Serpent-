#include "snake.h"

int main(){

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error SDL2 Init : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_LONGUEUR, TAILLE_LARGEUR, 0);

    if (window == NULL) 
    {
        printf("Error while creating a window : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Erreur à la création du renderer\n");
        SDL_Quit();
        return 1;
    }
    
    Corps* serpent = NULL;
    deplacement direction = droite;
    ajouter_corps(&serpent, TAILLE_LONGUEUR / 2, TAILLE_LARGEUR / 2);
    for (int i = 0; i < 5; i++)
    {
        ajouter_corps(&serpent,(TAILLE_LONGUEUR / 2) - i * TAILLE_SERPENT, TAILLE_LARGEUR / 2);
    }
    
    Fruit fruit = generation_fruit  (serpent);
    dessiner_fruit (renderer, fruit);

    int iq = 1;
    SDL_Event event;

    while (iq)
    {
        while (SDL_PollEvent(&event))
        {
            
            if (event.type == SDL_QUIT)
            {
                iq = 0;
            }else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (direction != bas) direction = haut;
                    break;
                case SDLK_DOWN:
                    if (direction != haut) direction = bas;
                    break;
                case SDLK_RIGHT:
                    if (direction != gauche) direction = droite;
                    break;
                case SDLK_LEFT:
                    if (direction != droite) direction = gauche;
                    break;
                }
            }
        }
        deplacement_serpent(&serpent, direction);

        if (frontiere(serpent)){
            printf("PERDU VOUS AVEZ !\n");
            iq = 0;
        }

        if (verifier_collision_fruit(serpent, fruit)){
            printf("C'est bon ?\n");
            ajouter_taille(serpent);
            fruit = generation_fruit(serpent);
        }
        
        Fruit fruit = generation_fruit (serpent);
        dessiner_fruit (renderer, fruit);

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        dessiner_bordure (renderer);

        dessiner_snake(renderer, serpent);

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_Quit();
    return 0;
}