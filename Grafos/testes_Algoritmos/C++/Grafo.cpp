#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();
typedef pair<int, int> PII;

void dijkstra(int origem, const vector<vector<PII>>& grafo, vector<int>& distancias) {
    int n = grafo.size();
    distancias.assign(n, INF);
    distancias[origem] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> fila_prioridade;
    fila_prioridade.push({0, origem});

    while (!fila_prioridade.empty()) {
        int dist = fila_prioridade.top().first;
        int atual = fila_prioridade.top().second;
        fila_prioridade.pop();

        if (dist > distancias[atual]) continue;

        for (auto vizinho : grafo[atual]) {
            int destino = vizinho.first;
            int peso = vizinho.second;

            if (distancias[atual] + peso < distancias[destino]) {
                distancias[destino] = distancias[atual] + peso;
                fila_prioridade.push({distancias[destino], destino});
            }
        }
    }
}

int main() {
    // Exemplo de grafo com 5 vértices (0 a 4)
    vector<vector<PII>> grafo(5);

    // Arestas: origem -> destino com peso
    grafo[0].push_back({1, 10});
    grafo[0].push_back({2, 5});
    grafo[1].push_back({2, 2});
    grafo[1].push_back({3, 1});
    grafo[2].push_back({1, 3});
    grafo[2].push_back({3, 9});
    grafo[2].push_back({4, 2});
    grafo[3].push_back({4, 4});
    grafo[4].push_back({0, 7});
    grafo[4].push_back({3, 6});

    int origem = 0;
    vector<int> distancias;
    dijkstra(origem, grafo, distancias);

    cout << "Distâncias mínimas a partir do vértice " << origem << ":\n";
    for (int i = 0; i < distancias.size(); ++i) {
        if (distancias[i] == INF) {
            cout << i << ": INFINITO\n";
        } else {
            cout << i << ": " << distancias[i] << "\n";
        }
    }

    return 0;
}
