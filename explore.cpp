#include "functions.h"


void explore(int* vals, string* expresion, int size, bool* facto) {

    if (size <= 0 || size > 10){
        return;
    }

    // avoid repeated states
    string key = encode(vals, size);
    if (LinearSearch(key)){
        return;
    }
    
    Procesados[ElementosProcesados] = key;
    ElementosProcesados += 1;

    // base case
    if (size == 1) {
        int v = vals[0];

        if (v >= 1 && v <= 100 && Resultados[v] == "") {   // The first result that enters to this part
            Resultados[v] = expresion[0];
        }
        return;
    }

    // combine pairs
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            int newVals[10];
            string newExprs[10];
            bool newFacto[10];

            bool* ptrnewFacto = newFacto;
            int* ptrnewVals = newVals;
            string* ptrnewExprs = newExprs;

            int newSize = buildNew(vals, expresion, size, i, j, ptrnewVals, ptrnewExprs);
            buildNewFact(facto,size, i,j,ptrnewFacto);

            char ops[] = {'+','-','*','/','%','^'};

            for (int k = 0; k < 6; k++) {
                int r;

                if (calculate(vals[i], vals[j], ops[k], r)) {
                    newVals[newSize] = r;
                    newFacto[newSize] = false;
                    newExprs[newSize] = "(" + expresion[i] + ops[k] + expresion[j] + ")"; // Concatenation of the operations
                    explore(newVals, newExprs, newSize + 1,newFacto);  // Because of that you lost 2 but win one
                }

                if (calculate(vals[j], vals[i], ops[k], r)) {
                    newVals[newSize] = r;
                    newFacto[newSize] = false;
                    newExprs[newSize] = "(" + expresion[j] + ops[k] + expresion[i] + ")";
                    explore(newVals, newExprs, newSize + 1,newFacto);
                }
            }
        }
    }

    // factorial step (controlled)
    for (int i = 0; i < size; i++) {
        int f;
             // First factorial of a element      Factorial      Avoid 1 and 2    Less than 1000
        if (facto[i] == false &&fact(vals[i], f) && f != vals[i] && f <= 1000) {

            int newVals[10];
            string newExprs[10];
            bool newUsedFact[10];
            // Make a copy of the elements to dont destroy other branchs
            for (int k = 0; k < size; k++) {
                newVals[k] = vals[k];
                newExprs[k] = expresion[k];
                newUsedFact[k] = facto[k];
            }

            // Replace the number for its factorial
            newVals[i] = f;   
            newExprs[i] = "(" + expresion[i] + "!)";
            newUsedFact[i] = true;
            explore(newVals, newExprs, size,newUsedFact);
        }
    }
}
