#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>

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
    ifstream file("input-day-5.txt");
    string str;

    bool delim_found = false;
    long output = 0;

    vector<tuple<long, long>> bounds;
    vector<long> check;

    while (getline(file, str))
    {
        if (str == "")
        {
            if (!delim_found)
            {
                delim_found = true;
            }
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        if (!delim_found)
        {
            vector<string> parts = split(str, "-");
            bounds.push_back(make_tuple(stol(parts[0]), stol(parts[1])));
        }
        else
        {
            check.push_back(stol(str));
        }
        cout << "\n------------------------------------------------";
    }

    for (long &num : check)
    {
        for (tuple<long, long> &tup : bounds)
        {
            long lower = get<0>(tup);
            long upper = get<1>(tup);

            if (num <= upper && num >= lower)
            {
                output++;
                break;
            }
        }
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
