#include <iostream>
#include <queue>
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"


void BFS(const IGraph& graph, int vertex, void (*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;

    while(bfsQueue.size() > 0) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);
        std::vector<int> adjacentVeticies = graph.GetNextVertices(current);
        for(int i = 0; i < adjacentVeticies.size(); ++i)
            if(!visited[adjacentVeticies[i]]) {
                bfsQueue.push(adjacentVeticies[i]);
                visited[adjacentVeticies[i]] = true;
            }
    }
}

int main() {

    ///   0---->1
    ///   | \  /
    ///   3   4--->2

    ListGraph listGraph(5);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 3);
    listGraph.AddEdge(0, 4);
    listGraph.AddEdge(1, 4);
    listGraph.AddEdge(4, 2);
    std::cout << "\nListGraph: ";
    BFS(listGraph, 0, [](int vertex) {std::cout << vertex << ", ";});

    MatrixGraph matrixGraph(listGraph);
    std::cout << "\nMatrixGraph: ";
    BFS(matrixGraph, 0, [](int vertex) {std::cout << vertex << ", ";});

    SetGraph setGraph(matrixGraph);
    std::cout << "\nSetGraph: ";
    BFS(setGraph, 0, [](int vertex) {std::cout << vertex << ", ";});

    ArcGraph arcGraph(setGraph);
    std::cout << "\nArcGraph: ";
    BFS(arcGraph, 0, [](int vertex) {std::cout << vertex << ", ";});

    return 0;
}
