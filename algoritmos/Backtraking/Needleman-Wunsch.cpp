#include <bits/stdc++.h>
using namespace std;

/**
 * Clase genérica para resolver el problema de Alineamiento de Secuencias
 * usando el algoritmo Needleman-Wunsch con Programación Dinámica
 */
template<typename T>
class SequenceAlignment {
private:
    vector<T> X, Y;  // Secuencias a alinear
    int m, n;        // Tamaños de las secuencias
    vector<vector<int>> dp;  // Tabla de programación dinámica
    
    // Función de penalización por desigualdad
    function<int(T, T)> penalty;
    int gap_penalty;  // Penalización por gap
    
public:
    /**
     * Constructor
     * @param x Primera secuencia
     * @param y Segunda secuencia
     * @param penalty_func Función que retorna la penalización entre dos elementos
     * @param gap Penalización por insertar un espacio
     */
    SequenceAlignment(const vector<T>& x, const vector<T>& y,
                     function<int(T, T)> penalty_func, int gap = 1) {
        X = x;
        Y = y;
        m = X.size();
        n = Y.size();
        penalty = penalty_func;
        gap_penalty = gap;
        
        // Inicializar tabla DP con tamaño (m+1) x (n+1)
        dp.assign(m + 1, vector<int>(n + 1, 0));
    }
    
    /**
     * Calcula el puntaje Needleman-Wunsch (mínima penalización)
     * @return El puntaje NW de las dos secuencias
     */
    int calculateNWScore() {
        // Casos base: secuencias vacías
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i * gap_penalty;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j * gap_penalty;
        }
        
        // Llenar la tabla usando la recurrencia
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // Caso 1: Alinear X[i-1] con Y[j-1]
                int match = dp[i-1][j-1] + penalty(X[i-1], Y[j-1]);
                
                // Caso 2: Alinear X[i-1] con gap
                int delete_x = dp[i-1][j] + gap_penalty;
                
                // Caso 3: Alinear Y[j-1] con gap
                int insert_y = dp[i][j-1] + gap_penalty;
                
                // Tomar el mínimo
                dp[i][j] = min({match, delete_x, insert_y});
            }
        }
        
        return dp[m][n];
    }
    
    /**
     * Reconstruye el alineamiento óptimo usando backtracking
     * @return Par de vectores con las secuencias alineadas (con -1 para gaps)
     */
    pair<vector<T>, vector<T>> reconstructAlignment() {
        vector<T> alignedX, alignedY;
        int i = m, j = n;
        
        // Backtracking desde dp[m][n] hasta dp[0][0]
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && 
                dp[i][j] == dp[i-1][j-1] + penalty(X[i-1], Y[j-1])) {
                // Caso 1: Se alinearon X[i-1] con Y[j-1]
                alignedX.push_back(X[i-1]);
                alignedY.push_back(Y[j-1]);
                i--;
                j--;
            }
            else if (i > 0 && dp[i][j] == dp[i-1][j] + gap_penalty) {
                // Caso 2: X[i-1] se alineó con gap
                alignedX.push_back(X[i-1]);
                alignedY.push_back(T(-1));  // -1 representa gap
                i--;
            }
            else {
                // Caso 3: Y[j-1] se alineó con gap
                alignedX.push_back(T(-1));  // -1 representa gap
                alignedY.push_back(Y[j-1]);
                j--;
            }
        }
        
        // Invertir porque construimos de atrás hacia adelante
        reverse(alignedX.begin(), alignedX.end());
        reverse(alignedY.begin(), alignedY.end());
        
        return {alignedX, alignedY};
    }
    
    /**
     * Imprime la tabla de programación dinámica (útil para debug)
     */
    void printDPTable() {
        cout << "Tabla DP:\n    ";
        for (int j = 0; j < n; j++) {
            cout << Y[j] << "  ";
        }
        cout << "\n";
        
        for (int i = 0; i <= m; i++) {
            if (i > 0) cout << X[i-1] << " ";
            else cout << "  ";
            
            for (int j = 0; j <= n; j++) {
                cout << dp[i][j] << "  ";
            }
            cout << "\n";
        }
    }
};

void example() {
    string s1 = "AGTACG";
    string s2 = "ACATAG";
    
    vector<char> X(s1.begin(), s1.end());
    vector<char> Y(s2.begin(), s2.end());
    
    // Función de penalización: 0 si son iguales, 2 si son diferentes
    auto penalty_func = [](char a, char b) {
        return (a == b) ? 0 : 2;
    };
    
    SequenceAlignment<char> aligner(X, Y, penalty_func, 1);
    
    int score = aligner.calculateNWScore();
    cout << "Puntaje NW: " << score << "\n\n";
    
    aligner.printDPTable();
    
    auto [alignedX, alignedY] = aligner.reconstructAlignment();
    
    cout << "\nAlineamiento óptimo:\n";
    for (char c : alignedX) {
        if (c == char(-1)) cout << "- ";
        else cout << c << " ";
    }
    cout << "\n";
    for (char c : alignedY) {
        if (c == char(-1)) cout << "- ";
        else cout << c << " ";
    }
    cout << "\n\n";
}

int main() {
    example();
    return 0;
}