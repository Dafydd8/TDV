#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map> 

using namespace std;


bool pesos_ok(vector<int>s,vector<int>pesos_m,vector<int>pesos_i){
    unordered_map<int, int> solucs;
    for(int i=0; i<s.size(); i++){
        if(s[i] != 0){
            solucs[s[i]] += pesos_i[i];
        }
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

int llenar_maquinas_FB(vector<int>&beneficios, vector<int>&pesos_i, vector<int>&pesos_m, vector<int>&s){

    if (s.size() == beneficios.size()){
        if pesos_ok(s, pesos_m, pesos_i){
            return suma_beneficios(s, beneficios);    
        }
        else{
            return 0;
        }

    else{
        vector<int>valores;
        for(int i=0; i<pesos_m.size()+1; i++){
            vector<int> s_aux = s;
            valores.push_back(llenar_maquinas_FB(beneficios, pesos_i, pesos_m, s_aux));
        }
        
        if (!valores.empty()) {
            return *max_element(valores.begin(), valores.end());
        } else {
            return 0;  
        }
    }
        
    }
}