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
        {0,1,1},
        {0,2,3},
        {1,2,6},
        {1,4,7},
        {1,5,5},
        {2,3,1},
        {2,4,4},
        {3,4,9},
        {4,5,8},
        {4,6,6},
        {4,7,12},
        {5,6,7},
        {6,7,2}
    };

    vector<Edge> mst = kruskal(n, edges);

    cout << "Aristas del MST:\n";
    for(auto &e : mst)
        cout << e.u << " - " << e.v << "  peso = " << e.w << "\n";
}
