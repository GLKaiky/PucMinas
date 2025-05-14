#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Grafo {
private:
    int V; 
    vector<vector<int>> adjacencia; 
    vector<int> distancia;

public:
    Grafo(int vertices) {
        this->V = vertices;
        adjacencia.resize(V);
        distancia.resize(V);
        distancia.push_back(0);
    }

    void adicionarAresta(int u, int v) {
        adjacencia[u].push_back(v);
        adjacencia[v].push_back(u); 
    }

    void BFS(int inicio) {
        vector<bool> visitado(V, false); 
        queue<int> fila; 

        visitado[inicio] = true;
        fila.push(inicio);

        cout << "Busca em Largura (BFS) a partir do vértice " << inicio << ": ";

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();


            for (int vizinho : adjacencia[atual]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    fila.push(vizinho);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Grafo g(6);

    g.adicionarAresta(0, 1);
    g.adicionarAresta(0, 2);
    g.adicionarAresta(1, 3);
    g.adicionarAresta(1, 4);
    g.adicionarAresta(2, 4);
    g.adicionarAresta(3, 5);
    g.adicionarAresta(4, 5);

    g.BFS(2);

    return 0;
}