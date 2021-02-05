Mateo Rojas 104985

El presente trabajo realiza la implementacion del TDA (Tipo de Dato Abstracto) Tabla Hash.
El Hash es una estructura que se puede utilizar para guardar datos de una forma mucho mas
optima que en los anteriores TDA. Una de las grandes ventajas del Hash es que la complejidad de varias
de sus operaciones primitivas, como son insertar, buscar y borrar, tienen complejidad O(1).
Su funcionamiento se basa en que el hash tiene un vector de elementos con
una determinada capacidad. Cuando se desea insertar un elemento,
existe una funcion de hasheo que encirpta la clave de dicho elemento y devuelve la posicion
del vector que va a ocupar. Para buscar, obtener, borrar, etc el procedimientoes el mismo y se
realizan diferentes funciones con el elemento de la posicion que da como resultado el hasheo.
Mas adelante se explicara la parte mas interesante del hash.
En este trabajo se entrega la implementacion de las primitivas de hash:
crear
insertar
quitar
obtener
contiene
cantidad
destruir
Y tambien, las de iteradores, que sirven para recorrer todos los elementos del hash.
Por ultimo un archivo de minipruebas para probar su funcionamiento.
puede ser externo(con sus primitivas crear, tiene siguiente, siguiente, destruir) e interno, para
el cual se brinda una funcion hash con cada clave, que recorre y ejecuta una funcion con todos
los elementos del hash.
Se compila con la linea:
gcc *.c -o hash -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
Y se ejecuta con Valgrind, con la linea:
valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./ hash
Diferentes tipos de hash:
Cuando un elemento devuelve una posicion ya ocupada es una colision y existen dos tipos de
Hash con diferentes soluciones a esto
Abierto: En un hash abierto las colisiones se resuelven insertando el elemento en la lista de
esa posicion, porque el vector, es un vector de listas.
Cerrado: Resuelve las colisiones insertando los elementos en el mismo hash. Hay dos formas,
Zona de Desborde y Exploracion de Posiciones
Rehash:
Esta es una funcion cuyo objetivo es evitar las proximas colisiones y maximizar la optimizacion
del hash. Cuando el factor de carga (cantidad de elementos / capacidad) supera un determinado limite,
el hash expande su vector e inserta nuevamente todos los nodos anteriormente insertados.
De esta forma las probabilidades de una colision disminuye.
