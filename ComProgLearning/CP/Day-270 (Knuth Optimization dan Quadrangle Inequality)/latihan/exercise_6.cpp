/*
============================================================
🏋️ Exercise 6: Penggabungan File Arsip dengan Faktor Kompresi
============================================================
Day: 270 | Difficulty: Menantang | Topic: Knuth Optimization (Weighted Sequential Merge)
Source: Archive File Merging Optimization
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N berkas arsip berurutan bernomor 1 sampai N dengan ukuran data s[0], ..., s[N-1].
Seluruh berkas harus digabungkan menjadi satu arsip utama melalui penggabungan berkas-berkas bersebelahan.
Sistem pengarsipan menerapkan faktor kompresi M.
Setiap kali dua segmen arsip bersebelahan [l..k] dan [k+1..r] digabungkan, biaya operasi kompresi adalah:
`Cost(l, r) = M * (sum_{t=l}^r s[t])`.
Urutan berkas tidak boleh diubah.

Tentukan TOTAL BIAYA KOMPRESI MINIMUM untuk menggabungkan seluruh berkas menjadi satu!

Selesaikan dengan KNUTH OPTIMIZATION dalam waktu O(N^2)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan M.
- Baris kedua berisi N bilangan bulat non-negatif s[0], ..., s[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi total biaya minimum.

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= M <= 10.000
- 0 <= s[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4 3
4 1 2 3

📎 SAMPLE OUTPUT 1:
57

[Penjelasan Sample 1:
Jika tanpa faktor M (M=1), biaya minimum adalah 19.
Dengan faktor M = 3, biaya tiap penggabungan dikalikan 3, sehingga total biaya minimum adalah 19 * 3 = 57.]

📎 SAMPLE INPUT 2:
1 10
100

📎 SAMPLE OUTPUT 2:
0

💡 HINT:
- Perkalian dengan skalar konstan positif M mempertahankan sifat Quadrangle Inequality:
  `M * (C(a, c) + C(b, d)) = M * (C(a, d) + C(b, c))`.
- Gunakan Knuth Optimization persis seperti pada Exercise 1 dengan mengalikan biaya interval dengan M.

🎯 Learning Goals:
- [ ] Memahami invarian skala linier positif terhadap Quadrangle Inequality.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
