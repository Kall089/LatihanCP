/*
============================================================
🏋️ Exercise 4: Paling Banyak K Jenis
============================================================
Day: 34 | Difficulty: Medium
Topic: Window + hitungan jenis
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah keranjang buah berisi N buah yang berjajar, buah ke-i berjenis a[i].
Kamu berjalan menyusuri jajaran itu dan mengambil buah secara BERURUTAN,
tetapi keranjangmu hanya boleh memuat paling banyak K JENIS buah berbeda
(jumlah buahnya tidak dibatasi, hanya jenisnya).
Cari jumlah buah TERBANYAK yang bisa kamu ambil.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= K <= N
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
6 2
1 2 1 2 3 3

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
5 1
1 1 2 2 2

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Simpan hitungan tiap jenis di dalam window, dan satu variabel
         "berapa jenis berbeda yang sedang ada". Dua pola yang harus
         berpasangan rapi:
             masuk : if (cnt[x]++ == 0) jenis++;
             keluar: if (--cnt[x] == 0) jenis--;

🎯 Learning Goals:
- [ ] Menjaga invariant hitungan jenis saat elemen masuk dan keluar
- [ ] Menulis operasi masuk/keluar yang saling bercermin
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: map hitungan, variabel jenis

    // TODO: masukkan a[r], susutkan selama jenis > K, catat panjang

    return 0;
}
