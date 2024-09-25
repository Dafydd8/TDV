#include <iostream>
#include <vector>
#include <map>
#include "funciones.h"
using namespace std;

int main() {
    vector<int> maquinas = {500, 500,500,500};
    vector<int> pesos = {107, 226, 565, 195, 216, 315, 252,565, 195, 216};
    vector<int> beneficios = {98, 221, 347, 459, 581, 718, 903, 98, 221, 347};
    vector<int> s;
    int maximo = 0;
    vector<int> best_solution;
    

    int a = llenar_maquinas_FB(beneficios, pesos, maquinas, s, best_solution);
    cout << a << endl;
    for (int i = 0; i < best_solution.size(); i++){
        cout << best_solution[i] << " ";
    }
    cout << endl;
/*
    best_solution = {};
    int b = llenar_maquinas_BT_opt(beneficios, pesos, maquinas, s, maximo, best_solution);
    cout << b << endl;
    for (int i = 0; i < best_solution.size(); i++){
        cout << best_solution[i] << " ";
    }
    cout << endl;
*/
    best_solution = {};
    int c = llenar_maquinas_BT_fact(beneficios, pesos, maquinas, s, best_solution);
    cout << c << endl;
    for (int i = 0; i < best_solution.size(); i++){
        cout << best_solution[i] << " ";
    }
    cout << endl;

/*
    best_solution = {}; 
    map<pair<int, vector<int>>, int> dp;
    int d = llenar_maquinas_pd(beneficios.size(), maquinas, pesos, beneficios, dp);
    best_solution = reconstruir(dp, beneficios.size(), maquinas, pesos, beneficios);
    cout << d << endl;
    for (int i = 0; i < best_solution.size(); i++){
        cout << best_solution[i] << " ";
    }
    cout << endl;
    return 0;
*/    
}