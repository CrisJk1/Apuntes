#include <bits/stdc++.h>
using namespace std;

void analizeSet(vector<int> set, int n){
    int totalSubSets = 1 << n;
    for (int i=0; i < totalSubSets; i++){
        cout << "{";
        //logica es esta
        for (int j= 0; j < n; j++){
            if ( i & ( 1<<j )){
                cout << set[j];
                if (j < n-1) cout << ", ";
            }
        }
        cout << "}"<< endl;
    }

}

void getSet(){
    int n;
    cin >> n;
    vector<int> set(n);
    for (int i = 0 ; i < n ; i++){
        cin >> set[i];
    }

    analizeSet(set, n);
}

int main(){
    getSet();
    return 0;
}