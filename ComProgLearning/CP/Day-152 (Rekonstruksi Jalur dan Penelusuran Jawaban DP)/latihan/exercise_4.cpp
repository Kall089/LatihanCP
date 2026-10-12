/*
============================================================
🏋️ Exercise 4: Rekonstruksi Subsekuens Bersama Terpanjang (LCS Reconstruction)
============================================================
Day: 152 | Difficulty: Medium | Topic: 2D DP Table Backtracking
Source: AtCoder Educational DP Contest F (LCS)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan dua buah string s dan t yang hanya terdiri dari karakter huruf kecil.
Tentukan sebuah string yang merupakan Subsekuens Bersama Terpanjang (Longest Common Subsequence - LCS)
dari kedua string tersebut.
Sebuah subsekuens dari sebuah string adalah string baru yang dibentuk dari string asli
dengan menghapus nol atau lebih karakter tanpa mengubah urutan relatif karakter yang tersisa.

Jika terdapat lebih dari satu kemungkinan LCS terpanjang, kamu boleh mencetak salah satu yang valid.

📥 INPUT FORMAT:
- Baris pertama berisi string s.
- Baris kedua berisi string t.

📤 OUTPUT FORMAT:
- Satu baris berisi string yang merupakan LCS terpanjang dari s dan t.
  (Jika LCS kosong, cetak baris kosong).

📏 CONSTRAINTS:
- 1 <= |s|, |t| <= 3.000
- s dan t hanya terdiri dari huruf kecil 'a'..'z'.

📎 SAMPLE INPUT 1:
axyb
abyxb

📎 SAMPLE OUTPUT 1:
axb

[Penjelasan Sample 1:
Panjang LCS terpanjang adalah 3.
Kemungkinan LCS dengan panjang 3 antara lain "axb" dan "ayb". Keduanya diterima.]

📎 SAMPLE INPUT 2:
aa
xya

📎 SAMPLE OUTPUT 2:
a

📎 SAMPLE INPUT 3:
abracadabra
avadakedavra

📎 SAMPLE OUTPUT 3:
aaadara

💡 HINT:
- Isi tabel DP 2D ukuran (|s|+1) x (|t|+1):
  - Jika s[i-1] == t[j-1]: dp[i][j] = dp[i-1][j-1] + 1.
  - Jika beda: dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
- Penelusuran Mundur (Backtracking):
  Mulai dari (i = |s|, j = |t|):
  - Jika s[i-1] == t[j-1]: karakter s[i-1] adalah bagian dari LCS!
    Simpan s[i-1], lalu mundur ke (i-1, j-1).
  - Jika beda:
    Jika dp[i-1][j] >= dp[i][j-1], mundur ke (i-1, j).
    Jika tidak, mundur ke (i, j-1).
- Jangan lupa: balikkan string hasil (reverse) sebelum mencetak!

🎯 Learning Goals:
- [ ] Menguasai penelusuran mundur 2D pada masalah string klasik (LCS).
- [ ] Menggunakan memori tabel DP tanpa array jejak tambahan (Table Backtracking).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan LCS Reconstruction
    // 1. Tabulasi dp[n+1][m+1]
    // 2. Backtracking dari (n, m) ke (0, 0)
    // 3. Reverse string hasil dan cetak

    return 0;
}
