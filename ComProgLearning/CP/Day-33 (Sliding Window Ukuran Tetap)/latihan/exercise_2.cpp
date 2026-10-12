/*
 * Day 20 — Sliding Window
 * File  : exercise_2.cpp
 * Topik : First Negative Number in Every Window of Size K
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat (bisa positif/negatif/nol).
 * Untuk setiap window kontinu berukuran K, cetak elemen NEGATIF PERTAMA
 * (dari kiri) yang ada di window tersebut. Jika tidak ada elemen negatif
 * di window, cetak 0.
 *
 * Total output: (N - K + 1) bilangan, dipisah spasi.
 *
 * Pendekatan SLIDING WINDOW dengan DEQUE menyimpan index elemen negatif:
 *   - Saat slide, push_back index baru jika A[i] < 0
 *   - Pop_front index yang sudah keluar window
 *   - Jika deque kosong → output 0, else output A[dq.front()]
 *
 * Input format  : Baris 1: N dan K (1 ≤ K ≤ N ≤ 200.000)
 *                 Baris 2: N bilangan bulat
 * Output format : (N-K+1) bilangan dipisah spasi (negatif pertama atau 0)
 * Constraints   : 1 ≤ K ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 8 3                    -1 -1 -7 -15 -15 0
 * 12 -1 -7 8 -15 30 16 28
 *
 * Sample Input 2:        Sample Output 2:
 * 5 2                    0 0 0 0
 * 1 2 3 4 5
 *
 * Sample Input 3:        Sample Output 3:
 * 4 2                    -8 -5 -5
 * -8 2 3 -5
 *
 * NOTE Sample 1:
 *   Window [12,-1,-7]   → first neg = -1
 *   Window [-1,-7,8]    → first neg = -1
 *   Window [-7,8,-15]   → first neg = -7
 *   Window [8,-15,30]   → first neg = -15
 *   Window [-15,30,16]  → first neg = -15
 *   Window [30,16,28]   → no neg → 0
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for (auto &x : A)
        cin >> x;

    // TODO: Implementasi dengan deque<int> menyimpan INDEX elemen negatif
    // Hint:
    // deque<int> dq;
    // for (int i = 0; i < n; i++) {
    //     // Buang index yang sudah keluar window
    //     while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    //     // Tambah index sekarang jika A[i] negatif
    //     if (A[i] < 0) dq.push_back(i);
    //     // Output ketika window penuh
    //     if (i >= k - 1) {
    //         if (dq.empty()) cout << 0;
    //         else cout << A[dq.front()];
    //         cout << (i == n - 1 ? '\n' : ' ');
    //     }
    // }

    return 0;
}
