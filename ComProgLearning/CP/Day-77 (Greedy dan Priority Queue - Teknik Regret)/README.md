# 📅 Day 77 — Greedy + Priority Queue: Teknik Regret

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Sampai kemarin, setiap keputusan greedy bersifat final. Hari ini keputusan
> bisa **dibatalkan** — dan itu membuat greedy jauh lebih kuat.

---

## 🎯 Tujuan Hari Ini

- [ ] Memahami pola **ambil dulu, sesali kemudian**
- [ ] Menjelaskan invarian dominasi keadaan yang membuat regret aman
- [ ] Memilih **arah heap** secara sadar (dua pola utama berlawanan)
- [ ] Mengenali kapan keputusan sebaiknya **ditunda**, bukan diambil
- [ ] Mengoordinasikan **dua struktur** dengan penunjuk monoton
- [ ] Mengenali **kapan regret berhenti bekerja** dan beralih ke DP

---

## 🔑 Ide Inti

> Ambil dulu semua yang terlihat menguntungkan. Kalau batasannya terlanggar,
> batalkan pilihan **terburuk** yang sudah diambil.

Saat bertemu kandidat, kamu **belum tahu** apa yang akan datang. Menolak sekarang
membuang informasi; menerima lalu membatalkan menunda keputusan sampai informasinya
cukup.

### Perbedaan dengan Day 75 — ini pembeda utamanya

| | Day 75 | Day 77 |
|---|---|---|
| Isi heap | kandidat yang **belum** dipilih | pilihan yang **sudah** diambil |
| Operasi | ambil yang terbaik | **buang** yang terburuk |
| Contoh | Huffman | jadwal deadline |

---

## 🧠 Empat Pola

| Pola | Urut | Isi heap | Arah | Aksi |
|---|---|---|---|---|
| Deadline + **durasi** | deadline ↑ | durasi terpilih | **MAX** | buang durasi terbesar |
| Deadline + **untung** | deadline ↑ | untung terpilih | **MIN** | buang untung terkecil |
| Isi ulang | posisi ↑ | kupon terlewat | **MAX** | tebus kupon terbesar |
| Modal bertumbuh | modal ↑ | untung terjangkau | **MAX** | ambil untung terbesar |

Dua pola pertama **membuang**, dua terakhir **mengambil**. Arah heap dua pola
pertama **berlawanan** — dan itu bukan kebetulan.

### Kenapa arahnya berlawanan

- **Pola 1:** batasan = total durasi. Membuang durasi terbesar membebaskan waktu
  paling banyak dengan mengorbankan satu kursus.
- **Pola 2:** setiap pekerjaan memakan **slot yang sama**. Membuang mana pun
  membebaskan sumber daya yang sama, jadi yang penting hanyalah **nilainya**.

"Terburuk" berarti hal yang berbeda. Salah arah tidak menghasilkan error — hanya
jawaban salah.

### Kenapa regret aman (invarian dominasi)

Algoritma menjaga **dua** sifat sekaligus setelah memproses `i` kandidat:

1. `|S_i|` maksimum di antara semua himpunan layak
2. di antara yang berukuran maksimum, **sumber daya terpakai minimum**

Sifat (2) membuat induksinya berjalan: keadaan dengan sumber daya lebih kecil
**mendominasi** — apa pun yang bisa dilakukan dari keadaan lain, bisa juga dari
keadaan ini.

⚠️ Buktinya mengandalkan urutan pemrosesan yang membuat batasan makin **ketat**.

### Kode inti

```cpp
// Pola 1 — deadline + durasi
sort(k.begin(), k.end());                        // deadline MENAIK
priority_queue<ll> pq;                           // MAX
for (auto& [d, t] : k) {
    pq.push(t); total += t;
    if (total > d) { total -= pq.top(); pq.pop(); }
}

// Pola 2 — deadline + keuntungan
priority_queue<ll, vector<ll>, greater<ll>> pq;  // MIN
for (auto& [d, p] : j) {
    pq.push(p); total += p;
    if ((ll)pq.size() > d) { total -= pq.top(); pq.pop(); }
}
```

### Menunda keputusan (Pola 3)

Jangan isi bensin saat melewati pom — simpan sebagai **kupon**. Saat bahan bakar
habis, tebus kupon **terbesar** yang sudah terkumpul.

**Kenapa menebus kupon lama itu sah?** Secara matematis, *kapan* bahan bakar
ditambahkan tidak mengubah apakah kita bisa mencapai pom itu — kita sudah
membuktikannya dengan benar-benar sampai di sana. Yang berubah hanyalah seberapa
banyak informasi yang kita punya saat memutuskan.

### Kapan regret berhenti bekerja

Begitu ada **dua besaran yang bersaing** (misalnya waktu *dan* nilai), invarian
(2) tidak lagi bisa dirumuskan — dua keadaan tidak bisa dibandingkan lewat satu
angka. Di situ biasanya **DP**.

Exercise 5 sengaja dibuat untuk mengalami ini: kerangka regret terlihat pas, tetapi
gagal, dan batasan soal (`N ≤ 2000`, `t ≤ 1000`) adalah petunjuk peralihan ke DP.

---

## 📁 Struktur Berkas

```
Day-77 (Greedy dan Priority Queue - Teknik Regret)/
├── README.md
├── teori/
│   └── Day_77_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Mengambil Kursus          (Easy)   regret dasar
│   ├── exercise_2.cpp   Pekerjaan Bertenggat      (Easy)   arah heap berlawanan
│   ├── exercise_3.cpp   Mengisi Bahan Bakar       (Medium) menunda keputusan
│   ├── exercise_4.cpp   Modal Bertumbuh           (Medium) dua struktur
│   ├── exercise_5.cpp   Kursus dengan Bobot       (Hard)   regret GAGAL → DP
│   └── exercise_6.cpp   Mesin Ganda               (Hard)   kapasitas M
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
| Solusi 1 (kursus) | **20.000** kasus acak vs brute force `2^n` | cocok |
| Solusi 2 (bertenggat) | **20.000** kasus acak vs brute force `2^n` | cocok |
| Solusi 3 (bahan bakar) | 5.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 4 (modal) | 5.000 kasus acak vs pencarian rekursif penuh | cocok |
| Solusi 5 (DP) | 5.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 6 (M mesin) | **20.000** kasus acak vs brute force `2^n` | cocok |
| Template | 2 × 20.000 kasus vs brute force | cocok |

Dua sample output yang saya tulis sendiri terbukti salah dan sudah diperbaiki:
Exercise 5 (masukannya saya ubah agar tidak semua kursus muat) dan Tugas 10
(`2` dengan data yang ternyata memberi `3` — datanya diganti).

---

## ⚠️ Jebakan

1. **Arah heap salah** — bandingkan Pola 1 dan Pola 2.
2. **Urutan pemrosesan salah** — regret hanya benar kalau batasan makin ketat.
3. **Menolak sejak awal** alih-alih mengambil lalu membatalkan.
4. **Lupa mengurangi akumulator** saat membatalkan.
5. **Mengisi bensin saat melewati pom** — menunda lebih baik.
6. **Overflow pada `d * M`** (Exercise 6) — kedua faktor muat di `int`, hasilnya tidak.
7. **Menyangka elemen yang baru masuk tidak boleh dibuang** — boleh, dan sering memang itu yang benar.
8. **Memaksa regret pada soal dua-besaran** — itu DP.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), priority queue (Day 24),
greedy dengan heap (Day 75), penunjuk monoton (Day 73), DP knapsack (Day 145).

**Berikutnya:**

- Day 78 — Scheduling dengan Deadline & Penalti
- Day 79 — Cara Membuktikan (atau Membantah) Greedy
- Day 80–82 — Ad-hoc, Constructive, Invariant

---

## 📝 Checklist Penguasaan

- [ ] Bisa menjawab "heap ini menyimpan kandidat atau pilihan?" untuk soal baru
- [ ] Bisa menjelaskan kenapa Pola 1 memakai MAX dan Pola 2 memakai MIN
- [ ] Bisa menyebutkan invarian dua-sifat yang membuat regret aman
- [ ] Bisa menjelaskan kenapa menebus kupon dari pom yang sudah terlewat itu sah
- [ ] Refleks memeriksa overflow saat memperluas batasan (`d * M`)
- [ ] Bisa mengenali "dua besaran bersaing" sebagai tanda beralih ke DP
