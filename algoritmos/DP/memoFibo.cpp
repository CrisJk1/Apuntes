#include <bits/stdc++.h>
using namespace std;

vector<long long> dp(101, -1);

long long fib(int n){
    if(n <= 1) return n;
    if(dp[n] != -1) return dp[n]; // Ya calculado

    dp[n] = fib(n-1) + fib(n-2);
    return dp[n];
}

int main(){
    int n = 100;
    cout << fib(n) << endl;
    return 0;
}