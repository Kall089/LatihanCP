/*
============================================================
🏋️ Exercise 6: Menyewa K Pekerja
============================================================
Day: 75 | Difficulty: Hard (Contest-level)
Topic: Heap + rasio (menggabungkan Day 74 dan Day 75)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerja. Pekerja ke-i memiliki kualitas q[i] dan upah minimum yang
dia harapkan w[i].
Kamu harus menyewa TEPAT K pekerja, dan pembayarannya harus memenuhi dua
aturan sekaligus:
  (1) Setiap pekerja yang disewa dibayar SEBANDING dengan kualitasnya.
      Artinya, jika pekerja i dibayar p[i], maka p[i] / q[i] harus sama
      untuk semua pekerja yang disewa.
  (2) Setiap pekerja yang disewa harus dibayar minimal sebesar w[i].
Cari TOTAL PEMBAYARAN MINIMUM. Cetak dengan enam angka di belakang koma.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- N baris berikutnya: q[i] dan w[i]

📤 OUTPUT FORMAT:
- Satu bilangan real dengan enam angka di belakang koma

📏 CONSTRAINTS:
- 1 <= K <= N <= 10^5
- 1 <= q[i] <= 10^4
- 1 <= w[i] <= 10^4

📎 SAMPLE INPUT 1:
3 2
10 70
20 30
5 30

📎 SAMPLE OUTPUT 1:
105.000000

📎 SAMPLE INPUT 2:
1 1
7 42

📎 SAMPLE OUTPUT 2:
42.000000

💡 HINT: Mulailah dengan menyederhanakan aturannya. Kalau kamu sudah
         memilih sekelompok pekerja, berapa biaya terkecil untuk membayar
         mereka secara sah?
         Aturan (1) mengatakan ada satu bilangan r sehingga tiap pekerja
         dibayar r dikali kualitasnya. Aturan (2) mengatakan r dikali q[i]
         harus minimal w[i] untuk setiap anggota kelompok. Susun ulang
         pertidaksamaan itu — kamu akan mendapat batas bawah untuk r yang
         berbentuk rasio.
         Karena r harus memenuhi SELURUH anggota, r harus sama dengan yang
         TERBESAR di antara batas-batas itu. Dan totalnya menjadi r dikali
         jumlah kualitas kelompok.
         Sekarang kamu punya rumus biaya yang hanya bergantung pada dua hal:
         rasio terbesar di dalam kelompok, dan jumlah kualitas kelompok.
         Untuk memanfaatkannya: urutkan pekerja menurut rasio menaik, lalu
         proses satu per satu dengan menganggap pekerja sekarang sebagai
         PENENTU rasio. Anggota lain harus berasal dari yang sudah
         terlewat.
         Di antara mereka, mana yang kamu pilih? Rumusnya memberitahumu
         secara langsung. Struktur data apa yang menjaga pilihan itu tetap
         optimal saat kelompokmu bergeser?
         Waspadai presisi: bandingkan rasio dengan perkalian silang saat
         mengurutkan (Day 74), meski perhitungan akhirnya memakai
         bilangan real.

🎯 Learning Goals:
- [ ] Menurunkan rumus biaya sebelum memilih algoritma
- [ ] Menggabungkan pengurutan rasio dengan heap berukuran tetap
- [ ] Menyadari kapan heap harus max-heap, bukan min-heap
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: turunkan rumus biaya sebuah kelompok

    // TODO: urutkan menurut rasio; pelihara K kualitas terkecil

    return 0;
}
