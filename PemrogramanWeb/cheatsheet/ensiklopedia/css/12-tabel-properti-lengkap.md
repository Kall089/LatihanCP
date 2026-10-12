# 12 — Tabel properti CSS umum

[← Media](11-media-query-container-layer.md) · [Indeks](README.md) · [Tailwind →](13-tailwind-utility-lengkap.md)

Katalog cepat: nama, untuk apa, nilai yang paling sering, pasangan tipikal. Bukan semua properti CSS yang pernah ada; ini yang muncul di tugas web dan proyek kuliah. Detail panjang ada di bab khusus.

Format tiap blok tetap sama: **untuk apa**, kode, penjelasan, **biasanya digabung dengan**.

## Cara pakai tabel

Cari nama properti (Ctrl+F). Kalau kamu ingat gejalanya (“teks keluar kartu”) lebih cepat buka [bab 14](14-resep-dan-kesalahan.md).

Nilai `inherit / initial / unset / revert` berlaku di hampir semua properti; tidak diulang di setiap baris.

## Layout dan kotak

### display

**Untuk apa:** model kotak dan apakah anak disusun flex/grid.

```css
.el { display: block; }
.el { display: flex; }
.el { display: none; }
```

Nilai umum: `block | inline | inline-block | none | flex | inline-flex | grid | inline-grid | contents | flow-root | list-item`.

**Biasanya digabungkan dengan:** `gap`, `width`, properti flex/grid.

### box-sizing

**Untuk apa:** apakah `width` termasuk padding dan border.

```css
* { box-sizing: border-box; }
```

Nilai: `content-box | border-box`.

**Biasanya digabungkan dengan:** `width: 100%`, `padding`, `border`.

### width / height / inline-size / block-size

**Untuk apa:** ukuran kotak.

```css
.box { width: min(100%, 40rem); height: auto; }
```

Nilai umum: `auto | 100% | 16rem | fit-content | min-content | max-content | stretch`.

**Biasanya digabungkan dengan:** `max-width`, `min-width: 0`, `box-sizing`.

### min-width / max-width / min-height / max-height

**Untuk apa:** batas ukuran, bukan ukuran tepat.

```css
.prosa { max-width: 65ch; }
.item { min-width: 0; }
.hero { min-height: 100dvh; }
```

**Biasanya digabungkan dengan:** `overflow`, flex/grid item.

### aspect-ratio

**Untuk apa:** rasio lebar terhadap tinggi.

```css
.thumb { aspect-ratio: 16 / 9; }
```

Nilai: `auto | 1 | 16 / 9 | 4 / 3`.

**Biasanya digabungkan dengan:** `object-fit`, `width: 100%`.

### padding / padding-*

**Untuk apa:** ruang dalam, ikut latar.

```css
.kartu { padding: 1rem 1.25rem; }
.kartu { padding-inline: 1.25rem; padding-block: 1rem; }
```

**Biasanya digabungkan dengan:** `background`, `border`, `border-radius`.

### margin / margin-*

**Untuk apa:** ruang luar, tidak dicat latar.

```css
.tengah { margin-inline: auto; }
.stack > * + * { margin-top: 0.75rem; }
```

**Biasanya digabungkan dengan:** `width` terbatas, atau diganti `gap` di flex/grid.

### overflow / overflow-x / overflow-y

**Untuk apa:** potong atau scroll konten berlebih.

```css
.daftar { overflow: auto; }
.kartu { overflow: hidden; }
```

Nilai: `visible | hidden | clip | scroll | auto`.

**Biasanya digabungkan dengan:** `max-height`, `border-radius`, `text-overflow`.

### overflow-wrap / word-break / hyphens

**Untuk apa:** memecah kata panjang.

```css
.kartu { overflow-wrap: anywhere; }
```

**Biasanya digabungkan dengan:** `min-width: 0`, `lang`.

### object-fit / object-position

**Untuk apa:** isi img/video dalam kotak tetap.

```css
img { object-fit: cover; object-position: center; }
```

Nilai fit: `contain | cover | fill | none | scale-down`.

**Biasanya digabungkan dengan:** `aspect-ratio`, `width/height`.

### vertical-align

**Untuk apa:** inline dan sel tabel.

```css
td { vertical-align: middle; }
```

**Biasanya digabungkan dengan:** `table-cell`, bukan flex.

### isolation

**Untuk apa:** stacking context baru.

```css
.kartu { isolation: isolate; }
```

**Biasanya digabungkan dengan:** `z-index` anak, overlay.

### contain / content-visibility / contain-intrinsic-size

**Untuk apa:** batasi pengaruh layout/cat, tunda render.

```css
.feed > * { content-visibility: auto; contain-intrinsic-size: auto 16rem; }
```

**Biasanya digabungkan dengan:** daftar panjang.

### resize

**Untuk apa:** pegangan ubah ukuran.

```css
textarea { resize: vertical; }
```

**Biasanya digabungkan dengan:** `overflow`, `min-height`.

### visibility

**Untuk apa:** sembunyi tetapi ruang tetap.

```css
.x { visibility: hidden; }
```

**Biasanya digabungkan dengan:** skeleton, bukan hamburger (itu `display`).

### opacity

**Untuk apa:** transparan seluruh subtree.

```css
.habis { opacity: 0.55; }
```

**Biasanya digabungkan dengan:** `transition`, `pointer-events`.

## Flexbox (ringkas)

Lihat katalog penuh [bab 04](04-flexbox-semua-properti.md).

| Properti | Untuk apa | Nilai umum | Digabung dengan |
| --- | --- | --- | --- |
| `flex-direction` | arah main axis | `row`, `column`, `*-reverse` | `justify-content` |
| `flex-wrap` | turun baris | `nowrap`, `wrap` | `align-content`, `gap` |
| `flex-flow` | direction+wrap | `column wrap` | `gap` |
| `justify-content` | main axis | `flex-start`, `center`, `space-between`, `space-evenly` | `gap` |
| `align-items` | cross axis | `stretch`, `center`, `flex-start`, `baseline` | `min-height` |
| `align-content` | antar baris wrap | `flex-start`, `space-between` | `flex-wrap` |
| `align-self` | override satu item | `auto`, `center`, `flex-start` | `align-items` induk |
| `place-content` | align-content + justify-content | `center`, `start space-between` | wrap/grid |
| `place-items` | align-items + justify-items | `center` | lebih berguna di grid |
| `place-self` | self dua sumbu | `center` | grid item |
| `gap` | jarak antar item | `0.5rem`, `1rem 1.5rem` | `padding` tepi |
| `flex-grow` | makan sisa | `0`, `1` | `flex-basis` |
| `flex-shrink` | boleh susut | `1`, `0` | `min-width: 0` |
| `flex-basis` | ukuran awal | `auto`, `0`, `16rem` | `flex-grow` |
| `flex` | grow shrink basis | `1`, `none`, `1 1 16rem` | `min-width: 0` |
| `order` | urutan visual | `0`, `-1`, `2` | media query; hati-hati a11y |

### flex

**Untuk apa:** shorthand item.

```css
.isi { flex: 1; min-width: 0; }
.tombol { flex: none; }
```

**Biasanya digabungkan dengan:** container `display: flex`.

## Grid (ringkas)

Lihat [bab 05](05-grid-semua-properti.md).

| Properti | Untuk apa | Nilai umum | Digabung dengan |
| --- | --- | --- | --- |
| `grid-template-columns` | kolom | `1fr 1fr`, `repeat(auto-fit, minmax(min(100%,15rem),1fr))` | `gap` |
| `grid-template-rows` | baris | `auto 1fr auto` | `min-height: 100dvh` |
| `grid-template-areas` | peta nama | `"nav nav" "side main"` | `grid-area` |
| `grid-template` | rows/areas/cols | lihat bab 05 | `gap` |
| `grid-auto-flow` | arah isi + dense | `row`, `column`, `dense` | `span` |
| `grid-auto-columns` | track implisit | `minmax(12rem, 20rem)` | `auto-flow: column` |
| `grid-auto-rows` | baris implisit | `minmax(8rem, auto)` | gallery |
| `grid` | shorthand padat | hindari di tugas | — |
| `grid-column` | rentang kolom | `1 / -1`, `span 2`, `2 / 4` | hero |
| `grid-row` | rentang baris | `span 2` | featured |
| `grid-area` | nama atau 4 garis | `hero`, `1 / 2 / 3 / 4` | template-areas |
| `justify-items` | isi sel inline | `stretch`, `center`, `start` | kartu vs ikon |
| `align-items` | isi sel block | `stretch`, `start` | tinggi kartu |
| `place-items` | keduanya | `center`, `start stretch` | |
| `justify-content` | grid di wadah | `center`, `space-between` | kolom tetap, bukan `1fr` |
| `align-content` | baris di wadah | `start`, `center` | `min-height` besar |
| `place-content` | keduanya | `center` | |
| `justify-self` | satu item inline | `end`, `center` | badge |
| `align-self` | satu item block | `start` | |
| `place-self` | keduanya | `center` | |

### grid-template-columns

**Untuk apa:** resep kolom.

```css
.katalog {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(min(100%, 15rem), 1fr));
}
```

**Biasanya digabungkan dengan:** `gap`, media query opsional.

## Position dan urutan cat

### position

**Untuk apa:** acuan letak.

```css
.kartu { position: relative; }
.badge { position: absolute; }
.header { position: sticky; top: 0; }
.modal { position: fixed; inset: 0; }
```

Nilai: `static | relative | absolute | fixed | sticky`.

**Biasanya digabungkan dengan:** `inset`, `z-index`, `top`.

### top / right / bottom / left / inset

**Untuk apa:** jarak ke tepi acuan.

```css
.overlay { inset: 0; }
.badge { top: 0.75rem; right: 0.75rem; }
```

**Biasanya digabungkan dengan:** `position` ≠ `static`.

### z-index

**Untuk apa:** urutan tumpukan.

```css
.header { z-index: 10; }
.modal { z-index: 40; }
```

**Biasanya digabungkan dengan:** `position`, `isolation`.

### float / clear

**Untuk apa:** teks mengelilingi gambar. Bukan layout halaman.

```css
img { float: left; }
.artikel { display: flow-root; }
```

**Biasanya digabungkan dengan:** `shape-outside` atau hindari.

## Warna dan latar

### color

**Untuk apa:** warna teks, diwariskan.

```css
body { color: #0f172a; }
```

**Biasanya digabungkan dengan:** `background`, kontras.

### background / background-*

**Untuk apa:** cat dan gambar belakang.

```css
.hero {
  background: #0f172a url("/h.jpg") center / cover no-repeat;
}
```

Properti pecahan: `background-color`, `image`, `size`, `position`, `repeat`, `origin`, `clip`, `attachment`, `blend-mode`.

**Biasanya digabungkan dengan:** `color` teks, overlay gradien.

### border / border-*

**Untuk apa:** bingkai yang memakan ukuran di `content-box`.

```css
.kartu { border: 1px solid #cbd5e1; }
```

**Biasanya digabungkan dengan:** `border-radius`, `box-sizing`.

### border-radius

**Untuk apa:** sudut.

```css
.kartu { border-radius: 0.75rem; }
.pill { border-radius: 999px; }
```

**Biasanya digabungkan dengan:** `overflow: hidden`.

### outline / outline-offset

**Untuk apa:** cincin fokus tanpa menggeser layout.

```css
:focus-visible { outline: 2px solid #0369a1; outline-offset: 3px; }
```

**Biasanya digabungkan dengan:** `:focus-visible`.

### box-shadow / text-shadow

**Untuk apa:** bayangan kotak / huruf.

```css
.kartu { box-shadow: 0 8px 24px rgb(15 23 42 / 0.1); }
```

**Biasanya digabungkan dengan:** `border-radius`, hover.

### caret-color / accent-color / color-scheme

**Untuk apa:** kursor, kontrol native, tema scrollbar.

```css
:root { color-scheme: light dark; }
input { accent-color: #0f766e; caret-color: #0f766e; }
```

**Biasanya digabungkan dengan:** form, `light-dark()`.

## Tipografi

### font-family

**Untuk apa:** tumpukan font.

```css
body { font-family: system-ui, sans-serif; }
```

**Biasanya digabungkan dengan:** `font-size`, `@font-face`.

### font-size

**Untuk apa:** ukuran huruf.

```css
h1 { font-size: clamp(1.75rem, 4vw, 3rem); }
```

**Biasanya digabungkan dengan:** `line-height`, `rem`.

### font-weight / font-style / font-stretch

**Untuk apa:** tebal, miring, lebar famili.

```css
strong { font-weight: 700; }
em { font-style: italic; }
```

**Biasanya digabungkan dengan:** file font yang punya weight itu.

### font

**Untuk apa:** shorthand; mereset banyak properti font.

```css
code { font: 500 0.9rem/1.5 ui-monospace, monospace; }
```

**Biasanya digabungkan dengan:** `font-size` + `font-family` wajib.

### line-height

**Untuk apa:** tinggi baris. Unitless disarankan.

```css
body { line-height: 1.6; }
h1 { line-height: 1.2; }
```

**Biasanya digabungkan dengan:** `font-size`, `max-width: 65ch`.

### letter-spacing / word-spacing

**Untuk apa:** jarak huruf/kata.

```css
.label { letter-spacing: 0.08em; text-transform: uppercase; }
```

**Biasanya digabungkan dengan:** `text-transform`.

### text-align / text-indent

**Untuk apa:** rata teks di dalam block.

```css
.prosa { text-align: start; }
.hero h1 { text-align: center; }
```

**Biasanya digabungkan dengan:** bukan untuk menengahkan kotak (itu margin/flex).

### text-decoration / text-underline-offset / text-decoration-thickness

**Untuk apa:** garis tautan dan ketebalannya.

```css
a { text-decoration-thickness: 0.08em; text-underline-offset: 0.18em; }
```

**Biasanya digabungkan dengan:** `:hover`, `:focus-visible`.

### text-transform

**Untuk apa:** kapital visual.

```css
.label { text-transform: uppercase; }
```

**Biasanya digabungkan dengan:** `letter-spacing`, `font-size` kecil.

### text-overflow / white-space / line-clamp

**Untuk apa:** ellipsis dan wrapping.

```css
.judul {
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
}
```

**Biasanya digabungkan dengan:** `min-width: 0`.

### direction / unicode-bidi / writing-mode / text-orientation

**Untuk apa:** arah tulisan.

```css
[dir="rtl"] { direction: rtl; }
```

**Biasanya digabungkan dengan:** properti logis (`margin-inline`).

### quotes / tab-size / hanging-punctuation

**Untuk apa:** kutip, tab di kode, gantung tanda baca.

```css
pre { tab-size: 2; }
```

**Biasanya digabungkan dengan:** `lang`, `white-space: pre`.

### list-style / list-style-type / position / image

**Untuk apa:** marker daftar.

```css
ul.menu { list-style: none; padding: 0; }
ol { list-style: decimal outside; }
```

**Biasanya digabungkan dengan:** `::marker`, `padding-inline-start`.

## Transform, filter, gerak

### transform / translate / rotate / scale

**Untuk apa:** gerak visual tanpa layout.

```css
.kartu:hover { translate: 0 -0.25rem; }
```

**Biasanya digabungkan dengan:** `transition`, `transform-origin`.

### transform-origin / transform-style / perspective / backface-visibility

**Untuk apa:** poros dan 3D.

```css
.menu { transform-origin: top right; }
```

**Biasanya digabungkan dengan:** `rotate`, flip card.

### filter / backdrop-filter

**Untuk apa:** efek pada elemen / pada yang di belakang.

```css
.header { background: rgb(255 255 255 / 0.7); backdrop-filter: blur(10px); }
```

**Biasanya digabungkan dengan:** latar alpha.

### mix-blend-mode / background-blend-mode

**Untuk apa:** campur warna dengan belakang / antar layer background.

```css
.hero { background-blend-mode: multiply; }
```

**Biasanya digabungkan dengan:** `isolation`.

### transition / transition-*

**Untuk apa:** interpolasi perubahan.

```css
.tombol { transition: background-color 150ms ease, transform 150ms ease; }
```

**Biasanya digabungkan dengan:** `:hover`, hindari `transition: all`.

### animation / animation-* / offset-* (motion path)

**Untuk apa:** keyframe.

```css
.toast { animation: masuk 200ms ease both; }
```

**Biasanya digabungkan dengan:** `@keyframes`, `prefers-reduced-motion`.

## Interaksi dan pointer

### cursor

**Untuk apa:** bentuk kursor.

```css
.tombol { cursor: pointer; }
.disabled { cursor: not-allowed; }
.link { cursor: pointer; }
.drag { cursor: grab; }
```

Nilai umum: `default | pointer | not-allowed | text | move | grab | grabbing | wait | help | zoom-in`.

**Biasanya digabungkan dengan:** `:disabled`, `pointer-events`.

### pointer-events

**Untuk apa:** apakah elemen menangkap klik/hover.

```css
.overlay-dekor { pointer-events: none; }
.tombol:disabled { pointer-events: none; }
```

`none` meneruskan klik ke bawah. Overlay dekoratif tidak boleh memakan klik isi.

**Biasanya digabungkan dengan:** `::before` overlay, `opacity: 0`.

### user-select

**Untuk apa:** boleh tidaknya menyeleksi teks.

```css
.label-ui { user-select: none; }
.kode { user-select: text; }
```

Jangan menonaktifkan seleksi pada artikel.

**Biasanya digabungkan dengan:** tombol, chip.

### touch-action

**Untuk apa:** gestur sentuh mana yang ditangani browser.

```css
.kanvas { touch-action: none; }
.slider { touch-action: pan-y; }
```

**Biasanya digabungkan dengan:** drag JS, carousel.

### scroll-behavior / scroll-margin / scroll-padding

**Untuk apa:** loncatan hash dan jarak header.

```css
html { scroll-behavior: smooth; }
h2[id] { scroll-margin-top: 5rem; }
```

**Biasanya digabungkan dengan:** sticky header, reduced motion.

### scroll-snap-*

**Untuk apa:** nempel per slide.

```css
.slider { scroll-snap-type: x mandatory; }
.slide { scroll-snap-align: center; }
```

**Biasanya digabungkan dengan:** flex overflow-x.

### overscroll-behavior / scrollbar-gutter / scrollbar-color / scrollbar-width

**Untuk apa:** rantai scroll, ruang scrollbar, warna scrollbar (Firefox + standar berkembang).

```css
.dialog { overscroll-behavior: contain; }
html { scrollbar-gutter: stable; }
```

**Biasanya digabungkan dengan:** modal.

## Tabel, kolom, break

### border-collapse / border-spacing / caption-side / empty-cells / table-layout

**Untuk apa:** model tabel.

```css
table { border-collapse: collapse; width: 100%; table-layout: fixed; }
```

`table-layout: fixed` + `width: 100%` membuat kolom patuh, teks diisi `overflow`/`ellipsis`.

**Biasanya digabungkan dengan:** `th`/`td` padding, `vertical-align`.

### column-count / column-width / column-gap / column-rule / break-inside

**Untuk apa:** teks koran / masonry kasar.

```css
.masonry { column-count: 3; column-gap: 1rem; }
.masonry > * { break-inside: avoid; }
```

**Biasanya digabungkan dengan:** `break-inside: avoid` pada kartu.

### break-before / break-after / orphans / widows / page

**Untuk apa:** pecah halaman cetak.

```css
h2 { break-after: avoid; }
@media print { .kartu { break-inside: avoid; } }
```

**Biasanya digabungkan dengan:** `@media print`.

## SVG dan gambar

### fill / stroke / stroke-width

**Untuk apa:** ikon SVG inline.

```css
.ikon { fill: currentColor; stroke: none; }
```

**Biasanya digabungkan dengan:** `color` induk.

### image-rendering / image-orientation / object-view-box

**Untuk apa:** piksel tegas vs halus.

```css
.pixel { image-rendering: pixelated; }
```

**Biasanya digabungkan dengan:** sprite 8-bit.

## Mask, clip, shape

### clip-path

**Untuk apa:** potong kotak jadi bentuk.

```css
.hero { clip-path: polygon(0 0, 100% 0, 100% 85%, 0 100%); }
.avatar { clip-path: circle(50%); }
```

**Biasanya digabungkan dengan:** `overflow`, animasi hati-hati (mahal).

### mask / mask-image / mask-size

**Untuk apa:** transparan mengikuti gambar/gradien.

```css
.fade { mask-image: linear-gradient(black, transparent); }
```

**Biasanya digabungkan dengan:** overflow teks, edge fade.

### shape-outside / shape-margin

**Untuk apa:** teks mengelilingi float.

```css
img { float: left; shape-outside: circle(); }
```

**Biasanya digabungkan dengan:** `float`.

## Variabel dan all

### custom property / var()

**Untuk apa:** token yang diwariskan.

```css
:root { --fg: #0f172a; }
body { color: var(--fg); }
```

**Biasanya digabungkan dengan:** tema, `calc`.

### all

**Untuk apa:** reset hampir semua properti.

```css
.widget { all: unset; }
```

**Biasanya digabungkan dengan:** bangun ulang komponen.

## Print dan speach (singkat)

### orphans / widows

**Untuk apa:** minimal baris tertinggal di halaman.

```css
p { orphans: 3; widows: 3; }
```

**Biasanya digabungkan dengan:** `@media print`.

## Tabel ringkas A–Z (nama → pasangan)

Gunakan ini sebagai indeks. Detail di baris atas atau bab khusus.

| Nama | Untuk apa | Nilai yang sering | Biasanya digabung dengan |
| --- | --- | --- | --- |
| `accent-color` | aksen checkbox/range | warna merek | form native |
| `align-content` | antar baris flex/grid | `start`, `center`, `space-between` | `flex-wrap`, tinggi tetap |
| `align-items` | cross axis / isi sel | `center`, `stretch`, `start` | `display: flex/grid` |
| `align-self` | override satu item | `start`, `center` | `align-items` |
| `animation` | jalankan keyframe | `masuk 200ms ease both` | `@keyframes` |
| `appearance` | kurangi gaya native | `none` | custom checkbox |
| `aspect-ratio` | rasio kotak | `16/9`, `1` | `object-fit` |
| `backdrop-filter` | kaca buram | `blur(10px)` | latar alpha |
| `backface-visibility` | sisi belakang 3D | `hidden` | flip |
| `background` | shorthand latar | warna + image | `color` teks |
| `background-blend-mode` | campur layer bg | `multiply` | beberapa image |
| `background-clip` | area cat | `text`, `padding-box` | gradien teks |
| `background-color` | cat datar | hex/hsl | `color` |
| `background-image` | url/gradien | `url()`, `linear-gradient` | `size cover` |
| `background-origin` | acuan posisi | `content-box` | padding |
| `background-position` | jangkar | `center`, `top` | `cover` |
| `background-repeat` | ubin | `no-repeat` | `size` |
| `background-size` | skala bg | `cover`, `contain` | `position` |
| `block-size` | tinggi logis | `auto`, `100%` | writing-mode |
| `border` | bingkai | `1px solid #cbd5e1` | radius |
| `border-collapse` | tabel | `collapse` | `td` border |
| `border-image` | bingkai gambar | `url() 12` | jarang + radius |
| `border-radius` | sudut | `0.75rem`, `999px` | `overflow` |
| `border-spacing` | jarak sel | `0 0.5rem` | `separate` |
| `bottom` | tepi bawah | `0`, `1rem` | `position` |
| `box-decoration-break` | pecah box | `clone` | kolom/inline |
| `box-shadow` | bayangan/ring | `0 8px 24px ...` | hover |
| `box-sizing` | model lebar | `border-box` | `*` reset |
| `break-inside` | jangan pecah | `avoid` | print, columns |
| `caption-side` | posisi caption | `bottom` | tabel |
| `caret-color` | kursor ketik | merek | input |
| `clear` | tolak float | `both` | clearfix |
| `clip-path` | potong bentuk | `circle()`, `polygon()` | hero |
| `color` | teks | hex | `currentColor` |
| `color-scheme` | tema native | `light dark` | `light-dark()` |
| `column-count` | jumlah kolom teks | `2`, `3` | `gap`, `break-inside` |
| `column-gap` | jarak kolom | `1rem` | grid/flex/columns |
| `contain` | batasi pengaruh | `layout paint` | feed |
| `content` | isi pseudo | `""`, `" *"` | `::before` |
| `content-visibility` | tunda render | `auto` | `contain-intrinsic-size` |
| `counter-increment` | naikkan counter | `bab 1` | `::before` |
| `counter-reset` | mulai counter | `bab` | `ol` kustom |
| `cursor` | kursor | `pointer` | tombol |
| `direction` | ltr/rtl | `rtl` | logical props |
| `display` | model kotak | `flex`, `grid`, `none` | gap |
| `empty-cells` | sel kosong | `hide` | tabel |
| `field-sizing` | ukuran field ikut isi | `content` | textarea modern |
| `filter` | blur/gray | `grayscale(1)` | hover gambar |
| `flex` | grow shrink basis | `1`, `none` | `min-width: 0` |
| `flex-basis` | ukuran awal | `16rem`, `0` | grow/shrink |
| `flex-direction` | arah | `row`, `column` | justify/align tertukar |
| `flex-flow` | dir+wrap | `row wrap` | gap |
| `flex-grow` | makan sisa | `1` | basis |
| `flex-shrink` | susut | `0` ikon | `min-width` |
| `flex-wrap` | wrap | `wrap` | `align-content` |
| `float` | alir kiri/kanan | `left` | `flow-root` |
| `font` | shorthand font | `500 1rem/1.5 system-ui` | hati-hati reset |
| `font-display` | di `@font-face` | `swap` | `@font-face` |
| `font-family` | famili | `system-ui, sans-serif` | fallback |
| `font-feature-settings` | OpenType | `"liga" 1` | font khusus |
| `font-kerning` | kerning | `normal` | judul |
| `font-optical-sizing` | opsz | `auto` | variable font |
| `font-size` | ukuran | `1rem`, `clamp(...)` | line-height |
| `font-style` | italic | `italic` | `em` |
| `font-synthesis` | bold/italic palsu | `none` | font terbatas |
| `font-variant` | small-caps dll | `small-caps` | label |
| `font-variation-settings` | sumbu variable | `"wght" 550` | variable font |
| `font-weight` | tebal | `400`, `700` | file weight |
| `forced-color-adjust` | hormati high contrast | `auto`, `none` | `forced-colors` |
| `gap` | jarak item | `1rem` | flex/grid |
| `grid` | shorthand grid | hindari | pecah properti |
| `grid-area` | nama/garis | `main` | template-areas |
| `grid-auto-columns` | kolom implisit | `20rem` | auto-flow column |
| `grid-auto-flow` | arah isi | `row`, `dense` | span |
| `grid-auto-rows` | baris implisit | `minmax(8rem,auto)` | gallery |
| `grid-column` | rentang kolom | `span 2`, `1 / -1` | hero |
| `grid-row` | rentang baris | `span 2` | featured |
| `grid-template` | shorthand template | areas+tracks | gap |
| `grid-template-areas` | peta | string nama | `grid-area` |
| `grid-template-columns` | kolom | `repeat(...)` | `minmax(0,1fr)` |
| `grid-template-rows` | baris | `auto 1fr auto` | footer |
| `hanging-punctuation` | gantung kutip | `first` | prosa |
| `height` | tinggi | `auto`, `100%` | `min-height` |
| `hyphens` | tanda hubung | `auto` | `lang` |
| `image-rendering` | skala gambar | `pixelated`, `auto` | ikon piksel |
| `initial-letter` | drop cap modern | `3` | artikel |
| `inline-size` | lebar logis | `min(100%, 40rem)` | logical |
| `inset` | keempat sisi | `0`, `1rem` | absolute/fixed |
| `inset-block` / `inset-inline` | sisi logis | `0` | RTL |
| `isolation` | stacking baru | `isolate` | z-index lokal |
| `justify-content` | main axis / grid di wadah | `space-between`, `center` | gap |
| `justify-items` | isi sel inline | `stretch`, `center` | grid |
| `justify-self` | satu item inline | `end` | grid |
| `left` | tepi kiri | `0` | position |
| `letter-spacing` | jarak huruf | `0.08em` | uppercase |
| `line-break` | pecah CJK | `strict` | CJK |
| `line-clamp` | potong n baris | `3` | `overflow: hidden` |
| `line-height` | tinggi baris | `1.6` | font-size |
| `list-style` | marker | `none`, `decimal` | nav ul |
| `margin` | ruang luar | `0`, `auto` | max-width |
| `margin-trim` | potong margin tepi container | `block` | dukungan baru |
| `mask-image` | topeng | gradien | fade |
| `max-block-size` / `max-inline-size` | max logis | `70rem` | prosa |
| `max-height` | batas tinggi | `70vh` | overflow auto |
| `max-width` | batas lebar | `65ch`, `70rem` | mx auto |
| `min-height` | tinggi minimal | `100dvh` | flex col |
| `min-width` | lebar minimal | `0`, `8rem` | flex item |
| `mix-blend-mode` | campur elemen | `multiply`, `difference` | isolation |
| `object-fit` | isi media | `cover` | aspect-ratio |
| `object-position` | jangkar media | `center top` | cover |
| `offset-path` / `offset-distance` | gerak di jalur | `path()`, `50%` | animasi |
| `opacity` | alfa subtree | `0.5` | transition |
| `order` | urutan flex/grid | `-1` | a11y hati-hati |
| `orphans` | sisa baris cetak | `3` | print |
| `outline` | cincin | `2px solid` | focus-visible |
| `outline-offset` | jarak cincin | `3px` | outline |
| `overflow` | potong/scroll | `auto`, `hidden` | max-height |
| `overflow-anchor` | cegah loncat scroll | `none` | chat |
| `overflow-wrap` | pecah kata | `anywhere` | min-width 0 |
| `overscroll-behavior` | rantai scroll | `contain` | modal |
| `padding` | ruang dalam | `1rem` | background |
| `page` | named page | `landscape` | `@page` |
| `paint-order` | urutan cat svg | `stroke fill` | ikon |
| `perspective` | kamera 3D | `800px` | anak rotateY |
| `place-content` | content 2 sumbu | `center` | flex wrap/grid |
| `place-items` | items 2 sumbu | `center` | grid |
| `place-self` | self 2 sumbu | `end` | grid |
| `pointer-events` | tangkap klik | `none` | overlay |
| `position` | model letak | `relative`, `sticky` | inset |
| `print-color-adjust` | cetak latar | `exact` | print |
| `quotes` | karakter kutip | `"“" "”"` | `q` |
| `resize` | drag ukuran | `vertical` | textarea |
| `right` | tepi kanan | `0` | position |
| `rotate` | properti putar | `180deg` | transition |
| `row-gap` | jarak baris | `1rem` | grid/flex wrap |
| `scale` | properti skala | `1.02` | hover |
| `scroll-behavior` | hash mulus | `smooth` | reduced motion |
| `scroll-margin-top` | jarak target | `5rem` | sticky header |
| `scroll-padding` | padding snap/target | `5rem` | container scroll |
| `scroll-snap-align` | nempel item | `start`, `center` | slider |
| `scroll-snap-stop` | jangan loncat 2 | `always` | mandatory |
| `scroll-snap-type` | aktifkan snap | `x mandatory` | overflow auto |
| `scrollbar-color` | warna scrollbar | `thumb track` | Firefox |
| `scrollbar-gutter` | ruang scrollbar | `stable` | overflow auto |
| `scrollbar-width` | tebal scrollbar | `thin` | Firefox |
| `shape-outside` | alur teks | `circle()` | float |
| `tab-size` | lebar tab | `2` | pre |
| `table-layout` | algoritma kolom | `fixed` | width 100% |
| `text-align` | rata teks | `start`, `center` | prosa |
| `text-decoration` | garis | `underline` | offset |
| `text-indent` | jorok baris 1 | `1.5em` | artikel |
| `text-overflow` | ellipsis | `ellipsis` | nowrap+hidden |
| `text-shadow` | bayangan huruf | `0 1px 2px ...` | teks di foto |
| `text-transform` | kapital | `uppercase` | tracking |
| `text-underline-offset` | jarak garis | `0.2em` | tautan |
| `text-wrap` | cara bungkus | `balance`, `pretty` | judul |
| `top` | tepi atas | `0` | sticky |
| `touch-action` | gestur | `pan-y` | slider |
| `transform` | fungsi 2D/3D | `translateY(-4px)` | transition |
| `transform-origin` | poros | `center`, `top` | rotate |
| `transform-style` | 3D anak | `preserve-3d` | kubus |
| `transition` | interpolasi | `transform 150ms` | hover |
| `translate` | geser terpisah | `0 -0.25rem` | hover kartu |
| `unicode-bidi` | bidi | `isolate` | campur bahasa |
| `user-select` | seleksi | `none` | UI chrome |
| `vertical-align` | inline/tabel | `middle` | td, img |
| `view-transition-name` | transisi halaman | `banner` | View Transitions |
| `visibility` | terlihat vs ruang | `hidden` | beda dari none |
| `white-space` | wrapping | `nowrap`, `pre-wrap` | ellipsis |
| `widows` | baris tinggal cetak | `3` | print |
| `width` | lebar | `min(100%, 70rem)` | mx auto |
| `will-change` | petunjuk animasi | `transform` | jangan massal |
| `word-break` | pecah huruf | `break-all` | token |
| `writing-mode` | vertikal | `vertical-rl` | logical |
| `z-index` | tumpukan | `10`, `40` | position |
| `zoom` | skala nonstandar | hindari | `transform: scale` |

### appearance

**Untuk apa:** mengurangi atau menyesuaikan chrome native kontrol.

```css
select, button { appearance: none; }
```

Setelah `none`, kamu wajib menggambar ulang panah select sendiri.

**Biasanya digabungkan dengan:** `background-image` panah, padding.

### counter-reset dan counter-increment

**Untuk apa:** nomor bab CSS.

```css
.prosa { counter-reset: langkah; }
.prosa h2 { counter-increment: langkah; }
.prosa h2::before { content: counter(langkah) ". "; }
```

**Biasanya digabungkan dengan:** `::before`, `ol` kustom.

### text-wrap

**Untuk apa:** `balance` meratakan baris judul; `pretty` mengurangi kata tunggal di baris terakhir.

```css
h1, h2 { text-wrap: balance; }
p { text-wrap: pretty; }
```

**Biasanya digabungkan dengan:** `max-width`, judul 2–4 baris.

### field-sizing

**Untuk apa:** textarea/input tumbuh mengikuti isi (dukungan baru).

```css
textarea { field-sizing: content; min-height: 6rem; max-height: 20rem; }
```

**Biasanya digabungkan dengan:** `min-height`, form komentar.

### view-transition-name

**Untuk apa:** menandai elemen agar View Transitions API menggerakkannya antar halaman/state.

```css
.hero { view-transition-name: hero; }
```

**Biasanya digabungkan dengan:** `document.startViewTransition`, Next.js view transitions.

## Properti logis vs fisik

**Untuk apa:** memilih API yang tidak rusak saat RTL.

| Fisik | Logis |
| --- | --- |
| `width` | `inline-size` |
| `height` | `block-size` |
| `margin-left` | `margin-inline-start` |
| `margin-right` | `margin-inline-end` |
| `padding-top` | `padding-block-start` |
| `border-left` | `border-inline-start` |
| `left` | `inset-inline-start` |
| `right` | `inset-inline-end` |
| `top` | `inset-block-start` |
| `text-align: left` | `text-align: start` |

```css
.icon { margin-inline-end: 0.5rem; }
```

**Biasanya digabungkan dengan:** `dir="rtl"`, navbar multibahasa.

## Yang sering tertukar

| Kamu mau | Bukan ini | Melainkan ini |
| --- | --- | --- |
| Tengah kotak di halaman | `text-align: center` pada body saja | `margin-inline: auto` + lebar, atau flex/grid |
| Tengah item flex vertikal | `justify-content` pada `row` | `align-items: center` |
| Jarak antar item | `margin` di semua anak | `gap` |
| Sembunyi dan lepas ruang | `visibility: hidden` | `display: none` |
| Sembunyi tapi ruang tetap | `display: none` | `visibility: hidden` / `opacity: 0` |
| Cincin fokus | `border` yang menggeser layout | `outline` atau `box-shadow` |
| Kolom katalog | banyak `float` | Grid `auto-fit` |
| Navbar | `position: absolute` semua tautan | Flex |
| Teks tidak ellipsis | `text-overflow` saja | + `overflow` + `nowrap` + `min-width: 0` |

## Indeks bab per kelompok

- Selector: [01](01-kaskade-selector-spesifisitas.md)
- Kotak & display: [02](02-box-model-display-visibility.md)
- Satuan & overflow: [03](03-satuan-sizing-overflow.md)
- Flex: [04](04-flexbox-semua-properti.md)
- Grid: [05](05-grid-semua-properti.md)
- Warna & huruf: [06](06-warna-tipografi-list.md)
- Latar & bingkai: [07](07-background-border-outline-shadow.md)
- Position: [08](08-position-zindex-float-sticky.md)
- Gerak: [09](09-transform-filter-transition-animation.md)
- Pseudo: [10](10-pseudo-class-element.md)
- Query & layer: [11](11-media-query-container-layer.md)
- Tailwind: [13](13-tailwind-utility-lengkap.md)
