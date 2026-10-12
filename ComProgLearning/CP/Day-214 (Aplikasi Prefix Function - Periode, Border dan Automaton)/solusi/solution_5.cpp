/*
============================================================
✅ Solution 5: Jumlah Substring Berbeda
============================================================
Approach: Penambahan inkremental + prefix function pada string terbalik
Complexity: Time O(n^2) | Space O(n)
Key Insight: Menambah satu karakter di akhir hanya bisa melahirkan substring
             baru yang berupa SUFIKS dari string baru. Sufiks dari cur =
             prefiks dari reverse(cur). Sebuah prefiks reverse(cur) sudah
             pernah ada sebelumnya persis ketika ia muncul lagi di tempat
             lain — dan panjang terbesar semacam itu adalah max(pi).

📖 PENJELASAN PENDEKATAN:
1. Bangun cur karakter demi karakter.
2. r = reverse(cur); hitung pi(r); mx = max(pi(r)).
3. Substring baru pada langkah ini = |cur| - mx.
   Alasannya: prefiks r sepanjang 1..mx semuanya muncul lagi di dalam r,
   artinya sufiks cur yang bersesuaian sudah pernah muncul sebelum karakter
   terakhir ditambahkan. Prefiks sepanjang mx+1 .. |cur| tidak muncul lagi,
   jadi semuanya benar-benar baru.
4. Jumlahkan.

Verifikasi "aba":
   cur="a"   r="a"    pi=[0]      mx=0  -> +1  (total 1)   {a}
   cur="ab"  r="ba"   pi=[0,0]    mx=0  -> +2  (total 3)   {b, ab}
   cur="aba" r="aba"  pi=[0,0,1]  mx=1  -> +2  (total 5)   {ba, aba}

🔄 ALTERNATIVE APPROACHES:
- Suffix automaton: O(n) — jumlah substring berbeda = sum(len[v]-len[link[v]]).
  Wajib kalau n > 10^5. Materi Day 222.
- Suffix array + LCP: n*(n+1)/2 - sum(LCP). O(n log n). Materi Day 220-221.
- Hashing semua substring ke set: O(n^2 log n) dan berisiko tabrakan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> bangunPi(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    ll total = 0;
    string cur;
    for (char ch : s) {
        cur += ch;
        string r(cur.rbegin(), cur.rend());
        vector<int> pi = bangunPi(r);
        int mx = 0;
        for (int v : pi) mx = max(mx, v);
        total += (ll)cur.size() - mx;
    }

    cout << total << '\n';
    return 0;
}
