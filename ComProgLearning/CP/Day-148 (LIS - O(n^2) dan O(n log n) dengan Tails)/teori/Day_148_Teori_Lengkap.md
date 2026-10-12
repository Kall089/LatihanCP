# Day 148 — Teori Lengkap: LIS, O(n²) dan O(n log n)

---

## 1. Masalah

Diberikan array `a[0..n-1]`. Cari **subsekuens** (tidak harus berdekatan,
urutan dipertahankan) terpanjang yang nilainya **naik**.

Contoh: `a = [10, 9, 2, 5, 3, 7, 101, 18]`.
Salah satu LIS: `[2, 3, 7, 18]`, panjang 4. Juga `[2, 5, 7, 101]`, juga 4.
Jawaban untuk "panjangnya" unik; "barisannya" tidak.

**Subsekuens vs substring.** Substring harus berdekatan. Subsekuens tidak.
`[2, 7, 18]` adalah subsekuens tapi bukan substring. Ini pembeda yang sering
terlewat saat membaca soal.

---

## 2. Kenapa Greedy Gagal

Godaan pertama: "ambil terus selama nilainya naik". Untuk
`[1, 100, 2, 3, 4]`, greedy dari kiri mengambil `1, 100` lalu berhenti —
panjang 2. Jawaban benarnya `1, 2, 3, 4` — panjang 4.

Masalahnya, mengambil `100` lebih awal menutup semua pilihan berikutnya.
Keputusan yang tampak baik secara lokal merusak masa depan. Itu tanda khas
bahwa soal ini perlu DP.

---

## 3. Versi O(n²)

**Definisi.** `dp[i]` = panjang LIS yang **berakhir tepat di `i`**.

Perhatikan bahwa definisi "sampai `i`" tidak bekerja: kita tidak akan tahu
nilai ekornya, sehingga tidak bisa memutuskan apakah `a[i]` boleh disambung.
Ini pelajaran yang sama seperti Kadane di Day 143.

**Rekurens.**

```
dp[i] = 1 + max{ dp[j] : j < i dan a[j] < a[i] }      (1 kalau himpunannya kosong)
jawaban = max atas SELURUH dp[i]
```

```cpp
vector<int> dp(n, 1);
for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)
        if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
int ans = *max_element(dp.begin(), dp.end());
```

`O(n²)` waktu. Cukup sampai `n ≈ 5000`.

⚠️ **Jawabannya `max(dp)`, bukan `dp[n-1]`.** Karena definisinya "berakhir
tepat di `i`", elemen terakhir belum tentu bagian dari LIS.

⚠️ **Untuk versi tidak-menurun**, ganti `a[j] < a[i]` menjadi `a[j] <= a[i]`.

Versi ini juga yang paling mudah dimodifikasi: LIS berbobot (ganti `+1`
dengan `+w[i]`), rekonstruksi (simpan `par[i] = j`), dan penghitungan (bawa
array `cnt`).

---

## 4. Versi O(n log n) — Array `tails`

Ini bagian yang harus benar-benar kamu pahami, bukan hafal.

### 4.1 Apa Isi `tails`

> **`tails[k]` = nilai EKOR TERKECIL di antara SEMUA subsekuens naik yang
> panjangnya `k+1`, dengan hanya mempertimbangkan elemen yang sudah diproses.**

Baca ulang kalimat itu. Setiap kata penting:

- **ekor** — nilai elemen terakhirnya, bukan panjangnya, bukan indeksnya.
- **terkecil** — di antara semua kandidat sepanjang itu, kita menyimpan yang
  ekornya paling kecil.
- **panjang `k+1`** — indeks `k` di array berkorespondensi dengan panjang
  `k+1`.

**Kenapa yang terkecil?** Karena ekor yang lebih kecil selalu **setidaknya
sama baiknya** untuk masa depan: apa pun yang bisa disambung ke ekor besar,
bisa juga disambung ke ekor kecil. Menyimpan yang terkecil tidak pernah
merugikan. Ini adalah **exchange argument** — pola yang sama seperti di
greedy (Day 71).

### 4.2 Kenapa `tails` Selalu Terurut Menaik

Ini bukan kebetulan; tanpanya `lower_bound` tidak sah.

> **Klaim.** `tails[0] < tails[1] < ... < tails[m-1]` setiap saat.

**Bukti.** Ambil sembarang `k`. Ada subsekuens naik berpanjang `k+2` yang
ekornya `tails[k+1]`. Buang elemen terakhirnya: kita dapat subsekuens naik
berpanjang `k+1` yang ekornya **lebih kecil** dari `tails[k+1]` (karena
barisannya naik). Karena `tails[k]` adalah ekor **terkecil** di antara semua
subsekuens berpanjang `k+1`, maka `tails[k] ≤` ekor tersebut `< tails[k+1]`. ∎

Jadi kita boleh melakukan binary search di atasnya.

### 4.3 Algoritmanya

```cpp
vector<int> tails;
for (int x : a) {
    auto it = lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end()) tails.push_back(x);   // x memperpanjang LIS
    else *it = x;                                // x memperbaiki ekor
}
int lis = tails.size();
```

Dua kasus, dan masing-masing punya arti:

- **`x` lebih besar dari semua isi `tails`** → ia bisa disambung ke subsekuens
  terpanjang yang ada, menghasilkan yang lebih panjang lagi → `push_back`.
- **Selain itu** → `lower_bound` menemukan posisi `p` pertama dengan
  `tails[p] >= x`. Artinya ada subsekuens berpanjang `p+1` yang bisa diakhiri
  oleh `x`, dan `x` lebih kecil (atau sama) dari ekor yang tercatat → perbarui.
  Panjang LIS **tidak berubah**, tapi masa depan jadi lebih terbuka.

`O(n log n)`: satu binary search per elemen.

### 4.4 `tails` BUKAN LIS-nya

Ini kesalahpahaman paling umum tentang algoritma ini.

Contoh: `a = [10, 9, 2, 5, 3, 7, 101, 18]`.

| x | aksi | `tails` setelahnya |
|---|---|---|
| 10 | push | `[10]` |
| 9 | ganti pos 0 | `[9]` |
| 2 | ganti pos 0 | `[2]` |
| 5 | push | `[2, 5]` |
| 3 | ganti pos 1 | `[2, 3]` |
| 7 | push | `[2, 3, 7]` |
| 101 | push | `[2, 3, 7, 101]` |
| 18 | ganti pos 3 | `[2, 3, 7, 18]` |

Di sini `[2,3,7,18]` kebetulan **memang** sebuah LIS. Tapi coba
`a = [1, 6, 7, 2, 3]`:

| x | `tails` |
|---|---|
| 1 | `[1]` |
| 6 | `[1, 6]` |
| 7 | `[1, 6, 7]` |
| 2 | `[1, 2, 7]` |
| 3 | `[1, 2, 3]` |

`tails` akhirnya `[1, 2, 3]`, dan panjang 3 memang benar. Tetapi `[1,2,3]`
**adalah** subsekuens di sini... hampir menipu. Perhatikan langkah keempat:
`tails = [1, 2, 7]` — barisan itu **bukan** subsekuens yang sah dari
`[1,6,7,2]`, karena `2` muncul **setelah** `7` di array asli. Isi `tails`
di tengah jalan bisa berupa gado-gado dari beberapa subsekuens berbeda.

> **Yang dijamin benar hanyalah `tails.size()`.** Untuk mendapatkan barisannya,
> gunakan rekonstruksi di bagian 6.

### 4.5 Ketat vs Tidak Menurun

| jenis | syarat | fungsi |
|---|---|---|
| **strictly increasing** | `a < b` | `lower_bound` |
| **non-decreasing** | `a ≤ b` | `upper_bound` |

**Kenapa?** `lower_bound(x)` menemukan elemen pertama `>= x`, dan
menggantinya. Artinya nilai yang **sama dengan** `x` ikut tergantikan — jadi
`x` tidak boleh menyambung dirinya sendiri → ketat.

`upper_bound(x)` menemukan elemen pertama `> x`. Nilai yang sama dengan `x`
**dilewati**, sehingga `x` boleh disambung ke belakang nilai yang sama → tidak
menurun.

**Uji cepat dengan `[1, 1, 1]`:** versi ketat harus memberi `1`; versi tidak
menurun harus memberi `3`. Kalau kodemu memberi angka lain, kamu memakai
fungsi yang salah. Selalu uji ini.

---

## 5. Trace Lengkap

`a = [3, 1, 4, 1, 5, 9, 2, 6]`, ketat naik.

| i | x | lower_bound | aksi | `tails` | panjang |
|---|---|---|---|---|---|
| 0 | 3 | end | push | `[3]` | 1 |
| 1 | 1 | pos 0 | `tails[0]=1` | `[1]` | 1 |
| 2 | 4 | end | push | `[1,4]` | 2 |
| 3 | 1 | pos 0 | `tails[0]=1` | `[1,4]` | 2 |
| 4 | 5 | end | push | `[1,4,5]` | 3 |
| 5 | 9 | end | push | `[1,4,5,9]` | 4 |
| 6 | 2 | pos 1 | `tails[1]=2` | `[1,2,5,9]` | 4 |
| 7 | 6 | pos 3 | `tails[3]=6` | `[1,2,5,6]` | 4 |

Jawaban 4. Contoh LIS yang sah: `[1, 4, 5, 9]` atau `[1, 4, 5, 6]`.
Perhatikan `tails` akhir `[1,2,5,6]` — barisan itu **bukan** subsekuens dari
`a` (nilai `2` muncul di indeks 6, setelah `5` di indeks 4).

---

## 6. Rekonstruksi Salah Satu LIS

Idenya: saat memproses `a[i]`, catat **posisi** `p` tempat ia mendarat di
`tails`, dan catat **siapa** elemen di `tails[p-1]` saat itu.

```cpp
vector<int> tails;          // menyimpan NILAI
vector<int> idx;            // idx[k] = INDEKS elemen yang mengisi tails[k]
vector<int> par(n, -1);     // par[i] = indeks elemen sebelum i pada LIS

for (int i = 0; i < n; i++) {
    int p = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
    if (p > 0) par[i] = idx[p - 1];          // penyambungnya
    if (p == (int)tails.size()) { tails.push_back(a[i]); idx.push_back(i); }
    else { tails[p] = a[i]; idx[p] = i; }
}

vector<int> lis;
for (int v = idx.back(); v != -1; v = par[v]) lis.push_back(a[v]);
reverse(lis.begin(), lis.end());
```

**Kenapa ini benar?** `par[i]` menunjuk ke elemen yang, pada saat `i`
diproses, mengakhiri subsekuens berpanjang `p` yang terbaik. Elemen itu
muncul **sebelum** `i` di array (karena sudah diproses) dan nilainya **lebih
kecil** dari `a[i]` (karena `tails` terurut dan `p-1 < p`). Jadi rantainya
sah. Panjang rantai dari `idx.back()` persis `tails.size()`.

⚠️ Jangan mengembalikan isi `tails` — lihat 4.4.

---

## 7. Varian dan Penyamaran

### 7.1 LDS (Longest Decreasing Subsequence)

Balik array-nya, atau negasikan semua nilainya, lalu jalankan LIS. Dua-duanya
benar; negasi lebih aman kalau kamu juga butuh indeksnya.

### 7.2 Menghitung Banyak LIS

Versi `O(n²)` dengan dua array:

```cpp
vector<int> len(n, 1), cnt(n, 1);
for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)
        if (a[j] < a[i]) {
            if (len[j] + 1 > len[i])      { len[i] = len[j] + 1; cnt[i] = cnt[j]; }
            else if (len[j] + 1 == len[i])  cnt[i] += cnt[j];
        }
// jumlahkan cnt[i] untuk semua i dengan len[i] == maksimum
```

Pola `>` menyalin, `==` menjumlahkan ini sama persis dengan menghitung jalur
terpendek di Day 127.

Untuk `O(n log n)`, butuh Fenwick tree atas nilai terkompresi yang menyimpan
pasangan `(panjang maksimum, jumlah)` — itu Day 170.

### 7.3 Box Stacking / Russian Doll Envelopes

Diberi `n` amplop `(w, h)`. Amplop `A` muat di dalam `B` kalau
`wA < wB` **dan** `hA < hB`. Cari rantai terpanjang.

**Solusi:** urutkan berdasarkan `w` **menaik**; kalau `w` sama, urutkan `h`
**MENURUN**. Lalu cari LIS pada barisan `h`.

**Kenapa tie-break-nya menurun?** Kalau dua amplop punya `w` yang sama, mereka
tidak boleh dua-duanya masuk rantai. Dengan mengurutkan `h` menurun untuk `w`
yang sama, barisan `h` mereka menjadi **menurun**, sehingga LIS (yang ketat
naik) secara otomatis hanya bisa mengambil salah satu. Ini trik yang sangat
elegan, dan tanpa ia jawabannya akan terlalu besar.

Uji: `[(1,1), (1,2), (2,3)]`. Dengan tie-break menurun urutannya
`(1,2), (1,1), (2,3)` → `h = [2, 1, 3]` → LIS = 2 ✓. Dengan tie-break menaik
urutannya `(1,1), (1,2), (2,3)` → `h = [1, 2, 3]` → LIS = 3 ✗ (salah, karena
dua amplop pertama sama-sama berlebar 1).

### 7.4 Teorema Dilworth

Jumlah **minimum** barisan tidak-naik yang diperlukan untuk menutupi seluruh
array = panjang barisan **naik** terpanjang. (Dan sebaliknya.)

Ini yang membuat soal "berapa minimum tumpukan kartu" (patience sorting) dan
"berapa minimum sistem antirudal" (klasik) diselesaikan dengan LIS.

### 7.5 LIS sebagai Jalur Terpanjang di DAG

Bangun DAG dengan edge `i → j` kalau `i < j` dan `a[i] < a[j]`. LIS = jalur
terpanjang (Day 120). Versi ini `O(n²)` karena edge-nya banyak, tetapi
memperlihatkan bahwa LIS bukan makhluk aneh — ia satu kasus DP di DAG.

### 7.6 LIS Berbobot (AtCoder DP-Q "Flowers")

Alih-alih memaksimalkan **panjang**, maksimalkan **jumlah bobot**. Versi
`O(n²)`-nya jelas; versi `O(n log n)`-nya butuh Fenwick prefix-max (Day 170).

---

## 8. Kesalahan yang Paling Sering Terjadi

1. **Mengira `tails` adalah LIS-nya.** Hanya ukurannya yang benar.
2. **`lower_bound` / `upper_bound` tertukar.** Uji dengan `[1,1,1]`.
3. **Mengambil jawaban `O(n²)` dari `dp[n-1]`** alih-alih `max(dp)`.
4. **`tails` tidak dikosongkan** antar test case.
5. **Box stacking tanpa tie-break menurun.**
6. **Rekonstruksi memakai isi `tails`** → barisan tidak sah.
7. **Menghitung banyak LIS tanpa memisahkan per panjang** → hasil terlalu
   besar.
8. **Memakai `0` sebagai nilai netral** padahal `a[i]` boleh negatif.
9. **Membaca "substring" sebagai "subsekuens"** atau sebaliknya. Untuk
   substring naik terpanjang (LC 674) jawabannya cukup satu sapuan `O(n)`,
   bukan LIS.

---

## 9. Ringkasan

- `O(n²)`: `dp[i]` = LIS yang **berakhir tepat di `i`**; jawabannya `max(dp)`.
- `O(n log n)`: `tails[k]` = **ekor terkecil** untuk panjang `k+1`. `tails`
  terurut menaik (terbukti), jadi `lower_bound` sah.
- `lower_bound` → ketat naik; `upper_bound` → tidak menurun.
- **`tails` bukan LIS-nya**; rekonstruksi butuh `par[]` dan `idx[]`.
- Box stacking = sort `w` naik, `h` **menurun** saat seri, lalu LIS pada `h`.
- Dilworth menghubungkan LIS dengan partisi minimum — sumber banyak soal yang
  tidak menyebut LIS sama sekali.
