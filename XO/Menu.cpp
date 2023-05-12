#include "Menu.h"

using namespace std;

bool mouseInRect(const SDL_Rect a){
    int x,y;
    SDL_GetMouseState(&x,&y);
    if(x>=a.x and x<=a.x+a.w and y>=a.y and y<=a.y+a.h) return true;
    return false;
}

menu::menu(){
    IMGRect = {0,0,600,600};

    mod[0] = {238,214,241,100};
    mod[1] = {238,342,241,100};
    mod[2] = {238,467,241,100};

    quit = false;
}

void menu::init()
{
    quit = false;
}

int menu::MenuRender(SDL_Renderer *gRenderer){
    SDL_RenderClear(gRenderer);

    SDL_RenderCopy(gRenderer, texture , &IMGRect, NULL);

    SDL_RenderPresent(gRenderer);

    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
    case SDL_QUIT:
        quit = true;
        break;
    case SDL_MOUSEMOTION:
        if(mouseInRect(mod[0])){
            IMGRect = {1200,0,600,600};
        }
        else if(mouseInRect(mod[1])){
            IMGRect = {600,0,600,600};
        }
        else if(mouseInRect(mod[2])){
            IMGRect = {1800,0,600,600};
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(mouseInRect(mod[0]) and SDL_MOUSEBUTTONDOWN) return 0;
        else if(mouseInRect(mod[1]) and SDL_MOUSEBUTTONDOWN) return 1;
        else if(mouseInRect(mod[2]) and SDL_MOUSEBUTTONDOWN) { quit = true;}
        break;
    }
    return 4;
}


