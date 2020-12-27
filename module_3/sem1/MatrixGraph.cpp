//
// Created by sergei on 27.12.2020.
//

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexCount) :
        adjacencyLists(vertexCount)
{
    for(int i = 0; i < vertexCount; ++i)
        adjacencyLists[i].resize(vertexCount);
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    int vCount = graph.VerticesCount();
    adjacencyLists.resize(vCount);
    for(int i = 0; i < vCount; ++i)
        adjacencyLists[i].resize(vCount, 0);

    for(int from = 0; from < adjacencyLists.size(); ++from) {
        std::vector<int> nextVertices = graph.GetNextVertices(from);
        for(int nextVertice : nextVertices)
            adjacencyLists[from][nextVertice] = 1;
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjacencyLists.size());
    assert(to >= 0 && to < adjacencyLists.size());

    adjacencyLists[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return adjacencyLists.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    std::vector<int> result;
    for (int i = 0; i < adjacencyLists.size(); ++i)
        if (adjacencyLists[vertex][i] == 1)
            result.push_back(i);

    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    std::vector<int> result;
    for (int i = 0; i < adjacencyLists.size(); ++i)
        if (adjacencyLists[i][vertex] == 1)
            result.push_back(i);

    return result;
}

