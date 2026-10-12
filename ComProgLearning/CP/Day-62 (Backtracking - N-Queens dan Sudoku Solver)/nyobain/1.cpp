#include <bits/stdc++.h>
using namespace std;

void backtracking(string &jalan, vector<string> &hasil, int n)
{
    if ((jalan.size()) == n)
    {
        hasil.push_back(jalan);
        return;
    }

    for (char c : {'0', '1'})
    {
        jalan.push_back(c);
        backtracking(jalan, hasil, n);
        jalan.pop_back();
    }
}

int main()
{
    int n = 3;

    vector<string> hasil;
    string jalan = "";

    backtracking(jalan, hasil, n);
    for (string s : hasil)
    {
        cout << s << endl;
    }
}