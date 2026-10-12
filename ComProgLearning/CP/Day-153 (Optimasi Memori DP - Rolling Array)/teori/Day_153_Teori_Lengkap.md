# Day 153 — Optimasi Memori DP (Rolling Array, Penekanan Dimensi, dan Bitset)

> **Ide satu kalimat:** Optimasi memori DP memangkas tabel multidimensi yang besar menjadi 2 baris, 1 baris, atau beberapa variabel independen dengan memanfaatkan sifat lokal ketergantungan transisi (*state dependency window*), menghemat memori hingga 99% tanpa mengubah hasil akhir.

---

## 1. Motivasi: Mengapa Memori Bisa Meledak?

Batas memori standar pada *Online Judge* (Codeforces, AtCoder, TLX) umumnya berkisar antara **64 MB hingga 256 MB**.
Sementara itu, jumlah state DP bertambah secara multiplikatif ($N \times M$ atau $N \times W$).

### Skala Masalah:
Misalkan masalah 0/1 Knapsack dengan:
- $N = 1.000$ barang
- Kapasitas $W = 100.000$

| Tipe Implementasi | Rumus Alokasi | Ukuran Memori | Vonis Online Judge |
|---|---|---|---|
| **2D `long long`** | $1001 \times 100001 \times 8\text{ byte}$ | **~800 MB** | ❌ **Memory Limit Exceeded (MLE)** |
| **2D `int`** | $1001 \times 100001 \times 4\text{ byte}$ | **~400 MB** | ❌ **Memory Limit Exceeded (MLE)** |
| **Rolling 2 Baris** | $2 \times 100001 \times 8\text{ byte}$ | **~1.6 MB** | ✅ **Accepted (AC)** |
| **Rolling 1 Baris** | $1 \times 100001 \times 8\text{ byte}$ | **~0.8 MB** | ✅ **Accepted (AC)** |

> **Rumus Menghitung Memori (5 Detik Sebelum Ngetik):**
> $$\text{Memori} = \text{Jumlah State} \times \text{Ukuran Tipe Data}$$
> - `bool`: 1 byte (atau 1 bit dengan `std::bitset`)
> - `int` / `float`: 4 byte
> - `long long` / `double`: 8 byte
> 
> *Catatan:* Batas 256 MB setara dengan $\approx 3.2 \times 10^7$ elemen `long long` atau $6.4 \times 10^7$ elemen `int`.

---

## 2. Tiga Tingkat Penekanan Dimensi

Tingkat optimasi ditentukan langsung oleh pola pembacaan dependensi pada transisi rekurens DP:

```
[Tingkat 1: Dua Baris Bergantian (dp[2][M])]
Transisi dp[i][j] membaca dp[i-1][k] pada sembarang kolom k (kiri, atas, diagonal).
Contoh: LCS, Edit Distance, Grid Path jika ada dependensi acak.
                       │
                       ▼
[Tingkat 2: Satu Baris dengan Loop Arah Khusus (dp[W])]
Transisi dp[i][w] hanya membaca kolom lebih kecil (w - x) dari baris lama.
Contoh: 0/1 Knapsack (Loop Mundur), Unbounded Knapsack (Loop Maju).
                       │
                       ▼
[Tingkat 3: Variabel Lepas O(1) Memory]
Transisi dp[i] hanya membaca 1 atau 2 langkah konstan sebelumnya: dp[i-1], dp[i-2].
Contoh: Fibonacci, House Robber, Climbing Stairs, Buy/Sell Stock with Cooldown.
```

---

## 3. Tingkat 1: Dua Baris Bergantian (`dp[2][M]`)

### Kapan Digunakan?
Ketika baris $i$ membutuhkan nilai dari baris $i-1$ di kolom $j$, $j-1$, atau $j+1$ secara simultan, sehingga kita tidak bisa langsung menimpa sel dalam satu baris.
Contoh klasik: **Edit Distance** dan **Longest Common Subsequence (LCS)**.

### Implementasi Pola Swap vs Modulo Parity:
Ada dua cara umum:

#### Pola A: `vector<int> prev` dan `vector<int> cur` (Disarankan)
```cpp
vector<int> prev(m + 1, 0);
vector<int> cur(m + 1, 0);

for (int i = 1; i <= n; i++) {
    cur[0] = i; // inisialisasi kolom 0 baris ini
    for (int j = 1; j <= m; j++) {
        if (s[i - 1] == t[j - 1]) {
            cur[j] = prev[j - 1] + 1;
        } else {
            cur[j] = max(prev[j], cur[j - 1]);
        }
    }
    prev.swap(cur); // O(1) swap pointer
}
// Jawaban akhir ada di prev[m]
```

#### Pola B: Array Ukuran 2 dengan Bitwise AND (`i & 1`)
```cpp
int dp[2][MAX_M];
for (int i = 1; i <= n; i++) {
    int now = i & 1;
    int old = (i - 1) & 1;
    for (int j = 1; j <= m; j++) {
        // Gunakan dp[now][j] dan dp[old][j]
    }
}
```

---

## 4. Tingkat 2: Satu Baris 1D — Kenapa Arah Loop Sangat Krusial?

Pada Knapsack, kita mereduksi tabel $N \times W$ menjadi satu baris array `dp[W + 1]`.

```
        j=0   j=1   j=2   j=3   j=4   j=5
dp = [   0,    0,    0,    0,    0,    0   ]
```

### 0/1 Knapsack (Barang Hanya 1 Kali): Wajib LOOP MUNDUR
Ketika memproses barang berbobot $w = 2$ dan nilai $v = 3$:
Kita menghitung dari $j = 5$ turun ke $j = 2$:
$$dp[j] = \max(dp[j], dp[j - w] + v)$$

```
Saat j = 5: dp[5] = max(dp[5], dp[3] + 3) -> membaca dp[3] yang MASIH NILAI LAMA (belum ketimpa).
Saat j = 4: dp[4] = max(dp[4], dp[2] + 3) -> membaca dp[2] yang MASIH NILAI LAMA.
...
Saat j = 2: dp[2] = max(dp[2], dp[0] + 3).
```
Karena sel di sebelah kiri belum diperbarui, kita dijamin **tidak memakai barang yang sama berulang kali**!

### Unbounded Knapsack / Coin Change: Wajib LOOP MAJU
Jika barang boleh dipakai berkali-kali tanpa batas:
Kita menghitung dari $j = w$ maju ke $j = W$:
$$dp[j] = \max(dp[j], dp[j - w] + v)$$
Saat $j = 4$, ia membaca $dp[2]$ yang **sudah diperbarui** dengan barang ini, sehingga secara otomatis memperhitungkan pemakaian kedua, ketiga, dst.

| Tipe Knapsack | Arah Loop Kapasitas | Alasan Matematis |
|---|---|---|
| **0/1 Knapsack (Bounded 1x)** | **Mundur** ($W \to w_i$) | Menjaga $dp[j - w_i]$ tetap merepresentasikan baris $i-1$ |
| **Unbounded Knapsack** | **Maju** ($w_i \to W$) | Memungkinkan $dp[j - w_i]$ merepresentasikan barang $i$ dipakai lagi |

---

## 5. Tingkat 3: Variabel Lepas ($O(1)$ Memori)

Jika baris atau langkah saat ini hanya membutuhkan 1 atau 2 state langsung di belakangnya:
$$dp[i] = f(dp[i-1], dp[i-2])$$

Kita tidak perlu array apa pun:
```cpp
// House Robber / Fibonacci / Buy-Sell Stock
long long prev2 = 0; // dp[i-2]
long long prev1 = 0; // dp[i-1]

for (int x : nums) {
    long long cur = max(prev1, prev2 + x);
    prev2 = prev1;
    prev1 = cur;
}
return prev1;
```
Memori terpangkas dari $O(N)$ menjadi **$O(1)$**.

---

## 6. Akselerasi Ekstrem: `std::bitset` untuk DP Boolean

Pada masalah reachability (Subset Sum, Knapsack Boolean, Partition Problem):
Setiap sel hanya bernilai `true` (1) atau `false` (0).

Jika $W \le 100.000$, alih-alih `vector<bool>` yang memakan $100.000$ byte:
Gunakan `std::bitset<100001>`:
- **Ukuran Memori**: Hanya $\frac{100001}{8} \approx 12.5\text{ KB}$! (Hemat 8x lipat).
- **Kecepatan Komputasi**: Operasi bitwise `|= (bs << w)` memproses **64 bit sekaligus per instruksi CPU** (kecepatan naik $\approx 64\times$).

```cpp
bitset<100001> dp;
dp[0] = 1; // Base case: jumlah 0 selalu mungkin

for (int w : weights) {
    dp |= (dp << w); // Transisi 1 baris untuk seluruh kapasitas!
}
// dp[target] bernilai 1 jika target dapat dicapai.
```

---

## 7. Kapan DILARANG Menggunakan Rolling Array?

> ⚠️ **PERINGATAN KERAS: Jangan gunakan Rolling Array jika:**

1. **Soal Meminta Rekonstruksi Jalur Lengkap**:
   Rolling array menghancurkan riwayat transisi masa lalu. Tanpa riwayat tersebut, kamu tidak bisa menelusuri mundur (*backtrack*) barang mana saja yang terpilih atau rute mana yang dilalui!
   *(Kecuali menggunakan algoritma Divide and Conquer / Hirschberg's Algorithm yang kompleks).*
2. **Transisi Memiliki Lompatan Jauh Tak Menentu**:
   Jika $dp[i]$ bergantung pada $dp[i - k]$ di mana $k$ bervariasi dari $1$ sampai $i$, kamu wajib menyimpan seluruh prefix tabel.
3. **Range DP / Interval DP**:
   Interval DP ($dp[l][r]$) membutuhkan sub-interval dengan berbagai panjang, tidak dapat di-roll secara naif menjadi 1D.

---

## 8. Ringkasan Prinsip Optimasi Memori

1. **Hitung memori sebelum mengetik**: Pastikan alokasi di bawah batas memori soal.
2. **Lihat stensil transisi**:
   - Butuh kiri dan atas $\implies$ 2 baris (`prev` & `cur`).
   - Hanya butuh kiri $\implies$ 1 baris loop mundur.
   - Hanya butuh 1-2 tetangga konstan $\implies$ 2-3 variabel.
3. **Gunakan `swap()` pointer**, hindari meng-copy isi seluruh vector setiap iterasi.
4. Manfaatkan **`std::bitset`** untuk percepatan 64x pada DP boolean.
