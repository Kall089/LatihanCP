/*
============================================================
🏋️ Exercise 4: Enam Klaim
============================================================
Day: 79 | Difficulty: Medium
Topic: Memutuskan benar atau salah dengan cepat
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah nomor klaim K dan sebuah masukan yang sesuai dengan klaim
itu. Klaim-klaimnya adalah:

  1. Untuk memilih sebanyak mungkin interval saling lepas [l, r) dari N
     interval: ambil terus interval dengan r terkecil yang masih muat.
  2. Untuk memilih sebanyak mungkin interval saling lepas: ambil terus
     interval TERPENDEK yang masih muat.
  3. Untuk meminimalkan jumlah waktu selesai N tugas pada satu mesin:
     kerjakan yang durasinya terpendek dulu.
  4. Untuk memaksimalkan nilai pada knapsack 0/1: ambil terus barang dengan
     rasio nilai per berat tertinggi yang masih muat.
  5. Untuk meminimalkan jumlah tumpukan yang digabung (biaya penggabungan
     sama dengan jumlah kedua tumpukan): urutkan sekali, lalu gabungkan
     berurutan dari kiri.
  6. Untuk meminimalkan keterlambatan terbesar N pekerjaan pada satu mesin:
     kerjakan yang tenggatnya paling awal dulu.

Untuk klaim nomor K dan masukan yang diberikan, cetak "BENAR" kalau strategi
itu menghasilkan jawaban optimal untuk masukan tersebut, atau dua bilangan:
hasil strategi tersebut dan hasil optimal.

📥 INPUT FORMAT:
- Baris pertama: K dan N
- N baris berikutnya: data sesuai klaim
  K = 1 atau 2 : l dan r
  K = 3        : t
  K = 4        : w dan v (baris pertama tambahan berisi W)
  K = 5        : a
  K = 6        : t dan d

📤 OUTPUT FORMAT:
- "BENAR", atau dua bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 <= K <= 6
- 1 <= N <= 8
- Seluruh nilai antara 1 dan 20; W antara 1 dan 30

📎 SAMPLE INPUT 1:
2 3
1 10
9 12
11 20

📎 SAMPLE OUTPUT 1:
1 2

📎 SAMPLE INPUT 2:
6 3
3 6
2 8
1 9

📎 SAMPLE OUTPUT 2:
BENAR

💡 HINT: Batasan N paling besar 8 adalah petunjuk yang sangat jelas: untuk
         SETIAP klaim, jawaban optimalnya boleh kamu hitung dengan mencoba
         seluruh kemungkinan.
         Untuk klaim yang tentang MEMILIH sebagian (nomor 1, 2, 4), coba
         seluruh himpunan bagian. Untuk klaim yang tentang MENYUSUN URUTAN
         (nomor 3, 6), coba seluruh permutasi. Untuk klaim nomor 5, coba
         seluruh cara menggabungkan.
         Menulis enam brute force terasa membosankan, dan itu memang
         intinya. Brute force yang membosankan dan jelas benar lebih
         berharga daripada satu solusi pintar yang mungkin salah.
         Tiga dari enam klaim itu SALAH. Sebelum menulis kode, tebak yang
         mana. Lalu bandingkan tebakanmu dengan hasil programmu — selisih
         antara tebakan dan kenyataan adalah ukuran seberapa jauh
         intuisimu masih bisa diperbaiki.
         Setelah selesai, untuk setiap klaim yang salah, jalankan pencarian
         acak untuk menemukan contoh tandingan TERKECIL, lalu hafalkan.

🎯 Learning Goals:
- [ ] Memilih bentuk brute force yang sesuai jenis soal
- [ ] Menguji intuisi sendiri terhadap kenyataan
- [ ] Membangun koleksi contoh tandingan pribadi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: enam brute force, masing-masing jelas benar

    // TODO: enam simulasi strategi, apa adanya

    return 0;
}
