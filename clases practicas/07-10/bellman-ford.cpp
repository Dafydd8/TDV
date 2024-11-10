#include <iostream>
#include <vector>
using namespace std;

struct Arista{
	int v,w;
	int peso;
};

pair<vector<int>, bool> bellmanFord(int n, int source, vector<Arista> aristas){
	vector<int> dist(n, 1e9);
	dist[source] = 0;
	for (int i = 0; i < n-1; i++){
		vector<int> distAux = dist;
		for(auto arista : aristas){
			int u = arista.v;
			int v = arista.w;
			if(dist[u] + arista.peso < distAux[v]){
				distAux[v] = dist[u] + arista.peso;
			}
		}
		dist = distAux;
	}
	bool ciclo_negativo = false;
	for (auto arista : aristas){
		int u = arista.v;
		int v = arista.w;
		if(dist[u] + arista.peso < dist[v]){
			ciclo_negativo = true;
		}
	}
	return {dist, ciclo_negativo};
}

int main(){	
	int n = 3;
	int source = 0;
	auto [dist, tieneCiclo] = bellmanFord(n, source, {Arista{0,1,2}, Arista{0,2,3}, Arista{1,2,-3}});
	for(int i = 0; i < n; i++){
		cout<<i<<" esta a distancia "<<dist[i]<<" de "<<source<<endl;
	}
	if(tieneCiclo){
		cout<<"El grafo tiene ciclos negativos"<<endl;
	}
}
