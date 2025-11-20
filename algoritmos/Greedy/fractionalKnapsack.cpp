#include <bits/stdc++.h>
#include <bits/stl_algo.h>
using namespace std;

struct Item {
    double value, weight;
};

double fractionalKnapsack(double W, vector<Item> &items){
    // 1. Ordenar por ratio (value/weight)
    sort(items.begin(), items.end(), [](const Item &a, const Item &b){
        return (a.value / a.weight) > (b.value / b.weight);});

    double totalValue = 0.0;

    // 2. Llenar la mochila
    for(const auto &it : items){
        if(W == 0) break;

        // Si cabe entero
        if(it.weight <= W){
            W -= it.weight;
            totalValue += it.value;
        }
        // Tomar fracción
        else{
            double fraction = W / it.weight;
            totalValue += it.value * fraction;
            W = 0;
        }
    }

    return totalValue;
}

int main(){
    vector<Item> items = {
        {60, 10},
        {100, 20},
        {120, 30}
    };

    double W = 50;

    cout << "Valor máximo obtenido = "
         << fractionalKnapsack(W, items) << "\n";
}