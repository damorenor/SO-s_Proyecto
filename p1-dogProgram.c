//damorenor + joacarrilloco
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
	       		       
#define REGISTER_SIZE ( (int) 1e7 ) 
#define NOMBRE_SIZE 32
#define TIPO_SIZE 32
#define RAZA_SIZE 16
#define TOTAL_NAMES 1716
#define TOTAL_BREEDS 13

#define HASH_SIZE 10007 
#define MOD 256

struct dogType
{
        unsigned char nombre [NOMBRE_SIZE];
        unsigned char tipo [TIPO_SIZE];
        int edad;
        unsigned char raza [RAZA_SIZE];
        int estatura;
        float peso;
        unsigned char sexo;

	int idPrev;
};


void initPointers();
void loadHeads();
void saveHeads();

void enterPet();
void seePet();
void deletePet();
void searchPet();

int CountRegisters();
void saveDog();
int getHash();
void getMascota();
void imprimirMascota();

int * lastID;
FILE *f;

//Carga el menu
void menu(){
	//Se imprime en consola el menú de usuario
	system("clear");
	printf("\t\t\tVET CLINIC :3\n"
			"est.2019\n\n\n"
			"\t1.\tIngresar Registro\n"
			"\t2.\tVer Registro\t\n"
			"\t3.\tBorrar Registro\n"
			"\t4.\tBuscar Registro\n"
			"\t5.\tSalir\n"
		);
	//Se recibe por teclado un entero que corresponde a la funcionalidad escogida
	short option;
	scanf("%hd",&option);
	switch(option){
		case 1:
			enterPet();
			break;
		case 2:
			seePet();
			break;
		case 3:
			deletePet();
			break;
		case 4:
			searchPet();
			break;
		case 5:
			saveHeads();
			exit( 0 );

		default:
		printf("ingrese una opción valida\n");
	}	
}

void run(){
	while(1){
		menu();

	}
}

int main()
{
	initPointers();
	loadHeads();	
	run();
	return 0;
}


void enterPet(){
	system("clear");
	printf("Ingrese porfavor los datos de la mascota:\n\n");

	struct dogType * mascota;
	mascota = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( mascota == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}
	
	memset( mascota->nombre, 0, NOMBRE_SIZE * sizeof ( unsigned char ) );
	printf("ingrese nombre:");
	scanf("%s",mascota->nombre);
	printf("\ningrese tipo:");
	scanf("%s",mascota->tipo);
	printf("\ningrese edad:");
	scanf("%d",&mascota->edad);
	printf("\ningrese raza:");
	scanf("%s",mascota->raza);
	printf("\ningrese estatura:");
	scanf("%d",&mascota->estatura);
	printf("\ningrese peso:");
	scanf("%f",&mascota->peso);
	printf("\ningrese sexo:");
	scanf("%s",&mascota->sexo);
	printf("\n\n" );

	int hash = getHash( mascota -> nombre );
	mascota -> idPrev = lastID[hash];
	lastID[hash] = CountRegisters();

	saveDog( mascota );

	printf("\nse guardó su mascota... Presione ENTER:");
	char end;
	scanf("%s",&end);
	

}


void seePet()
{


}


void deletePet()
{


}


void searchPet()
{

	printf("Ingrese el nombre de la mascota que quiere buscar\n" );

	unsigned char buff[NOMBRE_SIZE];
	
	memset( buff, 0, sizeof buff );	
	scanf("%s", buff );

	
	int hash, currId, i, equal;
	hash = getHash( buff );
	
	currId = lastID[hash];

	struct dogType * mascota;
	mascota = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( mascota == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}

	while( currId != -1 )
	{
		getMascota( currId, mascota );
		
		equal = 1;
		for( i = 0; i < NOMBRE_SIZE; ++ i )
		{
			if( mascota->nombre[i] != buff[i] ) // hay que cambiarlo
				equal = 0;
		}	
		
		if( equal )
			imprimirMascota( mascota );	
		currId = mascota -> idPrev;
	}


	printf("\nBusqueda finalizada presione enter para continuar");
	char end;
	scanf("%s",&end);
}

void imprimirMascota( struct dogType * mascota )
{

	printf("NOMBRE: %s\n", mascota -> nombre );
	printf("TIPO: %s\n", mascota -> tipo );
	printf("EDAD: %d\n", mascota -> edad );
	printf("RAZA: %s\n", mascota -> raza );
	printf("ESTATURA: %d\n", mascota -> estatura );
	printf("PESO: %f\n", mascota -> peso );
	printf("SEXO: %c\n", mascota -> sexo );
	printf("\n\n" );
}

void getMascota( int idx, struct dogType * mascota )
{
	FILE *g;
	int  check, size;
	g = fopen("dataDogs.dat","r");
	if(g == NULL){
		perror("error abriendo archivo (getMascota)");
		exit(-1);
	}

	check = fseek(g, idx * sizeof( struct dogType ), SEEK_SET);
	if (check == -1)
	{
		perror("error seek get Mascota");
		exit( -1 );
	}


	check = fread(mascota, sizeof( struct dogType ),1,g );
	if ( check == 0 )
	{
		perror("error en el read del archivo (getMascota)");
		exit(-1);
	}		
	fclose( g );
}


int CountRegisters(){
	FILE *g;
	int  check, size;
	g = fopen("dataDogs.dat","r");
	if(g == NULL){
		perror("error abriendo archivo (size)");
		exit(-1);
	}

	check = fseek(g,0L, SEEK_END);
	if (check == -1)
	{
		perror("error seek size archivo");
		exit( -1 );
	}

	size = ftell(g);
	if (size == -1)
	{
		perror("error tell size archivo");
		exit(-1);
	}

	fclose(g);
	
	return size / sizeof ( struct dogType );
}

void saveDog ( void *ap )
{
	f = fopen("dataDogs.dat", "a+");
	if( f == NULL )
	{
		perror("error abriendo archivo principal");
		exit( -1 );
	}
	
	struct dogType * dato;
	dato = (struct dogType *) ap;

	int r;
	r = fseek(f,0L, SEEK_END);
	if( r == -1 )
	{
		perror("error en la escritura de la mascota(seek)");
		exit( -1 );
	}
	r = fwrite( dato, sizeof( struct dogType ), 1, f );
	if( r == 0 )
	{
		perror("error en la escritura en el archivo principal");
		exit( -1 );
	}
	fclose( f );
}

int getHash( unsigned char * nombre )
{
	int hash, base, i;

	for( i = 0, hash = 0, base = 1; i < NOMBRE_SIZE; ++ i )
	{
		hash += ( nombre[i] ) * base;

		base *= MOD;
		base %= HASH_SIZE;

		hash %= HASH_SIZE;
	}

	return hash;
}


void initPointers()
{
	lastID = ( int * ) malloc ( HASH_SIZE * sizeof ( int ) );
	if( lastID == NULL )
	{
		perror("error en el malloc lastID" );
		exit( -1 );
	}
        memset( lastID, -1, HASH_SIZE * sizeof ( int ) );
}


void loadHeads(){
	FILE * points;
 	int check;	 
	
	points = fopen("dataPointers.dat", "r");
	 if(points == NULL){
                perror("error cargando apuntadores");
                exit(-1);
        }
	
	check = fread(lastID, HASH_SIZE * sizeof(int), 1, points );
	if( check == 0 )
	{
		perror("error en la lectura de apuntadores");	
		exit( -1 );
	}
	
	fclose( points );
}

void saveHeads(){
        FILE *points;
        int  check;

        points = fopen("dataPointers.dat","w+");
        if(points == NULL){
                perror("error generando apuntadores");
                exit(-1);
        }

        check = fwrite( lastID, HASH_SIZE * sizeof(int), 1, points );
        if( check == 0 )
	{
		perror("error en la lectura de apuntadores");	
		exit( -1 );
	}
	fclose(points);
}


