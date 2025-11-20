#include <bits/stdc++.h>
using namespace std;

struct Activity {
    int s, e; // start, end
};

vector<Activity> schedule(vector<Activity> &a){
    // 1. Ordenar por tiempo de finalización
    sort(a.begin(), a.end(), [](const Activity &x, const Activity &y){return x.e < y.e;});

    vector<Activity> chosen;

    if(a.empty()) return chosen;

    // 2. Seleccionar la primera actividad
    chosen.push_back(a[0]);
    int last_end = a[0].e;

    // 3. Recorrer el resto y tomar las compatibles
    for(int i = 1; i < a.size(); i++){
        if(a[i].s >= last_end){
            chosen.push_back(a[i]);
            last_end = a[i].e;
        }
    }

    return chosen;
}


int main(){
    vector<Activity> a = {
        {1, 4},
        {3, 5},
        {0, 6},
        {5, 7},
        {3, 9},
        {5, 9},
        {6, 10},
        {8, 11},
        {8, 12},
        {2, 14},
        {12, 16}
    };

    vector<Activity> result = schedule(a);

    cout << "Actividades seleccionadas:\n";
    for(auto &act : result){
        cout << "(" << act.s << ", " << act.e << ")\n";
    }
}
