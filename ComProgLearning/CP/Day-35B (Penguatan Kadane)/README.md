# Day 35B — Penguatan Kadane

> Sesi sisipan, bukan materi baru. Tujuannya menutup tiga celah yang biasanya
> tersisa sesudah Day 35: **kenapa benar**, **kapan dipakai**, **cara menurunkan varian**.
> Setelah ini, lanjut Day 36 (Monotonic Stack) dengan tenang.

**Estimasi: 2,5 – 3 jam.** Boleh dipecah dua hari.

---

## Kenapa sesi ini ada

Kadane itu tiga baris, jadi mudah "terasa paham" padahal yang terjadi cuma hafal
bentuknya. Tandanya khas: bisa menulis versi dasar, tapi bingung saat soalnya
berbunyi lain, dan tidak yakin kenapa reset itu sah. Day 35 sudah mengajarkan
mekanismenya — sesi ini mengejar **modelnya**.

---

## Struktur

```
Day-35B (Penguatan Kadane)/
├── README.md
├── teori/Penguatan_Kadane.md          ← inti sesi
├── latihan/
│   ├── drill_1_klasifikasi.md         ← pengenalan pola, tanpa kode
│   ├── drill_2_cari_bug.cpp           ← enam Kadane rusak + stress tester
│   └── drill_3_turunkan.cpp           ← lima varian, kamu yang turunkan
└── solusi/
    ├── drill_1_kunci.md
    ├── drill_2_kunci.md
    └── drill_3_kunci.cpp
```

---

## Urutan Pengerjaan

### Langkah 1 — Teori Bagian A (40 menit)
`teori/Penguatan_Kadane.md`, berhenti di akhir Bagian A.

Yang harus terjadi di kepala setelah bagian ini: kamu bisa menulis
`dp[i] = a[i] + max(0, dp[i-1])` dan menjelaskan **kenapa `a[i]` selalu ikut**.

Kerjakan **A.5 Uji Paham Diri** dengan jujur — tutup file kodenya. Kalau ada yang
tidak terjawab, itu justru informasi paling berharga di sesi ini.

### Langkah 2 — Drill 2: Cari Bug (30 menit)
`latihan/drill_2_cari_bug.cpp`

**Baca dulu, jangan compile.** Tebak bug + counterexample-nya di kertas, baru
jalankan. Menemukan bug orang lain melatih otot yang berbeda dari menulis kode
sendiri, dan itu otot yang dipakai saat kamu debugging di menit ke-40 kontes.

```bash
g++ -std=c++17 -O2 -o drill_2 drill_2_cari_bug.cpp && ./drill_2
```

Satu dari enam sengaja lolos stress test. Cari tahu kenapa — itu poin terpenting
dari drill ini.

### Langkah 3 — Teori Bagian B (25 menit)
Pohon keputusan + tabel "yang terlihat seperti Kadane tapi bukan".
Bagian ini yang paling menentukan di kontes dan paling jarang dilatih.

### Langkah 4 — Drill 1: Klasifikasi (15 menit)
`latihan/drill_1_klasifikasi.md` — 12 skenario, tulis teknik + sinyalnya.
Tanpa menulis kode sama sekali.

**Target: 10/12.** Di bawah itu, ulangi Bagian B besok sebelum lanjut Day 36.

### Langkah 5 — Teori Bagian C + Drill 3 (60 menit)
Baca Bagian C, lalu kerjakan `latihan/drill_3_turunkan.cpp`.

Aturan mainnya: **isi tiga baris turunan di komentar sebelum menulis kode.**
Kalau tiga baris itu tidak bisa kamu isi, kodenya pasti asal tebak.

```bash
g++ -std=c++17 -O2 -o drill_3 drill_3_turunkan.cpp && ./drill_3
```

| Soal | Varian | Yang dilatih |
|---|---|---|
| A | Minimum subarray | memakai ulang alat yang sudah ada, bukan menulis ulang |
| B | Melingkar | membelah ruang jawaban + penjaga edge case |
| C | Hapus ≤ 1 elemen | menambah state ke dp |
| D | Panjang ≥ k | **mengenali kapan Kadane tidak cukup** |
| E | Dua segmen terpisah | mengunci titik potong |

---

## Kriteria Lulus

Sesi ini selesai kalau ketiganya terpenuhi:

- [ ] Bisa menuliskan invariant `cur` dan `best` dari ingatan, dan menjelaskan
      kenapa `dp[i-1] ≤ 0` berarti buang
- [ ] Skor Drill 1 minimal 10/12
- [ ] Drill 3 hijau semua **tanpa** membuka kunci untuk soal A, B, C
      (D dan E boleh dengan bantuan — keduanya sudah melampaui Kadane)

Kalau lulus → **Day 36: Monotonic Stack**. Materinya sudah ada di folder `CP/`.

Kalau belum, yang paling berguna bukan mengulang seluruh Day 35, melainkan
mengulang **bagian yang gagal saja**: gagal di uji paham diri → Bagian A;
gagal di Drill 1 → Bagian B; gagal di Drill 3 → Bagian C.

---

## Soal Online untuk Konsolidasi

Kerjakan setelah lulus, sebagai pemantapan (bukan bagian dari sesi):

| Soal | Sumber | Varian |
|---|---|---|
| Maximum Subarray Sum | CSES 1643 | dasar |
| Maximum Subarray Sum II | CSES 1644 | panjang antara a dan b (= Drill 3 soal D) |
| Maximum Product Subarray | LeetCode 152 | dua variabel |
| Maximum Sum Circular Subarray | LeetCode 918 | melingkar |
| Maximum Subarray Sum with One Deletion | LeetCode 1186 | Kadane + state |
| Best Sightseeing Pair | LeetCode 1014 | pola "kunci ujung kanan" |
| Max Sum Rectangle | Codeforces gym / SPOJ KADANE2D | 2D |

Soal **Best Sightseeing Pair** layak dikerjakan meski terlihat tidak berhubungan —
ia melatih pola inti yang sama (kunci `r`, simpan yang terbaik dari kiri) dalam
penyamaran yang cukup berbeda untuk menguji apakah kamu benar-benar paham polanya.
