//
// Created by sergei on 27.12.2020.
//

#ifndef SEM1_IGRAPH_H
#define SEM1_IGRAPH_H

#include <vector>
#include <cassert>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //SEM1_IGRAPH_H
