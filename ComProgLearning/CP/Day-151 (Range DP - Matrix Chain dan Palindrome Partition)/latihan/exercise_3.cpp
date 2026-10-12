/*
============================================================
🏋️ Exercise 3: Potongan Sandi Palindrom (Palindrome Partitioning II)
============================================================
Day: 151 | Difficulty: Medium-Hard | Topic: Two-Stage DP (Range DP + 1D DP)
Source: LeetCode 132 (Palindrome Partitioning II) / Classic DP
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah sandi rahasia pada sebuah festival kuno ditulis dalam bentuk string S
yang hanya terdiri dari huruf kecil 'a'..'z'.
Kamu diminta memotong string tersebut di antara beberapa karakter sedemikian rupa
sehingga setiap potongan substring yang dihasilkan merupakan sebuah PALINDROM
(yaitu string yang sama jika dibaca dari kiri ke kanan maupun dari kanan ke kiri).

Tentukan jumlah garis potong MINIMUM yang diperlukan.
Catatan penting:
- Yang ditanyakan adalah jumlah garis pemotongan, BUKAN jumlah bagian hasil potongan.
- Hubungan: Jumlah Garis Potong = Jumlah Bagian - 1.
- Jika seluruh string S sudah merupakan palindrom, maka jumlah potongan yang dibutuhkan adalah 0.

📥 INPUT FORMAT:
- Satu baris berisi satu string S tanpa spasi.

📤 OUTPUT FORMAT:
- Satu bilangan bulat: jumlah garis potong minimum.

📏 CONSTRAINTS:
- 1 <= |S| <= 1.200
- S hanya berisi karakter huruf kecil 'a'..'z'.

📎 SAMPLE INPUT 1:
aab

📎 SAMPLE OUTPUT 1:
1

[Penjelasan Sample 1:
Potong string menjadi "aa" dan "b".
Kedua potongan merupakan palindrom ("aa" palindrom, "b" palindrom).
Jumlah garis potong = 1.]

📎 SAMPLE INPUT 2:
racecar

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
String "racecar" sudah merupakan palindrom penuh, sehingga butuh 0 potongan.]

📎 SAMPLE INPUT 3:
abc

📎 SAMPLE OUTPUT 3:
2

[Penjelasan Sample 3:
Potong menjadi "a", "b", "c". Butuh 2 garis potong.]

💡 HINT:
- Selesaikan dalam dua tahap terpisah:
  1. Tahap 1 (Range DP Boolean O(N^2)):
     Hitung tabel `isPal[l][r]` bernilai true jika substring S[l..r] palindrom.
     Basis:
     - len = 1: isPal[i][i] = true
     - len = 2: isPal[i][i+1] = (S[i] == S[i+1])
     - len >= 3: isPal[l][r] = (S[l] == S[r]) && isPal[l+1][r-1].
  2. Tahap 2 (DP 1D Linear O(N^2)):
     Definisikan dp[r] = jumlah bagian palindrom minimum untuk prefix sepanjang r karakter (S[0..r-1]).
     dp[0] = 0.
     Untuk r dari 1 s.d. n:
       Untuk l dari 0 s.d. r-1:
         Jika isPal[l][r-1]: dp[r] = min(dp[r], dp[l] + 1).
  3. Hasil akhir garis potong = dp[n] - 1.

🎯 Learning Goals:
- [ ] Menggabungkan pra-komputasi Range DP dengan transisi DP 1D linear.
- [ ] Menerapkan pengecekan palindrom interval dalam waktu O(1) setelah preprocessing.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // TODO: Selesaikan Palindrome Partitioning II
    // 1. Bangun tabel isPal[n][n] dengan Range DP
    // 2. Bangun array dp[n + 1] dengan DP 1D
    // 3. Cetak dp[n] - 1

    return 0;
}
