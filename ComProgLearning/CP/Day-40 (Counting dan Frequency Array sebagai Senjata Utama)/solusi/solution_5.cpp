/*
============================================================
✅ Solution 5: Hitung Huruf dalam Substring
============================================================
Approach: 26 prefix sum, satu untuk tiap huruf
Complexity: Time O(26n + q) | Space O(26n)
Key Insight: "Berapa huruf c di dalam s[l..r]" adalah prefix count (Day 29)
             yang dijalankan 26 kali secara paralel. Tidak ada ide baru --
             hanya penerapan alat lama pada 26 array sekaligus.

📖 PENJELASAN PENDEKATAN:
1. pre[i][c] = berapa huruf c di dalam s[0..i-1].
2. pre[i+1] = pre[i] (salin seluruh 26 slot), lalu naikkan slot s[i].
3. Jawaban = pre[r][c] - pre[l-1][c] untuk L, R yang 1-based.

MENYALIN 26 SLOT setiap langkah terlihat boros, tetapi totalnya hanya
26n operasi -- untuk n = 10^5 itu 2.6 juta, tidak terasa. Memakai
array<int,26> membuat penyalinan menjadi satu operasi memori kontigu
yang sangat cepat.

⚠️ HITUNG MEMORINYA SEBELUM MENULIS. Ini kebiasaan yang penting:
   n = 10^5  -> (10^5+1) * 26 * 4 byte ~= 10.4 MB     AMAN
   n = 10^6  -> 104 MB                                RISIKO MLE
   n = 10^7  -> 1 GB                                  MUSTAHIL

   Kalau n terlalu besar, alternatifnya: simpan posisi kemunculan tiap
   huruf dalam 26 vector terurut, lalu jawab dengan upper_bound -
   lower_bound. Memorinya hanya O(n) total, dengan biaya O(log n) per query.

⚠️ Perhatikan konversi 1-based ke 0-based. Dengan pre berukuran n+1,
   jawaban untuk L, R yang 1-based adalah pre[R] - pre[L-1] -- tidak perlu
   penyesuaian lain. Konvensi n+1 sekali lagi membayar dirinya sendiri.

🔄 ALTERNATIVE APPROACHES:
- 26 vector posisi + binary search: O(n) memori, O(log n) per query.
  Pilihan yang lebih baik saat n sangat besar.
- Wavelet tree (Day 194): berlebihan untuk alfabet 26.
- Kalau alfabetnya besar (misalnya nilai sampai 10^9), pendekatan 26-array
  runtuh sepenuhnya dan kamu HARUS memakai vector posisi + binary search.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    n = s.size();

    vector<array<int, 26>> pre(n + 1);
    pre[0].fill(0);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i];               // salin 26 slot, kontigu & cepat
        pre[i + 1][s[i] - 'a']++;
    }

    string out;
    while (q--) {
        int l, r;
        char c;
        cin >> l >> r >> c;
        out += to_string(pre[r][c - 'a'] - pre[l - 1][c - 'a']);
        out += '\n';
    }
    cout << out;

    return 0;
}
