/*
============================================================
🏋️ Exercise 4: Apakah Pengurutan Ini Stabil?
============================================================
Day: 43 | Difficulty: Medium
Topic: Stabilitas
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N benda, benda ke-i punya BERAT w[i] dan NAMA berupa satu huruf.
Urutkan benda-benda itu berdasarkan berat secara MENAIK.
Benda dengan berat yang sama harus TETAP dalam urutan seperti pada input
(inilah yang disebut pengurutan stabil).
Cetak nama-nama benda setelah diurutkan, sebagai satu string tanpa spasi.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: masing-masing w[i] dan satu huruf nama

📤 OUTPUT FORMAT:
- Satu baris berisi N huruf

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= w[i] <= 10^9

📎 SAMPLE INPUT 1:
5
3 a
1 b
3 c
2 d
1 e

📎 SAMPLE OUTPUT 1:
bedac

📎 SAMPLE INPUT 2:
3
5 x
5 y
5 z

📎 SAMPLE OUTPUT 2:
xyz

💡 HINT: Dari tiga algoritma yang kamu pelajari hari ini, hanya dua yang
         menghasilkan jawaban benar untuk soal ini. Yang ketiga akan gagal
         pada sampel 1 — coba pikirkan yang mana dan kenapa.
         Kalau kamu ingin memakai sort bawaan, ada satu detail yang harus
         kamu perhatikan tentang jaminan yang diberikannya.

🎯 Learning Goals:
- [ ] Memahami arti stabilitas secara konkret
- [ ] Mengetahui algoritma mana yang stabil dan mana yang tidak
- [ ] Tahu bahwa std::sort TIDAK menjamin stabilitas
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca pasangan (berat, nama)

    // TODO: urutkan secara STABIL berdasarkan berat

    return 0;
}
