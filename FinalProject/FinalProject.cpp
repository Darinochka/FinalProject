#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <cctype>
#include <map>
#include <conio.h>

using namespace std;

vector <string> Polish(const string& source);

map <int, double> CreateMapValues(const vector <string>& source,
    const int& xmin,
    const int& xmax,
    const int& step);

void Record(const string& function, const map<int, double>& Values, const string& path) {
    ofstream output;
    output.open(path);
    output << "Calculate result of " << function << endl;
    for (const auto& [key, value] : Values) {
        output << "x: " << key << " y: " << value << endl;
    }
    cout << "Loaded successfully!" << endl;
}

int main() {
    string function, command, path;
    int xmin, xmax, step;
    vector <string> polishNotation;
    vector <string> historyFunctions;
    cout << "This program will convert your function to reverse Polish notation, draw a tree," <<
        "and write its data to a file. To get started, write 'func'.\n" <<
        "If you want to see the history of your requests, enter 'history' \n" <<
        "For more information write 'about'\n";
    while (true) {
        cin >> command;
        if (command == "func") {
            //ввод данных
            cout << "Please, input your function: ";
            cin >> function;
            cout << "Input Xmin: ";
            cin >> xmin;
            cout << "Input Xmax: ";
            cin >> xmax;
            cout << "Input step: ";
            cin >> step;
            cout << "Input name file: ";
            cin >> path;
            //запись в новой функции в vector
            historyFunctions.push_back(function);
            //вывод польской нотации
            polishNotation = Polish(function);
            cout << "Polish notation: ";
            for (auto word : polishNotation) {
                cout << word << " ";
            }
            cout << endl;
            //запись в файл
            Record(function, CreateMapValues(polishNotation, xmin, xmax, step), path);
        }
        else if (command == "about") {

        }
        else if (command == "history") {
            int numFun = 1;
            if (!historyFunctions.empty()) {
                for (const auto& function : historyFunctions) {
                    cout << numFun << ". " << function << endl;
                    numFun++;
                }
            }
        }
        else {
            cout << "Incorrect command!" << endl;
        }
    }
    
    return 0;
}