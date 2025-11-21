#include <bits/stdc++.h>
using namespace std;

void printPerm(vector<int> perm, int n){
    cout << "{";
    for (int i = 0 ; i < n ; i++){
        cout << perm[i];
        if(i != n-1) cout << ", ";
    }
    cout << "}\n";
}

void permutation(vector<int> set, vector<int> perm,  int n){
    if(perm.size() == n){
        printPerm(perm, n);
        return;
    }
    
    for(int i = 0 ; i < n ; i++){

        if(find(perm.begin(), perm.end(), set[i]) == perm.end()){
            perm.push_back(set[i]);
            permutation(set, perm, n);
            perm.pop_back();
        }
    }

}

int main(){
    int n;
    cin >> n;
    vector<int> set(n), perm, sol;

    for(int i = 0 ; i < n ; i++){
        cin >> set[i];
    }

    permutation(set, perm,n);

    return 0;
}