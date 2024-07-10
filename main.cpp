#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "LinkedListInterface.hpp"
#include "LinkedList.hpp"

using namespace std;

enum Command
{
    CLEAR,
    EMPTY,
    DELETE,
    FIRST,
    INSERT,
    PRINT_LIST,
    REMOVE,
    REVERSE,
    SIZE,
    COPY,
    PRINT_COPY,
    LAST,
    APPEND,
    DROP,
    ERROR
};

int main(int argc, char* argv[])
{
    // open arg[1] or cin for input
    istream& in = (argc > 1) ? *(new ifstream(argv[1])) : cin;

    // open arg[2] or out for output
    ostream& out = (argc > 2) ? *(new ofstream(argv[2])) : cout;

    LinkedList<string> list;
    LinkedList<string> copy;

    string line;

    while(getline(in, line)) {
        istringstream iss(line);

        string command;
        iss >> command;

        Command c =
            (command == "Clear") ? Command::CLEAR :
            (command == "Empty") ? Command::EMPTY :
            (command == "Delete") ? Command::DELETE :
            (command == "First") ? Command::FIRST :
            (command == "Insert") ? Command::INSERT :
            (command == "PrintList") ? Command::PRINT_LIST :
            (command == "Remove") ? Command::REMOVE :
            (command == "Reverse") ? Command::REVERSE :
            (command == "Size") ? Command::SIZE :
            (command == "Copy") ? Command::COPY :
            (command == "PrintCopy") ? Command::PRINT_COPY :
            (command == "Last") ? Command::LAST :
            (command == "Append") ? Command::APPEND :
            (command == "Drop") ? Command::DROP :
            Command::ERROR;
        
        string l;
        istringstream temp(line);
        getline(temp, l, '\r');

        out << l << " ";

        try
        {
            string word;
            switch(c)
            {
                case Command::CLEAR:
                    list.clear();
                    out << "OK";
                    break;
                case Command::EMPTY:
                    out << ((list.empty()) ? "true" : "false");
                    break;
                case Command::DELETE:
                    if(!list.empty())
                    {
                        list.pop_front();
                        out << "OK";
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::FIRST:
                    if(!list.empty())
                    {
                        out << list.front();
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::INSERT:
                    while(iss >> word)
                    {
                        list.push_front(word);
                    }
                    break;
                case Command::PRINT_LIST:
                    if(!list.empty())
                    {
                        out << list.toString();
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::REMOVE:
                    iss >> word;
                    list.remove(word);
                    break;
                case Command::REVERSE:
                    if(!list.empty())
                    {
                        list.reverse();
                        out << "OK";
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::SIZE:
                    out << list.size();
                    break;
                case Command::COPY:
                    copy = list;
                    out << "OK";
                    break;
                case Command::PRINT_COPY:
                    if(!copy.empty())
                    {
                        out << copy.toString();
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::LAST:
                    if(!list.empty())
                    {
                        out << list.back();
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::APPEND:
                    while(iss >> word)
                    {
                        list.push_back(word);
                    }
                    break;
                case Command::DROP:
                    if(!list.empty())
                    {
                        list.pop_back();
                        out << "OK";
                    }
                    else
                    {
                        out << "Empty!";
                    }
                    break;
                case Command::ERROR:
                default:
                    out << "Error on line: " << line;
            }
        }
        catch(...)
        {
            out << "Empty!";
        }

        out << endl;
    }

	// Clean up input and output streams
    if(&in != &cin) delete &in;
    if(&out != &cout) delete &out;

    return 0;
}