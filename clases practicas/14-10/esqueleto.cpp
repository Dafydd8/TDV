#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
using namespace std;

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

class Grafo
{
private:
    int vertices;
   

    int maximoFlujoPorCamino(vector<int> &camino, vector<vector<int>> &grafoResidual)
    {   
        int rv = 1e9;
        for (int nodo = 0; nodo < camino.size()-1; nodo++){
            int nodo1 = camino[nodo];
            int nodo2 = camino[nodo+1];
            rv = min(rv, grafoResidual[nodo1][nodo2]);
        }
        return rv;
    }

    void actualizarGrafoResidual(int aumento, vector<int> &camino, vector<vector<int>> &grafoResidual){
        for (int k=0; k<camino.size()-1; k++){
            int i = camino[k];
            int j = camino[k+1];
            grafoResidual[i][j] -= aumento;
            grafoResidual[j][i] += aumento;
        }
    }

    vector<int> obtenerCaminoDePadres(int fuente, int sumidero, vector<int> &padre){
        vector<int> camino;
        int actual = sumidero;
        while(actual != fuente){
            camino.push_back(actual);
            actual = padre[actual];
        }
        camino.push_back(fuente);
        reverse(camino.begin(), camino.end());
        return camino;
    }

public:
	vector<vector<int>> capacidad;
    Grafo(int n) : vertices(n)
    {
        capacidad.resize(n, vector<int>(n, 0));
    }

    void agregarArco(int u, int v, int cap)
    {
        capacidad[u][v] = cap;
    }

    bool bfs(int fuente, int sumidero, vector<int> &padre, vector <vector <int>> &grafoResidual)
    {
        // Esta funcion debe modificar el vector padres y devolver si existe un camino de aumento de la fuente al sumidero.
        // En el vector padres, en la posicion i deben guardar quien descubrio al nodo i. En el caso de la fuente es -1.
        fill(padre.begin(), padre.end(), -1);

        vector<int> estado(grafoResidual.size(), -1);
        estado[fuente] = 0;
        queue<int> l;
        l.push(fuente);
        while(l.size() > 0){
            int v = l.front();
            for (int w = 0; w < grafoResidual.size(); w++){
                if (estado[w] == -1 && grafoResidual[v][w] > 0){
                    estado[w] = 0;
                    padre[w] = v;
                    l.push(w);
                }
            }
            estado[v] = 1;
            l.pop();
        }
        return estado[sumidero] != -1;
    }

    int fordFulkerson(int fuente, int sumidero)
    {
        int flujo = 0;
        vector<vector<int>> grafoResidual = capacidad;
        vector<int> padre(vertices, -1);
        while (bfs(fuente, sumidero, padre, grafoResidual))
        {
            vector<int> camino = obtenerCaminoDePadres(fuente, sumidero, padre);
            int aumento = maximoFlujoPorCamino(camino, grafoResidual);
            actualizarGrafoResidual(aumento, camino, grafoResidual);

            // Actualizar flujo
            flujo += aumento;

        }
        return flujo;
    }
};

void testBFSSimple()
{
	cout<<"Test BFS simple"<<endl;
    Grafo g(4);
    g.agregarArco(0, 1, 1);
    g.agregarArco(1, 2, 1);
    g.agregarArco(2, 3, 1);

    vector<int> parent(4, -1);
    vector<int> expected = {-1, 0, 1, 2};
    bool found = g.bfs(0, 3, parent,g.capacidad);
    assert(found);
    assert(parent == expected);
    cout<<"Paso!"<<endl;
}

void testBFSConCiclo()
{
	cout<<"Test BFS con ciclo"<<endl;
    Grafo g(4);
    g.agregarArco(0, 1, 1);
    g.agregarArco(1, 2, 1);
    g.agregarArco(2, 3, 1);
    g.agregarArco(3, 2, 1);
    g.agregarArco(2, 1, 1);
    vector<int> parent(4, -1);
    vector<int> expected = {-1, 0, 1, 2};
    bool found = g.bfs(0, 3, parent,g.capacidad);
    assert(found);
    assert(parent == expected);
    cout<<"Paso!"<<endl;
}

void testBFSDisconexo()
{
	cout<<"Test BFS disconexo"<<endl;
    Grafo g(4);
    vector<int> parent(4, -1);
    bool found = g.bfs(0, 3, parent, g.capacidad);
    assert(!found);
    cout<<"Paso!"<<endl;
}

void testFordFulkersonComplejo()
{
	cout<<"Test Ford Fulkerson complejo"<<endl;
    Grafo g(6);
    g.agregarArco(0, 1, 16);
    g.agregarArco(0, 2, 13);
    g.agregarArco(1, 2, 10);
    g.agregarArco(1, 3, 12);
    g.agregarArco(2, 1, 4);
    g.agregarArco(2, 4, 14);
    g.agregarArco(3, 2, 9);
    g.agregarArco(3, 5, 20);
    g.agregarArco(4, 3, 7);
    g.agregarArco(4, 5, 4);

    int maxFlow = g.fordFulkerson(0, 5);
    assert(maxFlow == 23);
    cout << "Paso! Flujo = " << maxFlow << endl;
}

void testFordFulkersonSimple(){
	cout<<"Test Ford Fulkerson simple"<<endl;
	Grafo g(2);
    g.agregarArco(0, 1, 10);
    int maxFlow = g.fordFulkerson(0, 1);
    assert(maxFlow == 10);
    cout << "Paso! Flujo = " << maxFlow << endl;
}

void testFordFulkersonDisconexo(){
	cout<<"Test Ford Fulkerson disconexo"<<endl;
	Grafo g(3);
    g.agregarArco(0, 1, 10);
    int maxFlow = g.fordFulkerson(0, 2);
    assert(maxFlow == 0); 
    cout << "Paso! Flujo = " << maxFlow << endl;
}

int main()
{
    testBFSSimple();
    testBFSConCiclo();
    testBFSDisconexo();
    testFordFulkersonSimple();
    testFordFulkersonDisconexo();
    testFordFulkersonComplejo();
    return 0;
}
