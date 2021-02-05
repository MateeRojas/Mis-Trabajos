#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "batalla.h"
#include "perfil.h"

#define MAX_TERRENO_FIL 13
#define MAX_TERRENO_COL 12
#define MAX_PERSONAJES 100
#define NULO 0
#define UN_JUGADOR 'U'
#define DOS_JUGADORES 'D'
#define PARAMETRO_INTENSIDAD 10
#define ENERGIA_INICIAL 5
#define CANTIDAD_INICIAL 3
#define BANDO_OFENSIVO 'O'
#define BANDO_DEFENSIVO 'D'
#define URUK 'U'
#define ORCO 'O'
#define HOMBRE 'H'
#define ELFO 'E'
#define NEGATIVO 'N'
#define AFIRMATIVO 'S'
#define VACIO ' '
#define INDETERMINADO 'I'
#define VIDA_URUK_ELFO 200
#define ATAQUE_URUK_ELFO 10
#define ENERGIA_URUK_ELFO 8
#define VIDA_ORCO_HOMBRE 100
#define ATAQUE_ORCO_HOMBRE 50
#define ENERGIA_ORCO_HOMBRE 3
#define FILA_INICIAL_HOMBRE 11
#define FILA_INICIAL_ORCO 1
#define HACER_POSITIVO -1
#define DISTANCIA_URUK_ELFO 3
#define RANGO_MAX_ORCO_HOMBRE 1
#define RANGO_MIN_ORCO_HOMBRE -1
#define MOVIMIENTO 1
#define FIN_SUPERIOR 0
#define LLEGADA 1


/*
PRE: recibe una matriz previamente inicializada
POST: imprime elemento a elemento la matriz
*/
void mostrar(juego_t* juego){
	for(int i = 0; i <  MAX_TERRENO_FIL; i++){
			for(int j = 0; j < MAX_TERRENO_COL; j++){
				printf("%c", (*juego).terreno[i][j]);
			}
			printf("\n");
	}
}

/*
PRE: recibe todos los datos para crear un personaje (codigo, plus y posicion)
POST: crea un nuevo personaje con los datos dados
*/
personaje_t generar_personaje(char codigo, int plus, int fila, int columna){
    personaje_t personaje;
    personaje.codigo = codigo;
    if (codigo == ELFO || codigo == URUK){
        personaje.vida = VIDA_URUK_ELFO - plus;
        personaje.ataque = ATAQUE_URUK_ELFO + plus;
    }
    else{
        personaje.vida = VIDA_ORCO_HOMBRE - plus;
        personaje.ataque = ATAQUE_ORCO_HOMBRE + plus;
    }
    personaje.fila = fila;
    personaje.columna = columna;
    return personaje;
}

/*
PRE: recibe los parametros para crear un numero aleatorio
POST: devuelve un numero aleatorio acorde a lo recibido
*/
int numero_aleatorio(int minimo, int amplitud){
	srand ((unsigned)time(NULL));
	int numero = rand() %amplitud + minimo;
	return numero;
}

/*
PRE: recibe el terreno, el vector de personajes de Rohan, su tope y el plus
POST: consigue posiciones aleatorias y posiciona tres elfos en ellas, a tra vez de otra funcion que se encarga de eso
*/	
void posicionar_elfos(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t rohan[MAX_PERSONAJES], int* cantidad_rohan, int plus_rohan){
    int columna, fila;
    bool esta_vacio = false;
    for (int i = *cantidad_rohan; i < CANTIDAD_INICIAL; i++){
    	esta_vacio = false;
        while(!esta_vacio){
            columna = numero_aleatorio(1, MAX_TERRENO_COL);
		    fila = numero_aleatorio((((MAX_TERRENO_FIL)/2)+1), MAX_TERRENO_FIL);
            if (terreno[fila][columna] == VACIO){
                esta_vacio = true;
                terreno[fila][columna] = ELFO;
                rohan[i] = generar_personaje(ELFO, plus_rohan, fila, columna);
                (*cantidad_rohan)++;
            }
        }
    }
}

/*
PRE:recibe el terreno, el vector de personajes de Isengard, su tope y el plus
POST:consigue posiciones aleatorias y posiciona tres urukhais en ellas, a tra vez de otra funcion que se encarga de eso
*/
void posicionar_urukhais(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t isengard[MAX_PERSONAJES], int* cantidad_isengard, int plus_isengard){
    int columna, fila;
    bool esta_vacio = false;
    for (int i = *cantidad_isengard; i < CANTIDAD_INICIAL; i++){
    	esta_vacio = false;
        while(!esta_vacio){
            columna = numero_aleatorio(1, MAX_TERRENO_COL);
		    fila = numero_aleatorio(1, (MAX_TERRENO_FIL/2));
            if (terreno[fila][columna] == VACIO){
                esta_vacio = true;
                terreno[fila][columna] = URUK;
                isengard[i] = generar_personaje(URUK, plus_isengard, fila, columna);
                (*cantidad_isengard)++;
            }
        }
    }
}

/*
PRE: recibe un juego entero
POST: asigna todas las variables a valores iniciales
*/
void vaciar_juego(juego_t* juego){
	(*juego).cantidad_rohan = NULO;
	(*juego).llegadas_rohan = NULO; 
	(*juego).cantidad_isengard =NULO;
	(*juego).llegadas_isengard = NULO;	
	(*juego).jugador_1.energia = ENERGIA_INICIAL;
	(*juego).jugador_2.energia = ENERGIA_INICIAL;	
	(*juego).modo_de_juego = INDETERMINADO;
}

/*
PRE: recibe un juego y los datos obtenidos del tp1
POST: asigna bando e intencidad a los jugadores del juego
*/
void asignar_datos_jugadores(juego_t* juego, char bando, int intensidad){
	(*juego).jugador_1.bando = bando;
	(*juego).jugador_1.intensidad = intensidad;
	if((*juego).jugador_1.bando == BANDO_DEFENSIVO){
	(*juego).jugador_2.bando = BANDO_OFENSIVO;
	}
	else{
		(*juego).jugador_2.bando = BANDO_DEFENSIVO;
	}
	(*juego).jugador_2.intensidad = PARAMETRO_INTENSIDAD - (*juego).jugador_1.intensidad;
}

/*
PRE: recibe un juego por referencia
POST: determina los pluses de cada bando utilizando intensidad obtenida y la funcion numero aleatorio 
*/
void determinar_plus(juego_t* juego){
	int aleatorio_1, aleatorio_2;
	aleatorio_1 = numero_aleatorio(NULO, 6);
	aleatorio_2 = numero_aleatorio(NULO, 6);
	if((*juego).jugador_1.bando == BANDO_OFENSIVO){
		(*juego).plus_rohan = ((*juego).jugador_1.intensidad) * aleatorio_1;
		(*juego).plus_isengard = ((*juego).jugador_2.intensidad) * aleatorio_2;
	}
	else{
		(*juego).plus_isengard = ((*juego).jugador_1.intensidad) * aleatorio_1;
		(*juego).plus_rohan = ((*juego).jugador_2.intensidad) * aleatorio_2;
	}
}

/*
PRE: recibe un terreno por referencia
POST: salvo por los bordes, lo inicializa en valores nulos, osea vacio
*/
void vaciar_terreno(juego_t* juego){
	for(int i = 0; i < MAX_TERRENO_FIL; i++){
		for(int j = 0; j < MAX_TERRENO_COL; j++){
			if(i == NULO || i == ((MAX_TERRENO_FIL-1)/2) || i == (MAX_TERRENO_FIL - 1)){
				(*juego).terreno[i][j] = '-';
			}
			else if((j == NULO || j == (MAX_TERRENO_COL - 1)) && (i != NULO && i!= ((MAX_TERRENO_FIL-1)/2)) && (i != (MAX_TERRENO_FIL - 1))){
				(*juego).terreno[i][j] = '|';
			}
			else{
				(*juego).terreno[i][j] = VACIO;
			}
		}
	}		
}

/*
PRE: recibe un juego por referencia
POST: recorre el vector de personajes de cada bando y los posiciona en el terreno
*/	
void posicionar_iniciales(juego_t* juego){
	for(int i = 0 ; i < 3 ; i++){
		(*juego).terreno[(*juego).rohan[i].fila][(*juego).rohan[i].columna] = ELFO;	
	}
	for(int j = 0 ; j < 3 ; j++){
		(*juego).terreno[(*juego).isengard[j].fila][(*juego).isengard[j].columna] = URUK;	
    }
}

/*
PRE: recibe un char por referencia
POST: pide al usuario un carácter válido y se lo asigna al juego, en su apartado modo de juego
*/
void determinar_modo_juego(char* modo_de_juego){
    printf("\nPrimero elija el modo de juego, si quiere PvP ingrese 'D', si quiere jugar contra la maquina, ingrese 'U'\n");
    scanf("%c", modo_de_juego);
    while (*modo_de_juego != UN_JUGADOR && *modo_de_juego != DOS_JUGADORES){
        printf("Carácter erróneo, ingrese uno válido \n");
        scanf(" %c", modo_de_juego);
    }
}

/*
PRE: recibe la energia del bando y el personaje a posicionar
POST: chequea si hayenergia suficiente, si no la hay, informa al usuario
*/
void verificar_energia(int* energia, char* tipo_personaje){
    char respuesta = NEGATIVO;
    if ((*energia) < ENERGIA_ORCO_HOMBRE){
        printf("Energia insuficiente");
        (*tipo_personaje) = NEGATIVO;
    }
    else if((*energia) < ENERGIA_URUK_ELFO && (*tipo_personaje) == URUK && (*energia) >= ENERGIA_ORCO_HOMBRE){
        printf("\nEnergia insuficiente para el personaje deseado, ¿posicionar orco? Ingrese 'S' para sí y 'N' para no.\n");
        scanf(" %c", &respuesta);
        while (respuesta != AFIRMATIVO && respuesta != NEGATIVO){
            printf("Carácter incorrecto, ingrese uno válido");
            scanf(" %c", &respuesta);
        }
        if (respuesta == NEGATIVO){
            (*tipo_personaje) = INDETERMINADO;
        }
        else{
            (*tipo_personaje) = ORCO;
            (*energia) -= ENERGIA_ORCO_HOMBRE;
        }
    }
    else if((*tipo_personaje) == URUK){
        (*energia) -= ENERGIA_URUK_ELFO;
    }
    else if ((*tipo_personaje) == ORCO){
        (*energia) -= ENERGIA_ORCO_HOMBRE;
    }
    else if ((*energia) < ENERGIA_URUK_ELFO && (*tipo_personaje) == ELFO && (*energia) >= ENERGIA_ORCO_HOMBRE){
        printf("\nEnergia insuficiente para el personaje deseado, ¿posicionar hombre? Ingrese 'S' para sí y 'N' para no.\n" );
        scanf(" %c", &respuesta);
        while (respuesta != AFIRMATIVO && respuesta != NEGATIVO){
            printf("Carácter incorrecto, ingrese uno válido");
            scanf(" %c", &respuesta);
        }
        if (respuesta == NEGATIVO){
            (*tipo_personaje) = INDETERMINADO;
        }
        else{
            (*tipo_personaje) = HOMBRE;
            (*energia) -= ENERGIA_ORCO_HOMBRE;
        }
    }
    else if((*tipo_personaje) == ELFO){
        (*energia) -= ENERGIA_URUK_ELFO;
    }
    else if ((*tipo_personaje) == HOMBRE){
        (*energia) -= ENERGIA_ORCO_HOMBRE;
    }
}

/*
PRE: recibe un jugador y un codigo por referencia
POST: pregunta si deasea posicionar un personaje al usuario y luego llama a una funcion para ver si tiene energia suficiente
*/
void pedir_tipo_personaje(jugador_t* jugador, char* tipo){
    if((*jugador).bando == BANDO_DEFENSIVO){
        printf("\nSi quiere posisionar un personaje, ingrese 'H' para hombre, 'E' para Elfo. Si no quiere posicionar nada, ingrese 'I'\n");
        scanf(" %c", tipo);
        while((*tipo) != ELFO && (*tipo) != HOMBRE && (*tipo) != INDETERMINADO){
            printf("\nCaracter no válido, ingrese uno de los dados\n");
            scanf(" %c", tipo);
        }
        if ((*tipo) != INDETERMINADO){
            verificar_energia(&((*jugador).energia), tipo);
        }
    }
    else{
        printf("\nSi quiere posisionar un personaje, ingrese 'O' para orco, 'U' para Urukhai. Si no quiere posicionar nada, ingrese 'I' \n");
        scanf(" %c", tipo);
        while((*tipo) != ORCO && (*tipo) != URUK && (*tipo) != INDETERMINADO){
            printf("\nCaracter no válido, ingrese uno de los dados\n");
            scanf(" %c", tipo);
        }
        if ((*tipo) != INDETERMINADO){
            verificar_energia(&((*jugador).energia), tipo);
        }
    }
}

/*
PRE: recibe el terreno, el tipo del personaje y su posicion
POST: pregunta la usuario en donde desea posicionar al personaje, de no poderse posicionar, informa al usuario
*/
void pedir_posicion(char tipo_personaje, int* columna, int* fila, char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL]){
    printf("\nIngrese la colmuna donde desea posicionar su personaje\n");
    scanf(" %i", columna);
    while((*columna) < 1  || (*columna) >= MAX_TERRENO_COL){
    printf("\nValor fuera del rango, ingrese uno válido\n");
    scanf("%i", columna);
    }
    if(tipo_personaje == URUK){
        do{
            printf("\nIngrese la fila donde desea posicionar su personaje \n");
            scanf(" %i", fila);
            while((*fila) < 1 || (*fila) > (MAX_TERRENO_FIL/2)){
                printf("\nValor fuera del rango, ingrese uno válido\n");
                scanf(" %i", fila);
            }
            if (terreno[*fila][*columna] != VACIO){
                printf("\nEspacio no disponible, ingrese otro\n");
            }
        } while(terreno[*fila][*columna] != VACIO);
    }        
    else if(tipo_personaje == ELFO){    
            do{
                printf("\nIngrese la fila donde desea posicionar su personaje\n");
                scanf(" %i", fila);
                while((*fila) > MAX_TERRENO_FIL || (*fila) < (MAX_TERRENO_FIL/2)+2){
                    printf("\nValor fuera del rango, ingrese uno válido\n");
                    scanf(" %i", fila);
                }
                if (terreno[*fila][*columna] != VACIO){
                    printf("\nEspacio no disponible, ingrese otro\n");
                }
            } while(terreno[*fila][*columna] != VACIO);
    }
    else if(tipo_personaje == HOMBRE){
            do{
                (*fila) = FILA_INICIAL_HOMBRE;
                if (terreno[(*fila)][(*columna)] != VACIO){
                    printf("\nEspacio no disponible, ingrese otro\n");
                }
            } while(terreno[*fila][*columna] != VACIO);
    }
    else if(tipo_personaje == ORCO){
            do{
                (*fila) = FILA_INICIAL_ORCO;
                if (terreno[*fila][*columna] != VACIO){
                    printf("\nEspacio no disponible, ingrese otro\n");
                }
            } while(terreno[*fila][*columna] != VACIO);
    }        
}

/*
PRE: recibe el terreno, los pluses de cada bando, un perosonaje y un jugador
POST: llama a diferentes funciones para recaudar todos los datos del nuevo personaje
*/
void preguntar_datos_personaje(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], int plus_isengard, int plus_rohan, personaje_t* personaje, jugador_t* jugador){
    char tipo_personaje;
    int fila, columna;
    pedir_tipo_personaje(jugador, &tipo_personaje);
    if(tipo_personaje != INDETERMINADO){
        pedir_posicion(tipo_personaje, &columna, &fila, terreno);
        if ((*jugador).bando == BANDO_OFENSIVO){
            (*personaje) = generar_personaje(tipo_personaje, plus_isengard, fila, columna);
        }
        else{
            (*personaje) = generar_personaje(tipo_personaje, plus_rohan, fila, columna);
        }
    }
    else{
        (*personaje).codigo = INDETERMINADO;
    }
}

/*
PRE: recibe el terreno, los pluses de cada bando, un perosonaje y un jugador
POST: muestra de quien es el turno y llama funciones que determinen que quiere hacer el usuario
*/
void pedir_datos_personaje(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], int plus_isengard, int plus_rohan, jugador_t* jugador, personaje_t* personaje){
    if((*jugador).bando == BANDO_DEFENSIVO){
        printf("\nEs el turno de las tropas de Rohan\n");
    }
    else{
        printf("\nEs el turno de las tropas de Isengard\n");
    }
    preguntar_datos_personaje(terreno, plus_isengard, plus_rohan, personaje, jugador);
}

/*
PRE: recibe el juego por referencia
POST: mediante muchas funciones, inicializara todos los valores del juego
*/
void inicializar_juego(juego_t* juego){
	char bando;
	int intensidad;
	printf("Bienvenidx, determinaremos tu bando\n");
	perfil(&bando, &intensidad);
	vaciar_juego(juego);
	asignar_datos_jugadores(juego, bando, intensidad);
	determinar_plus(juego);
	vaciar_terreno(juego);
	posicionar_elfos((*juego).terreno, (*juego).rohan, &((*juego).cantidad_rohan), (*juego).plus_rohan);
	posicionar_urukhais((*juego).terreno, (*juego).isengard, &((*juego).cantidad_isengard), (*juego).plus_isengard);		
	mostrar(juego);
	determinar_modo_juego(&(*juego).modo_de_juego);
}

/*
PRE: recibe el juego, y el personaje a posicionar
POST: modifica el juego, posicionando el personaje y luego lo muestra en pantalla
*/
void posicionar_personaje(juego_t* juego, personaje_t personaje){
    if(personaje.codigo != INDETERMINADO){
        (*juego).terreno[personaje.fila][personaje.columna] = personaje.codigo;
        if(personaje.codigo == ELFO || personaje.codigo == HOMBRE){
            (*juego).rohan[((*juego).cantidad_rohan)] = personaje;
            (*juego).cantidad_rohan++;
        }
        else{
        	(*juego).isengard[((*juego).cantidad_isengard)] = personaje;
            (*juego).cantidad_isengard++;
        }
    }
    mostrar(juego);
}

/*
PRE: recibe el terreno, los pluses de los bandos, un jugador y un personaje
POST: mediante distintas funciones, establece los datos de la cpu en valores iniciales
*/
void inicializar_cpu(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], int plus_isengard, int plus_rohan, jugador_t* jugador, personaje_t* personaje){
    int columna, fila;
    char tipo;

    if ((*jugador).energia >= ENERGIA_ORCO_HOMBRE){
        if((*jugador).bando == BANDO_OFENSIVO){
            do{
                columna = numero_aleatorio(1, MAX_TERRENO_COL);
                fila = FILA_INICIAL_ORCO;
            } while(terreno[fila][columna] != VACIO);
            tipo = ORCO;
            (*personaje) = generar_personaje(tipo, plus_isengard, fila, columna);
        }
        else{
            do{
                columna = numero_aleatorio(1, MAX_TERRENO_COL);
                fila = FILA_INICIAL_HOMBRE;
            } while(terreno[columna][fila] != VACIO);
            tipo = HOMBRE;
            (*personaje) = generar_personaje(tipo, plus_rohan, fila, columna);    
        }
        (*jugador).energia -= ENERGIA_ORCO_HOMBRE;
    }
    else{
        printf("\nLa cpu está sin energia, ¡aprovechá!\n\n");
        (*personaje).codigo = INDETERMINADO;
    }
}

/*
PRE: recibe un terreno, un personaje, el vector de personajes y su tope
POST: elimina el dicho personaje del terreno
*/
void matar_personaje(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t personajes[MAX_PERSONAJES], int* cantidad, int i){
    terreno[personajes[i].fila][personajes[i].columna] = VACIO;
    personajes[i] = personajes[(*cantidad) - 1];
    (*cantidad)--;
}

/*
PRE: recibe un entero negativo
POST: lo transforma a positivo
*/
int modulo(int numero){
    if (numero < 0){
        numero *= (HACER_POSITIVO);
    }
    return numero;
}

/*
PRE: recibe las cuatro posibles posiciones de un elfo/urukhai
POST: devuelve true si la distancia es menor igual a la distancia alcanzada por los uruk/elfos, o false si no 
*/
bool distancia_manhattan_3(int pos_y, int pos_x, int pos_yy, int pos_xx){
    int distancia = modulo(pos_y - pos_yy) + modulo(pos_x - pos_xx);
    return (distancia <= DISTANCIA_URUK_ELFO);
}

/*
PRE: recibe un terreno, el personaje a mover, la posicion de este, el contador de llegadas, el vector de personajes y su tope
POST: chequea como se debe mover, mediantes funciones lo mueve y si llega al "final" de su recorrido, suma un punto a llegadas y elimina el perosnaje
*/
void mover_orco(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t isengard[MAX_PERSONAJES], int* llegadas_isengard, int* cantidad_isengard, int posicion){
    if(isengard[posicion].fila == ((MAX_TERRENO_FIL/2)-1)){
        terreno[isengard[posicion].fila][isengard[posicion].columna] = VACIO;
        isengard[posicion].fila += (2*MOVIMIENTO);
        while (terreno[isengard[posicion].fila][isengard[posicion].columna] != VACIO){
        isengard[posicion].fila += MOVIMIENTO;
        }
        terreno[isengard[posicion].fila][isengard[posicion].columna] = ORCO;
    }
    else{
        terreno[isengard[posicion].fila][isengard[posicion].columna] = VACIO;
        isengard[posicion].fila += MOVIMIENTO;
        while (terreno[isengard[posicion].fila][isengard[posicion].columna] != VACIO){
        isengard[posicion].fila += MOVIMIENTO;
        }
        if (isengard[posicion].fila >= (MAX_TERRENO_FIL)-1){
            (*llegadas_isengard) += LLEGADA;
            matar_personaje(terreno, isengard, cantidad_isengard, posicion);
            terreno[isengard[posicion].fila][isengard[posicion].columna] = '-';
        }
        else{
            terreno[isengard[posicion].fila][isengard[posicion].columna] = ORCO;
        }
    }
}

/*
PRE:recibe un terreno, el personaje a mover, la posicion de este, el contador de llegadas, el vector de personajes y su tope
POST: chequea como se debe mover, mediantes funciones lo mueve y si llega al "final" de su recorrido, suma un punto a llegadas y elimina el perosnaje
*/
void mover_hombre(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t rohan[MAX_PERSONAJES], int* llegadas_rohan, int* cantidad_rohan, int posicion){
    if(rohan[posicion].fila == ((MAX_TERRENO_FIL/2)+1)){
        terreno[rohan[posicion].fila][rohan[posicion].columna] = VACIO;
        rohan[posicion].fila -= (2*MOVIMIENTO);
        while (terreno[rohan[posicion].fila][rohan[posicion].columna] != VACIO){
        rohan[posicion].fila -= MOVIMIENTO;
        }
        terreno[rohan[posicion].fila][rohan[posicion].columna] = HOMBRE;
    }
    else{
        terreno[rohan[posicion].fila][rohan[posicion].columna] = VACIO;
        rohan[posicion].fila -= MOVIMIENTO;
        while (terreno[rohan[posicion].fila][rohan[posicion].columna] != VACIO){
        rohan[posicion].fila -= MOVIMIENTO;
        }
    }    
    if (rohan[posicion].fila <= FIN_SUPERIOR){
            (*llegadas_rohan) += LLEGADA;
            matar_personaje(terreno, rohan, cantidad_rohan, posicion);
            terreno[rohan[posicion].fila][rohan[posicion].columna] = '-';
        }
    else{
        terreno[rohan[posicion].fila][rohan[posicion].columna] = HOMBRE;
    }        
}

/*
PRE: recibe el terreno, un personaje y su posicion
POST: a tra vez de funciones, atacapo a un personaje dentro de su rango y si lo mata lo elimina del terreno
*/
bool atacar_orco(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t isengard[MAX_PERSONAJES], personaje_t rohan[MAX_PERSONAJES], int* cantidad_rohan, int posicion){
    int i = 0;
    bool ataque = false;
    while(i < (*cantidad_rohan) && !ataque){
        for (int j = RANGO_MIN_ORCO_HOMBRE; j <= RANGO_MAX_ORCO_HOMBRE; j++){
            for (int k = RANGO_MIN_ORCO_HOMBRE; k <= RANGO_MAX_ORCO_HOMBRE; k++){
                if(isengard[posicion].fila + j == rohan[i].fila && isengard[posicion].columna + k == rohan[i].columna){
                    rohan[i].vida -= isengard[posicion].ataque;
                    ataque = true;
                }
            }
        }
        if (rohan[i].vida <= NULO){
            matar_personaje(terreno, rohan, cantidad_rohan, i);
        }
        i++;
    }
    return ataque;
}

/*
PRE:recibe el terreno, un personaje y su posicion
POST: a tra vez de funciones, ataca a un personaje dentro de su rango y si lo mata lo elimina del terreno
*/
bool atacar_hombre(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t isengard[MAX_PERSONAJES], personaje_t rohan[MAX_PERSONAJES], int* cantidad_isengard, int posicion){
    int i = 0;
    bool ataque = false;
    while(i < (*cantidad_isengard) && !ataque){
        for (int j = RANGO_MIN_ORCO_HOMBRE; j <= RANGO_MAX_ORCO_HOMBRE; j++){
            for (int k = RANGO_MIN_ORCO_HOMBRE; k <= RANGO_MAX_ORCO_HOMBRE; k++){
                if((rohan[posicion].fila + j) == isengard[i].fila && (rohan[posicion].columna + k) == isengard[i].columna){
                    isengard[i].vida -= rohan[posicion].ataque;
                    ataque = true;
                }
            }
        }
        if (isengard[i].vida <= NULO){
            matar_personaje(terreno, isengard, cantidad_isengard, i);
        }
        i++;
    }
    return ataque;
}

/*
PRE:recibe el terreno, un personaje y su posicion
POST: a tra vez de funciones, ataca a un personaje dentro de su rango y si lo mata lo elimina del terreno
*/
void atacar_urukhai(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t rohan[MAX_PERSONAJES], personaje_t isengard[MAX_PERSONAJES], int* cantidad_rohan, int posicion){
    for(int i = 0; i < (*cantidad_rohan); i++){
        if(distancia_manhattan_3(isengard[posicion].fila, isengard[posicion].columna, rohan[i].fila, rohan[i].columna)){
            rohan[i].vida -= isengard[posicion].ataque;
            if (rohan[i].vida <= NULO){
                matar_personaje(terreno, rohan, cantidad_rohan, i);
            }
        }
    }
}

/*
PRE:recibe el terreno, un personaje y su posicion
POST: a tra vez de funciones, ataca a un personaje dentro de su rango y si lo mata lo elimina del terreno
*/
void atacar_elfo(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t rohan[MAX_PERSONAJES], personaje_t isengard[MAX_PERSONAJES], int* cantidad_isengard, int posicion){
    for(int i = 0; i < (*cantidad_isengard); i++){
        if(distancia_manhattan_3(rohan[posicion].fila, rohan[posicion].columna, isengard[i].fila, isengard[i].columna)){
            isengard[i].vida -= rohan[posicion].ataque;
            if (isengard[i].vida <= NULO){
                matar_personaje(terreno, isengard, cantidad_isengard, i);
            }
        }
    }
}

/*
PRE: recibe un juego, el bando y la posicion del personaje
POST: llama a distintas funciones que determinaran que hace el personaje
*/
void jugar(juego_t* juego, char bando, int posicion_personaje){
    if (bando == BANDO_OFENSIVO){
        if ((*juego).isengard[posicion_personaje].codigo == URUK){
            atacar_urukhai((*juego).terreno, (*juego).rohan, (*juego).isengard, &((*juego).cantidad_rohan), posicion_personaje);
        }
        else if ((*juego).isengard[posicion_personaje].codigo == ORCO){
            if(!atacar_orco((*juego).terreno, (*juego).isengard, (*juego).rohan, &((*juego).cantidad_rohan), posicion_personaje)){
                mover_orco((*juego).terreno, (*juego).isengard, &((*juego).llegadas_isengard), &((*juego).cantidad_isengard), posicion_personaje);
            }
        }
    }
    if (bando == BANDO_DEFENSIVO){
        if ((*juego).rohan[posicion_personaje].codigo == ELFO){
            atacar_elfo((*juego).terreno, (*juego).rohan, (*juego).isengard, &((*juego).cantidad_isengard), posicion_personaje);
        }
        else if ((*juego).rohan[posicion_personaje].codigo == HOMBRE){
            if(!atacar_hombre((*juego).terreno, (*juego).isengard, (*juego).rohan, &((*juego).cantidad_isengard), posicion_personaje)){
                mover_hombre((*juego).terreno, (*juego).rohan, &((*juego).llegadas_rohan), &((*juego).cantidad_rohan), posicion_personaje);
            }
        }
    }
}
