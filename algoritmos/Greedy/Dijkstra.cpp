#include <bits/stdc++.h>
using namespace std;

struct Arista {
    int destino;
    long long peso;
};

struct Nodo {
    int vertice;
    long long distancia;
    bool operator>(const Nodo& otro) const {
        return distancia > otro.distancia;
    }
};

pair<vector<long long>, vector<int>> dijkstra(int n, vector<vector<Arista>>& grafo, int inicio) {
    vector<long long> dist(n, LLONG_MAX);
    vector<int> padre(n, -1);
    vector<bool> visitado(n, false);
    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;
    
    dist[inicio] = 0;
    pq.push({inicio, 0});
    
    while (!pq.empty()) {
        Nodo actual = pq.top();
        pq.pop();
        
        int u = actual.vertice;
        if (visitado[u]) continue;
        visitado[u] = true;
        
        for (const Arista& e : grafo[u]) {
            int v = e.destino;
            long long peso = e.peso;
            
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                padre[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }
    return {dist, padre};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, inicio;
    cin >> n >> m >> inicio;
    
    vector<vector<Arista>> grafo(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        grafo[u].push_back({v, w});
    }
    
    auto [dist, padre] = dijkstra(n, grafo, inicio);
    
    for (int i = 0; i < n; i++) {
        if (dist[i] == LLONG_MAX) {
            cout << inicio << " -> " << i << ": INF" << endl;
        } else {
            cout << inicio << " -> " << i << ": " << dist[i] << " [";
            vector<int> camino;
            for (int v = i; v != -1; v = padre[v]) camino.push_back(v);
            reverse(camino.begin(), camino.end());
            for (int j = 0; j < camino.size(); j++) {
                cout << camino[j];
                if (j < camino.size() - 1) cout << " -> ";
            }
            cout << "]" << endl;
        }
    }
    return 0;
}