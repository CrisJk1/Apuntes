#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int>& reinas, 
               vector<bool>& columnas_ocupadas,
               vector<bool>& diagonal1_ocupada,
               vector<bool>& diagonal2_ocupada,
               int fila, 
               const int n, 
               int &count){
    
    // Caso base: todas las reinas colocadas
    if(fila == n){
        count++;
        return;
    }

    // Probar cada columna en la fila actual
    for(int col = 0; col < n; col++){
        int d1 = fila - col + (n - 1);  // Diagonal der
        int d2 = fila + col;             // Diagonal izq
        
        // Verificar si es seguro colocar reina aquí
        if(!columnas_ocupadas[col] && 
           !diagonal1_ocupada[d1] && 
           !diagonal2_ocupada[d2]){
            
            // ======= HACER =======
            reinas[fila] = col;
            columnas_ocupadas[col] = true;
            diagonal1_ocupada[d1] = true;
            diagonal2_ocupada[d2] = true;
            
            // ======= RECURSION =======
            backtrack(reinas, 
                     columnas_ocupadas, 
                     diagonal1_ocupada, 
                     diagonal2_ocupada, 
                     fila + 1, n, count);
            
            // ======= DESHACER =======
            columnas_ocupadas[col] = false;
            diagonal1_ocupada[d1] = false;
            diagonal2_ocupada[d2] = false;
        }
    }
}

int main(){
    int n;
    cin >> n;

    vector<int> reinas(n, -1); // Pos reina en cada fila
    vector<bool> columnas_ocupadas(n, false); // n columnas
    vector<bool> diagonal1_ocupada(2*n - 1, false); // 2n-1 diagonales izq
    vector<bool> diagonal2_ocupada(2*n - 1, false); // 2n-1 diagonales der
    
    int count = 0;
    
    backtrack(reinas, columnas_ocupadas, diagonal1_ocupada, 
             diagonal2_ocupada, 0, n, count);
    
    cout << count << endl;
    
    return 0;
}