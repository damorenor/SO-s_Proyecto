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

#define HASH_SIZE 1007 
#define MOD 256


//Estructura que almacena la info de la mascota
struct dogType
{
        unsigned char nombre [NOMBRE_SIZE];
        char tipo [TIPO_SIZE];
        int edad;
        char raza [RAZA_SIZE];
        int estatura;
        float peso;
        char sexo;

	int idPrev;
};

int getHash( unsigned char * nombre )
{
	int hash, base, i;

	printf("%s\n", nombre );
	for( i = 0, hash = 0, base = 1; i < NOMBRE_SIZE; ++ i )
	{
		
		hash += ( nombre[i] ) * base;

	//	printf("%d\n", (int) nombre[i] );
	//	printf("%c\n", nombre[i] );

		base *= MOD;


		base %= HASH_SIZE;
		hash %= HASH_SIZE;
	       
		//printf("%d\n\n", hash );
		if( hash < 0 ) 
			exit( -1 );
	}

	return hash;
}


unsigned char ** mainNames;
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

//guarda dinamicamente el id del ultimo prrro que tiene dicho Hash
int lastID[HASH_SIZE]; 



int main()
{	
	srand( time( NULL ) );

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


	int * cnH;
        cnH = ( int * ) malloc ( HASH_SIZE * sizeof ( int ) );
	if( cnH == NULL )
	{
		perror("error en el malloc cnH" );
		exit( -1 );
	}
	memset( cnH, 0, HASH_SIZE * sizeof ( int ) );



	mainNames = ( unsigned char ** ) malloc( TOTAL_NAMES * sizeof ( unsigned char * ) );
	if( mainNames == NULL )
	{
		perror("error en el malloc de mainNames");
		exit(-1);
	}
	int i;
	for( i = 0; i < TOTAL_NAMES; ++ i )
	{
		mainNames[i] = (unsigned char * ) malloc ( NOMBRE_SIZE * sizeof ( unsigned char ) );
		if( mainNames[i] == NULL )
		{
			perror("error en el malloc de mainNames");
			exit(-1);
		}
		memset( mainNames[i], 0, NOMBRE_SIZE * sizeof ( unsigned char ) );
	}

	memset( lastID, -1, sizeof ( lastID ) );

	nameArrayGenerator();
	for( i = 0; i < TOTAL_NAMES; ++ i )
	{
		
		printf("%s\n", mainNames[i] );	
		for( int j = 0; j < 32; ++ j )
		{
			printf("%d ", (int) mainNames[i][j] );

		}

		printf("\n%d", getHash( mainNames[i] ) );
		printf("\n\n");
	}	

	exit( 0 );	
	for( i = 0; i < REGISTER_SIZE; ++ i )
	{

		strcpy( perro -> nombre, mainNames[ i%TOTAL_NAMES] );
		strcpy( perro -> tipo, "perro" );		
		perro -> edad = rand() % 18; 	
		strcpy( perro -> raza, mainBreeds[ rand()%TOTAL_BREEDS ] );
		perro -> estatura  = 50 + rand()% 51; 
		perro -> peso = 10.0 + 20.0 * ( (float) rand() / RAND_MAX );	
		perro -> sexo = ( rand() % 2 ) ? 'H' : 'M' ;

	
		int h;

//		for( int i = 0; i < NOMBRE_SIZE; ++ i )
//		{
//			printf("%d\n", (int) perro -> nombre[i] );
//		}
//		printf("\n\n");
		printf("%d\n", i );

		h = getHash( perro -> nombre );
		
	//	printf("%d\n", h );
		
//		++cnH[h];
//	exit ( 0 ) ;
	//	perro -> idPrev = lastID[h];
//		lastID[h] = i;
	
       // 	printf("NOMBRE: %s\n", perro -> nombre );
	//	printf("%d\n\n", h );
	//	printf("TIPO: %s\n", perro -> tipo );
	//	printf("EDAD: %d\n", perro -> edad );
	//	printf("RAZA: %s\n", perro -> raza );
	//	printf("ESTATURA: %d\n", perro -> estatura );
	//	printf("PESO: %f\n", perro -> peso );
	//	printf("SEXO: %c\n", perro -> sexo );
	//	printf("\n\n" );

	//	guardar( f, perro );	
	}	
	
	int sum = 0;	
	int mx = 0;	
	for( i = 0; i < HASH_SIZE; ++ i )
	{
		if( cnH[i] > mx )
			mx = cnH[i];	
		sum += cnH[i];
		printf("%d\n", cnH[i] );
	}
	printf("%d\n", mx );
	fclose( f );
	return 0;
}
