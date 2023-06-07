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
vector<ll> Equiprobable(ll N, ll M) {
    // Crear un vector con elementos de 1 a N
    vector<ll> arreglo(N);
    for (ll i = 0; i < N; ++i) {
        arreglo[i] = i + 1;
    }
    
    // Repetir cada elemento M/N veces
    vector<ll> secuencia(M);
    ll index = 0;
    for (ll i = 0; i < M; ++i) {
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
vector<ll> Skewed(ll N, ll M, double alpha) {

    
    ll SUM = 0;
    vector<ll> repeticiones(N);

    // Crear un vector con elementos de 1 a N
    for (ll i = 0; i < N; ++i) {
        repeticiones[i] = i + 1;
    }

    // Desordenar el vector
    random_device rd;
    mt19937 g(rd());
    shuffle(repeticiones.begin(), repeticiones.end(), g);
    
    vector<ll> copy(N);
    copy = repeticiones;
    

    // Asignamos los valores de f(i)
    for (ll i = 0; i < N; i++) {
        repeticiones[i] = floor(pow((repeticiones[i]), alpha));
        SUM += repeticiones[i];
    }

    // Normalizar el arreglo
    for (ll i = 0; i < N; ++i) {
        repeticiones[i] = ceil((static_cast<double>(repeticiones[i])/SUM)*M);
    }
    
    
    // Repetir cada elemento según repeticiones[i]
    vector<ll> secuencia(M);
    ll index = 0;
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < repeticiones[i]; ++j) {
            if (index == M) {
                secuencia.push_back(copy[i]);
            }
            secuencia[index] = copy[i];
            ++index;
        }

    }

    // Desordenar el arreglo
    shuffle(secuencia.begin(), secuencia.end(), g);

    return secuencia;
}

/*
SplayNode* fillSplay(SplayNode* root, vector<ll> secuencia, SplayTree st) {
    root = NULL;
    ll largo = secuencia.size();

    for (ll i = 0; i < largo; ++i) {
        root = st.Insert(secuencia[i], root);
    }
    return root;
}
*/

int main() {

    ll N = 1<<16;
    ll M = 1<<28;
    double alpha = 0;

    vector<ll> equi(M); //= Equiprobable(N, M);
    vector<ll> skw(M);  //= Skewed(N, M, alpha);

    SplayTree st;
    SplayNode *root = NULL;
    root = fillSplay(root, st, N);

    //st.InOrder(root);
    

    return 0;
}
