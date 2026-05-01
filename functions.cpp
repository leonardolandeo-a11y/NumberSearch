#include "functions.h"
#include <algorithm>

string Resultados[101];
string Procesados[10000];
int ElementosProcesados = 0;


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

int buildNew(int* oldVals, string* oldExpr, int size, int i, int j,int* newVals, string* newExpr) {

    int idx = 0;

    for (int k = 0; k < size; k++) {
        if (k != i && k != j) {  // Avoid the positions where the old elements were before
            newVals[idx] = oldVals[k];  
            newExpr[idx] = oldExpr[k];
            idx++;
        }
    }

    return idx;
}
void buildNewFact(bool* oldVals, int size, int i, int j,bool* newVals) {

    int idx = 0;

    for (int k = 0; k < size; k++) {
        if (k != i && k != j) {  // Avoid the positions where the old elements were before
            newVals[idx] = oldVals[k];  
            idx++;
        }
    }
}

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