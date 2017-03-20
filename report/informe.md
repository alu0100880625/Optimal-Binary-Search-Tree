# ÁRBOLES DE BÚSQUEDA BINARIA ÓPTIMOS
Kevin Diaz Marrero  
Aythami Torrado Cabrera  
Daniel Fernandez Perez  

## INTRODUCCIÓN

### ¿Qué es un árbol binario de búsqueda?
Un árbol binario no es más que una estructura de datos cuyos nodos pueden tener un hijo a la izquierda o a la derecha ( no más de 2). Por lo tanto un árbol binario de búsqueda no es más que un tipo de árbol binario cuya estructura de árbol se representa en informática.

![Sin titulo](arbol.png)

Estos árboles pueden realizar operaciones de:
* Búsqueda : La búsqueda en un árbol binario de búsqueda consiste en acceder a la raíz del árbol, si el elemento a localizar coincide con éste la búsqueda ha concluido con éxito, si el elemento es menor se busca en el subárbol izquierdo y si es mayor en el derecho. Si se alcanza un nodo hoja y el elemento no ha sido encontrado es que no existe en el árbol. Estas búsquedas son bastantes eficientes teniendo un máximo de comparaciones en el rango de  __[log2(N+1)] y N__
* Insertado: La inserción es similar a la búsqueda y se puede dar una solución tanto iterativa como recursiva. Si tenemos inicialmente como parámetro un árbol vacío se crea un nuevo nodo como único contenido el elemento a insertar. Si no lo está, se comprueba si el elemento dado es menor que la raíz del árbol inicial con lo que se inserta en el subárbol izquierdo y si es mayor se inserta en el subárbol derecho.
* Borrado: esta operación es más compleja y hay que tener en cuenta a borrar un nodo hija o padre el impacto que tendrá en la estructura del mismo.

### Árboles de búsqueda binario óptimos
 Si no vamos a modificar un árbol de búsqueda, y sabemos exactamente con qué frecuencia cada artículo  será accesible, podemos construir un árbol binario de búsqueda óptimo, que es un árbol de búsqueda donde el coste medio de buscar un artículo (el esperado coste de búsqueda) se reduce al __mínimo__.

 Incluso si sólo tenemos estimaciones de los costos de búsqueda, este sistema puede acelerar considerablemente las búsquedas en promedio.

Nosotros vamos a abordar la solución al mismo tanto mediante programación dinámica como con bottom_up.

## ALGORITMOS
### Programación dinámica

A la hora de abordar el problema mediante programación dinámica, hay que tener en cuenta el principio de optimibilidad, y este nos dice que :

> Todos los subárboles de un árbol óptimo son óptimos con respecto a las claves que contienen.”

De esta forma, abordaremos nuestro problema de la siguiente forma:
* Consideremos un subárbol óptimo que contenga las claves wi+1, wi+2, …, wj.
* Denotemos por Cij el número medio de comparaciones efectuadas en un subárbol óptimo que contiene las claves wi+1, wi+2, …, wj durante la búsqueda de una clave en el árbol principal (y convenimos en que Cii=0).
* Supongamos ahora que wk ocupa la raíz de ese subárbol.
* Sea el número medio de comparaciones efectuadas en ese subárbol durante la búsqueda de una clave en el árbol principal.

##### Pseudocódigo
El pseudocódigo de nuestro árbol mediante programación dinámica sería:
```
FUNCTION OPTIMAL_BINARY_SEARCH_TREE(keys, freq, n)  
begin   
   for i = 0 to n-1 do   
      aux_matrix(i,i) <- freq(i)  
   for L = 2 to n do
      for i = 0 to n do
         j <- i + L - 1
         aux_matrix(i,j) <- INFINITY
         for r = i to j do
            obst_freq <- 0
            if r > i then
              obst_freq + aux_matrix(i, r-1)
            elseif r < j then
              obst_freq + aux_matrix(r+1,j)
            else
              obst_freq + 0

            obst_freq + SUM(freq, i, j)

            if obst_freq < aux_matrix(i,j) then
              aux_matrix(i,j) <- obst_freq

  return aux_matrix(0, n-1)
end
```
Un pseudocódigo para nuestra función SUM sería:
```
FUNCTION SUM(freq, i, j)
begin
   s <- 0
   for k = i to j do
      s + freq(k)
   return s
end
```
##### Complejidad
El tiempo de complejidad es __O(n⁴)__. Pero este tiempo se puede reducir a __O(n³)__ pre-calculando la suma de las frecuencias en lugar de llamar a SUM una y otra vez.

##### Comprobaciones
| Nodos | Iteraciones | Tiempo (~s) |
| -- | -- | -- |
| 2 | 3 | 0.11 |
| 3 | 11 | 0.29 |
| 4 | 26 | 0.49 |
| 7 | 133 | 2.30 |
| 10 | 375 | 22.68|
| 15 | 1225 | 139.74|
|50 | 42875| 37589.90|

![Sin titulo](1.png)

> Hay que tener en cuenta que el tiempo depende del hardware del ordenador de pruebas y también de las __frecuencias__ que le pases en relación a cada nodo / key.

### Bottom up
#### Introducción
Bottom-up es una técnica que se base en ir resolviendo los subproblemas desde los de menor tamaño a los de más. De tal modo que al final nos de un resultado global de todo nuestro problema a resolver.
#### Pseudocódigo
```
FUNCTION BOTTOM_UP(keys, freq, n)
begin
   for i = 1 to SIZE_KEYS do
     limit <- i + SIZE_KEYS - n;
     for i = 0 to limit do
        j <- i + n - 1
        aux_matrix(i,j) <- INFINITY
        for  r = i to j
           temp < - SUM (i, j)
           if r > i then
              temporal  <- temporal + aux_matrix(i, r-1)
           if r < j
              temporal  <- temporal + aux_matrix(r+1, j)
           if temporal  < aux_matrix(i,j) then
              aux_matrix(i,j) <- temporal
end
```
##### Complejidad

##### Comprobaciones
| Nodos | Iteraciones | Tiempo (~s) |
| -- | -- | -- |
| 2 | 6 | 0.17 |
| 3 | 20 | 0.33 |
| 4 | 50 | 0.61 |
| 7 | 336 | 3.85 |
| 10 | 1210 | 19.58|
| 15 | 5440 | 141.42|
|50 | 563550| 39434.32|
## CONCLUCIONES

Como pudimos observar en la resolución mediante programación dinámica, el algoritmo es bastante efectivo, y aunque para cierta cantidad de nodos con sus respectivos frecuencias, el número de iteraciones sea mayor, sigue aportando una buena solución al problema planteado.
En comparación de usar la técnica bottom-up, el algoritmo de programación dinámica resuelve nuestro problema en la mitad de iteraciones e incluso la diferencia de tiempo de ejecución entre los dos métodos no son notorios en el hardware usado.


## BIBLIOGRAFÍA

*  http://www.geeksforgeeks.org/dynamic-programming-set-24-optimal-binary-search-tree/
* https://gist.github.com/mike168m/55fdb7e962fc521e56499b5c0b7dbe95
* https://alg12.wikischolars.columbia.edu/file/view/OPTIMALBST.pdf
* http://www.eli.sdsu.edu/courses/fall95/cs660/notes/OBST/OBST.html
* http://software.ucv.ro/~cmihaescu/ro/laboratoare/SDA/docs/arboriOptimali_en.pdf
* http://www.radford.edu/~nokie/classes/360/dp-opt-bst.html
