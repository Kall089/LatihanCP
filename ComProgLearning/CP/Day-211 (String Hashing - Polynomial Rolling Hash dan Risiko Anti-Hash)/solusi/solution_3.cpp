/*
============================================================
✅ Solution 3: Palindrom Substring
============================================================
Approach: Dua prefix hash (maju dan mundur)
Complexity: Time O(|S| + Q) | Space O(|S|)
Key Insight:
Sebuah potongan disebut palindrom kalau ia sama dengan dirinya sendiri saat
dibaca terbalik. Daripada membalik potongannya setiap kali ditanya, kita
membalik seluruh string SEKALI di awal lalu membangun hash keduanya.

Bagian tersulit adalah pemetaan indeks. Kalau string aslinya sepanjang n,
maka karakter pada posisi i berpindah ke posisi (n-1-i) setelah dibalik.
Akibatnya potongan [l..r] menjadi [n-1-r .. n-1-l] - perhatikan l dan r
saling bertukar peran. Salah di sini membuat jawaban tampak acak.
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
    int n = s.size();

    string t = s;
    reverse(t.begin(), t.end());

    const ll P = 131, M = 1000000009;
    vector<ll> hs(n + 1, 0), ht(n + 1, 0), p(n + 1, 1);
    for (int i = 0; i < n; i++) {
        hs[i + 1] = (hs[i] + (ll)(s[i] - 'a' + 1) * p[i]) % M;
        ht[i + 1] = (ht[i] + (ll)(t[i] - 'a' + 1) * p[i]) % M;
        p[i + 1] = p[i] * P % M;
    }
    auto getS = [&](int l, int r) { return (hs[r + 1] - hs[l] + M) % M; };
    auto getT = [&](int l, int r) { return (ht[r + 1] - ht[l] + M) % M; };

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;                              // ke 0-based
        int l2 = n - 1 - r, r2 = n - 1 - l;    // posisi yang sama pada string terbalik
        bool ya = getS(l, r) * p[l2] % M == getT(l2, r2) * p[l] % M;
        cout << (ya ? "YA" : "TIDAK") << "\n";
    }

    return 0;
}
