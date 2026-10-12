/*
============================================================
📋 TUGAS 15: Timsort Sederhana
============================================================
Source: Original
Difficulty: Hard
Topics: merge + insertion

PROBLEM:
Implementasikan versi sederhana Timsort: bagi array menjadi blok-blok
sepanjang 32, urutkan tiap blok dengan insertion sort, lalu gabungkan
blok-blok itu dengan merge secara bottom-up. Cetak array terurut dan
bandingkan waktunya dengan merge sort murni.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N bilangan terurut

CONSTRAINTS:
- 1 <= N <= 10^6

SAMPLE INPUT 1:
5
5 4 3 2 1

SAMPLE OUTPUT 1:
1 2 3 4 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Inilah yang dilakukan std::sort dan Timsort sungguhan: memakai insertion sort untuk potongan kecil karena konstantanya jauh lebih kecil.

    return 0;
}
