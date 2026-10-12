# 📅 Day 72 — Activity Selection & Interval Scheduling

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Penerapan pertama exchange argument Day 71 pada keluarga soal yang paling
> sering muncul di kontes: **interval**.

---

## 🎯 Tujuan Hari Ini

- [ ] Menjalankan activity selection `O(n log n)` tanpa berpikir
- [ ] **Membuktikan** kenapa "ujung terkecil" benar, dan menyebutkan **tiga kriteria salah** beserta contoh tandingannya
- [ ] Selalu menentukan **tertutup vs setengah terbuka** sebelum menulis kode
- [ ] Membedakan lima varian soal interval dan tahu masing-masing pakai teknik apa
- [ ] Mengenali sinyal **"ada bobot → bukan greedy, tapi DP"**
- [ ] Menyelesaikan varian dengan **banyak sumber daya** (K ruangan/mesin)

---

## 🗺️ Peta Keputusan Soal Interval

Empat kata pertama dalam soal menentukan seluruh pendekatanmu.

```
Soal interval
├── "sebanyak mungkin saling lepas"     -> urut r, greedy          O(n log n)
├── "sesedikit mungkin dibuang"         -> n − greedy di atas      O(n log n)
├── "semua dijadwalkan, berapa ruangan" -> sapuan event / heap     O(n log n)
├── "total bobot maksimum"              -> DP + lower_bound        O(n log n)
├── "K sumber daya + bobot"             -> MCMF / DP berdimensi    lebih mahal
└── "tutupi seluruh [0, T]"             -> greedy jangkauan        (Day 73)
```

---

## 🧠 Inti Materi

### Algoritmanya

```cpp
sort(a.begin(), a.end(), [](auto& x, auto& y){ return x.r < y.r; });

int hit = 0;
ll akhir = LLONG_MIN;            // BUKAN 0
for (auto& it : a)
    if (it.l > akhir) { hit++; akhir = it.r; }
```

**Intuisi satu kalimat:** interval yang selesai paling awal menyisakan sisa waktu
terbanyak untuk semua interval berikutnya.

### Tiga kriteria yang terlihat masuk akal tetapi salah

| Kriteria | Contoh tandingan | Greedy | Optimal |
|---|---|---|---|
| Urut waktu **mulai** | `[1,100] [2,3] [4,5]` | 1 | 2 |
| Urut **durasi** terpendek | `[1,10] [9,12] [11,20]` | 1 | 2 |
| Urut **konflik** paling sedikit | susunan bertingkat | 3 | 4 |
| **Urut ujung `r`** | — | ✅ benar | |

Kalau kamu tidak bisa menuliskan exchange argument untuk sebuah kriteria,
kriteria itu belum layak dipercaya.

### Tertutup vs setengah terbuka — penyebab WA nomor satu

`[1,5]` dan `[5,9]` — bentrok atau tidak? Bergantung soal.

| Model | Kapan | Syarat kode |
|---|---|---|
| Setengah terbuka `[l, r)` | "boleh langsung pindah saat selesai" | `it.l >= akhir` |
| Tertutup `[l, r]` | interval bilangan bulat, "termasuk kedua ujung" | `it.l > akhir` |

Satu karakter membedakan AC dan WA. Exercise 1 (setengah terbuka) dan Exercise 2
(tertutup) sengaja dipasangkan agar kamu terbiasa bertanya sebelum mengetik.

### Ruangan minimum — dua cara

```cpp
// Cara 1: sapuan event.  {t,-1} otomatis sebelum {t,+1} karena -1 < +1
for (auto& it : a) { ev.push_back({it.l, +1}); ev.push_back({it.r, -1}); }
sort(ev.begin(), ev.end());
int cur = 0, best = 0;
for (auto& e : ev) { cur += e.second; best = max(best, cur); }

// Cara 2: heap berisi waktu selesai ruangan yang terpakai
sort menurut l;
for (auto& it : a) {
    if (!pq.empty() && pq.top() <= it.l) pq.pop();
    pq.push(it.r);
}
jawaban = pq.size();
```

Keduanya menghitung hal yang sama: **tumpang tindih maksimum**. Fakta ini
(bilangan kromatik graf interval = ukuran klik maksimum) dipakai lagi di
Exercise 6 dan Tugas 08.

### Begitu ada bobot, greedy mati

```
[1,10] p=100      [1,2] p=1      [3,4] p=1
greedy: 2         optimal: 100
```

DP-nya:

```cpp
sort menurut r;
int p = lower_bound(R.begin(), R.begin() + i, L[i]) - R.begin();
dp[i+1] = max(dp[i], W[i] + dp[p]);
```

`lower_bound` untuk interval **tertutup**, `upper_bound` untuk **setengah
terbuka**. Salah pilih = WA yang sangat sulit dilacak.

---

## 📁 Struktur Berkas

```
Day-72 (Activity Selection dan Interval Scheduling)/
├── README.md
├── teori/
│   └── Day_72_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Festival Film                (Easy)    setengah terbuka
│   ├── exercise_2.cpp   Menghapus Jadwal Bentrok     (Easy)    tertutup
│   ├── exercise_3.cpp   Ruang Rapat Minimum          (Medium)  sapuan event
│   ├── exercise_4.cpp   Kelas dengan Dua Ruangan     (Medium)  dua sumber daya
│   ├── exercise_5.cpp   Jadwal Berbobot              (Hard)    DP
│   └── exercise_6.cpp   Menyewakan Mesin             (Hard)    K mesin + bobot
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
| Solusi 1 | 3.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 2 | 3.000 kasus acak vs brute force | cocok |
| Solusi 3 | 3.000 kasus acak vs perhitungan tindihan langsung | cocok |
| Solusi 4 | 3.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 5 | 3.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 6 (MCMF) | 1.200 kasus acak vs brute force `2^n` | cocok |
| Template | 3.000 kasus acak greedy vs brute force | cocok |

Generator stress test sengaja memakai koordinat **kecil** (1–15). Dengan
koordinat besar interval jarang bertabrakan dan semua strategi terlihat benar —
pelajaran tersendiri tentang cara membuat generator yang bagus. Tugas 14 meminta
kamu mengalami ini sendiri.

---

## ⚠️ Jebakan

1. **Mengurutkan menurut `l`.** Naluri terkuat, dan salah.
2. **`akhir = 0`.** Kalau ada `l ≤ 0`, interval pertama terlewat. Pakai `LLONG_MIN`.
3. **Menyalin `>` atau `>=` dari soal sebelumnya** tanpa memeriksa model interval.
4. **Menyangka soal berbobot bisa greedy.** Cari kata bobot/nilai/keuntungan.
5. **Ruangan minimum dikira activity selection.** Baca apakah interval boleh dibuang.
6. **`lower_bound` vs `upper_bound`** pada DP berbobot.
7. **"Jalankan greedy K kali"** untuk K sumber daya. Tidak benar — lihat Exercise 4.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), komparator (Day 43–47),
priority queue (Day 24), `lower_bound` (Day 49), kompresi koordinat (Day 38/40),
DP knapsack (Day 145).

**Tugas yang butuh materi lain:**

- Tugas 15 — butuh Fenwick Tree (Day 170) + kompresi koordinat (Day 38/40).
  Keduanya sudah kamu kerjakan, jadi tugas ini **terbuka**.
- Tugas 11 — memakai pola knapsack (Day 145), sudah **terbuka**.

**Berikutnya:**

- Day 73 — Interval Covering & Merging Intervals (greedy jangkauan, pola berbeda)
- Day 74 — Fractional Knapsack & Greedy Berbasis Rasio
- Day 77 — Greedy + Priority Queue (heap dari hari ini akan kembali)

---

## 📝 Checklist Penguasaan

- [ ] Bisa menulis activity selection dari nol dalam kurang dari 60 detik
- [ ] Bisa menyebutkan tiga kriteria salah **beserta contoh tandingannya**
- [ ] Selalu bertanya "tertutup atau setengah terbuka?" sebelum mengetik
- [ ] Bisa menjelaskan kenapa ruangan minimum = tumpang tindih maksimum
- [ ] Refleks berpikir DP begitu melihat bobot pada interval
- [ ] Bisa menjelaskan kenapa "pakai ruangan yang bebas paling akhir" itu benar
