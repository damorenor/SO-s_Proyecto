//damorenor + joacarrilloco
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
	       		       
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

int countRegisters();
void saveDog();
int getHash();
void getMascota();
void imprimirMascota();
void generateHc();

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
			free(lastID);
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
	lastID[hash] = countRegisters();

	saveDog( mascota );

	printf("\nse guardó su mascota... Presione ENTER:");
	char end;
	scanf("%s",&end);
	
	free(mascota);
}


void seePet(){
	system("clear");
	printf("Numero de perros registrados: ");
	printf("%d\n\n", countRegisters());

	printf("Ingrese el id de la mascota que desea ver:\n");
	int registerId;
	scanf("%d",&registerId);
	registerId--;

	struct dogType * mascota;
	mascota = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( mascota == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}
	getMascota(registerId, mascota);
	imprimirMascota(mascota);

	unsigned char hcName [20];//hc stands for historia clílica
	memset( hcName,0, sizeof (hcName));
	unsigned char hcFile [20];
	memset( hcFile,0, sizeof (hcFile));

	sprintf(hcName, "%d", registerId);
	strcat(hcName,"hc");
	strcat(hcName,".txt");

	strcat(hcFile,"gedit ");
	strcat(hcFile, hcName);

	if( access( hcName, F_OK ) == -1 ) {
		generateHc(hcName, mascota);
	}	

	system(hcFile);

	free(mascota);
	printf("\ncambios en la historia clinica realizados... Presione ENTER:");
	char end;
	scanf("%s",&end);
}


void deletePet()
{
	system("clear");
	printf("Numero de perros registrados: ");
	printf("%d\n\n", countRegisters());

	printf("Ingrese el id de la mascota que desea eliminar:\n");

	int registerId;
	scanf("%d",&registerId);
	registerId--;

		
	struct dogType * mascotaFinal;
	mascotaFinal = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( mascotaFinal == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}
	getMascota( countRegisters()-1, mascotaFinal );

	struct dogType * mascotaDelete;
	mascotaDelete = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( mascotaDelete == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}
	getMascota( registerId, mascotaDelete );

	// a partir de este punto comienza lo feo	
	int hashF, hashD;
	hashF = getHash( mascotaFinal -> nombre );
	hashD = getHash( mascotaDelete -> nombre );

	struct dogType * tmp;
	tmp = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( tmp  == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}
	
	int id, idAnt;
	id = -1;
	getMascota( lastID[hashF], tmp );
	while( 1 )
	{
		idAnt = tmp -> idPrev;
		if( tmp -> idPrev <= registerId )
			break;
		id = idAnt;
		getMascota( tmp -> idPrev, tmp );
	}	
	
	// id guarda el indice del primer elemento que pertenece a la lista de HashFinal y que se encuentra despues del elemento a ser borrado
	// si este elemento no existe se id vale -1 ( cuando la posicion borrada es la ultima )
	// para este elemento su prevId se modificara ya que antes la lista era de la forma:  ..... idAnt, id, ..... lastID[hashF]
	// ahora la lista pasa a ser de la forma: ..... id Prev, ultimaMascota(posicion eliminada), id, ......

	if( id != -1 )	
	{
		getMascota( id, tmp );
		tmp -> idPrev = registerId; // ahora tmp guarda la data completa de dicho elemento
	}
	
	// el head de la lista HashFinal, se re direcciona al que iba antes del ultimo elemento       
	lastID[hashF] = mascotaFinal -> idPrev;

	//ahora posicionando a la mascota final en la posicion eliminada(registerId) se apunta como elemento anterior a idPrev 
	mascotaFinal -> idPrev = idAnt;	

	struct dogType * tmp2;
	tmp2 = ( struct  dogType *) malloc( sizeof ( struct dogType ) );	
	if( tmp2  == NULL )
	{
		perror("error en el malloc de la mascota");
		exit( -1 );
	}
	
	int id2;
	id2 = -1;

	if( hashF != hashD )
	{	
		getMascota( lastID[hashD], tmp2 );
		while( 1 )
		{
			if( tmp2 -> idPrev <= registerId )
				break;
			id2 = tmp2 -> idPrev;
			getMascota( tmp2 -> idPrev, tmp2 );
		}	
		
		// id2 guarda el indice del primer elemento que apunta al elemento a ser borrado o -1 si el elemento borrado es el ultimo de su lista
		// la lista hashDelete era de la forma: ......( mascotaDelete -> prevId ), registerId, id2, .....
		// ahora es de la forma: ...... ( mascotaDelete -> prevId ), id2, .....
		
				
		if( id2 != -1 )	
		{
			getMascota( id2, tmp2 );
			tmp2 -> idPrev = mascotaDelete -> idPrev; // ahora tmp guarda la data completa del elemento id2
		}
		else
		{
			//el elemento a ser borrado es el ultimo de su lista, por tanto
			lastID[hashD] = mascotaDelete -> idPrev;
		}
	}
	else
	{
		//note que la informacion de mascotaFinal -> prevId es registerId, hay que arreglarlo porque se apuntaria a si misma
		mascotaFinal -> idPrev = mascotaDelete -> idPrev;
	}

	// aqui acaba lo feo :D

	//Re escritura de historias clinicas
	

	// Primero se elimina la historia clinica de la mascota registerId
	unsigned char hcNameDelete [20], hcNameLast [20];
	memset( hcNameDelete,0, sizeof (hcNameDelete));
	memset( hcNameLast, 0, sizeof (hcNameLast) );

	sprintf(hcNameDelete, "%d", registerId);
	strcat(hcNameDelete,"hc");
	strcat(hcNameDelete,".txt");

		
	sprintf(hcNameLast, "%d", countRegisters() - 1);
	strcat(hcNameLast,"hc");
	strcat(hcNameLast,".txt");

	int status;
	if( access( hcNameDelete, F_OK ) != -1 ) { 
		status = remove( hcNameDelete );	
		if( status != 0 )
		{
			perror( "Error eliminando historia clinica" );
			exit( -1 );

		}
	}	

	//Ahora se renombra la historia clinica del ultimo	
	
	if( access( hcNameLast, F_OK ) != -1 ) {
		status = rename( hcNameLast, hcNameDelete );
		if( status != 0 )
		{
			perror( "Error en el renombramiento de la historio clinica" );
			exit( -1 );
		}
		
	}

	//Re escritura del archivo	
	
	FILE * dbTmp;
	int check;
	dbTmp = fopen("dbTmp.dat", "a+");
	
	int i, tot;
	i = 0, tot = countRegisters() - 1;

	for( i = 0; i < tot; ++ i )
	{
		if( i == id ){
			check = fwrite ( tmp, sizeof( struct dogType ), 1, dbTmp );	
			if (check==0)
			{
				perror("error escritura dbTmp");
				exit(-1);
			}
		} 
		else if( i == id2 ){
			check = fwrite ( tmp2, sizeof( struct dogType ), 1, dbTmp );
			if (check==0)
			{
				perror("error escritura dbTmp");
				exit(-1);
			}	
		}
		else if( i == registerId ){
			check = fwrite ( mascotaFinal, sizeof( struct dogType ), 1, dbTmp );
			if (check==0)
			{
				perror("error escritura dbTmp");
				exit(-1);
			}
		} 
		else
		{
			getMascota( i, mascotaDelete );
			check  = fwrite( mascotaDelete, sizeof ( struct dogType ), 1, dbTmp ); 
			if (check==0)
			{
				perror("error escritura dbTmp");
				exit(-1);
			}
		}
	}
	fclose(dbTmp); 

	status = remove( "dataDogs.dat" );	
	if( status != 0 )
	{
		perror( "Error eliminando la base de datos" );
		exit( -1 );
	}

	status = rename( "dbTmp.dat", "dataDogs.dat" );
	if( status != 0 )
	{
		perror( "Error en el renombramiento de la base de datos" );
		exit( -1 );
	}

	free(mascotaFinal);
	free(mascotaDelete);
	free(tmp);
	free(tmp2);

	printf("\nLa mascota ha sido eliminada, presione ENTER para continuar");
	char end;
	scanf("%s",&end);
}


void searchPet()
{
	system("clear");
	printf("Ingrese el nombre de la mascota que quiere buscar:\n" );

	unsigned char buff[NOMBRE_SIZE];
	
	memset( buff, 0, sizeof buff );	
	scanf("%s", buff );
	printf("\n");
	
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
		printf("%d %d\n", currId, countRegisters());
		getMascota( currId, mascota );
		printf("%d %d\n", hash, getHash(mascota->nombre) );
		
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

	free(mascota);

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


int countRegisters(){
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


void generateHc(char* hcName, struct dogType* mascota){
	FILE *hc = fopen(hcName,"w+");
	int check;
	check = fprintf(hc,"NOMBRE: %s\n", mascota->nombre);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}
	check = fprintf(hc,"TIPO: %s\n", mascota->tipo);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}
	check = fprintf(hc,"EDAD: %d\n", mascota->edad);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}
	check = fprintf(hc,"RAZA: %s\n", mascota->raza);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}
	check = fprintf(hc,"ESTATURA: %d\n", mascota->estatura);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}
	check = fprintf(hc,"PESO: %f\n", mascota->peso);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}
	check = fprintf(hc,"SEXO: %s\n", &mascota->sexo);
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}

	check = fprintf(hc,"Historia clinica: \n");
	if (check < 0){
		perror("error generando historia clinica");
		exit(-1);
	}

	fclose(hc);
}
