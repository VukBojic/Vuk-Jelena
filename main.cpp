#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cctype>

using namespace std;

string prompt = "$ ";

void cmd_echo(const string &arg)
{
    cout << arg << "\n";
}

void cmd_time()
{
    time_t now = time(nullptr);
    tm *loc = localtime(&now);
    char buf[16];
    strftime(buf, sizeof(buf), "%H:%M:%S", loc);
    cout << buf << "\n";
}

void cmd_date()
{
    time_t now = time(nullptr);
    tm *loc = localtime(&now);
    char buf[16];
    strftime(buf, sizeof(buf), "%Y-%m-%d", loc);
    cout << buf << "\n";
}

int count_words(const string &text)
{
    int count = 0;
    bool in_word = false;

    for (char c : text)
    {
        if (isspace((unsigned char)c))
        {
            if (in_word)
            {
                count++;
                in_word = false;
            }
        }
        else
        {
            in_word = true;
        }
    }
    if (in_word)
        count++;
    return count;
}

void execute_wc(const string &opt, const string &arg)
{
    if (opt == "-w")
        cout << count_words(arg) << "\n";
    else if (opt == "-c")
        cout << arg.size() << "\n";
    else
        cout << "wc: unknown option\n";
}

int main()
{
    while (true)
    {
        cout << prompt;
        string line;

        if (!getline(cin, line))
            break; // Ctrl+D

        if (line.empty())
            continue;

        // --- parsiranje komande ---
        string cmd;
        string opt;
        string arg;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "echo")
        {
            size_t pos = line.find("echo");
            string rest = line.substr(pos + 4);

            // ukloni vodeće razmake
            while (!rest.empty() && rest[0] == ' ')
                rest.erase(rest.begin());

            // ako ima navodnike
            if (!rest.empty() && rest[0] == '"')
            {
                size_t end = rest.find_last_of('"');
                if (end != string::npos && end > 0)
                    arg = rest.substr(1, end - 1);
            }

            cmd_echo(arg);
        }
        else if (cmd == "time")
        {
            cmd_time();
        }
        else if (cmd == "date")
        {
            cmd_date();
        }
        else if (cmd == "wc")
        {
            ss >> opt;

            size_t q1 = line.find('"');
            size_t q2 = line.find_last_of('"');

            if (q1 != string::npos && q2 != string::npos && q2 > q1)
                arg = line.substr(q1 + 1, q2 - q1 - 1);

            execute_wc(opt, arg);
        }
        else
        {
            cout << "Unknown command: " << cmd << "\n";
        }
    }

    return 0;
}
