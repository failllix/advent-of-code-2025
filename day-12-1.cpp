#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main()
{
    ifstream file("input-day-12.txt");
    string str;

    long output = 0;

    vector<string> lines;

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

    vector<string> shapes_input(lines.begin(), lines.begin() + 24);
    vector<string> test_cases(lines.begin() + 24, lines.end());

    vector<tuple<long, vector<int>>> inputs;
    for (string &s : test_cases)
    {
        vector<string> parts = split(s, ": ");
        vector<string> size_parts = split(parts[0], "x");
        vector<int> sizes;
        transform(size_parts.begin(), size_parts.end(), back_inserter(sizes), [](auto num_str)
                  { return stoi(num_str); });

        vector<string> present_parts = split(parts[1], " ");
        vector<int> presents_count;
        transform(present_parts.begin(), present_parts.end(), back_inserter(presents_count), [](auto num_str)
                  { return stoi(num_str); });

        inputs.push_back(make_tuple(sizes[0] * sizes[1], presents_count));
    }

    vector<tuple<long, vector<int>>> maybe_valid_inputs;
    copy_if(inputs.begin(), inputs.end(), back_inserter(maybe_valid_inputs), [](auto input)
            { return get<0>(input) >= reduce(get<1>(input).begin(), get<1>(input).end()) * 9; });

    // As many others I was surprised that this is already the solution.
    // Apparently just ruling out all obviously impossible solutions is enough.
    // Every other input seems to have _some_ solution.

    output = maybe_valid_inputs.size();

    cout
        << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
