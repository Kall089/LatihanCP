# 11 — Media query, container, layer, nesting

[← Pseudo](10-pseudo-class-element.md) · [Indeks](README.md) · [Tabel properti →](12-tabel-properti-lengkap.md)

Aturan yang hanya berlaku pada kondisi tertentu: lebar layar, kemampuan hover, tema OS, ukuran **wadah**, atau dukungan properti. Plus cara mengelompokkan kaskade.

## Daftar isi

- [viewport meta](#viewport-meta)
- [@media width height](#media-width-height)
- [Mobile first vs desktop first](#mobile-first-vs-desktop-first)
- [hover pointer](#hover-pointer)
- [prefers-color-scheme](#prefers-color-scheme)
- [prefers-reduced-motion](#prefers-reduced-motion)
- [prefers-contrast dan forced-colors](#prefers-contrast-dan-forced-colors)
- [orientation aspect-ratio resolution](#orientation-aspect-ratio-resolution)
- [display-mode](#display-mode)
- [@media print](#media-print)
- [Operator and or not](#operator-and-or-not)
- [Range syntax](#range-syntax)
- [@supports](#supports)
- [@container](#container)
- [@layer](#layer)
- [@scope](#scope)
- [@import](#import)
- [Nesting](#nesting)
- [Custom property dan @property](#custom-property-dan-property)
- [Peta Tailwind breakpoint](#peta-tailwind-breakpoint)

## viewport meta

**Untuk apa:** agar CSS `px` dan viewport HP tidak di-scale seolah desktop 980px.

```html
<meta name="viewport" content="width=device-width, initial-scale=1">
```

Tanpa ini, media query `min-width: 48rem` bisa “selalu benar” di HP. Wajib di setiap halaman tugas.

**Biasanya digabungkan dengan:** semua `@media (min-width: ...)`.

## @media width height

### min-width

**Untuk apa:** mulai dari lebar ini ke atas. Pola mobile-first.

```css
.papan { display: grid; grid-template-columns: 1fr; gap: 1rem; }

@media (min-width: 40rem) {
  .papan { grid-template-columns: 1fr 1fr; }
}

@media (min-width: 64rem) {
  .papan { grid-template-columns: 1fr 1fr 1fr; }
}
```

Breakpoint mengikuti **konten**, bukan merek HP. `40rem` ≈ 640px jika root 16px. `48rem` ≈ 768. `64rem` ≈ 1024.

**Biasanya digabungkan dengan:** Grid/Flex yang berubah arah.

### max-width

**Untuk apa:** sampai lebar ini. Pola desktop-first atau override sempit.

```css
@media (max-width: 39.99rem) {
  .nav-desktop { display: none; }
  .nav-hamburger { display: block; }
}
```

Hati-hati celah 1px antara `max-width: 39.99rem` dan `min-width: 40rem`. Lebih bersih: satu arah saja (hanya `min-width`) + class default HP.

**Biasanya digabungkan dengan:** menyembunyikan kolom.

### height

**Untuk apa:** viewport pendek (keyboard HP, landscape).

```css
@media (max-height: 30rem) {
  .hero { min-height: 0; padding-block: 1rem; }
}
```

**Biasanya digabungkan dengan:** `min-height: 100dvh` yang kebablasan.

## Mobile first vs desktop first

**Untuk apa:** memilih default.

Mobile-first: tulis gaya HP tanpa query, lalu `min-width` menambah kolom.

```css
.menu { flex-direction: column; }
@media (min-width: 48rem) {
  .menu { flex-direction: row; }
}
```

Desktop-first: default desktop, lalu `max-width` merusak ke HP. Lebih mudah lupa kasus sempit.

**Biasanya digabungkan dengan:** Tailwind yang memang `sm:` `md:` = min-width.

## hover pointer

**Untuk apa:** membedakan mouse dan sentuh.

```css
@media (hover: hover) and (pointer: fine) {
  .kartu:hover { translate: 0 -0.2rem; }
}

@media (pointer: coarse) {
  .tombol { min-height: 44px; }
}
```

`hover: hover` = perangkat bisa hover sejati. `pointer: coarse` = jari.

**Biasanya digabungkan dengan:** `:hover` dekoratif, tap target.

## prefers-color-scheme

**Untuk apa:** tema OS.

```css
:root { color-scheme: light dark; }

@media (prefers-color-scheme: dark) {
  :root {
    --bg: #0b1220;
    --fg: #e2e8f0;
  }
}
```

Atau `light-dark()` di [bab 06](06-warna-tipografi-list.md). Toggle tema di situs tetap butuh class `.gelap` di `html` karena preferensi OS ≠ pilihan user di app.

**Biasanya digabungkan dengan:** custom property, `color-scheme`.

## prefers-reduced-motion

**Untuk apa:** kurangi animasi.

```css
@media (prefers-reduced-motion: reduce) {
  .kartu { transition: none; }
  .spinner { animation: none; }
}
```

**Biasanya digabungkan dengan:** [bab 09](09-transform-filter-transition-animation.md).

## prefers-contrast dan forced-colors

**Untuk apa:** kontras tinggi dan mode Windows High Contrast (`forced-colors`).

```css
@media (prefers-contrast: more) {
  .kartu { border: 2px solid currentColor; }
}

@media (forced-colors: active) {
  .tombol { border: 1px solid CanvasText; }
}
```

Di `forced-colors`, banyak `box-shadow` dan `background-image` diabaikan. Pakai `border` dan keyword sistem (`Canvas`, `CanvasText`, `LinkText`, `ButtonFace`).

**Biasanya digabungkan dengan:** fokus terlihat, jangan andalkan shadow saja.

## orientation aspect-ratio resolution

```css
@media (orientation: landscape) {
  .galeri { grid-template-columns: 1fr 1fr 1fr; }
}

@media (min-resolution: 2x) {
  .logo { background-image: url("/logo@2x.png"); }
}

@media (min-aspect-ratio: 16/9) {
  .hero { min-height: 80dvh; }
}
```

`orientation` mudah berubah saat keyboard muncul di HP — jangan simpan state penting hanya di sini.

**Biasanya digabungkan dengan:** gambar 2x, player.

## display-mode

**Untuk apa:** PWA standalone vs browser.

```css
@media (display-mode: standalone) {
  .pasang-app { display: none; }
}
```

**Biasanya digabungkan dengan:** manifest PWA.

## @media print

**Untuk apa:** gaya cetak / PDF.

```css
@media print {
  .nav, .iklan, .tombol { display: none; }
  a[href]::after { content: " (" attr(href) ")"; }
  body { background: white; color: black; }
}
```

**Biasanya digabungkan dengan:** `attr()`, `@page`.

## Operator and or not

**Untuk apa:** menggabungkan kondisi.

```css
@media (min-width: 48rem) and (hover: hover) {
  .tip { display: block; }
}

@media not print {
  .hanya-layar { background: #0f172a; }
}

@media (min-width: 40rem), (orientation: landscape) {
  .galeri { grid-template-columns: 1fr 1fr; }
}
```

Koma = atau. `and` = kedua wajib. `not` membalik query.

**Biasanya digabungkan dengan:** hover + lebar.

## Range syntax

**Untuk apa:** menulis rentang tanpa `min-`/`max-`.

```css
@media (width >= 40rem) { }
@media (40rem <= width < 64rem) { }
@media (height < 30rem) { }
```

Lebih mudah dibaca. Browser modern. Fallback: `min-width` + `max-width`.

**Biasanya digabungkan dengan:** mobile-first tetap memakai `width >=`.

## @supports

**Untuk apa:** fallback jika properti/selector belum ada.

```css
.grid-sederhana { display: flex; flex-wrap: wrap; }

@supports (display: grid) {
  .grid-sederhana { display: grid; grid-template-columns: repeat(3, 1fr); }
}

@supports selector(:has(*)) {
  form:has(:invalid) .banner { display: block; }
}

@supports not (backdrop-filter: blur(4px)) {
  .header { background: white; }
}
```

Jangan bungkus seluruh layout modern jika target browser sudah mendukung Grid (semua browser kelas saat ini). Berguna untuk `:has`, `subgrid`, `text-wrap: pretty`.

**Biasanya digabungkan dengan:** fitur sangat baru, bukan Flex vs Grid di 2026.

## @container

**Untuk apa:** gaya berdasarkan **lebar wadah**, bukan layar. Kartu di sidebar sempit bisa satu kolom meski desktop lebar.

### container-type

**Untuk apa:** menjadikan elemen container.

```css
.kartu {
  container-type: inline-size;
  container-name: kartu;
}
```

`inline-size` paling umum (lebar di LTR). `size` butuh tinggi terdefinisi. `normal` mematikan.

**Biasanya digabungkan dengan:** `@container`, unit `cqi`.

### container shorthand

```css
.kartu { container: kartu / inline-size; }
```

Nama / tipe.

**Biasanya digabungkan dengan:** beberapa container bersarang.

### query

```css
@container kartu (min-width: 20rem) {
  .kartu-badan { display: grid; grid-template-columns: 6rem 1fr; gap: 1rem; }
}

@container (width >= 30rem) {
  .aksi { justify-content: flex-end; }
}
```

Tanpa nama: container terdekat. Dengan nama: meloncat ke container bernama.

**Biasanya digabungkan dengan:** komponen yang dipakai di sidebar dan di konten.

### Unit cqi cqb cqw cqh

**Untuk apa:** 1% ukuran container.

```css
.kartu h2 { font-size: clamp(1rem, 2.5cqi + 0.8rem, 1.4rem); }
```

**Biasanya digabungkan dengan:** `container-type: inline-size`.

### style query

**Untuk apa:** query nilai custom property (dukungan berkembang).

```css
@container style(--layout: horizontal) {
  .isi { display: flex; }
}
```

**Biasanya digabungkan dengan:** token komponen; cek dukungan sebelum jadi syarat tugas.

## @layer

**Untuk apa:** mengunci prioritas kelompok, terlepas dari spesifisitas antar layer.

```css
@layer reset, tokens, dasar, komponen, utilitas;

@layer reset {
  *, *::before, *::after { box-sizing: border-box; }
  body { margin: 0; }
}

@layer tokens {
  :root { --bg: #f8fafc; --fg: #0f172a; }
}

@layer dasar {
  body { background: var(--bg); color: var(--fg); line-height: 1.6; }
  a { color: #0f766e; }
}

@layer komponen {
  .tombol { color: white; background: #0f172a; }
}

@layer utilitas {
  .text-merah { color: #b91c1c; }
}
```

Layer yang declared belakangan menang. `.text-merah` mengalahkan `.tombol` meski sama-sama satu class.

Aturan **di luar** `@layer` (unlayered) mengalahkan semua layer, kecuali `!important` yang terbalik (penting di layer lebih awal bisa menang — pelajari saat butuh, jangan andalkan).

```css
@import "tailwindcss/base" layer(reset);
```

**Biasanya digabungkan dengan:** Tailwind, reset, file komponen.

## @scope

**Untuk apa:** membatasi selector ke subtree tanpa menaikkan spesifisitas seperti `#app .kartu`.

```css
@scope (.kartu) {
  h2 { margin-top: 0; }
  p { color: #334155; }
}
```

Setara `.kartu h2` tetapi isolasi lebih jelas. Bisa donut scope: `@scope (.kartu) to (.isi)`.

**Biasanya digabungkan dengan:** komponen, nesting. Cek dukungan target.

## @import

**Untuk apa:** menarik stylesheet lain. Harus di dekat awal file, sebelum aturan biasa (kecuali `@charset` / `@layer`).

```css
@import url("reset.css") layer(reset);
@import "tokens.css" layer(tokens);
@import url("print.css") print;
```

Banyak `@import` menunda render. Di produksi, bundler biasanya menggabungkan.

**Biasanya digabungkan dengan:** `layer()`, media query.

## Nesting

**Untuk apa:** menulis selector anak di dalam blok.

```css
.kartu {
  padding: 1rem;

  & h2 { margin-top: 0; }

  &:hover { box-shadow: 0 8px 20px rgb(15 23 42 / 0.1); }

  @media (min-width: 48rem) {
    padding: 1.5rem;
  }
}
```

`&` wajib saat menyambung pseudo (`&:hover`). Media query di dalam nest berlaku untuk selector luar.

**Biasanya digabungkan dengan:** komponen, `@layer komponen`.

## Custom property dan @property

### var()

**Untuk apa:** membaca variabel. Pewarisan mengikuti pohon.

```css
:root { --pad: 1rem; }
.kartu { padding: var(--pad, 0.75rem); }
```

Argumen kedua = fallback.

**Biasanya digabungkan dengan:** tema, `calc(var(--header-h) + 0.5rem)`.

### @property

**Untuk apa:** mendaftarkan tipe agar variabel bisa dianimasikan.

```css
@property --sudut {
  syntax: "<angle>";
  inherits: false;
  initial-value: 0deg;
}

.pie { background: conic-gradient(#0f766e var(--sudut), #e2e8f0 0); }
.pie.isi { --sudut: 140deg; transition: --sudut 400ms; }
```

Tanpa `@property`, browser sering tidak menginterpolasi custom property.

**Biasanya digabungkan dengan:** gradien animasi, progress.

## Peta Tailwind breakpoint

Default Tailwind v3:

| Prefix | min-width |
| --- | --- |
| (tanpa) | semua |
| `sm:` | 640px |
| `md:` | 768px |
| `lg:` | 1024px |
| `xl:` | 1280px |
| `2xl:` | 1536px |

```html
<ul class="grid grid-cols-1 gap-4 sm:grid-cols-2 lg:grid-cols-3">
```

`max-sm:` = di bawah `sm`. `md:max-lg:` = dari md sampai di bawah lg.

Container query Tailwind v3.2+ / v4:

```html
<div class="@container">
  <div class="@md:flex @md:gap-4">
```

`@md` di sini adalah breakpoint **container**, bukan layar.

**Biasanya digabungkan dengan:** `grid-cols-1` sebagai default HP.

## Checklist

1. Ada meta viewport?
2. Default = HP, query menambah?
3. Hover tidak jadi satu-satunya petunjuk?
4. Kartu harus peduli wadah atau layar? Jika wadah → `@container`.
5. Utility vs komponen perang? → `@layer`.
6. Reduced motion dihormati?
