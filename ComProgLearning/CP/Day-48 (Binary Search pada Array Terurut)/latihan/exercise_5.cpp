/*
============================================================
🏋️ Exercise 5: Floor and Ceiling in Sorted Array
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array A terurut dan nilai X.
- Floor: elemen terbesar di A yang <= X (cetak -1 jika tidak ada)
- Ceiling: elemen terkecil di A yang >= X (cetak -1 jika tidak ada)

📎 SAMPLE INPUT:
6 5
1 2 4 8 10 12

📎 SAMPLE OUTPUT:
4 8
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Cari floor dan ceiling
    long long fl = -1, cl = -1;

    cout << fl << " " << cl << "\n";

    return 0;
}
