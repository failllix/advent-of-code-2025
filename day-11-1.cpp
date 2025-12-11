#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

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

int recursion(string current_node, unordered_map<string, vector<string>> &nodes)
{
    if (current_node == "out")
    {
        return 1;
    }

    int sum = 0;
    for (string &c : nodes[current_node])
    {
        sum += recursion(c, nodes);
    }

    return sum;
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

    output = recursion("you", nodes);

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
