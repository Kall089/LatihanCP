# Day 270 — Knuth Optimization dan Quadrangle Inequality

> **Ide satu kalimat:** Knuth Optimization memanfaatkan sifat *Quadrangle Inequality* pada fungsi biaya untuk membatasi titik pemisah optimal $opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$, mereduksi kompleksitas Range DP dari $\mathcal{O}(N^3)$ menjadi $\mathcal{O}(N^2)$ melalui argumen teleskopik.

---

## 1. Bentuk Rekurensi Range DP

Banyak masalah penggabungan berurutan (*sequential merging*), pemotongan (*stick cutting*), dan pohon pencarian biner optimal (*OBST*) memiliki formulasi Range DP:

$$dp[i][j] = \min_{i \le k < j} \{ dp[i][k] + dp[k+1][j] \} + C(i, j)$$

dengan kondisi batas:
$$dp[i][i] = 0 \quad \forall i$$

Pada algoritma naif:
- Terdapat $\mathcal{O}(N^2)$ pasang $(i, j)$.
- Setiap pasangan $(i, j)$ mencoba $k$ dari $i$ sampai $j-1$ ($\mathcal{O}(N)$ kemungkinan).
- Total kompleksitas: $\mathcal{O}(N^3)$, yang terlalu lambat untuk $N \ge 2000$.

---

## 2. Quadrangle Inequality (QI) & Monotonisitas

Agar Knuth Optimization berlaku, fungsi biaya interval $C(i, j)$ harus memenuhi dua kondisi matematis:

### 1. Quadrangle Inequality (QI)
Untuk setiap $a \le b \le c \le d$:
$$C(a, c) + C(b, d) \le C(a, d) + C(b, c)$$

Secara intuitif: "Biaya irisan ditambah biaya gabungan lebih kecil atau sama dengan biaya rentang-rentang silang."

### 2. Monotonisitas Interval
Untuk setiap $a \le b \le c \le d$ (interval $[b, c]$ termuat di dalam $[a, d]$):
$$C(b, c) \le C(a, d)$$

Biaya sub-interval selalu lebih kecil atau sama dengan biaya interval yang memuatnya.

> **Catatan Khusus:** Untuk fungsi biaya $C(i, j) = \sum_{k=i}^j A[k]$ dengan $A[k] \ge 0$:
> - $C(a, c) + C(b, d) = C(a, d) + C(b, c)$ (memenuhi persamaan QI secara eksak).
> - Monotonisitas terpenuhi karena seluruh $A[k] \ge 0$.

---

## 3. Teorema Knuth-Yao

Jika $C(i, j)$ memenuhi Quadrangle Inequality dan monotonisitas, maka titik pemisah optimal:
$$opt[i][j] = \arg\min_{i \le k < j} \{ dp[i][k] + dp[k+1][j] \}$$
memenuhi ketaksamaan monotonisitas:

$$opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$$

### Bukti Intuitif:
Jika kita memperluas interval di ujung kiri ($i \to i+1$), titik potong optimal tidak akan bergeser ke kiri.
Jika kita memperluas interval di ujung kanan ($j-1 \to j$), titik potong optimal tidak akan bergeser ke kiri.
Oleh karena itu, pencarian $k$ untuk rentang $[i, j]$ cukup dibatasi dalam interval:
$$k \in [opt[i][j-1], \min(j-1, opt[i+1][j])]$$

---

## 4. Analisis Kompleksitas Teleskopik: Mengapa $\mathcal{O}(N^2)$?

Untuk suatu panjang interval $L = j - i + 1$, kita menjumlahkan jumlah iterasi $k$ untuk seluruh $i$:

$$\sum_{i=1}^{N - L + 1} \Big( opt[i+1][i+L-1] - opt[i][i+L-2] + 1 \Big)$$

Perhatikan bahwa suku-suku $opt[i+1][\dots]$ dan $-opt[i][\dots]$ saling menghilangkan secara teleskopik:

$$(opt[2][L] - opt[1][L-1]) + (opt[3][L+1] - opt[2][L]) + \dots + (opt[N-L+2][N] - opt[N-L+1][N-1])$$
$$= opt[N-L+2][N] - opt[1][L-1] + \mathcal{O}(N) \le N + \mathcal{O}(N) = \mathcal{O}(N)$$

Karena total langkah untuk SATU nilai panjang $L$ adalah $\mathcal{O}(N)$, dan panjang interval $L$ bergerak dari $2$ sampai $N$ ($N$ nilai berbeda), maka:
$$\text{Total Waktu} = \sum_{L=2}^N \mathcal{O}(N) = \mathcal{O}(N^2)!$$

---

## 5. Ringkasan Perbandingan Optimasi DP

| Optimasi | Bentuk Rekurensi | Sifat Biaya | Kompleksitas |
|---|---|---|---|
| **D&C DP Optimization** | $dp[t][i] = \min_{j < i} \{ dp[t-1][j] + C(j, i) \}$ | QI pada $C(j, i)$ | $\mathcal{O}(K \cdot N \log N)$ |
| **Knuth Optimization** | $dp[i][j] = \min_{i \le k < j} \{ dp[i][k] + dp[k+1][j] \} + C(i, j)$ | QI & Monoton pada $C(i, j)$ | $\mathcal{O}(N^2)$ |
| **Convex Hull Trick** | $dp[i] = \min_{j < i} \{ dp[j] + b[j] \cdot a[i] \}$ | Linearitas bentuk $m \cdot x + c$ | $\mathcal{O}(N)$ atau $\mathcal{O}(N \log N)$ |
| **Li Chao Tree** | $dp[i] = \min_{j < i} \{ dp[j] + b[j] \cdot a[i] \}$ (non-monoton) | Evaluasi segmen garis pada tree | $\mathcal{O}(N \log N)$ |
