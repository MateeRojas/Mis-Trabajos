Mateo Rojas 104985
En el trabajo entregado, se ejecuta en su totalidad el TDA lista con todas sus funciones primitivas. Aparte, se entrega una lista de pruebas para verificar que el traajo funcione correctamente. Para compilar se usa la linea:
gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0
Y para ejecutar:
valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./ lista_se
El funcionamiento es sencillo, cuando creamos una lista, los hacemos de manera dinámica.
La lista está implementada con nodos enlazados, lo que acrecenta la dificultad de la misma. Están todas las primitivas del TDA Lista, las cuales tambien trabajan en forma dinámica.
En este mismo TDA implementamos los TDA Cola y Pila, usando nodos enlazados. Usamos sus funciones primitivas.

LISTA: es un TDA (tipo de dato abstracto) que, como dice su nombre, es una lista de NODOS ENLAZADOS. Para hacer mas facil la comprensión, es como un vector sin posiciones. Los nodos son los componentes de las listas. Estos tienen su valor/dato y, si la lista es simplemente enlazada, un puntero a su siguiente, pero si la lista es doblemente enlazada, tiene uno al siguiente y uno al anterior. Si alguno de estos no existe, apunta a NULL.
PILA: Su característica principal es que las operaciones que hagamos, las haremos si o si sobre el último elemento porque, si estuviésemos hablando literalmente de una pila, solo podríamos sacar, poner, etc, en el elemento de mas arriba.
COLA: Su característica principal es que los nodos se insertan al final y salen del principio, como si de una fila se hablara.
ITERADOR: es un tipo de dato abstracto que sirve para recorrer una lista, tiene sus funciones tales como, tiene_siguiente, crear y destruir. En este trabajo no se implementan, sin embargo, existen pruebas para verificar su funcinonamiento.
ITERADOR EXTERNO: provee un set de primitivas especiales para recorrer una estructura
ITERADOR INTERNO: permite recorrer todos los elementos de un tda sin tener que controlar el ciclo en el cual se recorre el mismo. 