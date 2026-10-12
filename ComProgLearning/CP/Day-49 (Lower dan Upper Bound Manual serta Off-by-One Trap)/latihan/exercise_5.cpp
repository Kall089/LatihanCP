/*
============================================================
🏋️ Exercise 5: Pasangan dengan Selisih Terbatas
============================================================
Day: 49 | Difficulty: Hard
Topic: Bound untuk setiap elemen
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan sebuah bilangan K yang
non-negatif. Hitung ada berapa PASANGAN INDEKS (i, j) dengan i < j
sedemikian sehingga selisih absolut antara a[i] dan a[j] tidak melebihi K.
Perhatikan bahwa jawabannya bisa sangat besar.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya pasangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= K <= 10^9
- -10^9 <= a[i] <= 10^9
- Jawaban bisa mencapai ~2 * 10^10

📎 SAMPLE INPUT 1:
5 2
1 3 5 2 4

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
3 0
5 5 5

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Setelah array diurutkan, "selisih tidak melebihi K" menjadi jauh
         lebih mudah dinyatakan: untuk setiap elemen, semua pasangannya
         berada dalam sebuah rentang KONTIGU.
         Untuk setiap i, cari indeks terakhir j sehingga a[j] <= a[i] + K,
         lalu hitung berapa elemen di antara i+1 sampai j.
         Perhatikan tipe data untuk a[i] + K, dan tipe data untuk hasil
         akhirnya.
         (Kalau kamu menyadari bahwa batas kanannya MONOTON saat i maju,
         kamu bisa menggantinya dengan two pointers dan menghemat faktor
         log — coba pikirkan juga.)

🎯 Learning Goals:
- [ ] Memakai bound untuk mengubah kondisi pasangan jadi hitungan rentang
- [ ] Mewaspadai overflow pada nilai ambang maupun hasil
- [ ] Melihat hubungan antara binary search dan two pointers
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan

    // TODO: untuk tiap i, cari batas kanan dengan bound

    // TODO: akumulasi jumlah pasangan, pakai long long

    return 0;
}
