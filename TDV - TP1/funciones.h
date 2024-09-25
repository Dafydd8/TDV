#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>

using namespace std;

int max(vector<int> v);
bool peso_ok(int maquina, vector<int> pesos_i, vector<int>s, int capacidad);
bool pesos_ok(vector<int>s,vector<int>pesos_m,vector<int>pesos_i);
int suma_beneficios(vector<int>s, vector<int>beneficios);
int suma_capacidades(vector<int> capacidades);
bool vale_la_pena(vector<int> s, vector<int> beneficios, int & max);
void invertir(vector<int> & v);
int llenar_maquinas_FB(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, vector<int> & best_solution);
int llenar_maquinas_BT_opt(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, int & maximo, vector<int> & best_solution);
int llenar_maquinas_BT_fact(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, vector<int> & best_solution);
int llenar_maquinas_pd(int item, vector<int> capacidades, vector<int>pesos, vector<int>beneficios, map<pair<int, vector<int>>, int> & dp);
vector<int> reconstruir(map<pair<int, vector<int>>, int> & dp, int i, vector<int> capacidades, vector<int>pesos, vector<int>beneficios);

#endif