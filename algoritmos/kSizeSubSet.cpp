#include <bits/stdc++.h>
using namespace std;

void printSet(vector<int> &set, int k){
    cout << "{";
    for(int i = 0 ; i < k ; i++){
        cout << set[i];
        if(i != k-1) cout << ", ";
    }
    cout << "}\n";
}

void subSetK(vector<int> &set, vector<int> &subSet, int pos, int n, int k){
    if(subSet.size() == k){
        printSet(subSet, k);
        return;
    }

    for(int i = pos ; i < n ; i++){
        subSet.push_back(set[i]);
        subSetK(set, subSet, i + 1, n, k);
        subSet.pop_back();
    }

}

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> set(n), subSet;

    for(int i = 0 ; i < n ; i++){
        cin >> set[i];
    }
    subSetK(set, subSet, 0, n, k);

}