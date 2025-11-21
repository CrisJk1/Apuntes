#include <bits/stdc++.h>
using namespace std;

// Nodo del árbol de Huffman
struct Node {
    char c;                // símbolo (solo válido en hojas)
    int freq;              // frecuencia total del subárbol
    Node *left, *right;    // hijos

    Node(char c, int freq) : c(c), freq(freq), left(NULL), right(NULL) {}
    Node(Node* l, Node* r) : c('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

// Comparador para priority_queue (menor freq primero)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Construir el árbol de Huffman (según el pseudocódigo)
Node* buildHuffmanTree(const unordered_map<char, int> &freq) {

    priority_queue<Node*, vector<Node*>, Compare> F;

    // 1. crear un árbol Ta para cada símbolo
    for (auto &p : freq) {
        Node* Ta = new Node(p.first, p.second);
        F.push(Ta);
    }

    // 2. mientras haya al menos dos árboles
    while (F.size() > 1) {

        // T1 = el árbol con menor frecuencia
        Node* T1 = F.top(); F.pop();

        // T2 = el árbol con segunda menor frecuencia total
        Node* T2 = F.top(); F.pop();

        // Crear T3 = fusión de T1 y T2
        Node* T3 = new Node(T1, T2);

        // Insertar T3 de vuelta al conjunto F
        F.push(T3);
    }

    // 3. F contiene un único árbol
    return F.top();
}

// Generar códigos binarios desde el árbol
void generateCodes(Node* root, string code, unordered_map<char, string> &mp) {
    if (!root) return;

    // Si es hoja → asignar código
    if (!root->left && !root->right) {
        mp[root->c] = code;
    }

    generateCodes(root->left,  code + "0", mp);
    generateCodes(root->right, code + "1", mp);
}

// Codificar un mensaje usando los códigos de Huffman
string encode(const string &text, unordered_map<char,string> &codeMap) {
    string encoded;
    for (char c : text) encoded += codeMap[c];
    return encoded;
}

// Decodificar un mensaje binario usando el árbol
string decode(Node* root, const string &encoded) {
    string result;
    Node* curr = root;

    for (char bit : encoded) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        // Si llegué a una hoja
        if (!curr->left && !curr->right) {
            result += curr->c;   // agregar el símbolo
            curr = root;         // volver a la raíz
        }
    }
    return result;
}

// Ejemplo de uso
int main() {

    string text = "huffman example";

    // Contar frecuencias
    unordered_map<char,int> freq;
    for (char c : text) freq[c]++;

    // Construir árbol
    Node* root = buildHuffmanTree(freq);

    // Generar códigos
    unordered_map<char,string> codeMap;
    generateCodes(root, "", codeMap);

    cout << "Códigos Huffman:\n";
    for (auto &p : codeMap) {
        cout << p.first << " : " << p.second << "\n";
    }

    // Codificar
    string encoded = encode(text, codeMap);
    cout << "\nTexto codificado:\n" << encoded << "\n";

    // Decodificar
    string decoded = decode(root, encoded);
    cout << "\nTexto decodificado:\n" << decoded << "\n";

    return 0;
}