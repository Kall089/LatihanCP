/*
============================================================
📋 TUGAS 14: Sonya and Matrix Beauty
============================================================
Source: CF 1080E
Difficulty: Hard
Topics: manacher pada baris tergabung

PROBLEM:
Diberikan matriks huruf berukuran N x M. Sebuah submatriks disebut cantik
jika setiap barisnya dapat disusun ulang sehingga seluruh submatriks menjadi
simetris (setiap baris palindrom dan susunan barisnya palindrom).
Hitung banyaknya submatriks yang cantik.

INPUT FORMAT:
- Baris pertama: N dan M
- N baris berikutnya: masing-masing M huruf

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N, M <= 250

SAMPLE INPUT 1:
1 3
aba

SAMPLE OUTPUT 1:
4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk tiap pasangan kolom (l, r), ubah setiap baris menjadi 'tanda tangan' paritas huruf, lalu jalankan Manacher pada kolom tanda tangan tersebut.

    return 0;
}
