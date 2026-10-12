# 📊 Day 32: String Dasar — Palindrom, Anagram & Frekuensi Karakter

> **Prasyarat:** Two Pointers (Day 19), STL string (Day 3)
> **Estimasi belajar:** 2–3 jam (teori + 6 latihan)
> **Kata kunci soal:** _"dibaca bolak-balik sama"_, _"huruf sama tapi urutan beda"_, _"berapa kali huruf muncul"_

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 32, kamu akan mampu:

- [ ] Menguasai operasi `std::string` yang paling sering dipakai di kontes
- [ ] Mengecek **palindrom** dengan dua pointer dalam **O(N)** tanpa memori tambahan
- [ ] Mengecek **anagram** lewat tabel frekuensi dalam **O(N)**, bukan sorting O(N log N)
- [ ] Membangun dan memakai **tabel frekuensi 26 huruf** sebagai senjata utama
- [ ] Menentukan apakah sebuah string bisa **disusun ulang** menjadi palindrom
- [ ] Mencari **palindrom terpanjang** d`engan teknik _expand around center_
- [ ] Menghindari jebakan `cin >> ` bercampur `getline`, dan indeks `substr`

---

## 🔍 1. Konsep & Intuisi

### Apa itu string di C++?

`std::string` pada dasarnya adalah **`vector<char>` yang diberi fasilitas tambahan**. Artinya semua kebiasaan vector berlaku: bisa di-`sort`, di-`reverse`, diakses dengan `s[i]`, dan punya `.size()`.

```cpp
string s = "halo";
s[0]          // 'h'      -> akses seperti array
s.size()      // 4
s += " dunia" // "halo dunia"
sort(s.begin(), s.end());   // huruf terurut
```

### Analogi: kalung manik-manik

Bayangkan string sebagai **kalung manik-manik berwarna**.

- **Palindrom** = kalung yang kalau dibalik, urutan warnanya tetap sama. Cara mengeceknya: pegang manik paling kiri dan paling kanan dengan dua jari, lalu jalankan kedua jari ke tengah sambil membandingkan.
- **Anagram** = dua kalung yang **jumlah tiap warnanya sama persis**, walaupun urutannya berbeda. Untuk mengeceknya kamu tidak perlu menyusun ulang kalungnya — cukup **hitung** ada berapa manik merah, berapa biru, dan seterusnya di masing-masing kalung.

> Inti Day 32: **banyak pertanyaan tentang string bisa dijawab dengan MENGHITUNG, bukan MENGURUTKAN atau MENCOBA SEMUA SUSUNAN.**

### Kenapa tabel frekuensi begitu penting?

Karena huruf kecil 'a'–'z' hanya ada 26, kita bisa menyimpan seluruh informasi "huruf apa saja yang ada dan berapa banyak" dalam **array berukuran 26** — sangat kecil dan sangat cepat.

```cpp
int hitung[26] = {};
for (char c : s) hitung[c - 'a']++;
```

**Kenapa `c - 'a'`?** Huruf disimpan komputer sebagai angka, dan 'a' sampai 'z' berurutan. Jadi:

```
'a' - 'a' = 0     'b' - 'a' = 1     'c' - 'a' = 2   ...   'z' - 'a' = 25
```

Hasilnya pas dipakai sebagai indeks array 0..25.

### Visualisasi ASCII: cek palindrom "katak"

```
       k    a    t    a    k
       ↑                   ↑
     kiri                kanan       'k' == 'k'  ✓  keduanya maju ke tengah

       k    a    t    a    k
            ↑         ↑
          kiri      kanan            'a' == 'a'  ✓  maju lagi

       k    a    t    a    k
                 ↑↑
              bertemu                 berhenti -> PALINDROM ✓

Jumlah perbandingan hanya N/2, bukan N.
```

### Visualisasi ASCII: anagram lewat frekuensi

```
"gerak"                    "kerag"
  g:1 e:1 r:1 a:1 k:1        k:1 e:1 r:1 a:1 g:1

Tabel frekuensi (hanya huruf yang muncul):
        a    e    g    k    r
gerak   1    1    1    1    1
kerag   1    1    1    1    1
        ─────────────────────
selisih 0    0    0    0    0   -> semua nol -> ANAGRAM ✓
```

### Kapan digunakan? (Pattern Recognition)

| Kalimat di soal                        | Teknik                               |
| -------------------------------------- | ------------------------------------ |
| "dibaca dari depan dan belakang sama"  | Dua pointer                          |
| "susunan ulang dari kata lain"         | Tabel frekuensi                      |
| "huruf mana yang paling sering muncul" | Tabel frekuensi                      |
| "bisakah disusun jadi palindrom"       | Tabel frekuensi + hitung yang ganjil |
| "substring terpanjang yang palindrom"  | Expand around center                 |
| "berapa kali pola muncul" (N kecil)    | Pencarian naif / `s.find`            |
| "berapa kali pola muncul" (N besar)    | KMP (Day 34) atau hashing (Day 33)   |

---

## 🧮 2. Analisis Kompleksitas

| Operasi                               | Kompleksitas                    | Catatan                          |
| ------------------------------------- | ------------------------------- | -------------------------------- |
| Cek palindrom (dua pointer)           | **O(N)** waktu, **O(1)** memori | Hanya N/2 perbandingan           |
| Cek palindrom (balik lalu bandingkan) | O(N) waktu, **O(N)** memori     | Boros memori, hindari            |
| Anagram (tabel frekuensi)             | **O(N)** waktu, O(26) memori    | ✅ cara terbaik                  |
| Anagram (sorting)                     | O(N log N)                      | Benar tapi lebih lambat          |
| Bisa jadi palindrom                   | **O(N)**                        | Hitung huruf berfrekuensi ganjil |
| Palindrom terpanjang (expand center)  | **O(N²)**                       | Cukup untuk N ≤ 5000             |
| Palindrom terpanjang (Manacher)       | O(N)                            | Materi lanjutan                  |
| Pencarian pola naif                   | O(N × M)                        | Cukup untuk N, M kecil           |
| `s.substr(i, len)`                    | **O(len)**                      | ⚠️ menyalin, bukan gratis!       |

### Perbandingan: anagram dengan sorting vs frekuensi

| N   | Sorting O(N log N) | Frekuensi O(N) |
| --- | ------------------ | -------------- |
| 10⁵ | ~1,7 juta operasi  | 10⁵ operasi    |
| 10⁶ | ~20 juta operasi   | 10⁶ operasi    |

Keduanya lolos, tapi frekuensi lebih cepat **dan** kodenya sama pendeknya.

---

## 💻 3. Implementasi C++

### 3.1 Operasi string yang wajib hafal

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "kompetisi";

    // ── Dasar ──
    cout << s.size() << "\n";           // 9
    cout << s[0] << "\n";               // 'k'
    cout << s.back() << "\n";           // 'i'

    // ── Iris (substr) ──
    cout << s.substr(0, 4) << "\n";     // "komp"  -> (mulai, PANJANG)
    cout << s.substr(3) << "\n";        // "petisi" -> dari indeks 3 sampai habis

    // ── Cari ──
    size_t pos = s.find("pet");
    if (pos != string::npos) cout << "ketemu di " << pos << "\n";   // 3

    // ── Ubah ──
    reverse(s.begin(), s.end());        // balik
    sort(s.begin(), s.end());           // urutkan hurufnya
    s += "!";                           // sambung

    // ── Konversi ──
    int angka = stoi("123");            // string -> int
    string teks = to_string(456);       // int -> string

    // ── Huruf besar/kecil ──
    for (char &c : s) c = tolower(c);
    return 0;
}
```

### 3.2 Cek palindrom (dua pointer)

```cpp
bool palindrom(const string& s) {
    int kiri = 0, kanan = (int)s.size() - 1;
    while (kiri < kanan) {
        if (s[kiri] != s[kanan]) return false;  // beda -> langsung berhenti
        kiri++;
        kanan--;
    }
    return true;   // dua jari bertemu tanpa perbedaan
}
```

> **Kenapa `kiri < kanan`, bukan `kiri <= kanan`?**
> Kalau panjangnya ganjil, huruf tengah tidak perlu dibandingkan dengan dirinya sendiri.
> Memakai `<` menghemat satu perbandingan dan tetap benar.

### 3.3 Cek anagram (tabel frekuensi)

```cpp
bool anagram(const string& a, const string& b) {
    if (a.size() != b.size()) return false;   // cek murah, lakukan duluan

    int hitung[26] = {};
    for (char c : a) hitung[c - 'a']++;       // tambah untuk a
    for (char c : b) hitung[c - 'a']--;       // kurangi untuk b

    for (int i = 0; i < 26; i++)
        if (hitung[i] != 0) return false;     // ada yang tidak seimbang
    return true;
}
```

### 3.4 Bisakah disusun ulang jadi palindrom?

```cpp
bool bisaJadiPalindrom(const string& s) {
    int hitung[26] = {};
    for (char c : s) hitung[c - 'a']++;

    int ganjil = 0;
    for (int i = 0; i < 26; i++)
        if (hitung[i] % 2 == 1) ganjil++;

    // Dalam palindrom semua huruf harus berpasangan.
    // Paling banyak SATU huruf boleh sendirian (diletakkan di tengah).
    return ganjil <= 1;
}
```

### 3.5 Palindrom terpanjang (expand around center)

```cpp
string palindromTerpanjang(const string& s) {
    int n = s.size();
    if (n == 0) return "";
    int mulaiTerbaik = 0, panjangTerbaik = 1;

    auto lebarkan = [&](int kiri, int kanan) {
        while (kiri >= 0 && kanan < n && s[kiri] == s[kanan]) {
            kiri--;
            kanan++;
        }
        // setelah loop, [kiri+1 .. kanan-1] adalah palindrom
        int panjang = kanan - kiri - 1;
        if (panjang > panjangTerbaik) {
            panjangTerbaik = panjang;
            mulaiTerbaik = kiri + 1;
        }
    };

    for (int i = 0; i < n; i++) {
        lebarkan(i, i);       // pusat satu huruf  -> panjang ganjil
        lebarkan(i, i + 1);   // pusat dua huruf   -> panjang genap
    }
    return s.substr(mulaiTerbaik, panjangTerbaik);
}
```

---

## 🔄 4. Trace / Simulasi

### Contoh 1: cek palindrom "malam"

| Langkah | kiri | kanan | s[kiri] | s[kanan] | Hasil                    |
| ------- | ---- | ----- | ------- | -------- | ------------------------ |
| 1       | 0    | 4     | 'm'     | 'm'      | sama ✓ lanjut            |
| 2       | 1    | 3     | 'a'     | 'a'      | sama ✓ lanjut            |
| 3       | 2    | 2     | —       | —        | kiri == kanan → berhenti |

**Hasil: PALINDROM.** Hanya 2 perbandingan untuk 5 huruf.

### Contoh 2: cek palindrom "kodok" vs "kodak"

```
"kodok" :  k o d o k        "kodak" :  k o d a k
           ↑       ↑                   ↑       ↑
           k = k   ✓                   k = k   ✓

           k o d o k                   k o d a k
             ↑   ↑                       ↑   ↑
             o = o ✓                     o ≠ a ✗  -> BUKAN palindrom
                                         berhenti di sini, tidak perlu lanjut
```

### Contoh 3: bisakah "aabbc" disusun jadi palindrom?

| Huruf | Frekuensi | Ganjil? |
| ----- | --------- | ------- |
| a     | 2         | tidak   |
| b     | 2         | tidak   |
| c     | 1         | **ya**  |

Jumlah huruf berfrekuensi ganjil = **1** → `1 <= 1` → **BISA**.
Contoh susunannya: `abcba` ✓

Bandingkan dengan `"aabbcd"`:

| Huruf | Frekuensi | Ganjil? |
| ----- | --------- | ------- |
| a     | 2         | tidak   |
| b     | 2         | tidak   |
| c     | 1         | **ya**  |
| d     | 1         | **ya**  |

Ganjil = 2 → `2 > 1` → **TIDAK BISA**. Dua huruf tidak bisa sama-sama menempati posisi tengah.

### Contoh 4: expand around center pada "babad"

| i   | Pusat | Melebar sampai  | Palindrom ditemukan | Panjang |
| --- | ----- | --------------- | ------------------- | ------- |
| 0   | b     | —               | "b"                 | 1       |
| 1   | a     | kiri=0, kanan=2 | **"bab"**           | **3**   |
| 1   | ab    | tidak melebar   | —                   | 0       |
| 2   | b     | kiri=1, kanan=3 | **"aba"**           | 3       |
| 3   | a     | —               | "a"                 | 1       |
| 4   | d     | —               | "d"                 | 1       |

**Jawaban: "bab"** (panjang 3, ditemukan lebih dulu daripada "aba").

---

## 📝 5. Variasi & Pattern

### Variasi 1: palindrom yang mengabaikan spasi & huruf besar

```cpp
bool palindromLonggar(string s) {
    string bersih;
    for (char c : s)
        if (isalnum(c)) bersih += tolower(c);   // ambil huruf & angka saja
    int i = 0, j = bersih.size() - 1;
    while (i < j) if (bersih[i++] != bersih[j--]) return false;
    return true;
}
// "Kasur ini rusak" -> "kasurinirusak" -> palindrom ✓
```

### Variasi 2: kelompokkan anagram

Kunci pengelompokan bisa berupa string yang sudah diurutkan, atau string frekuensi:

```cpp
map<string, vector<string>> grup;
for (string kata : daftar) {
    string kunci = kata;
    sort(kunci.begin(), kunci.end());   // "gerak" dan "kerag" -> "aegkr"
    grup[kunci].push_back(kata);
}
```

### Variasi 3: substring dengan huruf unik (butuh Day 20)

Gabungan tabel frekuensi + sliding window:

```cpp
int substringUnikTerpanjang(const string& s) {
    int hitung[26] = {}, kiri = 0, terbaik = 0;
    for (int kanan = 0; kanan < (int)s.size(); kanan++) {
        hitung[s[kanan] - 'a']++;
        while (hitung[s[kanan] - 'a'] > 1)      // ada yang dobel
            hitung[s[kiri++] - 'a']--;          // kecilkan jendela dari kiri
        terbaik = max(terbaik, kanan - kiri + 1);
    }
    return terbaik;
}
```

### Variasi 4: menghitung kemunculan pola (N kecil)

```cpp
int hitungMuncul(const string& teks, const string& pola) {
    int total = 0;
    for (size_t i = teks.find(pola); i != string::npos; i = teks.find(pola, i + 1))
        total++;
    return total;
}
// Untuk teks sangat panjang, ganti dengan KMP (Day 34).
```

### Variasi 5: perbandingan leksikografis

```cpp
if (a < b) ...          // "apel" < "bola" -> true, seperti urutan kamus
sort(kata.begin(), kata.end());   // vector<string> otomatis terurut kamus
```

⚠️ Hati-hati: `"Z" < "a"` bernilai **true**, karena huruf besar punya kode lebih kecil. Samakan dulu kalau tidak ingin begitu.

---

## ⚠️ 6. Common Mistakes & Edge Cases

### ❌ Mistake 1: `cin >>` lalu `getline` (paling sering!)

```cpp
int n;
cin >> n;
string baris;
getline(cin, baris);        // ❌ dapat string KOSONG!

// Penyebab: karakter enter setelah angka masih tertinggal di buffer.
cin >> n;
cin.ignore();               // ✅ buang sisa baris
getline(cin, baris);
```

### ❌ Mistake 2: parameter `substr` dikira (mulai, akhir)

```cpp
string s = "kompetisi";
s.substr(2, 5);    // ✅ "mpeti"  -> (mulai, PANJANG)
// BUKAN dari indeks 2 sampai 5!

// Kalau ingin dari i sampai j (inklusif):
s.substr(i, j - i + 1);
```

### ❌ Mistake 3: `substr` di dalam loop

```cpp
for (int i = 0; i < n; i++)
    if (s.substr(i, m) == pola) ...   // ❌ O(N × M), substr MENYALIN string

// Lebih baik bandingkan karakter langsung, atau pakai KMP.
```

### ❌ Mistake 4: `c - 'a'` pada huruf besar atau spasi

```cpp
string s = "Halo Dunia";
hitung[s[0] - 'a']++;      // ❌ 'H' - 'a' = -25 -> INDEKS NEGATIF, crash!

// Perbaikan:
for (char c : s)
    if (islower(c)) hitung[c - 'a']++;
// atau samakan dulu: c = tolower(c);
// atau pakai array 128 elemen dengan indeks (unsigned char)c
```

### ❌ Mistake 5: membandingkan `s.size()` dengan int negatif

```cpp
if (s.size() - 1 >= 0)     // ❌ SELALU true! size() bertipe unsigned
                           // string kosong: 0 - 1 = angka raksasa
if ((int)s.size() - 1 >= 0)  // ✅ cast dulu ke int
```

### Edge Cases yang perlu diuji

| Kasus                     | Kenapa berbahaya                                  |
| ------------------------- | ------------------------------------------------- |
| String kosong `""`        | Palindrom? Umumnya **ya**. Cek agar tidak crash   |
| Satu huruf `"a"`          | Selalu palindrom                                  |
| Semua huruf sama `"aaaa"` | Palindrom, dan semua substringnya palindrom       |
| Panjang genap vs ganjil   | Expand around center **wajib** menangani keduanya |
| Ada spasi / huruf besar   | `c - 'a'` bisa jadi indeks negatif                |

---

## 🏆 7. Tips Contest

### Red flags — tanda soal ini pakai teknik Day 32

- 🚩 _"Apakah kata ini dibaca sama dari depan dan belakang?"_ → dua pointer
- 🚩 _"Apakah kedua kata tersusun dari huruf yang sama?"_ → tabel frekuensi
- 🚩 _"Huruf apa yang paling sering muncul?"_ → tabel frekuensi
- 🚩 _"Bisakah huruf-hurufnya disusun ulang menjadi ...?"_ → tabel frekuensi
- 🚩 _"Substring terpanjang yang ..."_ → sliding window atau expand center

### Aturan praktis memilih teknik

```
Soal tentang string?
├── Cuma perlu tahu "huruf apa & berapa banyak"?
│   └── TABEL FREKUENSI 26  (paling murah, coba ini dulu)
├── Perlu membandingkan dua ujung?
│   └── DUA POINTER
├── Perlu substring terpanjang dengan syarat tertentu?
│   └── SLIDING WINDOW (Day 20)
└── Perlu mencari pola di teks panjang (N > 10^5)?
    └── KMP (Day 34) atau HASHING (Day 33)
```

### Time management

- Soal palindrom/anagram sederhana harus selesai **< 5 menit**. Ini biasanya soal A atau B di Div 2 — kerjakan lebih dulu untuk mengamankan poin.
- Jangan langsung memakai KMP untuk soal pencarian pola kalau N ≤ 1000. Pencarian naif sudah cukup dan **jauh lebih kecil risikonya salah tulis**.

### Trik implementasi

```cpp
// 1. Cek palindrom satu baris (untuk string pendek)
bool p = equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());

// 2. Tabel frekuensi langsung dari string
array<int, 26> f{};
for (char c : s) f[c - 'a']++;

// 3. Cek anagram tanpa array bantu (kalau boleh mengubah string)
sort(a.begin(), a.end());
sort(b.begin(), b.end());
bool ana = (a == b);
```

---

## 📌 8. Ringkasan & Cheatsheet

### Cheatsheet Singkat

```
╔══════════════════════════════════════════════════════════════╗
║  STRING DASAR — CHEATSHEET                                   ║
╠══════════════════════════════════════════════════════════════╣
║  OPERASI PENTING                                             ║
║    s.substr(mulai, PANJANG)     // bukan (mulai, akhir)!     ║
║    s.find(t)                    // string::npos kalau gagal  ║
║    reverse(s.begin(), s.end());                              ║
║    sort(s.begin(), s.end());                                 ║
║    cin.ignore();                // sebelum getline!          ║
║                                                              ║
║  PALINDROM  (dua pointer, O(N) waktu O(1) memori)            ║
║    int i = 0, j = s.size() - 1;                              ║
║    while (i < j) if (s[i++] != s[j--]) return false;         ║
║    return true;                                              ║
║                                                              ║
║  TABEL FREKUENSI                                             ║
║    int f[26] = {};                                           ║
║    for (char c : s) f[c - 'a']++;                            ║
║                                                              ║
║  ANAGRAM        -> tambah untuk a, kurangi untuk b, cek nol  ║
║  BISA PALINDROM -> banyaknya huruf ganjil <= 1               ║
║  PALINDROM TERPANJANG -> expand around center, 2 pusat:      ║
║                          (i, i) ganjil dan (i, i+1) genap    ║
╚══════════════════════════════════════════════════════════════╝
```

### Key Points

1. **Menghitung lebih murah daripada menyusun.** Anagram tidak butuh sorting; palindrom tidak butuh membalik string.
2. **Tabel frekuensi 26 huruf adalah senjata paling sering terpakai** di soal string tingkat awal.
3. **Dua pointer bekerja karena string punya dua ujung.** Pola yang sama muncul lagi di Day 34 (KMP).
4. **`substr` menyalin, bukan menunjuk.** Memanggilnya di dalam loop diam-diam membuat kode jadi O(N × M).
5. **`cin.ignore()` sebelum `getline`** — satu baris yang menyelamatkan dari bug "kok input saya kosong".
6. **Palindrom punya dua jenis pusat**: satu huruf (ganjil) dan dua huruf (genap). Lupa salah satunya = jawaban salah.

### Hubungan dengan materi lain

```
Day 19: Two Pointers ──┐
Day 20: Sliding Window ─┼──► Day 32: STRING DASAR (kamu di sini)
Day 3 : STL string ────┘            │
                                    ├──► Day 33: String Hashing
                                    └──► Day 34: KMP
```

### Link Soal Latihan di Online Judge

**LeetCode (mulai dari sini, paling ramah pemula)**

- [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) — palindrom dengan pembersihan
- [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/) — anagram klasik
- [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/) — pengelompokan
- [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) — expand around center
- [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) — frekuensi + sliding window

**Codeforces**

- [CF 4C - Registration System](https://codeforces.com/problemset/problem/4/C) — map string
- [CF 25A - IQ Test](https://codeforces.com/problemset/problem/25/A)
- [CF 118A - String Task](https://codeforces.com/problemset/problem/118/A) — manipulasi huruf dasar

**AtCoder**

- [ABC 049C - Daydream](https://atcoder.jp/contests/abc049/tasks/arc065_a) — greedy pada string
- [ABC 076B / ABC 122B - ATCG](https://atcoder.jp/contests/abc122/tasks/abc122_b) — substring

**CSES**

- [Palindrome Reorder](https://cses.fi/problemset/task/1755) — persis materi "bisa jadi palindrom"

---

_Selesai Day 32. Lanjut ke Day 33 (String Hashing) atau Day 34 (KMP) untuk menangani teks yang jauh lebih panjang._
