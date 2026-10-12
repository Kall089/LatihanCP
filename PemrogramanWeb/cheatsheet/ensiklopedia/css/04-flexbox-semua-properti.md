# 04 — Flexbox, semua properti

[← Satuan](03-satuan-sizing-overflow.md) · [Indeks](README.md) · [Grid →](05-grid-semua-properti.md)

Flexbox menyusun **satu arah utama**: baris atau kolom. Pakai ini untuk navbar, baris tombol, ikon + teks, footer yang ke bawah, dan isi kartu. Untuk katalog dua dimensi, pakai [Grid](05-grid-semua-properti.md).

Dua peran: **container** (`display: flex`) dan **item** (anak langsung). Properti container tidak diwariskan ke cucu. Cucu hanya jadi flex item jika induknya sendiri `display: flex`.

## Daftar isi

- [display flex](#display-flex)
- [flex-direction](#flex-direction)
- [flex-wrap](#flex-wrap)
- [flex-flow](#flex-flow)
- [justify-content](#justify-content)
- [align-items](#align-items)
- [align-content](#align-content)
- [align-self](#align-self)
- [place-content](#place-content)
- [place-items](#place-items)
- [place-self](#place-self)
- [gap row-gap column-gap](#gap-row-gap-column-gap)
- [flex-grow](#flex-grow)
- [flex-shrink](#flex-shrink)
- [flex-basis](#flex-basis)
- [flex shorthand](#flex-shorthand)
- [order](#order)
- [min-width 0 pada item](#min-width-0-pada-item)
- [margin auto pada item](#margin-auto-pada-item)
- [absolute di dalam flex](#absolute-di-dalam-flex)
- [Peta Tailwind](#peta-tailwind)
- [Checklist debug](#checklist-debug)

## display flex

**Untuk apa:** mengaktifkan formatting context flex. Anak langsung menjadi flex item.

```css
.baris { display: flex; }
.lencana { display: inline-flex; }
```

`flex`: container block-level (selebar induk). `inline-flex`: selebar isi, duduk di alur teks. Tanpa ini, `justify-content` tidak melakukan apa-apa.

**Biasanya digabungkan dengan:** `align-items`, `gap`, `flex-wrap`.

## flex-direction

Sumbu utama (main axis) mengikuti arah ini. `justify-content` bekerja di sumbu utama. `align-items` bekerja di sumbu silang (cross axis).

### row

**Untuk apa:** kiri ke kanan (di LTR). Bawaan.

```css
.menu {
  display: flex;
  flex-direction: row;
}
```

Main axis horizontal. Cross axis vertikal.

**Biasanya digabungkan dengan:** `align-items: center` untuk navbar.

### row-reverse

**Untuk apa:** membalik urutan visual di sumbu baris.

```css
.aksi {
  display: flex;
  flex-direction: row-reverse;
  gap: 0.5rem;
}
```

Item pertama di DOM tampil di kanan. Tab keyboard tetap mengikuti DOM, bukan visual — hati-hati aksesibilitas. Lebih aman tetap `row` lalu `margin-inline-start: auto` pada grup kanan.

**Biasanya digabungkan dengan:** `gap`, bukan sebagai pengganti urutan HTML.

### column

**Untuk apa:** atas ke bawah. Main axis jadi vertikal.

```css
.form {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.halaman {
  min-height: 100dvh;
  display: flex;
  flex-direction: column;
}
```

`justify-content` sekarang atas-bawah. `align-items` kiri-kanan. `width: 100%` pada anak sering tidak perlu karena `align-items: stretch` (bawaan) meregangkan lebar anak.

**Biasanya digabungkan dengan:** form, stack kartu, `min-height: 100dvh`.

### column-reverse

**Untuk apa:** bawah ke atas secara visual.

```css
.chat {
  display: flex;
  flex-direction: column-reverse;
  overflow: auto;
}
```

Pola chat: pesan terbaru dekat input. DOM tetap atas-ke-bawah; visual terbalik. Uji fokus dan screen reader.

**Biasanya digabungkan dengan:** `overflow: auto`, `flex: 1` pada wadah pesan.

## flex-wrap

### nowrap

**Untuk apa:** paksa satu baris. Bawaan. Item boleh menyusut (`flex-shrink`) sampai batas `min-width`.

```css
.toolbar {
  display: flex;
  flex-wrap: nowrap;
  gap: 0.5rem;
}
```

Di HP toolbar bisa overflow. Tambah `overflow-x: auto` atau ganti `wrap`.

**Biasanya digabungkan dengan:** `flex-shrink`, `min-width: 0`.

### wrap

**Untuk apa:** item pindah ke baris berikutnya jika tidak muat.

```css
.menu {
  display: flex;
  flex-wrap: wrap;
  gap: 0.75rem 1.25rem;
}
```

Setelah wrap, `align-content` mulai berarti (mengatur jarak antar baris).

**Biasanya digabungkan dengan:** `gap`, `justify-content`, chip, tag.

### wrap-reverse

**Untuk apa:** baris tambahan tumbuh ke arah berlawanan cross axis.

```css
.stiker {
  display: flex;
  flex-wrap: wrap-reverse;
}
```

Baris berikutnya muncul di atas (pada `row`). Jarang dibutuhkan.

**Biasanya digabungkan dengan:** UI khusus; uji dulu `wrap` biasa.

## flex-flow

**Untuk apa:** shorthand `flex-direction` + `flex-wrap`.

```css
.stack { flex-flow: column nowrap; }
.chip { flex-flow: row wrap; }
```

Urutan: arah dulu, lalu wrap.

**Biasanya digabungkan dengan:** `gap`, `display: flex`.

## justify-content

Mengatur item di **main axis**. Pada `row`: kiri-kanan. Pada `column`: atas-bawah. Tidak mengatur item di sumbu silang.

### flex-start / start / left

**Untuk apa:** rapatkan ke awal sumbu utama.

```css
.aksi {
  display: flex;
  justify-content: flex-start;
  gap: 0.5rem;
}
```

`flex-start` mengikuti arah flex (terpengaruh `row-reverse`). `start` mengikuti writing mode. `left` fisik ke kiri. Untuk tugas kuliah, `flex-start` dan `start` hampir selalu sama di LTR `row`.

**Biasanya digabungkan dengan:** `gap`, tombol kiri.

### flex-end / end / right

**Untuk apa:** rapatkan ke akhir sumbu utama.

```css
.aksi-kanan {
  display: flex;
  justify-content: flex-end;
  gap: 0.5rem;
}
```

**Biasanya digabungkan dengan:** sepasang tombol Batal/Simpan di kanan.

### center

**Untuk apa:** tengah di sumbu utama.

```css
.hero-aksi {
  display: flex;
  justify-content: center;
  gap: 1rem;
}
```

Untuk tengah horizontal *dan* vertikal di kotak tinggi, tambah `align-items: center` dan tinggi induk.

**Biasanya digabungkan dengan:** `align-items: center`, `min-height`.

### space-between

**Untuk apa:** item pertama di awal, terakhir di akhir, sisa ruang dibagi di antara item. Tidak ada ruang di tepi.

```css
.menu {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
```

Navbar klasik: logo kiri, tautan kanan. Dengan 2 item hasilnya bersih. Dengan 3 item, jarak antar celah sama.

**Biasanya digabungkan dengan:** `align-items: center`, kadang `flex-wrap`.

### space-around

**Untuk apa:** tiap item dapat ruang kiri-kanan yang sama; tepi dapat setengah.

```css
.pager {
  display: flex;
  justify-content: space-around;
}
```

Tepi terlihat lebih rapat daripada tengah. Sering kurang rapi dibanding `space-between` + `padding` atau `gap`.

**Biasanya digabungkan dengan:** pager sederhana; pertimbangkan `gap`.

### space-evenly

**Untuk apa:** jarak antar item dan ke tepi semuanya sama.

```css
.statistik {
  display: flex;
  justify-content: space-evenly;
}
```

**Biasanya digabungkan dengan:** baris 3–4 angka statistik.

### stretch (justify)

**Untuk apa:** pada flex, `justify-content: stretch` tidak meregangkan item seperti Grid. Flex item tidak membesar karena justify; pembesaran pakai `flex-grow`.

```css
.baris { justify-content: stretch; }
```

Aman diabaikan di Flexbox. Pakai `flex: 1` untuk berbagi ruang.

**Biasanya digabungkan dengan:** Grid, bukan Flex.

## align-items

Mengatur item di **cross axis**. Pada `row`: atas-bawah. Pada `column`: kiri-kanan. Bawaan: `stretch`.

### stretch

**Untuk apa:** item meregang mengisi tinggi (atau lebar, jika kolom) container, jika item tidak punya ukuran silang tetap.

```css
.kartu-baris {
  display: flex;
  align-items: stretch;
  gap: 1rem;
}
```

Tiga kartu dalam satu baris jadi sama tinggi. Isi yang lebih pendek tidak “mengambang”.

**Biasanya digabungkan dengan:** `gap`, kartu sejajar.

### flex-start / start / self-start

**Untuk apa:** nempel awal cross axis (atas pada `row`).

```css
.media {
  display: flex;
  align-items: flex-start;
  gap: 0.75rem;
}
```

Gambar dan teks mulai dari atas. Teks panjang tidak membuat gambar ter-stretch aneh jika gambar punya tinggi intrinsik — `stretch` pada img kadang merusak rasio tanpa `align-self`.

**Biasanya digabungkan dengan:** avatar + teks, `gap`.

### flex-end / end / self-end

**Untuk apa:** nempel akhir cross axis (bawah pada `row`).

```css
.meta {
  display: flex;
  align-items: flex-end;
  gap: 0.5rem;
}
```

**Biasanya digabungkan dengan:** angka + satuan, caption.

### center

**Untuk apa:** tengah di cross axis. Paling sering untuk navbar dan tombol ber-ikon.

```css
.tombol {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  gap: 0.4rem;
}
```

Ikon dan label satu garis tengah.

**Biasanya digabungkan dengan:** `justify-content: center`, `gap`.

### baseline / first baseline / last baseline

**Untuk apa:** meratakan garis dasar teks antar item, bukan kotak.

```css
.field-baris {
  display: flex;
  align-items: baseline;
  gap: 0.5rem;
}

label { font-size: 0.875rem; }
input { font-size: 1rem; }
```

Label dan input sebaris teks, meski ukuran huruf beda. `first baseline` / `last baseline` untuk kotak ber-beberapa baris.

**Biasanya digabungkan dengan:** form sebaris, harga + desimal.

## align-content

**Untuk apa:** mengatur **baris-baris** flex (bukan item di dalam satu baris) di cross axis, hanya jika ada sisa ruang dan `flex-wrap` menghasilkan lebih dari satu baris.

```css
.chip-cloud {
  display: flex;
  flex-wrap: wrap;
  align-content: flex-start;
  gap: 0.5rem;
  min-height: 8rem;
}
```

Tanpa wrap atau hanya satu baris, `align-content` seolah tidak jalan. Jangan tertukar dengan `align-items`.

Nilai: `flex-start`, `flex-end`, `center`, `space-between`, `space-around`, `space-evenly`, `stretch`.

`stretch` pada wrap membagi sisa tinggi ke tiap baris.

**Biasanya digabungkan dengan:** `flex-wrap: wrap`, tinggi container tetap.

## align-self

**Untuk apa:** override `align-items` untuk **satu item**.

```css
.media { display: flex; align-items: center; }

.media img {
  align-self: flex-start;
}

.media .spacer { align-self: stretch; }
```

Nilai: `auto` (ikut induk), plus semua nilai `align-items`.

**Biasanya digabungkan dengan:** avatar yang tidak boleh ikut tinggi kartu.

## place-content

**Untuk apa:** shorthand `align-content` + `justify-content`.

```css
.pusat-papan {
  display: flex;
  flex-wrap: wrap;
  place-content: center;
}

.papan {
  display: flex;
  flex-wrap: wrap;
  place-content: start space-between;
}
```

Satu nilai: keduanya. Dua nilai: align-content dulu, lalu justify-content.

**Biasanya digabungkan dengan:** flex wrap atau Grid. Lebih sering terlihat di Grid.

## place-items

**Untuk apa:** shorthand `align-items` + `justify-items`. Pada Flexbox, `justify-items` diabaikan, jadi praktis hanya `align-items`.

```css
.baris {
  display: flex;
  place-items: center;
}
```

Di Flex, tulis saja `align-items`. Di Grid, `place-items` sangat berguna.

**Biasanya digabungkan dengan:** Grid lebih daripada Flex.

## place-self

**Untuk apa:** shorthand `align-self` + `justify-self`. Pada Flex, `justify-self` tidak berlaku; item tidak bisa “self-justify” di main axis (kecuali margin auto).

```css
.item { place-self: center; }
```

Di Flex, ini praktis `align-self`. Di Grid, keduanya hidup.

**Biasanya digabungkan dengan:** Grid item, atau `align-self` di Flex.

## gap row-gap column-gap

**Untuk apa:** jarak antar item, tanpa margin collapse dan tanpa margin pada item terakhir.

```css
.menu {
  display: flex;
  gap: 1rem;
}

.chip {
  display: flex;
  flex-wrap: wrap;
  row-gap: 0.5rem;
  column-gap: 0.75rem;
}

.chip {
  gap: 0.5rem 0.75rem;
}
```

Shorthand `gap: baris kolom` saat wrap/grid. `gap` tidak menambah jarak di tepi container — itu tugas `padding`.

Jangan campur `gap` besar dan `margin` pada semua anak; jarak jadi dobel.

**Biasanya digabungkan dengan:** semua flex container modern. Pengganti `margin-right` pada `li + li`.

## flex-grow

**Untuk apa:** faktor pertumbuhan jika ada **sisa ruang** di main axis. Bawaan `0` (tidak tumbuh).

```css
.cari { flex-grow: 1; }
.logo { flex-grow: 0; }

.kolom-kiri { flex-grow: 1; }
.kolom-kanan { flex-grow: 2; }
```

Sisa ruang dibagi menurut rasio. `1` dan `2` berarti kanan dapat dua kali porsi sisa, bukan dua kali lebar total.

`flex-grow` tidak sendirian: `flex-basis` menentukan ukuran awal sebelum sisa dibagi.

**Biasanya digabungkan dengan:** `flex-shrink`, `flex-basis` atau shorthand `flex: 1`.

## flex-shrink

**Untuk apa:** faktor penyusutan jika item **tidak muat**. Bawaan `1` (boleh susut).

```css
.judul { flex-shrink: 1; min-width: 0; }
.ikon { flex-shrink: 0; }
```

Ikon 24px tidak ikut gepeng. Judul boleh susut + ellipsis. `flex-shrink: 0` pada banyak item = overflow horizontal.

**Biasanya digabungkan dengan:** `min-width: 0`, `flex-basis`, `text-overflow`.

## flex-basis

**Untuk apa:** ukuran awal item **sebelum** grow/shrink, di main axis. Bawaan `auto`.

```css
.sidebar { flex-basis: 16rem; }
.isi { flex-basis: 0; flex-grow: 1; }
.foto { flex-basis: 30%; }
```

- `auto`: pakai `width`/`height` jika ada, else ukuran konten.
- `0` atau `0%`: mulai dari nol, lalu grow membagi rata lebih adil.
- Panjang (`16rem`, `%`): target awal.

`flex-basis` mengalahkan `width` pada `row` (kecuali `auto` + width). Lebih jelas set basis daripada campur `width` + `flex`.

**Biasanya digabungkan dengan:** `flex-grow`, `flex-shrink`, `min-width: 0`.

## flex shorthand

**Untuk apa:** menulis grow, shrink, basis sekaligus. Ini cara yang disarankan.

### flex: initial

**Untuk apa:** `0 1 auto`. Tidak tumbuh, boleh susut, basis = ukuran konten/`width`. Sama seperti bawaan.

```css
.item { flex: initial; }
```

**Biasanya digabungkan dengan:** reset item yang sempat `flex: 1`.

### flex: auto

**Untuk apa:** `1 1 auto`. Tumbuh dan susut, basis konten.

```css
.isi { flex: auto; }
```

Item besar (gambar lebar) mulai lebih besar lalu berbagi sisa.

**Biasanya digabungkan dengan:** sidebar berukuran konten + isi yang mekar.

### flex: none

**Untuk apa:** `0 0 auto`. Tidak tumbuh, tidak susut.

```css
.tombol { flex: none; }
.avatar { flex: none; }
```

Ukuran mengikuti konten. Aman untuk tombol dan ikon.

**Biasanya digabungkan dengan:** `gap`, `align-items: center`.

### flex: 1

**Untuk apa:** `1 1 0%` di banyak browser (atau `1 1 0`). Tumbuh, susut, basis nol.

```css
.kolom { flex: 1; min-width: 0; }

.halaman { display: flex; flex-direction: column; min-height: 100dvh; }
.halaman main { flex: 1; }
```

Dua anak `flex: 1` berbagi rata. `main { flex: 1 }` mendorong footer ke bawah.

**Biasanya digabungkan dengan:** `min-width: 0` / `min-height: 0`.

### flex: 1 1 16rem

**Untuk apa:** basis 16rem, boleh tumbuh dan susut.

```css
.kartu {
  flex: 1 1 16rem;
}
```

Kartu di baris wrap: minimal “ingin” 16rem, sisa ruang dibagi.

**Biasanya digabungkan dengan:** `flex-wrap: wrap`, `gap`.

### Urutan nilai flex

```css
.item { flex: 1; }           /* grow saja, sisanya default */
.item { flex: 1 0; }         /* grow shrink, basis 0% */
.item { flex: 1 0 12rem; }   /* grow shrink basis */
.item { flex: 12rem; }       /* basis 12rem, grow 1 di beberapa parser — hindari; tulis lengkap */
```

Tulis tiga nilai jika ragu: `flex: grow shrink basis`.

**Biasanya digabungkan dengan:** container `display: flex`.

## order

**Untuk apa:** urutan visual. Bawaan `0`. Angka lebih kecil tampil lebih dulu.

```css
.menu-cari { order: -1; }
.menu-logo { order: 0; }
.menu-aksi { order: 1; }
```

Tidak mengubah urutan tab atau screen reader. Jangan pakai `order` untuk memindahkan tombol penting ke kanan; ubah HTML atau pakai `margin-inline-start: auto`.

```css
@media (max-width: 40rem) {
  .sidebar { order: 2; }
  .konten { order: 1; }
}
```

Di HP konten dulu, sidebar belakangan secara visual — tetap uji aksesibilitas.

**Biasanya digabungkan dengan:** media query; hindari sebagai layout utama.

## min-width 0 pada item

**Untuk apa:** mengizinkan item lebih sempit dari kontennya.

```css
.item-teks {
  flex: 1;
  min-width: 0;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}
```

Tanpa `min-width: 0`, flex item menolak menyusut di bawah `min-content` (kata terpanjang / gambar). Ellipsis tidak pernah muncul.

Pada `flex-direction: column`, analoginya `min-height: 0` agar anak bisa scroll.

**Biasanya digabungkan dengan:** `flex: 1`, `overflow`, `text-overflow`.

## margin auto pada item

**Untuk apa:** “makan” sisa ruang di main axis, pengganti `justify-self` yang tidak ada di Flex.

```css
.menu {
  display: flex;
  align-items: center;
  gap: 1rem;
}

.menu .aksi {
  margin-inline-start: auto;
}
```

Semua item di kiri, grup `.aksi` terdorong ke kanan. Bisa beberapa `margin: auto` untuk membagi ruang.

```css
.pusat-trik {
  display: flex;
}
.pusat-trik .item {
  margin: auto;
}
```

Item tunggal di tengah horizontal dan vertikal jika container punya tinggi.

**Biasanya digabungkan dengan:** navbar, `align-items: center`, `gap` pada grup kiri.

## absolute di dalam flex

**Untuk apa:** item `position: absolute` tidak ikut sebagai flex item biasa (tidak makan `gap` di beberapa kasus / keluar alur).

```css
.kartu {
  display: flex;
  position: relative;
}

.kartu .tutup {
  position: absolute;
  top: 0.5rem;
  right: 0.5rem;
}
```

Tombol tutup tidak mendorong isi. Container perlu `position: relative`.

**Biasanya digabungkan dengan:** [bab 08](08-position-zindex-float-sticky.md).

## Peta Tailwind

| CSS | Tailwind |
| --- | --- |
| `display: flex` | `flex` |
| `inline-flex` | `inline-flex` |
| `flex-direction: row` | `flex-row` |
| `column` | `flex-col` |
| `row-reverse` | `flex-row-reverse` |
| `column-reverse` | `flex-col-reverse` |
| `flex-wrap: wrap` | `flex-wrap` |
| `nowrap` | `flex-nowrap` |
| `wrap-reverse` | `flex-wrap-reverse` |
| `justify-content: flex-start` | `justify-start` |
| `flex-end` | `justify-end` |
| `center` | `justify-center` |
| `space-between` | `justify-between` |
| `space-around` | `justify-around` |
| `space-evenly` | `justify-evenly` |
| `align-items: flex-start` | `items-start` |
| `flex-end` | `items-end` |
| `center` | `items-center` |
| `baseline` | `items-baseline` |
| `stretch` | `items-stretch` |
| `align-content: center` | `content-center` |
| `flex-start` | `content-start` |
| `space-between` | `content-between` |
| `align-self: center` | `self-center` |
| `flex-start` | `self-start` |
| `stretch` | `self-stretch` |
| `gap: 1rem` | `gap-4` |
| `row-gap` | `gap-y-4` |
| `column-gap` | `gap-x-4` |
| `flex: 1 1 0%` | `flex-1` |
| `flex: auto` | `flex-auto` |
| `flex: none` | `flex-none` |
| `flex-grow: 1` | `grow` |
| `flex-grow: 0` | `grow-0` |
| `flex-shrink: 1` | `shrink` |
| `flex-shrink: 0` | `shrink-0` |
| `flex-basis: 0` | `basis-0` |
| `flex-basis: 16rem` | `basis-64` |
| `order: 1` | `order-1` |
| `order: -1` | `-order-1` |

Contoh navbar:

```html
<nav class="flex flex-wrap items-center justify-between gap-4">
  <a class="font-semibold" href="/">Toko</a>
  <div class="flex items-center gap-3">
    <a href="/produk">Produk</a>
    <a class="flex-none" href="/masuk">Masuk</a>
  </div>
</nav>
```

**Biasanya digabungkan dengan:** `md:flex-row` jika di HP `flex-col`.

## Checklist debug

1. Induk sudah `display: flex`?
2. Arahnya `row` atau `column`? `justify-*` mengikuti arah.
3. Tidak rata vertikal? Cek `align-items`, bukan `justify-content` (kecuali `column`).
4. Item tidak sama lebar? `flex: 1` + `min-width: 0`.
5. Ellipsis mogok? `min-width: 0; overflow: hidden; white-space: nowrap; text-overflow: ellipsis`.
6. Jarak dobel? Hapus margin anak, pakai `gap`.
7. Anak tidak 100% lebar di kolom? Bawaan `stretch` harusnya sudah; cek `align-items` yang kamu set `center`.
8. Footer tidak ke bawah? Halaman `flex-col min-h-dvh`, `main` `flex-1`.
