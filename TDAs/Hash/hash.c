#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"
#include "hash.h"
#include "hash_iterador.h"

#define INICIAL 0
#define ERROR -1
#define EXITO 0
#define MIN_CAPACIDAD 3
#define MAX_CLAVE 50
#define PAR 2
#define FACTOR_CARGA_MAX 0.75

typedef struct nodo{
  char* clave;
  void* valor;
}nodo_t;

struct hash{
  size_t capacidad;
  size_t cantidad;
  lista_t** vector;
  hash_destruir_dato_t destructor;
};

struct hash_iter{
    hash_t* hash;
    size_t indice_lista;
    size_t indice_vector;
};

//me copio de uds
char* dup_string(const char* s){
  if(!s)
    return NULL;

  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

/*
* PRE: Recibe un puntero a hash
* POST: inicializa en NULL todas las listas de su vector
*/
void inicializar_vector(hash_t* hash){
  for(int i = 0; i < (int)hash->capacidad; i++){
    hash->vector[i] = NULL;
  }
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
  if(!capacidad) return NULL;
  hash_t* hash = malloc(sizeof(hash_t));
  if(!hash) return NULL;
  hash->cantidad = INICIAL;
  if(capacidad < MIN_CAPACIDAD){
    hash->capacidad = MIN_CAPACIDAD;
  }
  if(capacidad % PAR == 0){
    hash->capacidad = capacidad+1;
  }
  else{
    hash->capacidad = capacidad;
  }
  hash->destructor = destruir_elemento;
  hash->vector = malloc(sizeof(lista_t*)*hash->capacidad);
  if(!hash->vector){
    free(hash);
    return NULL;
  }
  inicializar_vector(hash);
  return hash;
}

/*
* PRE: Recibe una clave
* POST: Funcion de hasheo, encripta la clave recibida y la devuelve
*/
size_t hasheo(const char* clave){
    return (size_t)clave[1]*strlen(clave);
}

/*
* PRE: Recibe una clave y un elemento
* POST: Crea un nodo con dicha clave y elemento y lo devuelve
*/
nodo_t* nodo_crear(char* clave, void* elemento){
  nodo_t* nodo = malloc(sizeof(nodo_t));
  if(!nodo) return NULL;
  nodo->clave = clave;
  nodo->valor = elemento;
  return nodo;
}

/*
* PRE: Recibe un elemento y un hash
* POST: Libera el elemento del hash
*/
void destructor_lista(void* elemento, void* hash){
  nodo_t* nodo = (nodo_t*)elemento;
  if(((hash_t*)hash)->destructor){
    ((hash_t*)hash)->destructor(nodo->valor);
  }
  free(nodo->clave);
  free(nodo);
}

/*
* PRE: Recibe un Hash, una clave y una posicion
* POST: Busca y devuelve el valor guardado en el vector del hash en esa posicion
*/
void* valor_nodo(hash_t* hash, const char* clave, size_t pos_hash){
  bool encontro = false;
  nodo_t* a_devolver;
  lista_iterador_t* it = lista_iterador_crear(hash->vector[pos_hash]);
  while(lista_iterador_tiene_siguiente(it) && !encontro){
    a_devolver = (nodo_t*)lista_iterador_siguiente(it);
    if(!strcmp((char*)a_devolver->clave, (char*)clave)){
      lista_iterador_destruir(it);
      return a_devolver->valor;
    }
  }
  lista_iterador_destruir(it);
  return NULL;
}

void* hash_obtener(hash_t* hash, const char* clave){
  if(!hash || !clave) return NULL;
  size_t pos_hash = hasheo((char*)clave)%hash->capacidad;
  return valor_nodo(hash, clave, pos_hash);
}

bool hash_contiene(hash_t* hash, const char* clave){
  if(!hash || !clave) return false;
  nodo_t* nodo = (nodo_t*)hash_obtener(hash, clave);
  if(nodo){
    return true;
  }
  else{
    return false;
  }
}

/*
* PRE: Recibe un Hash, una clave, una posicion y un iterador de lista
* POST: Busca y borra el nodo guardado en el vector del hash en esa posicion
*/
int borrar_nodo(hash_t* hash, const char* clave, size_t pos_hash, lista_iterador_t* it){
  nodo_t* a_borrar;
  size_t pos = 0;
  bool encontro = false;
  while(lista_iterador_tiene_siguiente(it) && !encontro){
    a_borrar = (nodo_t*)lista_iterador_siguiente(it);
    if(!strcmp((char*)a_borrar->clave, (char*)clave)){
      lista_borrar_de_posicion(hash->vector[pos_hash], pos);
      if(hash->destructor){
        hash->destructor(a_borrar->valor);
      }
      free(a_borrar->clave);
      free(a_borrar);
      encontro = true;
    }
    pos++;
  }
  if(!encontro){
    lista_iterador_destruir(it);
    return ERROR;
  }
  lista_iterador_destruir(it);
  hash->cantidad--;
  return EXITO;
}

int hash_quitar(hash_t* hash, const char* clave){
  if(!hash || !clave) return ERROR;
  size_t pos_hash = hasheo((char*)clave)%hash->capacidad;
  lista_iterador_t* it = lista_iterador_crear(hash->vector[pos_hash]);
  if(!it){
    return ERROR;
  }
  return borrar_nodo(hash, clave, pos_hash, it);
}

size_t hash_cantidad(hash_t* hash){
  if(!hash) return 0;
  return hash->cantidad;
}

/*
* PRE: Recibe dos numeros no negativos
* POST: Calcula si debe rehashear y devuelve true o false segun corresponda
*/
bool debe_rehash(size_t capacidad, size_t cantidad){
  return (float)(cantidad / capacidad) > FACTOR_CARGA_MAX;
}

hash_iterador_t* hash_iterador_crear(hash_t* hash){
  if(!hash) return NULL;
  hash_iterador_t* it = calloc(1, sizeof(struct hash_iter));
  if(!it) return NULL;
  it->hash = hash;
  return it;
}

bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
  bool tiene_siguiente = false;
  while(iterador->hash->capacidad > iterador->indice_vector && !tiene_siguiente){
    if(lista_vacia(iterador->hash->vector[iterador->indice_vector])){
      iterador->indice_vector++;
    }
    else{
      if(lista_elemento_en_posicion(iterador->hash->vector[iterador->indice_vector], iterador->indice_lista) != NULL){
        tiene_siguiente = true;
      }
    }
  }
  if(!tiene_siguiente){
    return false;
  }
  return true;
}

const char* hash_iterador_siguiente(hash_iterador_t* iterador){
  if(!iterador || !hash_iterador_tiene_siguiente(iterador)) return NULL;
  nodo_t* nodo = (nodo_t*)lista_elemento_en_posicion(iterador->hash->vector[iterador->indice_vector], (size_t)iterador->indice_lista);
  iterador->indice_lista++;
  if(iterador->indice_lista >= lista_elementos(iterador->hash->vector[iterador->indice_vector])){
    iterador->indice_vector++;
    iterador->indice_lista = 0;
  }

  return (char*)nodo->clave;
}

void hash_iterador_destruir(hash_iterador_t* iterador){
  free(iterador);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  if(!hash || !funcion) return 0;
  size_t claves = 0;
  bool resultado_funcion = false;
  hash_iterador_t* it = hash_iterador_crear(hash);
  while(hash_iterador_tiene_siguiente(it) && !resultado_funcion){
    const char* clave = hash_iterador_siguiente(it);
    resultado_funcion = funcion(hash, clave, aux);
    claves++;
  }
  hash_iterador_destruir(it);
  return claves;
}

/*
* PRE: Recibe un numero no negativo
* POST: Aumenta ese numero y se fija si es par o no, luego lo devuelve
*/
size_t aumento_capacidad(size_t capacidad_vieja){
  size_t capacidad_nueva = capacidad_vieja += capacidad_vieja/2;
  if(capacidad_nueva % PAR == 0) return capacidad_nueva+1;
  else{
    return capacidad_nueva;
  }
}

/*
* PRE: Recibe un Hash, una clave y un auxiliar
* POST: Inserta nodos en el hash, si pudo devuelve false, si no, true
*/
bool insertar_nuevos(hash_t* hash_viejo, const char* clave, void* aux){
  if(hash_insertar(((hash_t*)aux), clave, hash_obtener(hash_viejo, clave)) == EXITO) return false;
  return true;
}

/*
* PRE: Recibe un nodo y un hash
* POST: Libera el nodo
*/
void destructor_de_nodos(void* nodo, void* hash){
  free(((nodo_t*)nodo)->clave);
  free(nodo);
}

/*
* PRE: Recibe dos hashes
* POST: Inicializa y carga un hash, luego vacia el otro
*/
void llenar_hash(hash_t* hash, hash_t* hash_nuevo){
  hash->vector = realloc(hash->vector, (hash_nuevo->capacidad)*(sizeof(lista_t*)));
  for(size_t i = hash->capacidad; i < hash_nuevo->capacidad; i++){
    hash->vector[i] = NULL;
  }
  hash->capacidad = hash_nuevo->capacidad;
  hash->cantidad = hash_nuevo->cantidad;
  for(int i = 0; i < hash_nuevo->capacidad; i++){
    lista_con_cada_elemento(hash->vector[i], destructor_de_nodos, hash);
    lista_destruir(hash->vector[i]);
    hash->vector[i] = hash_nuevo->vector[i];
  }
}

/*
* PRE: Recibe un puntero a puntero hash
* POST: Llama a funciones para que se aumente la capacidad y se reinserten los elementos
*/
void rehash(hash_t** hash){
  hash_t* hash_nuevo = hash_crear((*hash)->destructor, aumento_capacidad((*hash)->capacidad));
  hash_con_cada_clave(*hash, insertar_nuevos, hash_nuevo);
  llenar_hash(*hash, hash_nuevo);
  free(hash_nuevo->vector);
  free(hash_nuevo);
  *hash = hash_nuevo;
}

/*
* PRE: Recibe un Hash, una clave y una posicion
* POST: Inserta el elemento en la posicion del hash
*/
int insertar(hash_t* hash, const char* clave, void* elemento, size_t pos){
  if(!hash->vector[pos]){
    hash->vector[pos] = lista_crear();
    if(!hash->vector[pos]) return ERROR;
  }
  nodo_t* nodo = nodo_crear(dup_string(clave), elemento);
  if(!lista_insertar(hash->vector[pos], nodo)){
    hash->cantidad++;
    if(debe_rehash(hash->capacidad, hash->cantidad)){
      rehash(&hash);
    }
    return EXITO;
  }
  return ERROR;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(!hash || !clave) return ERROR;
  if(hash_contiene(hash, clave)){
    hash_quitar(hash, clave);
  }
  size_t pos = hasheo(clave)%hash->capacidad;
  return insertar(hash, clave, elemento, pos);
}

void hash_destruir(hash_t* hash){
  if(!hash) return;
  for(int i = 0; i < hash->capacidad; i++){
    if(hash->vector[i]){
      lista_con_cada_elemento(hash->vector[i], destructor_lista, hash);
      lista_destruir(hash->vector[i]);
    }
  }
  free(hash->vector);
  free(hash);
}
