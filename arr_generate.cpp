#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "splayTree.h"
#include "rbTree.h"

using namespace std;
using ll = long long;

// Función que genera un arreglo equiprobable
vector<int> Equiprobable(int N, int M) {
    // Crear un vector con elementos de 1 a N
    vector<int> arreglo(N);
    for (int i = 0; i < N; ++i) {
        arreglo[i] = i + 1;
    }
    
    // Repetir cada elemento M/N veces
    vector<int> secuencia(M);
    int index = 0;
    for (int i = 0; i < M; ++i) {
        secuencia[i] = arreglo[index];
        index = (index + 1) % N;
    }
    
    // Desordenar el arreglo
    random_device rd;
    mt19937 g(rd());
    shuffle(secuencia.begin(), secuencia.end(), g);
    
    return secuencia;
}


// Función que genera un arreglo skewed, según alpha
vector<int> Skewed(int N, int M, double alpha) {

    
    int SUM = 0;
    vector<int> repeticiones(N);

    // Crear un vector con elementos de 1 a N
    for (int i = 0; i < N; ++i) {
        repeticiones[i] = i + 1;
    }

    // Desordenar el vector
    random_device rd;
    mt19937 g(rd());
    shuffle(repeticiones.begin(), repeticiones.end(), g);
    
    // Asignamos los valores de f(i)
    for (int i = 0; i < N; i++) {
        repeticiones[i] = floor(pow((repeticiones[i]), alpha));
        SUM += repeticiones[i];
    }

    // Normalizar el arreglo
    for (int i = 0; i < N; ++i) {
        repeticiones[i] = ceil((static_cast<double>(repeticiones[i])/SUM)*M);
    }
    
    // Repetir cada elemento según repeticiones[i]
    vector<int> secuencia(M);
    int index = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < repeticiones[i]; ++j) {
            if (index == M) {
                break;
            }
            secuencia[index] = i+1;
            ++index;
        }

    }

    // Desordenar el arreglo
    shuffle(secuencia.begin(), secuencia.end(), g);

    return secuencia;
}

/*
SplayNode* fillSplay(SplayNode* root, vector<int> secuencia, SplayTree st) {
    root = NULL;
    int largo = secuencia.size();

    for (int i = 0; i < largo; ++i) {
        root = st.Insert(secuencia[i], root);
    }
    return root;
}
*/

int main() {

    vector<int> equi = Equiprobable(100, 500);

    vector<int> skw  = Skewed(100, 500, 1.5);


    int largo = equi.size();

    SplayTree st;
    SplayNode *root;
    root = NULL;
    for (int i = 0; i < largo; ++i) {
        root = st.Insert(equi[i], root);
    }
    

    return 0;
}
