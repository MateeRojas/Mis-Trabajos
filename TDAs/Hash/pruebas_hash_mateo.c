#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "hash.h"
#include "hash_iterador.h"

#define ERROR -1
#define EXITO 0
#define ROJO     "\x1b[31m\x1b[1m"
#define VERDE    "\x1b[32m\x1b[1m"
#define CELESTE   "\x1b[0;36m"
#define NEUTRO   "\x1b[0m"

char* duplicar_string(const char* s){
  if(!s)
    return NULL;

  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

void destruir_string(void* elemento){
  if(elemento){
  //  printf("(Destructor) Libero el vehiculo: %s\n", (char*)elemento);
    free(elemento);
  }
}

bool mostrar_poke(hash_t* hash, const char* clave, void* aux){
  if(!clave){
    return true;
  }
  aux=aux;
  hash=hash;
  printf("\tPokemon registrado: %s\n", clave);

  return false;
}

bool probar(hash_t* hash, const char* clave, void* aux){
  if(!clave) return true;
  aux=aux;
  hash=hash;
  return false;
}

void probar_hash_nulo(int* pruebas, int* pruebas_pasadas){
  if(hash_insertar(NULL, "DEBEFALLAR", "Debe fallar") == ERROR){
    printf("\thash_insertar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_insertar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(hash_quitar(NULL, "DEBEFALLAR") == ERROR){
    printf("\thash_quitar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_quitar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_obtener(NULL, "DEBEFALLAR")){
    printf("\thash_obtener: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_obtener: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_contiene(NULL, "DEBEFALLAR")){
    printf("\thash_contiene: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_contiene: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(hash_cantidad(NULL) == 0){
    printf("\thash_cantidad: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_cantidad: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;
}

void probar_hash_vacio(int* pruebas, int* pruebas_pasadas){
  hash_t* pokedex = hash_crear(destruir_string, 3);

  if(hash_insertar(pokedex, "DEBEPASAR", duplicar_string("Debe pasar")) == EXITO){
    printf("\thash_insertar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_insertar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  hash_quitar(pokedex, "DEBEPASAR");

  if(hash_quitar(pokedex, "DEBEFALLAR") == ERROR){
    printf("\thash_quitar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_quitar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_obtener(pokedex, "DEBEFALLAR")){
    printf("\thash_obtener: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_obtener: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_contiene(pokedex, "DEBEFALLAR")){
    printf("\thash_contiene: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_contiene: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(hash_cantidad(pokedex)==0){
    printf("\thash_cantidad: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_cantidad: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  hash_destruir(pokedex);
}

void casos_borde(int* pruebas, int* pruebas_pasadas){
  hash_t* hash = hash_crear(NULL, 3);
  if(hash){
    printf("\thash_crear con destructor nulo: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_crear con destructor nulo: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;
  hash_destruir(hash);

 hash_t* hash_uno_y_medio = hash_crear(NULL, 2);

  if(hash_uno_y_medio){
    printf("\thash_crear con capacidad menor a la minima: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_crear con capacidad menor a la minima: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;
  hash_destruir(hash_uno_y_medio);

  hash_t* hash2 = hash_crear(destruir_string, 3);

  if(hash_insertar(hash2, NULL, "Debe fallar") == ERROR){
    printf("\thash_insertar con clave nula: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_insertar con clave nula: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(hash_insertar(hash2, "DEBEPASAR", NULL) == EXITO){
    printf("\thash_insertar inserta elemento nulo: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_insertar inserta elemento nulo: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  hash_insertar(hash2, "DEBESERUNO", duplicar_string("Debe ser 1"));
  hash_insertar(hash2, "DEBESERUNO", duplicar_string("Debe ser 1"));
  if(hash_con_cada_clave(hash2, probar, "Debe ser 1")==2){
    printf("\thash_insertar inserto clave repetida elimina la vieja: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_insertar inserto clave repetida elimina la vieja: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(hash_quitar(hash2, NULL) == ERROR){
    printf("\thash_quitar con clave nula: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_quitar con clave nula: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(hash_quitar(hash2, "NOESTA") == ERROR){
    printf("\thash_quitar con clave que no esta: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_quitar con clave que no esta: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;


  if(!hash_obtener(hash2, NULL)){
    printf("\thash_obtener con clave nula: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_obtener con clave nula: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_obtener(hash2, "NOESTA")){
    printf("\thash_obtener con clave que no esta: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_obtener con clave que no esta: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_contiene(hash2, NULL)){
    printf("\thash_contiene con clave nula: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_contiene con clave nula: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_contiene(hash2, "NOESTA")){
    printf("\thash_contiene con clave que no esta: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\thash_contiene con clave que no esta: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  hash_destruir(hash2);
}

void iteradores(int* pruebas, int* pruebas_pasadas){
  printf("\t"CELESTE"Hash nulo:"NEUTRO"\n");
  if(!hash_iterador_crear(NULL)){
    printf("\tIterador externo: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tIterador externo: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!hash_con_cada_clave(NULL, probar, NULL)){
    printf("\tIterador interno: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tIterador interno: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  hash_t* hash = hash_crear(destruir_string, 3);

  if(!hash_con_cada_clave(hash, NULL, NULL)){
    printf("\tIterador interno sin funcion: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tIterador interno sin funcion: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;
  //funcionamiento

  hash_destruir(hash);
}

void probar_funcionamiento(){
    printf("\t"CELESTE"El hash sera una Pokedex, y aca en Lomas de Zamora los id de Pokedex son medios raros."NEUTRO"\n");
    printf("\t"CELESTE"Creo un hash de capacidad 7 e inserto 3 Pokemon"NEUTRO"\n");
    hash_t* pokedex = hash_crear(destruir_string, 7);
    hash_insertar(pokedex, "BULB454UR", duplicar_string("Bolbasor"));
    hash_insertar(pokedex, "CH4RM4ND3R", duplicar_string("Charm*nder"));
    hash_insertar(pokedex, "5QU1RTL3", duplicar_string("Escuero"));
    if(hash_cantidad(pokedex) == 3){
      printf("\tLa cantidad es 3: "VERDE"SI"NEUTRO"\n");
    }
    else{
      printf("\tLa cantidad es 3: "ROJO"NO"NEUTRO"\n");
    }

    printf("\t"CELESTE"Borro a Charmander porque lo odio"NEUTRO"\n");
    hash_quitar(pokedex, "CH4RM4ND3R");
    if(hash_cantidad(pokedex) == 2){
      printf("\tLa cantidad disminuyo en 1: "VERDE"SI"NEUTRO"\n");
    }
    else{
      printf("\tLa cantidad disminuyo en 1: "ROJO"NO"NEUTRO"\n");
    }

    printf("\t"CELESTE"Hay algun Pokemon con la clave '5QU1RTL3'?"NEUTRO"\n");
    if(hash_contiene(pokedex, "5QU1RTL3")){
      printf("\tEsta? "VERDE"SI (BIEN)"NEUTRO"\n");
    }
    else{
      printf("\tEsta? "ROJO"NO (MAL)"NEUTRO"\n");
    }

    printf("\t"CELESTE"Y con la clave '4GUM0N'?"NEUTRO"\n");
    if(!hash_contiene(pokedex, "4GUM0N")){
      printf("\tEsta? "VERDE"NO (BIEN)"NEUTRO"\n");
    }
    else{
      printf("\tEsta? "ROJO"SI (MAL)"NEUTRO"\n");
    }

    printf("\t"CELESTE"Inserto 4 nuevos Pokemon"NEUTRO"\n");
    hash_insertar(pokedex, "CR0B4T", duplicar_string("Crobata"));
    hash_insertar(pokedex, "3L3CT4BUZZ", duplicar_string("El Electra"));
    hash_insertar(pokedex, "4L4K4Z4M", duplicar_string("Cris Angel: El Regreso"));
    hash_insertar(pokedex, "M3W", duplicar_string("Mewtwo menos uno"));

    if(hash_cantidad(pokedex) == 6){
      printf("\tLa cantidad es 6: "VERDE"SI"NEUTRO"\n");
    }
    else{
      printf("\tLa cantidad es 6: "ROJO"NO"NEUTRO"\n");
    }

    printf("\t"CELESTE"Muestro al Squirtle de mi Pokedex (Escuero)"NEUTRO"\n");
    char* escuero = hash_obtener(pokedex, "5QU1RTL3");
    if(escuero){
      printf("\t%s\n", escuero);
    }
    else{
      printf("\t"ROJO"FALLO"NEUTRO"\n" );
    }

    printf("\t"CELESTE"Muestro a Jorge"NEUTRO"\n");
    char* jorge = hash_obtener(pokedex, "J0R63");
    if(!jorge){
      printf("\t"VERDE"PASA, JORGE NUNCA EXISTIO"NEUTRO"\n" );
    }
    else{
      printf("\t"ROJO"FALLO"NEUTRO"\n" );
    }

    printf("\t"CELESTE"Uso el iterador interno para mostrar mis claves guardadas)"NEUTRO"\n");
    size_t cantidad = hash_con_cada_clave(pokedex, mostrar_poke, NULL);
    if(cantidad == 6){
      printf("\t"VERDE"Se mostraron todos los Pokemon"NEUTRO"\n" );
    }
    else{
      printf("\t"ROJO"FALLO"NEUTRO"\n" );
    }

    printf("\t"CELESTE"Uso el iterador externo para mostrar mis Pokemon)"NEUTRO"\n");
    hash_iterador_t* it = hash_iterador_crear(pokedex);
    size_t cantidad2 = 0;
    while(hash_iterador_tiene_siguiente(it)){
      const char* clave = hash_iterador_siguiente(it);
      if(clave){
        cantidad2++;
        printf("\tPokemon Registrado: %s, Id Pokedex: %s\n",(char*)hash_obtener(pokedex, clave), clave);
      }
    }
    if(cantidad2 == 6){
      printf("\t"VERDE"Se mostraron todos los Pokemon"NEUTRO"\n" );
    }
    else{
      printf("\t"ROJO"FALLO"NEUTRO"\n" );
    }
    hash_iterador_destruir(it);


    hash_destruir(pokedex);
}

int main(){
  int pruebas = 0, pruebas_pasadas = 0;
  printf("TDA Hash;\n");
  printf(""CELESTE"Pruebo funcinamiento:"NEUTRO"\n");
  probar_funcionamiento();
  printf(""CELESTE"Pruebas con Hash Nulo:"NEUTRO"\n");
  probar_hash_nulo(&pruebas, &pruebas_pasadas);
  printf(""CELESTE"Pruebas con Hash Vacio:"NEUTRO"\n");
  probar_hash_vacio(&pruebas, &pruebas_pasadas);
  printf(""CELESTE"Pruebas con casos borde:"NEUTRO"\n");
  casos_borde(&pruebas, &pruebas_pasadas);
  printf(""CELESTE"Pruebas con iteradores:"NEUTRO"\n");
  iteradores(&pruebas, &pruebas_pasadas);

  printf("Pasaron %d/%d pruebas\n", pruebas_pasadas, pruebas);
  return 0;
}
