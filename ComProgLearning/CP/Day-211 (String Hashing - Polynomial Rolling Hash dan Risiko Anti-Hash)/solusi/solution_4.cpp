/*
============================================================
✅ Solution 4: Menghitung Substring Berbeda
============================================================
Approach: Kumpulkan hash ternormalisasi semua substring ke dalam set
Complexity: Time O(n^2 log n) | Space O(n^2)
Key Insight:
Ini soal pertama yang memaksa kita memahami bahwa get(l, r) BELUM berupa
identitas substring. Nilainya masih mengandung bobot p^l, sehingga potongan
"ab" di posisi 0 dan "ab" di posisi 2 menghasilkan angka berbeda.

Solusinya menormalkan semua ke acuan yang sama dengan mengalikan p[n-l].
Setelah itu barulah dua substring identik dijamin bernilai sama, dan set
bisa menghitung yang berbeda dengan benar.

Untuk n yang jauh lebih besar, soal ini diselesaikan dengan Suffix Array
atau Suffix Automaton dalam O(n log n).
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

    const ll P = 131, M = 1000000009;
    int n = s.size();
    vector<ll> h(n + 1, 0), p(n + 1, 1);
    for (int i = 0; i < n; i++) {
        h[i + 1] = (h[i] + (ll)(s[i] - 'a' + 1) * p[i]) % M;
        p[i + 1] = p[i] * P % M;
    }
    // hash mentah s[l..r] (masih berbobot p^l)
    auto get = [&](int l, int r) -> ll {
        if (l > r) return 0;
        return (h[r + 1] - h[l] + M) % M;
    };
    // apakah s[a..b] == s[c..d]? kalikan silang, hindari modular inverse
    auto sama = [&](int a, int b, int c, int d) -> bool {
        if (b - a != d - c) return false;
        return get(a, b) * p[c] % M == get(c, d) * p[a] % M;
    };

    // Normalisasi: kalikan p[n-l] supaya substring identik di posisi berbeda
    // menghasilkan nilai yang sama persis.
    set<ll> unik;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++)
            unik.insert(get(l, r) * p[n - l] % M);

    cout << unik.size() << "\n";

    return 0;
}
