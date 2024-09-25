#include <iostream>
#include <vector>
#include <experimental/random>

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

int sumar(vector<int> v){
    int suma = 0;
    for (auto i : v){
        suma += i;
    }
    return suma;
}

//Primer approach, rustico
bool hay_subset(vector<int> c, int k, vector<int> solucion){
    if (c.size() == solucion.size()){
        return sumar(solucion) == k;
    }

    vector<int> solucion_con = solucion;
    solucion_con.push_back(c[solucion.size()]);
    vector<int> solucion_sin = solucion;
    solucion_sin.push_back(0);
    bool sin = hay_subset(c, k, solucion_sin);
    bool con = hay_subset(c, k, solucion_con);

    return con || sin;
}

//Segundo approach, rustico pero al menos no uso solucion 
bool hay_subset_2(vector<int> c, int k){
    if (k == 0){
        return true;
    }
    if (c.size() == 0 || k < 0){
        return false;
    }
    for (int i = 0; i < c.size(); i++){
        vector<int> aux = c;
        int elem = c[i];
        aux.erase(aux.begin()+i);
        if (hay_subset_2(aux, k-elem)){
            return true;
        }
    }
    return false;
}
//ESTA ES LA QUE MAS ME GUSTA
bool hay_subset_3(vector<int> c, int k, int index){
    if (index == 0){
        return false;
    }
    if (k == 0){
        return true;
    }
    int sin = hay_subset_3(c, k, index-1);
    int con = 0;
    if (k>=c[index-1]){
        con = hay_subset_3(c, k-c[index-1], index-1);
    }
    return con || sin;
}
//HACE hay_subset_3 PERO CON MEMOIZACION
int hay_subset_TD(vector<int> c, int k, int index, vector<vector<int>> & dp){
    if (index == 0){
        dp[index][k] = int(k == 0);
        return int(k == 0);
    }
    if (k == 0){
        dp[index][k] = 1;
        return 1;
    }
    if (dp[index][k] != -1){
        return dp[index][k];
    }
    int sin = hay_subset_TD(c, k, index-1, dp);
    int con = 0;
    if (k>=c[index-1]){
        con = hay_subset_TD(c, k-c[index-1], index-1, dp);
    }
    dp[index][k] = int(con + sin > 0);
    return dp[index][k];
}
//RECONSTRUCCION TD
vector<int> reconstruir(vector<int> c, int k, int index, vector<vector<int>> dp){
    vector<int> solucion = {};
    while(index > 0 && k > 0){
        int con = 0;
        if (k>=c[index-1]){
            con = dp[index-1][k-c[index-1]];
        }
        if (con == 1){
            solucion.push_back(c[index-1]);
            k -= c[index-1];
        }
        index--;
    }
    return solucion;
}

//OTRO APPROACH DE PD PERO BOTTOM-UP
int hay_subset_BU(int k, vector<int> c, vector<vector<int>> & dp){
    for (int i = 0; i < c.size()+1; i++){
        dp.push_back({1});
    }
    for (int i = 0; i < k; i++){
        dp[0].push_back(0);
    }
    for (int i = 1; i < c.size()+1; i++){
        int item = c[i-1];
        for (int j = 1; j < k+1; j++){
            if (j < c[i-1]){
                dp[i].push_back(dp[i-1][j]); // Si la j es menor al elemento actual, evaluo si lo podia conseguir antes
            }else{
                dp[i].push_back(dp[i-1][j] || j == item + (j-item) * (dp[i-1][j-item]));  // Si no, evaluo si lo podia conseguir antes o ahora como suma del actual mas otro anterior
            }
        }
    }
    return dp[c.size()][k];
}

// RECONSTRUCCION BU -> la misma de TD anda.

int main(){
    //Genero un c de 6 elementos random
    vector<int> c = {};
    for (int i = 0; i < 6; i ++){
        c.push_back(experimental::randint(1, 10));
    }
    cout << "c: ";
    print_list(c);

    int k = 6;
    cout << "k: " << k << endl;
    vector<int> s = {}; //esto era para primera version, nunca mas se uso
    vector<vector<int>> dp(c.size() + 1, vector<int>(k + 1, -1)); //esto es para la version TD
    vector<vector<int>> dp2; //esto es para la version BU

    int posible = hay_subset_TD(c, k, c.size(), dp);
    if (posible){
        cout << "Hay subset" << endl;
        cout << "Solucion: ";
        print_list(reconstruir(c, k, c.size(), dp));
    } else {
        cout << "No hay subset" << endl;
    }

    posible = hay_subset_BU(k, c, dp2);
    if (posible){
        cout << "Hay subset" << endl;
        cout << "Solucion: ";
        print_list(reconstruir(c, k, c.size(), dp2));
    } else {
        cout << "No hay subset" << endl;
    }

    return 0;
}