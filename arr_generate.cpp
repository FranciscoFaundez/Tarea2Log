#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>

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

    //---------------------------------------------------//

    //print secuencia

    cout << "equiprobable: " << endl;

    ll count = 0;
    for (ll i = 0; i < M; ++i) {
        cout << secuencia[i] << " ";
        count++;
    }

    cout << endl;
    cout << "count1: " << count << endl;

    //---------------------------------------------------//
    
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
                break;
            }
            secuencia[index] = i+1;
            ++index;
        }

    }

    // Desordenar el arreglo
    shuffle(secuencia.begin(), secuencia.end(), g);

    //---------------------------------------------------//
    //print secuencia
    ll count = 0;

    cout << "skewed: " << endl;

    for (ll i = 0; i < M; ++i) {
        cout << secuencia[i] << " ";
        count++;
    }
    cout << endl;
    cout << "count2: " << count << endl;

    //---------------------------------------------------//

    return secuencia;
}

int main() {

    vector<ll> equi = Equiprobable(100, 500);

    vector<ll> skw  = Skewed(100, 500, 1.5);

    return 0;
}
