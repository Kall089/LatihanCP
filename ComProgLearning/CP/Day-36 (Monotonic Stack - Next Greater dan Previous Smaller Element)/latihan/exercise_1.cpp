/*
============================================================
  Exercise 1: Balanced Brackets
============================================================
Diberikan sebuah string yang hanya berisi karakter '(', ')', '[', ']', '{', '}'.
Tentukan apakah string tersebut merupakan urutan bracket yang valid (balanced).

Aturan:
- Setiap bracket pembuka harus ditutup oleh bracket penutup yang sesuai.
- Bracket harus ditutup dalam urutan yang benar (LIFO).

📏 CONSTRAINTS:
  - 1 ≤ |s| ≤ 10^5
  - s hanya berisi ()[]{}

📎 SAMPLE INPUT:
  ()[]{}

📎 SAMPLE OUTPUT:
  YES

📎 SAMPLE INPUT 2:
  ([)]

📎 SAMPLE OUTPUT 2:
  NO

💡 HINT:
  - Gunakan stack<char>
  - Saat bertemu '(' atau '[' atau '{' → push
  - Saat bertemu ')' atau ']' atau '}':
      jika stack kosong atau top tidak cocok → INVALID
      jika cocok → pop
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
        // TODO: implementasi balanced brackets
    }

    if (!st.empty()) valid = false;

    cout << (valid ? "YES" : "NO") << "\n";
    return 0;
}
