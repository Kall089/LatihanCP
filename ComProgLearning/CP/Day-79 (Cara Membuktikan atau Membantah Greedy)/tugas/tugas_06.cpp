/*
============================================================
📋 TUGAS 06: Menemukan Kriteria Secara Empiris
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Penemuan

PROBLEM:
Diberikan n pekerjaan dengan dua bilangan a[i] dan b[i]. Biaya sebuah urutan adalah
nilai terbesar dari (jumlah a untuk k pekerjaan pertama) ditambah b pekerjaan ke-k,
atas seluruh k.
Temukan kriteria pengurutan yang benar dengan cara: tulis brute force permutasi,
daftar minimal delapan kriteria yang masuk akal, jalankan semuanya, catat mana yang
bertahan. Lalu buktikan dan implementasikan versi O(n log n)-nya.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: a[i] dan b[i]

OUTPUT FORMAT:
Satu bilangan: biaya minimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= a[i], b[i] <= 10^9

SAMPLE INPUT 1:
3
1 3
2 1
3 2

SAMPLE OUTPUT 1:
7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Delapan kriteria yang layak dicoba: a naik, a turun, b naik, b turun, a+b naik, a+b turun, a-b naik, b-a naik. Hanya satu yang bertahan, dan salah satu dari a atau b tidak muncul sama sekali.

    return 0;
}
