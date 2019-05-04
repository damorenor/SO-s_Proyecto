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
void loadPointers();
void savePointers();
void enterPet();
void seePet();
void deletePet();
void searchPet();

int * lastID;


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
			
			savePointers();
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
	loadPointers();	
	run();
	return 0;
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


void loadPointers()
{
	FILE * points;
	points = fopen("dataPointers.dat", "r" );

	int i, check;
	for( i = 0; i < HASH_SIZE; ++ i )
	{
		check = fseek(points, i * sizeof(int),SEEK_SET);
		if( check == -1 )
		{
			perror("error seek Pointers");
			exit( -1 );
		}
		check = fread(&lastID[i], sizeof(int), 1, points );
		
		if( check == 0 )
		{
			perror("error en lectura Pointers");
			exit(-1);
		}
	}
	fclose( points );
}


void savePointers(){
        FILE *points;
        int  check;

        points = fopen("dataPointers.dat","w+");
        if(points == NULL){
                perror("error generando apuntadores");
                exit(-1);
        }

        for (int i = 0; i < HASH_SIZE; ++i){
                check = fwrite(&lastID[i], sizeof(int),1,points);
                if (check == 0){
                        perror("error escribiendo dataPointers");
                }
        }
        fclose(points);
}


void enterPet()
{


}


void seePet()
{


}


void deletePet()
{


}


void searchPet()
{


}
