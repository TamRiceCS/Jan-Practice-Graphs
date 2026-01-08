#include <iostream>
#include <string>
#include "graph.cpp"
#include "adjacency_matrix.cpp"

bool buildMenu(char &userChar)
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
        while (true)
        {
            std::cin.clear();
            std::cout << "Please enter the name of the file containing a graph... " << std::endl;
            std::cout << "\nYour input: ";
            std::cin >> fileName;

            Graph *example = new AdjacencyMatrix(fileName);
            example->outputGraph();
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
        return false;
    }
    }
    return true;
}

bool optionMenu(char &userChar)
{
    std::cout << "Pick an algorithm to run on your graph..." << std::endl;
    std::cout << "   Press \'x\' to exit the program..." << std::endl;

    std::cout << "\nYour input: ";
    std::cin.clear();
    std::cin >> userChar;

    switch (userChar)
    {
    case 'x':
    {
        return false;
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

    // Graph *example = new AdjacencyMatrix("basic_matrix.txt");
    // example->setAsList();
    // example->outputGraph();

    while (progress)
    {
        progress = buildMenu(userChar);
    }

    std::cout << "Thank you, bye!\n"
              << std::endl;

    return 0;
}