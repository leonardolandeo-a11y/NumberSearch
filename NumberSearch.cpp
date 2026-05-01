/*

BUSQUEDA DE NUMEROS DEL 1 AL 100 USANDO UN METODO RECURSIVO

OBJETIVO:
Encontrar todos los numeros del 1 al 100 utilizando unicamente 4 numeros dados como entrada,
donde cada numero pertenece al rango [1 - 9].

------------------------------------------------------------
SOLUCION RECURSIVA:

La solucion se basa en recursividad, donde en cada paso reducimos el problema combinando elementos hasta llegar a una sola solucion.

------------------------------------------------------------
PROCESO:

1. Entrada inicial:
    Se recibe un arreglo de 4 numeros:
    [a, b, c, d], donde cada elemento pertenece a el rango [1-9].

2. Seleccion de pares:
    En cada nivel de la recursion, seleccionamos dos elementos del conjunto actual.
    Ejemplo:
    (a, b)

3. Operaciones posibles:
    Con cada par (a, b) podemos aplicar 6 operaciones basicas:
    - a + b
    - a - b
    - b - a
    - a * b
    - a / b (si b != 0)
    - b / a (si a != 0)

    Cada operacion genera un nuevo valor h.

4. Reduccion del problema:
    Cuando tenemos h, creamos un nuevo array reemplazando a y b por h:

    [a, b, c, d]
        ↓
    elegimos (a, b)
        ↓
    obtenemos h = operacion(a, b)
        ↓
    nuevo estado: [h, c, d]

5. Recursividad:
    El proceso se va a repetir con el nuevo array hasta llegar a un solo numero.

------------------------------------------------------------
CASO BASE:

Cuando el array llega a tener un solo elemento, entonces:
    - Utilizaremos ese numero como respuesta.
    - Verificamos si el numero pertenece [1-100].

------------------------------------------------------------

*/

#include <iostream>
#include <string>
#include <algorithm>
#include "functions.h"

using namespace std;


int main() {
    /*
    Nums -> Guardaremos los 4 numeros que llegan por entrada.
    Expresion -> Guardaremos la forma con la que llegamos a un nuevo numero por ejemplo (a * b)
    VerificacionFactorial -> Nos permite evitar factoriales dobles.

    --- Para cada uno creamos punteros ---
    */
    int Nums[4];
    string Expresion[4];
    bool VerificacionFactorial[4] = {false, false, false, false};

    int* ptrNums = Nums;
    string* ptrExpresion = Expresion;
    bool* ptrVerficacionFactorial = VerificacionFactorial;
    
    for (int i = 1; i <= 100; i++){
        Resultados[i] = "";
    }

    cout << "Ingresa los 4 numeros:\n";

    for (int i = 0; i < 4; i++) {
        cin >> ptrNums[i];
        ptrExpresion[i] = to_string(ptrNums[i]);
    }

    explore(ptrNums, ptrExpresion, 4,ptrVerficacionFactorial);
    cout << "\nResultados:\n";

    for (int i = 1; i <= 100; i++) {
        if (Resultados[i] != "")
            cout << i << ": " << Resultados[i] << endl;
        else
            cout << i << ": No es posible\n";
    }

    return 0;
}