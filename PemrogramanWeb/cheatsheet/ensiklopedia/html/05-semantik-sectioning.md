# 05 · Semantik dan sectioning

[← Daftar dan tabel](04-list-table.md) · [Daftar](README.md) · [Form →](06-form-kontrol-lengkap.md)

**Untuk apa file ini:** menandai **peran wilayah** halaman. Pembaca layar bisa loncat ke “navigasi”, “konten utama”, “kaki”. CSS tidak peduli kamu memakai `header` atau `div` — manusia dan alat bantu peduli.

## Daftar isi

- [Peta halaman yang sehat](#peta-halaman-yang-sehat)
- [`<header>`](#header)
- [`<nav>`](#nav)
- [`<main>`](#main)
- [`<section>`](#section)
- [`<article>`](#article)
- [`<aside>`](#aside)
- [`<footer>`](#footer)
- [`<address>`](#address)
- [`<hgroup>`](#hgroup)
- [`<search>`](#search)
- [`<div>` sebagai pembanding](#div-sebagai-pembanding)
- [Landmark dan berapa kali boleh dipakai](#landmark-dan-berapa-kali-boleh-dipakai)
- [Heading di dalam sectioning](#heading-di-dalam-sectioning)
- [Kesalahan semantik yang sering muncul](#kesalahan-semantik-yang-sering-muncul)

## Peta halaman yang sehat

**Untuk apa:** kerangka tugas profil, landing, atau katalog sederhana.

```html
<body>
  <header>
    <p class="logo">Jelajah Raja Ampat</p>
    <nav aria-label="Utama">
      <ul>
        <li><a href="#home">Beranda</a></li>
        <li><a href="#info">Info</a></li>
        <li><a href="#kontak">Kontak</a></li>
      </ul>
    </nav>
  </header>

  <main>
    <section id="home">
      <h1>Jelajah Raja Ampat</h1>
      <p>Trip kecil, kapal, dan peta yang jujur.</p>
    </section>

    <section id="info" aria-labelledby="judul-info">
      <h2 id="judul-info">Info keberangkatan</h2>
      <article>
        <h3>Open trip Oktober</h3>
        <p>Kuota 12 orang. Titik kumpul Sorong.</p>
      </article>
    </section>

    <aside>
      <h2>Catatan cuaca</h2>
      <p>Gelombang bisa membatalkan perahu kecil.</p>
    </aside>
  </main>

  <footer>
    <p><small>© 2026 Jelajah. Bukan operator resmi kawasan.</small></p>
    <address>
      <a href="mailto:halo@contoh.test">halo@contoh.test</a>
    </address>
  </footer>
</body>
```

Urutan di HTML sebaiknya urutan baca: header, main, footer. CSS Grid boleh menaruh aside di kiri secara visual tanpa memindahkan aside ke atas `h1` di sumber.

**Biasanya digabungkan dengan:** navbar sticky (CSS `position: sticky`), React komponen `Header`/`Main`/`Footer` yang men-render tag yang sama, Blade layout `@yield('content')` di dalam `<main>`.

## `<header>`

**Untuk apa:** pengantar suatu bagian: biasanya logo + navigasi di tingkat halaman, atau judul + meta di dalam `article`.

```html
<header>
  <a href="index.html">Jelajah Raja Ampat</a>
  <nav aria-label="Utama">...</nav>
</header>
```

Di dalam artikel:

```html
<article>
  <header>
    <h2>Open trip Oktober</h2>
    <p><time datetime="2026-10-12">12 Oktober 2026</time> · 4 hari</p>
  </header>
  <p>Titik kumpul bandara Sorong, pukul 06.00.</p>
</article>
```

Bukan hanya “blok paling atas yang berwarna”. Jika sebuah `div` hanya menaruh hero image tanpa judul/nav, itu belum tentu `header`.

Boleh ada **banyak** `header` di halaman, selama masing-masing mengantar sectioning-nya. Yang biasanya satu: header situs.

Jangan menaruh `header` di dalam `address` atau `footer` secara sia-sia. Jangan membungkus seluruh halaman dengan `header`.

**Biasanya digabungkan dengan:** CSS sticky + `z-index`, `scroll-margin` pada target, React `<header className="situs-header">`. Landmark otomatis “banner” jika `header` bukan anak `article`/`section`.

## `<nav>`

**Untuk apa:** kumpulan tautan **navigasi**. Menu utama, daftar isi, pagination, breadcrumb. Bukan setiap kelompok tautan (tautan sosial di footer tidak wajib `nav` kecuali kamu menganggapnya navigasi).

```html
<nav aria-label="Utama">
  <ul>
    <li><a href="#home">Beranda</a></li>
    <li><a href="#info">Info</a></li>
    <li><a href="kontak.html">Kontak</a></li>
  </ul>
</nav>
```

### Beberapa `nav` di satu halaman

Boleh. **Beri nama berbeda** lewat `aria-label` atau heading agar landmark tidak kembar “navigation”.

```html
<nav aria-label="Utama">...</nav>
...
<nav aria-label="Daftar isi halaman" aria-labelledby="judul-toc">
  <h2 id="judul-toc">Di halaman ini</h2>
  <ol>
    <li><a href="#harga">Harga</a></li>
    <li><a href="#faq">FAQ</a></li>
  </ol>
</nav>
```

Isi yang rapi: `ul`/`ol` + `li` + `a`. Boleh juga tautan langsung, tetapi daftar lebih mudah diumumkan.

`nav` tidak otomatis membuat hamburger. Itu CSS/JS. `nav` hanya makna.

Jangan membungkus seluruh halaman. Jangan memakai `nav` untuk daftar produk.

**Biasanya digabungkan dengan:** `aria-current="page"` pada tautan aktif (bab 08), tombol hamburger + `aria-expanded`, Next.js `<Link>`, Laravel `request()->routeIs('home')` untuk class aktif.

## `<main>`

**Untuk apa:** **konten utama** yang unik di halaman itu. Satu dokumen = **satu** `main` yang terlihat.

```html
<main id="konten-utama">
  <h1>Paket 4 hari</h1>
  <p>...</p>
</main>
```

Bukan pembungkus navbar. Bukan pembungkus footer. Skip link biasanya menunjuk ke `main` (bab 08 dan 09).

Jangan lebih dari satu `main` terlihat. `hidden` pada `main` cadangan (pola lama) membingungkan; hindari.

Di aplikasi React SPA, tetap satu `<main>` di layout, ganti isinya. Jangan setiap kartu jadi `main`.

**Biasanya digabungkan dengan:** skip link “Loncat ke konten”, CSS `main { max-width: 70rem; margin-inline: auto; }`, Blade `@yield('content')`, Next.js `app/page.js` di dalam `<main>` di `layout.js`.

## `<section>`

**Untuk apa:** bagian **bertema** di dalam dokumen. Idealnya punya heading.

```html
<section id="harga" aria-labelledby="judul-harga">
  <h2 id="judul-harga">Harga</h2>
  <p>Open trip 4 hari mulai Rp 8.500.000.</p>
</section>
```

`id` pada `section` membuat tautan `#harga` dan target navbar.

Bukan sinonim `div`. Jika kamu butuh wadah Grid tanpa tema baru, `div` lebih jujur.

Tes: “Bisakah bagian ini diberi judul yang masuk akal?” Jika tidak, kemungkinan besar `div`.

Jangan membuat `section` di dalam `section` berlapis-lapis hanya karena setiap kartu ingin dibungkus. Kartu mandiri sering lebih cocok `article`.

**Biasanya digabungkan dengan:** `id` + navbar, `aria-labelledby` ke heading, CSS padding per bagian (`scroll-mt-16`), React komponen `Section` yang menerima `judul` dan `id`.

## `<article>`

**Untuk apa:** potongan yang **masuk akal sendirian**: berita, kartu paket, komentar, widget yang bisa disebar.

```html
<article>
  <h3>Paket Pianemo sehari</h3>
  <p>Berangkat pagi dari Waisai, pulang sore. Termasuk perahu dan makan siang kotak.</p>
  <p><a href="pianemo.html">Detail Pianemo</a></p>
</article>
```

Di dalam umpan:

```html
<section aria-labelledby="judul-berita">
  <h2 id="judul-berita">Catatan lapangan</h2>
  <article>
    <header>
      <h3>Arus di kanal Arborek</h3>
      <p><time datetime="2026-09-01">1 September 2026</time></p>
    </header>
    <p>Arus pagi lebih jinak daripada siang.</p>
  </article>
  <article>
    <header>
      <h3>Dermaga penuh di akhir pekan</h3>
      <p><time datetime="2026-09-08">8 September 2026</time></p>
    </header>
    <p>Datang 20 menit lebih awal.</p>
  </article>
</section>
```

Tes: “Kalau potongan ini di-RSS / di-screenshot / dipindah ke halaman lain, masih utuh?” Jika ya, `article`. Jika hanya “bagian Harga dari halaman ini”, `section`.

`article` boleh berisi `section`, dan sebaliknya, tetapi jangan bersarang tanpa alasan.

**Biasanya digabungkan dengan:** CSS kartu, React `KartuPaket`, Laravel `@each` partial, heading sendiri di setiap kartu.

## `<aside>`

**Untuk apa:** konten **samping** terkait: tips, iklan, catatan cuaca, “artikel terkait”. Bukan sembarang kolom kiri.

```html
<aside>
  <h2>Tips cepat</h2>
  <ul>
    <li>Bawa uang tunai.</li>
    <li>Jangan menyentuh karang.</li>
  </ul>
</aside>
```

Di dalam artikel, `aside` = tangen terhadap artikel itu. Di tingkat halaman, `aside` = pelengkap `main`.

Jangan menaruh konten wajib (syarat pembayaran) hanya di `aside`. Pengguna bisa melewati landmark “complementary”.

Kolom layout “sidebar” secara visual belum tentu `aside`. Jika isinya menu, itu `nav`. Jika isinya filter yang merupakan bagian utama tugas halaman, pertimbangkan `section`.

**Biasanya digabungkan dengan:** CSS Grid `main aside { ... }`, kartu “terkait”, jangan `float` warisan kecuali merawat kode lama.

## `<footer>`

**Untuk apa:** penutup suatu bagian: kredit, hak cipta, tautan sekunder, meta penulis di artikel.

```html
<footer>
  <p><small>© 2026 Jelajah Raja Ampat</small></p>
  <ul>
    <li><a href="privasi.html">Privasi</a></li>
    <li><a href="kredit.html">Kredit foto</a></li>
  </ul>
</footer>
```

Di artikel:

```html
<article>
  <h3>Arus di kanal Arborek</h3>
  <p>...</p>
  <footer>
    <p>Ditulis oleh tim lapangan. Diperbarui <time datetime="2026-09-01">1 September 2026</time>.</p>
  </footer>
</article>
```

Boleh banyak `footer`. Landmark “contentinfo” biasanya hanya `footer` yang bukan anak `article`/`section`.

Jangan memasukkan seluruh form pemesanan ke footer hanya karena “di bawah”. Form pemesanan adalah isi `main`.

**Biasanya digabungkan dengan:** `small`, `address`, CSS border atas, Blade partial `footer.blade.php`.

## `<address>`

**Untuk apa:** **kontak penulis / pemilik** bagian terdekat (halaman atau artikel). Bukan sembarang alamat pos di artikel wisata.

```html
<footer>
  <address>
    Pengelola halaman: Jelajah Raja Ampat<br />
    <a href="mailto:halo@contoh.test">halo@contoh.test</a><br />
    <a href="tel:+629521234567">+62 952 1234 567</a>
  </address>
</footer>
```

Alamat penginapan di dalam ulasan hotel, jika itu bukan kontak penulis artikel, lebih jujur sebagai `<p>` biasa.

Default miring. Ubah dengan CSS `font-style: normal` jika tidak ingin miring.

Jangan menaruh `h1` di dalam `address`. Jangan memakai `address` untuk merapikan layout kartu.

**Biasanya digabungkan dengan:** `footer`, `mailto` / `tel` (bab 03), halaman kontak. Satu `address` per konteks penulis sudah cukup.

## `<hgroup>`

**Untuk apa:** mengelompokkan **satu heading + teks pendukung judul** (subjudul, tagline) agar subjudul tidak ikut dianggap heading tingkat baru di outline.

```html
<hgroup>
  <h1>Jelajah Raja Ampat</h1>
  <p>Trip kecil, kapal jujur, tanpa janji laut selalu tenang.</p>
</hgroup>
```

Anak yang dimaksud: satu `h1`–`h6` plus satu atau lebih `p`. Jangan menaruh dua `h1` di dalam satu `hgroup`.

```html
<!-- Maksud: judul + tagline, bukan dua heading -->
<hgroup>
  <h1>Paket 4 hari</h1>
  <p>Sorong · Waisai · Pianemo · Arborek</p>
</hgroup>
```

Dukungan outline browser historis berliku. Praktik modern: `hgroup` berguna untuk menandai tagline secara semantik; secara visual CSS mengatur ukurannya. Jika ragu, `h1` + `p` tanpa `hgroup` tetap sah.

Jangan memakai `hgroup` untuk membungkus seluruh hero (gambar, form, tombol). Itu `header` atau `div`.

**Biasanya digabungkan dengan:** hero title + tagline, CSS `hgroup p { font-size: 1.125rem; color: ... }`. Jarang wajib di penilaian tugas, tetapi rapi.

## `<search>`

**Untuk apa:** wilayah yang berisi **form pencarian**. HTML baru; browser modern merawatnya sebagai landmark.

```html
<search>
  <form action="/cari" method="get" role="search">
    <label for="q">Cari paket</label>
    <input id="q" name="q" type="search" />
    <button type="submit">Cari</button>
  </form>
</search>
```

Jika dukungan `search` dikhawatirkan di penilaian yang memakai alat lama, `form role="search"` sudah lama dikenal. Keduanya bisa dipasang bersama seperti di atas, atau pilih satu pola yang konsisten.

Bukan untuk sembarang `type="search"` yang terselip di pengaturan. Landmark search = pencarian situs / katalog.

**Biasanya digabungkan dengan:** `input type="search"`, JS filter di klien (contoh-praktik cheatsheet), Laravel `request('q')`, Next `searchParams`.

## `<div>` sebagai pembanding

**Untuk apa:** wadah **tanpa makna**. Grid, baris tombol, pembungkus yang hanya dibutuhkan CSS/JS.

```html
<div class="grid-kartu">
  <article>...</article>
  <article>...</article>
</div>
```

`div` bukan musuh. Musuhnya: **semua** jadi `div` sampai tidak ada `main`/`nav`/`h1`.

| Kebutuhan | Pakai |
| --- | --- |
| Konten utama | `main` |
| Menu tautan | `nav` |
| Bagian bertema + judul | `section` |
| Kartu mandiri | `article` |
| Pelengkap | `aside` |
| Pengantar | `header` |
| Penutup | `footer` |
| Hanya grid / flex | `div` |
| Hanya target inline | `span` |

`div` tidak boleh menggantikan `button` atau `a`. Tidak ada makna, tidak ada keyboard default.

**Biasanya digabungkan dengan:** Flexbox/Grid, React wrapper, class Tailwind. Di JSX, `div` tetap `div`; jangan ganti jadi `<section>` hanya agar “terlihat HTML5” jika tidak ada tema.

## Landmark dan berapa kali boleh dipakai

Landmark muncul di daftar rotasi pembaca layar.

| Elemen | Landmark tipikal | Berapa |
| --- | --- | --- |
| `header` (bukan di article/section) | banner | biasanya 1 |
| `nav` | navigation | banyak, **beri nama** |
| `main` | main | 1 terlihat |
| `aside` | complementary | banyak, beri nama jika >1 |
| `footer` (bukan di article/section) | contentinfo | biasanya 1 |
| `form` + nama / `search` | search atau form | sesuai kebutuhan |
| `section` + nama aksesibel | region | hanya jika punya nama |

`section` **tanpa** heading / `aria-label` / `aria-labelledby` **bukan** landmark. Itu bagus: tidak memenuhi daftar rotasi dengan region anonim.

```html
<!-- Region bernama -->
<section aria-labelledby="judul-harga">
  <h2 id="judul-harga">Harga</h2>
</section>

<!-- Bukan landmark, hanya pemisah tema internal -->
<section>
  <!-- tetap sebaiknya punya heading -->
  <h2>Harga</h2>
</section>
```

**Biasanya digabungkan dengan:** bab 08, daftar landmark di VoiceOver/NVDA rotor.

## Heading di dalam sectioning

Setiap `section`/`article`/`aside` yang terlihat idealnya punya heading. Tingkat heading mengikuti **kerangka dokumen**, bukan “di dalam section otomatis jadi h1”.

Praktik yang aman di tugas:

- Satu `h1` untuk judul halaman (sering di `main`).
- `h2` untuk `section` tingkat atas.
- `h3` untuk `article` di dalam section, atau subbagian.

```html
<main>
  <h1>Jelajah Raja Ampat</h1>
  <section>
    <h2>Paket</h2>
    <article>
      <h3>4 hari</h3>
    </article>
    <article>
      <h3>7 hari</h3>
    </article>
  </section>
</main>
```

Jangan mereset ke `h1` di setiap `article` pada halaman biasa. Pola “setiap article punya h1” lebih cocok halaman yang memang satu artikel penuh, atau sistem komponen yang dijamin sendirian di halaman.

**Biasanya digabungkan dengan:** bab 02, outline heading sebagai daftar isi.

## Kesalahan semantik yang sering muncul

1. **Hanya `div`.** Tidak ada `main`/`nav`/`h1`.
2. **Banyak `main`.** Satu per halaman.
3. **`section` tanpa judul** berlapis-lapis sebagai pengganti `div`.
4. **`article` untuk setiap kolom layout.**
5. **`aside` berisi checkout wajib.**
6. **`header` membungkus seluruh body.**
7. **`nav` pada daftar produk atau share button.**
8. **`address` untuk alamat dalam cerita wisata.**
9. **Footer berisi seluruh sitemap 80 tautan tanpa `nav` bernama**, atau sebaliknya: form utama di-`footer`.
10. **Mengira tag semantik mengubah tampilan.** Tanpa CSS, `section` kelihatan seperti `div`. Maknanya tetap berguna.

Latihan: ambil tugas halaman profil yang penuh `div`, ganti wilayah menjadi `header`/`nav`/`main`/`section`/`footer`, pastikan satu `h1`, dan beri `aria-label` jika ada dua `nav`.
