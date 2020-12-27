//
// Created by sergei on 27.12.2020.
//

#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertexCount) :
        numberVertices(vertexCount)
{}

ArcGraph::ArcGraph(const IGraph &graph) {
    numberVertices = graph.VerticesCount();

    for(int from = 0; from < numberVertices; ++from) {
        std::vector<int> nextVertices = graph.GetNextVertices(from);
        for(int nextVertice : nextVertices) {
            adjacencyLists.emplace_back(from, nextVertice);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjacencyLists.size());
    assert(to >= 0 && to < adjacencyLists.size());

    adjacencyLists.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return numberVertices;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    std::vector<int> result;
    for (auto adjacencyList : adjacencyLists)
        if (adjacencyList.From == vertex)
            result.push_back(adjacencyList.To);

    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    std::vector<int> result;
    for (auto adjacencyList : adjacencyLists)
        if (adjacencyList.To == vertex)
            result.push_back(adjacencyList.From);

    return result;
}
