#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// GLOBAL DATA
int nums[4];
string expr[4];
string results[101];

// visited states
set<string> visited;

// 🧱 STEP 2 — Operations
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
        res = pow(a,b);
        
    }
    else{
        return false;
    }

    return true;
}

bool fact(int x, int &res) {

    res = 1;
    for (int i = 1; i <= x; i++){
        res *= i;
    }

    return true;
}

// 🧱 STEP 4 — Build smaller array
int buildNew(int oldVals[], string oldExpr[], int size,   // Pointers (Clear)
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
string encode(int vals[], int size) {
    vector<int> temp(vals, vals + size);  // safe copy

    sort(temp.begin(), temp.end());

    string key = "";
    for (int x : temp)
        key += to_string(x) + ",";

    return key;
}

// 🧱 STEP 5 — Recursive exploration
void explore(int vals[], string exprs[], int size) {

    if (size <= 0 || size > 10) return;

    // avoid repeated states
    string key = encode(vals, size);
    if (visited.count(key)) return;   // Check if the element key exist in the set (if exists -> stops)
    visited.insert(key);

    // base case
    if (size == 1) {
        int v = vals[0];

        if (v >= 1 && v <= 100 && results[v] == "") {
            results[v] = exprs[0];
        }
        return;
    }

    // combine pairs
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            int newVals[10];
            string newExprs[10];

            int newSize = buildNew(vals, exprs, size, i, j, newVals, newExprs);

            char ops[] = {'+','-','*','/','%','^'};

            for (int k = 0; k < 6; k++) {
                int r;

                if (calculate(vals[i], vals[j], ops[k], r)) {
                    newVals[newSize] = r;
                    newExprs[newSize] = "(" + exprs[i] + ops[k] + exprs[j] + ")";
                    explore(newVals, newExprs, newSize + 1);
                }

                if (calculate(vals[j], vals[i], ops[k], r)) {
                    newVals[newSize] = r;
                    newExprs[newSize] = "(" + exprs[j] + ops[k] + exprs[i] + ")";
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
                newExprs[k] = exprs[k];
            }

            newVals[i] = f;
            newExprs[i] = "(" + exprs[i] + "!)";

            explore(newVals, newExprs, size);
        }
    }
}

// 🧱 STEP 6 — MAIN
int main() {

    for (int i = 1; i <= 100; i++)
        results[i] = "";

    cout << "Enter 4 numbers:\n";

    for (int i = 0; i < 4; i++) {
        cin >> nums[i];
        expr[i] = to_string(nums[i]);
    }

    explore(nums, expr, 4);

    cout << "\nResults:\n";

    for (int i = 1; i <= 100; i++) {
        if (results[i] != "")
            cout << i << ": " << results[i] << endl;
        else
            cout << i << ": NOT POSSIBLE\n";
    }

    return 0;
}