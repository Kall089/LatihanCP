/*
============================================================
🏋️ Exercise 3: Substring Seimbang Terpanjang
============================================================
Day: 41 | Difficulty: Medium
Topic: transformasi + prefix sum (Day 29) + hash map (Day 40) + string (Day 39)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string S yang hanya terdiri dari huruf 'a' dan 'b'.
Sebuah substring disebut SEIMBANG kalau banyaknya 'a' di dalamnya sama persis
dengan banyaknya 'b'. Cari panjang substring seimbang yang paling panjang.
Kalau tidak ada substring seimbang sama sekali, cetak 0.

Soal ini kelihatan seperti soal string, padahal bukan. Ada satu transformasi
yang mengubahnya menjadi soal array yang sudah kamu kenal. Pikirkan: apa yang
terjadi kalau 'a' kamu anggap +1 dan 'b' kamu anggap -1?

📥 INPUT FORMAT:
- Baris pertama: N (panjang string)
- Baris kedua: string S

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2·10^5
- S hanya berisi 'a' dan 'b'

📎 SAMPLE INPUT 1:
6
aabbba

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
5
aaaaa

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
8
abbabaab

📎 SAMPLE OUTPUT 3:
8

📎 SAMPLE INPUT 4:
4
baab

📎 SAMPLE OUTPUT 4:
4

💡 HINT: Setelah transformasi, "seimbang" berarti jumlahnya nol. Dan
         "substring dengan jumlah nol" berarti dua prefix yang NILAINYA SAMA.
         Simpan kemunculan PERTAMA tiap nilai prefix.

🎯 Learning Goals:
- [ ] Mengubah soal string jadi soal prefix sum
- [ ] Memahami kenapa yang disimpan kemunculan PERTAMA, bukan terakhir
- [ ] Menangani prefix kosong (nilai 0 pada indeks 0)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan string S

    // TODO: Ubah 'a' -> +1 dan 'b' -> -1, hitung prefix berjalan

    // TODO: Simpan di map: nilai prefix -> indeks PERTAMA kali muncul
    // Hint: jangan lupa memasukkan (0, 0) lebih dulu, mewakili prefix kosong
    //       Kalau nilai prefix sudah pernah ada, JANGAN ditimpa -
    //       kita mau jarak terjauh, jadi butuh kemunculan paling awal

    // TODO: Untuk tiap i, kalau prefix[i] sudah pernah muncul di posisi j,
    //       maka substring (j..i-1) seimbang, panjangnya i - j

    return 0;
}
