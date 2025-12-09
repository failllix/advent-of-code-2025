#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

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

long get_size(tuple<long, long> a, tuple<long, long> b)
{
    long x = abs(get<0>(a) - get<0>(b)) + 1;
    long y = abs(get<1>(a) - get<1>(b)) + 1;

    return x * y;
}

vector<tuple<long, long>> coords;

int main()
{
    ifstream file("input-day-9.txt");
    string str;

    long output = 0;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        vector<string> coord_parts = split(str, ",");

        coords.push_back(make_tuple(stol(coord_parts[0]), stol(coord_parts[1])));

        cout << "\n------------------------------------------------";
    }

    vector<long> sizes;

    for (int i = 0; i < coords.size(); i++)
    {
        tuple<long, long> a = coords[i];
        for (int x = i + 1; x < coords.size(); x++)
        {
            tuple<long, long> b = coords[x];
            sizes.push_back(get_size(a, b));
        }
    }

    sort(sizes.begin(), sizes.end(), greater<>());

    output = sizes[0];

    cout
        << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
