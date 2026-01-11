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
    bool valid = false;

public:
    virtual ~Graph()
    {
    }
    void setAsList()
    {
        aList = true;
        aMatrix = false;
    }
    void setaMatrix()
    {
        aMatrix = true;
        aList = false;
    }
    void setValid(bool fact)
    {
        valid = fact;
    }
    bool getValidity()
    {
        return valid;
    }
    virtual void outputGraph()
    {
    }
    // virtual void setAsMatrix();
    // virtual void setAsDirected();
    // virtual void setHasNegative();

    // virtual void outputGraph();
    // virtual void BFStraversal();
    // virtual void DFStraversal();
    // virtual void detectCycle(); // Contains code for both directed and undirected. Make call simple.
    // virtual void dijkstraShortest();
    // virtual void bellmanFordShortest();
    // virtual void floydWarshallShortest();
    // virtual void primMST();
    // virtual void kruskalMST();
    // virtual void boruvkaMST();
    // virtual void kahnTopological();
    // virtual void connectivity();
    // virtual void fordFulkersonFlow();
    // virtual void kargerFlow();
    // virtual void dinicFlow();
};