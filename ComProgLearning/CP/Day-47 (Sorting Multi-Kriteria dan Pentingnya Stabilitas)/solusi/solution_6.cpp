// Day 16 — Custom Comparator
// File  : solution_6.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> parseVer(const string& s) {
    vector<int> parts;
    stringstream ss(s);
    string tok;
    while (getline(ss, tok, '.'))
        parts.push_back(stoi(tok));
    return parts;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    sort(v.begin(), v.end(), [](const string& a, const string& b){
        return parseVer(a) < parseVer(b);
    });

    for (auto& s : v) cout << s << "\n";

    return 0;
}
