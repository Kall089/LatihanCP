/*
============================================================
🏋️ Exercise 1: Arus Logistik Berkas Besar (Grid Min Path O(M) Space)
============================================================
Day: 153 | Difficulty: Easy | Topic: 1D Rolling Array on Grid DP
Source: Classic Grid DP / Memory-Constrained DP
Time Limit: 2.0 detik | Memory Limit: 64 MB

📋 PROBLEM STATEMENT:
Sebuah perusahaan logistik ingin mengirimkan paket melintasi peta berukuran N baris dan M kolom.
Setiap sel (r, c) memiliki biaya melintas sebesar grid[r][c].
Perjalanan dimulai dari pojok kiri atas (0, 0) dan berakhir di pojok kanan bawah (N-1, M-1).
Dari setiap sel, rute hanya boleh bergerak ke Kanan (r, c + 1) atau ke Bawah (r + 1, c).
Biaya total adalah jumlah seluruh sel yang dilewati, termasuk sel awal dan akhir.

Karena ukuran grid sangat besar (N, M hingga 2.000) dan batas memori sangat ketat (64 MB),
kamu DILARANG menyimpan seluruh grid berukuran N x M ke dalam memori!
Selesaikan masalah ini dengan menggunakan array DP 1D berukuran paling banyak O(M)
dan proses input baris demi baris secara streaming (langsung).
Kamu hanya diminta mencetak biaya minimum; jalur langkah tidak perlu dicetak.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan M.
- N baris berikutnya masing-masing berisi M bilangan bulat non-negatif menyatakan biaya sel.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: biaya jalur minimum dari (0, 0) ke (N-1, M-1).

📏 CONSTRAINTS:
- 1 <= N, M <= 2.000
- 0 <= grid[r][c] <= 1.000.000.000
- Memori algoritma harus O(M) (maksimal satu baris DP).

📎 SAMPLE INPUT 1:
2 3
1 7 1
2 1 1

📎 SAMPLE OUTPUT 1:
5

[Penjelasan Sample 1:
Jalur optimal: (0,0)[1] -> Bawah -> (1,0)[2] -> Kanan -> (1,1)[1] -> Kanan -> (1,2)[1].
Total biaya = 1 + 2 + 1 + 1 = 5.]

📎 SAMPLE INPUT 2:
1 1
1000000000

📎 SAMPLE OUTPUT 2:
1000000000

[Penjelasan Sample 2:
Hanya ada 1 sel. Biaya sama dengan nilai sel itu sendiri.]

📎 SAMPLE INPUT 3:
1 4
1 2 3 4

📎 SAMPLE OUTPUT 3:
10

[Penjelasan Sample 3:
Hanya ada 1 baris. Seluruh sel harus dilewati: 1 + 2 + 3 + 4 = 10.]

💡 HINT:
- Gunakan satu vector `dp` berukuran M bertipe `long long`.
- Saat membaca baris ke-i dan kolom ke-j:
  - Sebelum sel (i, j) diproses, `dp[j]` masih berisi nilai optimal dari sel atas (i - 1, j).
  - Sel kiri (i, j - 1) sudah diperbarui dan tersimpan di `dp[j - 1]`.
  - Maka: `dp[j] = val + min(dp[j], dp[j - 1])`.
- Hati-hati dengan base case pada sel (0, 0), baris pertama (i = 0), dan kolom pertama (j = 0).

🎯 Learning Goals:
- [ ] Mereduksi memori grid 2D dari O(N*M) menjadi O(M) dengan pemrosesan streaming.
- [ ] Memahami invariant sel atas (lama) dan sel kiri (baru) dalam satu array 1D.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Selesaikan Grid Min Path dengan memori O(M)
    // 1. Alokasikan vector<ll> dp(m)
    // 2. Baca sel per baris dan lakukan update in-place

    return 0;
}
