/*
============================================================
🏋️ Exercise 5: Urutan Tugas dengan Bobot
============================================================
Day: 71 | Difficulty: Hard
Topic: Exchange argument untuk menurunkan komparator
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tugas. Tugas ke-i membutuhkan waktu t[i] untuk dikerjakan dan punya
bobot kepentingan w[i].
Tugas dikerjakan satu per satu tanpa jeda. Kalau tugas ke-i selesai pada
detik C[i], maka ia menyumbang biaya sebesar w[i] * C[i].
Susun urutan pengerjaan sehingga TOTAL BIAYA menjadi sekecil mungkin, lalu
cetak total biaya minimum itu.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: t[i] dan w[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total biaya minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= t[i], w[i] <= 10^6

📎 SAMPLE INPUT 1:
3
3 1
1 2
2 3

📎 SAMPLE OUTPUT 1:
17

📎 SAMPLE INPUT 3:
2
5 1
1 1

📎 SAMPLE OUTPUT 3:
7

💡 HINT: Ini generalisasi dari Exercise 1: di sana seluruh bobot bernilai
         satu. Sekarang bobotnya berbeda-beda, dan kriteria "terpendek
         dulu" belum tentu masih benar.
         Pakai teknik yang sama: ambil DUA tugas berdampingan, i lalu j.
         Tuliskan total biaya keduanya untuk urutan (i, j), lalu untuk
         urutan (j, i). Perhatikan bahwa tugas-tugas lain memberikan
         kontribusi yang SAMA pada kedua kasus, sehingga bisa diabaikan.
         Susun pertidaksamaan "urutan (i,j) lebih baik", lalu SEDERHANAKAN
         sampai kamu mendapat perbandingan antara dua besaran yang
         masing-masing hanya melibatkan satu tugas. Itulah komparatormu.
         Setelah menemukannya, waspadai satu hal: bentuk komparator yang
         melibatkan pembagian bisa kehilangan presisi. Bagaimana kamu
         menuliskannya kembali dengan perkalian saja? Dan apakah perkalian
         itu bisa meluap?

🎯 Learning Goals:
- [ ] Menurunkan komparator dari pertidaksamaan exchange argument
- [ ] Mengubah perbandingan pecahan menjadi perbandingan perkalian
- [ ] Mewaspadai overflow pada komparator
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: turunkan komparator dari pertidaksamaan dua tugas

    // TODO: hindari pembagian; perhatikan tipe data pada perkalian

    return 0;
}
