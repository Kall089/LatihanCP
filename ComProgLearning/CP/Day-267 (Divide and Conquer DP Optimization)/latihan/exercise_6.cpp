/*
============================================================
🏋️ Exercise 6: Gondola dan Indeks Ketidaksukaan (Ciel and Gondolas D&C DP)
============================================================
Day: 267 | Difficulty: Menantang | Topic: Divide & Conquer DP with 2D Prefix Sums
Source: Codeforces 321E (Ciel and Gondolas)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N orang pengunjung karnaval yang sedang mengantre berurutan untuk menaiki K buah gondola bianglala.
Setiap gondola harus diisi oleh satu segmen pengunjung berurutan tak kosong.
Antara pengunjung ke-i dan pengunjung ke-j terdapat nilai ketidaksukaan sebesar u[i][j] (di mana u[i][j] = u[j][i] dan u[i][i] = 0).
Biaya ketidaknyamanan satu gondola yang memuat pengunjung dari indeks l sampai r adalah
JUMLAH NILAI KETIDAKSUKAAN dari seluruh pasangan orang di dalam gondola tersebut:
`Cost(l, r) = sum_{l <= i < j <= r} u[i][j]`.

Tentukan TOTAL BIAYA KETIDAKNYAMANAN MINIMUM untuk membagi seluruh N pengunjung ke dalam tepat K gondola!

Selesaikan dengan algoritma DIVIDE & CONQUER DP OPTIMIZATION dipadukan dengan 2D Prefix Sum!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- N baris berikutnya masing-masing berisi N bilangan bulat (matriks ketidaksukaan u[i][j]).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya ketidaknyamanan minimum.

📏 CONSTRAINTS:
- 1 <= N <= 4.000
- 1 <= K <= min(N, 800)
- 0 <= u[i][j] <= 9
- u[i][j] = u[j][i], u[i][i] = 0

📎 SAMPLE INPUT 1:
5 2
0 0 1 1 1
0 0 1 1 1
1 1 0 0 0
1 1 0 0 0
1 1 0 0 0

📎 SAMPLE OUTPUT 1:
0

[Penjelasan Sample 1:
Bagi menjadi 2 kelompok: [1, 2] dan [3, 4, 5].
Di dalam kelompok [1, 2], ketidaksukaan = 0.
Di dalam kelompok [3, 4, 5], ketidaksukaan antar sesama mereka = 0.
Total ketidaksukaan = 0.]

📎 SAMPLE INPUT 2:
8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0

📎 SAMPLE OUTPUT 2:
7

💡 HINT:
- Bangun matriks 2D Prefix Sum `pref[i][j] = sum_{r=1}^i sum_{c=1}^j u[r][c]`.
- Jumlah ketidaksukaan semua pasangan di dalam interval `[l..r]` adalah:
  `submatrix_sum(l, l, r, r) / 2`.
  Nilai ini dapat dihitung dalam O(1)!
- Karena nilai elemen matriks non-negatif, fungsi biaya submatriks memenuhi Quadrangle Inequality.
- Gunakan D&C DP Optimization pada setiap layer `g = 1..K`.

🎯 Learning Goals:
- [ ] Menghitung biaya interaksi pasangan menggunakan 2D Prefix Sum dalam O(1).
- [ ] Mengoptimasi problem klasik Ciel and Gondolas hingga skala N = 4000, K = 800.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan 2D Prefix Sum + D&C DP

    return 0;
}
