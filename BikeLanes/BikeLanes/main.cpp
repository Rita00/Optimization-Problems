
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
    
    while(number_map--){
        
        map<pair<int,int>,int> graph;
        cin >> number_vertices >> number_arcs >> number_questions;
        
        while(number_arcs--){
            cin >> origin >> destination >> length;
            graph[{origin,destination}]=length;
        }
        
    }
    return 0;
}
