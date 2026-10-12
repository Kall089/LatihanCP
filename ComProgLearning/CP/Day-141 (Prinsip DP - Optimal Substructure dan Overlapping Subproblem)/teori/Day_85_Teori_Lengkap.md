# 📊 Day 85 — Konsep DP & Dynamic Programming 1D

> **Prasyarat:** Rekursi (Day 11), Kompleksitas (Day 7)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** _"berapa banyak cara"_, _"nilai maksimum/minimum"_, _"minimal langkah"_

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 85, kamu akan mampu:

- [ ] Menjelaskan dua syarat wajib DP: **overlapping subproblem** & **optimal substructure**
- [ ] Membedakan **rekursi biasa**, **memoisasi (top-down)**, dan **tabulasi (bottom-up)**
- [ ] Merancang **state** dan **transisi** dari nol untuk soal 1 dimensi
- [ ] Menyelesaikan pola klasik: tangga, house robber, coin change, jump game
- [ ] Melakukan **optimasi memori** dari O(N) menjadi O(1) (rolling variable)
- [ ] Mengetahui kapan sebuah masalah **bukan** DP (dan greedy sudah cukup)

---

## 🔍 1. Konsep & Intuisi

### Apa itu Dynamic Programming?

DP adalah **rekursi yang tidak mau menghitung hal yang sama dua kali**. Itu saja.

Kalau sebuah masalah bisa dipecah menjadi masalah yang lebih kecil, dan masalah kecil
yang sama muncul berulang kali, maka menyimpan jawabannya di sebuah tabel akan
mengubah kompleksitas dari eksponensial menjadi linear.

### Analogi: mengerjakan PR bersama teman sekelas

Bayangkan kamu mengerjakan 100 soal PR. Kamu sadar soal nomor 47 ternyata sudah
pernah kamu kerjakan persis di nomor 12.

- **Tanpa DP:** kamu kerjakan ulang dari awal. Kalau tiap soal butuh 10 menit dan
  banyak soal berulang, PR-mu tidak selesai semalaman.
- **Dengan DP:** setelah mengerjakan nomor 12, kamu **tulis jawabannya di buku catatan**.
  Saat ketemu soal yang sama di nomor 47, kamu tinggal lihat catatan — nol menit.

Buku catatan itulah **tabel DP**. Sesederhana itu.

### Kenapa fibonacci polos begitu lambat?

```
                    fib(5)
                  /        \
             fib(4)          fib(3)          <- fib(3) dihitung 2 kali
            /      \        /      \
       fib(3)     fib(2) fib(2)   fib(1)     <- fib(2) dihitung 3 kali
       /    \      /  \    /  \
   fib(2) fib(1) ...  ... ...  ...           <- makin dalam makin parah
```

`fib(50)` tanpa DP butuh sekitar **2 miliar pemanggilan**. Dengan DP: **50 pemanggilan**.
Itu bukan optimasi kecil — itu perbedaan antara program yang tidak pernah selesai
dan program yang selesai seketika.

### Dua syarat wajib sebuah masalah bisa di-DP

**1. Overlapping subproblems** — submasalah yang sama muncul berkali-kali.
Kalau setiap submasalah hanya muncul sekali, menyimpannya tidak ada gunanya
(itu namanya divide and conquer biasa, seperti merge sort).

**2. Optimal substructure** — jawaban terbaik keseluruhan bisa disusun dari
jawaban terbaik bagian-bagiannya.

> Contoh yang **melanggar** syarat kedua: mencari jalur **terpanjang tanpa mengulang simpul**
> pada graf berarah bersiklus. Jalur terpanjang ke B tidak bisa disusun begitu saja dari
> jalur terpanjang ke tetangga-tetangganya, karena bisa terjadi tabrakan simpul.

### Tiga pertanyaan untuk merancang DP

Setiap kali menghadapi soal DP, jawab tiga pertanyaan ini secara berurutan:

```
1. STATE     : "dp[i] artinya apa?"           <- definisikan dengan kalimat lengkap
2. TRANSISI  : "dp[i] dihitung dari mana?"     <- hubungan ke state yang lebih kecil
3. BASIS     : "yang paling kecil nilainya berapa?"  <- titik awal
```

Kalau ketiganya sudah terjawab, kodenya biasanya tinggal 5 baris.

### Visualisasi ASCII: naik tangga

Ada 5 anak tangga. Sekali melangkah boleh naik 1 atau 2 tangga.
Ada berapa cara mencapai tangga ke-5?

```
      cara[5] = 8
        ↑
      cara[4] = 5  ──┐
        ↑            ├──► cara[5] = cara[4] + cara[3] = 5 + 3 = 8
      cara[3] = 3  ──┘
        ↑
      cara[2] = 2
        ↑
      cara[1] = 1
        ↑
      cara[0] = 1   (basis: sudah di tujuan, ada 1 cara: diam)

Kenapa cara[i] = cara[i-1] + cara[i-2]?
Karena untuk sampai di tangga ke-i, langkah TERAKHIR-mu pasti
salah satu dari dua ini:
  - melangkah 1 dari tangga (i-1)  -> ada cara[i-1] jalan menuju ke sana
  - melangkah 2 dari tangga (i-2)  -> ada cara[i-2] jalan menuju ke sana
Tidak ada kemungkinan lain, dan keduanya tidak bertumpang tindih.
```

---

## 🧮 2. Analisis Kompleksitas

### Rumus umum kompleksitas DP

```
Waktu = (banyaknya state) × (biaya menghitung satu state)
```

| Jenis DP                           | Banyak state | Biaya per state | Total      |
| ---------------------------------- | ------------ | --------------- | ---------- |
| DP 1D sederhana (tangga, robber)   | O(N)         | O(1)            | **O(N)**   |
| DP 1D dengan pilihan (coin change) | O(N)         | O(K)            | **O(N·K)** |
| DP 1D pilihan bebas (LIS O(n²))    | O(N)         | O(N)            | **O(N²)**  |
| DP 2D (grid, LCS)                  | O(N·M)       | O(1)            | O(N·M)     |

### Perbandingan tiga pendekatan pada fibonacci

| Pendekatan           | Waktu    | Memori       | Catatan                         |
| -------------------- | -------- | ------------ | ------------------------------- |
| Rekursi polos        | O(2ⁿ)    | O(N) stack   | n = 50 → tidak selesai          |
| Memoisasi (top-down) | **O(N)** | O(N) + stack | Paling mirip cara berpikir      |
| Tabulasi (bottom-up) | **O(N)** | O(N)         | Tidak ada risiko stack overflow |
| Tabulasi + rolling   | **O(N)** | **O(1)**     | Paling hemat                    |

### Memoisasi vs Tabulasi — pilih yang mana?

| Aspek         | Memoisasi (top-down)                  | Tabulasi (bottom-up)                |
| ------------- | ------------------------------------- | ----------------------------------- |
| Cara menulis  | Tulis rekursi, tambah cache           | Isi tabel dari kecil ke besar       |
| Kelebihan     | Alami, hanya menghitung yang perlu    | Cepat, tanpa overhead rekursi       |
| Kekurangan    | Risiko **stack overflow** kalau dalam | Harus tahu urutan pengisian         |
| Kapan dipakai | State rumit, tidak semua terpakai     | State sederhana dan urutannya jelas |

> Untuk kontes, **mulailah dengan memoisasi** (lebih mudah dibuat benar), lalu ubah ke
> tabulasi kalau butuh lebih cepat atau takut stack overflow.

---

## 💻 3. Implementasi C++

### 3.1 Tiga cara menulis fibonacci

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ── (a) Rekursi polos — JANGAN dipakai, O(2^n) ──
ll fibPolos(int n) {
    if (n <= 1) return n;
    return fibPolos(n - 1) + fibPolos(n - 2);
}

// ── (b) Memoisasi / top-down — O(n) ──
ll memo[100];
bool sudah[100];

ll fibMemo(int n) {
    if (n <= 1) return n;                 // basis
    if (sudah[n]) return memo[n];         // sudah pernah dihitung -> baca catatan
    sudah[n] = true;
    return memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
}

// ── (c) Tabulasi / bottom-up — O(n) ──
ll fibTab(int n) {
    vector<ll> dp(n + 1);
    dp[0] = 0;                            // basis
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];    // transisi
    return dp[n];
}

// ── (d) Tabulasi + rolling variable — O(n) waktu, O(1) memori ──
ll fibHemat(int n) {
    if (n <= 1) return n;
    ll dua = 0, satu = 1;                 // dp[i-2], dp[i-1]
    for (int i = 2; i <= n; i++) {
        ll kini = dua + satu;
        dua = satu;
        satu = kini;
    }
    return satu;
}
```

### 3.2 Naik tangga (menghitung banyaknya cara)

```cpp
// dp[i] = banyaknya cara mencapai tangga ke-i
const ll MOD = 1e9 + 7;

ll naikTangga(int n) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;                            // basis: diam di tempat = 1 cara
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];                       // langkah terakhir 1 tangga
        if (i >= 2) dp[i] = (dp[i] + dp[i - 2]) % MOD;   // langkah terakhir 2 tangga
    }
    return dp[n];
}
```

### 3.3 House robber (jumlah maksimum tanpa mengambil tetangga)

```cpp
// dp[i] = untung maksimum dari rumah 1..i
ll houseRobber(vector<ll>& a, int n) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = a[1];
    for (int i = 2; i <= n; i++)
        dp[i] = max(dp[i - 1],            // lewati rumah ke-i
                    dp[i - 2] + a[i]);    // ambil rumah ke-i (lompati i-1)
    return dp[n];
}
```

### 3.4 Coin change — minimum koin

```cpp
const int INF = 1e9;

int coinChange(vector<int>& koin, int target) {
    vector<int> dp(target + 1, INF);
    dp[0] = 0;                            // basis: 0 rupiah butuh 0 koin
    for (int nilai = 1; nilai <= target; nilai++)
        for (int k : koin)
            if (k <= nilai && dp[nilai - k] != INF)
                dp[nilai] = min(dp[nilai], dp[nilai - k] + 1);
    return dp[target] == INF ? -1 : dp[target];
}
```

### 3.5 Coin change — banyaknya cara

```cpp
// PERHATIKAN URUTAN LOOP-nya, ini yang membedakan kombinasi vs permutasi.
ll cacahCara(vector<int>& koin, int target) {
    vector<ll> dp(target + 1, 0);
    dp[0] = 1;
    for (int k : koin)                        // koin di loop LUAR
        for (int nilai = k; nilai <= target; nilai++)
            dp[nilai] += dp[nilai - k];
    return dp[target];                        // menghitung KOMBINASI ({1,2} = {2,1})
}

// Kalau urutannya dibalik (nilai di luar, koin di dalam),
// yang terhitung adalah PERMUTASI ({1,2} dan {2,1} dianggap berbeda).
```

---

## 🔄 4. Trace / Simulasi

### Contoh 1: naik tangga, n = 5

| i   | dp[i-1] | dp[i-2] | dp[i] | Penjelasan                 |
| --- | ------- | ------- | ----- | -------------------------- |
| 0   | —       | —       | **1** | Basis: sudah di tujuan     |
| 1   | dp[0]=1 | —       | **1** | Hanya satu cara: langkah 1 |
| 2   | dp[1]=1 | dp[0]=1 | **2** | 1+1, atau 2                |
| 3   | dp[2]=2 | dp[1]=1 | **3** | 1+1+1, 1+2, 2+1            |
| 4   | dp[3]=3 | dp[2]=2 | **5** |                            |
| 5   | dp[4]=5 | dp[3]=3 | **8** | ← jawaban                  |

Perhatikan barisannya: 1, 1, 2, 3, 5, 8 — ini persis Fibonacci.

### Contoh 2: house robber, a = [2, 7, 9, 3, 1]

| i   | a[i] | dp[i-1] (lewati) | dp[i-2] + a[i] (ambil) | dp[i]  | Pilihan |
| --- | ---- | ---------------- | ---------------------- | ------ | ------- |
| 1   | 2    | —                | 0 + 2 = 2              | **2**  | ambil   |
| 2   | 7    | 2                | 0 + 7 = 7              | **7**  | ambil   |
| 3   | 9    | 7                | 2 + 9 = 11             | **11** | ambil   |
| 4   | 3    | 11               | 7 + 3 = 10             | **11** | lewati  |
| 5   | 1    | 11               | 11 + 1 = 12            | **12** | ambil   |

**Jawaban: 12** (dari rumah ke-1, ke-3, dan ke-5: 2 + 9 + 1 = 12).

Perhatikan langkah i=4: mengambil rumah bernilai 3 justru merugikan,
karena berarti harus melepas rumah bernilai 9. DP memutuskan ini secara otomatis.

### Contoh 3: coin change minimum, koin = {1, 3, 4}, target = 6

| nilai | Kandidat (dp[nilai - k] + 1)        | dp[nilai] |
| ----- | ----------------------------------- | --------- |
| 0     | —                                   | **0**     |
| 1     | dp[0]+1 = 1                         | **1**     |
| 2     | dp[1]+1 = 2                         | **2**     |
| 3     | dp[2]+1=3, dp[0]+1=**1**            | **1**     |
| 4     | dp[3]+1=2, dp[1]+1=2, dp[0]+1=**1** | **1**     |
| 5     | dp[4]+1=**2**, dp[2]+1=3, dp[1]+1=2 | **2**     |
| 6     | dp[5]+1=3, dp[3]+1=**2**, dp[2]+1=3 | **2**     |

**Jawaban: 2 koin** (yaitu 3 + 3).

> Perhatikan bahwa greedy akan salah di sini! Greedy mengambil koin terbesar dulu:
> 4 + 1 + 1 = **3 koin**. DP menemukan jawaban yang benar-benar minimum: **2 koin**.
> Inilah contoh nyata kapan greedy gagal dan DP wajib dipakai.

---

## 📝 5. Variasi & Pattern

### Pola 1: "berapa banyak cara" → jumlahkan

```cpp
dp[i] = dp[i-1] + dp[i-2] + ...        // hasilnya di-MOD kalau besar
```

_Contoh: naik tangga, cacah cara coin change, jalur di grid._

### Pola 2: "nilai maksimum/minimum" → ambil max/min

```cpp
dp[i] = max(dp[i-1], dp[i-2] + a[i]);
```

_Contoh: house robber, knapsack, LIS._

### Pola 3: "bisa atau tidak" → boolean

```cpp
dp[i] = dp[i-1] || dp[i-k];
```

_Contoh: subset sum, jump game, memecah kata._

### Pola 4: "minimal langkah" → min + 1

```cpp
dp[i] = min(dp[i], dp[j] + 1);
```

_Contoh: coin change minimum, minimum jumps._

### Variasi: rolling array untuk menghemat memori

Kalau `dp[i]` hanya bergantung pada beberapa state sebelumnya, tabel penuh tidak perlu:

```cpp
// Dari O(N) memori:
vector<ll> dp(n + 1);
for (int i = 2; i <= n; i++) dp[i] = dp[i-1] + dp[i-2];

// Menjadi O(1) memori:
ll a = 0, b = 1;
for (int i = 2; i <= n; i++) { ll c = a + b; a = b; b = c; }
```

### Variasi: merekonstruksi jawabannya, bukan cuma nilainya

```cpp
vector<int> dari(n + 1, -1);          // simpan dari mana dp[i] berasal
for (int i = 2; i <= n; i++) {
    if (dp[i-1] > dp[i-2] + a[i]) { dp[i] = dp[i-1];        dari[i] = i-1; }
    else                          { dp[i] = dp[i-2] + a[i]; dari[i] = i-2; }
}
// Telusuri mundur dari n memakai array dari[]
vector<int> jalur;
for (int i = n; i > 0; i = dari[i]) jalur.push_back(i);
reverse(jalur.begin(), jalur.end());
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### ❌ Mistake 1: lupa basis atau basis salah

```cpp
vector<ll> dp(n + 1, 0);
// dp[0] tidak diisi -> semua hasil jadi 0
dp[0] = 1;      // ✅ untuk "berapa cara": ada 1 cara melakukan apa-apa
dp[0] = 0;      // ✅ untuk "minimal koin": butuh 0 koin untuk nilai 0
```

Basis yang salah membuat **seluruh tabel salah**, dan gejalanya sering
"hasilnya 0 semua" atau "hasilnya kurang 1".

### ❌ Mistake 2: ukuran array kurang satu

```cpp
vector<ll> dp(n);        // ❌ indeks n tidak ada
vector<ll> dp(n + 1);    // ✅ karena kita memakai dp[1..n]
```

### ❌ Mistake 3: lupa modulo pada soal "berapa cara"

```cpp
dp[i] = dp[i-1] + dp[i-2];                  // ❌ overflow untuk n besar
dp[i] = (dp[i-1] + dp[i-2]) % MOD;          // ✅
```

### ❌ Mistake 4: urutan loop salah pada coin change

```cpp
// KOMBINASI ({1,2} sama dengan {2,1}) -> koin di LUAR
for (int k : koin) for (int v = k; v <= target; v++) dp[v] += dp[v-k];

// PERMUTASI ({1,2} beda dengan {2,1}) -> nilai di LUAR
for (int v = 1; v <= target; v++) for (int k : koin) if (k <= v) dp[v] += dp[v-k];
```

Menukar dua loop ini **mengubah arti jawabannya**. Baca soal baik-baik:
apakah urutan pengambilan koin dianggap berbeda?

### ❌ Mistake 5: memoisasi memakai 0 sebagai penanda "belum dihitung"

```cpp
ll memo[100];                   // diisi 0
if (memo[n]) return memo[n];    // ❌ kalau jawaban ASLINYA 0, dihitung ulang terus

// ✅ pakai penanda terpisah atau nilai mustahil
if (memo[n] != -1) return memo[n];   // inisialisasi dengan -1
```

### ❌ Mistake 6: stack overflow pada memoisasi dalam

Rekursi sedalam 10⁶ akan menabrak batas stack. Ubah ke tabulasi.

### Edge Cases yang perlu diuji

| Kasus                       | Kenapa berbahaya                                    |
| --------------------------- | --------------------------------------------------- |
| n = 0                       | Loop tidak jalan; apakah dp[0] sudah benar?         |
| n = 1                       | Transisi `dp[i-2]` mengakses indeks negatif         |
| Semua elemen 0 atau negatif | House robber bisa salah kalau basis dipaksa positif |
| Target tidak bisa dicapai   | Coin change harus mencetak −1, bukan INF            |
| Nilai jawaban sangat besar  | Wajib long long dan modulo                          |

---

## 🏆 7. Tips Contest

### Red flags — tanda soal ini DP

- 🚩 _"Berapa banyak cara untuk ..."_
- 🚩 _"Nilai maksimum/minimum yang bisa diperoleh"_
- 🚩 _"Minimal berapa langkah untuk ..."_
- 🚩 _"Bisakah dicapai tepat X?"_
- 🚩 Ada larangan seperti _"tidak boleh mengambil dua yang berdampingan"_
- 🚩 Kamu sudah menemukan solusi rekursif, tapi terlalu lambat

### Cara cepat memutuskan greedy atau DP

```
Pilihan sekarang mempengaruhi pilihan berikutnya?
├── Tidak → GREEDY mungkin cukup
└── Ya
    ├── Bisa dibuktikan greedy tetap benar? (exchange argument)
    │   └── Ya → GREEDY
    └── Tidak / ragu → DP ✅  (lebih aman, lebih lambat sedikit)
```

Contoh nyata dari materi ini: coin change {1, 3, 4} target 6 —
greedy memberi 3 koin, DP memberi 2 koin. **Greedy salah.**

### Urutan menulis DP saat kontes (5 menit)

```
1. Tulis definisi state sebagai KALIMAT di komentar
   // dp[i] = untung maksimum dari rumah 1..i
2. Tulis basis
3. Tulis transisi
4. Tentukan urutan loop
5. Cetak dp[n]
```

Kalau langkah 1 sulit ditulis dalam satu kalimat, biasanya berarti
**state-nya belum benar** — jangan buru-buru menulis kode.

### Time management

- DP 1D klasik (tangga, robber, coin change) harus selesai **< 10 menit**.
- Kalau sudah 20 menit dan transisinya belum ketemu, kemungkinan besar
  state-nya kurang satu dimensi. Coba tambahkan informasi ke state.

---

## 📌 8. Ringkasan & Cheatsheet

### Cheatsheet Singkat

```
╔══════════════════════════════════════════════════════════════╗
║  DYNAMIC PROGRAMMING 1D — CHEATSHEET                         ║
╠══════════════════════════════════════════════════════════════╣
║  TIGA PERTANYAAN WAJIB                                       ║
║    1. STATE    : dp[i] artinya apa? (tulis sebagai kalimat)  ║
║    2. TRANSISI : dp[i] dari state mana?                      ║
║    3. BASIS    : nilai terkecil berapa?                      ║
║                                                              ║
║  POLA TRANSISI                                               ║
║    "berapa cara"     -> dp[i] = dp[i-1] + dp[i-2]            ║
║    "maksimum"        -> dp[i] = max(dp[i-1], dp[i-2] + a[i]) ║
║    "minimal langkah" -> dp[i] = min(dp[i], dp[j] + 1)        ║
║    "bisa/tidak"      -> dp[i] = dp[i-1] || dp[i-k]           ║
║                                                              ║
║  BASIS YANG SERING DIPAKAI                                   ║
║    berapa cara   -> dp[0] = 1   (1 cara: tidak berbuat apa)  ║
║    minimal       -> dp[0] = 0, sisanya INF                   ║
║    maksimum      -> dp[0] = 0                                ║
║                                                              ║
║  MEMOISASI                    TABULASI                       ║
║    tulis rekursi + cache        isi tabel kecil -> besar     ║
║    hati-hati stack overflow     tidak ada rekursi            ║
║    penanda: memset(memo,-1,..)  urutan loop harus benar      ║
║                                                              ║
║  KOMPLEKSITAS = (jumlah state) x (biaya per state)           ║
║  HEMAT MEMORI : ganti tabel dengan 2 variabel bergulir       ║
╚══════════════════════════════════════════════════════════════╝
```

### Key Points

1. **DP = rekursi + catatan.** Kalau kamu sudah bisa menulis rekursinya, DP tinggal
   menambahkan tabel.
2. **Definisikan state sebagai kalimat lengkap** sebelum menulis kode. Ini menyelesaikan
   80% kesulitan.
3. **Basis adalah tempat bug paling sering bersembunyi.** Cek n = 0 dan n = 1 secara terpisah.
4. **Urutan loop pada coin change menentukan arti jawaban** (kombinasi vs permutasi).
5. **Greedy tidak selalu benar.** Contoh koin {1, 3, 4} membuktikannya dalam 10 detik.
6. **Rolling variable** menurunkan memori dari O(N) ke O(1) tanpa mengubah logika.

### Hubungan dengan materi lain

```
Day 11: Rekursi ────┐
                    ├──► Day 85: KONSEP DP & DP 1D (kamu di sini)
Day 7 : Kompleksitas┘            │
                                 ├──► Day 87-88: LIS
                                 ├──► Day 89-90: DP 2D (grid, edit distance)
                                 ├──► Day 92-93: Knapsack
                                 └──► Day 96   : Bitmask DP
```

### Link Soal Latihan di Online Judge

**LeetCode (mulai dari sini)**

- [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) — DP paling dasar
- [198. House Robber](https://leetcode.com/problems/house-robber/) — pola ambil/lewati
- [322. Coin Change](https://leetcode.com/problems/coin-change/) — minimal koin
- [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/) — banyaknya cara
- [55. Jump Game](https://leetcode.com/problems/jump-game/) — bisa/tidak
- [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)

**CSES Problem Set (bagian Dynamic Programming)**

- [Dice Combinations](https://cses.fi/problemset/task/1633) — naik tangga versi 6 langkah
- [Minimizing Coins](https://cses.fi/problemset/task/1634) — coin change minimum
- [Coin Combinations I](https://cses.fi/problemset/task/1635) — permutasi
- [Coin Combinations II](https://cses.fi/problemset/task/1636) — kombinasi
- [Removing Digits](https://cses.fi/problemset/task/1637)

**AtCoder Educational DP Contest** (sangat direkomendasikan)

- [A - Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a) — DP 1D paling murni
- [B - Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b) — versi K langkah

---

_Selesai Day 85. Lanjut ke Day 86–88 (LIS) lalu Day 89–90 (DP 2D)._
