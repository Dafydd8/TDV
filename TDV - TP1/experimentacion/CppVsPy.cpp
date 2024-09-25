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

int main(){/*
    vector<int> maquinas = {500,500,500,500};
    vector<int> pesos = {107, 226, 565, 195, 216, 315, 252,565, 195, 216};
    vector<int> pesos = {548, 423, 279, 744, 442}; //PESOS ALTOS
    //vector<int> pesos = {107, 226, 565, 195, 216}; //PESOS BAJOS
    vector<int> beneficios = {98, 221, 347, 459, 581}; 
    vector<int> beneficios = {617, 647, 362, 435, 243, 537, 173, 559, 428, 396};  
    vector<int> pesos = {673, 989, 588, 658, 628, 630, 369, 370, 785, 220};
*/
    vector<int> maquinas = {500,500,500,500};
    vector<int> maquinas2 = {1000,1000};
    vector<int> beneficios = {486, 535, 226, 454, 384, 741, 595, 956, 529, 713, 268, 223, 410, 335, 191, 328, 20, 322, 711, 727};  
    vector<int> pesos = {954, 314, 358, 420, 609, 305, 598, 420, 292, 153, 543, 720, 592, 372, 1002, 619, 162, 673, 415, 812};
    vector<int> s;

    vector<float> t_fb;
    vector<float> t_fact;
    vector<float> t_opt;
    vector<float> t_pd;
    vector<float> t_pd2;

    for (int i = 0 ; i < 10 ; i++){
        vector<int> best_solution;
/*
        // FB
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
*/
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

        start_4 = std::chrono::high_resolution_clock::now(); // Captura el tiempo inicial
        resultado_pd = llenar_maquinas_pd(beneficios.size(), maquinas2, pesos, beneficios, dp); // Bloque de código cuyo tiempo de ejecución quieres medir
        best_solution = reconstruir(dp, beneficios.size(), maquinas2, pesos, beneficios);
        end_4 = std::chrono::high_resolution_clock::now();// Captura el tiempo final
        duration_4 = end_4 - start_4;// Calcula la duración en milisegundos
        t_pd2.push_back(duration_4.count());
        dp.clear();

        best_solution.clear();
        cout<< "all done" << endl;
    }

    std::ofstream archivo("Cpp_PA_20.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo!" << std::endl;
        return 1;
    }
    cout << "hola" << endl;
    archivo << "4M,2M\n";
    for (int i = 0 ; i < 10 ; i++){
        archivo << t_pd[i] << "," << t_pd2[i] << "\n";
    }
    archivo.close();

    return 0;
}