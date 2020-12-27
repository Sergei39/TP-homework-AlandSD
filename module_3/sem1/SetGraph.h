//
// Created by sergei on 27.12.2020.
//

#ifndef SEM1_SETGRAPH_H
#define SEM1_SETGRAPH_H


#include "IGraph.h"
#include <unordered_map>

class SetGraph : public IGraph {
public:
    explicit SetGraph(int vertexCount);
    explicit SetGraph(const IGraph& graph);

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const  override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_map<int, int>> adjacencyLists;
};


#endif //SEM1_SETGRAPH_H
