/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <map>
#include <vector>

#define DEBUG_MODE false

using namespace std;

int total;
int n, blockHeight, maxHeight;

void printVector(vector<int> h){
    cout << "[\t";
    for(int val : h){
        cout << val << "\t";
    }
    cout << "]" << endl;
}

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}

void arcDown(vector<int> h, int k) {
    ///Parar
    if(k>=n){
        return;
    }
    /// Rule 3,4
    for(int i=h[k-1]-blockHeight+1 ; i<h[k-1] ; i++){
        /// entre 0 (e o anterior)
        if(0<=i){
            h.resize(k+1);
            h[k] = i;
            //RULE 2 and increment
            if(h[k]==0){
                if(DEBUG_MODE){printVector(h);}
                total++;
            }
            arcDown(h,k+1);
        }
    }
}

void arcUp(vector<int> h, int k) {
    ///Parar
    if(k>=n){
        return;
    }
    /// Rule 3,4
    for(int i=h[k-1]-blockHeight+1 ; i<h[k-1]+blockHeight ; i++){
        /// entre 0 e altura maxima
        if(0<=i and i<=maxHeight-blockHeight){
            /// Rule 1
            if(i != h[k-1]){
                h.resize(k+1);
                h[k] = i;
                /// Rule 2
                if(h[k]==0){
                    if(DEBUG_MODE){printVector(h);}
                    total++;
                }
                if(h[k-1]<h[k]){
                    arcUp(h,k+1);
                }else{
                    arcDown(h,k+1);
                }
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int test_cases;
    cin >> test_cases;
    
    for (int i = 0; i < test_cases; i++) {
        cin >> n;
        cin >> blockHeight;
        cin >> maxHeight;
        total=0;
        if(n>=3){
            vector<int> h;
            h.resize(1);
            arcUp(h,1);
        }
        cout << total%1000000007 << endl;
    }
    return 0;
}

/**
 * Regras!
 * 1- Arco com dimensão 3 <= K <= num_legos, i = i é o primeiro bloco, i = 2 o segundo até ao último bloco i = K
 * 2- O primeiro e último blocos devem ser colocados no chão, ou seja, h1 = 0 e hK = 0
 * 3- O iº bloco deve "tocar" nos seus vizinhos
 * 4- Os valores de hi devem ser monotonicamnete crescentes, até um certo bloco e decrescescer novamente
 * 5- Dois blocos consecutivos não podem ter o mesmo valor de hi (a mesma altura)
 */

/*
INPUT
------
7
3 3 3
3 3 4
3 3 5
3 3 6
4 3 7
5 5 10
8 4 30

 
OUTPUT
------
0
1
2
2
4
54
819
 
Input (Example 2)
--------------------
1
32 3 100
 
 
Output (Example 2)
---------------------
431655757
 
 
Input (Example 3)
--------------------
2
17 29 5899
70 16 276
 
 
Output (Example 3)
--------------------

162344589
70718620
 
 
 
5
3 3 3
3 3 4
3 3 5
3 3 6
4 3 7
 
 
 
 5
 3 3 3
 3 3 4
 3 3 5
 3 3 6
 4 3 7

  
 
*/
