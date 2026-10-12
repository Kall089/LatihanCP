/*
============================================================
📋 TUGAS 14: Partisi Koin dengan Selisih Bobot Minimum
============================================================
Source: Classic DP / Partition Min Difference
Difficulty: Hard
Topics: Bounded Subset Sum Min Absolute Difference

PROBLEM:
Dua orang saudara mendapatkan warisan berupa koin emas batangan.
Terdapat N jenis koin emas. Koin jenis ke-i berbobot w[i] gram dan terdapat c[i] keping.
Kedua saudara ingin membagi SELURUH koin emas tersebut ke dalam dua tumpukan
sedemikian rupa sehingga SELISIH MUTLAK total bobot antara kedua tumpukan
adalah SEKECIL MUNGKIN.

Tentukan selisih mutlak minimum total bobot antara kedua tumpukan.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: selisih mutlak bobot terkecil.

CONSTRAINTS:
1 <= N <= 80
1 <= w[i] <= 1.000
1 <= c[i] <= 200
Total bobot seluruh koin <= 40.000

SAMPLE INPUT 1:
2
4 3
5 2

SAMPLE OUTPUT 1:
0
(Penjelasan: Total koin: tiga koin 4 (bobot 12) + dua koin 5 (bobot 10) = total 22.
Tumpukan A: satu koin 5 + empat koin? Tidak: dua koin 5 (10) + satu koin?
Bisa bagi: (dua koin 4 + satu koin 5 = 8 + 5 = 13) dan (satu koin 4 + satu koin 5 = 9), selisih = 4.
Bagaimana dengan: (dua koin 5 = 10)?
Atau (satu koin 4 + satu koin 5 = 9)?
Jika total = 22, setengahnya adalah 11.
Bisakah membentuk 11 dari keping {4, 4, 4, 5, 5}?
Tidak ada subset yang berjumlah 11!
Subset terdekat <= 11:
- {4, 5} = 9 -> selisih = 22 - 2*9 = 4
- {5, 5} = 10 -> selisih = 22 - 2*10 = 2
- {4, 4, 4} = 12 -> selisih = |12 - 10| = 2.
Maka selisih mutlak minimum adalah 2!)

SAMPLE INPUT 2:
1
10 4

SAMPLE OUTPUT 2:
0
(Penjelasan: Empat keping 10 dapat dibagi dua keping (20) dan dua keping (20). Selisih 0)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> w(n);
    vector<int> c(n);
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
        total_sum += (long long)w[i] * c[i];
    }

    // TODO: Selesaikan Bounded Partition Min Difference
    // 1. target = total_sum / 2
    // 2. vector<bool> can(target + 1, false); can[0] = true;
    // 3. Update boolean can dengan paket biner
    // 4. Cari nilai s terbesar <= target yang can[s] == true
    // 5. Cetak total_sum - 2 * s

    return 0;
}
