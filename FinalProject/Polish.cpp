#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <stack>

using namespace std;


vector <string> Polish(const string& source) {
    bool neg, key = true;
    int length;
    string function;
    vector <string> output;
    stack <string> stk;
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
                stk.push(temp);
            }
            else if (word == ')') {
                neg = false;
                while (stk.top() != "(") {
                    output.push_back(stk.top());
                    stk.pop();
                }
                stk.pop();
            }
            else {
                while (stk.size() - 1 >= 0 && !stk.empty() && op[stk.top()] >= op[temp]) {
                    output.push_back(stk.top());
                    stk.pop();
                }
                stk.push(temp);
            }
        }
    }

    for (int i = 0; i < stk.size(); i++) {
        output.push_back(stk.top());
        stk.pop();
    }
    return output;
}