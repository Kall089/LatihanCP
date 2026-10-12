/*
============================================================
📋 TUGAS 08: K Best
============================================================
Source: POJ 3111
Difficulty: Medium
Topics: fractional programming

PROBLEM:
N benda dengan nilai v[i] dan bobot w[i]. Pilih tepat K benda yang
memaksimalkan (jumlah v) / (jumlah w). Cetak INDEKS benda yang dipilih.

INPUT FORMAT:
- Baris pertama: N dan K
- N baris berisi v[i] dan w[i]

OUTPUT FORMAT:
- K indeks (1-based), urutan bebas

CONSTRAINTS:
- 1 <= K <= N <= 10^5

SAMPLE INPUT 1:
3 2
1 1
2 1
3 1

SAMPLE OUTPUT 1:
2 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // sum(v) / sum(w) >= x  <=>  sum(v[i] - x*w[i]) >= 0. Transformasi ini sah karena w[i] > 0.

    return 0;
}
