#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

// TSP Held-Karp: dp[mask][i]
long long tsp_held_karp(const vector<vector<long long>>& dist) {
    int n = dist.size();
    int N = 1 << n;

    vector<vector<long long>> dp(N, vector<long long>(n, INF));

    // Caso base: iniciar en ciudad 0
    dp[1][0] = 0; // mask = 1<<0 = 1

    // DP sobre subconjuntos
    for (int mask = 1; mask < N; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue; // u no está en el subconjunto

            long long curr = dp[mask][u];
            if (curr == INF) continue;

            // Intentar ir a un nuevo nodo v
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue; // v ya está visitado

                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], curr + dist[u][v]);
            }
        }
    }

    // Cerrar el ciclo volviendo a 0
    long long ans = INF;
    int fullMask = N - 1;

    for (int u = 1; u < n; u++) {
        ans = min(ans, dp[fullMask][u] + dist[u][0]);
    }

    return ans;
}

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> dist(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    cout << "Costo mínimo del tour: " << tsp_held_karp(dist) << "\n";
}
