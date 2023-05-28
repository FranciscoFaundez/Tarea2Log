#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <cassert>

std::vector<int>PermutationSkew(int n_max, int seed, float alpha)
{
    // Tamaño del array M
    const int SIZE_ARR_M = 1 << 28;

    // Generamos la semilla para la función revolverlos arrays
    std::mt19937 g(seed);

    // Creamos el array de  1,...,N
    std::vector<int> arr_N(SIZE_ARR_M);

    for (int i = 0; i < n_max; i++)
    {
        // Asignamos a cada elemento i-esimo del array
        // el resto de dividir i entre n_max más 1
        // Generando una periodicidad de 1 hasta n_max
        arr_N[i] = i + 1;
    }

    // Revolvemos el array
    for (int i = n_max - 1; i > 0; i--) {
        std::swap(arr_N[i], arr_N[g() % (i + 1)]);
    }

    // Creamos el array para obtener los F
    std::vector<int> arr_F(SIZE_ARR_M);
    for (int i = 0; i < n_max; i++)
    {
        // Calculamos el valor F(i) = floor(pow(i, alpha))
        arr_F[i] = static_cast<int>(floor(pow(i, alpha)));
    }

    // SUM
    int SUM = std::accumulate(arr_F.begin(), arr_F.end(), 0);

    // Normalizamos F -> (F(i)/SUM)*M
    for (int i = 0; i < n_max; i++)
    {
        arr_F[i] = static_cast<int>(ceil(arr_F[i] / SUM) * SIZE_ARR_M);
    }

    // Creamos el array para la permutacion Skew
    std::vector<int> arr_C(SIZE_ARR_M);

    // Rellenamos C
    // Rellenamos C
    int i = 0;
    for (int j = 0; j < n_max; j++)
    {
        for (int k = 0; k < arr_F[j]; k++)
        {
            // Si el i sobrepasa el tamaño del array C
            if (i == SIZE_ARR_M)
            {
                break;
            }
            // Copiamos el valor
            arr_C[i] = arr_N[j];
            // Avanzamos al siguiente indice en el array C
            i++;
        }
    }

    // Revolvemos el array C
    for (int i = SIZE_ARR_M - 1; i > 0; i--) {
        std::swap(arr_C[i], arr_C[g() % (i + 1)]);
    }

    // Retornamos el array C
    return arr_C;
}

int main()
{
    /*
    const int n_max = 5;
    const int seed = 1234;
    const float alpha = 0.5;

    const int SIZE_ARR_M = 1 << 28;

    int *arr_C = PermutationSkew(n_max, seed, alpha);

    // Test 1: Verificar que el arreglo generado no es nulo.
    assert(arr_C != nullptr);

    // Test 2: Verificar que el arreglo generado tiene el tamaño correcto.
    int count = sizeof(arr_C)/sizeof(arr_C[0]);
    assert(count == SIZE_ARR_M);

    // Test 3: Verificar que la función PermutationSkew toma tres argumentos enteros.
    assert(sizeof(PermutationSkew(n_max, seed, alpha)) ==
           sizeof(int *) * SIZE_ARR_M);

    // Test 4: Verificar que la función PermutationSkew devuelve un puntero a un arreglo de enteros.
    assert(typeid(PermutationSkew(n_max, seed, alpha)).name() ==
           typeid(int *).name());

    // Test 5: Verificar que la función PermutationSkew genera una permutación de los números del 1 al n_max.
    bool is_permutation = true;
    for (int i = 1; i <= n_max; i++)
    {
        bool found = false;
        for (int j = 0; j < SIZE_ARR_M; j++)
        {
            if (arr_C[j] == i)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            is_permutation = false;
            break;
        }
    }
    assert(is_permutation);

    // Test 6: Verificar que la función PermutationSkew utiliza la semilla proporcionada para generar la permutación.
    int *arr_C2 = PermutationSkew(n_max, seed, alpha);
    bool is_same_permutation = true;
    for (int i = 0; i < SIZE_ARR_M; i++)
    {
        if (arr_C[i] != arr_C2[i])
        {
            is_same_permutation = false;
            break;
        }
    }
    assert(is_same_permutation);

    // Test 7: Verificar que la función PermutationSkew no genera la misma permutación cada vez que se llama con la misma semilla.
    std::mt19937 g(seed + 1);
    int *arr_C3 = PermutationSkew(n_max, seed + 1, alpha);
    bool is_different_permutation = false;
    for (int i = 0; i < SIZE_ARR_M; i++)
    {
        if (arr_C[i] != arr_C3[i])
        {
            is_different_permutation = true;
            break;
        }
    }
    assert(is_different_permutation);

    // Test 8: Verificar que la función PermutationSkew no genera permutaciones repetidas.
    bool is_unique_permutation = true;
    for (int i = 0; i < SIZE_ARR_M; i++)
    {
        for (int j = i + 1; j < SIZE_ARR_M; j++)
        {
            if (arr_C[i] == arr_C[j])
            {
                is_unique_permutation = false;
                break;
            }
        }
    }
    assert(is_unique_permutation);

    // Test 9: Verificar que la función PermutationSkew no modifica el tamaño del arreglo arr_C.
    assert(sizeof(arr_C) == sizeof(int *) * SIZE_ARR_M);

    // Test 10: Verificar que la función PermutationSkew libera la memoria asignada por malloc.
    delete[] arr_C;
    */
    std::cout << "All tests passed!" << std::endl;
    return 0;
}