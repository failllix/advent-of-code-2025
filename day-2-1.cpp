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

int64_t buildLowestNumberOfLength(int64_t length)
{
    std::string num = "1";
    for (int64_t i = 1; i < length; i++)
    {
        num = num + "0";
    }
    return std::stoi(num);
}

std::vector<long> getIdsForStartingHalf(std::string start_half, long max_value)
{
    std::vector<long> values;

    long half = std::stol(start_half);
    std::string half_string = std::to_string(half);
    long curr = std::stol(half_string + half_string);
    while (curr <= max_value)
    {
        values.push_back(curr);
        half = half + 1;
        half_string = std::to_string(half);
        curr = std::stol(half_string + half_string);
    }

    return values;
}

int main()
{
    std::ifstream file("input-day-2.txt");
    std::string str;

    long sum;

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

            std::cout << "\nlengths: "
                      << std::to_string(lower_bound.length())
                      << " / "
                      << std::to_string(upper_bound.length());

            if (upper_bound.length() == lower_bound.length() && lower_bound.length() % 2 == 1)
            {
                std::cout << "\nSkipping numbers of uneven length, where range does not allow numbers with even length";
                continue;
            }

            int64_t min_length_of_half = (lower_bound.length() + 2 - 1) / 2;

            std::cout << "\nmin length of half for next invalid id: "
                      << std::to_string(min_length_of_half);

            long left;

            if (lower_bound.length() % 2 == 1)
            {
                left = buildLowestNumberOfLength(min_length_of_half);
            }
            else
            {
                left = std::stol(lower_bound.substr(0, min_length_of_half));
                long right = std::stol(lower_bound.substr(min_length_of_half, lower_bound.length()));

                if (right > left)
                {
                    left++;
                }
            }

            std::cout << "\nStarting left half: "
                      << std::to_string(left);

            std::cout << "\nbounds: "
                      << lower_bound
                      << " / "
                      << upper_bound;

            std::vector<long> ids = getIdsForStartingHalf(std::to_string(left), std::stol(upper_bound));

            for (const long &id : ids)
            {
                std::cout
                    << "\n"
                    << std::to_string(id);
                sum = sum + id;
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
