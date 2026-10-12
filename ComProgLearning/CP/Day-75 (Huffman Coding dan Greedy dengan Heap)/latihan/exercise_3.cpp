/*
============================================================
🏋️ Exercise 3: Membelah Papan
============================================================
Day: 75 | Difficulty: Medium
Topic: Huffman terbalik (dari akar ke daun)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah papan panjang harus dipotong menjadi N potongan dengan panjang
a[1], a[2], ..., a[N].
Setiap kali kamu memotong sebuah papan, biayanya sama dengan panjang papan
yang sedang dipotong (bukan panjang hasil potongannya).
Kamu boleh memotong dalam urutan apa pun, dan boleh memotong di posisi mana
pun.
Cari TOTAL BIAYA MINIMUM untuk mendapatkan seluruh N potongan.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total biaya minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
3
8 4 4

📎 SAMPLE OUTPUT 1:
24

📎 SAMPLE INPUT 2:
1
10

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Soal ini terasa berbeda dari Exercise 1 karena arahnya terbalik:
         di sana kamu MENGGABUNGKAN, di sini kamu MEMBELAH.
         Coba pikirkan mundur. Kalau kamu memutar rekaman proses pemotongan
         dari akhir ke awal, apa yang kamu lihat?
         Perhatikan juga biayanya. Ketika sebuah papan sepanjang L dibelah
         menjadi dua bagian x dan y, biayanya L, yaitu x + y. Bandingkan
         dengan biaya menggabungkan x dan y.
         Setelah kamu melihat kesamaannya, soal ini menjadi Exercise 1
         persis.
         Sampel 1: papan awal sepanjang 16. Coba hitung dengan tangan dua
         urutan pemotongan berbeda dan lihat mana yang lebih murah.

🎯 Learning Goals:
- [ ] Mengenali Huffman yang disajikan terbalik
- [ ] Melihat kesetaraan "belah" dan "gabung"
- [ ] Percaya pada pemetaan sebelum menulis kode baru
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: petakan ke soal yang sudah kamu selesaikan

    return 0;
}
