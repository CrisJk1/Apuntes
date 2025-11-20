#include <bits/stdc++.h>
using namespace std;

struct union_find{
    vector<int> e;
    union_find(int n) {e.assign(n, -1);}

    int findSet(int x) {return (e[x] < 0 ? x : e[x] = findSet(e[x]));}
    bool sameSet(int a, int b) {return findSet(a) == findSet(b);}
    bool size(int x) {return -e[findSet(x)];}

    bool unionSet(int x, int y){
        x = findSet(x), y = findSet(y);
        if(x == y) return 0;
        if(e[x] > e[y]) swap(x,y);
        e[x] += e[y], e[y] = x;
        return 1;
    }
};

struct Edge {
    int u, v, w; // origen, destino, peso
};

vector<Edge> kruskal(int n, vector<Edge> &edges){
    // 1. Ordenar aristas por peso
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){return a.w < b.w;});

    // 2. Inicializar DSU
    union_find uf(n);
    vector<Edge> T;  // MST

    // 3. Recorrer aristas en orden creciente
    for(const Edge &e : edges){
        if(uf.findSet(e.u) != uf.findSet(e.v)){
            // Conecta dos componentes distintas
            T.push_back(e);
            uf.unionSet(e.u, e.v);
        }
    }

    // 4. Retornar el árbol generador mínimo
    return T;
}

int main(){
    int n = 13;  // cantidad de vértices
    vector<Edge> edges = {
        {1,2,1},
        {1,3,3},
        {2,3,6},
        {2,5,7},
        {2,6,5},
        {3,4,1},
        {3,5,4},
        {4,5,9},
        {5,6,8},
        {5,7,6},
        {5,8,12},
        {6,7,7},
        {7,8,2}
    };

    vector<Edge> mst = kruskal(n, edges);

    cout << "Aristas del MST:\n";
    for(auto &e : mst)
        cout << e.u << " - " << e.v << "  peso = " << e.w << "\n";
}
