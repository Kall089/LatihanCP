/*
============================================================
🏋️ Exercise 3: Mengubah Barisan Menjadi Terurut Tidak Menaik (Suffix Minimum)
============================================================
Day: 272 | Difficulty: Medium | Topic: Slope Trick (Min-Heap / Suffix Minimum)
Source: Dual Sequence Alignment Problem
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah barisan bilangan bulat A = [a_0, a_1, ..., a_{N-1}].
Kamu ingin membuat barisan baru B = [b_0, b_1, ..., b_{N-1}] sedemikian sehingga:
1. B terurut TIDAK MENAIK (non-increasing): b_0 >= b_1 >= b_2 >= ... >= b_{N-1}.
2. Seluruh elemen b_i adalah bilangan bulat.
3. Total biaya perubahan, yaitu sum_{i=0}^{N-1} |a_i - b_i|, bernilai sekecil mungkin.

Selesaikan masalah ini dengan SLOPE TRICK menggunakan Min-Heap (atau negasi) dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a_0, a_1, ..., a_{N-1}.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum perubahan.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- -1.000.000.000 <= a_i <= 1.000.000.000

📎 SAMPLE INPUT 1:
5
1 2 3 4 5

📎 SAMPLE OUTPUT 1:
6

[Penjelasan Sample 1:
Barisan B optimal adalah [3, 3, 3, 3, 3] (semua sama dengan median).
Total biaya = |1 - 3| + |2 - 3| + |3 - 3| + |4 - 3| + |5 - 3| = 2 + 1 + 0 + 1 + 2 = 6.]

📎 SAMPLE INPUT 2:
5
5 4 3 2 1

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
Barisan awal sudah terurut tidak menaik, tidak memerlukan perubahan (biaya 0).]

💡 HINT:
- Rekurensi untuk barisan tidak menaik (b_i <= b_{i-1}):
  dp[i](x) = |x - a_i| + min_{y >= x} dp[i-1](y).
- Operasi min_{y >= x} adalah sufiks minimum, yang memotong semua lereng menurun (slope < 0) menjadi datar (slope = 0).
- Dengan demikian, kita hanya perlu memelihara lereng menaik (slope > 0) menggunakan sebuah Min-Heap `R`!
- Untuk setiap a_i:
  - Jika !R.empty() dan a_i > R.top():
    tambah jawaban sebesar (a_i - R.top())
    R.pop()
    R.push(a_i)
    R.push(a_i)
  - Selain itu:
    R.push(a_i)
- Alternatif: Kalikan seluruh elemen dengan -1 dan gunakan algoritma non-decreasing dari Exercise 1.

🎯 Learning Goals:
- [ ] Memahami dualitas Slope Trick antara Max-Heap (prefiks min) dan Min-Heap (sufiks min).
- [ ] Menyelesaikan masalah barisan non-increasing dalam O(N log N).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Slope Trick (Min-Heap) O(N log N)

    return 0;
}
