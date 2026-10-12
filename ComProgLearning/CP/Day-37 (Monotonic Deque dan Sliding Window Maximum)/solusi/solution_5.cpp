/*
============================================================
  Solution 5: First Non-Repeating in Stream
============================================================
Kompleksitas: O(n) — setiap karakter push/pop queue tepat sekali
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; cin >> s;
    queue<char> q;
    int freq[26] = {};
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        freq[c-'a']++;
        q.push(c);
        while (!q.empty() && freq[q.front()-'a'] > 1) q.pop();
        cout << (q.empty() ? '#' : q.front());
        if (i < (int)s.size()-1) cout << ' ';
    }
    cout << "\n";
    return 0;
}
