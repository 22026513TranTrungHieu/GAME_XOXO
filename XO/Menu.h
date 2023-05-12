#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <SDL_mixer.h>

class menu{
public:
    menu();
    ~menu() {};

    int MenuRender(SDL_Renderer *gRenderer);
    void init();
    bool endgame()
    {
        return quit;
    }
    SDL_Texture* texture;

protected:
    SDL_Rect mod[3];
    SDL_Rect IMGRect = {0,0,600,600};

private:
    bool quit;
};

