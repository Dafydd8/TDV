#include <iostream>
#include <vector>

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

bool vale_la_pena(vector<int> s, vector<int> beneficios, int & max){
    int benef_tot = 0;
    for(int i = 0; i < s.size(); i++){
        if (s[i] != 0){
            benef_tot += beneficios[i];
        }
    }
    for (int i = s.size(); i < beneficios.size(); i++){
        benef_tot += beneficios[i];
    }
    return benef_tot > max;
}

int llenar_mochila_BT_opt(vector<int> beneficios, vector<int> pesos_i, vector<int> pesos_m, vector<int> s, int & maximo){
    if (s.size() == beneficios.size()){
        if (pesos_ok(s, pesos_m, pesos_i)){
            int b = suma_beneficios(s, beneficios);
            if (b > maximo){
                maximo = b;
            }
            return b;
        }
        else{
            return 0;
        }
    }
    else{
        vector<int> valores;
        for (int i = 0; i < pesos_m.size()+1; i++){
            if (vale_la_pena(s, beneficios, maximo)){
                vector<int> s_aux = s;
                s_aux.push_back(i);
                valores.push_back(llenar_mochila_BT_opt(beneficios, pesos_i, pesos_m, s_aux, maximo));
            }
        }
        return max(valores);
    }
}