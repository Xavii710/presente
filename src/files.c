#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

void highscore_update(int *Score){
 	FILE *archivo;

 	char caracteres[100];
 	archivo = fopen("resources/highscore.txt","r");

 	if (archivo == NULL){
  	exit(1);
  }

 	else{
 	  while (feof(archivo) == 0){
      fgets(caracteres,100,archivo);
    }
  }
  fclose(archivo);
  if (atoi(caracteres)<*Score){
    FILE *archivo;
    archivo = fopen("resources/highscore.txt","w");
    sprintf(caracteres, "%d", *Score);
    fputs(caracteres,archivo);
    fclose(archivo);
  }
}

int current_highscore(){
  FILE *archivo;

 	char caracteres[100];
 	archivo = fopen("resources/highscore.txt","r");

 	if (archivo == NULL){
  	exit(1);
  }

 	else{
 	  while (feof(archivo) == 0){
      fgets(caracteres,100,archivo);
    }
  }
  fclose(archivo);
  return atoi(caracteres);
}
