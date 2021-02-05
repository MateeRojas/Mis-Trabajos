#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "lista.h"

#define EXITO 0
#define ERROR -1
#define INICIAL 0

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
 }nodo_t;

struct lista{
	size_t cantidad;
	nodo_t* primero;
	nodo_t* ultimo;
};

struct lista_iterador {
	lista_t* lista;
	nodo_t* indice;
};


lista_t* lista_crear(){
	lista_t* lista = calloc(1, sizeof(lista_t));
		if(!lista){
		return NULL;
	}

	return lista;
}

/*
 * Recibe un elemento de cualquier tipo
 * Reserva memoria para un nodo, lo inicilializa en NULL y
 * asigna el elemento recibido al nodo
 */
nodo_t* generar_nodo(void* elemento){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo){
		return NULL;
	}
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return nodo;
}

/*
 * Recibe una lista
 * Chequea si no tiene nada, en ese caso devuelve true,
 * si no, false
 */
bool lista_vacia(lista_t* lista){
	if(lista == NULL){
		return true;
	}

	return lista->primero == NULL;

}


/*
 * Recibe una lista
 * Chequea si es NULL, en ese caso devuelve true,
 * si no, false
 */
bool lista_nula(lista_t* lista){
	if(lista == NULL){

	}

	return lista == NULL;
}

size_t lista_elementos(lista_t* lista){
	if(lista_nula(lista)){
		return 0;
	}

	return lista->cantidad;
}

int insertar_pri(lista_t* lista, nodo_t* nodo){
	lista->primero = nodo;
	lista->ultimo = nodo;
	lista->cantidad++;

	return EXITO;
}

/*
 * Recibe una lista y un nodo a insertar
 * Inserta el nodo al final de la lista y aumenta la contidad
 * de nodos de la lista
 */
int insertar_al_final(lista_t* lista, nodo_t* nodo){
	lista->ultimo->siguiente = nodo;
	lista->ultimo = nodo;
	lista->cantidad++;

	return EXITO;
}

int lista_insertar(lista_t* lista, void* elemento){
	if(lista_nula(lista)){
		return ERROR;
	}
	else{
		if(lista_vacia(lista)){
			nodo_t* nodo = generar_nodo(elemento);
			insertar_pri(lista, nodo);
		}
		else{
			nodo_t* nodo = generar_nodo(elemento);
			insertar_al_final(lista, nodo);
		}

		return EXITO;
	}
}

/*
 * Recibe una lista y un nodo a insertar
 * Inserta el nodo en el primer logar y aumenta la cantidad
 * de nodos de lista
 */
int insertar_al_principio(lista_t* lista, nodo_t* nodo){
	nodo_t* aux = lista->primero;
	lista->primero = nodo;
	nodo->siguiente = aux;
	lista->cantidad++;

	return EXITO;
}

/*
 * Recibe una lista, un nodo a insertar y la posicion donde se quiere insertar
 * Recorre la lista hasta la posicion anterior de la indicada e inserta el nodo
 * en la siguiente posicion, redireccionando el contexto y aumentando la cantidad
 */
int insert(lista_t* lista, nodo_t* nodo, size_t posicion){
	size_t contador = INICIAL;
	nodo_t* i = lista->primero;
	while(i != NULL){
		if(contador == posicion-1){
			nodo_t* nuevo = i;
			nodo_t* aux = i->siguiente;
			nuevo->siguiente = nodo;
			nodo->siguiente = aux;
			lista->cantidad++;
			i = NULL;
		}
		else{
			contador++;
			i = i->siguiente;
		}
	}

	return EXITO;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(lista_vacia(lista)){
		lista_insertar(lista, elemento);
	}
	else if(posicion == INICIAL){
		nodo_t* nodo = generar_nodo(elemento);
		insertar_al_principio(lista, nodo);
	}
	else if(posicion > lista->cantidad){
		nodo_t* nodo = generar_nodo(elemento);
		insertar_al_final(lista, nodo);
	}
	else{
		nodo_t* nodo = generar_nodo(elemento);
		insert(lista, nodo, posicion);
	}

	return EXITO;
}

/*
 * Recibe una lista con un nodo
 * Elimina el unico nodo, liberando su memoria
 * y disminuyendo la cantidad
 */
int eliminar_unico(lista_t* lista){
	free(lista->primero);
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->cantidad--;

	return EXITO;
}

/*
 * Recibe una lista
 * Libera el ultimo nodo, redireccionando el contexto con ayuda de variables auxiliares
 * y disminuye la cantidad
 */
int eliminar_ultimo(lista_t * lista){
	nodo_t* aux = lista->primero;
	nodo_t* anterior;
	while(aux != NULL){
		if(aux->siguiente == NULL){
			anterior->siguiente = NULL;
			free(aux);
			aux = NULL;
			lista->cantidad--;
			lista->ultimo = anterior;
		}
		else{
			anterior = aux;
			aux = aux->siguiente;
		}
	}

	return EXITO;
}

int lista_borrar(lista_t* lista){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(lista_vacia(lista)){
		return ERROR;
	}
	else if(lista->cantidad == 1){
		eliminar_unico(lista);
	}
	else{
		eliminar_ultimo(lista);
	}

	return EXITO;
}

/*
 * Recibe una lista
 * Libera el primer elemento, redireccionando el contexto
 * y disminuye la cantidad
 */
int borrar_primero(lista_t* lista){
	nodo_t* aux = lista->primero;
	lista->primero = aux->siguiente;
	free(aux);
	lista->cantidad--;

	return EXITO;
}


/*
 * Recibe una lista y la posicion en la cual se quiere eliminar un nodo
 * Recorre la lista hasta el anterior elemento a eliminar y elimina el siguiente,
 * redireccionando el contexto y disminuyendo la cantidad
 */
int borrar_de_posicion(lista_t* lista, size_t posicion){
	size_t contador = INICIAL;
	nodo_t* i = lista->primero;
	while(i != NULL){
		if(contador == posicion-1){
			nodo_t* aux = i;
			nodo_t* prescindible = i->siguiente;
			aux->siguiente = prescindible->siguiente;
			free(prescindible);
			lista->cantidad--;
			i = NULL;
		}
		else{
			contador++;
			i = i->siguiente;
		}
	}

	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(lista_vacia(lista)){

		return ERROR;
	}

	if(posicion == INICIAL){
		borrar_primero(lista);
	}
	else if(posicion+1 >= lista->cantidad){
		lista_borrar(lista);
	}
	else{
		borrar_de_posicion(lista, posicion);
	}

	return EXITO;
}

void* lista_ultimo(lista_t* lista){
	if(lista_nula(lista) || lista_vacia(lista)){
		return NULL;
	}
	else{
		return lista->ultimo->elemento;
	}
}

/*
 * Recibe una lista, una posicion y un elemento a rellenar
 * Llena el elemento con el contenido del nodo en la posicion indicada
 */
void* determinar_elemento(lista_t* lista, size_t posicion, void* elemento){
	size_t contador = 0;
	nodo_t* i = lista->primero;
	while(i != NULL){
		if(contador == posicion){
			elemento = i->elemento;
			i = NULL;
		}
		else{
			contador++;
			i = i->siguiente;
		}
	}

	return elemento;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	void* elemento = NULL;
	if(lista_nula(lista)){
		return NULL;
	}
	else if(lista_vacia(lista)){

		return NULL;
	}
	else if(posicion > lista->cantidad){
		return NULL;
	}
	else{
		elemento = determinar_elemento(lista, posicion, elemento);
	}

	return elemento;
}

/*
 * Recibe una lista vacia y un nodo
 * Apila el nodo
 */
int apilar_primero(lista_t* lista, nodo_t* nodo){
	lista->primero = nodo;
	lista->ultimo = nodo;
	lista->cantidad++;

	return EXITO;
}

/*
 * Recibe una lista y un nodo
 * Apila el nodo
 */
int apilar(lista_t* lista, nodo_t* nodo){
	lista->ultimo->siguiente = nodo;
	lista->ultimo = nodo;
	lista->cantidad++;

	return EXITO;
}

int lista_apilar(lista_t* lista, void* elemento){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(!elemento){
		return ERROR;
	}

	nodo_t* nodo = generar_nodo(elemento);
	if(lista_vacia(lista)){
		apilar_primero(lista, nodo);
	}
	else{
		apilar(lista, nodo);
	}

	return EXITO;
}

/*
 * Recibe una lista vacia y un nodo
 * Desapila el nodo
 */
int desapilar_unico(lista_t* lista){
	free(lista->primero);
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->cantidad--;

	return EXITO;
}

/*
 * Recibe una lista y un nodo
 * Desapila el nodo
 */
int desapilar(lista_t* lista){
	nodo_t* aux = lista->primero;
	nodo_t* anterior;
	while(aux != NULL){
		if(aux->siguiente == NULL){
				anterior->siguiente = NULL;
			free(aux);
			aux = NULL;
			lista->cantidad--;
			lista->ultimo = anterior;
		}
		else{
			anterior = aux;
			aux = aux->siguiente;
		}
	}

	return EXITO;
}

int lista_desapilar(lista_t* lista){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(lista_vacia(lista)){

		return ERROR;
	}
	else if(lista->cantidad == 1){
		desapilar_unico(lista);
	}
	else{
		desapilar(lista);
	}

	return EXITO;
}

void* lista_tope(lista_t* lista){
	if(lista_nula(lista) || lista_vacia(lista)){
			return NULL;
		}
		else{
			return lista->ultimo->elemento;
		}
}

void* lista_primero(lista_t* lista){
	if(lista_nula(lista)){
		return NULL;
	}

	if(lista_vacia(lista)){
		return NULL;
	}
	else{
		return lista->primero->elemento;
	}
}

/*
 * Recibe una lista vacia y un nodo
 * Encola el nodo
 */
int encolar_primero(lista_t* lista, nodo_t* nodo){
	lista->primero = nodo;
	lista->ultimo = nodo;
	lista->cantidad++;

	return EXITO;
}

/*
 * Recibe una lista y un nodo
 * Encola el nodo
 */
int encolar(lista_t* lista, nodo_t* nodo){
	lista->ultimo->siguiente = nodo;
	lista->ultimo = nodo;
	lista->cantidad++;

	return EXITO;
}

int lista_encolar(lista_t* lista, void* elemento){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(!elemento){
		return ERROR;
	}

	nodo_t* nodo = generar_nodo(elemento);
	if(lista_vacia(lista)){
		encolar_primero(lista, nodo);
	}
	else{
		encolar(lista, nodo);
	}

	return EXITO;
}

/*
 * Recibe una lista vacia y un nodo
 * Desncola el nodo
 */
int desencolar_unico(lista_t* lista){
	free(lista->primero);
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->cantidad--;

	return EXITO;
}

/*
 * Recibe una lista y un nodo
 * Desncola el nodo
 */
int desencolar(lista_t* lista){
	nodo_t* aux = lista->primero;
	lista->primero = aux->siguiente;
	free(aux);
	lista->cantidad--;

	return EXITO;
}

int lista_desencolar(lista_t* lista){
	if(lista_nula(lista)){
		return ERROR;
	}

	if(lista_vacia(lista)){
		return ERROR;
	}
	else if(lista->cantidad == 1){
		desencolar_unico(lista);
	}
	else{
		desencolar(lista);
	}

	return EXITO;
}

bool iterador_nulo(lista_iterador_t* it){
	return it == NULL;
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(lista_nula (lista)){
		return NULL;
	}
	else{
		lista_iterador_t* it = calloc(1, sizeof(lista_iterador_t));
		if(!it){
			return NULL;
		}
		it->lista = lista;
		it->indice = lista->primero;

		return it;
	}
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(iterador_nulo(iterador)){
		return false;
	}
	return iterador->indice != NULL;
}

void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if(iterador_nulo(iterador) || !lista_iterador_tiene_siguiente(iterador)){
		return NULL;
	}
	void* elemento = iterador->indice->elemento;
	iterador->indice = iterador->indice->siguiente;

	return elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
	if(!iterador_nulo(iterador)){
		free(iterador);
	}
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void *contexto){
	if(lista_nula(lista)){
		return;
	}

	lista_iterador_t* it = lista_iterador_crear(lista);
	while(lista_iterador_tiene_siguiente(it)){
		funcion(lista_iterador_siguiente(it), contexto);
	}
	lista_iterador_destruir(it);
}

void lista_destruir(lista_t* lista){
	if(!lista_vacia(lista)){
		nodo_t* i = lista->primero;
    	nodo_t* aux;
    	while (i != NULL) {
        	aux = i;
        	i = i->siguiente;
       	 	free(aux);
    	}
	}

	free(lista);
}
