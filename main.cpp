#include "Permutations.h"
#include "RBTree.h"
#include "SplayTree.h"
#include <string>
#include <fstream>

void LoopSearch(int index_perm, std::vector<int> perm, AbstractTree tree, std::string type_tree, int min_log_num_nodos, int max_log_num_nodos, int seed){
    
    // Abrir archivo para agregar los datos
    std::ofstream df_search("df_search.txt", ios::app);

    try {
        // Verificar si se abrió correctamente
        if (!df_search.is_open()) {
            throw runtime_error("No se pudo abrir el archivo para escritura");
        }
        
        //Loop de búsquedas
        for(int j = 1; j < ((1 << (min_log_num_nodos-1))+1); j++){
            tree.insert(j);
        }
        for(int log_num_nodos = min_log_num_nodos; log_num_nodos<max_log_num_nodos;log_num_nodos++){
            
            for(int j = (1 << (log_num_nodos-1)+1); j < ((1 << log_num_nodos)+1); j++){
                tree.insert(j);
            }

            // Escoger 5 al azar
            std::mt19937 g(seed); // Set generador
            std::uniform_int_distribution<int> dis(1,(log_num_nodos-1));

            for(int k = 0; k<5;k++){
                auto start_search = std::chrono::high_resolution_clock::now();
                splay_tree.search(dis(g));
                auto end_search = std::chrono::high_resolution_clock::now()
                std::chrono::duration<double> delta_search = end_search - start_search;
                //Escribimos
                df_search << index_perm <<"," << type_tree <<","<< (1<<log_num_nodos) <<","<<delta_search.count()<<","<< tree.memoryUsage()<<std::endl;
            }
        }
        tree.clear(); // Liberamos memoria
        df_search.close(); // cerramos el archivo correctamente
    }
    catch (const exception& e) {
        df_search.close(); // cerramos el archivo correctamente
        cerr << "Error: " << e.what() << std::endl;
    }
}

void LoopPermutationSkew(int index_perm, float alpha, SplayTree st, RBTree rbt, int max_num, int min_log_num_nodos, int max_log_num_nodos, int seed){

    // Creamos una permutacion equiprobable y medimos
    // cuanto demora en crearse
    auto start_perm = std::chrono::high_resolution_clock::now();
    arr = PermutationSkew(max_num,arr_seed[i],alpha);
    auto end_perm = std::chrono::high_resolution_clock::now();
        
    std::chrono::duration<double> delta_perm = end_perm - start_perm; // delta

    try{
        std::ofstream df_permutation("df_permutation.txt", ios::app);

        // Verificar si se abrió correctamente
        if (!df_permutation.is_open()) {
            throw runtime_error("No se pudo abrir el archivo para escritura");
        }

        df_permutation << index_perm << ", Skew,"<< alpha << "," << max_num << "," << delta_perm.count() << "," << arr_seed[i] << std::endl;
        df_permutation.closed()
    }
    catch (const exception& e) {
        df_permutation.close(); // cerramos el archivo correctamente
        cerr << "Error: " << e.what() << std::endl;
    }
    // Splay Tree
    LoopSearch(index_perm, arr, st, "SplayTree", min_log_num_nodos, max_log_num_nodos,arr_seed[i]);
    
    // RedBlack Tree
    LoopSearch(index_perm, arr, rbt, "RBTree", min_log_num_nodos, max_log_num_nodos,arr_seed[i]);

}


int main(){

    // Condiciones iniciales del Experimento
    const int num_experiments = 2;
    const int max_num_in_array = 6; //2^6
    const int num_search_for_state = 5;
    const int min_log_num_nodos = 5; //2^5
    const int max_log_num_nodos = 10; //2^10
    const int seed = 1234;

    // Creacion de datasets
    std::ofstream df_permutation("df_permutation.txt");
    std::ofstream df_search("df_search.txt");

    //DataFrame headers
    df_permutation <<"index, type_permutation, alpha, max_num_array, time_creation_permutation, seed_creation_permutation" << std::endl;
    df_search << "index_permutation, type_tree, num_nodes, time_search(us), tree_memory_used(bytes)"<< std::endl;

    df_permutation.close();
    df_search.close();
    // Generador de seed aleatorias para las permutaciones
    std::mt19937 g(seed); // Set generador
    std::uniform_int_distribution<int> dis(0, 9999);
    int arr_seed[num_experiments];

    for (int i = 0; i <num_experiments; i++){
        arr_seed[i] = dis(g);
    } // Terminamos de generar las seeds para las permutaciones


    // Instanciar variables
    std::vector<int> array_equi;

    std::vector<int> array_skew;

    SplayTree splay_tree;

    RedBlackTree rb_tree;

    int index_perm = 0;

    // Loop experimentos
    for(int i = 0; i<num_experiments; i++){

        // Definimos el valor maximo del N en la creacion de las permutaciones
        for(int max_num = 5; max_num<max_num_in_array; max_num++){

            // Permutacion Equiprobable

            // Creamos una permutacion equiprobable y medimos
            // cuanto demora en crearse
            auto start_perm = std::chrono::high_resolution_clock::now();
            array_equi = PermutationEqui(max_num,arr_seed[i]);
            auto end_perm = std::chrono::high_resolution_clock::now();
                
            std::chrono::duration<double> delta_perm = end_perm - start_perm; // delta

            try{
                std::ofstream df_permutation("df_permutation.txt", ios::app);

                // Verificar si se abrió correctamente
                if (!df_permutation.is_open()) {
                    throw runtime_error("No se pudo abrir el archivo para escritura");
                }

                df_permutation << index_perm << ", Equiprobable, 0," << max_num << "," << delta_perm.count() << "," << arr_seed[i] << std::endl;
                df_permutation.closed()
            }
            catch (const exception& e) {
                df_search.close(); // cerramos el archivo correctamente
                cerr << "Error: " << e.what() << std::endl;
            }
            // Splay Tree
            LoopSearch(index_perm, array_equi, splay_tree, "SplayTree", min_log_num_nodos, max_log_num_nodos,arr_seed[i]);
            
            // RedBlack Tree
            LoopSearch(index_perm, array_equi, rb_tree, "RBTree", min_log_num_nodos, max_log_num_nodos,arr_seed[i]);

            index_perm++;

            LoopPermutationSkew(index_perm, 0.5, splay_tree, rb_tree, max_num, min_log_num_nodos, max_log_num_nodos, arr_seed[i]);

            index_perm++;

            LoopPermutationSkew(index_perm, 1.0, splay_tree, rb_tree, max_num, min_log_num_nodos, max_log_num_nodos, arr_seed[i]);

            index_perm++;

            LoopPermutationSkew(index_perm, 1.5, splay_tree, rb_tree, max_num, min_log_num_nodos, max_log_num_nodos, arr_seed[i]);

            index_perm++;
        }
    }
    
    return 0;
}
