# Modul 04 — Tailwind CSS

> Praktikum terkait: [`../../1-pembelajaran/04-tailwind-css/`](../../1-pembelajaran/04-tailwind-css/)
> (3 bab: utility & responsive, komponen kartu, state interaksi).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menjelaskan filosofi *utility-first* dan trade-off-nya dibanding CSS manual.
- Menerjemahkan pengetahuan CSS Modul 02–03 ke class Tailwind (dan sebaliknya).
- Memakai skala spacing, warna, dan tipografi Tailwind dengan konsisten.
- Membuat desain responsif dan state interaktif dengan prefix (`md:`, `hover:`).
- Tahu batas CDN vs build process, dan kapan masing-masing pantas dipakai.

**Prasyarat**: Modul 02 dan 03. Tailwind tidak menggantikan pemahaman CSS —
ia hanya *cara menulis* CSS. `items-center` tetap `align-items: center`;
kalau kamu tidak paham flexbox, Tailwind tak akan menolongmu.

---

## 1. Filosofi utility-first

CSS tradisional: beri elemen **nama** (`.kartu-profil`), lalu tulis gayanya
di file terpisah. Tailwind: rangkai **class kecil satu-tugas** langsung di HTML.

```html
<!-- CSS tradisional -->
<div class="kartu">
  <h2 class="kartu-judul">Halo</h2>
</div>
<style>
  .kartu { background: white; padding: 24px; border-radius: 12px;
           box-shadow: 0 1px 3px rgba(0,0,0,0.1); }
  .kartu-judul { font-size: 1.25rem; font-weight: 700; }
</style>

<!-- Tailwind -->
<div class="bg-white p-6 rounded-xl shadow">
  <h2 class="text-xl font-bold">Halo</h2>
</div>
```

### Mengapa orang menyukainya

1. **Tidak mengarang nama.** Tak ada lagi `.kartu-v2-final-fix`. Penamaan
   adalah salah satu masalah tersulit pemrograman — Tailwind menghapusnya.
2. **Skala terbatas = konsisten.** `p-4`, `p-6`, `p-8` — bukan 37 nilai
   padding acak. Desain otomatis terlihat rapi.
3. **Tidak ada CSS mati.** Hapus HTML-nya, hilanglah stylenya. CSS
   tradisional menumpuk rule yang tak ada yang berani hapus.
4. **Perubahan bersifat lokal.** Mengedit class satu elemen tak mungkin
   merusak halaman lain — beda dengan mengedit `.kartu` yang dipakai entah
   di mana saja.

### Keberatan umum — dan jawabannya

- *"HTML jadi panjang dan jelek."* Benar. Trade-off yang disengaja: gaya
  terlihat di tempat ia dipakai.
- *"Sama saja dengan inline style?"* **Tidak.** Inline style tidak bisa
  `hover:`, tidak bisa `md:`, tidak punya skala tema, dan specificity-nya
  bermasalah. Utility class punya semuanya.
- *"Class-nya duplikat di mana-mana."* Solusinya bukan copy-paste, melainkan
  **ekstraksi komponen** (React, Modul 06): tulis sekali di `ProdukCard`,
  pakai berkali-kali.

### Setup untuk belajar (CDN)

```html
<head>
  <script src="https://cdn.tailwindcss.com"></script>
</head>
```

Satu baris, tanpa Node.js — inilah yang dipakai praktikum dan studi kasus
dashboard. **Jangan untuk produksi** (dibahas bagian 6).

---

## 2. Utility inti — peta CSS → Tailwind

### Spacing: skala 1 unit = 0.25rem = 4px

| Tailwind | CSS |
|---|---|
| `p-4` | `padding: 1rem` (16px) |
| `px-6` | `padding-left/right: 1.5rem` |
| `py-2` | `padding-top/bottom: 0.5rem` |
| `pt-8` | `padding-top: 2rem` |
| `m-4` / `mt-8` | `margin` / `margin-top` |
| `mx-auto` | `margin-left/right: auto` (menengahkan!) |
| `gap-4` | `gap: 1rem` |
| `space-y-4` | jarak vertikal antar anak |

### Tipografi

| Tailwind | CSS |
|---|---|
| `text-sm` / `text-base` / `text-lg` / `text-xl` / `text-2xl`… | `font-size` 14/16/18/20/24px… |
| `font-medium` / `font-semibold` / `font-bold` | `font-weight` 500/600/700 |
| `text-center` | `text-align: center` |
| `leading-relaxed` | `line-height: 1.625` |
| `tracking-tight` | `letter-spacing` negatif |
| `truncate` | potong teks + ellipsis |

### Warna: `{properti}-{warna}-{intensitas}`

```html
<div class="bg-sky-600 text-white border border-sky-700">
```

- Properti: `bg-` (background), `text-` (warna teks), `border-`.
- Warna: `slate`, `gray`, `red`, `amber`, `emerald`, `sky`, `blue`,
  `violet`, `rose`, dll.
- Intensitas: `50` (paling terang) → `500`–`600` (utama) → `950` (paling gelap).

Resep aman: latar `white`/`slate-50`, teks utama `slate-900`, teks sekunder
`slate-600`, aksen satu warna `sky-600`/`emerald-600`.

### Layout (langsung dari Modul 03!)

| Tailwind | CSS |
|---|---|
| `flex` | `display: flex` |
| `items-center` | `align-items: center` |
| `justify-between` | `justify-content: space-between` |
| `flex-col` | `flex-direction: column` |
| `flex-1` | `flex: 1` |
| `grid grid-cols-3` | `display:grid; grid-template-columns: repeat(3,1fr)` |
| `col-span-2` | `grid-column: span 2` |
| `hidden` / `block` | `display: none` / `block` |
| `w-full` / `w-64` | `width: 100%` / `16rem` |
| `max-w-4xl` | `max-width: 56rem` |
| `min-h-screen` | `min-height: 100vh` |

### Dekorasi

| Tailwind | CSS |
|---|---|
| `rounded-lg` / `rounded-xl` / `rounded-full` | `border-radius` 8px/12px/9999px |
| `border` / `border-2` | `border-width` 1px/2px |
| `shadow` / `shadow-md` / `shadow-lg` | `box-shadow` bertingkat |
| `opacity-50` | `opacity: 0.5` |
| `transition` | transisi properti umum 150ms |

---

## 3. Responsive: prefix breakpoint

Aturan terpenting: **tanpa prefix = mobile**. Prefix = `min-width` (persis
media query mobile-first Modul 03).

| Prefix | Aktif saat | Setara |
|---|---|---|
| (tanpa) | selalu | gaya dasar |
| `sm:` | ≥ 640px | `@media (min-width: 640px)` |
| `md:` | ≥ 768px | `@media (min-width: 768px)` |
| `lg:` | ≥ 1024px | `@media (min-width: 1024px)` |
| `xl:` | ≥ 1280px | `@media (min-width: 1280px)` |

```html
<!-- 1 kolom di HP, 2 di tablet, 3 di desktop -->
<div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">

<!-- Menu: tersembunyi di HP, flex di tablet ke atas -->
<nav class="hidden md:flex gap-6">

<!-- Padding membesar di layar besar -->
<section class="px-4 md:px-8 lg:px-16">
```

Kesalahan klasik: menulis `md:flex` **tanpa** `hidden` dasar lalu bingung
kenapa menu tampil di HP — atau sebaliknya, `hidden md:flex` lalu lupa
menyediakan menu hamburger untuk HP.

---

## 4. State: prefix interaksi

```html
<button class="bg-sky-600 text-white px-4 py-2 rounded-lg
               hover:bg-sky-700
               focus-visible:ring-2 focus-visible:ring-sky-400
               active:scale-95
               disabled:opacity-50 disabled:cursor-not-allowed
               transition">
  Simpan
</button>
```

| Prefix | Kapan aktif |
|---|---|
| `hover:` | Kursor di atas |
| `focus:` / `focus-visible:` | Fokus / fokus keyboard |
| `active:` | Sedang ditekan |
| `disabled:` | Elemen disabled |
| `checked:` | Checkbox/radio tercentang |
| `group-hover:` | Saat **parent** ber-class `group` di-hover |
| `dark:` | Mode gelap |

Pola `group-hover` — kartu yang menyorot judulnya:

```html
<a href="#" class="group block rounded-xl border p-6 hover:shadow-lg transition">
  <h3 class="font-bold group-hover:text-sky-600 transition">Judul Kartu</h3>
  <p class="text-slate-600">Deskripsi…</p>
</a>
```

Prefix bisa dirantai: `md:hover:bg-sky-700` = hover **dan** layar ≥768px.

---

## 5. Contoh utuh: kartu produk

Pola yang sama dengan praktikum `02-komponen-kartu` dan studi kasus dashboard:

```html
<article class="max-w-sm rounded-xl bg-white shadow-md overflow-hidden
                hover:shadow-lg transition">
  <img src="menu.jpg" alt="Kopi susu gula aren"
       class="h-48 w-full object-cover">
  <div class="p-6">
    <div class="flex items-center justify-between">
      <h2 class="text-xl font-bold text-slate-900">Kopi Susu</h2>
      <span class="rounded-full bg-emerald-100 px-3 py-1
                   text-sm font-medium text-emerald-700">
        Best Seller
      </span>
    </div>
    <p class="mt-2 text-slate-600 leading-relaxed">
      Espresso, susu segar, gula aren asli.
    </p>
    <div class="mt-4 flex items-center justify-between">
      <span class="text-lg font-bold text-sky-600">Rp18.000</span>
      <button class="rounded-lg bg-sky-600 px-4 py-2 text-white
                     hover:bg-sky-700 focus-visible:ring-2 transition">
        Pesan
      </button>
    </div>
  </div>
</article>
```

Perhatikan: setiap class bisa kamu terjemahkan balik ke CSS Modul 02–03.
Latihan bagus: tulis versi CSS manualnya, bandingkan panjangnya.

---

## 6. CDN vs build process

| | CDN (`cdn.tailwindcss.com`) | Build (npm + PostCSS) |
|---|---|---|
| Setup | 1 baris script | `npm install`, config |
| Ukuran CSS | Semua utility (besar, ~MB di-generate runtime) | Hanya class terpakai (sering <10 KB) |
| Kustomisasi tema | Terbatas | Penuh (`tailwind.config`) |
| Kelayakan produksi | ❌ | ✅ standar industri |
| Dipakai di | Praktikum 04, studi kasus 02 | Next.js (Modul 07–08, studi kasus 03) |

Cara kerja build: Tailwind **memindai** file HTML/JSX-mu mencari nama class,
lalu men-generate CSS hanya untuk class yang ditemukan. Konsekuensi penting:

```jsx
/* ❌ TIDAK terdeteksi scanner — class dirakit runtime */
<div className={`bg-${warna}-500`}>

/* ✅ nama class utuh terlihat di kode */
<div className={warna === "merah" ? "bg-red-500" : "bg-sky-500"}>
```

Ini juga alasan kamu tak boleh menyingkat/menyambung nama class dengan
variabel — tulis selalu **utuh**.

---

## 7. Kesalahan umum

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | Merakit class dinamis (`bg-${x}-500`) | Style hilang saat build | Tulis nama class utuh |
| 2 | Lupa gaya dasar mobile | Elemen hilang/berantakan di HP | Tanpa prefix dulu, baru `md:` |
| 3 | Nilai arbitrer di mana-mana (`w-[137px]`) | Konsistensi skala hancur | Pakai skala; arbitrer = pengecualian |
| 4 | Copy-paste class panjang ke 10 tempat | Ubah satu, lupa sembilan | Ekstrak komponen (Modul 06) |
| 5 | Tak paham CSS di baliknya | Buntu saat layout aneh | Kuasai Modul 02–03 |
| 6 | CDN di produksi | Lambat, versi bisa berubah | Build process |
| 7 | Menghapus `transition` | Interaksi terasa kasar | `transition` + `hover:` berpasangan |

---

## 8. Cheatsheet

```text
LAYOUT     flex items-center justify-between gap-4 | flex-col | flex-1
           grid grid-cols-1 md:grid-cols-3 gap-6 | col-span-2
           hidden md:block | w-full max-w-4xl mx-auto | min-h-screen

SPACING    p-4 px-6 py-2 pt-8 | m-4 mt-8 mx-auto | gap-4 space-y-4
           (angka × 4px: 2=8px, 4=16px, 6=24px, 8=32px)

TEKS       text-sm text-base text-xl text-3xl | font-medium font-bold
           text-slate-600 text-center leading-relaxed truncate

WARNA      bg-white bg-sky-600 bg-slate-50 | text-slate-900
           border-slate-200 | intensitas: 50 terang … 600 utama … 950 gelap

DEKORASI   rounded-lg rounded-xl rounded-full | border border-2
           shadow shadow-md shadow-lg | opacity-50 | overflow-hidden

RESPONSIVE sm:640 md:768 lg:1024 xl:1280 — tanpa prefix = mobile!
           grid-cols-1 sm:grid-cols-2 lg:grid-cols-3

STATE      hover:bg-sky-700 focus-visible:ring-2 active:scale-95
           disabled:opacity-50 group + group-hover:… dark:bg-slate-900
           transition (jangan lupa!)
```

## Lanjut ke praktikum

Kerjakan berurutan di [`../../1-pembelajaran/04-tailwind-css/`](../../1-pembelajaran/04-tailwind-css/):

1. `01-utility-responsive` — utility inti + prefix breakpoint (bagian 2–3).
2. `02-komponen-kartu` — merangkai kartu utuh (bagian 5).
3. `03-state-interaksi` — hover/focus/group (bagian 4).

Lalu uji diri dengan [`../../3-latihan-soal/04-tailwind-css/soal.md`](../../3-latihan-soal/04-tailwind-css/soal.md),
dan praktikkan skala penuh di [`../../4-studi-kasus/02-dashboard-interaktif/`](../../4-studi-kasus/02-dashboard-interaktif/).
