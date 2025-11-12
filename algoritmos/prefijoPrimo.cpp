#include <bits/stdc++.h>
using namespace std;

//Algorithm isItPrime implmented with brute force O(n)
bool isItPrime(int number){
    if(number <= 1)
        return false;
    
    for(int i = 2 ; i < number ; i++){
        if( number%i == 0) 
            return false;
    }

    return true;
    
}
//Algorithm analizeThree implmented with brute force O(n**3)
void analizeThree(){
    int counter = 0;
    for (int i = 1 ; i < 10 ; i++){
        for (int j = 0 ; j < 10 ; j++){
            for (int k = 0 ; k < 10 ; k++){
                int second = (i * 10) + j;
                int third = (i * 100) + (j * 10) + k;
                if( isItPrime(i) && isItPrime(second) && isItPrime(third)) 
                    counter ++;
            }
        }
    }
    cout << counter;
}

int main(){
    analizeThree();
    return 0;
}