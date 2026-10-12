/*
============================================================
  Exercise 4: Sliding Window Minimum
============================================================
Diberikan array A dan integer k. Untuk setiap window berukuran k,
cetak elemen minimum. Variasi dari Sliding Window Maximum.

📏 CONSTRAINTS:
  - 1 ≤ k ≤ n ≤ 10^5
  - -10^9 ≤ A[i] ≤ 10^9

📎 SAMPLE INPUT:
  8 3
  1 3 -1 -3 5 3 6 7

📎 SAMPLE OUTPUT:
  -1 -3 -3 -3 3 3

📎 SAMPLE INPUT 2:
  5 2
  4 3 1 2 5

📎 SAMPLE OUTPUT 2:
  3 1 1 2

💡 HINT:
  Sama seperti Sliding Window Maximum, tetapi deque menjaga nilai
  dalam urutan MENAIK (hapus dari belakang jika nilai >= a[i]).
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> dq; // menyimpan INDEX, monotonic increasing values

    for (int i = 0; i < n; i++) {
        // TODO: hapus index keluar window (front)
        // TODO: hapus dari belakang deque yang nilainya >= a[i]
        dq.push_back(i);

        if (i >= k-1) {
            cout << a[dq.front()];
            cout << " \n"[i == n-1];
        }
    }
    return 0;
}
