#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <regex>

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

    vector<vector<string>> lines;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        regex reg("\\s+");
        str = regex_replace(str, reg, " ");
        trim(str);

        cout
            << "\nnormalized: '" + str + "'\n++++++++++++++++++++++++++++++++++++++++++++++++";

        lines.push_back(split(str, " "));

        cout << "\n------------------------------------------------";
    }

    vector<string> operators = lines.back();
    lines.pop_back();

    vector<long> results(operators.size(), 0);
    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> line = lines[i];
        for (int x = 0; x < line.size(); x++)
        {
            string o = operators[x];
            long num = stol(line[x]);

            if (results[x] == 0)
            {
                results[x] = num;
            }
            else
            {
                if (o == "+")
                {
                    results[x] += num;
                }
                if (o == "*")
                {
                    results[x] *= num;
                }
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
