#include"Menu.h"

using namespace std;

bool mouseInRect(const SDL_Rect a){
    int x,y;
    SDL_GetMouseState(&x,&y);
    if(x>=a.x and x<=a.x+a.w and y>=a.y and y<=a.y+a.h) return true;
    return false;
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

menu::menu(const char* path){
    texture = SDL_loadTexture(path);
    IMGRect = {0,0,600,600};

    mod[0] = {238,214,241,100};
    mod[1] = {238,342,241,100};
    mod[2] = {238,467,241,100};
}

int menu::MenuRender(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture , &IMGRect, NULL);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
    case SDL_QUIT:
        exit(0);
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
        else if(mouseInRect(mod[2]) and SDL_MOUSEBUTTONDOWN) return 2;
        break;
    }
    return 4;
}


