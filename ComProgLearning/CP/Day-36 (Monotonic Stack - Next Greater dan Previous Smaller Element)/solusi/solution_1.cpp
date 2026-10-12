/*
============================================================
  Solution 1: Balanced Brackets
============================================================
Kompleksitas: O(n) waktu, O(n) ruang
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    stack<char> st;
    bool valid = true;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) { valid = false; break; }
            char top = st.top(); st.pop();
            if (c == ')' && top != '(') { valid = false; break; }
            if (c == ']' && top != '[') { valid = false; break; }
            if (c == '}' && top != '{') { valid = false; break; }
        }
    }

    if (!st.empty()) valid = false;
    cout << (valid ? "YES" : "NO") << "\n";
    return 0;
}
