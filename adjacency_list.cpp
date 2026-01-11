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
};