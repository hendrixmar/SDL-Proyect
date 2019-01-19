#include "main.h"

SDL_Surface *screen;
int winX=640, winY=480;
int gLastTick;
int anim=0, avanza=0;
int amplia=0;
int mouX=0, mouY=0, mouse=0;

void putpixel(int x, int y, int color)
{
	if( x<0 || x>=winX || y<0 || y>=winY )
		return;

	unsigned int *ptr = (unsigned int*)screen->pixels;
	int lineoffset = (winY-1-y) * (screen->pitch / 4);
	ptr[lineoffset + x] = color;
}

int getpixel( int x, int y )
{
	if( x<0 || x>=winX || y<0 || y>=winY )
		return( 0 );

	unsigned int *ptr = (unsigned int*)screen->pixels;
	int lineoffset = (winY-1-y) * (screen->pitch / 4);
	//int lineoffset = y * (screen->pitch / 4);
	//return( 0 );
	return( ptr[lineoffset + x] );
}

//Funciones asociadas a la estructura SDL
void initSDL()
{
	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);

	// Attempt to create a 640x480 window with 32bit pixels.
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_RESIZABLE );

	// If we fail, return error.
	if ( screen == NULL )
	{
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		exit(1);
	}

	gLastTick = SDL_GetTicks();
}

void render()
{
	// Lock surface if needed
	if (SDL_MUSTLOCK(screen))
		if (SDL_LockSurface(screen) < 0)
			return;
	//borrar pantalla
	borrar();

	//llamar a despliegue de usuario
	principal();


	// Unlock if needed
	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, winX, winY);
}
void borrar()
{
	int x,y, yofs=0, ofs;

	for (y = 0; y < winY; y++)
	{
		for (x = 0, ofs = yofs; x < winX; x++, ofs++)
		{
			;((unsigned int*)screen->pixels)[ofs] = 0;
		}
		yofs += screen->pitch / 4;
	}

}

