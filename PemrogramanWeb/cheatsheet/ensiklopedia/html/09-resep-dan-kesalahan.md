# 09 · Resep dan kesalahan

[← Aksesibilitas](08-aksesibilitas-aria.md) · [Daftar](README.md)

**Untuk apa file ini:** menyalin pola yang sering diminta di praktikum, plus daftar kesalahan yang paling sering memotong nilai. Setiap resep adalah kerangka. Ganti teks, path, dan data.

## Daftar isi

- [Resep 1 · Halaman profil / landing pendek](#resep-1--halaman-profil--landing-pendek)
- [Resep 2 · Navbar + skip link + target sticky](#resep-2--navbar--skip-link--target-sticky)
- [Resep 3 · Kartu produk / paket](#resep-3--kartu-produk--paket)
- [Resep 4 · Form kontak yang lolos penilaian](#resep-4--form-kontak-yang-lolos-penilaian)
- [Resep 5 · Form pemesanan ber-fieldset](#resep-5--form-pemesanan-ber-fieldset)
- [Resep 6 · Tabel harga yang bisa di-scroll](#resep-6--tabel-harga-yang-bisa-di-scroll)
- [Resep 7 · Galeri gambar ber-figure](#resep-7--galeri-gambar-ber-figure)
- [Resep 8 · FAQ dengan `details` atau accordion](#resep-8--faq-dengan-details-atau-accordion)
- [Resep 9 · Hero + gambar cadangan rasio](#resep-9--hero--gambar-cadangan-rasio)
- [Resep 10 · Embed peta / video aman](#resep-10--embed-peta--video-aman)
- [Resep 11 · Pesan sukses dan error di form JS](#resep-11--pesan-sukses-dan-error-di-form-js)
- [Resep 12 · Kerangka Blade / React yang setara](#resep-12--kerangka-blade--react-yang-setara)
- [Daftar kesalahan HTML yang memotong nilai](#daftar-kesalahan-html-yang-memotong-nilai)
- [Cara men-debug “tidak kelihatan / tidak jalan”](#cara-men-debug-tidak-kelihatan--tidak-jalan)
- [Checklist sebelum kumpul](#checklist-sebelum-kumpul)

## Resep 1 · Halaman profil / landing pendek

**Untuk apa:** tugas “kenalkan diri / destinasi / UMKM” satu file HTML.

```html
<!doctype html>
<html lang="id">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Profil — Jelajah Raja Ampat</title>
    <meta name="description" content="Profil singkat trip kecil di Raja Ampat." />
    <link rel="stylesheet" href="style.css" />
  </head>
  <body>
    <a class="skip" href="#konten-utama">Loncat ke konten</a>

    <header>
      <p class="logo">Jelajah</p>
      <nav aria-label="Utama">
        <ul>
          <li><a href="#tentang" aria-current="page">Tentang</a></li>
          <li><a href="#keahlian">Fokus</a></li>
          <li><a href="#kontak">Kontak</a></li>
        </ul>
      </nav>
    </header>

    <main id="konten-utama" tabindex="-1">
      <section id="tentang">
        <h1>Jelajah Raja Ampat</h1>
        <p>Trip kecil, kapal jujur, tanpa janji laut selalu kaca.</p>
        <figure>
          <img
            src="images/pianemo.jpg"
            alt="Gugusan karst Pianemo dari puncak kayu"
            width="1200"
            height="800"
          />
          <figcaption>Pianemo, pagi hari.</figcaption>
        </figure>
      </section>

      <section id="keahlian" aria-labelledby="judul-fokus">
        <h2 id="judul-fokus">Fokus</h2>
        <ul>
          <li>Open trip 4 hari</li>
          <li>Charter keluarga</li>
          <li>Penjelasan tiket kawasan yang terpisah</li>
        </ul>
      </section>

      <section id="kontak" aria-labelledby="judul-kontak">
        <h2 id="judul-kontak">Kontak</h2>
        <form action="#" method="post">
          <p>
            <label for="nama">Nama</label>
            <input id="nama" name="nama" type="text" autocomplete="name" required />
          </p>
          <p>
            <label for="email">Email</label>
            <input id="email" name="email" type="email" autocomplete="email" required />
          </p>
          <p>
            <label for="pesan">Pesan</label>
            <textarea id="pesan" name="pesan" rows="4" required></textarea>
          </p>
          <p>
            <button type="submit">Kirim</button>
          </p>
        </form>
      </section>
    </main>

    <footer>
      <p><small>© 2026 Jelajah. Tugas kuliah, bukan operator resmi.</small></p>
    </footer>
  </body>
</html>
```

Yang dinilai biasanya: `lang`, charset, viewport, satu `h1`, `alt`, `label`, landmark, path CSS.

**Biasanya digabungkan dengan:** CSS Flex navbar + Grid kartu, JS tidak wajib.

## Resep 2 · Navbar + skip link + target sticky

**Untuk apa:** menu yang nempel di atas tidak menutupi judul saat loncat `#id`.

```html
<a class="skip" href="#konten-utama">Loncat ke konten</a>
<header class="situs-header">
  <nav aria-label="Utama">
    <ul>
      <li><a href="#home">Beranda</a></li>
      <li><a href="#info">Info</a></li>
      <li><a href="#harga">Harga</a></li>
    </ul>
  </nav>
</header>
<main id="konten-utama" tabindex="-1">
  <section id="home"><h1>Jelajah</h1></section>
  <section id="info"><h2>Info</h2></section>
  <section id="harga"><h2>Harga</h2></section>
</main>
```

```css
.situs-header {
  position: sticky;
  top: 0;
  z-index: 10;
  background: #fff;
}

#konten-utama,
section[id] {
  scroll-margin-top: 4.5rem;
}
```

Hamburger (HP):

```html
<button
  type="button"
  class="tombol-menu"
  aria-expanded="false"
  aria-controls="menu-utama"
>
  Menu
</button>
<ul id="menu-utama" hidden>
  ...
</ul>
```

Jangan `href="#"` + jQuery `preventDefault` sebagai item menu palsu.

**Biasanya digabungkan dengan:** [css.md](../../css.md) sticky, JS `aria-expanded`, Tailwind `sticky top-0 scroll-mt-20`.

## Resep 3 · Kartu produk / paket

**Untuk apa:** katalog. Setiap kartu mandiri = `article`.

```html
<section aria-labelledby="judul-paket">
  <h2 id="judul-paket">Paket</h2>
  <div class="grid-kartu">
    <article class="kartu">
      <h3>4 hari</h3>
      <p>Sorong, Waisai, Pianemo, Arborek.</p>
      <p><s>Rp 9.800.000</s> <strong>Rp 8.500.000</strong> <span class="lencana">Diskon</span></p>
      <p><a href="paket-4-hari.html">Detail paket 4 hari</a></p>
    </article>
    <article class="kartu">
      <h3>7 hari</h3>
      <p>Termasuk Wayag dan liveaboard.</p>
      <p><strong>Rp 14.000.000</strong></p>
      <p><a href="paket-7-hari.html">Detail paket 7 hari</a></p>
    </article>
  </div>
</section>
```

Tautan “Detail” harus unik. Jangan tiga tautan “Klik di sini”.

Jika seluruh kartu bisa diklik, pola yang lebih aman: tautan di judul, atau satu tautan teregang CSS (`::after` absolut) — tetap satu `<a>`, bukan `<article onclick>`.

**Biasanya digabungkan dengan:** CSS Grid, React `map`, Laravel `@foreach($pakets as $paket)`.

## Resep 4 · Form kontak yang lolos penilaian

**Untuk apa:** checklist dosen: label, name, type yang benar, tombol submit.

```html
<form action="https://httpbin.org/post" method="post">
  <p>
    <label for="nama">Nama</label>
    <input id="nama" name="nama" type="text" autocomplete="name" required maxlength="80" />
  </p>
  <p>
    <label for="email">Email</label>
    <input id="email" name="email" type="email" autocomplete="email" required />
  </p>
  <p>
    <label for="topik">Topik</label>
    <select id="topik" name="topik" required>
      <option value="" disabled selected>Pilih topik</option>
      <option value="kuota">Cek kuota</option>
      <option value="charter">Charter</option>
      <option value="lain">Lainnya</option>
    </select>
  </p>
  <p>
    <label for="pesan">Pesan</label>
    <textarea id="pesan" name="pesan" rows="5" required minlength="10"></textarea>
  </p>
  <p>
    <label>
      <input type="checkbox" name="setuju" value="ya" required />
      Saya setuju dihubungi lewat email
    </label>
  </p>
  <p>
    <button type="submit">Kirim</button>
    <button type="button" id="batal">Batal</button>
  </p>
</form>
```

`action="#"` boleh untuk statis. Jangan lupa: tombol batal `type="button"`.

**Biasanya digabungkan dengan:** Laravel `@csrf` jika POST ke aplikasimu, JS `preventDefault` jika tidak ada server.

## Resep 5 · Form pemesanan ber-fieldset

**Untuk apa:** radio/checkbox yang punya judul kelompok.

```html
<form action="/pesan" method="post">
  <fieldset>
    <legend>Data pemesan</legend>
    <p>
      <label for="nama">Nama</label>
      <input id="nama" name="nama" type="text" autocomplete="name" required />
    </p>
    <p>
      <label for="wa">WhatsApp</label>
      <input id="wa" name="wa" type="tel" autocomplete="tel" required />
    </p>
  </fieldset>

  <fieldset>
    <legend>Paket</legend>
    <label><input type="radio" name="paket" value="4hari" required /> 4 hari</label>
    <label><input type="radio" name="paket" value="7hari" /> 7 hari</label>
  </fieldset>

  <fieldset>
    <legend>Tambahan (opsional)</legend>
    <label><input type="checkbox" name="fasilitas[]" value="snorkel" /> Snorkel</label>
    <label><input type="checkbox" name="fasilitas[]" value="kamera" /> Kamera</label>
  </fieldset>

  <p>
    <label for="berangkat">Tanggal berangkat</label>
    <input id="berangkat" name="berangkat" type="date" required />
  </p>
  <p>
    <label for="bukti">Bukti transfer (JPG/PDF)</label>
    <input id="bukti" name="bukti" type="file" accept="image/jpeg,application/pdf" />
  </p>
  <p>
    <button type="submit">Kirim pemesanan</button>
  </p>
</form>
```

Jika ada file: `enctype="multipart/form-data"` pada `<form>`.

**Biasanya digabungkan dengan:** bab 06, validasi Laravel `array`, `date`, `file`.

## Resep 6 · Tabel harga yang bisa di-scroll

**Untuk apa:** data berkolom di HP tanpa mematahkan semantik.

```html
<div class="tabel-bungkus">
  <table>
    <caption>Harga open trip 2026 (ilustrasi tugas)</caption>
    <thead>
      <tr>
        <th scope="col">Paket</th>
        <th scope="col">Durasi</th>
        <th scope="col">Kuota</th>
        <th scope="col">Harga</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <th scope="row">Pianemo</th>
        <td>1 hari</td>
        <td>10</td>
        <td>Rp 1.500.000</td>
      </tr>
      <tr>
        <th scope="row">4 hari</th>
        <td>4 hari</td>
        <td>12</td>
        <td>Rp 8.500.000</td>
      </tr>
    </tbody>
  </table>
</div>
```

```css
.tabel-bungkus {
  overflow-x: auto;
}

table {
  border-collapse: collapse;
  min-width: 36rem;
  width: 100%;
}
```

Jangan mengubah ini menjadi tiga `div` kolom yang tidak bisa dibaca sebagai tabel jika dosen meminta tabel.

**Biasanya digabungkan dengan:** bab 04, zebra `tr:nth-child(even)`.

## Resep 7 · Galeri gambar ber-figure

**Untuk apa:** beberapa foto yang masing-masing punya keterangan.

```html
<section aria-labelledby="judul-galeri">
  <h2 id="judul-galeri">Galeri</h2>
  <ul class="galeri">
    <li>
      <figure>
        <img src="images/pianemo.jpg" alt="Karst Pianemo dari puncak" width="800" height="600" loading="lazy" />
        <figcaption>Pianemo</figcaption>
      </figure>
    </li>
    <li>
      <figure>
        <img src="images/arborek.jpg" alt="Dermaga kayu Pulau Arborek" width="800" height="600" loading="lazy" />
        <figcaption>Arborek</figcaption>
      </figure>
    </li>
  </ul>
</section>
```

Gambar pertama di hero: jangan `loading="lazy"`.

Lightbox: tombol/tautan yang membuka `<dialog>`, bukan `div` gelap tanpa fokus.

**Biasanya digabungkan dengan:** CSS Grid, `next/image`, `alt` yang tidak sama semua (“gambar”).

## Resep 8 · FAQ dengan `details` atau accordion

**Untuk apa:** hemat ARIA jika cukup native.

```html
<section aria-labelledby="judul-faq">
  <h2 id="judul-faq">Pertanyaan</h2>
  <details>
    <summary>Apakah tiket kawasan termasuk paket?</summary>
    <p>Tidak. Dijelaskan terpisah sebelum berangkat.</p>
  </details>
  <details>
    <summary>Bisa charter untuk keluarga 6 orang?</summary>
    <p>Bisa. Pilih radio Charter di form pemesanan.</p>
  </details>
</section>
```

Jika dosen meminta tombol accordion kustom, pakai pola `aria-expanded` di bab 08. Jangan keduanya sekaligus pada pertanyaan yang sama.

**Biasanya digabungkan dengan:** CSS `summary { cursor: pointer; }`, JS tidak wajib.

## Resep 9 · Hero + gambar cadangan rasio

**Untuk apa:** mencegah loncat layout.

```html
<header class="hero">
  <h1>Jelajah Raja Ampat</h1>
  <p>Open trip 4 hari dari Sorong.</p>
  <p><a class="tombol" href="#pesan">Cek kuota</a></p>
  <img
    class="hero-foto"
    src="images/hero.jpg"
    alt="Laut jernih di antara pulau karst"
    width="1600"
    height="900"
    fetchpriority="high"
    decoding="async"
  />
</header>
```

```css
.hero-foto {
  display: block;
  width: 100%;
  height: auto;
}
```

Background-image hero: tulis judul di HTML, bukan hanya di gambar. Jika teks ada di dalam foto, ulangi di `h1`.

**Biasanya digabungkan dengan:** `object-fit: cover` pada kotak tetap, `next/image priority`.

## Resep 10 · Embed peta / video aman

```html
<h2>Lokasi kumpul</h2>
<iframe
  title="Peta bandara Sorong"
  src="https://www.openstreetmap.org/export/embed.html?bbox=...&amp;layer=mapnik"
  width="600"
  height="400"
  loading="lazy"
></iframe>
<p><a href="https://www.openstreetmap.org/?..." target="_blank" rel="noreferrer">Buka peta layar penuh (tab baru)</a></p>

<h2>Cuplikan Arborek</h2>
<video controls width="640" height="360" poster="images/arborek-poster.jpg" preload="metadata">
  <source src="video/arborek.mp4" type="video/mp4" />
  <track kind="captions" src="video/arborek-id.vtt" srclang="id" label="Indonesia" default />
  <p>Video tidak diputar. <a href="video/arborek.mp4">Unduh MP4</a>.</p>
</video>
```

Jangan autoplay bersuara. Sediakan tautan cadangan.

**Biasanya digabungkan dengan:** CSS rasio 16/9, `sandbox` jika menanam HTML tak dipercaya.

## Resep 11 · Pesan sukses dan error di form JS

```html
<form id="form-kontak" action="/kontak" method="post">
  <p role="status" aria-live="polite" id="status-form"></p>
  <label for="email">Email</label>
  <input id="email" name="email" type="email" required aria-describedby="email-error" />
  <p id="email-error" hidden></p>
  <button type="submit">Kirim</button>
</form>
```

```js
const form = document.querySelector("#form-kontak");
const status = document.querySelector("#status-form");
const email = document.querySelector("#email");
const emailError = document.querySelector("#email-error");

form.addEventListener("submit", async (e) => {
  e.preventDefault();
  emailError.hidden = true;
  email.removeAttribute("aria-invalid");

  if (!email.value.includes("@")) {
    email.setAttribute("aria-invalid", "true");
    emailError.textContent = "Email belum valid.";
    emailError.hidden = false;
    email.focus();
    return;
  }

  const data = new FormData(form);
  status.textContent = "Mengirim…";
  // await fetch(...)
  status.textContent = "Pesan terkirim. Kami balas lewat email.";
  form.reset();
});
```

Jangan hanya `alert()`. Jangan menghapus `label` saat sukses.

**Biasanya digabungkan dengan:** [javascript.md](../../javascript.md) `fetch`, React `setError`.

## Resep 12 · Kerangka Blade / React yang setara

### Blade layout

```html
{{-- resources/views/layouts/app.blade.php --}}
<!doctype html>
<html lang="id">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>@yield('title', 'Jelajah')</title>
    @vite(['resources/css/app.css', 'resources/js/app.js'])
  </head>
  <body>
    <a class="skip" href="#konten-utama">Loncat ke konten</a>
    @include('partials.header')
    <main id="konten-utama" tabindex="-1">
      @yield('content')
    </main>
    @include('partials.footer')
  </body>
</html>
```

Form POST: `@csrf`. Ubah method: `@method('PUT')`. Isi ulang: `old('nama')`. Error: `@error('nama')`.

### React / Next layout

```jsx
<html lang="id">
  <body>
    <a className="skip" href="#konten-utama">Loncat ke konten</a>
    <Header />
    <main id="konten-utama" tabIndex={-1}>
      {children}
    </main>
    <Footer />
  </body>
</html>
```

Ingat: `className`, `htmlFor`, `tabIndex`, `dateTime`, `autoPlay`, `srcSet`. Tag semantik tetap sama.

**Biasanya digabungkan dengan:** [laravel.md](../../laravel.md), [react-js.md](../../react-js.md), [next-js.md](../../next-js.md).

## Daftar kesalahan HTML yang memotong nilai

### Kerangka

1. Tidak ada `<!doctype html>`.
2. Tidak ada `lang="id"`.
3. Tidak ada `charset` / `viewport`.
4. `<title>` masih `Document`.
5. Path `style.css` / `script.js` 404.
6. Skrip di `head` tanpa `defer`, lalu `querySelector` = `null`.

### Teks dan semantik

7. Banyak `h1` atau loncat ke `h4`.
8. Seluruh halaman `div`.
9. Banyak `main`.
10. `<br><br><br>` sebagai jarak.
11. `<p>` berisi `div` / `ul`.
12. `<u>` sebagai tautan palsu.

### Media

13. `<img>` tanpa `alt` (atau `alt="gambar"`).
14. `target="_blank"` tanpa `rel="noreferrer"`.
15. `href="#"` untuk tombol.
16. Iframe tanpa `title`.
17. Video autoplay bersuara.

### Daftar dan tabel

18. Tabel untuk navbar / layout.
19. Judul kolom memakai `td` bukan `th`.
20. `ul` tanpa `li`.
21. Daftar bersarang di luar `li`.

### Form

22. Tidak ada `label` / `for` tidak cocok `id`.
23. Tidak ada `name` — server kosong.
24. File tanpa `multipart/form-data`.
25. `<button>Batal</button>` mensubmit.
26. Radio beda `name`.
27. `type="number"` untuk telepon.
28. Placeholder sebagai satu-satunya label.

### Aksesibilitas

29. `div onclick` sebagai tombol.
30. `outline: none` tanpa pengganti.
31. Dua `nav` tanpa `aria-label`.
32. `aria-hidden` pada induk berfokus.
33. Warna saja untuk “wajib / error / habis”.
34. `id` dobel.

### Proses

35. File tidak UTF-8 — huruf rusak meski ada meta.
36. Nama file `Foto.JPG` vs `foto.jpg` di server Linux.
37. Mengumpulkan folder tanpa gambar yang di-`src`.
38. Menempel semua contoh ensiklopedia ke satu file sampai tidak ada hierarki.

## Cara men-debug “tidak kelihatan / tidak jalan”

1. **View Source vs Elements.** Source = yang kamu tulis. Elements = yang browser perbaiki. Jika `p` terpotong, lihat aturan susunan.
2. **Network.** CSS/JS/gambar 404 = path salah, bukan “HTML rusak”.
3. **Console.** Error JS menghentikan skrip berikutnya.
4. **Computed.** `hidden` dilawan `display: flex`.
5. **Aksesibilitas panel.** Nama tombol kosong?
6. **Validator.** [Nu HTML Checker](https://validator.w3.org/nu/) — tidak semua peringatan memotong nilai, tetapi `id` dobel dan `for` nyasar terlihat.
7. **Matikan ekstensi.** Dark reader / blocker kadang menyembunyikan iframe.

Pertanyaan wajib: “Apakah file yang saya buka di browser **file yang sama** yang saya edit?” Path `file://` vs Live Server vs `php artisan serve` sering beda folder.

**Biasanya digabungkan dengan:** DevTools, bukan menebak dengan menambah `!important` atau `br`.

## Checklist sebelum kumpul

- [ ] Doctype, `lang="id"`, charset, viewport, judul tab spesifik
- [ ] Satu `h1`, heading berurut
- [ ] `header` / `nav` / `main` / `footer` (atau alasan jelas jika tidak)
- [ ] Semua gambar bermakna ber-`alt`; dekorasi `alt=""`
- [ ] Semua input ber-`label` dan `name`
- [ ] Tombol aksi adalah `<button>` atau `<input type="submit">`
- [ ] Tautan luar `_blank` ber-`rel="noreferrer"`
- [ ] Tidak ada `id` dobel
- [ ] CSS dan gambar termuat (cek Network)
- [ ] Tab sekali dari atas: skip link, menu, isi, form
- [ ] Fokus terlihat
- [ ] HP: viewport + tidak ada scroll horizontal aneh (kecuali tabel yang memang di-scroll)
- [ ] Form file: `enctype` jika perlu
- [ ] Tidak ada rahasia di komentar HTML
- [ ] Teks “lorem” / `asdf` / `Document` sudah diganti

Jika waktu tinggal 10 menit: perbaiki `alt`, `label`, `lang`, `h1`, dan path CSS. Itu empat item yang paling sering terlihat penguji manusia.
