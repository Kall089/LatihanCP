/*
============================================================
🏋️ Exercise 1: Lampion di Tangga Kampung (Climbing Stairs with Broken Steps)
============================================================
Day: 066 | Difficulty: Easy | Topic: Top-Down Memoization 1D
Source: Classic Recursion to DP
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Warga sebuah kampung memasang lampion di sepanjang deretan anak tangga dari tangga 0 hingga N.
Kamu mulai berdiri di anak tangga ke-0 dan ingin mencapai puncak tangga ke-N.
Dari anak tangga saat ini, kamu hanya boleh melangkah naik tepat 1 anak tangga atau tepat 3 anak tangga.

Namun, terdapat B buah anak tangga yang rapuh/rusak sehingga TIDAK BOLEH diinjak sama sekali.
(Anak tangga rapuh boleh dilompati jika kamu melangkah 3 anak tangga melewatinya).

Hitung berapa banyak urutan langkah berbeda yang mungkin untuk mencapai puncak tangga ke-N,
modulo 1.000.000.007!
Catatan: Untuk N = 0, diam di tempat dihitung sebagai 1 cara yang sah.

Selesaikan dengan pendekatan REKURSIF DENGAN MEMOISASI (Top-Down)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan B.
- Baris kedua berisi B bilangan bulat positif menyatakan indeks anak tangga yang rapuh (baris ini kosong jika B = 0).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: banyak urutan langkah modulo 1.000.000.007.

📏 CONSTRAINTS:
- 0 <= N <= 400
- 0 <= B <= N
- Indeks anak tangga rapuh unik dan berada dalam rentang [1, N]

📎 SAMPLE INPUT 1:
4 0

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1:
Cara mencapai tangga 4 tanpa tangga rapuh:
1. 1 + 1 + 1 + 1
2. 1 + 3
3. 3 + 1
Total ada 3 cara.]

📎 SAMPLE INPUT 2:
3 1
1

📎 SAMPLE OUTPUT 2:
1

[Penjelasan Sample 2:
Tangga 1 rapuh (tidak boleh diinjak).
Langkah yang sah hanya langsung melompat 3 langkah dari 0 menuju 3 (0 -> 3).
Total 1 cara.]

📎 SAMPLE INPUT 3:
0 0

📎 SAMPLE OUTPUT 3:
1

💡 HINT:
- Definisikan fungsi rekursif:
  `solve(i)`: banyak cara mencapai anak tangga i dari 0.
- Kasus Dasar:
  - `if (i < 0) return 0;`
  - `if (i == 0) return 1;`
  - `if (is_broken[i]) return 0;`
- Cek Memoisasi:
  - `if (seen[i]) return memo[i];`
  - `seen[i] = true;`
- Rekursi:
  - Dari tangga i, kita bisa datang dari i - 1 atau i - 3:
    `return memo[i] = (solve(i - 1) + solve(i - 3)) % MOD;`

🎯 Learning Goals:
- [ ] Memahami 3 baris sakti memoisasi pada fungsi rekursif 1D.
- [ ] Menangani kasus dasar negatif dan kondisi terhalang (*broken steps*).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, b;
    if (!(cin >> n >> b)) return 0;

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
