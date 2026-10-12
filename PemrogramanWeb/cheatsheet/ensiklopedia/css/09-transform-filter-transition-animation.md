# 09 — Transform, filter, transition, animation

[← Position](08-position-zindex-float-sticky.md) · [Indeks](README.md) · [Pseudo →](10-pseudo-class-element.md)

Gerakan yang baik menjelaskan perubahan. Gerakan yang buruk membuat mual dan mengganggu keyboard. Hormati `prefers-reduced-motion`.

## Daftar isi

- [transform-function](#transform-function)
- [Properti terpisah translate rotate scale](#properti-terpisah-translate-rotate-scale)
- [transform-origin](#transform-origin)
- [transform-style perspective backface](#transform-style-perspective-backface)
- [will-change](#will-change)
- [filter](#filter)
- [backdrop-filter](#backdrop-filter)
- [mix-blend-mode background-blend-mode](#mix-blend-mode-background-blend-mode)
- [transition](#transition)
- [animation dan @keyframes](#animation-dan-keyframes)
- [prefers-reduced-motion](#prefers-reduced-motion)
- [Peta Tailwind](#peta-tailwind)

## transform-function

**Untuk apa:** memindahkan, memutar, menskala, memiringkan **tanpa mengubah layout** (ruang asli tetap). Membuat containing block / stacking context.

### translate

**Untuk apa:** geser.

```css
.geser { transform: translate(0.5rem, 0); }
.geser { transform: translateX(100%); }
.geser { transform: translateY(-0.25rem); }
.geser3 { transform: translate3d(0, 0, 0); }
```

Persen relatif ke ukuran **elemen itu**, bukan induk. `translateY(-50%)` = naik setengah tingginya sendiri.

**Biasanya digabungkan dengan:** hover kartu, menengahkan `absolute`.

### rotate

**Untuk apa:** putar di bidang 2D atau sumbu 3D.

```css
.chevron.buka { transform: rotate(180deg); }
.kartu { transform: rotate(-2deg); }
.kubus { transform: rotateX(45deg) rotateY(20deg); }
```

**Biasanya digabungkan dengan:** `transform-origin`, transisi.

### scale

**Untuk apa:** perbesar/perkecil dari origin.

```css
.kartu:hover { transform: scale(1.02); }
.tekan:active { transform: scale(0.97); }
.lebar { transform: scaleX(1.1); }
```

`scale(0)` menyembunyikan visual tetapi masih makan ruang dan bisa diklik.

**Biasanya digabungkan dengan:** `transition`, `box-shadow`.

### skew

**Untuk apa:** miring. Cepat membuat teks sulit dibaca.

```css
.pita { transform: skewX(-12deg); }
```

**Biasanya digabungkan dengan:** pita dekoratif, bukan paragraf.

### matrix / matrix3d

**Untuk apa:** gabungan numerik. Jarang ditulis tangan.

```css
.x { transform: matrix(1, 0, 0, 1, 10, 20); }
```

**Biasanya digabungkan dengan:** keluaran tool, bukan tugas kuliah.

### Beberapa fungsi

**Untuk apa:** rantai. Urutan penting: diterapkan dari **kanan ke kiri** (secara matematis), secara praktis tulis urutan yang kamu baca: biasanya `translate` lalu `rotate` lalu `scale` sesuai kebutuhan.

```css
.badge {
  transform: translate(-50%, -50%) rotate(8deg) scale(1);
}
```

Satu properti `transform`; menulis `transform` kedua menimpa, tidak menambah.

**Biasanya digabungkan dengan:** hover yang mengulang seluruh rantai.

## Properti terpisah translate rotate scale

**Untuk apa:** menggeser satu sumbu tanpa menimpa rotasi.

```css
.kartu {
  translate: 0 0;
  rotate: 0deg;
  scale: 1;
  transition: translate 200ms, scale 200ms;
}

.kartu:hover {
  translate: 0 -0.25rem;
  scale: 1.02;
}
```

Ini tidak menimpa `rotate` yang mungkin di-set class lain. Browser modern. Alternatif Tailwind v3: `translate-y-*` memakai `--tw-translate` di satu `transform` gabungan.

**Biasanya digabungkan dengan:** transisi independen.

## transform-origin

**Untuk apa:** titik poros rotate/scale. Bawaan `50% 50%`.

```css
.chevron { transform-origin: center; }
.menu { transform-origin: top right; }
.daun { transform-origin: 0 100%; }
```

**Biasanya digabungkan dengan:** `rotate`, dropdown scale.

## transform-style perspective backface

### perspective

**Untuk apa:** kedalaman 3D pada **anak**.

```css
.panggung {
  perspective: 800px;
}

.kartu { transform: rotateY(30deg); }
```

`perspective` di induk. `perspective()` di `transform` anak hanya memengaruhi elemen itu.

**Biasanya digabungkan dengan:** `transform-style: preserve-3d`.

### transform-style

**Untuk apa:** `preserve-3d` menjaga anak di ruang 3D yang sama.

```css
.kubus { transform-style: preserve-3d; }
```

**Biasanya digabungkan dengan:** wajah kubus `translateZ`.

### backface-visibility

**Untuk apa:** `hidden` menyembunyikan sisi belakang saat diputar.

```css
.kartu-wajah { backface-visibility: hidden; }
```

**Biasanya digabungkan dengan:** flip card `rotateY(180deg)`.

### perspective-origin

**Untuk apa:** posisi “kamera”.

```css
.panggung { perspective-origin: 50% 30%; }
```

**Biasanya digabungkan dengan:** `perspective`.

## will-change

**Untuk apa:** petunjuk ke browser bahwa properti akan berubah. Mudah disalahgunakan.

```css
.kartu:hover { will-change: transform; }
```

Jangan pasang `will-change: transform` di semua kartu selamanya; memakan memori. Lebih baik biarkan browser, atau pasang sesaat sebelum animasi.

**Biasanya digabungkan dengan:** animasi berat, bukan default.

## filter

**Untuk apa:** efek pada **seluruh elemen termasuk anak**. Membuat stacking context.

```css
.redup { filter: brightness(0.7); }
.abu { filter: grayscale(1); }
.blur { filter: blur(8px); }
.bayangan { filter: drop-shadow(0 8px 12px rgb(15 23 42 / 0.2)); }
.kombo { filter: contrast(1.1) saturate(1.2); }
```

Fungsi: `blur()`, `brightness()`, `contrast()`, `drop-shadow()`, `grayscale()`, `hue-rotate()`, `invert()`, `opacity()`, `saturate()`, `sepia()`.

`blur` pada elemen besar mahal. `opacity()` di filter beda dengan properti `opacity` (tetap filter pipeline).

**Biasanya digabungkan dengan:** hover gambar, `transition: filter`.

## backdrop-filter

**Untuk apa:** memfilter **apa yang di belakang** elemen, seolah kaca buram.

```css
.header {
  background: rgb(255 255 255 / 0.72);
  backdrop-filter: blur(10px);
}
```

Elemen harus punya latar transparan/translucent, kalau tidak tidak ada yang terlihat. Beberapa browser butuh latar tidak fully opaque.

**Biasanya digabungkan dengan:** `background` alpha, `border`, sticky header.

## mix-blend-mode background-blend-mode

**Untuk apa:** `mix-blend-mode` mencampur elemen dengan apa di belakangnya. `background-blend-mode` mencampur layer `background-image` satu sama lain.

```css
.teks-foto { mix-blend-mode: difference; }
.hero {
  background-image: url("/t.jpg"), linear-gradient(#0f766e, #0f172a);
  background-blend-mode: multiply;
}
```

`isolation: isolate` pada induk membatasi campur.

**Biasanya digabungkan dengan:** hero, desain editorial. Uji kontras.

## transition

**Untuk apa:** menginterpolasi perubahan properti yang **bisa dianimasikan**.

### Bagian shorthand

```css
.tombol {
  transition: background-color 150ms ease, transform 150ms ease;
}

.tombol {
  transition-property: background-color, transform;
  transition-duration: 150ms;
  transition-timing-function: ease;
  transition-delay: 0s;
}
```

`transition: 200ms` saja memakai `all` — bisa menganimasikan hal tak terduga. Tulis properti eksplisit.

Tidak semua properti mulus: `display`, `height: auto` klasik bermasalah. `opacity` dan `transform` paling hemat.

**Biasanya digabungkan dengan:** `:hover`, `:focus-visible`, class JS.

### timing function

**Untuk apa:** kecepatan kurva.

```css
.linear { transition-timing-function: linear; }
.ease { transition-timing-function: ease; }
.out { transition-timing-function: ease-out; }
.custom { transition-timing-function: cubic-bezier(0.22, 1, 0.36, 1); }
.langkah { transition-timing-function: steps(4, end); }
```

`ease-out` enak untuk masuk. `ease-in` untuk keluar. `linear` untuk progress bar.

**Biasanya digabungkan dengan:** durasi 100–300ms UI, lebih lama hanya untuk dekorasi.

### transition-behavior dan interpolate-size

**Untuk apa:** transisi `height: auto` di browser baru.

```css
.panel {
  interpolate-size: allow-keywords;
  height: 0;
  transition: height 200ms ease;
}

.panel.buka { height: auto; }
```

Dukungan belum merata. Pola aman: `grid-template-rows: 0fr` → `1fr`.

```css
.akordion > .isi { display: grid; grid-template-rows: 0fr; transition: 200ms; }
.akordion.buka > .isi { grid-template-rows: 1fr; }
.akordion .isi > * { overflow: hidden; }
```

**Biasanya digabungkan dengan:** accordion, `overflow: hidden`.

## animation dan @keyframes

### @keyframes

**Untuk apa:** menamai urutan keyframe.

```css
@keyframes masuk {
  from { opacity: 0; translate: 0 0.5rem; }
  to { opacity: 1; translate: 0 0; }
}

@keyframes pulsa {
  0%, 100% { opacity: 1; }
  50% { opacity: 0.45; }
}
```

`from` = 0%, `to` = 100%. Beberapa stop boleh.

**Biasanya digabungkan dengan:** `animation-name`.

### animation shorthand

**Untuk apa:** menerapkan keyframe ke elemen.

```css
.toast {
  animation: masuk 200ms ease-out both;
}

.skeleton {
  animation: pulsa 1.2s ease-in-out infinite;
}
```

Urutan umum: `name duration timing delay iteration direction fill play-state`.

**Biasanya digabungkan dengan:** class yang dipasang saat mount.

### animation-iteration-count

**Untuk apa:** `1` (bawaan), angka, atau `infinite`.

```css
.spinner { animation: putar 0.7s linear infinite; }
```

**Biasanya digabungkan dengan:** `prefers-reduced-motion` untuk hentikan loop.

### animation-direction

**Untuk apa:** `normal`, `reverse`, `alternate`, `alternate-reverse`.

```css
.ayun { animation: ayun 1s ease-in-out infinite alternate; }
```

**Biasanya digabungkan dengan:** `infinite`.

### animation-fill-mode

**Untuk apa:** mempertahankan gaya before/after animasi. `none`, `forwards`, `backwards`, `both`.

```css
.masuk { animation: masuk 200ms ease both; }
```

Tanpa `forwards`/`both`, elemen bisa “kedip” kembali ke gaya sebelum animasi.

**Biasanya digabungkan dengan:** fade-in masuk.

### animation-play-state

**Untuk apa:** `paused` / `running`.

```css
.marquee:hover { animation-play-state: paused; }
```

**Biasanya digabungkan dengan:** carousel, reduced motion.

### animation-composition

**Untuk apa:** `replace` (bawaan), `add`, `accumulate` saat beberapa animasi mengenai properti sama.

```css
.layer { animation-composition: add; }
```

**Biasanya digabungkan dengan:** animasi majemuk; jarang di tugas.

## prefers-reduced-motion

**Untuk apa:** menghormati pengguna yang meminta gerak minimal.

```css
@media (prefers-reduced-motion: reduce) {
  *,
  *::before,
  *::after {
    animation-duration: 0.01ms !important;
    animation-iteration-count: 1 !important;
    transition-duration: 0.01ms !important;
    scroll-behavior: auto !important;
  }
}
```

Lebih halus: matikan hanya loop dekoratif, biarkan fade 100ms.

**Biasanya digabungkan dengan:** semua `animation: infinite`, `scroll-behavior: smooth`.

## Peta Tailwind

| CSS | Tailwind |
| --- | --- |
| `scale(1.05)` | `scale-105` |
| `scale(0.95)` | `scale-95` |
| `rotate(180deg)` | `rotate-180` |
| `translateY(-0.25rem)` | `-translate-y-1` |
| `translateX(50%)` | `translate-x-1/2` |
| `skewX(12deg)` | `skew-x-12` |
| `origin-center` | `origin-center` |
| `origin-top-right` | `origin-top-right` |
| `blur(8px)` | `blur` / `blur-lg` |
| `grayscale(1)` | `grayscale` |
| `brightness(0.7)` | `brightness-75` |
| `drop-shadow` | `drop-shadow-md` |
| `backdrop-filter: blur(8px)` | `backdrop-blur` |
| `transition` | `transition` |
| `duration 150ms` | `duration-150` |
| `ease-out` | `ease-out` |
| `delay-100` | `delay-100` |
| `animate-spin` | `animate-spin` |
| `animate-pulse` | `animate-pulse` |
| `animate-bounce` | `animate-bounce` |
| `animate-none` | `animate-none` |

```html
<article class="transition duration-200 hover:-translate-y-1 hover:shadow-lg motion-reduce:transform-none">
```

**Biasanya digabungkan dengan:** `motion-reduce:transition-none`, `hover:` hanya sebagai tambahan bukan satu-satunya petunjuk.
