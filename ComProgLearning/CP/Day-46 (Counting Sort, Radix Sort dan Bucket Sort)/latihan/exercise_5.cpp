/*
============================================================
🏋️ Exercise 5: Selisih Terbesar Antar Tetangga
============================================================
Day: 46 | Difficulty: Hard
Topic: Bucket sort dengan prinsip pigeonhole
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat non-negatif. Bayangkan array itu
diurutkan menaik. Cari SELISIH TERBESAR antara dua elemen yang bersebelahan
pada array terurut tersebut.
Jika N kurang dari 2, jawabannya 0.
Tantangannya: selesaikan dalam waktu O(N) dan ruang O(N), TANPA benar-benar
mengurutkan array (jadi tidak boleh memakai sort maupun radix sort).

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: selisih terbesar antar tetangga

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 0 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
3 6 9 1

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
2
1 1000000000

📎 SAMPLE OUTPUT 2:
999999999

📎 SAMPLE INPUT 3:
1
5

📎 SAMPLE OUTPUT 3:
0

💡 HINT: Misalkan nilai terkecil adalah mn dan terbesar adalah mx.
         Kalau kamu membagi rentang [mn, mx] menjadi N-1 ember yang sama
         lebar, maka lebar tiap ember adalah (mx - mn) / (N - 1).
         Sekarang pikirkan: ada N bilangan yang harus masuk ke N-1 ember.
         Apa yang bisa kamu simpulkan tentang jawaban akhirnya dibandingkan
         dengan lebar ember?
         Kalau kesimpulan itu benar, kamu hanya perlu menyimpan nilai
         MINIMUM dan MAKSIMUM di tiap ember — isi ember selengkapnya tidak
         diperlukan sama sekali.

🎯 Learning Goals:
- [ ] Memakai prinsip pigeonhole untuk membuang kemungkinan
- [ ] Menyadari bahwa kadang kamu hanya butuh ringkasan tiap ember
- [ ] Menyelesaikan masalah "terurut" tanpa mengurutkan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: cari mn dan mx, tangani kasus khusus

    // TODO: N-1 ember, simpan hanya min dan max tiap ember

    // TODO: jawaban = selisih terbesar antara max ember sebelumnya dan
    //       min ember berikutnya (lewati ember kosong)

    return 0;
}
