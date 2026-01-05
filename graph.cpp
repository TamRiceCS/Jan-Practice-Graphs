#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Graph
{
private:
    bool aList = false;
    bool aMatrix = false;
    bool directed = false;
    bool hasNegative = false;

public:
    void setAsList();
    void setAsMatrix();
    void setAsDirected();
    void setHasNegative();

    void outputGraph();
    void BFStraversal();
    void DFStraversal();
    void detectCycle(); // Contains code for both directed and undirected. Make call simple.
    void dijkstraShortest();
    void bellmanFordShortest();
    void floydWarshallShortest();
    void primMST();
    void kruskalMST();
    void boruvkaMST();
    void kahnTopological();
    void connectivity();
    void fordFulkersonFlow();
    void kargerFlow();
    void dinicFlow();
};