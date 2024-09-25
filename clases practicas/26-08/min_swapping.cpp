#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;




int cast_to_int(vector<int>& M){
    int res=0;
    for(int i =0; i<M.size();i++){
        res+= M[M.size()-1-i] * pow(10, i) ;
    }
    return res;
}

int FB(vector<int>& A, int c){
	int m= cast_to_int(A);
    if (c == 0){
        return m;
    }else{
        for (int i = 0; i < A.size(); i++){
            for (int j = 0; j < A.size(); j++){
                swap(A[i], A[j]);
                m = min(m, FB(A, c-1));
                swap(A[i], A[j]);
            }
        }
        return m
    }

}

int BT(vector<int>& A, int c){
	int m= cast_to_int(A);
    if (c == 0){
        return m;
    }else{
        for (int i = 0; i < A.size(); i++){
            for (int j = 0; j < A.size(); j++){
                if (A[i] > A[j]){
                    swap(A[i], A[j]);
                    m = min(m, FB(A, c-1));
                    swap(A[i], A[j]);
                }
            }
        }
        return m
    }

}


int main() {
    vector<int> M;
    int k=3;
    for(int i =0; i< 9; i++){
        M.push_back(9-i);
        cout<< M[i] << "-";
    }
    cout<< endl;

    
    auto start = chrono::steady_clock::now();
    
    std::cout <<  FB (M,k)<< "\n";

    auto end = chrono::steady_clock::now();

    cout << "Elapsed time FB: "<< chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;

    start = chrono::steady_clock::now();
    
    std::cout <<  BT (M,k)<< "\n";

    end = chrono::steady_clock::now();

    cout << "Elapsed time BT: "<< chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs" << endl;
    
}