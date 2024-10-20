if (IMG_Init(IMG_INIT_PNG) == 0) 
    {
        printf("Erreur d'initialisation de la SDL_Image\n");
        return 1;
    }

SDL_Surface* surface = IMG_Load("bottle.png");
    if (surface == NULL) 
    {
        printf("Error loading image %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) 
    {
        printf("Error creating texture\n");
        return 1;
    }


    #define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define SPEED 25
struct Tail {
  int x,y;
};

SDL_Rect Haut_bordure = {0,0,1000,20};
        SDL_RenderFillRect(renderer,&Haut_bordure);

        SDL_Rect Bas_bordure = {0,900-20,1000,20};
        SDL_RenderFillRect(renderer,&Bas_bordure);

        SDL_Rect Gauche_bordure = {0,0,20,1000};
        SDL_RenderFillRect(renderer,&Gauche_bordure);

        SDL_Rect Droite_bordure = {1000-20,0,20,900};
        SDL_RenderFillRect(renderer,&Droite_bordure);


printf("Fruit généré à x = %d, y = %d\n", Fruit.x, Fruit.y);
    return fruit;