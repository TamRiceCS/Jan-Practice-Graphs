#include <iostream>
#include <string>
#include "graph.cpp"
#include "adjacency_matrix.cpp"

Graph *buildMenu(char &userChar, bool &progress)
{
    // will need to later include graph variable as a parameter
    std::cout << "\n\nPlease generate a graph to work with, empty graphs (no nodes) are invalid." << std::endl;
    std::cout << "   1. Generate an adjacency matrix (2D Matrix)..." << std::endl;
    std::cout << "   2. Generate an adjacency list (Vector of Nodes)..." << std::endl;
    std::cout << "   Press \'x\' to exit the program..." << std::endl;

    std::cout << "\nYour input: ";
    std::cin.clear();
    std::cin >> userChar;

    std::string fileName = "";

    switch (userChar)
    {
    case '1':
    {
        std::cout << "\nYou selected option 1..." << std::endl;
        std::cin.clear();
        std::cout << "   Please enter the name of the file containing a graph... " << std::endl;
        std::cout << "\nYour input: ";
        std::cin >> fileName;

        Graph *example = new AdjacencyMatrix(fileName);
        example->outputGraph();

        if (example->getValidity())
        {
            progress = true;
            return example;
        }
        break;
    }
    case '2':
    {
        std::cout << "\nYou selected option 1..." << std::endl;
        break;
    }
    case 'x':
    {
        progress = false;
        return NULL;
    }
    }
    progress = true;
    return NULL;
}

char optionMenu(char &userChar)
{
    std::cout << "\nPick an algorithm to run on your graph..." << std::endl;
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
    // include a generic graph variable

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
            char event = optionMenu(userChar);
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