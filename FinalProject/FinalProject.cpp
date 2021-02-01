#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <cctype>
#include <map>

using namespace std;

vector <string> Polish(const string& function);

map <int, double> CreateMapValues(const vector <string>& source,
    const int& xmin,
    const int& xmax,
    const int& step);

void Record(const map<int, double>& Values, const string& path) {
    ofstream output;
    output.open(path);
    for (const auto& [key, value] : Values) {
        output << "x: " << key << "y: " << value << endl;
    }
}
int main() {
    string function, command, path;
    int xmin, xmax, step;
    vector <string> polishNotation;
    cout << "This program will convert your function to reverse Polish notation, draw a tree," <<
        "and write its data to a file. To get started, write 'start'.\n" <<
        "For more information write 'about'\n";
    cin >> command;
    if (command == "start") {
        //ввод данных
        cout << "Please, input your function: ";
        cin >> function;
        cout << "Please, input Xmin: ";
        cin >> xmin;
        cout << "Please, input Xmax: ";
        cin >> xmax;
        cout << "Please, input step: ";
        cin >> step;
        cout << "Please, input name file: ";
        cin >> path;
        //вывод польской нотации
        polishNotation = Polish(function);
        cout << "Polish notation: ";
        for (auto word : polishNotation) {
            cout << word << " ";
        }
        Record(CreateMapValues(polishNotation, xmin, xmax, step), path);

    }
    else if (command == "about") {

    }
}