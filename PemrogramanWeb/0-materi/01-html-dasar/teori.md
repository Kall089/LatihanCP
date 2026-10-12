# Modul 01 — HTML Dasar

> Praktikum terkait: [`../../1-pembelajaran/01-html-dasar/`](../../1-pembelajaran/01-html-dasar/)
> (5 bab: struktur dokumen, teks & daftar, tautan & gambar, tabel, formulir).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menjelaskan peran HTML dibanding CSS dan JavaScript.
- Menulis kerangka dokumen HTML5 yang valid dari nol, tanpa mencontek.
- Memilih tag yang tepat berdasarkan **makna** konten (semantik), bukan tampilannya.
- Membuat tautan, gambar, tabel, dan formulir yang benar dan aksesibel.
- Mengenali kesalahan umum yang sering muncul di ujian dan tugas.

---

## 1. Apa itu HTML, dan mengapa ia "struktur"?

HTML (*HyperText Markup Language*) adalah bahasa **markup**, bukan bahasa
pemrograman: ia tidak punya logika, perulangan, atau kondisi. Tugasnya satu —
memberi **struktur dan makna** pada konten.

Analogi rumah yang dipakai sepanjang mata kuliah ini:

| Teknologi | Peran | Analogi rumah |
|---|---|---|
| HTML | Struktur & makna konten | Rangka, tembok, ruangan |
| CSS | Tampilan | Cat, dekorasi, tata letak perabot |
| JavaScript | Perilaku | Instalasi listrik, saklar, sensor |

**Mengapa dipisah?** Prinsip *separation of concerns*: setiap file punya satu
tanggung jawab. Kalau ingin mengubah warna tombol, kamu cukup menyentuh CSS
tanpa risiko merusak konten. Praktikum `1-pembelajaran/` selalu memisahkan
`index.html`, `style.css`, dan `script.js` karena alasan ini.

Browser membaca file HTML dari atas ke bawah, membangun **DOM** (pohon objek
dokumen — dibahas dalam Modul 05), lalu menggambarnya ke layar.

---

## 2. Anatomi elemen

```text
   tag pembuka           isi (konten)         tag penutup
  ┌───────────┐   ┌─────────────────────┐   ┌────┐
  <a href="https://kampus.ac.id">Situs Kampus</a>
     └──────────────┬───────────┘
        atribut = nama="nilai"
```

Istilah yang wajib dibedakan (sering keluar di ujian):

- **Elemen**: keseluruhan unit — tag pembuka + isi + tag penutup.
- **Tag**: penandanya saja, misal `<p>` atau `</p>`.
- **Atribut**: informasi tambahan pada tag pembuka, format `nama="nilai"`.
- **Elemen void**: tidak punya isi dan tidak punya tag penutup:
  `<img>`, `<br>`, `<hr>`, `<input>`, `<meta>`, `<link>`.

Aturan **nesting** (bersarang): elemen harus ditutup dalam urutan terbalik dari
pembukaannya.

```html
<!-- BENAR -->
<p>Ini <strong>penting</strong> sekali.</p>

<!-- SALAH: tag menyilang -->
<p>Ini <strong>penting</p></strong>
```

---

## 3. Kerangka dokumen HTML5

Setiap file `.html` mengikuti kerangka yang sama. Hafalkan — ini soal ujian
klasik dan baris pertama setiap praktikum.

```html
<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Judul di Tab Browser</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <h1>Halo Dunia</h1>
  <p>Semua yang tampil di layar ada di dalam body.</p>
  <script src="script.js"></script>
</body>
</html>
```

Fungsi tiap bagian — dan **mengapa** ia ada:

| Baris | Fungsi | Mengapa penting |
|---|---|---|
| `<!DOCTYPE html>` | Deklarasi HTML5 | Tanpa ini browser masuk *quirks mode* — rendering lawas yang tidak konsisten |
| `<html lang="id">` | Akar dokumen + bahasa | Screen reader memilih pengucapan; mesin pencari tahu bahasa konten |
| `<head>` | Metadata (TIDAK tampil) | Tempat charset, judul tab, link CSS, meta SEO |
| `<meta charset="UTF-8">` | Encoding karakter | Tanpa ini huruf non-latin bisa jadi `Ã©` |
| `<meta name="viewport">` | Lebar layar = lebar perangkat | **Wajib** agar media query (Modul 03) bekerja di HP |
| `<title>` | Judul tab & hasil pencarian | Elemen SEO paling dasar |
| `<body>` | Semua konten yang tampil | Satu-satunya bagian yang digambar |
| `<script>` di akhir body | Muat JS | Elemen sudah ter-parse saat JS jalan (lihat Modul 05) |

---

## 4. Teks: heading, paragraf, penekanan

### Heading = outline dokumen

`<h1>`–`<h6>` bukan sekadar "teks besar". Mereka membentuk **kerangka
dokumen** yang dipakai screen reader (pengguna bisa lompat antar-heading) dan
mesin pencari.

Aturan praktis:

1. Satu `<h1>` per halaman — judul utama.
2. Jangan loncat level: `h1 → h2 → h3`, bukan `h1 → h3`.
3. Jangan memilih heading karena ukurannya — ukuran diatur CSS.

```html
<h1>Warung Kopi Senja</h1>
  <h2>Menu Andalan</h2>
    <h3>Kopi Susu Gula Aren</h3>
  <h2>Lokasi</h2>
```

### Penekanan bermakna vs murni visual

- `<strong>` = penting (dibaca dengan penekanan oleh screen reader).
- `<em>` = penekanan intonasi.
- `<b>` dan `<i>` = murni visual, tanpa makna — hindari bila ada makna.

### Daftar

```html
<ul>              <!-- unordered: urutan tidak penting -->
  <li>Kopi</li>
  <li>Teh</li>
</ul>

<ol>              <!-- ordered: urutan penting (langkah, ranking) -->
  <li>Panaskan air</li>
  <li>Seduh kopi</li>
</ol>
```

`<li>` hanya boleh menjadi anak langsung `<ul>`/`<ol>`. Daftar boleh
bersarang: taruh `<ul>` **di dalam** sebuah `<li>`.

---

## 5. Tautan dan gambar

### Tautan `<a>`

```html
<!-- Absolut: keluar situs; buka tab baru dengan aman -->
<a href="https://developer.mozilla.org" target="_blank" rel="noopener">MDN</a>

<!-- Relatif: antar-file dalam proyek -->
<a href="tentang.html">Tentang</a>
<a href="../index.html">Kembali ke beranda</a>

<!-- Anchor: lompat ke elemen ber-id pada halaman yang sama -->
<a href="#kontak">Hubungi kami</a>
...
<section id="kontak">...</section>

<!-- Protokol khusus -->
<a href="mailto:halo@kampus.ac.id">Email</a>
<a href="tel:+628123456789">Telepon</a>
```

**Mengapa `rel="noopener"` saat `target="_blank"`?** Tanpanya, halaman tujuan
mendapat referensi `window.opener` ke halamanmu — celah keamanan (*reverse
tabnabbing*).

### Gambar `<img>`

```html
<img src="img/logo.png" alt="Logo Warung Kopi Senja" width="200" height="80">
```

- `src`: lokasi file (relatif atau absolut).
- `alt`: **wajib**. Dibaca screen reader, tampil saat gambar gagal dimuat,
  dan diindeks mesin pencari. Untuk gambar murni dekoratif, tulis `alt=""`
  (atribut tetap ada, nilainya kosong).
- `width`/`height`: mencegah *layout shift* — browser tahu ukuran sebelum
  gambar termuat.

---

## 6. Tabel — hanya untuk data tabular

**Mengapa bukan untuk layout?** Dulu (era 90-an) tabel dipakai menyusun
halaman. Sekarang itu tugas flexbox/grid (Modul 03); tabel layout merusak
aksesibilitas dan responsivitas.

```html
<table>
  <caption>Nilai Praktikum Kelas A</caption>
  <thead>
    <tr>
      <th scope="col">Nama</th>
      <th scope="col">Modul</th>
      <th scope="col">Nilai</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Sinta</td>
      <td>HTML Dasar</td>
      <td>92</td>
    </tr>
    <tr>
      <td>Andi</td>
      <td>HTML Dasar</td>
      <td>85</td>
    </tr>
  </tbody>
</table>
```

Struktur yang benar (perhatikan hierarkinya):

```text
table
├── caption          (judul tabel — opsional tapi disarankan)
├── thead
│   └── tr           (baris)
│       └── th ...   (sel JUDUL, default tebal + scope)
└── tbody
    └── tr
        └── td ...   (sel DATA)
```

- `scope="col"` / `scope="row"` memberi tahu screen reader arah judul.
- `colspan="2"` menggabungkan sel ke samping; `rowspan="2"` ke bawah.
- Hasil render default: tabel polos tanpa garis — garis/warna diatur CSS
  (`border-collapse: collapse` adalah pasangan setianya).

---

## 7. Formulir — pintu masuk data pengguna

Formulir adalah topik bab terakhir praktikum
(`1-pembelajaran/01-html-dasar/05-formulir`) dan fondasi validasi JavaScript
di Modul 05.

```html
<form action="/daftar" method="post">
  <label for="nama">Nama lengkap</label>
  <input id="nama" name="nama" type="text" required>

  <label for="email">Email kampus</label>
  <input id="email" name="email" type="email" required>

  <label for="prodi">Program studi</label>
  <select id="prodi" name="prodi">
    <option value="ti">Teknik Informatika</option>
    <option value="si">Sistem Informasi</option>
  </select>

  <fieldset>
    <legend>Jalur pendaftaran</legend>
    <label><input type="radio" name="jalur" value="reguler" checked> Reguler</label>
    <label><input type="radio" name="jalur" value="transfer"> Transfer</label>
  </fieldset>

  <label>
    <input type="checkbox" name="setuju" required>
    Saya menyetujui ketentuan
  </label>

  <button type="submit">Kirim</button>
</form>
```

Konsep kunci:

1. **`label` terhubung ke `input`** lewat `for` = `id` (atau dengan
   membungkus input di dalam label). Mengapa: klik label memfokuskan input,
   dan screen reader membacakan tujuannya. *Placeholder bukan pengganti
   label* — ia hilang saat mulai mengetik.
2. **`name`** = kunci data saat dikirim (`nama=Sinta&email=...`). Input tanpa
   `name` tidak ikut terkirim.
3. **`type`** menentukan keyboard di HP dan validasi bawaan:
   `text`, `email`, `password`, `number`, `date`, `checkbox`, `radio`,
   `file`, `range`, `color`.
4. **Validasi tanpa JavaScript**: `required`, `min`, `max`, `minlength`,
   `maxlength`, `pattern`. Browser menolak submit dan menampilkan pesan.
5. `radio` dengan `name` sama = satu grup, hanya satu terpilih.
6. `method="get"` menaruh data di URL (pencarian); `method="post"`
   mengirim di body (data sensitif/mengubah server).

---

## 8. HTML Semantik — tag yang bercerita

`<div>` dan `<span>` adalah wadah **tanpa makna**. HTML5 menyediakan tag
yang menjelaskan *peran* bagian halaman:

```text
┌──────────────────────────────────────────────┐
│ <header>   logo + judul situs                │
│   <nav>    menu navigasi utama               │
├──────────────────────────────────────────────┤
│ <main>     konten utama (SATU per halaman)   │
│  ┌────────────────────────┐ ┌─────────────┐  │
│  │ <section>              │ │ <aside>     │  │
│  │   <article>            │ │  konten     │  │
│  │   unit konten mandiri  │ │  samping    │  │
│  │   <article> ...        │ │             │  │
│  └────────────────────────┘ └─────────────┘  │
├──────────────────────────────────────────────┤
│ <footer>   kontak, hak cipta                 │
└──────────────────────────────────────────────┘
```

| Tag | Makna | Contoh isi |
|---|---|---|
| `<header>` | Kepala halaman/bagian | Logo, judul, tagline |
| `<nav>` | Kumpulan tautan navigasi | Menu utama |
| `<main>` | Konten utama, **satu per halaman** | Seluruh isi inti |
| `<section>` | Bagian tematik ber-heading | "Menu", "Testimoni" |
| `<article>` | Konten utuh yang mandiri | Post blog, kartu produk |
| `<aside>` | Konten sampingan | Sidebar, info terkait |
| `<footer>` | Kaki halaman/bagian | Kontak, copyright |
| `<figure>` + `<figcaption>` | Media + keterangannya | Grafik + caption |

**Mengapa repot-repot?**

1. **Aksesibilitas**: screen reader punya perintah "lompat ke main/nav".
   Dengan div semua, fitur itu mati.
2. **SEO**: mesin pencari menimbang konten `<main>` dan `<article>` lebih
   tinggi.
3. **Keterbacaan kode**: `</footer>` jelas; `</div>` ke-37 tidak.

Kapan `<div>` boleh? Saat butuh wadah murni untuk keperluan styling/layout
dan tidak ada tag semantik yang cocok. Semantik dulu, div belakangan.

---

## 9. Kesalahan umum (dan cara menghindarinya)

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | Lupa tag penutup | Layout rusak "misterius" | Indentasi rapi; validasi di validator.w3.org |
| 2 | Heading loncat level (`h1`→`h3`) | Outline kacau bagi screen reader | Turun satu level tiap kali |
| 3 | `<img>` tanpa `alt` | Tak aksesibel; jelek saat gagal muat | Selalu isi `alt` (boleh `alt=""` untuk dekorasi) |
| 4 | `<br><br>` untuk jarak | Jarak tak konsisten, tak responsif | Jarak = `margin` di CSS |
| 5 | Placeholder sebagai label | Hilang saat mengetik; tak dibaca AT | `<label for>` selalu ada |
| 6 | Tabel untuk layout | Tidak responsif, tidak aksesibel | Flexbox/grid (Modul 03) |
| 7 | `div` untuk segalanya | Kode sulit dirawat | Tag semantik dulu |
| 8 | Atribut tanpa kutip / typo `scr=` | Kadang jalan, kadang tidak | Selalu `nama="nilai"`; teliti |

---

## 10. Cheatsheet

```html
<!-- KERANGKA -->
<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Judul</title>
</head>
<body> ... </body>
</html>

<!-- TEKS -->
<h1>–<h6>  <p>  <strong>  <em>  <blockquote>  <code>  <pre>

<!-- DAFTAR -->
<ul><li>...</li></ul>      <ol><li>...</li></ol>

<!-- TAUTAN & GAMBAR -->
<a href="url" target="_blank" rel="noopener">teks</a>
<a href="#id">anchor</a>
<img src="x.jpg" alt="deskripsi" width="..." height="...">

<!-- TABEL -->
<table><caption>..</caption>
  <thead><tr><th scope="col">..</th></tr></thead>
  <tbody><tr><td>..</td></tr></tbody>
</table>

<!-- FORM -->
<form action="..." method="post">
  <label for="x">Label</label>
  <input id="x" name="x" type="email" required>
  <select><option value="v">Teks</option></select>
  <textarea name="pesan"></textarea>
  <button type="submit">Kirim</button>
</form>

<!-- SEMANTIK -->
<header> <nav> <main> <section> <article> <aside> <footer>
```

## Lanjut ke praktikum

Kerjakan berurutan di [`../../1-pembelajaran/01-html-dasar/`](../../1-pembelajaran/01-html-dasar/):

1. `01-struktur-dokumen` — kerangka dokumen (bagian 3 materi ini).
2. `02-teks-dan-daftar` — heading, paragraf, list (bagian 4).
3. `03-tautan-dan-gambar` — href, alt (bagian 5).
4. `04-tabel` — thead/tbody/th/td (bagian 6).
5. `05-formulir` — label, input, validasi bawaan (bagian 7).

Setelah selesai, uji diri dengan [`../../3-latihan-soal/01-html-dasar/soal.md`](../../3-latihan-soal/01-html-dasar/soal.md).
