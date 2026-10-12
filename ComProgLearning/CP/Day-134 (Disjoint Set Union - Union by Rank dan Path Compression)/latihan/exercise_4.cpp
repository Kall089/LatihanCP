/*
============================================================
🏋️ Exercise 4: Membangun Jalan
============================================================
Day: 134 | Difficulty: Medium
Topic: DSU + laporan bertahap
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah negara punya N kota yang mula-mula tidak terhubung sama sekali.
Selama M hari, setiap hari dibangun satu jalan yang menghubungkan dua kota.
Setelah pembangunan jalan pada SETIAP hari, laporkan dua hal:
- berapa banyak komponen kota yang masih terpisah, dan
- berapa banyak kota di dalam komponen TERBESAR saat itu.
Jalan boleh saja menghubungkan dua kota yang sudah terhubung sebelumnya.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- M baris berikutnya: masing-masing dua kota yang dihubungkan

📤 OUTPUT FORMAT:
- M baris, masing-masing dua bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= M <= 2 * 10^5

📎 SAMPLE INPUT 1:
5 4
1 2
1 3
4 5
1 5

📎 SAMPLE OUTPUT 1:
4 2
3 3
2 3
1 5

💡 HINT: Kedua informasi yang diminta bisa dijaga secara INKREMENTAL —
         kamu tidak perlu menyapu seluruh kota setiap hari.
         Banyaknya komponen berkurang tepat satu setiap kali dua komponen
         yang berbeda benar-benar bergabung.
         Untuk ukuran terbesar, perhatikan bahwa ia hanya bisa BERTAMBAH,
         tidak pernah berkurang. Jadi kamu cukup membandingkannya dengan
         ukuran komponen hasil penggabungan yang baru saja terjadi.
         Pikirkan: kapan tepatnya kamu harus membaca ukuran gabungan itu,
         sebelum atau sesudah penggabungan?

🎯 Learning Goals:
- [ ] Menjaga statistik global secara inkremental
- [ ] Menyadari bahwa ukuran maksimum bersifat monoton naik
- [ ] Menghindari penyapuan ulang O(N) per operasi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: jaga `komponen` dan `terbesar` secara inkremental

    // TODO: perbarui `terbesar` setelah setiap penggabungan yang berhasil

    return 0;
}
