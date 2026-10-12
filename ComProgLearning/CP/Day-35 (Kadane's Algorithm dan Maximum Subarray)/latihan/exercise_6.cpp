/*
============================================================
🏋️ Exercise 6: Submatriks dengan Jumlah Maksimum
============================================================
Day: 35 | Difficulty: Hard (Contest-level)
Topic: Kunci dua baris + Kadane 1D
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan matriks berukuran R baris dan C kolom berisi bilangan bulat
(boleh negatif). Cari SUBMATRIKS berbentuk persegi panjang yang tidak kosong
dengan jumlah seluruh elemennya paling besar, lalu cetak jumlah itu.
Submatriks ditentukan oleh sepasang batas baris dan sepasang batas kolom.
Mencoba semua submatriks secara naif membutuhkan O(R^2 * C^2) yang terlalu
lambat; kamu perlu menurunkannya menjadi O(R^2 * C).

📥 INPUT FORMAT:
- Baris pertama: R dan C
- R baris berikutnya: masing-masing C bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= R, C <= 300
- -10^6 <= g[i][j] <= 10^6

📎 SAMPLE INPUT 1:
4 4
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2

📎 SAMPLE OUTPUT 1:
15

📎 SAMPLE INPUT 2:
2 2
-1 -2
-3 -4

📎 SAMPLE OUTPUT 2:
-1

💡 HINT: Kunci sepasang batas baris (atas dan bawah). Setelah keduanya
         terkunci, "jumlah submatriks" hanya bergantung pada batas kolom —
         dan itu persis masalah subarray maksimum satu dimensi.
         Untuk menghindari menghitung ulang, akumulasikan jumlah kolom
         secara bertahap saat batas bawah bergerak turun.

🎯 Learning Goals:
- [ ] Teknik "kunci satu dimensi, selesaikan dimensi lain"
- [ ] Menghitung jumlah kolom secara inkremental, bukan dari nol
- [ ] Memperkirakan apakah O(R^2 * C) lolos untuk batas yang diberikan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca matriks

    // TODO: untuk setiap batas atas, reset array kolom

    // TODO: untuk setiap batas bawah, tambahkan barisnya ke array kolom,
    //       lalu jalankan Kadane pada array kolom

    return 0;
}
