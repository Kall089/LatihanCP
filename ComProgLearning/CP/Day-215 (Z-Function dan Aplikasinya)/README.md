# Day 215 — Z-Function & Aplikasinya

> **Ide satu kalimat:** `z[i]` menjawab *"kalau aku menempelkan salinan S di posisi i, berapa huruf yang cocok?"* — dan satu pointer yang tidak pernah mundur membuatnya O(n).

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 215, kamu akan mampu:

- [ ] Membedakan `z[i]` (melihat ke depan) dari `pi[i]` (melihat ke belakang)
- [ ] Menulis konstruksi z-box **9 baris** dengan benar dari ingatan
- [ ] Menjelaskan kenapa `r` monoton naik ⟹ total O(n)
- [ ] Memakai trik `P + separator + T` dan tahu kenapa separator wajib
- [ ] Menurunkan **border**, **periode**, **kompresi**, **rotasi** dari `z[i] == n − i`
- [ ] Memilih antara Z dan pi secara sadar, bukan karena kebiasaan

---

## Struktur Folder

```
Day-215 (Z-Function dan Aplikasinya)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_215_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Bangun Z-Array)
│   ├── exercise_2.cpp   (Warm-up  : Cari Pola dengan Z)
│   ├── exercise_3.cpp   (Core     : Border, Periode, Kompresi)
│   ├── exercise_4.cpp   (Core     : Kalung Berputar / Rotasi)
│   ├── exercise_5.cpp   (Challenge: Awalan Bersama Minimal K)
│   └── exercise_6.cpp   (Contest  : Menyusun Teks dari Stempel — CF 535D)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← bangunZ, cariZ, border, periode, rotasi, overlap, z→pi
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

`teori/Day_215_Teori_Lengkap.md`. Tiga bagian yang menentukan:

1. **Diagram z-box** (bagian 1). Fokus pada satu pertanyaan: *kenapa tebakan awal dibatasi
   `r − i`?* Jawabannya — di luar z-box kita tidak punya bukti apa pun — adalah seluruh
   algoritma dalam satu kalimat.
2. **Tabel trace `"aabcaabxaabc"`** (bagian 4.1). Perhatikan baris `i = 5` dan `i = 9`:
   keduanya menyalin dari kembaran dan tidak mulai dari nol. Itu penghematannya.
3. **Trace matching `"aba"` di `"ababa"`** (bagian 4.2). Perhatikan `z[4]` berhenti **tepat**
   di 3 karena separator.

### Langkah 2 — Pelajari Template (15 menit)

`template/template.cpp`. Yang wajib masuk template pribadimu adalah **9 baris ini, persis**:

```cpp
vector<int> bangunZ(const string& s) {
    int n = s.size(); vector<int> z(n, 0); int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}
```

> ⚠️ **Konvensi `r` di sini EKSKLUSIF.** Versi inklusif yang beredar memakai
> `min(r - i + 1, ...)`. Kedua-duanya benar, tapi **mencampurnya** adalah off-by-one
> yang bisa menghabiskan 40 menit kontes. Pilih satu, tulis di template, jangan pernah ganti.

### Langkah 3 — Kerjakan Latihan (90–120 menit)

| # | Judul | Tingkat | Waktu target | Konsep utama |
|---|-------|---------|--------------|--------------|
| 1 | Bangun Z-Array | Easy | 15 mnt | z-box dari nol |
| 2 | Cari Pola | Easy | 15 mnt | separator + konversi indeks |
| 3 | Border/Periode/Kompresi | Medium | 20 mnt | `z[i] == n − i` |
| 4 | Kalung Berputar | Medium | 25 mnt | `B+B`, hindari hitung ganda |
| 5 | Awalan Bersama Min K | Hard | 30 mnt | histogram + suffix sum |
| 6 | Stempel (CF 535D) | Hard | 40 mnt | border ⟹ tumpang tindih valid |

**Aturan frustrasi 30 menit** berlaku. Buntu lewat itu → baca **komentar approach** di
`solusi/`, tutup lagi, tulis sendiri.

### Langkah 4 — Tugas (di luar sesi)

- **01–05 (Easy):** terapan langsung. CSES 1753, CSES 1732, CF 126B ada di sini.
- **06–10 (Medium):** butuh satu transformasi (reverse, concat, komplemen).
- **11–15 (Hard):** ABC141 E, ABC150 F, CF 1968G1, CF 535D, SPOJ PERIOD.

Tugas 14 sengaja lebih alami dikerjakan dengan **pi**, bukan z. Kerjakan dua-duanya
lalu catat mana yang lebih nyaman — itu latihan memilih alat, bukan sekadar memakai alat.

---

## Cara Kompilasi & Uji

```bash
g++ -std=c++17 -O2 -Wall -o sol solusi/solution_2.cpp
printf 'ababa\naba\n' | ./sol
```

---

## Cheatsheet Hari Ini

```
z[i] = panjang awalan bersama S dan S[i..]     z[0] = 0 (konvensi kita)

INTI (r eksklusif):
  if (i < r) z[i] = min(r - i, z[i - l]);
  while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
  if (i + z[i] > r) { l = i; r = i + z[i]; }

cari pola      : z pada P + '\1' + T, cek z[i] >= |P|
border         : z[i] == n - i          (panjangnya n - i)
periode kecil  : i TERKECIL dengan z[i] == n - i
kompresi       : + syarat n % i == 0
rotasi         : z pada A + '\1' + B + B, hanya k = 0..|B|-1
hitung prefiks : histogram z + suffix sum, +1 untuk posisi 0
substr berbeda : Σ (|cur| - max z(rev(cur)))   O(n²)

SEPARATOR: '\1', BUKAN '#'
```

---

## pi atau z? Tabel Keputusan

| Situasi | Pilih |
| ------- | ----- |
| "cocok berapa huruf dari posisi i dengan awal string" | **Z** — definisinya langsung |
| Butuh **automaton** untuk DP counting string | **pi** — Z tidak punya automaton |
| Rantai border / hitung kemunculan tiap prefiks | **pi** — rantainya adalah pohon |
| Semua border sekaligus | **Z** — satu loop lurus, tanpa rantai |
| Matching sederhana sekali pakai | **Z** — 9 baris, lebih sedikit yang bisa salah |
| Memori ketat (butuh `O(m)` saja) | **pi** — tidak perlu string gabungan |
| Kamu grogi dan hanya hafal satu | **yang kamu hafal** |

---

## Common Mistakes Hari Ini

1. **Mencampur konvensi `r`** inklusif dan eksklusif. Bug paling mahal hari ini.
2. **Separator `'#'` bocor** karena input boleh memuatnya. Pakai `'\1'`.
3. **`z[0] = n`** di implementasi lain, lalu `max(z)` jadi salah total.
4. **Lupa `n % i == 0`** pada kompresi. Sama seperti jebakan Day 214.
5. **`while` tanpa cek `i + z[i] < n`** → baca di luar string.
6. **Rotasi dihitung ganda:** posisi `k = |B|` di `B+B` duplikat dari `k = 0`.
   Sampel `"aaaa"` akan memberi 5 alih-alih 4.
7. **Memori `P + sep + T`** untuk `|P| = |T| = 10^6` = 8 MB int. Biasanya aman, tapi hitung.

---

## Checklist Sebelum Lanjut ke Day 216

- [ ] Bisa menulis `bangunZ` dari ingatan dalam < 2 menit, tanpa off-by-one
- [ ] Bisa menjelaskan kenapa totalnya O(n) (argumen `r` monoton)
- [ ] Bisa menjelaskan kenapa separator wajib, dengan contoh tandingan
- [ ] Hafal `z[i] == n − i` ⟹ border
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah menyelesaikan minimal 8 dari 15 tugas
- [ ] Sudah AC minimal 2 soal di online judge (CSES 1753 dan CSES 1732 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1753 — String Matching](https://cses.fi/problemset/task/1753) | CSES | matching dasar |
| [CSES 1732 — Finding Borders](https://cses.fi/problemset/task/1732) | CSES | border via z |
| [CF 126B — Password](https://codeforces.com/problemset/problem/126/B) | Codeforces | border + kemunculan tengah |
| [CF 432D — Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) | Codeforces | z lebih mudah dari pi di sini |
| [CF 535D — Tavas and Malekas](https://codeforces.com/problemset/problem/535/D) | Codeforces | border + cakupan interval |
| [CF 1968G1 — Division + LCP](https://codeforces.com/problemset/problem/1968/G1) | Codeforces | z + binary search |
| [ABC 141 E — Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e) | AtCoder | substring berulang |
| [ABC 150 F — Xor Shift](https://atcoder.jp/contests/abc150/tasks/abc150_f) | AtCoder | z pada array, bukan string |
| [SPOJ PERIOD](https://www.spoj.com/problems/PERIOD/) | SPOJ | periode tiap prefiks |

---

## Preview Day 216 — Manacher

Besok: **semua substring palindrom dalam O(n)**.

Kamu akan melihat **pola yang sama persis** dengan hari ini — satu interval "paling kanan"
yang sudah terbukti, kembaran yang dicerminkan, dan pointer yang tidak pernah mundur.
Bedanya cuma satu: cerminnya bukan translasi, melainkan **refleksi**.

Kalau hari ini kamu benar-benar paham kenapa `r` tidak pernah mundur, besok akan terasa
seperti mengenali wajah lama.
