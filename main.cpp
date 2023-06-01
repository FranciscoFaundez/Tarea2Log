#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <malloc.h>
#include <random>
#include "PermutationEquiprob.h"
#include "PermutationSkew.h"
//#include "rbTree.h"
#include "splayTree.h"

int main(){

    // Creación del archivo de texto
    std::ofstream archivo("experimento.txt"); 
    //header
    archivo << "Tipo de Permutación,Alpha,Tipo de árbol,Max Número en Array,Número de Nodos,Tiempo de Búsqueda (us),Memoria Usada (bytes)"<< std::endl;
    
    // Seed del Experimento
    int seed = 1234;

    // Generador de numeros aleatorios
    std::mt19937 g(seed);

    // Condiciones iniciales del Experimento 
    int num_experiments = 2;
    int max_num_in_array = 6; //2^6
    int max_num_nodos = 10; //2^10

    // Instanciar variables
    std::vector<int> array_equi;
    std::vector<int> array_skew;

    for(int i = 0; i<num_experiments; i++){
        for(int num_nodos = 1; num_nodos<max_num_nodos;i++){
            for(int max_num = 5; max_num<max_num_in_array; i++){

            }
        }
    }

    archivo.close(); // Cierre del archivo de texto

    return 0;
}