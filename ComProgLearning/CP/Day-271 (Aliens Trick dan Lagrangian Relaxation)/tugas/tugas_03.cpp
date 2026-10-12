/*
============================================================
📋 TUGAS 03: Memilih K Interval Berbobot dengan Waktu Istirahat (Cooldown)
============================================================
Source: Weighted Activity Selection with Cooldown
Difficulty: Hard
Topics: Aliens Trick, Interval DP

PROBLEM:
Diberikan N interval pekerjaan dengan waktu mulai L[i], selesai R[i], dan profit W[i].
Mesin memerlukan waktu pendinginan/istirahat sebesar D setelah menyelesaikan pekerjaan sebelum
dapat memulai pekerjaan berikutnya.
Dengan kata lain, pekerjaan j dapat dilakukan setelah pekerjaan i jika dan hanya jika:
`R[i] + D <= L[j]`.
Pilih paling banyak K pekerjaan yang memenuhi syarat tersebut.

Tentukan TOTAL PROFIT MAKSIMUM yang dapat diperoleh!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan D.
N baris berikutnya masing-masing berisi tiga bilangan bulat L[i], R[i], dan W[i].

OUTPUT FORMAT:
Satu baris berisi total profit maksimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= D <= 1.000.000.000
0 <= L[i] < R[i] <= 1.000.000.000
1 <= W[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 2 2
1 3 10
2 5 20
5 7 15

SAMPLE OUTPUT 1:
25
(Interval 1 selesai di 3, butuh pendinginan D=2 sehingga siap di 3+2=5.
Interval 3 mulai di 5 (5 >= 5), valid! Total = 10 + 15 = 25.)

SAMPLE INPUT 2:
3 2 3
1 3 10
2 5 20
5 7 15

SAMPLE OUTPUT 2:
20
(Jika D=3, interval 1 siap di 3+3=6 > 5, tidak bisa dilanjut dengan interval 3.
Pilihan terbaik adalah mengambil interval 2 tunggal dengan bobot 20.)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll d;
    if (!(cin >> n >> k >> d)) return 0;

    // TODO: Selesaikan dengan Aliens Trick O(N log N)

    return 0;
}
