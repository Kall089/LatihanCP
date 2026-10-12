# Cara mengenali soal dari batasan

[← 00-peta](README.md) · [Kata kunci →](kata-kunci.md) · [Indeks CP](../README.md)

**Teori:** Waktu 1–2 detik C++ kira-kira **10⁸ operasi sederhana**. Pilih algoritma dari `n`, bukan dari perasaan. Kalau `n` menolak O(n²), jangan mulai menulis dua loop “dulu coba”.

**Kapan:** selalu, sebelum mengetik. **Tidak:** soal interaktif yang anggarannya tertulis terpisah — itu batas *tanya*, bukan batas *n*.

## Tabel constraint

| n (atau n·m) | Yang muat | Folder |
|---|---|---|
| ≤ 10 | n!, 2^n · n² longgar | [05-rekursi](../05-rekursi/README.md) |
| ≤ 20 | 2^n, 2^n · n, TSP | [09-dp/15](../09-dp/15-bitmask-tsp.md) |
| ≤ 40 | MITM 2^(n/2) | [04 meet-in-middle](../04-sorting-searching/meet-in-the-middle.md) |
| ≤ 80–90 | Floyd n³, DP n³ ketat | [08 floyd](../08-graf/bellman-floyd.md), [09 range](../09-dp/11-range.md) |
| ≤ 400 | n³ longgar | range DP, Floyd |
| ≤ 2000 | n², n² log n pas | [09 LCS](../09-dp/09-lcs-edit.md), knapsack 2D |
| ≤ 1e5 | n log n, n √n hati-hati | sort, BIT, SegTree, two pointers |
| ≤ 2e5 | n log n, hindari √n berat | sama |
| ≤ 1e6 | n, n log n ketat | sieve, prefix, two pointers |
| ≤ 1e7 | hampir hanya O(n) | linear sieve, Z, KMP |
| ≤ 1e18 | log n, matrix expo, math | [07 matrix](../07-number-theory/matrix-xor.md) |

**Proses:** soal menulis `1 ≤ n ≤ 2·10^5`, `1 ≤ q ≤ 2·10^5`, array berubah.

```
n = 2e5  → tolak O(n²)
ada update → prefix statis tidak cukup
query jumlah → Fenwick atau SegTree
```

Buka [10 Fenwick](../10-struktur-data/fenwick.md) atau [SegTree](../10-struktur-data/segment-tree.md).

**Jebakan:** `t` test case. Total `sum n` yang dihitung, bukan `n` satu tes. `n ≤ 100` tapi `t ≤ 1e5` bisa tetap TLE.

**Kompleksitas:** anggap 2 detik ≈ 1e8–2e8. `O(n log n)` untuk n=2e5 ≈ 3.6e6, aman. `O(n √n)` ≈ 6e7, pas. `O(n²)` = 4e10, mustahil.

## Ada update atau tidak

| Data | Query | Senjata |
|---|---|---|
| tetap | jumlah `[l,r]` | [prefix](../03-array/prefix-difference.md) |
| tetap | min/max/gcd `[l,r]` | [Sparse Table](../10-struktur-data/sparse-table.md) |
| update titik | jumlah prefix | [Fenwick](../10-struktur-data/fenwick.md) |
| update titik | min / gabungan lain | [SegTree](../10-struktur-data/segment-tree.md) |
| update rentang | jumlah/min | [lazy](../10-struktur-data/lazy.md) |
| banyak query offline, unik | Mo | [Mo](../10-struktur-data/mo.md) |

## Graf atau bukan

| Kalimat | Arah |
|---|---|
| kota, jalan, persahabatan | [08-graf](../08-graf/README.md) |
| jarak, bobot ≥ 0 | [Dijkstra](../08-graf/dijkstra.md) |
| ada bobot negatif | [Bellman](../08-graf/bellman-floyd.md) |
| “minimal sisi agar terhubung” | [MST](../08-graf/dsu-mst.md) |
| syarat “A atau B” | [2-SAT](../08-graf/two-sat.md) |
| kapasitas pipa | [Dinic](../08-graf/dinic.md) |
| pohon (n-1 sisi, terhubung) | [11-pohon](../11-pohon/README.md) |

## DP atau greedy

Tulis satu keputusan greedy. Coba tukar dua pilihan. Kalau ada counterexample kecil, itu DP.

| Gejala | File |
|---|---|
| ambil / tidak, kapasitas | [knapsack](../09-dp/05-01-knapsack.md) |
| dua string | [LCS](../09-dp/09-lcs-edit.md) |
| n ≤ 20 himpunan | [TSP](../09-dp/15-bitmask-tsp.md) |
| angka 1..R syarat digit | [digit DP](../09-dp/18-digit.md) |
| interval, bukti tukar | [greedy](../06-greedy/interval-exchange.md) |

Contoh greedy gagal: koin `{1,3,4}` target `6`. Greedy 4+1+1 = 3 koin, optimal 3+3 = 2. Jejak lengkap: [04-coin](../09-dp/04-coin-unbounded.md).

## Kode: baca constraint lalu tolak

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool muat_n2(ll n) {
    return n <= 2000;
}

bool muat_nlogn(ll n) {
    return n <= 400000;
}

string pilih_jumlah_rentang(bool ada_update, bool data_tetap) {
    if (!ada_update && data_tetap) return "prefix";
    if (ada_update) return "fenwick_atau_segtree";
    return "sparse_atau_prefix";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n = 200000;
    cout << (muat_n2(n) ? "boleh n^2\n" : "tolak n^2\n");
    cout << pilih_jumlah_rentang(true, false) << '\n';
}
```

**Jebakan:** memori. `int dp[4000][4000]` ≈ 64 MB. `ll dp[5000][5000]` ≈ 200 MB, sering MLE. `vector<vector<int>>` lebih boros karena pointer.

**Kompleksitas memori:** 64 MB ≈ 1.6e7 `int`. Hitung sebelum alokasi 2D besar.
