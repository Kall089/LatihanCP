/*
============================================================
📋 TUGAS 13: Wiggle Sort
============================================================
Source: LeetCode 324
Difficulty: Hard
Topics: quickselect + penempatan

PROBLEM:
Susun ulang array sehingga polanya menjadi a[0] < a[1] > a[2] < a[3] > ...
Dijamin selalu ada solusi. Kerjakan dalam O(N) waktu rata-rata.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N bilangan

CONSTRAINTS:
- 1 <= N <= 5*10^4

SAMPLE INPUT 1:
6
1 5 1 1 6 4

SAMPLE OUTPUT 1:
1 6 1 5 1 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Cari median dengan nth_element, lalu tempatkan elemen ke indeks ganjil dan genap dengan pemetaan indeks tertentu. Perhatikan penanganan nilai yang SAMA dengan median.

    return 0;
}
