/*
============================================================
🏋️ Exercise 3: Mencampur Bahan Bakar
============================================================
Day: 74 | Difficulty: Medium
Topic: Fractional dengan tujuan berbeda (minimalkan biaya)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu membutuhkan tepat L liter bahan bakar. Tersedia N pemasok; pemasok
ke-i sanggup menyediakan paling banyak a[i] liter dengan harga c[i] per
liter.
Kamu boleh membeli sebagian dari kuota mana pun.
Cari BIAYA TOTAL MINIMUM untuk mendapatkan tepat L liter, atau -1 kalau
seluruh pasokan yang tersedia tidak mencukupi.
Cetak biaya dengan enam angka di belakang koma.

📥 INPUT FORMAT:
- Baris pertama: N dan L
- N baris berikutnya: a[i] dan c[i]

📤 OUTPUT FORMAT:
- Satu bilangan real dengan enam angka di belakang koma, atau -1

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= L <= 10^9
- 1 <= a[i] <= 10^9
- 1 <= c[i] <= 10^9

📎 SAMPLE INPUT 1:
3 10
5 3
4 2
6 5

📎 SAMPLE OUTPUT 1:
28.000000

📎 SAMPLE INPUT 2:
2 100
5 1
5 1

📎 SAMPLE OUTPUT 2:
-1

💡 HINT: Perhatikan bahwa kali ini kamu MEMINIMALKAN, bukan memaksimalkan.
         Apakah itu mengubah arah pengurutanmu?
         Perhatikan juga bahwa harga sudah dinyatakan PER LITER. Bandingkan
         dengan Exercise 1, di mana kamu harus menghitung sendiri nilai per
         kilogram. Mana yang lebih sederhana, dan kenapa?
         Sampel 2 mengingatkanmu bahwa permintaan bisa tidak terpenuhi.
         Periksa total pasokan sebelum atau selama proses.
         Waspadai overflow: a sampai 10^9 dan c sampai 10^9, sehingga biaya
         satu pemasok saja bisa mencapai 10^18.

🎯 Learning Goals:
- [ ] Menyesuaikan arah greedy untuk tujuan minimasi
- [ ] Menyadari kapan rasio sudah diberikan langsung oleh soal
- [ ] Menangani kasus permintaan tak terpenuhi dan overflow
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tentukan arah pengurutan untuk tujuan minimasi

    // TODO: ambil serakah, potong yang terakhir

    // TODO: deteksi pasokan tidak mencukupi

    return 0;
}
