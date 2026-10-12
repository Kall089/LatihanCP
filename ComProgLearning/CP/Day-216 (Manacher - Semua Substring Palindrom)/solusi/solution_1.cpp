/*
============================================================
✅ Solution 1: Palindrom Terpanjang
============================================================
Approach: Manacher versi transformasi
Complexity: Time O(n) | Space O(n)
Key Insight: Sisipkan pemisah di antara setiap huruf sehingga SEMUA palindrom
             berpanjang ganjil. Lalu simpan satu palindrom "paling kanan"
             (pusat c, batas r) dan gunakan CERMIN p[2c - i] untuk menebak
             jawaban di posisi baru — analog persis dengan z-box Day 215,
             hanya simetrinya refleksi, bukan translasi.

📖 PENJELASAN PENDEKATAN:
1. T = "#a#b#...#", panjangnya 2n+1 (selalu ganjil).
2. Untuk tiap i:
   a. Kalau i < r, isi di sekitar i adalah cerminan isi di sekitar 2c - i,
      jadi p[i] >= min(r - i, p[2c - i]).
      Batas r - i wajib: di luar r kita belum punya bukti apa pun.
   b. Ekspansi manual.
   c. Perbarui (c, r) kalau jangkauannya melewati r.
3. Ambil p[i] terbesar; panjang asli = p[i], posisi awal = (i - p[i]) / 2.

MENGAPA O(n): setiap iterasi while yang berhasil mendorong r maju minimal 1.
r monoton naik dan terbatas 2n+1, jadi total ekspansi manual O(n).

⚠️ KONVERSI INDEKS adalah bagian yang paling sering salah, bukan algoritmanya.
   Verifikasi sekali dengan "abba": p[4] = 4, posisi = (4-4)/2 = 0, jawab
   s.substr(0, 4) = "abba". ✓

🔄 ALTERNATIVE APPROACHES:
- Ekspansi dari pusat naif: O(n^2), TLE pada "aaaa...a". Cukup untuk n <= 5000.
- DP is_pal[l][r]: O(n^2) waktu DAN ruang -> MLE untuk n > 10^4.
- Hashing S + reverse(S) + binary search: O(n log n), probabilistik, bisa di-hack.
- Eertree: O(n), memberi lebih banyak (palindrom berbeda), tapi kodenya 3x lebih panjang.
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

    int best = 0, pos = 0;
    for (int i = 0; i < (int)p.size(); i++)
        if (p[i] > best) { best = p[i]; pos = (i - p[i]) / 2; }

    cout << s.substr(pos, best) << '\n';
    return 0;
}
