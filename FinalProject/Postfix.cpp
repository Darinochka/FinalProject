#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <stack>
using namespace std;


vector <string> CreatePostfixExpr(const string& function) {
    bool neg = false, key = true;
    int length;
    vector <string> output;
    stack <string> stk;
    map <string, int> op = { {"^", 3},
                            {"*", 2},
                            {"/", 2},
                            {"+", 1},
                            {"-", 1}, };
    for (const char& word : function) {
        string temp(1, word);
        if (isdigit(word) || word == 'x' || (word == '-' && neg && key)) {
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

    while (!stk.empty()) {
        output.push_back(stk.top());
        stk.pop();
    }
    return output;
}