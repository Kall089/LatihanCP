/*
============================================================
✅ Solution 6: Supersequence Bersama Terpendek (SCS)
============================================================
Approach: tabel LCS, lalu telusuri balik sambil menulis huruf dari KEDUA sisi
Complexity: Time O(n*m) | Space O(n*m)
Key Insight: Supersequence terpendek menulis huruf-huruf LCS SEKALI SAJA
             (dipakai bersama), dan semua huruf lain masing-masing sekali.
             Karena itu panjangnya n + m - LCS.

📖 KENAPA RUMUSNYA n + m - LCS:
   Setiap huruf a dan setiap huruf b harus muncul. Kalau tidak ada yang bisa
   dipakai bersama, panjangnya n + m. Setiap huruf yang bisa dipakai untuk
   MEMENUHI a DAN b sekaligus menghemat satu karakter. Jumlah maksimum huruf
   yang bisa dipakai bersama -- dengan urutan tetap terjaga di kedua string --
   persis definisi LCS.

📖 REKONSTRUKSINYA (telusuri balik tabel LCS):
   cocok                       -> tulis huruf itu SEKALI, i--, j--
   dp[i-1][j] >= dp[i][j-1]    -> tulis a[i-1], i--
   selain itu                  -> tulis b[j-1], j--
   Setelah loop, HABISKAN sisa string yang belum selesai.

⚠️ MENGHABISKAN SISA ADALAH LANGKAH YANG PALING SERING TERLUPA.
   Loop utama berhenti begitu salah satu indeks mencapai 0. Kalau i masih > 0,
   seluruh sisa a HARUS ditulis; sama untuk b. Melupakannya menghasilkan
   string yang lebih pendek dari yang seharusnya -- dan yang lebih buruk,
   string itu bukan supersequence yang sah.

⚠️ HURUF YANG COCOK DITULIS SEKALI, bukan dua kali. Di situlah penghematannya.

⚠️ JAWABANNYA TIDAK UNIK. Sampel 2 ("ab", "cd") bisa menghasilkan "abcd",
   "acbd", "cdab", dan lainnya -- semuanya sepanjang 4 dan semuanya sah.
   PANJANGNYA yang unik.

⚠️ VERIFIKASI HASILMU SENDIRI: tulis fungsi kecil yang mengecek apakah
   string a benar-benar subsekuens dari hasilmu (dua pointer, O(n)). Lakukan
   untuk a dan b. Ini cara tercepat menangkap bug rekonstruksi.

VERIFIKASI SAMPEL 1 (a="abac", b="cab"):
   LCS("abac","cab") = "ab" (panjang 2)
   panjang SCS = 4 + 3 - 2 = 5  ✓
   Telusuri balik menghasilkan "cabac":
     'c' subsekuens? c-a-b-a-c: ya untuk "cab" (c,a,b) dan "abac" (a,b,a,c) ✓

VERIFIKASI SAMPEL 3 (a="abcde", b="ace"):
   LCS = "ace" (3) -> panjang 5 + 3 - 3 = 5 -> "abcde"  ✓
   Masuk akal: b sudah subsekuens a, jadi a sendiri sudah cukup.

🔄 ALTERNATIVE APPROACHES:
- DP langsung: dp[i][j] = panjang SCS dari prefiks. cocok -> dp[i-1][j-1]+1;
  beda -> 1 + min(dp[i-1][j], dp[i][j-1]). Setara, dan kalau kamu menurunkannya
  sendiri kamu akan melihat ia hanya "LCS yang dibalik".
- SCS untuk TIGA string atau lebih adalah masalah NP-hard secara umum --
  jangan mencoba memperluas begitu saja.
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
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) { res += a[i-1]; i--; j--; }   // SEKALI saja
        else if (dp[i-1][j] >= dp[i][j-1]) { res += a[i-1]; i--; }
        else { res += b[j-1]; j--; }
    }
    while (i > 0) { res += a[i-1]; i--; }        // HABISKAN sisa a
    while (j > 0) { res += b[j-1]; j--; }        // HABISKAN sisa b
    reverse(res.begin(), res.end());

    cout << res.size() << '\n' << res << '\n';
    return 0;
}
