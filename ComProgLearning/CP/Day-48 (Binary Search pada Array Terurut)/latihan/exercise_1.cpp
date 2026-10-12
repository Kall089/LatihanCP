/*
============================================================
🏋️ Exercise 1: Binary Search Standard
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array A berukuran N yang sudah terurut secara ascending dan sebuah target X.
Cari dan cetak indeks (0-indexed) dari X di dalam array A. Jika X tidak ditemukan, cetak -1.

📥 INPUT FORMAT:
- Baris pertama: N X (1 <= N <= 10^5, -10^9 <= X <= 10^9)
- Baris kedua: N buah integer terurut A[1], A[2], ..., A[N] (-10^9 <= A[i] <= 10^9)

📤 OUTPUT FORMAT:
- Sebuah integer: indeks dari X (0-indexed) atau -1 jika tidak ada.

📎 SAMPLE INPUT 1:
5 7
1 3 5 7 9

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
4 2
1 3 5 7

📎 SAMPLE OUTPUT 2:
-1

💡 HINT: Gunakan dua pointer low=0 dan high=n-1. Mid dihitung dengan low + (high-low)/2.
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

    // TODO: Implementasikan Binary Search manual
    // Simpan indeks di ans (-1 jika tidak ketemu)
    int ans = -1;

    cout << ans << "\n";

    return 0;
}
