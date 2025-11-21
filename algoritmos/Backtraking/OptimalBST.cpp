#include <bits/stdc++.h>
using namespace std;

/**
 * Clase para representar un nodo del árbol
 */
template<typename KeyType>
struct TreeNode {
    KeyType key;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(KeyType k) : key(k), left(nullptr), right(nullptr) {}
};

/**
 * Clase genérica para resolver el problema de Optimal Binary Search Tree (OBST)
 * usando Programación Dinámica
 */
template<typename KeyType = string, typename FreqType = double>
class OptimalBST {
private:
    struct Item {
        KeyType key;
        FreqType freq;
        int id;
        
        Item(KeyType k, FreqType f, int i) : key(k), freq(f), id(i) {}
    };
    
    vector<Item> items;
    int n;  // Número de claves
    
    // Tablas de programación dinámica
    vector<vector<FreqType>> cost;  // cost[i][j] = costo óptimo para claves i..j
    vector<vector<int>> root;       // root[i][j] = raíz óptima para claves i..j
    vector<vector<FreqType>> freq_sum;  // Sumas precalculadas de frecuencias
    
public:
    /**
     * Constructor
     */
    OptimalBST() : n(0) {}
    
    /**
     * Agrega una clave con su frecuencia
     * @param key La clave a agregar
     * @param freq Frecuencia de búsqueda (probabilidad)
     */
    void addKey(KeyType key, FreqType freq) {
        items.push_back(Item(key, freq, n));
        n++;
    }
    
    /**
     * Calcula el costo óptimo y construye las tablas DP
     * @return El costo mínimo del árbol óptimo
     */
    FreqType solve() {
        if (n == 0) return 0;
        
        // Inicializar tablas (1-indexed para facilitar la implementación)
        cost.assign(n + 2, vector<FreqType>(n + 2, 0));
        root.assign(n + 2, vector<int>(n + 2, 0));
        freq_sum.assign(n + 2, vector<FreqType>(n + 2, 0));
        
        // Precalcular sumas de frecuencias
        precalculateFreqSums();
        
        // Casos base: subproblemas de tamaño 1
        for (int i = 1; i <= n; i++) {
            cost[i][i] = items[i-1].freq;
            root[i][i] = i;
        }
        
        // Llenar la tabla por tamaño de subproblema
        for (int s = 1; s < n; s++) {  // s = j - i (tamaño - 1)
            for (int i = 1; i <= n - s; i++) {
                int j = i + s;
                cost[i][j] = numeric_limits<FreqType>::max();
                
                // Probar cada posible raíz r en el rango [i, j]
                for (int r = i; r <= j; r++) {
                    // Costo = suma de frecuencias + costo subárbol izq + costo subárbol der
                    FreqType c = freq_sum[i][j] + 
                                 cost[i][r-1] + 
                                 cost[r+1][j];
                    
                    if (c < cost[i][j]) {
                        cost[i][j] = c;
                        root[i][j] = r;
                    }
                }
            }
        }
        
        return cost[1][n];
    }
    
private:
    /**
     * Precalcula las sumas de frecuencias para todos los rangos
     * Optimización: reduce el cálculo de suma de O(n) a O(1)
     */
    void precalculateFreqSums() {
        // Casos base: rangos de tamaño 1
        for (int i = 1; i <= n; i++) {
            freq_sum[i][i] = items[i-1].freq;
        }
        
        // Rangos más grandes
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                freq_sum[i][j] = freq_sum[i][j-1] + items[j-1].freq;
            }
        }
    }
    
public:
    /**
     * Construye el árbol óptimo a partir de las tablas DP
     * @return Puntero a la raíz del árbol construido
     */
    TreeNode<KeyType>* buildTree() {
        if (n == 0 || cost.empty()) {
            cout << "⚠️  Primero debes ejecutar solve()!\n";
            return nullptr;
        }
        return buildTreeHelper(1, n);
    }
    
private:
    /**
     * Función auxiliar recursiva para construir el árbol
     */
    TreeNode<KeyType>* buildTreeHelper(int i, int j) {
        if (i > j) return nullptr;
        
        int r = root[i][j];
        TreeNode<KeyType>* node = new TreeNode<KeyType>(items[r-1].key);
        
        node->left = buildTreeHelper(i, r - 1);
        node->right = buildTreeHelper(r + 1, j);
        
        return node;
    }
    
public:
    /**
     * Imprime el árbol en formato visual
     */
    void printTree(TreeNode<KeyType>* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr) return;
        
        cout << prefix;
        cout << (isLeft ? "├── " : "└── ");
        cout << node->key << "\n";
        
        if (node->left != nullptr || node->right != nullptr) {
            if (node->left != nullptr) {
                printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
            } else {
                cout << prefix + (isLeft ? "│   " : "    ") << "├── [null]\n";
            }
            
            if (node->right != nullptr) {
                printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
            } else {
                cout << prefix + (isLeft ? "│   " : "    ") << "└── [null]\n";
            }
        }
    }
    
    /**
     * Imprime las claves y frecuencias
     */
    void printKeys() {
        cout << "\nClaves y Frecuencias:\n";
        cout << "─────────────────────\n";
        for (int i = 0; i < n; i++) {
            cout << "  " << items[i].key << ": " 
                 << fixed << setprecision(2) << items[i].freq << "\n";
        }
    }
    
    /**
     * Imprime la tabla de costos
     */
    void printCostTable() {
        if (cost.empty()) {
            cout << "⚠️  Primero debes ejecutar solve()!\n";
            return;
        }
        
        cout << "\nTabla de Costos (cost[i][j]):\n";
        cout << "      ";
        for (int j = 1; j <= n; j++) {
            cout << setw(8) << j;
        }
        cout << "\n";
        
        for (int i = 1; i <= n; i++) {
            cout << setw(4) << i << "  ";
            for (int j = 1; j <= n; j++) {
                if (i <= j) {
                    cout << setw(8) << fixed << setprecision(2) << cost[i][j];
                } else {
                    cout << setw(8) << "-";
                }
            }
            cout << "\n";
        }
    }
    
    /**
     * Imprime la tabla de raíces
     */
    void printRootTable() {
        if (root.empty()) {
            cout << "⚠️  Primero debes ejecutar solve()!\n";
            return;
        }
        
        cout << "\nTabla de Raíces (root[i][j]):\n";
        cout << "      ";
        for (int j = 1; j <= n; j++) {
            cout << setw(8) << j;
        }
        cout << "\n";
        
        for (int i = 1; i <= n; i++) {
            cout << setw(4) << i << "  ";
            for (int j = 1; j <= n; j++) {
                if (i <= j) {
                    cout << setw(8) << items[root[i][j]-1].key;
                } else {
                    cout << setw(8) << "-";
                }
            }
            cout << "\n";
        }
    }
    
    /**
     * Calcula el costo de búsqueda promedio de un árbol dado
     */
    FreqType calculateActualCost(TreeNode<KeyType>* node, int depth = 1) {
        if (node == nullptr) return 0;
        
        FreqType freq = 0;
        for (const auto& item : items) {
            if (item.key == node->key) {
                freq = item.freq;
                break;
            }
        }
        
        return freq * depth + 
               calculateActualCost(node->left, depth + 1) + 
               calculateActualCost(node->right, depth + 1);
    }
    
    /**
     * Imprime la solución completa
     */
    void printSolution() {
        cout << "\n========== SOLUCIÓN OBST ==========\n";
        
        printKeys();
        
        FreqType optimalCost = solve();
        cout << "\nCosto óptimo (tiempo de búsqueda ponderado): " 
             << fixed << setprecision(4) << optimalCost << "\n";
        
        printCostTable();
        printRootTable();
        
        cout << "\nÁrbol Óptimo Construido:\n";
        TreeNode<KeyType>* tree = buildTree();
        printTree(tree);
        
        FreqType actualCost = calculateActualCost(tree);
        cout << "\nVerificación del costo: " 
             << fixed << setprecision(4) << actualCost << "\n";
    }
    
    /**
     * Limpia memoria del árbol
     */
    void deleteTree(TreeNode<KeyType>* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
    /**
     * Resetea el problema
     */
    void reset() {
        items.clear();
        cost.clear();
        root.clear();
        freq_sum.clear();
        n = 0;
    }
};

void example() {
    OptimalBST<string, double> obst;
    obst.addKey("A", 0.2);
    obst.addKey("B", 0.3);
    obst.addKey("C", 0.5);
    
    obst.printSolution();
    cout << "\n";
}

int main() {
    example();
    return 0;
}