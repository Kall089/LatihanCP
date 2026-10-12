/*
============================================================
📋 TUGAS 15: Urutkan 10^7 Bilangan
============================================================
Source: Original
Difficulty: Hard
Topics: optimasi nyata

PROBLEM:
Baca 10^7 bilangan bulat dan cetak seluruhnya dalam keadaan terurut.
Batas waktunya 1 detik, sehingga std::sort dengan cin/cout biasa akan TLE.
Kamu perlu radix sort DAN pembacaan/penulisan yang cepat.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N bilangan terurut

CONSTRAINTS:
- 1 <= N <= 10^7
- 0 <= a[i] <= 10^9

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
    // Tiga hal harus benar: radix sort, pembacaan cepat (getchar_unlocked atau baca seluruh buffer sekaligus), dan penulisan cepat (bangun satu string). Salah satu saja lambat, kamu tetap TLE.

    return 0;
}
