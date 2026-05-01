#include <iostream>
#include <string>
#include <algorithm>
#include "functions.h"

using namespace std;




int main() {
    int Nums[4];
    string Expresion[4];
    bool usedFact[4] = {false, false, false, false};

    int* ptrNums = Nums;
    string* ptrExpresion = Expresion;
    bool* ptrFactorial = usedFact;
    for (int i = 1; i <= 100; i++)
        Resultados[i] = "";

    cout << "Enter 4 numbers:\n";

    for (int i = 0; i < 4; i++) {
        cin >> ptrNums[i];
        ptrExpresion[i] = to_string(ptrNums[i]);
    }

    explore(ptrNums, ptrExpresion, 4,ptrFactorial);
    cout << "\nResultados:\n";

    for (int i = 1; i <= 100; i++) {
        if (Resultados[i] != "")
            cout << i << ": " << Resultados[i] << endl;
        else
            cout << i << ": NOT POSSIBLE\n";
    }

    return 0;
}