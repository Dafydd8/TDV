#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map> 

using namespace std;

bool pesos_ok(vector<int>s,vector<int>pesos_m,vector<int>pesos_i){
    unordered_map<int, int> solucs;
    for(int i=0; i<s.size(); i++){
        solucs[s[i]] += pesos_i[i];
    }
    solucs.erase(0);

    for (const auto& par : solucs) {
        int clave = par.first;
        int valor = par.second;
        if (valor > pesos_m[clave-1]) {
            return false;
        }
    }
    return true;
}

int suma_beneficios(vector<int>s, vector<int>beneficios){
    int rv=0;
    for(int i=0; i<s.size(); i++){
        if(s[i]!=0){
            rv+= beneficios[i];
        }
    }
    return rv;
}

bool peso_ok(int maquina, vector<int> pesos_i, vector<int>s, int capacidad){
    for(int i=0; i< s.size(); i++){
        if (s[i]==maquina){
            capacidad-= pesos_i[i];
        }
    }
    return capacidad>= pesos_i[s.size()];
}

int llenar_maquinas_BT_fact(vector<int>&beneficios, vector<int>&pesos_i, vector<int>&pesos_m, vector<int>&s){
    if (s.size() == beneficios.size()){
        return suma_beneficios(s, beneficios);
    }
    else{
        vector<int> valores;
        for(int i=0; i<pesos_m.size()+1; i++){
            if (peso_ok(i,pesos_i, s, pesos_m[i-1])){
                vector<int> s_aux = s;
                s_aux.push_back(i);
                valores.push_back(llenar_maquinas_BT_fact(beneficios, pesos_i, pesos_m, s_aux));
            }
        }
        if (!valores.empty()) {
            return *max_element(valores.begin(), valores.end());
        } else {
            return 0;  
        }
    }
}