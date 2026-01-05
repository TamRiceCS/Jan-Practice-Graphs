#include <iostream>
#include <string>

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

    switch (userChar)
    {
    case '1':
    {
        std::cout << "\nYou selected option 1..." << std::endl;
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

    while (progress)
    {
        progress = buildMenu(userChar);
    }

    std::cout << "Thank you, bye!\n"
              << std::endl;

    return 0;
}