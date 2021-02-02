#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;


vector <string> Polish(const string& source) {
    bool neg, key = true;
    int length;
    string function;
    vector <string> output;
    list <string> stack;
    map <string, int> op = { {"^", 3},
                            {"*", 2},
                            {"/", 2},
                            {"+", 1},
                            {"-", 1} };
    for (const auto& word : source) {
        if (word != ' ') {
            function += word;
        }
    }
    for (const char& word : function) {
        string temp(1, word);
        if (isdigit(word) || word == 'x' || (word == '-' && neg)) {
            if (key) {
                output.push_back(temp);
                key = false;
            }
            else {
                output[output.size() - 1] += word;
            }
        }
        else {
            key = true;
            if (word == '(') {
                neg = true;
                stack.push_back(temp);
            }
            else if (word == ')') {
                neg = false;
                while (stack.back() != "(") {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            }
            else {
                while (stack.size() - 1 >= 0 && !stack.empty() && op[stack.back()] >= op[temp]) {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(temp);
            }
        }
    }

    for (int i = 0; i < stack.size(); i++) {
        output.push_back(stack.back());
        stack.pop_back();
    }
    return output;
}