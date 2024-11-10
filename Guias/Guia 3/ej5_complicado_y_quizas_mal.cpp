#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int inf(){  
    return std::numeric_limits<int>::max();
}
struct distancia{
    int a;
    int b;
    int dist = 0;
};

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

//aristas es un vector de de vectores que contienen <nodo vecino, peso de la arista>
distancia* BFS_dist(const vector<vector<pair<int, int>>> & aristas, int nodo){
    distancia* max_dist = new distancia();
    max_dist->a = nodo;
    max_dist->dist = 0;
    vector<distancia*> distancias(aristas.size());
    for (int i = 0; i < aristas.size(); i++){
        distancias[i] = new distancia();
    }
    vector<int> estados(aristas.size(), -1);
    estados[nodo] = 0;

    queue<int> q;
    q.push(nodo);

    while(q.size() != 0){
        int v = q.front();
        for (auto vecino : aristas[v]){
            int w = vecino.first;
            if (estados[w] == -1){
                int peso = vecino.second;
                int dist = distancias[v]->dist + peso;
                if (dist > max_dist->dist){
                    max_dist->dist = dist;
                    max_dist->b = w;
                }
                distancias[w]->dist = dist;
                estados[w] = 0;
                q.push(w);
            }
        }
        estados[v] = 1;
        q.pop();
    }
    return max_dist;
}

distancia* camino_max(const vector<vector<pair<int, int>>> & aristas){
    distancia* camino_max = nullptr;
    for (int i = 0; i < aristas.size(); i++){
        distancia* nuevo = BFS_dist(aristas, i);
        if (camino_max == nullptr || nuevo->dist > camino_max->dist){
            camino_max = nuevo;
        }
    }
    return camino_max;
}



int main() {
    // Valor grande que se usa como "infinito" para enteros
    vector<vector<pair<int,int>>> aristas = {{{1, 1}, {2, 1}}, {{0, 1},{3, 1}}, {{0, 1}}, {{1,1}}};
    distancia* dist = BFS_dist(aristas, 1);
    cout << "a:" << dist->a << " b:" << dist->b << " dist:" << dist->dist << endl;

    distancia* camino = camino_max(aristas);
    cout << "a:" << camino->a << " b:" << camino->b << " dist:" << camino->dist << endl;

    return 0;
}