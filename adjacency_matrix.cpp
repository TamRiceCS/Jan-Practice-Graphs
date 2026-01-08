#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class AdjacencyMatrix : public Graph
{
private:
    std::vector<std::vector<int>> matrix;

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
    }

    void outputGraph()
    {
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