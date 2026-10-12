/*
============================================================
📋 Tugas 08: Poisoned Dagger (Codeforces 1613C)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Simulasi Racun)

PROBLEM STATEMENT:
Monoparp menyerang naga dengan N tebasan pedang beracun pada detik A[1], A[2], ..., A[N].
Setiap tebasan memberikan racun yang berdurasi K detik (memberikan 1 damage per detik).
Jika tebasan baru dilakukan saat racun terdahulu masih aktif, efek racun sebelumnya terhenti dan racun baru berdurasi K detik dimulai kembali.
Naga memiliki darah sebesar H. Cari durasi K MINIMUM agar total damage yang diterima naga minimal H.

INPUT FORMAT:
- Baris 1: N H
- Baris 2: N integer A[1..N] (terurut ascending)

OUTPUT FORMAT:
- Satu integer: nilai K minimum.

CONSTRAINTS:
- 1 ≤ N ≤ 100
- 1 ≤ H ≤ 10^18
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
2 5
1 5

SAMPLE OUTPUT 1:
3

PENJELASAN SAMPLE 1:
Dengan K = 3:
- Tebasan 1 di detik 1: aktif detik 1, 2, 3 (3 damage).
- Tebasan 2 di detik 5: aktif detik 5, 6, 7 (3 damage).
Total damage = 6 (>= 5).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long h;
    if (!(cin >> n >> h)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Binary search durasi K

    return 0;
}
