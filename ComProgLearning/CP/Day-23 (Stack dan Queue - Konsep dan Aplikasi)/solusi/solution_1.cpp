/*
============================================================
✅ Solution 1: Valid Brackets (Stack)
============================================================
Approach: Stack-based bracket matching
Complexity: Time O(N) | Space O(N)
Key Insight: Push opening brackets, pop & check on closing brackets.
             Valid iff stack empty at end.

📖 PENJELASAN PENDEKATAN:
1. Iterasi setiap karakter
2. Bracket buka → push ke stack
3. Bracket tutup → cek top stack apakah match
4. Akhir: stack harus kosong

🔄 ALTERNATIVE APPROACHES:
- Counter (hanya untuk satu jenis bracket): O(1) space
- Replace pairs repeatedly: O(N²) — TLE
============================================================
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
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) {
                valid = false;
                break;
            }
            char top = st.top();
            st.pop();
            if (c == ')' && top != '(') { valid = false; break; }
            if (c == '}' && top != '{') { valid = false; break; }
            if (c == ']' && top != '[') { valid = false; break; }
        }
    }

    if (!st.empty()) valid = false;

    cout << (valid ? "YES" : "NO") << '\n';

    return 0;
}
