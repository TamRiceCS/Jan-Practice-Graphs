#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class AdjacencyList : public Graph
{
private:
    class Node
    {
    public:
        int destinationNode;
        int weight;

        Node(int dNode, int w)
        {
            destinationNode = dNode;
            weight = w;
        }
    };

    std::vector<std::vector<Node *>> list;

public:
    AdjacencyList(std::string fileName)
    {
        std::ifstream vectorFile(fileName);
        try
        {
            if (!vectorFile.is_open())
            {
                std::cout << "Could not open the file..." << std::endl;
            }
        }
        catch (...)
        {
            std::cout << "Something went wrong with the file... Please try again..." << std::endl;
            return;
        }

        int number = 0;
        int sign = 1;
        int nodeNum = 0;
        std::string fileLine = "";

        while (std::getline(vectorFile, fileLine))
        {
            std::vector<Node *> links;
            int number = 0;

            if (fileLine == "[]")
            {
                continue;
            }

            for (int i = 0; i < fileLine.size(); i++)
            {
                if (fileLine[i] == '-')
                {
                    sign = -1;
                }
                else if (std::isdigit(fileLine[i]))
                {
                    number *= 10;
                    number += (fileLine[i] - '0') * sign;
                }
                else if (number > 1000 || number < -1000)
                {
                    std::cout << "Value of weight is not in range." << std::endl;
                    setValid(false);
                    return;
                }
                else if (fileLine[i] == ',' || fileLine[i] == ']')
                {
                    if ((sign == -1 && number != 0) || sign == 1)
                    {
                        links.push_back(new Node(nodeNum, number));
                    }
                    number = 0;
                    sign = 1;
                    nodeNum++;
                }
            }
            if (links.size() > 0)
            {
                list.push_back(links);
                links.clear();
            }
            nodeNum = 0;
        }

        if (list.size() > 0)
        {
            setValid(true);
        }
    }

    ~AdjacencyList()
    {
        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list[i].size(); j++)
            {
                delete list[i][j];
            }
        }
    }

    void outputGraph()
    {
        if (list.size() == 0)
        {
            return;
        }

        std::cout << "\n";
        for (int i = 0; i < list.size(); i++)
        {
            std::cout << i << " has child(ren): ";
            for (int j = 0; j < list[i].size(); j++)
            {
                if (j != list[i].size() - 1)
                {
                    std::cout << "-> " << list[i][j]->destinationNode << ": " << list[i][j]->weight << ", ";
                }
                else
                {
                    std::cout << "-> " << list[i][j]->destinationNode << ": " << list[i][j]->weight << std::endl;
                }
            }
        }
    }

    void BFStraversal(int node)
    {
        if (node >= list.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::queue<int> adjacencies;
        std::vector<bool> visited(list.size(), false);

        adjacencies.push(node);

        while (!adjacencies.empty())
        {
            int parent = adjacencies.front();
            std::cout << "   Visited " << parent << std::endl;
            adjacencies.pop();
            visited[parent] = true;

            for (int i = 0; i < list[parent].size(); i++)
            {
                int child = list[parent][i]->destinationNode;
                if (!visited[child])
                {
                    adjacencies.push(child);
                    visited[child] = true;
                }
            }
        }
    }

    void DFStraversal(int node)
    {
        if (node >= list.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::stack<int> adjacencies;
        std::vector<bool> visited(list.size(), false);

        adjacencies.push(node);

        while (!adjacencies.empty())
        {
            int parent = adjacencies.top();
            std::cout << "   Visited " << parent << std::endl;
            adjacencies.pop();
            visited[parent] = true;

            for (int i = 0; i < list[parent].size(); i++)
            {
                int child = list[parent][i]->destinationNode;
                if (!visited[child])
                {
                    adjacencies.push(child);
                    visited[child] = true;
                }
            }
        }
    }

    void dijkstraShortest(int node)
    {
        if (getNegativeStatus())
        {
            std::cout << "Dijkstra does not work on negative edge / cycle graphs..." << std::endl;
            return;
        }

        if (node >= list.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::vector<int> distances(list.size(), INT_MAX);
        std::queue<int> next;

        next.push(node);
        distances[node] = 0;

        while (!next.empty())
        {
            int parent = next.front();
            next.pop();

            for (int i = 0; i < list[parent].size(); i++)
            {
                if (list[parent][i]->weight + distances[parent] < distances[list[parent][i]->destinationNode])
                {
                    distances[list[parent][i]->destinationNode] = list[parent][i]->weight + distances[parent];
                    next.push(list[parent][i]->destinationNode);
                    std::cout << "  New distance of " << distances[list[parent][i]->destinationNode] << " found for ";
                    std::cout << list[parent][i]->destinationNode << std::endl;
                }
                else
                {
                    std::cout << "   " << distances[list[parent][i]->destinationNode] << " is better than ";
                    std::cout << list[parent][i]->weight + distances[parent] << std::endl;
                }
            }
        }

        std::cout << "\nThe ending distances are..." << std::endl;
        for (int i = 0; i < distances.size(); i++)
        {
            std::cout << "   Node " << i << "\'s shortest distance is " << distances[i] << std::endl;
        }
    }

    void bellmanFordShortest(int node)
    {
        if (node >= list.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::vector<int> distances(list.size(), INT_MAX);
        distances[node] = 0;

        for (int i = 0; i < list.size() - 1; i++)
        {
            std::cout << "\nNormalization at " << i + 1 << " out of " << list.size() - 1 << std::endl;
            for (int j = 0; j < list.size(); j++)
            {
                for (int k = 0; k < list[j].size(); k++)
                {
                    if (distances[j] == INT_MAX)
                    {
                        continue;
                    }
                    else if (distances[list[j][k]->destinationNode] > list[j][k]->weight + distances[j])
                    {
                        distances[list[j][k]->destinationNode] = list[j][k]->weight + distances[j];
                        std::cout << "   New better weight found for " << list[j][k]->destinationNode << " it is ";
                        std::cout << distances[list[j][k]->destinationNode] << std::endl;
                    }
                }
            }
        }

        for (int i = 0; i < list.size(); i++)
        {
            if (distances[i] == INT_MAX)
            {
                continue;
            }
            for (int j = 0; j < list[i].size(); j++)
            {
                if (distances[list[i][j]->destinationNode] > list[i][j]->weight + distances[i])
                {
                    std::cout << "\nGraph has a negative cycle..." << std::endl;
                    return;
                }
            }
        }
    }

    void floydWarshallShortest()
    {
        std::vector<std::vector<int>> allDist(list.size(), std::vector<int>(list.size(), INT_MAX));

        for (int i = 0; i < list.size(); i++)
        {
            allDist[i][i] = 0;
        }

        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list[i].size(); j++)
            {
                if (i == j)
                {
                    continue;
                }
                allDist[i][j] = list[i][j]->weight;
            }
        }

        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list.size(); j++)
            {
                for (int k = 0; k < list.size(); k++)
                {
                    if (allDist[i][k] == INT_MAX || allDist[j][k] == INT_MAX)
                    {
                        continue;
                    }
                    if (allDist[i][j] > allDist[i][k] + allDist[j][k])
                    {
                        allDist[i][j] = allDist[i][k] + allDist[j][k];
                    }
                }
            }
        }

        std::cout << "\nAll known distances..." << std::endl;
        for (int i = 0; i < allDist.size(); i++)
        {
            std::cout << " Starting from node " << i << std::endl;
            for (int j = 0; j < allDist[i].size(); j++)
            {
                std::cout << "   You can reach " << j << " with a weight of " << allDist[i][j] << std::endl;
            }
        }
    }

    void primMST(int node)
    {
        // pair is distance, source, destination
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Compare> cheapest;
        std::vector<bool> visited(list.size(), false);
        std::queue<int> traverse;

        if (node >= list.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        traverse.push(node);
        visited[node] = true;

        while (!traverse.empty())
        {
            int parent = traverse.front();
            traverse.pop();

            for (int i = 0; i < list[parent].size(); i++)
            {

                std::vector<int> temp = {list[parent][i]->weight, parent, list[parent][i]->destinationNode};
                cheapest.emplace(temp);
            }
            while (!cheapest.empty())
            {
                int weight = cheapest.top()[0];
                int source = cheapest.top()[1];
                int destination = cheapest.top()[2];
                cheapest.pop();

                if (!visited[destination])
                {
                    std::cout << "   New branch of minimum spanning tree added from " << source << " to ";
                    std::cout << destination << " with a weight of " << weight << std::endl;
                    traverse.push(destination);
                    visited[destination] = true;
                    break;
                }
            }
        }
    }

    void kruskalMST()
    {
        // pair is distance, source, destination
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Compare> cheapest;
        std::vector<bool> visited(list.size(), false);

        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list[i].size(); j++)
            {
                std::vector<int> temp = {list[i][j]->weight, i, list[i][j]->destinationNode};
                cheapest.emplace(temp);
            }
        }

        int edges = list.size();
        while (!cheapest.empty())
        {
            int weight = cheapest.top()[0];
            int source = cheapest.top()[1];
            int destination = cheapest.top()[2];
            cheapest.pop();

            if (visited[source] && visited[destination])
            {
                std::cout << "   Edge between " << source << " and " << destination << " of ";
                std::cout << weight << " causes a cycle; the edge can't be used." << std::endl;
            }
            else
            {
                visited[source] = true;
                visited[destination] = true;
                std::cout << "  Edge between " << source << " and " << destination << " of ";
                std::cout << weight << " is an MST branch!" << std::endl;
                edges--;
            }

            if (edges == 1)
            {
                return;
            }
        }
    }
};