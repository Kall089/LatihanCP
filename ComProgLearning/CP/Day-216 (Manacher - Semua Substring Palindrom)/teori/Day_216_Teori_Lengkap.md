# 📊 Day 216: Manacher — Semua Substring Palindrom dalam O(n)

> **Prasyarat:** Z-function (Day 215), KMP & pi (Day 213–214), String Hashing (Day 211)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"palindrom terpanjang"*, *"hitung substring palindrom"*, *"apakah S[l..r] palindrom"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 216, kamu akan mampu:

- [ ] Menjelaskan kenapa palindrom butuh perlakuan khusus untuk **panjang genap**
- [ ] Menulis Manacher versi **transformasi `#`** (satu array, tanpa duplikasi kode)
- [ ] Menulis Manacher versi **dua array `d1`/`d2`** (lebih cepat, tanpa alokasi ekstra)
- [ ] Menjelaskan **cermin refleksi** dan kenapa pointer `r` tidak pernah mundur
- [ ] **Menghitung** total substring palindrom dalam O(n)
- [ ] Menjawab query *"apakah `S[l..r]` palindrom?"* dalam **O(1)**
- [ ] Memilih antara Manacher, hashing, dan Eertree secara sadar

---

## 🔍 1. Konsep & Intuisi

### Masalah: palindrom punya dua "rasa"

```
"aba"    panjang GANJIL  -> pusatnya HURUF 'b'
"abba"   panjang GENAP   -> pusatnya CELAH antara dua 'b'
```

Inilah sumber semua kerumitan Manacher. Algoritma naif "ekspansi dari pusat"
harus dijalankan **dua kali** (sekali untuk pusat huruf, sekali untuk pusat celah),
dan tetap O(n²) pada `"aaaa...a"`.

### Trik transformasi: paksa semuanya jadi ganjil

Sisipkan pemisah di antara setiap huruf, juga di ujung-ujungnya:

```
S     =    a   b   b   a
T     =  # a # b # b # a #
indeks   0 1 2 3 4 5 6 7 8
```

Sekarang:

```
palindrom GENAP "abba" di S  ->  palindrom GANJIL "#a#b#b#a#" di T, pusat di indeks 4
palindrom GANJIL "bb"?  bukan, "b" saja  ->  di T pusat di indeks 3 atau 5
```

**Setiap** palindrom di `T` punya panjang ganjil, karena huruf asli dan `#`
selalu berselang-seling. Satu jenis pusat saja — kode jadi separuh.

```
|T| = 2n + 1  selalu ganjil
p[i] = radius palindrom di T berpusat di i (tidak termasuk pusatnya)

  panjang palindrom asli di S = p[i]
  posisi awal di S            = (i - p[i]) / 2
```

Rumus `panjang asli = p[i]` terlihat ajaib, tapi masuk akal: dari radius `p[i]` di `T`,
tepat separuhnya adalah huruf asli.

### Ide inti: cermin (sama seperti z-box, tapi refleksi)

```
palindrom "paling kanan" yang sudah ditemukan: pusat c, batas kanan r

        c
   |----+----|
   l         r
        ^
        |
   i' = 2c - i        i
        ●             ●
      cermin       posisi sekarang
```

Karena `[l, r]` adalah palindrom, isi di sekitar `i` adalah **cerminan** isi di sekitar `i'`.
Jadi:

```
tebakan awal p[i] = min(r - i, p[2c - i])
                         ↑        ↑
                    batas aman   jawaban kembaran
```

Batas `r - i` wajib: di luar `r` kita **belum punya bukti apa pun**, dan pengecekan
manual di sanalah yang mendorong `r` maju.

> **Perbandingan langsung dengan Day 215:**
> Z-box memakai **translasi** (`z[i - l]`), Manacher memakai **refleksi** (`p[2c - i]`).
> Argumen kompleksitasnya **identik**: setiap ekspansi manual yang berhasil menaikkan `r`,
> dan `r` tidak pernah mundur ⟹ total O(n).

### Alternatif: dua array tanpa transformasi

Versi cp-algorithms memakai dua array terpisah, tanpa membangun string baru:

```
d1[i] = banyaknya palindrom GANJIL berpusat di i
      = radius + 1     (palindrom terpanjangnya punya panjang 2*d1[i] - 1)

d2[i] = banyaknya palindrom GENAP berpusat di celah SEBELUM i
      (palindrom terpanjangnya punya panjang 2*d2[i])
```

```
S = "abba"
i    :  0  1  2  3
d1   :  1  1  1  1      (tidak ada palindrom ganjil > 1 huruf)
d2   :  0  0  2  0      (d2[2] = 2 -> "abba", panjang 4)
```

Lebih cepat (tanpa alokasi `2n+1`) dan lebih hemat memori, tapi kodenya dua kali lipat.
**Rekomendasi:** hafalkan versi transformasi untuk kontes (lebih sedikit yang bisa salah),
simpan versi dua array di template untuk saat `n` sangat besar.

---

## 🧮 2. Analisis Kompleksitas

| Tugas | Waktu | Ruang | Catatan |
| ----- | ----- | ----- | ------- |
| Manacher (transformasi) | O(n) | O(n) | array `2n+1` |
| Manacher (dua array) | O(n) | O(n) | dua array `n`, tanpa string baru |
| Palindrom terpanjang | O(n) | O(n) | ambil `max(p[i])` |
| Hitung total substring palindrom | O(n) | O(n) | jumlahkan radius |
| Query `S[l..r]` palindrom? | O(1) per query | O(n) | setelah preprocessing |
| Semua palindrom **berbeda** | O(n) | O(n) | butuh **Eertree**, bukan Manacher |

**Perbandingan dengan alternatif:**

| Pendekatan | Waktu | Deterministik? | Catatan |
| ---------- | ----- | -------------- | ------- |
| Naif ekspansi pusat | O(n²) | ✓ | cukup untuk n ≤ 5000 |
| DP `is_pal[l][r]` | O(n²) waktu, O(n²) ruang | ✓ | MLE untuk n > 10^4 |
| Hashing (S + reverse S) | O(n) preprocess, O(1) query | ✗ | bisa di-hack |
| **Manacher** | **O(n)** | **✓** | pilihan default |
| Eertree (palindromic tree) | O(n) | ✓ | untuk palindrom **berbeda** & DP palindromik |

> ⚠️ **Manacher TIDAK memberi jumlah palindrom BERBEDA.** Ia menghitung kemunculan.
> `"aaa"` punya 6 kemunculan palindrom tapi hanya 3 yang berbeda (`a`, `aa`, `aaa`).
> Untuk yang berbeda, kamu butuh Eertree atau suffix structure.

---

## 💻 3. Implementasi C++

### 3.1 Versi transformasi (rekomendasi untuk kontes)

```cpp
// Mengembalikan p[] pada string tertransformasi T = #a#b#...#
// p[i] = radius; panjang palindrom asli berpusat di i adalah p[i].
vector<int> manacher(const string& s) {
    string t = "#";
    for (char c : s) { t += c; t += '#'; }

    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;                    // pusat & batas kanan palindrom terkanan

    for (int i = 0; i < n; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);   // cermin

        // ekspansi manual
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n
               && t[i - p[i] - 1] == t[i + p[i] + 1])
            p[i]++;

        if (i + p[i] > r) { c = i; r = i + p[i]; }    // palindrom terkanan baru
    }
    return p;
}
```

Sebelas baris. Perhatikan `min(r - i, p[2*c - i])` — bandingkan dengan
`min(r - i, z[i - l])` kemarin. Struktur yang sama, cermin yang berbeda.

**Cara membaca hasilnya:**

```cpp
vector<int> p = manacher(s);

// palindrom terpanjang
int best = 0, pos = 0;
for (int i = 0; i < (int)p.size(); i++)
    if (p[i] > best) { best = p[i]; pos = (i - p[i]) / 2; }
string jawab = s.substr(pos, best);

// total kemunculan substring palindrom (termasuk 1 huruf)
long long total = 0;
for (int v : p) total += (v + 1) / 2;
```

**Kenapa `(p[i] + 1) / 2`?** Palindrom berpusat di `i` dengan radius `p[i]` memuat
`p[i], p[i]-2, p[i]-4, ...` sebagai panjang-panjang palindrom yang juga berpusat di sana.
Banyaknya suku dalam deret itu adalah `⌈p[i]/2⌉ = (p[i] + 1) / 2`.

### 3.2 Versi dua array (untuk n sangat besar)

```cpp
// d1[i] = banyak palindrom ganjil berpusat di i  (panjang terpanjang 2*d1[i]-1)
// d2[i] = banyak palindrom genap dengan pusat di celah SEBELUM i (panjang 2*d2[i])
pair<vector<int>, vector<int>> manacher2(const string& s) {
    int n = s.size();
    vector<int> d1(n), d2(n);

    // --- ganjil ---
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }

    // --- genap ---
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) { l = i - k - 1; r = i + k; }
    }
    return {d1, d2};
}

// total kemunculan palindrom
long long totalPalindrom(const string& s) {
    auto [d1, d2] = manacher2(s);
    long long t = 0;
    for (int v : d1) t += v;
    for (int v : d2) t += v;
    return t;
}
```

Di versi ini `d1[i]` dan `d2[i]` **sudah** merupakan hitungan, jadi total palindrom
tinggal dijumlahkan langsung — lebih bersih daripada `(p[i]+1)/2`.

### 3.3 Query O(1): apakah `S[l..r]` palindrom?

```cpp
struct CekPalindrom {
    vector<int> p;                       // hasil manacher pada T
    CekPalindrom(const string& s) : p(manacher(s)) {}

    // l, r inklusif, 0-based pada S
    bool cek(int l, int r) const {
        int pusat = l + r + 1;           // indeks pusat di T
        return p[pusat] >= r - l + 1;
    }
};
```

**Menurunkan `pusat = l + r + 1`:** huruf `S[k]` berada di indeks `2k + 1` pada `T`.
Titik tengah antara `S[l]` dan `S[r]` di `T` adalah `((2l+1) + (2r+1)) / 2 = l + r + 1`. ✓

### 3.4 Awalan & akhiran palindromik

Sering muncul di soal "tambahkan huruf agar jadi palindrom":

```cpp
// Panjang awalan palindromik TERPANJANG dari s.
int awalanPalindromTerpanjang(const string& s) {
    vector<int> p = manacher(s);
    int best = 0;
    for (int i = 0; i < (int)p.size(); i++)
        if (i - p[i] == 0) best = max(best, p[i]);   // menyentuh ujung kiri
    return best;
}
```

Bandingkan dengan cara pi di Day 214 (`pi` dari `rev(s) + '#' + s`) — hasilnya sama,
tapi Manacher memberi **semua** awalan palindromik sekaligus, bukan hanya yang terpanjang.

---

## 🔄 4. Trace & Simulasi

### 4.1 Transformasi — `S = "abba"`

```
S =      a   b   b   a
T =  #   a   #   b   #   b   #   a   #
i =  0   1   2   3   4   5   6   7   8
```

| i | T[i] | i < r? | tebakan (`min(r−i, p[2c−i])`) | ekspansi | p[i] | (c, r) baru |
|---|------|--------|-------------------------------|----------|------|-------------|
| 0 | `#` | tidak | 0 | kiri habis | **0** | (0, 0) |
| 1 | `a` | tidak | 0 | `T[0]='#'` = `T[2]='#'` ✓ → 1; lalu kiri habis | **1** | (1, 2) |
| 2 | `#` | tidak | 0 | `T[1]='a'` vs `T[3]='b'` ✗ | **0** | tetap |
| 3 | `b` | tidak | 0 | `#`=`#` ✓→1; `a` vs `b` ✗ | **1** | (3, 4) |
| 4 | `#` | tidak | 0 | `b`=`b` ✓→1; `#`=`#` ✓→2; `a`=`a` ✓→3; `#`=`#` ✓→4; habis | **4** | (4, 8) |
| 5 | `b` | 5<8 ✓ | `min(8−5, p[3]=1) = 1` | `#` vs `#`… `T[3]='b'` vs `T[7]='a'` ✗ | **1** | tetap |
| 6 | `#` | 6<8 ✓ | `min(2, p[2]=0) = 0` | `b` vs `a` ✗ | **0** | tetap |
| 7 | `a` | 7<8 ✓ | `min(1, p[1]=1) = 1` | kanan habis | **1** | tetap |
| 8 | `#` | 8<8 tidak | 0 | kanan habis | **0** | tetap |

```
p =  0  1  0  1  4  1  0  1  0
                 ↑
            p[4] = 4  -> palindrom terpanjang panjang 4
            posisi awal di S = (4 - 4)/2 = 0
            jawab = S.substr(0, 4) = "abba"   ✓

total kemunculan = Σ (p[i]+1)/2
                 = 0 + 1 + 0 + 1 + 2 + 1 + 0 + 1 + 0 = 6
Verifikasi manual pada "abba":
  panjang 1 : a, b, b, a        -> 4
  panjang 2 : bb                -> 1
  panjang 4 : abba              -> 1
  total                            6   ✓
```

Perhatikan baris `i = 5` dan `i = 7`: keduanya **menyalin dari cermin** dan tidak
memulai ekspansi dari nol. Pada string seperti `"aaaa...a"`, penghematan inilah
yang memisahkan O(n) dari O(n²).

### 4.2 Versi dua array — `S = "aaa"`

```
S : a  a  a
i : 0  1  2

--- ganjil ---
i=0: k=1, cek s[-1] -> berhenti           d1[0] = 1   ("a")
i=1: k=1, s[0]='a'==s[2]='a' -> k=2       d1[1] = 2   ("a", "aaa")
i=2: cermin, lalu berhenti                d1[2] = 1   ("a")

--- genap (pusat di celah SEBELUM i) ---
i=0: tidak ada celah kiri                 d2[0] = 0
i=1: s[0]='a'==s[1]='a' -> k=1            d2[1] = 1   ("aa")
i=2: s[1]='a'==s[2]='a' -> k=1            d2[2] = 1   ("aa")

total = (1+2+1) + (0+1+1) = 6
Verifikasi: a,a,a (3) + aa,aa (2) + aaa (1) = 6   ✓
Tapi palindrom BERBEDA hanya 3: {a, aa, aaa}      <- Manacher tidak menjawab ini
```

### 4.3 Query O(1) — `S = "abacaba"`

```
S : a  b  a  c  a  b  a
i : 0  1  2  3  4  5  6

p =  0 1 0 3 0 1 0 7 0 1 0 3 0 1 0      (indeks 0..14 pada T)

cek(0, 6): pusat = 0+6+1 = 7    p[7] = 7 >= 7   -> YA    ("abacaba")
cek(0, 2): pusat = 0+2+1 = 3    p[3] = 3 >= 3   -> YA    ("aba")
cek(1, 3): pusat = 1+3+1 = 5    p[5] = 1 >= 3   -> TIDAK ("bac")
cek(2, 4): pusat = 2+4+1 = 7    p[7] = 7 >= 3   -> YA    ("aca")
```

Perhatikan `cek(0,6)` dan `cek(2,4)` memakai **pusat yang sama** (indeks 7).
Itu benar: `"abacaba"` dan `"aca"` sama-sama berpusat di huruf `'c'`.
Rumusnya hanya menanyakan *"apakah radius di pusat itu cukup panjang?"*

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "substring palindrom terpanjang" | `max(p[i])` |
| "berapa banyak substring palindrom" (kemunculan) | `Σ (p[i]+1)/2` |
| "berapa banyak palindrom **berbeda**" | **Eertree**, bukan Manacher |
| "apakah S[l..r] palindrom" (banyak query) | `p[l+r+1] >= r-l+1` |
| "awalan/akhiran palindromik terpanjang" | `p[i]` yang menyentuh ujung |
| "potong S jadi k bagian palindrom" | Manacher + DP |
| "berapa pasang palindrom yang bersambung" | Manacher + prefix sum atas radius |
| "huruf minimal ditambah agar jadi palindrom" | pi (Day 214) atau Manacher |

### Pattern penting: Manacher + DP partisi

*Bagi S menjadi bagian-bagian palindrom, minimalkan banyaknya bagian.*

```cpp
CekPalindrom cp(s);
int n = s.size();
vector<int> dp(n + 1, INT_MAX);
dp[0] = 0;
for (int i = 1; i <= n; i++)
    for (int j = 0; j < i; j++)
        if (cp.cek(j, i - 1) && dp[j] != INT_MAX)
            dp[i] = min(dp[i], dp[j] + 1);
```

O(n²) dengan cek O(1). Tanpa Manacher, cek palindrom naif membuatnya O(n³).

### Pattern: menghitung pasangan palindrom

*Berapa pasang `(i, j)` dengan `i < j`, `S[0..i]` palindrom dan `S[j..n-1]` palindrom?*

Bangun dua array boolean dari Manacher (`awalanPal[i]`, `akhiranPal[j]`),
lalu prefix sum. O(n) total.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **`#` ada di dalam input.** Transformasi memakai `'#'` sebagai pemisah. Kalau soal
   mengizinkan karakter apa pun, pakai `'\1'`. Ini jebakan yang sama dengan separator
   di Day 215, dan sama seringnya terlewat.

2. **Salah rumus konversi indeks.** Hafalkan dua ini dan verifikasi sekali dengan
   contoh kecil sebelum submit:
   ```
   panjang asli    = p[i]
   posisi awal di S = (i - p[i]) / 2
   pusat untuk (l,r) = l + r + 1
   ```

3. **Batas ekspansi.** `i - p[i] - 1 >= 0 && i + p[i] + 1 < n` — **dua-duanya** wajib.
   Melewatkan salah satu = out of bounds yang kadang tidak crash (jadi lolos di lokal,
   RE di judge).

4. **Mengira Manacher menghitung palindrom BERBEDA.** Ia menghitung **kemunculan**.
   Kalau soal bilang "distinct", ganti alat.

5. **Overflow.** `"aaaa...a"` dengan n = 10^6 punya `n(n+1)/2 ≈ 5·10^11` kemunculan
   palindrom. `int` jebol. Pakai `long long`.

6. **Mencampur konvensi `d1`/`d2`.** Beberapa sumber mendefinisikan `d2[i]` sebagai
   pusat di celah **setelah** `i`, bukan sebelum. Salah satu saja tercampur → off-by-one.
   Pakai versi di template ini dan jangan menyalin dari tempat lain.

7. **String kosong.** `manacher("")` menghasilkan `t = "#"`, `p = [0]` — aman, tapi
   jangan lalu memanggil `s.substr(pos, best)` dengan `best = 0` tanpa mengecek.

### Edge cases wajib diuji

```
S = "a"        -> palindrom terpanjang "a",  total 1
S = "ab"       -> palindrom terpanjang "a" atau "b",  total 2
S = "aa"       -> palindrom terpanjang "aa", total 3
S = "aaaa"     -> total 10, cermin bekerja keras
S = "abcd"     -> tidak ada palindrom > 1, total 4
S = "abacaba"  -> terpanjang seluruh string, total 12
```

---

## 🏆 7. Tips Contest

**Red flag → aksi:**

- Kata *"palindrom"* + `n` sampai 10^5/10^6 → Manacher. Hampir tidak ada alternatif
  yang lebih sederhana.
- Kata *"palindrom"* + `n ≤ 5000` → ekspansi naif O(n²) sudah cukup. **Jangan** tulis
  Manacher kalau tidak perlu; naif lebih kecil risikonya.
- Kata *"palindrom BERBEDA"* atau *"DP di atas palindrom"* → Eertree, bukan Manacher.
- Banyak query *"apakah S[l..r] palindrom"* → Manacher sekali, lalu O(1) per query.
  Alternatif hashing juga O(1) tapi bisa di-hack.

**Manacher vs hashing:**

| Situasi | Pilih |
| ------- | ----- |
| Codeforces, ada fase hack | **Manacher** — deterministik |
| Butuh struktur (semua radius sekaligus) | **Manacher** |
| Sudah menulis hashing untuk bagian lain soal | **hashing** — jangan tambah kode |
| ICPC / juri tidak adversarial, kejar waktu | **hashing** — lebih cepat ditulis |

**Trik implementasi:** simpan Manacher versi transformasi **persis 11 baris** di template,
lengkap dengan **komentar rumus konversi indeks**. Konversi indeks itulah — bukan
algoritmanya — yang biasanya salah saat kontes.

**Manajemen waktu:** kalau soalnya palindrom dan kamu buntu > 20 menit setelah Manacher
jadi, kemungkinan besar bagian sulitnya bukan palindromnya, melainkan DP/counting
di atasnya. Pisahkan dua masalah itu di kertas.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MANACHER
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MASALAH : palindrom genap & ganjil butuh pusat berbeda
  SOLUSI  : T = # a # b # ... #    -> semua jadi ganjil, |T| = 2n+1

  INTI:
    if (i < r) p[i] = min(r - i, p[2*c - i]);        // CERMIN (refleksi)
    while (batas aman && t[i-p[i]-1] == t[i+p[i]+1]) p[i]++;
    if (i + p[i] > r) { c = i; r = i + p[i]; }

  r MONOTON NAIK -> O(n)      (argumen sama persis dengan z-box Day 215)

  KONVERSI INDEKS (yang paling sering salah):
    panjang asli      = p[i]
    posisi awal di S  = (i - p[i]) / 2
    pusat untuk (l,r) = l + r + 1
    cek palindrom     = p[l + r + 1] >= r - l + 1

  HITUNGAN:
    total kemunculan  = Σ (p[i] + 1) / 2          <- pakai long long
    palindrom BERBEDA = butuh EERTREE, bukan ini

  VERSI DUA ARRAY (n besar):
    d1[i] = jumlah palindrom ganjil berpusat di i
    d2[i] = jumlah palindrom genap, pusat di celah SEBELUM i
    total = Σ d1 + Σ d2
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Perbandingan tiga hari terakhir

| | Day 213–214 (pi) | Day 215 (z) | Day 216 (Manacher) |
| --- | --- | --- | --- |
| Pertanyaan | awalan = akhiran? | cocok dari posisi i? | palindrom berpusat di i? |
| Simetri | translasi ke belakang | translasi | **refleksi** |
| Pointer monoton | `j` amortisasi | `r` | `r` |
| Punya automaton? | ✓ | ✗ | ✗ |
| Untuk DP counting | ✓ terbaik | — | via Eertree |

Ketiganya adalah **variasi dari satu ide**: simpan bukti terjauh yang sudah kamu punya,
gunakan kembali lewat simetri, dan biarkan satu pointer maju monoton membayar seluruh biaya.

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 2111 — Longest Palindrome](https://cses.fi/problemset/task/2111) | CSES | Manacher dasar |
| [CSES 1111 — Longest Palindrome](https://cses.fi/problemset/task/1111) | CSES | Manacher dasar |
| [LeetCode 5 — Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) | LeetCode | pemanasan |
| [LeetCode 647 — Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) | LeetCode | hitung kemunculan |
| [CF 7D — Palindrome Degree](https://codeforces.com/problemset/problem/7/D) | Codeforces | Manacher/hash + DP |
| [CF 17E — Palisection](https://codeforces.com/problemset/problem/17/E) | Codeforces | pasangan palindrom bersinggungan |
| [CF 1080E — Sonya and Matrix Beauty](https://codeforces.com/problemset/problem/1080/E) | Codeforces | Manacher pada baris tergabung |
| [SPOJ LPS](https://www.spoj.com/problems/LPS/) | SPOJ | palindrom terpanjang |
| [SPOJ MSUBSTR](https://www.spoj.com/problems/MSUBSTR/) | SPOJ | Manacher + counting |
| [AtCoder ABC 237 E / ABC 398 F](https://atcoder.jp/) | AtCoder | terapan palindrom |

---

**Selanjutnya:** Day 217 — **Trie**. Kita berpindah dari "satu string dianalisis dalam-dalam"
ke "banyak string disimpan bersama". Trie adalah fondasi untuk Aho-Corasick (Day 219),
yang pada dasarnya adalah **KMP automaton untuk banyak pola sekaligus** — jadi Day 214
akan kembali berguna di sana.
