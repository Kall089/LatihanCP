# Day 66 — Memoisasi: Jembatan Langsung dari Rekursi ke Dynamic Programming

> **Ide satu kalimat:** Memoisasi adalah teknik mengingat hasil setiap pemanggilan fungsi rekursif menggunakan tabel cache (*look-up table*), memangkas percabangan eksponensial $\mathcal{O}(2^N)$ menjadi polinomial atau linear $\mathcal{O}(N)$ hanya dengan menambahkan 3 baris logika.

---

## 1. Masalah pada Rekursi Polos: Fenomena "Lupa Ingatan"

Pertimbangkan fungsi rekursif perhitungan bilangan Fibonacci:
```cpp
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
```

Secara matematis kode di atas **100% benar**, bersih, dan sangat mudah dibaca.
Namun saat dijalankan untuk $n = 50$, program akan macet atau membutuhkan waktu berjam-jam!

### Mengapa Sangat Lambat?
Pohon rekursi bercabang dua di setiap pemanggilan:
```text
                         fib(5)
                   /               \
             fib(4)                 fib(3)
            /      \               /      \
        fib(3)    fib(2)        fib(2)    fib(1)
       /     \    /    \        /    \
    fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
    /    \
 fib(1) fib(0)
```

Perhatikan:
- `fib(3)` dihitung ulang **2 kali** dari nol.
- `fib(2)` dihitung ulang **3 kali** dari nol.
- `fib(1)` dihitung ulang **5 kali** dari nol.

Jumlah simpul pada pohon tumbuh secara eksponensial: $\mathcal{O}(2^N)$.
Padahal, variasi nilai unik parameter $n$ yang sebenarnya dicari hanyalah $n + 1$ nilai: `fib(0)` sampai `fib(n)`!

---

## 2. Tiga Baris Sakti Memoisasi

Memoisasi menyelesaikan masalah ini dengan analogi sederhana: **"Sebelum menghitung, cek buku catatan. Jika sudah ada, langsung pakai. Jika belum ada, hitung sekali lalu catat di buku."**

### Tiga Komponen Logika:
1. **Pengecekan Cache** di awal fungsi.
2. **Pencatatan ke Cache** saat jawaban ditemukan.
3. **Pengembalian Nilai Tercatat** (`return memo[...] = hasil`).

```cpp
vector<long long> memo(N + 1, -1);

long long fib(int n) {
    // 1. Kasus Dasar (Base Case)
    if (n <= 1) return n;

    // 2. Baris Sakti 1: Cek apakah sudah pernah dihitung
    if (memo[n] != -1) return memo[n];

    // 3. Baris Sakti 2 & 3: Hitung, catat, lalu kembalikan
    return memo[n] = fib(n - 1) + fib(n - 2);
}
```

Dengan 3 baris tersebut:
- Kompleksitas waktu anjlok dari $\mathcal{O}(2^N) \to \mathcal{O}(N)$!
- Setiap nilai $0 \le k \le N$ dihitung **tepat satu kali**.

---

## 3. Struktur Data Cache dan Nilai Sentinel

### A. Array 1D / 2D dengan Sentinel `-1`
Paling umum jika hasil perhitungan selalu non-negatif:
```cpp
vector<int> memo(N + 1, -1);
vector<vector<long long>> memo(N + 1, vector<long long>(W + 1, -1));
```

### B. Array Penanda Terpisah (`seen` / `visited`)
Wajib digunakan jika nilai sah fungsi bisa bernilai `-1` atau `0`:
```cpp
vector<long long> memo(N + 1);
vector<bool> seen(N + 1, false);

long long solve(int i) {
    if (seen[i]) return memo[i];
    seen[i] = true;
    return memo[i] = compute(i);
}
```

### C. Map Cache (`std::map` atau `unordered_map`)
Digunakan saat nilai state sangat besar (misal koordinat $10^9$) atau himpunan state jarang (*sparse*):
```cpp
map<pair<long long, long long>, long long> memo;

long long solve(long long x, long long y) {
    if (memo.count({x, y})) return memo[{x, y}];
    return memo[{x, y}] = ...;
}
```

---

## 4. Memoisasi (Top-Down) vs Tabulasi (Bottom-Up)

| Aspek | Memoisasi (Top-Down) | Tabulasi (Bottom-Up) |
|---|---|---|
| **Gaya Berpikir** | Dari masalah besar dipecah ke submasalah kecil | Dari kasus dasar dibangun ke masalah besar |
| **Implementasi** | Rekursif + Cache | Iteratif (Loop `for`) + Tabel |
| **Kunjungan State** | Hanya menghitung state yang **benar-benar dibutuhkan** (*lazy evaluation*) | Menghitung **seluruh** tabel berurutan |
| **Overhead** | Memori call-stack dan pemanggilan fungsi | Ringan, ramah cache CPU, tanpa overhead stack |
| **Risiko** | *Stack Overflow* jika kedalaman rekursi $> 10^5$ | Tidak ada risiko stack overflow |
| **Optimasi Memori** | Sulit dioptimasi dengan rolling array | Sangat mudah dioptimasi menjadi 1 baris / $O(1)$ |

---

## 5. Checklist Debug Memoisasi

Jika fungsi memoisasi kamu mengalami **TLE** atau **RTE**:
1. **Lupa Menyimpan Hasil**: Menulis `return solve(...)` tanpa `memo[state] = ...`.
2. **Sentinel Bentrok**: Menggunakan `-1` sebagai penanda belum dikunjungi, padahal `-1` adalah hasil perhitungan valid (sehingga submasalah dihitung berulang kali!). Gunakan array `seen` terpisah.
3. **Multi-Testcase Reset**: Lupa membersihkan tabel memo (`memo.assign(...)`) pada setiap test case.
4. **Stack Overflow**: Kedalaman rekursi melebihi batas sistem ($> 10^5$). Gunakan iterasi bottom-up jika $N$ sangat besar.
5. **State Tidak Lengkap**: Fungsi rekursif mengakses variabel global yang berubah-ubah sehingga parameter fungsi tidak merepresentasikan state secara unik.
