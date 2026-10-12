/*
============================================================
📋 TUGAS 12: Asteroid Collision
============================================================
Source: Original
Difficulty: Hard
Topics: stack, simulation

PROBLEM:
Diberikan n asteroid dalam satu baris. Asteroid[i] mewakili ukuran dan arah:
- Positif → bergerak ke kanan
- Negatif → bergerak ke kiri

Saat dua asteroid bertabrakan, yang lebih kecil meledak.
Jika sama besar → keduanya meledak.
Asteroid yang bergerak arah sama tidak bertabrakan.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (asteroid)

OUTPUT FORMAT:
- Asteroid yang tersisa (dalam urutan asli, dipisah spasi)

CONSTRAINTS:
- 1 ≤ n ≤ 10^4
- -1000 ≤ asteroid[i] ≤ 1000, asteroid[i] ≠ 0

SAMPLE INPUT 1:
5
5 10 -5 -10 5

SAMPLE OUTPUT 1:
5 5

SAMPLE INPUT 2:
4
8 -8 -2 3

SAMPLE OUTPUT 2:
-2 3

NOTE: Gunakan stack. Push asteroid ke kanan langsung.
      Asteroid ke kiri → cek top stack:
        jika top lebih kecil → pop dan terus
        jika sama besar → pop keduanya, stop
        jika top lebih besar → asteroid baru meledak, stop
        jika stack kosong atau top negatif → push ke stack.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
