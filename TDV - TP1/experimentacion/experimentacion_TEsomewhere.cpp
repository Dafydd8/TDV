#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "funciones.h"
#include <chrono>
using namespace std;

int main(){
    vector<int> maquinas = {1000, 1000};
    /*
    vector<int> pesos = {107, 226, 565, 195, 216, 315, 252};
    vector<int> beneficios = {98, 221, 347, 459, 581, 718, 903};
    */
    vector<int> pesos = {226, 565, 195, 216, 315};
    vector<int> beneficios = {209, 106, 221, 302, 212};
    vector<int> s;

    vector<float> t_fb;
    vector<float> t_fact;
    vector<float> t_opt;
    vector<float> t_pd;

    for (int i = 0 ; i < 10 ; i++){
        // FB
        vector<int> best_solution;
        auto start_1 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_fb = llenar_maquinas_FB(beneficios, pesos, maquinas, s, best_solution); // Bloque de código cuyo tiempo de ejecución quieres medir
        auto end_1 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_1 = end_1 - start_1;// Calcula la duración en milisegundos
        t_fb.push_back(duration_1.count());

        // OPT
        best_solution = {};
        int maximo = 0;
        auto start_2 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_opt = llenar_maquinas_BT_opt(beneficios, pesos, maquinas, s, maximo, best_solution); // Bloque de código cuyo tiempo de ejecución quieres medir
        auto end_2 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_2 = end_2 - start_2;// Calcula la duración en milisegundos
        t_opt.push_back(duration_2.count());

        // FACT
        best_solution = {};
        auto start_3 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_fact = llenar_maquinas_BT_fact(beneficios, pesos, maquinas, s, best_solution); // Bloque de código cuyo tiempo de ejecución quieres medir
        auto end_3 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_3 = end_3 - start_3;// Calcula la duración en milisegundos
        t_fact.push_back(duration_3.count());
        cout<< "a" << endl;

        // PD
        map<pair<int, vector<int>>, int> dp;
        auto start_4 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_pd = llenar_maquinas_pd(beneficios.size(), maquinas, pesos, beneficios, dp); // Bloque de código cuyo tiempo de ejecución quieres medir
        best_solution = reconstruir(dp, beneficios.size(), maquinas, pesos, beneficios);
        auto end_4 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_4 = end_4 - start_4;// Calcula la duración en milisegundos
        t_pd.push_back(duration_4.count());
        dp.clear();

        best_solution.clear();
        cout<< "all done" << endl;
    }

    std::ofstream archivo("todos_entran_somewhere_5.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo!" << std::endl;
        return 1;
    }
    archivo << "FB,FACT,OPT,PD\n";
    for (int i = 0 ; i < 10 ; i++){
        archivo << t_fb[i] << "," << t_fact[i] << "," << t_opt[i] << "," << t_pd[i] << "\n";
    }
    archivo.close();

    return 0;
}