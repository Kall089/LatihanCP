/*
============================================================
✅ Solution 2: Rabin-Karp: Hitung Kemunculan Pola
============================================================
Approach: Rabin-Karp dengan prefix hash
Complexity: Time O(|T| + |P|) | Space O(|T|)
Key Insight:
Pencarian naif membandingkan huruf demi huruf pada setiap posisi, sehingga
kasus terburuknya O(n*m). Rabin-Karp menggantinya dengan satu perbandingan
angka per posisi.

Hash pola dihitung dengan bobot mulai p^0, sedangkan hash jendela pada posisi i
berbobot mulai p^i. Karena itu hash pola dikalikan p[i] lebih dulu agar
bobotnya setara sebelum dibandingkan.

Catatan: hash yang sama belum menjamin string yang sama (bisa terjadi
tabrakan). Untuk data besar atau kontes dengan fase hacking, pakai double
hashing seperti pada template.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, pola;
    if (!(cin >> s >> pola)) return 0;

    int m = pola.size();
    if (m > (int)s.size()) { cout << 0 << "\n"; return 0; }

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

    // hash pola, berbobot mulai p^0
    ll hp = 0, pw = 1;
    for (int i = 0; i < m; i++) {
        hp = (hp + (ll)(pola[i] - 'a' + 1) * pw) % M;
        pw = pw * P % M;
    }

    int total = 0;
    for (int i = 0; i + m <= n; i++)
        if (get(i, i + m - 1) == hp * p[i] % M) total++;

    cout << total << "\n";

    return 0;
}
