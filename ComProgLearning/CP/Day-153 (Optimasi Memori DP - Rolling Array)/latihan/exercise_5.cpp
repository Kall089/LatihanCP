/*
============================================================
🏋️ Exercise 5: Subsekuens Jumlah Target dengan Bitset (Subset Sum Bitset)
============================================================
Day: 153 | Difficulty: Medium | Topic: Bitset DP Optimization
Source: Classic Subset Sum / Bitwise Acceleration
Time Limit: 1.0 detik | Memory Limit: 32 MB

📋 PROBLEM STATEMENT:
Diberikan N buah bilangan bulat positif a[0], a[1], ..., a[N-1] dan sebuah target jumlah T.
Tentukan apakah terdapat sebuah SUBSET dari bilangan-bilangan tersebut yang jika dijumlahkan
menghasilkan nilai TEPAT sama dengan T.
Setiap bilangan dalam array a hanya boleh digunakan paling banyak satu kali.

Batasan: N hingga 1.000 dan target T hingga 100.000.
Pendekatan 2D standar akan memakan memori 1000 x 100001 byte ~ 100 MB (MLE pada batas 32 MB).
Bahkan DP 1D boolean biasa dengan loop mundur O(N * T) membutuhkan 10^8 iterasi,
yang berisiko Time Limit Exceeded pada batas 1.0 detik.
Kamu DIANJURKAN menggunakan `std::bitset` untuk mereduksi memori menjadi hanya ~12.5 KB
dan mempercepat transisi hingga 64 kali lipat!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan T.
- Baris kedua berisi N bilangan bulat positif a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Cetak string `BISA` jika ada subset yang berjumlah T, atau `TIDAK BISA` jika tidak ada.

📏 CONSTRAINTS:
- 1 <= N <= 1.000
- 1 <= T <= 100.000
- 1 <= a[i] <= 100.000
- Memori maksimal 32 MB

📎 SAMPLE INPUT 1:
4 12
3 4 5 9

📎 SAMPLE OUTPUT 1:
BISA

[Penjelasan Sample 1:
Subset {3, 4, 5} berjumlah 3 + 4 + 5 = 12.]

📎 SAMPLE INPUT 2:
4 9
2 3 7 8

📎 SAMPLE OUTPUT 2:
BISA

[Penjelasan Sample 2:
Subset {2, 7} berjumlah 2 + 7 = 9.]

📎 SAMPLE INPUT 3:
3 6
2 5 7

📎 SAMPLE OUTPUT 3:
TIDAK BISA

[Penjelasan Sample 3:
Kemungkinan jumlah subset: {0, 2, 5, 7, 7, 9, 12, 14}. Tidak ada yang bernilai 6.]

💡 HINT:
- Gunakan `std::bitset<100005> dp;`
- Inisialisasi: `dp[0] = 1;` (jumlah 0 selalu mungkin).
- Untuk setiap elemen `x`:
  - `dp |= (dp << x);`
  - Transisi ini menggeser seluruh bit kemungkinan sejauh `x` dan menggabungkannya secara bitwise OR.
  - Memproses 64 nilai kapasitas sekaligus per siklus CPU!
- Cek apakah `dp[T] == 1`.

🎯 Learning Goals:
- [ ] Menguasai optimasi `std::bitset` untuk DP Boolean / Reachability.
- [ ] Mengetahui perbedaan performa dan memori antara `vector<bool>` vs `bitset`.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_T = 100005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // TODO: Selesaikan Subset Sum dengan bitset<MAX_T>

    return 0;
}
