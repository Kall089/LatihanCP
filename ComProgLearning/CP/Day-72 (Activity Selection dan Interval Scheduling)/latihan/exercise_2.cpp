/*
============================================================
🏋️ Exercise 2: Menghapus Jadwal Bentrok
============================================================
Day: 72 | Difficulty: Easy
Topic: Varian penyamaran activity selection
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kalender kamu berisi N acara. Acara ke-i berlangsung pada rentang tertutup
[l[i], r[i]], artinya acara itu menempati seluruh waktu dari l[i] sampai
r[i] termasuk kedua ujungnya.
Dua acara dianggap bentrok kalau rentangnya beririsan, termasuk kalau hanya
bersentuhan di satu titik.
Cari BERAPA ACARA MINIMUM yang harus kamu hapus agar tidak ada lagi acara
yang bentrok.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: l[i] dan r[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah acara minimum yang dihapus

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= l[i] <= r[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 2
2 3
3 4
1 3

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
1
5 5

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Sebelum menulis apa pun, tanyakan: apakah ini soal baru, atau soal
         Exercise 1 yang ditanyakan dengan cara berbeda?
         Kalau kamu berhasil memilih sebanyak mungkin acara yang TIDAK
         bentrok, apa hubungan jumlah itu dengan jawaban yang diminta?
         Perhatikan bahwa kali ini rentangnya TERTUTUP dan bersentuhan pun
         dihitung bentrok. Sampel 1 sengaja memuat [1,2] dan [2,3] untuk
         mengujimu.
         Kemampuan mengenali soal yang sama dalam penyamaran berbeda jauh
         lebih berharga daripada menghafal algoritma baru.

🎯 Learning Goals:
- [ ] Mengenali penyamaran activity selection
- [ ] Menghubungkan "maksimal dipilih" dengan "minimal dibuang"
- [ ] Menyesuaikan syarat untuk rentang tertutup
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kenali bahwa ini soal yang sama

    // TODO: hati-hati, rentang di sini TERTUTUP

    return 0;
}
