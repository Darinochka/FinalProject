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

map <int, string> CreateMapValues(  const vector <string>& source,
                                    const int& xmin,
                                    const int& xmax,
                                    const int& step);

void CheckPath(const string& path) {
    ofstream output(path);
    if (!output) {
        throw exception();
    }
}

void InputPath(string& path) {
    try {
        cout << "Input path your file and name of the file: ";
        cin >> path;
        CheckPath(path);
    }
    catch (exception& ex) {
        cout << "Wrong path! Try again...\n";
        InputPath(path);
    }
}

void CheckArguments(const int& xmin, const int& xmax, const int& step) {
    if (xmin > xmax || 
        step > xmax - xmin || 
        step < 0 ||
        xmin < 0 ||
        xmax < 0) {
        throw exception();
    }
}

void InputArguments(int& xmin, int& xmax, int& step) {
    try {
        cout << "Input Xmin: ";
        cin >> xmin;
        cout << "Input Xmax: ";
        cin >> xmax;
        cout << "Input step: ";
        cin >> step;
        CheckArguments(xmin, xmax, step);
    }
    catch (exception& ex) {
        cout << "Wrong data! Try again...\n";
        InputArguments(xmin, xmax, step);
    }
}

void CheckFunction(const string& function) {
    bool key = false, //=false, если до текущего стоял знак или (
         neg = false; //=true если 
    int count = 0;
    vector <char> op = { '+', '-', '*', '/', '^' };
    for (int i = 0; i < function.size(); i++) {
        if (isdigit(function[i]) && !key) {
            key = (!(i == function.size() || isdigit(function[i + 1])));
            if (neg) {
                if (function[i+1] == ')') {
                    neg = false;
                }
            }
        }
        else if (function[i] == 'x' && !key) {
            key = true;
            if (neg) {
                if (function[i+1] == ')') {
                    neg = false;
                }
            }
        }
        else if (function[i] == '(' && !key && !neg) {
            neg = (function[i + 1] == '-');
            count++;
        }
        else if (function[i] == ')' && key && !neg) {
            count--;
        }
        else if (i != 0 && i != function.size()-1) {
            if (function[i] == '-' && function[i-1] == '(' && neg) {}
            else if (find(op.begin(), op.end(), function[i]) != op.end() && key && !neg) {
                key = false;
            }
            else {
                throw exception();
            }
        }
        else {
            throw exception();
        }
    }
    if (count != 0) {
        throw exception();
    }
}

void InputFunction(string& function) {
    try {
        cout << "Please, input your function: ";
        cin >> function;
        CheckFunction(function);
    }
    catch (exception& ex) {
        cout << "Wrong function! Try again...\n";
        InputFunction(function);
    }
}

void PrintPolishNotation(const vector<string>& polishNotation) {
    cout << "Polish notation: ";
    for (auto word : polishNotation) {
        cout << word << " ";
    }
    cout << endl;
}

void PrintHistory(const vector <string>& historyFunctions) {
    int numFun = 1;
    if (!historyFunctions.empty()) {
        for (const auto& function : historyFunctions) {
            cout << numFun << ". " << function << endl;
            numFun++;
        }
    }
    else {
        cout << "History is empty..." << endl;
    }
}

void Record(const string& function, const map<int, string>& values, const string& path) {
    ofstream output;
    output.open(path);
    output << "Calculate result of " << function << endl;
    for (const auto& [key, value] : values) {
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
            InputFunction(function);
            InputArguments(xmin, xmax, step);
            InputPath(path);
            historyFunctions.push_back(function);
            polishNotation = Polish(function);
            PrintPolishNotation(polishNotation); 
            Record(function, CreateMapValues(polishNotation, xmin, xmax, step), path);
            //рисовка дерева
        } else if (command == "history") {
            PrintHistory(historyFunctions);
        }
        else {
            cout << "Incorrect command!" << endl;
        }
        
    }
    
    return 0;
}