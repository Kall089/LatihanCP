# Day 152 — Rekonstruksi Jalur dan Penelusuran Jawaban DP

> **Ide satu kalimat:** Rekonstruksi jalur adalah proses menelusuri mundur (*backtracking*) dari state akhir optimal menuju base case untuk memulihkan rangkaian keputusan atau susunan elemen konkret yang menghasilkan nilai optimum tersebut.

---

## 1. Motivasi: Mengapa Perlu Rekonstruksi Jalur?

Banyak masalah kompetitif tidak hanya berhenti pada pertanyaan:
- *"Berapa nilai keuntungan maksimum yang bisa didapat?"*
- *"Berapa jarak terpendek dari start ke finish?"*
- *"Berapa panjang LCS dari dua string?"*

Melainkan melangkah lebih jauh dengan menuntut solusi konkret:
- *"Barang nomor berapa saja yang dimasukkan ke dalam ransel?"*
- *"Jalur koordinat atau deretan belokan mana saja yang dilalui?"*
- *"Apa string konkret dari Longest Common Subsequence tersebut?"*
- *"Apa barisan angka konkret dari Longest Increasing Subsequence?"*

```
                 +-----------------------------------+
                 |        Dynamic Programming        |
                 +-----------------------------------+
                                  |
            +---------------------+---------------------+
            |                                           |
            v                                           v
   [Nilai Optimal Saja]                     [Rekonstruksi Jawaban]
  "Berapa biayanya? -> 42"              "Rangkaian keputusannya apa?"
  Bisa hemat memori                     Wajib mempertahankan riwayat
  (Rolling Array diperbolehkan)         (Tabel 2D lengkap atau Parent Array)
```

---

## 2. Prinsip Umum Rekonstruksi 4 Langkah

Semua teknik rekonstruksi jalur DP bertumpu pada 4 langkah universal:

```
[Langkah 1: Isi Tabel]
Jalankan DP seperti biasa sampai seluruh state terisi (Forward / Tabulasi).
Misal: dp[n][W] atau dp[0].
            │
            ▼
[Langkah 2: Mulai dari Ujung Akhir]
Ambil state yang memuat jawaban optimal akhir (biasanya dp[n][W] atau dp[0][n-1]).
            │
            ▼
[Langkah 3: Tanya "Dari Mana Nilai Ini Berasal?"]
Evaluasi semua kemungkinan transisi pendahulu yang menghasilkan nilai saat ini.
            │
            ▼
[Langkah 4: Mundur dan Balikkan Jawaban (Jika Diperlukan)]
Bergerak ke state pendahulu, ulangi sampai base case tercapai.
Jika rekonstruksi ditelusuri dari belakang, balikkan array/string hasil (reverse).
```

---

## 3. Dua Pola Utama Rekonstruksi

### Pola A: Menyimpan Keputusan / Jejak (`Parent / Choice Array`)
Pada saat mengisi tabel DP, jika suatu transisi memperbarui nilai optimal state saat ini, kita langsung mencatat dari mana transisi itu berasal atau pilihan apa yang diambil.

```cpp
// Contoh pada LIS atau DP 1D:
if (dp[j] + 1 > dp[i]) {
    dp[i] = dp[j] + 1;
    parent[i] = j;       // Catat pendahulu terbaik
}
```

- **Kelebihan**: Sangat intuitif, cepat ditelusuri, ideal untuk DP 1D, graf DAG, atau transisi yang cabangnya banyak.
- **Kekurangan**: Membutuhkan array tambahan sebesar jumlah state.

### Pola B: Membandingkan Ulang Tabel DP (`Table Backtracking`)
Kita **tidak menyimpan array parent tambahan apa pun**. Setelah seluruh tabel DP selesai diisi, kita menelusuri mundur dengan menguji persamaan optimalitas (*optimality condition*):
*"Apakah $dp[i][w] == dp[i-1][w]$ (barang $i$ di-skip) atau $dp[i][w] == dp[i-1][w - w_i] + v_i$ (barang $i$ diambil)?"*

```cpp
// Contoh pada 0/1 Knapsack:
int cur_w = W;
vector<int> chosen;
for (int i = n; i >= 1; i--) {
    // Jika nilainya berbeda dari baris tanpa barang i, pasti barang i diambil
    if (dp[i][cur_w] != dp[i - 1][cur_w]) {
        chosen.push_back(i);
        cur_w -= weight[i];
    }
}
reverse(chosen.begin(), chosen.end());
```

- **Kelebihan**: Bebas memori tambahan (menghemat $O(N \times W)$ memori tambahan).
- **Kekurangan**: Kode rekonsiliasi harus konsisten 100% dengan formula transisi forward DP.

---

## 4. Studi Kasus 1: Knapsack 0/1 dengan Rekonstruksi

Diberikan $N$ barang dengan berat $w_i$ dan nilai $v_i$, serta kapasitas $W$.
Cari nilai maksimum dan cetak indeks barang yang dipilih (1-indexed) terurut menaik!

### Trace Simulasi Manual:
Misal kapasitas $W = 5$, barang:
1. $(w_1 = 2, v_1 = 3)$
2. $(w_2 = 3, v_2 = 4)$
3. $(w_3 = 4, v_3 = 5)$

Tabel $dp[i][j]$:
```
           j=0  j=1  j=2  j=3  j=4  j=5
i=0 (none)   0    0    0    0    0    0
i=1 (2, 3)   0    0    3    3    3    3
i=2 (3, 4)   0    0    3    4    4    7  <-- dp[2][5] = 7 (ambil 1 dan 2)
i=3 (4, 5)   0    0    3    4    5    7  <-- dp[3][5] = 7
```

**Proses Penelusuran Mundur:**
1. Mulai dari $i = 3, w = 5$: $dp[3][5] = 7$.
   Bandingkan dengan $dp[2][5] = 7$.
   Karena $dp[3][5] == dp[2][5]$, nilai maksimum tercapai **tanpa barang 3**. Barang 3 tidak diambil!
   State baru: $i = 2, w = 5$.
2. Di $i = 2, w = 5$: $dp[2][5] = 7$.
   Bandingkan dengan $dp[1][5] = 3$.
   Karena $dp[2][5] \ne dp[1][5]$, barang 2 **pasti diambil**!
   Kapasitas berkurang: $w \leftarrow 5 - 3 = 2$.
   State baru: $i = 1, w = 2$.
3. Di $i = 1, w = 2$: $dp[1][2] = 3$.
   Bandingkan dengan $dp[0][2] = 0$.
   Karena berbeda, barang 1 **pasti diambil**!
   Kapasitas berkurang: $w \leftarrow 2 - 2 = 0$.
   State baru: $i = 0, w = 0$ (selesai).
4. Barang terpilih yang dikumpulkan: $\{2, 1\}$.
   Setelah dibalik: **`1 2`** dengan nilai total **7**.

---

## 5. Studi Kasus 2: Longest Common Subsequence (LCS)

Diberikan dua string $A$ dan $B$. Cetak string LCS terpanjang yang sesungguhnya.

### Rekurens:
$$dp[i][j] = \begin{cases}
dp[i-1][j-1] + 1 & \text{jika } A[i-1] == B[j-1] \\
\max(dp[i-1][j], dp[i][j-1]) & \text{jika } A[i-1] \ne B[j-1]
\end{cases}$$

### Penelusuran Mundur:
Mulai dari $(i = |A|, j = |B|)$:
- Jika $A[i-1] == B[j-1]$:
  Karakter ini adalah bagian dari LCS!
  Tambahkan $A[i-1]$ ke string hasil, lalu mundur secara diagonal ke $(i-1, j-1)$.
- Jika $A[i-1] \ne B[j-1]$:
  Jika $dp[i-1][j] \ge dp[i][j-1]$, mundur ke $(i-1, j)$.
  Jika tidak, mundur ke $(i, j-1)$.
- Ketika $i = 0$ atau $j = 0$, berhenti, lalu balikkan string hasil.

```cpp
string lcs_str = "";
int i = n, j = m;
while (i > 0 && j > 0) {
    if (a[i - 1] == b[j - 1]) {
        lcs_str.push_back(a[i - 1]);
        i--; j--;
    } else if (dp[i - 1][j] >= dp[i][j - 1]) {
        i--;
    } else {
        j--;
    }
}
reverse(lcs_str.begin(), lcs_str.end());
```

---

## 6. Penanganan Tie-Breaker (Leksikografis)

Jika terdapat beberapa jalur yang menghasilkan nilai optimum yang sama, soal sering kali menentukan **aturan tie-breaker**, misalnya:
- *"Pilih susunan yang terkecil secara leksikografis."*
- *"Pilih indeks terkecil pada perbedaan pertama."*

### Jebakan Tie-Breaker Lokal vs Global:
> **PENTING:** Memilih keputusan lokal terkecil saat bergerak maju atau mundur belum tentu menghasilkan string leksikografis global terkecil jika tidak dirancang dengan teliti!

### Teknik Suffix DP untuk Leksikografis Maju:
Jika soal meminta urutan keputusan dari kiri ke kanan yang leksikografis terkecil:
1. Definisikan $dp[i]$ = biaya optimal dari titik $i$ ke finish (arah mundur / suffix).
2. Mulai rekonstruksi dari start ($i = 0$).
3. Di setiap langkah, tinjau seluruh pilihan $j$ yang mungkin secara **terurut menaik**. Pilihan pertama yang memenuhi:
   $$\text{cost}(i \to j) + dp[j] == dp[i]$$
   adalah pilihan yang **dijamin optimal sekaligus leksikografis paling awal**!

---

## 7. Jebakan Klasik Rekonstruksi Jalur DP

| # | Jebakan | Dampak | Solusi |
|---|---|---|---|
| 1 | **Memakai Rolling Array 1D** | Nilai baris lama tertimpa; riwayat asal-usul hilang selamanya. | Jangan gunakan rolling array jika butuh rekonstruksi, kecuali memakai Hirschberg algorithm. |
| 2 | **Lupa `reverse()`** | Jalur tercetak terbalik dari finish ke start. | Selalu ingat arah penelusuran mundur; panggil `reverse(path.begin(), path.end())`. |
| 3 | **Off-by-One pada Indeks (0-based vs 1-based)** | Output indeks meleset 1 angka dari yang diminta soal. | Sinkronkan indeks sejak pembacaan input dan pencetakan. |
| 4 | **Tie-Breaker yang Tidak Konsisten** | Solusi menghasilkan nilai benar tetapi ditolak (WA) karena beda konfigurasi. | Gunakan urutan evaluasi deterministik (`<` vs `<=`) sesuai spesifikasi soal. |
| 5 | **Menelusuri State Tak Terjangkau (Unreachable)** | Runtime Error / Mengakses memori liar. | Pastikan `dp[state] != INF` sebelum melakukan penelusuran transisi. |

---

## 8. Ringkasan Singkat

1. Rekonstruksi jalur memerlukan **riwayat keputusan yang utuh**.
2. **Pola Bandingkan Tabel** menghemat memori karena memanfaatkan tabel DP yang sudah ada tanpa array tambahan.
3. **Pola Parent Array** memudahkan DP 1D dan kasus banyak cabang.
4. Setiap langkah rekonstruksi **wajib mengurangi ukuran masalah** (misal sisa kapasitas $w$, sisa indeks $i$), membuktikan penelusuran pasti berhenti (terminasi).
