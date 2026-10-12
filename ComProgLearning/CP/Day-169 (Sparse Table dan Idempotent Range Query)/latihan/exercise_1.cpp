/*
============================================================
🏋️ Exercise 1: Minimum pada Rentang
============================================================
Day: 169 | Difficulty: Easy
Topic: Sparse table dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat yang TIDAK PERNAH BERUBAH, dan Q
pertanyaan. Setiap pertanyaan berisi sepasang indeks a dan b (1-based,
inklusif), dan kamu harus menjawab nilai TERKECIL di antara elemen pada
rentang tersebut.
Perhatikan bahwa Q sangat besar, sehingga menyapu rentang untuk setiap
pertanyaan akan menghasilkan 10^11 operasi dan pasti TLE.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: a dan b

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- 1 <= a <= b <= N
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
6 4
5 1 9 3 7 2
2 5
3 6
1 5
4 4

📎 SAMPLE OUTPUT 1:
1
2
1
3

💡 HINT: Prefix sum tidak berlaku di sini — tidak ada cara "mengurangkan"
         sebuah minimum dari minimum lainnya.
         Sebagai gantinya, hitung dulu jawaban untuk seluruh blok yang
         PANJANGNYA PANGKAT DUA. Blok panjang 2^k bisa dibangun dari dua
         blok panjang 2^(k-1) yang bersebelahan.
         Untuk menjawab sebuah rentang, pikirkan: berapa blok berukuran
         pangkat dua yang kamu butuhkan untuk menutupi rentang sepanjang
         len? Jawabannya mungkin mengejutkanmu — dan alasan kenapa itu
         cukup adalah sifat khusus dari operasi minimum.
         Peringatan: untuk menghitung pangkat dua terbesar yang tidak
         melebihi len, JANGAN memakai fungsi logaritma bawaan yang berbasis
         floating point. Ia bisa memberi hasil yang meleset satu.

🎯 Learning Goals:
- [ ] Membangun tabel blok pangkat dua
- [ ] Menemukan sendiri kenapa dua blok cukup
- [ ] Menghitung log2 dengan cara yang aman
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tabel lg, lalu tabel sp berukuran K x N

    // TODO: sp[0] = array asli, lalu bangun k = 1, 2, ...
    //       perhatikan BATAS loop i

    // TODO: query dengan dua blok; perhatikan indeks awal blok kanan

    return 0;
}
