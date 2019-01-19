#include <stdlib.h>
#if defined(_MSC_VER)
 #include <SDL.h>
#else
 #include <SDL/SDL.h>
#endif


#include <vector>
// Physics iterations per second
#define PHYSICSFPS 60

using namespace std;
//Tamaño de pantalla
extern int winX, winY;	//tamaño ventana
extern int gLastTick, anim,avanza, amplia;
extern SDL_Surface *screen;
extern int mouX, mouY, mouse;
extern int alpha;


int loadTextura( char * archivo );
int getTextu( int x, int y, int ntextu, char *rgb );
void showTextura( int xtar, int ytar, int ntextu );
void initTextura();
void fuego(int xtar, int ytar, double  );
void fuego2(int xtar, int ytar, double  );
int loadBitmap(char * source);
void city();
//Prototipos de SDL
void putpixel(int x, int y, int color);

void winZoom();
void borrar();

void initSDL();
void render();
void idle();



//Prototipos de MAIN
void principal();
void checkEvents();
