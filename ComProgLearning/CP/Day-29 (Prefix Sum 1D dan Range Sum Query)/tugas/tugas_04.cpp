/*
============================================================
📋 TUGAS 04: Hitung Huruf 'AC'
============================================================
Source: AtCoder ABC122 C
Difficulty: Easy
Topics: prefix count

PROBLEM:
Diberikan string S sepanjang N yang terdiri dari huruf A, C, G, T, dan Q
pertanyaan berupa rentang [l, r]. Untuk setiap pertanyaan, hitung berapa
kali substring "AC" muncul di dalam S[l..r].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: string S
- Q baris: l dan r

OUTPUT FORMAT:
- Q baris berisi bilangan

CONSTRAINTS:
- 2 <= N <= 10^5
- 1 <= Q <= 10^5

SAMPLE INPUT 1:
8 3
ACACTACG
3 7
2 3
1 8

SAMPLE OUTPUT 1:
2
0
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
    // Tandai posisi i kalau S[i]=='A' dan S[i+1]=='C', lalu prefix count. Hati-hati batas kanan.

    return 0;
}
