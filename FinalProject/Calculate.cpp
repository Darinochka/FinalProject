#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
using namespace std;

double Calcul(const string& operation,
    const double& firstNum,
    const double& secondNum) {
    if (operation == "^") {
        return pow(firstNum,secondNum);
    }
    else if (operation == "*") {
        return firstNum * secondNum;
    }
    else if (operation == "/") {
        return firstNum / secondNum;
    }
    else if (operation == "+") {
        return firstNum + secondNum;
    }
    else if (operation == "-") {
        return firstNum - secondNum;
    }
}

vector <string> FindFirstOperation(vector <string>& source) {
    vector <string> op = { "+", "-", "*", "/", "^" };
    double firstNum, secondNum;
    string resultCalc;
    int indexOp;
    for (indexOp = 0; indexOp < source.size(); indexOp++) {
        if (find(begin(op), end(op), source[indexOp]) != op.end()) {
            break;
        }
    }
    firstNum = stod(source[indexOp - 2]);
    secondNum = stod(source[indexOp - 1]);
    if ((firstNum == 0 && secondNum == 0 && source[indexOp] == "^") || (secondNum == 0 && source[indexOp] == "/")) {
        source.clear();
        source.push_back("undefined");
        return source;
    }
    else {
        resultCalc = to_string(Calcul(source[indexOp], firstNum, secondNum));
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