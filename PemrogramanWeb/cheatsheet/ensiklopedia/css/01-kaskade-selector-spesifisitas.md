# 01 — Kaskade, selector, dan spesifisitas

[← Indeks](README.md) · [Box model →](02-box-model-display-visibility.md)

CSS tidak “asal menempel”. Browser mengumpulkan semua aturan yang mengenai sebuah elemen, lalu memilih pemenang. Kalau selectormu kalah, halaman terlihat seolah CSS-mu tidak jalan.

## Daftar isi

- [Tiga tempat menulis CSS](#tiga-tempat-menulis-css)
- [Urutan kaskade](#urutan-kaskade)
- [Pewarisan](#pewarisan)
- [Kata kunci inherit initial unset revert](#kata-kunci-inherit-initial-unset-revert)
- [Properti all](#properti-all)
- [Spesifisitas](#spesifisitas)
- [Selector universal](#selector-universal)
- [Selector tipe](#selector-tipe)
- [Selector class](#selector-class)
- [Selector id](#selector-id)
- [Selector atribut](#selector-atribut)
- [Combinator](#combinator)
- [Daftar selector](#daftar-selector)
- [:not](#not)
- [:is](#is)
- [:where](#where)
- [:has](#has)
- [:scope dan nesting](#scope-dan-nesting)
- [!important](#important)
- [@layer](#layer)
- [Custom property](#custom-property)
- [Kesalahan selector](#kesalahan-selector)

## Tiga tempat menulis CSS

**Untuk apa:** memisahkan atau menempelkan aturan tampilan ke HTML.

```html
<link rel="stylesheet" href="style.css">
```

```html
<style>
  .kartu { padding: 1rem; }
</style>
```

```html
<p style="color: #164863">Papua Barat Daya</p>
```

External (`<link>`) untuk banyak halaman. Internal (`<style>`) untuk satu halaman atau tugas singkat. Inline untuk darurat atau atribut yang memang harus spesifik. Inline tidak bisa `:hover` atau `@media`.

**Biasanya digabungkan dengan:** satu file `style.css` sebagai sumber utama, plus class di HTML/Blade/`className` React.

## Urutan kaskade

**Untuk apa:** memahami siapa yang menang kalau dua aturan mengenai properti yang sama.

Urutan kasar dari yang kalah ke yang menang (disederhanakan untuk kuliah):

1. User agent (CSS bawaan browser).
2. Normal author CSS (file dan `<style>` kamu).
3. Inline style biasa.
4. Author `!important`.
5. Inline `!important`.

Di dalam CSS author yang sama, browser masih melihat: cascade layer → spesifisitas → urutan sumber. Yang ditulis belakangan menang hanya jika spesifisitasnya sama atau lebih tinggi.

```css
p { color: black; }
p { color: crimson; }
```

Paragraf jadi crimson karena kedua selector sama kuat, yang bawah menang.

**Biasanya digabungkan dengan:** DevTools tab Computed untuk melihat aturan yang dicoret.

## Pewarisan

**Untuk apa:** tahu properti mana yang menurun ke anak, mana yang tidak.

```css
article {
  color: #0f172a;
  font-family: Georgia, serif;
  border: 1px solid #cbd5e1;
}
```

`color` dan `font-family` diwariskan ke `<p>` di dalam artikel. `border` tidak diwariskan; anak tidak otomatis dapat bingkai. Properti yang sering diwariskan: warna teks, font, `line-height`, `letter-spacing`, `list-style`, `visibility`. Yang tidak: `margin`, `padding`, `border`, `width`, `display`, `background`.

**Biasanya digabungkan dengan:** set tipografi di `body` atau `article`, lalu override di judul.

## Kata kunci inherit initial unset revert

### inherit

**Untuk apa:** memaksa anak memakai nilai induk, termasuk properti yang biasanya tidak diwariskan.

```css
.tombol-tautan {
  color: inherit;
  font: inherit;
}
```

Tombol di dalam kartu berwarna gelap akan ikut gelap, tidak kembali ke biru bawaan browser.

**Biasanya digabungkan dengan:** reset tombol dan tautan di dalam komponen.

### initial

**Untuk apa:** mengembalikan properti ke nilai awal spesifikasi, bukan ke nilai induk.

```css
.judul-khusus {
  font-weight: initial;
}
```

`font-weight` judul kembali ke `normal`, meskipun induknya `700`.

**Biasanya digabungkan dengan:** menetralkan warisan yang mengganggu satu komponen.

### unset

**Untuk apa:** `inherit` jika properti memang diwariskan, `initial` jika tidak.

```css
.bersih {
  color: unset;
  margin: unset;
}
```

`color` kembali ke induk. `margin` kembali ke `0` (nilai awal), bukan ke margin induk.

**Biasanya digabungkan dengan:** reset cepat satu properti tanpa menghafal apakah ia diwariskan.

### revert

**Untuk apa:** mengembalikan ke nilai yang akan dipakai seolah aturan author-mu tidak ada (sering ke stylesheet browser atau user).

```css
.tautan-polos {
  color: revert;
  text-decoration: revert;
}
```

Tautan bisa kembali biru dan bergaris sesuai browser.

**Biasanya digabungkan dengan:** membatalkan reset global yang kebablasan.

### revert-layer

**Untuk apa:** mundur ke cascade layer sebelumnya, bukan ke seluruh origin.

```css
@layer dasar {
  a { color: navy; }
}
@layer tema {
  a { color: crimson; }
  .tautan-dasar { color: revert-layer; }
}
```

`.tautan-dasar` memakai `navy` dari layer `dasar`.

**Biasanya digabungkan dengan:** `@layer` di proyek yang memisahkan reset, komponen, dan utilitas.

## Properti all

**Untuk apa:** men-set ulang hampir semua properti sekaligus, kecuali `direction`, `unicode-bidi`, dan custom property.

```css
.widget {
  all: unset;
}
```

Komponen jadi “telanjang”: tidak mewarisi margin aneh dari reset global, lalu kamu bangun ulang dari nol.

**Biasanya digabungkan dengan:** web component, badge, atau tombol yang harus kebal terhadap CSS halaman.

## Spesifisitas

**Untuk apa:** menghitung siapa yang menang antar selector author di layer yang sama.

Browser menghitung kira-kira `(inline, ID, class/atribut/pseudo-class, tipe/pseudo-element)`.

| Selector | Skor kasar (ID, class, tipe) |
| --- | --- |
| `*` | 0,0,0 |
| `p` | 0,0,1 |
| `div p` | 0,0,2 |
| `.kartu` | 0,1,0 |
| `.kartu.aktif` | 0,2,0 |
| `[type="email"]` | 0,1,0 |
| `:hover` | 0,1,0 |
| `#nav` | 1,0,0 |
| `#nav .kartu p` | 1,1,1 |
| `style="..."` | menang atas semua selector biasa |
| `:where(.kartu)` | 0,0,0 (nol) |
| `:is(.kartu, #nav)` | mengikuti argumen terkuat (`#nav`) |
| `:not(.kartu)` | class di dalam `:not` dihitung |
| `:has(.kartu)` | isi `:has` dihitung |

```css
#hero p { color: red; }      /* 1,0,1 */
.hero p { color: blue; }     /* 0,1,1 */
```

Teks tetap merah meskipun `.hero p` ditulis di bawah. Tambah class, jangan kejar dengan ID.

**Biasanya digabungkan dengan:** class BEM atau utility, hindari ID untuk styling.

## Selector universal

**Untuk apa:** mengenai semua elemen. Paling sering untuk `box-sizing`.

```css
*,
*::before,
*::after {
  box-sizing: border-box;
}
```

Tanpa ini, `width: 100%` + `padding` mudah membuat kotak lebih lebar dari wadah.

**Biasanya digabungkan dengan:** reset margin `body`, bukan pewarnaan massal (berat dan sulit di-debug).

## Selector tipe

**Untuk apa:** mengenai semua elemen nama tag tertentu.

```css
p {
  line-height: 1.7;
}

h1, h2, h3 {
  line-height: 1.2;
}
```

Bagus untuk tipografi dasar. Jangan andalkan `div` sebagai selector utama; terlalu longgar.

**Biasanya digabungkan dengan:** class komponen di atas reset elemen.

## Selector class

**Untuk apa:** gaya yang dipakai berulang dan bisa digabung.

```css
.kartu { padding: 1rem; }
.kartu--unggulan { border-color: goldenrod; }
.kartu.habis { opacity: 0.55; }
```

Titik di CSS, tanpa titik di HTML: `class="kartu kartu--unggulan"`. Dua class tanpa spasi di CSS berarti elemen harus punya keduanya.

**Biasanya digabungkan dengan:** `className` React, `classList.toggle`, dan modifier.

## Selector id

**Untuk apa:** satu elemen unik. Spesifisitas tinggi.

```css
#checkout { scroll-margin-top: 5rem; }
```

Lebih sehat memakai ID untuk tautan dalam halaman, `label for`, atau `aria-labelledby`, bukan untuk mewarnai tombol.

**Biasanya digabungkan dengan:** `href="#checkout"` dan `scroll-margin-top` jika ada header sticky.

## Selector atribut

### Keberadaan atribut

**Untuk apa:** elemen yang punya atribut tertentu, nilainya tidak peduli.

```css
a[download] { font-weight: 600; }
input[required] { border-left: 3px solid crimson; }
```

**Biasanya digabungkan dengan:** form dan tautan berkas.

### Persis sama

**Untuk apa:** nilai atribut tepat sama.

```css
input[type="email"] { width: 100%; }
button[aria-pressed="true"] { background: #0f172a; color: white; }
```

Tanda kutip disarankan. `type=email` tanpa kutip rapuh.

**Biasanya digabungkan dengan:** `width: 100%`, `:focus-visible`, dan validasi.

### Daftar kata (~=)

**Untuk apa:** atribut yang berisi beberapa kata dipisah spasi, seperti `class` atau `rel`.

```css
a[rel~="external"] { padding-right: 1.2em; }
```

Cocok jika nilai adalah token, bukan substring acak.

**Biasanya digabungkan dengan:** ikon “buka tab baru”.

### Awalan bahasa (|=)

**Untuk apa:** nilai tepat sama atau diawali `nilai-`.

```css
[lang|="id"] { quotes: "“" "”" "‘" "’"; }
```

`id` dan `id-ID` kena, `idiot` tidak.

**Biasanya digabungkan dengan:** `html[lang]`.

### Awalan (^=)

**Untuk apa:** nilai diawali string tertentu.

```css
a[href^="https://"] { color: #0f766e; }
a[href^="#"] { font-style: italic; }
```

**Biasanya digabungkan dengan:** pewarnaan tautan internal vs eksternal.

### Akhiran ($=)

**Untuk apa:** nilai diakhiri string tertentu.

```css
a[href$=".pdf"] { font-weight: 600; }
img[src$=".svg"] { width: 1.25rem; }
```

**Biasanya digabungkan dengan:** ikon jenis berkas.

### Mengandung (*=)

**Untuk apa:** substring di mana saja.

```css
a[href*="youtube.com"] { color: #b91c1c; }
```

Mudah kena positif palsu. Lebih ketat daripada `^=` jika domain bisa muncul di query.

**Biasanya digabungkan dengan:** daftar tautan sumber.

### Bendera i dan s

**Untuk apa:** perbandingan atribut tanpa peduli huruf besar-kecil (`i`) atau sensitif (`s`).

```css
input[type="email" i] { text-transform: none; }
```

`EMAIL` dan `email` sama-sama kena jika browser mendukung bendera `i`.

**Biasanya digabungkan dengan:** form yang HTML-nya tidak konsisten.

## Combinator

### Descendant (spasi)

**Untuk apa:** elemen di dalam leluhur, sedalam apa pun.

```css
.kartu p { color: #334155; }
```

Semua `<p>` di dalam `.kartu`, termasuk yang terbungkus `<div>` lagi.

**Biasanya digabungkan dengan:** tipografi kartu atau artikel.

### Child (>)

**Untuk apa:** anak langsung saja.

```css
.kartu > h2 { margin-top: 0; }
.menu > a { padding: 0.5rem; }
```

`h2` di dalam nested card tidak ikut. Lebih aman untuk komponen.

**Biasanya digabungkan dengan:** kartu, menu, list item.

### Adjacent sibling (+)

**Untuk apa:** saudara kandung yang langsung menyusul.

```css
h2 + p { margin-top: 0.25rem; }
label + input { margin-top: 0.25rem; }
```

Hanya paragraf yang langsung di bawah `h2`.

**Biasanya digabungkan dengan:** jarak judul-isi, form vertikal.

### General sibling (~)

**Untuk apa:** semua saudara kandung setelahnya.

```css
h2 ~ p { max-width: 65ch; }
input:checked ~ .panel { display: block; }
```

Trik checkbox-hack: panel setelah checkbox ikut terbuka tanpa JavaScript.

**Biasanya digabungkan dengan:** accordion CSS murni, form kondisi.

### Nesting modern

**Untuk apa:** menulis combinator tanpa mengulang induk.

```css
.kartu {
  padding: 1rem;

  & > h2 { margin-top: 0; }
  & p { color: #334155; }
}
```

`&` mewakili selector luar. Tanpa `&`, beberapa browser tetap menestarkan sebagai descendant, tetapi tulis `&` agar niatmu jelas.

**Biasanya digabungkan dengan:** komponen di file CSS biasa atau CSS Modules.

## Daftar selector

**Untuk apa:** satu blok untuk banyak target.

```css
h1, h2, h3, .judul {
  font-family: Georgia, serif;
}
```

Koma = “atau”. Jangan salah ketik koma jadi descendant.

**Biasanya digabungkan dengan:** reset tipografi.

## :not

**Untuk apa:** elemen yang tidak cocok dengan selector di dalam.

```css
.kartu:not(.habis) { opacity: 1; }
a:not([href^="http"]) { font-style: italic; }
p:not(:last-child) { margin-bottom: 0.75rem; }
```

Spesifisitas `:not(.habis)` memasukkan class `.habis`. `:not(p)` memasukkan satu tipe.

```css
.menu a:not(:last-child) {
  border-right: 1px solid #e2e8f0;
}
```

Pemisah antar tautan tanpa garis di item terakhir.

**Biasanya digabungkan dengan:** `:last-child`, atribut, dan class state.

## :is

**Untuk apa:** menyingkat daftar alternatif; spesifisitas mengikuti argumen terkuat.

```css
:is(h1, h2, h3):hover {
  text-decoration: underline;
}

:is(.kartu, .panel) a {
  color: inherit;
}
```

Hati-hati:

```css
:is(.kartu, #sidebar) p { color: red; }
```

Spesifisitasnya seperti `#sidebar p`, jadi bisa menimpa `.kartu p` di tempat lain.

**Biasanya digabungkan dengan:** daftar heading atau komponen sejenis.

## :where

**Untuk apa:** sama seperti `:is`, tetapi spesifisitasnya nol.

```css
:where(h1, h2, h3) {
  line-height: 1.2;
}

.prosa h2 {
  line-height: 1.05;
}
```

Reset aman: class biasa selalu bisa menimpa tanpa perang spesifisitas.

**Biasanya digabungkan dengan:** file reset atau `@layer dasar`.

## :has

**Untuk apa:** memilih induk berdasarkan isi atau saudara di dalamnya. “Parent selector”.

```css
.kartu:has(img) {
  padding-top: 0;
}

form:has(:invalid) .peringatan {
  display: block;
}

.item:has(+ .item) {
  border-bottom: 1px solid #e2e8f0;
}

html:has(dialog[open]) {
  overflow: hidden;
}
```

Kartu yang berisi gambar kehilangan padding atas. Form yang punya field invalid menampilkan peringatan. `html:has(dialog[open])` mengunci scroll saat modal terbuka.

`:has` menghitung spesifisitas isinya. `.kartu:has(#unggulan)` sangat kuat.

**Biasanya digabungkan dengan:** form, kartu media, dialog, dan state tanpa class tambahan di induk.

## :scope dan nesting

**Untuk apa:** menandai akar selector saat query atau nesting.

```css
.daftar {
  & > :scope { }
}

.daftar {
  :scope > li { list-style: none; }
}
```

Di CSS nesting, `&` lebih umum daripada `:scope`. Di `element.querySelector(":scope > li")`, `:scope` adalah elemen tempat kamu memanggil query.

**Biasanya digabungkan dengan:** JavaScript `querySelector` dan CSS nest.

## !important

**Untuk apa:** memaksa kemenangan di origin yang sama. Senjata terakhir.

```css
.tersembunyi {
  display: none !important;
}
```

Sah untuk utility yang memang harus menang (`sr-only`, hide). Tidak sah sebagai obat selector yang kalah karena ID.

**Biasanya digabungkan dengan:** class utility, bukan selector halaman biasa.

## @layer

**Untuk apa:** mengelompokkan CSS agar urutan kemenangan bisa kamu tentukan, terlepas dari spesifisitas antar layer.

```css
@layer reset, dasar, komponen, utilitas;

@layer reset {
  * { box-sizing: border-box; }
  body { margin: 0; }
}

@layer dasar {
  a { color: navy; }
}

@layer komponen {
  .tombol { color: white; }
}

@layer utilitas {
  .text-merah { color: crimson; }
}
```

Utility di layer terakhir mengalahkan komponen meski spesifikasinya lebih rendah. Tailwind v3+ memakai model ini.

**Biasanya digabungkan dengan:** reset + komponen + utility; lihat [bab 11](11-media-query-container-layer.md).

## Custom property

**Untuk apa:** variabel yang mewarisi dan bisa diubah per cabang pohon.

```css
:root {
  --warna-teks: #0f172a;
  --warna-latar: #f8fafc;
  --spasi: 1rem;
}

.kartu {
  color: var(--warna-teks);
  background: var(--warna-latar);
  padding: var(--spasi);
}

.kartu--gelap {
  --warna-teks: #f8fafc;
  --warna-latar: #0f172a;
}
```

Anak memakai `var(--warna-teks)` akan ikut tema cabang `.kartu--gelap`. `var(--x, cadangan)` memakai cadangan jika `--x` tidak valid.

**Biasanya digabungkan dengan:** tema terang/gelap, spacing skala, dan Tailwind `theme()`.

## Kesalahan selector

**Untuk apa:** menghindari perang yang tidak perlu.

```css
div div div p span { color: red; }
#app .halaman .kartu .judul { }
```

Selector dalam tidak membuat CSS “lebih hebat”; ia hanya rapuh. Lebih baik `.kartu__judul` atau `.judul-kartu`.

```css
.tombol {
  color: white;
}
#hero .tombol {
  color: navy;
}
```

Kalau tombol di hero harus putih, jangan bungkus dengan ID. Turunkan spesifisitas lawan, atau pakai class modifier `.tombol--terang`.

**Biasanya digabungkan dengan:** satu class per peran visual, DevTools, dan `@layer`.
