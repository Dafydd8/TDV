#include <iostream>
#include <vector>

using namespace std;

bool coloreable(int nodo, vector<vector<int>> aristas, int color, vector<int> coloreo){
    for(auto v : (aristas[nodo])){
        if(coloreo[v] == color){
            return false;
        }
    }
    return true;
}

bool coloreo_posible(int nodo, vector<vector<int>> aristas, vector<int> colores, vector<int> & coloreo){
    if (nodo == aristas.size()){
        if (coloreo.size() > 0){
            coloreo[-1] = colores[0];
        }
        return true;
    }
    coloreo_posible(nodo+1, aristas, colores, coloreo);
    for (auto color : colores){
        if (coloreable(nodo, aristas, color, coloreo)){
            coloreo[nodo] = color;
            return true;
        }
    }
    return false;
}

int main(){
    vector<int> colores = {0,1};
    vector<vector<int>> aristas = {{1,2}, {0,2}, {0,1}};
    vector<int> coloreo = {-1,-1,-1};
    if (coloreo_posible(0, aristas, colores, coloreo)){
        cout << "Coloreo posible" << endl;
    } else {
        cout << "Coloreo imposible" << endl;
    }
    
    return 0;
}