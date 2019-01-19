#include "main.h"

//Este archivo incluirá las primitivas para ser llamadas desde archivo main.c
// desde la función "principal()"

//Los prototipos de las funciones de las primitivas seberán ponerse en main.h

//para el mapa de bits de texto


//Este archivo incluye las operaciones de texto y consola
//Prototipos de TEXTURAS
extern int textuDebug;
typedef struct {
	int __width;	//ancho
	int __height;	//alto
	int prof;	//profundidad en bits por pixel
	char * mapa;//apuntador al mapa
} bitMaps;

bitMaps texturas[60];

vector<bitMaps> listBitMaps;


int textuDebug=0;
//para mapas de bits de texto

int numberBitMap = 0;
int textura = 0;
int loadTextura( char * archivo );
int aplicaTextu=0;
double N=0;
float verTextuX,verTextuY;

//Ordena la carga de todas las texturas
void initTextura()
{
	//nombre_de_archivo
	 loadTextura( (char *)"city2.bmp" );// 0

    loadTextura( (char *)"city3.bmp" ); // 1
   	loadTextura( (char *)"building_front3.bmp" ); // 2
   	loadTextura( (char *)"building_front3_2.bmp" ); // 3
   	loadTextura( (char *)"edificio3.bmp" ); // 4

   	loadTextura( (char *)"efecto_fuego/fuego1.bmp" ); // 5
   	loadTextura( (char *)"efecto_fuego/fuego2.bmp" ); // 6
   	loadTextura( (char *)"efecto_fuego/fuego3.bmp" ); // 7
   	loadTextura( (char *)"efecto_fuego/fuego4.bmp" ); // 8
   	loadTextura( (char *)"efecto_fuego/fuego5.bmp" ); // 9
   	loadTextura( (char *)"efecto_fuego/fuego6.bmp" ); // 10
   	loadTextura( (char *)"efecto_fuego/fuego7.bmp" ); // 11
   	loadTextura( (char *)"efecto_fuego/fuego8.bmp" ); // 12
   	loadTextura( (char *)"efecto_fuego/fuego9.bmp" ); // 13
   	loadTextura( (char *)"efecto_fuego/fuego10.bmp" ); // 14
   	loadTextura( (char *)"efecto_fuego/fuego11.bmp" ); // 15


   	loadTextura( (char *)"efecto_fuego2/F1.bmp" ); // 16
   	loadTextura( (char *)"efecto_fuego2/F2.bmp" ); // 17
   	loadTextura( (char *)"efecto_fuego2/F3.bmp" ); // 18
   	loadTextura( (char *)"efecto_fuego2/F4.bmp" ); // 19
   	loadTextura( (char *)"efecto_fuego2/F5.bmp" ); // 20
   	loadTextura( (char *)"efecto_fuego2/F6.bmp" ); // 21
   	loadTextura( (char *)"efecto_fuego2/F7.bmp" ); // 22
   	loadTextura( (char *)"efecto_fuego2/F8.bmp" ); // 23
   	loadTextura( (char *)"efecto_fuego2/F9.bmp" ); // 24
   	loadTextura( (char *)"efecto_fuego2/F10.bmp" ); // 25
   	loadTextura( (char *)"efecto_fuego2/F11.bmp" ); // 26


    loadTextura( (char *)"logo.bmp" ); // 27

    loadTextura( (char *)"logo2.bmp" ); // 28

    loadTextura( (char *)"logointro.bmp" ); // 39

    loadTextura( (char *)"metro2.bmp" ); // 30
    loadTextura( (char *)"metro1.bmp" ); // 31
    loadTextura( (char *)"guy.bmp" ); // 32
}


void fuego(int xTarget, int yTarget, double T ){
    showTextura(xTarget,yTarget, ((int)(T-.1)% 11) +5 );
}
void fuego2(int xTarget, int yTarget, double T ){

    showTextura(xTarget,yTarget, ((int)(T-.1)% 11) +16 );
}


//Muestra textura en pantalla
void showTextura( int xTarget, int yTarget, int indexBitMap )
{
    bitMaps *image = &texturas[indexBitMap];
	int x,y, color;
	char rgb[3];

	for( y=0; y  < image->__height ; y++ )
		for( x=0; x < image->__width && xTarget + x <640 && (y + yTarget > 50 || N > 4000 ) ; x++ )
		{

            color = getTextu( x,y, indexBitMap, rgb );

			if( color !=6775670 && color != 12628991 )
                    putpixel( xTarget+x, yTarget+y,color);
		}
}
//Obtiene color de pixel a partir de coordenadas absolutas enteras
int getTextu( int x, int y, int indexBitMap, char *rgb )
{
    bitMaps *temp = &texturas[indexBitMap];
    int index;

	if( x<0 ) x=0;
    if( x>=temp->__width ) x=temp->__width-1;

	if( y<0 ) y=0;
    if( y>=temp->__height ) y=temp->__height-1;

    index =(temp->__width)*3*y + x*3 + (temp->__width%4)*y;

    rgb[0] = temp->mapa[ index + 2 ];
    rgb[1] = temp->mapa[ index + 1 ];
    rgb[2] = temp->mapa[ index + 0 ];
    return SDL_MapRGB(screen->format,rgb[0], rgb[1], rgb[2]);

}

//Carga una textura, por nombre de archivo
int loadTextura( char * archivo )
{
	FILE    *ifd;
	int sizeAlocate;
	short int padding;
	int inicioDatos;
    bitMaps *temp = &texturas[numberBitMap];

	ifd = fopen( archivo, "r" );
	if( ifd==0 )
	{
		return 1;
	}

	//inicio de los datos
	fseek( ifd, 10, SEEK_SET );
	fread( &inicioDatos,1,4,ifd );

	//geometría
	fseek( ifd, 18, SEEK_SET );
	fread( &temp->__width,1,4,ifd );
	fread( &temp->__height,1,4,ifd );
	padding = (short int)(temp->__width%4);	//bytes extras para hacer múltiplo de 4

	//obtener número de bits por pixel
	fseek( ifd, 28, SEEK_SET );
	fread( &temp->prof,1,2,ifd );

	//leer imagen
	fseek( ifd, inicioDatos, SEEK_SET );
    sizeAlocate = temp->__width * temp->__height * 3 + padding*temp->__height;
	temp->mapa = (char *)malloc( sizeAlocate ); //padding: número de bytes extras por cada renglón


	fread( temp->mapa, 1,sizeAlocate ,ifd );


	numberBitMap++;
	fclose( ifd );
	return 0;

}


