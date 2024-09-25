#include <bits/stdc++.h>
using namespace std;


bool canVisitAllNodes(vector<vector<int> >& arr, int x, int n)
{
    queue<int> q;
    vector<int> visited(n, -1);

    visited[x] = 0;
    q.push(x);

    while(q.size() != 0){
        int v = q.front();
        for (int i = 0; i < arr[v].size(); i++){
            int w = arr[v][i];
            if (visited[w] == -1){
                visited[w] = 0;
                q.push(w);
            }   
        }
        visited[v] = 1;
        q.pop();
    }

    for (int i = 0; i < visited.size(); i++){
        if (visited[i] == -1){
            return false;
        }
    }

    return true;
}

// Driver code
int main()
{
    vector<vector<int> > arr
        = { { 1, 2 }, { 0, 3, 2 }, { 0, 1 }, { 1 }, {}};
    int N = 5, X = 4;

    // Function Call
    if (canVisitAllNodes(arr, X, N)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}
