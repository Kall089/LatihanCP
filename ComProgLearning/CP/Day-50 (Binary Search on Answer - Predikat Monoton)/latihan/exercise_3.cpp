/*
============================================================
🏋️ Exercise 3: Potong Kayu (SPOJ EKO)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pohon dengan tinggi H[1..N]. Gergaji diset pada ketinggian H.
Setiap pohon yang tingginya > H akan dipotong bagian atasnya (mendapatkan H[i] - H kayu).
Maksimalkan ketinggian gergaji H sedemikian hingga total kayu yang diperoleh minimal M meter.

📎 SAMPLE INPUT:
4 7
20 15 10 17

📎 SAMPLE OUTPUT:
15
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // TODO: Implementasi binary search ketinggian gergaji H
    long long ans = 0;

    cout << ans << "\n";

    return 0;
}
