/*
============================================================
✅ Solution 4: Edit Distance + Daftar Operasinya
============================================================
Approach: tabel penuh, lalu telusuri balik sambil mengidentifikasi operasi
Complexity: Time O(n*m) | Space O(n*m)
Key Insight: Setiap sel tabel edit distance mendapat nilainya dari tepat satu
             (atau lebih) tetangga. Membandingkan dp[i][j] dengan ketiga
             tetangganya memberitahu kita operasi mana yang dipakai -- tidak
             perlu menyimpan array jejak terpisah.

📖 ATURAN PENELUSURAN dari (i, j):
   1. a[i-1] == b[j-1]                 -> COCOK, gratis. i--, j--
   2. dp[i][j] == dp[i-1][j-1] + 1     -> GANTI a[i-1] -> b[j-1]. i--, j--
   3. dp[i][j] == dp[i-1][j] + 1       -> HAPUS a[i-1]. i--
   4. selain itu                        -> SISIP b[j-1]. j--

⚠️ LOOP-NYA (i > 0 || j > 0), BUKAN &&.
   Kalau salah satu string sudah habis, sisanya TETAP harus diurus: kalau
   i > 0 dan j == 0, semua sisa a harus dihapus; kalau i == 0 dan j > 0,
   semua sisa b harus disisipkan. Memakai && akan diam-diam melewatkan
   operasi-operasi itu, sehingga jumlah baris yang tercetak kurang dari
   angka yang kamu cetak di baris pertama -- WA yang membingungkan.
   Sampel 2 ("abc" -> "a") menguji tepat kasus ini.

⚠️ PERIKSA "COCOK" LEBIH DULU. Kalau nomor 2 dicek duluan, kamu bisa
   melaporkan "GANTI a -> a" pada huruf yang sebenarnya sudah sama.

⚠️ SETIAP CABANG WAJIB DIJAGA BATAS INDEKSNYA (i > 0, j > 0) sebelum
   mengakses dp[i-1][...] atau a[i-1]. Tanpa penjagaan itu, kasus di tepi
   tabel akan membaca di luar batas.

⚠️ JAWABANNYA TIDAK UNIK. Kalau ada beberapa jejak dengan jumlah operasi
   sama, mana pun benar. Jangan bandingkan dengan satu output tetap.

VERIFIKASI SAMPEL 1 ("kitten" -> "sitting", dp = 3):
   (6,7): n vs g beda, dp[6][7]=3, dp[5][6]=3 -> bukan diag+1(4);
          dp[6][6]=2 -> 2+1=3 cocok? itu cabang HAPUS... periksa juga
          dp[6][6] adalah ATAS? Bukan: atas = dp[i-1][j] = dp[5][7] = 4.
          kiri = dp[6][6] = 2 -> 2+1 = 3 -> SISIP g. j-- -> (6,6)
   (6,6): n == n -> cocok, (5,5)
   (5,5): e vs i beda, diag dp[4][4]=1 -> 1+1=2 = dp[5][5] -> GANTI e -> i
   (4,4): t == t -> (3,3) ; (3,3): t == t -> (2,2)
   (2,2): i == i -> (1,1)
   (1,1): k vs s beda, diag dp[0][0]=0 -> 0+1=1 = dp[1][1] -> GANTI k -> s
   hasil (setelah reverse): GANTI k -> s, GANTI e -> i, SISIP g   ✓

VERIFIKASI SAMPEL 3 ("aa" -> "aa"):
   Semua cocok, loop selesai tanpa mencatat apa pun -> 0 operasi  ✓

🔄 ALTERNATIVE APPROACHES:
- Simpan array arah saat mengisi tabel: penelusuran jadi trivial, memori
  bertambah satu tabel. Berguna kalau biaya operasinya tidak seragam sehingga
  perbandingan "dp[i][j] == tetangga + 1" tidak lagi berlaku.
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
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});

    vector<string> ops;
    int i = n, j = m;
    while (i > 0 || j > 0) {                       // "||", BUKAN "&&"
        if (i > 0 && j > 0 && a[i-1] == b[j-1]) {  // COCOK diperiksa DULU
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + 1) {
            ops.push_back(string("GANTI ") + a[i-1] + " -> " + b[j-1]);
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + 1) {
            ops.push_back(string("HAPUS ") + a[i-1]);
            i--;
        } else {
            ops.push_back(string("SISIP ") + b[j-1]);
            j--;
        }
    }
    reverse(ops.begin(), ops.end());

    cout << dp[n][m] << '\n';
    for (auto& s : ops) cout << s << '\n';
    return 0;
}
