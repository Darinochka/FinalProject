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
    string _op;    // one of +, -, *, /, #
    string _value = ""; // integer value used for constants.
    ExprNode* _left;  // left subtree
    ExprNode* _right; // right subtree
};

ExprNode* Transform(vector <string>& v) {
    vector <string> ops = { "+", "-", "*", "/", "^" };
    string node = v[0];
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

int HighNode(ExprNode source) {
    if (source.GetValue() == "") {
        return min(HighNode(source.GetLeft()), HighNode(source.GetRight())) * 2;
    }
    else {
        if (source.GetValue().size() == 1) {
            return 1;
        }
        else {
            return source.GetValue().size() / 2;
        }
    }
}
using coordinateXY = vector <pair<string, pair<int, int>>>;

void Coordinate(ExprNode source, coordinateXY& renderpipe, int x, int y) {
    int size = HighNode(source);
    if (source.GetValue() == "") {
        renderpipe.push_back({ source.GetOp(), {x, y} });
        for (int shift = 1; shift < size + 1; shift++) {
            renderpipe.push_back({ "/", {x - shift, y - shift} });
            renderpipe.push_back({ "\\", {x + shift, y - shift} });
        }
        Coordinate(source.GetLeft(), renderpipe, x - size - 1, y - size - 1);
        Coordinate(source.GetRight(), renderpipe, x + size + 1, y - size - 1);
    }
    else {
        renderpipe.push_back({ source.GetValue(), {x - source.GetValue().size() + 1, y} }); 
    }
}

void Render(coordinateXY& renderpipe) {
    int max = -1;
    int high = abs(renderpipe[renderpipe.size()-1].second.second);
    for (auto item : renderpipe) {
        if (abs(item.second.first) > abs(max)) {
            max = abs(item.second.first);
        }
    }
    for (auto &item : renderpipe) {
        item.second.first += max + 1;
    }
    for (int i = 0; i < high+1; i++) {
        int shift = 0, length = 0;
        for (auto item : renderpipe) {
            if (abs(item.second.second) == i) {
                string temp(item.second.first - shift - length, ' ');
                cout << temp;
                cout << item.first;
                shift = item.second.first;
                length = item.first.size();
            }
        }
        cout << endl;
    }
}

coordinateXY& Sort(coordinateXY& renderpipe) {
    sort(renderpipe.begin(), renderpipe.end(),
        [](auto a, auto b) {return abs(a.second.second) < abs(b.second.second); });
    return renderpipe;
}

void LaunchRender(const vector<string>& polish) {
    vector <string> reverse_polish;
    coordinateXY renderpipe;
    int x = 0, y = 0;

    for (int i = polish.size()-1; i >= 0; i--) {
        reverse_polish.push_back(polish[i]);
    }

    ExprNode* result = Transform(reverse_polish);
    Coordinate(*result, renderpipe, x, y);
    Render(Sort(renderpipe));
}