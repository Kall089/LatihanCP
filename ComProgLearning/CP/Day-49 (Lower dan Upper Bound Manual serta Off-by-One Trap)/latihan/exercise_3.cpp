/*
============================================================
🏋️ Exercise 3: Nilai Terdekat
============================================================
Day: 49 | Difficulty: Medium
Topic: Kasus tepi pada bound
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan Q pertanyaan. Untuk setiap
pertanyaan berisi bilangan x, cetak elemen array yang nilainya PALING DEKAT
dengan x (yaitu yang selisih absolutnya paling kecil).
Jika ada dua elemen yang sama dekatnya, cetak yang nilainya LEBIH KECIL.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: masing-masing satu bilangan x

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= nilai, x <= 10^9

📎 SAMPLE INPUT 1:
5 4
10 2 7 4 1
5
0
100
6

📎 SAMPLE OUTPUT 1:
4
1
10
7

💡 HINT: Kandidat jawabannya hanya ada dua: elemen pertama yang >= x, dan
         elemen tepat sebelumnya. Bandingkan keduanya.
         Tetapi ada dua situasi di mana salah satu kandidat itu TIDAK ADA.
         Periksa keduanya SEBELUM mengakses array — mengakses indeks n atau
         indeks -1 adalah penyebab runtime error paling sering di topik ini.
         Perhatikan sampel: dua pertanyaan pertama menguji tepat dua situasi
         tersebut.

🎯 Learning Goals:
- [ ] Menangani kedua kasus tepi secara eksplisit
- [ ] Menerjemahkan aturan seri menjadi arah perbandingan yang benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan

    // TODO: untuk tiap x, cari batas lalu periksa DUA kasus tepi

    // TODO: bandingkan dua kandidat, perhatikan aturan seri

    return 0;
}
