/*
============================================================
✅ Solution 3: Huruf Paling Sering Muncul
============================================================
Approach: Tabel frekuensi + pemilihan maksimum
Complexity: Time O(N + 26) | Space O(26)
Key Insight:
Karena kita menelusuri tabel dari indeks 0 ('a') menuju 25 ('z'),
memakai perbandingan ">" (bukan ">=") membuat huruf yang lebih awal
secara alfabet tetap bertahan ketika jumlahnya sama. Tie-breaking
selesai tanpa kode tambahan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int hitung[26] = {};
    for (char c : s) hitung[c - 'a']++;

    int terbaik = 0;
    for (int i = 1; i < 26; i++)
        if (hitung[i] > hitung[terbaik]) terbaik = i;   // ">" -> alfabet terkecil menang

    cout << char('a' + terbaik) << " " << hitung[terbaik] << "\n";

    return 0;
}
