#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DSU
{
    vector<int> id;
    DSU(int n)
    {
        id.resize(n);
        for (int i = 0; i < n; i++)
        {
            id[i] = i;
        }
    }

    void conectar_nodos(int v, int w)
    {
        v = representante(v);
        w = representante(w);
        if (v == w)
            return;
        id[w] = v;
    }

    bool estan_en_la_misma_componente(int v, int w)
    {
        return representante(v) == representante(w);
    }
    int representante(int v)
    {
        if (id[v] == v)
            return v;
        id[v] = representante(id[v]);
        return id[v];
    }
};
struct Arista
{
    int v, w, costo;
    bool operator<(Arista b)
    {
        return costo < b.costo;
    }
};
int distribucion_de_agua(int n, vector<int> p, vector<vector<int>> c)
{
    /*
     * n es la cantidad de casas
     * p[i] es el costo de contruir un pozo en la casa i
     * c[i][j] es el costo de construir una cañeria entre i y j
     */
    DSU conjuntos(n + 1);
    vector<Arista> aristas;

    for (int i = 0; i < n; i++)
    {
        Arista nueva_arista = {n, i, p[i]};
        aristas.push_back(nueva_arista);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Arista nueva_arista = {i, j, c[i][j]};
            aristas.push_back(nueva_arista);
        }
    }
    sort(aristas.begin(), aristas.end());

    int rv = 0;
    vector<Arista> E;
    for (int i = 0; i < aristas.size(); i++){
        if (!conjuntos.estan_en_la_misma_componente(aristas[i].v, aristas[i].w)){
            rv += aristas[i].costo;
            conjuntos.conectar_nodos(aristas[i].v, aristas[i].w);
        }
    }

    return rv;
}

int main()
{
    // Ejemplo
    cout << distribucion_de_agua(3, {1, 2, 2}, {{0, 1, 2}, {1, 0, 3}, {2, 3, 0}}) << endl;
    cout << distribucion_de_agua(3, {1, 1, 3}, {{0, 3, 2}, {3, 0, 1}, {2, 1, 0}}) << endl;
}
