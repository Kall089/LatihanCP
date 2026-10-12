/*
============================================================
📋 TUGAS 08: Berapa Kali Pola Muncul di Setiap Prefiks
============================================================
Source: Original
Difficulty: Medium
Topics: automaton + prefix sum

PROBLEM:
Diberikan teks T dan pola P. Untuk setiap i dari 1 sampai |T|, cetak berapa
kali P muncul sebagai substring di dalam T[0..i-1] (prefiks T sepanjang i).

INPUT FORMAT:
- Baris pertama: T
- Baris kedua: P

OUTPUT FORMAT:
- |T| baris, masing-masing satu bilangan

CONSTRAINTS:
- 1 <= |P| <= |T| <= 10^6

SAMPLE INPUT 1:
aaaa
aa

SAMPLE OUTPUT 1:
0
1
2
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
    // Jalankan KMP sekali, tandai posisi akhir kemunculan, lalu prefix sum.

    return 0;
}
