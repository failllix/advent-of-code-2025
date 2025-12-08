#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, long> cache;

long recursion(int starting_index, vector<string> remaining)
{
    if (remaining.empty())
    {
        return 1;
    }

    string key = to_string(starting_index) + "|" + to_string(remaining.size());

    if (cache.count(key))
    {
        return cache[key];
    }

    string curr_line = remaining[0];
    int last_index_of_split = -1;

    while (curr_line.find('^', last_index_of_split + 1) != string::npos)
    {
        last_index_of_split = curr_line.find('^', last_index_of_split + 1);

        if (last_index_of_split == starting_index)
        {
            cache[key] = recursion(starting_index - 1, vector(remaining.begin() + 1, remaining.end())) + recursion(starting_index + 1, vector(remaining.begin() + 1, remaining.end()));
            return cache[key];
        }
    }

    return recursion(starting_index, vector(remaining.begin() + 1, remaining.end()));
}

int main()
{
    ifstream file("input-day-7.txt");
    string str;

    vector<string> lines;

    long output = 0;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        lines.push_back(str);

        cout << "\n------------------------------------------------";
    }

    output = recursion(lines[0].find('S'), vector(lines.begin() + 1, lines.end()));

    cout
        << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
