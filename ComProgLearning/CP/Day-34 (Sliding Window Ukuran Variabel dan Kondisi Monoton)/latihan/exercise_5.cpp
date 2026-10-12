/*
============================================================
🏋️ Exercise 5: Hitung Subarray dengan Tepat K Jenis
============================================================
Day: 34 | Difficulty: Hard
Topic: Trik atMost(K) - atMost(K-1)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan sebuah bilangan K.
Hitung ADA BERAPA BANYAK subarray (potongan berurutan tidak kosong) yang
memuat TEPAT K nilai berbeda.
Sebagai contoh, pada array [1,2,1,2,3] dengan K = 2, subarray yang memenuhi
adalah [1,2], [2,1], [1,2], [1,2,1], [2,1,2], [1,2,1,2], dan [2,3] — total 7.
Perhatikan bahwa predikat "tepat K" TIDAK monoton, sehingga sliding window
tidak bisa langsung diterapkan. Kamu perlu satu langkah akal-akalan.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya subarray

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= K <= N
- 1 <= a[i] <= 10^9
- Jawaban bisa mencapai ~2 * 10^10

📎 SAMPLE INPUT 1:
5 2
1 2 1 2 3

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
4 1
1 1 1 1

📎 SAMPLE OUTPUT 2:
10

💡 HINT: "Paling banyak K" bersifat monoton, sedangkan "tepat K" tidak.
         Kalau kamu bisa menghitung "paling banyak K", maka "tepat K"
         adalah selisih dua hitungan.
         Untuk menghitung BANYAKNYA subarray (bukan yang terpanjang), setiap
         posisi r menyumbang sejumlah subarray sekaligus — berapa?

🎯 Learning Goals:
- [ ] Trik pengurangan untuk predikat "tepat"
- [ ] Rumus hasil += r - l + 1 dan alasannya
- [ ] Ingat long long untuk hitungan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: tulis fungsi atMost(a, K) yang menghitung BANYAK subarray
//       dengan paling banyak K nilai berbeda

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca input

    // TODO: jawabannya atMost(K) - atMost(K-1)

    return 0;
}
