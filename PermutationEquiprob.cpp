#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <cassert>

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

int main(){
        // Constantes
    const int n_max = 5;
    const int seed = 1234;

    const int SIZE_ARR_M = 1 << 28;
    // Array de testeo
    std::vector<int> arr = PermutationEqui(n_max, seed);

    // Test 1: Prueba que el tamaño del arreglo generado es igual a 2^28
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
    std::vector<int> arr2 = PermutationEqui(n_max, seed+1);
    assert(arr != arr2);
    std::cout << "Paso\n" << std::endl;

    // Test 4: Prueba que el arreglo generado sea igual cada vez que se llama a la función con una semilla identica
    std::cout << "Test 4\n Prueba que el arreglo generado\n sea igual cada vez que se llama\n a la funcion con una semilla identica\n" << std::endl;
    std::vector<int> arr3 = PermutationEqui(n_max, seed+1);
    assert(arr2 == arr3);
    std::cout << "Paso\n" << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
};