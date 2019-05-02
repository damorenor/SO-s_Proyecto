//damorenor + joacarrilloco
#include <stdio.h>
#include <stdlib.h>

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

typedef struct dogType pet;//Se define tipo de dato pa ahorrar codigo :D

//Inicialización del registro de mascotas y carga de datos necesarios
void init(){
	printf("Se creó el registro\n");
}

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
		case 2:
		seePet();
		case 3:
		deletePet();
		case 4:
		searchPet();
		case 5:
		exit(-1);
		default:
		printf("ingrese una opción valida\n");
	}	
}

//Ejecución permanente del programa
void run(){
	while(1){
		menu();
	}
}

//main
int main(int argc, char const *argv[])
{
	init();
	run();
	return 0;
}
