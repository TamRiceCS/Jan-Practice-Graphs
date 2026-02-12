class AdjacencyMatrix : public Graph
{
private:
    std::vector<std::vector<int>> matrix;

    void checkValidity()
    {
        if (matrix.size() == 0)
        {
            matrix.clear();
            setValid(false);
            std::cout << "\nThe graph is invalid, empty matrixes are not accepted...";
            return;
        }

        int nodesNum = matrix[0].size();

        for (int i = 0; i < matrix.size(); i++)
        {
            if (matrix[i].size() == 0 || matrix[i].size() != nodesNum)
            {
                std::cout << "\nThe graph is invalid, wrong amount of nodes on line " << i + 1 << "...";
                matrix.clear();
                setValid(false);
                return;
            }
        }

        std::cout << "\nThe graph is valid...";
        setValid(true);
    }

public:
    AdjacencyMatrix(std::string fileName)
    {
        std::ifstream vectorFile(fileName);
        try
        {
            if (!vectorFile.is_open())
            {
                std::cout << "Could not open the file..." << std::endl;
                setValid(false);
                return;
            }
        }
        catch (...)
        {
            std::cout << "Something went wrong with the file... Please try again..." << std::endl;
            setValid(false);
            return;
        }

        int number = 0;
        int sign = 1;
        std::string fileLine = "";

        while (std::getline(vectorFile, fileLine))
        {
            std::vector<int> adjacencies;
            int number = 0;
            if (matrix.size() == 10)
            {
                std::cout << "Your graph has too many nodes..." << std::endl;
                matrix.clear();
                return;
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
                    std::cout << "Your graph contains a node not within the valid range..." << std::endl;
                    matrix.clear();
                    return;
                }
                else if (fileLine[i] == ',' || fileLine[i] == ']')
                {
                    adjacencies.push_back(number);
                    number = 0;
                    sign = 1;
                }
            }
            matrix.push_back(adjacencies);
            adjacencies.clear();
        }

        checkValidity();
        setAsMatrix();
    }

    void outputGraph()
    {
        if (matrix.size() == 0)
        {
            return;
        }

        std::cout << "\n";
        for (int i = 0; i < matrix.size(); i++)
        {
            std::cout << "[";
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (j != matrix[i].size() - 1)
                {
                    std::cout << matrix[i][j] << ", ";
                }
                else
                {
                    std::cout << matrix[i][j] << "]" << std::endl;
                }
            }
        }
    }

    void connectivity()
    {
        std::vector<bool> visited(matrix.size(), false);
        std::queue<int> traverse;

        std::cout << "\nThe graph has the following components..." << std::endl;
        std::cout << "   ";

        for (int i = 0; i < matrix.size(); i++)
        {
            if (visited[i])
            {
                continue;
            }

            traverse.push(i);
            visited[i] = true;
            std::cout << " " << i;

            while (!traverse.empty())
            {
                int top = traverse.front();
                traverse.pop();

                for (int j = 0; j < matrix[i].size(); j++)
                {
                    // check top -> n
                    if (matrix[i][j] != 0 && !visited[j])
                    {
                        std::cout << " " << j;
                        traverse.push(j);
                        visited[j] = true;
                    }

                    // check n -> top (if top is a destination it's still part of the component)
                    else if (matrix[j][i] != 0 && !visited[j])
                    {
                        std::cout << " " << j;
                        traverse.push(j);
                        visited[j] = true;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void directedness()
    {
        setDirectedness(true);
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] != 0 && (matrix[i][j] != matrix[j][i]))
                {
                    setDirectedness(false);
                    break;
                }
            }
        }

        if (getDirectedness())
        {
            std::cout << "The graph is directed." << std::endl;
        }

        else
        {
            std::cout << "The graph is NOT directed." << std::endl;
        }
    }

    void BFStraversal(int node)
    {
        if (node >= matrix.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::queue<int> adjacencies;
        std::vector<bool> visited(matrix.size(), false);

        adjacencies.push(node);

        while (!adjacencies.empty())
        {
            int parent = adjacencies.front();
            std::cout << "   Visited " << parent << std::endl;
            adjacencies.pop();
            visited[parent] = true;

            for (int i = 0; i < matrix[parent].size(); i++)
            {
                if (!visited[i] && matrix[parent][i] != 0)
                {
                    adjacencies.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    void DFStraversal(int node)
    {
        if (node >= matrix.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::stack<int> adjacencies;
        std::vector<bool> visited(matrix.size(), false);

        adjacencies.push(node);

        while (!adjacencies.empty())
        {
            int parent = adjacencies.top();
            std::cout << "   Visited " << parent << std::endl;
            adjacencies.pop();
            visited[parent] = true;

            for (int i = 0; i < matrix[parent].size(); i++)
            {
                if (!visited[i] && matrix[parent][i] != 0)
                {
                    adjacencies.push(i);
                    visited[i] = true;
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

        if (node >= matrix.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::vector<int> distances(matrix.size(), INT_MAX);
        std::queue<int> next;

        next.push(node);
        distances[node] = 0;

        while (!next.empty())
        {
            int parent = next.front();
            next.pop();

            for (int i = 0; i < matrix[parent].size(); i++)
            {
                if ((distances[parent] + matrix[parent][i] < distances[i]) && matrix[parent][i] != 0)
                {
                    distances[i] = distances[parent] + matrix[parent][i];
                    next.push(i);
                    std::cout << "  New distance of " << distances[i] << " found for " << i << std::endl;
                }
                else if (matrix[parent][i] != 0)
                {
                    std::cout << "   " << distances[i] << " is better than " << distances[parent] + matrix[parent][i] << std::endl;
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
        if (node >= matrix.size())
        {
            std::cout << "This node is out of bounds, please try again." << std::endl;
            return;
        }

        std::vector<int> distances(matrix.size(), INT_MAX);
        distances[node] = 0;

        for (int k = 0; k < matrix.size() - 1; k++)
        {
            std::cout << "\nNormalization at " << k + 1 << " out of " << matrix.size() - 1 << std::endl;
            for (int i = 0; i < matrix.size(); i++)
            {
                for (int j = 0; j < matrix[i].size(); j++)
                {
                    if (matrix[i][j] == 0 || distances[i] == INT_MAX)
                    {
                        continue;
                    }
                    else if (distances[j] > matrix[i][j] + distances[i])
                    {
                        distances[j] = matrix[i][j] + distances[i];
                        std::cout << "   New better weight found for " << j << " it is " << distances[j] << std::endl;
                    }
                }
            }
        }

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] == 0)
                {
                    continue;
                }
                else if (distances[j] > matrix[i][j] + distances[i])
                {
                    std::cout << "\nGraph has a negative cycle..." << std::endl;
                    return;
                }
            }
        }

        std::cout << "\nThe ending distances are..." << std::endl;
        for (int i = 0; i < distances.size(); i++)
        {
            if (distances[i] != INT_MAX)
            {
                std::cout << "   Node " << i << "\'s shortest distance is " << distances[i] << std::endl;
            }
            else
            {
                std::cout << "   Node " << i << " could not be accessed from the starting node of " << node << std::endl;
            }
        }
    }

    void floydWarshallShortest()
    {
        std::vector<std::vector<int>> allDist(matrix.size(), std::vector<int>(matrix[0].size(), INT_MAX));

        for (int i = 0; i < matrix.size(); i++)
        {
            allDist[i][i] = 0;
        }

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (matrix[i][j] != 0)
                {
                    allDist[i][j] = matrix[i][j];
                }
            }
        }

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                for (int k = 0; k < matrix[j].size(); k++)
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
        std::vector<bool> visited(matrix.size(), false);
        std::queue<int> traverse;

        if (node >= matrix.size())
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

            for (int i = 0; i < matrix[parent].size(); i++)
            {
                if (matrix[parent][i] != 0)
                {
                    std::vector<int> temp = {matrix[parent][i], parent, i};
                    cheapest.emplace(temp);
                }
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
        std::vector<bool> visited(matrix.size(), false);

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                if (matrix[i][j] != 0)
                {
                    std::vector<int> temp = {matrix[i][j], i, j};
                    cheapest.emplace(temp);
                }
            }
        }

        int edges = matrix.size();
        while (!cheapest.empty())
        {
            int weight = cheapest.top()[0];
            int source = cheapest.top()[1];
            int destination = cheapest.top()[2];
            cheapest.pop();

            if (visited[source] && visited[destination])
            {
                std::cout << "   Edge between " << source << " and " << destination << " of ";
                std::cout << weight << " causes a cycle and can't be used." << std::endl;
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
        // TODO: Implement checks that the graph is a DAG before implementation
        std::vector<int> weightedness(matrix.size(), 0);

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] != 0)
                {
                    weightedness[j]++;
                }
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

        while (!tour.empty() && visits <= matrix.size())
        {
            int parent = tour.front();
            tour.pop();
            answer.push(parent);
            visits++;

            for (int i = 0; i < matrix[parent].size(); i++)
            {
                if (matrix[parent][i] != 0)
                {
                    weightedness[i]--;
                    if (weightedness[i] == 0)
                    {
                        tour.push(i);
                    }
                }
            }
        }

        if (visits != matrix.size())
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

    bool fordBFS(int source, int destination, std::vector<int> &edges, std::vector<std::vector<int>> residual)
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
                if (residual[worker][i] > 0 && !visited[i])
                {
                    visited[i] = true;
                    edges[i] = worker;

                    if (i == destination)
                    {
                        return true;
                    }
                    travel.push(i);
                }
            }
        }
        return false;
    }

    void fordFulkersonFlow(int source, int destination)
    {

        if (source > matrix.size() || destination > matrix.size())
        {
            std::cout << "The source or destination is not within range..." << std::endl;
            return;
        }

        std::vector<std::vector<int>> residual(matrix.size());
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                residual[i].push_back(matrix[i][j]);
            }
        }

        std::vector<int> edges(matrix.size(), -1);
        int maxFlow = 0;

        std::cout << "\nStarting Ford Fulkerson" << std::endl;
        while (fordBFS(source, destination, edges, residual))
        {
            std::cout << std::endl;
            int pathFlow = INT_MAX;
            for (int i = destination; i != source; i = edges[i])
            {
                pathFlow = std::min(pathFlow, residual[edges[i]][i]);
                std::cout << "   Used path from " << edges[i] << " to " << i << std::endl;
            }

            std::cout << "   Max path flow is: " << pathFlow << std::endl;

            // starting from the destination
            // as long as we aren't at the source
            // travel to the node's parent

            // this works because it's going from child node to parent node.
            // the child then becomes the parent and the process repeats.
            for (int i = destination; i != source; i = edges[i])
            {
                if (edges[i] == -1)
                {
                    continue;
                }
                residual[edges[i]][i] -= pathFlow;
                residual[i][edges[i]] += pathFlow;
            }

            edges.assign(matrix.size(), -1);
            maxFlow += pathFlow;
        }

        std::cout << "\nThe max flow of this graph is " << maxFlow << std::endl;
    }
};