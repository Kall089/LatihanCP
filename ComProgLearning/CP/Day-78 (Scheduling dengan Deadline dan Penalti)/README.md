# 📅 Day 78 — Scheduling dengan Deadline & Penalti

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Tiga fungsi tujuan yang terlihat mirip, diawali baris kode yang sama, tetapi
> membutuhkan tiga pendekatan yang sama sekali berbeda.

---

## 🎯 Tujuan Hari Ini

- [ ] Membedakan **tiga fungsi tujuan** penjadwalan dan memilih teknik yang tepat
- [ ] Membuktikan **EDF** lewat exchange argument
- [ ] Menerapkan **Moore–Hodgson** dan menjelaskan ke mana pekerjaan yang "dibuang" pergi
- [ ] Mengenali **kapan bobot mematikan greedy** dan kapan tidak
- [ ] Menegakkan tenggat lewat **batas loop DP**, bukan pemeriksaan terpisah
- [ ] Memakai teknik **modifikasi tenggat** untuk menangani prasyarat

---

## 🔑 Tiga Fungsi Tujuan

| Yang diminimalkan | Teknik | Kompleksitas |
|---|---|---|
| Keterlambatan **maksimum** | EDF (urut tenggat) | `O(n log n)` |
| **Jumlah** yang terlambat | Moore–Hodgson (EDF + regret **MAX**) | `O(n log n)` |
| **Bobot** yang terlambat | **NP-hard**; DP untuk batasan kecil | `O(n·T)` |

Ketiganya diawali `sort` menurut tenggat menaik — sehingga kodenya terlihat mirip.
Hanya dua yang selesai di situ.

> **Bacalah fungsi tujuannya dengan sangat teliti.** "Minimalkan keterlambatan"
> saja tidak cukup; cari tahu apakah maksimum, jumlah, atau total bobot.

---

## 🧠 Inti Materi

### EDF — dan kejutannya

```cpp
sort menurut TENGGAT menaik;
ll t = 0, worst = LLONG_MIN;                  // BUKAN 0 — jawaban bisa negatif
for (auto& [d, dur] : j) { t += dur; worst = max(worst, t - d); }
```

**Durasi sama sekali tidak muncul dalam kriteria.** Alasannya: karena semua
pekerjaan dikerjakan, waktu selesai terakhir selalu `Σt` apa pun urutannya. Yang
bisa diatur hanyalah *siapa* yang menanggung akumulasi itu.

Bukti: tukar dua pekerjaan berdampingan dengan `d_i > d_j`. Setelah ditukar `L_j`
turun, dan `L_i` yang baru `= S+t_i+t_j−d_i < S+t_i+t_j−d_j` = `L_j` **semula**. ∎

### Moore–Hodgson — ke mana yang dibuang pergi

```cpp
sort menurut tenggat menaik;
priority_queue<ll> pq;                        // MAX-heap durasi
for (auto& [d, dur] : j) {
    pq.push(dur); t += dur;
    if (t > d) { t -= pq.top(); pq.pop(); }   // buang durasi TERBESAR
}
jawaban = n - pq.size();
```

Pekerjaan yang dibuang **tetap dikerjakan** — hanya dijadwalkan setelah semua
yang tepat waktu. Karena sudah pasti terlambat, kapan tepatnya tidak memengaruhi
fungsi tujuan. Isi heap adalah himpunan **tepat waktu**, bukan yang dikerjakan.

### Kapan bobot mematikan greedy

| Situasi | Greedy? |
|---|---|
| Durasi **seragam** + bobot | ✅ regret **MIN** (buang bobot terkecil) |
| Durasi **bervariasi** + bobot | ❌ NP-hard → DP |

Durasi seragam berarti hanya **satu** besaran bersaing. Begitu durasi bervariasi,
ada dua besaran (waktu yang dimakan, bobot yang diselamatkan) dan invarian Day 77
tidak bisa dirumuskan.

> **Aturan:** regret bekerja kalau keadaan bisa diringkas jadi **satu angka** yang
> bisa dibandingkan.

### DP berbobot — dua detail yang menentukan kebenaran

```cpp
sort menurut TENGGAT menaik;                  // WAJIB
vector<ll> dp(T + 1, -1);  dp[0] = 0;         // -1 = belum tercapai
for (auto& x : j) {
    ll batas = min(x.d, T);                   // tenggat = BATAS ATAS loop
    for (ll w = batas; w >= x.t; w--)         // MUNDUR
        if (dp[w - x.t] >= 0)
            dp[w] = max(dp[w], dp[w - x.t] + x.w);
}
jawaban = total − max(dp);
```

1. **Batas atas loop adalah `d_i`, bukan `T`** — itulah yang menegakkan tenggat.
2. **Urut tenggat menaik** — karena kalau sehimpunan bisa tepat waktu semua, maka
   mengerjakannya menurut tenggat menaik juga berhasil. Tanpa pengurutan, DP-nya salah.

### Modifikasi tenggat untuk prasyarat

```
d_efektif[a] = min( d[a],  d_efektif[b] − t[b] )   untuk setiap a → b
```

Proses graf ke arah **terbalik** (topologis mundur). Setelah itu, prasyarat bisa
**diabaikan sepenuhnya**: karena `d_efektif[a] < d_efektif[b]`, EDF pasti
menempatkan `a` sebelum `b` secara otomatis.

Pola "modifikasi masukan agar batasan tersirat menjadi eksplisit, lalu jalankan
algoritma sederhana" muncul di banyak soal.

### Kosakata

| Istilah | Definisi |
|---|---|
| Lateness `L_i` | `C_i − d_i` (boleh **negatif**) |
| Tardiness `T_i` | `max(0, C_i − d_i)` |
| Late job `U_i` | biner: `1` kalau `C_i > d_i` |
| Makespan | `max C_i` |

EDF meminimalkan lateness **dan** tardiness sekaligus.

### Notasi tiga bidang (untuk mencari referensi)

| Notasi | Status |
|---|---|
| `1 \|\| L_max` | EDF, mudah |
| `1 \|\| Σ U_j` | Moore–Hodgson, mudah |
| `1 \|\| Σ w_j U_j` | **NP-hard** |
| `1 \| r_j \| L_max` non-preemptive | **NP-hard** |
| `1 \| r_j \| L_max` preemptive | EDF, mudah |

---

## 📁 Struktur Berkas

```
Day-78 (Scheduling dengan Deadline dan Penalti)/
├── README.md
├── teori/
│   └── Day_78_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Keterlambatan Terkecil     (Easy)   EDF
│   ├── exercise_2.cpp   Sesedikit Mungkin Terlambat(Easy)   Moore-Hodgson
│   ├── exercise_3.cpp   Penalti Seragam            (Medium) regret MIN
│   ├── exercise_4.cpp   Denda Berbobot             (Medium) greedy MATI → DP
│   ├── exercise_5.cpp   Tenggat dengan Prasyarat   (Hard)   modifikasi tenggat
│   └── exercise_6.cpp   Denda dengan Waktu Rilis   (Hard)   bitmask
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
| Seluruh 29 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (EDF) | 4.000 kasus vs **seluruh permutasi** | cocok |
| Solusi 2 (Moore–Hodgson) | 4.000 kasus vs seluruh permutasi | cocok |
| Solusi 3 (regret seragam) | 4.000 kasus vs seluruh permutasi | cocok |
| Solusi 4 (DP berbobot) | 4.000 kasus vs seluruh permutasi | cocok |
| Solusi 5 (prasyarat) | 3.000 kasus vs **seluruh urutan topologis** | cocok |
| Solusi 6 (bitmask + rilis) | 3.000 kasus vs seluruh permutasi | cocok |
| Template | 3 × 4.000 kasus vs seluruh permutasi | cocok |

Verifikasi Solusi 5 patut dicatat: klaim "modifikasi tenggat lalu EDF biasa sudah
memenuhi seluruh prasyarat dan optimal" diuji terhadap pencarian menyeluruh atas
semua urutan topologis, bukan sekadar sampel.

Empat sample output yang saya tulis sendiri terbukti salah dan sudah diperbaiki:
Exercise 2 (datanya ternyata memberi `0`), Exercise 6 sampel 3 (`100` → `3`),
Tugas 11 (`10` → `15`), Tugas 12 (datanya diganti agar jawabannya benar `1`).

---

## ⚠️ Jebakan

1. **Memakai EDF untuk soal "jumlah terlambat"** — fungsi tujuan berbeda.
2. **Memakai Moore–Hodgson untuk soal berbobot** — ia memaksimalkan jumlah.
3. **Memaksa greedy pada weighted tardiness** — NP-hard.
4. **`worst = 0`** pada EDF — jawabannya bisa negatif, pakai `LLONG_MIN`.
5. **Batas atas loop DP memakai `T` alih-alih `d_i`** — tenggat tak tertegakkan.
6. **Lupa mengurutkan tenggat menaik sebelum DP.**
7. **Menyimpan `(denda, waktu)` sekaligus per bitmask** — kedua besaran bertentangan.
8. **Lupa `max(f, r)`** pada soal berwaktu rilis — mesin harus menunggu.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), regret (Day 77), knapsack
(Day 145), bitmask (Day 60), pengurutan topologis (Day 116), tie-break (Day 76).

**Berikutnya:**

- Day 79 — Cara Membuktikan (atau Membantah) Greedy
- Day 80 — Soal Ad-hoc
- Day 81 — Soal Constructive
- Day 82 — Invariant, Parity & Monovariant

---

## 📝 Checklist Penguasaan

- [ ] Bisa menyebutkan tiga fungsi tujuan dan tekniknya masing-masing
- [ ] Bisa membuktikan EDF dari nol
- [ ] Bisa menjelaskan ke mana pekerjaan yang dibuang Moore–Hodgson pergi
- [ ] Bisa menjelaskan kenapa durasi seragam menyelamatkan greedy
- [ ] Refleks memakai `d_i` sebagai batas atas loop DP
- [ ] Bisa menurunkan rumus tenggat efektif untuk prasyarat
- [ ] Bisa membedakan lateness dan tardiness
