#ifndef _BATALLA_H_
#define _BATALLA_H_

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


typedef struct personaje{
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;		
} personaje_t;
	
typedef struct jugador{
	char bando;
	int intensidad;
	int energia;
} jugador_t;

typedef struct juego{
	char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL];
	personaje_t rohan[MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	personaje_t isengard[MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard; 
	jugador_t jugador_1;
	jugador_t jugador_2;
	char modo_de_juego;		
} juego_t;

void inicializar_juego(juego_t* juego);
bool hay_ganador(juego_t juego);
void pedir_datos_personaje(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], int plus_isengard, int plus_rohan, jugador_t* jugador, personaje_t* personaje);
void posicionar_personaje(juego_t* juego, personaje_t personaje);
void inicializar_cpu(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], int plus_isengard, int plus_rohan, jugador_t* jugador, personaje_t* personaje);
void jugar(juego_t* juego, char bando, int posicion_personaje);

#endif /*_BATALLA_H_ */