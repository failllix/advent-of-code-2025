#include <fstream>
#include <string>
#include <iostream>

int main()
{
    std::ifstream file("input-day-1.txt");
    std::string str;

    std::int32_t position = 50;
    std::int32_t password;

    while (std::getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        std::cout << "\n------------------------------------------------";
        std::cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        std::string prefix = str.substr(0, 1);
        std::int8_t value = std::stoi(str.substr(1, str.length())) % 100;
        std::cout << "\nprefix: " + prefix;
        std::cout << "\nraw value: " + std::to_string(value);

        if (prefix == "L")
        {
            value = value * -1;
        }

        std::cout << "\ncalculated value: " + std::to_string(value);

        std::cout << "\nold position:" + std::to_string(position);
        position = position + value;
        std::cout << "\nraw new position:" + std::to_string(position);

        if (position < 0)
        {
            position = 100 - (position * -1);
        }

        if (position > 99)
        {
            position = position - 100;
        }
        std::cout << "\nadjusted position: " + std::to_string(position);

        if (position == 0)
        {
            password++;
        }
        std::cout << "\n------------------------------------------------";
    }

    std::cout << "\n\n====\n";
    std::cout << std::to_string(password);
    std::cout << "\n";
}
