#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <tuple>

using namespace std;

int main()
{
    ifstream file("input-day-4.txt");
    string str;

    long output = 0;

    vector<vector<char>> lines;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        vector<char> papers = vector<char>(str.begin(), str.end());

        lines.push_back(papers);

        cout << "\n------------------------------------------------";
    }

    vector<tuple<int, int>> to_remove;
    do
    {
        to_remove.clear();

        for (int y = 0; y < lines.size(); y++)
        {
            vector<char> current_line = lines[y];
            for (int x = 0; x < current_line.size(); x++)
            {
                int surrounding = 0;

                if (lines[y][x] != '@')
                {
                    continue;
                }

                // left
                if (x > 0)
                {
                    if (lines[y][x - 1] == '@')
                    {
                        surrounding++;
                    }
                }

                // right
                if (x < current_line.size() - 1)
                {
                    if (lines[y][x + 1] == '@')
                    {
                        surrounding++;
                    }
                }

                // above
                if (y > 0)
                {
                    // above
                    if (lines[y - 1][x] == '@')
                    {
                        surrounding++;
                    }

                    // top left
                    if (x > 0)
                    {
                        if (lines[y - 1][x - 1] == '@')
                        {
                            surrounding++;
                        }
                    }

                    // top right
                    if (x < current_line.size() - 1)
                    {
                        if (lines[y - 1][x + 1] == '@')
                        {
                            surrounding++;
                        }
                    }
                }

                // below
                if (y < lines.size() - 1)
                {
                    // below
                    if (lines[y + 1][x] == '@')
                    {
                        surrounding++;
                    }

                    // bottom left
                    if (x > 0)
                    {
                        if (lines[y + 1][x - 1] == '@')
                        {
                            surrounding++;
                        }
                    }

                    // bottom right
                    if (x < current_line.size() - 1)
                    {
                        if (lines[y + 1][x + 1] == '@')
                        {
                            surrounding++;
                        }
                    }
                }

                if (surrounding < 4)
                {
                    output++;
                    to_remove.push_back(make_tuple(y, x));
                }
            }
        }

        for (const tuple<int, int> &remove : to_remove)
        {
            lines[get<0>(remove)][get<1>(remove)] = 'x';
        }
    } while (to_remove.size() > 0);

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
