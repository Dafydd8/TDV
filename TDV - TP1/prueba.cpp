#include <vector>
#include <map>
#include <tuple>
#include <iostream>

using namespace std;

int max(vector<int> v){
    int rv = v[0];
    for (int i = 0; i < v.size(); i++){
        if (v[i] > rv){
            rv = v[i];
        }
    }
    return rv;
}

void suma(int & carlos){
    carlos += 1;
}

void invertir(vector<int> & v){
    vector<int> aux;
    for (int i = v.size()-1; i >= 0; i--){
        aux.push_back(v[i]);
    }
    v = aux;
}

using namespace std;
int main(){
    vector<int> v = {1,2,3,4,5};
    invertir(v);
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;

    vector<int> s = {1,6,2,3};
    vector<int> a = s;
    a.push_back(4);
    cout << max(a) << endl;

    map<int, int> m;
    m[1] += 1;

    cout << m[1] << endl;

    int carlos = 0;
    suma(carlos);
    cout << carlos << endl;

    tuple<int,int,int> t = {1,2,3};

    map<vector<int>, int> mapa;

    mapa[{1,2,3}] = 1;
    
    cout << mapa[{1,2,3}] << endl;
    
    return 0;
}
