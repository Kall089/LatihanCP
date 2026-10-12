# 📊 Day 147: Bounded Knapsack & Optimasi Dekomposisi Biner

**Hari**: Day 147 dari 308 Hari Competitive Programming  
**Topik**: Dynamic Programming — Bounded Knapsack, Dekomposisi Biner, & Unbounded Short-Circuit  
**Prasyarat**: Coin Change & Unbounded Knapsack (Day 144), 0/1 Knapsack (Day 145), Subset Sum (Day 146)  
**Difficulty**: ⭐⭐⭐  
**Learning Objectives**:
- Memahami posisi **Bounded Knapsack** sebagai jembatan antara 0/1 Knapsack ($c_i = 1$) dan Unbounded Knapsack ($c_i = \infty$).
- Menganalisis mengapa pendekatan naif (mereplikasi barang sebanyak stok $c_i$) mengalami **Time Limit Exceeded (TLE)** saat stok besar.
- Menguasai teknik **Dekomposisi Biner (Binary Splitting)** untuk memecah stok $c_i$ menjadi $O(\log c_i)$ paket barang virtual.
- Membuktikan secara matematis bahwa kombinasi paket biner $\{1, 2, 4, \dots, \text{sisa}\}$ mencakup seluruh bilangan bulat dalam rentang $[0, c_i]$ tanpa pernah melebihi $c_i$.
- Mengimplementasikan **Pintasan Unbounded (Unbounded Short-Circuit)** saat $c_i \times w_i \ge W$ untuk memangkas faktor $\log c_i$ menjadi $O(W)$.
- Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 🔍 1. Konsep & Intuisi

### 1.1 Spektrum Masalah Knapsack

Dalam keluarga masalah Knapsack, kita memiliki tas berkapasitas bobot $W$ dan $N$ jenis barang. Setiap jenis barang $i$ memiliki bobot $w_i$, nilai $v_i$, dan batas persediaan/stok $c_i$:

```
0/1 Knapsack (Day 145):       c[i] = 1        (Hanya boleh ambil 0 atau 1)
Bounded Knapsack (Day 147):   1 < c[i] < ∞    (Boleh ambil 0, 1, 2, ..., c[i])
Unbounded Knapsack (Day 144): c[i] = ∞        (Boleh ambil sebanyak-banyaknya)
```

Bounded Knapsack adalah bentuk paling realistis dalam kehidupan sehari-hari: toko kelontong atau minimarket selalu memiliki stok barang dalam jumlah terbatas, bukan cuma 1 barang dan bukan pula stok tak terhingga.

### 1.2 Formulasi Matematis

Diberikan:
- Kapasitas ransel: $W$
- $N$ jenis barang: $(w_i, v_i, c_i)$ untuk $i = 0 \dots N-1$

Kita ingin memilih bilangan bulat $k_i$ (jumlah unit barang ke-$i$ yang diambil) sehingga:
$$\max \sum_{i=0}^{N-1} k_i \cdot v_i \quad \text{dengan kendala } \sum_{i=0}^{N-1} k_i \cdot w_i \le W \quad \text{dan} \quad 0 \le k_i \le c_i$$

---

## ⚠️ 2. Kenapa Pendekatan Naif Gagal?

### 2.1 Pendekatan Naif: Duplikasi Barang
Cara paling sederhana yang terpikirkan adalah memperlakukan setiap barang yang memiliki stok $c_i$ sebagai $c_i$ buah barang identik yang masing-masing boleh diambil $0$ atau $1$ kali.

Contoh: Jika barang A berbobot 3, bernilai 5, dan stok 4, kita anggap ada 4 barang terpisah:
- Barang $A_1$: $(w=3, v=5)$
- Barang $A_2$: $(w=3, v=5)$
- Barang $A_3$: $(w=3, v=5)$
- Barang $A_4$: $(w=3, v=5)$

Lalu jalankan algoritma 0/1 Knapsack biasa.

### 2.2 Analisis Kompleksitas Naif
Misalkan total stok seluruh barang adalah $C_{\text{total}} = \sum_{i=0}^{N-1} c_i$.
$$\text{Kompleksitas Waktu Naif} = O(W \times C_{\text{total}}) = O\left(W \sum_{i=0}^{N-1} c_i\right)$$

Mari kita hitung untuk batasan umum di Competitive Programming:
- $N = 100$
- $W = 10.000$
- $c_i = 1.000$ untuk setiap barang

Maka:
$$\text{Total Operasi} = 10.000 \times (100 \times 1.000) = 1.000.000.000 = 10^9 \text{ operasi!}$$
Dengan batas waktu standar 1.0 detik ($\approx 10^8$ operasi di C++), solusi naif ini **pasti mengalami Time Limit Exceeded (TLE)**!

Kita membutuhkan metode untuk merepresentasikan seluruh kemungkinan kuantitas $0 \dots c_i$ dengan jumlah elemen yang jauh lebih sedikit dari $c_i$.

---

## 💡 3. Ide Dekomposisi Biner (Binary Splitting)

Bagaimana sebuah sistem timbangan tradisional di pasar dapat menimbang berat dari 1 gram hingga 15 gram hanya dengan menggunakan 4 buah anak timbangan?
Jawabannya: anak timbangan bernilai **1 gram, 2 gram, 4 gram, dan 8 gram** (pangkat dua)!

$$\begin{aligned}
1 &= 1 \\
2 &= 2 \\
3 &= 1 + 2 \\
4 &= 4 \\
5 &= 1 + 4 \\
6 &= 2 + 4 \\
7 &= 1 + 2 + 4 \\
\dots & \\
15 &= 1 + 2 + 4 + 8
\end{aligned}$$

Setiap bilangan bulat dari $0$ sampai $2^k - 1$ dapat dibentuk secara unik dari kombinasi subset $\{1, 2, 4, \dots, 2^{k-1}\}$.

### Bagaimana Jika Stok $c_i$ Bukan Bentuk $2^k - 1$?

Misalkan stok barang adalah $c_i = 13$.
Pangkat dua berturut-turut adalah:
1. Ambil $1$, sisa $13 - 1 = 12$.
2. Ambil $2$, sisa $12 - 2 = 10$.
3. Ambil $4$, sisa $10 - 4 = 6$.
4. Jika kita mengambil $8$, totalnya melebihi stok ($1 + 2 + 4 + 8 = 15 > 13$).
   Maka, kita **JANGAN** mengambil 8. Seluruh sisa yang tersisa, yaitu **6**, langsung dijadikan potongan terakhir!

Maka pecahan paket untuk stok 13 adalah: **$\{1, 2, 4, 6\}$**.
Total barang yang terwakili: $1 + 2 + 4 + 6 = 13$.

```
Stok 13 barang identik:
┌───┐ ┌───────┐ ┌───────────────┐ ┌───────────────────┐
│ 1 │ │   2   │ │       4       │ │         6         │
└───┘ └─────────┘ └───────────────┘ └───────────────────┘
```

### Bukti Bahwa $\{1, 2, 4, 6\}$ Dapat Membentuk $0 \dots 13$:
1. Tiga paket pertama $\{1, 2, 4\}$ dapat membentuk bilangan dari **$0$ hingga $7$** (karena $1+2+4=7$).
2. Jika kita menambahkan paket **$6$** ke sembarang subset dari $\{1, 2, 4\}$, kita memperoleh nilai:
   $$6 + [0 \dots 7] = [6 \dots 13]$$
3. Gabungan kedua rentang:
   $$[0 \dots 7] \cup [6 \dots 13] = [0 \dots 13]$$
Kedua interval tersebut saling bertumpang tindih (overlap di $6$ dan $7$), sehingga **setiap bilangan bulat dari $0$ hingga $13$ dapat dibentuk**, dan tidak mungkin melebihi $13$!

### Dari $c_i$ Menjadi $O(\log c_i)$ Paket
Dengan memecah stok $c_i$ menjadi potongan pangkat dua dan sisanya:
$$\text{Banyak potongan virtual} \le \lfloor \log_2 c_i \rfloor + 1$$
Untuk $c_i = 1.000$, alih-alih 1.000 barang, kita hanya membutuhkan **10 potongan** ($\le 10$)!
Kompleksitas turun dari $10^9$ operasi menjadi:
$$100 \times 10 \times 10.000 = 10^7 \text{ operasi} \implies \mathbf{0.02\text{ detik (AC)!}}$$

---

## ⚡ 4. Algoritma Pemecahan Biner & Implementasi

Berikut adalah algoritma pemecahan stok dalam C++:

```cpp
// Misalkan barang berbobot w, bernilai v, dan memiliki stok cnt.
int sisa = cnt;
int k = 1;

while (sisa > 0) {
    int ambil = min(k, sisa); // Ambil k jika masih cukup, atau sisa terakhir
    
    int bobot_paket = ambil * w;
    long long nilai_paket = (long long)ambil * v;
    
    // Jalankan 0/1 Knapsack MUNDUR untuk paket virtual ini!
    for (int j = W; j >= bobot_paket; j--) {
        dp[j] = max(dp[j], dp[j - bobot_paket] + nilai_paket);
    }
    
    sisa -= ambil;
    k *= 2; // Gandakan ukuran paket untuk iterasi berikutnya
}
```

> [!IMPORTANT]
> Karena setiap paket virtual hanya boleh diambil maksimal **satu kali** (pilihan biner: ambil paket ini atau tidak), loop kapasitas $j$ **WAJIB MUNDUR** dari $W$ ke $bobot\_paket$!

---

## 🚀 5. Pintasan Unbounded (Unbounded Short-Circuit)

Sebelum memecah barang menjadi paket biner, periksa kondisi kapasitas:
$$\text{Jika } c_i \times w_i \ge W$$

Apa artinya?
Artinya, sekalipun kita mengisi seluruh tas ransel hanya dengan barang jenis ke-$i$, persediaan barang tersebut **tidak akan pernah habis** sebelum tas penuh!
Dengan kata lain, barang jenis $i$ ini berperilaku persis seperti **Unbounded Knapsack**!

### Optimasi Dua Jalur:
1. Jika $c_i \times w_i \ge W$:
   Jalankan **Loop MAJU** ($O(W)$ tanpa faktor $\log c_i$):
   ```cpp
   for (int j = w; j <= W; j++) {
       dp[j] = max(dp[j], dp[j - w] + v);
   }
   ```
2. Jika $c_i \times w_i < W$:
   Jalankan **Dekomposisi Biner** + Loop MUNDUR ($O(W \log c_i)$).

Teknik penggabungan ini disebut *Complete Knapsack Hybrid* dan merupakan implementasi Bounded Knapsack standar tercepat di Competitive Programming!

---

## 🧮 6. Simulasi Langkah Demi Langkah

Misalkan kita memiliki ransel dengan kapasitas $W = 10$.
Barang: Bobot $w = 2$, Nilai $v = 3$, Stok $c = 5$.

### Dekomposisi Stok 5:
- $k=1$: ambil 1, sisa 4. Paket 1: bobot $1 \times 2 = 2$, nilai $1 \times 3 = 3$.
- $k=2$: ambil 2, sisa 2. Paket 2: bobot $2 \times 2 = 4$, nilai $2 \times 3 = 6$.
- $k=4 > 2$: ambil sisa 2. Paket 3: bobot $2 \times 2 = 4$, nilai $2 \times 3 = 6$.
Paket yang terbentuk:
1. Paket A: $(w=2, v=3)$
2. Paket B: $(w=4, v=6)$
3. Paket C: $(w=4, v=6)$

Tabel DP (awal semua 0):
`dp = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]`

1. **Setelah Paket A $(w=2, v=3)$ diproses (Loop Mundur)**:
   `dp[2..3] = 3`, `dp[4..10] = 3`
   Nilai: `[0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3]`

2. **Setelah Paket B $(w=4, v=6)$ diproses (Loop Mundur)**:
   - `dp[6] = max(dp[6], dp[2] + 6) = 3 + 6 = 9` (artinya: paket A + paket B = 3 barang)
   - `dp[4] = max(dp[4], dp[0] + 6) = 6`
   Nilai: `[0, 0, 3, 3, 6, 6, 9, 9, 9, 9, 9]`

3. **Setelah Paket C $(w=4, v=6)$ diproses (Loop Mundur)**:
   - `dp[10] = max(dp[10], dp[6] + 6) = 9 + 6 = 15` (artinya: paket A + B + C = 5 barang, bobot 10, nilai 15!)
   - `dp[8]  = max(dp[8], dp[4] + 6) = 6 + 6 = 12`
   Nilai akhir pada kapasitas 10: $\mathbf{15}$.
   Periksa: 5 barang $\times$ nilai 3 = 15. Bobot $5 \times 2 = 10 \le 10$. Tepat optimal!

---

## ⚠️ 7. Common Mistakes & Edge Cases

1. **Loop Maju pada Paket Biner**:
   Jika kamu menggunakan loop maju pada paket biner, paket tersebut akan dapat diambil berkali-kali, melanggar batas stok $c_i$. Paket biner **wajib memakai loop mundur**!

2. **Salah Menghitung Potongan Terakhir**:
   Kesalahan umum: memaksakan mengambil $k$ tanpa mengecek apakah $k > sisa$.
   Rumus yang benar: `ambil = min(k, sisa); sisa -= ambil; k *= 2;`.

3. **Stok $c_i = 0$**:
   Jika barang memiliki stok 0, lewati barang tersebut tanpa membuat paket apa pun.

4. **Integer Overflow pada Akumulasi Nilai**:
   Nilai paket adalah $ambil \times v_i$. Jika $ambil \approx 10^5$ dan $v_i \approx 10^5$, perkalian ini melebihi $2 \times 10^9$ (batas signed 32-bit int). Gunakan `long long` untuk perhitungan nilai paket dan array DP!

5. **Menggunakan Dekomposisi Biner untuk Counting DP**:
   Dekomposisi biner mempertahankan **jangkauan nilai (reachability)** dan **nilai optimal aditif (max/min)**, tetapi **TIDAK mempertahankan keunikan cara (counting)**!
   Contoh: Stok 5 dipecah jadi $\{1, 2, 2\}$. Jumlah 2 unit dapat dibentuk dari paket 2 pertama ATAU paket 2 kedua. Pada Counting DP, ini akan terhitung ganda! Untuk counting dengan stok terbatas, gunakan recurrence DP asli atau Monotonic Deque.

---

## 🏆 8. Perbandingan Kompleksitas & Memilih Pendekatan

| Pendekatan | Kompleksitas Waktu | Kompleksitas Memori | Kapan Digunakan |
|---|---|---|---|
| **Naif (Duplikasi 1 per 1)** | $O(W \sum c_i)$ | $O(W)$ | Hanya ketika $\sum c_i \le 100$ |
| **Dekomposisi Biner** | $O(W \sum \log c_i)$ | $O(W)$ | Standar di CP ($c_i \le 10^5, W \le 10^5$) |
| **Hybrid (Unbounded Shortcut + Biner)** | $\le O(W \sum \log c_i)$ | $O(W)$ | Rekomendasi terbaik dan paling praktis |
| **Monotonic Queue Optimization (Sliding Window)** | $O(N \times W)$ | $O(W)$ | Ketika $c_i$ sangat besar dan $O(W \log C)$ TLE |

---

## 📌 9. Ringkasan & Tautan Latihan

- Bounded Knapsack membatasi barang paling banyak $c_i$ unit.
- Naif $O(W \cdot C)$ terlalu lambat saat stok besar.
- Pecah stok $c_i$ menjadi paket biner $1, 2, 4, 8, \dots, sisa$.
- Perlakukan setiap paket sebagai barang 0/1 knapsack (loop kapasitas mundur).
- Gunakan pintasan Unbounded jika $c_i \times w_i \ge W$.

### Rekomendasi Latihan Online Judge:
- **POJ**: [1742 — Coins (Bounded Subset Sum)](http://poj.org/problem?id=1742)
- **HDU**: [2191 — Multiple Pack (Classic Bounded Knapsack)](https://acm.dingbacode.com/showproblem.php?pid=2191)
- **Codeforces**: [106C — Buns](https://codeforces.com/problemset/problem/106/C)
- **AtCoder**: [ABC 060 D — Simple Knapsack](https://atcoder.jp/contests/abc060/tasks/arc073_b)
