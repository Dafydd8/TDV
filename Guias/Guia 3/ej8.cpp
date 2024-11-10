#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <queue>

using namespace std;

/*FUNCIONES AUXILIARES*/
void print_dict(map<pair<int,int>, vector<vector<int>>> aristas){
    for (const auto& [clave, valor] : aristas){
        cout << "("<< clave.first << ", " << clave.second << "): " << endl;
        for (auto elem : valor){
            cout << "{" << elem[0] << ", " << elem[1] << ", " << elem[2] << "}" << endl;
        }
    }
}

int min(vector<int> v){
    if (v.size() == 0){
        return 0;
    }
    int rv = 1e9;
    for (auto n : v){
        if (n <= rv){
            rv = n;
        }
    }
    return rv;
}

map<pair<int,int>, vector<vector<int>>> armar_grafo(vector<int> monedas, int objetivo){
    map<pair<int,int>, vector<vector<int>>> aristas;
    queue<pair<int,int>> nodos_actuales;
    nodos_actuales.push(make_pair(0,0));
    queue<pair<int,int>> siguientes;
    int fila = 0;
    int columna = 0;
    int k = objetivo / min(monedas);
    while(nodos_actuales.size() != 0){
        pair<int,int> s = nodos_actuales.front();
        nodos_actuales.pop();
        aristas[s] = {};
        int fila = s.first;
        int columna = s.second;
        if (fila == objetivo && columna == k){
            break;
        }
        if (fila == objetivo){
            siguientes.push(make_pair(fila, columna+1));
            aristas[s].push_back({fila, columna+1, 0});
        }else{
            for (auto moneda : monedas){
                if (moneda + fila <= objetivo){
                    siguientes.push(make_pair(fila+moneda, columna+1));
                    aristas[s].push_back({fila+moneda, columna+1, 1});
                }
            }
        }
        if (nodos_actuales.size() == 0){
            nodos_actuales = siguientes;
            siguientes = {};
        }
    }
    
    return aristas;
}

/*FUNCION PRINCIPAL*/
int vuelto(vector<int> monedas, int objetivo){
    map<pair<int,int>, vector<vector<int>>> aristas = armar_grafo(monedas, objetivo); //armar el grafo
    pair<int,int> s = {0,0}; //nodo de inicio
    pair<int,int> t = {objetivo, k}; //nodo final
    int k = objetivo / min(monedas); //cantidad de monedas máxima que puedo usar

    //INICIALIZAR DISTANCIAS Y VISITADOS
    map<pair<int,int>, int> distancias; 
    map<pair<int,int>, bool> visitados;
    for (const auto& [clave, valor] : aristas){ //O(m)
        distancias[clave] = 1e9;
        visitados[clave] = false;
    }
    distancias[s] = 0;
    visitados[s] = true;

    //DIJKSTRA ADAPTADO
    while(!(visitados[t])){ //n iteraciones
        int minimo = 1e9;
        //BUSCAR NODO i DE LOS NO VISITADOS CON DISTANCIA TENTATIVA MINIMA Y MARCARLO VISITADO
        pair<int,int> i;
        for (const auto& [clave, valor] : aristas){ //m iteraciones
            if (!(visitados[clave]) && distancias[clave] < minimo){
                minimo = distancias[clave];
                i = clave;
            }
        }
        visitados[i] = true;

        //PARA CADA VECINO DE i ACTUALIZAR EL COSTO A SUS VECINOS
        vector<vector<int>> vecinos = aristas[i];
        for (int j = 0; j < vecinos.size(); j++){
            int peso = vecinos[j][2];
            pair<int,int> vecino = make_pair(vecinos[j][0], vecinos[j][1]);
            if (!(visitados[vecino])){
                int d = distancias[i] + peso;
                if (d < distancias[vecino]){
                    distancias[vecino] = d;
                }
            }
        }
    }
    return distancias[t];
}

int main(){
    vector<int> monedas = {1,5,12};
    int objetivo = 15;

    //TESTEAR armar_grafo()
    //map<pair<int,int>, vector<vector<int>>> aristas = armar_grafo(monedas, objetivo);
    //print_dict(aristas);

    int rta = vuelto(monedas, objetivo);
    cout << "necesito usar " << rta << " monedas" << endl;

    return 0;
}