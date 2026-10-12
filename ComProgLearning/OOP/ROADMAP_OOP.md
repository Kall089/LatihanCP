# 🧱 ROADMAP OOP DENGAN C++

**Bahasa:** C++17 (C++20 mulai Blok 6)
**Struktur:** 12 blok · 2 fase · 11 proyek + 1 capstone
**Prasyarat:** C++ dasar — variabel, fungsi, pointer, referensi, `vector`. Sudah kamu punya dari folder `CP/`.

> **Roadmap ini tidak dibagi per hari.** Satu blok = satu unit belajar yang utuh,
> selesai saat proyeknya jalan dan checklist-nya terpenuhi — bukan saat harinya habis.
> Kecepatan tiap orang berbeda dan blok-bloknya memang tidak sama berat.

---

## 🎯 Kenapa C++ untuk Belajar OOP

Java dan Python menyembunyikan banyak hal demi kenyamanan. C++ tidak.
Menyebalkan saat menulis kode, tapi **ideal saat belajar** — kamu jadi melihat
mekanisme yang di bahasa lain hanya bisa dihafal:

- **Destructor** — Java punya garbage collector, jadi "kapan objek mati" tidak
  pernah terasa. Di C++ kamu mengendalikannya, dan dari situ lahir RAII.
- **Copy vs move** — di Java semua objek adalah referensi, jadi "menyalin objek"
  bukan pertanyaan. Di C++ ini pertanyaan besar, dan menjawabnya membuatmu
  paham *value semantics*.
- **Virtual table** — polymorphism di Java terasa ajaib. Di C++ kamu bisa
  melihat mekanismenya, dan paham kenapa ada biayanya.
- **Polymorphism statis** — template memberi cara kedua, yang tidak ada
  padanannya di Java klasik.

Setelah roadmap ini, pindah ke OOP Java atau Python butuh beberapa hari, bukan
beberapa bulan.

---

## 📖 Cara Pakai

1. **Satu blok = satu unit.** Kerjakan berurutan, jangan lompat.
2. **Proyek di akhir blok itu wajib.** Bukan bonus — beberapa proyek dipakai
   ulang di blok berikutnya.
3. **Setelah proyek jalan, kerjakan bagian "Perubahan Requirement"** di
   `SPESIFIKASI.md`. Di sinilah desainmu benar-benar diuji.
4. **Blok selesai kalau checklist-nya terpenuhi**, bukan kalau materinya sudah
   dibaca. Checklist ada di `README.md` tiap blok.
5. **Kode diketik ulang, bukan disalin.** OOP terasa mudah saat dibaca — itu menipu.

### Struktur folder tiap blok

```
OOP/Blok-XX (Nama Blok)/
├── README.md              panduan + checklist kelulusan blok
├── teori/Teori_Blok_XX.md penjelasan + diagram + kode beranotasi
├── latihan/               file .cpp dengan TODO
├── solusi/                solusi + ALASAN keputusan desainnya
└── proyek/
    ├── SPESIFIKASI.md     requirement + perubahan requirement
    ├── starter/
    └── referensi/
```

---

# ═══════════════════════════════════
# FASE 1 — FONDASI & MATERI KULIAH
# ═══════════════════════════════════

Setelah fase ini kamu bisa mengerjakan hampir semua soal ujian PBO, membaca
kode OOP orang lain, dan menulis class yang **benar**. Belum tentu class yang
**bagus** — itu urusan Fase 2.

---

## 📦 Blok 1 — Dari Prosedural ke Objek

> Paham **masalah apa** yang sebenarnya dipecahkan OOP, dan bisa menulis class
> sederhana yang siklus hidupnya benar.

- Masalah yang dipecahkan OOP: state tersebar, coupling, invariant yang bocor
- `struct` vs `class`, access specifier (`public` / `private` / `protected`)
- Member function, pointer `this`, definisi di luar kelas
- Constructor & destructor: siklus hidup objek
- Member initializer list & urutan inisialisasi yang sebenarnya
- `const` correctness: `const` member function dan objek `const`

**🛠 Proyek — `Pecahan`:** class pecahan dengan penyederhanaan otomatis, operasi
aritmetika, perbandingan, dan pencetakan.

---

## 📦 Blok 2 — Enkapsulasi & Sumber Daya

> Enkapsulasi bukan soal "bikin `private` lalu kasih getter", melainkan soal
> **menjaga invariant**.

- Invariant kelas: siapa yang menjaganya, dan kapan ia boleh dilanggar sementara
- Getter & setter: kapan berguna, kapan justru merusak enkapsulasi
- `static` member variable & `static` member function
- `friend` function dan `friend` class: kekuatan dan bahayanya
- Operator overloading (`+`, `==`, `<`, `<<`, `[]`)
- RAII: kenapa destructor adalah fitur pembeda C++

**🛠 Proyek — `MyString`:** class string dengan manajemen memori manual.

---

## 📦 Blok 3 — Copy, Move & Rule of Five

> Blok tersulit di Fase 1 dan yang paling sering dilewati di kuliah. Kalau kamu
> menguasainya, kamu sudah di atas rata-rata lulusan PBO.

- Copy constructor: shallow copy vs deep copy
- Copy assignment operator & jebakan self-assignment
- Rule of Three: kenapa ketiganya datang bersamaan
- Move semantics: `rvalue` reference dan `std::move`
- Move constructor, move assignment — Rule of Five
- Rule of Zero & smart pointer (`unique_ptr`, `shared_ptr`)

**🛠 Proyek — refactor `MyString`:** dari Rule of Five ke Rule of Zero.

**🚦 Checkpoint 1**
- [ ] Bisa menjelaskan kenapa class dengan pointer mentah **butuh** lima fungsi
- [ ] Bisa menunjuk di kode mana `MyString` akan crash tanpa copy constructor
- [ ] Bisa menjelaskan keadaan objek setelah di-`std::move`
- [ ] Tahu kenapa Rule of Zero lebih baik daripada Rule of Five

---

## 📦 Blok 4 — Inheritance

> Blok ini mengajarkan inheritance **beserta batasnya**. Topik terakhir sengaja
> mengkritik topik-topik sebelumnya; itu bukan kontradiksi, itu intinya.

- Inheritance dasar: relasi *is-a* dan `public` inheritance
- `protected`, `private` inheritance, dan perubahan hak akses
- Urutan pemanggilan constructor & destructor dalam hierarki
- Function hiding vs overloading vs overriding — tiga hal berbeda
- Multiple inheritance, diamond problem, `virtual` inheritance
- **Kapan inheritance justru salah:** LSP dan pengantar komposisi

**🛠 Proyek — hierarki `Kendaraan`:** dibangun, lalu dikritisi sendiri.

---

## 📦 Blok 5 — Polymorphism

> Inti dari OOP. Setelah blok ini kamu bisa menjelaskan **bagaimana**
> polymorphism bekerja, bukan sekadar memakainya.

- `virtual` function & dynamic dispatch
- Virtual table: bagaimana polymorphism bekerja di balik layar
- Virtual destructor: kenapa wajib, dan apa persisnya yang bocor tanpanya
- Pure virtual function & abstract class
- Interface di C++ (abstract class tanpa data)
- `override`, `final`, dan bug diam-diam yang dicegahnya

**🛠 Proyek — penggambar bentuk:** dengan renderer yang bisa diganti-ganti.

**🚦 Checkpoint 2**
- [ ] Bisa menggambar vtable untuk hierarki tiga kelas
- [ ] Bisa menjelaskan apa persisnya yang bocor kalau destructor tidak `virtual`
- [ ] Bisa membedakan overriding, overloading, dan hiding di potongan kode
- [ ] Tahu kapan `override` menyelamatkanmu dari bug

---

## 📦 Blok 6 — Template & Polymorphism Statis

> Cara kedua melakukan polymorphism. Ini yang membedakan "bisa OOP" dari
> "bisa C++ modern".

- Function template & deduksi tipe
- Class template
- Template specialization (penuh dan parsial)
- Polymorphism statis vs dinamis: trade-off dan kapan pilih mana
- CRTP — pengantar
- `concept` (C++20): cara modern membatasi template

**🛠 Proyek — `Vektor<T>`:** container generik dengan iterator.

---

## 📦 Blok 7 — Exception & Penanganan Error

> Kuncinya bukan sintaks `try/catch`, melainkan **jaminan** apa yang diberikan
> fungsimu saat gagal.

- `try` / `catch` / `throw` dan hierarki `std::exception`
- Exception safety: jaminan basic, strong, nothrow
- RAII sebagai fondasi exception safety — copy-and-swap idiom
- `noexcept`: apa artinya dan kapan dipakai
- Alternatif exception: error code, `std::optional`, `std::expected`
- Anti-pattern: `catch(...)`, menelan error, exception sebagai alur normal

**🛠 Proyek — `Vektor<T>` exception-safe:** menambahkan jaminan strong.

---

## 📦 Blok 8 — UML & Desain Kelas

> Sebagian besar materi ujian PBO ada di sini. Tapi tujuannya bukan menghafal
> notasi — melainkan bisa **berpikir dalam relasi antar objek** sebelum menulis kode.

- Class diagram: notasi dasar dan cara membacanya
- Association, aggregation, composition — beserta bedanya **di kode**
- Dependency, generalization, realization
- Sequence diagram: memodelkan alur interaksi
- Use case diagram secukupnya, dan kenapa jangan berlebihan
- Dari kalimat requirement ke class diagram

**🛠 Proyek — sistem perpustakaan:** diagram dulu, kode kemudian.

**🚦 Checkpoint 3 — Akhir Fase 1**
- [ ] Bisa mengubah satu paragraf requirement menjadi class diagram
- [ ] Bisa membedakan aggregation dan composition **di kode**, bukan cuma di diagram
- [ ] Bisa menulis kelas yang exception-safe dengan jaminan strong
- [ ] Siap mengerjakan soal ujian PBO apa pun

---

# ═══════════════════════════════════
# FASE 2 — DESAIN & PATTERN
# ═══════════════════════════════════

Fase 1 mengajarkan **mekanisme**. Fase 2 mengajarkan **penilaian** — kapan
memakai mekanisme itu, dan yang lebih penting, kapan tidak.

---

## 📦 Blok 9 — SOLID & Prinsip Desain

> Lima prinsip yang paling sering disebut dan paling sering disalahpahami,
> ditambah prinsip lain yang justru lebih sering berguna sehari-hari.

- **S** — Single Responsibility (dan apa arti "satu alasan berubah")
- **O** — Open/Closed
- **L** — Liskov Substitution (dan kasus Persegi vs Persegi Panjang)
- **I** — Interface Segregation
- **D** — Dependency Inversion
- **Kritik terhadap SOLID:** kapan prinsip ini berlebihan
- Composition over inheritance — mendalam
- Law of Demeter & "Tell, Don't Ask"
- DRY, KISS, YAGNI — dan bahayanya kalau dipaksakan
- Coupling & cohesion: cara mengenalinya di kode sendiri
- Dependency Injection

**🛠 Proyek — refactor sistem perpustakaan** (proyek Blok 8) dengan SOLID + DI.

---

## 📦 Blok 10 — Creational Pattern

> Mulai blok ini, tiap pattern dipelajari dengan urutan tetap:
> **masalah → solusi naif → kenapa gagal → pattern → kapan TIDAK dipakai.**
> Menghafal diagram pattern tanpa tahu masalahnya adalah cara tercepat
> menghasilkan kode yang terlalu rumit.

- Factory Method
- Abstract Factory
- Builder
- Prototype
- Singleton — dan kenapa banyak orang membencinya

**🛠 Proyek — sistem konfigurasi & pembuatan objek.**

---

## 📦 Blok 11 — Structural & Behavioral Pattern

**Structural:**
- Adapter · Decorator · Composite · Facade · Proxy
- Bridge & Flyweight (ringkas)

**Behavioral:**
- Strategy · Observer · Command (dengan undo/redo) · State
- Template Method · Iterator · Visitor
- Chain of Responsibility, Mediator, Memento (ringkas)

**🛠 Proyek — editor teks:** dengan undo/redo dan sistem plugin.

**🚦 Checkpoint 4**
- [ ] Bisa menyebutkan **masalah** yang dipecahkan setiap pattern, bukan diagramnya
- [ ] Bisa menunjuk kapan sebuah pattern **tidak** layak dipakai
- [ ] Bisa merefactor kode 200 baris yang buruk, dengan alasan tiap langkah

---

## 📦 Blok 12 — Kualitas Kode & Capstone

- Arsitektur berlapis: memisahkan domain dari infrastruktur
- Menguji kode OOP: unit test, test double, *seam*
- Code smell & katalog refactoring
- Anti-pattern OOP: God Object, Anemic Model, Yo-yo Problem

**🏁 Capstone — aplikasi lengkap** dari requirement sampai test.

---

# 📊 Ringkasan

| Blok | Tema | Proyek |
|---|---|---|
| 1 | Dari prosedural ke objek | `Pecahan` |
| 2 | Enkapsulasi & sumber daya | `MyString` manual |
| 3 | Copy, move, Rule of Five | `MyString` → Rule of Zero |
| 4 | Inheritance & batasnya | Hierarki `Kendaraan` |
| 5 | Polymorphism | Penggambar bentuk |
| 6 | Template & polymorphism statis | `Vektor<T>` |
| 7 | Exception & error handling | `Vektor<T>` exception-safe |
| 8 | UML & desain kelas | Sistem perpustakaan |
| 9 | SOLID & prinsip desain | Refactor perpustakaan |
| 10 | Creational pattern | Sistem konfigurasi |
| 11 | Structural & behavioral pattern | Editor teks |
| 12 | Kualitas kode & capstone | Aplikasi lengkap |

---

# 🛣 Jalur Cepat untuk Ujian PBO

Kalau ujian dekat dan waktunya tidak cukup untuk seluruh Fase 1:

```
Blok 1  →  Blok 2  →  Blok 4  →  Blok 5  →  Blok 8
fondasi    enkapsulasi  inheritance  polymorphism   UML
```

Menutup hampir semua materi ujian PBO standar. Blok 3, 6, 7 dilewati sementara
— **tapi kembalilah ke Blok 3**, karena copy/move adalah yang membedakan paham
C++ dari sekadar bisa menulis class.

---

# ⚠️ Kesalahan Umum Saat Belajar OOP

Bukan kesalahan sintaks — kesalahan cara belajar, dan lebih mahal:

1. **Mengira OOP = bikin class untuk semua hal.** Fungsi bebas sering jawaban
   yang lebih baik. Blok 9 membahas ini.
2. **Menghafal definisi 4 pilar tanpa merasakan masalahnya.** "Enkapsulasi
   adalah menyembunyikan data" itu hafalan. "Enkapsulasi adalah menjaga
   invariant agar objek tidak pernah berada di keadaan tidak valid" itu paham.
3. **Memakai inheritance untuk berbagi kode.** Penyebab kerusakan terbesar di
   kode OOP nyata. Inheritance untuk *substitutability*, bukan reuse.
4. **Belajar design pattern terlalu awal.** Pattern tanpa pengalaman merasakan
   masalahnya menghasilkan over-engineering. Itu sebabnya pattern ada di
   Blok 10, bukan Blok 3.
5. **Melewati proyek karena "sudah paham teorinya".** Kamu tidak akan tahu
   desainmu buruk sampai kamu harus mengubahnya.
6. **Tidak pernah membaca kode orang lain.** Setelah Blok 5, mulai baca kode
   sumber pustaka kecil. Percepatan terbesar yang tersedia gratis.

---

# 📚 Referensi

| Buku / Sumber | Untuk blok | Catatan |
|---|---|---|
| *Programming: Principles and Practice Using C++* — Stroustrup | 1–5 | paling ramah pemula |
| *A Tour of C++* — Stroustrup | 1–7 | ringkas, untuk gambaran cepat |
| *Effective C++* — Meyers | 2–7 | wajib setelah Blok 3 |
| *Effective Modern C++* — Meyers | 3, 6 | move semantics & template |
| [learncpp.com](https://www.learncpp.com/) | 1–7 | tutorial gratis paling lengkap |
| [cppreference.com](https://en.cppreference.com/) | semua | rujukan, bukan tutorial |
| *Head First Design Patterns* | 10–11 | contohnya Java, konsepnya sama |
| [refactoring.guru](https://refactoring.guru/design-patterns) | 10–11 | penjelasan pattern paling jelas |
| *Refactoring* — Fowler | 12 | katalog code smell |
