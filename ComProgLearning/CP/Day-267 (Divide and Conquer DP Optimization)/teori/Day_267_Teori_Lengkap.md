# Day 267 — Divide and Conquer DP Optimization

> **Ide satu kalimat:** Jika indeks transisi optimal $opt[i][j]$ bersifat monoton terhadap $j$ ($opt[i][j] \le opt[i][j+1]$), algoritma Divide & Conquer dapat memangkas ruang pencarian dari $\mathcal{O}(K \cdot N^2)$ menjadi $\mathcal{O}(K \cdot N \log N)$.

---

## 1. Motivasi dan Bentuk Rekurensi Standar

Banyak permasalahan partisi barisan memiliki formulasi DP dua dimensi:
$$dp[g][i] = \min_{0 \le j < i} \{ dp[g-1][j] + \text{Cost}(j + 1, i) \}$$

Di mana:
- $g$: Jumlah segmen/kelompok yang telah dibentuk ($1 \le g \le K$).
- $i$: Prefix elemen yang dipartisi ($1 \le i \le N$).
- $j$: Titik pemisah segmen terakhir ($j$ memisahkan prefix $1..j$ dan segmen baru $j+1..i$).
- $\text{Cost}(j+1, i)$: Biaya pembentukan satu segmen dari elemen $j+1$ hingga $i$.

### Masalah Kompleksitas:
- Terdapat $K \times N$ state.
- Setiap state memerlukan loop mencari $j$ dari $0$ hingga $i - 1$, yang memakan waktu $\mathcal{O}(N)$.
- Total waktu brute force DP: $\mathcal{O}(K \cdot N^2)$.
- Jika $N = 20.000$ dan $K = 30$, maka $K \cdot N^2 \approx 1.2 \times 10^{10}$ operasi $\implies$ **Time Limit Exceeded (TLE)**!

---

## 2. Syarat Monotonisitas dan Sifat Monge

Definisikan $opt[g][i]$ sebagai indeks $j$ terbaik yang meminimalkan $dp[g][i]$.
Optimasi Divide & Conquer dapat diterapkan jika dan hanya jika titik potong optimal memenuhi kondisi **monoton tidak menurun**:
$$opt[g][i] \le opt[g][i+1]$$

Artinya: **Jika prefix bertambah panjang ($i \to i+1$), pemisah terbaiknya tidak akan pernah bergerak mundur ke kiri!**

### Kondisi Cukup: Quadrangle Inequality (Sifat Monge)
Sifat monotonisitas ini dijamin berlaku jika fungsi biaya $\text{Cost}(l, r)$ memenuhi **Quadrangle Inequality**:
Untuk sembarang $a \le b \le c \le d$:
$$\text{Cost}(a, c) + \text{Cost}(b, d) \le \text{Cost}(a, d) + \text{Cost}(b, c)$$

Contoh fungsi biaya yang memenuhi sifat Monge:
1. **Kuadrat Jumlah Subarray**: $\text{Cost}(l, r) = \left(\sum_{k=l}^r a_k\right)^2$ dengan $a_k \ge 0$.
2. **Jarak Absolut ke Median**: $\text{Cost}(l, r) = \sum_{k=l}^r |x_k - \text{median}|$.
3. **Banyaknya Pasangan Elemen Sama / Pasangan Inversi**: dalam subarray $l..r$.

---

## 3. Algoritma Divide & Conquer

Karena transisi untuk layer $g$ hanya bergantung pada layer $g - 1$, kita dapat menghitung setiap layer secara independen menggunakan rekursi pembagian rentang (*divide and conquer*).

Untuk layer $g$ tertentu:
```cpp
void compute(int l, int r, int opt_l, int opt_r) {
    if (l > r) return;

    int mid = l + (r - l) / 2;
    int best_k = opt_l;
    long long best_val = INF;

    // Cari titik transisi terbaik k untuk mid
    for (int k = opt_l; k <= min(opt_r, mid - 1); k++) {
        if (dp_prev[k] == INF) continue;
        long long current_cost = dp_prev[k] + cost(k + 1, mid);
        if (current_cost < best_val) {
            best_val = current_cost;
            best_k = k;
        }
    }

    dp_curr[mid] = best_val;

    // Bagi dua secara rekursif
    compute(l, mid - 1, opt_l, best_k);
    compute(mid + 1, r, best_k, opt_r);
}
```

### Analisis Kompleksitas:
- Kedalaman pohon rekursi adalah $\mathcal{O}(\log N)$.
- Pada setiap level kedalaman, jumlah panjang rentang pencarian $[opt_l, opt_r]$ di seluruh pemanggilan adalah $\mathcal{O}(N)$.
- Waktu per layer $g$: $\mathcal{O}(N \log N)$.
- Total waktu untuk $K$ layer: $\mathcal{O}(K \cdot N \log N)$.
- Untuk $N = 20.000$ dan $K = 30$: $K \cdot N \log_2(N) \approx 30 \times 20.000 \times 15 \approx 9 \times 10^6$ operasi $\implies$ **Selesai dalam < 0.1 detik!**

---

## 4. Checklist & Jebakan Gotchas

1. **Urutan Dependensi Layer**: Hitung layer $g$ dari $1$ sampai $K$, di mana `dp_curr` dihitung dari `dp_prev` (menghemat memori menjadi $\mathcal{O}(N)$).
2. **Batas Loop Pencarian**: Indeks pemisah $k$ tidak boleh sama dengan $mid$ jika segmen tidak boleh kosong ($k \le mid - 1$).
3. **Nilai Awal / Kasus Dasar**:
   - `dp[0][0] = 0`, semua `dp[0][i] = INF` untuk $i > 0$.
4. **Bobot Negatif**: Jika array mengandung bilangan negatif, sifat Monge pada kuadrat jumlah subarray bisa rusak! Pastikan elemen $\ge 0$.
5. **Tie-Breaking**: Jika dua nilai kandidat menghasilkan biaya yang persis sama, pilihlah $k$ terkecil secara konsisten agar relasi monotonisitas tetap terjaga.
