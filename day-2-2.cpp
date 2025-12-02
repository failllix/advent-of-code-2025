#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <bitset>

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

bool isInvalidId(long id_to_check)
{
    std::string id = std::to_string(id_to_check);

    for (int i = 1; i < id.length(); i++)
    {
        if (id.length() % i == 0)
        {
            std::string pattern_to_check = id.substr(0, i);

            bool irregularityFound = false;
            for (int x = 1; x < id.length() / i; x++)
            {
                if (pattern_to_check != id.substr(i * x, i))
                {
                    irregularityFound = true;
                    break;
                }
            }
            if (!irregularityFound)
            {

                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::ifstream file("input-day-2.txt");
    std::string str;

    long sum = 0;

    while (std::getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        std::cout << "\n------------------------------------------------";
        std::cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        std::vector<std::string> ids = split(str, ",");

        for (const std::string id : ids)
        {
            std::cout << "\n..............................";
            std::cout << "\nid: " + id;

            std::vector<std::string> id_parts = split(id, "-");

            std::string lower_bound = id_parts[0];
            std::string upper_bound = id_parts[1];

            std::cout << "\nbounds: "
                      << lower_bound
                      << " / "
                      << upper_bound;

            for (long curr = std::stol(lower_bound); curr <= std::stol(upper_bound); curr++)
            {
                if (isInvalidId(curr))
                {
                    sum = sum + curr;
                }
            }

            std::cout
                << "\n..............................";
        }

        std::cout << "\n------------------------------------------------";
    }

    std::cout << "\n\n====\n";
    std::cout << std::to_string(sum);
    std::cout << "\n";
}
