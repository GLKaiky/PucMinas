
#include <iostream>
#include <list>
#include <vector>

using namespace std;

namespace G
{
    template <typename T>
    class Vertex
    {
    public:
        T data;

        Vertex(T data) : data(data) {}
    };

    template <typename T>
    class Edge
    {
    public:
        Vertex<T> u;
        Vertex<T> v;

        Edge(Vertex<T> src, Vertex<T> dest) : u(src), v(dest) {}
    };

    template <typename T>
    class Graph
    {

    protected:
        vector<Edge<T>> edges;
        vector<Vertex<T>> vertices;

        bool directional = false;

    public:
        virtual void print() = 0;

            void addVertex(T v) { vertices.push_back(Vertex<T>(v)); };
        vector<Vertex<T>> getVertices() { return vertices; }
        Vertex<T> getVerticeByIndex(int index) { return vertices[index]; }
        vector<Vertex<T>> getNeighbors(T u) { return {}; }
        // Costly, not recomended
        void removeVertex(T v) { vertices.erase(find(vertices.begin(), vertices.end(), v)); }
        void removeVertexByIndex(int index) { vertices.erase(vertices.begin() + index); }

        void addEdge(Vertex<T> u, Vertex<T> v) { edges.push_back(Edge<T>(u, v)); };
        void addEdgeByIndex(int u, int v) { edges.push_back(Edge<T>(getVerticeByIndex(u), getVerticeByIndex(u))); };
        vector<Edge<T>> getEdges(T u, T v) { return edges; }
        vector<Edge<T>> getEdgesByVertex(T u)
        {
            vector<Edge<T>> ret;
            for (size_t i = 0; i < edges.size(); i++)
            {
                if (edges[i].u == u || (!directional && edges[i].v == u))
                {
                    ret.push_back(edges[i]);
                }
            }
            return ret;
        }
        // Costly, not recomended
        void removeEdge(Edge<T> edge) { edges.erase(find(edges.begin(), edges.end(), edge)); };
        void removeEdgeByIndex(int index) { edges.erase(vertices.begin() + index); };
    };
}
