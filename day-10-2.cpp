#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

unordered_map<string, vector<vector<int>>> comb_cache;

vector<vector<int>> comb(int n, int k)
{
    string key = to_string(n) + "," + to_string(k);
    if (comb_cache.count(key))
    {
        return comb_cache[key];
    }

    string bitmask(k, 1);
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
    } while (prev_permutation(bitmask.begin(), bitmask.end()));

    comb_cache[key] = out;
    return comb_cache[key];
}

vector<int> get_machine_state(int target_length, vector<vector<int>> &btns, vector<int> &presses_per_index, vector<int> &combination)
{
    vector<int> state(target_length, 0);

    for (int i = 0; i < combination.size(); i++)
    {
        vector<int> btn = btns[combination[i]];
        for (int &b : btn)
        {
            state[b] += presses_per_index[i];
        }
    }

    return state;
}

void recursion(int index,
               int current_total_sum,
               int max_per_button,
               int num_buttons,
               int min_sum_required,
               vector<int> &current,
               vector<vector<int>> &all_solutions)
{

    int remaining_buttons = num_buttons - index;
    int max_potential_gain = remaining_buttons * max_per_button;

    if (current_total_sum + max_potential_gain < min_sum_required)
    {
        return;
    }

    if (index == num_buttons)
    {
        if (current_total_sum >= min_sum_required)
        {
            all_solutions.push_back(current);
        }
        return;
    }

    for (int i = 0; i <= max_per_button; ++i)
    {
        current[index] = i;

        recursion(index + 1,
                  current_total_sum + i,
                  max_per_button,
                  num_buttons,
                  min_sum_required,
                  current,
                  all_solutions);
    }
}

unordered_map<string, vector<vector<int>>> press_cache;

vector<vector<int>> get_press_combinations(int n, int x, int min_sum)
{
    string key = to_string(n) + "," + to_string(x) + "," + to_string(min_sum);
    if (press_cache.count(key))
    {
        return press_cache[key];
    }

    vector<vector<int>> results;

    if ((long long)x * n < min_sum)
    {
        return results;
    }

    vector<int> current_combination(x, 0);
    recursion(0, 0, n, x, min_sum, current_combination, results);

    press_cache[key] = results;
    return press_cache[key];
}

// Sadly this doesn't run for the big input sizes... :(
// Others mostly used linear equation solvers, although there also seem to be other approaches
// Maybe I'll revisit this eventually

int main()
{
    ifstream file("input-day-10.txt");
    string str;

    long output = 0;
    vector<vector<int>> target_states;
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

        string target_str = elements[elements.size() - 1];
        target_str.erase(0, 1);
        target_str.erase(target_str.end() - 1);

        vector<string> num_strs = split(target_str, ",");

        vector<int> target;
        transform(num_strs.begin(), num_strs.end(), back_inserter(target), [](auto s)
                  { return stoi(s); });

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
        vector<int> target_state = target_states[i];
        vector<vector<int>> btns = buttons[i];

        cout << endl
             << i << "/" << target_states.size() << endl;

        int lowest = -1;
        for (int btns_pressed = 1; btns_pressed < btns.size(); btns_pressed++)
        {
            cout << endl
                 << btns_pressed << "/" << btns.size() << endl;

            int min = *min_element(target_state.begin(), target_state.end());
            int max = *max_element(target_state.begin(), target_state.end());
            vector<vector<int>> combinations = comb(btns.size(), btns_pressed);

            cout << endl
                 << "combinations: " << combinations.size() << endl;

            for (auto &c : combinations)
            {

                vector<vector<int>> button_press_amounts = get_press_combinations(max, c.size(), min);

                cout << endl
                     << "press combinations : " << button_press_amounts.size() << endl;

                for (auto &presses : button_press_amounts)
                {

                    vector<int> state = get_machine_state(target_state.size(), btns, presses, c);

                    if (state == target_state)
                    {
                        int sum = 0;
                        for (int &p : presses)
                        {
                            sum += p;
                        }
                        if (lowest == -1 || sum < lowest)
                        {
                            lowest = sum;
                        }
                    }
                }
            }
        }
        output += lowest;
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
