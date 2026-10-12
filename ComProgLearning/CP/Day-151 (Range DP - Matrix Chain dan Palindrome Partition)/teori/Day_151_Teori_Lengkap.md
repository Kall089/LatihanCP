# 📊 Day 151: Range DP — Matrix Chain Multiplication & Palindrome Partitioning

**Hari**: Day 151 dari 308 Hari Competitive Programming  
**Topik**: Dynamic Programming — Range DP (Interval DP), Titik Pecah, & Pengisian Berdasarkan Panjang  
**Prasyarat**: LCS (Day 149), DP Grid (Day 150), Prefix Sum 1D (Day 29)  
**Difficulty**: ⭐⭐⭐⭐  
**Learning Objectives**:
- Memahami konsep dasar **Range DP**: state bukan lagi satu indeks $i$, melainkan pasangan interval $[l, r]$.
- Memahami struktur rekurens pemecahan interval $[l, r]$ menjadi dua sub-interval $[l, m]$ dan $[m+1, r]$ melalui titik pecah $m$.
- Menguasai alasan mutlak mengapa pengisian tabel Range DP **WAJIB diurutkan berdasarkan PANJANG interval (`len`)**, bukan indeks biasa.
- Menguasai studi kasus klasik **Matrix Chain Multiplication (MCM)** dan penanganan dimensi $p[0 \dots N]$.
- Menguasai **Stone Merging (Slimes)** dengan bantuan *Prefix Sum* untuk menghitung biaya penggabungan dalam $O(1)$.
- Menguasai **Palindrome Partitioning II** menggunakan pendekatan dua tahap: Range DP boolean $O(N^2)$ dilanjutkan DP 1D $O(N^2)$.
- Memahami paradigma **Reverse Range DP** pada *Burst Balloons* (menentukan balon terakhir yang dipecah).
- Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 🔍 1. Konsep & Karakteristik Range DP

Pada DP Linear 1D, state biasanya adalah posisi $i$ (misal: "jawaban terbaik untuk prefix $0 \dots i$").
Namun, pada banyak permasalahan, operasi yang dilakukan melibatkan **penggabungan atau pemecahan elemen yang bersebelahan** (kontigu):
- Mengalikan rantai matriks yang bersebelahan: $(A_1 \times A_2) \times A_3$ vs $A_1 \times (A_2 \times A_3)$
- Menggabungkan dua tumpukan batu yang berdampingan menjadi satu
- Menentukan apakah suatu substring $S[l \dots r]$ adalah palindrom
- Memotong batang kayu pada titik-titik pemotongan tertentu

Pada kasus-kasus seperti ini, sub-masalah yang terbentuk selalu berupa **interval tertutup $[l, r]$**!

### Definisi State:
$$dp[l][r] = \text{jawaban optimal untuk memproses sub-segmen dari indeks } l \text{ sampai } r$$

Karena ada $N$ kemungkinan batas kiri $l$ dan $N$ kemungkinan batas kanan $r$ dengan $l \le r$, jumlah state adalah:
$$\frac{N(N+1)}{2} = O(N^2) \text{ state}$$

---

## 💡 2. Struktur Rekurens & Ide Titik Pecah (Split Point)

### 2.1 Mengapa Operasi Terakhir Menjamin Optimal Substructure?
Bayangkan kamu menggabungkan serangkaian elemen dari $l$ sampai $r$.
Apapun urutan penggabungannya, **langkah terakhir** selalu berupa penggabungan **dua buah blok besar yang bersebelahan**:
- Blok kiri: hasil penggabungan sub-interval $[l, m]$
- Blok kanan: hasil penggabungan sub-interval $[m+1, r]$

```
                Interval Penuh [l, r]
                /                   \
        Sub-interval [l, m]     Sub-interval [m+1, r]
```

Jika hasil penggabungan akhir ingin bernilai optimal (misal biaya minimum), maka sub-interval $[l, m]$ harus diselesaikan dengan cara **paling optimal**, dan sub-interval $[m+1, r]$ juga harus diselesaikan dengan cara **paling optimal**!

Karena kita tidak tahu di mana posisi titik pemisah $m$ yang terbaik, kita **mencoba seluruh kemungkinan titik pecah $m$** dari $l$ sampai $r-1$:

$$\mathbf{dp[l][r] = \min_{l \le m < r} \Big( dp[l][m] + dp[m+1][r] + \text{BiayaGabung}(l, m, r) \Big)}$$

### 2.2 Base Case (Kasus Dasar):
Untuk interval dengan panjang 1 ($l = r$):
- Satu elemen tunggal atau satu matriks tunggal tidak membutuhkan operasi penggabungan apa pun.
$$dp[i][i] = 0 \quad \text{untuk setiap } 1 \le i \le N$$

---

## 🧭 3. Urutan Pengisian Tabel (Hukum Panjang Interval)

Ini adalah **kesalahan nomor satu** yang paling sering dilakukan saat pertama kali menulis Range DP:

> ❌ **SALAH BESAR**: Menulis loop dengan $l$ dari $1$ ke $N$, dan $r$ dari $l$ ke $N$.
> Mengapa salah? Karena saat menghitung $dp[l][r]$, rumus membutuhkan $dp[m+1][r]$. Jika $l$ maju, nilai $dp[m+1][r]$ (yang barisnya lebih bawah) mungkin **belum pernah dihitung!**

### ✅ Urutan yang Benar: Berdasarkan PANJANG (`len`)
Sebuah interval berpanjang `len` selalu dipecah menjadi sub-interval berpanjang $len_1$ dan $len_2$ di mana:
$$len_1 < len \quad \text{dan} \quad len_2 < len$$

Artinya, jika kita menghitung semua interval berpanjang 1, lalu semua interval berpanjang 2, lalu berpanjang 3, ..., hingga berpanjang $N$:
**Semua sub-interval yang dibutuhkan dijamin SUDAH SELESAI dihitung dan valid!**

### Kerangka 3 Loop Standar Range DP:
```cpp
// 1. Inisialisasi Base Case (Panjang 1)
for (int i = 1; i <= n; i++) {
    dp[i][i] = 0;
}

// 2. Loop Luar: Panjang Interval dari 2 s.d. n
for (int len = 2; len <= n; len++) {
    // 3. Loop Tengah: Batas Kiri l
    for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1; // Batas Kanan
        
        dp[l][r] = INF;
        
        // 4. Loop Dalam: Titik Pecah m
        for (int m = l; m < r; m++) {
            ll cost = dp[l][m] + dp[m + 1][r] + hitungBiaya(l, m, r);
            dp[l][r] = min(dp[l][r], cost);
        }
    }
}
```

Kompleksitas:
- Jumlah state: $O(N^2)$
- Transisi per state: $O(N)$ iterasi titik pecah $m$
- **Total Waktu: $O(N^3)$**
- **Total Memori: $O(N^2)$**

Pada batas waktu 2.0 detik di C++, algoritma $O(N^3)$ dapat menangani $N \le 400 \dots 500$ dengan aman ($\approx \frac{500^3}{6} \approx 2 \times 10^7$ operasi dalam loop terdalam).

---

## 🧮 4. Kasus Klasik 1: Matrix Chain Multiplication (MCM)

Perkalian matriks bersifat **asosiatif**: $(A \times B) \times C = A \times (B \times C)$.
Hasil matriks akhirnya sama persis, namun **jumlah operasi perkalian skalar bisa berbeda drastis!**

### Representasi Dimensi:
Diberikan $N$ matriks $A_1, A_2, \dots, A_N$.
Matriks $A_i$ berukuran $p[i-1] \times p[i]$.
Mengalikan matriks berukuran $a \times b$ dengan matriks berukuran $b \times c$ membutuhkan:
$$\text{Biaya} = a \times b \times c \text{ operasi perkalian}$$
Matriks hasilnya berukuran $a \times c$.

Ketika kita memecah rantai matriks dari $A_l$ sampai $A_r$ pada titik $m$:
- Blok kiri $A_l \dots A_m$ menghasilkan matriks berukuran $p[l-1] \times p[m]$ dengan biaya $dp[l][m]$.
- Blok kanan $A_{m+1} \dots A_r$ menghasilkan matriks berukuran $p[m] \times p[r]$ dengan biaya $dp[m+1][r]$.
- Mengalikan kedua matriks hasil tersebut membutuhkan perkalian:
  $$\mathbf{\text{BiayaGabung} = p[l-1] \times p[m] \times p[r]}$$

### Rekurens MCM:
$$dp[l][r] = \min_{l \le m < r} \Big( dp[l][m] + dp[m+1][r] + p[l-1] \cdot p[m] \cdot p[r] \Big)$$

### Trace Contoh Nyata:
Tiga matriks: $A_1 (10 \times 30)$, $A_2 (30 \times 5)$, $A_3 (5 \times 60)$.
Array dimensi: $p = [10, 30, 5, 60]$.

1. **Panjang 1**:
   $dp[1][1] = 0$, $dp[2][2] = 0$, $dp[3][3] = 0$.
2. **Panjang 2**:
   - $dp[1][2] = dp[1][1] + dp[2][2] + 10 \times 30 \times 5 = 0 + 0 + 1500 = 1500$
   - $dp[2][3] = dp[2][2] + dp[3][3] + 30 \times 5 \times 60 = 0 + 0 + 9000 = 9000$
3. **Panjang 3 ($dp[1][3]$)**:
   - Titik pecah $m = 1$: $(A_1) \times (A_2 A_3)$
     $\text{Biaya} = dp[1][1] + dp[2][3] + 10 \times 30 \times 60 = 0 + 9000 + 18000 = \mathbf{27.000}$
   - Titik pecah $m = 2$: $(A_1 A_2) \times (A_3)$
     $\text{Biaya} = dp[1][2] + dp[3][3] + 10 \times 5 \times 60 = 1500 + 0 + 3000 = \mathbf{4.500}$
   - Nilai minimum: $\min(27000, 4500) = \mathbf{4.500}$!
   Mengelompokkan sebagai $(A_1 A_2) A_3$ adalah **6 kali lebih cepat** daripada $A_1 (A_2 A_3)$!

---

## 🪨 5. Kasus Klasik 2: Stone Merging (Slimes / AtCoder DP N)

Terdapat $N$ tumpukan batu berjajar dengan berat $a_1, a_2, \dots, a_N$.
Dalam satu langkah, kamu boleh menggabungkan dua tumpukan batu yang **bersebelahan** menjadi satu tumpukan baru.
Biaya penggabungan tersebut adalah **jumlah berat kedua tumpukan yang digabung**.
Berapa biaya total minimum untuk menggabungkan seluruh $N$ tumpukan menjadi satu tumpukan tunggal?

### Peran Prefix Sum:
Ketika dua tumpukan dari sub-interval $[l, m]$ dan $[m+1, r]$ digabung menjadi satu tumpukan $[l, r]$, total berat tumpukan baru tersebut adalah seluruh batu dari $l$ sampai $r$:
$$\text{BiayaGabung}(l, r) = \sum_{k=l}^r a_k = \text{pref}[r] - \text{pref}[l-1]$$
Perhatikan bahwa biaya gabung ini bernilai **sama untuk semua titik pecah $m$**!

### Rekurens:
$$dp[l][r] = \min_{l \le m < r} (dp[l][m] + dp[m+1][r]) + (\text{pref}[r] - \text{pref}[l-1])$$

---

## 🔄 6. Palindrome Partitioning II (Kombinasi Range DP + DP 1D)

Diberikan string $S$. Berapa jumlah potongan minimum agar setiap bagian hasil potongan merupakan sebuah **palindrom**?

### Tahap 1: Range DP Boolean ($O(N^2)$)
Definisikan `isPal[l][r]` = true jika substring $S[l \dots r]$ adalah palindrom:
1. Basis:
   - Panjang 1: `isPal[i][i] = true`
   - Panjang 2: `isPal[i][i+1] = (S[i] == S[i+1])`
2. Panjang $\ge 3$:
   `isPal[l][r] = (S[l] == S[r]) && isPal[l+1][r-1]`

### Tahap 2: DP 1D Linear ($O(N^2)$)
Definisikan $cut[i]$ = jumlah potongan minimum untuk prefix $S[0 \dots i]$:
- Jika `isPal[0][i] == true`, maka $cut[i] = 0$ (tidak perlu dipotong).
- Jika tidak:
  $$cut[i] = \min_{0 < j \le i \text{ dan } isPal[j][i]} (cut[j-1] + 1)$$

Hasil akhir untuk seluruh string adalah $cut[N-1]$.

---

## 🎈 7. Reverse Range DP: Burst Balloons (LeetCode 312)

Pada soal *Burst Balloons*, ketika kita meletuskan balon $m$, dua balon di sebelah kiri dan kanannya menjadi bersebelahan. Ini merusak ketergantungan sub-masalah jika kita berpikir "balon mana yang diletuskan pertama kali".

### Kunci Solusi: Berpikir Terbalik (Balon Terakhir yang Diletuskan)
Alih-alih memikirkan balon yang pecah pertama, pikirkan: **balon $m$ adalah balon TERAKHIR dalam interval $[l, r]$ yang diletuskan**.
Karena balon $m$ adalah yang terakhir meletus di $[l, r]$, maka saat balon $m$ meletus, seluruh balon lain di $[l, r]$ sudah hilang, sehingga tetangga dari balon $m$ adalah tepat balon batas luar $l-1$ dan $r+1$!

$$\mathbf{dp[l][r] = \max_{l \le m \le r} \Big( dp[l][m-1] + dp[m+1][r] + nums[l-1] \times nums[m] \times nums[r+1] \Big)}$$

---

## ⚠️ 8. Common Mistakes & Edge Cases

1. **Loop Terluar Berdasarkan Indeks $l$**:
   Selalu gunakan panjang interval `len` dari $2$ sampai $N$ pada loop terluar!
2. **Integer Overflow pada MCM**:
   Perkalian dimensi $p[l-1] \times p[m] \times p[r]$ dengan $p[i] \approx 10^5$ akan bernilai $10^{15}$, melebihi 32-bit int! Gunakan `long long` untuk array DP dan perkalian biaya.
3. **Lupa Kasus Panjang 1**:
   Pastikan $dp[i][i] = 0$ sudah terinisialisasi dengan benar.
4. **Off-by-one pada Indeks Matriks**:
   Ingat bahwa $N$ matriks memiliki $N+1$ dimensi pada array $p$. Matriks ke-$i$ (1-indexed) berukuran $p[i-1] \times p[i]$.

---

## 📌 9. Ringkasan & Tautan Latihan

- State Range DP adalah interval tertutup $[l, r]$.
- Transisi mengevaluasi seluruh titik pecah $m \in [l, r-1]$.
- Urutan pengisian **wajib berdasarkan panjang interval (`len`)** menaik.
- Kompleksitas standar $O(N^3)$ waktu dan $O(N^2)$ memori.

### Rekomendasi Latihan Online Judge:
- **AtCoder**: [Educational DP Contest N — Slimes](https://atcoder.jp/contests/dp/tasks/dp_n)
- **LeetCode**: [312 — Burst Balloons](https://leetcode.com/problems/burst-balloons/)
- **LeetCode**: [132 — Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)
- **LeetCode**: [1547 — Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)
- **LeetCode**: [664 — Strange Printer](https://leetcode.com/problems/strange-printer/)
- **SPOJ**: [MIXTURES — Harry Potter and the Mixtures](https://www.spoj.com/problems/MIXTURES/)
