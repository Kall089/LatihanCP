# 📊 Day 213: KMP — Prefix Function & Pencarian Pola O(n + m)

> **Prasyarat:** String Hashing (Day 211), String Dasar (Day 39)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"cari pola"*, *"awalan yang juga akhiran"*, *"periode string"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 213, kamu akan mampu:

- [ ] Menjelaskan arti **failure function (tabel pi)** dengan kalimat sendiri
- [ ] Membangun tabel pi dalam **O(m)** dan menjelaskan kenapa loop-nya tidak O(m²)
- [ ] Mencari pola di dalam teks dalam **O(n + m)** tanpa pernah memundurkan indeks teks
- [ ] Menemukan **semua border** sebuah string lewat rantai pi
- [ ] Menghitung **periode terkecil** dengan rumus `n − pi[n−1]`
- [ ] Menghitung **berapa kali tiap prefiks muncul** dalam satu kali jalan
- [ ] Memutuskan kapan memakai KMP dan kapan hashing lebih cocok

---

## 🔍 1. Konsep & Intuisi

### Masalah pada pencarian naif

Cari pola `"ababc"` di dalam teks `"ababdababc"`:

```
teks : a b a b d a b a b c
pola : a b a b c
       ✓ ✓ ✓ ✓ ✗          gagal di huruf ke-5

Cara naif: geser pola satu langkah, lalu ULANG DARI AWAL
teks : a b a b d ...
pola :   a b a b c
         ✗                 gagal langsung
```

Yang boros: kita **membuang seluruh informasi** yang sudah didapat. Padahal kita sudah tahu
4 huruf pertama cocok (`abab`), dan itu petunjuk berharga.

### Analogi: mencari kata di buku sambil mengingat ejaan

Bayangkan kamu mencari kata **"ababc"** sambil membaca buku dengan jari.

Kamu sudah membaca `a-b-a-b`, lalu huruf berikutnya ternyata `d`, bukan `c`. Kamu gagal.

- **Cara pemula:** hapus semua ingatan, tarik jari mundur, mulai mengeja lagi dari huruf berikutnya.
- **Cara KMP:** kamu sadar bahwa `"ab"` di **akhir** bagian yang sudah cocok ternyata sama dengan
  `"ab"` di **awal** kata yang dicari. Jadi dua huruf itu **masih berguna** — kamu tidak perlu
  mengulang, cukup melanjutkan seolah-olah sudah cocok 2 huruf.

> **Inti KMP:** jarimu di buku **tidak pernah mundur**. Yang mundur hanyalah "sudah cocok berapa huruf".

### Apa itu failure function (tabel pi)?

```
pi[i] = panjang prefiks TERPANJANG dari pola yang sekaligus menjadi
        sufiks dari potongan pola[0..i], TAPI bukan potongan itu sendiri.
```

Untuk pola `"ababc"`:

```
 i │ pola[0..i] │ prefiks = sufiks?          │ pi[i]
───┼────────────┼────────────────────────────┼──────
 0 │ "a"        │ tidak ada (harus lebih pendek) │  0
 1 │ "ab"       │ "a" vs "b"  ✗              │  0
 2 │ "aba"      │ "a" == "a"  ✓              │  1
 3 │ "abab"     │ "ab" == "ab" ✓             │  2
 4 │ "ababc"    │ tidak ada yang cocok       │  0
```

Jadi pi = **[0, 0, 1, 2, 0]**.

### Kenapa tabel itu menyelamatkan kita?

Saat kecocokan sepanjang `j` huruf gagal, kita **tidak perlu membuang semuanya**.
Sebanyak `pi[j−1]` huruf terakhir yang sudah cocok ternyata juga merupakan **awal pola**,
jadi kecocokan itu bisa dipakai ulang.

```cpp
j = pi[j - 1];   // satu baris inilah seluruh keajaiban KMP
```

### Visualisasi ASCII: mundur tanpa memundurkan teks

```
teks : a b a b d a b a b c
       0 1 2 3 4 5 6 7 8 9
pola : a b a b c
       ✓ ✓ ✓ ✓ ✗          gagal di i=4 (teks 'd' vs pola 'c'), j=4

pi[3] = 2, jadi j turun dari 4 menjadi 2.
Artinya: geser pola sejauh 4-2 = 2 langkah, TANPA menyentuh i.

teks : a b a b d a b a b c
           └─┘
pola :     a b a b c
           ✓ ✓ ← dua huruf ini sudah dianggap cocok, gratis
               ✗   'd' vs 'a' -> j turun lagi jadi pi[1] = 0
                   sekarang j = 0, i baru boleh maju

i TIDAK PERNAH MUNDUR. Itu sebabnya totalnya O(n + m).
```

### Kapan digunakan? (Pattern Recognition)

| Kalimat di soal | Teknik |
|---|---|
| "cari semua kemunculan pola" | KMP matching |
| "awalan yang juga menjadi akhiran" | pi[n−1] dan rantainya |
| "periode terkecil string" | n − pi[n−1] |
| "apakah string ini pengulangan" | n % (n − pi[n−1]) == 0 |
| "berapa kali tiap prefiks muncul" | Hitung mundur pada rantai pi |
| "gabungkan dua string, cari sambungan" | pi pada `a + '#' + b` |

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Kompleksitas | Catatan |
|---|---|---|
| Membangun tabel pi | **O(m)** | Amortized — lihat penjelasan di bawah |
| Pencarian pola | **O(n)** | Setelah pi dibangun |
| **Total** | **O(n + m)** | Deterministik, tanpa risiko tabrakan |
| Memori | O(m) | Hanya array pi |

### Kenapa membangun pi itu O(m), bukan O(m²)?

Di dalamnya ada `while` bersarang, jadi sekilas terlihat seperti O(m²). Kuncinya adalah
**analisis amortisasi**:

- Nilai `j` **naik paling banyak 1** pada setiap iterasi luar → total kenaikan ≤ m.
- Setiap putaran `while` **menurunkan** j minimal 1.
- Karena j tidak pernah negatif, total penurunan ≤ total kenaikan ≤ m.

Jadi seluruh putaran `while` di sepanjang program **digabungkan** hanya berjalan ≤ m kali.
Argumen yang sama berlaku untuk tahap pencarian.

### Perbandingan dengan metode lain

| Metode | Waktu | Risiko salah | Fleksibilitas | Kesulitan |
|---|---|---|---|---|
| Naif | O(n·m) | tidak ada | rendah | sangat mudah |
| **KMP** | **O(n + m)** | **tidak ada** | sedang | sedang |
| Hashing (Day 33) | O(n + m) | ada (tabrakan) | **tinggi** | mudah |
| Z-function | O(n + m) | tidak ada | sedang | sedang |
| Aho-Corasick | O(n + total pola) | tidak ada | banyak pola | sulit |

> **KMP vs Hashing:** KMP **deterministik** — tidak ada peluang salah sama sekali, dan tidak bisa
> di-hack. Hashing lebih fleksibel untuk pertanyaan sembarang tentang substring.

---

## 💻 3. Implementasi C++

### 3.1 Membangun tabel pi

```cpp
vector<int> bangunPi(const string& p) {
    int m = p.size();
    vector<int> pi(m, 0);          // pi[0] selalu 0

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];         // panjang kecocokan sejauh ini

        // Selama huruf tidak cocok, mundur ke border yang lebih pendek
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];

        if (p[i] == p[j]) j++;     // cocok -> kecocokan bertambah 1
        pi[i] = j;
    }
    return pi;
}
```

### 3.2 Pencarian pola KMP

```cpp
vector<int> cariKMP(const string& teks, const string& pola) {
    vector<int> pi = bangunPi(pola), hasil;
    int n = teks.size(), m = pola.size();
    int j = 0;                     // sudah cocok berapa huruf

    for (int i = 0; i < n; i++) {  // i TIDAK PERNAH mundur
        while (j > 0 && teks[i] != pola[j]) j = pi[j - 1];
        if (teks[i] == pola[j]) j++;

        if (j == m) {              // pola lengkap ditemukan
            hasil.push_back(i - m + 1);
            j = pi[j - 1];         // lanjutkan, agar tumpang tindih ikut terhitung
        }
    }
    return hasil;
}
```

> **Kenapa `j = pi[j-1]` setelah ketemu, bukan `j = 0`?**
> Supaya kemunculan yang **saling tumpang tindih** ikut terdeteksi.
> Contoh: mencari `"aa"` di `"aaa"` menghasilkan 2 kemunculan, bukan 1.

### 3.3 Trik penggabungan: mencari pola tanpa fungsi terpisah

```cpp
// Bangun pi dari gabungan pola + pemisah + teks.
// Pemisah WAJIB karakter yang tidak muncul di keduanya.
string gabung = pola + '#' + teks;
vector<int> pi = bangunPi(gabung);

int m = pola.size();
for (int i = m + 1; i < (int)gabung.size(); i++)
    if (pi[i] == m)                       // seluruh pola cocok di sini
        cout << i - 2 * m << " ";         // posisi awal pada teks (0-based)
```

### 3.4 Semua border lewat rantai pi

```cpp
// Border = potongan yang menjadi awalan sekaligus akhiran (bukan seluruhnya).
vector<int> semuaBorder(const string& s) {
    vector<int> pi = bangunPi(s), b;
    int k = pi.back();
    while (k > 0) {                 // rantai: border dari border juga border
        b.push_back(k);
        k = pi[k - 1];
    }
    reverse(b.begin(), b.end());    // urut menaik
    return b;
}
```

### 3.5 Periode terkecil

```cpp
int periodeTerkecil(const string& s) {
    vector<int> pi = bangunPi(s);
    return (int)s.size() - pi.back();
}

// Apakah s merupakan pengulangan utuh dari potongan yang lebih pendek?
bool pengulanganUtuh(const string& s) {
    int n = s.size(), p = periodeTerkecil(s);
    return p < n && n % p == 0;
}
```

### 3.6 Menghitung kemunculan tiap prefiks

```cpp
// cnt[i] = berapa kali prefiks sepanjang (i+1) muncul di dalam s
vector<long long> hitungPrefiks(const string& s) {
    int n = s.size();
    vector<int> pi = bangunPi(s);
    vector<long long> cnt(n, 1);        // tiap prefiks minimal muncul sekali

    // Telusuri MUNDUR: setiap kemunculan prefiks panjang (i+1)
    // otomatis juga merupakan kemunculan border-nya.
    for (int i = n - 1; i > 0; i--)
        if (pi[i] > 0) cnt[pi[i] - 1] += cnt[i];

    return cnt;
}
```

---

## 🔄 4. Trace / Simulasi

### Contoh 1: membangun pi untuk "aabaaab"

| i | huruf | j awal | Proses `while` | Cocok? | pi[i] |
|---|---|---|---|---|---|
| 0 | a | — | — | — | **0** |
| 1 | a | pi[0]=0 | tidak jalan | 'a'=='a' ✓ | **1** |
| 2 | b | pi[1]=1 | 'b'≠'a' → j=pi[0]=0 | 'b'≠'a' ✗ | **0** |
| 3 | a | pi[2]=0 | tidak jalan | 'a'=='a' ✓ | **1** |
| 4 | a | pi[3]=1 | tidak jalan | 'a'=='a' ✓ | **2** |
| 5 | a | pi[4]=2 | 'a'≠'b' → j=pi[1]=1 | 'a'=='a' ✓ | **2** |
| 6 | b | pi[5]=2 | tidak jalan | 'b'=='b' ✓ | **3** |

**pi = [0, 1, 0, 1, 2, 2, 3]**

Verifikasi pi[6] = 3: potongan `"aabaaab"` punya awalan `"aab"` yang juga menjadi akhirannya. ✓

### Contoh 2: mencari "aba" di dalam "ababa"

pi untuk `"aba"` = [0, 0, 1].

| i | teks[i] | j sebelum | Aksi | j sesudah | Ketemu? |
|---|---|---|---|---|---|
| 0 | a | 0 | cocok dengan pola[0] | 1 | |
| 1 | b | 1 | cocok dengan pola[1] | 2 | |
| 2 | a | 2 | cocok dengan pola[2] | 3 | ✅ **posisi 1** (1-based), lalu j = pi[2] = 1 |
| 3 | b | 1 | cocok dengan pola[1] | 2 | |
| 4 | a | 2 | cocok dengan pola[2] | 3 | ✅ **posisi 3**, lalu j = pi[2] = 1 |

**Hasil: kemunculan pada posisi 1 dan 3** — keduanya berbagi huruf 'a' di tengah,
dan KMP menangkap keduanya karena `j` di-reset ke `pi[j-1]`, bukan ke 0.

### Contoh 3: rantai border pada "abcababcab"

```
pi = [0,0,0,1,2,0,1,2,3,4,5]   -> pi terakhir = 5

Rantai border:
  k = 5   -> border "abcab"   (panjang 5)
  k = pi[4] = 2 -> border "ab" (panjang 2)
  k = pi[1] = 0 -> berhenti

Semua border (menaik): [2, 5]
```

Cek manual:
- `"abcab"`: awalan `"abcab"` ✓, akhiran `"abcab"` ✓
- `"ab"`: awalan `"ab"` ✓, akhiran `"ab"` ✓

### Contoh 4: periode "ababab"

```
pi = [0,0,1,2,3,4]  -> pi[n-1] = 4
periode = n - pi[n-1] = 6 - 4 = 2

Cek: n % periode = 6 % 2 = 0  -> "ababab" adalah pengulangan utuh dari "ab" (3 kali) ✓
```

Bandingkan dengan `"aabaa"`:
```
pi = [0,1,0,1,2]  -> periode = 5 - 2 = 3
Cek: 5 % 3 = 2 != 0  -> BUKAN pengulangan utuh
Tapi 3 tetap periode yang sah: s[0]==s[3] ('a'=='a'), s[1]==s[4] ('a'=='a') ✓
```

---

## 📝 5. Variasi & Pattern

### Variasi 1: apakah B merupakan rotasi dari A?

```cpp
// B rotasi A jika |A| == |B| DAN B muncul di dalam A+A
bool rotasi(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    return !cariKMP(a + a, b).empty();
}
```

### Variasi 2: berapa huruf minimal ditambahkan agar jadi palindrom

Tambahkan di **depan**: cari border terpanjang dari `s + '#' + balik(s)`.

```cpp
string t = s;
reverse(t.begin(), t.end());
vector<int> pi = bangunPi(s + '#' + t);
int cocok = pi.back();               // panjang palindrom terpanjang di AKHIR s
cout << (int)s.size() - cocok << "\n";   // sisanya harus ditambahkan
```

### Variasi 3: substring bersama terpanjang di ujung (overlap dua string)

```cpp
// Berapa panjang akhiran A yang juga merupakan awalan B?
vector<int> pi = bangunPi(b + '#' + a);
int overlap = pi.back();
```
Berguna untuk soal "gabungkan dua kata dengan tumpang tindih maksimum".

### Variasi 4: KMP automaton (untuk DP di atas string)

```cpp
// aut[j][c] = keadaan berikutnya kalau saat ini sudah cocok j huruf lalu bertemu huruf c
vector<array<int,26>> bangunAutomaton(const string& p) {
    int m = p.size();
    vector<int> pi = bangunPi(p);
    vector<array<int,26>> aut(m + 1);
    for (int j = 0; j <= m; j++)
        for (int c = 0; c < 26; c++) {
            if (j < m && c == p[j] - 'a') aut[j][c] = j + 1;
            else aut[j][c] = (j == 0 ? 0 : aut[pi[j - 1]][c]);
        }
    return aut;
}
```
Dipakai pada soal seperti "hitung string sepanjang n yang TIDAK memuat pola tertentu".

### Variasi 5: mencari banyak pola sekaligus

Kalau polanya banyak, KMP satu per satu menjadi lambat. Naik level ke **Aho-Corasick**
(pada dasarnya KMP di atas trie).

---

## ⚠️ 6. Common Mistakes & Edge Cases

### ❌ Mistake 1: mengulang dari awal setelah gagal

```cpp
while (j > 0 && teks[i] != pola[j]) j = 0;        // ❌ ini pencarian naif
while (j > 0 && teks[i] != pola[j]) j = pi[j-1];  // ✅ inti KMP
```

### ❌ Mistake 2: reset ke 0 setelah menemukan pola

```cpp
if (j == m) { hasil.push_back(i - m + 1); j = 0; }         // ❌ kemunculan tumpang tindih hilang
if (j == m) { hasil.push_back(i - m + 1); j = pi[j-1]; }   // ✅
```
Gejalanya: mencari `"aa"` di `"aaaa"` menjawab 2, padahal seharusnya 3.

### ❌ Mistake 3: pemisah pada trik penggabungan bisa muncul di string

```cpp
string gabung = pola + "a" + teks;   // ❌ 'a' bisa muncul di teks -> hasil salah
string gabung = pola + "#" + teks;   // ✅ pilih karakter yang mustahil muncul
```
Kalau string bisa berisi karakter apa pun, pakai `'\1'` atau nilai di luar alfabet.

### ❌ Mistake 4: salah membaca arti pi

`pi[i]` bukan "berapa kali pola muncul" dan bukan pula "posisi kemunculan".
Ia adalah **panjang awalan terpanjang yang juga menjadi akhiran** dari potongan `pola[0..i]`.
Salah paham di sini membuat semua turunannya salah.

### ❌ Mistake 5: lupa bahwa border tidak boleh seluruh string

```
"aaa" -> border terpanjang = 2 ("aa"), BUKAN 3
```
Definisinya *proper prefix* — harus lebih pendek dari string aslinya. Rumus `pi` sudah
menjaminnya, tapi orang sering salah saat menghitung manual.

### ❌ Mistake 6: menghitung prefiks dari depan, bukan dari belakang

```cpp
for (int i = 1; i < n; i++) cnt[pi[i]-1] += cnt[i];      // ❌ nilai belum lengkap
for (int i = n - 1; i > 0; i--) if (pi[i]) cnt[pi[i]-1] += cnt[i];  // ✅
```
Harus mundur, karena kontribusi prefiks panjang menurun ke prefiks yang lebih pendek.

### Edge Cases yang perlu diuji

| Kasus | Kenapa berbahaya |
|---|---|
| Pola lebih panjang dari teks | Harus mengembalikan kosong, jangan crash |
| Pola sepanjang 1 huruf | pi hanya `[0]`, cek loop tidak error |
| Semua huruf sama (`"aaaa"`) | Kemunculan tumpang tindih paling banyak di sini |
| Pola == teks | Harus ketemu tepat 1 kali di posisi 1 |
| Tidak ada kemunculan sama sekali | Output harus jelas (kosong atau −1) |

---

## 🏆 7. Tips Contest

### Red flags — tanda soal ini pakai KMP

- 🚩 *"Cari semua kemunculan pola di dalam teks"* dengan |teks| besar
- 🚩 *"Awalan terpanjang yang juga merupakan akhiran"*
- 🚩 *"Periode terkecil"* atau *"apakah string ini pengulangan"*
- 🚩 *"Berapa kali tiap prefiks muncul"*
- 🚩 *"Berapa huruf minimal ditambahkan agar menjadi palindrom"*
- 🚩 Soal menyebut kata **border**, **prefix function**, atau **failure function**

### KMP atau Hashing?

```
Butuh jaminan 100% benar (tanpa peluang tabrakan)?
├── Ya → KMP
└── Tidak masalah probabilistik
    ├── Pertanyaannya cuma "cari pola ini" → KMP (lebih rapi)
    └── Pertanyaannya bermacam-macam tentang substring sembarang → HASHING
```

Di **Codeforces yang punya fase hacking**, KMP lebih aman karena tidak bisa dipatahkan
dengan anti-hash test.

### Kebiasaan yang menyelamatkan

1. Simpan `bangunPi` dan `cariKMP` di template pribadi — 15 baris, hafalkan polanya.
2. Setelah menemukan pola, **selalu** `j = pi[j-1]`, jangan `j = 0`.
3. Untuk trik penggabungan, pakai pemisah `'#'` dan pastikan tidak ada di input.
4. Kalau ragu apakah jawabanmu benar, uji dengan `"aaaa"` — string ini menangkap
   hampir semua bug KMP.

### Time management

- Menulis KMP dari nol: **≤ 5 menit** kalau sudah hafal.
- Untuk |teks| ≤ 1000 dan cuma satu pencarian, `s.find()` sudah cukup — tidak perlu KMP.

---

## 📌 8. Ringkasan & Cheatsheet

### Cheatsheet Singkat

```
╔══════════════════════════════════════════════════════════════╗
║  KMP — CHEATSHEET                                            ║
╠══════════════════════════════════════════════════════════════╣
║  ARTI pi[i]                                                  ║
║    panjang awalan terpanjang dari p[0..i] yang juga           ║
║    menjadi akhirannya (tidak boleh seluruh potongan)          ║
║                                                              ║
║  BANGUN pi                                        O(m)       ║
║    for (i = 1..m-1) {                                        ║
║        j = pi[i-1];                                          ║
║        while (j > 0 && p[i] != p[j]) j = pi[j-1];            ║
║        if (p[i] == p[j]) j++;                                ║
║        pi[i] = j;                                            ║
║    }                                                         ║
║                                                              ║
║  CARI POLA                                        O(n)       ║
║    for (i = 0..n-1) {                                        ║
║        while (j > 0 && t[i] != p[j]) j = pi[j-1];            ║
║        if (t[i] == p[j]) j++;                                ║
║        if (j == m) { catat(i-m+1); j = pi[j-1]; }            ║
║    }                                                         ║
║                                                              ║
║  TURUNAN LANGSUNG                                            ║
║    border terpanjang  = pi[n-1]                              ║
║    semua border       = rantai pi[k-1] sampai 0              ║
║    periode terkecil   = n - pi[n-1]                          ║
║    pengulangan utuh   = n % (n - pi[n-1]) == 0               ║
║    hitung prefiks     = telusuri MUNDUR, cnt[pi[i]-1]+=cnt[i]║
║                                                              ║
║  TRIK GABUNG   pi(pola + '#' + teks), cari nilai == m        ║
╚══════════════════════════════════════════════════════════════╝
```

### Key Points

1. **Indeks teks tidak pernah mundur.** Hanya `j` yang turun. Itulah sumber O(n + m).
2. **`j = pi[j-1]` adalah seluruh isi KMP.** Sisanya cuma pembungkus.
3. **pi bukan sekadar alat pencarian pola** — ia langsung memberi border, periode, dan
   jumlah kemunculan prefiks. Banyak soal hanya butuh pi, tanpa pencarian sama sekali.
4. **Setelah ketemu, kembalikan j ke pi[j−1]**, supaya kemunculan tumpang tindih terhitung.
5. **KMP deterministik**, hashing probabilistik. Kalau soal bisa di-hack, pilih KMP.
6. **Uji dengan "aaaa"** — string paling ampuh untuk menangkap bug KMP.

### Hubungan dengan materi lain

```
Day 39 : String Dasar ──┐
Day 211: Hashing ───────┼──► Day 213: KMP (kamu di sini)
                        │             │
                        │             ├──► Day 215: Z-function (konsep serupa)
                        │             ├──► Day 219: Aho-Corasick (KMP di atas trie)
                        └─────────────┴──► Suffix Array / Automaton (lanjutan)
```

### Link Soal Latihan di Online Judge

**CSES String Section**
- [String Matching](https://cses.fi/problemset/task/1753) — persis exercise 2
- [Finding Borders](https://cses.fi/problemset/task/1732) — persis exercise 5
- [Finding Periods](https://cses.fi/problemset/task/1733) — persis exercise 4

**Codeforces**
- [CF 432D - Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) — persis exercise 6
- [CF 471D - MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) — KMP pada selisih
- [CF 1200E - Compress Words](https://codeforces.com/problemset/problem/1200/E) — overlap dua string

**LeetCode**
- [28. Find the Index of the First Occurrence](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)
- [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/) — periode
- [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) — trik penggabungan

**AtCoder**
- [ABC 150F - Xor Shift](https://atcoder.jp/contests/abc150/tasks/abc150_f) — KMP pada barisan angka

---

*Selesai Day 213. Lanjut ke Day 214 (Aplikasi Prefix Function: Periode, Border, Automaton) atau Day 215 (Z-Function).*
