/*
============================================================
✅ Solution 1: Bandingkan Dua Substring
============================================================
Approach: Polynomial prefix hash + perbandingan silang
Complexity: Time O(|S| + Q) | Space O(|S|)
Key Insight:
Prefix hash bekerja persis seperti prefix sum: sekali dibangun dalam O(n),
hash potongan mana pun bisa diambil dengan satu pengurangan.

Yang perlu diperhatikan, get(l, r) menghasilkan hash yang MASIH BERBOBOT p^l.
Dua potongan pada posisi berbeda punya bobot berbeda, jadi tidak bisa langsung
dibandingkan. Membaginya dengan p^l butuh modular inverse yang mahal; jauh
lebih murah mengalikan silang:
    get(a,b) * p[c]  ==  get(c,d) * p[a]
Kedua ruas kini berbobot p^(a+c), sehingga adil dibandingkan.
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

    int q;
    cin >> q;
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // ubah ke 0-based
        cout << (sama(a - 1, b - 1, c - 1, d - 1) ? "SAMA" : "BEDA") << "\n";
    }

    return 0;
}
