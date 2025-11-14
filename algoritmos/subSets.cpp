#include <bits/stdc++.h>
using namespace std;

void printSubSet(vector<int> subSet){
    cout << "{";
    for(int i= 0 ; i < subSet.size() ; i++){
        cout << subSet[i];
        if(i != subSet.size() - 1) cout << ", ";
    }
    cout << "}\n";
}


void getSubset(vector<int> set, vector<int> subSet, int pos, int n){

    printSubSet(subSet);
    for(int i = pos ; i < n; i++){
        subSet.push_back(set[i]);
        getSubset(set, subSet, i + 1, n);
        subSet.pop_back();

    }
}


int main(){
    int n;
    cin >> n;
    vector<int> set(n), subset;

    for(int i = 0 ; i < n ; i++){
        cin >> set[i];
    }

    getSubset(set, subset, 0, n);

    return 0;
}