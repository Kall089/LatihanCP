/*
============================================================
🏋️ Exercise 3: Rata-rata Maksimum dari K Elemen
============================================================
Day: 51 | Difficulty: Medium
Topic: Trik a[i] - x
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan real dan sebuah bilangan K. Pilih TEPAT K bilangan di
antaranya sehingga RATA-RATA bilangan yang terpilih menjadi sebesar mungkin.
Cetak rata-rata maksimum itu dengan 6 desimal.
Perhatikan bahwa soal ini sebenarnya punya solusi langsung yang jauh lebih
sederhana. Tetapi kerjakanlah dengan BINARY SEARCH, karena teknik yang
dipakai di sini adalah kunci untuk Exercise 4 dan 5 yang tidak punya solusi
langsung.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan real

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 6 desimal

📏 CONSTRAINTS:
- 1 <= K <= N <= 10^5
- -10^6 <= a[i] <= 10^6

📎 SAMPLE INPUT 1:
4 2
1 3 5 2

📎 SAMPLE OUTPUT 1:
4.000000

📎 SAMPLE INPUT 2:
3 3
1.5 2.5 3.5

📎 SAMPLE OUTPUT 2:
2.500000

💡 HINT: "Rata-rata" bukan besaran yang monoton terhadap apa pun, sehingga
         binary search tidak bisa langsung diterapkan. Tetapi perhatikan:

             rata-rata terpilih >= x
             (jumlah terpilih) / K >= x
             jumlah terpilih - K*x >= 0
             jumlah dari (a[i] - x) untuk yang terpilih >= 0

         Setelah transformasi itu, pertanyaannya menjadi: "apakah ada K
         elemen yang jumlah (a[i] - x)-nya tidak negatif?" — dan itu cukup
         mengambil K nilai terbesar.
         Transformasi ini adalah pola terpenting dari seluruh materi hari
         ini. Pastikan kamu memahaminya, bukan sekadar menyalinnya.

🎯 Learning Goals:
- [ ] Menurunkan sendiri transformasi a[i] - x
- [ ] Memahami kenapa transformasi itu memulihkan monotonisitas
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: predikat bisa(x): ambil K nilai (a[i] - x) terbesar, cek jumlah >= 0

    // TODO: cari x TERBESAR yang masih layak

    return 0;
}
