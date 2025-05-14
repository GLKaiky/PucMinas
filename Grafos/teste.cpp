#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class Graph {
public:
    int numVertex;
    vector<vector<int>> adjList;

    Graph(int numVertex) : numVertex(numVertex), adjList(numVertex) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void print() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < numVertex; i++) {
            cout << char('A' + i) << ": ";
            for (int v : adjList[i]) {
                cout << char('A' + v) << " ";
            }
            cout << endl;
        }
    }
};

vector<bool> visited;
vector<int> path;
vector<vector<int>> cycles;

bool isSameCycle(const vector<int>& cycle1, const vector<int>& cycle2) {
    if (cycle1.size() != cycle2.size()) return false;
    vector<int> temp = cycle2;
    for (int i = 0; i < cycle1.size(); i++) {
        rotate(temp.begin(), temp.begin() + 1, temp.end());
        if (cycle1 == temp) return true;
    }
    reverse(temp.begin(), temp.end());
    for (int i = 0; i < cycle1.size(); i++) {
        rotate(temp.begin(), temp.begin() + 1, temp.end());
        if (cycle1 == temp) return true;
    }
    return false;
}

void normalizeCycle(vector<int>& cycle) {
    rotate(cycle.begin(), min_element(cycle.begin(), cycle.end()), cycle.end());
}

void storeCycle() {
    vector<int> cycle(path.begin(), path.end());
    normalizeCycle(cycle);
    if (none_of(cycles.begin(), cycles.end(), [&](const vector<int>& c) { return isSameCycle(c, cycle); })) {
        cycles.push_back(cycle);
        for (int v : cycle) cout << char('A' + v) << "-";
        cout << char('A' + cycle[0]) << endl;
    }
}

void findCycles(Graph& g, int start, int v, int length) {
    visited[v] = true;
    path.push_back(v);

    for (int u : g.adjList[v]) {
        if (u == start && length >= 2) {
            storeCycle();
        } else if (!visited[u] && u > start) {
            findCycles(g, start, u, length + 1);
        }
    }

    visited[v] = false;
    path.pop_back();
}

void contarCiclos(Graph& g) {
    auto start_time = chrono::high_resolution_clock::now();
    cycles.clear();
    visited.assign(g.numVertex, false);

    for (int i = 0; i < g.numVertex; i++) {
        findCycles(g, i, i, 0);
    }

    auto end_time = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double, micro>(end_time - start_time).count();
    
    cout << "Total Cycles: " << cycles.size() << endl;
    cout << "Execution Time: " << time_taken << " microseconds" << endl;
}

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "GRAPH:" << endl;
    g.print();
    cout << "\nCYCLES:" << endl;
    contarCiclos(g);
    
    return 0;
}
