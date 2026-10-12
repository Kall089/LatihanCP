/*
============================================================
📋 TUGAS 13: Langkah Maju dan Mundur Terbatas
============================================================
Source: Codeforces / Original
Difficulty: Medium
Topics: State Design, Avoiding Illegal Transitions

PROBLEM:
Terdapat N petak bernomor 0 sampai N-1 dengan nilai koin C[0], ..., C[N-1].
Mulai dari petak 0, kamu ingin mengumpulkan total koin maksimum dengan aturan:
1. Dari petak i, kamu boleh melangkah MAJU ke petak i + 1 atau i + 2.
2. Kamu juga diperbolehkan melangkah MUNDUR ke petak i - 1, TETAPI:
   - Kamu TIDAK BOLEH melangkah mundur dua kali berturut-turut!
   - Total langkah mundur sepanjang permainan dibatasi maksimal 1 kali!
Hitung koin maksimum yang bisa kamu kumpulkan saat mencapai petak N-1.
Setiap kali mendarat di petak i, kamu mendapatkan nilai C[i].
(Catatan: C[i] bisa bernilai negatif).

INPUT FORMAT:
Baris pertama: N
Baris kedua: N bilangan bulat C[0], ..., C[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: total koin maksimum mencapai petak N-1.

CONSTRAINTS:
2 <= N <= 100.000
-10.000 <= C[i] <= 10.000

SAMPLE INPUT 1:
4
0 10 -5 20

SAMPLE OUTPUT 1:
30
(Penjelasan: Maju 0 -> 1 (+10), maju 1 -> 3 (+20). Total = 30.)

SAMPLE INPUT 2:
5
0 -10 30 -5 10

SAMPLE OUTPUT 2:
40
(Penjelasan: Maju 0 -> 2 (+30), mundur 2 -> 1 (-10), maju 1 -> 3 (-5), maju 3 -> 4 (+10)...
 Lebih baik 0 -> 2 (+30), maju 2 -> 4 (+10) = 40.)
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

    vector<long long> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    // TODO: Rancang state dp[i][mundur_terpakai][langkah_terakhir_mundur]
    // Pastikan tidak ada siklus tak hingga dan properti DAG tetap terjaga

    return 0;
}
