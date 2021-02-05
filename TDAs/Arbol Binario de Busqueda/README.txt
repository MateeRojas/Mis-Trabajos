//Mateo Rojas 104985

En el presente trabajo, se implementa un ABB (Árbol Binario de Búsqueda) y todas las funciones de este.
Cada función del ABB está implementada individualmente en el .c del trabajo. La recursividad es crucial debido a que
se puede aprovechar la estructura del dato para simplificar el tiempo de ejecución de las acciones de esta forma (una
de las características principales del arbol) y , de hecho, la mismísima definición de ABB es recursiva:
Un primer nodo, llamado raiz, puede tener dos nodos hijos, los cuales serán la raiz de distintos subárboles y así
sucesivamente. Los nodos tendrán valores los cuales terminan de sellar la definicion de ABB, debido a su Orden.
Como en este trabajo se recibió un archivo .h y nuestro objetivo es implementar el .c, lo que se esta creando en realidad es
la libreria "abb.h" para poder incluirla en un programa "x" y pueda ser utilizada por el usuario, a modo de caja negra.
El mismo podrá llamar a todas sus funciones y el ABB hará lo que se le indica.
Adicionalmente, tiene funciones para recorrer el árbol en distintos ordenes, para conocer todos los nodos de este y
tambien, un iterador interno para, además de recorrer, operar con estos.
Para compilar un programa con nuestro abb implementado, se utilizará la linea de comando:
gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
Y para ejecutar, usando el programa Valgrind:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb
Lo último es para verificar que no haya pérdidas de memoria.
Junto al enunciado vienen incluídas unas pruebas las cuales deberemos ejecutar para verificar el correcto funcionamiento
de nuestro TDA. Como éstas son básicas, hay que checkear muchos casos donde nuestro trabajo podría romperse y, para ello,
se envía tambien un archivo de pruebas propio donde se termina de checkear el funcionamiento del TDA.

ABB y diferencia con AB: Un árbol binario es una estructura muy útil a la hora de realizar búsquedas. Por definición,
un AB tiene un nodo padre de todos los demás nodos, llamado raiz. Este puede tener 0, 1 ó 2 nodos hijos, los cuales serán
raices de más subárboles. La diferencia ente AB y ABB es que el segundo, tiene un orden estricto a la hora de la posicion
de los nodos. En un ABB si existe un nodo raíz con un determinado valor, todos los nodos a su izquierda tendrán valor menor a este
y todos los de su derecha, mayor. En caso de que se admitan nodos con iguales valores, el implementador deberá decidir
en qué lado colocarlo.
El ABB tiene sus propias funciones. Las principales son:
.crear
.destruir
.vacio
.insertar
.eliminar
.buscar
.recorrer

Objetivo de la función destruir: En este ABB se trabaja con la memoria dinámica, por ende toda memoria reservada debe ser destruida.
Cuando se crea un árbol, se reserva memoria para un ABB vacío, y a medida que se agregan nodos, la memoria
reservada aumenta. Al terminar de usar el árbol, si no se libera toda esa memoria, se pierde y de poco sirven todas
las optimizaciones que hicimos. Por eso es tan importante llamar a arbol_destruir.

Complejidades:
Según sus instrucciones, cada función tarda su determinado tiempo en ejecutarse y tiene su complejidad:
arbol_crear: O(1), instrucciones simples de creación.
arbol_inserta: O(n), en el peor de los casos, cuando el arbol está degenerado y es una lista, recorre TODOS
los elementos. Luego inserta.
arbol_borrar: O(n), en el peor de los casos, cuando el arbol está degenerado y es una lista, recorre TODOS
los elementos. Luego borra.
arbol_buscar: O(n),En el peor de los casos, cuando el arbol está degenerado y es una lista, recorre TODOS
los elementos. Luego devuelve el elemento buscado.
arbol_raíz: O(1), devuelve el elemento de un nodo.
arbol_vacío: O(1), hace un checkeo simple.
arbol_recorrido_inorden/postorden/preorden: O(n), recorre en un orden determinado TODOS los elementos del ABB.
Llena un array de forma simple.
arbol_destruir: Si es ABB es estático O(1). En este caso como cada nodo esta reservado en memoria dinámica, es necesrio
liberarlos uno por uno, haciendo que la función sea O(n).
abb_con_cada_elemento: O(n) Como lo dice su nombre, hace algo con TODOS los elementos. Si ese algo demora más que O(n),
la complejidad puede variar.
