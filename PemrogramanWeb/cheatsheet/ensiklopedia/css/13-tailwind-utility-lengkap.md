# 13 — Tailwind utility lengkap

[← Tabel properti](12-tabel-properti-lengkap.md) · [Indeks](README.md) · [Resep →](14-resep-dan-kesalahan.md)

Tailwind menulis CSS lewat **class utilitas**. Satu class ≈ satu deklarasi. Yang kamu hafal di bab CSS tetap berlaku; ini hanya peta namanya.

Contoh memakai skala default Tailwind v3. Proyek v4 + `@theme` bisa mengubah angka. Cek `tailwind.config` / `@theme` sebelum berdebat dengan asisten.

## Daftar isi

- [Cara baca class](#cara-baca-class)
- [Skala spacing](#skala-spacing)
- [Padding](#padding)
- [Margin](#margin)
- [Space between](#space-between)
- [Gap size width height](#gap-size-width-height)
- [Warna](#warna)
- [Tipografi](#tipografi)
- [Flex](#flex)
- [Grid](#grid)
- [Position inset z-index](#position-inset-z-index)
- [Border radius outline ring](#border-radius-outline-ring)
- [Effect](#effect)
- [Overflow object](#overflow-object)
- [Interaksi](#interaksi)
- [State hover focus peer group](#state-hover-focus-peer-group)
- [Breakpoint](#breakpoint)
- [Arbitrary values](#arbitrary-values)
- [dark rtl important](#dark-rtl-important)
- [Pola class yang sering](#pola-class-yang-sering)

## Cara baca class

**Untuk apa:** memecah string class jadi CSS di kepala.

```html
<button class="md:hover:bg-slate-900 md:hover:text-white">
```

Dibaca dari kiri prefix ke utility: pada `md` ke atas, saat `hover`, `background = slate-900` dan `color = white`.

Urutan di HTML tidak menentukan kemenangan (kecuali dua class sama spesifik di sumber generated). Konflik `p-2 p-8` = yang belakangan di CSS generated, bukan di atribut. Jangan tulis keduanya.

**Biasanya digabungkan dengan:** satu niat per class, `clsx` / `cn()` di React.

## Skala spacing

**Untuk apa:** angka padding/margin/gap/position.

Jika `1rem = 16px`:

| Class number | rem | px |
| --- | --- | --- |
| `0` | 0 | 0 |
| `px` | 1px | 1px |
| `0.5` | 0.125 | 2 |
| `1` | 0.25 | 4 |
| `1.5` | 0.375 | 6 |
| `2` | 0.5 | 8 |
| `2.5` | 0.625 | 10 |
| `3` | 0.75 | 12 |
| `3.5` | 0.875 | 14 |
| `4` | 1 | 16 |
| `5` | 1.25 | 20 |
| `6` | 1.5 | 24 |
| `7` | 1.75 | 28 |
| `8` | 2 | 32 |
| `9` | 2.25 | 36 |
| `10` | 2.5 | 40 |
| `11` | 2.75 | 44 |
| `12` | 3 | 48 |
| `14` | 3.5 | 56 |
| `16` | 4 | 64 |
| `20` | 5 | 80 |
| `24` | 6 | 96 |
| `28` | 7 | 112 |
| `32` | 8 | 128 |
| `36` | 9 | 144 |
| `40` | 10 | 160 |
| `44` | 11 | 176 |
| `48` | 12 | 192 |
| `52` | 13 | 208 |
| `56` | 14 | 224 |
| `60` | 15 | 240 |
| `64` | 16 | 256 |
| `72` | 18 | 288 |
| `80` | 20 | 320 |
| `96` | 24 | 384 |

`p-4` = padding 1rem. `gap-2` = 0.5rem. `top-3` = 0.75rem.

**Biasanya digabungkan dengan:** `rem` di CSS murni agar terasa sama.

## Padding

**Untuk apa:** ruang dalam.

```html
<section class="p-4">...</section>
<section class="px-4 py-6">...</section>
<section class="pt-2 pr-4 pb-8 pl-3">...</section>
<section class="ps-4 pe-2">...</section>
```

| Class | CSS |
| --- | --- |
| `p-4` | `padding: 1rem` |
| `px-4` | `padding-inline: 1rem` |
| `py-4` | `padding-block: 1rem` |
| `pt pr pb pl` | atas kanan bawah kiri |
| `ps pe` | inline-start / inline-end (RTL-aware) |
| `p-px` | `1px` |
| `p-0` | `0` |

**Biasanya digabungkan dengan:** `bg-*`, `rounded-*`, `border`.

## Margin

**Untuk apa:** ruang luar. Nilai negatif pakai minus di depan.

```html
<h2 class="mt-8 mb-2">Judul</h2>
<div class="mx-auto w-full max-w-3xl">...</div>
<div class="-mt-4">tarik ke atas</div>
```

| Class | CSS |
| --- | --- |
| `m-4` | `margin: 1rem` |
| `mx-auto` | `margin-inline: auto` |
| `my-0` | `margin-block: 0` |
| `mt-auto` | `margin-top: auto` (dorong ke bawah di flex col) |
| `ms-auto` | dorong ke end (navbar RTL-aman) |
| `-mx-4` | margin negatif horizontal (full-bleed ringan) |

**Biasanya digabungkan dengan:** `max-w-*`, flex `mt-auto`.

## Space between

**Untuk apa:** jarak antar anak lewat selector `> * + *`, tanpa flex gap (berguna kalau bukan flex/grid).

```html
<ul class="space-y-2">
  <li>Satu</li>
  <li>Dua</li>
</ul>
<div class="flex space-x-3">...</div>
```

`space-x-3` memasang `margin-inline-start` pada anak selain pertama. Lebih modern: `flex gap-3` — tidak berantakan dengan wrap.

**Biasanya digabungkan dengan:** stack vertikal non-flex; prefer `gap` jika sudah flex/grid.

## Gap size width height

### gap

**Untuk apa:** jarak flex/grid.

```html
<div class="flex gap-4">
<div class="grid gap-x-4 gap-y-6">
```

**Biasanya digabungkan dengan:** `flex`, `grid`.

### width height size

**Untuk apa:** ukuran kotak.

```html
<img class="h-12 w-12" alt="">
<div class="size-10">ikon</div>
<div class="w-full max-w-xl">
<div class="w-1/2">
<div class="w-screen">
<div class="min-h-dvh">
<div class="min-w-0">
```

| Class | CSS |
| --- | --- |
| `w-full` | `width: 100%` |
| `w-screen` | `100vw` |
| `w-min` `w-max` `w-fit` | `min-content` / `max-content` / `fit-content` |
| `w-1/2` `w-1/3` `w-2/3` `w-1/4` | pecahan |
| `w-11/12` | 91.6% |
| `max-w-xs` | 20rem |
| `max-w-sm` | 24rem |
| `max-w-md` | 28rem |
| `max-w-lg` | 32rem |
| `max-w-xl` | 36rem |
| `max-w-2xl` | 42rem |
| `max-w-3xl` | 48rem |
| `max-w-4xl` | 56rem |
| `max-w-5xl` | 64rem |
| `max-w-6xl` | 72rem |
| `max-w-7xl` | 80rem |
| `max-w-prose` | 65ch |
| `max-w-screen-sm` … `2xl` | sama seperti breakpoint |
| `min-w-0` | `min-width: 0` |
| `h-auto` | `height: auto` |
| `h-full` | `100%` |
| `h-screen` | `100vh` |
| `h-dvh` `h-svh` `h-lvh` | viewport dinamis/kecil/besar |
| `min-h-dvh` | halaman penuh HP |
| `size-8` | `width`+`height` 2rem |

**Biasanya digabungkan dengan:** `mx-auto`, `min-w-0` pada flex child.

## Warna

### Palet

**Untuk apa:** nama warna + angka ketebalan 50–950.

Paling sering: `slate`, `gray`, `zinc`, `neutral`, `stone`, `red`, `orange`, `amber`, `yellow`, `lime`, `green`, `emerald`, `teal`, `cyan`, `sky`, `blue`, `indigo`, `violet`, `purple`, `fuchsia`, `pink`, `rose`. Plus `white`, `black`, `transparent`, `current`.

Angka: `50` hampir putih, `500` sedang, `900`/`950` hampir hitam.

```html
<p class="bg-slate-50 text-slate-900">
<button class="bg-emerald-700 text-white hover:bg-emerald-800">
```

**Biasanya digabungkan dengan:** kontras `text-*` vs `bg-*` (jangan `text-slate-400` di `bg-white` untuk teks panjang).

### Prefix warna

| Prefix | Properti |
| --- | --- |
| `bg-sky-600` | `background-color` |
| `text-slate-700` | `color` |
| `border-slate-200` | `border-color` |
| `outline-sky-500` | `outline-color` |
| `ring-sky-400` | ring (box-shadow) |
| `from-sky-500` `via-cyan-400` `to-emerald-400` | stop gradien |
| `accent-emerald-600` | `accent-color` |
| `caret-emerald-600` | `caret-color` |
| `decoration-sky-500` | `text-decoration-color` |
| `shadow-slate-900/10` | warna bayangan (v3+) |
| `fill-current` `stroke-current` | SVG |

Alpha: `bg-slate-900/60` = 60% opak. `bg-black/40` overlay.

**Biasanya digabungkan dengan:** `hover:bg-*`, `dark:bg-*`.

### Gradien

```html
<div class="bg-gradient-to-r from-teal-700 to-sky-800 text-white">
<div class="bg-gradient-to-b from-black/50 to-transparent">
```

Arah: `to-t` `to-tr` `to-r` `to-br` `to-b` `to-bl` `to-l` `to-tl`.

**Biasanya digabungkan dengan:** overlay hero, `from-black/50`.

## Tipografi

```html
<h1 class="text-3xl font-bold tracking-tight text-balance">
<p class="max-w-prose text-base leading-7 text-slate-600">
```

### font-size

| Class | ukuran kasar |
| --- | --- |
| `text-xs` | 0.75rem / 12px + line-height |
| `text-sm` | 0.875rem / 14px |
| `text-base` | 1rem / 16px |
| `text-lg` | 1.125rem |
| `text-xl` | 1.25rem |
| `text-2xl` | 1.5rem |
| `text-3xl` | 1.875rem |
| `text-4xl` | 2.25rem |
| `text-5xl` … `text-9xl` | display |

Arbitrary: `text-[clamp(1.75rem,4vw,3rem)]`.

**Biasanya digabungkan dengan:** `font-bold`, `leading-*`, `text-balance`.

### weight style family

| Class | CSS |
| --- | --- |
| `font-thin` … `font-black` | 100–900 |
| `font-normal` | 400 |
| `font-medium` | 500 |
| `font-semibold` | 600 |
| `font-bold` | 700 |
| `italic` `not-italic` | font-style |
| `font-sans` `font-serif` `font-mono` | family tema |

**Biasanya digabungkan dengan:** `tracking-*` pada judul.

### leading tracking align decoration

| Class | CSS |
| --- | --- |
| `leading-none` | `line-height: 1` |
| `leading-tight` | 1.25 |
| `leading-snug` | 1.375 |
| `leading-normal` | 1.5 |
| `leading-relaxed` | 1.625 |
| `leading-loose` | 2 |
| `leading-7` | `1.75rem` |
| `tracking-tighter` … `tracking-widest` | letter-spacing |
| `text-left` `text-center` `text-right` `text-justify` `text-start` `text-end` | text-align |
| `underline` `line-through` `no-underline` | decoration |
| `decoration-2` `underline-offset-4` | ketebalan/offset |
| `uppercase` `lowercase` `capitalize` `normal-case` | transform |
| `truncate` | nowrap + hidden + ellipsis |
| `text-ellipsis` `text-clip` | text-overflow |
| `whitespace-nowrap` `whitespace-pre` `whitespace-pre-wrap` | white-space |
| `break-words` `break-all` `break-keep` | wrap |
| `line-clamp-2` `line-clamp-3` `line-clamp-none` | clamp |
| `text-balance` `text-pretty` | text-wrap |
| `align-middle` `align-top` `align-text-bottom` | vertical-align |
| `list-none` `list-disc` `list-decimal` | list-style |
| `list-inside` `list-outside` | position |

`truncate` wajib induk flex/grid child punya `min-w-0`.

**Biasanya digabungkan dengan:** `min-w-0`, `max-w-prose`.

## Flex

Lihat [bab 04](04-flexbox-semua-properti.md) untuk arti properti.

```html
<nav class="flex flex-wrap items-center justify-between gap-4">
<button class="inline-flex items-center justify-center gap-2">
<main class="flex min-h-dvh flex-col">
  <div class="flex-1">isi</div>
</main>
```

| Class | CSS |
| --- | --- |
| `flex` | `display: flex` |
| `inline-flex` | `inline-flex` |
| `flex-row` `flex-col` | direction |
| `flex-row-reverse` `flex-col-reverse` | reverse |
| `flex-wrap` `flex-nowrap` `flex-wrap-reverse` | wrap |
| `justify-start` `justify-end` `justify-center` | justify-content |
| `justify-between` `justify-around` `justify-evenly` `justify-stretch` | |
| `items-start` `items-end` `items-center` `items-baseline` `items-stretch` | align-items |
| `content-start` `content-center` `content-between` … | align-content |
| `self-start` `self-center` `self-stretch` `self-end` | align-self |
| `flex-1` `flex-auto` `flex-none` `flex-initial` | flex shorthand |
| `grow` `grow-0` | flex-grow |
| `shrink` `shrink-0` | flex-shrink |
| `basis-0` `basis-1/2` `basis-64` `basis-full` `basis-auto` | flex-basis |
| `order-first` `order-last` `order-1` `-order-1` | order |

**Biasanya digabungkan dengan:** `min-w-0` pada `flex-1` teks, `gap-*`.

## Grid

```html
<ul class="grid grid-cols-1 gap-4 sm:grid-cols-2 xl:grid-cols-3">
<header class="grid grid-cols-[auto_1fr_auto] items-center gap-4">
<div class="col-span-2">
<div class="col-span-full">
```

| Class | CSS |
| --- | --- |
| `grid` `inline-grid` | display |
| `grid-cols-1` … `grid-cols-12` | `repeat(n, minmax(0,1fr))` |
| `grid-cols-none` | none |
| `grid-cols-subgrid` | subgrid |
| `grid-rows-2` | rows |
| `grid-flow-row` `grid-flow-col` `grid-flow-dense` | auto-flow |
| `auto-rows-auto` `auto-rows-fr` `auto-rows-min` | auto-rows |
| `auto-cols-auto` `auto-cols-fr` | auto-columns |
| `col-span-2` `col-span-full` | grid-column span |
| `col-start-2` `col-end-4` | garis |
| `row-span-2` `row-start-1` | baris |
| `justify-items-start` `justify-items-center` `justify-items-stretch` | |
| `place-items-center` `place-content-center` `place-self-end` | |

Arbitrary katalog:

```html
<ul class="grid grid-cols-[repeat(auto-fit,minmax(min(100%,15rem),1fr))] gap-4">
```

Catatan: `grid-cols-3` memakai `minmax(0,1fr)` — lebih aman terhadap overflow daripada `1fr` mentah.

**Biasanya digabungkan dengan:** `sm:`, `lg:`, `gap-4`.

## Position inset z-index

```html
<article class="relative">
  <span class="absolute right-3 top-3 z-10">Baru</span>
</article>
<header class="sticky top-0 z-10">
<div class="fixed inset-0 z-40 bg-black/50">
```

| Class | CSS |
| --- | --- |
| `static` `relative` `absolute` `fixed` `sticky` | position |
| `inset-0` | `inset: 0` |
| `inset-x-0` `inset-y-4` | sumbu |
| `top-0` `right-3` `bottom-4` `left-1/2` | sisi |
| `start-0` `end-3` | logis |
| `-top-2` | negatif |
| `z-0` `z-10` `z-20` `z-30` `z-40` `z-50` `z-auto` | z-index |
| `isolate` `isolation-auto` | isolation |
| `float-left` `float-right` `float-none` | float |
| `clear-both` `clear-start` | clear |

Tengah absolute: `absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-1/2`.

**Biasanya digabungkan dengan:** `scroll-mt-20` pada heading.

## Border radius outline ring

```html
<button class="rounded-md border border-slate-200 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-sky-500 focus-visible:ring-offset-2">
```

| Class | CSS |
| --- | --- |
| `border` | `1px solid` + warna default |
| `border-0` `border-2` `border-4` | width |
| `border-t` `border-b` `border-s` | satu sisi |
| `border-dashed` `border-dotted` `border-none` | style |
| `rounded` | 0.25rem |
| `rounded-sm` `rounded-md` `rounded-lg` `rounded-xl` `rounded-2xl` `rounded-3xl` | skala |
| `rounded-full` | 9999px |
| `rounded-t-lg` `rounded-s-md` | sisi |
| `outline` `outline-2` `outline-offset-2` | outline |
| `outline-none` | hapus outline — wajib ganti ring |
| `ring` `ring-2` `ring-inset` | box-shadow ring |
| `ring-offset-2` `ring-offset-white` | jarak + warna “lubang” |
| `divide-y` `divide-slate-200` | border antar anak |
| `divide-x-2` | vertikal |

**Biasanya digabungkan dengan:** `focus-visible:ring-*`, `hover:border-*`.

## Effect

```html
<article class="shadow-sm transition hover:-translate-y-1 hover:shadow-lg">
<header class="bg-white/80 backdrop-blur">
<img class="grayscale hover:grayscale-0">
```

| Class | CSS |
| --- | --- |
| `shadow-sm` `shadow` `shadow-md` `shadow-lg` `shadow-xl` `shadow-2xl` `shadow-none` `shadow-inner` | box-shadow |
| `opacity-0` … `opacity-100` | opacity |
| `blur` `blur-sm` `blur-lg` `blur-none` | filter blur |
| `brightness-75` `contrast-125` `grayscale` `invert` `sepia` `saturate-50` `hue-rotate-15` | filter |
| `drop-shadow-md` | filter drop-shadow |
| `backdrop-blur` `backdrop-blur-md` `backdrop-brightness-75` | backdrop-filter |
| `mix-blend-multiply` `mix-blend-difference` | mix-blend-mode |
| `bg-blend-multiply` | background-blend-mode |
| `scale-95` `scale-100` `scale-105` | scale |
| `rotate-45` `-rotate-2` `rotate-180` | rotate |
| `translate-y-1` `-translate-y-1` `translate-x-1/2` | translate |
| `skew-x-12` | skew |
| `origin-center` `origin-top` `origin-top-right` | transform-origin |
| `transition` `transition-colors` `transition-transform` `transition-opacity` `transition-none` | transition-property |
| `duration-150` `duration-200` `duration-300` | duration |
| `ease-linear` `ease-in` `ease-out` `ease-in-out` | timing |
| `delay-100` | delay |
| `animate-spin` `animate-ping` `animate-pulse` `animate-bounce` `animate-none` | animation |

**Biasanya digabungkan dengan:** `motion-reduce:transition-none`, `hover:`.

## Overflow object

```html
<img class="h-48 w-full object-cover">
<pre class="overflow-x-auto">
<p class="min-w-0 truncate">
```

| Class | CSS |
| --- | --- |
| `overflow-auto` `overflow-hidden` `overflow-scroll` `overflow-visible` `overflow-clip` | overflow |
| `overflow-x-auto` `overflow-y-hidden` | sumbu |
| `overscroll-contain` `overscroll-none` | overscroll |
| `scroll-smooth` | scroll-behavior |
| `scroll-mt-20` | scroll-margin-top |
| `snap-x` `snap-mandatory` `snap-center` `snap-start` | snap |
| `object-contain` `object-cover` `object-fill` `object-none` `object-scale-down` | object-fit |
| `object-center` `object-top` `object-left-top` | object-position |
| `aspect-auto` `aspect-square` `aspect-video` | 16/9 = video |
| `sr-only` `not-sr-only` | secara visual sembunyi, tetap ke SR |

**Biasanya digabungkan dengan:** `rounded-*` + `overflow-hidden`.

## Interaksi

| Class | CSS |
| --- | --- |
| `cursor-pointer` `cursor-not-allowed` `cursor-grab` `cursor-wait` | cursor |
| `pointer-events-none` `pointer-events-auto` | pointer-events |
| `select-none` `select-text` `select-all` | user-select |
| `touch-pan-y` `touch-none` | touch-action |
| `resize-y` `resize-none` | resize |
| `appearance-none` | appearance |

**Biasanya digabungkan dengan:** `disabled:cursor-not-allowed`.

## State hover focus peer group

### User state

| Prefix | Kapan |
| --- | --- |
| `hover:` | kursor di atas |
| `focus:` | fokus (termasuk klik) |
| `focus-visible:` | fokus keyboard |
| `focus-within:` | anak berfokus |
| `active:` | sedang ditekan |
| `visited:` | tautan dikunjungi |
| `disabled:` | disabled |
| `enabled:` | tidak disabled |
| `checked:` | checkbox/radio |
| `required:` `optional:` | form |
| `valid:` `invalid:` | validasi native |
| `placeholder-shown:` | masih kosong + placeholder |
| `autofill:` | diisi browser |
| `read-only:` | readonly |

```html
<input class="border focus:border-sky-500 focus-visible:outline-none focus-visible:ring-2">
<button class="disabled:opacity-50 disabled:cursor-not-allowed" disabled>
```

**Biasanya digabungkan dengan:** gaya default + satu state, bukan hanya hover.

### Struktural

| Prefix | Kapan |
| --- | --- |
| `first:` `last:` `only:` | anak |
| `odd:` `even:` | nth |
| `first-of-type:` `last-of-type:` | tipe |
| `empty:` | :empty |

```html
<ul class="divide-y">
  <li class="py-2 first:pt-0 last:pb-0">
```

**Biasanya digabungkan dengan:** `divide-y`.

### Pseudo-element

| Prefix | Target |
| --- | --- |
| `before:` `after:` | ::before/after — butuh `before:content-['']` |
| `placeholder:` | ::placeholder |
| `file:` | tombol file |
| `marker:` | ::marker |
| `selection:` | ::selection |
| `backdrop:` | ::backdrop |
| `first-letter:` `first-line:` | prosa |

```html
<label class="after:ml-0.5 after:text-red-600 after:content-['*']">Nama
```

**Biasanya digabungkan dengan:** `relative` jika before absolute.

### group

**Untuk apa:** state induk mengontrol anak.

```html
<a class="group block rounded-xl p-4 hover:bg-slate-50">
  <h2 class="group-hover:text-sky-700">Judul</h2>
  <p class="text-slate-600">Ringkasan</p>
</a>
```

Beberapa group: `group/kartu` lalu `group-hover/kartu:`.

**Biasanya digabungkan dengan:** kartu yang seluruhnya tautan.

### peer

**Untuk apa:** state **saudara sebelumnya** mengontrol elemen berikutnya.

```html
<input id="s" type="checkbox" class="peer sr-only">
<label for="s" class="peer-checked:bg-emerald-600">Toggle</label>
<p class="hidden peer-invalid:block text-red-700">Email tidak valid</p>
```

`peer` harus **sebelum** elemen yang memakai `peer-*` di DOM.

**Biasanya digabungkan dengan:** switch, pesan error, checkbox hack.

### has-

**Untuk apa:** prefix `:has()`.

```html
<label class="has-[:checked]:border-emerald-600">
<form class="has-[:invalid]:ring-1 has-[:invalid]:ring-red-300">
```

**Biasanya digabungkan dengan:** form, kartu berisi gambar `has-[img]:p-0`.

### aria dan data

```html
<button class="aria-expanded:rotate-180" aria-expanded="true">
<div class="data-[open=true]:block hidden">
```

**Biasanya digabungkan dengan:** komponen JS (Headless UI, Radix).

## Breakpoint

Mobile-first: class tanpa prefix = semua lebar. Prefix = **min-width** itu ke atas.

| Prefix | min-width |
| --- | --- |
| `sm:` | 640px |
| `md:` | 768px |
| `lg:` | 1024px |
| `xl:` | 1280px |
| `2xl:` | 1536px |

Max dan range:

| Prefix | Arti |
| --- | --- |
| `max-sm:` | &lt; 640px |
| `max-md:` | &lt; 768px |
| `md:max-lg:` | 768–1023px |

```html
<div class="flex flex-col gap-3 md:flex-row md:items-center">
<p class="text-sm md:text-base">
<aside class="max-md:hidden">sidebar hanya tablet+
```

Target perangkat:

| Prefix | Media |
| --- | --- |
| `motion-reduce:` | prefers-reduced-motion |
| `motion-safe:` | no reduce |
| `dark:` | class `.dark` atau media (tergantung config) |
| `contrast-more:` | prefers-contrast |
| `forced-colors:` | forced-colors |
| `print:` | cetak |
| `portrait:` `landscape:` | orientation |
| `pointer-fine:` `pointer-coarse:` | pointer |
| `hover:` sebagai variant perangkat di v4 / plugin — hati-hati jangan tertukar dengan state hover |

Di v3, `hover:` adalah state, bukan media `hover: hover`. Untuk media, pakai raw: `[@media(hover:hover)]:hover:-translate-y-1` atau plugin.

Container (v4 / `@tailwindcss/container-queries`):

```html
<div class="@container">
  <div class="flex flex-col @min-[20rem]:flex-row">
```

**Biasanya digabungkan dengan:** default `grid-cols-1`.

## Arbitrary values

**Untuk apa:** nilai yang tidak ada di skala, ditulis dalam `[]`.

```html
<div class="w-[17.5rem] bg-[#164863] top-[calc(var(--header)+0.5rem)]">
<div class="grid grid-cols-[16rem_minmax(0,1fr)]">
<p class="text-[clamp(1rem,2vw,1.25rem)]">
<div class="shadow-[0_8px_24px_rgb(15_23_42/0.12)]">
```

Arbitrary property (properti apa pun):

```html
<div class="[counter-increment:langkah] [--pad:1.25rem] p-[var(--pad)]">
```

Arbitrary variant:

```html
<div class="[&_img]:rounded-lg [&_a]:underline">
<ul class="[&>li]:border-b">
```

`_` di dalam arbitrary = spasi.

**Biasanya digabungkan dengan:** token desain yang tidak ada di palet, bukan sebagai kebiasaan setiap class.

### Arbitrary vs extend theme

Kalau `bg-[#164863]` muncul 20 kali, lebih sehat tambah warna di config:

```js
theme: { extend: { colors: { papua: "#164863" } } }
```

Lalu `bg-papua`.

**Biasanya digabungkan dengan:** satu sumber token.

## dark rtl important

### dark

**Untuk apa:** tema gelap.

```html
<html class="dark">
<body class="bg-white text-slate-900 dark:bg-slate-950 dark:text-slate-100">
```

Config `darkMode: 'class'` (umum) vs `'media'` (ikut OS).

**Biasanya digabungkan dengan:** `color-scheme`, tombol toggle.

### RTL

```html
<div class="ms-auto text-start">
<div class="rtl:rotate-180">
```

Prefer `ps`/`pe`/`ms`/`me`/`start`/`end` daripada `pl`/`ml` + `rtl:`.

**Biasanya digabungkan dengan:** `dir="rtl"`.

### important

```html
<div class="!p-0">
```

`!` menambah `!important`. Senjata terakhir, sama seperti CSS.

**Biasanya digabungkan dengan:** menimpa class pihak ketiga.

### @layer dan @apply

**Untuk apa:** menulis komponen di CSS memakai utility.

```css
@layer components {
  .tombol {
    @apply inline-flex items-center rounded-md bg-slate-900 px-3 py-2 text-white;
  }
}
```

Jangan `@apply` berantai panjang sampai tidak kebaca. Utility di HTML tetap lebih jujur untuk tugas React.

**Biasanya digabungkan dengan:** `@layer components`, bukan utilitas yang hanya dipakai sekali.

## Pola class yang sering

### Halaman terpusat

```html
<main class="mx-auto w-full max-w-5xl px-4 py-8">
```

**Biasanya digabungkan dengan:** `min-h-dvh`.

### Navbar

```html
<header class="sticky top-0 z-10 flex flex-wrap items-center justify-between gap-4 border-b bg-white/90 px-4 py-3 backdrop-blur">
  <a class="font-semibold" href="/">Toko</a>
  <nav class="flex flex-wrap items-center gap-3">
    <a class="hover:underline" href="/produk">Produk</a>
  </nav>
</header>
```

**Biasanya digabungkan dengan:** `scroll-mt-24` pada section.

### Kartu

```html
<article class="flex flex-col overflow-hidden rounded-xl border border-slate-200 bg-white shadow-sm">
  <img class="aspect-video w-full object-cover" alt="">
  <div class="flex flex-1 flex-col gap-2 p-4">
    <h2 class="text-lg font-semibold">Nama</h2>
    <p class="line-clamp-3 text-sm text-slate-600">...</p>
    <a class="mt-auto text-sm font-medium text-sky-700" href="#">Detail</a>
  </div>
</article>
```

**Biasanya digabungkan dengan:** induk `grid`.

### Form field

```html
<label class="block space-y-1">
  <span class="text-sm font-medium">Email</span>
  <input class="w-full rounded-md border border-slate-300 px-3 py-2 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-sky-500">
</label>
```

**Biasanya digabungkan dengan:** `peer` untuk error.

### Overlay modal

```html
<div class="fixed inset-0 z-40 grid place-items-center bg-slate-900/50 p-4">
  <div class="max-h-[80dvh] w-full max-w-lg overflow-auto rounded-xl bg-white p-6">
```

**Biasanya digabungkan dengan:** `html:has(dialog[open]):overflow-hidden` atau class `overflow-hidden` di body.

## Checklist class

1. Konflik `p-2 p-8`? Sisakan satu.
2. Flex child teks? `min-w-0`.
3. Fokus keyboard? `focus-visible:ring` atau `outline`.
4. HP dulu: tanpa prefix, lalu `md:`.
5. Hover bukan satu-satunya petunjuk.
6. `outline-none` tanpa ring = bug aksesibilitas.
7. `w-screen` sering menyebabkan scrollbar horizontal; prefer `w-full`.
