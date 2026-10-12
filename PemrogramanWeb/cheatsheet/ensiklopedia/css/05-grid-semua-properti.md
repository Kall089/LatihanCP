# 05 — Grid, semua properti

[← Flexbox](04-flexbox-semua-properti.md) · [Indeks](README.md) · [Warna →](06-warna-tipografi-list.md)

Grid menyusun **baris dan kolom sekaligus**. Pakai ini untuk katalog produk, dashboard (sidebar + isi), gallery, dan kerangka halaman. Di dalam sel, Flexbox tetap juara untuk rata ikon-teks.

Dua peran: **container** (`display: grid`) dan **item** (anak langsung). Garis grid bernomor: kolom 1 di kiri, baris 1 di atas (LTR).

## Daftar isi

- [display grid](#display-grid)
- [grid-template-columns](#grid-template-columns)
- [grid-template-rows](#grid-template-rows)
- [repeat auto-fill auto-fit minmax](#repeat-auto-fill-auto-fit-minmax)
- [fr dan minmax 0](#fr-dan-minmax-0)
- [grid-template-areas](#grid-template-areas)
- [grid-template shorthand](#grid-template-shorthand)
- [grid-auto-columns dan grid-auto-rows](#grid-auto-columns-dan-grid-auto-rows)
- [grid-auto-flow](#grid-auto-flow)
- [grid shorthand](#grid-shorthand)
- [gap](#gap)
- [justify-items](#justify-items)
- [align-items](#align-items)
- [place-items](#place-items)
- [justify-content](#justify-content)
- [align-content](#align-content)
- [place-content](#place-content)
- [justify-self align-self place-self](#justify-self-align-self-place-self)
- [grid-column grid-row span](#grid-column-grid-row-span)
- [grid-area](#grid-area)
- [line names](#line-names)
- [subgrid](#subgrid)
- [masonry dan dense](#masonry-dan-dense)
- [Peta Tailwind](#peta-tailwind)
- [Checklist debug](#checklist-debug)

## display grid

**Untuk apa:** mengaktifkan grid. Anak langsung masuk sel.

```css
.papan { display: grid; }
.meta { display: inline-grid; grid-auto-flow: column; gap: 0.5rem; }
```

`inline-grid` selebar isi. Tanpa template, satu kolom otomatis: anak menumpuk vertikal seperti block, tetapi sudah jadi grid item.

**Biasanya digabungkan dengan:** `grid-template-columns`, `gap`.

## grid-template-columns

**Untuk apa:** menentukan jumlah dan ukuran kolom.

### Daftar panjang tetap

**Untuk apa:** kolom dengan lebar yang kamu ketahui.

```css
.dashboard {
  display: grid;
  grid-template-columns: 16rem minmax(0, 1fr);
  gap: 1.5rem;
}
```

Sidebar 16rem, isi makan sisa. `minmax(0, 1fr)` wajib agar kolom isi boleh menyusut (hindari overflow teks).

**Biasanya digabungkan dengan:** media query satu kolom di HP.

### Tiga kolom sama

**Untuk apa:** bagi rata.

```css
.katalog {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr;
  gap: 1rem;
}
```

Sama dengan `repeat(3, 1fr)`. Di HP biasanya terlalu sempit; ganti lewat media query atau `auto-fit`.

**Biasanya digabungkan dengan:** `gap`, `minmax`.

### Campuran satuan

**Untuk apa:** kolom tetap + fleksibel + konten.

```css
.header {
  display: grid;
  grid-template-columns: auto 1fr auto;
  gap: 1rem;
  align-items: center;
}
```

Logo selebar konten, cari mekar, aksi selebar konten. Alternatif Flex + `margin-inline-start: auto`.

**Biasanya digabungkan dengan:** `align-items: center`.

### none

**Untuk apa:** tidak ada template eksplisit; kolom dibuat `grid-auto-columns`.

```css
.jejak { grid-template-columns: none; }
```

**Biasanya digabungkan dengan:** `grid-auto-flow: column`.

## grid-template-rows

**Untuk apa:** tinggi baris eksplisit.

```css
.halaman {
  display: grid;
  grid-template-rows: auto 1fr auto;
  min-height: 100dvh;
}
```

Header dan footer setinggi konten, `main` makan sisa. Ini pola “sticky footer” tanpa flex.

```css
.kalender {
  grid-template-rows: repeat(6, minmax(4rem, 1fr));
}
```

**Biasanya digabungkan dengan:** `min-height: 100dvh`, area.

## repeat auto-fill auto-fit minmax

### repeat(n, track)

**Untuk apa:** mengulang pola track.

```css
.papan { grid-template-columns: repeat(4, 1fr); }
.papan { grid-template-columns: repeat(2, 12rem 1fr); }
```

Yang kedua menghasilkan 4 track: `12rem 1fr 12rem 1fr`.

**Biasanya digabungkan dengan:** `gap`.

### minmax(min, max)

**Untuk apa:** track punya batas bawah dan atas.

```css
.papan {
  grid-template-columns: repeat(3, minmax(12rem, 1fr));
}
```

Tiap kolom minimal 12rem, boleh tumbuh sama rata. Jika wadah < 36rem + gap, terjadi overflow kecuali kamu bungkus dengan `auto-fit` atau media query.

**Biasanya digabungkan dengan:** `repeat`, `auto-fit`.

### auto-fit

**Untuk apa:** sebanyak mungkin kolom yang muat; **kolom kosong dilipat** sehingga item melebar mengisi.

```css
.katalog {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(min(100%, 15rem), 1fr));
  gap: 1rem;
}
```

`min(100%, 15rem)` mencegah overflow di layar < 15rem: kolom boleh lebih sempit dari 15rem sampai 100% wadah.

**Biasanya digabungkan dengan:** `gap`, kartu produk. Ini resep katalog paling aman.

### auto-fill

**Untuk apa:** sebanyak mungkin kolom yang muat; **kolom kosong tetap ada** sebagai track hantu.

```css
.katalog {
  grid-template-columns: repeat(auto-fill, minmax(15rem, 1fr));
}
```

Jika hanya ada 1 kartu di wadah lebar, `auto-fill` membiarkan kartu selebar ~15rem (sisa jadi kolom kosong). `auto-fit` meregangkan kartu itu sampai penuh. Pilih `auto-fill` jika kamu tidak ingin 1 item jadi spanduk lebar.

**Biasanya digabungkan dengan:** gallery yang jumlah itemnya berubah.

### min() di dalam minmax

**Untuk apa:** kolom responsif tanpa media query.

```css
minmax(min(100%, 18rem), 1fr)
```

Pola resmi modern. Tanpa `min(100%, ...)`, `minmax(18rem, 1fr)` memaksa overflow di HP sempit.

**Biasanya digabungkan dengan:** `auto-fit` / `auto-fill`.

## fr dan minmax 0

**Untuk apa:** `1fr` = satu bagian **sisa ruang bebas**. Sisa dihitung setelah track tetap dan gap.

```css
grid-template-columns: 200px 1fr 2fr;
```

Setelah 200px + gap, sisa dibagi 1:2.

`1fr` setara `minmax(auto, 1fr)`. `auto` sebagai minimum = `min-content`. Teks panjang atau gambar menolak kolom menyusut.

```css
grid-template-columns: minmax(0, 1fr) minmax(0, 2fr);
```

Minimum 0: kolom boleh lebih sempit dari konten. Tambah `overflow-wrap` atau `overflow: auto` di dalam sel.

**Biasanya digabungkan dengan:** `min-width: 0` pada item, `img { max-width: 100%; }`.

## grid-template-areas

**Untuk apa:** menamai wilayah, lalu menaruh item ke nama itu.

```css
.halaman {
  display: grid;
  grid-template-columns: 16rem minmax(0, 1fr);
  grid-template-rows: auto 1fr auto;
  grid-template-areas:
    "nav nav"
    "side main"
    "foot foot";
  min-height: 100dvh;
}

.nav  { grid-area: nav; }
.side { grid-area: side; }
.main { grid-area: main; }
.foot { grid-area: foot; }
```

Setiap string adalah satu baris. Nama sama yang berdampingan menyatu. Titik `.` artinya sel kosong.

```css
grid-template-areas:
  "hero hero"
  "kartu ."
  "kartu iklan";
```

Jumlah sel per baris harus sama. Nama harus identifier (huruf, tanpa spasi).

**Biasanya digabungkan dengan:** `grid-area` pada anak, media query yang menyusun ulang area.

### Menyusun ulang di HP

**Untuk apa:** satu kolom tanpa mengubah HTML.

```css
.halaman {
  grid-template-columns: 1fr;
  grid-template-areas:
    "nav"
    "main"
    "side"
    "foot";
}

@media (min-width: 48rem) {
  .halaman {
    grid-template-columns: 16rem minmax(0, 1fr);
    grid-template-areas:
      "nav nav"
      "side main"
      "foot foot";
  }
}
```

**Biasanya digabungkan dengan:** mobile-first.

## grid-template shorthand

**Untuk apa:** merangkai rows, areas, columns.

```css
.halaman {
  display: grid;
  grid-template:
    "nav nav" auto
    "side main" 1fr
    "foot foot" auto
    / 16rem minmax(0, 1fr);
}
```

Bentuk: `area-dan-rows / columns`. Sulit dibaca jika belum terbiasa; bentuk panjang lebih aman untuk tugas.

**Biasanya digabungkan dengan:** `gap`, `min-height`.

## grid-auto-columns dan grid-auto-rows

**Untuk apa:** ukuran track **implisit** (yang muncul karena item di luar template, atau `auto-flow`).

```css
.slider {
  display: grid;
  grid-auto-flow: column;
  grid-auto-columns: min(80%, 20rem);
  overflow-x: auto;
  gap: 1rem;
}

.feed {
  grid-auto-rows: minmax(8rem, auto);
}
```

Tanpa ini, track implisit berukuran `auto`.

**Biasanya digabungkan dengan:** `grid-auto-flow: column`, carousel.

## grid-auto-flow

### row

**Untuk apa:** mengisi kiri ke kanan, lalu baris baru. Bawaan.

```css
.papan { grid-auto-flow: row; }
```

**Biasanya digabungkan dengan:** `grid-template-columns`.

### column

**Untuk apa:** mengisi atas ke bawah, lalu kolom baru.

```css
.hari {
  display: grid;
  grid-auto-flow: column;
  grid-template-rows: repeat(24, 1fr);
}
```

**Biasanya digabungkan dengan:** `grid-auto-columns`, kalender.

### dense

**Untuk apa:** mengisi lubang yang ditinggalkan item yang `span` besar.

```css
.masonry-sederhana {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(10rem, 1fr));
  grid-auto-flow: dense;
}
```

Item kecil bisa “naik” mengisi celah di atas, sehingga urutan visual ≠ DOM. Hati-hati aksesibilitas dan tab order.

**Biasanya digabungkan dengan:** `span` yang bervariasi, gallery.

### row dense / column dense

**Untuk apa:** kombinasi arah + rapat.

```css
grid-auto-flow: row dense;
```

**Biasanya digabungkan dengan:** item `grid-column: span 2`.

## grid shorthand

**Untuk apa:** satu properti untuk template + auto-flow + auto tracks. Sangat padat.

```css
.papan {
  grid: auto-flow dense 8rem / repeat(3, 1fr);
}
```

Artinya: `grid-auto-flow: dense`, `grid-auto-rows: 8rem`, `grid-template-columns: repeat(3, 1fr)`. Mudah salah. Untuk kuliah, tulis properti terpisah.

**Biasanya digabungkan dengan:** prototipe cepat, bukan file tim.

## gap

**Untuk apa:** jarak antar track, tidak di tepi.

```css
.papan { gap: 1rem; }
.papan { row-gap: 1.5rem; column-gap: 1rem; }
.papan { gap: 1.5rem 1rem; }
```

`grid-gap` nama lama, masih jalan, lebih baik `gap`.

**Biasanya digabungkan dengan:** semua grid, `padding` untuk tepi.

## justify-items

**Untuk apa:** meratakan **isi sel** di sumbu inline (kiri-kanan di LTR). Default `stretch`.

### stretch

**Untuk apa:** item melebar mengisi sel.

```css
.papan { justify-items: stretch; }
```

Kartu dan tombol selebar kolom. Paling sering diinginkan.

**Biasanya digabungkan dengan:** `width` anak `auto`.

### start / end / center / left / right

**Untuk apa:** item selebar konten, nempel sisi sel.

```css
.papan { justify-items: center; }
```

Semua kartu di tengah kolomnya. Untuk menengahkan grid **sebagai kelompok** di wadah lebih lebar, pakai `justify-content`.

**Biasanya digabungkan dengan:** ikon dalam sel, bukan kartu yang harus penuh.

## align-items

**Untuk apa:** meratakan isi sel di sumbu block (atas-bawah). Default `stretch`.

```css
.papan { align-items: start; }
.papan { align-items: center; }
.papan { align-items: stretch; }
```

`stretch` membuat kartu dalam satu baris sama tinggi (jika baris lebih tinggi dari konten terpendek). `start` membuat tinggi mengikuti isi — baris tetap setinggi item tertinggi, item pendek tidak meregang.

**Biasanya digabungkan dengan:** `gap`, kartu. Tertukar sering dengan `align-content`.

## place-items

**Untuk apa:** `align-items` + `justify-items`.

```css
.papan { place-items: center; }
.papan { place-items: start stretch; }
```

Satu nilai: keduanya. Dua nilai: block dulu (align), lalu inline (justify).

`place-items: center` menengahkan setiap item di dalam selnya — bukan menengahkan grid di halaman.

**Biasanya digabungkan dengan:** sel yang lebih besar dari item, ikon.

## justify-content

**Untuk apa:** meratakan **seluruh grid** di dalam container jika total lebar track < lebar container.

```css
.papan {
  display: grid;
  grid-template-columns: repeat(3, 10rem);
  justify-content: center;
}
```

Tiga kolom 10rem di wadah 50rem: blok grid di tengah. Nilai: `start`, `end`, `center`, `space-between`, `space-around`, `space-evenly`, `stretch`.

Tidak terlihat jika kolom memakai `1fr` (track sudah makan semua ruang).

**Biasanya digabungkan dengan:** kolom berukuran tetap/`auto`, bukan `1fr`.

## align-content

**Untuk apa:** sama untuk sumbu baris, jika tinggi total track < tinggi container.

```css
.papan {
  min-height: 100dvh;
  align-content: start;
}
```

Tanpa ini, bawaan `stretch` bisa membagi sisa tinggi ke baris. `start` menjaga baris rapat di atas.

**Biasanya digabungkan dengan:** `min-height` besar, gallery.

## place-content

**Untuk apa:** `align-content` + `justify-content`.

```css
.papan { place-content: center; }
.papan { place-content: start center; }
```

**Biasanya digabungkan dengan:** papan yang tidak mengisi viewport.

## justify-self align-self place-self

**Untuk apa:** override per item.

```css
.papan { justify-items: stretch; }

.papan .lencana {
  justify-self: end;
  align-self: start;
}

.papan .ikon {
  place-self: center;
}
```

`place-self: center` = tengah di kedua sumbu sel.

**Biasanya digabungkan dengan:** badge di sel, tombol yang tidak boleh full width.

## grid-column grid-row span

### Nomor garis

**Untuk apa:** menaruh item dari garis ke garis.

```css
.hero {
  grid-column: 1 / 3;
  grid-row: 1 / 2;
}
```

Mulai garis kolom 1, sampai garis 3 (melintasi 2 kolom). `-1` = garis terakhir eksplisit.

```css
.full { grid-column: 1 / -1; }
```

Item selebar semua kolom eksplisit.

**Biasanya digabungkan dengan:** hero, judul section.

### span

**Untuk apa:** “ambillah n track dari posisi otomatis atau awal”.

```css
.lebar { grid-column: span 2; }
.tinggi { grid-row: span 2; }
.kotak { grid-column: span 2; grid-row: span 2; }
```

```css
.mulai-tengah {
  grid-column: 2 / span 2;
}
```

Mulai garis 2, rentang 2 kolom.

**Biasanya digabungkan dengan:** `auto-fit`, featured card.

### grid-column-start / end

**Untuk apa:** bentuk panjang.

```css
.item {
  grid-column-start: 1;
  grid-column-end: 3;
  grid-row-start: auto;
  grid-row-end: span 2;
}
```

`auto` = letakkan sesuai alur.

**Biasanya digabungkan dengan:** `dense` jika banyak span.

## grid-area

**Untuk apa:** satu properti untuk row-start / col-start / row-end / col-end, atau nama area.

```css
.hero { grid-area: hero; }

.item {
  grid-area: 1 / 2 / 3 / 4;
}
```

Urutan angka: **row-start / column-start / row-end / column-end**. Mudah tertukar. Lebih jelas pakai `grid-column` + `grid-row` atau nama area.

**Biasanya digabungkan dengan:** `grid-template-areas`.

## line names

**Untuk apa:** menamai garis agar tidak menghafal nomor.

```css
.halaman {
  display: grid;
  grid-template-columns: [full-start] 1fr [main-start] minmax(0, 70rem) [main-end] 1fr [full-end];
}

.isi { grid-column: main-start / main-end; }
.bleed { grid-column: full-start / full-end; }
```

Gambar full-bleed di artikel: isi di kolom tengah, gambar merentang `full`.

```css
grid-template-columns: repeat(3, [col] 1fr);
```

Menghasilkan nama `col` berulang.

**Biasanya digabungkan dengan:** artikel, `minmax(0, 70rem)`.

## subgrid

**Untuk apa:** grid anak memakai track induk, agar kolom antar kartu sejajar.

```css
.katalog {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 1rem;
}

.kartu {
  display: grid;
  grid-template-rows: subgrid;
  grid-row: span 3;
}
```

Judul, isi, tombol di semua kartu berbagi garis baris yang sama — tombol rata bawah tanpa `margin-top: auto`. Dukungan browser modern sudah baik; uji target tugas.

```css
.kartu {
  display: grid;
  grid-template-columns: subgrid;
  grid-column: span 2;
}
```

Anak mengikuti kolom induk.

**Biasanya digabungkan dengan:** `span`, kartu seragam.

## masonry dan dense

Masonry sejati (`grid-template-rows: masonry`) belum merata di semua browser. Pola yang aman untuk tugas:

```css
.gallery {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(12rem, 1fr));
  grid-auto-flow: dense;
  gap: 0.75rem;
}

.lebar { grid-column: span 2; }
```

Atau kolom CSS:

```css
.masonry {
  column-count: 3;
  column-gap: 1rem;
}
.masonry > * { break-inside: avoid; margin-bottom: 1rem; }
```

`column-count` bukan Grid; urutan atas-bawah per kolom.

**Biasanya digabungkan dengan:** `break-inside: avoid`, media query kurangi kolom.

## Peta Tailwind

| CSS | Tailwind |
| --- | --- |
| `display: grid` | `grid` |
| `inline-grid` | `inline-grid` |
| `grid-template-columns: repeat(3, 1fr)` | `grid-cols-3` |
| `repeat(12, 1fr)` | `grid-cols-12` |
| `none` | `grid-cols-none` |
| `subgrid` | `grid-cols-subgrid` |
| `grid-template-rows: repeat(2, 1fr)` | `grid-rows-2` |
| `grid-auto-flow: row` | `grid-flow-row` |
| `column` | `grid-flow-col` |
| `dense` | `grid-flow-dense` |
| `row dense` | `grid-flow-row-dense` |
| `grid-auto-rows: minmax(0, 1fr)` | `auto-rows-fr` |
| `auto` | `auto-rows-auto` |
| `grid-auto-columns` | `auto-cols-*` |
| `gap: 1rem` | `gap-4` |
| `column-gap` | `gap-x-4` |
| `row-gap` | `gap-y-4` |
| `justify-items: start` | `justify-items-start` |
| `center` | `justify-items-center` |
| `stretch` | `justify-items-stretch` |
| `align-items: start` | `items-start` |
| `place-items: center` | `place-items-center` |
| `justify-content: center` | `justify-center` |
| `align-content: start` | `content-start` |
| `place-content: center` | `place-content-center` |
| `justify-self: end` | `justify-self-end` |
| `align-self: start` | `self-start` |
| `place-self: center` | `place-self-center` |
| `grid-column: span 2` | `col-span-2` |
| `1 / -1` | `col-span-full` |
| `grid-column-start: 2` | `col-start-2` |
| `grid-column-end: 4` | `col-end-4` |
| `grid-row: span 2` | `row-span-2` |
| `grid-row-start` | `row-start-*` |

Arbitrary columns:

```html
<section class="grid grid-cols-1 gap-4 md:grid-cols-2 xl:grid-cols-[16rem_minmax(0,1fr)]">
```

Katalog:

```html
<ul class="grid grid-cols-[repeat(auto-fit,minmax(min(100%,15rem),1fr))] gap-4">
```

**Biasanya digabungkan dengan:** `md:grid-cols-2`, `lg:grid-cols-3`.

## Checklist debug

1. Sudah `display: grid`?
2. Overflow horizontal? Ganti `1fr` jadi `minmax(0, 1fr)`, item `min-width: 0`, gambar `max-w-full`.
3. Satu kartu di desktop selebar halaman? Itu `auto-fit`. Ganti `auto-fill` atau batasi `max-width` kartu.
4. Kartu tidak sama tinggi? `align-items: stretch` (bawaan) + jangan set height anak `fit-content` tanpa alasan.
5. Item tidak di area yang dimaksud? Cek ejaan `grid-area` vs `template-areas`.
6. `justify-content: center` “tidak jalan”? Kolom `1fr` sudah penuh; tengahkan dengan `max-width` + `margin-inline: auto` pada container.
7. HP pecah 3 kolom? Tambah `grid-template-columns: 1fr` dulu, lalu `md:` / media query.
8. Span membuat lubang? `grid-auto-flow: dense` atau terima lubang.
9. Anak wrapper React merusak grid? Wrapper itu yang jadi satu-satunya item. Pakai `display: contents` hati-hati, atau jangan bungkus.
