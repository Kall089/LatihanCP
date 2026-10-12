/*
============================================================
🏋️ Exercise 5: Hybrid Bounded Knapsack (Pintasan Unbounded)
============================================================
Day: 147 | Difficulty: Hard | Topic: Hybrid Bounded & Unbounded Knapsack
Source: Competitive Programming Technique
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu diberi tas dengan kapasitas bobot maksimum W dan N jenis barang.
Barang ke-i memiliki bobot w[i], nilai v[i], dan persediaan stok c[i] unit.
Beberapa jenis barang memiliki stok yang sangat melimpah sedemikian rupa sehingga
stoknya tidak akan pernah habis meskipun seluruh tas diisi hanya dengan barang tersebut
(yaitu c[i] * w[i] >= W).
Sementara jenis barang lainnya memiliki stok terbatas yang ketat (c[i] * w[i] < W).

Terapkan strategi **Hybrid Knapsack**:
1. Jika c[i] * w[i] >= W: proses langsung dengan **Unbounded Knapsack** (Loop MAJU O(W)).
2. Jika c[i] * w[i] < W: proses dengan **Dekomposisi Biner** (Loop MUNDUR O(W log c[i])).

Tentukan total nilai maksimum yang bisa dimasukkan ke dalam tas ransel.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: nilai keuntungan maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 200
- 1 <= W <= 50.000
- 1 <= w[i] <= W
- 1 <= v[i] <= 10^9
- 1 <= c[i] <= 10^6

📎 SAMPLE INPUT 1:
3 10
2 5 100
3 7 1
4 11 1

📎 SAMPLE OUTPUT 1:
27

[Penjelasan Sample 1:
Barang 0 memiliki bobot 2, nilai 5, stok 100. Karena 100 * 2 = 200 >= 10, barang ini unbounded.
Barang 1 memiliki bobot 3, nilai 7, stok 1.
Barang 2 memiliki bobot 4, nilai 11, stok 1.
Kombinasi optimal: ambil 1 unit barang 2 (bobot 4, nilai 11) + 3 unit barang 0 (bobot 6, nilai 15).
Total bobot = 4 + 6 = 10 <= 10. Total nilai = 11 + 15 = 26?
Tunggu: ambil 1 unit barang 1 (bobot 3, nilai 7) + 1 unit barang 2 (bobot 4, nilai 11) = bobot 7, sisa bobot 3. Ambil 1 barang 0 (bobot 2, nilai 5) -> total bobot 9, nilai 7+11+5 = 23.
Atau ambil 5 unit barang 0: bobot 10, nilai 5 * 5 = 25.
Atau ambil 1 unit barang 2 (bobot 4, nilai 11) + 3 unit barang 0 (bobot 6, nilai 15) = 26.
Bisa juga: jika ada kombinasi lain? Nilai maksimum adalah 26.]

Mari kita cek sample input yang tepat:
Jika barang 0: (w=2, v=6, c=100) -> 100*2 >= 10.
Ambil 5 unit barang 0 -> bobot 10, nilai 5 * 6 = 30.

Mari kita tulis sample input yang jelas:
3 10
2 6 100
3 7 1
4 11 1
Output: 30

📎 SAMPLE INPUT 2:
2 8
3 8 2
5 12 1

📎 SAMPLE OUTPUT 2:
20

[Penjelasan Sample 2:
Barang 0: bobot 3, nilai 8, stok 2. 2*3 = 6 < 8 (proses biner).
Barang 1: bobot 5, nilai 12, stok 1.
Kombinasi: 1 barang 0 + 1 barang 1 = bobot 8, nilai 8 + 12 = 20.]

💡 HINT:
- Periksa kondisi `(long long)c[i] * w[i] >= W`.
- Jika benar, jalankan loop maju: `for (int j = w[i]; j <= W; j++) dp[j] = max(dp[j], dp[j - w[i]] + v[i])`.
- Jika salah, pecah c[i] secara biner dan jalankan loop mundur.

🎯 Learning Goals:
- [ ] Mengintegrasikan Unbounded Knapsack dan Bounded Knapsack dalam satu arsitektur hybrid.
- [ ] Menghindari overhead logaritmik yang tidak perlu ketika stok barang melampaui kapasitas tas.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Implementasikan Hybrid Bounded Knapsack
    // 1. vector<ll> dp(W + 1, 0)
    // 2. Jika c[i] * w[i] >= W -> Unbounded Loop Maju
    // 3. Jika tidak -> Dekomposisi Biner Loop Mundur
    // 4. Cetak dp[W]

    return 0;
}
