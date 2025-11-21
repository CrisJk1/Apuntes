#include <bits/stdc++.h>
using namespace std;

struct Arista {
    int destino;
    long long peso;
};

// Par: {peso, vertice}
struct Nodo {
    long long peso;
    int vertice;
    bool operator>(const Nodo& otro) const {
        return peso > otro.peso; // Min-heap
    }
};

// Función mejorada de Prim con inicio aleatorio
pair<long long, vector<pair<int, int>>> prim(int n, vector<vector<Arista>>& grafo, int inicio = -1) {
    // Si no se especifica inicio, elegir uno aleatorio
    if (inicio == -1) {
        srand(time(nullptr));
        inicio = rand() % n;
    }
    
    vector<bool> enMST(n, false);
    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;
    
    vector<pair<int, int>> aristasMST;
    vector<int> padre(n, -1);
    long long pesoTotal = 0;
    
    // Iniciar desde el vértice elegido
    pq.push({0, inicio});
    padre[inicio] = inicio;
    
    int aristas_procesadas = 0;
    
    while (!pq.empty() && aristas_procesadas < n - 1) {
        Nodo actual = pq.top();
        pq.pop();
        
        int v = actual.vertice;
        long long peso = actual.peso;
        
        if (enMST[v]) continue;
        
        // Agregar vértice al MST
        enMST[v] = true;
        pesoTotal += peso;
        
        // Guardar la arista (excepto el nodo inicial)
        if (v != inicio) {
            aristasMST.push_back({padre[v], v});
            aristas_procesadas++;
        }
        
        // Buscar vecino de menor costo no visitado
        for (const Arista& e : grafo[v]) {
            if (!enMST[e.destino]) {
                pq.push({e.peso, e.destino});
                padre[e.destino] = v;
            }
        }
    }
    
    return {pesoTotal, aristasMST};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<Arista>> grafo(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }
    
    auto [peso, aristas] = prim(n, grafo);
    cout << "Peso MST: " << peso << endl;
    cout << "Aristas:" << endl;
    for (auto [u, v] : aristas) {
        cout << u << " - " << v << endl;
    }
    
    return 0;
}