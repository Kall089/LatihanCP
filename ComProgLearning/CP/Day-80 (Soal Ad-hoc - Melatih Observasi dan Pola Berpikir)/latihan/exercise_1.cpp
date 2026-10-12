/*
============================================================
🏋️ Exercise 1: Menyamakan dengan Biaya Terkecil
============================================================
Day: 80 | Difficulty: Easy
Topic: Median sebagai titik optimal
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tiang dengan tinggi a[i]. Kamu ingin membuat semua tiang sama tinggi.
Menaikkan atau menurunkan sebuah tiang sebanyak satu satuan berbiaya satu.
Kamu boleh memilih tinggi akhir berapa pun (bilangan bulat).
Cari TOTAL BIAYA MINIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total biaya minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5
1 2 9 2 6

📎 SAMPLE OUTPUT 1:
12

📎 SAMPLE INPUT 2:
1
7

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Naluri pertama adalah memakai RATA-RATA. Uji ide itu pada sampel 1
         sebelum mempercayainya — rata-ratanya 4, dan biayanya bukan 12.
         Untuk menemukan yang benar, pikirkan seperti ini: bayangkan tinggi
         target bergerak ke kanan sejauh satu satuan. Berapa banyak tiang
         yang biayanya bertambah, dan berapa yang berkurang?
         Dari situ kamu bisa menyimpulkan kapan menggeser target masih
         menguntungkan, dan kapan berhenti.
         Titik berhentinya punya nama, dan kamu sudah mengenalnya.
         Sebagai pemeriksaan: kalau N genap, apakah jawabannya unik? Coba
         hitung biaya untuk beberapa target di antara dua nilai tengah dan
         lihat apa yang terjadi.
         Perhatikan tipe data: 2*10^5 tiang dengan selisih sampai 10^9.

🎯 Learning Goals:
- [ ] Menurunkan titik optimal lewat argumen pergeseran
- [ ] Membedakan kapan median dan kapan rata-rata yang benar
- [ ] Menyadari bahwa jawaban optimal bisa tidak unik
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tentukan titik optimal lewat argumen pergeseran

    return 0;
}
