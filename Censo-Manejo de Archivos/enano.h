#ifndef _ENANO_H_
#define _ENANO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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


typedef struct enano{
  char nombre[MAX_NOMBRE];
  int edad;
  int cantidad_misiones;
  int id_rango;
} enano_t;

typedef struct rango{
  int id;
  char nombre[MAX_RANGO];
  char descripcion[MAX_DESCRPCION];
} rango_t;

int listar_enanos(int id_rango);

void escribir_enano(FILE* mision, enano_t enano);

bool cantidades_cumplidas(int cantidad_guerreros, int cantidad_lideres, int cantidad_generales, int guerreros_pedidos, int lideres_pedidos, int generales_pedidos);

int elegir_enanos(int guerreros, int lideres, int generales, char nombre_mision[]);

int actualizar_censo(const char* mision);

int promover_enanos();


#endif /*_ENANO_H_ */