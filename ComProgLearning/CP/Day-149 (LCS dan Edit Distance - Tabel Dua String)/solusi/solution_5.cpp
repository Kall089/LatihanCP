/*
============================================================
✅ Solution 5: Substring Bersama Terpanjang
============================================================
Approach: tabel LCS dengan satu baris diubah -- RESET alih-alih max
Complexity: Time O(n*m) | Space O(n*m)
Key Insight: Substring harus BERDEKATAN. Jadi begitu ada satu huruf yang tidak
             cocok, rantainya PUTUS dan harus dimulai dari nol lagi. Itu
             berarti dp[i][j] direset ke 0, bukan mewarisi nilai tetangga.

📖 REKURENS:
   dp[i][j] = panjang substring bersama yang BERAKHIR TEPAT di a[i-1] dan b[j-1]
   cocok : dp[i][j] = dp[i-1][j-1] + 1
   beda  : dp[i][j] = 0                       <-- RESET
   jawaban = MAX atas SELURUH tabel           <-- bukan dp[n][m]

📖 PERHATIKAN POLA YANG SAMA SEPERTI KADANE (Day 143):
   Definisinya "BERAKHIR TEPAT DI ..." -- dan konsekuensinya selalu sama:
   jawabannya adalah maksimum atas seluruh state, bukan state terakhir.
   Kalau kamu mengambil dp[n][m], kamu hanya menanyakan "substring bersama
   yang berakhir tepat di huruf terakhir KEDUA string", yang hampir selalu 0.

⚠️ JANGAN TERTUKAR ANTARA SUBSEQUENCE DAN SUBSTRING.
   Sampel 2 sengaja memakai string yang sama dengan Latihan 1: LCS-nya 4,
   tapi substring bersama terpanjangnya hanya 2. Kalau kodemu memberi 4 di
   sampel itu, kamu masih memakai max alih-alih reset.

⚠️ SIMPAN INDEKS AKHIR untuk memotong substring-nya:
   a.substr(endA - best, best).
   Simpan endA hanya saat rekor baru dipecahkan.

⚠️ MEMORI. Kalau hanya panjangnya yang diminta, rolling array bekerja di sini
   juga -- dan lebih mudah daripada di LCS, karena kita hanya butuh diagonal
   (dp[i-1][j-1]), bukan atas dan kiri.

VERIFIKASI SAMPEL 1 (a="abcdxyz", b="xyzabcd"):
   Blok "abcd" cocok di a[0..3] dan b[3..6] -> dp naik 1,2,3,4 di diagonal itu
   Blok "xyz" cocok -> maksimum 3
   best = 4, substring "abcd"  ✓

VERIFIKASI SAMPEL 2 (a="abcbdab", b="bdcaba"):
   Pasangan terpanjang yang berdekatan: "ab" (a[0..1] vs b[3..4]) -> 2  ✓
   Bandingkan: LCS-nya 4. Perbedaan inilah inti latihan ini.

🔄 ALTERNATIVE APPROACHES:
- SUFFIX AUTOMATON atau SUFFIX ARRAY dari a + '#' + b: O((n+m) log) atau
  bahkan linear. Diperlukan kalau string-nya besar (10^5), di mana O(n*m)
  mustahil. Itu materi Day 210-an.
- Binary search pada panjang + hashing (Day 211): tebak L, kumpulkan semua
  hash substring sepanjang L dari kedua string, cek irisannya.
  O((n+m) log n) dan jauh lebih mudah daripada suffix automaton.
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
    int best = 0, endA = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = 0;              // RESET
            if (dp[i][j] > best) { best = dp[i][j]; endA = i; }
        }

    cout << best << '\n';
    cout << (best ? a.substr(endA - best, best) : string()) << '\n';
    return 0;
}
