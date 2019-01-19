#include "main.h"


//Para ventana auxiliar
//SDL_Surface *auxiliar;

// Prototipos
void idle();
void init();
void checkEvents();
double i[2]={5,5},j[2]={5,5}, z[2]={5,5}, E=0, T=0,   U=0;
int L= 0;
extern double N;

void principal()
{

    if(  L < 1920){ //escena metro

        showTextura(0 -L %640,120,30);
        showTextura(640 -L %640,120,30);
        showTextura(0,70+ rand()%15,31);
        showTextura(100,100+ rand()%15,32);
        L+=5;
    }

    else if(N  < 2000 ) // Escena de la ciudad siendo atacada
        city();

    else if(N  < 5000 ){ // escena del edificio

        city();
        if(rand()% 2)showTextura(120,100+U,27 );
        if(U < 150) U += 1;
    }

    else { //portada final

        showTextura(0,0,29);



    }




}



void city(){

     if(935 >= z[0]){
        i[1] = i[0] += .3;
        j[1] = j[0] += .2;
        z[1] = z[0] += 4.5;
        showTextura(5-j[0],50,0);
        showTextura(5-i[0],50,1);
        showTextura(5-z[0],50,2);

        fuego2(150-i[1],100, abs(i[0]));
        fuego2(245-i[1],187, abs(i[0]));
        fuego2(275-i[1],167, abs(j[0]));
        fuego2(465-i[1],187, abs(j[0]));

        fuego(120-j[1],250, abs(j[0]));
        fuego(340-j[1],200, abs(j[0]));

        fuego(140-i[1],180, abs(j[0]));

        fuego2(600-i[1],140, abs(j[0]));
    }
    else{

        if(E  < 300){
            showTextura(5-j[0],50,0);
            showTextura(5-i[0],50,1);
            showTextura(5-z[0],50,2);

            fuego2(150-i[1],100, abs(i[0]));
            fuego2(245-i[1],187, abs(i[0]));
            fuego2(275-i[1],167, abs(j[0]));
            fuego2(465-i[1],187, abs(j[0]));

            fuego(120-j[1],250, abs(j[0]));
            fuego(340-j[1],200, abs(j[0]));

            fuego(140-i[1],180, abs(j[0]));

            fuego2(600-i[1],140, abs(j[0]));



        }
        if(T > 500){
            E += 10;
            N += 10;



            if(E > 1000 ) E = 500;
            showTextura(70,  -1200+E,4);
            showTextura(70,  -700+E,4);


        }else{
            T += 2.5;



            showTextura(570-T,  -1200,4);
            showTextura(570-T,  -700,4);


        }



        i[0] += .3;
        j[0] += .2;
        z[0] += 2.5;

    }




    if( z[0] > 100 && z[0] < 1100) showTextura(640-z[0]+20,50,3);



}

// Entry point
int main(int argc, char *argv[])
{

	initSDL();
	init();     //inicializar valores iniciales
	initTextura();
	render();   //dibujar
	idle();     //se llamará esta función una y otra vez

	return 0;
}


void init()
{
	; //aquí se inicializarán datos relacionadas con la aplicación
}

void checkEvents()
{
	// Poll for events, and handle the ones we care about.
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			break;
		case SDL_KEYUP:
			// If escape is pressed, return (and thus, quit)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit( 0 );
			// Barra espaciadora para encender/apagar animación
			if( event.key.keysym.sym == SDLK_SPACE )
			{
				anim = !anim;
				if( anim )
					gLastTick = SDL_GetTicks();
			}
			// 'Z' minúscula para encender/apagar zoom
			if( event.key.keysym.sym == SDLK_z )
			{

				render();
			}
			break;
		case SDL_VIDEORESIZE:
			winX=event.resize.w; winY=event.resize.h;
			screen = SDL_SetVideoMode(winX, winY, 32, SDL_SWSURFACE | SDL_RESIZABLE );
			render();
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouX = event.button.x;
			mouY = winY - event.button.y;
			mouse = 1;
			//printf( "x: %d, y: %d\n", event.button.x, event.button.y );
			render();
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

void idle()
{
	// Ask SDL for the time in milliseconds
	int tick;

	// Main loop: loop forever.
	while (1)
	{
		if( anim )
		{
			avanza++;
			if( avanza>10 )
				avanza=0;

			tick = SDL_GetTicks();
			if (tick <= gLastTick)
			{
				SDL_Delay(1);
				continue;
			}

			// Render stuff
			render();
			gLastTick += 1000 / PHYSICSFPS;
		} else
			SDL_Delay(100);

		checkEvents();
	}
}
