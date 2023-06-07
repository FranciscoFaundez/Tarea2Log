#include <fstream>
#include <map>
#include <string>
#include "splayTree.h"
#include "rbTree.h"

using namespace std;


// Función que genera un arreglo equiprobable
vector<uint> Equiprobable(uint N, uint M, int seed) {
    // Crear un vector con elementos de 1 a N
    vector<uint> arreglo(N);
    for (uint i = 0; i < N; ++i) {
        arreglo[i] = i + 1;
    }
    
    // Repetir cada elemento M/N veces
    vector<uint> secuencia(M);
    uint index = 0;
    for (uint i = 0; i < M; ++i) {
        secuencia[i] = arreglo[index];
        index = (index + 1) % N;
    }
    
    // Desordenar el arreglo
    mt19937 g(seed);
    shuffle(secuencia.begin(), secuencia.end(), g);
    
    return secuencia;
}


// Función que genera un arreglo skewed, según alpha
vector<uint> Skewed(uint N, uint M, double alpha, int seed) {


    uint SUM = 0;
    vector<uint> repeticiones(N);

    // Crear un vector con elementos de 1 a N
    for (uint i = 0; i < N; ++i) {
        repeticiones[i] = i + 1;
    }

    // Desordenar el vector
    mt19937 g(seed);
    shuffle(repeticiones.begin(), repeticiones.end(), g);
    
    vector<uint> copy(N);
    copy = repeticiones;
    

    // Asignamos los valores de f(i)
    for (uint i = 0; i < N; i++) {
        repeticiones[i] = floor(pow((repeticiones[i]), alpha));
        SUM += repeticiones[i];
    }

    // Normalizar el arreglo
    for (uint i = 0; i < N; ++i) {
        repeticiones[i] = ceil((static_cast<double>(repeticiones[i])/SUM)*M);
    }

    
    // Repetir cada elemento según repeticiones[i]
    vector<uint> secuencia(M);
    uint index = 0;
    for (uint i = 0; i < N; ++i) {
        for (uint j = 0; j < repeticiones[i]; ++j) {
            if (index == M) {
                secuencia.push_back(copy[i]);
            }
            secuencia[index] = copy[i];
            ++index;
        }

    }

    // Desordenar el arreglo
    shuffle(secuencia.begin(), secuencia.end(), g);

    return secuencia;
}

/*
SplayNode* fillSplay(SplayNode* root, vector<uint> secuencia, SplayTree st) {
    root = NULL;
    uint largo = secuencia.size();

    for (uint i = 0; i < largo; ++i) {
        root = st.Insert(secuencia[i], root);
    }
    return root;
}
*/

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

void LoopSearch(int index_perm, std::vector<uint> perm, double alpha , SplayTree st, SplayNode* root, RBTree rbt, Node* raiz, int max_num, int seed){

    size_t mem_splay = sizeof(st)+ (1 << max_num)*sizeof(SplayNode);
    size_t mem_rbt = sizeof(rbt)+ (1 << max_num)*sizeof(Node);
    // array de tiempos
    std::vector<double> times_splay;
    std::vector<double> times_rbt;

    // Tests SplayTree
    for (uint & search_value : perm) {

        auto start_search_splay = std::chrono::high_resolution_clock::now();
        root = st.Search(search_value, root);
        auto end_search_splay = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> delta_search_splay = end_search_splay - start_search_splay;

        auto start_search_rbt = std::chrono::high_resolution_clock::now();
        raiz = rbt.search(search_value);
        auto end_search_rbt = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> delta_search_rbt = end_search_rbt - start_search_rbt;

        // Guardamos los tiempos
        times_splay.push_back(delta_search_splay.count());
        times_rbt.push_back(delta_search_rbt.count());
    }
    // Promedio y Std
    double mean_time_search_splay = 0;
    double std_time_search_splay = 0;
    double sum = 0;
    double variance = 0;

    for(double & x: times_splay){
        sum += x;
    }

    mean_time_search_splay = sum / static_cast<double>(times_splay.size());

    for(double & x: times_splay){
        variance += pow(x - mean_time_search_splay,2);
    }

    std_time_search_splay = sqrt(variance/static_cast<double>(times_splay.size()-1));

    char buffer1[50];
    std::sprintf(buffer1, "%.10f", mean_time_search_splay);
    std::string mean_time_splay = buffer1;

    char buffer2[50];
    std::sprintf(buffer2, "%.10f", std_time_search_splay);
    std::string std_time_splay = buffer2;

    //Guardamos datos

    std::map<std::string, std::string> datapoint_splay = {{"index_permutation", std::to_string(index_perm)},
                                                           {"type_tree", "SplayTree"},
                                                           {"num_nodes", std::to_string((1 << max_num))},
                                                           {"mean_time_search(us)", mean_time_splay},
                                                           {"std_time_search(us)", std_time_splay},
                                                           {"alpha",std::to_string(alpha)},
                                                           {"tree_memory_usage(bytes)",std::to_string(mem_splay)},
                                                           {"seed",std::to_string(seed)},
    };
    // Escribir los datos en el archivo
    escribirArchivo("df_search.txt",datapoint_splay);


    double mean_time_search_rbt = 0;
    double std_time_search_rbt = 0;
    double sum2 = 0;
    double variance2 = 0;

    for(double & x: times_rbt){
        sum2 += x;
    }

    mean_time_search_rbt = sum2 / static_cast<double>(times_rbt.size());

    for(double & x: times_rbt){
        variance2 += pow(x - mean_time_search_rbt,2);
    }

    std_time_search_rbt = sqrt(variance2/static_cast<double>(times_rbt.size()-1));

    char buffer3[50];
    std::sprintf(buffer3, "%.10f", mean_time_search_rbt);
    std::string mean_time_rbt = buffer3;

    char buffer4[50];
    std::sprintf(buffer4, "%.10f", std_time_search_rbt);
    std::string std_time_rbt = buffer4;

    std::map<std::string, std::string> datapoint_rbt = {{"index_permutation", std::to_string(index_perm)},
                                                        {"type_tree", "RBTree"},
                                                        {"num_nodes", std::to_string((1 << max_num))},
                                                        {"mean_time_search(us)", mean_time_rbt},
                                                        {"std_time_search(us)", std_time_rbt},
                                                        {"alpha",std::to_string(alpha)},
                                                        {"tree_memory_usage(bytes)",std::to_string(mem_rbt)},
                                                        {"seed",std::to_string(seed)},
    };
    // Escribir los datos en el archivo
    escribirArchivo("df_search.txt",datapoint_rbt);
}





int main() {
    // Condiciones iniciales del Experimento
    const int num_experiments = 3;
    const int seed = 1234;

    // Instanciar variables
    const double alphas[3] = {0.5f, 1.0f, 1.5f};
    int index_perm = 0;
    uint M = 1 << 28;

    vector<uint> equi; //= Equiprobable(N, M);
    vector<uint> skw;  //= Skewed(N, M, alpha);

    SplayTree st;
    SplayNode *root = nullptr;
    RBTree rbt;
    Node* raiz = nullptr;

    // Generador de seed aleatorias para las permutaciones
    std::mt19937 gen(seed); // Set generador
    std::uniform_int_distribution<int> dis(0, 9999);
    int arr_seed[num_experiments];
    for (int & i : arr_seed){
        i = dis(gen);
    } // Terminamos de generar las seeds para las permutaciones

    cout<< "###################### N = 16 ######################"<< endl;
    cout<< "Rellenando SplayTree..."<< endl;
    // Primer N -> 2^16
    root = fillSplay(root, st, 0, (1<<16));
    cout<< "Rellenando RedBlackTree..."<< endl;
    rbt.fillRB(0,(1<<16));

    for(int & x : arr_seed){
        cout<< "Creando array equiprobable..."<< endl;
        equi = Equiprobable((1<<16),M,x);
        cout<< "Tomando tiempos de busqueda..."<< endl;
        LoopSearch(index_perm,equi,0,st,root,rbt,raiz,16,x);
        index_perm++;
        cout<< "Limpiando array equiprobable..."<< endl;
        equi.clear();
        for(double alpha : alphas) {
            cout<< "Creando array skew de alpha = "<< alpha << endl;
            skw = Skewed((1 << 16), M, alpha, x);
            cout<< "Tomando tiempos de busqueda..."<< endl;
            LoopSearch(index_perm, skw, alpha,st, root, rbt, raiz, 16,x);
            index_perm++;
            cout<< "Limpiando array skew de alpha = "<< alpha << endl;
            skw.clear();
        }
    }
/**
    // 2^(n-1) -> 2^n
    for (int i = 16; i<17; i++){
    cout<< "###################### N = " << i+1  << " ######################"<< endl;
        cout<< "Rellenando SplayTree..."<< endl;
        root = fillSplay(root, st, (1<<i), (1<<(i+1)));
        cout<< "Rellenando RedBlackTree..."<< endl;
        rbt.fillRB((1<<i),(1<<(i+1)));

        for(int & x : arr_seed){
            cout<< "Creando array equiprobable..."<< endl;
            equi = Equiprobable((1<<(i+1)),M,x);
            cout<< "Tomando tiempos de busqueda..."<< endl;
            LoopSearch(index_perm,equi,0,st,root,rbt,raiz,i+1,x);
            index_perm++;
            cout<< "Limpiando array equiprobable..."<< endl;
            equi.clear();
            for(double alpha : alphas) {
                cout<< "Creando array skew de alpha = "<< alpha << endl;
                skw = Skewed((1 << (i+1)), M, alpha, x);
                cout<< "Tomando tiempos de busqueda..."<< endl;
                LoopSearch(index_perm, skw,alpha ,st, root, rbt, raiz, i+1,x);
                index_perm++;
                cout<< "Limpiando array skew de alpha = "<< alpha << endl;
                skw.clear();
            }
        }
    }
*/
    return 0;
}
