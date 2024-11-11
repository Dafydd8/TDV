#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;


int bestFit(int weight[], int n, int c)
{
    int res = 0;
    int bin_rem[n];
    for (int i = 0; i < n; i++){
        bin_rem[i] = c;
    }

    for (int j = 0; j < n; j++){
        int e = weight[j];
        int i = 0;
        int min = c+1;
        int bin_minima = 0;
        while(i < res){
            if(bin_rem[i] >= e && bin_rem[i] - e < min){
                min = bin_rem[i] - e;
                bin_minima = i;
            }
            i++;
        }
        if (min == c+1){
            bin_rem[res] -= e;
            res++;
        }else{
            bin_rem[bin_minima] -= e;
        }
    }
    
    return res;
}
 
int main()
{   
    auto start = high_resolution_clock::now();
	long long result;

    int weight[] = { 2, 5, 4, 7, 1, 3, 8 };
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required in Best Fit : "
         << bestFit(weight, n, c);

    auto stop = high_resolution_clock::now();
	auto diff = duration<double>(stop - start);
	cout << ", con tiempo: " << diff.count() << endl;
    return 0;
}