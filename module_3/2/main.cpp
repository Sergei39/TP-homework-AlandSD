#include <iostream>

#include <vector>
#include <cassert>
#include <queue>
#include <map>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int vertexCount);
    explicit ListGraph(const IGraph& graph);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const  override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyLists;
};

ListGraph::ListGraph(int vertexCount) :
        adjacencyLists(vertexCount)
{}

ListGraph::ListGraph(const IGraph &graph) {
    adjacencyLists.resize(graph.VerticesCount());
    for(int from = 0; from < adjacencyLists.size(); ++from)
        adjacencyLists[from] = graph.GetNextVertices(from);
}

void ListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjacencyLists.size());
    assert(to >= 0 && to < adjacencyLists.size());

    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

// работает долго
std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());
    std::vector<int> result;
    for(int from = 0; from < adjacencyLists.size(); ++from)
        for(int i = 0; i < adjacencyLists[from].size(); ++i)
            if(adjacencyLists[from][i] == vertex)
                result.push_back(from);

    return result;
}



struct Vertex {
    int NumberWay;
    int Layer;

    Vertex() : NumberWay(0), Layer(0) {}
    Vertex(int numberWay, int layer) : NumberWay(numberWay), Layer(layer) {}
};

int BFS(const IGraph& graph, int start, int end) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> bfsQueue;
    std::map<int, Vertex> vertex;
    bfsQueue.push(start);
    vertex[start] = Vertex(1, 0);
    visited[start] = true;

    while(bfsQueue.size() > 0) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        std::vector<int> adjacentVeticies = graph.GetNextVertices(current);
        for(int i = 0; i < adjacentVeticies.size(); ++i)
            if(!visited[adjacentVeticies[i]]) {
                bfsQueue.push(adjacentVeticies[i]);
                vertex[adjacentVeticies[i]] = Vertex(vertex[current].NumberWay, vertex[current].Layer + 1);
                visited[adjacentVeticies[i]] = true;
            }
            else {
                if(vertex[adjacentVeticies[i]].Layer == vertex[current].Layer + 1)
                    vertex[adjacentVeticies[i]].NumberWay += vertex[current].NumberWay;
            }
    }

    return vertex[end].NumberWay;
}

int main() {
    int v, w;
    std::cin >> v >> w;
    ListGraph graph(v);

    for (int i = 0; i < w; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int start, end;
    std::cin >> start >> end;

    int way = BFS(graph, start, end);
    std::cout << way;

    return 0;
}
