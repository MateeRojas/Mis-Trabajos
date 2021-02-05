#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "enano.h"

#define FORMATO_LECTURA "%[^;];%i;%i;%i\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%i\n"
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
#define MUERTO -1
#define MISION_EXITOSA 1
#define OBRERO 1
#define APRENDIZ 2
#define GUERRERO 3
#define LIDER 4
#define GENERAL 5
#define MISIONES_MIN_APRENDIZ 10
#define MISIONES_MIN_GUERRERO 100
#define MISIONES_MIN_LIDER 250
#define EDAD_MIN_GUERRERO 40
#define EDAD_MAX_GUERRERO 50
#define EDAD_MIN_LIDER 50
#define EDAD_MAX_LIDER 60
#define ERROR -1
#define MAX_APRENDICES_MISION 10
#define NULO 0
#define TAMANIO_LEIDOS 4

/*
*PRE: recibe la ruta donde se desee escribir un enano y dicho enano
*POST: escribe los datos del enano en la ruta deseada
*/
void escribir_enano(FILE* mision, enano_t enano){
  fwrite(&enano, sizeof(enano_t), 1, mision);
}

/*
*PRE: recibirá como parametro el nombre de la funcion que tiene los datos para actualizar
*POST: dejará el archivo de censo actualizado, sumandole 1 a os enanos que completaron la mision y eliminando aquellos que no
*/
int actualizar_censo(const char* mision){
  FILE* enanos = fopen("censo.csv", "r");
  if(!enanos){
    perror("Error de apertura enanos");
    return ERROR;
  }

  FILE* mision_terminada = fopen(mision, "r");
  if(!mision_terminada){
    perror("Error de apertura");
    fclose(enanos);
    return ERROR;
  }
  
  FILE* censo_actualizado;
  censo_actualizado = fopen("censo_actualizado.csv", "w");
  if(!censo_actualizado){
    perror("Error de apertura censo");
    fclose(enanos);
    fclose(mision_terminada);
    return ERROR;
  }

  int leidos_censo = NULO;
  enano_t enano_censo;
  enano_t enano_mision;
  
  leidos_censo = fscanf(enanos, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
  fread(&enano_mision, sizeof(enano_t), 1, mision_terminada);
  
  while(!feof(mision_terminada) && leidos_censo != EOF){
    if(strcmp(enano_mision.nombre, enano_censo.nombre) == COINCIDENCIA){
      if(enano_mision.edad == MUERTO){
         leidos_censo = fscanf(enanos, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
         fread(&enano_mision, sizeof(enano_t), 1, mision_terminada);
        
     }else{
      fprintf(censo_actualizado, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, (enano_censo.cantidad_misiones + MISION_EXITOSA), enano_censo.id_rango);
      leidos_censo = fscanf(enanos, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
      fread(&enano_mision, sizeof(enano_t), 1, mision_terminada);
     }
    }
    else if(strcmp(enano_mision.nombre, enano_censo.nombre) < COINCIDENCIA){
        fprintf(censo_actualizado, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, (enano_censo.cantidad_misiones + MISION_EXITOSA), enano_censo.id_rango);
        leidos_censo = fscanf(enanos, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
        fread(&enano_mision, sizeof(enano_t), 1, mision_terminada);  
      
    }else{
      fprintf(censo_actualizado, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);
      leidos_censo = fscanf(enanos, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
    }    
  }
  while(!feof(mision_terminada)){
    fprintf(censo_actualizado, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, (enano_censo.cantidad_misiones + MISION_EXITOSA), enano_censo.id_rango);
    fread(&enano_mision, sizeof(enano_t), 1, mision_terminada);  
  }
  while(leidos_censo != EOF){
    fprintf(censo_actualizado, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);
    leidos_censo = fscanf(enanos, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);      
  }
fclose(enanos);
fclose(mision_terminada);
fclose(censo_actualizado);
remove("censo.csv");
rename("censo_actualizado.csv", "censo.csv");
return 0;

}

/*
*PRE: recibira el rango que se desea listar
*POST: mostrara por pantalla nombre de rango y datos de cada enano
*/
int listar_enanos(int id_rango){
  FILE* enanos;
  enanos = fopen("censo.csv", "r");
  if(!enanos){
    perror("Error de apertura enanos");
    return ERROR;
  }
  
  FILE* rangos;
  rangos = fopen("rangos.dat", "r");
  if(!rangos){
    perror("error en rangos");
    fclose(enanos);
    return ERROR;
  }
  
  int leidos = NULO;
  enano_t enano;
  rango_t rango;
  
  fseek(rangos, ((long)(id_rango-1)*(long)sizeof(rango_t)), SEEK_SET);
  fread(&rango, sizeof(rango_t), 1, rangos);
  printf("%s \n", rango.nombre);
  printf("%s \n", rango.descripcion);
  while(leidos != EOF){
    leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.cantidad_misiones, &enano.edad, &enano.id_rango);
    if(enano.id_rango == id_rango){
      printf("nombre: %s edad: %i cantidad de misiones: %i rango: %i\n", enano.nombre, enano.cantidad_misiones, enano.edad, enano.id_rango);
    }
  }
  
  fclose(enanos);
  fclose(rangos);
  return 0;

}

/*
*PRE: recibe la cantidad de aprendices, guerreros, lideres y generales que iran a la mision
*POST: si hay suficientes devuelve true, si no. false
*/
bool cantidades_cumplidas(int cantidad_guerreros, int cantidad_lideres, int cantidad_generales, int guerreros_pedidos, int lideres_pedidos, int generales_pedidos){
  return (cantidad_guerreros == guerreros_pedidos && cantidad_lideres == lideres_pedidos && cantidad_generales == generales_pedidos);
}

/*
*PRE: recibira la cantidad de guerreros lideres y generales que se necesitan para una mision, de la cual se recibe el nombre. si no recibe el nokmbre lo llamara mision.dat
*POST: creará un archivo binario con el listado de los enanos que fueron (siempre se llevan hasta 10 aprendices). Si no hay suficientes lo borra 
*/
int elegir_enanos(int guerreros, int lideres, int generales, char nombre_mision[]){
  
  FILE* enanos;
  enanos = fopen("censo.csv", "r");
  if(!enanos){
    perror("Error de apertura enanos");
    return ERROR;
  }
  
  FILE* mision;
  mision = fopen(nombre_mision, "r");
  if(mision != NULL){
    perror("nombre no disponible");
    fclose(enanos);
    fclose(mision);
    return ERROR;
  }
  
  mision = fopen(nombre_mision, "w");
  if(mision == NULL){
    perror("Error de apertura mision");
    fclose(enanos);
    return ERROR;
  }

  int leidos = NULO;
  enano_t enano;
  int contador_guerreros = NULO;
  int contador_lideres = NULO;
  int contador_generales = NULO;
  int contador_aprendices = NULO;  
  leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
  while(leidos == TAMANIO_LEIDOS){
        if(enano.id_rango == APRENDIZ && contador_aprendices < MAX_APRENDICES_MISION){
          escribir_enano(mision, enano);
          contador_aprendices++;
          leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
        }
        else if(enano.id_rango == GUERRERO && contador_guerreros < guerreros){
          escribir_enano(mision, enano);
          contador_guerreros++;
          leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
        }
        else if(enano.id_rango == LIDER && contador_lideres < lideres){
          escribir_enano(mision, enano);
          contador_lideres++;
          leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
        }
        else if(enano.id_rango == GENERAL && contador_generales < generales){
          escribir_enano(mision, enano);
          contador_generales++;
          leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
        }
        else{
        leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);  
        }
    }
  if(guerreros > contador_guerreros){
    fclose(mision);
    fclose(enanos);
    remove(nombre_mision);
    return ERROR;
  }
  else if(lideres > contador_lideres){
    fclose(mision);
    fclose(enanos);
    remove(nombre_mision);
    return ERROR;
  }
  else if(generales > contador_generales){
    fclose(mision);
    fclose(enanos);
    remove(nombre_mision);
    return ERROR;
  }

  fclose(enanos); 
  fclose(mision);
  return 0;
  

}


/*
*PRE: recibe la cantidad de misiones de un aprendiz
*POST: si cumple con las condiciones dadas, devuelve true, si no, false
*/
bool aprendiz_para_promover(int misiones, int id){
  bool promocion = false;
  if(misiones > MISIONES_MIN_APRENDIZ && id == APRENDIZ){
    promocion = true;
  }
  return promocion;
}

/*
*PRE: recibe la cantidad de misiones de un guerrero y su edad
*POST: si cumple con las condiciones dadas, devuelve true, si no, false
*/
bool guerrero_para_promover(int misiones, int edad, int id){
  bool promocion = false;
  if(misiones > MISIONES_MIN_GUERRERO && edad >= EDAD_MIN_GUERRERO && edad < EDAD_MAX_GUERRERO && id == GUERRERO){
    promocion = true;
  }
  return promocion;
}
/*
*PRE: recibe la cantidad de misiones de un lider y su edad
*POST: si cumple con las condiciones dadas, devuelve true, si no, false
*/
bool lider_para_promover(int misiones, int edad, int id){
  bool promocion = false;
  if(misiones > MISIONES_MIN_LIDER && edad >= EDAD_MIN_LIDER && edad < EDAD_MAX_LIDER && id == LIDER){
    promocion = true;
  }
  return promocion;
}

/*
*PRE: recibe un enano para promover
*POST: chequea si cumple las condiciones y si lo hace, aumenta en uno su rango
*/
void promocion(enano_t* enano){    
    if(aprendiz_para_promover(enano->cantidad_misiones, enano->id_rango)){
      enano->id_rango++;
    }else if(guerrero_para_promover(enano->cantidad_misiones, enano->edad, enano->id_rango)){
      enano->id_rango ++;
    }else if(lider_para_promover(enano->cantidad_misiones, enano->edad, enano->id_rango)){
      enano->id_rango ++;
    }
}

/*
*PRE: no recibe parametros
*POST: a travez de funciones, determina si un enano esta apto para promoverse y si lo esta, lo promueve
*/
int promover_enanos(){
  FILE* enanos;
  enanos = fopen("censo.csv", "r");
  if(!enanos){
    perror("Error de apertura enanos");
    return ERROR;
  }
  
  FILE* enanos_promovidos;
  enanos_promovidos = fopen("enanos_promovidos.csv", "w");
  if(!enanos_promovidos){
    perror("Error de apertura enanos promovidos");
    fclose(enanos);
    return ERROR;
  }
  enano_t enano;
  int leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
  while(leidos != EOF){
      promocion(&enano);
      fprintf(enanos_promovidos, FORMATO_ESCRITURA, enano.nombre, enano.edad, enano.cantidad_misiones, enano.id_rango);
      leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);    
  }
  
  fclose(enanos);
  fclose(enanos_promovidos);
  remove("censo.csv");
  rename("enanos_promovidos.csv", "censo.csv");
  return 0;
}