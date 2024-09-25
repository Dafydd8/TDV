#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

/* FUNCIONES AUXILIARES */

template <typename T>
void print_list(vector<T> v){
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
}

template <typename T>
void print_queue(queue<T> v){
    while(v.size() > 0){
        cout << v.front() << " ";
        v.pop();
    }
    cout << endl;
}

/* FUNCIONES PRINCIPALES */

bool operaciones(const queue<int> & operandos, int objetivo, int conseguido){ //devuelve si hay una secuencia de operaciones para operandos que resulte en objetivo
    if (conseguido > objetivo){ // prescindible, pero ayuda a cortar soluciones que no van a ningun lado
        return false;
    }
    if (operandos.size() == 0){ //caso base
        return conseguido == objetivo;
    }
    queue<int> operandos2 = operandos;
    int n = operandos2.front();
    operandos2.pop();
    bool suma = operaciones(operandos2, objetivo, conseguido + n); //se cosigue sumando el actual?
    bool multiplicacion = false;
    bool potencia = false;
    if (conseguido != 0){ // siempre considero que el primer elemento se suma (tiene que aparecer en la solucion)
        multiplicacion = operaciones(operandos2, objetivo, conseguido * n); //se cosigue multiplicando el actual?
        potencia = operaciones(operandos2, objetivo, pow(conseguido, n)); //se cosigue elevando al actual?
    }
    return suma || multiplicacion || potencia;
}

// hecho con PD TD
bool operaciones_TD(const queue<int> & operandos, int objetivo, int conseguido, vector<int> & dp){ //devuelve si hay una secuencia de operaciones para operandos que resulte en objetivo
    if (conseguido > objetivo){ //este caso no es necesario en normal (aunque ayuda a cortar soluciones que no van a ningun lado), pero si en PD por accesos a indices
        return false;
    }
    if (operandos.size() == 0){ //caso base
        dp[conseguido] = conseguido == objetivo;
        return dp[conseguido];
    }
    if(dp[conseguido] != -1){ //ya lo calcule
        return dp[conseguido];
    }
    queue<int> operandos2 = operandos;
    int n = operandos2.front();
    operandos2.pop();
    bool suma = operaciones_TD(operandos2, objetivo, conseguido + n, dp); //se cosigue sumando el actual?
    bool multiplicacion = false;
    bool potencia = false;
    if (conseguido != 0){ // siempre considero que el primer elemento se suma (tiene que aparecer en la solucion)
        multiplicacion = operaciones_TD(operandos2, objetivo, conseguido * n, dp); //se cosigue multiplicando el actual?
        potencia = operaciones_TD(operandos2, objetivo, pow(conseguido, n), dp); //se cosigue elevando al actual?
    }
    dp[conseguido] = suma || multiplicacion || potencia; //guardo el resultado
    return dp[conseguido];
}

// 0 es suma, 1 es multiplicacion, 2 es potencia
vector<int> reconstruccion(const queue<int> & operandos, int objetivo, int conseguido, vector<int> & dp){
    vector<int> solucion;
    queue<int> operandos2 = operandos; // para poder ir popeando los elementos
    while(conseguido != objetivo || operandos2.size() > 0){ // segunda condicion porque sino a veces le falta describir operaciones (multiplicaciones o potencias por 1 por ejemplo, o sumas con 0 finales)
        int n = operandos2.front();
        operandos2.pop();
        if (n + conseguido <= objetivo && dp[n + conseguido] == 1){
            solucion.push_back(0);
            conseguido += n;
        }else if (conseguido != 0 && n * conseguido <= objetivo && dp[n * conseguido] == 1){
            solucion.push_back(1);
            conseguido *= n;
        }else if (conseguido != 0 && pow(conseguido, n) <= objetivo && dp[pow(conseguido, n)] == 1){
            solucion.push_back(2);
            conseguido = pow(conseguido, n);
        }
    }
    solucion.erase(solucion.begin()); // siempre comienza con un 0 de la primer suma del primer elemento
    return solucion;
}

int main(){
    vector<int> nros = {3, 1, 5, 2, 1};
    queue<int> operandos;
    for (int i = 0; i < nros.size(); i++){
        operandos.push(nros[i]);
    }

    int objetivo = 31;
    vector<int> dp(objetivo+1, -1);
    bool hay_solucion = operaciones_TD(operandos, objetivo, 0, dp);
    cout << "rta recursiva: " << hay_solucion << endl;
    cout << "rta PD: " << operaciones_TD(operandos, objetivo, 0, dp) << endl;
    //cout << "dp: ";
    //print_list(dp);
    if (hay_solucion){
        print_list(reconstruccion(operandos, objetivo, 0, dp));
    }
    return 0;
}