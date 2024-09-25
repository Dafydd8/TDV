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

//BUSCA EL MEJOR PAGO POSIBLE PARA C CON LOS BILLETES DISPONIBLES (PD Bottom-Up)
int mejor_pago(vector<int> billetes, int c, vector<vector<int>> & dp){
    for (int i = 0; i < billetes.size()+1; i++){
        dp.push_back({0}); //si c = 0, mi mejor pago es 0
    }
    for (int i = 0; i < c; i++){
        dp[0].push_back(0); //si no tengo billetes, no puedo pagar, mi mejor pago es 0
    }
    for(int i = 1; i < billetes.size()+1; i++){
        int billete = billetes[i-1];
        for (int j = 1; j < c+1; j++){
            if (j <= billete){ // si el billete es mayor que lo que tengo que pagar
                if (dp[i-1][j] != 0 && dp[i-1][j] < billete){
                    dp[i].push_back(dp[i-1][j]); // si podia pagarlo antes y ese pago era mejor que usar el billete actual, usar el viejo
                }
                else{
                    dp[i].push_back(billete); // si no podia pagarlo antes o era mejor pagar con el billete actual, usar el billete actual
                }
            }else{
                int pagable = billete + dp[i-1][j-billete]; // la suma que puedo pagar con el billete actual y el mejor pago sin el billete actual
                if (pagable >= j){
                    dp[i].push_back(pagable); // si puedo pagar con pagable, usar pagable
                }else{
                    dp[i].push_back(0); // si no puedo pagar con pagable, no puedo pagar, mi mejor pago es 0
                }
            }
        }
    }
    return dp[billetes.size()][c];
}

//RECONSTRUYE LA SOLUCION A PARTIR DE LA MATRIZ DE PROGRAMACION DINAMICA
vector<int> recontruir(vector<vector<int>> dp, vector<int> billetes, int c){
    vector<int> solucion;
    int i = billetes.size();
    int j = c;
    while(i > 0 && j > 0){
        int billete = billetes[i-1];
        if (dp[i][j] < billete){
            i--; // si el mejor pago es menor que el billete actual, no se uso el billete actual
        }else if (dp[i][j] <= dp[i-1][j] || dp[i-1][j] == 0){
            j = j - billete; // sino, si el mejor pago es mejor o igual que el mejor pago sin el billete actual (si dicho pago no era 0), se uso el billete actual
            solucion.push_back(billete);
            i--;
        }
    }
    return solucion;
}

int main(){
    vector<int> billetes = {2, 3, 5, 10, 10, 20, 20};
    int c = 31;
    vector<vector<int>> dp;

    int mejor_p = mejor_pago(billetes, c, dp);
    cout << "mejor pago: " << mejor_p << endl;
    if (mejor_p == 0){
        cout << "No se puede pagar" << endl;
    }else{
        cout << "se puede pagar con: ";
        vector<int> solucion = recontruir(dp, billetes, c);
        print_list(solucion);
    }

    return 0;
}
