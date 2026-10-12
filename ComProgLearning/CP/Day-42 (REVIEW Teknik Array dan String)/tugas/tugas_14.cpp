/*
============================================================
📋 TUGAS 14: Dua Segmen dengan Panjang Tetap
============================================================
Source: LeetCode 1031
Difficulty: Hard
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan N bilangan non-negatif dan dua panjang L dan M. Pilih DUA subarray
yang TIDAK saling tumpang tindih, satu berpanjang tepat L dan satu berpanjang
tepat M, sehingga total jumlah keduanya maksimum. Urutan keduanya bebas -
segmen berpanjang L boleh berada di kiri maupun di kanan segmen berpanjang M.

INPUT FORMAT:
- Baris pertama: N, L, dan M
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- L + M <= N <= 1000
- 0 <= a[i] <= 1000

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
9 1 2
0 6 5 2 2 5 1 9 4
output:
20
penjelasan: segmen berpanjang 1 = [9] pada posisi 8, dan segmen berpanjang 2 =
[6,5] pada posisi 2..3. Totalnya 9 + 11 = 20. Perhatikan bahwa segmen M berada
DI KIRI segmen L di sini - kalau kodemu hanya mencoba satu susunan, kamu akan salah.

SAMPLE 2 - L lebih panjang
input:
9 3 2
3 8 1 3 2 1 8 9 0
output:
29

SAMPLE 3 - keduanya panjang
input:
10 4 3
2 1 5 6 0 9 5 0 3 8
output:
31

SAMPLE 4 - kasus minimal
input:
2 1 1
1 1
output:
2

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- kunci TITIK POTONG, lalu kedua sisi menjadi masalah bebas
- kamu perlu mencoba DUA susunan: L di kiri M, dan M di kiri L
- prefix sum membuat jumlah tiap segmen O(1)
- jangan lupa segmen tidak boleh tumpang tindih meski hanya satu elemen
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TEBAKAN TEKNIK SAYA: ______________________
    // SINYAL DI SOAL     : ______________________

    // TODO: Kerjakan di sini

    return 0;
}
