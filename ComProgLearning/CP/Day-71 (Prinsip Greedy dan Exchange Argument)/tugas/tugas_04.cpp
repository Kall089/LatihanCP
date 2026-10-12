/*
============================================================
📋 TUGAS 04: Tasks and Deadlines
============================================================
Source: CSES 1630
Difficulty: Medium
Topics: Greedy, exchange argument

PROBLEM:
Ada n tugas dengan durasi dan tenggat masing-masing. Tugas dikerjakan satu per satu
tanpa jeda. Kalau sebuah tugas selesai pada waktu x dan tenggatnya d, kamu mendapat
nilai d - x (bisa negatif). Cari total nilai maksimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: durasi dan tenggat

OUTPUT FORMAT:
Satu bilangan: total nilai maksimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= durasi, tenggat <= 10^6

SAMPLE INPUT 1:
3
6 10
8 15
5 12

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tenggat sama sekali tidak memengaruhi urutan optimal — total tenggat konstan. Yang perlu diminimalkan adalah jumlah waktu selesai. Ini persis Exercise 1.

    return 0;
}
