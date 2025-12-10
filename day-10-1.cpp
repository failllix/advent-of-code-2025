#include <fstream>
#include <string>
#include <iostream>
#include <vector>
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

vector<vector<int>> comb(int n, int k)
{
    std::string bitmask(k, 1);
    bitmask.resize(n, 0);

    vector<vector<int>> out;

    do
    {
        vector<int> series;
        for (int i = 0; i < n; ++i)
        {
            if (bitmask[i])
                series.push_back(i);
        }
        out.push_back(series);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return out;
}

string get_machine_state(int target_length, vector<vector<int>> btns, vector<int> combination)
{
    string state(target_length, '.');
    for (int &c : combination)
    {
        vector<int> btn = btns[c];
        for (int &b : btn)
        {
            if (state[b] == '.')
            {
                state[b] = '#';
            }
            else
            {
                state[b] = '.';
            }
        }
    }
    return state;
}

int main()
{
    ifstream file("input-day-10.txt");
    string str;

    long output = 0;
    vector<string> target_states;
    vector<vector<vector<int>>> buttons;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        vector<string> elements = split(str, " ");

        string target = elements[0];
        target.erase(0, 1);
        target.erase(target.end() - 1);

        target_states.push_back(target);
        vector<string> local_buttons(elements.begin() + 1, elements.end() - 1);

        vector<vector<int>> parsed_buttons;

        for (auto &btn : local_buttons)
        {
            btn.erase(0, 1);
            btn.erase(btn.end() - 1);
            vector<string> button_parts = split(btn, ",");

            vector<int> parsed_indices;
            transform(button_parts.begin(), button_parts.end(), back_inserter(parsed_indices), [](auto num_str)
                      { return stoi(num_str); });

            parsed_buttons.push_back(parsed_indices);
        }

        buttons.push_back(parsed_buttons);

        cout << "\n------------------------------------------------";
    }

    for (int i = 0; i < target_states.size(); i++)
    {
        string target_state = target_states[i];
        vector<vector<int>> btns = buttons[i];

        bool solution_found = false;
        for (int activations = 1; activations < btns.size(); activations++)
        {
            vector<vector<int>> combinations = comb(btns.size(), activations);

            for (auto &c : combinations)
            {
                string state = get_machine_state(target_state.size(), btns, c);

                if (state == target_state)
                {
                    solution_found = true;
                    output += activations;
                    break;
                }
            }

            if (solution_found)
            {
                break;
            }
        }
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
