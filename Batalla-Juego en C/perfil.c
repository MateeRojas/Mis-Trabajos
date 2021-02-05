#include <stdio.h>
#include "perfil.h"


void perfil(char* tipo, int* intensidad){
	#define ARIES 1
	#define TAURO 2
	#define GEMINIS 3
	#define CANCER 4
	#define LEO 5
	#define VIRGO 6
	#define LIBRA 7
	#define ESCORPIO 8
	#define SAGITARIO 9
	#define CAPRICORNIO 10
	#define ACUARIO 11
	#define PISCIS 12
	const int NUM_ZODIACO_MAX = 12;
	const int NUM_ZODIACO_MIN = 1;
	const int MALDADES_MAX = 99;
	const int MALDADES_MIN = 0;
	const int MASCOTAS_MAX = 5;
	const int MASCOTAS_MIN = 0;
	const int MALDADES_MEDIO = 50;
	const int OPERADOR_CUATRO = 4;
	const int OPERADOR_UNO = 1;
	const int OPERADOR_DIEZ = 10;
	const char TIPO_AIRE = 'A';
	const char TIPO_FUEGO = 'F';
	const char TIPO_TIERRA = 'T';
	const char TIPO_AGUA = 'W';
	const char DRAMA = 'D';
	const char ACCION = 'A';
	const char TERROR = 'T';
	const char COMEDIA = 'C';
	const char BANDO_OFENSIVO = 'O';
	const char BANDO_DEFENSIVO = 'D';
	const char BANDO_INDETERMINADO = 'N';
	//Procedimiento que recibe un número (del 1 al 12) 
	//Una vez recibido el número, lo asignará a una variable por referencia
	void obtener_signo(int * signo_zodiacal){
    	printf("Ingrese su signo zodiacal (número correspondiente a su signo, siendo Aries el 1 y Piscis el 12 ) \n");  
    	scanf("%i", signo_zodiacal);
    	while(*signo_zodiacal > NUM_ZODIACO_MAX || *signo_zodiacal < NUM_ZODIACO_MIN){
        	printf("Signo fuera del rango 1-12, por favor ingrese un valor valido \n");
        	scanf("%i", signo_zodiacal);
        }
	}

	//Procedimiento que recibe un carácter ("A". "D", "C" ó "T") 
	//Una vez recibido el carácter, lo asignará a una variable por referencia
	void obtener_cine(char * genero_preferido){
		printf("Ingrese su género de cine favorito, siendo A acción, D drama, C comedia y T terror \n");
		scanf(" %c", genero_preferido);
		while(*genero_preferido != ACCION && *genero_preferido != COMEDIA && *genero_preferido != DRAMA && *genero_preferido != TERROR){
			printf("Caracter erróneo, ingrese uno válido \n");
			scanf(" %c", genero_preferido);
		}
	}

	//Procedimiento que recibe un número (del 0 al 99)
	//Una vez recibido el número, lo asignará a una variable por referencia
	void obtener_maldades(int * cantidad_maldades){
    	printf("Ingrese la cantidad de maldades que hizo en el ultimo mes (entre 0 y 99) \n");  
    	scanf("%i", cantidad_maldades);
    	while(*cantidad_maldades > MALDADES_MAX || *cantidad_maldades < MALDADES_MIN){
        	printf("Maldades fuera del rango 0-99, por favor ingrese un valor valido \n");
        	scanf("%i", cantidad_maldades);
    	}
	}

	//Procedimiento que recibe un número (del 0 al 5)
	//Una vez recibido el número, lo asignará a una variable por referencia
	void obtener_mascotas(int * cantidad_mascotas){
    	printf("Ingrese la cantidad de mascotas que posee (entre 0 y 5, si posee más de 5, ingrese 5) \n");  
    	scanf("%i", cantidad_mascotas);
    	while(*cantidad_mascotas > MASCOTAS_MAX || *cantidad_mascotas < MASCOTAS_MIN){
        	printf("Número fuera del rango 0-5, por favor ingrese un valor valido \n");
        	scanf("%i", cantidad_mascotas);
    	}
	}

	//Función que recibe un numero (del 1 al 12) que representa un signo 	
	//Devuelve un carácter ("T", "A", "W" ó "F") que representa un signo 
	char tipo_signo_obtenido(int signo_zodiacal){
    	char tipo;
    	switch (signo_zodiacal){
        	case ARIES:
        	case LEO:
        	case SAGITARIO:
            	tipo = TIPO_FUEGO;
            	break;
        	case TAURO:
        	case VIRGO:
        	case CAPRICORNIO:
            	tipo = TIPO_TIERRA;
            	break;
        	case GEMINIS:
        	case LIBRA:
        	case ACUARIO:
            	tipo = TIPO_AIRE;
            	break;
        	case CANCER:
        	case ESCORPIO:
        	case PISCIS:
            	tipo = TIPO_AGUA;
            	break;
    	}
    
    	return tipo;
	}

	//Procedimiento que recibe por referencia tres números (del 1 al 12, del 0 al 99 y del 0 al 5 ) y un carácter ("D", "A", "T" ó "C")
	//Manda cada variable a una función diferente
	void preguntar_todo(int * signo_zodiacal, char* genero_preferido, int * cantidad_maldades,int * cantidad_mascotas){
		obtener_signo(signo_zodiacal);
    	obtener_cine(genero_preferido);
    	obtener_maldades(cantidad_maldades);
		obtener_mascotas(cantidad_mascotas);
	}

	//Función que recibe dos carácteres representativos ("A". "D", "C" ó "T" y "T", "A", "W" ó "F") y un número (del 0 al 99) 
	//Devuelve un carácter que representa el bando ("D", "O" ó "N")
	char bando_asignado(char tipo_signo, char genero_preferido, int cantidad_maldades){
		char bando;
		if( (tipo_signo == TIPO_AIRE || tipo_signo == TIPO_FUEGO) && (genero_preferido == COMEDIA || genero_preferido == TERROR) && (cantidad_maldades >= MALDADES_MEDIO)){
			bando = BANDO_OFENSIVO;
		}
		else if((tipo_signo == TIPO_TIERRA || tipo_signo == TIPO_AGUA) && (genero_preferido == DRAMA || genero_preferido == ACCION) && (cantidad_maldades < MALDADES_MEDIO)){
		 		bando = BANDO_DEFENSIVO;
		}
		else{
    		bando = BANDO_INDETERMINADO;    	
    		}
    	return bando;	
    	    
	}

	//Funcion que recibe dos numeros, (del 0 al 99 y del 0 al 5)  	
	//Devuelve un número, producto de una suma 
	int intensidad_obtenida(int cantidad_maldades, int cantidad_mascotas){
		int puntos_maldades;
		if(cantidad_maldades < MALDADES_MEDIO){
			puntos_maldades = (cantidad_maldades / OPERADOR_DIEZ) + OPERADOR_UNO;
		}
		else{
			puntos_maldades = (cantidad_maldades / OPERADOR_DIEZ) - OPERADOR_CUATRO;
		}
		return puntos_maldades + cantidad_mascotas;
	}

	//Procedimiento que recibe un número (de 1 a 10) y un carácter ("D", "O" ó "N")
	//Compara e imprime un resultado, según el caso 
	void mostrar_perfil(char bando, int intensidad){
		if(bando == BANDO_DEFENSIVO){
			printf("Gracias a sus datos personales se pudo determinar que usted, guerrerx noble, forma parte del bando defensivo, con una intensidad de %i. Esperemos que luche y defienda a su pueblo con honor, al mando de Rohan.\n", intensidad);
		}
		else{
			printf("Gracias a sus datos personales se pudo determinar que usted, guerrerx noble, forma parte del ofensivo, con una intensidad de %i. Esperemos que luche y triunfe con honor, al mando de Isengard.\n", intensidad);
		}

	}

    int signo_zodiacal, cantidad_maldades, cantidad_mascotas;
    char genero_preferido, tipo_signo, bando;
    
    printf("Bienvenidx a este programa llamado Helm Royale. En la Guerra del Anillo están peleando Rohan e Isengard. El bando defensivo es el de Rohan, y el ofensivo es el de Isengard. Este programa, a partir de tus datos personales, determinará de qué lado estás. ¡Comencemos!\n");
    
    preguntar_todo(&signo_zodiacal, &genero_preferido, &cantidad_maldades, &cantidad_mascotas);
    
    tipo_signo = tipo_signo_obtenido(signo_zodiacal);
    
    bando = bando_asignado(tipo_signo, genero_preferido, cantidad_maldades);
    
    while(bando == BANDO_INDETERMINADO){
    	printf("Tus datos no logran definir un bando, por favor ingrese otros\n");
    	preguntar_todo(&signo_zodiacal, &genero_preferido, &cantidad_maldades, &cantidad_mascotas);
    	bando = bando_asignado(tipo_signo, genero_preferido, cantidad_maldades);
    }
	
	*intensidad = intensidad_obtenida(cantidad_maldades, cantidad_mascotas);
    *tipo = bando;
    
    mostrar_perfil(bando, *intensidad);
}