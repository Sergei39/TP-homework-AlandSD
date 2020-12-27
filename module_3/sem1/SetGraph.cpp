//
// Created by sergei on 27.12.2020.
//

#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) :
        adjacencyLists(vertexCount)
{}

SetGraph::SetGraph(const IGraph &graph) {
    int vCount = graph.VerticesCount();
    adjacencyLists.resize(vCount);

    for(int from = 0; from < adjacencyLists.size(); ++from) {
        std::vector<int> nextVertices = graph.GetNextVertices(from);
        for(int nextVertice : nextVertices)
            adjacencyLists[from][nextVertice] = 1;
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjacencyLists.size());
    assert(to >= 0 && to < adjacencyLists.size());

    adjacencyLists[from][to] = 1;
}

int SetGraph::VerticesCount() const {
    return adjacencyLists.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    std::vector<int> result;
    for (auto it = adjacencyLists[vertex].begin(); it != adjacencyLists[vertex].end(); ++it)
        result.push_back(it->first);

    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    std::vector<int> result;
    for(int from = 0; from < adjacencyLists.size(); ++from)
        for(int i = 0; i < adjacencyLists[from].size(); ++i)
            if(adjacencyLists[from].find(vertex) != adjacencyLists[from].end())
                result.push_back(from);

    return result;
}
