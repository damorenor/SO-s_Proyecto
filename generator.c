//damorenor + joacarrilloco
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REGISTER_SIZE int(1e8 + 10)
#define NOMBRE_SIZE 32
#define TIPO_SIZE 32
#define RAZA_SIZE 16

//Estructura que almacena la info de la mascota
struct dogType
{
        char nombre [NOMBRE_SIZE];
        char tipo [TIPO_SIZE];
        int edad;
        char raza [RAZA_SIZE];
        int estatura;
        float peso;
        char sexo;
};


char mainNames [171827][32];

void guardar ( FILE *f, void *ap )
{
	struct dogType * dato;
	dato = (struct dogType *) ap;


	int r;
	r = fwrite( dato, sizeof( struct dogType ), 1, f );
	if( r == 0 )
	{
		perror("error en la escritura en el archivo principal");
		exit( -1 );
	}
}


int main()
{
	FILE *f;
	f = fopen("dataDogs.dat", "w+");

	if( f == NULL )
	{
		perror("error abriendo archivo principal");
		exit( -1 );
	}


	srand( time( NULL ) );
	
	struct dogType * perro;
	perro = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	
	if( perro == NULL )
	{
		perror("error en el malloc");
		exit( -1 );
	}

	int i;
	for( i = 0; i < 10; ++ i )
	{
		strcpy( perro -> nombre, "la mama de more" );		
		strcpy( perro -> tipo, "perro" );		
		perro -> edad = rand() % 18; 	
		strcpy( perro -> raza, "aun no c" );
		perro -> estatura  = 50 + rand()% 51; 
		perro -> peso = 10.0 + 20.0 * ( (float) rand() / RAND_MAX );	
		perro -> sexo = ( rand() % 2 ) ? 'H' : 'M' ;


		printf("%s\n", perro -> nombre );
		printf("%s\n", perro -> tipo );
		printf("%d\n", perro -> edad );
		printf("%s\n", perro -> raza );
		printf("%d\n", perro -> estatura );
		printf("%f\n", perro -> peso );
		printf("%c\n", perro -> sexo );
		printf("\n\n" );

		guardar( f, perro );	
	}	


	fclose( f );
	return 0;
}
