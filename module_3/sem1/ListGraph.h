//
// Created by sergei on 27.12.2020.
//

#ifndef SEM1_LISTGRAPH_H
#define SEM1_LISTGRAPH_H

#include "IGraph.h"

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


#endif //SEM1_LISTGRAPH_H
