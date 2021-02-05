#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "enano.h"

#define FORMATO_LECTURA "%[^;];%i;%i;%i\n"
#define COINCIDENCIA 0
#define INICIAL 1
#define ACTUALIZAR "actualizar_censo"
#define ELEGIR "integrantes_mision"
#define PROMOVER "promover_enanos"
#define LISTAR "listar_enanos"
#define MISION "mision"
#define MAX_NOMBRE 50
#define MAX_RANGO 50
#define MAX_DESCRPCION 200
#define ARGUMENTOS_ELEGIR 6
#define ARGUMENTOS_ACTUALIZAR 3
#define ARGUMENTOS_PROMOVER 2
#define ARGUMENTOS_LISTAR 3
#define ERROR -1


int main(int argc, const char *argv[]){
  if(argc >= 2){
    if(strcmp(argv[INICIAL], ACTUALIZAR) == COINCIDENCIA){
      char nombre[MAX_NOMBRE];
      strcpy(nombre, argv[2]);
      strcat(nombre, ".dat");
      if(argc != ARGUMENTOS_ACTUALIZAR){
        perror("Cantidad de argumentos inválida");
        return ERROR;
      }
      else{
        actualizar_censo(nombre);
      }
    }

    else if(strcmp(argv[INICIAL], ELEGIR) == COINCIDENCIA){
      if(argc == (ARGUMENTOS_ELEGIR)){
        char nombre[MAX_NOMBRE];
        strcpy(nombre, argv[5]);
        strcat(nombre, ".dat");
        elegir_enanos(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), nombre);
      }
      else if(argc == (ARGUMENTOS_ELEGIR - 1)){
        char nombre[MAX_NOMBRE];
        strcpy(nombre, MISION);
        strcat(nombre, ".dat");
        elegir_enanos(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), nombre);
      }
      else{
        perror("Cantidad de argumentos inválida");
        return ERROR;
      }

    }
    else if(strcmp(argv[INICIAL], PROMOVER) == COINCIDENCIA){
      if(argc != ARGUMENTOS_PROMOVER){
        perror("Cantidad de argumentos inválida");
        return ERROR;
      }
      else{
        promover_enanos();
      }

    }
    else if(strcmp(argv[INICIAL], LISTAR) == COINCIDENCIA){
      if(argc != ARGUMENTOS_LISTAR){
        perror("Cantidad de argumentos inválida");
        return ERROR;
      }
      else{
        listar_enanos(atoi(argv[2]));

      }

    }
    else{
      perror("Nombre de mision no válido, fin del programa\n");
    }

  }
  else{
    perror("Cantidad de argumentos inválida");
  }

	return 0;
}