# 10 — Pseudo-class dan pseudo-element

[← Transform](09-transform-filter-transition-animation.md) · [Indeks](README.md) · [Media →](11-media-query-container-layer.md)

Pseudo-class (`:hover`) memilih **keadaan**. Pseudo-element (`::before`) memilih **bagian yang tidak ada di HTML**, atau potongan teks. Satu titik dua untuk class, dua untuk element (bentuk lama satu titik dua masih jalan di beberapa nama).

## Daftar isi

- [User action](#user-action)
- [Fokus](#fokus)
- [Tautan](#tautan)
- [Form](#form)
- [Struktural](#struktural)
- [Anak dan tipe](#anak-dan-tipe)
- [:not :is :where :has](#not-is-where-has)
- [Lain-lain](#lain-lain)
- [Pseudo-element](#pseudo-element)
- [Peta Tailwind](#peta-tailwind)

## User action

### :hover

**Untuk apa:** kursor di atas elemen.

```css
.tombol:hover { background: #0f172a; color: white; }
.kartu:hover { box-shadow: 0 8px 24px rgb(15 23 42 / 0.12); }
```

Di layar sentuh, hover bisa “nempel” setelah tap. Jangan taruh informasi penting hanya di hover. Media `hover: hover` membatasi ke perangkat yang benar-benar punya hover.

**Biasanya digabungkan dengan:** `transition`, `:focus-visible`, `@media (hover: hover)`.

### :active

**Untuk apa:** saat ditekan (mouse down / tap).

```css
.tombol:active { transform: scale(0.98); }
```

**Biasanya digabungkan dengan:** `:hover`, `transition`.

### :focus

**Untuk apa:** elemen yang punya fokus, termasuk klik mouse pada tombol/tautan.

```css
.input:focus { border-color: #0369a1; }
```

Klik tombol juga memicu `:focus`, sehingga outline muncul pada mouse — banyak yang lalu `outline: none` dan merusak keyboard.

**Biasanya digabungkan dengan:** lebih baik `:focus-visible`.

### :focus-visible

**Untuk apa:** fokus yang “perlu terlihat”, biasanya keyboard.

```css
.tombol:focus-visible {
  outline: 2px solid #0369a1;
  outline-offset: 3px;
}
```

Pola modern: tidak menonaktifkan outline global; pasang gaya ini.

**Biasanya digabungkan dengan:** `outline-offset`, `ring` Tailwind.

### :focus-within

**Untuk apa:** elemen atau **keturunannya** berfokus.

```css
.field:focus-within {
  border-color: #0369a1;
  box-shadow: 0 0 0 3px #bfdbfe;
}
```

Kartu field menyala saat input di dalamnya diketik.

**Biasanya digabungkan dengan:** form group, dropdown yang terbuka lewat fokus.

## Fokus

### :target

**Untuk apa:** elemen yang `id`-nya cocok dengan hash URL.

```css
#faq-2:target {
  background: #ecfdf5;
  scroll-margin-top: 5rem;
}
```

**Biasanya digabungkan dengan:** `scroll-margin-top`, accordion CSS.

### :target-within

**Untuk apa:** diri atau keturunan adalah `:target` (dukungan lebih baru).

```css
.bagian:target-within { outline: 1px dashed #0f766e; }
```

**Biasanya digabungkan dengan:** layout bersarang.

### :modal

**Untuk apa:** elemen di top layer, misalnya `<dialog open>` modal.

```css
dialog:modal { border: 0; padding: 1.25rem; }
```

**Biasanya digabungkan dengan:** `::backdrop`.

### :fullscreen

**Untuk apa:** elemen yang sedang fullscreen API.

```css
.video:fullscreen { background: black; }
```

**Biasanya digabungkan dengan:** pemutar video.

## Tautan

### :any-link

**Untuk apa:** `a` yang punya `href` (`:link` atau `:visited`).

```css
:any-link { color: #0f766e; }
```

**Biasanya digabungkan dengan:** reset tautan.

### :link dan :visited

**Untuk apa:** belum / sudah dikunjungi. `:visited` sangat dibatasi (privasi): hampir hanya warna.

```css
a:link { color: #0369a1; }
a:visited { color: #6d28d9; }
```

Tidak bisa mengubah `background-image` atau `opacity` secara bebas di `:visited`.

**Biasanya digabungkan dengan:** artikel, bukan tombol UI.

### :local-link

**Untuk apa:** tautan ke origin yang sama (dukungan terbatas).

```css
a:local-link { font-weight: 600; }
```

**Biasanya digabungkan dengan:** nav; cek dukungan atau pakai class.

## Form

### :disabled dan :enabled

**Untuk apa:** kontrol yang tidak / bisa dipakai.

```css
input:disabled {
  opacity: 0.6;
  cursor: not-allowed;
}
```

**Biasanya digabungkan dengan:** `aria-disabled` pada elemen non-form (tidak kena `:disabled`).

### :read-only dan :read-write

**Untuk apa:** field yang tidak bisa / bisa diedit.

```css
input:read-only { background: #f1f5f9; }
```

**Biasanya digabungkan dengan:** `readonly` HTML.

### :placeholder-shown

**Untuk apa:** field yang masih menampilkan placeholder (nilai kosong).

```css
input:placeholder-shown + .label-float {
  transform: none;
}
```

Trik label mengambang tanpa JS.

**Biasanya digabungkan dengan:** `::placeholder`, sibling label.

### :default

**Untuk apa:** opsi/radio/checkbox bawaan.

```css
input:default { outline: 1px dashed #94a3b8; }
```

**Biasanya digabungkan dengan:** form reset.

### :checked

**Untuk apa:** checkbox, radio, option terpilih.

```css
input[type="checkbox"]:checked + .teks { font-weight: 600; }

.switch input:checked + .track { background: #0f766e; }
```

**Biasanya digabungkan dengan:** `+` sibling, switch CSS.

### :indeterminate

**Untuk apa:** checkbox “sebagian” (diset JS `indeterminate = true`).

```css
input:indeterminate { accent-color: #ca8a04; }
```

**Biasanya digabungkan dengan:** pilih semua di tabel.

### :valid dan :invalid

**Untuk apa:** lolos / gagal validasi native (`required`, `type="email"`, `pattern`).

```css
input:invalid { border-color: #b91c1c; }
input:valid { border-color: #15803d; }
```

`:invalid` pada field `required` kosong sudah aktif **sejak load** — form terlihat “penuh error” sebelum disentuh. Lebih baik `:user-invalid` atau class JS setelah submit.

**Biasanya digabungkan dengan:** `:user-invalid`, pesan error.

### :user-valid dan :user-invalid

**Untuk apa:** validitas setelah pengguna berinteraksi.

```css
input:user-invalid { border-color: #b91c1c; }
```

**Biasanya digabungkan dengan:** `aria-describedby` pesan.

### :required dan :optional

**Untuk apa:** atribut `required` atau tidak.

```css
label:has(+ input:required)::after { content: " *"; color: #b91c1c; }
```

**Biasanya digabungkan dengan:** `:has`, teks “wajib”.

### :in-range dan :out-of-range

**Untuk apa:** `min`/`max` pada number/date/range.

```css
input:out-of-range { border-color: #b91c1c; }
```

**Biasanya digabungkan dengan:** `min`, `max`.

### :blank

**Untuk apa:** field kosong (dukungan masih timpang). Alternatif: `:placeholder-shown`.

```css
input:blank { background: #f8fafc; }
```

**Biasanya digabungkan dengan:** fallback `:placeholder-shown`.

### :autofill

**Untuk apa:** diisi browser/password manager.

```css
input:autofill { box-shadow: 0 0 0 1000px #ecfdf5 inset; }
```

Background kuning bawaan Chrome sulit ditimpa tanpa trik.

**Biasanya digabungkan dengan:** `box-shadow` inset.

## Struktural

### :root

**Untuk apa:** elemen akar dokumen (`html`). Spesifisitas lebih tinggi dari `html`.

```css
:root {
  --spasi: 1rem;
  --header-h: 3.5rem;
}
```

**Biasanya digabungkan dengan:** custom property global.

### :scope

**Untuk apa:** akar referensi. Di stylesheet nest, mirip `&`. Di JS `querySelector(":scope > li")`.

```css
.daftar > :scope { }
```

**Biasanya digabungkan dengan:** JS, nesting.

### :empty

**Untuk apa:** tidak punya anak, termasuk teks (spasi di HTML membuat **tidak** empty).

```css
.slot:empty { display: none; }
.slot:empty::before { content: "Belum ada data"; }
```

Komentar HTML tidak dihitung sebagai anak di sebagian browser modern untuk `:empty`, tetapi whitespace iya. Jangan andalkan jika template menaruh newline.

**Biasanya digabungkan dengan:** state kosong CSS.

## Anak dan tipe

### :first-child dan :last-child

**Untuk apa:** anak pertama/terakhir dari induk, **apa pun jenisnya**.

```css
.kartu :first-child { margin-top: 0; }
.menu li:last-child { border-right: 0; }
```

Kalau anak pertama adalah `<img>`, `p:first-child` tidak kena.

**Biasanya digabungkan dengan:** reset margin, pemisah.

### :only-child

**Untuk apa:** satu-satunya anak.

```css
.aksi:only-child { width: 100%; }
```

**Biasanya digabungkan dengan:** tombol tunggal vs sepasang.

### :nth-child()

**Untuk apa:** pola urutan di antara saudara, semua tipe dihitung.

```css
tr:nth-child(even) { background: #f8fafc; }
.kartu:nth-child(3n) { grid-column: span 2; }
li:nth-child(n + 4) { opacity: 0.7; }
li:nth-child(-n + 3) { font-weight: 600; }
```

Pola: `odd`, `even`, `An+B`. `n + 4` = dari ke-4 sampai akhir. `-n + 3` = tiga pertama.

**Biasanya digabungkan dengan:** tabel zebra, grid featured.

### :nth-last-child()

**Untuk apa:** sama, dihitung dari belakang.

```css
li:nth-last-child(-n + 2) { font-style: italic; }
```

Dua terakhir.

**Biasanya digabungkan dengan:** pemisah, “dan lain-lain”.

### :first-of-type :last-of-type :only-of-type

**Untuk apa:** pertama/terakhir/satu-satunya **dari tag yang sama**.

```css
.prosa p:first-of-type { font-size: 1.125rem; }
```

Gambar di atas tidak menghalangi `p:first-of-type`.

**Biasanya digabungkan dengan:** artikel, lead paragraph.

### :nth-of-type() :nth-last-of-type()

**Untuk apa:** pola hanya di antara saudara bertag sama.

```css
img:nth-of-type(odd) { border-radius: 0.75rem 0.15rem; }
```

**Biasanya digabungkan dengan:** gallery campuran teks.

### of S dalam nth-child

**Untuk apa:** hitung hanya yang cocok selector `S` (Selector Level 4).

```css
.kartu:nth-child(2n of .featured) { border-color: goldenrod; }
```

Bukan “setiap `.kartu` genap”, melainkan setiap item genap di antara yang `.featured`.

**Biasanya digabungkan dengan:** daftar campur.

## :not :is :where :has

Sudah di [bab 01](01-kaskade-selector-spesifisitas.md). Ringkas pakai:

```css
.menu a:not([aria-current="page"]) { color: #475569; }
:is(h1, h2, h3) { line-height: 1.2; }
:where(a) { text-decoration-thickness: 0.08em; }
.kartu:has(img) { padding-top: 0; }
form:has(:user-invalid) .ringkasan { display: block; }
```

**Biasanya digabungkan dengan:** form, kartu, reset.

## Lain-lain

### :lang()

**Untuk apa:** berdasarkan bahasa.

```css
:lang(id) { quotes: "“" "”"; }
p:lang(ar) { direction: rtl; }
```

**Biasanya digabungkan dengan:** `lang` di HTML.

### :dir()

**Untuk apa:** `ltr` atau `rtl` terhitung.

```css
.ikon:dir(rtl) { transform: scaleX(-1); }
```

**Biasanya digabungkan dengan:** ikon panah.

### :defined

**Untuk apa:** custom element yang sudah didefinisikan.

```css
my-card:not(:defined) { display: none; }
```

**Biasanya digabungkan dengan:** web component.

### :host :host() :host-context()

**Untuk apa:** di dalam shadow DOM.

```css
:host { display: block; }
:host([hidden]) { display: none; }
```

**Biasanya digabungkan dengan:** component stylesheet.

### :left :right :first (paged)

**Untuk apa:** `@page` cetak.

```css
@page :first { margin-top: 2in; }
```

**Biasanya digabungkan dengan:** `@media print`.

## Pseudo-element

### ::before dan ::after

**Untuk apa:** kotak palsu di dalam elemen. **Wajib** `content`.

```css
.wajib::after {
  content: " *";
  color: #b91c1c;
}

.kartu::before {
  content: "";
  position: absolute;
  inset: 0;
  background: rgb(15 23 42 / 0.35);
}

.kutip::before { content: "“"; }
```

`content: ""` untuk dekorasi kosong. Tanpa `content`, kotak tidak ada. Tidak tersedia pada elemen replaced tertentu (`img`, `input`) secara andal.

`::before` adalah anak pertama palsu, `::after` anak terakhir palsu. `z-index` dan `position` berlaku.

**Biasanya digabungkan dengan:** induk `relative`, ikon CSS, overlay.

### ::first-letter dan ::first-line

**Untuk apa:** huruf/baris pertama block.

```css
.prosa p::first-letter {
  font-size: 3em;
  float: left;
  line-height: 0.9;
  padding-right: 0.1em;
}

.prosa p::first-line { font-weight: 600; }
```

Hanya pada container block. Properti yang boleh terbatas.

**Biasanya digabungkan dengan:** artikel editorial.

### ::placeholder

**Untuk apa:** teks placeholder input/textarea.

```css
::placeholder { color: #94a3b8; opacity: 1; }
```

Beberapa browser memakai `opacity` bawaan < 1. Kontras placeholder sering gagal AA — jangan jadikan placeholder satu-satunya label.

**Biasanya digabungkan dengan:** `<label>` terlihat.

### ::selection

**Untuk apa:** teks yang disorot pengguna.

```css
::selection {
  background: #0f766e;
  color: white;
}
```

**Biasanya digabungkan dengan:** merek, uji kontras.

### ::marker

**Untuk apa:** peluru/angka list.

```css
::marker { color: #0f766e; }
```

**Biasanya digabungkan dengan:** `ol`, `ul`.

### ::backdrop

**Untuk apa:** latar belakang `dialog` modal / fullscreen.

```css
dialog::backdrop {
  background: rgb(15 23 42 / 0.5);
}
```

**Biasanya digabungkan dengan:** `dialog:modal`.

### ::file-selector-button

**Untuk apa:** tombol pada `input type="file"`.

```css
::file-selector-button {
  font: inherit;
  border: 0;
  background: #e2e8f0;
  padding: 0.4rem 0.75rem;
}
```

**Biasanya digabungkan dengan:** form unggah.

### ::cue

**Untuk apa:** subtitle `<track>` video.

```css
video::cue { font-size: 1.1rem; background: rgb(0 0 0 / 0.6); }
```

**Biasanya digabungkan dengan:** pemutar.

### ::part() dan ::slotted()

**Untuk apa:** menembus shadow DOM / slot.

```css
my-card::part(judul) { font-weight: 700; }
::slotted(img) { width: 100%; }
```

**Biasanya digabungkan dengan:** web component.

### ::spelling-error ::grammar-error ::target-text

**Untuk apa:** garis error ejaan, dan teks yang di-highlight oleh navigasi fragmen teks.

```css
::target-text { background: #fde68a; }
```

**Biasanya digabungkan dengan:** pencarian dalam halaman modern.

## Peta Tailwind

| Pseudo | Prefix Tailwind |
| --- | --- |
| `:hover` | `hover:` |
| `:focus` | `focus:` |
| `:focus-visible` | `focus-visible:` |
| `:focus-within` | `focus-within:` |
| `:active` | `active:` |
| `:visited` | `visited:` |
| `:disabled` | `disabled:` |
| `:checked` | `checked:` |
| `:required` | `required:` |
| `:invalid` | `invalid:` |
| `:first-child` | `first:` |
| `:last-child` | `last:` |
| `:only-child` | `only:` |
| `:nth-child(odd)` | `odd:` |
| `:nth-child(even)` | `even:` |
| `:empty` | `empty:` |
| `::before` | `before:` |
| `::after` | `after:` |
| `::placeholder` | `placeholder:` |
| `::file-selector-button` | `file:` |
| `::marker` | `marker:` |
| `::selection` | `selection:` |
| `::backdrop` | `backdrop:` |
| `:first-of-type` | `first-of-type:` |
| `:last-of-type` | `last-of-type:` |

```html
<button class="bg-slate-900 text-white hover:bg-slate-700 focus-visible:outline focus-visible:outline-2 focus-visible:outline-offset-2">
  Simpan
</button>
```

```html
<label class="flex items-center gap-2 has-[:checked]:font-semibold">
```

`has-` dan `peer-` / `group-` ada di [bab 13](13-tailwind-utility-lengkap.md).

**Biasanya digabungkan dengan:** `disabled:opacity-50 disabled:cursor-not-allowed`.
