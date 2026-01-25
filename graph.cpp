#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>

class Graph
{
private:
    bool aList = false;
    bool aMatrix = false;
    bool valid = false;
    bool directed = false;
    bool hasNegative = false;

public:
    virtual ~Graph()
    {
    }
    void setAsList()
    {
        aList = true;
        aMatrix = false;
    }
    void setAsMatrix()
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

    void setNegative(bool fact)
    {
        hasNegative = fact;
    }

    bool getNegativeStatus()
    {
        return hasNegative;
    }

    virtual void outputGraph() = 0;
    virtual void BFStraversal(int node) = 0;
    virtual void DFStraversal(int node) = 0;
    //  virtual void detectCycle(); // Contains code for both directed and undirected. Make call simple.
    virtual void dijkstraShortest(int node) = 0;
    virtual void bellmanFordShortest(int node) = 0;
    //  virtual void floydWarshallShortest();
    //  virtual void primMST();
    //  virtual void kruskalMST();
    //  virtual void boruvkaMST();
    //  virtual void kahnTopological();
    //  virtual void connectivity();
    //  virtual void fordFulkersonFlow();
    //  virtual void kargerFlow();
    //  virtual void dinicFlow();
};