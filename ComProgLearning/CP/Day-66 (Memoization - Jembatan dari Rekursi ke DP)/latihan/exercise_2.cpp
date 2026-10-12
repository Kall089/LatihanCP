/*
============================================================
🏋️ Exercise 2: Kurir di Pematang Sawah (Frog Jump Min Energy)
============================================================
Day: 066 | Difficulty: Easy-Medium | Topic: Top-Down Memoization with Optimization
Source: AtCoder Educational DP Contest - Frog 1 / Review
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang kurir berdiri di petak ke-0 pada deretan N buah pematang sawah (berindeks 0 sampai N-1).
Pematang sawah ke-i memiliki ketinggian H[i].
Kurir ingin mencapai pematang sawah tujuan di petak ke-N-1.

Dari petak ke-i saat ini, kurir hanya diperbolehkan melangkah ke:
1. Petak tepat di depannya: petak i + 1
2. Atau melompati satu petak: petak i + 2 (jika i + 2 < N)

Energi yang dibutuhkan untuk berpindah dari petak i ke petak j adalah selisih mutlak ketinggian:
`|H[i] - H[j]|`.

Hitung TOTAL ENERGI MINIMUM yang diperlukan kurir untuk mencapai petak N-1!
(Jika N = 1, kurir sudah berada di tujuan, energinya 0).

Selesaikan dengan pendekatan REKURSIF DENGAN MEMOISASI (Top-Down)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat H[0], H[1], ..., H[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total energi minimum.

📏 CONSTRAINTS:
- 1 <= N <= 400
- 0 <= H[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
10 30 20 40

📎 SAMPLE OUTPUT 1:
30

[Penjelasan Sample 1:
Rute terbaik: petak 0 -> petak 1 -> petak 3.
Energi = |10 - 30| + |30 - 40| = 20 + 10 = 30.]

📎 SAMPLE INPUT 2:
1
99

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
N = 1, kurir sudah berada di petak tujuan. Energi = 0.]

📎 SAMPLE INPUT 3:
3
5 100 5

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3:
Kurir melompat 2 langkah langsung dari petak 0 ke petak 2:
Energi = |5 - 5| = 0.]

💡 HINT:
- Definisikan fungsi rekursif:
  `solve(i)`: energi minimum untuk berpindah dari petak i menuju petak akhir N - 1.
- Kasus Dasar:
  - `if (i == N - 1) return 0;`
- Cek Memoisasi:
  - `if (seen[i]) return memo[i];`
  - `seen[i] = true;`
- Rekursi:
  - Opsi 1 (melangkah ke i + 1): `|H[i] - H[i+1]| + solve(i + 1)`
  - Opsi 2 (melangkah ke i + 2, jika i + 2 < N): `|H[i] - H[i+2]| + solve(i + 2)`
  - Ambil nilai minimum dari kedua opsi tersebut.

🎯 Learning Goals:
- [ ] Mengubah persoalan minimisasi rekursif menjadi efisien melalui memoisasi sufiks.
- [ ] Menggunakan tipe data `long long` untuk menghindari overflow pada akumulasi biaya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
