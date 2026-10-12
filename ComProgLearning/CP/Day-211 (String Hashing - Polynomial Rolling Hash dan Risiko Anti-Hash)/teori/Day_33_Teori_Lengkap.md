# 📊 Day 33: String Hashing — Polynomial Hash, Rabin-Karp & Collision

> **Prasyarat:** String Dasar (Day 32), Prefix Sum 1D (Day 29), Modulo (Day 22)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"apakah dua potongan sama"*, *"berapa substring berbeda"*, *"substring terpanjang yang berulang"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 33, kamu akan mampu:

- [ ] Menjelaskan cara kerja **polynomial hashing** dan kenapa ia membuat perbandingan jadi O(1)
- [ ] Membangun **prefix hash** lalu mengambil hash substring mana pun dalam **O(1)**
- [ ] Mengimplementasikan **Rabin-Karp** untuk pencarian pola O(n + m)
- [ ] Menghitung peluang **tabrakan (collision)** dan cara menekannya
- [ ] Memakai **double hashing** dan **base acak** sebagai pengaman
- [ ] Menyelesaikan pola klasik: cek palindrom substring, hitung substring berbeda, LCS biner
- [ ] Menghindari jebakan overflow, base ≤ ukuran alfabet, dan anti-hash test

---

## 🔍 1. Konsep & Intuisi

### Masalah yang ingin dipecahkan

Membandingkan dua potongan string sepanjang L butuh **O(L)** — kita harus mengeja huruf demi huruf.
Kalau ada 10⁵ pertanyaan pada string sepanjang 10⁵, totalnya 10¹⁰ operasi. Jauh terlalu lambat.

**Pertanyaannya:** bisakah dua potongan string dibandingkan dalam **satu langkah**?

### Analogi: nomor punggung pemain bola

Bayangkan setiap kata diberi **nomor punggung** yang dihitung dari huruf-hurufnya.

- Kalau dua pemain nomor punggungnya **berbeda**, sudah pasti mereka orang yang berbeda. ✅ Pasti benar.
- Kalau nomor punggungnya **sama**, hampir pasti orangnya sama — walaupun secara teori bisa saja kebetulan.

Membandingkan dua nomor punggung cuma butuh **satu perbandingan angka**, bukan mengeja seluruh nama.
Itulah inti string hashing: **mengubah string menjadi angka**, lalu membandingkan angkanya.

### Kenapa harus "polynomial"?

Kita ingin fungsi yang **peka terhadap urutan**. Kalau kita cuma menjumlahkan kode hurufnya,
maka "abc" dan "cba" akan bernilai sama — jelas buruk.

Solusinya: beri **bobot berbeda** untuk tiap posisi, memakai pangkat dari sebuah bilangan `p`:

```
hash(s) = s[0]·p⁰ + s[1]·p¹ + s[2]·p² + ... + s[n-1]·p^(n-1)   (mod m)
```

Sekarang posisi ikut menentukan nilai, jadi "abc" ≠ "cba".

Nilainya bisa raksasa, karena itu semuanya dihitung **modulo m** (sebuah bilangan prima besar).

### Visualisasi ASCII: menghitung hash "abc"

```
Anggap p = 31, m = 10^9 + 9, dan huruf dipetakan a=1, b=2, c=3

  huruf :   a       b        c
  kode  :   1       2        3
  bobot : p⁰=1    p¹=31   p²=961
          ────────────────────────
  hasil : 1·1  +  2·31  +  3·961
        =  1   +   62   +  2883
        = 2946

  hash("abc") = 2946 mod (10^9+9) = 2946
```

### Kunci utama: prefix hash

Sama seperti prefix sum menjawab "jumlah dari L sampai R" dalam O(1),
**prefix hash** menjawab "hash dari L sampai R" dalam O(1).

```
h[i] = hash dari s[0..i-1]      (h[0] = 0)

hash(s[l..r]) = ( h[r+1] − h[l] ) · p^(−l)
```

Karena pembagian modular itu mahal, kita biasanya **tidak membaginya**.
Sebagai gantinya, saat membandingkan dua substring kita **samakan bobotnya** dengan mengalikan:

```
Bandingkan s[a..b] dengan s[c..d]  (panjang sama):
   ( h[b+1] − h[a] ) · p^c   ==   ( h[d+1] − h[c] ) · p^a   ?
```

Cara ini menghindari modular inverse sepenuhnya.

### Visualisasi: prefix hash bekerja seperti prefix sum

```
  s     :    a      b      c      a      b
  index :    0      1      2      3      4

  h[0] = 0
  h[1] = h[0] + a·p⁰
  h[2] = h[1] + b·p¹
  h[3] = h[2] + c·p²
  h[4] = h[3] + a·p³
  h[5] = h[4] + b·p⁴
           └────────────┘
     hash(s[1..3]) = h[4] − h[1]      (masih berbobot p¹, perlu disamakan)
```

### Kapan digunakan? (Pattern Recognition)

| Kalimat di soal | Teknik |
|---|---|
| "apakah dua potongan ini sama?" | Prefix hash + bandingkan O(1) |
| "berapa kali pola muncul" | Rabin-Karp |
| "berapa substring berbeda" | Kumpulkan hash ke dalam set |
| "substring terpanjang yang muncul dua kali" | Binary search panjang + hash set |
| "substring bersama terpanjang dari dua string" | Binary search + hash |
| "apakah potongan ini palindrom" | Hash normal + hash terbalik |

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Kompleksitas | Catatan |
|---|---|---|
| Membangun prefix hash | **O(n)** | Sekali di awal |
| Ambil hash substring | **O(1)** | Inti kekuatannya |
| Bandingkan dua substring | **O(1)** | Dibandingkan O(L) cara biasa |
| Rabin-Karp cari pola | **O(n + m)** | Rata-rata; kasus terburuk O(n·m) kalau banyak tabrakan |
| Hitung substring berbeda | O(n²) | Kumpulkan semua hash ke set |
| Substring berulang terpanjang | O(n log n) | Binary search + hash set |

### Perbandingan dengan cara lain

| Kebutuhan | Naif | Hashing | KMP (Day 34) | Suffix Automaton |
|---|---|---|---|---|
| Cari 1 pola | O(n·m) | O(n + m) | **O(n + m)** deterministik | O(n) |
| Bandingkan 2 substring | O(L) | **O(1)** | tidak bisa | O(1) |
| Banyak pola berbeda | lambat | **mudah** | perlu Aho-Corasick | mudah |
| Risiko salah | tidak ada | ada (kecil) | **tidak ada** | tidak ada |
| Kesulitan menulis | mudah | **mudah** | sedang | sulit |

> **Kelebihan hashing:** sangat fleksibel — sekali prefix hash dibangun, ratusan jenis pertanyaan
> tentang substring bisa dijawab. **Kekurangannya:** bersifat probabilistik, ada peluang salah.

---

## 💻 3. Implementasi C++

### 3.1 Polynomial hash sederhana (satu mod)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll P = 131;              // base, harus > ukuran alfabet
const ll M = 1000000009;       // mod, bilangan prima besar

ll hashString(const string& s) {
    ll h = 0, pow = 1;
    for (char c : s) {
        h = (h + (c - 'a' + 1) * pow) % M;   // +1 supaya 'a' tidak jadi 0
        pow = (pow * P) % M;
    }
    return h;
}
```

> **Kenapa `c - 'a' + 1`, bukan `c - 'a'`?**
> Kalau 'a' dipetakan ke 0, maka "a", "aa", dan "aaa" semuanya berhash 0 — tabrakan sepele.
> Selalu petakan ke 1..26.

### 3.2 Prefix hash + hash substring O(1)

```cpp
struct Hash {
    int n;
    vector<ll> h, p;                 // h[i] = hash s[0..i-1], p[i] = P^i

    Hash(const string& s) : n(s.size()), h(n + 1, 0), p(n + 1, 1) {
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p[i]) % M;
            p[i + 1] = (p[i] * P) % M;
        }
    }

    // Hash mentah s[l..r] (masih berbobot p^l, belum dinormalkan)
    ll get(int l, int r) const {
        return (h[r + 1] - h[l] + M) % M;    // +M agar tidak negatif
    }

    // Apakah s[a..b] sama dengan s[c..d]? (panjang harus sama)
    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        // Samakan bobot dengan mengalikan silang: hindari modular inverse
        return get(a, b) * p[c] % M == get(c, d) * p[a] % M;
    }
};
```

### 3.3 Double hashing (pengaman dari anti-hash test)

```cpp
struct HashGanda {
    static const ll M1 = 1000000007, M2 = 998244353;
    ll P1, P2;
    int n;
    vector<ll> h1, h2, p1, p2;

    HashGanda(const string& s) : n(s.size()),
        h1(n + 1, 0), h2(n + 1, 0), p1(n + 1, 1), p2(n + 1, 1) {
        // Base acak: membuat anti-hash test tidak bisa disiapkan lebih dulu
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        P1 = 131 + rng() % 100 * 2;      // ganjil, > 26
        P2 = 137 + rng() % 100 * 2;

        for (int i = 0; i < n; i++) {
            ll c = s[i] - 'a' + 1;
            h1[i + 1] = (h1[i] + c * p1[i]) % M1;
            h2[i + 1] = (h2[i] + c * p2[i]) % M2;
            p1[i + 1] = p1[i] * P1 % M1;
            p2[i + 1] = p2[i] * P2 % M2;
        }
    }

    pair<ll, ll> get(int l, int r) const {
        return {(h1[r + 1] - h1[l] + M1) % M1, (h2[r + 1] - h2[l] + M2) % M2};
    }

    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        auto x = get(a, b), y = get(c, d);
        return x.first  * p1[c] % M1 == y.first  * p1[a] % M1
            && x.second * p2[c] % M2 == y.second * p2[a] % M2;
    }
};
```

### 3.4 Rabin-Karp — cari semua kemunculan pola

```cpp
vector<int> rabinKarp(const string& teks, const string& pola) {
    int n = teks.size(), m = pola.size();
    vector<int> hasil;
    if (m > n) return hasil;

    Hash ht(teks);
    ll hp = 0, pw = 1;
    for (int i = 0; i < m; i++) {          // hash pola (bobot mulai p^0)
        hp = (hp + (pola[i] - 'a' + 1) * pw) % M;
        pw = pw * P % M;
    }

    for (int i = 0; i + m <= n; i++) {
        // Bandingkan hash teks[i..i+m-1] dengan hash pola,
        // setelah bobotnya disamakan.
        if (ht.get(i, i + m - 1) == hp * ht.p[i] % M)
            hasil.push_back(i);
    }
    return hasil;
}
```

---

## 🔄 4. Trace / Simulasi

### Contoh 1: membangun prefix hash "aba" (P = 31, M = 10⁹+9)

| i | s[i] | kode | p[i] | kode·p[i] | h[i+1] = h[i] + kode·p[i] |
|---|---|---|---|---|---|
| — | — | — | — | — | h[0] = **0** |
| 0 | a | 1 | 1 | 1 | h[1] = 0 + 1 = **1** |
| 1 | b | 2 | 31 | 62 | h[2] = 1 + 62 = **63** |
| 2 | a | 1 | 961 | 961 | h[3] = 63 + 961 = **1024** |

### Contoh 2: mengambil hash substring

```
s = "aba", ingin hash s[1..2] = "ba"

get(1, 2) = h[3] − h[1] = 1024 − 1 = 1023

Cek manual: "ba" pada posisi 1 berbobot mulai p¹
   b·p¹ + a·p² = 2·31 + 1·961 = 62 + 961 = 1023  ✅ COCOK
```

Perhatikan nilai 1023 ini **masih berbobot p¹**, bukan p⁰.
Karena itu ia belum bisa langsung dibandingkan dengan hash "ba" yang berdiri sendiri (yang bernilai 2 + 31 = 33).

### Contoh 3: menyamakan bobot saat membandingkan

```
s = "abab", bandingkan s[0..1] ("ab") dengan s[2..3] ("ab")

get(0,1) = h[2] − h[0] = 63 − 0   = 63        (berbobot p⁰)
get(2,3) = h[4] − h[2] = ...      = 63·p²     (berbobot p²)

Cara membandingkan tanpa pembagian — kalikan silang:
   get(0,1) · p[2]  ==  get(2,3) · p[0]
       63 · 961     ==   63·961 · 1
          60543     ==      60543            ✅ SAMA
```

Inilah alasan rumus `sama()` mengalikan silang dengan `p[c]` dan `p[a]`.

### Contoh 4: Rabin-Karp mencari "aba" di "ababa"

| i | Substring | Hash teks (dinormalkan) | Hash pola | Cocok? |
|---|---|---|---|---|
| 0 | "aba" | H | H | ✅ ketemu di 0 |
| 1 | "bab" | X | H | ❌ |
| 2 | "aba" | H | H | ✅ ketemu di 2 |

**Hasil: pola muncul di indeks 0 dan 2** — dua kemunculan yang saling tumpang tindih,
dan hashing menangkap keduanya tanpa perlakuan khusus.

---

## 📝 5. Variasi & Pattern

### Variasi 1: cek apakah substring adalah palindrom

Bangun hash untuk string asli **dan** string yang dibalik. Sebuah substring adalah palindrom
kalau hash-nya sama dengan hash bayangan cerminnya.

```cpp
Hash maju(s);
string t = s; reverse(t.begin(), t.end());
Hash mundur(t);

int n = s.size();
bool palindrom(int l, int r) {
    // s[l..r] pada string terbalik menempati posisi (n-1-r) .. (n-1-l)
    return maju.sama(l, r, n - 1 - r, n - 1 - l);
}
```

> ⚠️ Perhatikan: `sama()` di sini membandingkan antar dua objek Hash yang berbeda,
> jadi versinya perlu sedikit disesuaikan. Lihat `template.cpp` untuk implementasi utuhnya.

### Variasi 2: menghitung substring berbeda

```cpp
// O(n^2): kumpulkan hash semua substring, ukuran set = jawabannya
set<pair<ll,ll>> unik;
for (int l = 0; l < n; l++)
    for (int r = l; r < n; r++)
        unik.insert(hg.getNormal(l, r));   // hash yang sudah dinormalkan
cout << unik.size() << "\n";
```

### Variasi 3: substring terpanjang yang muncul minimal dua kali

Sifat kuncinya **monoton**: kalau ada substring berulang sepanjang L, pasti ada juga yang sepanjang L−1.
Karena monoton, panjangnya bisa dicari dengan **binary search**.

```cpp
bool adaBerulang(int len) {
    unordered_set<ll> terlihat;
    for (int i = 0; i + len <= n; i++) {
        ll h = hashNormal(i, i + len - 1);
        if (terlihat.count(h)) return true;
        terlihat.insert(h);
    }
    return false;
}
// Lalu binary search pada len: cari nilai terbesar yang masih true.
```

### Variasi 4: substring bersama terpanjang dari dua string

Pola yang sama — binary search pada panjang, lalu kumpulkan semua hash panjang L dari string
pertama ke dalam set, dan cek apakah ada yang muncul di string kedua.

### Variasi 5: hashing untuk selain huruf

Hashing tidak terbatas pada string. Barisan angka, susunan pohon, bahkan himpunan bisa di-hash.
Untuk angka besar, petakan dulu ke 1..k dengan coordinate compression (Day 38).

---

## ⚠️ 6. Common Mistakes & Edge Cases

### ❌ Mistake 1: overflow saat mengalikan

```cpp
int h = (h + c * pow) % M;        // ❌ int × int bisa melebihi 2·10⁹
long long h = (h + c * pow) % M;  // ✅ semua variabel long long
```
Kalau M mendekati 10⁹, hasil perkalian bisa mencapai 10¹⁸ — hanya muat di `long long`.

### ❌ Mistake 2: memetakan 'a' ke 0

```cpp
h += (c - 'a') * pow;       // ❌ "a", "aa", "aaa" semuanya jadi 0
h += (c - 'a' + 1) * pow;   // ✅
```

### ❌ Mistake 3: hasil pengurangan jadi negatif

```cpp
return (h[r+1] - h[l]) % M;        // ❌ bisa negatif di C++
return (h[r+1] - h[l] + M) % M;    // ✅ tambahkan M dulu
```
C++ mempertahankan tanda pada operasi modulo, berbeda dengan Python.

### ❌ Mistake 4: base terlalu kecil

```cpp
const ll P = 26;   // ❌ sama dengan ukuran alfabet -> tabrakan mudah terjadi
const ll P = 131;  // ✅ prima, lebih besar dari alfabet
```

### ❌ Mistake 5: base tetap pada kontes dengan hack (Codeforces)

Kalau base dan mod-nya bisa ditebak, lawan bisa menyiapkan **anti-hash test** yang
sengaja membuat tabrakan. Pakai **base acak** yang dibangkitkan saat program berjalan.

```cpp
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll P = 131 + rng() % 100 * 2;
```

### ❌ Mistake 6: satu mod pada data besar (paradoks ulang tahun)

Kalau kita membandingkan **semua pasangan** dari k substring, jumlah pasangannya k²/2.
Dengan satu mod sebesar 10⁹, peluang ada tabrakan menjadi besar begitu k mencapai puluhan ribu:

| Jumlah substring k | Peluang tabrakan (1 mod ≈ 10⁹) |
|---|---|
| 1.000 | ~0,05 % |
| 10.000 | ~5 % |
| 50.000 | ~70 % ⚠️ |
| 100.000 | ~99 % ❌ |

**Solusi: double hashing.** Dua mod berbeda membuat peluangnya menjadi sekitar 10⁻¹⁸ — praktis nol.

### Edge Cases yang perlu diuji

| Kasus | Kenapa berbahaya |
|---|---|
| Substring panjangnya 0 | `get(l, r)` dengan r < l harus ditangani |
| Panjang kedua substring beda | `sama()` harus mengembalikan false lebih dulu |
| Seluruh string huruf sama ("aaaa") | Sering menjadi anti-hash test |
| l = 0 (mulai dari awal) | `p[0] = 1`, pastikan tidak salah indeks |
| String kosong | h hanya berisi h[0] = 0 |

---

## 🏆 7. Tips Contest

### Red flags — tanda soal ini pakai hashing

- 🚩 *"Apakah dua potongan string ini sama?"* dengan banyak pertanyaan
- 🚩 *"Berapa banyak substring berbeda?"*
- 🚩 *"Substring terpanjang yang muncul lebih dari sekali"*
- 🚩 *"Substring bersama terpanjang dari dua string"*
- 🚩 Ada **banyak pola** yang harus dicari sekaligus
- 🚩 Kamu butuh membandingkan potongan string di dalam loop

### Hashing atau KMP?

```
Cuma cari SATU pola di teks?
├── Ya → KMP (deterministik, tidak ada risiko tabrakan)
└── Tidak — perlu membandingkan banyak potongan sembarang
    └── HASHING ✅ (jauh lebih fleksibel)
```

### Kebiasaan yang menyelamatkan

1. **Selalu `long long`** untuk semua variabel hash.
2. **Selalu `+ M`** sebelum modulo pada pengurangan.
3. **Double hashing** kalau n > 10⁴ atau soalnya bisa di-hack.
4. **Base acak** di Codeforces (ada fase hacking).
5. Simpan `struct Hash` di template pribadimu — menulis ulang saat kontes membuang 5 menit.

### Time management

- Menulis prefix hash dari nol: **≤ 5 menit** kalau sudah hafal polanya.
- Kalau soal cuma minta satu pencarian pola sederhana, `s.find()` sudah cukup — jangan berlebihan.

---

## 📌 8. Ringkasan & Cheatsheet

### Cheatsheet Singkat

```
╔══════════════════════════════════════════════════════════════╗
║  STRING HASHING — CHEATSHEET                                 ║
╠══════════════════════════════════════════════════════════════╣
║  RUMUS DASAR                                                 ║
║    hash(s) = Σ s[i]·p^i  (mod m)                             ║
║    p = 131 (prima > alfabet), m = 1e9+9 (prima besar)        ║
║    petakan huruf ke 1..26, JANGAN 0..25                      ║
║                                                              ║
║  PREFIX HASH                                                 ║
║    h[i+1] = h[i] + (s[i]-'a'+1) · p[i]                       ║
║    p[i+1] = p[i] · P                                         ║
║                                                              ║
║  HASH SUBSTRING (mentah, masih berbobot p^l)                 ║
║    get(l, r) = (h[r+1] - h[l] + M) % M                       ║
║                                                              ║
║  BANDINGKAN s[a..b] vs s[c..d]  (hindari modular inverse)    ║
║    get(a,b) · p[c] % M  ==  get(c,d) · p[a] % M              ║
║                                                              ║
║  KOMPLEKSITAS                                                ║
║    bangun O(n) | hash substring O(1) | bandingkan O(1)       ║
║                                                              ║
║  PENGAMAN TABRAKAN                                           ║
║    n > 1e4        -> WAJIB double hashing                    ║
║    ada fase hack  -> base acak (mt19937_64)                  ║
╚══════════════════════════════════════════════════════════════╝
```

### Key Points

1. **Hashing mengubah perbandingan string O(L) menjadi O(1).** Itu satu-satunya alasan ia ada.
2. **Prefix hash adalah prefix sum untuk string.** Polanya persis sama.
3. **Kalikan silang, jangan membagi.** Modular inverse mahal dan mudah salah tulis.
4. **Petakan huruf mulai dari 1**, bukan 0 — kalau tidak, "a" dan "aa" bertabrakan.
5. **Hash yang sama belum tentu string yang sama.** Itulah harga kecepatannya. Double hashing
   menekan risikonya sampai praktis nol.
6. **Kalau cuma butuh cari satu pola, KMP lebih aman** karena deterministik.

### Hubungan dengan materi lain

```
Day 29: Prefix Sum ──┐
Day 22: Modulo ──────┼──► Day 33: STRING HASHING (kamu di sini)
Day 32: String Dasar ┘            │
                                  ├──► Day 34: KMP (versi deterministik)
                                  └──► Suffix Array / Automaton (lanjutan)
```

### Link Soal Latihan di Online Judge

**Codeforces**
- [CF 271D - Good Substrings](https://codeforces.com/problemset/problem/271/D) — hitung substring berbeda
- [CF 180D / 30E - Tricky and Clever Password](https://codeforces.com/problemset/problem/30/E) — hash + palindrom
- [CF 985F - Isomorphic Strings](https://codeforces.com/problemset/problem/985/F) — hashing per huruf

**LeetCode**
- [28. Find the Index of the First Occurrence](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) — Rabin-Karp
- [1044. Longest Duplicate Substring](https://leetcode.com/problems/longest-duplicate-substring/) — binary search + hash
- [187. Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/) — rolling hash

**CSES**
- [String Matching](https://cses.fi/problemset/task/1753) — hitung kemunculan pola
- [Finding Borders](https://cses.fi/problemset/task/1732) — prefix = suffix
- [Finding Periods](https://cses.fi/problemset/task/1733)
- [Longest Palindrome](https://cses.fi/problemset/task/1111) — hash maju + mundur

**AtCoder**
- [ABC 141E - Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e) — substring berulang terpanjang

---

*Selesai Day 33. Lanjut ke Day 34 (KMP) untuk versi deterministik yang tidak punya risiko tabrakan.*
