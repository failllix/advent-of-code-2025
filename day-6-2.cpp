#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

string &ltrim(string &s)
{
    s.erase(0, s.find_first_not_of(" "));
    return s;
}

string &rtrim(string &s)
{
    s.erase(s.find_last_not_of(" ") + 1, s.length());
    return s;
}

string &trim(string &s)
{
    s = ltrim(s);
    s = rtrim(s);
    return s;
}

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
    ifstream file("input-day-6.txt");
    string str;

    long long output = 0;

    vector<vector<char>> lines;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        lines.push_back(vector<char>(str.begin(), str.end()));

        cout << "\n------------------------------------------------";
    }

    vector<vector<char>> transposed(lines[0].size(), vector<char>(lines.size(), ' '));

    for (int x = 0; x < lines[0].size(); x++)
    {
        for (int y = 0; y < lines.size(); y++)
        {
            transposed[x][y] = lines[y][x];
        }
    }

    char current_operator;
    bool new_operation = false;
    vector<long> results;

    for (int x = 0; x < transposed.size(); x++)
    {
        vector<char> line = transposed[x];
        if (line[line.size() - 1] == '+' || line[line.size() - 1] == '*')
        {
            current_operator = line[line.size() - 1];
            line.pop_back();
            new_operation = true;
        }

        string numString(line.begin(), line.end());
        trim(numString);
        if (numString == "")
        {
            continue;
        }
        int num = stol(numString);

        if (new_operation)
        {
            results.push_back(num);
            new_operation = false;
        }
        else
        {
            if (current_operator == '+')
            {
                results.back() += num;
            }
            if (current_operator == '*')
            {
                results.back() *= num;
            }
        }
    }

    for (long &num : results)
    {
        output += num;
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
