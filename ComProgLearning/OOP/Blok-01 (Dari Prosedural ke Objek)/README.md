# Blok 1 — Dari Prosedural ke Objek

> **Ide satu kalimat:** OOP bukan tentang "membuat class", tapi tentang membuat
> objek yang **tidak bisa berada dalam keadaan salah**.

**Estimasi:** 4–6 jam teori · 3–4 jam latihan · 2–3 jam proyek
**Prasyarat:** C++ dasar — fungsi, `struct`, pointer, referensi, `vector`

---

## Setelah Blok Ini Kamu Bisa

- Menjelaskan **masalah apa** yang dipecahkan OOP, bukan sekadar menyebut empat pilar
- Menulis class yang siklus hidupnya benar — lahir bersih, mati bersih
- Menjelaskan urutan inisialisasi yang **sebenarnya**, bukan yang kamu kira
- Memakai `const` dengan benar, dan tahu kenapa itu bukan formalitas
- Menilai kapan sesuatu **tidak** perlu jadi class

---

## Struktur Folder

```
Blok-01 (Dari Prosedural ke Objek)/
├── README.md                       ← kamu di sini
├── teori/Teori_Blok_1.md           6 bagian, ~1 jam baca
├── latihan/latihan_1.cpp .. latihan_7.cpp
├── solusi/solusi_1.cpp .. solusi_7.cpp
└── proyek/
    ├── SPESIFIKASI.md              baca sebelum mulai
    ├── starter/pecahan.cpp         kerangka + program uji
    └── referensi/                  🔒 jangan dibuka sebelum versimu jalan
```

---

## Urutan Pengerjaan

### Langkah 1 — Teori bagian 1 (30 menit)

`teori/Teori_Blok_1.md` bagian 1: **Masalah yang Dipecahkan OOP**.

Bagian ini sengaja **tidak** dimulai dari definisi empat pilar, melainkan dari
kode prosedural yang rusak. Alasannya: "enkapsulasi adalah menyembunyikan data"
itu hafalan yang tidak menuntun apa-apa. Yang menuntun adalah melihat kode yang
bocor, lalu paham kenapa `private` menutupnya.

Bagian 1.7 juga penting dan jarang diajarkan: **kapan OOP bukan jawabannya.**

### Langkah 2 — Teori bagian 2–3 + Latihan 1 (45 menit)

Access specifier, member function, `this`.

Latihan 1 mengubah kode prosedural menjadi class. Perhatikan satu hal saat
mengerjakannya: **jumlah parameter berkurang satu di semua fungsi.** Itu bukan
kebetulan — itu inti perubahan dari prosedural ke objek, dan `this` adalah
parameter yang hilang itu.

Latihan 1 juga punya pertanyaan jujur: kenapa `private` untuk `Titik2D` padahal
tidak ada invariant? Jawaban yang benar mungkin "tidak terlalu berguna", dan itu
memang jawabannya. Baca bagian itu di solusinya.

### Langkah 3 — Teori bagian 4 + Latihan 2 & 3 (60 menit)

Constructor & destructor.

| Latihan | Fokus |
|---|---|
| 2 — `Waktu` | constructor menjaga invariant lewat **satu** fungsi normalisasi |
| 3 — Tebak keluaran | urutan lahir dan mati |

Latihan 3 **wajib dikerjakan sebelum dijalankan.** Tulis tebakanmu di file dulu.
Ini melatih hal yang tidak bisa dilatih dengan menulis kode: memprediksi kapan
objek lahir dan mati. Kemampuan itu yang membuat RAII di Blok 2 terasa masuk akal.

### Langkah 4 — Teori bagian 5 + Latihan 4 (45 menit)

Member initializer list.

Latihan 4 punya tiga bug yang berbeda jenis: satu lolos kompilasi tapi hasilnya
salah, dua lagi gagal kompilasi. **Compile dengan `-Wall`** — peringatan
`-Wreorder` di Bagian A adalah petunjuknya, dan itu peringatan yang tidak boleh
kamu abaikan seumur hidup menulis C++.

Pola yang menyatukan ketiganya: **badan constructor sudah terlambat.** Saat
kurung kurawal pembuka dijalankan, semua anggota sudah terlanjur diinisialisasi.

### Langkah 5 — Teori bagian 6 + Latihan 5 & 6 (45 menit)

`const` correctness dan `explicit`.

Latihan 6 punya **eksperimen wajib**: hapus `explicit`, hidupkan `cetakSuhu(25)`,
kompilasi, lalu kembalikan. Rasakan sendiri bahwa kompilator diam saja saat
menebak `25` itu Celsius. Membaca penjelasan tentang `explicit` tidak seefektif
melihatnya gagal diam-diam.

### Langkah 6 — Latihan 7 (35 menit)

Gabungan seluruh blok. Class `Persediaan` dengan empat invariant nyata.

Tiga pertanyaan desain di akhir file **lebih penting daripada kodenya**.
Khususnya nomor 3: kenapa class ini tidak punya `setStok(int)`? Jawabannya
mengubah cara pandang terhadap enkapsulasi.

### Langkah 7 — Proyek: Class `Pecahan` (2–3 jam)

Baca `proyek/SPESIFIKASI.md`, kerjakan di `proyek/starter/pecahan.cpp`.

Pecahan dipilih karena ia contoh terkecil yang punya **invariant sungguhan** —
tidak seperti `Titik2D` yang sebenarnya tidak butuh enkapsulasi.

**Jangan lewati Bagian 4 (Perubahan Requirement).** Di CP ada judge yang bilang
solusimu benar. Di OOP tidak ada yang bisa bilang "desainmu buruk" — jadi umpan
baliknya datang dari mengubah requirement setelah selesai. Perubahan A punya
jawaban numerik yang mengukur desainmu: berapa baris di **luar** kelas yang
harus berubah saat `int` diganti `long long`? Jawaban yang benar nol.

---

## Cara Menjalankan

```bash
cd "OOP/Blok-01 (Dari Prosedural ke Objek)"

# latihan
g++ -std=c++17 -Wall -Wextra -o out latihan/latihan_1.cpp && ./out

# proyek
g++ -std=c++17 -Wall -Wextra -o pecahan proyek/starter/pecahan.cpp && ./pecahan
```

`-Wall -Wextra` bukan opsional di blok ini. Latihan 4 secara khusus mengandalkan
peringatan kompilator sebagai bagian dari pelajarannya.

---

## Kartu Ingatan

```cpp
class Nama {
public:                              // apa yang bisa dilakukan — di ATAS
    Nama() = default;                // minta constructor default kembali
    explicit Nama(int v);            // explicit untuk satu parameter
    Nama(int a, int b);
    ~Nama();                         // otomatis, urutan terbalik

    int  ambil() const;              // const = janji tidak mengubah
    void ubah(int v);                // tanpa const = memang mengubah

private:                             // bagaimana isinya disimpan — di BAWAH
    int a_ = 0;                      // inisialisasi default di tempat
    int b_ = 1;
};

int Nama::ambil() const { return a_; }          // jangan lupa Nama:: dan const

Nama::Nama(int a, int b) : a_(a), b_(b) {}      // urutan HARUS sama dengan
                                                 // urutan DEKLARASI
```

---

## Kesalahan Umum

| # | Kesalahan | Gejala | Perbaikan |
|---|---|---|---|
| 1 | Lupa `const` pada member function | error saat objek dilewatkan `const&` | beri `const` pada semua yang tidak mengubah |
| 2 | Initializer list tidak urut | nilai sampah, peringatan `-Wreorder` | samakan dengan urutan deklarasi |
| 3 | Menugaskan di badan constructor | boros; error untuk `const`/referensi | pakai initializer list |
| 4 | Menulis constructor lalu `A a;` error | "no matching constructor" | tambah `A() = default;` |
| 5 | Constructor 1 parameter tanpa `explicit` | konversi diam-diam | beri `explicit` |
| 6 | Semua anggota `public` | tidak ada invariant terjaga | mulai dari `private` |
| 7 | Getter + setter untuk semua anggota | sama saja `public`, cuma lebih panjang | dibahas Blok 2 |
| 8 | Lupa `NamaKelas::` saat definisi di luar | "was not declared in this scope" | tambahkan prefiksnya |

---

## Checklist Lulus Blok 1

Blok ini selesai kalau **semuanya** tercentang — bukan kalau materinya sudah dibaca.

- [ ] Bisa menyebutkan tiga masalah kode prosedural beserta nama resminya
      (invariant tidak dijaga · coupling tinggi · abstraksi bocor)
- [ ] Bisa menjelaskan kenapa `Pecahan b;` gagal setelah `Pecahan(int,int)` ditulis
- [ ] Bisa menjelaskan kenapa `: b_(a_ * 2)` berbahaya kalau `b_` dideklarasikan duluan
- [ ] Bisa menyebutkan tiga hal yang **hanya** bisa lewat initializer list
- [ ] Bisa menjelaskan kenapa `explicit` ada, dari pengalaman eksperimen Latihan 6
- [ ] Bisa menyebutkan satu contoh di mana class **tidak** diperlukan
- [ ] Latihan 1–7 selesai, semuanya kompilasi bersih dengan `-Wall -Wextra`
- [ ] Proyek `Pecahan` jalan dan keluarannya cocok persis
- [ ] Perubahan Requirement A, B, C dikerjakan; D dijawab tertulis
- [ ] Tahu **angka** dari Perubahan A: berapa baris di luar kelas yang berubah

Kalau ada yang belum tercentang, ulangi bagian teorinya **sambil mengerjakan
latihannya lagi** — bukan dengan membaca ulang. Membaca ulang memberi rasa paham
tanpa kemampuannya.

---

## Preview Blok 2 — Enkapsulasi & Sumber Daya

Blok 1 mengajarkan **cara membuat** objek yang lahir dan mati dengan benar.
Blok 2 menanyakan pertanyaan yang lebih tajam: **apa sebenarnya yang dijaga**
oleh enkapsulasi, dan kenapa getter/setter untuk semua anggota justru merusaknya.

Di sana juga ada RAII — konsekuensi langsung dari destructor otomatis yang kamu
lihat di Latihan 3, dan alasan kenapa C++ tidak butuh garbage collector.

Proyeknya `MyString` dengan manajemen memori manual. Itu kelas yang **akan**
rusak parah kalau disalin — dan kerusakan itulah yang membuka Blok 3.
