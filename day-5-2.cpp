#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
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

int main()
{
    ifstream file("input-day-5.txt");
    string str;

    bool delim_found = false;
    long output = 0;

    vector<long> uppers;
    vector<long> lowers;

    while (getline(file, str))
    {
        if (str == "")
        {
            break;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        vector<string> parts = split(str, "-");
        lowers.push_back(stol(parts[0]));
        uppers.push_back(stol(parts[1]));

        cout << "\n------------------------------------------------";
    }

    sort(lowers.begin(), lowers.end());
    sort(uppers.begin(), uppers.end());

    long long current_max_upper = 0;

    for (int i = 0; i < lowers.size(); i++)
    {
        long lower = lowers[i];
        long upper = uppers[i];

        if (lower <= current_max_upper && upper <= current_max_upper)
        {
            continue;
        }

        if (lower <= current_max_upper)
        {
            output += upper - current_max_upper;
        }
        else
        {
            output += upper - lower + 1;
        }

        current_max_upper = upper;
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
