# 🧱 OOP dengan C++

Folder belajar Object-Oriented Programming, disusun **per blok** — masing-masing
berisi teori, latihan bertahap, dan satu proyek penutup.

📄 **Mulai dari sini:** [`ROADMAP_OOP.md`](ROADMAP_OOP.md) — 12 blok, 2 fase.
▶️ **Sudah bisa dikerjakan:** [`Blok-01 (Dari Prosedural ke Objek)`](Blok-01%20%28Dari%20Prosedural%20ke%20Objek%29/README.md)

---

## Ringkasan Singkat

| | |
|---|---|
| **Bahasa** | C++17 (C++20 mulai Blok 6) |
| **Struktur** | 12 blok · 11 proyek + 1 capstone · tanpa penomoran hari |
| **Fase 1** | Blok 1–8 — fondasi & materi kuliah PBO |
| **Fase 2** | Blok 9–12 — SOLID, prinsip desain, design pattern |
| **Prasyarat** | C++ dasar (sudah kamu punya dari folder `CP/`) |

---

## Bedanya dengan Folder `CP/`

Ini disengaja, karena keterampilan yang dilatih memang berbeda:

| | `CP/` | `OOP/` |
|---|---|---|
| Yang dilatih | menemukan algoritma yang benar & cepat | merancang struktur yang enak diubah |
| Ukuran keberhasilan | AC di judge | kode masih enak disentuh 6 bulan lagi |
| Bentuk latihan | 15 tugas per hari, jawabannya tunggal | 5–8 latihan + proyek, jawabannya banyak |
| Umpan balik | judge bilang benar/salah | kamu sendiri, lewat perubahan requirement |

Karena tidak ada judge yang bisa bilang "desainmu buruk", tiap proyek di
roadmap ini punya bagian **"ubah requirement-nya"** — kamu diminta menambah
fitur setelah selesai. Kalau perubahan kecil menuntut kamu membongkar banyak
kelas, di situlah desainmu ketahuan.

---

## Struktur Folder Tiap Blok

```
OOP/Blok-XX (Nama Blok)/
├── README.md              panduan + checklist kelulusan blok
├── teori/Teori_Blok_XX.md penjelasan, diagram, kode beranotasi
├── latihan/latihan_N.cpp  5-8 file dengan TODO
├── solusi/solusi_N.cpp    solusi + ALASAN keputusan desainnya
└── proyek/
    ├── SPESIFIKASI.md     requirement + Perubahan Requirement
    ├── starter/
    └── referensi/
```

**Satu blok = satu unit belajar yang utuh.** Blok selesai saat proyeknya jalan
dan checklist-nya terpenuhi, bukan saat harinya habis. Kecepatan tiap orang
berbeda, dan blok-bloknya memang tidak sama berat.

Bedanya dengan folder `CP/`: file solusi di sini menjelaskan **kenapa desainnya
begitu**, bukan hanya kenapa algoritmanya benar. Sering ada bagian
"pendekatan alternatif dan trade-off"-nya, karena di OOP jarang ada satu
jawaban yang mutlak benar.

---

## Cara Belajar yang Disarankan

**1. Baca teori sambil mengetik ulang kodenya.** Bukan menyalin — mengetik.
OOP terasa mudah saat dibaca, dan itu menipu.

**2. Kerjakan latihan tanpa melihat solusi minimal 20 menit.** Kalau buntu,
baca bagian "PENDEKATAN" di file solusi, bukan kodenya.

**3. Proyek jangan dilewati.** Proyek-proyeknya saling menyambung. `MyString`
dari Blok 2 dipakai ulang di Blok 3. Sistem perpustakaan dari Blok 8 di-refactor
di Blok 9. Capstone memakai beberapa sekaligus.

**4. Setelah proyek selesai, kerjakan "Perubahan Requirement" di
`SPESIFIKASI.md`.** Ini bagian paling berharga. Desain yang baik membuat
perubahan itu terasa mudah; desain yang buruk membuatnya menyakitkan. Rasa
sakit itulah umpan baliknya.

**5. Catat di `PROGRESS.md`.** Terutama topik yang masih goyah — itu yang kamu
ulangi saat mengerjakan proyek, bukan dengan membaca ulang teorinya.

---

## Titik Periksa

Empat checkpoint ada di `ROADMAP_OOP.md`. Ringkasnya:

| Setelah | Kamu harus bisa |
|---|---|
| Blok 3 | Menjelaskan kenapa class dengan pointer mentah butuh lima fungsi |
| Blok 5 | Menggambar vtable, dan menjelaskan apa yang bocor tanpa virtual destructor |
| Blok 8 | Mengubah paragraf requirement jadi class diagram — siap ujian PBO |
| Blok 11 | Menyebut *masalah* tiap pattern, dan kapan pattern itu tidak layak dipakai |

---

## Jalur Cepat untuk Ujian PBO

Kalau ujian sudah dekat dan waktunya tidak cukup untuk seluruh Fase 1:

```
Blok 1  →  Blok 2  →  Blok 4  →  Blok 5  →  Blok 8
fondasi    enkapsulasi  inheritance  polymorphism   UML
```

Menutup hampir semua materi ujian PBO standar. Blok 3, 6, dan 7 dilewati
sementara — **tapi kembalilah ke Blok 3**, karena copy/move adalah yang
membedakan paham C++ dari sekadar bisa menulis class.

---

## Status Pembangunan Materi

| Bagian | Status |
|---|---|
| `ROADMAP_OOP.md` | ✅ selesai |
| `README.md` · `PROGRESS.md` | ✅ selesai |
| **Blok 1 — Dari Prosedural ke Objek** | ✅ **selesai** — teori, 7 latihan + solusi, proyek `Pecahan` |
| Blok 2–12 | ⬜ belum dibuat |

Materi dibangun bertahap mengikuti urutan belajar, jadi kamu tidak perlu
menunggu semuanya jadi untuk mulai.
