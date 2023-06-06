//
// Created by admin on 04-06-2023.
//

#include "headers/Permutations.h"

std::vector<int> PermutationEqui(int n_max, int seed) {
    // Tamaño del vector arr
    const int SIZE_ARR_M = 1 << 28;

    // Generamos la semilla para la función shuffle
    std::mt19937 g(seed);

    // Creamos el vector arr
    std::vector<int> arr(SIZE_ARR_M);
    for (int i = 0; i < SIZE_ARR_M; i++) {
        // Agregamos a cada elemento i-esimo del vector
        // el resto de dividir i entre n_max más 1
        // Generando una periodicidad de 1 hasta n_max
        arr[i] = (i % n_max) + 1;
    }

    // Revolvemos el array
    std::shuffle(arr.begin(), arr.end(), g);

    // Retornamos el vector
    return arr;
}

std::vector<int> PermutationSkew(int n_max, int seed, float alpha){
    // alpha igual 0 implica un array equiprobable
    if (alpha==0){
        return PermutationEqui(n_max,seed);
    }

    // Tamaño del array M
    const int SIZE_ARR_M = 1 << 28;

    // Generamos la semilla para la función revolverlos arrays
    std::mt19937 g(seed);

    // Creamos el array de  1,...,N
    std::vector<int> arr_N(n_max);
    std::iota(arr_N.begin(), arr_N.end(), 1);

    // Revolvemos el array
    std::shuffle(arr_N.begin(), arr_N.end(), g);

    // Creamos el array para obtener los F
    std::vector<int> arr_F(n_max);
    for (int i = 0; i < n_max; i++) {
        // Calculamos el valor F(i) = floor(pow(i, alpha))
        arr_F[i] = static_cast<int>(std::floor(std::pow(i+1, alpha)));
    }

    // SUM
    int SUM = std::accumulate(arr_F.begin(), arr_F.end(), 0);

    // Normalizamos F -> (F(i)/SUM)*M
    const float norm_factor = static_cast<float>(SIZE_ARR_M) / SUM;
    for (int i = 0; i < n_max; i++) {
        arr_F[i] = static_cast<int>(std::ceil(arr_F[i] * norm_factor));
    }

    // Creamos el array para la permutacion Skew
    std::vector<int> arr_C(SIZE_ARR_M);

    // Rellenamos C
    int i = 0;
    for (int j = 0; j < n_max; j++){
        for (int k = 0; k < arr_F[j]; k++){
            // Si el i sobrepasa el tamaño del array C
            if (i == SIZE_ARR_M){
                break;
            }
            // Copiamos el valor
            arr_C[i] = arr_N[j];
            // Avanzamos al siguiente indice en el array C
            i++;
        }
    }

    // Revolvemos el array C
    std::shuffle(arr_C.begin(), arr_C.end(), g);

    // Retornamos el array C
    return arr_C;
}