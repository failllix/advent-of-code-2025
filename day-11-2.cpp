#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
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

unordered_map<string, long> cache;

long recursion(string current_node, unordered_map<string, vector<string>> &nodes, bool visited_dac, bool visited_fft)
{
    string key = current_node + to_string(visited_dac) + to_string(visited_fft);
    if (cache.count(key))
    {
        return cache[key];
    }

    if (current_node == "dac")
    {
        visited_dac = true;
    }

    if (current_node == "fft")
    {
        visited_fft = true;
    }

    if (current_node == "out")
    {
        if (visited_dac && visited_fft)
        {
            return 1;
        }
        return 0;
    }

    long sum = 0;
    for (string &c : nodes[current_node])
    {
        sum += recursion(c, nodes, visited_dac, visited_fft);
    }

    cache[key] = sum;
    return cache[key];
}

int main()
{
    ifstream file("input-day-11.txt");
    string str;

    long output = 0;

    unordered_map<string, vector<string>> nodes;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        vector<string> parts = split(str, ": ");

        vector<string> connections = split(parts[1], " ");

        string key = parts[0];
        nodes[key] = connections;

        cout << "\n------------------------------------------------";
    }

    output = recursion("svr", nodes, false, false);

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
