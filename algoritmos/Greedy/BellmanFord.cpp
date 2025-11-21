#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

void bellmanFord(const vector<vector<int>>& aristas, int n, int inicio, int fin) {
    vector<int> dist(n, INT_MAX);
    vector<int> pred(n, -1);
    dist[inicio] = 0;
    
    // Optimización: detener si no hay cambios
    bool cambio = true;
    for (int i = 0; i < n - 1 && cambio; i++) {
        cambio = false;
        for (const auto& e : aristas) {
            if (dist[e[0]] != INT_MAX && dist[e[0]] + e[2] < dist[e[1]]) {
                dist[e[1]] = dist[e[0]] + e[2];
                pred[e[1]] = e[0];
                cambio = true;
            }
        }
    }
    
    // Verificar ciclo negativo
    for (const auto& e : aristas) {
        if (dist[e[0]] != INT_MAX && dist[e[0]] + e[2] < dist[e[1]]) {
            cout << "\nERROR: Ciclo negativo detectado\n";
            return;
        }
    }
    
    if (dist[fin] == INT_MAX) {
        cout << "\nNo existe camino de " << inicio << " a " << fin << "\n";
        return;
    }
    
    // Reconstruir camino
    vector<int> camino;
    for (int v = fin; v != -1; v = pred[v])
        camino.push_back(v);
    
    cout << "\n==============================================\n";
    cout << "Nodo " << inicio << " -> Nodo " << fin << "\n";
    cout << "==============================================\n";
    cout << "Costo: " << dist[fin] << "\n";
    cout << "Camino: ";
    for (int i = camino.size() - 1; i >= 0; i--) {
        cout << camino[i];
        if (i > 0) cout << " -> ";
    }
    cout << "\n==============================================\n\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, inicio;
    cin >> n >> m >> inicio;
    
    vector<vector<int>> aristas;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        aristas.push_back({u, v, w});
    }
    
    vector<int> dist(n, INT_MAX);
    vector<int> pred(n, -1);
    dist[inicio] = 0;
    
    // Relajar aristas V-1 veces
    for (int i = 0; i < n - 1; i++) {
        for (const auto& e : aristas) {
            if (dist[e[0]] != INT_MAX && dist[e[0]] + e[2] < dist[e[1]]) {
                dist[e[1]] = dist[e[0]] + e[2];
                pred[e[1]] = e[0];
            }
        }
    }
    
    // Detectar ciclo negativo
    for (const auto& e : aristas) {
        if (dist[e[0]] != INT_MAX && dist[e[0]] + e[2] < dist[e[1]]) {
            cout << "\n CICLO NEGATIVO DETECTADO" << endl;
            cout << "Arista problema: " << e[0] << " -> " << e[1] << " (peso: " << e[2] << ")" << endl;
            return 0;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) {
            cout << inicio << " -> " << i << ": INF" << endl;
        } else {
            cout << inicio << " -> " << i << ": " << dist[i] << " [";
            vector<int> camino;
            for (int v = i; v != -1; v = pred[v]) camino.push_back(v);
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