
#include <iostream>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int number_maps;
    int number_vertices, number_arcs, number_questions;
    int origin, destination, length;
    
    cin >> number_maps;
    
    while(number_maps--){
        
        map<pair<int,int>,int> graph;
        cin >> number_vertices >> number_arcs >> number_questions;
        
        while(number_arcs--){
            cin >> origin >> destination >> length;
            graph[{origin,destination}]=length;
        }
        
    }
    return 0;
}

/*
Example Input
=================
6
12 18 4 2 13
3 24
4 12
4 28
2 53
5 25
3 64
6 32
6 56
7 54
8 69
7 81
7 92
9 10 8 10 7 4
8 11 2 11 12 12 12 10 3 4 43
2 13
3 24
4 12
4 28
4 44
2 13
3 24
1 42
4 28
4 43
2 13
3 24
1 42
4 28
4 42
2 13
3 24
1 42
4 28
4 41
2 13
3 24
1 42
4 28



Example output
=================
3 6 12 17 0 00
1 35 5
1 35
13 1

 
*/
