#include <iostream>
#include <vector>
#include <list>
#include <limits>

#include <stack>


using namespace std;

struct pairEdgeWeight {
    int weight;
    int edge;
};

class Graph{

    private:
        int size;
        vector <list <pairEdgeWeight>> adj;

    public:
        Graph(int size){
            this->size = size;
            this->adj.resize(size);    
        }

        ~Graph(){ }

        bool addEdge(int startEdge,int edge, int weight){
            try{
                pairEdgeWeight* newConection = new pairEdgeWeight();

                newConection->edge = edge;
                newConection->weight = weight;

                this->adj[startEdge].push_back(*newConection);

                delete newConection;

            }catch(const exception& e){

                printf("%s", e.what());

                return false;
            }

            return true;
        }

        void printGraph(){
            for(int i = 0; i<this->size; i++){
                printf("Vertice %d", i  );
                for(const auto& connection : adj[i]){
                    printf("-> (Destino: %d, Peso: %d) ", connection.edge, connection.weight);
                }
                printf("\n");
            }
        }
    
        void djikstra(int vetInicial){
            int distance[this->size];

            distance[vetInicial] = 0; //vertice inicial com distância 0

            for(int i = 0; i<this->size; i++){ //inicializar os demais vertices com distância infinita
                if(i == vetInicial){
                    continue; //caso I seja igual ao vertice inicial, ignora pois não deve ser inifinito
                }
                distance[i] = numeric_limits<int>::max();
            }


            for(int i = 0; i < this->size; i++){
                int minSize = numeric_limits<int>::max();

                for(const auto& connection : this->adj[vetInicial]){
                    
                    cout << "Conecção para o Vértice: " << connection.edge  << " Com peso " << connection.weight << endl;

                    if((connection.weight + distance[vetInicial]) < distance[connection.edge]){

                        distance[connection.edge] = connection.weight + distance[vetInicial];
                                                    
                        if(minSize > distance[connection.edge]){
                            
                            minSize = connection.edge;
                            
                        }

                    }
                }

                if(minSize < this->size){
                    vetInicial = minSize;
                }
                            
            }

            for(int i = 0; i<this->size; i++){
                cout << distance[i] << endl;
            }

        }

        void DFS(int startVertex){
            stack<int> stack;
            
            vector<bool> hasVisited(this->size, false);

            stack.top(startVertex);
            hasVisited[startVertex] = true;

            while(!stack.empty()){

                int maxSize = numeric_limits<int>::min();

                for(pairEdgeWeight v : this->adj[stack.top()]){
                    
                    if(v.weight > maxSize){
                        maxSize = v.weight;
                    }   

                    
                }
            }
        }
};


int main(){
    Graph* g = new Graph(4);

    g->addEdge(0, 1, 3);
    g->addEdge(1, 2, 1);
    g->addEdge(2, 0, 2);
    g->addEdge(2, 3, 5);

    g->printGraph();

    g->djikstra(0);
    
    delete g;
}