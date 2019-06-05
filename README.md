# Parcial1AYED

Desarrollar una m´aquina que ejecute un programa almacenado en un ar-
chivo como una secuencia de instrucciones. Las instrucciones del programa
ser´an escritas en un lenguaje de programaci´on elemental AYED19, que ser´a
descripto a continuaci´on. En el lenguaje AYED19 cada instrucci´on ocupa un
reglon. Hay 5 tipos de instrucciones:

1) Declaraci´on de variables. Las variables ser´an de tipo entero, cuyo nombre
ser´a de un solo caracter de la ’a’ a la ’z’.

2) Asignaci´on. Permite asignar un valor entero a alguna de las variables
previamente declaradas. Las instrucciones de este tipo son de la forma:
Var = expresion aritmetica
donde
Var es el nombre de una variable previamente definida
expresion aritmetica es una expresi´on que puede ser un n´umero, una va-
riable o una operacion aritm´etica cuyos operadores son de las 4 operaciones
aritm´eticas, y como operandos son n´umeros enteros de un solo d´ıgito o nom-
bres de variables antes declaradas.

3) Condicional. Es una instrucci´on IF seguida por condici´on booleana en-
tre par´entesis THEN instrucci´on. (una sola)
la condici´on booleana tiene como operadores relacionales al igual (==), dis-
tinto (!=), menor (<) y mayor (> )

4) Show. Es un comando que permite imprimir por pantalla el valor de
una expresion aritmetica definida anteriormente.

5) Salto. Cada instrucci´on del programa tiene asignado un n´umero que
representa su posici´on en la secuencia del programa, comenzando desde 1.
La instrucci´on JUMP contiene un n´umero que hace referencia al salto en el
flujo de ejecuci´on del programa hacia la instrucci´on dada por el n´umero.
