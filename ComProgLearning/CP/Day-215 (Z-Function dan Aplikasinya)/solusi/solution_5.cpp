/*
============================================================
✅ Solution 5: Awalan Bersama Minimal K
============================================================
Approach: Z-array + histogram + suffix sum
Complexity: Time O(n) | Space O(n)
Key Insight: Posisi i menyumbang untuk SEMUA k dari 1 sampai z[i] sekaligus.
             Banyak penambahan rentang [1, z[i]] yang hanya dijawab sekali di
             akhir = kasus klasik difference array / suffix sum. Tidak perlu
             struktur data apa pun.

📖 PENJELASAN PENDEKATAN:
1. Bangun z. Ingat konvensi z[0] = 0 di sini, padahal posisi 0 sebenarnya
   cocok sepanjang n. Kita tangani secara terpisah di langkah 4.
2. hist[len]++ untuk tiap i >= 1 dengan z[i] = len.
3. f(k) = banyaknya i dengan z[i] >= k = suffix sum dari hist.
   Hitung mundur: f(k) = f(k+1) + hist[k].
4. Tambahkan 1 untuk posisi 0, yang cocok dengan prefiks berapa pun.

VERIFIKASI "aaa":
   z = [0, 2, 1]
   hist = [_, 1, 1, 0]     (z[1]=2 -> hist[2]++, z[2]=1 -> hist[1]++)
   suffix sum: f(3)=0, f(2)=0+1=1, f(1)=1+1=2
   +1 untuk posisi 0     : f(1)=3, f(2)=2, f(3)=1   ✓

Bandingkan dengan Day 214 solution 3 (versi pi): hasilnya identik, tapi di sana
kita mewariskan lewat rantai pi, di sini cukup suffix sum lurus. Untuk masalah
INI, z lebih sederhana.

⚠️ OVERFLOW: pada "aaaa...a" dengan n = 10^6, f(1) = 10^6 saja aman untuk int,
tetapi soal serupa yang menjumlahkan seluruh f(k) mencapai ~5*10^11. Pakai
long long sejak awal — biayanya nol.

🔄 ALTERNATIVE APPROACHES:
- Prefix function + agregasi rantai: O(n) (Day 214 solution 3).
- Suffix automaton: O(n), tapi jauh lebih panjang.
- Naif per k: O(n^2), TLE.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> bangunZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> z = bangunZ(s);

    // Step 1: histogram nilai z
    vector<ll> hist(n + 2, 0);
    for (int i = 1; i < n; i++) hist[z[i]]++;

    // Step 2: f(k) = jumlah i dengan z[i] >= k  (suffix sum)
    vector<ll> f(n + 2, 0);
    for (int k = n; k >= 1; k--) f[k] = f[k + 1] + hist[k];

    // Step 3: posisi 0 cocok dengan setiap prefiks
    string out;
    for (int k = 1; k <= n; k++) {
        out += to_string(f[k] + 1);
        out += '\n';
    }
    cout << out;

    return 0;
}
