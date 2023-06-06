#include "headers/Permutations.h"
#include "headers/RBTree.h"
#include "headers/SplayTree.h"
#include "lib/progressbar.h"
#include <chrono>
#include <fstream>
#include <map>
#include <string>


// Función para escribir en un archivo
void escribirArchivo( const std::string& nombreArchivo, const std::map<std::string, std::string>& datos) {
    std::ofstream archivo;
    try {
        // Abrir archivo para escritura
        archivo.open(nombreArchivo, std::ios::app);

        // Verificar si se abrió correctamente
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo para escritura");
        }

        // Escribir los datos en el archivo
        for (auto const& [clave, valor] : datos) {
            archivo << clave << "," << valor << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al escribir en el archivo: " << e.what() << std::endl;
        archivo.close();
        return;
    }

    // Cerrar el archivo
    archivo.close();
}

void LoopInsert(AbstractTree* tree, int max_num){
    progressbar bar( max_num);
    // Rellenamos el arbol con 1 -> 2^max_num
    for(int j = 1; j < (max_num + 1); j++){

        auto start_insert = std::chrono::high_resolution_clock::now();
        tree->insert(j);
        auto end_insert = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> delta_insert = start_insert - end_insert;

        char buffer[50];
        std::sprintf(buffer, "%.10f", delta_insert.count());
        std::string result = buffer;

        std::map<std::string, std::string> datapoint_insert = {{"type_tree", tree->typeTree()},
                                                               {"value_add", std::to_string(j)},
                                                               {"time_insert(us)", result},
        };

        escribirArchivo("df_insert.txt",datapoint_insert);
        bar.update();
    }
    tree->clear();
}

void LoopSearch(int index_perm, std::vector<int> perm, AbstractTree* tree, int max_num, int num_searchs, int seed){
        //Loop de insertar
        // Rellenamos el arbol con 1 -> 2^max_num
        for(int j = 1; j < ((1 << max_num) + 1); j++){
            tree->insert(j);
        }
        // Escoger 5 al azar
        //std::mt19937 g(seed); // Set generador
        //std::uniform_int_distribution<int> dis(0,(1<<28)-1); // (0, 2^28 -1)

        // crear vector que guarda los tiempos
        // Tests
        for (int & k : perm){

            auto start_search = std::chrono::high_resolution_clock::now();
            tree->search(k);
            auto end_search = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> delta_search = end_search - start_search; // guardarlo en el vector de tiempos
        }

        //int SUM = std::accumulate(arr_F.begin(), arr_F.end(), 0);

        char buffer[50];
        std::sprintf(buffer, "%.10f", delta_search.count()); //reemplazar por SUM/(1<<28)
        std::string result = buffer;


    std::map<std::string, std::string> datapoint_search = {{"index_permutation", std::to_string(index_perm)},
                                                           {"type_tree", tree->typeTree()},
                                                           {"num_nodes", std::to_string((1 << max_num))},
                                                           {"time_search(us)", result},
                                                           {"tree_memory_usage(bytes)",std::to_string(tree->memoryUsage())},
    };
    // Escribir los datos en el archivo
    escribirArchivo("df_search.txt",datapoint_search);

    tree->clear(); // Liberamos memoria
}

void LoopPermutation(int index_perm, float alpha, SplayTree* st, RBTree* rbt, int max_num, int num_search , int seed){

    // Creamos una permutacion equiprobable y medimos
    // cuanto demora en crearse
    auto start_perm = std::chrono::high_resolution_clock::now();
    std::vector<int> arr = PermutationSkew((1<<max_num),seed,alpha);
    auto end_perm = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> delta_perm = end_perm - start_perm; // delta


    std::map<std::string, std::string> datapoint = {{"index", std::to_string(index_perm)},
                                                    {"alpha", std::to_string(alpha)},
                                                    {"max_num_array", std::to_string(1<<max_num)},
                                                    {"time_creation_permutation", std::to_string(std::round(delta_perm.count()* 1e10) / 1e10)},
                                                    {"seed_creation_permutation",std::to_string(seed)},
                                                    };

    // Escribir los datos en el archivo
    escribirArchivo("df_permutation.txt",datapoint);

    // Splay Tree
    LoopSearch(index_perm, arr, st, max_num, num_search, seed);

    // RedBlack Tree
    LoopSearch(index_perm, arr, rbt, max_num, num_search, seed);
}


int main(){
    // Condiciones iniciales del Experimento
    const int num_experiments = 5;
    const int num_search = 5;
    const int n_min = 2; //2^2
    const int n_max = 10; //2^10
    const int seed = 1234;

    // Instanciar variables
    const float alphas[4] = {0.0f, 0.5f, 1.0f, 1.5f};
    SplayTree splay_tree;
    RBTree rb_tree;
    int index_perm = 0;

    // Testeamos antes de aplicar el experimento
    rb_tree.test();
    splay_tree.test();

    // Generador de seed aleatorias para las permutaciones
    std::mt19937 gen(seed); // Set generador
    std::uniform_int_distribution<int> dis(0, 9999);
    int arr_seed[num_experiments];
    for (int & i : arr_seed){
        i = dis(gen);
    } // Terminamos de generar las seeds para las permutaciones

    std::cout <<"\n############## ANALIZANDO INSERT ###############\n" << std::endl;
    // Analizamos los tiempos que demoran en insertar un nuevo elemento
    std::cout <<"SplayTree\n" << std::endl;
    LoopInsert(&splay_tree,(1<<n_max));
    std::cout <<"\nRedBlackTree\n" << std::endl;
    LoopInsert(&rb_tree,(1<<n_max));


    // Loop experimentos
    std::cout <<"\n############## EXPERIMENTOS ###############\n" << std::endl;
    progressbar bar( 4* (n_max-n_min)*num_experiments);
    std::cout << "Iniciando progreso..." << std::endl;
    for(int & i : arr_seed){
        // Definimos el valor maximo del N en la creacion de las permutaciones
        for (int n = n_min; n < n_max; n++)
            for (float alpha : alphas) {
                bar.update();
                LoopPermutation(index_perm, alpha, &splay_tree, &rb_tree, n, num_search, i);
                index_perm++;
            }
    }
    std::cout <<"\n############## END ###############" << std::endl;
    return 0;
}

