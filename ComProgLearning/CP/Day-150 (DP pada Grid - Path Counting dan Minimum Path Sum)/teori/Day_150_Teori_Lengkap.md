# Day 150 — Teori Lengkap: DP pada Grid

---

## 1. Kenapa Materi Ini Terasa Mudah (dan Kenapa Itu Menipu)

Grid DP biasanya jadi soal DP pertama yang dikuasai orang, karena tabelnya
terlihat persis seperti gridnya. Bahayanya: karena mudah, orang menghafal
`dp[i][j] = dp[i-1][j] + dp[i][j-1]` tanpa tahu **kapan rumus itu berhenti
berlaku**. Bagian 7 hari ini justru tentang batasnya.

---

## 2. Grid Kanan-Bawah Adalah DAG

Ini bukan analogi; ini fakta yang bisa dibuktikan.

Setiap sel `(i, j)` adalah simpul. Gerakan yang diizinkan:
`(i, j) → (i+1, j)` dan `(i, j) → (i, j+1)`.

> **Klaim.** Graf ini tidak mungkin punya siklus.

**Bukti.** Definisikan `f(i, j) = i + j`. Setiap gerakan yang diizinkan
menaikkan `f` tepat 1. Kalau ada siklus, kita akan kembali ke sel awal dengan
`f` yang sudah bertambah — mustahil, karena `f` untuk satu sel adalah nilai
tetap. ∎

Fungsi seperti `f` disebut **monovariant** (Day 82), dan trik "cari besaran
yang selalu naik" adalah cara standar membuktikan sesuatu adalah DAG.

**Konsekuensinya besar.** Day 120 mengajarkan bahwa DP di DAG memerlukan
urutan topologis. Di sini urutan itu **gratis**: memproses baris demi baris
dari kiri ke kanan otomatis memenuhi syarat, karena ketika kita sampai di
`(i, j)`, sel `(i-1, j)` (baris sebelumnya) dan `(i, j-1)` (kiri) sudah
selesai.

> Grid DP = DP di DAG dengan urutan topologis yang tidak perlu dihitung.

---

## 3. Menghitung Jalur

**Soal.** Dari `(0,0)` ke `(R-1, C-1)`, hanya boleh kanan dan bawah. Ada
berapa jalur?

**Definisi.** `dp[i][j]` = banyak jalur dari `(0,0)` ke `(i,j)`.

**Keputusan terakhir.** Langkah terakhir datang dari atas atau dari kiri. Dua
himpunan jalur itu saling lepas (dibedakan oleh langkah terakhirnya), jadi
boleh dijumlahkan.

```
dp[i][j] = dp[i-1][j] + dp[i][j-1]
dp[0][0] = 1
sel di luar grid dianggap 0
```

**Kompleksitas.** `O(R·C)`.

**Modulo wajib.** Untuk `R = C = 1000`, jumlah jalurnya `C(1998, 999)` —
angka dengan ratusan digit. Soal selalu meminta modulo `10^9+7`.

### 3.1 Menghindari `if` Tepi dengan Padding

Menulis `if (i > 0) ... if (j > 0) ...` di setiap sel membuat kode panjang dan
rawan. Lebih bersih: pakai indeks `1..R` dan `1..C`, dan biarkan baris `0` dan
kolom `0` berisi **elemen identitas** (0 untuk penjumlahan).

```cpp
vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
dp[1][1] = 1;                                  // set MANUAL
for (int i = 1; i <= R; i++)
    for (int j = 1; j <= C; j++)
        if (!(i == 1 && j == 1))
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
```

⚠️ `dp[1][1]` harus di-set manual dan **dilewati** di dalam loop, karena
tetangganya semua nol dan akan menimpanya dengan 0.

---

## 4. Halangan

Beberapa sel tidak boleh diinjak (ditandai `#`).

**Untuk penghitungan jalur:**

```cpp
if (grid[i][j] == '#') { dp[i][j] = 0; continue; }
```

**Kenapa ini cukup?** Karena `0` adalah elemen identitas penjumlahan. Sel
terhalang menyumbang nol ke tetangganya, sehingga semua jalur yang
melewatinya otomatis "mati" tanpa perlu logika tambahan.

⚠️ **Sel awal atau tujuan bisa saja terhalang.** Kalau `(0,0)` adalah `#`,
jawabannya 0 — tapi banyak kode langsung menulis `dp[0][0] = 1` sebelum
memeriksa. Periksa dulu.

⚠️ **Tugaskan `0` secara eksplisit**, jangan hanya `continue` pada array yang
mungkin punya nilai sisa (misalnya pada soal multi-test).

**Untuk minimum, `0` SALAH.** Nol berarti "gratis", sehingga jalur haram malah
jadi pilihan termurah. Sentinelnya harus `INF`:

```cpp
if (grid[i][j] == '#') { dp[i][j] = INF; continue; }
...
ll best = min(dp[i-1][j], dp[i][j-1]);
if (best >= INF) dp[i][j] = INF;                 // LEWATI, jangan tambahkan
else             dp[i][j] = a[i][j] + best;
```

⚠️ **Sel bersentinel tidak boleh dipakai merelaksasi.** `INF + a[i][j]`
menghasilkan angka besar yang bukan `INF` lagi, dan nilai sampah itu menular
ke seluruh grid. Ini persis kesalahan yang sama seperti di Day 120.

Aturan umumnya: **sentinel harus elemen identitas dari operator gabungnya.**
`0` untuk `+`, `+INF` untuk `min`, `-INF` untuk `max`.

---

## 5. Jumlah Jalur Minimum

**Definisi.** `dp[i][j]` = biaya minimum mencapai `(i,j)`, termasuk biaya sel
itu sendiri.

```
dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1])
dp[0][0] = a[0][0]
```

### 5.1 Trace

```
grid       dp
1 3 1      1  4  5
1 5 1  ->  2  7  6
4 2 1      6  8  7
```

`dp[2][2] = 7`, lewat `1 → 3 → 1 → 1 → 1`. Perhatikan `dp[1][2] = 6`, bukan
`5 + 1 = 8` — karena datang dari atas (`5`) lebih murah daripada dari kiri
(`7`).

### 5.2 Rekonstruksi

Telusuri balik dari `(R-1, C-1)`:

```cpp
vector<pair<int,int>> path;
int i = R - 1, j = C - 1;
while (i > 0 || j > 0) {
    path.push_back({i, j});
    if (i == 0)                             j--;
    else if (j == 0)                        i--;
    else if (dp[i-1][j] <= dp[i][j-1])      i--;
    else                                    j--;
}
path.push_back({0, 0});
reverse(path.begin(), path.end());
```

⚠️ Loop-nya `i > 0 || j > 0`, bukan `&&` — kalau salah satu sudah 0, sisanya
tetap harus ditelusuri.

⚠️ Rekonstruksi butuh tabel penuh; kalau kamu sudah memakai rolling array
(bagian 6), informasinya sudah terbuang.

---

## 6. Rolling Array — Memori `O(C)`

`dp[i][j]` hanya butuh baris `i-1` dan sel di kirinya. Satu baris cukup:

```cpp
vector<ll> dp(C, 0);
dp[0] = 1;
for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
        if (grid[i][j] == '#') { dp[j] = 0; continue; }
        if (j > 0) dp[j] = (dp[j] + dp[j-1]) % MOD;
        // dp[j] sebelum ditulis = nilai baris ATAS; dp[j-1] = nilai KIRI
    }
```

**Kenapa ini bekerja?** Saat memproses `(i, j)`, isi `dp[j]` masih berasal dari
baris `i-1` (belum ditimpa), dan `dp[j-1]` sudah diperbarui ke baris `i`.
Persis dua nilai yang dibutuhkan.

⚠️ **Loop `j` harus dari kiri ke kanan.** Dibalik, `dp[j-1]` masih berisi
nilai baris atas, bukan kiri.

⚠️ Untuk minimum: `dp[j] = a[i][j] + min(dp[j], dp[j-1])`, dengan penanganan
khusus untuk `j == 0` (hanya bisa dari atas).

---

## 7. Kapan Grid DP BERHENTI Berlaku

Ini bagian yang paling sering dilewatkan.

### 7.1 Gerakan 4 Arah

Kalau boleh bergerak ke atas dan ke kiri juga, argumen monovariant di bagian 2
runtuh — `i + j` tidak lagi selalu naik. Grafnya **bersiklus**, jadi tidak ada
urutan topologis, jadi tidak ada DP.

| pertanyaan | alat yang benar |
|---|---|
| jalur terpendek, biaya seragam | **BFS** (Day 114) |
| jalur termurah, biaya non-negatif | **Dijkstra** (Day 127) |
| meminimalkan edge termahal | Dijkstra minimax (Day 127) |
| jalur **terpanjang** tanpa mengulang sel | **NP-hard** |
| menghitung jalur tanpa mengulang sel | #P-hard (hanya brute force / bitmask) |

Kesalahan yang umum: mencoba "menambal" DP dengan iterasi berulang sampai
konvergen. Itu sebenarnya Bellman-Ford yang ditulis ulang dengan buruk.

### 7.2 Grid Sangat Besar Tanpa Halangan

Kalau `R, C ≤ 10^6` dan tidak ada halangan, tabel `O(R·C)` mustahil. Tapi
jawabannya punya bentuk tertutup:

```
banyak jalur = C(R + C - 2, R - 1)
```

**Kenapa?** Setiap jalur adalah barisan `R-1` langkah bawah dan `C-1` langkah
kanan; jalur ditentukan sepenuhnya oleh **posisi mana** yang dipilih untuk
langkah bawah. Hitung dengan faktorial + invers modular (Day 90-an),
`O(R + C)`.

**Halangan sedikit (`k ≤ 3000`)?** Ada teknik "inclusion-exclusion terurut":
urutkan halangan, `f[i]` = jalur ke halangan ke-`i` tanpa melewati halangan
lain, lalu kurangi. `O(k²)`. Itu soal AtCoder DP-Y.

---

## 8. Varian yang Sering Muncul

### 8.1 Segitiga (LC 120)

Tetangganya `(i-1, j-1)` dan `(i-1, j)` — bukan atas dan kiri. Rekurensnya
sama bentuknya; yang berubah hanya definisi "tetangga". Ini pengingat bahwa
grid DP bukan tentang bentuk persegi, melainkan tentang **struktur DAG**.

### 8.2 Dimensi Tambahan: Kunci / Koin / Kupon

"Boleh menghancurkan sampai `K` tembok" → `dp[i][j][k]`. Dimensi grid tetap
dikendalikan urutan baris; dimensi tambahan diproses di dalamnya.
`O(R·C·K)`.

### 8.3 DUA Jalur Sekaligus

"Dua orang berjalan dari `(0,0)` ke `(R-1,C-1)`, maksimalkan total permen yang
dikumpulkan; sel yang dilewati keduanya hanya dihitung sekali."

Kuncinya: buat keduanya melangkah **bersamaan**. Setelah `k` langkah, keduanya
berada di sel dengan `i + j = k`. Jadi kalau kita tahu `k` dan `i1` dan `i2`,
kolomnya tertentukan: `j1 = k - i1`, `j2 = k - i2`.

```
dp[k][i1][i2] , transisi dari 4 kombinasi (masing-masing bawah/kanan)
kalau i1 == i2 (sel sama), hitung nilainya SEKALI
```

`O(R·C·R)` — bukan `O((R·C)²)` seperti yang dikhawatirkan. Trik "langkah
bersamaan sehingga satu dimensi bisa disimpulkan" muncul di banyak soal.

### 8.4 DP Arah Terbalik (LC 174 Dungeon Game)

Kadang DP maju tidak bekerja, karena kebutuhan di masa depan memengaruhi
keputusan sekarang. "Berapa HP minimum di awal supaya tidak pernah mencapai 0"
harus dihitung dari **tujuan ke awal**. Kalau DP majumu terasa buntu, coba
balik arahnya sebelum menyerah.

### 8.5 Tepat K Belokan

`dp[i][j][arah][k]`. Dimensi arah diperlukan karena "belokan" bergantung pada
arah datang.

---

## 9. Kesalahan yang Paling Sering Terjadi

1. **Sel awal terhalang tapi `dp[0][0] = 1` ditulis lebih dulu.**
2. **Halangan pada soal minimum diisi `0`** alih-alih `INF`.
3. **Sentinel `INF` ikut merelaksasi** → nilai sampah menular.
4. **Lupa modulo.**
5. **Rolling array dengan loop `j` dari kanan.**
6. **Rekonstruksi dari tabel yang sudah digulung.**
7. **Mencoba DP pada gerakan 4 arah.**
8. **`int` untuk jumlah biaya** — `10^6` sel × `10^9` overflow.
9. **`dp[1][1]` tidak dilewati** pada versi padding, sehingga tertimpa 0.
10. **Membaca grid karakter dengan `cin >> c` per sel** padahal inputnya per
    baris (atau sebaliknya). Baca formatnya baik-baik.

---

## 10. Ringkasan

- Grid kanan-bawah adalah **DAG** karena `i + j` selalu naik; urutan
  topologisnya gratis.
- Hitung jalur: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`, halangan → `0`.
- Jumlah minimum: `dp[i][j] = a[i][j] + min(atas, kiri)`, halangan → `INF`,
  dan sentinel harus **dilewati**.
- Sentinel selalu **elemen identitas operator gabung**: `0`, `+INF`, `-INF`.
- Padding menghilangkan `if` tepi; rolling array memangkas memori jadi `O(C)`
  dengan biaya kehilangan rekonstruksi.
- Tanpa halangan → kombinatorika `C(R+C-2, R-1)`.
- 4 arah → bukan DP lagi: BFS atau Dijkstra.
