# 📈 Progress OOP

Isi sendiri sambil jalan. Kolom **Catatan** yang paling penting — di situ kamu
menulis apa yang masih goyah, dan itulah yang kamu ulangi saat mengerjakan
proyek (bukan dengan membaca ulang teorinya).

Tanda: `⬜` belum · `🔄` sedang · `✅` selesai · `⚠️` selesai tapi goyah

---

## Fase 1 — Fondasi & Materi Kuliah

### Blok 1 — Dari Prosedural ke Objek

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori 1 — masalah yang dipecahkan OOP | ⬜ | | |
| Teori 2 — `struct` vs `class`, akses | ⬜ | | |
| Teori 3 — member function, `this` | ⬜ | | |
| Teori 4 — constructor & destructor | ⬜ | | |
| Teori 5 — initializer list | ⬜ | | |
| Teori 6 — `const` correctness | ⬜ | | |
| Latihan 1 — dari struct ke class | ⬜ | | |
| Latihan 2 — `Waktu` | ⬜ | | |
| Latihan 3 — tebak keluaran | ⬜ | | |
| Latihan 4 — perbaiki initializer list | ⬜ | | |
| Latihan 5 — `const` correctness | ⬜ | | |
| Latihan 6 — `explicit` | ⬜ | | |
| Latihan 7 — `Persediaan` | ⬜ | | |
| 🛠 Proyek — `Pecahan` | ⬜ | | |
| ↳ Perubahan Requirement A–D | ⬜ | | berapa baris luar berubah? ___ |
| ✅ Checklist lulus blok | ⬜ | | |

### Blok 2 — Enkapsulasi & Sumber Daya

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — `MyString` | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

### Blok 3 — Copy, Move & Rule of Five

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — `MyString` → Rule of Zero | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

**🚦 Checkpoint 1** — lihat `ROADMAP_OOP.md`
- [ ] Kenapa class dengan pointer mentah butuh lima fungsi
- [ ] Di mana `MyString` crash tanpa copy constructor
- [ ] Keadaan objek setelah di-`std::move`
- [ ] Kenapa Rule of Zero lebih baik daripada Rule of Five

### Blok 4 — Inheritance

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — hierarki `Kendaraan` | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

### Blok 5 — Polymorphism

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — penggambar bentuk | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

**🚦 Checkpoint 2**
- [ ] Bisa menggambar vtable untuk hierarki tiga kelas
- [ ] Apa persisnya yang bocor tanpa virtual destructor
- [ ] Membedakan overriding, overloading, hiding di potongan kode
- [ ] Kapan `override` menyelamatkanmu dari bug

### Blok 6 — Template & Polymorphism Statis

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — `Vektor<T>` | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

### Blok 7 — Exception & Penanganan Error

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — `Vektor<T>` exception-safe | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

> Saat sampai blok ini, **kembali ke proyek `Pecahan` Blok 1** dan ganti
> penanganan pembagian-dengan-nol dari perbaikan diam-diam menjadi exception.
> Sudah dikerjakan? ⬜

### Blok 8 — UML & Desain Kelas

| Bagian | Status | Tanggal | Catatan |
|---|---|---|---|
| Teori | ⬜ | | |
| Latihan | ⬜ | | |
| 🛠 Proyek — sistem perpustakaan | ⬜ | | |
| ✅ Checklist lulus blok | ⬜ | | |

**🚦 Checkpoint 3 — Akhir Fase 1**
- [ ] Mengubah satu paragraf requirement jadi class diagram
- [ ] Membedakan aggregation dan composition **di kode**
- [ ] Menulis kelas exception-safe dengan jaminan strong
- [ ] Siap mengerjakan soal ujian PBO apa pun

---

## Fase 2 — Desain & Pattern

### Blok 9 — SOLID & Prinsip Desain

| Bagian | Status | Catatan |
|---|---|---|
| Teori | ⬜ | |
| Latihan | ⬜ | |
| 🛠 Proyek — refactor perpustakaan | ⬜ | |

### Blok 10 — Creational Pattern

Isi kolom terakhir dengan **masalahnya**, bukan diagramnya. Kalau kolom itu
tidak bisa kamu isi dari ingatan, kamu belum benar-benar paham pattern-nya.

| Pattern | Status | Masalah yang dipecahkannya |
|---|---|---|
| Factory Method | ⬜ | |
| Abstract Factory | ⬜ | |
| Builder | ⬜ | |
| Prototype | ⬜ | |
| Singleton | ⬜ | |
| 🛠 Proyek — sistem konfigurasi | ⬜ | |

### Blok 11 — Structural & Behavioral Pattern

| Pattern | Status | Masalah yang dipecahkannya |
|---|---|---|
| Adapter | ⬜ | |
| Decorator | ⬜ | |
| Composite | ⬜ | |
| Facade | ⬜ | |
| Proxy | ⬜ | |
| Bridge & Flyweight | ⬜ | |
| Strategy | ⬜ | |
| Observer | ⬜ | |
| Command | ⬜ | |
| State | ⬜ | |
| Template Method | ⬜ | |
| Iterator | ⬜ | |
| Visitor | ⬜ | |
| CoR · Mediator · Memento | ⬜ | |
| 🛠 Proyek — editor teks | ⬜ | |

**🚦 Checkpoint 4**
- [ ] Menyebutkan **masalah** tiap pattern, bukan diagramnya
- [ ] Menunjuk kapan sebuah pattern **tidak** layak dipakai
- [ ] Merefactor kode 200 baris yang buruk, dengan alasan tiap langkah

### Blok 12 — Kualitas Kode & Capstone

| Bagian | Status | Catatan |
|---|---|---|
| Arsitektur berlapis | ⬜ | |
| Menguji kode OOP | ⬜ | |
| Code smell & refactoring | ⬜ | |
| Anti-pattern OOP | ⬜ | |
| 🏁 Capstone | ⬜ | |

---

## Daftar Topik yang Masih Goyah

Pindahkan ke sini setiap kali kamu menandai `⚠️`. Hapus barisnya saat sudah mantap.

| Blok | Topik | Kenapa masih goyah | Sudah diulang? |
|---|---|---|---|
| | | | |

---

## Catatan Proyek

| Proyek | Selesai | Perubahan requirement? | Yang dipelajari |
|---|---|---|---|
| 1 — `Pecahan` | ⬜ | ⬜ | |
| 2 — `MyString` | ⬜ | ⬜ | |
| 3 — Rule of Zero | ⬜ | ⬜ | |
| 4 — `Kendaraan` | ⬜ | ⬜ | |
| 5 — Penggambar bentuk | ⬜ | ⬜ | |
| 6 — `Vektor<T>` | ⬜ | ⬜ | |
| 7 — Exception-safe | ⬜ | ⬜ | |
| 8 — Perpustakaan | ⬜ | ⬜ | |
| 9 — Refactor SOLID | ⬜ | ⬜ | |
| 10 — Sistem konfigurasi | ⬜ | ⬜ | |
| 11 — Editor teks | ⬜ | ⬜ | |
| 🏁 Capstone | ⬜ | — | |
