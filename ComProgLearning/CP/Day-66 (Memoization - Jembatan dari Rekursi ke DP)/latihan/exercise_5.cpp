/*
============================================================
🏋️ Exercise 5: Subsekuens Bersama Terpanjang (LCS Top-Down)
============================================================
Day: 066 | Difficulty: Medium | Topic: 2D Top-Down Memoization
Source: Classic LCS / Top-Down Paradigm
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan dua string teks S dan T.
Tentukan PANJANG dari Subsekuens Bersama Terpanjang (Longest Common Subsequence - LCS) dari S dan T!

Subsekuens dari sebuah string adalah barisan karakter baru yang dihasilkan dengan menghapus nol
atau beberapa karakter tanpa mengubah urutan relatif karakter yang tersisa.

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

📥 INPUT FORMAT:
- Baris pertama berisi string S.
- Baris kedua berisi string T.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: panjang LCS maksimum.

📏 CONSTRAINTS:
- 0 <= |S|, |T| <= 1.000
- S dan T hanya terdiri dari huruf kecil 'a'..'z'

📎 SAMPLE INPUT 1:
abcde
ace

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1:
Subsekuens bersama terpanjang adalah "ace" dengan panjang 3.]

📎 SAMPLE INPUT 2:
abc
def

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
Tidak ada karakter bersama, panjang LCS = 0.]

📎 SAMPLE INPUT 3:
aggtab
gxtxayb

📎 SAMPLE OUTPUT 3:
4

[Penjelasan Sample 3:
LCS adalah "gtab" dengan panjang 4.]

💡 HINT:
- Definisikan fungsi rekursif:
  `solve(i, j)`: panjang LCS dari substring `S[i..N-1]` dan `T[j..M-1]`.
- Kasus Dasar:
  - `if (i == N || j == M) return 0;`
- Cek Memoisasi:
  - `if (memo[i][j] != -1) return memo[i][j];`
- Transisi:
  - Jika `S[i] == T[j]`:
    `return memo[i][j] = 1 + solve(i + 1, j + 1);`
  - Jika `S[i] != T[j]`:
    `return memo[i][j] = max(solve(i + 1, j), solve(i, j + 1));`

🎯 Learning Goals:
- [ ] Memahami formulasi rekursif top-down untuk pencocokan dua string.
- [ ] Menangani kasus dasar string kosong dan percabangan 2 arah saat karakter tidak cocok.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan dengan 2D top-down memoization

    return 0;
}
