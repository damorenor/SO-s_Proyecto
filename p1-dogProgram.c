//damorenor + jocarrilloco
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1e8;

//Estructura que almacena la info de la mascota
struct dogType
{
	char nombre [32];
	char tipo [32];
	int edad;
	char raza [16];
	int estatura;
	float peso;
	char sexo;
};

typedef struct dogType pet;//Se define tipo de dato pa ahorrar codigo :D

//Inicialización del registro de mascotas
void buildRegister(){
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
	exit(-1);
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
	buildRegister();
	run();
	return 0;
}
