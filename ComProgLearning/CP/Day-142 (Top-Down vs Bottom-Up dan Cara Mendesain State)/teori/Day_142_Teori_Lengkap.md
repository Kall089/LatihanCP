# 📊 Day 142: Top-Down vs Bottom-Up & Cara Mendesain State

**Hari**: Day 142 dari 308 Hari Competitive Programming  
**Topik**: Dynamic Programming — Paradigma Evaluasi & Metodologi Desain State  
**Prasyarat**: Prinsip DP (Day 141), Memoization (Day 66), Analisis Kompleksitas (Day 15)  
**Difficulty**: ⭐⭐⭐  
**Learning Objectives**:
- Memahami secara mendalam perbedaan cara kerja, kelebihan, dan kelemahan **Top-Down (Memoisasi)** vs **Bottom-Up (Tabulasi)**.
- Menguasai kerangka kerja **"Empat Uji Desain State"** untuk merancang state DP yang benar dan efisien tanpa menebak-nebak.
- Memahami konsep properti Markov dalam DP: kapan dan mengapa sebuah dimensi harus ditambahkan ke dalam state.
- Mengetahui batas kedalaman rekursi stack memori dan teknik memilih pendekatan yang aman dari Runtime Error (Stack Overflow).
- Memahami intuisi dasar **Rolling Array** untuk mereduksi kompleksitas ruang memori.
- Mengenali dan menghindari 5 jebakan fatal yang paling sering menjatuhkan solusi DP dalam kontes.

---

## 🔍 1. Konsep & Intuisi: Top-Down vs Bottom-Up

Dalam Dynamic Programming, **rekurens matematika yang sama** dapat dievaluasi menggunakan dua paradigma yang berbeda:

1. **Top-Down (Memoisasi)**: Memulai dari submasalah target terbesar (misal `f(N)`), lalu secara rekursif memecahnya menjadi submasalah-submasalah yang lebih kecil saat dibutuhkan. Setiap hasil yang telah dihitung disimpan dalam *lookup table* (cache) agar tidak pernah dihitung ulang.
2. **Bottom-Up (Tabulasi)**: Memulai dari submasalah paling dasar (base case, misal `dp[0]` atau `dp[1]`), lalu mengisi tabel secara iteratif dengan urutan tertentu (biasanya menaik atau topologis) hingga mencapai submasalah target `dp[N]`.

### Analogi Sederhana: Membangun Piramida

- **Pendekatan Top-Down**: Kamu berdiri di puncak piramida dan ingin meletakkan batu puncak. Kamu bertanya ke bawah: *"Batu penopang di bawah saya sudah siap belum?"*. Jika belum, pertanyaan diteruskan ke bawah sampai ke tanah (base case). Begitu tanah siap, batu di atasnya diletakkan, dicatat, dan kamu naik kembali ke puncak.
- **Pendekatan Bottom-Up**: Kamu mulai langsung dari tanah. Kamu letakkan seluruh fondasi lapis demi lapis dari bawah ke atas secara teratur hingga mencapai puncak. Kamu tidak perlu bertanya ke siapa pun karena lapisan di bawahnya dijamin sudah selesai sebelum kamu mulai membangun lapisan di atasnya.

```
TOP-DOWN (Memoization)                    BOTTOM-UP (Tabulation)
   Mulai dari target                             Mulai dari dasar
       f(5)                                           dp[5]
      /    \                                            ▲
    f(4)   f(3) (cek cache!)                            │ iterasi menaik
    /  \                                              dp[2]
  f(3) f(2)                                           dp[1]
  /  \                                                dp[0] (base case)
f(2) f(1) ...                                   Membangun dari fondasi
```

### Visualisasi Graf Dependensi (DAG State)

Setiap masalah DP sebenarnya membentuk **Directed Acyclic Graph (DAG)**:
- Simpul (Node) = State
- Sisi Berarah (Edge) $u \to v$ = Dependensi (state $u$ membutuhkan hasil dari state $v$)

```
[State 0] ───► [State 1] ───► [State 2] ───► [State 3] ───► [State N]
   ▲              │              ▲              │
   └──────────────┴──────────────┘──────────────┘
```

- **Top-Down** menelusuri DAG ini menggunakan **DFS (Depth-First Search)** dengan memoisasi. Top-down otomatis menentukan urutan evaluasi melalui rekursi.
- **Bottom-Up** mengevaluasi simpul-simpul DAG mengikuti **Topological Sort** (urutan topologis). Programmer harus secara eksplisit menentukan urutan iterasi loop sehingga setiap state dievaluasi hanya setelah seluruh dependensinya selesai dihitung.

---

## 🧮 2. Analisis Kompleksitas & Perbandingan Mendalam

Berikut adalah perbandingan mendalam antara kedua paradigma:

| Kriteria | Top-Down (Memoization) | Bottom-Up (Tabulation) |
| :--- | :--- | :--- |
| **Gaya Penulisan** | Rekursif + tabel cache | Iteratif (looping `for` / `while`) |
| **Urutan Evaluasi** | Alami (on-demand via rekursi) | Ditentukan manual oleh programmer (harus topologis) |
| **Ruang Memori** | Tabel Cache + Stack Frame Rekursi | Hanya Tabel DP (bisa dioptimasi rolling array) |
| **Overhead Konstan** | Lebih lambat karena pemanggilan fungsi berulang | Sangat cepat (ramah instruksi CPU dan cache L1/L2) |
| **Evaluasi State Mati** | **Hanya menghitung state yang relevan/terjangkau** | Menghitung seluruh tabel (kecuali diberi pruning) |
| **Risiko Runtime Error** | Rentan **Stack Overflow** bila rekursi terlalu dalam | **Sangat aman** dari stack overflow |
| **Optimasi Memori** | Sulit mereduksi dimensi tabel | **Mudah** direduksi (misal $O(N \times W) \to O(W)$) |

### Bahaya Nyata: Stack Overflow pada Top-Down

Setiap pemanggilan fungsi dalam C++ mengalokasikan **Stack Frame** pada memori stack (berisi parameter fungsi, variabel lokal, dan return address).
- Di banyak sistem judge (dan OS default seperti Linux/macOS), ukuran memori stack dibatasi antara **1 MB hingga 8 MB** (meskipun memory limit total soal adalah 256 MB atau 512 MB).
- Satu frame fungsi rekursi biasanya berukuran 32 hingga 64 byte.
- Jika kedalaman rekursi mencapai $N = 10^5$ hingga $10^6$, tumpukan stack akan melebihi 8 MB dan menghasilkan **SIGSEGV / Runtime Error (Exit code 139)**!

> **Aturan Praktis (Rule of Thumb)**:
> - Kedalaman rekursi $\le 10^4$: Sangat aman untuk Top-Down.
> - Kedalaman rekursi $10^4 - 10^5$: Waspada, hindari passing objek besar by-value.
> - Kedalaman rekursi $> 10^5$: **Wajib pilih Bottom-Up** kecuali stack limit dinaikkan secara eksplisit.

---

## 📐 3. Empat Uji Desain State (The 4-Step State Design Framework)

Bagian tersulit dari Dynamic Programming bukan mengetik kodenya, melainkan **merancang definisinya (State)**. Jika state sudah benar, transisi dan kodenya sering kali hanya butuh beberapa baris.

Gunakan kerangka **"Empat Uji Desain State"** berikut sebelum menulis kode:

```
┌─────────────────────────────────────────────────────────────┐
│               EMPAT UJI DESAIN STATE DP                     │
├─────────────────────────────────────────────────────────────┤
│ 1. BISA DIKALIMATKAN?   Definisi lengkap & spesifik        │
│ 2. CUKUP INFORMASINYA?  Properti Markov (bebas riwayat)    │
│ 3. SETARA?              Masa depan identik untuk state sama│
│ 4. MUAT?                |State| × Biaya Transisi ≤ 10^8    │
└─────────────────────────────────────────────────────────────┘
```

### Uji 1: Bisa Dikalimatkan?
State harus dapat didefinisikan dengan satu kalimat bahasa manusia yang lengkap dan presisi.
- ❌ **Buruk**: `dp[i]` = *"hasil terbaik pada i"*. (Hasil apa? Apakah elemen ke-$i$ wajib diambil? Apakah kapasitas terpakai penuh?)
- ✅ **Baik**: `dp[i][w]` = *"nilai maksimum yang dapat diperoleh dari memilih subset barang indeks $0 \dots i$ dengan total bobot tepat $w$."*

### Uji 2: Cukup Informasinya? (Markov Property)
Sebuah sistem memiliki properti Markov jika: **Masa depan hanya bergantung pada state saat ini, bukan pada bagaimana kita sampai ke state tersebut.**
Tanyakan pada diri sendiri:
> *"Bila saya hanya diberi tahu indeks dan nilai state saat ini tanpa melihat riwayat langkah sebelumnya, bisakah saya menentukan langkah legal berikutnya secara pasti?"*
Jika jawabannya **TIDAK**, berarti ada informasi masa lalu yang hilang! Anda **wajib menambah dimensi**.

### Uji 3: Setara?
Apakah dua jalur berbeda yang berakhir pada state yang sama benar-benar memiliki masa depan yang setara?
Jika ada jalur A dan jalur B yang keduanya berakhir di posisi $i$, namun jalur A masih menyisakan 1 kupon gratis sedangkan jalur B kuponnya sudah habis, keduanya **TIDAK SETARA**. Menggabungkannya ke dalam satu state `dp[i]` akan menyebabkan hasil salah (Wrong Answer). Simpan status kupon dalam dimensi terpisah: `dp[i][kupon_tersisa]`.

### Uji 4: Muat?
Hitung perkiraan jumlah state dan waktu operasi:
$$\text{Total Operasi} \approx (\text{Banyaknya State}) \times (\text{Biaya Transisi per State})$$
- Jika Total Operasi $\le 10^8$, solusi akan lolos dalam batas waktu 1.0–2.0 detik.
- Jika memori tabel $\le 256\text{ MB}$ (misal tabel `int` berukuran $1000 \times 1000$ butuh $4\text{ MB}$, masih sangat aman).
- Jika state terlalu besar, pertimbangkan reduksi dimensi atau kompresi state (bitmask / coordinate compression).

---

## 🔬 4. Studi Kasus Penambahan Dimensi

Mari kita bedah mengapa soal-soal klasik memerlukan penambahan dimensi:

### Kasus A: Soal Liburan (Vacation / AtCoder DP-C)
- **Aturan**: Setiap hari kamu boleh memilih aktivitas A, B, atau C. Kamu **tidak boleh** memilih aktivitas yang sama dua hari berturut-turut.
- ❌ **State 1D**: `dp[i]` = kebahagiaan maksimal sampai hari ke-$i$.
  - *Gagal pada Uji 2*: Saat di hari ke-$i$, kita tidak tahu aktivitas apa yang dipilih di hari ke-$(i-1)$, sehingga kita tidak tahu pilihan mana yang dilarang!
- ✅ **State 2D**: `dp[i][act]` = kebahagiaan maksimal sampai hari ke-$i$ di mana aktivitas hari ke-$i$ adalah `act` ($0, 1,$ atau $2$).
  - Transisi:
    $$dp[i][A] = \text{poin}[i][A] + \max(dp[i-1][B], dp[i-1][C])$$

### Kasus B: Jalur Termurah dengan 1 Tiket Diskon
- **Aturan**: Cari biaya perjalanan minimum dari kota $1$ ke kota $N$. Kamu memiliki 1 kupon diskon untuk memotong biaya 1 tiket perjalanan sebesar 50%.
- ❌ **State 1D**: `dp[u]` = biaya minimum ke kota $u$.
  - *Gagal pada Uji 3*: Jalur yang sampai ke $u$ dengan kupon utuh jauh lebih berharga daripada jalur yang sampai ke $u$ dengan kupon sudah terpakai.
- ✅ **State 2D**: `dp[u][k]` = biaya minimum ke kota $u$ dengan status kupon $k$ ($0$: belum dipakai, $1$: sudah dipakai).

### Kasus C: Beli Saham dengan Cooldown (FSM DP)
- **Aturan**: Setelah menjual saham, kamu wajib istirahat 1 hari (cooldown) sebelum boleh membeli kembali.
- ✅ **State**: Representasikan sebagai state machine:
  - `hold[i]`: memegang saham di akhir hari $i$.
  - `sold[i]`: baru saja menjual saham di hari $i$.
  - `rest[i]`: tidak memegang saham dan tidak sedang cooldown di hari $i$.

---

## 💻 5. Implementasi C++ Komparatif: Top-Down vs Bottom-Up

Mari bandingkan implementasi problem klasik **Frog Jump (AtCoder DP-A)**:
Katak berada di batu $0$, ingin ke batu $N-1$. Dari batu $i$, boleh melompat ke $i+1$ atau $i+2$ dengan biaya $|h[i] - h[j]|$.

### Versi 1: Top-Down (Memoization)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;
vector<int> h;
vector<int> memo;

int solveTopDown(int i) {
    // Base Case: sudah di batu awal (indeks 0)
    if (i == 0) return 0;
    
    // Cek cache
    if (memo[i] != -1) return memo[i];
    
    // Transisi
    int ans = solveTopDown(i - 1) + abs(h[i] - h[i - 1]);
    if (i >= 2) {
        ans = min(ans, solveTopDown(i - 2) + abs(h[i] - h[i - 2]));
    }
    
    return memo[i] = ans; // Simpan ke cache & return
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    h.resize(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    
    memo.assign(n, -1); // Reset cache dengan sentinel -1
    cout << solveTopDown(n - 1) << "\n";
    return 0;
}
```

### Versi 2: Bottom-Up (Tabulation)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    
    vector<int> dp(n, INF);
    dp[0] = 0; // Base case
    
    // Evaluasi iteratif dari i = 1 sampai n-1
    for (int i = 1; i < n; i++) {
        dp[i] = min(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));
        if (i >= 2) {
            dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
        }
    }
    
    cout << dp[n - 1] << "\n";
    return 0;
}
```

---

## 🔄 6. Trace / Simulasi Langkah Demi Langkah

Misalkan $N = 4$ dengan tinggi $h = [10, 30, 40, 20]$.

### Simulasi Top-Down:
1. Panggil `solve(3)`: belum ada di cache.
2. Cabang 1: panggil `solve(2)`.
   - Cabang 1.1: panggil `solve(1)`.
     - Cabang 1.1.1: panggil `solve(0)` $\to$ **Base Case = 0**.
     - Kembali ke `solve(1)`: biaya $= 0 + |30 - 10| = 20$. Simpan `memo[1] = 20`.
   - Kembali ke `solve(2)`:
     - dari `solve(1)`: $20 + |40 - 30| = 30$.
     - coba `solve(0)`: hitung $0 + |40 - 10| = 30$.
     - `memo[2] = min(30, 30) = 30`.
3. Kembali ke `solve(3)`:
   - dari `solve(2)`: $30 + |20 - 40| = 50$.
   - Cabang 2: coba `solve(1)` $\to$ **HIT CACHE!** Langsung baca `memo[1] = 20` (tanpa rekursi ulang).
   - biaya $= 20 + |20 - 30| = 30$.
4. Hasil akhir: `min(50, 30) = 30`.

### Simulasi Bottom-Up:
Inisialisasi: `dp = [0, INF, INF, INF]`
- $i = 1$: `dp[1] = min(INF, dp[0] + |30 - 10|) = 20`.
- $i = 2$:
  - lompat dari 1: `dp[1] + |40 - 30| = 20 + 10 = 30`.
  - lompat dari 0: `dp[0] + |40 - 10| = 0 + 30 = 30`.
  - `dp[2] = min(30, 30) = 30`.
- $i = 3$:
  - lompat dari 2: `dp[2] + |20 - 40| = 30 + 20 = 50`.
  - lompat dari 1: `dp[1] + |20 - 30| = 20 + 10 = 30`.
  - `dp[3] = min(50, 30) = 30`.
Hasil terbaca langsung di `dp[3] = 30`.

---

## 📦 7. Pengenalan Rolling Array

Perhatikan bahwa pada Frog Jump:
- `dp[i]` hanya membutuhkan `dp[i-1]` dan `dp[i-2]`.
- Nilai `dp[i-3]`, `dp[i-4]`, dst. tidak akan pernah dibaca lagi!

Oleh karena itu, kita tidak butuh array berukuran $N$. Kita hanya butuh 3 variabel yang berputar (rolling):
```cpp
int prev2 = 0; // dp[0]
int prev1 = abs(h[1] - h[0]); // dp[1]

for (int i = 2; i < n; i++) {
    int cur = min(prev1 + abs(h[i] - h[i - 1]), prev2 + abs(h[i] - h[i - 2]));
    prev2 = prev1;
    prev1 = cur;
}
```
Kompleksitas memori berkurang dari **$O(N)$ menjadi $O(1)$**!

> ⚠️ **Catatan Penting**: Jika Anda menggunakan Rolling Array, Anda **kehilangan riwayat**, sehingga **tidak bisa merekonstruksi jalur/pilihan solusi**. Jika soal meminta *"tampilkan urutan batu yang dilewati"*, Anda wajib menyimpan seluruh tabel $O(N)$.

---

## ⚠️ 8. Lima Jebakan Umum (Common Pitfalls)

1. **Lupa Mereset Cache pada Multi-Testcase**:
   Pada soal dengan $T$ testcase, array `memo` global harus di-`memset` atau di-`assign` ulang di setiap testcase. Jika lupa, sisa perhitungan testcase sebelumnya akan terbawa dan menyebabkan WA.
2. **Sentinel Collision (-1 sebagai tanda belum dihitung)**:
   Jika kemungkinan nilai sah dari fungsi adalah $-1$ (misalnya keuntungan rugi), maka menggunakan `-1` sebagai penanda *"belum dihitung"* akan membuat program melakukan rekursi berulang kali (TLE).
   *Solusi*: Gunakan array boolean `visited[i]` terpisah, atau gunakan sentinel nilai lain seperti `INF` atau `-2`.
3. **Stack Overflow pada Top-Down**:
   Jika $N = 5 \times 10^5$, rekursi linear hampir pasti menabrak batas stack frame OS (biasanya 8 MB). Pilihlah Bottom-Up secara default untuk $N > 10^5$.
4. **Salah Menentukan Arah Loop Iterasi**:
   Pada Bottom-Up, selalu pastikan state prasyarat sudah dihitung sebelum state yang membutuhkannya dievaluasi.
5. **Menyimpan Terlalu Banyak Riwayat di State**:
   Hanya simpan informasi yang secara langsung memengaruhi keputusan masa depan. Jangan simpan seluruh urutan elemen ke dalam state!

---

## 🎯 9. Rangkuman & Action Plan

- Gunakan **Top-Down** ketika:
  - Ruang state sangat renggang (sparse), hanya sedikit state yang benar-benar tercapai.
  - Urutan evaluasi topologis sangat rumit untuk dirumuskan secara iteratif.
- Gunakan **Bottom-Up** ketika:
  - $N$ besar ($> 10^5$) untuk menghindari overhead pemanggilan fungsi dan risiko stack overflow.
  - Ingin melakukan optimasi memori menggunakan Rolling Array.
- Selalu jalankan **Empat Uji Desain State**: Bisa dikalimatkan, Cukup informasinya, Setara, dan Muat.
