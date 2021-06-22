#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class ExprNode {
public:
    ExprNode(string oper, ExprNode* left, ExprNode* right) {
        _op = oper;
        _left = left;
        _right = right;
    }
    ExprNode(string val) {
        _value = val;
    }

    string GetValue() const {
        return _value;
    }

    ExprNode GetLeft() const {
        return *_left;
    }

    ExprNode GetRight() const {
        return *_right;
    }

    string GetOp() const {
        return _op;
    }

private:
    string _op;
    string _value = ""; 
    ExprNode* _left;  
    ExprNode* _right; 
};

ExprNode* Transform(vector <string>& v) {
    vector <string> ops = { "+", "-", "*", "/", "^" };
    string node = v.front();
    v.erase(v.begin(), v.begin() + 1);
    if (find(ops.begin(), ops.end(), node) != ops.end()) {
        ExprNode* right = Transform(v);
        ExprNode* left = Transform(v);
        return new ExprNode (node, left, right);
    }
    else {
        return new ExprNode(node);
    }
}

struct Node {
    string element;
    int x;
    int y;
};

using coordinateXY = vector <Node> ;

coordinateXY& SortedVector(coordinateXY& source) {
    bool key = true;
    while (key) {
        key = false;
        for (int i = 0; i < source.size() - 1; i++) {
            if (source[i].y < source[i + 1].y) {
                swap(source[i], source[i + 1]);
                key = true;
            }
        }
    }
    return source;
}

int HighOfNode(ExprNode source) {
    if (source.GetValue() == "") { // source == BinOp
        return min(HighOfNode(source.GetLeft()), HighOfNode(source.GetRight())) * 2;
    }
    else if (source.GetValue().size() == 1) {
        return 1;
    }
    return source.GetValue().size() / 2 + 1;
}

void Coordinate(ExprNode source, coordinateXY& renderpipe, int x, int y) {
    int size = HighOfNode(source);
    if (source.GetValue() == "") { // source == BinOp
        renderpipe.push_back({ source.GetOp(), x, y });
        for (int shift = 1; shift < size + 1; shift++) {
            renderpipe.push_back({ "/", x - shift, y - shift });
            renderpipe.push_back({ "\\", x + shift, y - shift });
        }
        Coordinate(source.GetLeft(), renderpipe, x - size - 1, y - size - 1);
        Coordinate(source.GetRight(), renderpipe, x + size + 1, y - size - 1);
    }
    else {
        renderpipe.push_back({ source.GetValue(), (int)(x - source.GetValue().size() + 1), y });
    }
}

void Render(coordinateXY& renderpipe) {
    int max = -1; //max |X| coordinate
    int high = abs(renderpipe[renderpipe.size()-1].y); //high of node

    for (auto item : renderpipe) {
        if (abs(item.x) > abs(max)) {
            max = abs(item.x);
        }
    }   
    for (auto &item : renderpipe) {
        item.x += max + 1;
    }
    for (int i = 0; i < high+1; i++) {
        int shift = 0, length = 0;
        for (auto item : renderpipe) {
            if (abs(item.y) == i) {
                string temp(abs(item.x - shift - length), ' ');
                cout << temp << item.element;
                shift = item.x;
                length = item.element.size();
            }
        }
        cout << endl;
    }
}

coordinateXY& Sort(coordinateXY& renderpipe) {
    return SortedVector(renderpipe);
}

void LaunchRender(const vector<string>& postfixExpr) {
    vector <string> reverse_postfixExpr;
    coordinateXY renderpipe;
    int x = 0, y = 0;

    for (int i = postfixExpr.size()-1; i >= 0; i--) {
        reverse_postfixExpr.push_back(postfixExpr[i]);
    }

    ExprNode* BinOp = Transform(reverse_postfixExpr);
    Coordinate(*BinOp, renderpipe, x, y);
    Render(Sort(renderpipe));
}