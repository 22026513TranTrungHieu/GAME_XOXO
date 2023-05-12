/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "bot.h"
#include "Menu.h"
#include <SDL_mixer.h>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

const int Square_Width = 199;
const int Square_Height = 199;
const int TotalSquares = 9;

int modgame;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool xx[9], oo[9];

enum Status{
    Default,
    Mousemotion,
    X,
    O,
    Total
};

SDL_Texture* texture[ Total ];
SDL_Texture* End;
SDL_Texture* Win;
SDL_Texture* Lose;
SDL_Texture* Draw;
SDL_Texture *WinX, *WinO;

//sound
Mix_Chunk* chosingsound;
Mix_Chunk* winsound;
Mix_Chunk* losesound;
Mix_Chunk* drawsound;
Mix_Music* BGsound;



// bao nhiêu ô
const int squares = 3;

// lượt của ai
bool humanround = true;

//đã đi bn nước
int movated = 0;

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Init buttons
		void InitButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e , int i );

		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		Status mCurrentSprite;



};

LButton Button[ TotalSquares ];

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = Default;
}

void LButton::InitButton()
{
    mCurrentSprite = Default;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e , int i)
{
    if( humanround || modgame == 1 )
    {
        //If mouse event happened
        if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

            //Check if mouse is in button
            bool inside = true;

            //Mouse is left of the button
            if( x < mPosition.x )
            {
                inside = false;
            }
            //Mouse is right of the button
            else if( x > mPosition.x + Square_Width )
            {
                inside = false;
            }
            //Mouse above the button
            else if( y < mPosition.y )
            {
                inside = false;
            }
            //Mouse below the button
            else if( y > mPosition.y + Square_Height )
            {
                inside = false;
            }

            //Mouse is outside button
            if( !inside )
            {
                if(mCurrentSprite == Mousemotion)
                    mCurrentSprite = Default;
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                if( mCurrentSprite == Default || mCurrentSprite == Mousemotion )
                    switch( e->type )
                    {
                        case SDL_MOUSEMOTION:
                        mCurrentSprite = Mousemotion;
                        break;

                        case SDL_MOUSEBUTTONDOWN:
                        if(humanround)
                        {
                            mCurrentSprite = X;
                            humanround = false;
                            xx[ i ] = true;
                            movated++;
                            Mix_PlayChannel(-1,chosingsound,0);
                        }
                        else
                            if(modgame == 1)
                        {
                            mCurrentSprite = O;
                            humanround = true;
                            oo[ i ] = true;
                            Mix_PlayChannel(-1,chosingsound,0);
                        }
                        break;
                    }
            }
        }
    }
    else
        if(modgame == 0)
    {
        mCurrentSprite = O;
        humanround = true;
        oo[ i ] = true;
    }
}

void LButton::render()
{
    SDL_Rect RenderIMG = { mPosition.x, mPosition.y, Square_Width, Square_Height};
    SDL_RenderCopy( gRenderer, texture[ mCurrentSprite ], NULL, &RenderIMG );
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//Initialize Audio
				if(Mix_OpenAudio(20000,MIX_DEFAULT_FORMAT, 2, 4000) == -1)
                    return false;
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

    texture[ Default ] = loadTexture( "Main/Default.png" );
    texture[ Mousemotion ] = loadTexture( "Main/Mousemotion.png" );
    texture[ X ] = loadTexture( "Main/X.png" );
    texture[ O ] = loadTexture( "Main/O.png" );
    End = loadTexture( "End/End.png" );
    Win = loadTexture( "Result/Win.png" );
    Lose = loadTexture( "Result/Lose.png" );
    Draw = loadTexture( "Result/Draw.png" );

    WinX = loadTexture( "Result/WinX.png" );
    WinO = loadTexture( "Result/WinO.png" );
    losesound = Mix_LoadWAV("Music/losesound.wav");
    chosingsound = Mix_LoadWAV("Music/chosingsound.wav");
    BGsound = Mix_LoadMUS("Music/BGsound.wav");
    drawsound = Mix_LoadWAV("Music/drawsound.wav");
    winsound = Mix_LoadWAV("Music/winsound.wav");

    Button[0].setPosition( 0, 0);
    Button[1].setPosition( 0, SCREEN_HEIGHT/3 + 1 );
    Button[2].setPosition( 0, SCREEN_HEIGHT/3*2 + 1 );
    Button[3].setPosition( SCREEN_WIDTH/3 + 1, 0);
    Button[4].setPosition( SCREEN_WIDTH/3*2 + 1, 0);
    Button[5].setPosition( SCREEN_WIDTH/3 + 1, SCREEN_HEIGHT/3 + 1);
    Button[6].setPosition( SCREEN_WIDTH/3 + 1, SCREEN_HEIGHT/3*2 + 1);
    Button[7].setPosition( SCREEN_WIDTH/3*2 + 1, SCREEN_HEIGHT/3 + 1);
    Button[8].setPosition( SCREEN_WIDTH/3*2 + 1, SCREEN_HEIGHT/3*2 + 1);
    Mix_PlayMusic(BGsound,-1);
	return success;
}

void close()
{
    for(int i=0; i<Total; i++)
    {
        SDL_DestroyTexture( texture[i] );
        texture[i] = NULL;
    }
    SDL_DestroyTexture( End );
    End = NULL;
    Mix_HaltChannel(-1);
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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

menu Menu;

bool rendergameEnd()
{
    SDL_RenderCopy( gRenderer, End, NULL, NULL );

    SDL_RenderPresent( gRenderer );
    Mix_PlayMusic(BGsound,-1);
    Menu.init();
    while( !Menu.endgame() )
        {
            int x = Menu.MenuRender( gRenderer );
            if( x!=4 )
            {
                modgame = x;
                return 1;
            }
        }
    return 0;
}

void Showgame()
{
    SDL_Texture* Currenttexture = NULL;
    Mix_HaltMusic();
    if( gameEnd(xx) )
    {
        if(modgame == 0)
            Currenttexture = Win;
        else
            Currenttexture = WinX;
        Mix_PlayChannel(-1,winsound,0);
    }
    else
        if( movated == 5 )
        {
            Currenttexture = Draw;
            Mix_PlayChannel(-1,drawsound,0);
        }
        else{

            if(modgame == 0){
                Currenttexture = Lose;
                Mix_PlayChannel(-1,losesound,0);
            }
            else{
                Currenttexture = WinO;
                Mix_PlayChannel(-1,winsound,0);
            }
        }

    SDL_RenderCopy( gRenderer, Currenttexture, NULL, NULL );
    SDL_RenderPresent( gRenderer );
}

int main( int argc, char* args[] )
{

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
            Menu.texture = loadTexture( "Menu/Menu.png" );
        while( !Menu.endgame() )
        {
            int x = Menu.MenuRender( gRenderer );
            if( x!=4 )
            {
                modgame = x;
                break;
            }
        }

		    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
			//Main loop flag
			bool quit = Menu.endgame();
			//Event handler
			SDL_Event e;
			//While application is running
			while( !quit )
			{

			    if( gameEnd(xx) || gameEnd(oo) || movated == 5)
                {
                    Showgame();
                    SDL_Delay(5000);

                    bool ok = rendergameEnd();

                    if(ok)
                    {
                        for(int i=0; i<TotalSquares; i++)
                        {
                            xx[i] = false;
                            oo[i] = false;
                        }

                        humanround = true;
                        movated = 0;

                        for(int i=0; i<TotalSquares; i++)
                        {
//                            SDL_DestroyTexture( texture[i] );
                            Button[ i ].InitButton();
                        }
                    }
                    else
                        quit = true;
                }

			    else
				{//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle button events
					for( int i = 0; i < TotalSquares; ++i )
					{
					    if(modgame == 0)
					    {
					        int bot = 9;
                            if(!humanround)
                            {
                                controlBot( movated, bot, xx, oo);
                                Button[ bot ].handleEvent( &e, bot );
                            }
                            if(i == bot)
                                continue;
					    }

						Button[ i ].handleEvent( &e, i );
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Draw blue horizontal line
				SDL_SetRenderDrawColor( gRenderer, 159, 234, 249 , 0xFF);

				for(int i=1; i<squares; i++)
                {
                    SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 3 * i, SCREEN_WIDTH, SCREEN_HEIGHT / 3 * i );
                    SDL_RenderDrawLine( gRenderer, SCREEN_WIDTH / 3 * i, 0, SCREEN_WIDTH/ 3 * i, SCREEN_HEIGHT );
                }

//                SDL_Rect Position;
//                Position.x = SCREEN_WIDTH / 3 + 1 ;
//                Position.y = SCREEN_HEIGHT / 3 + 1 ;
//                Position.w = SCREEN_WIDTH / 3 -1;
//                Position.h = SCREEN_HEIGHT / 3 -1;
//                SDL_RenderCopy( gRenderer, Currenttexture, NULL, &Position);

//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//				SDL_RenderClear( gRenderer );

				for(int i=0; i<TotalSquares; i++)
                {
                    Button[i].render();
                }


                //Update screen
				SDL_RenderPresent( gRenderer );
				}
			}
		}
	}


	//Free resources and close SDL
	close();

	return 0;
}

