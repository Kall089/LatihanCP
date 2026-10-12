/*
============================================================
🏋️ Exercise 2: Membuktikan Greedy Gagal
============================================================
Day: 74 | Difficulty: Easy
Topic: Membandingkan greedy rasio dengan DP 0/1
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N barang dengan berat w[i] dan nilai v[i], serta kapasitas W.
Kali ini barang TIDAK boleh dipotong: setiap barang diambil utuh atau tidak
sama sekali.
Seorang teman mengusulkan strategi: "urutkan menurut nilai per berat dari
yang tertinggi, lalu ambil terus selama masih muat".
Tentukan apakah strategi itu memberikan hasil optimal.
Cetak "OPTIMAL" kalau iya, atau dua bilangan: hasil strategi teman dan hasil
optimal yang sesungguhnya.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- "OPTIMAL", atau dua bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= W <= 10^4
- 1 <= w[i] <= 10^4
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
3 10
6 7
5 5
5 5

📎 SAMPLE OUTPUT 1:
7 10

📎 SAMPLE INPUT 2:
3 10
5 10
3 6
2 4

📎 SAMPLE OUTPUT 2:
OPTIMAL

💡 HINT: Bagian pertama mudah: simulasikan saja strategi temanmu.
         Bagian kedua membutuhkan jawaban yang benar-benar optimal. Batasan
         W paling besar 10^4 memberi tahu kamu pendekatan mana yang
         dimaksud — kamu sudah mempelajarinya di Day 145.
         Perhatikan arah loop kapasitas pada DP. Kalau arahnya terbalik,
         kamu justru menghitung soal yang berbeda (barang boleh diambil
         berkali-kali).
         Setelah kodemu jalan, lakukan ini: buat generator masukan acak
         dengan n kecil, jalankan ribuan kali, dan hitung berapa persen
         kasus yang TIDAK optimal. Angkanya sekitar dua belas persen —
         cukup jarang untuk lolos beberapa sampel, cukup sering untuk
         membuatmu WA di kontes.

🎯 Learning Goals:
- [ ] Menyadari bahwa greedy rasio gagal pada 0/1
- [ ] Mengingat kembali arah loop DP knapsack
- [ ] Mengukur tingkat kegagalan greedy secara empiris
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: simulasikan strategi greedy rasio

    // TODO: hitung jawaban optimal dengan DP; perhatikan arah loopnya

    return 0;
}
