#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <stack>


using namespace std;
vector<bool> visited;
map<pair<int, int>, int> graph;
map<int, list<int>> outNeighbours, inNeighbours;
map<int, list<int>> components;

void Visit(int u, stack<int> &L) {
    list<int>::iterator v;
    if (!visited[u]) {
        visited[u] = true;
        for (v = outNeighbours[u].begin(); v != outNeighbours[u].end(); v++) {
            Visit(*v, L);
        }
        L.push(u);
    }
}

bool isAssigned(int u) {
    for (auto const&[key, val] : components) {
        for (int i : val) {
            if (i == u) return true;
        }
    }
    return false;
}

void AssignComponent(int u, int root) {
    list<int>::iterator v;
    if (!isAssigned(u)) {
        components[root].push_back(u);
        for (v = inNeighbours[u].begin(); v != inNeighbours[u].end(); v++) {
            AssignComponent(*v, root);
        }
    }
}

void removeSingleComp() {
    list<int> remove;
    for (auto const&[key, val] : components) {
        if (val.size() < 2)
            remove.push_back(key);
    }
    for (auto i : remove)
        components.erase(i);
}

void Kosaraju(int numV) {
    stack<int> L;
    visited.resize(0);
    visited.resize(numV);
    for (int u = 0; u < numV; u++) {
        Visit(u, L);
    }
    while (!L.empty()) {
        int u = L.top();
        L.pop();
        AssignComponent(u, u);
    }
    removeSingleComp();
}

void printComponents() {
    cout << "\n\n=======================" << endl;
    for (auto const&[key, val] : components) {
        cout << key;
        for (int i : val) {
            cout << "\t" << i << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int number_maps;
    int number_vertices, number_arcs, number_questions;
    int origin, destination, length;

    cin >> number_maps;

    while (number_maps--) {
        outNeighbours.clear();
        inNeighbours.clear();
        components.clear();
        graph.clear();
        cin >> number_vertices >> number_arcs >> number_questions;
        while (number_arcs--) {
            cin >> origin >> destination >> length;
            origin--;
            destination--;
            graph[{origin, destination}] = length;
            outNeighbours[origin].push_back(destination);
            inNeighbours[destination].push_back(origin);
        }
        Kosaraju(number_vertices);
        printComponents();
    }
    cout << endl;
    return 0;
}

/*
Example Input
=================
6
12 18 4
2 1 3
3 2 4
4 1 2
4 2 8
2 5 3
5 2 5
3 6 4
6 3 2
6 5 6
7 5 4
8 6 9
7 8 1
7 9 2
9 10 8
10 7 4
8 11 2
11 12 12
12 10 3
4 4 3
2 1 3
3 2 4
4 1 2
4 2 8
4 4 4
2 1 3
3 2 4
1 4 2
4 2 8
4 4 3
2 1 3
3 2 4
1 4 2
4 2 8
4 4 2
2 1 3
3 2 4
1 4 2
4 2 8
4 4 1
2 1 3
3 2 4
1 4 2
4 2 8



Example output
=================
3 6 12 17
0 0 0
1 3 5 5
1 3 5
1 3
1

 
*/
