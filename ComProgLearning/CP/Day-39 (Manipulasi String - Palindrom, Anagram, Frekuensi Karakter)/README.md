# Day 32 — String Dasar: Palindrom, Anagram & Frekuensi Karakter

> **Ide satu kalimat:** banyak pertanyaan tentang string bisa dijawab dengan **menghitung**, bukan dengan mengurutkan atau mencoba semua susunan.

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 32, kamu akan mampu:

- [ ] Menguasai operasi `std::string` yang paling sering dipakai di kontes
- [ ] Mengecek **palindrom** dengan dua pointer dalam **O(N)** tanpa memori tambahan
- [ ] Mengecek **anagram** lewat tabel frekuensi **O(N)**, bukan sorting O(N log N)
- [ ] Memakai **tabel frekuensi 26 huruf** sebagai senjata utama soal string
- [ ] Menentukan apakah string bisa **disusun ulang** menjadi palindrom
- [ ] Mencari **palindrom terpanjang** dengan *expand around center*
- [ ] Menghindari jebakan `cin >>` bercampur `getline` dan indeks `substr`

---

## Struktur Folder

```
Day-32 (String Dasar)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_32_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Cek Palindrom)
│   ├── exercise_2.cpp   (Warm-up  : Anagram atau Bukan)
│   ├── exercise_3.cpp   (Core     : Huruf Paling Sering Muncul)
│   ├── exercise_4.cpp   (Core     : Susun Ulang Jadi Palindrom)
│   ├── exercise_5.cpp   (Challenge: Menghitung Kemunculan Pola)
│   └── exercise_6.cpp   (Contest  : Palindrom Terpanjang)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← palindrom, frekuensi, expand center, pencarian pola
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori
`teori/Day_32_Teori_Lengkap.md`. Fokus pada **analogi kalung manik-manik** di bagian 1
dan **tabel trace** di bagian 4 — dua bagian itu yang membuat konsepnya "klik".

### Langkah 2 — Pelajari Template
`template/template.cpp` berisi empat fungsi siap pakai: `palindrom`, `anagram`,
`susunPalindrom`, dan `palindromTerpanjang`.

### Langkah 3 — Kerjakan Latihan Berurutan
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
echo "katak" | ./latihan/exercise_1
```

### Langkah 4 — Cek Solusi (kalau macet > 30 menit)
Semua solusi **sudah diverifikasi**: dikompilasi dan dijalankan pada seluruh
sample (18 uji, lolos semua).

### Langkah 5 — Kerjakan 15 Tugas Mandiri
Target minimal **10 dari 15** sebelum lanjut ke Day 33 (String Hashing).

---

## Quick Reference — Cheatsheet String Dasar

```
OPERASI PENTING
  s.substr(mulai, PANJANG)   // (mulai, PANJANG) — bukan (mulai, akhir)!
  s.find(t)                  // string::npos kalau tidak ketemu
  reverse(s.begin(), s.end());
  sort(s.begin(), s.end());
  cin.ignore();              // WAJIB sebelum getline setelah cin >>

PALINDROM  — dua pointer, O(N) waktu, O(1) memori
  int i = 0, j = s.size() - 1;
  while (i < j) if (s[i++] != s[j--]) return false;
  return true;

TABEL FREKUENSI — senjata utama
  int f[26] = {};
  for (char c : s) f[c - 'a']++;

ANAGRAM         -> tambah untuk A, kurangi untuk B, semua harus nol
BISA PALINDROM  -> banyaknya huruf berfrekuensi ganjil <= 1
PALINDROM TERPANJANG -> expand around center, DUA jenis pusat:
                        (i, i) untuk ganjil, (i, i+1) untuk genap

Tiga jebakan utama:
  ✗ substr(2, 5) dikira "indeks 2 sampai 5"   -> itu (mulai, PANJANG)
  ✗ getline langsung setelah cin >> n         -> dapat baris kosong
  ✗ c - 'a' pada huruf besar/spasi            -> indeks negatif, crash
```

---

## Cara Cepat Memilih Teknik

```
Soal tentang string?
├── Cuma butuh "huruf apa & berapa banyak"?
│   └── TABEL FREKUENSI 26   (paling murah, coba ini dulu)
├── Membandingkan dua ujung?
│   └── DUA POINTER
├── Substring terpanjang dengan syarat?
│   └── SLIDING WINDOW (Day 20)
└── Cari pola di teks panjang (N > 10^5)?
    └── KMP (Day 34) atau HASHING (Day 33)
```

---

## Soal Online Judge Rekomendasi

### LeetCode (paling ramah untuk memulai)
- [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)
- [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)
- [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)
- [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
- [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

### CSES
- [Palindrome Reorder](https://cses.fi/problemset/task/1755) — persis exercise 4

### Codeforces
- [CF 118A - String Task](https://codeforces.com/problemset/problem/118/A)
- [CF 4C - Registration System](https://codeforces.com/problemset/problem/4/C)

### AtCoder
- [ABC 122B - ATCG](https://atcoder.jp/contests/abc122/tasks/abc122_b)

---

## Checklist Penyelesaian

- [ ] Membaca teori, terutama bagian Trace
- [ ] Bisa menjelaskan sendiri kenapa `kiri < kanan`, bukan `kiri <= kanan`
- [ ] `exercise_1.cpp` — palindrom dua pointer
- [ ] `exercise_2.cpp` — anagram tabel frekuensi
- [ ] `exercise_3.cpp` — huruf terbanyak + tie-breaking
- [ ] `exercise_4.cpp` — susun ulang jadi palindrom
- [ ] `exercise_5.cpp` — hitung kemunculan pola
- [ ] `exercise_6.cpp` — palindrom terpanjang (dua jenis pusat!)
- [ ] Minimal 10 dari 15 tugas mandiri
- [ ] Submit & AC **CSES Palindrome Reorder**
- [ ] Bisa menjawab: kapan harus pindah dari pencarian naif ke KMP?

---

**Materi visual pendamping:** buka `learn-cp-visual` → menu **String → String Dasar**
untuk melihat animasi dua pointer dan tabel frekuensi bergerak langkah demi langkah.
