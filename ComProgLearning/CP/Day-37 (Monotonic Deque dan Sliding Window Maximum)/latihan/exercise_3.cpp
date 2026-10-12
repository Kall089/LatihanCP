/*
============================================================
  Exercise 3: Sliding Window Maximum
============================================================
Diberikan array A dan integer k. Untuk setiap window berukuran k,
cetak elemen maksimum. Gunakan deque untuk O(n) solution.

📏 CONSTRAINTS:
  - 1 ≤ k ≤ n ≤ 10^5
  - -10^9 ≤ A[i] ≤ 10^9

📎 SAMPLE INPUT:
  8 3
  1 3 -1 -3 5 3 6 7

📎 SAMPLE OUTPUT:
  3 3 5 5 6 7

📎 SAMPLE INPUT 2:
  5 2
  4 3 1 2 5

📎 SAMPLE OUTPUT 2:
  4 3 2 5

💡 HINT:
  Deque menyimpan INDEX dalam urutan menurun nilai.
  Saat window bergerak:
  1. Hapus index yang sudah keluar window (dq.front() <= i-k)
  2. Hapus dari belakang semua index dengan nilai <= A[i]
  3. Push i ke belakang deque
  4. dq.front() adalah index maximum window saat ini
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> dq; // menyimpan INDEX, monotonic decreasing values

    for (int i = 0; i < n; i++) {
        // TODO: hapus index yang sudah keluar window
        // TODO: hapus dari belakang deque semua yang nilainya <= a[i]
        dq.push_back(i);

        if (i >= k-1) {
            cout << a[dq.front()];
            cout << " \n"[i == n-1];
        }
    }
    return 0;
}
