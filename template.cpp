#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    ifstream file("input-day-xx.txt");
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

        cout << "\n------------------------------------------------";
    }

    cout << "\n\n====\n";
    cout << to_string(output);
    cout << "\n";
}
