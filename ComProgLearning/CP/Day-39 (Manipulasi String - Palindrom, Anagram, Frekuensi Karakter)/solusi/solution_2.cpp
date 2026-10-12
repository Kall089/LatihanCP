/*
============================================================
✅ Solution 2: Anagram atau Bukan
============================================================
Approach: Tabel frekuensi 26 huruf
Complexity: Time O(N) | Space O(26) = O(1)
Key Insight:
Anagram hanya peduli BERAPA BANYAK tiap huruf, bukan urutannya.
Dengan menambah untuk A dan mengurangi untuk B pada tabel yang sama,
dua kata yang anagram akan saling meniadakan sehingga seluruh tabel
menjadi nol. Ini O(N), lebih cepat daripada sorting O(N log N).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    if (a.size() != b.size()) { cout << "TIDAK\n"; return 0; }

    int hitung[26] = {};
    for (char c : a) hitung[c - 'a']++;
    for (char c : b) hitung[c - 'a']--;

    for (int i = 0; i < 26; i++)
        if (hitung[i] != 0) { cout << "TIDAK\n"; return 0; }

    cout << "YA\n";

    return 0;
}
