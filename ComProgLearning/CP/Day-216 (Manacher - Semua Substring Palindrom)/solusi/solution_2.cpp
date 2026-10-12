/*
============================================================
✅ Solution 2: Hitung Substring Palindrom
============================================================
Approach: Manacher + menjumlahkan jumlah palindrom per pusat
Complexity: Time O(n) | Space O(n)
Key Insight: Palindrom berpusat di i dengan radius p[i] "membungkus"
             palindrom-palindrom lebih pendek dengan PUSAT YANG SAMA:
             panjangnya p[i], p[i]-2, p[i]-4, ... sampai 1 atau 0.
             Banyaknya suku deret itu adalah ceil(p[i]/2) = (p[i]+1)/2.

📖 PENJELASAN PENDEKATAN:
1. Jalankan Manacher.
2. total = sum atas semua i dari (p[i] + 1) / 2.
3. Cetak dengan long long.

KENAPA TIDAK ADA YANG TERHITUNG DUA KALI: setiap substring palindrom punya
TEPAT SATU pusat pada string tertransformasi (pusat huruf kalau ganjil,
pusat '#' kalau genap). Jadi penjumlahan per pusat adalah partisi sempurna
dari himpunan palindrom.

VERIFIKASI "abba": p = [0,1,0,1,4,1,0,1,0]
   (0+1)/2=0, (1+1)/2=1, 0, 1, (4+1)/2=2, 1, 0, 1, 0  ->  total 6
   Manual: a,b,b,a (4) + bb (1) + abba (1) = 6  ✓

⚠️ OVERFLOW: "aaaa...a" dengan n = 10^6 menghasilkan n(n+1)/2 = 5.0005*10^11.
   int jebol pada n sekitar 65000. Pakai long long sejak awal.

⚠️ Ini menghitung KEMUNCULAN, bukan palindrom BERBEDA. "aaa" -> 6 kemunculan
   tapi hanya 3 palindrom berbeda {a, aa, aaa}. Untuk distinct, pakai Eertree.

🔄 ALTERNATIVE APPROACHES:
- Versi dua array (d1, d2): total = sum(d1) + sum(d2) — lebih langsung,
  tidak perlu rumus (p+1)/2 sama sekali. Lihat template bagian 5.
- Naif: O(n^2), cukup untuk n <= 5000.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> manacher(const string& s) {
    string t = "#";
    for (char c : s) { t += c; t += '#'; }
    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n
               && t[i - p[i] - 1] == t[i + p[i] + 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    vector<int> p = manacher(s);

    ll total = 0;
    for (int v : p) total += (v + 1) / 2;

    cout << total << '\n';
    return 0;
}
