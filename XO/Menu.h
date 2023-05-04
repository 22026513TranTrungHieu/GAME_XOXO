#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <SDL_mixer.h>

class menu{
public:
    menu(const char* path);
    ~menu() {};

    int MenuRender();

protected:
    SDL_Rect mod[3];
    SDL_Rect IMGRect = {0,0,600,600};
    SDL_Texture texture;
};

