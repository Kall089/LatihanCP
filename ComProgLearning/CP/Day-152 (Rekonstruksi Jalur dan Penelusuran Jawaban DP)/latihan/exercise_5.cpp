/*
============================================================
🏋️ Exercise 5: Penjelajah Labirin Grid Berbobot (Grid Min Path Reconstruction)
============================================================
Day: 152 | Difficulty: Medium | Topic: 2D Grid DP + Path Reconstruction
Source: Classic Grid DP / LeetCode 64 Variation
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang penjelajah labirin berada di sel pojok kiri atas (0, 0) dari sebuah grid berukuran R x C.
Tujuannya adalah mencapai sel pojok kanan bawah (R - 1, C - 1).
Setiap sel (r, c) memiliki biaya lewat sebesar grid[r][c].

Dari posisi (r, c), penjelajah hanya boleh melangkah:
- Ke bawah (Down, disimbolkan karakter 'D') menuju (r + 1, c).
- Ke kanan (Right, disimbolkan karakter 'R') menuju (r, c + 1).

Total biaya perjalanan adalah jumlah biaya seluruh sel yang dilewati, termasuk sel awal (0, 0)
dan sel akhir (R - 1, C - 1).

Tentukan:
1. Di baris pertama: biaya total perjalanan minimum.
2. Di baris kedua: string arah langkah sepanjang (R + C - 2) yang memuat rangkaian 'D' dan 'R'.

Aturan Pemecah Seri (Tie-Breaker):
Jika ada lebih dari satu jalur yang menghasilkan total biaya minimum yang sama,
pilih jalur dengan string langkah yang TERKECIL SECARA LEKSIKOGRAFIS (di mana karakter 'D' < 'R').
Artinya, kita memprioritaskan melangkah ke bawah ('D') sedapat mungkin jika biayanya sama!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat R dan C.
- R baris berikutnya masing-masing berisi C bilangan bulat menyatakan nilai grid[r][c].

📤 OUTPUT FORMAT:
- Baris pertama: satu bilangan bulat, biaya perjalanan minimum.
- Baris kedua: string sepanjang (R + C - 2) berisi karakter 'D' dan 'R'.
  (Khusus jika R = 1 dan C = 1, baris kedua dicetak kosong).

📏 CONSTRAINTS:
- 1 <= R, C <= 1.000
- 0 <= grid[r][c] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 3
1 3 1
1 5 1
4 2 1

📎 SAMPLE OUTPUT 1:
7
DDRR

[Penjelasan Sample 1:
Jalur DDRR:
(0,0)[1] -> D -> (1,0)[1] -> D -> (2,0)[4] -> R -> (2,1)[2] -> R -> (2,2)[1].
Total biaya = 1 + 1 + 4 + 2 + 1 = 9.
Jalur lain:
(0,0)[1] -> D -> (1,0)[1] -> R -> (1,1)[5] -> ...
Jalur optimal:
(0,0)[1] -> R -> (0,1)[3] -> R -> (0,2)[1] -> D -> (1,2)[1] -> D -> (2,2)[1] = 1+3+1+1+1 = 7 (RRDD).
(0,0)[1] -> D -> (1,0)[1] -> D -> (2,0)[4] -> R -> (2,1)[2] -> R -> (2,2)[1] = 9.
(0,0)[1] -> D -> (1,0)[1] -> R -> (1,1)[5]...
Biaya minimum yang dicapai adalah 7 (lewat jalur 1 -> 3 -> 1 -> 1 -> 1 dengan langkah RRDD).
Jika ada seri antara DDRR dan RRDD, 'D' < 'R' akan memilih 'D'. Pada kasus ini 7 dicapai lewat RRDD.]

📎 SAMPLE INPUT 2:
1 1
42

📎 SAMPLE OUTPUT 2:
42
(baris kedua kosong)

📎 SAMPLE INPUT 3:
2 2
1 2
2 1

📎 SAMPLE OUTPUT 3:
4
DR

[Penjelasan Sample 3:
Dua jalur mungkin:
- DR: (0,0) -> D -> (1,0) -> R -> (1,1) : biaya 1 + 2 + 1 = 4.
- RD: (0,0) -> R -> (0,1) -> D -> (1,1) : biaya 1 + 2 + 1 = 4.
Keduanya berbiaya 4. Karena 'D' < 'R', maka jalur "DR" yang dipilih.]

💡 HINT:
- Gunakan Suffix DP pada grid:
  `dp[r][c]` = biaya minimum dari sel (r, c) menuju (R-1, C-1).
  dp[R-1][C-1] = grid[R-1][C-1].
  dp[r][c] = grid[r][c] + min(dp[r+1][c] [jika valid], dp[r][c+1] [jika valid]).
- Rekonstruksi Maju dari (0, 0):
  Saat berada di (r, c):
  Cek opsi 'D' (r + 1, c) terlebih dahulu!
  Jika r + 1 < R dan `dp[r][c] == grid[r][c] + dp[r+1][c]`:
    Ambil langkah 'D', update r = r + 1.
  Jika tidak:
    Ambil langkah 'R', update c = c + 1.

🎯 Learning Goals:
- [ ] Menerapkan Suffix DP pada grid 2D untuk deterministik leksikografis maju.
- [ ] Memahami penanganan batas tepi dan tie-breaker langkah grid ('D' vs 'R').
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    vector<vector<ll>> grid(r, vector<ll>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }

    // TODO: Selesaikan Grid Min Path Leksikografis
    // 1. Suffix dp[r][c] dari (R-1, C-1) ke (0, 0)
    // 2. Rekonstruksi maju dari (0, 0): utamakan 'D' daripada 'R'
    // 3. Cetak biaya dan string langkah

    return 0;
}
