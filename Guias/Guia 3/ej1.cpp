#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int max(int a, int b){
    if (a > b){
        return a;
    }else{
        return b;
    }
}

template <typename T>
void print_list(vector<T> v){
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
}

void print_matrix(vector<vector<int>> m){
    for (auto i : m){
        print_list(i);
    }
}

vector<int> BFS(vector<vector<int>> aristas, int nodo, vector<int> & estados, int componente){
    vector<int> rv;
    queue<int> q;
    estados[nodo] = 0;
    q.push(nodo);
    while(q.size() != 0){
        int v = q.front();
        for (auto vecino : aristas[v]){
            if (estados[vecino] == -1){
                estados[vecino] = 0;
                q.push(vecino);
            }
        }
        estados[v] = componente;
        q.pop();
    }
    for (int i = 0; i < estados.size(); i++){
        if (estados[i] == componente){
            rv.push_back(i);
        }
    }
    return rv;
}

vector<vector<int>> componentes_conexas(vector<vector<int>> aristas, vector<int> nodos){
    vector<int> estados(nodos.size(), -1);
    vector<vector<int>> componentes;
    int componente = 1;
    for (auto nodo : nodos){
        if (estados[nodo] == -1){
            componentes.push_back(BFS(aristas, nodo, estados, componente));
        }
        componente++;
    }
    return componentes;
}

int main(){
    vector<vector<int>> aristas = {{1, 2}, {0, 2}, {0, 1}, {4}, {3}};
    vector<int> nodos = {0, 1, 2, 3, 4};
    vector<vector<int>> componentes = componentes_conexas(aristas, nodos);
    print_matrix(componentes);

    return 0;
}