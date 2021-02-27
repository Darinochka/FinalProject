﻿#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <cctype>
#include <map>
#include <cstring>
#include <conio.h>
#include <iomanip>

using namespace std;

vector <string> Polish(const string& source);

map <int, string> CreateMapValues(  const vector <string>& source,
                                    const int& xmin,
                                    const int& xmax,
                                    const int& step);

class Function {
public:
    void Input() {
        InputFunction(function);
        InputArguments(xmin, xmax, step);
        InputPath(path);
        historyFunctions.push_back(function);
        polishNotation = Polish(function);
    }

    void PrintPolishNotation() const {
        cout << "Polish notation: ";
        for (auto word : polishNotation) {
            cout << word << " ";
        }
        cout << endl;
    }

    void PrintHistory() const{
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

    void RenderTree() const {
        
    }
    void Record() const {
        ofstream output;
        output.open(path);
        map<int, string> values = CreateMapValues(polishNotation, xmin, xmax, step);
        output << "Calculate result of " << function << endl;
        for (const auto& [key, value] : values) {
            output << "x: " << key << " y: " << value << endl;
        }
        cout << "Loaded successfully!" << endl;
    }

private:
    string function, path;
    int xmin, xmax, step;
    vector<string> polishNotation, historyFunctions;

    void CheckPath(const string& path) const {
        char temp[5];
        path.copy(temp, 4, path.size() - 4);
        temp[4] = '\0';
        if (strcmp(temp, ".txt") != 0) {
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

    void CheckArguments(const int& xmin, const int& xmax, const int& step) const{
        if (xmin > xmax ||
            step > abs(xmin - xmax) ||
            step < 0) {
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

    void CheckFunction(const string& function) const{
        bool key = false, //=false, если до текущего стоял знак или (
            neg = false; //=true если (-
        int countBrackets = 0;
        vector <char> op = { '+', '-', '*', '/', '^' };
        for (int i = 0; i < function.size(); i++) {
            if (isdigit(function[i]) && !key) {
                key = (!(i == function.size() || isdigit(function[i + 1])));
                neg = neg && function[i + 1] == ')' ? false : neg;
            }
            else if (function[i] == 'x' && !key) {
                key = true;
                neg = neg && function[i + 1] == ')' ? false : neg;
            }
            else if (function[i] == '(' && !key && !neg) {
                neg = (function[i + 1] == '-');
                countBrackets++;
            }
            else if (function[i] == ')' && key && !neg) {
                countBrackets--;
            }
            else if (i != 0 && i != function.size() - 1) {
                if (function[i] == '-' && function[i - 1] == '(' && neg) {}
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
        if (countBrackets != 0) {
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

};

int main() {
    string command;
    Function function;
    cout << "This program will convert your function to reverse Polish notation, draw a tree," <<
            "and write its data to a file. To get started, write 'func'.\n" <<
            "If you want to see the history of your requests, enter 'history' \n" <<
            "For more information write 'about'\n";
    while (command != "exit") {
        cin >> command;
        if (command == "func") {
            function.Input();
            function.PrintPolishNotation();
            function.Record();
            //рисовка дерева
        } else if (command == "history") {
            function.PrintHistory();
        }
        else if (command == "about") {
            cout << "You can use only INTEGER numbers.\n " <<
                "You can use +, -, ^, *, /, (, )\n" <<
                "You have to use negative numbers in round brackets. For priority operations also you can use it." <<
                "For name of file you have to use only latin alphabet and txt format. Your file will save in current folder.\n" <<
                "Write 'exit' in order exit from the programm\n";
        }
        else {
            cout << "Incorrect command!" << endl;
        }
    }
    return 0;
}