/*
============================================================
🏋️ Exercise 1: Factory Machines (CSES Factory Machines)
============================================================
Day: 50 | Difficulty: Easy
Topic: Binary Search on Answer
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N mesin pabrik. Mesin ke-i butuh K[i] detik untuk membuat 1 produk.
Semua mesin bekerja secara paralel. Cari waktu MINIMUM yang dibutuhkan untuk membuat T produk.

📥 INPUT FORMAT:
- Baris 1: N T (1 <= N <= 2*10^5, 1 <= T <= 10^9)
- Baris 2: N integer K[1], K[2], ..., K[N] (1 <= K[i] <= 10^9)

📤 OUTPUT FORMAT:
- Satu integer: waktu minimum dalam detik.

📎 SAMPLE INPUT:
3 7
3 2 5

📎 SAMPLE OUTPUT:
8

💡 HINT: check(time) menghitung sum(time / K[i]). Jika sum >= T, maka time cukup.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long t;
    if (!(cin >> n >> t)) return 0;

    vector<long long> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];

    // TODO: Binary search pada waktu jawaban
    long long ans = 0;

    cout << ans << "\n";

    return 0;
}
