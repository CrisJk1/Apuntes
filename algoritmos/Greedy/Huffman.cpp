#include <bits/stdc++.h>
using namespace std;

// Nodo del árbol de Huffman
struct Node {
    char ch;          // carácter
    int freq;         // frecuencia
    Node *left, *right;

    Node(char c, int f, Node* l=nullptr, Node* r=nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

// Comparador para la min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;  // min-heap
    }
};

// Genera los códigos recursivamente
void buildCodes(Node* root, string code, unordered_map<char,string> &codes){
    if(!root) return;

    // Si es una hoja, asignar código
    if(!root->left && !root->right){
        codes[root->ch] = code;
        return;
    }

    buildCodes(root->left,  code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

// Función principal Huffman
unordered_map<char,string> huffman(const vector<char> &chars, const vector<int> &freq){
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Crear nodos individuales
    for(int i = 0; i < chars.size(); i++){
        pq.push(new Node(chars[i], freq[i]));
    }

    // Construir el árbol
    while(pq.size() > 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node *merged = new Node('$', left->freq + right->freq, left, right);
        pq.push(merged);
    }

    // Raíz del árbol
    Node* root = pq.top();

    // Generar códigos
    unordered_map<char,string> codes;
    buildCodes(root, "", codes);

    return codes;
}

int main(){
    vector<char> chars = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<int> freq  = {  5,   9,  12,  13,  16,  45};

    auto codes = huffman(chars, freq);

    cout << "Códigos de Huffman:\n";
    for(auto &p : codes){
        cout << p.first << ": " << p.second << "\n";
    }
}