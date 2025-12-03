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

        string num = "";

        int remaining_length = 12;
        int maxIndex = 0;
        while (remaining_length > 0)
        {
            int highestNum = 0;
            for (int i = maxIndex; i < str.length() - remaining_length + 1; i++)
            {
                int curr = joltages[i] - '0';
                if (curr > highestNum)
                {
                    highestNum = curr;
                    maxIndex = i + 1;
                }
            }
            num += to_string(highestNum);
            remaining_length--;
        }
        cout
            << "\n"
            << num;
        output += stol(num);

        cout
            << "\n------------------------------------------------";
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
