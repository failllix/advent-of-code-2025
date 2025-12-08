#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <set>

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

double get_distance(string coord_a, string coord_b)
{
    vector<string> parts_s_a = split(coord_a, ",");
    vector<string> parts_s_b = split(coord_b, ",");

    vector<int> parts_a;

    for (const string &a : parts_s_a)
    {
        parts_a.push_back(stoi(a));
    }

    vector<int> parts_b;

    for (const string &b : parts_s_b)
    {
        parts_b.push_back(stoi(b));
    }

    return sqrt(pow(parts_a[0] - parts_b[0], 2) + pow(parts_a[1] - parts_b[1], 2) + pow(parts_a[2] - parts_b[2], 2));
}

vector<string> coords;

int main()
{
    ifstream file("input-day-8.txt");
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

        coords.push_back(str);

        cout << "\n------------------------------------------------";
    }

    vector<tuple<string, double>> distances;

    for (int i = 0; i < coords.size(); i++)
    {
        string curr = coords[i];
        for (int y = i + 1; y < coords.size(); y++)
        {
            string compare = coords[y];
            tuple<string, double> el(curr + "|" + compare, get_distance(curr, compare));
            distances.push_back(el);
        }
    }

    sort(distances.begin(), distances.end(), [](const auto &lhs, const auto &rhs)
         { return get<1>(lhs) < get<1>(rhs); });

    vector<set<string>> circuits;

    for (string &coord : coords)
    {
        set<string> base = {coord};
        circuits.push_back(base);
    }

    int i = 0;

    while (circuits.size() > 1)
    {
        tuple<string, double> distance = distances[i];
        i++;
        vector<string> pair = split(get<0>(distance), "|");
        string a = pair[0];
        string b = pair[1];

        int index_with_a;
        int index_with_b;

        for (int i = 0; i < circuits.size(); i++)
        {
            set<string> curr = circuits[i];
            if (curr.count(a))
            {
                index_with_a = i;
            }
            if (curr.count(b))
            {
                index_with_b = i;
            }
        }

        if (index_with_a == index_with_b)
        {
            continue;
        }

        circuits[index_with_a].insert(circuits[index_with_b].begin(), circuits[index_with_b].end());
        circuits.erase(circuits.begin() + index_with_b);
        if (circuits.size() == 1)
        {
            output = stoi(split(a, ",")[0]) * stoi(split(b, ",")[0]);
        }
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
