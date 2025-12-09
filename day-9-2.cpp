#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
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

long get_size(tuple<long, long> a, tuple<long, long> b)
{
    long x = abs(get<0>(a) - get<0>(b)) + 1;
    long y = abs(get<1>(a) - get<1>(b)) + 1;

    return x * y;
}

bool check_for_continuity(long min, long max, vector<tuple<long, long>> coords)
{
    bool found_min_bound = false;
    bool found_max_bound = false;

    if (coords.empty())
    {
        return false;
    }

    if (coords.size() == 1)
    {
        long coord_min = get<0>(coords[0]);
        long coord_max = get<1>(coords[0]);

        if (coord_min <= min && coord_max >= max)
        {
            return true;
        }

        return false;
    }

    sort(coords.begin(), coords.end(), [](const auto &lhs, const auto &rhs)
         { return get<0>(lhs) < get<0>(rhs); });

    for (int i = 1; i < coords.size(); i++)
    {
        tuple<long, long> prev = coords[i - 1];
        tuple<long, long> curr = coords[i];
        long prev_min = get<0>(prev);
        long prev_max = get<1>(prev);
        long curr_min = get<0>(curr);
        long curr_max = get<1>(curr);

        if (prev_min <= min || curr_min <= min)
        {
            found_min_bound = true;
        }

        if (prev_max >= max || curr_max >= max)
        {
            found_max_bound = true;
        }

        if (curr_min > prev_max)
        {
            return false;
        }
    }

    if (!found_min_bound || !found_max_bound)
    {
        return false;
    }

    return true;
}

bool check_horizontal_bounding(long ax, long bx, long ay, vector<tuple<tuple<long, long>, tuple<long, long>>> horizontals)
{
    vector<tuple<long, long>> above;
    vector<tuple<long, long>> below;

    for (tuple<tuple<long, long>, tuple<long, long>> &h : horizontals)
    {
        tuple<long, long> start = get<0>(h);
        tuple<long, long> end = get<1>(h);

        long start_x = get<0>(start);
        long start_y = get<1>(start);
        long end_x = get<0>(end);
        if (end_x < ax || start_x > bx)
        {
            continue;
        }

        tuple<long, long> horizontal = make_tuple(start_x, end_x);

        if (start_y <= ay)
        {
            above.push_back(horizontal);
        }

        if (start_y >= ay)
        {
            below.push_back(horizontal);
        }
    }

    bool above_continous = check_for_continuity(ax, bx, above);
    bool below_continous = check_for_continuity(ax, bx, below);

    return above_continous && below_continous;
}

bool check_vertical_bounding(long ay, long by, long ax, vector<tuple<tuple<long, long>, tuple<long, long>>> verticals)
{
    vector<tuple<long, long>> left;
    vector<tuple<long, long>> right;

    for (tuple<tuple<long, long>, tuple<long, long>> &v : verticals)
    {
        tuple<long, long> start = get<0>(v);
        tuple<long, long> end = get<1>(v);

        long start_y = get<1>(start);
        long start_x = get<0>(start);
        long end_y = get<1>(end);
        if (end_y < ay || start_y > by)
        {
            continue;
        }

        tuple<long, long> vertical = make_tuple(start_y, end_y);

        if (start_x <= ax)
        {
            left.push_back(vertical);
        }

        if (start_x >= ax)
        {
            right.push_back(vertical);
        }
    }

    bool above_continous = check_for_continuity(ay, by, left);
    bool below_continous = check_for_continuity(ay, by, right);

    return above_continous && below_continous;
}

unordered_map<string, bool> cache;

bool is_on_bounding_box(tuple<long, long> a, tuple<long, long> b, vector<tuple<tuple<long, long>, tuple<long, long>>> verticals, vector<tuple<tuple<long, long>, tuple<long, long>>> horizontals)
{
    long ax = get<0>(a);
    long bx = get<0>(b);
    long ay = get<1>(a);
    long by = get<1>(b);

    string key = to_string(ax) + "," + to_string(ay) + "|" + to_string(bx) + "," + to_string(by);
    if (cache.count(key))
    {
        return cache[key];
    }

    bool horizontal = ay == by;

    if (horizontal)
    {
        cache[key] = check_horizontal_bounding(ax, bx, ay, horizontals);
    }
    else
    {
        cache[key] = check_vertical_bounding(ay, by, ax, verticals);
    }

    return cache[key];
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

    vector<tuple<tuple<long, long>, tuple<long, long>>> verticals;
    vector<tuple<tuple<long, long>, tuple<long, long>>> horizontals;

    for (int i = 0; i < coords.size(); i++)
    {
        int x = i - 1;
        if (x < 0)
        {
            x = coords.size() - 1;
        }

        tuple<long, long> a = coords[i];
        tuple<long, long> b = coords[x];

        if (get<0>(a) == get<0>(b))
        {
            if (get<1>(a) < get<1>(b))
            {
                verticals.push_back(make_tuple(a, b));
            }
            else
            {
                verticals.push_back(make_tuple(b, a));
            }
        }

        if (get<1>(a) == get<1>(b))
        {
            if (get<0>(a) < get<0>(b))
            {
                horizontals.push_back(make_tuple(a, b));
            }
            else
            {
                horizontals.push_back(make_tuple(b, a));
            }
        }
    }

    for (int i = 0; i < coords.size(); i++)
    {
        tuple<long, long> a = coords[i];
        for (int x = i + 1; x < coords.size(); x++)
        {
            tuple<long, long> b = coords[x];

            long ax = get<0>(a);
            long ay = get<1>(a);
            long bx = get<0>(b);
            long by = get<1>(b);

            bool left = is_on_bounding_box(make_tuple(min(ax, bx), min(ay, by)), make_tuple(min(ax, bx), max(ay, by)), verticals, horizontals);
            bool right = is_on_bounding_box(make_tuple(max(ax, bx), min(ay, by)), make_tuple(max(ax, bx), max(ay, by)), verticals, horizontals);
            bool up = is_on_bounding_box(make_tuple(min(ax, bx), min(ay, by)), make_tuple(max(ax, bx), min(ay, by)), verticals, horizontals);
            bool down = is_on_bounding_box(make_tuple(min(ax, bx), max(ay, by)), make_tuple(max(ax, bx), max(ay, by)), verticals, horizontals);

            if (left && right && up && down)
            {
                long size = get_size(a, b);
                if (size > output)
                {
                    output = size;
                }
            }
        }
    }

    cout
        << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
