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
    double resultCalc, firstNum, secondNum;
    int indexOp;
    for (indexOp = 0; indexOp < source.size(); indexOp++) {
        if (find(begin(op), end(op), source[indexOp]) != op.end()) {
            break;
        }
    }
    firstNum = stod(source[indexOp - 2]);
    secondNum = stod(source[indexOp - 1]);
    resultCalc = Calcul(source[indexOp], firstNum, secondNum);
    source.erase(source.begin() + indexOp - 2, source.begin() + indexOp+1);
    if (source.empty()) {
        source.push_back(to_string(resultCalc));
    }
    else {
        source.insert(source.begin() + indexOp - 2, to_string(resultCalc));
    }
    return source;
}

double Result(const vector <string>& source, const int& x) {
    vector <string> output = source;
    for (auto& word : output) {
        if (word == "x") {
            word = to_string(x);
        }
    }
    while (output.size() != 1) {
        FindFirstOperation(output);
    }
    return stod(output.front());
}

map <int, double> CreateMapValues(  const vector <string>& source,
                                    const int& xmin,
                                    const int& xmax,
                                    const int& step) {
    map <int, double> resultMap;
    for (int x = xmin; x <= xmax; x += step) {
        resultMap[x] = Result(source, x);
    }
    return resultMap;
}