/*
============================================================
✅ Solution 3: Query Palindrom O(1)
============================================================
Approach: Manacher sekali, lalu lookup radius per query
Complexity: Time O(n + q) | Space O(n)
Key Insight: "Apakah S[l..r] palindrom" sama dengan "apakah radius palindrom
             di pusat (l, r) setidaknya sepanjang r - l + 1". Manacher sudah
             menyimpan radius maksimum di SETIAP pusat, jadi jawabannya
             satu perbandingan.

📖 PENJELASAN PENDEKATAN:
1. Manacher sekali di awal.
2. Turunkan indeks pusat:
   huruf S[k] berada di indeks 2k + 1 pada T.
   Titik tengah antara S[l] dan S[r] adalah ((2l+1) + (2r+1)) / 2 = l + r + 1.
3. Jawab: p[l + r + 1] >= r - l + 1.

Rumus ini bekerja untuk panjang genap maupun ganjil sekaligus — itulah hadiah
dari transformasi '#'. Kalau panjang (r-l+1) genap, l+r+1 kebetulan menunjuk
ke sebuah '#'; kalau ganjil, ia menunjuk ke huruf. Tidak perlu percabangan.

⚠️ 1-BASED vs 0-BASED: soal memberi 1-based. Kurangi 1 dari keduanya SEBELUM
   memakai rumus. Ini penyebab WA yang paling sering di soal jenis ini.

⚠️ I/O: dengan Q sampai 10^6, cin/cout tanpa sync_with_stdio(false) akan TLE.
   Kumpulkan output ke satu string lalu cetak sekali.

🔄 ALTERNATIVE APPROACHES:
- Hashing maju + mundur: O(1) per query juga, dan lebih fleksibel (bisa untuk
  pertanyaan non-palindrom). Tapi probabilistik dan bisa di-hack.
- DP is_pal[l][r]: O(n^2) memori -> mustahil untuk n = 10^6.
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

    int q;
    cin >> q;
    string out;
    out.reserve(q * 4);

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;                                  // ke 0-based
        bool ok = p[l + r + 1] >= r - l + 1;
        out += ok ? "YES\n" : "NO\n";
    }
    cout << out;

    return 0;
}
