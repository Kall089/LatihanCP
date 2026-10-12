/*
============================================================
🏋️ Exercise 6: Nilai Terkecil ke-K yang Dinamis
============================================================
Day: 170 | Difficulty: Hard (Contest-level)
Topic: BIT sebagai multiset + descent
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Mula-mula sebuah himpunan kosong (boleh memuat nilai kembar).
Ada Q operasi:
- "+ x" : masukkan bilangan x ke dalam himpunan.
- "- x" : keluarkan SATU salinan bilangan x dari himpunan (dijamin ada).
- "? k" : cetak bilangan TERKECIL KE-K yang ada di dalam himpunan saat itu
  (dijamin himpunan memuat setidaknya k elemen).
Nilai x bisa mencapai 10^9.

📥 INPUT FORMAT:
- Baris pertama: Q
- Q baris berikutnya: operasi

📤 OUTPUT FORMAT:
- Satu baris untuk setiap operasi "?"

📏 CONSTRAINTS:
- 1 <= Q <= 2 * 10^5
- 1 <= x <= 10^9
- 1 <= k <= ukuran himpunan saat itu

📎 SAMPLE INPUT 1:
6
+ 5
+ 2
+ 8
? 2
- 2
? 2

📎 SAMPLE OUTPUT 1:
5
8

💡 HINT: Simpan HITUNGAN setiap nilai di dalam struktur hari ini, bukan
         nilainya. Menyisipkan berarti menambah satu pada posisi nilai itu;
         mengeluarkan berarti mengurangi satu.
         Dengan begitu, query prefiks memberitahumu "berapa elemen yang
         nilainya tidak melebihi x" — dan itu adalah fungsi yang MONOTON
         terhadap x.
         Pendekatan paling langsung: binary search di luar struktur,
         memanggil query pada setiap langkah. Berapa kompleksitasnya?
         Tetapi ada cara yang lebih baik: kamu bisa MENURUNI struktur BIT
         secara langsung, memanfaatkan bahwa setiap simpul menanggung blok
         berukuran pangkat dua. Mulai dari pangkat dua terbesar dan
         turunkan, sambil memutuskan apakah melangkah ke kanan.
         Cara kedua menghilangkan satu faktor logaritma. Kerjakan cara
         pertama dulu, lalu coba yang kedua.
         Jangan lupa: seluruh nilai yang akan pernah muncul harus sudah
         diketahui sebelum kamu membangun kamus kompresi.

🎯 Learning Goals:
- [ ] Memakai BIT sebagai multiset dinamis
- [ ] Membandingkan binary search di luar versus descent di dalam
- [ ] Menyadari kapan O(log^2 n) bisa diturunkan menjadi O(log n)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca seluruh operasi, kumpulkan nilai, kompres

    // TODO: BIT menyimpan HITUNGAN per nilai

    // TODO: query ke-k lewat binary search, lalu perbaiki dengan descent

    return 0;
}
