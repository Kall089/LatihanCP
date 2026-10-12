/*
============================================================
✅ Solution 1: Panjang LCS
============================================================
Approach: DP tabel dua dimensi atas pasangan PREFIKS
Complexity: Time O(n*m) | Space O(n*m)
Key Insight: Untuk dua string, keputusan terakhir selalu tentang HURUF
             TERAKHIR kedua prefiks. Kalau cocok, pasangkan; kalau tidak,
             buang salah satunya dan ambil yang lebih baik.

📖 REKURENS:
   dp[i][j] = panjang LCS dari a[0..i-1] dan b[0..j-1]
   cocok : dp[i][j] = dp[i-1][j-1] + 1
   beda  : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
   base  : dp[0][j] = dp[i][0] = 0   (LCS dengan string kosong = 0)

📖 KENAPA SAAT COCOK KITA TIDAK PERLU MEMBANDINGKAN DENGAN max(atas, kiri)?
   Klaim: kalau a[i-1] == b[j-1] = c, SELALU ada LCS optimal yang memakai
   pasangan huruf itu.
   Bukti: ambil LCS optimal apa pun. Kalau ia tidak memakai a[i-1] maupun
   b[j-1], tambahkan c di ujungnya -> lebih panjang, kontradiksi. Kalau ia
   memakai a[i-1] tapi dipasangkan ke b[k] dengan k < j-1, tukar pasangannya
   ke b[j-1] -- panjangnya sama dan tetap sah. Jadi diagonal saja aman.

⚠️ INDEKS. Tabel 1-INDEXED, string 0-INDEXED. Huruf terakhir prefiks i adalah
   a[i-1]. Menulis a[i] adalah bug nomor satu di seluruh materi DP dua string,
   dan gejalanya adalah jawaban yang meleset satu atau segmentation fault.

⚠️ ALOKASI (n+1) x (m+1), bukan n x m.

⚠️ MEMORI. 3000 x 3000 int = 36 MB. Masih aman, tapi 5000 x 5000 = 100 MB
   sudah di ambang batas. Kalau hanya panjangnya yang diminta, pakai rolling
   array (lihat template bagian 2).

VERIFIKASI SAMPEL 1 (a="abcbdab", b="bdcaba"):
   dp[7][6] = 4  ✓
   Salah satu LCS: "bcba". Yang lain: "bdab", "bcab".
   Panjangnya unik; barisannya TIDAK.

VERIFIKASI SAMPEL 3 (a="ace", b="abcde"):
   a seluruhnya subsekuens dari b -> 3  ✓

🔄 ALTERNATIVE APPROACHES:
- Rolling array: O(min(n,m)) memori, tapi rekonstruksi jadi mustahil.
- Kalau kedua string adalah PERMUTASI, LCS bisa diubah menjadi LIS dan
  diselesaikan O(n log n) (Day 148).
- Untuk string sangat besar: bitset O(nm/64), atau Hunt-Szymanski kalau
  pasangan cocoknya sedikit.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;   // a[i-1], BUKAN a[i]
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    cout << dp[n][m] << '\n';
    return 0;
}
