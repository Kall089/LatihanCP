/*
============================================================
🏋️ Exercise 4: Semua Jumlah yang Bisa Dibentuk
============================================================
Day: 145 | Difficulty: Medium
Topic: Subset sum
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu punya N keping koin dengan nilai masing-masing. Setiap koin hanya bisa
dipakai sekali.
Cari SELURUH jumlah uang berbeda yang bisa kamu bentuk dengan memilih
sebagian koin (subhimpunan tidak kosong).
Cetak berapa banyak jumlah berbeda yang mungkin, lalu daftar jumlah-jumlah
itu dalam urutan menaik.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N nilai koin

📤 OUTPUT FORMAT:
- Baris pertama: banyaknya jumlah berbeda
- Baris kedua: jumlah-jumlah itu terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= nilai koin <= 1000

📎 SAMPLE INPUT 1:
4
4 2 5 2

📎 SAMPLE OUTPUT 1:
9
2 4 5 6 7 8 9 11 13

📎 SAMPLE INPUT 2:
1
7

📎 SAMPLE OUTPUT 2:
1
7

💡 HINT: Ini knapsack 0/1 di mana "nilai" sebuah barang sama dengan
         "beratnya". Kamu tidak memaksimalkan apa pun — kamu hanya
         menandai jumlah mana saja yang BISA dicapai.
         Berapa jumlah maksimum yang mungkin? Itu menentukan ukuran array
         yang kamu butuhkan.
         Satu hal yang sering terlupa: sebelum memproses koin mana pun,
         jumlah berapa yang sudah pasti bisa dicapai? Menandainya adalah
         basis dari seluruh perhitungan.
         Perhatikan bahwa soal meminta subhimpunan TIDAK KOSONG.
         Bonus: kalau kamu memakai struktur bit alih-alih array boolean,
         seluruh perhitungan bisa dipercepat sekitar 64 kali dan kodenya
         justru menjadi lebih pendek. Coba cari tahu caranya.

🎯 Learning Goals:
- [ ] Mengenali subset sum sebagai knapsack dengan nilai = berat
- [ ] Menginisialisasi basis dengan benar
- [ ] Mengetahui trik bitset untuk subset sum
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tentukan batas atas jumlah

    // TODO: tandai basis, lalu proses tiap koin (perhatikan arah loop)

    // TODO: kumpulkan jumlah yang tercapai, kecuali nol

    return 0;
}
