#include <iostream>
#include <vector>
#include <experimental/random>

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

int max_benef_TD(int k, vector<int> longitudes, vector<int> beneficios, vector<int> & dp){
    if (k == 0){
        return 0;
    }
    if (dp[k] != -1){
        return dp[k];
    }
    for (int i = 0; i < longitudes.size(); i++){
        if (longitudes[i] <= k){
            dp[k] = max(dp[k], beneficios[i] + max_benef_TD(k-longitudes[i], longitudes, beneficios, dp));
        }
    }
    if (dp[k] == -1){
        dp[k] = 0;
        return 0;
    }
    return dp[k];
}

vector<int> reconstruir(int k, vector<int> longitudes, vector<int> beneficios, vector<int> dp){
    vector<int> solucion;
    while(k > 0){
        int m = 0;
        int best_lng = -1;
        for (int lng = 0; lng < beneficios.size(); lng++){
            if (longitudes[lng] <= k){
                if (m <= beneficios[lng] + dp[k-longitudes[lng]]){
                    m = beneficios[lng] + dp[k-longitudes[lng]];
                    best_lng = longitudes[lng];
                }
            }
        }
        k-= best_lng;
        solucion.push_back(best_lng);
    }
    return solucion;
}



int max_benef_BU(int k, vector<int> longitudes, vector<int> beneficios, vector<int> & dp){
    dp.push_back(0);
    for (int c = 1; c < k+1; c++){
        int m = -1;
        for (int item = 0; item < longitudes.size(); item++){
            if (longitudes[item] <= c){
                m = max(m, beneficios[item] + dp[c-longitudes[item]]);
            }
        }
        if (m == -1){
            dp.push_back(0);
        }else{
            dp.push_back(m);
        }
    }
    return dp[k];
}


int main(){
    vector<int> longitudes = {2, 3, 5};
    vector<int> beneficios = {80,140,170};
    int k = 22;
    vector<int> dp (k+1, -1);
    vector<int> dp2;

    cout << max_benef_TD(k, longitudes, beneficios, dp) << endl;
    cout << max_benef_BU(k,longitudes, beneficios, dp2) << endl;
    print_list(reconstruir(k, longitudes, beneficios, dp));
    print_list(reconstruir(k, longitudes, beneficios, dp2));

    dp.clear();
    dp2.clear();
    return 0;
}