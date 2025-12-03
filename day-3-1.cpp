#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream file("input-day-3.txt");
    string str;

    long output;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        const std::vector<char> joltages = vector<char>(str.begin(), str.end());

        int highestDecimal = 0;
        int highestDecimalIndex = 0;
        for (int decimalIndex = 0; decimalIndex < str.length() - 1; decimalIndex++)
        {
            int curr = joltages[decimalIndex] - '0';
            if (curr > highestDecimal)
            {
                highestDecimal = curr;
                highestDecimalIndex = decimalIndex;
            }
        }

        int highestOne = 0;
        for (int oneIndex = highestDecimalIndex + 1; oneIndex < str.length(); oneIndex++)
        {
            int curr = joltages[oneIndex] - '0';
            if (curr > highestOne)
            {
                highestOne = curr;
            }
        }

        string num = to_string(highestDecimal) + to_string(highestOne);

        output = output + stol(num);

        cout
            << "\n------------------------------------------------";
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
