/*
============================================================
🏋️ Exercise 4: Panjang LCS Dua Baris Bergantian (LCS Length O(min(N, M)) Space)
============================================================
Day: 153 | Difficulty: Medium | Topic: 2-Row Rolling Array LCS
Source: Classic DP / AtCoder DP F Variation
Time Limit: 2.0 detik | Memory Limit: 64 MB

📋 PROBLEM STATEMENT:
Diberikan dua string S dan T yang hanya terdiri dari karakter huruf kecil 'a'..'z'.
Tentukan PANJANG dari Subsekuens Bersama Terpanjang (Longest Common Subsequence - LCS)
antara string S dan string T.

Batasan: Panjang kedua string dapat mencapai 5.000 karakter.
Tabel 2D biasa berukuran 5001 x 5001 int akan memakan sekitar ~100 MB memori,
yang melampaui batas memori 64 MB (Memory Limit Exceeded).
Kamu DIHARUSKAN mengimplementasikan algoritma DP dengan teknik Rolling Array 2 Baris
sehingga pemakaian memori menjadi O(min(|S|, |T|)).

📥 INPUT FORMAT:
- Baris pertama berisi string S.
- Baris kedua berisi string T.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: panjang LCS dari S dan T.

📏 CONSTRAINTS:
- 1 <= |S|, |T| <= 5.000
- S dan T hanya berisi huruf kecil 'a'..'z'.
- Memori DP harus O(min(|S|, |T|)).

📎 SAMPLE INPUT 1:
axyb
abyxb

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1:
Subsekuens bersama terpanjang adalah "axb" atau "ayb" dengan panjang 3.]

📎 SAMPLE INPUT 2:
aa
xya

📎 SAMPLE OUTPUT 2:
1

📎 SAMPLE INPUT 3:
abracadabra
avadakedavra

📎 SAMPLE OUTPUT 3:
7

[Penjelasan Sample 3:
LCS adalah "aaadara" dengan panjang 7.]

💡 HINT:
- Jika panjang T > panjang S, tukar S dan T agar dimensi kolom M = min(|S|, |T|).
- Gunakan dua baris: `vector<int> prev(M + 1, 0)` dan `vector<int> cur(M + 1, 0)`.
- Untuk setiap karakter S[i-1] (i dari 1 sampai N):
  - `cur[0] = 0`
  - Untuk setiap j dari 1 sampai M:
    - Jika S[i-1] == T[j-1]: `cur[j] = prev[j-1] + 1`
    - Jika tidak: `cur[j] = max(prev[j], cur[j-1])`
  - Lakukan swap pointer: `prev.swap(cur)`.
- Cetak `prev[M]`.

🎯 Learning Goals:
- [ ] Mengimplementasikan DP LCS 2 baris (`prev` dan `cur`) untuk menghemat memori hingga 99%.
- [ ] Memahami kapan rekonstruksi tidak diperlukan sehingga optimasi memori aman digunakan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan LCS dengan 2 Baris Bergantian
    // 1. Pastikan string t adalah yang lebih pendek
    // 2. Gunakan prev dan cur berukuran |t| + 1
    // 3. Update dan swap setiap baris

    return 0;
}
