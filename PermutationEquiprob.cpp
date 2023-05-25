#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>

int* PermutationEqui(int n_max, int seed){
    // Tamaño del array M
    int SIZE_ARR_M = pow(2,28);
    // Creamos el array arr
    int* arr = (int*) malloc(SIZE_ARR_M*sizeof(int));

    for (int i = 0; i < SIZE_ARR_M; i++){
        // Asignamos a cada elemento i-esimo del array
        // el resto de dividir i entre n_max más 1
        // Generando una periodicidad de 1 hasta n_max
        arr[i] = (i % n_max) + 1;
    }

    // Generamos la semilla para la función shuffle
    std::mt19937 g(seed);

    // Revolvemos el array
    std::shuffle(arr, arr + SIZE_ARR_M, g);

    // Retornamos el array
    return arr;
};