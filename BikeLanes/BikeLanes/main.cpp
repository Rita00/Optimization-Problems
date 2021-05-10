#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

vector<int> solution;

map<int, pair<int, int>> edge;
//map<pair<int, int>, int> edge;
map<int, int> k_set;
map<int, int> k_rank;

vector<bool> visited;
map<int, list<int>> outNeighbours, inNeighbours;
map<int, list<int>> components;


void make_set(const list<int>& V) {
    for (auto v : V) {
        k_set[v] = v;
        k_rank[v] = 0;
    }
}

int find_set(int a) {
    if (k_set[a] != a) {
        k_set[a] = find_set(k_set[a]);
    }
    return k_set[a];
}

void link_set(int a, int b) {
    if (k_rank[a] > k_rank[b]) {
        k_set[b] = a;
    } else {
        k_set[a] = b;
    }
    if (k_rank[a] == k_rank[b]) {
        k_rank[b]++;
    }
}

void union_set(int a, int b) {
    link_set(find_set(a), find_set(b));
}

bool sortEdge(const pair<int, int> &a, const pair<int, int> &b) {
    return (a.second < b.second);
}

int Kruskals(const list<int>& V) {
    int count = 0;
    map<int, vector<pair<int, int>>> ordered_edges_weight;
    k_rank.clear();
    k_set.clear();


    make_set(V);

    //sort edges in E into nondecreasing order by weight
//    for (auto &it : edge) {
//        ordered_edges_weight[it.second].push_back(it.first);
//    }

    sort(edge.begin(), edge.end());

    for (auto const&[key, val] : edge) {
        if (find_set(val.first) != find_set(val.second)) {
            count += key;
            union_set(val.first, val.second);
        }
    }

//    for (auto &it : ordered_edges_weight) {
//        for (auto const&[u, v] : it.second) {
//            if (find_set(u) != find_set(v)) {
////                count += it.first;
//                count += edge[{u, v}];
//                union_set(u, v);
//            }
//        }
//    }
    return count;
}

void initKruskals() {
    int total = 0, max = 0, current;
    for (const auto& c : components) {
        current = Kruskals(c.second);
        total += current;
        if (current > max) {
            max = current;
        }
    }
    solution.push_back(max);
    solution.push_back(total);
}


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

int getMaxComponent() {
    unsigned int max = 0;
    list<int>::iterator v;
    for (auto & component : components) {
        unsigned int size = component.second.size();
        if (size > max)
            max = size;
        
    }
    return (int)max;
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
        edge.clear();
        solution.clear();
        cin >> number_vertices >> number_arcs >> number_questions;
        while (number_arcs--) {
            cin >> origin >> destination >> length;
            origin--;
            destination--;
//            edge[{origin, destination}] = length;
            edge[length] = {origin, destination};
            outNeighbours[origin].push_back(destination);
            inNeighbours[destination].push_back(origin);
        }
        Kosaraju(number_vertices);
        
        solution.push_back((int) components.size());
        solution.push_back((int) (getMaxComponent()));
        switch (number_questions) {
            case 1:
                cout << solution[0] << endl;
                break;
            case 2:
                cout << solution[0] << " " << solution[1] << endl;
                break;
            case 3:
                initKruskals();
                cout << solution[0] << " " << solution[1] << " " << solution[2] << endl;
                break;
            case 4:
                initKruskals();
                cout << solution[0] << " " << solution[1] << " " << solution[2] << " " << solution[3] << endl;
                break;


        }

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
