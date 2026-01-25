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
            }
        }
        catch (...)
        {
            std::cout << "Something went wrong with the file... Please try again..." << std::endl;
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
};