#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nameArrayGenerator(char mainNames[1716][33]){
	FILE *names;
	names = fopen("nombresBinario.dat","r");
	if(names == NULL){
		perror("error open de nombresBinario");
		exit(-1);
	}
	int check;
	char *buffer;
	for(int i=0;i<1;i++){
		check = fseek(names,sizeof(buffer)*i,SEEK_SET);
		if(check == -1){
			perror("error seek nombresBinario");
			exit(-1);
		}

		check = fread(&buffer,sizeof(buffer),1,names);
		if(check == 0){
			perror("error lectura de nombresBinario");
			exit(-1);
		}

		mainNames[i] =  buffer;//el problema es en esta linea
	}
	fclose(names);
}


int main(int argc, char const *argv[])
{
	char mainNames[1716][33];//crear una constante pa esta monda :D
	nameArrayGenerator(mainNames);
	printf("%s\n", mainNames[0]);
	return 0;
}