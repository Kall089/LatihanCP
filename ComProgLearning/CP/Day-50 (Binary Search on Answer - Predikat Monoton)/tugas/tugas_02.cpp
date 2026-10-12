/*
============================================================
📋 Tugas 02: Minimum Speed to Arrive on Time (LeetCode 1870)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer with Floating-point Hours

PROBLEM STATEMENT:
Kamu harus menempuh N perjalanan kereta berurutan dengan jarak dist[1..N].
Setiap perjalanan kereta (kecuali perjalanan terakhir) harus berangkat pada jam bulat.
Artinya, jika perjalanan i selesai pada waktu 2.3 jam, kamu harus menunggu hingga jam ke-3 untuk naik kereta berikutnya.

Diberikan total batas waktu HOUR (bilangan desimal).
Cari kecepatan bulat positif MINIMUM (km/jam) yang dibutuhkan agar tiba tepat waktu (total waktu ≤ HOUR).
Jika tidak memungkinkan dengan kecepatan berapa pun, cetak -1.

INPUT FORMAT:
- Baris 1: N HOUR (N integer, HOUR double)
- Baris 2: N integer dist[1..N]

OUTPUT FORMAT:
- Satu integer: kecepatan minimum, atau -1 jika tidak memungkinkan.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 1.0 ≤ HOUR ≤ 10^9
- 1 ≤ dist[i] ≤ 100.000

SAMPLE INPUT 1:
3 6.0
1 3 2

SAMPLE OUTPUT 1:
1

SAMPLE INPUT 2:
3 2.7
1 3 2

SAMPLE OUTPUT 2:
3

PENJELASAN SAMPLE 2:
Dengan speed = 3:
- Kereta 1 (1 km): ceil(1/3) = 1 jam
- Kereta 2 (3 km): ceil(3/3) = 1 jam
- Kereta 3 (2 km): 2/3 = 0.67 jam (karena terakhir, tidak perlu dibulatkan)
Total waktu = 1 + 1 + 0.67 = 2.67 jam (<= 2.7).

HINT:
Batas atas kecepatan bisa di-set ke 10^7.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    double hour;
    if (!(cin >> n >> hour)) return 0;

    vector<long long> dist(n);
    for (int i = 0; i < n; i++) cin >> dist[i];

    // TODO: Implementasikan Binary Search on Answer untuk kecepatan

    return 0;
}
