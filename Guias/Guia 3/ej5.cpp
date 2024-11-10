#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

int inf(){  
    return std::numeric_limits<int>::max();
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

pair<int,int> BFS_dist(vector<vector<int>> & aristas, int nodo){
    vector<int> distancias(aristas.size(), -1);
    vector<int> estados(aristas.size(), -1);
    estados[nodo] = 0;
    distancias[nodo] = 0;
    int indice_max = 0;
    queue<int> q;
    q.push(nodo);
    while(q.size() != 0){ //n veces
        int v = q.front();
        for (auto vecino : aristas[v]){ //n veces
            if (estados[vecino] == -1){//O(1)
                distancias[vecino] = distancias[v] + 1; //O(1)
                if (distancias[vecino] > distancias[indice_max]){//O(1)
                    indice_max = vecino;//O(1)
                }//O(1)
                estados[vecino] = 0;//O(1)
                q.push(vecino);//O(1)
            }
        }
        estados[v] = 1;//O(1)
        q.pop();//O(1)
    }
    return make_pair(distancias[indice_max], indice_max);
}

pair<int,int> camino_max(vector<vector<int>> & aristas){
    int max_dist = 0;
    pair<int,int> camino;
    for (int i = 0; i < aristas.size(); i++){
        pair<int,int> rta = BFS_dist(aristas, i);
        if (rta.first > max_dist){
            max_dist = rta.first;
            camino = make_pair(i, rta.second);
        }
    }
    return camino;
}

int main(){
    vector<vector<int>> aristas = {{1,2},{0},{0,3},{2}};

    pair<int,int> camino = camino_max(aristas);
    cout << "a:" << camino.first << " b:" << camino.second << endl;
    
    return 0;
}