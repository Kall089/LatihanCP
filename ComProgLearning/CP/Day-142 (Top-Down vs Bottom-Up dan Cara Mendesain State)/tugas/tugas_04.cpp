/*
============================================================
📋 TUGAS 04: Kupon Wajib Digunakan Tepat Sekali
============================================================
Source: Modification of Frog Jump
Difficulty: Medium
Topics: State Design, Enforcing Terminal State

PROBLEM:
Terdapat N pos dengan ketinggian H[0], H[1], ..., H[N-1].
Dari pos i, kamu boleh bergerak ke pos (i + 1) atau (i + 2) dengan biaya energi |H[i] - H[j]|.
Kamu memiliki 1 kupon gratis.
BERBEDA dengan soal latihan, kali ini kamu WAJIB menggunakan kupon tersebut tepat satu kali
di salah satu lompatan dalam perjalanan dari pos 0 ke pos N-1.
Cari total energi minimum untuk mencapai pos N-1 dengan syarat kupon wajib terpakai.

INPUT FORMAT:
Baris pertama: N (N >= 2)
Baris kedua: N bilangan bulat H[0], ..., H[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: energi minimum dengan kupon terpakai tepat sekali.

CONSTRAINTS:
2 <= N <= 100.000
0 <= H[i] <= 1.000.000.000

SAMPLE INPUT 1:
2
7 99

SAMPLE OUTPUT 1:
0
(Penjelasan: Lompat dari 0 ke 1 wajib menggunakan kupon, sehingga biaya = 0.)

SAMPLE INPUT 2:
4
0 4 8 12

SAMPLE OUTPUT 2:
4
(Penjelasan: Tanpa kupon lompat 0->2->3 biaya 8+4=12. Dengan kupon pada 0->2 biaya 0, lalu 2->3 biaya 4, total = 4.)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // TODO: Definisikan dp[i][used] di mana used = 0 (belum) atau 1 (sudah).
    // Basis: dp[0][0] = 0, dp[0][1] = INF (karena belum ada lompatan yang dilakukan!).
    // Jawaban akhir HARUS dp[n-1][1] (kupon WAJIB sudah terpakai).

    return 0;
}
