# 📊 Day 214: Aplikasi Prefix Function — Periode, Border & Automaton

> **Prasyarat:** KMP & tabel pi (Day 213), String Hashing (Day 211)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"string berulang"*, *"potongan terkecil"*, *"awalan = akhiran"*, *"hitung string yang tidak mengandung pola"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 214, kamu akan mampu:

- [ ] Membedakan **border**, **periode**, dan **periode terkecil** — dan membuktikan hubungannya
- [ ] Menemukan **semua border** lewat rantai pi dalam O(n)
- [ ] Menentukan apakah string adalah **pengulangan utuh** dari potongan yang lebih pendek
- [ ] Menghitung **berapa kali setiap prefiks muncul** sebagai substring, dalam O(n)
- [ ] Membangun **KMP automaton** `aut[m+1][A]` dan menjelaskan kenapa ia bebas `while`
- [ ] Memakai automaton untuk **DP menghitung string** yang menghindari/mengandung pola
- [ ] Menghitung **jumlah substring berbeda** secara inkremental dengan pi pada string terbalik

---

## 🔍 1. Konsep & Intuisi

Day 213 memberi kita satu benda: tabel `pi`. Hari ini kita panen dari benda itu.
Semua aplikasi di bawah **tidak menambah algoritma baru** — semuanya hanya cara membaca `pi`.

### Border: awalan yang juga akhiran

```
s = a b a b a b a
    └─┘         └─┘   "ab"    -> border panjang 2
    └───┘     └───┘   "abab"  -> border panjang 4
    └─────┘ └─────┘   "ababa" -> border panjang 5  <- TERPANJANG
```

`pi[n-1]` = **border terpanjang** dari seluruh string. Itu definisinya, bukan teorema.

### Periode: langkah geser yang membuat string menutup dirinya sendiri

`p` disebut **periode** dari `s` bila `s[i] == s[i + p]` untuk semua `i` yang valid.

```
s = a b a b a b a       n = 7
p = 2:
    a b a b a b a
      ↘ ↘ ↘ ↘ ↘         geser 2, semua huruf yang bertumpuk COCOK  ✓
    _ _ a b a b a
```

### Teorema kunci (hafalkan ini, bukan kodenya)

```
        p adalah periode   ⟺   n − p adalah panjang border

        periode terkecil   =   n − pi[n−1]
```

**Kenapa?** Kalau geser sejauh `p` masih cocok, maka bagian yang bertumpuk — panjangnya `n − p`
— muncul di awal DAN di akhir. Itu persis definisi border. Bolak-balik dua arah, jadi ⟺.
Border **terpanjang** ⟹ periode **terkecil**. Satu baris kode, satu teorema.

### Pengulangan utuh

```
periode terkecil k = n − pi[n−1]

n % k == 0  ⟹  s adalah (n/k) salinan dari s[0..k−1]
n % k != 0  ⟹  s "hampir" periodik tapi terpotong
```

```
"abcabcabc"  n=9, pi[8]=6, k=3, 9%3==0  -> "abc" × 3        ✓ utuh
"abcabca"    n=7, pi[6]=4, k=3, 7%3!=0  -> "abc"+"abc"+"a"  ✗ terpotong (periode tetap 3)
"aaaa"       n=4, pi[3]=3, k=1, 4%1==0  -> "a" × 4          ✓ utuh
"abcd"       n=4, pi[3]=0, k=4, 4%4==0  -> "abcd" × 1       ✓ trivial
```

> ⚠️ **Jebakan paling sering:** `n % k == 0` itu **syarat tambahan**, bukan bonus.
> Tanpa cek itu, `"abcabca"` akan salah dilaporkan sebagai pengulangan `"abc"`.

### Rantai pi: semua border sekaligus

Border dari border tetap border. Maka semua panjang border adalah:

```
pi[n−1],  pi[pi[n−1] − 1],  pi[pi[pi[n−1] − 1] − 1],  ...  sampai 0
```

```
s = "abacabaabacaba"  (n = 14)
pi[13] = 7   -> border "abacaba"
pi[6]  = 3   -> border "aba"
pi[2]  = 1   -> border "a"
pi[0]  = 0   -> berhenti

Semua border: {1, 3, 7}
```

Rantai ini panjangnya bisa sampai O(n) (contoh: `"aaaa...a"`), tapi menelusurinya tetap O(n).

---

## 🧮 2. Analisis Kompleksitas

| Tugas                                    | Waktu        | Ruang    | Catatan |
| ---------------------------------------- | ------------ | -------- | ------- |
| Bangun pi                                | O(n)         | O(n)     | amortisasi, lihat Day 213 |
| Border terpanjang                        | O(1)         | —        | tinggal baca `pi[n−1]` |
| Semua border                             | O(n)         | O(n)     | panjang rantai ≤ n |
| Periode terkecil                         | O(1)         | —        | `n − pi[n−1]` |
| Hitung kemunculan tiap prefiks           | O(n)         | O(n)     | satu loop mundur |
| Bangun KMP automaton                     | O(m · A)     | O(m · A) | A = ukuran alfabet |
| Jalankan automaton di teks               | O(n)         | O(1)     | **tanpa** while — cocok untuk stream |
| DP hitung string menghindari pola        | O(L · m · A) | O(m)     | rolling array |
| Jumlah substring berbeda (inkremental)   | O(n²)        | O(n)     | n ≤ ~5000 |

**Kapan automaton menang atas KMP biasa?**

- Teks datang **potong-potong** (stream) — tidak boleh mundur, tidak boleh disimpan.
- Teks di-**generate** oleh DP — kita butuh transisi eksplisit, bukan loop `while`.
- Butuh **worst-case O(1) per karakter**, bukan amortisasi.

Harganya: memori `O(m · A)`. Untuk `m = 10^6` dan `A = 26` itu 26 juta int = 104 MB → **MLE**.
Automaton hanya layak saat `m` kecil (≤ 10^5) atau alfabet kecil.

---

## 💻 3. Implementasi C++

### 3.1 Fondasi — tabel pi (dari Day 213)

```cpp
vector<int> bangunPi(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
```

### 3.2 Periode & kompresi

```cpp
// Periode terkecil (selalu ada; paling buruk = n)
int periodeTerkecil(const string& s) {
    vector<int> pi = bangunPi(s);
    return (int)s.size() - pi.back();
}

// Panjang blok terkecil yang bila diulang utuh menghasilkan s.
// Jika s bukan pengulangan utuh, kembalikan n.
int blokKompresi(const string& s) {
    int n = s.size();
    int k = n - bangunPi(s).back();
    return (n % k == 0) ? k : n;       // <- cek keterbagian WAJIB
}
```

### 3.3 Semua border, dari pendek ke panjang

```cpp
vector<int> semuaBorder(const string& s) {
    vector<int> pi = bangunPi(s), res;
    int k = pi.back();
    while (k > 0) { res.push_back(k); k = pi[k - 1]; }
    reverse(res.begin(), res.end());   // rantai turun -> balik jadi naik
    return res;
}
```

### 3.4 Berapa kali tiap prefiks muncul sebagai substring

Ide: setiap posisi `i` "menyumbang" satu kemunculan untuk prefiks sepanjang `pi[i]`,
lalu sumbangan itu **diwariskan ke bawah** lewat rantai pi. Kalau kita proses `i` dari
besar ke kecil, pewarisan cukup satu langkah — inilah trik O(n)-nya.

```cpp
// cnt[len] = berapa kali prefiks sepanjang len muncul sebagai substring s.
vector<long long> hitungPrefiks(const string& s) {
    int n = s.size();
    vector<int> pi = bangunPi(s);
    vector<long long> cnt(n + 1, 0);

    for (int i = 0; i < n; i++) cnt[pi[i]]++;          // sumbangan mentah
    for (int len = n; len > 0; len--)                  // WARISKAN ke border
        cnt[pi[len - 1]] += cnt[len];
    for (int len = 1; len <= n; len++) cnt[len]++;     // prefiks itu sendiri

    cnt[0] = 0;                                        // panjang 0 tak bermakna
    return cnt;
}
```

> Untuk menghitung kemunculan prefiks **pola** di dalam **teks**, jalankan fungsi ini
> pada `pola + '#' + teks`, lalu baca `cnt[len]` untuk `len ≤ |pola|`
> (karakter pemisah `#` harus tidak muncul di keduanya).

### 3.5 KMP Automaton

`aut[state][c]` = state baru setelah membaca karakter `c` saat sedang di `state`
(state = "sudah cocok berapa huruf pola").

```cpp
// pola diberi sentinel '#' agar state m menjadi state serap yang benar.
vector<array<int, 26>> bangunAutomaton(string pola) {
    pola += '#';
    int m = pola.size();
    vector<int> pi = bangunPi(pola);
    vector<array<int, 26>> aut(m);

    for (int i = 0; i < m; i++)
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != pola[i])
                aut[i][c] = aut[pi[i - 1]][c];  // <- pinjam jawaban state lebih kecil
            else
                aut[i][c] = i + ('a' + c == pola[i]);
        }
    return aut;                                 // aut[m-1] = state "pola ditemukan"
}
```

**Kenapa `aut[pi[i-1]][c]` boleh dipinjam?** Karena `pi[i-1] < i`, jawabannya sudah
dihitung di iterasi sebelumnya. Ini persis "unrolling" loop `while` KMP menjadi tabel —
`while` yang amortisasi diubah jadi lookup O(1) sejati.

Menjalankannya:

```cpp
int st = 0;
for (char ch : teks) {
    st = aut[st][ch - 'a'];
    if (st == (int)pola.size()) { /* cocok berakhir di posisi ini */ }
}
```

### 3.6 DP di atas automaton — menghitung string yang menghindari pola

*Berapa banyak string panjang `L` atas alfabet `A` huruf pertama yang **tidak** memuat `pola`?*

```cpp
const long long MOD = 1e9 + 7;

long long hitungTanpaPola(int L, int A, const string& pola) {
    int m = pola.size();
    auto aut = bangunAutomaton(pola);
    vector<long long> dp(m, 0), nx;
    dp[0] = 1;                                   // panjang 0, belum cocok apa-apa

    for (int step = 0; step < L; step++) {
        nx.assign(m, 0);
        for (int s = 0; s < m; s++) {
            if (!dp[s]) continue;
            for (int c = 0; c < A; c++) {
                int t = aut[s][c];
                if (t == m) continue;            // state m = pola muncul -> buang
                nx[t] = (nx[t] + dp[s]) % MOD;
            }
        }
        dp.swap(nx);
    }
    long long total = 0;
    for (long long v : dp) total = (total + v) % MOD;
    return total;
}
```

Kompleksitas `O(L · m · A)`. Kalau `L` besar (10^18), ganti loop dengan
**perpangkatan matriks** `m × m` → `O(m³ log L)`.

### 3.7 Jumlah substring berbeda, inkremental

Menambah satu karakter di akhir string sepanjang `n` menambahkan
`(n+1) − max(pi(reverse(s')))` substring baru.

```cpp
long long jumlahSubstringBerbeda(const string& s) {
    long long total = 0;
    string cur = "";
    for (char ch : s) {
        cur += ch;
        string r = cur; reverse(r.begin(), r.end());
        vector<int> pi = bangunPi(r);
        int mx = 0; for (int v : pi) mx = max(mx, v);
        total += (long long)cur.size() - mx;
    }
    return total;
}
```

**Intuisi:** substring baru = sufiks dari `cur` yang belum pernah muncul.
Sufiks `cur` = prefiks `reverse(cur)`. Prefiks `reverse(cur)` yang **pernah muncul lagi**
di dalamnya persis yang panjangnya ≤ `max(pi)`. Sisanya, `|cur| − max(pi)` buah, benar-benar baru.

O(n²) total — aman sampai `n ≈ 5000`.

---

## 🔄 4. Trace & Simulasi

### 4.1 Periode & border — `s = "abacabaabacaba"` (n = 14)

```
i  : 0  1  2  3  4  5  6  7  8  9 10 11 12 13
s  : a  b  a  c  a  b  a  a  b  a  c  a  b  a
pi : 0  0  1  0  1  2  3  1  2  3  4  5  6  7
```

```
border terpanjang = pi[13] = 7          -> "abacaba"
periode terkecil  = 14 − 7 = 7
14 % 7 == 0 ?  YA  -> tapi cek: s = "abacaba" + "abacaba" ?
                     "abacaba"+"abacaba" = "abacabaabacaba"  ✓ COCOK

rantai border: 7 -> pi[6]=3 -> pi[2]=1 -> pi[0]=0
semua border = {1, 3, 7}
```

### 4.2 Automaton untuk `pola = "aba"` (alfabet {a,b})

```
pola+'#' = "aba#",  pi = [0,0,1,0]

state 0  (belum cocok)     : 'a' -> 1     'b' -> 0
state 1  ("a")             : 'a' -> 1     'b' -> 2
state 2  ("ab")            : 'a' -> 3 ✓   'b' -> 0
state 3  ("aba" = COCOK)   : 'a' -> 1     'b' -> 2

Diagram:
        a          b          a
   (0) ---> (1) ---> (2) ---> (3)*
    ^\_b_/   \_a_(1)  \_b_(0)  \_a_(1) \_b_(2)
```

Jalankan pada teks `"ababa"`:

```
karakter : a    b    a    b    a
state    : 1    2    3*   2    3*
                     ^         ^
                  cocok      cocok    -> "aba" muncul di indeks 0 dan 2
```

Perhatikan: dari state 3, karakter `'b'` langsung ke 2 — automaton **sudah tahu** bahwa
`"aba"` diikuti `"b"` menyisakan `"ab"` yang berguna. Tidak ada `while` sama sekali.

### 4.3 Hitung kemunculan tiap prefiks — `s = "aaa"`

```
pi = [0, 1, 2]

Langkah 1, sumbangan mentah  cnt[pi[i]]++ :
   cnt = [1, 1, 1, 0]        (indeks 0..3)

Langkah 2, wariskan len = 3 -> 1 :
   len=3: cnt[pi[2]] = cnt[2] += cnt[3]=0   -> cnt = [1,1,1,0]
   len=2: cnt[pi[1]] = cnt[1] += cnt[2]=1   -> cnt = [1,2,1,0]
   len=1: cnt[pi[0]] = cnt[0] += cnt[1]=2   -> cnt = [3,2,1,0]

Langkah 3, +1 untuk diri sendiri (len 1..3) :
   cnt = [_, 3, 2, 1]

Verifikasi manual pada "aaa":
   "a"   muncul 3x  ✓
   "aa"  muncul 2x  ✓
   "aaa" muncul 1x  ✓
```

---

## 📝 5. Variasi & Pattern

| Kalimat di soal                                     | Yang dipakai |
| --------------------------------------------------- | ------------ |
| "potongan terpendek yang bila diulang jadi S"        | `n − pi[n−1]` + cek `n % k == 0` |
| "berapa huruf minimal ditambah agar S jadi periodik" | `k − n % k` dengan `k` = periode terkecil |
| "berapa huruf ditambah **di awal** agar S jadi palindrom" | pi dari `rev(S) + '#' + S` |
| "semua panjang awalan yang juga akhiran"             | rantai pi |
| "berapa kali awalan ke-i muncul"                     | `hitungPrefiks` |
| "hitung string panjang L tanpa substring P"          | DP di automaton |
| "teks datang satu per satu / tidak muat di memori"   | automaton (stream) |
| "jumlah substring berbeda", n ≤ 5000                 | pi inkremental pada string terbalik |
| "apakah A rotasi dari B"                             | cari `A` di `B + B` |

### Turunan penting: menambah huruf agar jadi palindrom

```cpp
// Huruf minimal yang ditambahkan DI AWAL s agar s menjadi palindrom.
int tambahanPalindromDepan(const string& s) {
    string r = s; reverse(r.begin(), r.end());
    string t = r + '#' + s;              // '#' tidak boleh ada di s
    return (int)s.size() - bangunPi(t).back();
}
```

> ⚠️ **Perhatikan arahnya — ini sering tertukar.**
> `pi` terakhir dari `rev(s) + '#' + s` = panjang **akhiran palindromik terpanjang**
> (bukan awalan). Karena itu sisanya harus dicerminkan **di depan**.
>
> Verifikasi cepat dengan `s = "aacecaaa"`: `pi` terakhir = 3 (akhiran `"aaa"`),
> jadi 8 − 3 = **5** huruf ditambahkan di awal.
> Bandingkan: awalan palindromik terpanjangnya justru 7 (`"aacecaa"`), yang berarti
> hanya **1** huruf perlu ditambahkan **di akhir**. Untuk arah itu, tukar perannya:
> pakai `pi` dari `s + '#' + rev(s)`.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Lupa `n % k == 0`.** `"abcabca"` bukan pengulangan utuh, meski periodenya 3.
   Ini penyebab WA paling umum di soal "string compression".

2. **Separator bocor.** Memakai `'#'` padahal string boleh memuat `'#'`. Pakai karakter
   di luar alfabet soal (`'\1'`, `'{'`, atau angka −1 kalau bekerja dengan `vector<int>`).

3. **Automaton tanpa sentinel.** Tanpa `pola += '#'`, state `m` tidak punya transisi keluar
   dan kamu akan membaca di luar array. Sentinel membuat `aut` berukuran `m+1` state secara alami.

4. **MLE pada automaton.** `m = 10^6`, `A = 26` → 104 MB. Kalau `m` besar, jangan pakai
   automaton; pakai KMP biasa dengan `while`.

5. **Overflow pada `hitungPrefiks`.** Untuk `s = "aaaa...a"` (n = 10^6), `cnt[1] ≈ 10^6`
   tapi total seluruh kemunculan ≈ `n²/2 = 5·10^11`. Pakai `long long`.

6. **String kosong.** `pi.back()` pada string kosong = UB. Selalu `if (s.empty()) return ...`.

7. **`reverse` lupa di `semuaBorder`.** Rantai pi menghasilkan urutan **menurun**.
   Kalau soal minta menaik, balik dulu.

8. **DP automaton: state `m` tidak dibuang.** Kalau soal minta "mengandung pola",
   state `m` justru harus jadi state serap (`aut[m][c] = m`), bukan dibuang.

### Edge cases wajib diuji

```
s = "a"          -> pi=[0],  periode 1,  border {},   utuh ✓
s = "aa"         -> pi=[0,1], periode 1, border {1},  utuh ✓
s = "ab"         -> pi=[0,0], periode 2, border {},   utuh (trivial)
s = "aaaaaa"     -> rantai border panjang: {1,2,3,4,5}
pola lebih panjang dari teks  -> jawaban 0, jangan crash
alfabet 1 huruf  -> DP automaton tetap benar
```

---

## 🏆 7. Tips Contest

**Red flag → aksi:**

- Muncul kata *"periodik" / "diulang" / "blok terkecil"* → langsung tulis `n − pi[n−1]`,
  lalu **segera** tulis cek `n % k`. Tulis dua-duanya sekaligus supaya tidak lupa.
- *"Hitung banyak string yang ..."* + ada pola string → automaton + DP. Hampir pasti.
- *"Berapa kali X muncul"* dengan banyak X yang semuanya prefiks → `hitungPrefiks`, sekali jalan.

**Keputusan hashing vs pi:**

| Situasi | Pilih |
| ------- | ----- |
| Butuh **struktur** (border, periode, automaton) | prefix function |
| Butuh **banding substring sembarang** O(1)      | hashing |
| Juri **adversarial** (Codeforces hack)          | prefix function (deterministik) |
| Butuh cepat ditulis, risiko boleh               | hashing |

**Hemat waktu:** simpan `bangunPi` + `bangunAutomaton` di template pribadi. Keduanya < 25 baris
dan muncul di puluhan soal.

**Manajemen waktu:** kalau 10 menit setelah menulis `pi` kamu belum tahu apa yang harus dilakukan
dengan tabelnya, kemungkinan soalnya bukan soal pi — cek Z-function (Day 215) atau suffix
automaton (Day 222).

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  SEMUANYA DARI SATU TABEL pi
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  border terpanjang   = pi[n-1]
  semua border        = pi[n-1] -> pi[k-1] -> ... -> 0
  periode terkecil    = n - pi[n-1]
  pengulangan utuh    = (n % (n - pi[n-1]) == 0)
  huruf agar periodik = k - n % k        (0 jika sudah utuh)
  akhiran palindromik = pi dari rev(s)+'#'+s   (-> tambah di AWAL)
  awalan  palindromik = pi dari s+'#'+rev(s)   (-> tambah di AKHIR)
  cari pola           = pi dari pola+'#'+teks, cari nilai == |pola|
  hitung tiap prefiks = cnt[pi[i]]++ ; wariskan mundur ; +1
  automaton           = aut[i][c] = (cocok ? i+1 : aut[pi[i-1]][c])
  DP hindari pola     = O(L·m·A), buang state m
  substring berbeda   = Σ (|cur| - max pi(rev(cur)))     O(n²)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1732 — Finding Borders](https://cses.fi/problemset/task/1732) | CSES | rantai border |
| [CSES 1733 — Finding Periods](https://cses.fi/problemset/task/1733) | CSES | periode |
| [CF 1200 B/… — Compress String](https://codeforces.com/problemset) | Codeforces | kompresi |
| [CF 432D — Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) | Codeforces | border + hitung prefiks |
| [CF 471D — MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) | Codeforces | pi pada array selisih |
| [CF 526D — Om Nom and Necklace](https://codeforces.com/problemset/problem/526/D) | Codeforces | periodisitas lanjut |
| [UVa 455 — Periodic Strings](https://onlinejudge.org/) | UVa | periode dasar |
| [SPOJ NHAY — A Needle in the Haystack](https://www.spoj.com/problems/NHAY/) | SPOJ | matching |
| [AtCoder ABC 257 G — Prefix Concatenation](https://atcoder.jp/contests/abc257/tasks/abc257_g) | AtCoder | pi + DP |

---

**Selanjutnya:** Day 215 — Z-Function. Alat yang menjawab pertanyaan berbeda
("berapa panjang kecocokan dari posisi i dengan awal string?") tapi sering saling menggantikan
dengan pi. Kamu akan belajar kapan masing-masing lebih nyaman.
