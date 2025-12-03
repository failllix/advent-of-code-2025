#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    std::ifstream file("input-day-xx.txt");
    std::string str;

    long output;

    while (std::getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        std::cout << "\n------------------------------------------------";
        std::cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        std::cout << "\n------------------------------------------------";
    }

    std::cout << "\n\n====\n";
    std::cout << std::to_string(output);
    std::cout << "\n";
}
