/*
============================================================
🏋️ Exercise 5: Titik Pemotongan Paling Seimbang
============================================================
Day: 29 | Difficulty: Hard
Topic: Prefix sum + minimisasi selisih
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah tali direpresentasikan sebagai array berisi N bilangan bulat, di mana
a[i] adalah berat manik ke-i. Kamu harus memotong tali itu di antara dua manik
sehingga terbagi menjadi dua bagian yang keduanya tidak kosong.
Cari posisi potong yang membuat SELISIH ABSOLUT antara total berat bagian kiri
dan total berat bagian kanan menjadi SEKECIL MUNGKIN. Cetak selisih minimum itu.
Jika ada beberapa posisi dengan selisih yang sama kecilnya, cukup cetak
selisihnya saja.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: selisih absolut minimum

📏 CONSTRAINTS:
- 2 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5
3 1 4 1 5

📎 SAMPLE OUTPUT 1:
2

Penjelasan (total = 14):
  potong setelah 1 manik -> kiri 3,  kanan 11, selisih 8
  potong setelah 2 manik -> kiri 4,  kanan 10, selisih 6
  potong setelah 3 manik -> kiri 8,  kanan 6,  selisih 2   <- terkecil
  potong setelah 4 manik -> kiri 9,  kanan 5,  selisih 4

📎 SAMPLE INPUT 2:
2
10 -10

📎 SAMPLE OUTPUT 2:
20

💡 HINT: total = pre[n]. Kalau potong setelah i elemen pertama (1 <= i <= n-1),
         kiri = pre[i] dan kanan = total - pre[i]. Selisihnya
         |2*pre[i] - total|. Satu loop cukup.
         Perhatikan batas i: kedua bagian harus tidak kosong.

🎯 Learning Goals:
- [ ] Menyatakan "kanan" sebagai total dikurangi "kiri"
- [ ] Berhati-hati pada batas iterasi agar bagian tidak kosong
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: bangun prefix

    // TODO: untuk i = 1..n-1, hitung |2*pre[i] - total|, ambil minimum

    return 0;
}
