#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <cmath>
#include <numeric>

int* PermutationSkew(int n_max, int seed, float alpha){
    // Tamaño del array M
    int SIZE_ARR_M = pow(2,28);

    // Creamos el array de  1,...,N
    int* arr_N = (int *) malloc(n_max*sizeof(int));
    
    for (int i = 0; i < n_max; i++){
        // Asignamos a cada elemento i-esimo del array
        // el resto de dividir i entre n_max más 1
        // Generando una periodicidad de 1 hasta n_max
        arr_N[i] = i+ 1;
    }    

    // Creamos el array de  1,...,N
    int* arr_N = (int *) malloc(n_max*sizeof(int));

    // Generamos la semilla para la función shuffle
    std::mt19937 g(seed);

    // Revolvemos el array
    std::shuffle(arr_N, arr_N + n_max, g);

    // Creamos el array para obtener los F
    int* arr_F = (int *) malloc(n_max*sizeof(int));

    for (int i = 0; i < n_max; i++){
        // Calculamos el valor F(i) = floor(pow(i, alpha))
        arr_F[i] = floor(pow(i,alpha));
    }

    // SUM
    int SUM = std::accumulate(arr_F, arr_F + n_max, 0);

    // Normalizamos F -> (F(i)/SUM)*M
    for (int i = 0; i < n_max; i++){
        arr_F[i] = ceil(arr_F[i]/SUM)*SIZE_ARR_M;
    }

    // Creamos el array para la permutacion Skew
    int* arr_C = (int *) malloc(SIZE_ARR_M*sizeof(int));

    // Rellenamos C
    int i = 0;
    while (true){
        // indice auxiliar para el array N y F
        int aux_n = 0;
        for (int j = 0; j < arr_F[aux_n]; j++){
            // Si el i sobrepasa el tamaño del array C
            if (i == SIZE_ARR_M){
                break;
            }
            // Copiamos el valor
            arr_C[i] = arr_N[aux_n];
            // Avanzamos al siguiente indice en el array C
            i++;
        }
        // Avanzamos al siguiente elemento del array F y N
        aux_n++;
    }

    //Liberamos memoria
    free(arr_N);
    free(arr_F);

    // Revolvemos el array C
    std::shuffle(arr_C, arr_C + SIZE_ARR_M, g);

    // Retornamos el array C
    return arr_C;
}   