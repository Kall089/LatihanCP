/*
============================================================
🏋️ Exercise 6: Menutupi Setiap Titik K Kali
============================================================
Day: 73 | Difficulty: Hard (Contest-level)
Topic: Covering + heap + sapuan
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah pagar membentang dari posisi 0 sampai posisi M (M bilangan bulat).
Pagar terdiri atas M segmen satuan; segmen ke-j adalah bagian dari posisi
j sampai j+1, untuk j dari 0 sampai M-1.
Ada N tukang cat; tukang ke-i bersedia mengecat segmen-segmen pada rentang
[l[i], r[i]), artinya segmen l[i] sampai r[i]-1.
Setiap segmen harus dicat oleh SETIDAKNYA K tukang yang berbeda.
Setiap tukang boleh dipilih paling banyak sekali.
Cari JUMLAH TUKANG MINIMUM yang harus dipilih, atau -1 kalau tidak mungkin.

📥 INPUT FORMAT:
- Baris pertama: N, M, dan K
- N baris berikutnya: l[i] dan r[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah tukang minimum, atau -1

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= M <= 2 * 10^5
- 1 <= K <= 10
- 0 <= l[i] < r[i] <= M

📎 SAMPLE INPUT 1:
4 4 1
0 2
1 3
2 4
0 4

📎 SAMPLE OUTPUT 1:
1

📎 SAMPLE INPUT 2:
4 4 2
0 2
1 3
2 4
0 4

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
1 4 2
0 4

📎 SAMPLE OUTPUT 3:
-1

💡 HINT: Dengan K bernilai 1 soal ini adalah Exercise 3. Yang membuatnya
         jauh lebih sulit adalah setiap segmen harus tertutup K kali.
         Sapu posisi dari kiri ke kanan. Pada posisi j, hitung berapa banyak
         tukang terpilih yang masih aktif (yaitu r-nya masih di kanan j).
         Kalau jumlahnya kurang dari K, kamu harus menambah tukang.
         Tukang mana yang kamu tambahkan? Di antara tukang yang l-nya sudah
         terlewat (jadi mereka menutupi posisi j) dan belum dipilih, ambil
         yang r-nya PALING BESAR. Struktur data apa yang memberimu itu
         dengan cepat?
         Untuk melacak berapa tukang yang masih aktif tanpa memeriksa satu
         per satu, pikirkan cara mencatat "pada posisi ini, sekian tukang
         berakhir" — teknik dari Day 31 sangat cocok.
         Kalau pada suatu posisi tidak ada lagi tukang yang bisa ditambahkan
         padahal masih kurang, jawabannya -1.

🎯 Learning Goals:
- [ ] Memperluas covering dari sekali menjadi K kali
- [ ] Menggabungkan heap dengan sapuan posisi
- [ ] Melacak jumlah aktif secara efisien
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kelompokkan tukang menurut l

    // TODO: sapu posisi; jaga agar jumlah aktif tidak kurang dari K

    // TODO: heap untuk memilih r terbesar; catat kapan tiap tukang berakhir

    return 0;
}
