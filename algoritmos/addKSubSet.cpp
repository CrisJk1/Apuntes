#include <bits/stdc++.h>
using namespace std;

void printSubSet(vector<int> subSet){
    cout << "{";
    for (int i = 0 ; i< subSet.size() ; i++){
        cout << subSet[i];
        if(subSet[i] != subSet[subSet.size() - 1]) cout << ", ";
    }
    cout <<"}\n";
}

int addSubSet(vector<int> subSet){
    int counter = 0;
    for (int i = 0 ; i < subSet.size() ; i++){
        counter += subSet[i];
    }
    return counter;
}

void subSetK(vector<int> &set, vector<int> &subset, int pos, int k, int n){
    if(addSubSet(subset) == k){
        printSubSet(subset);
        return;
    } 

    for(int i = pos ; i < n ; i++){
        subset.push_back(set[i]);
        subSetK(set, subset, i + 1, k, n);
        subset.pop_back();
    }
}

int main(){
    int n, k;
    cin >> n >> k;
    std::vector<int> set(n), subset;

    for(int i = 0 ; i < n ; i++)
        cin >> set[i];
    
    if(addSubSet(set) < k){
        cout << "{}";
        return 0;
    }

    else if(addSubSet(set) == k){
        printSubSet(set);
        return 0;
    }
    
    subSetK(set,subset, 0, k, n);
    
}