/*
============================================================
🏋️ Exercise 4: Rekonstruksi Kurung Perkalian Matriks
============================================================
Day: 151 | Difficulty: Medium-Hard | Topic: Range DP Reconstruction
Source: Classic Matrix Chain Parenthesization / CLRS
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Selain mengetahui jumlah perkalian skalar minimum, seorang perekayasa perangkat lunak
juga harus mengetahui BAGAIMANA cara mengelompokkan tanda kurung pada rantai perkalian matriks
A[1] * A[2] * ... * A[N].

Diberikan N matriks berukuran p[i-1] x p[i].
Cari:
1. Di baris pertama: biaya perkalian skalar minimum.
2. Di baris kedua: ekspresi string tanda kurung optimal dengan aturan:
   - Matriks ke-i (1-indexed) ditulis sebagai `A` diikuti nomor indeksnya, misal `A1`, `A2`, dst.
   - Ketika dua sub-ekspresi L dan R dikalikan, gabungkan dengan format `(L x R)`.
   - Untuk matriks tunggal N = 1, cukup cetak `A1` tanpa kurung.
   - Jika ada beberapa cara pengelompokan yang menghasilkan nilai minimum yang sama,
     pilih titik pecah k terkecil (tie-breaker: minimal k).

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N + 1 bilangan bulat p[0], p[1], ..., p[N].

📤 OUTPUT FORMAT:
- Baris pertama: jumlah perkalian skalar minimum.
- Baris kedua: string ekspresi pengelompokan tanda kurung optimal.

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= p[i] <= 10.000

📎 SAMPLE INPUT 1:
3
10 30 5 60

📎 SAMPLE OUTPUT 1:
4500
((A1 x A2) x A3)

[Penjelasan Sample 1:
Optimal split pertama ada di k = 2 (memisahkan matriks 1..2 dan matriks 3).
Sub-ekspresi matriks 1..2 adalah (A1 x A2).
Lalu dikalikan dengan A3 menghasilkan ((A1 x A2) x A3).]

📎 SAMPLE INPUT 2:
1
15 20

📎 SAMPLE OUTPUT 2:
0
A1

[Penjelasan Sample 2: Matriks tunggal tidak memerlukan operasi penggabungan apa pun.]

📎 SAMPLE INPUT 3:
4
5 10 3 12 5

📎 SAMPLE OUTPUT 3:
405
((A1 x A2) x (A3 x A4))

💡 HINT:
- Simpan array titik pecah terbaik: `split[l][r] = k_terbaik`.
- Gunakan fungsi rekursif `buildExpr(l, r)`:
  - Jika l == r, return "A" + to_string(l + 1).
  - Jika tidak, return "(" + buildExpr(l, split[l][r]) + " x " + buildExpr(split[l][r] + 1, r) + ")".

🎯 Learning Goals:
- [ ] Menerapkan pelacakan keputusan (backtracking) pada tabel Range DP.
- [ ] Membentuk struktur pohon sintaks / ekspresi tanda kurung dari tabel DP 2D.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    // TODO: Selesaikan MCM dan Rekonstruksi Tanda Kurung
    // 1. Simpan split[l][r] saat menemukan cost yang lebih kecil
    // 2. Fungsi rekursif rekonstruksi string tanda kurung
    // 3. Cetak dp[0][n-1] dan string hasil

    return 0;
}
