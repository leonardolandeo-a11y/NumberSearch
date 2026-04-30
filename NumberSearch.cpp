#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// GLOBAL DATA
string Resultados[101];

// visited states
string Procesados[10000];
int ElementosProcesados = 0;
// 🧱 STEP 2 — Operations
bool LinearSearch(string obj){
    for (int i = 0; i<ElementosProcesados;i++){
        if (Procesados[i] == obj){
            return true;
        }
    }
    return false;
}

bool calculate(int a, int b, char op, int &res) {

    if (op == '+'){
        res = a + b;
    }
    else if (op == '-'){
        res = a - b;
    }
    else if (op == '*'){
         res = a * b;
    }
    else if (op == '/') {
        if (b == 0 || a % b != 0){
            return false;
        }
        res = a / b;
    }
    else if (op == '%') {
        if (b == 0){
            return false;
        }
        res = a % b;
    }
    else if (op == '^') {
        if ( b > 10){
            return false;
        }

        res = 1;
        
        for(int i = 0; i<b;i++){
            res *=a;
        }

        
    }
    else{
        return false;
    }

    return true;
}

bool fact(int x, int &res) {
    if (x < 0 || x > 10) return false;
    res = 1;
    for (int i = 1; i <= x; i++){
        res *= i;
    }

    return true;
}

// 🧱 STEP 4 — Build smaller array
int buildNew(int* oldVals, string* oldExpr, int size,   // Pointers (Clear)
             int i, int j,
             int newVals[], string newExpr[]) {

    int idx = 0;

    for (int k = 0; k < size; k++) {
        if (k != i && k != j) {
            newVals[idx] = oldVals[k];
            newExpr[idx] = oldExpr[k];
            idx++;
        }
    }

    return idx;
}

// 🔥 SAFE encode (FIXED)
string encode(int* vals, int size) {
    int temp[size];
    for (int i = 0; i< size; i++){
        temp[i] = vals[i];
    }
    sort(temp, temp+size);

    string key = "";
    for (int i = 0; i< size; i++){
        key += to_string(temp[i]) + ",";
    }
    return key;
}

// 🧱 STEP 5 — Recursive exploration
void explore(int* vals, string* expresion, int size) {

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

        if (v >= 1 && v <= 100 && Resultados[v] == "") {
            Resultados[v] = expresion[0];
        }
        return;
    }

    // combine pairs
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            int newVals[10];
            string newExprs[10];

            int newSize = buildNew(vals, expresion, size, i, j, newVals, newExprs);

            char ops[] = {'+','-','*','/','%','^'};

            for (int k = 0; k < 6; k++) {
                int r;

                if (calculate(vals[i], vals[j], ops[k], r)) {
                    newVals[newSize] = r;
                    newExprs[newSize] = "(" + expresion[i] + ops[k] + expresion[j] + ")";
                    explore(newVals, newExprs, newSize + 1);
                }

                if (calculate(vals[j], vals[i], ops[k], r)) {
                    newVals[newSize] = r;
                    newExprs[newSize] = "(" + expresion[j] + ops[k] + expresion[i] + ")";
                    explore(newVals, newExprs, newSize + 1);
                }
            }
        }
    }

    // factorial step (controlled)
    for (int i = 0; i < size; i++) {
        int f;

        if (fact(vals[i], f) && f != vals[i] && f <= 1000) {

            int newVals[10];
            string newExprs[10];

            for (int k = 0; k < size; k++) {
                newVals[k] = vals[k];
                newExprs[k] = expresion[k];
            }

            newVals[i] = f;
            newExprs[i] = "(" + expresion[i] + "!)";

            explore(newVals, newExprs, size);
        }
    }
}

// 🧱 STEP 6 — MAIN
int main() {
    int Nums[4];
    string Expresion[4];
    

    int* ptrNums = Nums;
    string* ptrExpresion = Expresion;

    for (int i = 1; i <= 100; i++)
        Resultados[i] = "";

    cout << "Enter 4 numbers:\n";

    for (int i = 0; i < 4; i++) {
        cin >> ptrNums[i];
        ptrExpresion[i] = to_string(ptrNums[i]);
    }

    explore(ptrNums, ptrExpresion, 4);
    cout << "\nResultados:\n";

    for (int i = 1; i <= 100; i++) {
        if (Resultados[i] != "")
            cout << i << ": " << Resultados[i] << endl;
        else
            cout << i << ": NOT POSSIBLE\n";
    }

    return 0;
}