# Latihan Soal 01 — HTML Dasar

Kerjakan tanpa membuka `5-kunci-jawaban-latihan/`. Tulis alasan singkat untuk
setiap pilihan ganda. Materi: [`../../0-materi/01-html-dasar/teori.md`](../../0-materi/01-html-dasar/teori.md).

---

## A. Soal konsep (10)

### A1. Pilihan ganda — tag vs elemen vs atribut

Perhatikan cuplikan:

```html
<a href="https://kampus.ac.id">Situs Kampus</a>
```

Mana pernyataan yang **benar**?

- a. `<a>` adalah elemen, `href` adalah tag, `Situs Kampus` adalah atribut.
- b. `<a>` dan `</a>` adalah tag; keseluruhan (pembuka + isi + penutup) adalah elemen; `href` adalah atribut.
- c. `href="https://kampus.ac.id"` adalah elemen; `<a>` adalah atribut.
- d. Tag dan elemen adalah istilah yang sama; atribut hanya ada di CSS.

### A2. Pilihan ganda — elemen void

Manakah yang **semua** anggotanya elemen void (tanpa tag penutup)?

- a. `<img>`, `<br>`, `<p>`, `<input>`
- b. `<img>`, `<br>`, `<hr>`, `<input>`, `<meta>`, `<link>`
- c. `<div>`, `<span>`, `<img>`
- d. `<ul>`, `<li>`, `<br>`

### A3. Esai — HTML semantik

Seorang mahasiswa membungkus seluruh halaman dengan `<div>`: header, menu,
konten utama, dan kaki halaman. Jelaskan **dua** alasan konkret mengapa
mengganti ke `<header>`, `<nav>`, `<main>`, `<footer>` lebih baik. Sebutkan
juga berapa kali `<main>` boleh muncul per halaman.

### A4. Prediksi render / path — gambar relatif

Struktur folder:

```text
proyek/
├── index.html
└── aset/
    └── foto/
        └── nim.jpg
```

Di `index.html` mahasiswa menulis:

```html
<img src="foto/nim.jpg" alt="Foto mahasiswa">
```

Apa yang terjadi saat halaman dibuka? Tulis path `src` yang **benar**.
Jelaskan mengapa path dihitung dari lokasi file HTML, bukan dari folder
kerja VS Code.

### A5. Pilihan ganda — label formulir

```html
<label>Email</label>
<input id="email" name="email" type="email">
```

Mengapa ini **belum** aksesibel, dan perbaikan yang tepat?

- a. Sudah benar karena ada `id` dan `name`.
- b. Placeholder wajib ditambahkan; `label` boleh dihapus.
- c. `label` harus terhubung lewat `for="email"` (sama dengan `id` input), atau input dibungkus di dalam `label`.
- d. Ganti `<label>` menjadi `<p>` agar lebih semantik.

### A6. Esai — `alt` pada gambar

Kapan `alt` wajib berisi deskripsi, dan kapan `alt=""` (kosong) justru
benar? Apa yang terjadi bagi pengguna screen reader jika atribut `alt`
**dihilangkan sama sekali**?

### A7. Prediksi — nesting

Apa yang salah pada markup ini, dan bagaimana browser + screen reader
bisa "tersesat"? Tulis versi yang benar.

```html
<p>Batas waktu <strong>hari Jumat</p></strong>
```

### A8. Pilihan ganda — tabel

Untuk tabel nilai mahasiswa, sel judul kolom "NIM" sebaiknya memakai…

- a. `<td>` di dalam `<tbody>`, karena semua sel sama saja.
- b. `<th scope="col">` di dalam `<thead>`.
- c. `<h3>` di dalam `<td>` agar lebih besar.
- d. `<div class="judul">` di dalam `<table>`.

### A9. Esai — heading

Mengapa satu halaman cukup **satu** `<h1>`, dan mengapa loncat dari
`<h1>` ke `<h3>` (tanpa `<h2>`) bermasalah? Kaitkan dengan outline dokumen.

### A10. Prediksi tautan

```html
<a href="https://developer.mozilla.org" target="_blank">MDN</a>
```

Apa perilaku saat diklik? Atribut apa yang **kurang** untuk keamanan, dan
mengapa `rel="noopener"` dibutuhkan?

---

## B. Soal praktik kecil (3)

Kerjakan di file baru (jangan menimpa `1-pembelajaran/`).

### B1. Kerangka semantik

Buat `profil.html` kerangka HTML5 (`<!DOCTYPE>`, `lang="id"`, charset,
viewport, title). Di `body`: `<header>` berisi `<h1>` nama lengkap,
`<main>` berisi satu `<section>` "Tentang", `<footer>` berisi teks hak
cipta. Tidak boleh memakai `<div>` untuk keempat bagian itu.

### B2. Gambar relatif + figure

Anggap file HTML di `halaman/index.html` dan gambar di
`halaman/img/kampus.jpg`. Tulis elemen `<figure>` berisi `<img>` dengan
path relatif yang benar, `alt` bermakna, plus `<figcaption>`.

### B3. Formulir ber-label

Tulis `<form method="post">` dengan tiga kontrol: nama (teks, `required`),
email (`type="email"`), dan pesan (`textarea`). Setiap kontrol punya
`<label>` yang terhubung lewat `for`/`id`. Tombol `type="submit"`.
Placeholder boleh ada, **bukan** pengganti label.
