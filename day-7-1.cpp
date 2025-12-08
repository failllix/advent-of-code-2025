#include <fstream>
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main()
{
    ifstream file("input-day-7.txt");
    string str;

    long output = 0;

    int last_index_of_split = 0;
    set<int> current_streams;
    set<int> new_streams;

    while (getline(file, str))
    {
        if (str == "")
        {
            continue;
        }
        cout << "\n------------------------------------------------";
        cout << "\ninput: " + str + "\n++++++++++++++++++++++++++++++++++++++++++++++++";

        last_index_of_split = -1;

        if (current_streams.empty())
        {
            new_streams.insert(str.find_first_of('S'));
        }
        else
        {
            while (str.find('^', last_index_of_split + 1) != string::npos)
            {
                last_index_of_split = str.find('^', last_index_of_split + 1);

                if (current_streams.count(last_index_of_split))
                {
                    new_streams.erase(last_index_of_split);
                    output++;
                    new_streams.insert(last_index_of_split - 1);
                    new_streams.insert(last_index_of_split + 1);
                    str[last_index_of_split - 1] = '|';
                    str[last_index_of_split + 1] = '|';
                }
            }
        }

        if (last_index_of_split > -1 || current_streams.empty())
        {
            current_streams = new_streams;
        }

        cout << "\n------------------------------------------------";
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
