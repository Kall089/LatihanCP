# Day 154 — REVIEW DP Dasar (Sintesis & Kerangka Kerja Universal DP)

> **Ide satu kalimat:** Dynamic Programming bukanlah tentang menghafal rumus, melainkan tentang kerangka berpikir memecah masalah menjadi relasi rekursif berstruktur DAG (*Directed Acyclic Graph*), memetakan 4 komponen inti (State, Transisi, Kasus Dasar, Urutan), dan mengenali salah satu dari 5 arketipe klasik.

---

## 1. Peta Kurikulum DP Dasar (Day 141 — Day 153)

| Hari | Topik Utama | Inti Pembelajaran yang Wajib Melekat |
|---|---|---|
| **Day 141** | Pengantar & Prinsip DP | 2 Syarat (*Optimal Substructure* & *Overlapping Subproblems*), 4 Komponen |
| **Day 142** | Top-Down vs Bottom-Up | Memoisasi (rekursif) vs Tabulasi (iteratif), DAG of states, 4 Uji State |
| **Day 143** | DP 1D Sederhana | Climbing Stairs, House Robber, LIS $O(N^2)$, DP Prefiks |
| **Day 144** | Coin Change & Unbounded DP | Min Coins, Ways to Make Change, urutan loop Permutasi vs Kombinasi |
| **Day 145** | 0/1 Knapsack & Bounded DP | Pemilihan biner (ambil / lewatkan), loop kapasitas mundur |
| **Day 146** | Variasi Knapsack | Fractional vs 0/1 vs Multi-choice, Subset Sum reachability |
| **Day 147** | DP Kombinatorik & Counting | Pascal triangle, Catalan, derangement, aritmetika modulo |
| **Day 148** | DP String Dasar | Palindrome substring checking, Edit Distance, Matching |
| **Day 149** | LCS & String Alignment | Longest Common Subsequence, Alignment, Prefix matching |
| **Day 150** | DP pada Grid 2D | Jalur terpendek/maksimum, rintangan, triangular & multirute |
| **Day 151** | Interval / Range DP | Matrix Chain Multiplication, Pemotongan optimal, loop atas panjang $L$ |
| **Day 152** | Rekonstruksi Jawaban DP | Parent array vs Table backtracking, Tie-breaking, Suffix DP |
| **Day 153** | Optimasi Memori DP | Rolling array 2-baris, 1-baris, $O(1)$ variabel lepas, `std::bitset` |

---

## 2. Kerangka Berpikir Universal: 4 Komponen Wajib

Sebelum mengetik kode, tuliskan 4 baris ini di atas kertas atau komentar kode:

```
1. STATE       : dp[i][j] = nilai terbaik / banyak cara untuk submasalah (i, j).
2. TRANSISI    : dp[i][j] = formula transisi dari state-state sebelumnya.
3. KASUS DASAR : dp[0][...] = nilai awal yang sudah pasti diketahui tanpa perhitungan.
4. URUTAN      : Arah perulangan loop agar state dependensi selalu dihitung lebih dulu.
```

### Analisis Kompleksitas Instan:
- **Waktu**: $\mathcal{O}(\text{Jumlah State} \times \text{Waktu Transisi per State})$
- **Memori**: $\mathcal{O}(\text{Jumlah State})$ (sebelum optimasi rolling array)

---

## 3. Lima Kerangka Kode Universal

Hampir 90% persoalan DP dasar dan menengah adalah turunan dari 5 bentuk kerangka ini:

### Kerangka 1: DP 1D (Barisan & Jendela)
```cpp
// Contoh: House Robber / Kadane / Fibonacci
vector<long long> dp(n + 1, 0);
dp[0] = base_0;
dp[1] = base_1;

for (int i = 2; i <= n; i++) {
    dp[i] = max(dp[i - 1], dp[i - 2] + val[i]);
}
```

### Kerangka 2: Knapsack & Kapasitas (Loop Kapasitas)
```cpp
// 0/1 Knapsack (Loop Mundur) vs Unbounded (Loop Maju)
vector<long long> dp(W + 1, 0);

for (int i = 0; i < n; i++) {
    // Mundur untuk 0/1 (tiap barang 1 kali)
    for (int w = W; w >= weight[i]; w--) {
        dp[w] = max(dp[w], dp[w - weight[i]] + val[i]);
    }
}
```

### Kerangka 3: Dua String (Awalan & Karakter Terakhir)
```cpp
// Contoh: LCS / Edit Distance
vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (s[i - 1] == t[j - 1]) {
            dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
}
```

### Kerangka 4: Grid 2D (Sel Masuk Atas & Kiri)
```cpp
// Contoh: Grid Path Sum
vector<vector<long long>> dp(n, vector<long long>(m, INF));
dp[0][0] = grid[0][0];

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j]);
        if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j]);
    }
}
```

### Kerangka 5: Interval / Range DP (Loop Atas Panjang Subarray)
```cpp
// Contoh: Matrix Chain Multiplication / Palindrome Substring
// Perhatikan: Loop terluar WAJIB panjang interval L!
for (int L = 2; L <= n; L++) {
    for (int i = 0; i + L - 1 < n; i++) {
        int j = i + L - 1;
        dp[i][j] = INF;
        for (int k = i; k < j; k++) {
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + cost(i, k, j));
        }
    }
}
```

---

## 4. Tabel Pengenalan Soal (Keyword $\to$ Kerangka)

| Kata Kunci di Soal | Arketipe DP | Karakteristik Khas |
|---|---|---|
| "Berapa banyak cara mencapai...", "Papan catur" | **DP Kombinatorik / Grid** | Operasi penjumlahan modulo $10^9+7$ |
| "Maksimum tanpa dua bersebelahan" | **DP 1D House Robber** | Transisi $dp[i] = \max(dp[i-1], dp[i-2] + x)$ |
| "Kapasitas tas", "Subset tepat berat W" | **0/1 Knapsack** | Loop kapasitas mundur |
| "Koin tak terbatas", "Pecahan uang" | **Unbounded Knapsack** | Loop koin di luar, kapasitas di dalam (maju) |
| "Subsekuens terpanjang pada 2 teks" | **Two Strings (LCS)** | Cek kecocokan karakter terakhir $s[i-1] == t[j-1]$ |
| "Penyuntingan teks: hapus, sisip, ganti" | **Edit Distance** | Mengambil minimum dari 3 operasi (atas, kiri, serong) |
| "Urutkan penggabungan elemen bersebelahan" | **Range / Interval DP** | Loop terluar panjang interval $L$ dari $2$ ke $N$ |
| "Cetak urutan barang terpilih / rute langkah" | **Rekonstruksi Jawaban** | Jangan gunakan rolling array, gunakan parent array / backtracking |
| "Batas memori sangat kecil (32 MB - 64 MB)" | **Optimasi Memori DP** | Rolling array 2-baris atau 1-baris atau bitset |

---

## 5. Checklist Debug & 5 Kesalahan Paling Fatal

Jika solusi menghasilkan **Wrong Answer (WA)**, **Time Limit Exceeded (TLE)**, atau **Runtime Error (RTE)**:

### 10 Pertanyaan Checklist Debug:
1. **Multi-Testcase Reset**: Apakah seluruh array/tabel DP telah dikosongkan pada setiap test case baru?
2. **Arah Loop**: Apakah loop kapasitas pada 0/1 Knapsack berjalan **MUNDUR**?
3. **Loop Range DP**: Apakah loop interval terluar berjalan atas **PANJANG** $L$, bukan indeks $i$?
4. **Base Case Eksak**: Apakah sel unreachable diinisialisasi dengan $\infty$ atau $-1$, dan bukan $0$?
5. **Integer Overflow**: Apakah ada perkalian/penjumlahan yang melebihi $2 \times 10^9$ dan membutuhkan `long long`?
6. **Modulo Arithmetic**: Apakah operasi pengurangan telah diberi `(a - b % MOD + MOD) % MOD`?
7. **Batas Array (Off-By-One)**: Apakah ukuran array $N+1$ atau $N$ dan indeks string 0-based vs 1-based konsisten?
8. **Nilai Awal / Seri (Tie-Breaking)**: Jika rekonstruksi meminta leksikografis terkecil, apakah urutan branching deterministik?
9. **DAG Cyclic**: Apakah ada siklus rekursi tak berujung (*infinite recursion*) pada top-down?
10. **Batas Memori**: Apakah tabel $N \times W$ melebihi 256 MB sehingga butuh rolling array?

---

## 6. Jembatan Menuju DP Tingkat Lanjut (Day 155+)

Setelah menguasai DP Dasar (Day 141–154), kamu siap melangkah ke materi DP Tingkat Lanjut:
- **Day 155 (Desain State Lanjut)**: Menambah dimensi state saat informasi saat ini tidak mencukupi (misal sisa koin, status transaksi).
- **Day 156–157 (Bitmask DP)**: Representasi himpunan subset sebagai bilangan integer biner (Traveling Salesperson Problem, Matching).
- **Day 159 (Digit DP)**: Menghitung bilangan dalam rentang $[L, R]$ yang memenuhi sifat digit khusus.
- **Day 161 (Tree DP)**: DP pada struktur pohon dan graf tanpa siklus.
