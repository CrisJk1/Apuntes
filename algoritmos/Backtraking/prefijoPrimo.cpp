#include <bits/stdc++.h>
using namespace std;

bool esPrimo(long long n) { // Complejidad O(sqrt{n})
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;
    
    for(long long i = 5; i * i <= n; i += 6) {
        if(n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int prefiprimo(){ // Enfoque backtracking
    int cnt = 0;
    for(int a = 1; a <= 9; a++){
        if(!esPrimo(a)) continue;
        for(int b = 0; b <= 9; b++){
            if(!esPrimo(10*a+b)) continue;
            for(int c = 0; c <= 9; c++){
                if(!esPrimo(100*a+10*b+c)) continue;
                cnt++;
            }
        }
    }
    return cnt;
}

int main(){
    prefiprimo();
    return 0;
}