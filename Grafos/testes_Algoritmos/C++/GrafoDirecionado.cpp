#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

#include <pair>

using namespace std;

struct PathTrace {
    int discovery;
    int finish;
};

class GrafoDirecionado {
    private:

        vector <list<int>> adj;
        int size;


        vector<list<int> > reverseEdges(){
            vector<list<int>> reverseAdj;
            reverseAdj.resize(this->size);

            for(int i = 0; i< this->size; i++){
                
                for(int v : this->adj[i]){
                    reverseAdj[v].push_back(i);
                }
            }
            
            return reverseAdj; 
        }


        vector<pair<int, int>> DFS(vector<list<int>> adj, vector<pair<int, int>> time ,vector<bool> visited,int startVertice, int index){
            
            if(adj[startVertice].empty() || visited[startVertice] == true){
                return time;
            }

            visited[startVertice] = true;

            for(int v : adj[startVertice]){

                if(visited[v] == false){
                    time.push_back({index, DFS(adj, time, visited, v, index++)});
                    return time.back();
                } else {
                    time.push_back({index, index++});
                    return time.back();
                }
                
            }


        }

    public:

    GrafoDirecionado(int size){
        this->size = size;
        adj.resize(size);
    }


    bool addEdge(int startEdge, int endEdge) {
        try{

            adj[startEdge].push_back(endEdge);
            cout << "Vertice: " << startEdge << " Aponta para: " << endEdge << endl;

        }catch(const exception& e){
            cout << "Excessão capturada" << e.what() << endl;
            return false;
        }   

        return true;

    }

    void printGraph() {
        for (int i = 0; i < this->size; i++) {
            cout << "Vértice: " << i << " tem arestas para: ";
            for (int v : this->adj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    


    void BFS(int startVertice){
        queue<int> queue; //fila de visitação
        
        vector<bool> visited(this->size, false); //marcar vertice como visitado ou não

        int order[this->size]; //ordem de visitação
        short index = 0;
        queue.push(startVertice);
            
        visited[queue.front()] = true; //marca como visitado

        while(!queue.empty()){ //enquanto a fila não estiver vazia (ainda há vertices para visitar)

            order[index++] = queue.front();     
            
            for(int v : adj[queue.front()]){
                
                if(visited[v] == false){
                    queue.push(v);
                    visited[v] = true;  
                }
            }

            queue.pop();
        }

        for(int i = 0; i< index; i++){
            cout << order[i] << endl;
        }
    }

    




};

int main(){
    GrafoDirecionado * g = new GrafoDirecionado(3);
    
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 2);
    
}