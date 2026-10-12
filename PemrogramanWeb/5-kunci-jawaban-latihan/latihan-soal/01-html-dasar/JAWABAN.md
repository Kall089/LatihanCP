# Jawaban 01 — HTML Dasar

Bukan hanya huruf benar: tiap butir menjelaskan **mengapa**.

---

## A. Konsep

### A1 — b

**Tag** adalah penanda (`<a>`, `</a>`). **Elemen** adalah unit utuh: tag
pembuka + konten + tag penutup. **Atribut** adalah pasangan `nama="nilai"`
pada tag pembuka (`href`). Menyamakan tag dengan elemen adalah jebakan ujian
klasik.

### A2 — b

Elemen void tidak punya isi dan tidak ditutup: `img`, `br`, `hr`, `input`,
`meta`, `link`. `<p>` dan `<div>` punya penutup; `<ul>`/`<li>` juga.

### A3

Dua alasan (salah satu pasangan ini):

1. **Aksesibilitas** — screen reader punya perintah "lompat ke main/nav";
   semua-div mematikan landmark itu.
2. **SEO / keterbacaan kode** — mesin pencari menimbang `<main>`/`<article>`;
   manusia membaca `</footer>` lebih mudah daripada `</div>` ke-37.

`<main>` **satu kali** per halaman.

### A4

Gambar **gagal dimuat** (404). Path dihitung dari lokasi `index.html`, jadi
yang benar `aset/foto/nim.jpg`. Folder kerja editor tidak mempengaruhi URL
relatif di browser.

### A5 — c

Hubungan `label for` = `input id` (atau bungkus input di dalam label) membuat
klik teks memfokuskan kontrol dan screen reader mengumumkan tujuan. `id`
sendiri tidak menghubungkan. Placeholder bukan pengganti label.

### A6

`alt` deskriptif untuk gambar yang menyampaikan informasi. `alt=""` untuk
gambar murni dekoratif (atribut tetap ada). Jika atribut **dihilangkan**,
AT sering membacakan nama file — berisik dan tidak bermakna.

### A7

Tag menyilang: `<strong>` ditutup setelah `</p>`. Nesting harus LIFO
(terakhir dibuka, pertama ditutup). Benar:

```html
<p>Batas waktu <strong>hari Jumat</strong></p>
```

Browser mencoba "memperbaiki" tree, outline jadi kacau.

### A8 — b

Sel judul kolom = `<th scope="col">` di `<thead>`. `<td>` adalah sel data.
Heading HTML tidak menggantikan `th`; `div` di dalam `table` tidak valid
sebagai model tabel.

### A9

`<h1>` = judul utama dokumen (outline). Lebih dari satu membingungkan
hierarki. Loncat `h1`→`h3` membuat level 2 hilang; pengguna AT yang navigasi
per heading kehilangan tingkatan. Turun satu level setiap kali.

### A10

Klik membuka MDN di **tab baru**. Kurang `rel="noopener"` (sebaiknya plus
`noreferrer`). Tanpa `noopener`, halaman tujuan mendapat `window.opener` ke
halamanmu (*reverse tabnabbing*).

---

## B. Praktik

### B1

```html
<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Profil — Sinta Ramadhani</title>
</head>
<body>
  <header>
    <h1>Sinta Ramadhani</h1>
  </header>
  <main>
    <section>
      <h2>Tentang</h2>
      <p>Mahasiswa Teknik Informatika yang sedang belajar pemrograman web.</p>
    </section>
  </main>
  <footer>
    <p>© 2026 Sinta Ramadhani</p>
  </footer>
</body>
</html>
```

### B2

```html
<figure>
  <img src="img/kampus.jpg" alt="Gedung kampus tampak depan" width="800" height="450">
  <figcaption>Kampus pada pagi hari.</figcaption>
</figure>
```

`src` relatif terhadap `halaman/index.html` → `img/kampus.jpg`, bukan
`halaman/img/...` dan bukan path `/Users/...`.

### B3

```html
<form action="#" method="post">
  <p>
    <label for="nama">Nama</label>
    <input id="nama" name="nama" type="text" required>
  </p>
  <p>
    <label for="email">Email</label>
    <input id="email" name="email" type="email" required>
  </p>
  <p>
    <label for="pesan">Pesan</label>
    <textarea id="pesan" name="pesan" required></textarea>
  </p>
  <button type="submit">Kirim</button>
</form>
```

`for` harus **identik** dengan `id`. `name` diperlukan agar data ikut
terkirim jika suatu saat ada `action` server.
