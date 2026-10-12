# Cheatsheet HTML

[← Daftar panduan](README.md) · [Lanjut CSS →](css.md)

HTML adalah **kerangka dan makna** halaman. Ia tidak mengatur warna atau pergerakan. Ia mengatakan: ini judul, ini tombol, ini tautan, ini form.

## Daftar isi

- [Kerangka halaman](#kerangka-halaman)
- [Teks dan heading](#teks-dan-heading)
- [Tautan dan gambar](#tautan-dan-gambar)
- [Daftar dan tabel](#daftar-dan-tabel)
- [Semantik layout](#semantik-layout)
- [Formulir](#formulir)
- [Atribut penting](#atribut-penting)
- [Aksesibilitas singkat](#aksesibilitas-singkat)
- [Kesalahan umum](#kesalahan-umum)

## Kerangka halaman

**Untuk apa:** setiap file HTML yang dibuka browser.

```html
<!doctype html>
<html lang="id">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Jelajah Raja Ampat</title>
    <link rel="stylesheet" href="style.css" />
  </head>
  <body>
    <h1>Halo</h1>
    <script src="script.js" defer></script>
  </body>
</html>
```

- `lang="id"` membantu pembaca layar dan terjemahan.
- `charset` agar huruf Indonesia tidak rusak.
- `viewport` wajib supaya CSS responsif bekerja di HP.
- CSS di `head`, JavaScript klasik di akhir `body` atau pakai `defer`.

**Biasanya digabungkan dengan:** [css.md](css.md) dan [javascript.md](javascript.md).

## Teks dan heading

**Untuk apa:** menyusun hierarki bacaan, bukan sekadar “huruf besar”.

```html
<h1>Satu per halaman</h1>
<h2>Bagian</h2>
<h3>Subbagian</h3>
<p>Paragraf biasa.</p>
<strong>Penting</strong>
<em>Penekanan</em>
<br />
<hr />
```

Jangan loncat `h1` ke `h3` hanya karena ukurannya bagus; ukuran diatur CSS. `<b>` dan `<i>` hanya tampilan; `<strong>` dan `<em>` punya makna.

**Biasanya digabungkan dengan:** CSS `font-size`, dan outline heading di tugas profil.

## Tautan dan gambar

**Untuk apa:** pindah halaman dan menampilkan gambar.

```html
<a href="#info">Lihat informasi</a>
<a href="https://contoh.test" target="_blank" rel="noreferrer">Situs luar</a>
<img src="images/ampat.png" alt="Gugusan pulau Raja Ampat" width="800" height="500" />
```

- `#info` loncat ke `id="info"` di halaman yang sama.
- `alt` menjelaskan gambar jika gagal dimuat atau untuk pembaca layar. Hiasan murni boleh `alt=""`.
- `width`/`height` membantu cadangan ruang (kurangi layout geser).

**Biasanya digabungkan dengan:** `scroll-mt-16` di CSS/Tailwind, dan `next/image` di Next.js.

## Daftar dan tabel

**Untuk apa:** urutan, daftar tidak berurut, dan data berkolom.

```html
<ul>
  <li>Sunblock</li>
  <li>Uang tunai</li>
</ul>

<ol>
  <li>Pesawat ke Sorong</li>
  <li>Kapal ke Waisai</li>
</ol>

<table>
  <thead>
    <tr><th>Item</th><th>Harga</th></tr>
  </thead>
  <tbody>
    <tr><td>Tiket kawasan</td><td>Rp 500.000</td></tr>
  </tbody>
</table>
```

Jangan memakai tabel untuk layout halaman; pakai Flexbox/Grid.

**Biasanya digabungkan dengan:** CSS tabel/kartu, atau daftar harga seperti di tugas Kunjungan.

## Semantik layout

**Untuk apa:** menandai peran wilayah, bukan hanya `div` bertumpuk.

```html
<header>Logo dan menu</header>
<nav aria-label="Utama">...</nav>
<main>
  <section id="home">...</section>
  <article>Kartu yang mandiri</article>
  <aside>Catatan samping</aside>
</main>
<footer>Kredit</footer>
```

- `main` sekali per halaman.
- `section` = bagian bertema (Home, Info).
- `article` = potongan yang masuk akal sendirian (berita, kartu produk).
- `div` = wadah tanpa makna, untuk CSS/grid.

**Biasanya digabungkan dengan:** navbar sticky, dan komponen React yang meniru tag yang sama.

## Formulir

**Untuk apa:** meminta input. Setiap input butuh `label`.

```html
<form action="/kirim" method="post">
  <label for="nama">Nama</label>
  <input id="nama" name="nama" type="text" required />

  <label for="email">Email</label>
  <input id="email" name="email" type="email" />

  <label>
    <input type="checkbox" name="setuju" value="ya" />
    Saya setuju
  </label>

  <button type="submit">Kirim</button>
  <button type="button">Batal, tidak mengirim form</button>
</form>
```

`for` pada label harus sama dengan `id` input. `name` yang dibaca server/FormData. `type="button"` tidak mensubmit.

**Biasanya digabungkan dengan:** JS `preventDefault`, React controlled input, Laravel `@csrf`.

## Atribut penting

| Atribut | Untuk apa |
|---|---|
| `id` | unik, target `#`, dihubungkan label |
| `class` | gaya berulang, selector CSS |
| `hidden` | sembunyikan (bisa diubah JS) |
| `disabled` | nonaktifkan kontrol |
| `required` | wajib diisi (validasi browser) |
| `placeholder` | contoh isian, bukan pengganti label |
| `aria-label` | nama untuk pembaca layar jika teks tidak terlihat |

**Biasanya digabungkan dengan:** CSS `.menu.terbuka` dan `classList` JavaScript.

## Aksesibilitas singkat

**Untuk apa:** halaman tetap bisa dipakai keyboard dan pembaca layar.

- Tombol aksi pakai `<button>`, bukan `<div onclick>`.
- Jangan andalkan warna saja untuk status (tambah teks “Habis”).
- Fokus harus kelihatan (`:focus-visible`).
- Gambar bermakna punya `alt` yang jujur.

**Biasanya digabungkan dengan:** CSS fokus dan event `Enter`/`Space` pada kontrol asli.

## Kesalahan umum

- **Lupa `alt` atau `label`:** tugas sering dipotong nilainya.
- **Banyak `h1`:** pilih satu judul halaman.
- **`div` untuk tombol:** tidak bisa di-Tab dengan benar.
- **CSS/JS 404:** path `href`/`src` salah relatif ke file HTML.

Latihan: buat halaman profil: `header`, satu `h1`, foto ber-`alt`, form kontak ber-`label`.

Referensi: [MDN HTML](https://developer.mozilla.org/en-US/docs/Web/HTML).
