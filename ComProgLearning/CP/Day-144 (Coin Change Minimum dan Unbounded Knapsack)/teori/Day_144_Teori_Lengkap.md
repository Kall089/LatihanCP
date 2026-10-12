# 📊 Day 144: Coin Change Minimum & Unbounded Knapsack

**Hari**: Day 144 dari 308 Hari Competitive Programming  
**Topik**: Dynamic Programming — Coin Change Minimum, Unbounded Knapsack, & Rekonstruksi Solusi  
**Prasyarat**: Prinsip DP (Day 141), Desain State (Day 142), DP Linear 1D (Day 143)  
**Difficulty**: ⭐⭐  
**Learning Objectives**:
- Memahami karakteristik masalah **Unbounded Knapsack** di mana setiap elemen/koin tersedia dalam jumlah tak terbatas.
- Menguasai rekurens dan transisi **Coin Change Minimum** beserta penanganan inisialisasi tak terhingga (`INF`).
- Membuktikan secara formal mengapa pendekatan **Greedy gagal** pada sistem koin umum dan kapan DP wajib digunakan.
- Menguasai **Hukum Arah Loop (Forward vs Backward Loop)**: perbedaan mendasar loop maju (unbounded) vs loop mundur (0/1 knapsack).
- Mampu melakukan **rekonstruksi solusi** menggunakan pointer keputusan (`pick` / `parent array`) untuk mencetak koin-koin penyusun.
- Membedakan dengan tegas antara **Coin Combinations I (Permutasi)** dan **Coin Combinations II (Kombinasi)** melalui pengaturan urutan *nested loop*.
- Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 🔍 1. Konsep & Intuisi

### 1.1 Apa itu Unbounded Knapsack & Coin Change?

Dalam kehidupan sehari-hari maupun pemrograman kompetitif, kita sering menemui masalah optimasi dengan sumber daya yang **tidak terbatas**:
- Menukar uang sejumlah nominal $X$ menggunakan pecahan koin yang tersedia tanpa batas di laci kasir.
- Mengisi kapasitas wadah $W$ dengan beberapa jenis barang berbobot $w_i$ dan bernilai $v_i$, di mana setiap jenis barang dapat diproduksi atau diambil berulang kali sebanyak yang kita inginkan.

Karakteristik inilah yang mendefinisikan keluarga masalah **Unbounded Knapsack** (Knapsack Tak Berbatas):
$$\text{Persediaan per item } i = \infty \quad (\text{atau minimal } \lfloor W / w_i \rfloor)$$

Hal ini kontras dengan **0/1 Knapsack** (Day 145), di mana setiap item hanya boleh diambil paling banyak **satu kali** (pilihan biner: ambil atau tidak).

```
0/1 Knapsack:        Barang A (stok: 1)  ──►  Boleh diambil 0 atau 1 kali
Unbounded Knapsack:  Barang A (stok: ∞)  ──►  Boleh diambil 0, 1, 2, 3, ... kali
```

### 1.2 Masalah Coin Change Minimum

Diberikan sebuah himpunan koin $C = \{c_1, c_2, \dots, c_N\}$ dan sebuah nominal target $X$. Kita ingin mencari **jumlah koin paling sedikit** yang jika dijumlahkan bernilai tepat $X$. Jika nominal $X$ tidak mungkin dibentuk oleh kombinasi koin yang ada, laporkan `-1`.

#### Definisi State DP
Misalkan:
$$\text{dp}[i] = \text{jumlah koin minimum untuk membentuk nominal tepat } i$$

#### Transisi Rekurens
Untuk membentuk nominal $i$, pertimbangkan koin terakhir apa yang kita pasang. Jika koin terakhir yang kita ambil bernilai $c$, maka sebelum mengambil koin tersebut kita harus sudah membentuk nominal $(i - c)$ dengan koin sesedikit mungkin:
$$\text{dp}[i] = \min_{c \in C, \, c \le i} \Big( \text{dp}[i - c] + 1 \Big)$$

#### Base Case & Nilai Awal
- $\text{dp}[0] = 0$: Membentuk nominal $0$ membutuhkan tepat $0$ koin.
- Untuk $i > 0$, $\text{dp}[i] = \infty$ (di kode diwakili bilangan besar seperti `1e9 + 7`). Ini menandakan bahwa pada awalnya nominal tersebut belum diketahui apakah bisa dicapai atau belum.

```
       +---+---+---+---+---+---+---+
dp[i]: | 0 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ |
       +---+---+---+---+---+---+---+
  i:     0   1   2   3   4   5   6
```

---

## ⚠️ 2. Kenapa Pendekatan Greedy Gagal?

Banyak pemula tergoda untuk menyelesaikan masalah koin dengan strategi **Greedy**: *"Selalu ambil koin dengan pecahan terbesar yang tidak melebihi sisa nominal."*

Strategi ini **salah** untuk sistem koin umum!

### Bukti Penyangkal (Counterexample)

Misalkan kita memiliki pecahan koin $C = \{1, 3, 4\}$ dan ingin membentuk nominal $X = 6$.

1. **Hasil Algoritma Greedy**:
   - Ambil koin terbesar $\le 6$: pilih **4**. Sisa nominal = $6 - 4 = 2$.
   - Ambil koin terbesar $\le 2$: pilih **1**. Sisa nominal = $2 - 1 = 1$.
   - Ambil koin terbesar $\le 1$: pilih **1**. Sisa nominal = $1 - 1 = 0$.
   - **Total koin Greedy**: $4 + 1 + 1 \implies \mathbf{3\text{ koin}}$.

2. **Hasil Optimal Dynamic Programming**:
   - DP mengevaluasi seluruh kemungkinan transisi.
   - Pilihan: ambil koin **3**, sisa nominal $6 - 3 = 3$.
   - Ambil koin **3** lagi, sisa nominal $3 - 3 = 0$.
   - **Total koin Optimal**: $3 + 3 \implies \mathbf{2\text{ koin}}$.

```
Greedy:  [4] ──► [1] ──► [1]   (3 koin)  ❌ Suboptimal
DP:      [3] ──► [3]           (2 koin)  ✅ OPTIMAL
```

### Kapan Greedy Aman?
Greedy hanya dijamin optimal pada **Sistem Koin Kanonik** (*Canonical Coin System*), seperti pecahan mata uang Rupiah standar $\{100, 200, 500, 1000\}$ atau koin Amerika Serikat $\{1, 5, 10, 25\}$. Namun, dalam Competitive Programming, jenis koin selalu arbitrer. **Gunakan selalu DP kecuali ada bukti matematika tegas bahwa sistem koin tersebut kanonik.**

---

## 🔄 3. Hukum Arah Loop: Forward vs Backward Loop

Salah satu konsep paling krusial di seluruh topik Dynamic Programming adalah memahami bagaimana **arah iterasi loop kapasitas** menentukan apakah sebuah barang boleh diambil berkali-kali (*unbounded*) atau hanya sekali (*0/1*).

Perhatikan kedua cuplikan kode C++ berikut:

```cpp
// 1. Unbounded Knapsack (Barang boleh diambil BERKALI-KALI)
for (int i = 0; i < N; i++) {
    for (int w = wt[i]; w <= W; w++) { // LOOP MAJU (Forward)
        dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }
}

// 2. 0/1 Knapsack (Barang hanya boleh diambil MAKSIMAL 1 KALI)
for (int i = 0; i < N; i++) {
    for (int w = W; w >= wt[i]; w--) { // LOOP MUNDUR (Backward)
        dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }
}
```

Hanya satu kata yang berubah: **arah loop `w`**! Mengapa efeknya begitu drastis?

### Penjelasan Mekanisme Memori:

#### Kasus Loop MAJU (`w = wt` naik hingga `W`):
Saat kita berada pada kapasitas $w$, nilai submasalah yang kita akses, yaitu `dp[w - wt]`, **sudah dihitung dan diperbarui pada iterasi barang yang sama**.
Artinya, jika barang $i$ sudah dimasukkan saat menghitung kapasitas $(w - wt)$, maka ketika kita menghitung kapasitas $w$, barang $i$ tersebut **bisa dimasukkan lagi**!
Hal ini secara otomatis mengizinkan penggunaan item berulang kali ($1\times, 2\times, 3\times, \dots$).

#### Kasus Loop MUNDUR (`w = W` turun hingga `wt`):
Saat kita berada pada kapasitas $w$, nilai submasalah `dp[w - wt]` **belum tersentuh sama sekali pada iterasi barang ke-$i$ saat ini**.
Nilai `dp[w - wt]` murni berasal dari hasil barang-barang sebelumnya ($i - 1$).
Akibatnya, barang ke-$i$ tidak mungkin dimasukkan lebih dari satu kali!

### Uji Mandiri Cepat:
Misalkan terdapat 1 barang dengan bobot $wt = 2$ dan nilai $val = 3$. Kapasitas ransel $W = 6$.
- **Versi Mundur (0/1)**:
  `dp[6] = max(dp[6], dp[4] + 3) = 3` (karena `dp[4]` saat itu masih bernilai 0).
  Barang hanya terpakai 1 kali. Hasil akhir = $3$.
- **Versi Maju (Unbounded)**:
  - `w = 2`: `dp[2] = dp[0] + 3 = 3`
  - `w = 4`: `dp[4] = dp[2] + 3 = 6`
  - `w = 6`: `dp[6] = dp[4] + 3 = 9`
  Barang terpakai 3 kali ($2+2+2 = 6$). Hasil akhir = $9$.

```
KAPASITAS:    0    1    2    3    4    5    6
Loop Mundur: [0]  [0]  [3]  [3]  [3]  [3]  [3]  ──► Barang hanya 1x
Loop Maju:   [0]  [0]  [3]  [3]  [6]  [6]  [9]  ──► Barang terpakai 3x
```

---

## 🧮 4. Simulasi & Trace Step-by-Step

Mari kita lakukan simulasi langsung untuk masalah **Coin Change Minimum** dengan input:
- Koin $C = \{1, 3, 4\}$
- Target nominal $X = 6$

Inisialisasi tabel DP:
$$\text{dp}[0] = 0, \quad \text{dp}[1 \dots 6] = \infty$$

| $i$ (Nominal) | Kandidat Transisi ($i - c$) | Perhitungan $\min$ | Nilai $\text{dp}[i]$ | Penjelasan / Koin Dipakai |
|---|---|---|---|---|
| **0** | - | Base case | **0** | Tidak butuh koin |
| **1** | $c=1: \text{dp}[0] + 1 = 1$ | $\min(1) = 1$ | **1** | $\{1\}$ |
| **2** | $c=1: \text{dp}[1] + 1 = 2$ | $\min(2) = 2$ | **2** | $\{1, 1\}$ |
| **3** | $c=1: \text{dp}[2] + 1 = 3$<br>$c=3: \text{dp}[0] + 1 = 1$ | $\min(3, 1) = 1$ | **1** | $\{3\}$ (langsung pakai koin 3) |
| **4** | $c=1: \text{dp}[3] + 1 = 2$<br>$c=3: \text{dp}[1] + 1 = 2$<br>$c=4: \text{dp}[0] + 1 = 1$ | $\min(2, 2, 1) = 1$ | **1** | $\{4\}$ (langsung pakai koin 4) |
| **5** | $c=1: \text{dp}[4] + 1 = 2$<br>$c=3: \text{dp}[2] + 1 = 3$<br>$c=4: \text{dp}[1] + 1 = 2$ | $\min(2, 3, 2) = 2$ | **2** | $\{1, 4\}$ atau $\{4, 1\}$ |
| **6** | $c=1: \text{dp}[5] + 1 = 3$<br>$c=3: \text{dp}[3] + 1 = 2$<br>$c=4: \text{dp}[2] + 1 = 3$ | $\min(3, 2, 3) = 2$ | **2** | $\{3, 3\}$ **(Optimal!)** |

Hasil akhir: $\text{dp}[6] = 2$ koin (yaitu pecahan $3 + 3$).

---

## 🛠️ 5. Rekonstruksi Solusi (Backtracking / Decision Pointer)

Mengetahui *berapa* koin minimum seringkali belum cukup; kita sering diminta mencetak *koin apa saja* yang digunakan.

### Mekanisme Array `pick` (atau `parent`):
1. Buat array `pick` berukuran $X + 1$, diinisialisasi dengan $-1$.
2. Setiap kali nilai $\text{dp}[i]$ diperbarui dengan koin $c$, catat koin tersebut:
   ```cpp
   if (dp[i - c] + 1 < dp[i]) {
       dp[i] = dp[i - c] + 1;
       pick[i] = c; // Catat bahwa nominal i tercapai dengan menambahkan koin c
   }
   ```
3. Untuk merekonstruksi, mulai dari target $X$ dan telusuri mundur hingga mencapai $0$:
   ```cpp
   int curr = X;
   vector<int> coins_used;
   while (curr > 0) {
       int c = pick[curr];
       coins_used.push_back(c);
       curr -= c;
   }
   ```

```
curr = 6 ──(pick[6] = 3)──► sisa = 3 ──(pick[3] = 3)──► sisa = 0 (Selesai!)
Koin penyusun: 3, 3.
```

---

## 🎭 6. Empat Varian Penting Keluarga Soal

Perhatikan perbedaan mendasar pada struktur loop dan base case untuk 4 varian utama:

| Varian Masalah | Posisi Loop Koin vs Nominal | Arah Loop Kapasitas | Base Case | Relasi Transisi |
|---|---|---|---|---|
| **Coin Change Min** | Bebas (biasanya nominal di luar) | Maju | `dp[0]=0`, lainnya $\infty$ | `min(dp[i], dp[i-c] + 1)` |
| **Unbounded Knapsack** | Koin/Item di luar, kapasitas di dalam | Maju ($wt \to W$) | `dp[0...W] = 0` | `max(dp[w], dp[w-wt] + val)` |
| **Coin Combinations I (Permutasi)** | **Nominal di LUAR**, Koin di DALAM | Maju ($1 \to X$) | `dp[0] = 1`, lainnya $0$ | `dp[i] = (dp[i] + dp[i-c]) % MOD` |
| **Coin Combinations II (Kombinasi)** | **Koin di LUAR**, Nominal di DALAM | Maju ($c \to X$) | `dp[0] = 1`, lainnya $0$ | `dp[i] = (dp[i] + dp[i-c]) % MOD` |

### Penjelasan Kritis: Permutasi vs Kombinasi
- **Permutasi (Urutan penting)**:
  Susunan $\{1, 3\}$ dan $\{3, 1\}$ dianggap **dua cara berbeda**.
  Dengan meletakkan loop nominal di luar, pada setiap nominal kita bebas memilih koin apa pun sebagai koin terakhir.
- **Kombinasi (Urutan tidak penting)**:
  Susunan $\{1, 3\}$ dan $\{3, 1\}$ dianggap **satu cara yang sama**.
  Dengan meletakkan loop koin di luar, kita memproses semua penggunaan koin jenis $1$, kemudian koin jenis $2$, dst. Koin yang sudah lewat tidak akan pernah dipilih lagi di belakang koin jenis baru, sehingga tidak akan pernah terjadi permutasi berulang!

---

## 💻 7. Implementasi Standar C++17

Berikut adalah implementasi acuan untuk **Minimizing Coins**:

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    // Optimasi Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    // dp[i] menyimpan koin minimum untuk membentuk nominal i
    vector<int> dp(x + 1, INF);
    dp[0] = 0; // Base case: nominal 0 butuh 0 koin

    for (int i = 1; i <= x; i++) {
        for (int c : coins) {
            // WAJIB: cek i >= c dan cek dp[i - c] != INF agar tidak overflow
            if (i >= c && dp[i - c] != INF) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }

    // Jika dp[x] tetap INF, berarti mustahil dibentuk
    if (dp[x] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[x] << "\n";
    }

    return 0;
}
```

---

## ⚠️ 8. Common Mistakes & Edge Cases

1. **Integer Overflow pada Penjumlahan INF**:
   Jika `INF` diatur ke `INT_MAX` ($2^{31}-1$), maka operasi `dp[i - c] + 1` akan mengalami overflow menjadi bilangan negatif sangat kecil, sehingga `min(...)` akan memilih nilai negatif palsu tersebut.
   *Solusi*: Gunakan `INF = 1e9 + 7` atau selalu pasang guard: `if (dp[i - c] != INF)`.

2. **Inisialisasi Base Case Salah**:
   Lupa mengeset `dp[0] = 0` atau secara keliru menginisialisasi seluruh array dengan 0. Jika seluruh array diinisialisasi 0, program akan selalu menjawab 0 koin untuk nominal apa pun.

3. **Target $X = 0$**:
   Jika target $X = 0$, jawabannya adalah `0` koin. Pastikan kode menangani kasus ini dengan benar tanpa mencetak `-1`.

4. **Koin Berulang atau Koin 0**:
   Jika input mengandung koin bernilai 0, loop transisi `i - c` bisa mengalami *infinite loop* atau pembagian dengan nol. Di CP, batasan koin umumnya $c_i \ge 1$.

5. **Salah Arah Loop Kapasitas**:
   Membuat loop mundur pada Unbounded Knapsack akan mengubah logika menjadi 0/1 Knapsack tanpa menghasilkan pesan kompilasi error (silent bug).

---

## 🏆 9. Tips Kontes

1. **Cek Batasan $N$ dan $X$**:
   - Jika $N \le 100$ dan $X \le 10^6$, kompleksitas waktu adalah $O(N \times X) \approx 10^8$ operasi, yang memakan waktu $\approx 0.1 - 0.3$ detik di server judge modern.
   - Jika $X \le 10^{18}$ tetapi $N$ kecil ($N \le 3$), jangan gunakan DP tabel biasa! Gunakan matematika (Extended Euclidean) atau BFS modulo koin terkecil (*Shortest Path Faster Algorithm / Dijkstra on Modulo*).
2. **Kombinasi vs Permutasi**:
   Baca baik-baik deskripsi soal: apakah urutan pemilihan koin membedakan cara pembayaran?
   - "Order matters" $\implies$ Permutasi (Nominal di loop luar).
   - "Distinct combinations" $\implies$ Kombinasi (Koin di loop luar).

---

## 📌 10. Ringkasan & Tautan Latihan

- **Unbounded Knapsack**: Barang boleh diambil berkali-kali $\implies$ **Loop Maju**.
- **0/1 Knapsack**: Barang maksimal 1 kali $\implies$ **Loop Mundur**.
- **Coin Change Min**: Inisialisasi `INF`, base `dp[0] = 0`, transisi `min`.
- **Rekonstruksi**: Gunakan array `pick[i]` untuk mencatat koin pemenang dan lacak balik dari $X \to 0$.

### Rekomendasi Soal Online Judge:
- **CSES**: [Minimizing Coins](https://cses.fi/problemset/task/1634)
- **CSES**: [Coin Combinations I](https://cses.fi/problemset/task/1635)
- **CSES**: [Coin Combinations II](https://cses.fi/problemset/task/1636)
- **LeetCode**: [322. Coin Change](https://leetcode.com/problems/coin-change/)
- **LeetCode**: [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/)
- **AtCoder**: [Educational DP Contest - Knapsack 2](https://atcoder.jp/contests/dp/tasks/dp_e)
