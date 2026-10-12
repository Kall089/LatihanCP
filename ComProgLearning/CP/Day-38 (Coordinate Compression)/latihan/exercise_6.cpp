/*
============================================================
🏋️ Exercise 6: Grid Setelah Pemadatan
============================================================
Day: 38 | Difficulty: Hard (Contest-level)
Topic: Kompresi dua dimensi
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Di sebuah papan raksasa berukuran 10^9 kali 10^9 terdapat N kartu, kartu
ke-i berada di baris A[i] dan kolom B[i]. Setiap posisi paling banyak
ditempati satu kartu.
Berulang kali, selama masih ada BARIS yang seluruhnya kosong dan berada
di antara dua baris yang berisi kartu, seluruh kartu di bawahnya digeser
ke atas satu langkah sehingga baris kosong itu hilang. Hal yang sama
berlaku untuk KOLOM kosong.
Setelah tidak ada lagi baris maupun kolom kosong yang bisa dihapus,
tentukan posisi akhir setiap kartu. Cetak posisi akhirnya (1-based)
dalam urutan yang sama dengan input.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: masing-masing A[i] dan B[i]

📤 OUTPUT FORMAT:
- N baris, masing-masing dua bilangan (baris dan kolom akhir, 1-based)

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= A[i], B[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 1
2 1
4 2
4 4

📎 SAMPLE OUTPUT 1:
1 1
2 1
3 2
3 3

💡 HINT: Deskripsi soalnya panjang, tetapi jawabannya sangat pendek:
         posisi akhir sebuah kartu hanyalah PERINGKAT koordinatnya di antara
         seluruh koordinat yang terpakai. Baris dan kolom dikompresi secara
         TERPISAH.
         Soal ini adalah kompresi koordinat 2D dalam bentuk paling murni —
         seluruh cerita penggeserannya hanyalah pembungkus.

🎯 Learning Goals:
- [ ] Mengenali kompresi di balik deskripsi soal yang berbelit
- [ ] Mengompres dua sumbu secara terpisah
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kumpulkan semua A ke satu kamus, semua B ke kamus lain

    // TODO: bangun keduanya, lalu cetak idx+1 masing-masing

    return 0;
}
