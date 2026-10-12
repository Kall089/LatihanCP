# Ensiklopedia CSS + Tailwind

Katalog API tampilan web. Setiap entri menjawab tiga hal: **untuk apa**, **kode + penjelasan**, dan **biasanya digabung dengan apa**. Bahasa yang dipakai sama seperti menjelaskan ke teman satu praktikum.

Bukan ringkasan singkat. File di folder ini membedah selector, properti, nilai, dan utility Tailwind satu per satu. Cheatsheet ringkas tetap ada di [css.md](../../css.md). Pakai folder ini kalau kamu butuh “properti ini ada, nilainya apa, biasanya dipasang bareng apa”.

## Cara baca

1. Buka Markdown Preview.
2. Mulai dari [kaskade dan selector](01-kaskade-selector-spesifisitas.md) kalau selectormu kalah misterius.
3. Lanjut ke box model, satuan, Flexbox, lalu Grid. Itu urutan yang paling sering dipakai di tugas.
4. Tailwind ada di [bab 13](13-tailwind-utility-lengkap.md). Utility-nya hampir selalu terjemahan 1:1 dari properti CSS di bab sebelumnya.
5. Kalau lupa nama properti, buka [tabel properti](12-tabel-properti-lengkap.md). Kalau layout-nya berantakan, buka [resep dan kesalahan](14-resep-dan-kesalahan.md).

Format tiap entri:

```text
**Untuk apa:**
kode
penjelasan singkat
**Biasanya digabungkan dengan:**
```

Contoh kode adalah potongan terpisah, bukan satu proyek utuh. Jangan menempelkan semua contoh ke satu file HTML.

## Daftar bab

| File | Isi |
| --- | --- |
| [01-kaskade-selector-spesifisitas.md](01-kaskade-selector-spesifisitas.md) | Cara CSS dipilih: origin, `!important`, `@layer`, pewarisan, hitungan spesifisitas, selector tipe/class/id/atribut, combinator, `:not`, `:is`, `:where`, `:has` |
| [02-box-model-display-visibility.md](02-box-model-display-visibility.md) | Content, padding, border, margin, `box-sizing`, semua nilai `display` yang sering dipakai, `visibility`, `opacity`, `content-visibility` |
| [03-satuan-sizing-overflow.md](03-satuan-sizing-overflow.md) | `px`, `rem`, `em`, `%`, viewport, container query unit, `calc`/`min`/`max`/`clamp`, width/height, overflow, scroll, object-fit |
| [04-flexbox-semua-properti.md](04-flexbox-semua-properti.md) | Semua properti Flexbox: direction, wrap, justify, align, place, grow/shrink/basis, `flex`, `order`, `gap` |
| [05-grid-semua-properti.md](05-grid-semua-properti.md) | Semua properti Grid: template, area, auto-flow, line, span, justify/align/place items-content-self, `fr`, `minmax`, `subgrid` |
| [06-warna-tipografi-list.md](06-warna-tipografi-list.md) | Warna, kontras, font, text-*, list-style, vertical-align, white-space |
| [07-background-border-outline-shadow.md](07-background-border-outline-shadow.md) | Background image/gradient, border, radius, outline, box-shadow, text-shadow, ring |
| [08-position-zindex-float-sticky.md](08-position-zindex-float-sticky.md) | `static/relative/absolute/fixed/sticky`, inset, z-index, stacking context, float/clear |
| [09-transform-filter-transition-animation.md](09-transform-filter-transition-animation.md) | Transform 2D/3D, filter, backdrop-filter, transition, `@keyframes`, animation |
| [10-pseudo-class-element.md](10-pseudo-class-element.md) | `:hover`, `:focus-*`, form, structural, `:target`, `::before`/`::after`, `::placeholder`, `::selection` |
| [11-media-query-container-layer.md](11-media-query-container-layer.md) | `@media`, `@supports`, `@container`, `@layer`, `@scope`, `@import`, nesting, custom property |
| [12-tabel-properti-lengkap.md](12-tabel-properti-lengkap.md) | Katalog properti CSS umum: nama, untuk apa, nilai umum, pasangan tipikal |
| [13-tailwind-utility-lengkap.md](13-tailwind-utility-lengkap.md) | Peta utility Tailwind: spacing, warna, tipografi, flex, grid, position, effect, state, breakpoint, arbitrary value |
| [14-resep-dan-kesalahan.md](14-resep-dan-kesalahan.md) | Resep layout yang sering diminta plus kesalahan yang bikin nilai praktikum potong |

## Urutan belajar yang masuk akal

1. Selector dan kaskade — biar aturanmu tidak “tidak jalan” tanpa sebab.
2. Box model + satuan — biar kartu dan form tidak meledak ke samping.
3. Flexbox — navbar, baris tombol, isi kartu.
4. Grid — katalog, dashboard, kerangka halaman.
5. Warna, huruf, background, border — finishing visual.
6. Position dan z-index — badge, header nempel, modal.
7. Transisi dan animasi — gerak yang tidak mengganggu.
8. Pseudo-class — hover, fokus, form error, item genap/ganjil.
9. Media query dan container — HP vs desktop.
10. Tailwind — tulis class yang sama tanpa pindah file CSS.

## CSS murni atau Tailwind?

Keduanya mengatur hal yang sama.

- Tugas “tulis CSS di `style.css`” → pakai bab 01–12.
- Proyek React/Next yang sudah pasang Tailwind → pakai bab 13, lalu cek bab CSS kalau utility-nya tidak kamu hafal.
- Jangan campur 20 class Tailwind *dan* CSS yang menimpa class yang sama tanpa alasan. Pilih satu sumber kebenaran per komponen.

Contoh terjemahan cepat:

| CSS | Tailwind |
| --- | --- |
| `display: flex` | `flex` |
| `justify-content: space-between` | `justify-between` |
| `align-items: center` | `items-center` |
| `gap: 1rem` | `gap-4` |
| `padding: 1rem` | `p-4` |
| `margin-inline: auto` | `mx-auto` |
| `width: 100%` | `w-full` |
| `max-width: 48rem` | `max-w-3xl` |
| `background: #0f172a` | `bg-slate-900` |
| `display: grid; grid-template-columns: 1fr 1fr` | `grid grid-cols-2` |
| `@media (min-width: 768px)` | `md:` |

Skala spacing Tailwind default: `1 = 0.25rem = 4px` jika root `16px`. Jadi `p-4` = `1rem` = `16px`.

## Yang tidak dibahas di sini

- Cara menginstal Node, React, atau Next. Itu ada di cheatsheet teknologi masing-masing.
- Animasi karakter 3D, shader, atau CSS Houdini tingkat dalam.
- Framework CSS lain (Bootstrap, DaisyUI) kecuali disebut sebagai perbandingan singkat.

## Rujukan resmi

- [CSS di MDN](https://developer.mozilla.org/en-US/docs/Web/CSS)
- [Selectors Level 4](https://www.w3.org/TR/selectors-4/)
- [CSS Flexible Box Layout](https://www.w3.org/TR/css-flexbox-1/)
- [CSS Grid Layout](https://www.w3.org/TR/css-grid-2/)
- [Tailwind CSS](https://tailwindcss.com/docs)

Dicek ulang **22 September 2026**. Nilai dan nama utility mengikuti Tailwind v3/v4 yang umum di kelas. Kalau proyekmu memakai preset sendiri, skala warna dan spacing bisa berbeda.

## Pintasan per masalah

- Aturan tidak jalan → [01](01-kaskade-selector-spesifisitas.md), lalu DevTools Computed.
- Kartu lebih lebar dari layar → [02](02-box-model-display-visibility.md) `box-sizing`, [03](03-satuan-sizing-overflow.md) `min-width: 0` / `max-width`.
- Item flex tidak rata → [04](04-flexbox-semua-properti.md).
- Kolom grid tidak mau 3 di desktop → [05](05-grid-semua-properti.md) + [11](11-media-query-container-layer.md).
- Teks tidak kebaca → [06](06-warna-tipografi-list.md).
- Badge nempel di sudut kartu → [08](08-position-zindex-float-sticky.md).
- Hover tidak ada di HP → [10](10-pseudo-class-element.md) dan [14](14-resep-dan-kesalahan.md).
- Lupa class Tailwind → [13](13-tailwind-utility-lengkap.md).
