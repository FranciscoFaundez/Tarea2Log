#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

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
vector<int> Skewed(int N, int M, int alpha) {

    int SUM = 0;
    // Crear un vector con elementos de 1 a N, en donde asignaremos f(i)
    vector<int> repeticiones(N);
    for (int i = 0; i < N; i++) {
        repeticiones[i] = floor(pow((i + 1), alpha));
        SUM += repeticiones[i];
    }

    // Normalizar el arreglo
    for (int i = 0; i < N; ++i) {
        repeticiones[i] = floor((repeticiones[i]/SUM)*M);
    }
    
    // Repetir cada elemento según repeticiones[i]
    vector<int> secuencia(M);
    int index = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < repeticiones[i]; ++j) {
            secuencia[index] = i+1;
            ++index;
        }
    }

    // Desordenar el arreglo
    random_device rd;
    mt19937 g(rd());
    shuffle(secuencia.begin(), secuencia.end(), g);
    
    return secuencia;
}

int main() {

    //----------------------------------------------------//
    /*
    // Generar un arreglo equiprobable
    int N = 1 << 12;
    int M = 1 << 16;
    int alpha = 0.5;

    
    vector<int> sec_eq = Equiprobable(N, M);
    for (int i = 0; i < M; ++i) {
        cout << sec_eq[i] << " ";
    }
    cout << endl;
    
    
    // Generar un arreglo skewed
    vector<int> sec_skew = Skewed(N, M, alpha);
    for (int i = 0; i < M; ++i) {
        cout << sec_skew[i] << " ";
    }
    cout << endl;
    */
   //----------------------------------------------------//

   //Skewed(100, 500, 1.5);

   int N = 100;
    int M = 500;
    int alpha = 1;
    int SUM = 0;
    // Crear un vector con elementos de 1 a N, en donde asignaremos f(i)
    vector<int> repeticiones(N);
    for (int i = 0; i < N; i++) {
        repeticiones[i] = floor(pow((i + 1), alpha));
        SUM += repeticiones[i];
    }
    for (int i = 0; i < N; ++i) {
        cout << repeticiones[i] << " ";
    }

    cout << " " << endl;
    cout << "SUM: " << SUM << endl;
    cout << " " << endl;
    // Normalizar el arreglo
    for (int i = 0; i < N; ++i) {
        repeticiones[i] = floor((repeticiones[i]/SUM)*M);
    }

    //printear cada valor de repeticiones
    for (int i = 0; i < N; ++i) {
        cout << repeticiones[i] << " ";
    }
    return 0;
}
