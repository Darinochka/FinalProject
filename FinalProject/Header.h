#pragma once
using namespace std;
vector <string> CreatePostfixExpr(const string& source);

map <int, string> CreateMapValues(const vector <string>& source,
    const int& xmin,
    const int& xmax,
    const int& step);

void LaunchRender(const vector<string>& polish);
