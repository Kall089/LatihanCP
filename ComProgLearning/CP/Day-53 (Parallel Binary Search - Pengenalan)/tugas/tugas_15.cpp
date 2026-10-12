/*
============================================================
📋 TUGAS 15: PBS Bersarang
============================================================
Source: Original
Difficulty: Hard
Topics: PBS dua lapis

PROBLEM:
N kejadian menambah nilai ke rentang. Untuk setiap query, cari PASANGAN
(waktu t, ambang x) terkecil secara leksikografis sehingga pada waktu t
terdapat setidaknya k posisi yang nilainya melebihi x. Cetak t dan x.

INPUT FORMAT:
- Baris pertama: M, N, Q
- N baris: l r v
- Q baris: k

OUTPUT FORMAT:
- Q baris berisi dua bilangan

CONSTRAINTS:
- M, N, Q <= 5*10^4

SAMPLE INPUT 1:
3 2 1
1 3 5
2 3 5
2

SAMPLE OUTPUT 1:
1 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dua lapis binary search bersarang. Hitung dulu total biayanya - kalau log^2 terlalu mahal, cari cara menggabungkan kedua lapisnya.

    return 0;
}
