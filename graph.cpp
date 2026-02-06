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
    class Compare
    {
    public:
        bool operator()(std::vector<int> a, std::vector<int> b)
        {
            if (a[0] > b[0])
            {
                return true;
            }
            return false;
        }
    };

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

    bool getDirectedness()
    {
        return directed;
    }

    void setDirectedness(bool fact)
    {
        directed = fact;
    }

    void setNegative(bool fact)
    {
        hasNegative = fact;
    }

    bool getNegativeStatus()
    {
        return hasNegative;
    }

    //  virtual void detectCycle(); // Contains code for both directed and undirected. Make call simple.
    // virtual void detectDirectedness();
    //  virtual void connectivity();
    virtual void outputGraph() = 0;
    virtual void BFStraversal(int node) = 0;
    virtual void DFStraversal(int node) = 0;
    virtual void dijkstraShortest(int node) = 0;
    virtual void bellmanFordShortest(int node) = 0;
    virtual void floydWarshallShortest() = 0;
    virtual void primMST(int node) = 0;
    virtual void kruskalMST() = 0;
    virtual void kahnTopological() = 0;
    virtual void fordFulkersonFlow(int source, int destination) = 0;
    //  virtual void kargerFlow();
};