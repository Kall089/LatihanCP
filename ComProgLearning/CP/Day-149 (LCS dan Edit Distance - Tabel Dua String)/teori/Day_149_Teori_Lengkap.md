# Day 149 — Teori Lengkap: LCS & Edit Distance

---

## 1. Loncatan Konseptual Hari Ini

Sampai Day 148, semua DP kita memakai **satu** indeks: posisi di dalam satu
array. Hari ini ada **dua** string, dan karenanya dua indeks. Loncatannya
kecil tapi penting:

> `dp[i][j]` = jawaban untuk **prefiks** `a[0..i-1]` dan **prefiks**
> `b[0..j-1]`.

Perhatikan konvensi indeksnya, karena ini sumber bug nomor satu:

- Tabelnya berukuran `(n+1) × (m+1)`, **1-indexed**.
- String-nya tetap **0-indexed**.
- Jadi huruf terakhir dari prefiks `i` adalah `a[i-1]`, bukan `a[i]`.

Baris `0` dan kolom `0` melambangkan **string kosong**, dan itulah yang
memberi kita base case yang bersih.

---

## 2. Kenapa "Huruf Terakhir" Adalah Pertanyaan yang Tepat

Semua DP dua string yang akan kamu temui berputar pada satu pertanyaan di
setiap sel:

> **Apakah `a[i-1]` sama dengan `b[j-1]`?**

Alasannya sama seperti Day 143: kita mencari **keputusan terakhir**. Untuk dua
string, keputusan terakhir selalu tentang huruf terakhir masing-masing prefiks:
dipakai, dibuang, dicocokkan, atau diganti.

Dari pertanyaan itu lahir maksimal empat kemungkinan, dan setiap masalah
memilih subset serta operator gabungnya sendiri:

| tetangga | artinya |
|---|---|
| `dp[i-1][j-1]` (diagonal) | pakai/cocokkan **keduanya** |
| `dp[i-1][j]` (atas) | buang `a[i-1]` |
| `dp[i][j-1]` (kiri) | buang `b[j-1]` |
| `dp[i][j]` sendiri | (dipakai pada varian dengan biaya) |

---

## 3. LCS — Longest Common Subsequence

**Soal.** Cari subsekuens terpanjang yang muncul di **kedua** string.
(Subsekuens: urutan dipertahankan, tidak harus berdekatan.)

**Definisi.** `dp[i][j]` = panjang LCS dari `a[0..i-1]` dan `b[0..j-1]`.

**Rekurens.**

```
kalau a[i-1] == b[j-1] :  dp[i][j] = dp[i-1][j-1] + 1
kalau tidak            :  dp[i][j] = max(dp[i-1][j], dp[i][j-1])
base                   :  dp[0][j] = dp[i][0] = 0
```

**Kenapa saat cocok kita TIDAK perlu mempertimbangkan `max(atas, kiri)`?**
Ini pertanyaan yang bagus dan jawabannya tidak sepele. Klaimnya: kalau
`a[i-1] == b[j-1] = c`, maka **selalu ada** LCS optimal yang memakai pasangan
huruf itu. Sebab, ambil LCS optimal mana pun. Kalau ia tidak memakai `a[i-1]`
maupun `b[j-1]`, kita bisa menambahkan `c` di ujungnya — jadi lebih panjang,
kontradiksi. Kalau ia memakai `a[i-1]` yang dipasangkan ke `b[k]` dengan
`k < j-1`, tukar pasangannya ke `b[j-1]` — panjangnya tidak berubah dan tetap
sah. Jadi mengambil diagonal saja tidak pernah merugikan.

**Kompleksitas.** `O(n·m)` waktu dan memori.

### 3.1 Trace: `a = "ABCBDAB"`, `b = "BDCABA"`

```
        ""  B  D  C  A  B  A
    ""   0  0  0  0  0  0  0
    A    0  0  0  0  1  1  1
    B    0  1  1  1  1  2  2
    C    0  1  1  2  2  2  2
    B    0  1  1  2  2  3  3
    D    0  1  2  2  2  3  3
    A    0  1  2  2  3  3  4
    B    0  1  2  2  3  4  4
```

`dp[7][6] = 4`. Salah satu LCS: `BCBA`. Yang lain: `BDAB`, `BCAB`. Panjangnya
unik; barisannya tidak.

---

## 4. Edit Distance (Levenshtein)

**Soal.** Jumlah minimum operasi untuk mengubah `a` menjadi `b`, dengan tiga
operasi berbiaya 1: **sisip**, **hapus**, **ganti**.

**Definisi.** `dp[i][j]` = jumlah operasi minimum untuk mengubah `a[0..i-1]`
menjadi `b[0..j-1]`.

**Rekurens.**

```
kalau a[i-1] == b[j-1] :  dp[i][j] = dp[i-1][j-1]                 (gratis)
kalau tidak            :  dp[i][j] = 1 + min( dp[i-1][j-1],       GANTI
                                              dp[i-1][j],         HAPUS
                                              dp[i][j-1] )        SISIP
base                   :  dp[i][0] = i        (hapus semua i huruf)
                          dp[0][j] = j        (sisipkan semua j huruf)
```

### 4.1 Membaca Ketiga Operasi di Tabel

Ini bagian yang membuat edit distance "klik". Setiap arah punya arti fisik:

- **Diagonal (`dp[i-1][j-1]`) = GANTI.** Kita menyelesaikan `a[i-1]` dan
  `b[j-1]` sekaligus, dengan mengubah yang satu jadi yang lain. Kedua prefiks
  menyusut satu.
- **Atas (`dp[i-1][j]`) = HAPUS.** Kita membuang `a[i-1]`. Prefiks `a`
  menyusut, prefiks `b` tidak — masih ada `b[j-1]` yang harus diurus.
- **Kiri (`dp[i][j-1]`) = SISIP.** Kita menyisipkan `b[j-1]` ke dalam `a`.
  Prefiks `b` menyusut, `a` tidak.

Kalau kamu bisa mengucapkan tiga kalimat itu tanpa melihat, kamu sudah
menguasai edit distance.

### 4.2 Kenapa Base Case-nya BUKAN Nol

Ini perbedaan paling penting dari LCS, dan kesalahan paling umum.

`dp[i][0]` berarti "ubah `a[0..i-1]` menjadi string kosong". Itu memerlukan
`i` penghapusan — bukan 0. Simetris, `dp[0][j] = j` (sisipkan semua).

Kalau kamu menginisialisasinya dengan 0, seluruh tabel akan terlalu kecil dan
jawabannya salah, tapi biasanya tetap "masuk akal" secara sekilas — jenis bug
yang lolos dari uji kecil.

### 4.3 Trace: `a = "kitten"`, `b = "sitting"`

```
         ""  s  i  t  t  i  n  g
    ""    0  1  2  3  4  5  6  7
    k     1  1  2  3  4  5  6  7
    i     2  2  1  2  3  4  5  6
    t     3  3  2  1  2  3  4  5
    t     4  4  3  2  1  2  3  4
    e     5  5  4  3  2  2  3  4
    n     6  6  5  4  3  3  2  3
```

`dp[6][7] = 3`. Operasinya: `k→s` (ganti), `e→i` (ganti), sisipkan `g`.
Jawaban klasik yang memang 3.

---

## 5. Dua Masalah, Satu Tabel

Inilah inti hari ini. Perhatikan bahwa struktur loop-nya **identik**; hanya
tiga hal yang berbeda.

| | LCS | Edit Distance |
|---|---|---|
| `dp[i][j]` | panjang LCS prefiks | biaya minimum ubah prefiks |
| base | `0` di mana-mana | `dp[i][0]=i`, `dp[0][j]=j` |
| saat **cocok** | `dp[i-1][j-1] + 1` | `dp[i-1][j-1]` |
| saat **beda** | `max(atas, kiri)` | `1 + min(diag, atas, kiri)` |
| operator | `max` (maksimalkan) | `min` (minimalkan) |
| diagonal saat beda | **tidak dipakai** | dipakai (= ganti) |

Satu perbedaan struktural yang layak dicatat: **LCS tidak memakai diagonal
saat hurufnya berbeda**, karena "mengganti huruf" bukan operasi yang tersedia
di LCS. Edit distance memakainya. Itulah kenapa edit distance punya tiga
kandidat dan LCS hanya dua.

**Hubungan kuantitatif.** Kalau operasi yang diizinkan hanya **sisip dan
hapus** (tanpa ganti), maka:

```
jarak = n + m - 2 * LCS(a, b)
```

Itu tepat soal LC 583. Dengan "ganti" diizinkan, jaraknya bisa lebih kecil,
karena satu penggantian mengerjakan pekerjaan dua operasi.

---

## 6. Rekonstruksi

### 6.1 Merekonstruksi LCS

Telusuri balik dari `dp[n][m]`:

```cpp
string res;
int i = n, j = m;
while (i > 0 && j > 0) {
    if (a[i-1] == b[j-1]) { res += a[i-1]; i--; j--; }       // ambil huruf
    else if (dp[i-1][j] >= dp[i][j-1]) i--;                  // naik
    else j--;                                                 // ke kiri
}
reverse(res.begin(), res.end());
```

Arahnya: pindah ke tetangga yang nilainya **sama** dengan `dp[i][j]` — itu
berarti sel tersebut yang menjadi sumber nilai kita. Kalau dua-duanya sama,
pilih salah satu; keduanya menghasilkan LCS yang sah (mungkin berbeda).

### 6.2 Merekonstruksi Operasi Edit Distance

```cpp
int i = n, j = m;
vector<string> ops;
while (i > 0 || j > 0) {
    if (i > 0 && j > 0 && a[i-1] == b[j-1]) { i--; j--; }                 // cocok
    else if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + 1) {
        ops.push_back("GANTI " + string(1,a[i-1]) + " -> " + string(1,b[j-1]));
        i--; j--;
    } else if (i > 0 && dp[i][j] == dp[i-1][j] + 1) {
        ops.push_back("HAPUS " + string(1, a[i-1]));  i--;
    } else {
        ops.push_back("SISIP " + string(1, b[j-1]));  j--;
    }
}
reverse(ops.begin(), ops.end());
```

⚠️ Loop-nya `i > 0 || j > 0`, bukan `&&` — kalau salah satu string habis
duluan, sisanya tetap harus dihapus atau disisipkan.

⚠️ Periksa `cocok` **lebih dulu**. Kalau tidak, kamu bisa melaporkan "ganti
a→a" yang tidak masuk akal.

---

## 7. Varian Penting

### 7.1 Longest Common SUBSTRING (Berdekatan)

Satu baris berbeda, dan konsekuensinya besar:

```
kalau a[i-1] == b[j-1] :  dp[i][j] = dp[i-1][j-1] + 1
kalau tidak            :  dp[i][j] = 0                 <-- RESET, bukan max
jawaban                :  MAX atas SELURUH tabel       <-- bukan dp[n][m]
```

**Kenapa reset?** Karena substring harus berdekatan; begitu ada satu huruf
yang tidak cocok, rantai putus dan harus mulai dari nol. Ini persis seperti
perbedaan Kadane ("berakhir tepat di i") versus DP kumulatif di Day 143.

Jangan tertukar: "subsequence" boleh melompat, "substring" tidak.

### 7.2 Shortest Common Supersequence (SCS)

String terpendek yang memuat `a` **dan** `b` sebagai subsekuens.

```
panjang SCS = n + m - LCS(a, b)
```

**Kenapa?** Huruf-huruf LCS dipakai bersama (dihitung sekali); sisanya harus
ditulis masing-masing. Untuk merekonstruksi stringnya, telusuri balik tabel
LCS dan tuliskan huruf yang dilewati dari kedua sisi.

### 7.3 Jumlah Penghapusan Minimum

`n + m - 2·LCS`. Sudah dibahas di bagian 5.

### 7.4 LIS = LCS

Kalau `a` adalah **permutasi** dari `1..n`, maka LIS(`a`) = LCS(`a`, `[1..n]`).
Ini jembatan langsung ke Day 148. Perhatikan bahwa ini `O(n²)` — jadi bukan
cara yang lebih cepat, tapi ia menunjukkan bahwa kedua masalah bertetangga.
(Kebalikannya juga ada dan berguna: LCS **dua permutasi** bisa diubah menjadi
LIS, lalu diselesaikan `O(n log n)`.)

### 7.5 Biaya Operasi Berbeda-beda

Kalau sisip berbiaya `ci`, hapus `cd`, ganti `cr`:

```
dp[i][j] = min( dp[i-1][j-1] + (cocok ? 0 : cr),
                dp[i-1][j] + cd,
                dp[i][j-1] + ci )
```

Perhatikan: kalau `cr > ci + cd`, algoritma otomatis memilih hapus+sisip
alih-alih ganti. Tidak perlu `if` tambahan — `min` mengurusnya.

### 7.6 LCS Tiga String

`dp[i][j][k]`, `O(nmk)`. Rekurensnya analog: cocok bertiga → diagonal + 1;
selain itu → max dari tiga tetangga.

---

## 8. Optimasi Memori

### 8.1 Rolling Array — `O(min(n,m))`

`dp[i][j]` hanya butuh baris `i-1` dan baris `i`. Simpan dua baris saja, atau
bahkan satu baris dengan variabel bantu:

```cpp
vector<int> dp(m + 1, 0);
for (int i = 1; i <= n; i++) {
    int prevDiag = 0;                     // = dp[i-1][j-1]
    for (int j = 1; j <= m; j++) {
        int simpan = dp[j];               // ini masih dp[i-1][j]
        if (a[i-1] == b[j-1]) dp[j] = prevDiag + 1;
        else                  dp[j] = max(dp[j], dp[j-1]);
        prevDiag = simpan;                // untuk iterasi j berikutnya
    }
}
```

⚠️ **Nilai diagonal harus disimpan SEBELUM ditimpa.** Ini satu-satunya bagian
yang rumit, dan melupakannya menghasilkan jawaban yang salah secara halus.

⚠️ Pastikan yang digulung adalah dimensi yang **lebih kecil**: tukar `a` dan
`b` kalau perlu, agar memorinya `O(min(n,m))`.

⚠️ **Rolling array membuat rekonstruksi mustahil** — kamu membuang informasi
yang dibutuhkan. Untuk rekonstruksi dengan memori linear, ada algoritma
**Hirschberg** (divide and conquer, `O(nm)` waktu tapi `O(min(n,m))` memori).
Itu materi lanjutan.

### 8.2 Batas Praktis

`n = m = 5000` → `25·10^6` sel. Dengan `int` itu 100 MB — sudah di ambang
batas memori banyak kontes. Pakai `short` kalau nilainya muat, atau rolling
array. Untuk `n = m = 10^5`, `O(nm)` mustahil; ada trik bitset `O(nm/64)`
untuk LCS, dan Hunt–Szymanski kalau jumlah pasangan cocoknya sedikit.

---

## 9. Kesalahan yang Paling Sering Terjadi

1. **`a[i]` alih-alih `a[i-1]`.** Bug nomor satu. Tabel 1-indexed, string
   0-indexed.
2. **Base case edit distance diisi nol.** Harus `i` dan `j`.
3. **LCSubstring memakai `max` alih-alih reset ke 0.**
4. **Jawaban LCSubstring diambil dari `dp[n][m]`** — harusnya maksimum
   seluruh tabel.
5. **Rolling array tanpa menyimpan diagonal.**
6. **Mencoba merekonstruksi dari tabel yang sudah digulung.**
7. **Alokasi `(n) × (m)`** alih-alih `(n+1) × (m+1)`.
8. **Loop rekonstruksi edit distance memakai `&&`** alih-alih `||`.
9. **Mengira LCS unik.** Panjangnya unik; barisannya bisa banyak.
10. **`int[5001][5001]` sebagai variabel lokal** → stack overflow. Deklarasikan
    global atau pakai `vector`.

---

## 10. Ringkasan

- DP dua string: `dp[i][j]` untuk pasangan **prefiks**; tabel `(n+1)×(m+1)`;
  huruf terakhirnya `a[i-1]` dan `b[j-1]`.
- Pertanyaan di setiap sel selalu sama: **apakah huruf terakhirnya cocok?**
- LCS: cocok → diagonal+1; beda → `max(atas, kiri)`; base 0.
- Edit distance: cocok → diagonal; beda → `1 + min(diag, atas, kiri)`;
  base `i` dan `j`. Diagonal=ganti, atas=hapus, kiri=sisip.
- LCSubstring = LCS dengan **reset ke 0** dan jawaban `max` seluruh tabel.
- SCS = `n + m − LCS`; hapus minimum = `n + m − 2·LCS`.
- Rolling array memangkas memori tapi mematikan rekonstruksi.
