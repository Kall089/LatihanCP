/*
============================================================
📋 TUGAS 14: Perjalanan Hemat Baterai (Battery-Constrained DP)
============================================================
Source: Original
Difficulty: Medium
Topics: State Design with Resource Constraint

PROBLEM:
Sebuah mobil listrik melakukan perjalanan melintasi N stasiun bernomor 0 sampai N-1.
Kapasitas maksimal baterai mobil adalah B unit.
Mobil mulai di stasiun 0 dengan baterai terisi penuh (B unit).
Untuk berpindah dari stasiun i ke stasiun i + 1, mobil menghabiskan consume[i] unit baterai.
Di setiap stasiun i (kecuali stasiun awal dan akhir), terdapat fasilitas pengisian daya
yang dapat menambah baterai sebesar charge[i] unit (tetapi baterai tidak bisa melebihi B).
Namun, mengisi daya di stasiun i membutuhkan biaya uang sebesar cost[i].
Pengisian daya bersifat opsional (boleh mengisi, boleh tidak).
Jika baterai mobil mencapai < 0 di tengah jalan sebelum mencapai stasiun berikutnya, mobil mogok.
Cari total biaya uang minimum yang harus dikeluarkan untuk mencapai stasiun N-1 tanpa pernah mogok.
Jika mustahil mencapai stasiun N-1, cetak -1.

INPUT FORMAT:
Baris pertama: N B
Baris kedua: N-1 bilangan bulat consume[0], ..., consume[N-2]
Baris ketiga: N bilangan bulat charge[0], ..., charge[N-1]
Baris keempat: N bilangan bulat cost[0], ..., cost[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: biaya minimum, atau -1 jika mustahil.

CONSTRAINTS:
2 <= N <= 1.000
1 <= B <= 500
1 <= consume[i] <= B

SAMPLE INPUT 1:
3 10
6 6
0 5 0
0 20 0

SAMPLE OUTPUT 1:
20
(Penjelasan: Dari 0 ke 1 baterai sisa 10-6=4. Untuk lanjut ke 2 butuh 6, jadi harus isi daya di 1 (tambah 5 jadi 9, biaya 20). Dari 1 ke 2 sisa 9-6=3. Total biaya = 20.)

SAMPLE INPUT 2:
2 5
10
0 0
0 0

SAMPLE OUTPUT 2:
-1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, b;
    if (!(cin >> n >> b)) return 0;

    vector<int> consume(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> consume[i];

    vector<int> charge(n), cost(n);
    for (int i = 0; i < n; i++) cin >> charge[i];
    for (int i = 0; i < n; i++) cin >> cost[i];

    // TODO: Definisikan dp[i][bat] = biaya minimum berada di stasiun i dengan sisa baterai bat
    // Ukuran tabel N x (B + 1) -> 1.000 x 500 = 5 x 10^5 state (sangat efisien)

    return 0;
}
