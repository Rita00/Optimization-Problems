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
