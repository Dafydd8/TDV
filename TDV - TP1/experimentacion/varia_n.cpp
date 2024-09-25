#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "funciones.h"
#include <chrono>
using namespace std;

vector<int> copia_hasta(vector<int> v, int i){
    vector<int> rv;
    for (int j = 0 ; j < i ; j++){
        rv.push_back(v[j]);
    }
    return rv;
}

int main(){
    vector<int> maquinas = {500,500,500,500};
    vector<int> pesos = {107, 226, 565, 195, 216, 315, 252,565, 195, 216};
    vector<int> beneficios = {98, 221, 347, 459, 581, 718, 903, 98, 221, 347};   
    vector<int> s;

    vector<float> t_fb;
    vector<float> t_fact;
    vector<float> t_opt;
    vector<float> t_pd;

    for (int i = 0 ; i < 10 ; i++){
        vector<int> pesos_aux = copia_hasta(pesos, i+1);
        vector<int> beneficios_aux = copia_hasta(beneficios, i+1);

        // FB
        vector<int> best_solution;
        auto start_1 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_fb = llenar_maquinas_FB(beneficios_aux, pesos_aux, maquinas, s, best_solution); // Bloque de código cuyo tiempo de ejecución quieres medir
        auto end_1 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_1 = end_1 - start_1;// Calcula la duración en milisegundos
        t_fb.push_back(duration_1.count());

        // OPT
        best_solution = {};
        int maximo = 0;
        auto start_2 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_opt = llenar_maquinas_BT_opt(beneficios_aux, pesos_aux, maquinas, s, maximo, best_solution); // Bloque de código cuyo tiempo de ejecución quieres medir
        auto end_2 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_2 = end_2 - start_2;// Calcula la duración en milisegundos
        t_opt.push_back(duration_2.count());

        // FACT
        best_solution = {};
        auto start_3 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_fact = llenar_maquinas_BT_fact(beneficios_aux, pesos_aux, maquinas, s, best_solution); // Bloque de código cuyo tiempo de ejecución quieres medir
        auto end_3 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_3 = end_3 - start_3;// Calcula la duración en milisegundos
        t_fact.push_back(duration_3.count());
        cout<< "a" << endl;

        // PD
        map<pair<int, vector<int>>, int> dp;
        auto start_4 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        int resultado_pd = llenar_maquinas_pd(beneficios_aux.size(), maquinas, pesos_aux, beneficios_aux, dp); // Bloque de código cuyo tiempo de ejecución quieres medir
        cout <<"hoi"<<endl;
        best_solution = reconstruir(dp, beneficios_aux.size(), maquinas, pesos_aux, beneficios_aux);
        auto end_4 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        std::chrono::duration<double, std::milli> duration_4 = end_4 - start_4;// Calcula la duración en milisegundos
        t_pd.push_back(duration_4.count());
        dp.clear();

        best_solution.clear();
        cout<< "all done" << endl;
    }

    std::ofstream archivo("varia_n_4M.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo!" << std::endl;
        return 1;
    }
    archivo << "i,FB,FACT,OPT,PD\n";
    for (int i = 0 ; i < 10 ; i++){
        archivo << i+1 << "," << t_fb[i] << "," << t_fact[i] << "," << t_opt[i] << "," << t_pd[i] << "\n";
    }
    archivo.close();

    return 0;
}