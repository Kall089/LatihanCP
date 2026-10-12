/*
============================================================
📋 TUGAS 12: Kecepatan Optimal Kapal
============================================================
Source: Original
Difficulty: Hard
Topics: ternary + biaya

PROBLEM:
Sebuah kapal menempuh jarak D. Pada kecepatan v, konsumsi bahan bakarnya
adalah a*v^2 + b per jam, dan biaya waktunya c per jam. Cari kecepatan v
pada rentang [1, V] yang meminimumkan biaya total perjalanan. Cetak biaya
minimum dengan 6 desimal.

INPUT FORMAT:
- Satu baris: D a b c V

OUTPUT FORMAT:
- Satu bilangan, 6 desimal

CONSTRAINTS:
- 1 <= D, V <= 10^6
- 1 <= a, b, c <= 10^6

SAMPLE INPUT 1:
100 1 1 1 100

SAMPLE OUTPUT 1:
300.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // biaya(v) = (D/v) * (a*v^2 + b + c). Sederhanakan dulu, lalu periksa apakah cembung terhadap v.

    return 0;
}
