#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<set<int>> u(set<set<int>> a, set<set<int>> b){
    set<set<int>> res;
    for (auto e : a){
        res.insert(e);
    }
    for (auto e : b){
        res.insert(e);
    }
    return res;
}

set<set<int>> subconjuntos(set<int> s, set<int> act){
    set<set<int>> ret;
    if (s.size() == 0){
        ret.insert(act);
        return ret;
    }else{
        int n = *(s.begin());
        s.erase(s.begin());
        set<set<int>> a = subconjuntos(s, act);
        act.insert(n);
        set<set<int>> b = subconjuntos(s, act);
        act.erase(n);
        ret = u(a, b);
        return ret;
    }
}

int main(){
    set<int> s = {1,3,4};
    set<int> act = {};
    set<set<int>> res = subconjuntos(s, act);
    for (auto e : res){
        cout << "[";
        for (auto i :e){
            cout << i << " ";
        }
        cout << "]";   
    }

    return 0;
}



/*
def subconjuntos(s, act):
    ret = set()
    if len(s) == 0:
        ret.add(act)
        return ret
    else:
        for elem in s:
            s.remove(elem)
            a = subconjuntos(s, act)
            aux = {elem}
            b = subconjuntos(s, act | aux)
            ret = a | b
            s.add(elem)
            break
        return ret
    
s = {3,4}
act = {1}
print(subconjuntos(s, act))
*/