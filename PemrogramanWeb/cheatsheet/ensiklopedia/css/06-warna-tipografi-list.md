# 06 — Warna, tipografi, list

[← Grid](05-grid-semua-properti.md) · [Indeks](README.md) · [Background →](07-background-border-outline-shadow.md)

Teks yang tidak kebaca atau hierarki yang datar membuat halaman terasa “belum selesai”, meski layoutnya benar. Bagian ini membedah warna, font, dan daftar.

## Daftar isi

- [Menulis warna](#menulis-warna)
- [color dan currentColor](#color-dan-currentcolor)
- [opacity vs alpha](#opacity-vs-alpha)
- [color-scheme dan light-dark](#color-scheme-dan-light-dark)
- [font-family](#font-family)
- [font-size](#font-size)
- [font-weight font-style font-stretch](#font-weight-font-style-font-stretch)
- [font-variation-settings](#font-variation-settings)
- [line-height](#line-height)
- [letter-spacing word-spacing](#letter-spacing-word-spacing)
- [text-align text-indent](#text-align-text-indent)
- [text-decoration](#text-decoration)
- [text-transform](#text-transform)
- [text-underline-offset](#text-underline-offset)
- [white-space overflow-wrap](#white-space-overflow-wrap)
- [vertical-align](#vertical-align)
- [font shorthand](#font-shorthand)
- [@font-face dan font-display](#font-face-dan-font-display)
- [list-style](#list-style)
- [quotes](#quotes)
- [tab-size](#tab-size)
- [caret-color accent-color](#caret-color-accent-color)
- [Kontras](#kontras)

## Menulis warna

**Untuk apa:** menyatakan warna yang dimengerti browser.

```css
.judul { color: #0f172a; }
.judul { color: #0f172add; }
.muted { color: rgb(51 65 85 / 0.85); }
.muted { color: hsl(215 16% 27%); }
.link { color: hsl(215 80% 40% / 0.9); }
.oklch { color: oklch(55% 0.12 250); }
.nama { color: crimson; }
.transparan { color: transparent; }
```

- Hex 6 digit: `#rrggbb`. 8 digit: plus alpha.
- `rgb(r g b / a)` sintaks modern (spasi, bukan koma). Bentuk lama `rgb(r, g, b)` masih valid.
- `hsl(h s% l% / a)`: hue 0–360, saturasi dan lightness persen. Enak untuk tema.
- `oklch`: lebih merata secara persepsi; bagus untuk skala warna, dukungan modern.
- Keyword: `transparent`, `currentColor`, nama CSS.

Jangan andalkan `darkblue` versus hex desain; pilih palet lalu tempel konsisten.

**Biasanya digabungkan dengan:** custom property `--warna-teks`, Tailwind `slate/red/...`.

## color dan currentColor

**Untuk apa:** `color` mewarnai teks dan mewariskan. `currentColor` = nilai `color` elemen itu.

```css
.kartu {
  color: #0f172a;
}

.kartu svg {
  stroke: currentColor;
}

.kartu hr {
  border-color: currentColor;
  opacity: 0.2;
}
```

Ikon SVG ikut warna teks. Saat `.kartu--gelap { color: white; }`, ikon ikut putih.

**Biasanya digabungkan dengan:** `border-color`, `box-shadow`, `fill`/`stroke`.

## opacity vs alpha

**Untuk apa:** membedakan transparan seluruh kotak versus transparan warna saja.

```css
.lemah { opacity: 0.5; }
.teks-lemah { color: rgb(15 23 42 / 0.5); }
.latar-lemah { background: rgb(15 23 42 / 0.5); }
```

`opacity` memengaruhi teks, border, anak, dan membuat stacking context. Alpha pada `color` hanya teks. Anak `opacity` tidak bisa “lebih solid” dari induk.

**Biasanya digabungkan dengan:** `disabled`, overlay, bukan untuk meniru abu-abu teks (lebih baik warna solid kontras).

## color-scheme dan light-dark

**Untuk apa:** memberitahu browser agar scrollbar, form native, dan `canvas` mengikuti tema.

```css
:root { color-scheme: light dark; }

body {
  color: light-dark(#0f172a, #e2e8f0);
  background: light-dark(#f8fafc, #0b1220);
}
```

`light-dark()` memilih nilai pertama di skema terang, kedua di gelap. Butuh `color-scheme` yang mengizinkan keduanya.

**Biasanya digabungkan dengan:** `prefers-color-scheme`, custom property.

## font-family

**Untuk apa:** tumpukan font. Browser memakai yang pertama tersedia.

```css
body {
  font-family: system-ui, "Segoe UI", Roboto, sans-serif;
}

.prosa {
  font-family: Georgia, "Times New Roman", serif;
}

.kode {
  font-family: ui-monospace, SFMono-Regular, Menlo, Consolas, monospace;
}
```

Selalu akhiri dengan generic: `serif`, `sans-serif`, `monospace`, `system-ui`. Nama berkspasi wajib dikutip.

`system-ui` mengikuti OS: cepat, familiar, tidak perlu unduh.

**Biasanya digabungkan dengan:** `font-size`, `line-height`, `@font-face`.

## font-size

**Untuk apa:** ukuran huruf. Lebih aman `rem` daripada `px` untuk teks bacaan.

```css
html { font-size: 100%; }

body { font-size: 1rem; }
small, .meta { font-size: 0.875rem; }
h1 { font-size: clamp(1.75rem, 1rem + 2vw, 3rem); }
```

Skala tipikal: 0.75 / 0.875 / 1 / 1.125 / 1.25 / 1.5 / 1.875 / 2.25 rem.

`font-size: 0` kadang dipakai menghapus celah inline-block; lebih baik Flex.

**Biasanya digabungkan dengan:** `line-height`, `clamp`, `max-width: 65ch`.

## font-weight font-style font-stretch

### font-weight

**Untuk apa:** ketebalan. Angka 100–900 atau keyword.

```css
.badan { font-weight: 400; }
.tebal { font-weight: 700; }
.medium { font-weight: 500; }
b, strong { font-weight: 700; }
```

`bold` = 700, `normal` = 400. Kalau font variable, 450 juga valid. Kalau font statis hanya punya 400 dan 700, `500` bisa diemulasikan jelek (synthetic bold).

**Biasanya digabungkan dengan:** `font-family` yang memang punya file weight itu.

### font-style

**Untuk apa:** `normal`, `italic`, `oblique`.

```css
em, .kutip { font-style: italic; }
```

Jika file italic tidak ada, browser miringkan sintetis. Kurang rapi.

**Biasanya digabungkan dengan:** `em`, kutipan, bukan untuk seluruh paragraf panjang.

### font-stretch / font-width

**Untuk apa:** condensed/expanded pada keluarga yang mendukung.

```css
.sempit { font-stretch: condensed; }
.sempit { font-width: 87.5%; }
```

**Biasanya digabungkan dengan:** font variable width.

## font-variation-settings

**Untuk apa:** sumbu mentah font variable (`wght`, `opsz`, `SOFT`, …).

```css
.judul {
  font-variation-settings: "wght" 650, "opsz" 32;
}
```

Lebih baik properti native (`font-weight`, `font-optical-sizing`) jika ada, agar pewarisan tidak aneh.

**Biasanya digabungkan dengan:** font variable yang kamu host.

## line-height

**Untuk apa:** tinggi kotak baris. Tanpa satuan = kelipatan `font-size` elemen; ini yang disarankan.

```css
body { line-height: 1.6; }
h1, h2 { line-height: 1.2; }
.rapat { line-height: 1; }
```

`line-height: 24px` kaku saat font membesar. `1.5` pada body, `1.1–1.25` pada judul besar.

`line-height` diwariskan sebagai angka jika kamu memakai unitless — anak dengan font lebih besar tetap proporsional. Jika induk `line-height: 24px`, anak mewarisi 24px kaku.

**Biasanya digabungkan dengan:** `font-size`, `max-width: 65ch`.

## letter-spacing word-spacing

**Untuk apa:** jarak antar huruf / kata.

```css
.label {
  letter-spacing: 0.08em;
  text-transform: uppercase;
}

.lebar { letter-spacing: 0.02em; }
.rapat { letter-spacing: -0.02em; }
```

Huruf kapital kecil (label) sering butuh spacing positif. Judul display kadang sedikit negatif. Jangan berlebihan.

**Biasanya digabungkan dengan:** `text-transform: uppercase`, `font-weight`.

## text-align text-indent

### text-align

**Untuk apa:** meratakan **teks dalam block**, bukan meratakan kotak di halaman.

```css
.prosa { text-align: start; }
.kutipan { text-align: justify; }
.angka { text-align: end; }
.hero h1 { text-align: center; }
```

`justify` merapikan kiri-kanan; di baris pendek (HP) bisa jelek (sungai spasi). `start`/`end` mengikuti arah tulisan.

`text-align: center` pada flex container tidak menengahkan flex item; itu tetap `justify-content`.

**Biasanya digabungkan dengan:** `max-width` prosa, tabel angka.

### text-indent

**Untuk apa:** menjorok baris pertama.

```css
.paragraf { text-indent: 1.5em; }
```

**Biasanya digabungkan dengan:** artikel panjang, bukan UI.

## text-decoration

**Untuk apa:** garis bawah, coret, atas.

```css
a { text-decoration: underline; }
a:hover { text-decoration-thickness: 0.12em; }

.habis { text-decoration: line-through; color: #64748b; }

.tautan {
  text-decoration-line: underline;
  text-decoration-style: solid;
  text-decoration-color: currentColor;
  text-decoration-thickness: from-font;
  text-underline-offset: 0.2em;
}
```

Shorthand: `text-decoration: underline 0.1em #0ea5e9`.

`none` pada tautan menghilangkan petunjuk visual — sediakan cara lain (warna + hover + fokus).

**Biasanya digabungkan dengan:** `:hover`, `:focus-visible`, `text-underline-offset`.

## text-transform

**Untuk apa:** mengubah tampilan kapital tanpa mengubah teks di HTML.

```css
.label { text-transform: uppercase; }
.judul { text-transform: capitalize; }
.kode { text-transform: none; }
```

Screen reader biasanya tetap membaca teks asli. Untuk singkatan, lebih baik tulis benar di HTML.

**Biasanya digabungkan dengan:** `letter-spacing`, `font-size` lebih kecil.

## text-underline-offset

**Untuk apa:** menjauhkan garis bawah dari glif.

```css
a {
  text-underline-offset: 0.18em;
  text-decoration-thickness: 0.08em;
}
```

Mengurangi tabrakan dengan huruf `g` `y` `j`.

**Biasanya digabungkan dengan:** `text-decoration`, hover.

## white-space overflow-wrap

Lihat [bab 03](03-satuan-sizing-overflow.md) untuk katalog penuh. Ringkas tipografi:

```css
.prosa { overflow-wrap: anywhere; }
.judul-kartu {
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}
```

**Biasanya digabungkan dengan:** `min-width: 0` di flex/grid.

## vertical-align

**Untuk apa:** meratakan elemen **inline atau table-cell** terhadap baris. Tidak bekerja pada flex/grid item.

```css
img.ikon { vertical-align: middle; }
sup { vertical-align: super; font-size: 0.75em; }
td.angka { vertical-align: middle; }
```

Nilai: `baseline`, `middle`, `top`, `bottom`, `sub`, `super`, `text-top`, `text-bottom`, panjang.

Untuk ikon di tombol, `inline-flex` + `align-items: center` lebih dapat diandalkan.

**Biasanya digabungkan dengan:** tabel, `sup`/`sub`, img sebaris.

## font shorthand

**Untuk apa:** satu baris font. **Wajib** menyertakan `font-size` dan `font-family`. Reset beberapa properti font lain ke initial.

```css
.kode {
  font: 500 0.9rem/1.5 ui-monospace, monospace;
}
```

Urutan umum: `style weight size/line-height family`.

```css
.system { font: menu; }
```

Keyword sistem (`menu`, `caption`) memakai font UI OS. Jarang di web app modern.

**Biasanya digabungkan dengan:** komponen kecil; hindari di `body` jika kamu juga set `font-stretch` dll.

## @font-face dan font-display

**Untuk apa:** mendaftarkan file font.

```css
@font-face {
  font-family: "Sumber Sans";
  src: url("/fonts/sumber.woff2") format("woff2");
  font-weight: 400 700;
  font-style: normal;
  font-display: swap;
  unicode-range: U+0000-00FF;
}
```

`font-display: swap` tampilkan fallback dulu (bisa FOUC). `optional` batal unduh jika lambat. `woff2` cukup untuk browser modern.

**Biasanya digabungkan dengan:** `preconnect` ke host font, `font-family` stack.

## list-style

### list-style-type

**Untuk apa:** bentuk marker.

```css
ul { list-style-type: disc; }
ul.kosong { list-style-type: none; }
ol { list-style-type: decimal; }
ol.latin { list-style-type: lower-alpha; }
ol.romawi { list-style-type: upper-roman; }
```

Nilai lain: `circle`, `square`, `decimal-leading-zero`, `disclosure-closed`.

**Biasanya digabungkan dengan:** `padding-inline-start`, `::marker`.

### list-style-position

**Untuk apa:** marker di dalam atau di luar kotak.

```css
li { list-style-position: outside; }
.rapat { list-style-position: inside; }
```

`outside` (bawaan) marker di padding. `inside` marker ikut baris pertama teks.

**Biasanya digabungkan dengan:** `padding-inline-start: 1.25rem` pada `ul`.

### list-style-image

**Untuk apa:** gambar sebagai marker. Sulit dikontrol; lebih baik `::marker` atau flex + ikon.

```css
ul { list-style-image: url("/dot.svg"); }
```

**Biasanya digabungkan dengan:** jarang; prefer custom.

### list-style shorthand

```css
ul { list-style: none; }
ol { list-style: decimal outside; }
```

Nav dan kartu yang kebetulan `<ul>` hampir selalu `list-style: none` + reset padding.

**Biasanya digabungkan dengan:** `display: flex` pada menu.

### ::marker

**Untuk apa:** mewarnai atau mengubah font marker.

```css
li::marker {
  color: #0f766e;
  font-weight: 700;
}
```

Tidak semua properti boleh di `::marker` (margin/padding terbatas).

**Biasanya digabungkan dengan:** `ol`, langkah tutorial.

## quotes

**Untuk apa:** karakter kutipan untuk `q` dan `quotes`.

```css
:lang(id) { quotes: "“" "”" "‘" "’"; }

q::before { content: open-quote; }
q::after { content: close-quote; }
```

**Biasanya digabungkan dengan:** `<q>`, `lang`.

## tab-size

**Untuk apa:** lebar tab di `pre`.

```css
pre { tab-size: 2; }
```

**Biasanya digabungkan dengan:** `white-space: pre`, `overflow-x: auto`.

## caret-color accent-color

**Untuk apa:** `caret-color` = kursor ketik. `accent-color` = checkbox, radio, range native.

```css
input { caret-color: #0f766e; }
input[type="checkbox"] { accent-color: #0f766e; }
```

Tidak mengganti seluruh desain form, hanya aksen native.

**Biasanya digabungkan dengan:** `:focus-visible`, token warna merek.

## Kontras

**Untuk apa:** memastikan teks terbaca, termasuk outdoor dan mode terang.

```css
.bahaya {
  background: #7f1d1d;
  color: #fff7ed;
}

.lemah-salah {
  background: #fff;
  color: #cbd5e1;
}
```

Abu muda di putih gagal kontras. Target kasar WCAG AA: 4.5:1 untuk teks biasa, 3:1 untuk teks besar. Jangan andalkan warna saja untuk error (tambah ikon/teks).

**Biasanya digabungkan dengan:** `focus-visible` ring, pengujian DevTools / extension kontras.
