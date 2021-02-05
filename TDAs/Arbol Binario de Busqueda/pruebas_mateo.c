//Mateo Rojas 104985
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

#define EXITO 0
#define ERROR -1
#define IGUALES 0
#define SEGUNDO -1
#define PRIMERO 1
#define VACIO 0
#define ROJO     "\x1b[31m\x1b[1m"
#define VERDE    "\x1b[32m\x1b[1m"
#define CELESTE   "\x1b[0;36m"
#define NEUTRO   "\x1b[0m"

typedef struct poke{
	int id;
	char nombre;
}poke_t;

bool mostrar_hasta_17(void* elemento, void* extra){
	extra=extra;

	if(elemento){
		printf("%i ", ((poke_t*)elemento)->id);
		if(((poke_t*)elemento)->id == 17){
			return true;
		}
	}
	return false;
}

bool mostrar_hasta_16(void* elemento, void* extra){
	extra=extra;

	if(elemento){
		printf("%i ", ((poke_t*)elemento)->id);
		if(((poke_t*)elemento)->id == 16){
			return true;
		}
	}
	return false;
}

poke_t* crear_poke(int id, char nombre){
	poke_t* poke = malloc(sizeof(poke_t));
	if(poke){
		poke->id = id;
		poke->nombre = nombre;
	}
	return poke;
}

void destruir_pokes(poke_t* poke){
	if(poke){
		free(poke);
	}
}

int comparar_pokes(void* poke1, void* poke2){
	if(!poke1 || !poke2){
		return 0;
	}
	if(((poke_t*)poke1)->id > ((poke_t*)poke2)->id){
		return 1;
	}
	if(((poke_t*)poke1)->id < ((poke_t*)poke2)->id){
		return -1;
	}
	return 0;
}

int comparar_enteros(int entero1, int entero2){
	if(!entero1 || !entero2){
    return 0;
  }
  if(entero1 > entero2){
    return PRIMERO;
  }
	else if(entero2 > entero1){
    return SEGUNDO;
  }
  else return IGUALES;
	return 0;
}

void destruir_enteros(int entero){
  return;
}

bool contar_pokes(void* elemento, void* extra){
	extra=extra;

	if(elemento){
		*(int*)extra +=1;
	}

	return false;
}

bool mostrar_nombres(void* elemento, void* extra){
	extra=extra;

	if(elemento){
		printf("%c ", ((poke_t*)elemento)->nombre);
	}

	return false;
}

void abb_vacio(int* pruebas, int* pruebas_pasadas){
  abb_t* arbol_vac = arbol_crear((abb_comparador)comparar_enteros, (abb_liberar_elemento)destruir_enteros);
  int ejemplo = 1;
  int array_ejemplo[3];


  if(arbol_borrar(arbol_vac, (void*)ejemplo) == ERROR){
    printf("\tarbol_borrar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_borrar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!arbol_buscar(arbol_vac, (void*)1)){
    printf("\tarbol_buscar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_buscar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!arbol_raiz(arbol_vac)){
    printf("\tarbol_raiz: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_raiz: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_vacio(arbol_vac)){
    printf("\tarbol_vacio: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_vacio: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_recorrido_inorden(arbol_vac, (void**)array_ejemplo, 3) == VACIO){
    printf("\tarbol_recorrido_inorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_recorrido_inorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_recorrido_preorden(arbol_vac, (void**)array_ejemplo, 3) == VACIO){
    printf("\tarbol_recorrido_preorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_recorrido_preorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_recorrido_postorden(arbol_vac, (void**)array_ejemplo, 3) == VACIO){
    printf("\tarbol_recorrido_postorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_recorrido_postorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

	if(arbol_insertar(arbol_vac, &ejemplo) == ERROR){
		printf("\tarbol_insertar: "ROJO"FALLA :("NEUTRO"\n");
	}
	else{
		printf("\tarbol_insertar: "VERDE"PASA :)"NEUTRO"\n");
		arbol_borrar(arbol_vac, (void*)ejemplo);
		*pruebas_pasadas+=1;
	}
	*pruebas+=1;

	arbol_destruir(arbol_vac);
}

void abb_nulo(int* pruebas, int* pruebas_pasadas){
  abb_t* arbol_nulo = NULL;
  int ejemplo = 1;
  int array_ejemplo[3];

  if(arbol_insertar(arbol_nulo, &ejemplo) == ERROR){
    printf("\tarbol_insertar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_insertar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_borrar(arbol_nulo, &ejemplo) == ERROR){
    printf("\tarbol_borrar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_borrar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!arbol_buscar(arbol_nulo, &ejemplo)){
    printf("\tarbol_buscar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }else printf("\tarbol_buscar: "ROJO"FALLA :("NEUTRO"\n");
  *pruebas +=1;

  if(!arbol_raiz(arbol_nulo)){
    printf("\tarbol_raiz: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_raiz: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_vacio(arbol_nulo)){
    printf("\tarbol_vacio: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_vacio: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_recorrido_inorden(arbol_nulo, (void**)array_ejemplo, 3) == VACIO){
    printf("\tarbol_recorrido_inorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_recorrido_inorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_recorrido_postorden(arbol_nulo, (void**)array_ejemplo, 3) == VACIO){
    printf("\tarbol_recorrido_postorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_recorrido_postorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_recorrido_preorden(arbol_nulo, (void**)array_ejemplo, 3) == VACIO){
    printf("\tarbol_recorrido_preorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_recorrido_preorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;
}

void elemento_nulo(int* pruebas, int* pruebas_pasadas){
  abb_t* arbol_ejemplo = arbol_crear((abb_comparador)comparar_enteros, (abb_liberar_elemento)destruir_enteros);
  int array_ejemplo[3];

  if(arbol_insertar(arbol_ejemplo, NULL) == ERROR){
    printf("\tarbol_insertar: "ROJO"FALLA :("NEUTRO"\n");
  }
  else{
    printf("\tarbol_insertar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  *pruebas +=1;

  if(arbol_borrar(arbol_ejemplo, NULL) == ERROR){
    printf("\tarbol_borrar: "ROJO"FALLA :("NEUTRO"\n");
  }
  else{
    printf("\tarbol_borrar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  *pruebas +=1;

  arbol_insertar(arbol_ejemplo, NULL);

  if(!arbol_buscar(arbol_ejemplo, NULL)){
    printf("\tarbol_buscar: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_buscar: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(!arbol_raiz(arbol_ejemplo)){
    printf("\tarbol_raiz: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  else{
    printf("\tarbol_raiz: "ROJO"FALLA :("NEUTRO"\n");
  }
  *pruebas +=1;

  if(arbol_vacio(arbol_ejemplo)){
    printf("\tarbol_vacio: "ROJO"FALLA :("NEUTRO"\n");
  }
  else{
    printf("\tarbol_vacio: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  *pruebas +=1;

  if(arbol_recorrido_inorden(arbol_ejemplo, (void**)array_ejemplo, 3) == ERROR){
    printf("\tarbol_recorrido_inorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  else{
    printf("\tarbol_recorrido_inorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  *pruebas +=1;

  if(arbol_recorrido_preorden(arbol_ejemplo, (void**)array_ejemplo, 3) == ERROR){
    printf("\tarbol_recorrido_preorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  else{
    printf("\tarbol_recorrido_preorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  *pruebas +=1;

  if(arbol_recorrido_postorden(arbol_ejemplo, (void**)array_ejemplo, 3) == ERROR){
    printf("\tarbol_recorrido_postorden: "ROJO"FALLA :("NEUTRO"\n");
  }
  else{
    printf("\tarbol_recorrido_postorden: "VERDE"PASA :)"NEUTRO"\n");
    *pruebas_pasadas+=1;
  }
  *pruebas +=1;

  arbol_destruir(arbol_ejemplo);
}

void probar_funcionamiento(int* pruebas, int* pruebas_pasadas){
	printf(""CELESTE"\tCreo un arbol y lo lleno de Pokemon (structs)\n"NEUTRO"");
	  abb_t* arbol_poke = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)destruir_pokes);
		poke_t* p18 = crear_poke(18, 'a');
		poke_t* p30 = crear_poke(30, 'b');
		poke_t* p16 = crear_poke(16, 'c');
		poke_t* p17 = crear_poke(17, 'd');
		poke_t* p12 = crear_poke(12, 'e');
		poke_t* p14 = crear_poke(14, 'f');
		poke_t* p1 = crear_poke(1, 'g');
		poke_t* p26 = crear_poke(26, 'h');
		poke_t* p15 = crear_poke(15, 'i');

		arbol_insertar(arbol_poke, p18);
		arbol_insertar(arbol_poke, p30);
		arbol_insertar(arbol_poke, p16);
		arbol_insertar(arbol_poke, p17);
		arbol_insertar(arbol_poke, p12);
		arbol_insertar(arbol_poke, p14);
		arbol_insertar(arbol_poke, p1);
		arbol_insertar(arbol_poke, p26);

		int contador = 0;
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, contar_pokes, &contador);
		if(contador == 8){
			printf("\tLa cantidad de Pokemon es 8: "VERDE"PASA :)"NEUTRO"\n");
			*pruebas_pasadas += 1;
		}else{
			printf("\tLa cantidad de Pokemon es 8: "ROJO"FALLA :("NEUTRO"\n");
		}
		*pruebas += 1;

		if(((poke_t*)arbol_raiz(arbol_poke))->id == 18){
			printf("\tEl Pokemon raiz es el 18: "VERDE"PASA :)"NEUTRO"\n");
			*pruebas_pasadas += 1;
		}else{
			printf("\tEl Pokemon raiz es el 18: "ROJO"FALLA :("NEUTRO"\n");
		}
		*pruebas += 1;
		contador = 0;

		printf(""CELESTE"\tBorro una hoja (Pokemon 26)\n"NEUTRO"");
		arbol_borrar(arbol_poke, p26);
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, contar_pokes, &contador);
		if(contador == 7){
			printf("\tLa cantidad de Pokemon disminuyo en 1: "VERDE"PASA :)"NEUTRO"\n");
			*pruebas_pasadas += 1;
		}else{
			printf("\tLa cantidad de Pokemon disminuyo en 1: "ROJO"FALLA :("NEUTRO"\n");
		}
		*pruebas += 1;
		contador = 0;

		printf(""CELESTE"\tInserto el Pokemon 15 para que el 14 tenga un hijo\n"NEUTRO"");
		arbol_insertar(arbol_poke, p15);
		printf(""CELESTE"\tBorro un Pokemon con un solo pokehijo (Pokemon 14)\n"NEUTRO"");
		arbol_borrar(arbol_poke, p14);
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, contar_pokes, &contador);
		if(contador == 7){
			printf("\tLa cantidad de Pokemon disminuyo en 1: "VERDE"PASA :)"NEUTRO"\n");
			*pruebas_pasadas += 1;
		}else{
			printf("\tLa cantidad de Pokemon disminuyo en 1: "ROJO"FALLA :("NEUTRO"\n");
		}
		*pruebas += 1;
		contador = 0;

		printf(""CELESTE"\tBorro la raiz (Pokemon 18)\n"NEUTRO"");
		arbol_borrar(arbol_poke, p18);
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, contar_pokes, &contador);
		if(contador == 6){
			printf("\tLa cantidad de Pokemon disminuyo en 1: "VERDE"PASA :)"NEUTRO"\n");
			*pruebas_pasadas += 1;
		}else{
			printf("\tLa cantidad de Pokemon disminuyo en 1: "ROJO"FALLA :("NEUTRO"\n");
		}
		*pruebas += 1;

		if(((poke_t*)arbol_raiz(arbol_poke))->id == 17){
			printf("\tEl Pokemon raiz es el 17: "VERDE"PASA :)"NEUTRO"\n");
			*pruebas_pasadas += 1;
		}else{
			printf("\tEl Pokemon raiz es el 17: "ROJO"FALLA :("NEUTRO"\n");
		}
		*pruebas += 1;
		contador = 0;

		printf(""CELESTE"\tRecorro inorden e imprimo id (debe salir: 1 12 15 16 17 30)\n"NEUTRO"");
		void* array_ejemplo[6];
		arbol_recorrido_inorden(arbol_poke, array_ejemplo, 6);
		printf("\t");
		for(int i = 0; i < 6 ; i++){
			printf("%i ", ((poke_t*)array_ejemplo[i])->id);
		}
		printf("\n");

		printf(""CELESTE"\tRecorro preorden e imprimo id (debe salir: 17 16 12 1 15 30)\n"NEUTRO"");
		void* array_ejemplo2[6];
		arbol_recorrido_preorden(arbol_poke, array_ejemplo2, 6);
		printf("\t");
		for(int i = 0; i < 6 ; i++){
			printf("%i ", ((poke_t*)array_ejemplo2[i])->id);
		}
		printf("\n");

		printf(""CELESTE"\tRecorro postorden e imprimo id (debe salir: 1 15 12 16 30 17)\n"NEUTRO"");
		void* array_ejemplo3[6];
		arbol_recorrido_postorden(arbol_poke, array_ejemplo3, 6);
		printf("\t");
		for(int i = 0; i < 6 ; i++){
			printf("%i ", ((poke_t*)array_ejemplo3[i])->id);
		}
		printf("\n");

		printf(""CELESTE"\tUso el iterador interno para mostrar los nombres de los Pokemon en inorden)\n"NEUTRO"");
		printf(""ROJO"\tCUIDADO: Los nombres son muy descriptivos)\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_INORDEN, mostrar_nombres, NULL);
		printf("\n");

		printf(""CELESTE"\tUso el iterador interno para mostrar los nombres de los Pokemon en postorden)\n"NEUTRO"");
		printf(""ROJO"\tCUIDADO: Los nombres son muy descriptivos)\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, mostrar_nombres, NULL);
		printf("\n");


		printf(""CELESTE"\tUso el iterador interno para mostrar los nombres de los Pokemon en postorden)\n"NEUTRO"");
		printf(""ROJO"\tCUIDADO: Los nombres son muy descriptivos)\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_PREORDEN, mostrar_nombres, NULL);
		printf("\n");
		arbol_destruir(arbol_poke);
}

void iterador_interno(int* pruebas, int* pruebas_pasadas){
	int contador = 0;
	abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, contar_pokes, &contador);
	if(contador == VACIO){
		printf("\tRebota arbol nulo: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tRebota arbol nulo: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;

	contador = 0;
	abb_t* arbol = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)destruir_pokes);
	abb_con_cada_elemento(arbol, 4, contar_pokes, &contador);
	if(contador == VACIO){
		printf("\tRebota recorrido nulo: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tRebota recorrido nulo: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;
	arbol_destruir(arbol);

	contador = 0;
	abb_t* arbol_ejemplo = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)destruir_pokes);
	abb_con_cada_elemento(arbol_ejemplo, ABB_RECORRER_PREORDEN, NULL, &contador);
	if(contador == VACIO){
		printf("\tRebota funcion nula: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tRebota funcion nula: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;
	arbol_destruir(arbol_ejemplo);

	printf(""CELESTE"\tCreo y uso el mismo arbol que en probar funcionamiento\n"NEUTRO"");
	  abb_t* arbol_poke = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)destruir_pokes);
		poke_t* p18 = crear_poke(18, 'a');
		poke_t* p30 = crear_poke(30, 'b');
		poke_t* p16 = crear_poke(16, 'c');
		poke_t* p17 = crear_poke(17, 'd');
		poke_t* p12 = crear_poke(12, 'e');
		poke_t* p14 = crear_poke(14, 'f');
		poke_t* p1 = crear_poke(1, 'g');
		poke_t* p26 = crear_poke(26, 'h');

		arbol_insertar(arbol_poke, p18);
		arbol_insertar(arbol_poke, p30);
		arbol_insertar(arbol_poke, p16);
		arbol_insertar(arbol_poke, p17);
		arbol_insertar(arbol_poke, p12);
		arbol_insertar(arbol_poke, p14);
		arbol_insertar(arbol_poke, p1);
		arbol_insertar(arbol_poke, p26);

		printf(""CELESTE"\tMuesto inorden hasta pokemon 17\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_INORDEN, mostrar_hasta_17, NULL);
		printf("\n");
		printf(""CELESTE"\tMuesto preorden hasta pokemon 17\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_PREORDEN, mostrar_hasta_17, NULL);
		printf("\n");
		printf(""CELESTE"\tMuesto postorden hasta pokemon 17\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, mostrar_hasta_17, NULL);
		printf("\n");

		printf(""CELESTE"\tAhora hasta el 16\n"NEUTRO"");
		printf(""CELESTE"\tMuesto inorden hasta pokemon 16\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_INORDEN, mostrar_hasta_16, NULL);
		printf("\n");
		printf(""CELESTE"\tMuesto preorden hasta pokemon 16\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_PREORDEN, mostrar_hasta_16, NULL);
		printf("\n");
		printf(""CELESTE"\tMuesto postorden hasta pokemon 16\n"NEUTRO"");
		printf("\t");
		abb_con_cada_elemento(arbol_poke, ABB_RECORRER_POSTORDEN, mostrar_hasta_16, NULL);
		printf("\n");
		arbol_destruir(arbol_poke);
}

void casos_borde(int* pruebas, int* pruebas_pasadas){
	abb_t* arbol = arbol_crear((abb_comparador)NULL, (abb_liberar_elemento)destruir_pokes);
	if(!arbol){
		printf("\tCrear arbol con comparador nulo: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tCrear arbol con comparador nulo: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;

	abb_t* arbol_des = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)NULL);
	if(arbol_des){
		printf("\tCrear arbol con comparador nulo: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tCrear arbol con comparador nulo: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;
	arbol_destruir(arbol_des);

	abb_t* arbol_igual = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)destruir_pokes);
	poke_t* p1 = crear_poke(16, 'c');
	poke_t* p2 = crear_poke(16, 'c');
	poke_t* p3 = crear_poke(16, 'c');
	poke_t* p4 = crear_poke(18, 'c');
	int primero = arbol_insertar(arbol_igual, p1);
	int segundo = arbol_insertar(arbol_igual, p2);
	int tercero = arbol_insertar(arbol_igual, p3);
	if(!primero && !segundo && !tercero){
		printf("\tInserto 3 veces el mismo Pokemon: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tInserto 3 veces el mismo Pokemon: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;

	if(arbol_borrar(arbol_igual, p4) == ERROR){
		printf("\tIntento borrar un elemento que no esta: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tIntento borrar un elemento que no esta: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;

	if(arbol_buscar(arbol_igual, p4)){
		printf("\tIntento buscar un elemento que no esta: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tIntento buscar un elemento que no esta: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;
	destruir_pokes(p4);
	arbol_destruir(arbol_igual);

	printf(""CELESTE"\tCreo y uso el mismo arbol que en probar funcionamiento\n"NEUTRO"");
	int array_ejemplo1[10];
	int array_ejemplo2[10];
	int array_ejemplo3[10];
	int array_vacio[1];

	abb_t* arbol_poke = arbol_crear((abb_comparador)comparar_pokes, (abb_liberar_elemento)destruir_pokes);
	poke_t* p18 = crear_poke(18, 'a');
	poke_t* p30 = crear_poke(30, 'b');
	poke_t* p16 = crear_poke(16, 'c');
	poke_t* p17 = crear_poke(17, 'd');
	poke_t* p12 = crear_poke(12, 'e');
	poke_t* p14 = crear_poke(14, 'f');
	poke_t* p5 = crear_poke(5, 'g');
	poke_t* p26 = crear_poke(26, 'h');

	arbol_insertar(arbol_poke, p18);
	arbol_insertar(arbol_poke, p30);
	arbol_insertar(arbol_poke, p16);
	arbol_insertar(arbol_poke, p17);
	arbol_insertar(arbol_poke, p12);
	arbol_insertar(arbol_poke, p14);
	arbol_insertar(arbol_poke, p5);
	arbol_insertar(arbol_poke, p26);

	printf(""CELESTE"\tLleno un array en inorden de tamanio menor a la cantidad de Pokemon\n"NEUTRO"");
	arbol_recorrido_inorden(arbol_poke, (void**)array_ejemplo1, 3);
	printf("\t");
	for(int i = 0; i < 3 ; i++){
		printf("%i ", ((poke_t*)array_ejemplo1[i])->id);
	}
	printf("\n");

	printf(""CELESTE"\tLleno un array en postorden de tamanio menor a la cantidad de Pokemon\n"NEUTRO"");
	arbol_recorrido_postorden(arbol_poke, (void**)array_ejemplo2, 3);
	printf("\t");
	for(int i = 0; i < 3 ; i++){
		printf("%i ", ((poke_t*)array_ejemplo2[i])->id);
	}
	printf("\n");

	printf(""CELESTE"\tLleno un array en preorden de tamanio menor a la cantidad de Pokemon\n"NEUTRO"");
	arbol_recorrido_preorden(arbol_poke, (void**)array_ejemplo3, 3);
	printf("\t");
	for(int i = 0; i < 3 ; i++){
		printf("%i ", ((poke_t*)array_ejemplo3[i])->id);
	}
	printf("\n");

	printf(""CELESTE"\tAhora uno de tamanio 0\n"NEUTRO"");

	if(!arbol_recorrido_inorden(arbol_poke, (void**)array_vacio, 0)){
		printf("\tInorden: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tInorden: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;

	if(!arbol_recorrido_preorden(arbol_poke, (void**)array_vacio, 0)){
		printf("\tPreorden: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tPreorden: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;

	if(!arbol_recorrido_postorden(arbol_poke, (void**)array_vacio, 0)){
		printf("\tPostorden: "VERDE"PASA :)"NEUTRO"\n");
		*pruebas_pasadas+=1;
	}
	else{
		printf("\tPostorden: "ROJO"FALLA :("NEUTRO"\n");
	}
	*pruebas +=1;


	arbol_destruir(arbol_poke);




}

int main(){
  int pruebas = 0, pruebas_pasadas = 0;

  printf("TDA ABB:\n");
  printf("A continuación, se probará el funcinamiento del TDA en general:\n");
  probar_funcionamiento(&pruebas, &pruebas_pasadas);
  printf("Pruebas con abb nulo:\n");
  abb_nulo(&pruebas, &pruebas_pasadas);
  printf("Pruebas con abb vacio:\n");
  abb_vacio(&pruebas, &pruebas_pasadas);
  printf("Pruebas con elementos nulos:\n");
  elemento_nulo(&pruebas, &pruebas_pasadas);
  printf("Pruebas con iterador interno:\n");
  iterador_interno(&pruebas, &pruebas_pasadas);
  printf("Pruebas con casos borde:\n");
  casos_borde(&pruebas, &pruebas_pasadas);

	printf("PasasteS "VERDE"%d"NEUTRO"/"VERDE"%d"NEUTRO" pruebas\n", pruebas_pasadas, pruebas);



  return 0;
}
