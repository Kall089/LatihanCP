# Cheatsheet CSS

[← Daftar panduan](README.md) · [HTML](html.md) · [Lanjut JavaScript →](javascript.md)

CSS mengatur **bagaimana HTML ditampilkan**. HTML mengatakan “ini tombol”, CSS mengatakan “tombol ini biru, sudutnya membulat, dan lebarnya mengikuti isi”.

## Daftar isi

- [Menghubungkan CSS](#menghubungkan-css)
- [Tiga cara menulis CSS](#tiga-cara-menulis-css)
- [Selector dan prioritas](#selector-dan-prioritas)
- [Box model dan ukuran](#box-model-dan-ukuran)
- [Display](#display)
- [Warna dan tipografi](#warna-dan-tipografi)
- [Flexbox](#flexbox)
- [Grid](#grid)
- [Position](#position)
- [Responsif](#responsif)
- [Interaksi dan transisi](#interaksi-dan-transisi)
- [Variabel CSS](#variabel-css)
- [Tailwind CSS](#tailwind-css)
- [Satuan dan calc](#satuan-dan-calc)
- [Overflow dan gambar](#overflow-dan-gambar)
- [Pseudo-class dan pseudo-element](#pseudo-class-dan-pseudo-element)
- [Transform dan animasi](#transform-dan-animasi)
- [z-index](#z-index)
- [Resep kartu](#resep-kartu)
- [Kesalahan umum](#kesalahan-umum)

## Menghubungkan CSS

**Untuk apa:** memisahkan struktur HTML dan aturan tampilan agar mudah dirawat.

`index.html`, di dalam `<head>`:

```html
<link rel="stylesheet" href="style.css">
```

`style.css`:

```css
body {
  margin: 0;
  font-family: system-ui, sans-serif;
  background: #f8fafc;
  color: #0f172a;
}
```

`margin: 0` menghapus jarak bawaan halaman. `font-family` memilih keluarga huruf; browser memakai pilihan berikutnya jika pilihan pertama tidak tersedia.

**Biasanya digabungkan dengan:** HTML biasa, template Blade Laravel, atau komponen React. Di React gunakan `className="kartu"`; di HTML/Blade gunakan `class="kartu"`.

## Tiga cara menulis CSS

**Untuk apa:** memahami tempat aturan ditulis. Tugas praktikum sering menuntut ketiganya terlihat.

**Inline** — langsung di elemen, untuk satu properti darurat atau tugas:

```html
<p style="letter-spacing: 2px; text-transform: uppercase">Papua Barat Daya</p>
```

Sulit dirawat jika dipakai di banyak elemen. Tidak bisa `:hover` atau media query.

**Internal** — blok `<style>` di `<head>`, untuk aturan milik satu halaman:

```html
<style>
  .visit-label { color: #164863; font-weight: bold; }
</style>
```

**External** — file `style.css` yang dipakai banyak halaman. Ini cara utama.

Jika ketiga-tiganya mengenai properti yang sama, yang lebih spesifik menang; kalau spesifisitas sama, yang belakangan menang. Inline sangat spesifik, jadi mudah “mengalahkan” file eksternal tanpa kamu sadari.

**Biasanya digabungkan dengan:** HTML tugas kuliah, dan nanti Tailwind yang menggantikan banyak aturan di class.

## Selector dan prioritas

**Untuk apa:** menentukan elemen mana yang akan diberi aturan.

```css
p { line-height: 1.6; }                 /* Semua paragraf */
.kartu { padding: 1rem; }              /* Semua class kartu */
#judul-utama { font-size: 2rem; }       /* Elemen dengan id ini */
.kartu p { color: #475569; }            /* Paragraf di dalam kartu */
.kartu > h2 { margin-top: 0; }          /* h2 anak langsung kartu */
input[type="email"] { width: 100%; }   /* Input dengan tipe email */
```

Gunakan class untuk gaya yang akan dipakai berulang. `id` harus unik di satu halaman dan sering dipakai untuk tujuan lain, misalnya penghubung `label` dengan `input`.

Dalam origin, tingkat importance, dan cascade layer yang sama: selector ID lebih spesifik daripada class, dan class lebih spesifik daripada selector tag. Jika spesifisitas sama, aturan yang ditulis terakhir menang. Hindari menjadikan `!important` solusi pertama; periksa selector yang bertabrakan lewat DevTools.

**Biasanya digabungkan dengan:** class HTML, class kondisional React, dan `classList` JavaScript.

## Box model dan ukuran

**Untuk apa:** mengatur ruang yang ditempati elemen. Urutannya dari dalam: **content → padding → border → margin**.

```css
*, *::before, *::after {
  box-sizing: border-box;
}

.kotak {
  width: 100%;
  max-width: 30rem;
  padding: 1rem;
  border: 1px solid #cbd5e1;
  margin: 2rem auto;
}
```

- `padding`: ruang antara isi dan tepi kotak.
- `margin`: ruang di luar kotak; `auto` di kiri-kanan dapat menengahkan kotak yang lebih sempit dari wadahnya.
- `border-box`: lebar yang ditentukan sudah mencakup padding dan border.
- `max-width`: membatasi lebar maksimum tanpa memaksa layar kecil melebar.
- `px`: ukuran CSS tetap; `rem`: relatif ke ukuran huruf root; `%`: relatif ke acuan properti tersebut, sering kali wadah; `fr`: bagian ruang dalam Grid.

**Biasanya digabungkan dengan:** container halaman, kartu, formulir, dan layout responsif.

## Display

**Untuk apa:** mengatur apakah elemen menjadi kotak lebar penuh, duduk di baris teks, atau menyusun anak.

```css
.lencana { display: inline-block; padding: 0.15rem 0.5rem; }
.tersembunyi { display: none; }
.baris { display: flex; }
.papan { display: grid; }
```

- `block`: ambil satu baris penuh (`div`, `p`, `h1`).
- `inline`: ikut alur teks, lebar mengikuti isi (`span`, `a`).
- `inline-block`: seperti teks, tetapi boleh punya width/padding yang teratur.
- `none`: hilang dari layout (menu HP yang tertutup).
- `flex` / `grid`: lihat bagian Flexbox dan Grid.

`visibility: hidden` menyembunyikan tetapi masih memakan ruang. `display: none` melepas ruang itu.

**Biasanya digabungkan dengan:** navbar hamburger, badge, dan layout.

## Warna dan tipografi

**Untuk apa:** membuat informasi nyaman dibaca dan membedakan tingkat kepentingannya.

```css
h1 {
  font-size: clamp(1.75rem, 4vw, 3rem);
  line-height: 1.15;
  font-weight: 700;
}

p {
  max-width: 65ch;
  line-height: 1.7;
  color: #334155;
}
```

`clamp(minimum, nilai fleksibel, maksimum)` membuat ukuran judul mengikuti layar dalam batas tertentu. `ch` berguna membatasi panjang baris. `line-height` tanpa satuan mengikuti ukuran huruf elemen.

**Biasanya digabungkan dengan:** artikel, judul halaman, dan desain mobile. Pastikan teks tetap jelas terhadap latarnya.

## Flexbox

**Untuk apa:** menyusun elemen dalam satu arah utama, misalnya menu horizontal atau ikon di samping teks.

```html
<nav class="menu" aria-label="Navigasi utama">
  <a href="/">Beranda</a>
  <a href="/produk">Produk</a>
</nav>
```

```css
.menu {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 1rem;
  flex-wrap: wrap;
}
```

`justify-content` mengatur sumbu utama; `align-items` mengatur sumbu silang. Secara default arah utamanya baris. Jika memakai `flex-direction: column`, sumbu utamanya berubah menjadi vertikal. `gap` memberi jarak antaritem, dan `flex-wrap` mengizinkan item turun baris.

**Biasanya digabungkan dengan:** navbar, baris tombol, isi kartu, dan Grid untuk kerangka halaman yang lebih besar.

## Grid

**Untuk apa:** menyusun layout baris dan kolom, misalnya katalog produk.

```css
.daftar-produk {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(min(100%, 15rem), 1fr));
  gap: 1rem;
}
```

`auto-fit` menghitung kolom yang muat. Setiap kolom memiliki batas minimum sampai `15rem`, tetapi tetap boleh menyempit mengikuti wadah kecil karena `min(100%, 15rem)`. `1fr` membagi sisa ruang secara merata.

Untuk dua kolom tetap:

```css
.dashboard {
  display: grid;
  grid-template-columns: 15rem minmax(0, 1fr);
  gap: 1.5rem;
}
```

Kolom pertama untuk sidebar, kolom kedua untuk konten. Tambahkan media query agar menjadi satu kolom di layar kecil.

**Biasanya digabungkan dengan:** daftar dari `.map()` React dan Flexbox di dalam masing-masing kartu.

## Position

**Untuk apa:** menempatkan elemen dengan hubungan posisi tertentu, misalnya label di sudut kartu.

```css
.kartu { position: relative; }

.label-baru {
  position: absolute;
  top: 0.75rem;
  right: 0.75rem;
}

.header {
  position: sticky;
  top: 0;
  z-index: 10;
  background: white;
}
```

`relative` tetap mengikuti alur dokumen sekaligus bisa menjadi acuan anak `absolute`. `absolute` keluar dari alur normal. `sticky` tetap ikut layout, lalu menempel saat mencapai batas scroll. `fixed` biasanya menempel terhadap viewport, misalnya tombol bantuan mengambang.

**Biasanya digabungkan dengan:** badge produk, header, dan wadah yang memiliki batas ukuran. Untuk layout utama, mulai dengan Flexbox/Grid agar isi tidak saling menimpa.

## Responsif

**Untuk apa:** menyesuaikan halaman dengan ruang yang tersedia.

Di `<head>` HTML:

```html
<meta name="viewport" content="width=device-width, initial-scale=1">
```

```css
.konten {
  display: grid;
  grid-template-columns: 1fr;
  gap: 1rem;
  width: min(100% - 2rem, 70rem);
  margin-inline: auto;
}

@media (min-width: 48rem) {
  .konten { grid-template-columns: 1fr 1fr; }
}

img {
  max-width: 100%;
  height: auto;
  display: block;
}
```

Mulai dari satu kolom untuk layar kecil. Ketika lebar cukup, ubah menjadi dua kolom. Breakpoint dipilih ketika konten membutuhkan perubahan, bukan karena harus mengikuti merek perangkat tertentu.

**Biasanya digabungkan dengan:** Grid, Flexbox, ukuran fleksibel, dan gambar responsif.

## Interaksi dan transisi

**Untuk apa:** memberi umpan balik saat pengguna menyentuh kontrol.

```css
.tombol {
  background: #1d4ed8;
  color: white;
  transition: background-color 150ms ease;
}

.tombol:hover { background: #1e40af; }
.tombol:focus-visible { outline: 3px solid #0f172a; outline-offset: 3px; }
.tombol:disabled { opacity: 0.6; cursor: not-allowed; }

@media (prefers-reduced-motion: reduce) {
  .tombol { transition: none; }
}
```

`:hover` untuk pointer; `:focus-visible` memperjelas fokus, khususnya saat navigasi keyboard. `:disabled` mengikuti atribut HTML `disabled`; CSS saja tidak menonaktifkan tombol.

**Biasanya digabungkan dengan:** event JavaScript dan state React, misalnya `disabled={sedangMenyimpan}`.

## Variabel CSS

**Untuk apa:** menyimpan nilai desain yang dipakai berkali-kali.

```css
:root {
  --warna-utama: #1d4ed8;
  --radius: 0.75rem;
}

.kartu { border-radius: var(--radius); }
.tombol { background: var(--warna-utama); }
```

Mengubah `--warna-utama` memperbarui semua aturan yang menggunakannya. Variabel juga bisa didefinisikan pada elemen tertentu untuk membatasi cakupannya.

**Biasanya digabungkan dengan:** tema terang/gelap, komponen berulang, dan desain konsisten antarlaman.

## Tailwind CSS

**Untuk apa:** menulis CSS sebagai class kecil di HTML, tanpa mengarang nama `.kartu-final-v2`.

Satu class ≈ satu properti:

| Class | CSS biasa |
|---|---|
| `flex` | `display: flex` |
| `items-center` | `align-items: center` |
| `justify-between` | `justify-content: space-between` |
| `grid` | `display: grid` |
| `grid-cols-1` | `grid-template-columns: 1fr` |
| `gap-4` | `gap: 1rem` |
| `p-4` | `padding: 1rem` |
| `mt-8` | `margin-top: 2rem` |
| `bg-[#ddf2fd]` | `background-color: #ddf2fd` |
| `text-sm` | `font-size` kecil |
| `rounded` | `border-radius` |
| `hidden` | `display: none` |
| `md:flex` | `display: flex` mulai ±768px |
| `w-full` | `width: 100%` |
| `max-w-7xl` | lebar maksimal besar |
| `mx-auto` | `margin-left/right: auto` |
| `min-h-16` | tinggi minimal 4rem (64px) |
| `sticky top-0` | `position: sticky; top: 0` |
| `z-50` | `z-index: 50` |
| `hover:bg-[#427d9d]` | background saat hover |
| `sr-only` | tersembunyi visual, tetap dibaca screen reader |

Prefix lain: `sm:` ±640px, `md:` ±768px, `lg:` ±1024px, `xl:` ±1280px, `hover:`, `focus:`, `peer-checked:` (checkbox + saudara).

**Mobile-first:** class tanpa prefix berlaku dari HP. Prefix `md:` / `lg:` baru aktif di layar lebih lebar.

```html
<div class="grid grid-cols-1 gap-6 md:grid-cols-3">
  <article>Kartu 1</article>
  <article>Kartu 2</article>
  <article>Kartu 3</article>
</div>
```

HP: 1 kolom (`grid-cols-1`). Tablet ke atas: 3 kolom (`md:grid-cols-3`). Tidak perlu menulis `md:grid-cols-1`; itu sudah default.

`scroll-mt-16` = `scroll-margin-top: 4rem` (64px). Dipakai di section `#home` / `#info` supaya judul tidak ketutup navbar `sticky` yang tingginya `min-h-16`.

Latihan CDN (bukan untuk produksi):

```html
<script src="https://cdn.tailwindcss.com"></script>
```

Di Next.js / proyek serius, Tailwind di-build lewat PostCSS, bukan CDN.

**Biasanya digabungkan dengan:** HTML tugas, komponen React (`className`), layout Next.js, dan CSS biasa untuk hal yang utilitasnya capek (hamburger `:checked`, `grid-template-areas`).

Tailwind tidak menggantikan pemahaman Flexbox/Grid. `items-center` tetap `align-items: center`.

## Resep kartu

Gabungan **box model + Flexbox + tipografi**. Letakkan HTML ini di dalam `<body>`:

```html
<article class="kartu-produk">
  <h2>Buku JavaScript</h2>
  <p>Catatan praktis untuk belajar interaksi web.</p>
  <a href="/produk/buku-javascript">Lihat detail</a>
</article>
```

```css
.kartu-produk {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
  padding: 1.25rem;
  background: white;
  border: 1px solid #cbd5e1;
  border-radius: 0.75rem;
}

.kartu-produk h2, .kartu-produk p { margin: 0; }
.kartu-produk a { margin-top: auto; }
```

`margin-top: auto` mendorong tautan ke bawah ketika kartu memiliki ruang ekstra, misalnya saat kartu disamakan tingginya oleh Grid. URL detail di sini contoh; halaman tujuannya perlu kamu buat.

## Satuan dan calc

**Untuk apa:** memilih ukuran yang tidak pecah di HP.

| Satuan | Artinya | Pakai untuk |
|---|---|---|
| `px` | tetap | border 1px, shadow |
| `rem` | relatif ke `html` | padding, font, gap |
| `%` | relatif ke induk | lebar kolom |
| `vw` / `vh` | bagian layar | hero penuh layar |
| `dvh` | tinggi layar dinamis | HP dengan bar alamat |
| `ch` | lebar karakter | panjang baris artikel |
| `fr` | sisa ruang Grid | kolom katalog |

```css
.hero {
  min-height: calc(100dvh - 4rem);
  width: min(100% - 2rem, 70rem);
}
```

`calc` menggabungkan satuan. `min()` memilih yang lebih kecil: di HP `100% - 2rem`, di desktop batas 70rem.

**Biasanya digabungkan dengan:** navbar 64px (`4rem`) dan layout `max-w-7xl`.

## Overflow dan gambar

**Untuk apa:** mencegah halaman “melebar” dan merapikan foto.

```css
.potong { overflow: hidden; }
.bisa-scroll { overflow: auto; max-height: 12rem; }

.foto {
  width: 100%;
  height: 16rem;
  object-fit: cover;
  object-position: center 40%;
}
```

- `hidden`: potong isi (dropdown, sudut membulat pada gambar).
- `auto`: muncul scrollbar jika perlu.
- `object-fit: cover`: isi kotak, boleh terpotong. `contain`: utuh, boleh ada sisa kosong.

**Biasanya digabungkan dengan:** kartu foto, banner, dan `next/image`.

## Pseudo-class dan pseudo-element

**Untuk apa:** gaya berdasarkan keadaan atau sisipan tanpa HTML tambahan.

```css
a:hover { text-decoration: underline; }
input:focus { border-color: #1d4ed8; }
li:first-child { font-weight: 700; }
p::first-line { font-weight: 600; }

.menu a::after {
  content: "";
  display: block;
  height: 3px;
  transform: scaleX(0);
}
.menu a:hover::after { transform: scaleX(1); }
```

`::before` / `::after` butuh `content`. Jangan menaruh informasi penting hanya di `content`; pembaca layar bisa melewatkannya.

**Biasanya digabungkan dengan:** navbar underline, badge, dan state React (`disabled`).

## Transform dan animasi

**Untuk apa:** gerak kecil sebagai umpan balik, bukan dekorasi wajib.

```css
.tombol { transition: transform 150ms ease, background-color 150ms ease; }
.tombol:hover { transform: translateY(-2px); }

@keyframes muncul {
  from { opacity: 0; transform: translateY(8px); }
  to { opacity: 1; transform: none; }
}

.kartu { animation: muncul 200ms ease; }

@media (prefers-reduced-motion: reduce) {
  .tombol, .kartu { transition: none; animation: none; }
}
```

`transform` sering lebih halus daripada menggeser `top`/`margin`. Hormati `prefers-reduced-motion`.

**Biasanya digabungkan dengan:** `:hover`, dan class yang ditambah JavaScript.

## z-index

**Untuk apa:** mengatur siapa yang di depan. Hanya berlaku jika elemen punya `position` selain `static` (atau konteks stacking lain).

```css
.navbar { position: sticky; top: 0; z-index: 50; }
.dropdown { position: absolute; z-index: 20; }
.modal { position: fixed; z-index: 100; }
```

Anak tidak bisa “menembus” orang tua yang sudah membuat stacking context (misalnya `opacity`, `transform`, `z-index`). Kalau angka besar tidak mempan, cek induknya dulu.

**Biasanya digabungkan dengan:** navbar sticky, hamburger, dan overlay.

## Kesalahan umum

- **CSS tidak muncul:** periksa lokasi `style.css`, atribut `href`, dan panel Network.
- **Lebar melebihi layar:** periksa fixed width, teks panjang, dan `box-sizing`.
- **`z-index` tidak bekerja seperti dugaan:** periksa stacking context, bukan sekadar menaikkan angkanya.
- **Elemen ingin ditengahkan:** tentukan dulu apakah yang ditengahkan teks (`text-align`) atau kotak (Flexbox/Grid/margin).
- **Fokus keyboard hilang:** jangan menghapus outline tanpa menggantinya dengan indikator yang terlihat.

Latihan: ubah contoh kartu menjadi tiga kartu, susun dengan Grid, lalu cek pada lebar 360px dan 1024px.

Referensi lanjutan: [MDN CSS](https://developer.mozilla.org/en-US/docs/Web/CSS).
