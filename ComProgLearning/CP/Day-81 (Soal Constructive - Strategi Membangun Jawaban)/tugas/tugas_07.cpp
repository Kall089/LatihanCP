/*
============================================================
📋 TUGAS 07: Menyusun Graf Berderajat Tertentu
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Konstruksi graf + paritas

PROBLEM:
Diberikan n dan barisan derajat d[1..n], susun graf sederhana tak berarah dengan n simpul
yang derajat tiap simpulnya persis d[i], atau nyatakan tidak mungkin.

INPUT FORMAT:
Baris 1: n
Baris 2: n bilangan d[i]

OUTPUT FORMAT:
NO, atau YES lalu jumlah sisi dan daftar sisinya

CONSTRAINTS:
1 <= n <= 500, 0 <= d[i] < n

SAMPLE INPUT 1:
4
2 2 2 2

SAMPLE OUTPUT 1:
YES
4
1 2
2 3
3 4
4 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Periksa paritas jumlah derajat lebih dulu. Lalu pakai algoritma Havel-Hakimi: ambil simpul berderajat terbesar, sambungkan ke simpul-simpul berderajat terbesar berikutnya, ulangi.

    return 0;
}
