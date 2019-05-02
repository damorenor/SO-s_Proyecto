//damorenor + joacarrilloco
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REGISTER_SIZE ( (int) 1e7 ) 
#define NOMBRE_SIZE 32
#define TIPO_SIZE 32
#define RAZA_SIZE 16
#define TOTAL_NAMES 1716
#define TOTAL_BREEDS 13

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


char mainNames [TOTAL_NAMES][NOMBRE_SIZE]; 

void nameArrayGenerator(){
	FILE *names;
	names = fopen("dataNames.dat","r");
	if(names == NULL){
		perror("error open de dataNames");
		exit(-1);
	}
	int check;
	char buffer[NOMBRE_SIZE];
	for(int i=0;i<TOTAL_NAMES;i++){
		check = fseek(names,sizeof(buffer)*i,SEEK_SET);
		if(check == -1){
			perror("error seek dataNames");
			exit(-1);
		}

		check = fread(&buffer,sizeof(buffer),1,names);
		if(check == 0){
			perror("error lectura de dataNames");
			exit(-1);
		}

		strcpy(mainNames[i], buffer);
	}
	fclose(names);
}

char mainBreeds [TOTAL_BREEDS][RAZA_SIZE];

void breedArrayGenerator(){
        FILE *breeds;
        breeds = fopen("dataBreeds.dat","r");
        if(breeds == NULL){
                perror("error open de dataBreeds");
                exit(-1);
        }
        int check;
        char buffer[RAZA_SIZE];
        for(int i=0;i<TOTAL_BREEDS;i++){
                check = fseek(breeds,sizeof(buffer)*i,SEEK_SET);
                if(check == -1){
                        perror("error seek dataBreeds");
                        exit(-1);
                }

                check = fread(&buffer,sizeof(buffer),1,breeds);
                if(check == 0){
                        perror("error lectura de dataBreeds");
                        exit(-1);
                }

                strcpy(mainBreeds[i], buffer);
        }
        fclose(breeds);
}


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
	srand( time( NULL ) );

	nameArrayGenerator();
	breedArrayGenerator();

	FILE *f;
	f = fopen("dataDogs.dat", "w+");

	if( f == NULL )
	{
		perror("error abriendo archivo principal");
		exit( -1 );
	}


	struct dogType * perro;
	perro = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	
	if( perro == NULL )
	{
		perror("error en el malloc");
		exit( -1 );
	}

	int i;
	for( i = 0; i < REGISTER_SIZE; ++ i )
	{
		strcpy( perro -> nombre, mainNames[ rand()%TOTAL_NAMES ] );
		strcpy( perro -> tipo, "perro" );		
		perro -> edad = rand() % 18; 	
		strcpy( perro -> raza, mainBreeds[ rand()%TOTAL_BREEDS ] );
		perro -> estatura  = 50 + rand()% 51; 
		perro -> peso = 10.0 + 20.0 * ( (float) rand() / RAND_MAX );	
		perro -> sexo = ( rand() % 2 ) ? 'H' : 'M' ;


	//	printf("NOMBRE: %s\n", perro -> nombre );
	//	printf("TIPO: %s\n", perro -> tipo );
	//	printf("EDAD: %d\n", perro -> edad );
	//	printf("RAZA: %s\n", perro -> raza );
	//	printf("ESTATURA: %d\n", perro -> estatura );
	//	printf("PESO: %f\n", perro -> peso );
	//	printf("SEXO: %c\n", perro -> sexo );
	//	printf("\n\n" );

		guardar( f, perro );	
	}	

	fclose( f );
	return 0;
}
