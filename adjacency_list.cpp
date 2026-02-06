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
            list.push_back(links);
            links.clear();
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
        for (int i = 0; i < list.size(); i++)
        {
            std::cout << "\n"
                      << i << " has child(ren): ";
            for (int j = 0; j < list[i].size(); j++)
            {
                if (j != list[i].size() - 1)
                {
                    std::cout << "-> " << list[i][j]->destinationNode << ": " << list[i][j]->weight << ", ";
                }
                else
                {
                    std::cout << "-> " << list[i][j]->destinationNode << ": " << list[i][j]->weight;
                }
            }
            std::cout << std::endl;
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

    void kahnTopological()
    {
        std::vector<int> weightedness(list.size(), 0);

        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list[i].size(); j++)
            {
                weightedness[list[i][j]->destinationNode]++;
            }
        }

        std::queue<int> tour;
        std::queue<int> answer;
        int visits = 0;

        for (int i = 0; i < weightedness.size(); i++)
        {
            if (weightedness[i] == 0)
            {
                tour.push(i);
            }
        }

        while (!tour.empty() && visits <= list.size())
        {
            int parent = tour.front();
            tour.pop();
            answer.push(parent);
            visits++;

            for (int i = 0; i < list[parent].size(); i++)
            {
                int child = list[parent][i]->destinationNode;
                weightedness[child]--;
                if (weightedness[child] == 0)
                {
                    tour.push(child);
                }
            }
        }

        if (visits != list.size())
        {
            std::cout << " A topological sort is not possible..." << std::endl;
            return;
        }

        visits = 0;
        std::cout << "\nThe topological sort is as follows: " << std::endl;
        while (!answer.empty())
        {
            std::cout << "  " << visits << "th : " << answer.front() << " node" << std::endl;
            visits++;
            answer.pop();
        }
    }

    bool fordBFS(int source, int destination, std::vector<Node *> &edges, std::vector<std::vector<Node *>> residual)
    {
        std::queue<int> travel;
        std::vector<bool> visited(residual.size(), false);

        travel.push(source);
        visited[source] = true;

        while (!travel.empty())
        {
            int worker = travel.front();
            travel.pop();

            for (int i = 0; i < residual[worker].size(); i++)
            {
                int child = residual[worker][i]->destinationNode;
                int edgeWeight = residual[worker][i]->weight;

                if (!visited[child] && residual[worker][i]->weight != 0)
                {
                    visited[child] = true;
                    Node *edgeIndex = new Node(worker, edgeWeight);
                    edges[child] = edgeIndex;

                    if (child == destination)
                    {
                        return true;
                    }

                    travel.push(child);
                }
            }
        }
        return false;
    }

    void fordFulkersonFlow(int source, int destination)
    {

        int count = 0;

        if (source > list.size() || destination > list.size())
        {
            std::cout << "The source or destination is not within range..." << std::endl;
            return;
        }

        std::cout << "Starting Ford Fulkerson..." << std::endl;

        std::vector<std::vector<Node *>>
            residual(list.size()); // this will need to be deleted at end

        for (int i = 0; i < list.size(); i++)
        {
            for (int j = 0; j < list[i].size(); j++)
            {
                Node *rIndex = new Node(list[i][j]->destinationNode, list[i][j]->weight);
                residual[i].push_back(rIndex);
            }
        }

        std::vector<Node *> edges(list.size(), NULL); // this will need to be deleted at end of every iter
        int maxFlow = 0;

        while (fordBFS(source, destination, edges, residual))
        {
            count++;
            std::cout << std::endl;
            int pathFlow = INT_MAX;

            for (int i = destination; i != source; i = edges[i]->destinationNode)
            {
                pathFlow = std::min(pathFlow, edges[i]->weight);
                std::cout << " Used path from " << edges[i]->destinationNode << " to " << i << std::endl;
            }

            std::cout << "  Max path flow is: " << pathFlow << std::endl;
            maxFlow += pathFlow;

            for (int i = destination; i != source; i = edges[i]->destinationNode)
            {
                int sourceNode = edges[i]->destinationNode;

                for (int j = 0; j < residual[sourceNode].size(); j++)
                {
                    if (residual[sourceNode][j]->destinationNode == i)
                    {
                        residual[sourceNode][j]->weight -= pathFlow;
                        std::cout << "   +Forward Edge " << sourceNode << " -> " << residual[sourceNode][j]->destinationNode;
                        std::cout << " of " << residual[sourceNode][j]->weight << std::endl;

                        break;
                    }
                }

                // backward edge
                for (int j = 0; j < residual[i].size() + 1; j++)
                {
                    if (j == residual[i].size())
                    {
                        Node *edgeIndex = new Node(sourceNode, pathFlow);
                        std::cout << "   -Backward edge " << i << " -> " << sourceNode;
                        std::cout << " of " << pathFlow << std::endl;
                        residual[i].push_back(edgeIndex);
                        break;
                    }
                    else if (residual[i][j]->destinationNode == sourceNode)
                    {
                        residual[i][j]->weight += pathFlow;
                        std::cout << "   -Backward edge " << i << " -> " << residual[i][j]->destinationNode;
                        std::cout << " of " << residual[i][j]->weight << std::endl;
                        break;
                    }
                }
            }

            for (int i = 0; i < edges.size(); i++)
            {
                delete edges[i];
            }

            edges.resize(list.size(), NULL);
        }
        std::cout << "\nThe max flow of this graph is " << maxFlow << std::endl;
    }
};