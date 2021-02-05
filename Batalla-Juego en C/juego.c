#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "batalla.h"

bool hay_ganador(juego_t juego){
    bool gana_alguien = false;
    if(juego.llegadas_rohan >= 5){
        gana_alguien = true;
        printf("\nLa batalla ha llegado a su fin, Rohan y su ejercito han triunfado gracias a ti, noble guerrerx. ¡Felicitaciones! A partir de hoy, reina la paz.\n");
    }
    else if (juego.llegadas_isengard >= 5){
        gana_alguien = true;
        printf("\nLa batalla ha llegado a su fin, Isengar y su ejercito han triunfado gracias a ti, noble guerrerx. ¡Felicitaciones! A partir de hoy, reina el caos\n");
    }
    return gana_alguien;
}

void jugar_rohan(juego_t* juego){
    for (int i = 0; i < (*juego).cantidad_rohan; i++){
        jugar(juego, BANDO_DEFENSIVO, i);
    }
    if((*juego).jugador_2.energia < 10){
        (*juego).jugador_2.energia++;
    }
}

void jugar_isengard(juego_t* juego){
    for (int i = 0; i < (*juego).cantidad_isengard; i++){
        jugar(juego, BANDO_OFENSIVO, i);
    }
    if((*juego).jugador_1.energia < 10){
        (*juego).jugador_1.energia++;
    }
}

int main(){
	
 	juego_t juego;
	personaje_t personaje;
	inicializar_juego(&juego);



	while(!hay_ganador(juego)){
        if (juego.jugador_1.bando == BANDO_DEFENSIVO){
            pedir_datos_personaje(juego.terreno, juego.plus_isengard, juego.plus_rohan, &(juego.jugador_1), &personaje);
            posicionar_personaje(&juego, personaje);
            if(juego.modo_de_juego == DOS_JUGADORES){
                pedir_datos_personaje(juego.terreno, juego.plus_isengard, juego.plus_rohan, &(juego.jugador_2), &personaje);
            }
            else{
                inicializar_cpu(juego.terreno, juego.plus_isengard, juego.plus_rohan, &(juego.jugador_2), &personaje);
            }
            posicionar_personaje(&juego, personaje);
            printf("\nEnergia Rohan: %i\n", juego.jugador_1.energia);
            printf("\nEnergia Isengard: %i\n", juego.jugador_2.energia);
            printf("%i\n", juego.cantidad_isengard);
        }
        else{
            if(juego.modo_de_juego == DOS_JUGADORES){
                pedir_datos_personaje(juego.terreno, juego.plus_isengard, juego.plus_rohan, &(juego.jugador_2), &personaje);
            }
            else{
                inicializar_cpu(juego.terreno, juego.plus_isengard, juego.plus_rohan, &(juego).jugador_2, &personaje);
            }
            posicionar_personaje(&juego, personaje);
            pedir_datos_personaje(juego.terreno, juego.plus_isengard, juego.plus_rohan, &(juego.jugador_1), &personaje);
            posicionar_personaje(&juego, personaje);
            printf("\nEnergia Rohan: %i\n", juego.jugador_2.energia);
            printf("\nEnergia Isengard: %i\n", juego.jugador_1.energia);
        }
        jugar_rohan(&juego);
        jugar_isengard(&juego);
        printf("\nLlegadas de Rohan: %i\n", juego.llegadas_rohan);
        printf("\nLlegadas de Isengard: %i\n", juego.llegadas_isengard);
    
    }
    return 0;
}