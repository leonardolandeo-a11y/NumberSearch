#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
using namespace std;

extern string Resultados[101];
extern string Procesados[10000];
extern int ElementosProcesados;

bool LinearSearch(string obj);
bool calculate(int a, int b, char op, int &res);
bool fact(int x, int &res);

int buildNew(int* oldVals, string* oldExpr, int size, int i, int j,int* newVals, string* newExpr);
void buildNewFact(bool* oldVals, int size, int i, int j,bool* newVals);

string encode(int* vals, int size);
void explore(int* vals, string* expresion, int size, bool* facto);


#endif