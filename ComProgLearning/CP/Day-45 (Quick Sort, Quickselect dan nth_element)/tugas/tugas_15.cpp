/*
============================================================
📋 TUGAS 15: Median of Medians
============================================================
Source: Original
Difficulty: Hard
Topics: seleksi O(n) dijamin

PROBLEM:
Implementasikan algoritma median-of-medians untuk mencari elemen terkecil
ke-k dengan jaminan O(N) pada KASUS TERBURUK (bukan hanya rata-rata).
Bandingkan waktu berjalannya dengan quickselect pivot acak pada data acak
maupun data terurut.

INPUT FORMAT:
- Baris pertama: N dan k
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= k <= N <= 10^6

SAMPLE INPUT 1:
6 3
5 2 8 1 9 3

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Bagi menjadi kelompok berisi 5, cari median tiap kelompok, lalu cari median dari median-median itu secara rekursif, dan pakai sebagai pivot. Konstantanya besar sehingga dalam PRAKTIK sering lebih lambat daripada pivot acak - itu pelajarannya.

    return 0;
}
