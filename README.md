# Parcial1AYED

Desarrollar una máquina que ejecute un programa almacenado en un archivo 
como una secuencia de instrucciones. Las instrucciones del programa
serán escritas en un lenguaje de programación elemental AYED19, que será
descripto a continuación. En el lenguaje AYED19 cada instrucción ocupa un
reglon. Hay 5 tipos de instrucciones:

1) Declaración de variables. Las variables serán de tipo entero, cuyo nombre
será de un solo caracter de la ’a’ a la ’z’.

2) Asignación. Permite asignar un valor entero a alguna de las variables
previamente declaradas. Las instrucciones de este tipo son de la forma:
Var = expresion aritmetica
donde
Var es el nombre de una variable previamente definida
expresion aritmetica es una expresión que puede ser un número, una va-
riable o una operacion aritmética cuyos operadores son de las 4 operaciones
aritméticas, y como operandos son números enteros de un solo dígito o nom-
bres de variables antes declaradas.

3) Condicional. Es una instrucción IF seguida por condición booleana en-
tre paréntesis THEN instrucción. (una sola)
la condición booleana tiene como operadores relacionales al igual (==), dis-
tinto (!=), menor (<) y mayor (> )

4) Show. Es un comando que permite imprimir por pantalla el valor de
una expresion aritmetica definida anteriormente.

5) Salto. Cada instrucción del programa tiene asignado un número que
representa su posición en la secuencia del programa, comenzando desde 1.
La instrucción JUMP contiene un número que hace referencia al salto en el
flujo de ejecución del programa hacia la instrucción dada por el número.
