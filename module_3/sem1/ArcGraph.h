//
// Created by sergei on 27.12.2020.
//

#ifndef SEM1_ARCGRAPH_H
#define SEM1_ARCGRAPH_H


#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int vertexCount);
    explicit ArcGraph(const IGraph& graph);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const  override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    struct Edge {
        int From;
        int To;
        Edge(int from, int to) : From(from), To(to) {}
    };

    int numberVertices;
    std::vector<Edge> adjacencyLists;
};


#endif //SEM1_ARCGRAPH_H
