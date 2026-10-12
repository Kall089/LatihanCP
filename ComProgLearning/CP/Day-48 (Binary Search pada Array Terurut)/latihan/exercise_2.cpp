/*
============================================================
🏋️ Exercise 2: Lower Bound & Upper Bound Manual
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array A berukuran N terurut ascending dan target X.
Cetak dua buah nilai:
1. Indeks elemen pertama yang nilainya >= X (Lower Bound)
2. Indeks elemen pertama yang nilainya > X (Upper Bound)
Jika tidak ada, cetak N.

📥 INPUT FORMAT:
- Baris 1: N X
- Baris 2: N buah integer terurut

📤 OUTPUT FORMAT:
- Dua integer dipisahkan spasi: lower_bound_index upper_bound_index

📎 SAMPLE INPUT:
6 4
1 2 4 4 4 7

📎 SAMPLE OUTPUT:
2 5
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

    // TODO: Hitung lower bound dan upper bound manual
    int lb = n, ub = n;

    cout << lb << " " << ub << "\n";

    return 0;
}
