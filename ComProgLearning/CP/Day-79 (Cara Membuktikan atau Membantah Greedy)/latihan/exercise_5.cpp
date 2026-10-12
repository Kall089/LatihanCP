/*
============================================================
🏋️ Exercise 5: Menebak Kriteria dari Data
============================================================
Day: 79 | Difficulty: Hard
Topic: Memakai brute force untuk MENEMUKAN kriteria
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan. Pekerjaan ke-i punya dua bilangan a[i] dan b[i].
Sebuah jadwal adalah urutan pengerjaan seluruh pekerjaan. Kalau pekerjaan
dikerjakan dalam urutan p[1], p[2], ..., p[N], biaya jadwal itu
didefinisikan sebagai nilai TERBESAR di antara

    (a[p1] + a[p2] + ... + a[pk]) + b[pk]

untuk seluruh k dari 1 sampai N.
Cari BIAYA MINIMUM di antara seluruh urutan yang mungkin.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: a[i] dan b[i]

📤 OUTPUT FORMAT:
- Satu bilangan: biaya minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i], b[i] <= 10^9

📎 SAMPLE INPUT 1:
3
1 3
2 1
3 2

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
1
5 5

📎 SAMPLE OUTPUT 2:
10

💡 HINT: Batasan N sampai 2*10^5 berarti kamu butuh sesuatu seperti
         pengurutan. Tetapi urut menurut apa?
         Jangan menebak. Lakukan ini sebagai gantinya:
         (1) tulis brute force atas seluruh permutasi untuk N <= 7;
         (2) buat daftar kriteria pengurutan yang masuk akal — misalnya a
             menaik, a menurun, b menaik, b menurun, a+b menaik, a+b
             menurun, a-b, b-a;
         (3) jalankan SEMUANYA terhadap brute force pada ribuan masukan
             acak dan catat mana yang tidak pernah gagal.
         Pendekatan ini disebut "menemukan kriteria secara empiris", dan ia
         jauh lebih cepat daripada menatap soal berharap mendapat ilham.
         Setelah menemukan satu yang bertahan, BARU buktikan dengan
         exchange argument: ambil dua pekerjaan berdampingan, tuliskan
         biaya untuk kedua urutan, kurangkan, sederhanakan.
         Petunjuk untuk buktinya: bagian yang memuat jumlah a sebelum
         kedua pekerjaan itu, dan bagian yang memuat jumlah a keduanya,
         akan saling hilang.
         Kamu mungkin terkejut menemukan bahwa salah satu dari a atau b
         sama sekali tidak muncul dalam kriteria akhirnya.

🎯 Learning Goals:
- [ ] Memakai brute force sebagai alat PENEMU, bukan sekadar pemverifikasi
- [ ] Menguji banyak kriteria sekaligus secara sistematis
- [ ] Membuktikan setelah menemukan, bukan sebelumnya
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: temukan kriterianya secara empiris lebih dulu

    // TODO: lalu buktikan, lalu implementasikan versi cepatnya

    return 0;
}
