#include <fstream>
#include <string>
#include <iostream>

int main()
{
    std::ifstream file("input-day-1.txt");
    std::string str;

    std::int32_t position = 50;
    std::int32_t previous_position;
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
        std::cout << "\nprefix: " + prefix;
        std::int32_t value = std::stoi(str.substr(1, str.length()));
        std::cout << "\nraw value: " + std::to_string(value);

        std::int32_t position_update = value % 100;
        std::cout << "\nposition update: " + std::to_string(position_update);
        std::int32_t rotations = value / 100;
        std::cout << "\nadditional rotations: " + std::to_string(rotations);
        password = password + rotations;

        if (prefix == "L")
        {
            position_update = position_update * -1;
        }
        std::cout << "\ncalculated value: " + std::to_string(position_update);

        std::cout << "\nold position:" + std::to_string(position);
        previous_position = position;
        position = position + position_update;
        std::cout << "\nraw new position:" + std::to_string(position);

        if (position < 0)
        {
            position = 100 - (position * -1);
            if (previous_position != 0 && position != 0)
            {
                password++;
            }
        }

        if (position > 99)
        {
            position = position - 100;
            if (previous_position != 0 && position != 0)
            {
                password++;
            }
        }
        std::cout << "\nadjusted position: " + std::to_string(position);

        if (position == 0)
        {
            password++;
        }
        std::cout << "\npassword: " + std::to_string(password);
        std::cout << "\n------------------------------------------------";
    }

    std::cout << "\n\n====\n";
    std::cout << std::to_string(password);
    std::cout << "\n";
}
