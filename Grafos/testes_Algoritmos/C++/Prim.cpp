#include <iostream>
#include <vector> 
#include <list>
#include <limits>
#include <queue>
#include <utility>

using namespace std;

class Prim {
    private:
        vector<list<pair<int, int> > > adj; //Grafo Ponderado não direcionado par {Peso, Vertice}
        int size;

    public:
        Prim(int size) {
            this->size = size;
            adj.resize(size);
        }

        ~Prim(){ }

        bool addVertices(int startVertice, int endVertice, int weight) {
            try{
                this->adj[startVertice].push_back({weight, endVertice});     
            }catch(exception &e){
                cout << "Erro: " << e.what() << endl;
                return false;
            }

            return true;
        }

        void printGraph(){
            for(int i = 0; i<this->size; i++){
                cout << "Vertice " << i << " aponta para ";

                for(const auto& v : adj[i]){
                    cout << v.second << " com peso " << v.first << " ";
                }

                cout << endl;
            }
        }

        void dijkstra(int startVertice){
            vector<int> distances(this->size, numeric_limits<int>::max());
            vector<int> pi(this->size, -1);
            vector<bool> visited(this->size, false);


            priority_queue<pair<int, int>, vector <pair<int, int> >, greater<pair <int, int> > > minHeap;

            distances[startVertice] = 0;
            minHeap.push({0, startVertice});

            while(!minHeap.empty()){

                int index = minHeap.top().second;
                minHeap.pop();

                if(visited[index]) continue;

                visited[index] = true;


                for(const auto& v : adj[index]){
                    if(distances[index] + v.first < distances[v.second] && !visited[v.second]){
                        distances[v.second] = distances[index] + v.first;
                        pi[v.second] = index;
                        

                        minHeap.push({distances[v.second], v.second});
                    }
                }

            }

            for (int i = 0; i < this->size; i++) {
                cout << "Distância de " << startVertice << " até " << i << ": ";
                if (distances[i] == numeric_limits<int>::max()) cout << "Infinito";
                else cout << distances[i];
                cout << endl;
            }
        }

        bool belmanFord(int startVertice){
            vector<int> distances(this->size, numeric_limits<int>::max());
            queue<int> queue;

            distances[startVertice] = 0;

            queue.push(startVertice);

            while(!queue.empty()){

                int index = queue.front();
                queue.pop();

                for(const auto& v : adj[index]){
                    int weight = v.first;
                    int value = v.second;

                    if(distances[index] + weight < distances[value]){
                        distances[value] = distances[index] + weight;

                        queue.push(value);

                    }
                }
            }

            queue.push(startVertice);

            cout << "Segunda repetição" << endl;

            while(!queue.empty()){
                int index = queue.front();
                  
                queue.pop();

                for(const auto& v : adj[index]){
                    int weight = v.first;
                    int value = v.second;

                    if(distances[index] + weight < distances[value]){
                        return false;
                    }
 
                    queue.push(value);
                }
            }

            return true;
        }

        void prim(int root){
            vector<int> key(this->size, numeric_limits<int>::max()); //inicializar tudo com null e infinito
            vector<int> pi(this->size, -1);
            vector<bool> visited(this->size, false);

            key[root] = 0;

            priority_queue<pair<int, int> , vector<pair<int, int> >, greater<pair<int,int>>> pq;

            pq.push({0, root}); //peso e vertice

            while(!pq.empty()){

                int index =  pq.top().second; // pega o vertice e aresta do top do heap minimo

                pq.pop(); //remove eles

                if(visited[index]) continue;
                visited[index] = true;

                for(const auto& v : adj[index]){

                    if(!visited[v.second] && v.first < key[v.second]){

                        pi[v.second] = index;
                        key[v.second] = v.first;

                        pq.push({key[v.second], v.second});
                    }
                }
            }
            
            cout << "Árvore Geradora Mínima (Prim):\n";
            for (int i = 0; i < this->size; i++) {
                if (pi[i] != -1) {
                    cout << pi[i] << " - " << i << " (peso " << key[i] << ")\n";
                }
            }
        }
};

int main() {

    Prim graph(6);

    graph.addVertices(0, 1, 8);  
    graph.addVertices(0, 2, 10);   
    graph.addVertices(1, 3, 1);   
    graph.addVertices(3, 2, -4);   
    graph.addVertices(3, 4, -1);   
    graph.addVertices(2, 4, 2);   
    graph.addVertices(4, 5, -2);  
    graph.addVertices(5, 2, 1);


    cout << "Grafo original:\n";
    graph.printGraph();
    cout << "\n";

    // Testa o algoritmo de Prim a partir do vértice 0
    cout << "Executando Belman Ford a partir do vértice 0:\n";
    
    if(!graph.belmanFord(0)){
        cout << "Entrou em loop negativo" << endl;
    }else {
        cout << "Deu boa" << endl;
    }


}