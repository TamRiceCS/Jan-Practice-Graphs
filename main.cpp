#include <iostream>
#include <string>
#include "graph.cpp"
#include "adjacency_matrix.cpp"
#include "adjacency_list.cpp"

Graph *buildMenu(char &userChar, bool &progress)
{
    // will need to later include graph variable as a parameter
    std::cout << "\n\nPlease generate a graph to work with, empty graphs (no nodes) are invalid. All nodes are zero indexed..." << std::endl;
    std::cout << "   1. Generate an adjacency matrix (2D Matrix)..." << std::endl;
    std::cout << "   2. Generate an adjacency list (Vector of Nodes)..." << std::endl;
    std::cout << "   Press \'x\' to exit the program..." << std::endl;

    std::cout << "\nYour input: ";
    std::cin.clear();
    std::cin >> userChar;
    std::string fileName = "";

    Graph *example = NULL;

    switch (userChar)
    {
    case '1':
    {
        std::cout << "\nYou selected option 1..." << std::endl;
        std::cin.clear();
        std::cout << "   Please enter the name of the file containing a graph..." << std::endl;
        std::cout << "   0s are treated as empty spots, Valid weights range [-999, 999], valid nodes range [1,10]..." << std::endl;
        std::cout << "\nYour input: ";
        std::cin >> fileName;

        example = new AdjacencyMatrix(fileName);
        example->outputGraph();

        if (example->getValidity())
        {
            progress = true;
            return example;
        }
        else
        {
            std::cout << "   The given graph is not valid..." << std::endl;
        }
        break;
    }
    case '2':
    {
        std::cout << "\nYou selected option 2..." << std::endl;
        std::cin.clear();
        std::cout << "   Please enter the name of the file containing a graph..." << std::endl;
        std::cout << "   -0 is an empry node, valid weights range [-999, 999], valid nodes range [1,10]..." << std::endl;
        std::cout << "\nYour input: ";
        std::cin >> fileName;

        example = new AdjacencyList(fileName);
        example->outputGraph();

        if (example->getValidity())
        {
            return example;
        }
        else
        {
            std::cout << "   The given graph is not valid..." << std::endl;
            delete example;
            example = NULL;
        }
        break;
    }
    case 'x':
    {
        progress = false;
        return NULL;
    }
    }
    progress = true;
    return example;
}

char optionMenu(char &userChar, Graph *example)
{
    std::cout << "\nPick an algorithm to run on your graph..." << std::endl;
    std::cout << "   1. Run BFS algorithm..." << std::endl;
    std::cout << "   2. Run DFS algorithm..." << std::endl;
    std::cout << "   3. Run Dijksta's Shortest Path algorithm..." << std::endl;
    std::cout << "   4. Run Bellman Foed's Shortest Path algorithm..." << std::endl;
    std::cout << "   Press \'b\' to enter another graph..." << std::endl;
    std::cout << "   Press \'x\' to exit the program..." << std::endl;

    std::cout << "\nYour input: ";
    std::cin.clear();
    std::cin >> userChar;

    switch (userChar)
    {
    case 'x':
    {
        return 'x';
    }
    case '1':
    {
        std::cout << "\nYou selected option 1..." << std::endl;
        std::cout << "   What node would you like to start BFS at?" << std::endl;

        int node = 0;
        std::cout << "\nYour input: ";
        std::cin.clear();
        std::cin >> node;

        example->BFStraversal(node);
    }
    case '2':
    {
        std::cout << "\nYou selected option 2..." << std::endl;
        std::cout << "   What node would you like to start DFS at?" << std::endl;

        int node = 0;
        std::cout << "\nYour input: ";
        std::cin.clear();
        std::cin >> node;

        example->DFStraversal(node);
    }
    case '3':
    {
        std::cout << "\nYou selected option 3..." << std::endl;
        std::cout << "   What node would you like to start Dijkstra's Shortest Path Algorithm at?" << std::endl;

        int node = 0;
        std::cout << "\nYour input: ";
        std::cin.clear();
        std::cin >> node;

        example->dijkstraShortest(node);
    }
    case '4':
    {
        std::cout << "\nYou selected option 2..." << std::endl;
        std::cout << "   What node would you like to start Bellman-Ford's Shortest Path Algorithm at?" << std::endl;

        int node = 0;
        std::cout << "\nYour input: ";
        std::cin.clear();
        std::cin >> node;

        example->bellmanFordShortest(node);
    }
    default:
    {
        return userChar;
    }
    }

    return true;
}

int main()
{
    char userChar = '-';
    std::string userStr = "";
    bool progress = true;

    std::cout << "\nWelcome to my graph practice code." << std::endl;
    Graph *example = NULL;

    while (progress)
    {
        if (example == NULL)
        {
            example = buildMenu(userChar, progress);
        }
        else
        {
            char event = optionMenu(userChar, example);
            if (event == 'x')
            {
                progress = false;
            }
            else if (event == 'b')
            {
                delete example;
                example = NULL;
            }
        }
    }

    std::cout << "Thank you, bye!\n"
              << std::endl;

    return 0;
}