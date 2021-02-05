#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define EXITO 0
#define ERROR -1
#define INICIAL 0

void mostrar(void* elemento, void* contador){
  if(elemento && contador){
    printf("%i ", *(char*)elemento);
  }  
}


void probar_lista(){
 lista_t* lista = lista_crear();
  
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6,
  siete = 7, ocho = 8, nueve = 9, diez = 10;
  
  printf("Inserto 1 y 2 a una lista vacia:\n");
  lista_insertar(lista, &uno);
  lista_insertar(lista, &dos);
  for(size_t i = 0; i < lista_elementos(lista); i++){
    printf("%i ", *(int*)lista_elemento_en_posicion(lista, i));
  }

  printf("\n");

  printf("Inserto 4 en posicion 100 (ultima):\n");
  lista_insertar_en_posicion(lista, &cuatro, 100);
  for(size_t i = 0; i < lista_elementos(lista); i++){
    printf("%i ", *(int*)lista_elemento_en_posicion(lista, i));
  }

  printf("\n");

  printf("Inserto 3 en la 'posicion 3':\n");
  lista_insertar_en_posicion(lista, &tres, 2);
  for(size_t i = 0; i < lista_elementos(lista); i++){
    printf("%i ", *(int*)lista_elemento_en_posicion(lista, i));
  }

  printf("\n");

  printf("Borro el 2:\n");
  lista_borrar_de_posicion(lista, 1);

  for(size_t i=0;i<lista_elementos(lista);i++)
    printf("%i ", *(int*)lista_elemento_en_posicion(lista, i));

  printf("\n");

  printf("Imprimo la lista usando el iterador externo: \n");
  lista_iterador_t* it = lista_iterador_crear(lista);
  while(lista_iterador_tiene_siguiente(it))
    printf("%i ", *(int*)lista_iterador_siguiente(it));
  printf("\n");

  lista_iterador_destruir(it);

  int contador = 0;
  printf("Imprimo la lista usando el iterador interno: \n");
  lista_con_cada_elemento(lista, mostrar, (void*)&contador);
  printf("\n");
  
  printf("Pongo los numeros faltantes en su respectiva posicion hasta el 10:\n");
  lista_insertar_en_posicion(lista, &dos, 1);
  lista_insertar(lista, &cinco);
  lista_insertar(lista, &seis);
  lista_insertar(lista, &siete);
  lista_insertar(lista, &ocho);
  lista_insertar(lista, &nueve);
  lista_insertar(lista, &diez);
  for(size_t i = 0; i < lista_elementos(lista); i++){
    printf("%i ", *(int*)lista_elemento_en_posicion(lista, i));
  }

  printf("\n");

  lista_destruir(lista);
}

void probar_cola(){
  lista_t* cola = lista_crear();

  char hola[]={'h','o','l','a'};

  for(size_t i = 0 ; i < 4 ; i++){
    printf("encolo %c, ", hola[i]);
    lista_encolar(cola, &hola[i]);
  }
  
  printf("\nDesencolo y muestro: ");
  while(!lista_vacia(cola)){
    printf("%c", *(char*)lista_primero(cola));
    lista_desencolar(cola);
  }
  printf("\n");
  lista_destruir(cola);
}

void probar_pila(){
  lista_t* pila = lista_crear();
  char mundo[] = {'o','d','n','u', 'm'};

  for(int i = 0; mundo[i]!= 0 ;i++){
    printf("Apilo %c\n", mundo[i]);
    lista_apilar(pila, &mundo[i]);
  }

  printf("\nDesapilo y muestro los elementos apilados: ");
  while(!lista_vacia(pila)){
    printf("%c", *(char*)lista_tope(pila));
    lista_desapilar(pila);
  }
  printf("\n");

  lista_destruir(pila);
}

int probar_listas_nulas(lista_t* lista){
  int contador_exitos = 0;
  char elemento = 'F';
  if(lista_insertar(lista, &elemento) == ERROR){
    printf("\tlista_insertar: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar: FALLA :(\n");
  }

  if(lista_insertar_en_posicion(lista, &elemento, 1) == ERROR){
    printf("\tlista_insertar_en_posicion: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar_en_posicion: FALLA :(\n");
  }

  if(lista_borrar(lista) == ERROR){
    printf("\tlista_borrar: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_borrar: FALLA :(\n");
  }

  if(lista_borrar_de_posicion(lista, 1) == ERROR){
    printf("\tlista_lista_borrar_de_posicion: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_borrar_de_posicion: FALLA :(\n");
  }

  if(lista_elemento_en_posicion(lista, 1) == NULL){
    printf("\tlista_elemento_en_posicion: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_elemento_en_posicion: FALLA :(\n");
  }

  if(lista_ultimo(lista) == NULL){
    printf("\tlista_ultimo: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_ultimo: FALLA :(\n");
  }

  if(lista_apilar(lista, &elemento) == ERROR){
    printf("\tlista_apilar: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_apilar: FALLA :(\n");
  }

  if(lista_desapilar(lista) == ERROR){
    printf("\tlista_desapilar: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_desapilar: PASA :(\n");
  }

  if(lista_encolar(lista, &elemento) == ERROR){
    printf("\tlista_encolar: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_encolar: FALLA :(\n");
  }

  if(lista_desencolar(lista) == ERROR){
    printf("\tlista_desencolar: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_desencolar: FALLA :(\n");
  }

  if(lista_primero(lista) == NULL){
    printf("\tlista_primero: PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_primero: FALLA :(\n"); 
  }

  lista_iterador_t* it = lista_iterador_crear(lista);
  if(it == NULL){
    printf("\tlista_iterador_crear: PASA :)\n");  
    contador_exitos++;
  }
  else{
    printf("\tlista_iterador_crear: FALLA :(\n");   
  }

  return contador_exitos;
}

int probar_elementos_nulos(void* elemento){
  int contador_exitos = 0;
  lista_t* lista = lista_crear();
  if(!lista){
    return ERROR;
  }

  if(lista_insertar(lista, elemento) != ERROR){
    printf("\tlista_insertar: PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar: FALLA :(\n"); 
  }

  if(lista_insertar_en_posicion(lista, elemento, 1) != ERROR){
    printf("\tlista_insertar_en_posicion: PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar_en_posicion: FALLA :(\n"); 
  }

  if(lista_apilar(lista, elemento) == ERROR){
    printf("\tlista_apilar: PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_apilar: FALLA :(\n"); 
  }

  if(lista_encolar(lista, elemento) == ERROR){
    printf("\tlista_encolar: PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_encolar: FALLA :(\n"); 
  }

  lista_destruir(lista);
  return contador_exitos;
}

int probar_casos_borde(){
  int contador_exitos = 0;
  int cero = 0;
  
  printf("Uso listas vacías:\n");
  lista_t * lista = lista_crear();
  int inserto_vacio = lista_insertar(lista, &cero);
  if(inserto_vacio == EXITO){
    printf("\tlista_insertar PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar FALLA :(\n");
  }
  lista_borrar(lista);

  int inserto_pos_vacio = lista_insertar_en_posicion(lista, &cero, 465);
  if(inserto_pos_vacio == EXITO){
    printf("\tlista_insertar_en_posicion PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar_en_posicion FALLA :(\n");
  }
  lista_borrar(lista);

  int borro_vacio = lista_borrar(lista);
  if(borro_vacio == ERROR){
    printf("\tlista_borrar PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_borrar FALLA :(\n");
  }
  lista_borrar(lista);

  int borro_pos_vacio = lista_borrar_de_posicion(lista, 4);
  if(borro_pos_vacio == ERROR){
    printf("\tlista_borrar_de_posicion PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_borrar_de_posicion FALLA :(\n");
  }
  lista_borrar(lista);

  void* elemento_posicion = lista_elemento_en_posicion(lista, 5);
  if(elemento_posicion == NULL){
    printf("\tlista_insertar_en_posicion PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar_en_posicion FALLA :(\n");
  }

  void* ultimo = lista_ultimo(lista);
  if(ultimo == NULL){
    printf("\tlista_ultimo PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_ultimo FALLA :(\n");
  }

  int apilo_vacio = lista_apilar(lista, &cero);
  if(apilo_vacio == EXITO){
    printf("\tlista_apilar PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_apilar FALLA :(\n");
  }
  lista_borrar(lista);

  int desapilar_vacio = lista_desapilar(lista);
  if(desapilar_vacio == ERROR){
    printf("\tlista_desapilar PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_desapilar FALLA :(\n");
  }

  void* tope = lista_tope(lista);
  if(tope == NULL){
    printf("\tlista_tope PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_tope FALLA :(\n");
  }

  int desencolo_vacio = lista_encolar(lista, &cero);
  if(desencolo_vacio == EXITO){
    printf("\tlista_encolar PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_encolar FALLA :(\n");
  }
  lista_borrar(lista);

  int desapilo_vacio = lista_desapilar(lista);
  if(desapilo_vacio == ERROR){
    printf("\tlista_desapilar PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_desapilar FALLA :(\n");
  }

  void* primero = lista_primero(lista);
  if(primero == NULL){
    printf("\tlista_primero PASA :)\n"); 
    contador_exitos++;
  }
  else{
    printf("\tlista_primero FALLA :(\n");
  }

  printf("Inserto elementos para que deje de estar vacía\n");
  lista_insertar(lista, &cero);
  lista_insertar(lista, &cero);
  lista_insertar(lista, &cero);
  printf("Pruebo posiciones que no existen:\n");
  size_t posicion_zapada = 512;
  if(lista_insertar_en_posicion(lista, &cero, posicion_zapada) == EXITO){
    printf("\tlista_insertar_en_posicion PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_insertar_en_posicion FALLA :(\n");
  }

  if(lista_borrar_de_posicion(lista, posicion_zapada) == EXITO){
    printf("\tlista_borrar_de_posicion PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_borrar_de_posicion FALLA :(\n");
  }

  if(lista_elemento_en_posicion(lista, posicion_zapada) == EXITO){
    printf("\tlista_elemento_en_posicion PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_elemento_en_posicion FALLA :(\n");
  }

  lista_destruir(lista);
  return contador_exitos;
}

int probar_it(){
  int contador_exitos = 0;
  lista_t* lista_vacia = lista_crear();

  printf("Creo iterador con lista nula:\n");
  if(lista_iterador_crear(NULL) == NULL){
    printf("lista_iterador_crear PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("lista_iterador_crear FALLA :(\n");
  }

  printf("Creo iterador con lista vacia:\n");
  lista_iterador_t* it = lista_iterador_crear(lista_vacia);
  if(it != NULL){
    printf("lista_iterador_crear PASA :)\n");
    lista_iterador_destruir(it);
    contador_exitos++;
  }
  else{
    printf("lista_iterador_crear FALLA :(\n");
  }

  printf("Mando iteradores nulos:\n");
  if(!lista_iterador_tiene_siguiente(NULL)){
    printf("\tlista_iterador_tiene_siguiente PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_iterador_tiene_siguiente FALLA :(\n");
  }
  
  if(lista_iterador_siguiente(NULL) == NULL){
    printf("\tlista_iterador_siguiente PASA :)\n");
    contador_exitos++;
  }
  else{
    printf("\tlista_iterador_siguiente FALLA :(\n");
  }

  lista_destruir(lista_vacia);

  return contador_exitos;
}

void probar_mateo(){
  int contador_exitos = 0;
  printf("\nMando listas nulas:\n");
  int pruebas_nulas = probar_listas_nulas(NULL);
  contador_exitos += pruebas_nulas;
  printf("\nMando elementos nulos:\n");
  int elementos_nulos = probar_elementos_nulos(NULL);
  contador_exitos += elementos_nulos;
  printf("\nPruebo casos borde\n");
  int casos_borde = probar_casos_borde();
  contador_exitos += casos_borde; 
  printf("Pruebo con iteradores\n");
  int it = probar_it();
  contador_exitos+= it;
  printf("Pasaron %i/35 pruebas\n", contador_exitos);
}

int main(){

  printf("Pruebo lista:\n");
  probar_lista();
  
  printf("\nPruebo cola:\n");
  probar_cola();

  printf("\nPruebo pila:\n");
  probar_pila();
  
  printf("\nPruebo con mis pruebas(?:\n");
  probar_mateo();

  return 0;
}
