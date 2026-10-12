/*
============================================================
✅ Solution 3: Edit Distance (Levenshtein)
============================================================
Approach: tabel dua dimensi, minimum atas tiga operasi
Complexity: Time O(n*m) | Space O(n*m)
Key Insight: Tabelnya PERSIS tabel LCS. Yang berubah hanya tiga hal:
             base case, operator gabung (min alih-alih max), dan fakta bahwa
             diagonal kini juga dipakai saat huruf BERBEDA -- karena "ganti"
             adalah operasi yang tersedia di sini dan tidak tersedia di LCS.

📖 MEMBACA KETIGA ARAH SEBAGAI OPERASI FISIK:
   DIAGONAL dp[i-1][j-1] = GANTI a[i-1] menjadi b[j-1].
                           Kedua prefiks menyusut satu.
   ATAS     dp[i-1][j]   = HAPUS a[i-1].
                           Prefiks a menyusut; b[j-1] masih harus diurus.
   KIRI     dp[i][j-1]   = SISIP b[j-1] ke dalam a.
                           Prefiks b menyusut; a tidak.
   Kalau kamu bisa mengucapkan tiga kalimat ini tanpa melihat, kamu sudah
   menguasai edit distance.

⚠️ BASE CASE BUKAN NOL -- INI PERBEDAAN TERPENTING DARI LCS.
   dp[i][0] = i artinya "ubah a[0..i-1] menjadi string kosong" = i penghapusan.
   dp[0][j] = j artinya "bangun b[0..j-1] dari kosong" = j penyisipan.
   Mengisinya dengan 0 membuat seluruh tabel terlalu kecil, dan jawabannya
   tetap "kelihatan masuk akal" -- bug yang lolos dari uji kecil.
   Sampel 2 ("abcde" -> "a", jawaban 4) menangkapnya langsung.

⚠️ SAAT HURUF COCOK, BIAYANYA 0 -- bukan 1, dan TIDAK perlu dibandingkan
   dengan hapus/sisip. (Secara formal perbandingan itu tidak pernah menang,
   dengan argumen exchange yang mirip Solution 1.)

⚠️ MEMORI. 5000 x 5000 int = 100 MB. Kalau hanya angkanya yang diminta, pakai
   rolling array. Jangan mendeklarasikan int dp[5001][5001] sebagai variabel
   LOKAL -- itu stack overflow; pakai global atau vector.

VERIFIKASI SAMPEL 1 ("kitten" -> "sitting"):
   dp[6][7] = 3   ✓
   Jejaknya: k->s (ganti), e->i (ganti), sisipkan g.

VERIFIKASI SAMPEL 2 ("abcde" -> "a"):
   Hapus b, c, d, e -> 4  ✓  (base case yang membuat ini benar)

🔄 ALTERNATIVE APPROACHES:
- Tanpa operasi GANTI (hanya sisip/hapus): jawabannya n + m - 2*LCS.
  Itu soal LC 583, dan hubungannya menjelaskan kenapa "ganti" berharga:
  ia mengerjakan pekerjaan dua operasi sekaligus.
- Biaya berbeda per operasi: ganti min-nya dengan versi berbobot. Menariknya,
  kalau biaya ganti > sisip + hapus, min() otomatis memilih hapus+sisip --
  tidak perlu if tambahan.
- Kalau hanya perlu tahu "apakah jaraknya <= k", ada optimasi pita (band)
  yang hanya menghitung 2k+1 diagonal -> O(n*k).
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
    for (int i = 0; i <= n; i++) dp[i][0] = i;     // HAPUS semua
    for (int j = 0; j <= m; j++) dp[0][j] = j;     // SISIP semua

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];          // gratis
            else dp[i][j] = 1 + min({ dp[i-1][j-1],                 // GANTI
                                      dp[i-1][j],                   // HAPUS
                                      dp[i][j-1] });                // SISIP

    cout << dp[n][m] << '\n';
    return 0;
}
