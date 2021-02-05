#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "abb.h"

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2
#define PRIMERA_POSICION 0
#define IGUALES 0
#define SEGUNDO -1
#define PRIMERO 1
#define EXITO 0
#define ERROR -1
#define VACIO 0
#define NO false
#define SI true

/*
 * Ya vas a ver por qué
*/
nodo_abb_t* nodo_borrar(abb_t* arbol, nodo_abb_t* nodo, void* elemento, bool* pudo_borrar);

/*
 * PRE: recibe un elemento para crear un nodo
 * POST: reserva memoria para un nodo_abb_t y asigna el elemento
 * al elemento del nodo. Luego lo devuelve
*/
nodo_abb_t* crear_nodo(void* elemento){
  nodo_abb_t* nodo = calloc(1, sizeof(nodo_abb_t));
  nodo->elemento = elemento;
  return nodo;
}

void* arbol_raiz(abb_t* arbol){
  if(!arbol || arbol_vacio(arbol)){
    return NULL;
  }
  return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
  if(!arbol){
    return true;
  }
  return (arbol->nodo_raiz == NULL);
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
  if(!comparador){
    return NULL;
  }
  abb_t* abb = calloc(3, sizeof(abb_t*));
  if(!abb){
    return NULL;
  }
  abb->comparador = comparador;
  abb->destructor = destructor;
  return abb;
}

/*
 * PRE: recibe un arbol vacio y un elemento para insertarle
 * POST: crea el nodo y lo asigna a la raiz del arbol
*/
int insertar_primero(abb_t* arbol, void* elemento){
  arbol->nodo_raiz = crear_nodo(elemento);
  return EXITO;
}

/*
 * PRE: recibe un nodo a rellenar y un elemento
 * POST: crea un nodo, le asigna el elemento y lo iguala
 * al nodo recibido
*/
nodo_abb_t* nodo_nuevo(nodo_abb_t* nodo, void* elemento){
  nodo_abb_t* nodo_nuevo = crear_nodo(elemento);
  nodo = nodo_nuevo;
  return nodo;
}

/*
 * PRE: funcion recursiva, recibe la raiz del arbol, un elemento y un arbol
 * POST: recorre recursivamente el arbol hasta encontrar el lugar donde se debe
 * insertar el nuevo elemento (usando el comparador). Inserta el nuevo nodo
 * a travez de una función
*/
nodo_abb_t* insertar(nodo_abb_t* nodo, void* elemento, abb_t* arbol){
  if(!nodo){
    nodo = nodo_nuevo(nodo, elemento);
  }
  else if(arbol->comparador(nodo->elemento, elemento) >= IGUALES){
    nodo->izquierda=insertar(nodo->izquierda, elemento, arbol);
  }
  else{
    nodo->derecha=insertar(nodo->derecha, elemento, arbol);
  }
  return nodo;
}

int arbol_insertar(abb_t* arbol, void* elemento){
  if(!arbol){
    return ERROR;
  }
  if(arbol_vacio(arbol)){
    insertar_primero(arbol, elemento);
    return EXITO;
  }
  else{
    arbol->nodo_raiz=insertar(arbol->nodo_raiz, elemento, arbol);
    return EXITO;
  }
}

/*
* PRE: funcion recursiva, recibe un arbol, el elemento buscado y la raiz
* POST: recorre el arbol recursivamente hasta encontrar el elemento
* (usando el comparador). Luego lo devuelve
*/
void* buscar(abb_t* arbol, void* elemento, nodo_abb_t* nodo){
    if(!nodo) return NULL;
    if(arbol->comparador(elemento, nodo->elemento) == PRIMERO){
        buscar(arbol, elemento, nodo->derecha);
    }
    else if(arbol->comparador(elemento, nodo->elemento) == SEGUNDO){
        buscar(arbol, elemento, nodo->izquierda);
    }
    return elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
  if(!arbol){
    return NULL;
  }
  return buscar(arbol, elemento, arbol->nodo_raiz);
}

/*
 * PRE: recibe un nodo a chequear
 * POST: chequea si sus dos hijos son NULL, en ese caso devuelve TRUE,
 * si no, FALSE
*/
bool es_hoja(nodo_abb_t* nodo){
  return (nodo->derecha == NULL && nodo->izquierda == NULL);
}

/*
 * PRE: recibe un nodo a chequear
 * POST: chequea si su hijo derecho es NULL, en ese caso devuelve FALSE,
 * si no, TRUE
*/
bool tiene_derecha(nodo_abb_t* nodo){
  return (nodo->derecha != NULL);
}

/*
 * PRE: recibe un nodo a chequear
 * POST: chequea si su hijo izquierdo es NULL, en ese caso devuelve FALSE,
 * si no, TRUE
*/
bool tiene_izquierda(nodo_abb_t* nodo){
  return (nodo->izquierda != NULL);
}

/*
 * PRE: funcion recursiva, recibe un nodo
 * POST: recorre recursivamente el sub-arbol hasta llegar a su hijo más
 * derecho, y lo devuelve
*/
nodo_abb_t* buscar_menor_mayor(nodo_abb_t* nodo){
  if(!nodo->derecha){
    return nodo;
  }
  return buscar_menor_mayor(nodo->derecha);
}


/*
 * PRE: recibe un arbol y un elemento a encontrar
 * POST: llama a una funcion recursiva para encontrar el nodo buscado y
 * lo devuelve
*/
void* buscar_nodo(abb_t* arbol, void* elemento){
  if(!arbol){
    return NULL;
  }
  void* nodo_buscado = buscar(arbol, elemento, arbol->nodo_raiz);
  return nodo_buscado;
}

/*
 * PRE: recibe un arbol, un nodo a borrar(sin hijos) y un booleano para chequear
 * POST: destuye el elemento del nodo y lo libera, devolviendo NULL
*/
nodo_abb_t* borrar_hoja(abb_t* arbol, nodo_abb_t* nodo, bool* pudo_borrar){
  if(!*pudo_borrar){
    arbol->destructor(nodo->elemento);
  }
  free(nodo);
  *pudo_borrar = SI;
  return NULL;
}

/*
 * PRE: recibe un arbol, un nodo a borrar(con un hijo) y un booleano para chequear
 * POST: destuye el elemento del nodo y lo libera, devolviendo su hijo izquierdo
*/
nodo_abb_t* borrar_con_izquierda(abb_t* arbol, nodo_abb_t* nodo, bool* pudo_borrar){
  nodo_abb_t* aux = nodo->izquierda;
  if(!*pudo_borrar){
    arbol->destructor(nodo->elemento);
  }
  free(nodo);
  *pudo_borrar = SI;
  return aux;
}

/*
 * PRE: recibe un arbol, un nodo a borrar(con un hijo) y un booleano para chequear
 * POST: destuye el elemento del nodo y lo libera, devolviendo su hijo derecho
*/
nodo_abb_t* borrar_con_derecha(abb_t* arbol, nodo_abb_t* nodo, bool* pudo_borrar){
  nodo_abb_t* aux = nodo->derecha;
  if(!*pudo_borrar){
    arbol->destructor(nodo->elemento);
  }
  free(nodo);
  *pudo_borrar = SI;
  return aux;
}

nodo_abb_t* borrar_con_hijes(abb_t* arbol, nodo_abb_t* nodo, bool* pudo_borrar){
  *pudo_borrar = SI;
  nodo_abb_t* menor_mayor = buscar_menor_mayor(nodo->izquierda);
  arbol->destructor(nodo->elemento);
  nodo->elemento = menor_mayor->elemento;
  nodo->izquierda = nodo_borrar(arbol, nodo->izquierda, menor_mayor->elemento, pudo_borrar);
  return nodo;
}

/*
 * PRE: funcion recursiva, recibe un arbol, un nodo, elemto a borrar y un booleano
 * para chequear
 * POST: recorre recursivamente el arbol hasta encontrar el nodo a borrar
 * (usando el comparador del arbol). Cuando lo encuentra, depende el caso llama
 * a diferentes funciones para borrar
*/
nodo_abb_t* nodo_borrar(abb_t* arbol, nodo_abb_t* nodo, void* elemento, bool* pudo_borrar){
  if(!nodo){
    return NULL;
  }
  if(!arbol->comparador(nodo->elemento, elemento)){
    if(es_hoja(nodo)){
      return borrar_hoja(arbol, nodo, pudo_borrar);
    }
    else if(!tiene_derecha(nodo)){
      return borrar_con_izquierda(arbol, nodo, pudo_borrar);
    }
    else if(!tiene_izquierda(nodo)){
      return borrar_con_derecha(arbol, nodo, pudo_borrar);
    }
    else{
      return borrar_con_hijes(arbol, nodo, pudo_borrar);
    }
  }
  if(arbol->comparador(nodo->elemento, elemento) < IGUALES){
    nodo->derecha = nodo_borrar(arbol, nodo->derecha, elemento, pudo_borrar);
    return nodo;
  }
  else{
    nodo->izquierda = nodo_borrar(arbol, nodo->izquierda, elemento, pudo_borrar);
    return nodo;
  }
}

int arbol_borrar(abb_t* arbol, void* elemento){
  if(!arbol){
    return ERROR;
  }
  bool pudo_borrar = NO;
  arbol->nodo_raiz = nodo_borrar(arbol, arbol->nodo_raiz, elemento, &pudo_borrar);
  if(pudo_borrar){
    return EXITO;
  }
  return ERROR;
}

/*
 * PRE: recibe un tamaño maximo y una posicion
 * POST: chequea si se pueden seguir agregando elementos, comparando el tamaño
 * y la posicion. Devuelve TRUE o FALSE según corresponda
*/
bool hay_espacio(int tamanio, int pos){
  return (pos < tamanio);
}

/*
 * PRE: recibr un array a cargar, un nodo cuyo dato cargaremos y la posicion actual
 * POST: asigna el elemento del nodo a la posicion dicha del array
*/
void cargar_array(void** array, nodo_abb_t* nodo, int* posicion){
  array[*posicion] = nodo->elemento;
  (*posicion)++;
}

/*
 * PRE: funcion recursiva, recibe la raiz, un array a cargar con su tamaño y la
 * posicion actual
 * POST: recursivamente, carga el array, llamando funciones, en PREORDEN
*/
void recorrer_pre(nodo_abb_t* nodo, void** array, int tamanio_array, int* posicion){
  if(!nodo || !hay_espacio(tamanio_array, *posicion)){
    return;
  }
  if(hay_espacio(tamanio_array, *posicion)){
    cargar_array(array, nodo, posicion);

  }
  if(hay_espacio(tamanio_array, *posicion)){
    recorrer_pre(nodo->izquierda, array, tamanio_array, posicion);
  }
  if(hay_espacio(tamanio_array, *posicion)){
    recorrer_pre(nodo->derecha, array, tamanio_array, posicion);
  }
}

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
  if(!arbol || arbol_vacio(arbol)){
    return VACIO;
  }
  int posicion = PRIMERA_POSICION;
  recorrer_pre(arbol->nodo_raiz, array, tamanio_array, &posicion);
  return posicion;
}

/*
 * PRE: funcion recursiva, recibe la raiz, un array a cargar con su tamaño y la
 * posicion actual
 * POST: recursivamente, carga el array, llamando funciones, en INORDEN
*/
void recorrer_in(nodo_abb_t* nodo, void** array, int tamanio_array, int* posicion){
  if(!nodo || !hay_espacio(tamanio_array, *posicion)){
    return;
  }
  if(hay_espacio(tamanio_array, *posicion)){
    recorrer_in(nodo->izquierda, array, tamanio_array, posicion);
  }
  if(hay_espacio(tamanio_array, *posicion)){
    cargar_array(array, nodo, posicion);

  }
  if(hay_espacio(tamanio_array, *posicion)){
    recorrer_in(nodo->derecha, array, tamanio_array, posicion);
  }
}

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
  if(!arbol || arbol_vacio(arbol)){
    return VACIO;
  }
  int posicion = PRIMERA_POSICION;
  recorrer_in(arbol->nodo_raiz, array, tamanio_array, &posicion);
  return posicion;
}

/*
 * PRE: funcion recursiva, recibe la raiz, un array a cargar con su tamaño y la
 * posicion actual
 * POST: recursivamente, carga el array, llamando funciones, en POSTORDEN
*/
void recorrer_post(nodo_abb_t* nodo, void** array, int tamanio_array, int* posicion){
  if(!nodo || !hay_espacio(tamanio_array, *posicion)){
    return;
  }
  if(hay_espacio(tamanio_array, *posicion)){
    recorrer_post(nodo->izquierda, array, tamanio_array, posicion);
  }
  if(hay_espacio(tamanio_array, *posicion)){
    recorrer_post(nodo->derecha, array, tamanio_array, posicion);
  }
  if(hay_espacio(tamanio_array, *posicion)){
    cargar_array(array, nodo, posicion);

  }
}

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
  if(!arbol || arbol_vacio(arbol)){
    return VACIO;
  }
  int posicion = PRIMERA_POSICION;
  recorrer_post(arbol->nodo_raiz, array, tamanio_array, &posicion);
  return posicion;
}

/*
 * PRE: funcion recursiva, recibe un arbol y su raiz
 * POST: recorre el arbol recursivamente y usa su destructor para liberar
 * elementos de los nodos seguido de la liberacion de memoria de estos
*/
void borrar_nodos(abb_t* arbol, nodo_abb_t* nodo){
  if(!nodo){
    return;
  }
  borrar_nodos(arbol, nodo->izquierda);
  borrar_nodos(arbol, nodo->derecha);
  arbol->destructor(nodo->elemento);
  free(nodo);
}

void arbol_destruir(abb_t* arbol){
  if(!arbol){
    return;
  }
  borrar_nodos(arbol, arbol->nodo_raiz);
  free(arbol);
}

/*
 * PRE: funcion recursiva, recibe un nodo raiz, una funcion bool y un puntero extra
 * POST: en inorden, ejecuta la funcion con cada elemento del arbol. Termina
 * cuando llega al final o cuando la funcion devuelve true
*/
bool inorden(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* extra){
  if(!raiz){
    return false;
  }
  if(inorden(raiz->izquierda, funcion, extra)){
    return true;
  }
  if(funcion(raiz->elemento, extra)){
    return true;
  }
  return inorden(raiz->derecha, funcion, extra);
}

/*
 * PRE: funcion recursiva, recibe un nodo raiz, una funcion bool y un puntero extra
 * POST: en postorden, ejecuta la funcion con cada elemento del arbol. Termina
 * cuando llega al final o cuando la funcion devuelve true
*/
bool postorden(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* extra){
  if(!raiz){
    return false;
  }
  if(postorden(raiz->izquierda, funcion, extra)){
    return true;
  }
  if(postorden(raiz->derecha, funcion, extra)){
    return true;
  }
  return funcion(raiz->elemento, extra);
}

/*
 * PRE: funcion recursiva, recibe un nodo raiz, una funcion bool y un puntero extra
 * POST: en preorden, ejecuta la funcion con cada elemento del arbol. Termina
 * cuando llega al final o cuando la funcion devuelve true
*/
bool preorden(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* extra){
  if(!raiz){
    return false;
  }
  if(funcion(raiz->elemento, extra)){
    return true;
  }
  if(preorden(raiz->izquierda, funcion, extra)){
    return true;
  }
  return preorden(raiz->derecha, funcion, extra);
}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
  if(!arbol || !funcion){
    return;
  }
  switch (recorrido){
    case ABB_RECORRER_INORDEN:
      inorden(arbol->nodo_raiz, funcion, extra);
      break;
    case ABB_RECORRER_PREORDEN:
      preorden(arbol->nodo_raiz, funcion, extra);
      break;
    case ABB_RECORRER_POSTORDEN:
      postorden(arbol->nodo_raiz, funcion, extra);
      break;
    default:
      return;
  }
}
