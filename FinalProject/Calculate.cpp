#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
using namespace std;

double Calcul(const string& operation,
    const double& leftNum,
    const double& rightNum) {
    if (operation == "^") {
        return pow(leftNum,rightNum);
    }
    else if (operation == "*") {
        return leftNum * rightNum;
    }
    else if (operation == "/") {
        return leftNum / rightNum;
    }
    else if (operation == "+") {
        return leftNum + rightNum;
    }
    else if (operation == "-") {
        return leftNum - rightNum;
    }
}

vector <string> FindFirstOperation(vector <string>& source) {
    vector <string> op = { "+", "-", "*", "/", "^" };
    double leftNum, rightNum;
    string resultCalc;
    int indexOp;
    for (indexOp = 0; indexOp < source.size(); indexOp++) {
        if (find(begin(op), end(op), source[indexOp]) != op.end()) {
            break;
        }
    }
    leftNum = stod(source[indexOp - 2]);
    rightNum = stod(source[indexOp - 1]);
    if ((leftNum == 0 && rightNum == 0 && source[indexOp] == "^") || (rightNum == 0 && source[indexOp] == "/")) {
        source.clear();
        source.push_back("undefined");
        return source;
    }
    else {
        resultCalc = to_string(Calcul(source[indexOp], leftNum, rightNum));
        source.erase(source.begin() + indexOp - 2, source.begin() + indexOp + 1);
        if (source.empty()) {
            source.push_back(resultCalc);
        }
        else {
             source.insert(source.begin() + (indexOp - 2), 1, resultCalc);
        }
        if (source.size() != 1) {
            return FindFirstOperation(source);
        }
        else {
            return source;
        }
    }
}

string Result(const vector <string>& source, const int& x) {
    vector <string> output = source;
    for (auto& word : output) {
        if (word == "x") {
            word = to_string(x);
        }
        else if (word == "-x") {
            word = to_string(-x);
        }
        else if (word == "e") {
            word = "2.718281";
        }
    }
    return FindFirstOperation(output).front();
}

map <int, string> CreateMapValues(  const vector <string>& source,
                                    const int& xmin,
                                    const int& xmax,
                                    const int& step) {
    map <int, string> resultMap;
    for (int x = xmin; x <= xmax; x += step) {
        resultMap[x] = Result(source, x);
    }
    return resultMap;
}