# 03 — Satuan, sizing, overflow

[← Box model](02-box-model-display-visibility.md) · [Indeks](README.md) · [Flexbox →](04-flexbox-semua-properti.md)

Satuan yang salah membuat kartu meledak di HP atau judul raksasa di desktop. Bagian ini membedah unit, fungsi ukuran, overflow, dan scroll.

## Daftar isi

- [px](#px)
- [rem](#rem)
- [em](#em)
- [persen](#persen)
- [ch ex cap ic lh rlh](#ch-ex-cap-ic-lh-rlh)
- [Viewport: vw vh vmin vmax sv* lv* dv*](#viewport-vw-vh-vmin-vmax-sv-lv-dv)
- [Container query unit](#container-query-unit)
- [fr](#fr)
- [calc](#calc)
- [min max clamp](#min-max-clamp)
- [width height min max](#width-height-min-max)
- [box-sizing ulang](#box-sizing-ulang)
- [overflow](#overflow)
- [overflow-wrap word-break hyphens](#overflow-wrap-word-break-hyphens)
- [text-overflow dan white-space](#text-overflow-dan-white-space)
- [object-fit](#object-fit)
- [scroll-behavior scroll-margin scroll-padding](#scroll-behavior-scroll-margin-scroll-padding)
- [scroll-snap](#scroll-snap)
- [overscroll-behavior](#overscroll-behavior)
- [scrollbar-gutter](#scrollbar-gutter)
- [resize](#resize)

## px

**Untuk apa:** piksel CSS. Ukuran tetap di layar referensi, tetap diskala oleh zoom browser.

```css
.garis { border-width: 1px; }
.icon { width: 24px; height: 24px; }
```

Bagus untuk garis 1px dan ikon yang memang didesain per piksel. Kurang bagus sebagai `font-size` utama: tidak ikut preferensi root.

**Biasanya digabungkan dengan:** `border`, `box-shadow`, `outline`.

## rem

**Untuk apa:** kelipatan `font-size` elemen root (`html`). Default umum 16px, jadi `1rem = 16px`.

```css
html { font-size: 100%; }

.kartu { padding: 1rem; }
h1 { font-size: 2rem; }
```

Kalau pengguna memperbesar font browser, seluruh skala `rem` ikut. Tailwind `p-4` = `1rem`.

**Biasanya digabungkan dengan:** spacing, `font-size` judul, media query `48rem`.

## em

**Untuk apa:** kelipatan `font-size` elemen itu sendiri (atau induk, saat dipakai di `font-size`).

```css
.tombol {
  font-size: 1rem;
  padding: 0.5em 1em;
  border-radius: 0.375em;
}

.tombol--besar { font-size: 1.25rem; }
```

Tombol besar otomatis punya padding lebih longgar. Jebakan: `em` bersarang di `font-size` berlipat ganda.

```css
.nav { font-size: 1.1em; }
.nav .item { font-size: 1.1em; }
```

Item jadi 1.21× root, bukan 1.1×. Untuk itu pakai `rem`.

**Biasanya digabungkan dengan:** padding komponen yang ikut ukuran huruf.

## persen

**Untuk apa:** relatif ke acuan properti. Bukan selalu “persen layar”.

```css
.kolom { width: 50%; }
.tinggi-penuh { height: 100%; }
```

`width: %` relatif ke lebar containing block. `height: %` hanya jalan jika induk punya tinggi terhitung. `padding: 50%` pada elemen block dihitung dari **lebar** induk, bukan tinggi — trik lama aspect-ratio.

**Biasanya digabungkan dengan:** `max-width`, Grid `1fr` sebagai alternatif.

## ch ex cap ic lh rlh

### ch

**Untuk apa:** lebar kira-kira glif `0` pada font elemen.

```css
.prosa { max-width: 65ch; }
input[size] { width: 20ch; }
```

Panjang baris bacaan nyaman sekitar 45–75 karakter.

**Biasanya digabungkan dengan:** `line-height`, `width: 100%`.

### ex

**Untuk apa:** tinggi x-height font.

```css
.ikon-tengah { height: 1ex; }
```

Jarang; lebih sering `em`.

**Biasanya digabungkan dengan:** ikon sebaris teks.

### cap

**Untuk apa:** tinggi huruf kapital.

```css
.ikon { height: 1cap; }
```

**Biasanya digabungkan dengan:** ikon di samping judul.

### ic

**Untuk apa:** ukuran ideograf (CJK).

```css
.judul-cjk { max-width: 20ic; }
```

**Biasanya digabungkan dengan:** tipografi CJK.

### lh dan rlh

**Untuk apa:** `lh` = `line-height` elemen; `rlh` = `line-height` root.

```css
.badge { height: 1lh; padding-inline: 0.5em; }
```

Badge setinggi satu baris teks.

**Biasanya digabungkan dengan:** inline-flex, `align-items: center`.

## Viewport: vw vh vmin vmax sv* lv* dv*

### vw dan vh

**Untuk apa:** 1% lebar/tinggi viewport.

```css
.hero { min-height: 100vh; }
.judul { font-size: 5vw; }
```

`100vh` di HP sering terlalu tinggi karena bilah alamat. `5vw` judul bisa terlalu kecil di HP dan terlalu besar di TV.

**Biasanya digabungkan dengan:** `clamp()` untuk font, `min-height` bukan `height` kaku.

### vmin dan vmax

**Untuk apa:** `vmin` = yang lebih kecil antara vw dan vh; `vmax` yang lebih besar.

```css
.kotak-layar { width: 80vmin; height: 80vmin; }
```

Kotak tetap persegi berdasarkan sisi pendek layar.

**Biasanya digabungkan dengan:** overlay, avatar hero.

### svh lvh dvh (dan svw, lvw, dvw)

**Untuk apa:** viewport kecil (sv*), besar (lv*), dinamis (dv*) agar bilah URL HP tidak merusak layout.

```css
.halaman { min-height: 100dvh; }
.hero-penuh { min-height: 100svh; }
```

`dvh` berubah saat browser chrome muncul/hilang. `svh` stabil “terkecil”. `lvh` “terbesar”.

**Biasanya digabungkan dengan:** flex kolom halaman, hero.

### vi vb

**Untuk apa:** 1% viewport di sumbu inline/block.

```css
.panel { width: 40vi; }
```

Mengikuti `writing-mode`.

**Biasanya digabungkan dengan:** layout logis.

## Container query unit

**Untuk apa:** ukuran relatif ke container query, bukan ke layar.

```css
.kartu {
  container-type: inline-size;
}

.kartu h2 {
  font-size: clamp(1rem, 4cqi, 1.5rem);
}
```

`cqi` = 1% inline-size container. Juga: `cqb`, `cqw`, `cqh`, `cqmin`, `cqmax`.

**Biasanya digabungkan dengan:** `@container`, lihat [bab 11](11-media-query-container-layer.md).

## fr

**Untuk apa:** pecahan sisa ruang di Grid.

```css
.papan {
  display: grid;
  grid-template-columns: 16rem 1fr 1fr;
}
```

Sisa lebar setelah `16rem` dibagi dua kolom sama rata. `fr` tidak valid di `width` biasa.

**Biasanya digabungkan dengan:** `minmax(0, 1fr)`, `gap`.

## calc

**Untuk apa:** hitung nilai dari campuran satuan.

```css
.konten {
  width: calc(100% - 2rem);
}

.sticky-offset {
  top: calc(var(--header) + 0.5rem);
}

.kolom {
  width: calc((100% - 2rem) / 3);
}
```

Harus ada operator dengan spasi: `100% - 2rem`, bukan `100%-2rem`. Boleh campur `px`, `rem`, `%`, `vw`.

**Biasanya digabungkan dengan:** custom property, `min()`.

## min max clamp

### min

**Untuk apa:** pakai nilai terkecil.

```css
.halaman {
  width: min(100% - 2rem, 70rem);
}
```

Di layar sempit: hampir penuh. Di layar lebar: berhenti di 70rem.

**Biasanya digabungkan dengan:** `margin-inline: auto`.

### max

**Untuk apa:** pakai nilai terbesar.

```css
.tombol {
  width: max(12rem, 40%);
}
```

Tidak lebih sempit dari 12rem, kecuali wadahnya sendiri lebih kecil — tetap awasi overflow.

**Biasanya digabungkan dengan:** `min-width`, `clamp`.

### clamp

**Untuk apa:** `clamp(min, disukai, max)`.

```css
h1 {
  font-size: clamp(1.75rem, 1rem + 2vw, 3rem);
}

.kartu {
  padding: clamp(0.75rem, 2vw, 2rem);
}
```

Judul tumbuh dengan layar tetapi tidak lebih kecil dari 1.75rem dan tidak lebih besar dari 3rem.

**Biasanya digabungkan dengan:** tipografi fluid, padding hero.

## width height min max

Lihat juga [bab 02](02-box-model-display-visibility.md). Ringkas nilai khusus:

```css
.isi { width: fit-content; }
.isi { width: max-content; }
.isi { width: min-content; }
.isi { width: stretch; }
```

`min-content`: selebar kata terpanjang. `max-content`: selebar teks tanpa wrapping. `fit-content`: seperti `min(max-content, available)`. Berguna untuk chip dan tooltip.

**Biasanya digabungkan dengan:** `white-space`, flex item yang tidak boleh mekar.

### min-content max-content fit-content sebagai jebakan

**Untuk apa:** paham kenapa kolom grid “tidak mau menyusut”.

```css
.kolom-teks {
  min-width: min-content;
}
```

URL panjang atau gambar tanpa `max-width` memaksa `min-content` besar. Obat: `min-width: 0`, `overflow-wrap: anywhere`, `img { max-width: 100%; }`.

**Biasanya digabungkan dengan:** Grid `minmax(0, 1fr)`.

## box-sizing ulang

**Untuk apa:** mengingatkan bahwa satuan lebar tergantung model kotak.

```css
.input {
  box-sizing: border-box;
  width: 100%;
  padding: 0.6rem 0.75rem;
  border: 1px solid #cbd5e1;
}
```

Tanpa `border-box`, input 100% + padding + border keluar form.

**Biasanya digabungkan dengan:** reset global di [bab 02](02-box-model-display-visibility.md).

## overflow

### visible

**Untuk apa:** konten boleh keluar. Bawaan.

```css
.badge-induk { overflow: visible; }
```

Anak `absolute` di luar kartu tetap kelihatan.

**Biasanya digabungkan dengan:** dropdown, badge keluar kartu.

### hidden

**Untuk apa:** potong, tidak bisa di-scroll.

```css
.kartu {
  overflow: hidden;
  border-radius: 0.75rem;
}
```

Gambar sudut kartu mengikuti radius. Overlay yang keluar akan terpotong — pindahkan dropdown ke portal jika perlu.

**Biasanya digabungkan dengan:** `border-radius`, hero image.

### clip

**Untuk apa:** potong tanpa membuat scroll container.

```css
.potong { overflow: clip; }
```

Mirip `hidden` tetapi lebih ketat untuk programatik scroll.

**Biasanya digabungkan dengan:** efek visual, bukan daftar.

### scroll

**Untuk apa:** selalu jadi scroll container.

```css
.daftar {
  max-height: 16rem;
  overflow: scroll;
}
```

Di Windows kadang muncul scrollbar disabled. `auto` biasanya lebih ramah.

**Biasanya digabungkan dengan:** `max-height`.

### auto

**Untuk apa:** scrollbar hanya jika konten melampaui.

```css
.dialog-badan {
  max-height: 70vh;
  overflow: auto;
}
```

**Biasanya digabungkan dengan:** modal, `<pre>`, tabel.

### overflow-x dan overflow-y

**Untuk apa:** sumbu terpisah. Satu sumbu `visible` dipaksa jadi `auto` jika sumbu lain tidak `visible`.

```css
.kode {
  overflow-x: auto;
  overflow-y: hidden;
}
```

**Biasanya digabungkan dengan:** `white-space: pre`, tabel lebar.

## overflow-wrap word-break hyphens

### overflow-wrap

**Untuk apa:** boleh memecah kata panjang agar tidak keluar kotak.

```css
.kartu { overflow-wrap: anywhere; }
.prosa { overflow-wrap: break-word; }
```

`anywhere` lebih agresif (memengaruhi `min-content`). `break-word` pecah hanya jika perlu.

**Biasanya digabungkan dengan:** `min-width: 0`, URL, email.

### word-break

**Untuk apa:** `break-all` memecah di huruf mana pun; kasar untuk teks Latin.

```css
.kode-inline { word-break: break-all; }
```

Untuk CJK, `word-break: keep-all` menahan pemecahan.

**Biasanya digabungkan dengan:** token, hash, bukan paragraf biasa.

### hyphens

**Untuk apa:** tanda hubung otomatis. Butuh `lang` di HTML.

```css
.prosa {
  hyphens: auto;
}
```

```html
<html lang="id">
```

**Biasanya digabungkan dengan:** `lang`, `overflow-wrap`.

## text-overflow dan white-space

### white-space

**Untuk apa:** merawat spasi dan wrapping.

```css
.ellipsis {
  white-space: nowrap;
}

.kode { white-space: pre; }
.prosa-form { white-space: pre-wrap; }
```

`normal`: rapatkan spasi, bungkus. `nowrap`: satu baris. `pre`: seperti `<pre>`. `pre-wrap`: jaga spasi tetapi boleh bungkus. `pre-line`: rapatkan spasi, jaga newline. `break-spaces`: jaga semua spasi.

**Biasanya digabungkan dengan:** `text-overflow`, `<pre>`.

### text-overflow

**Untuk apa:** titik-titik saat teks terpotong. Hanya jalan jika overflow bukan visible dan teks tidak wrap.

```css
.judul-kartu {
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
}
```

Untuk banyak baris, pakai `-webkit-line-clamp` / `line-clamp`.

```css
.kutipan {
  display: -webkit-box;
  -webkit-box-orient: vertical;
  -webkit-line-clamp: 3;
  overflow: hidden;
}
```

Modern: `line-clamp: 3` di browser baru.

**Biasanya digabungkan dengan:** `min-width: 0` pada flex item (wajib, kalau tidak ellipsis mogok).

## object-fit

**Untuk apa:** isi gambar di kotak tetap.

```css
img.cover {
  width: 100%;
  height: 100%;
  object-fit: cover;
}

img.logo {
  width: 8rem;
  height: 3rem;
  object-fit: contain;
}
```

**Biasanya digabungkan dengan:** `aspect-ratio`, `object-position`.

## scroll-behavior scroll-margin scroll-padding

### scroll-behavior

**Untuk apa:** animasi loncat tautan hash.

```css
html { scroll-behavior: smooth; }
@media (prefers-reduced-motion: reduce) {
  html { scroll-behavior: auto; }
}
```

**Biasanya digabungkan dengan:** `prefers-reduced-motion`, ID bagian.

### scroll-margin-top

**Untuk apa:** jarak extra saat elemen jadi target scroll, agar tidak ditutup header sticky.

```css
#konten {
  scroll-margin-top: 5rem;
}

h2[id] { scroll-margin-top: calc(var(--header-h) + 0.75rem); }
```

**Biasanya digabungkan dengan:** `position: sticky` header, `href="#id"`.

### scroll-padding

**Untuk apa:** padding “jangkauan” scroll container, mirip scroll-margin tetapi di wadah.

```css
.halaman {
  scroll-padding-top: 5rem;
}
```

**Biasanya digabungkan dengan:** snap, halaman dengan header tetap.

## scroll-snap

**Untuk apa:** carousel atau gallery yang “nempel” per slide.

```css
.slider {
  display: flex;
  overflow-x: auto;
  scroll-snap-type: x mandatory;
  gap: 1rem;
}

.slide {
  flex: 0 0 80%;
  scroll-snap-align: center;
  scroll-snap-stop: always;
}
```

`proximity` lebih longgar daripada `mandatory`. `scroll-snap-stop: always` mencegah lompat dua slide.

**Biasanya digabungkan dengan:** flex baris, `aspect-ratio`, tombol JS opsional.

## overscroll-behavior

**Untuk apa:** mencegah scroll rantai ke halaman di belakang modal.

```css
.dialog-badan { overscroll-behavior: contain; }
body.kunci { overscroll-behavior: none; }
```

`contain`: tidak meneruskan ke induk. `none`: plus menonaktifkan bounce refresh di beberapa browser.

**Biasanya digabungkan dengan:** `html:has(dialog[open]) { overflow: hidden; }`.

## scrollbar-gutter

**Untuk apa:** sediakan ruang scrollbar agar isi tidak bergeser saat scrollbar muncul.

```css
html { scrollbar-gutter: stable; }
```

**Biasanya digabungkan dengan:** `overflow: auto` pada kolom yang tingginya berubah.

## resize

**Untuk apa:** izinkan pengguna menarik sudut, biasanya textarea.

```css
textarea {
  resize: vertical;
  min-height: 8rem;
  max-height: 24rem;
}
```

`none` menonaktifkan. `both` dua arah. Elemen harus `overflow` selain `visible`.

**Biasanya digabungkan dengan:** `min-height`, form.
