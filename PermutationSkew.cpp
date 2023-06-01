#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <set>
#include <cassert>

std::vector<int>PermutationSkew(int n_max, int seed, float alpha){
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

int main(){
    // Constantes
    const int n_max = 5;
    const int seed = 1234;
    const float alpha = 0.5;

    const int SIZE_ARR_M = 1 << 28;
    // Array de testeo
    std::vector<int> arr = PermutationSkew(n_max, seed, alpha);

    // Test 1: Verificar que el arreglo generado tiene el tamaño correcto.
    std::cout << "Test 1\n Prueba que el largo del arreglo generado es igual a 2^28\n" << std::endl;    
    assert(arr.size() == SIZE_ARR_M);
    std::cout << "Largo correcto\n" << std::endl;

    // Test 2: Prueba que el arreglo generado tenga n_max números enteros en el rango de 1 a n_max
    std::cout << "Test 2\n Prueba que el arreglo generado tenga n_max\n numeros enteros en el rango de 1 a n_max\n" << std::endl;
    std::set<int> unique_nums(arr.begin(), arr.end());
    assert(unique_nums.size() == n_max);
    for (int i = 1; i <= n_max; i++) {
        assert(unique_nums.count(i) == 1);
    }
    std::cout << "Paso\n" << std::endl;

    // Test 3: Prueba que el arreglo generado sea diferente cada vez que se llama a la función con una semilla diferente
    std::cout << "Test 3\n Prueba que el arreglo generado\n sea diferente cada vez que se llama\n a la funcion con una semilla diferente\n" << std::endl;
    std::vector<int> arr2 = PermutationSkew(n_max, seed+1, alpha);
    assert(arr != arr2);
    std::cout << "Paso\n" << std::endl;

    // Test 4: Prueba que el arreglo generado sea igual cada vez que se llama a la función con una semilla identica
    std::cout << "Test 4\n Prueba que el arreglo generado\n sea igual cada vez que se llama\n a la funcion con una semilla identica\n" << std::endl;
    std::vector<int> arr3 = PermutationSkew(n_max, seed, alpha);
    assert(arr == arr3);
    std::cout << "Paso\n" << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}