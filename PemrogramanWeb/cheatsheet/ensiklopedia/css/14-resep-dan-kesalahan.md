# 14 — Resep dan kesalahan

[← Tailwind](13-tailwind-utility-lengkap.md) · [Indeks](README.md)

Kumpulan pola yang sering diminta di praktikum, plus bug yang bikin “CSS-ku tidak jalan”. Setiap resep memakai bentuk yang sama: untuk apa, kode, penjelasan, biasanya digabung dengan.

## Daftar isi

- [Reset minimal](#reset-minimal)
- [Halaman terpusat](#halaman-terpusat)
- [Sticky footer](#sticky-footer)
- [Navbar](#navbar)
- [Kartu produk](#kartu-produk)
- [Katalog responsif](#katalog-responsif)
- [Dashboard sidebar](#dashboard-sidebar)
- [Form rapi](#form-rapi)
- [Badge di sudut](#badge-di-sudut)
- [Modal dialog](#modal-dialog)
- [Accordion](#accordion)
- [Tabs visual](#tabs-visual)
- [Tabel yang tidak meledak](#tabel-yang-tidak-meledak)
- [Hero foto + teks](#hero-foto--teks)
- [Ellipsis judul](#ellipsis-judul)
- [Tombol ikon](#tombol-ikon)
- [Skip link](#skip-link)
- [Kesalahan: aturan tidak jalan](#kesalahan-aturan-tidak-jalan)
- [Kesalahan: overflow horizontal](#kesalahan-overflow-horizontal)
- [Kesalahan: flex dan grid](#kesalahan-flex-dan-grid)
- [Kesalahan: position dan z-index](#kesalahan-position-dan-z-index)
- [Kesalahan: gambar dan media](#kesalahan-gambar-dan-media)
- [Kesalahan: form dan fokus](#kesalahan-form-dan-fokus)
- [Kesalahan: Tailwind](#kesalahan-tailwind)
- [Kesalahan: responsif](#kesalahan-responsif)
- [Checklist sebelum kumpul tugas](#checklist-sebelum-kumpul-tugas)

## Reset minimal

**Untuk apa:** menghilangkan kejutan browser sebelum kamu menata apa pun.

```css
*, *::before, *::after { box-sizing: border-box; }

body {
  margin: 0;
  line-height: 1.6;
  font-family: system-ui, sans-serif;
}

img, video, svg { max-width: 100%; height: auto; }
img { display: block; }

button, input, textarea, select { font: inherit; }
```

Tanpa `box-sizing`, padding membuat `width: 100%` overflow. Tanpa `img { max-width: 100% }`, foto merusak grid. `font: inherit` pada kontrol membuat input tidak memakai Times aneh.

**Biasanya digabungkan dengan:** `color-scheme`, token `--fg/--bg`.

## Halaman terpusat

**Untuk apa:** konten tidak menempel tepi dan tidak melebar tak terbaca.

```css
.halaman {
  width: min(100% - 2rem, 70rem);
  margin-inline: auto;
}
```

`100% - 2rem` = ada napas 1rem kiri-kanan. `70rem` = berhenti di layar lebar.

Tailwind: `mx-auto w-full max-w-5xl px-4`.

**Biasanya digabungkan dengan:** `min-height: 100dvh` jika perlu footer di bawah.

## Sticky footer

**Untuk apa:** footer di bawah viewport meski konten pendek.

```css
body {
  min-height: 100dvh;
  display: flex;
  flex-direction: column;
}

main { flex: 1; }
```

Atau Grid: `grid-template-rows: auto 1fr auto` pada body/wrapper.

**Biasanya digabungkan dengan:** `min-height: 100dvh`, bukan `height: 100vh` kaku.

## Navbar

**Untuk apa:** logo kiri, tautan kanan, rapi di HP.

```css
.nav {
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  justify-content: space-between;
  gap: 1rem;
}

.nav-tautan {
  display: flex;
  flex-wrap: wrap;
  gap: 0.75rem 1rem;
}
```

`space-between` memisahkan dua kelompok. `wrap` mencegah overflow di HP. Jangan `position: absolute` tiap tautan.

Header nempel:

```css
.header {
  position: sticky;
  top: 0;
  z-index: 10;
  background: rgb(255 255 255 / 0.92);
  backdrop-filter: blur(10px);
}
```

**Biasanya digabungkan dengan:** `scroll-margin-top` pada section, hamburger + `display: none` sampai `md`.

## Kartu produk

**Untuk apa:** gambar, judul, harga, tombol yang tinggi kartunya sejajar di grid.

```css
.kartu {
  display: flex;
  flex-direction: column;
  overflow: hidden;
  border: 1px solid #e2e8f0;
  border-radius: 0.75rem;
  background: white;
}

.kartu img {
  aspect-ratio: 16 / 9;
  width: 100%;
  object-fit: cover;
}

.kartu-isi {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  padding: 1rem;
  flex: 1;
}

.kartu .aksi { margin-top: auto; }
```

`flex: 1` pada isi + `margin-top: auto` pada aksi = tombol rata bawah meski judul beda panjang.

**Biasanya digabungkan dengan:** grid katalog, `line-clamp-3` pada deskripsi.

## Katalog responsif

**Untuk apa:** 1 kolom di HP, sebanyak yang muat di desktop, tanpa media query wajib.

```css
.katalog {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(min(100%, 15rem), 1fr));
  gap: 1rem;
}
```

Kalau satu item tidak boleh melebar jadi spanduk, ganti `auto-fit` → `auto-fill`.

Tailwind: `grid grid-cols-1 gap-4 sm:grid-cols-2 lg:grid-cols-3`.

**Biasanya digabungkan dengan:** kartu flex-col, `minmax(0,1fr)` jika kolom pecah.

## Dashboard sidebar

**Untuk apa:** sisi kiri tetap, isi makan sisa.

```css
.shell {
  display: grid;
  grid-template-columns: 1fr;
  min-height: 100dvh;
}

@media (min-width: 48rem) {
  .shell {
    grid-template-columns: 16rem minmax(0, 1fr);
  }
}
```

`minmax(0, 1fr)` mencegah tabel di isi mendorong sidebar.

**Biasanya digabungkan dengan:** sidebar `position: sticky; top: 0; align-self: start; max-height: 100dvh; overflow: auto`.

## Form rapi

**Untuk apa:** label di atas field, jarak konsisten, fokus kelihatan.

```css
.form {
  display: flex;
  flex-direction: column;
  gap: 0.85rem;
}

.field { display: flex; flex-direction: column; gap: 0.3rem; }

.field input,
.field textarea,
.field select {
  width: 100%;
  padding: 0.55rem 0.7rem;
  border: 1px solid #cbd5e1;
  border-radius: 0.4rem;
}

.field input:focus-visible {
  outline: 2px solid #0369a1;
  outline-offset: 2px;
}

.aksi {
  display: flex;
  justify-content: flex-end;
  gap: 0.5rem;
}
```

Jangan andalkan placeholder sebagai label. `*` wajib lewat teks atau `::after`, bukan warna saja.

**Biasanya digabungkan dengan:** `:user-invalid`, `peer`, `has-`.

## Badge di sudut

**Untuk apa:** label “Baru” di atas gambar kartu.

```css
.kartu { position: relative; }

.badge {
  position: absolute;
  top: 0.75rem;
  right: 0.75rem;
  z-index: 1;
  padding: 0.15rem 0.5rem;
  border-radius: 999px;
  background: #fbbf24;
  font-size: 0.75rem;
}
```

Induk wajib `relative`. Kalau induk `overflow: hidden` + badge keluar sedikit, badge terpotong — kecilkan `top/right` atau jangan overflow.

**Biasanya digabungkan dengan:** `isolation: isolate` jika banyak overlay.

## Modal dialog

**Untuk apa:** overlay mengunci fokus visual ke kotak.

```css
dialog.modal {
  border: 0;
  border-radius: 0.75rem;
  padding: 1.25rem;
  width: min(100% - 2rem, 32rem);
}

dialog.modal::backdrop {
  background: rgb(15 23 42 / 0.5);
}

html:has(dialog[open]) { overflow: hidden; }
```

Pakai `<dialog>` + `showModal()` agar top layer dan Esc jalan. `position: fixed; inset: 0` manual mudah kalah z-index.

**Biasanya digabungkan dengan:** `overscroll-behavior: contain` pada badan dialog.

## Accordion

**Untuk apa:** buka-tutup tanpa merusak tinggi dengan `display: none` yang tidak bisa dianimasikan.

```css
.acc-isi {
  display: grid;
  grid-template-rows: 0fr;
  transition: grid-template-rows 200ms ease;
}

.acc.buka .acc-isi { grid-template-rows: 1fr; }

.acc-isi > * { overflow: hidden; }
```

Atau native `<details>`/`<summary>` — lebih mudah diakses, animasi terbatas.

**Biasanya digabungkan dengan:** `button` + `aria-expanded`, reduced motion.

## Tabs visual

**Untuk apa:** tab aktif punya garis bawah, panel tersembunyi.

```css
.tab { border-bottom: 2px solid transparent; }
.tab.aktif { border-bottom-color: #0f172a; font-weight: 600; }

.panel { display: none; }
.panel.aktif { display: block; }
```

Pilih tab dengan JS atau radio+`:checked`. Jangan hanya ganti warna tanpa `aria-selected`.

**Biasanya digabungkan dengan:** `role="tablist"`, fokus keyboard.

## Tabel yang tidak meledak

**Untuk apa:** kolom patuh, teks panjang tidak mendorong layout.

```css
.bungkus { overflow-x: auto; }

table {
  width: 100%;
  border-collapse: collapse;
  table-layout: fixed;
}

th, td {
  padding: 0.5rem 0.75rem;
  text-align: start;
  vertical-align: top;
  overflow-wrap: anywhere;
}
```

Di dalam grid/flex, bungkus tabel `min-width: 0`.

**Biasanya digabungkan dengan:** `overflow-x: auto`, `th` sticky.

## Hero foto + teks

**Untuk apa:** judul kebaca di atas gambar.

```css
.hero {
  position: relative;
  min-height: 20rem;
  color: white;
}

.hero img {
  position: absolute;
  inset: 0;
  width: 100%;
  height: 100%;
  object-fit: cover;
}

.hero::after {
  content: "";
  position: absolute;
  inset: 0;
  background: rgb(15 23 42 / 0.45);
}

.hero-isi {
  position: relative;
  z-index: 1;
  padding: 2rem 1.25rem;
}
```

Gambar absolute + overlay `::after` + isi `z-index`. Kontras teks wajib diuji.

**Biasanya digabungkan dengan:** `clamp` judul, `min-height`.

## Ellipsis judul

**Untuk apa:** judul kartu satu baris lalu `...`.

```css
.judul {
  min-width: 0;
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
}
```

Tiga syarat sekaligus. Di flex item, `min-width: 0` paling sering terlupakan.

Banyak baris: `line-clamp: 2` + `overflow: hidden`.

**Biasanya digabungkan dengan:** `flex: 1`.

## Tombol ikon

**Untuk apa:** ikon dan teks satu garis tengah.

```css
.tombol {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  gap: 0.4rem;
  padding: 0.5rem 0.9rem;
  border: 0;
  border-radius: 0.4rem;
  cursor: pointer;
}

.tombol:focus-visible {
  outline: 2px solid #0369a1;
  outline-offset: 2px;
}

.tombol:disabled {
  opacity: 0.55;
  cursor: not-allowed;
}
```

**Biasanya digabungkan dengan:** `svg { width: 1.1em; height: 1.1em; }`, `currentColor`.

## Skip link

**Untuk apa:** pengguna keyboard meloncat ke konten.

```css
.skip {
  position: absolute;
  left: 0.5rem;
  top: 0.5rem;
  translate: 0 -150%;
}

.skip:focus { translate: 0 0; }
```

Letakkan tautan pertama di `<body>`.

**Biasanya digabungkan dengan:** `id` pada `<main>`.

## Kesalahan: aturan tidak jalan

**Untuk apa:** debug kaskade sebelum menulis `!important`.

Gejala dan cek:

1. Typo selector: `.Kartu` ≠ `.kartu`. Class HTML tanpa titik, CSS dengan titik.
2. File CSS tidak terhubung: `<link rel="stylesheet" href="style.css">` path salah.
3. Kalah spesifisitas: `#nav a` mengalahkan `.tombol`. Lihat [bab 01](01-kaskade-selector-spesifisitas.md).
4. Aturan dicoret di DevTools Computed: ada yang lebih spesifik atau belakangan.
5. `display: flex` belum dipasang tetapi kamu set `justify-content`.
6. Custom property salah nama: `var(--warna)` vs `--color`.
7. Tailwind: class belum ada di content path, atau typo `justfy-center`.
8. Inline style menimpa file.
9. Cache browser: hard reload.

```css
/* lemah */
div p { color: red; }

/* yang menang tanpa sadar */
#app .prosa p { color: black; }
```

**Biasanya digabungkan dengan:** DevTools, turunkan spesifisitas lawan.

## Kesalahan: overflow horizontal

**Untuk apa:** menghilangkan scroll kiri-kanan misterius.

Penyebab umum:

- `width: 100vw` (menghitung scrollbar).
- `width: 100%` + padding tanpa `border-box`.
- Flex/grid item `min-width: auto` + kata/URL/gambar panjang.
- `margin-left: calc(50% - 50vw)` full-bleed.
- `transform` atau `box-shadow` besar — kadang tidak, kadang iya tergantung browser.
- Pre/kode `white-space: pre` tanpa `overflow-x: auto`.

Obat standar:

```css
.item { min-width: 0; }
img { max-width: 100%; }
.papan { grid-template-columns: minmax(0, 1fr) minmax(0, 2fr); }
```

**Biasanya digabungkan dengan:** `overflow-wrap: anywhere` pada teks.

## Kesalahan: flex dan grid

**Untuk apa:** merapikan layout yang “hampir benar”.

| Gejala | Sebab | Obat |
| --- | --- | --- |
| Item tidak rata vertikal | `justify-content` pada `row` | `align-items: center` |
| Kolom flex tidak 50-50 | `flex: auto` + konten beda | `flex: 1` + `min-width: 0` |
| Footer tidak ke bawah | body bukan flex col | `min-height: 100dvh; flex-direction: column` + `main { flex: 1 }` |
| Ellipsis tidak muncul | flex item min-content | `min-width: 0` |
| Grid overflow | `1fr` = `minmax(auto,1fr)` | `minmax(0,1fr)` |
| Satu kartu selebar layar | `auto-fit` | `auto-fill` atau `max-width` kartu |
| Anak tidak jadi kolom | wrapper extra (React) | hapus wrapper atau `contents` |
| `gap` + `margin` dobel | keduanya dipakai | pilih satu |
| `align-content` “mati” | tidak wrap / satu baris | `flex-wrap: wrap` + tinggi sisa |

**Biasanya digabungkan dengan:** [bab 04](04-flexbox-semua-properti.md) dan [05](05-grid-semua-properti.md).

## Kesalahan: position dan z-index

**Untuk apa:** badge/dropdown/modal yang hilang atau di belakang.

1. `absolute` tanpa induk `relative` → loncat ke leluhur jauh.
2. `sticky` tanpa `top`.
3. `sticky` di dalam `overflow: hidden`.
4. `z-index: 999` di dalam kartu `opacity: 0.99` tetap kalah kartu sebelah.
5. `fixed` di dalam `transform` tidak menempel viewport.
6. Dropdown terpotong `overflow: hidden` + `border-radius`.

```css
.kartu { position: relative; isolation: isolate; }
.dropdown { position: absolute; z-index: 20; }
```

Modal global: pindah ke `body` / portal, `z-index` skala (10 header, 40 overlay).

**Biasanya digabungkan dengan:** [bab 08](08-position-zindex-float-sticky.md).

## Kesalahan: gambar dan media

**Untuk apa:** foto tidak gepeng dan tidak meledak.

```css
img { max-width: 100%; height: auto; display: block; }
.thumb { aspect-ratio: 16 / 9; object-fit: cover; }
```

Jangan set `width` dan `height` CSS yang merusak rasio tanpa `object-fit`. Isi `alt`. Jangan background-image untuk konten bermakna (tidak ada alt).

SVG `width: 100%` tanpa `height` kadang 150px aneh — set `height: auto` atau kotak eksplisit.

**Biasanya digabungkan dengan:** `rounded` + `overflow: hidden`.

## Kesalahan: form dan fokus

**Untuk apa:** form yang bisa dipakai keyboard dan tidak berteriak error di load.

- `:invalid` pada `required` kosong aktif sejak awal → pakai `:user-invalid` atau class setelah submit.
- `outline: none` tanpa pengganti → tab tidak kelihatan.
- Placeholder sebagai satu-satunya label.
- `div` diklik jadi tombol tanpa `button` / `tabindex` / keyboard.
- Target sentuh &lt; ~44px.

```css
:focus-visible { outline: 2px solid #0369a1; outline-offset: 2px; }
```

**Biasanya digabungkan dengan:** `<label for>`, `aria-describedby`.

## Kesalahan: Tailwind

**Untuk apa:** class yang tertulis tetapi tidak berubah.

1. File JSX belum masuk `content` di config v3.
2. Typo: `justify-centre`, `items-centre`, `flex-column` (yang benar `flex-col`).
3. Konflik `p-2 p-8` — hasil tergantung urutan generated, bukan HTML.
4. `w-screen` overflow.
5. `space-x-4` + `flex-wrap` aneh; pakai `gap-4`.
6. `truncate` tanpa `min-w-0`.
7. `hover:` saja di HP, tidak ada state aktif/fokus.
8. `dark:` tidak jalan karena `darkMode` class tetapi `<html>` tanpa `dark`.
9. Arbitrary `bg-[#fff]` berulang — jadikan token.
10. Mencampur CSS module yang menimpa utility tanpa sadar.

**Biasanya digabungkan dengan:** [bab 13](13-tailwind-utility-lengkap.md), DevTools class list.

## Kesalahan: responsif

**Untuk apa:** HP dulu, desktop kemudian.

- Lupa `<meta name="viewport" ...>`.
- Desktop-first lalu lupa `max-width` untuk HP.
- `font-size: 5vw` tanpa `clamp` — kecil di HP, raksasa di TV.
- `hover` sebagai satu-satunya cara melihat menu.
- Breakpoint ikut iPhone tertentu (`375px`) bukan konten (`40rem` saat 2 kolom mulai muat).
- Container perlu query wadah, tetapi kamu hanya pakai `@media` layar — kartu di sidebar tetap 3 kolom.

```html
<meta name="viewport" content="width=device-width, initial-scale=1">
```

**Biasanya digabungkan dengan:** `grid-cols-1 md:grid-cols-2`, `@container`.

## Checklist sebelum kumpul tugas

1. Meta viewport ada.
2. `box-sizing: border-box` global.
3. Gambar tidak overflow (`max-width: 100%`).
4. Kontras teks vs latar cukup.
5. Fokus keyboard terlihat di tautan, tombol, input.
6. Tidak ada scroll horizontal di HP 320–390px.
7. Navbar wrap atau jadi menu, tidak potong.
8. Form punya label, error tidak hanya warna.
9. `prefers-reduced-motion` tidak diabaikan jika ada animasi loop.
10. Class/selector tidak perang dengan ID dan `!important` acak.
11. HTML semantik: heading berurut, `button` untuk aksi, `a` untuk pindah halaman.
12. Di React: `className`, bukan `class`.

Kalau satu item gagal, buka bab terkait di [indeks](README.md) daripada menambah CSS acak di bawah file.
