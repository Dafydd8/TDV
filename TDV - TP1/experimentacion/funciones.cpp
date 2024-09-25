#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map> 
#include <map> 
#include "funciones.h" 


using namespace std;

int max(vector<int> v){
    if(v.size() == 0){
        return 0;
    }
    int rv = v[0];
    for (int i = 0; i < v.size(); i++){
        if (v[i] > rv){
            rv = v[i];
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

int suma_capacidades(vector<int> capacidades){
    int rv = 0;
    for (int i = 0; i < capacidades.size(); i++){
        rv += capacidades[i];
    }
    return rv;
}

bool vale_la_pena(vector<int> s, vector<int> beneficios, int & max){
    int benef_tot = suma_beneficios(s, beneficios);

    for (int i = s.size(); i < beneficios.size(); i++){
        benef_tot += beneficios[i];
    }

    return benef_tot > max;
}

void invertir(vector<int> & v){
    vector<int> aux;
    for (int i = v.size()-1; i >= 0; i--){
        aux.push_back(v[i]);
    }
    v = aux;
}

int llenar_maquinas_FB(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, vector<int> & best_solution){
    if (s.size() == beneficios.size()){
        if (pesos_ok(s, pesos_m, pesos_i) && (suma_beneficios(s, beneficios) > suma_beneficios(best_solution, beneficios))){
            best_solution = s;
            return suma_beneficios(s, beneficios);
        }
        else{   
            return 0;
        }  
    } 
    else{
        vector<int> valores;
        for (int i = 0; i <= pesos_m.size(); i++){
            vector<int> s_aux = s;
            s_aux.push_back(i);
            int beneficio = llenar_maquinas_FB(beneficios, pesos_i, pesos_m, s_aux, best_solution);
            valores.push_back(beneficio);
        }
        return max(valores);
    }
}

int llenar_maquinas_BT_opt(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, int & maximo, vector<int> & best_solution){
    if (s.size() == beneficios.size()){
        if (pesos_ok(s, pesos_m, pesos_i)){
            int b = suma_beneficios(s, beneficios);
            if (b > maximo){
                maximo = b;
                best_solution = s;
            }
            return b;
        }
        else{
            return 0;
        }
    }
    else{
        vector<int> valores;
        if (vale_la_pena(s, beneficios, maximo)){
            for (int i = 0; i < pesos_m.size()+1; i++){
                vector<int> s_aux = s;
                s_aux.push_back(i);
                valores.push_back(llenar_maquinas_BT_opt(beneficios, pesos_i, pesos_m, s_aux, maximo, best_solution));
            }
        }
        return max(valores);
    }
}

int llenar_maquinas_BT_fact(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, vector<int> & best_solution){
    if (s.size() == beneficios.size()){
        int beneficio = suma_beneficios(s, beneficios);
        if (beneficio > suma_beneficios(best_solution, beneficios)){
            best_solution = s;
        }
        return suma_beneficios(s, beneficios);
    }
    else{
        vector<int> valores;
        for(int i=0; i<pesos_m.size()+1; i++){
            if (i == 0 || peso_ok(i, pesos_i, s, pesos_m[i-1])){
                vector<int> s_aux = s;
                s_aux.push_back(i);
                valores.push_back(llenar_maquinas_BT_fact(beneficios, pesos_i, pesos_m, s_aux, best_solution));
            }
        }
        return max(valores);
    }
}

int llenar_maquinas_pd(int item, vector<int> capacidades, vector<int>pesos, vector<int>beneficios, map<pair<int, vector<int>>, int> & dp){
    if (item == 0){
        pair<int, vector<int>>clave = make_pair(0, capacidades);
        dp[clave] = 0;
        return 0;
    }
    else{
        pair<int, vector<int>> clave;
        clave.first = item;
        clave.second = capacidades;
        if (dp.find(clave) != dp.end()){
            return dp[clave];
        }
        int sin = llenar_maquinas_pd(item-1, capacidades, pesos, beneficios,dp);
        int maximo_con = 0;
        for (int m = 0; m < capacidades.size(); m++){
            if (pesos[item-1] <= capacidades[m]){
                vector<int> nuevas_capacidades = capacidades;
                nuevas_capacidades[m] -= pesos[item-1];
                maximo_con = max(maximo_con, beneficios[item-1] + llenar_maquinas_pd(item-1, nuevas_capacidades, pesos, beneficios,dp));
            }
        }
        int rv = max(sin, maximo_con);
        dp[clave] = rv;
        return rv;
    }
}

vector<int> reconstruir(map<pair<int, vector<int>>, int> & dp, int i, vector<int> capacidades, vector<int>pesos, vector<int>beneficios){
    vector<int> rv;
    while(i > 0 && suma_capacidades(capacidades) > 0){
        pair<int, vector<int>> clave = make_pair(i-1, capacidades);
        if (dp[clave] == dp[make_pair(i, capacidades)]){
            i--;
            rv.push_back(0);
        }else{
            for (int m = 1; m < capacidades.size()+1; m++){
                if (pesos[i-1] <= capacidades[m-1]){
                    vector<int> nuevas_capacidades = capacidades;
                    nuevas_capacidades[m-1] -= pesos[i-1];
                    int n = beneficios[i-1] + dp[make_pair(i-1, nuevas_capacidades)];
                    if (dp[make_pair(i, capacidades)] == n){
                        capacidades = nuevas_capacidades;
                        rv.push_back(m);
                        i--;
                        break;
                    }
                }
            }
        }
    }
    while(i > 0){
        rv.push_back(0);
        i--;
    }

    invertir(rv);
    return rv;
}
