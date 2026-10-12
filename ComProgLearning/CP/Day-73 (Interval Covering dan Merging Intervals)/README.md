# 📅 Day 73 — Interval Covering & Merging Intervals

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Day 72 mengajarkan *memilih* interval. Hari ini tentang *menyapu* sumbu —
> dan itu mengubah kriteria pengurutannya.

---

## 🎯 Tujuan Hari Ini

- [ ] Menjelaskan **kapan urut `l`, kapan urut `r`**, dan kenapa
- [ ] Menulis merge intervals tanpa jatuh ke jebakan `max`
- [ ] Menguasai **greedy jangkauan terjauh** untuk covering, termasuk kasus IMPOSSIBLE
- [ ] Mengenali covering yang menyamar (jump game, video stitching)
- [ ] Membedakan **"pilih dari interval yang ada"** dan **"tempatkan interval bebas"**
- [ ] Menangani perbedaan **bilangan bulat vs kontinu** dengan trik `r + 1`

---

## 🔑 Aturan Pengurutan — Baca Ini Dulu

Day 72 menanamkan refleks *"interval → urut `r`"*. Hari ini refleks itu **salah**
untuk dua pola utama.

| Kamu sedang… | Urut menurut | Contoh |
|---|---|---|
| **Menyapu sumbu** kiri→kanan | `l` | merging, covering |
| **Memilih himpunan bagian** | `r` | activity selection, titik penusuk |

> Kriteria pengurutan ditentukan oleh **pertanyaan**, bukan oleh bentuk datanya.

Kesalahan paling umum di blok ini adalah menyalin kode Day 72 lalu mengganti
soalnya. Tulis ulang dari nol setiap kali.

---

## 🧠 Inti Materi

### Merge intervals

```cpp
sort(a.begin(), a.end());                    // urut l

vector<pll> res{a[0]};
for (size_t i = 1; i < a.size(); i++) {
    auto [l, r] = a[i];
    if (l <= res.back().second)
        res.back().second = max(res.back().second, r);   // max — WAJIB
    else
        res.push_back({l, r});
}
```

**Kenapa cukup memeriksa blok terakhir:** setelah diurutkan menurut `l`, kalau
interval baru tidak beririsan dengan blok terakhir, ia pasti juga tidak
beririsan dengan blok mana pun sebelumnya — blok-blok itu berakhir lebih awal.

**Jebakan `max`:** `res.back().second = a[i].second` memendekkan `[1,10]` menjadi
`[1,3]` ketika bertemu `[2,3]`. Bug ini butuh interval yang **termuat penuh**
untuk muncul, sehingga sering lolos sampel.

### Interval covering — greedy jangkauan terjauh

```
sampai = S
selama sampai < T:
    terjauh = max(r) untuk semua interval dengan l <= sampai
    jika terjauh == sampai:  -1   (ada lubang)
    sampai = terjauh; hit++
```

**Kesalahan umum:** mengambil interval **pertama** yang muat, bukan yang
**terjauh**.

**Penunjuk tidak boleh di-reset.** `sampai` hanya membesar, jadi interval yang
sudah memenuhi `l ≤ sampai` akan selamanya memenuhinya. Penunjuk `i` hanya maju →
`O(n)`. Me-reset di setiap putaran membuatnya `O(n²)` dan TLE.

**Jangan lupa IMPOSSIBLE.** Lupa menanganinya menghasilkan loop tak berujung,
bukan sekadar jawaban salah.

### Titik penusuk minimum — dual activity selection

```cpp
sort menurut r;
for (auto& [l, r] : a)
    if (l > titik) { hit++; titik = r; }   // tembak di ujung KANAN
```

Angkanya **sama** dengan jumlah interval saling lepas maksimum. Batas bawah:
`k` interval lepas butuh `k` titik. Batas atas: algoritma memakai tepat sebanyak
itu. Keduanya bertemu → optimal.

### Bilangan bulat vs kontinu

| | `[1,3]` dan `[4,6]` |
|---|---|
| Kontinu | ada lubang `(3,4)` |
| Bilangan bulat (`{1,2,3}`, `{4,5,6}`) | menyambung, tidak ada lubang |

**Trik penyeragaman:** ubah `[l, r]` menjadi `[l, r+1]` lalu pakai kode kontinu
apa adanya.

**Cara memutuskan cepat:** "hari ke-", "menit ke-", "posisi ke-" → bilangan
bulat. "panjang", "waktu", "koordinat" → kontinu.

---

## 📁 Struktur Berkas

```
Day-73 (Interval Covering dan Merging Intervals)/
├── README.md
├── teori/
│   └── Day_73_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Menggabungkan Rentang        (Easy)    merging
│   ├── exercise_2.cpp   Total Waktu Server Sibuk     (Easy)    total panjang
│   ├── exercise_3.cpp   Menyiram Taman               (Medium)  covering
│   ├── exercise_4.cpp   Lompat Sejauh Mungkin        (Medium)  covering menyamar
│   ├── exercise_5.cpp   Menutupi dengan Panjang Tetap(Hard)    interval bebas
│   └── exercise_6.cpp   Menutupi Setiap Titik K Kali (Hard)    covering + heap
├── solusi/
│   └── solution_1..6.cpp
├── tugas/
│   └── tugas_01..15.cpp
└── template/
    └── template.cpp
```

---

## ✅ Semua Kode Sudah Diverifikasi

| Yang diuji | Cara | Hasil |
|---|---|---|
| Seluruh 30 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (merging) | 3.000 kasus acak vs referensi independen | cocok |
| Solusi 2 (total panjang) | 3.000 kasus acak vs himpunan titik langsung | cocok |
| Solusi 3 (covering) | 3.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 4 (jump) | 3.000 kasus acak vs BFS | cocok |
| Solusi 5 (menara) | 3.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 6 (K lapis) | 2.000 kasus acak vs brute force `2^n` | cocok |
| Template (covering) | 4.000 kasus acak vs brute force | cocok |

Dua sample output yang saya tulis sendiri ternyata salah dan sudah diperbaiki:
Tugas 09 (`3` → `2`) dan Tugas 10 (`2` → `1`).

---

## ⚠️ Jebakan

1. **Lupa `max`** saat menggabungkan → interval yang termuat penuh merusak hasil.
2. **Covering: ambil yang pertama muat**, bukan yang terjauh.
3. **Covering: lupa IMPOSSIBLE** → loop tak berujung → TLE.
4. **Penunjuk di-reset** di dalam loop covering → `O(n²)`.
5. **Mencampur kriteria pengurutan** Day 72 dan Day 73.
6. **Bilangan bulat diperlakukan kontinu** (atau sebaliknya).
7. **`l` bisa negatif** — jangan inisialisasi dengan 0.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), activity selection (Day 72),
priority queue (Day 24), difference array (Day 31), kompresi koordinat (Day 38/40).

**Tugas yang butuh materi lain:**

- Tugas 15 — difference array (Day 31) atau BIT (Day 170). Keduanya sudah kamu
  kerjakan → **terbuka**.
- Tugas 12 — DP di atas koordinat terkompresi (Day 38 + Day 145) → **terbuka**.
- Tugas 13 — `std::map` sebagai daftar blok (Day 21) → **terbuka**.

**Berikutnya:**

- Day 74 — Fractional Knapsack & Greedy Berbasis Rasio
- Day 75 — Huffman Coding & Greedy dengan Heap (heap dari Exercise 6 kembali)
- Day 77 — Greedy + Priority Queue (teknik regret)

---

## 📝 Checklist Penguasaan

- [ ] Bisa menyebutkan aturan "menyapu → urut `l`, memilih → urut `r`" tanpa ragu
- [ ] Refleks menulis `max` saat menggabungkan
- [ ] Bisa menulis covering lengkap dengan kasus `-1` dari nol
- [ ] Bisa menjelaskan kenapa penunjuk covering tidak perlu mundur
- [ ] Bisa mengenali jump game sebagai covering
- [ ] Selalu bertanya "bilangan bulat atau kontinu?" sebelum mengetik
