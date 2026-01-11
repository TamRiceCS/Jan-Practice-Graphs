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
};