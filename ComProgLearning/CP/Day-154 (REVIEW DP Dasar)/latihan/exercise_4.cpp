/*
============================================================
🏋️ Exercise 4: Pembagian Cerita Bergambar Terpanjang (LCS + Lexicographical Reconstruction)
============================================================
Day: 154 | Difficulty: Medium | Topic: 2D DP + Lexicographical Reconstruction
Source: Review Synthesis / AtCoder DP F Variant
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan dua teks naskah cerita S dan T yang hanya terdiri dari karakter huruf kecil 'a'..'z'.
Tugas kamu adalah:
1. Menentukan PANJANG dari Subsekuens Bersama Terpanjang (LCS) antara S dan T.
2. MEREKONSTRUKSI dan mencetak STRING LCS tersebut.

Jika terdapat LEBIH DARI SATU string LCS dengan panjang maksimum yang sama, kamu HARUS
mencetak string LCS yang SECARA LEKSIKOGRAFIS PALING KECIL!
Jika tidak ada karakter yang sama sama sekali (panjang 0), cetak 0 pada baris pertama dan baris kosong pada baris kedua.

Batasan: Panjang string S dan T hingga 1.000 karakter.

📥 INPUT FORMAT:
- Baris pertama berisi string S.
- Baris kedua berisi string T.

📤 OUTPUT FORMAT:
- Baris pertama berisi satu bilangan bulat: panjang LCS maksimum.
- Baris kedua berisi string LCS yang secara leksikografis paling kecil.

📏 CONSTRAINTS:
- 1 <= |S|, |T| <= 1.000
- S dan T hanya terdiri dari huruf kecil 'a'..'z'

📎 SAMPLE INPUT 1:
abacba
abdcaba

📎 SAMPLE OUTPUT 1:
5
ababa

[Penjelasan Sample 1:
Subsekuens bersama terpanjang memiliki panjang 5.
Kandidat LCS di antaranya adalah "ababa" dan "abcba".
Karena 'a' < 'c' pada karakter ke-3, "ababa" leksikografis lebih kecil daripada "abcba".]

📎 SAMPLE INPUT 2:
xyz
abc

📎 SAMPLE OUTPUT 2:
0


[Penjelasan Sample 2:
Tidak ada karakter yang sama, panjang LCS = 0, string kosong.]

📎 SAMPLE INPUT 3:
axyb
abyxb

📎 SAMPLE OUTPUT 3:
3
axb

[Penjelasan Sample 3:
LCS yang mungkin: "axb" dan "ayb". "axb" lebih kecil leksikografis.]

💡 HINT:
- Gunakan SUFFIX DP agar rekonstruksi dapat dilakukan secara GREEDY DARI DEPAN KE BELAKANG:
  - `dp[i][j]` = panjang LCS dari sufiks S[i..N-1] dan T[j..M-1].
  - Base case: `dp[N][*] = 0` dan `dp[*][M] = 0`.
  - Transisi:
    - Jika `S[i] == T[j]`: `dp[i][j] = 1 + dp[i+1][j+1]`.
    - Jika tidak: `dp[i][j] = max(dp[i+1][j], dp[i][j+1])`.
- Rekonstruksi Maju Leksikografis:
  - Dari state `(i, j)`, cari karakter huruf 'a'..'z' terkecil `c` sedemikian rupa sehingga:
    Karakter `c` muncul di posisi `i' >= i` pada S dan `j' >= j` pada T, dan
    `1 + dp[i'+1][j'+1] == dp[i][j]`.
  - Pilihlah kemunculan pertama karakter `c` tersebut, tambahkan `c` ke hasil, lalu lanjutkan dari `(i'+1, j'+1)`.

🎯 Learning Goals:
- [ ] Menguasai perpaduan antara perhitungan nilai optimal (panjang LCS) dan rekonstruksi string.
- [ ] Menerapkan teknik Suffix DP untuk menjamin hasil rekonstruksi terurut leksikografis terkecil.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan LCS Panjang + Rekonstruksi Leksikografis

    return 0;
}
