#include <bits/stdc++.h>
using namespace std;

int knapsack(int W, vector<int> &w, vector<int> &v, int n){
    vector<vector<int>> dp(n+1, vector<int>(W+1,0));

    for(int i = 1; i <= n; i++){
        for(int cap = 0; cap <= W; cap++){
            dp[i][cap] = dp[i-1][cap]; // No tomar

            if(w[i-1] <= cap){ // Si cabe
                dp[i][cap] = max(dp[i][cap], 
                                 v[i-1] + dp[i-1][cap - w[i-1]]);}
        }
    }
    return dp[n][W];
}

vector<int> knapsackItems(int W, vector<int> &w, vector<int> &v, vector<vector<int>>& dp, int n){
    vector<int> taken;
    int cap = W;

    for(int i = n; i >= 1; i--){
        // Si el valor cambió, significa que tome el item i
        if(dp[i][cap] != dp[i-1][cap]){
            taken.push_back(i-1);   // guardamos el indice del item
            cap -= w[i-1];          // reducir capacidad restante
        }
    }

    return taken;
}

int main(){
    vector<int> w = {5,4,6};
    vector<int> v = {10,40,30};
    cout << knapsack(10, w, v, 3) << endl;
    return 0;
}