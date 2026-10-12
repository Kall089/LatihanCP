# 07 · Atribut global

[← Form](06-form-kontrol-lengkap.md) · [Daftar](README.md) · [Aksesibilitas →](08-aksesibilitas-aria.md)

**Untuk apa file ini:** atribut yang **boleh dipasang di hampir semua elemen**. `id` dan `class` yang paling sering. Yang lain mudah disalahgunakan jika hanya ditiru dari tutorial.

## Daftar isi

- [`id`](#id)
- [`class`](#class)
- [`style`](#style)
- [`title`](#title)
- [`hidden`](#hidden)
- [`tabindex`](#tabindex)
- [`accesskey`](#accesskey)
- [`contenteditable`](#contenteditable)
- [`draggable`](#draggable)
- [`spellcheck`](#spellcheck)
- [`lang`](#lang)
- [`dir`](#dir)
- [Atribut global tetangga yang sering ketemu](#atribut-global-tetangga-yang-sering-ketemu)
- [`data-*`](#data-)
- [Mana yang ke CSS, mana yang ke JS](#mana-yang-ke-css-mana-yang-ke-js)
- [Kesalahan atribut global](#kesalahan-atribut-global)

## `id`

**Untuk apa:** nama **unik** untuk satu elemen di halaman. Target tautan `#id`, target `label for`, target JS `getElementById`, target CSS `#id` (jarang ideal).

```html
<section id="harga">
  <h2>Harga</h2>
</section>
<a href="#harga">Lihat harga</a>

<label for="email">Email</label>
<input id="email" name="email" type="email" />
```

Aturan:

- Satu `id` = satu elemen. Dobel `id` merusak label, fragmen, dan JS.
- Tidak boleh spasi. Hindari karakter aneh. Aman: huruf, angka, `-`, `_`. Mulai dengan huruf.
- Huruf besar/kecil dianggap unik (`Harga` ≠ `harga`), tetapi jangan mengandalkan itu.
- Jangan memakai `id` yang sama di setiap kartu hasil `map` React. Pakai `useId()` atau id dari data.

```html
<!-- Salah: dua id sama -->
<h2 id="info">Info</h2>
<p id="info">...</p>
```

CSS `#harga` terlalu kuat dan tidak bisa dipakai ulang. Lebih rapi `.section-harga` atau `section` + utilitas. `id` tetap berguna untuk tautan dan label, bukan sebagai sistem gaya.

`id` kosong atau hanya angka (`id="1"`) bermasalah di CSS (`#1` bukan selector yang valid tanpa escape).

**Biasanya digabungkan dengan:** `href="#id"`, `for`, `aria-labelledby`, `aria-describedby`, `document.getElementById`, Next hash, `scroll-margin-top`. React: `id={useId()}` untuk form dalam komponen.

## `class`

**Untuk apa:** menandai **kelompok** elemen agar CSS/JS bisa memilih yang berulang. Boleh banyak class, dipisah spasi.

```html
<article class="kartu kartu--unggulan">
  <h3 class="kartu__judul">Paket 4 hari</h3>
</article>
```

```css
.kartu {
  border: 1px solid #cbd5e1;
  padding: 1rem;
}

.kartu--unggulan {
  border-color: #0f172a;
}
```

Tidak harus unik. Sepuluh kartu boleh `class="kartu"`.

Nama class tidak memengaruhi semantik HTML. `class="button"` pada `div` **tidak** membuatnya jadi tombol.

Di React: `className`, bukan `class`. Beberapa pustaka memakai `classNames` / `clsx` untuk menggabungkan:

```jsx
<article className={clsx("kartu", unggulan && "kartu--unggulan")}>
```

Tailwind = banyak class utilitas:

```html
<article class="rounded-xl border border-slate-200 p-4">
```

Jangan mencampur 15 class BEM *dan* 20 class Tailwind pada elemen yang sama tanpa aturan. Pilih satu sumber kebenaran per komponen.

JS:

```js
el.classList.add("terbuka");
el.classList.remove("terbuka");
el.classList.toggle("terbuka");
```

Jangan menulis `el.className += " terbuka"` berulang — mudah dobel dan menghapus class lain jika kamu salah assign.

**Biasanya digabungkan dengan:** seluruh CSS, Tailwind, `querySelector(".kartu")`, Laravel `class="{{ $aktif ? 'aktif' : '' }}"`.

## `style`

**Untuk apa:** CSS **sebaris** pada satu elemen. Mengalahkan banyak aturan stylesheet (kecuali `!important` tertentu).

```html
<p style="color: #b91c1c; max-width: 40rem;">Kuota tersisa 2 kursi.</p>
```

Pakai untuk:

- prototipe 30 detik
- nilai yang memang unik dan datang dari data (warna tema pengguna: `style="--tema: #0f172a"`)

Jangan pakai untuk:

- seluruh layout halaman
- hover/fokus (tidak bisa `:hover` di atribut style)
- media query

Custom property sebaris adalah pola yang wajar:

```html
<article style="--warna-aksen: #0f766e">
```

```css
.kartu {
  border-color: var(--warna-aksen);
}
```

Di React: `style={{ color: '#b91c1c', maxWidth: '40rem' }}` — objek, camelCase. Bukan string kecuali kamu tahu risikonya.

**Biasanya digabungkan dengan:** data dinamis (progress width), hindari di tugas yang menilai file `style.css` terpisah.

## `title`

**Untuk apa:** keterangan tambahan sebagai **tooltip mouse**. Bukan label, bukan pengganti teks tautan, bukan `alt`.

```html
<abbr title="Taman Nasional">TN</abbr>
<button type="button" title="Hapus item dari keranjang">Hapus</button>
```

Masalah:

- HP hampir tidak ada hover.
- Keyboard dan pembaca layar **tidak konsisten** membacanya.
- Muncul lambat, hilang cepat.
- Tooltip native tidak bisa di-style.

Jangan:

```html
<img src="peta.png" title="Peta" />
<!-- alt tetap wajib; title bukan cadangan alt -->
```

Jangan menaruh informasi wajib hanya di `title` (“wajib isi NIK”). Tulis di teks / `aria-describedby`.

**Biasanya digabungkan dengan:** `abbr`, ikon yang sudah punya teks terlihat. Tooltip kustom = JS + aksesibilitas sendiri, bukan atribut `title` saja.

## `hidden`

**Untuk apa:** menyembunyikan elemen **beserta turunannya** dari tampilan dan biasanya dari pohon aksesibilitas. Boolean.

```html
<p hidden>Pesan sukses akan muncul di sini.</p>
<div id="modal" hidden>
  <p>Isi dialog</p>
</div>
```

```js
modal.hidden = false;
```

Setara kasar CSS `display: none`, tetapi makna “ini memang tidak relevan sekarang” lebih jelas di HTML. CSS yang memaksa `display: block` pada `[hidden]` bisa **menampilkan kembali** elemen — jangan lawan `hidden` tanpa sadar.

```css
/* Berbahaya jika kamu tidak tahu akibatnya */
[hidden] {
  display: block;
}
```

Bukan untuk:

- menyembunyikan input tapi tetap mengirim nilai → `type="hidden"`
- menutup secara visual tetapi tetap ingin dibaca → itu bukan `hidden`
- accordion yang masih “ada” bagi AT → sering `hidden` pada panel, atau `hidden="until-found"` di browser baru

`hidden="until-found"` (dukungan bertambah): elemen tersembunyi tetapi bisa ditemukan lewat pencarian dalam halaman.

Jangan `hidden` + `aria-hidden="false"` bertentangan.

**Biasanya digabungkan dengan:** JS toggle, dialog, pesan sukses, React `{ok && <p>Terkirim</p>}` (lebih umum daripada atribut hidden).

## `tabindex`

**Untuk apa:** mengatur apakah elemen masuk urutan Tab, dan di posisi mana.

| Nilai | Untuk apa |
| --- | --- |
| tidak ada | elemen interaktif native (`a[href]`, `button`, `input`, …) sudah bisa di-Tab |
| `0` | masuk urutan Tab **alami** (dokumen). Untuk elemen yang kamu buat interaktif |
| `-1` | bisa difokus lewat JS (`el.focus()`) tetapi tidak di-Tab |
| `1`, `2`, `3`… | **jangan.** Memaksa urutan dan merusak navigasi |

```html
<!-- Dialog: fokus ke panel, tidak perlu Tab ke wrapper dari luar -->
<div
  id="dialog"
  role="dialog"
  aria-labelledby="judul-dialog"
  tabindex="-1"
>
  <h2 id="judul-dialog">Syarat trip</h2>
  <button type="button">Tutup</button>
</div>
```

```html
<!-- Custom control: lebih baik pakai button asli -->
<div class="sakelar" role="switch" aria-checked="false" tabindex="0">...</div>
```

Jika kamu menulis `tabindex="0"` pada `div`, kamu **berutang** keyboard: Enter/Space, fokus terlihat, peran ARIA. Lebih murah memakai `<button>`.

Jangan `tabindex="0"` pada setiap paragraf “agar bisa di-Tab”. Itu siksaan.

**Biasanya digabungkan dengan:** manajemen fokus dialog, skip link (`href` ke `main` dengan `tabindex="-1"` agar `focus()` jalan di beberapa browser), bab 08.

## `accesskey`

**Untuk apa:** pintasan huruf + modifier browser (Alt / Alt+Shift / Ctrl+Option, **berbeda per browser dan OS**).

```html
<button type="submit" accesskey="s">Kirim</button>
```

Masalah: bentrok dengan pintasan pembaca layar dan browser. Pengguna tidak melihat petunjuk yang konsisten. Hindari di situs publik kecuali intranet yang dilatih.

Jika dipakai, tampilkan petunjuk di UI, jangan andalkan tebakan Alt+S.

**Biasanya digabungkan dengan:** aplikasi internal. Bukan persyaratan tugas umum. Jangan meniru dari snippet lama.

## `contenteditable`

**Untuk apa:** membuat elemen bisa diketik seperti editor. Nilai `true` / `plaintext-only` / `false`.

```html
<p contenteditable="true">Ubah teks ini (latihan).</p>
<div contenteditable="plaintext-only" aria-label="Catatan cepat"></div>
```

Bukan pengganti `<textarea>` untuk form yang dikirim. Isi `contenteditable` **tidak** otomatis ikut `name` submit. Kamu harus menyalin ke `input hidden` atau mengirim lewat JS.

Masalah: paste HTML kotor, kursor, undo, dan aksesibilitas. `plaintext-only` mengurangi tag yang menempel.

Jangan membuat seluruh `body` jadi `contenteditable` kecuali kamu sedang membuat editor.

**Biasanya digabungkan dengan:** editor kaya (lebih baik pustaka), `input` hidden, React yang biasanya menghindari ini kecuali editor. Untuk tugas catatan, `textarea` lebih benar.

## `draggable`

**Untuk apa:** menandai elemen boleh di-drag API HTML Drag and Drop.

```html
<article draggable="true" id="kartu-1">Paket 4 hari</article>
```

Nilai: `true` / `false`. Gambar dan tautan sering sudah draggable secara default.

API ini tua dan janggal di HP. Untuk urut-urut kartu di HP, pointer event / pustaka lebih umum.

Tanpa JS `dragstart` / `drop` / `preventDefault` pada zona drop, atribut sendirian hampir tidak berguna.

**Biasanya digabungkan dengan:** `ondragstart` menyimpan `dataTransfer`, zona `ondragover` + `ondrop`. React: `onDragStart`. Aksesibilitas: sediakan tombol “naik/turun” selain drag.

## `spellcheck`

**Untuk apa:** meminta atau menolak koreksi ejaan browser.

```html
<textarea name="pesan" spellcheck="true"></textarea>
<input type="text" name="kode" spellcheck="false" autocomplete="off" />
```

Nilai `true` / `false`. Berguna mematikan pada kode, slug, nama ilmiah. Tidak merata di semua browser/OS. Bukan validasi.

**Biasanya digabungkan dengan:** `textarea` bahasa manusia, `lang="id"` agar kamus (kadang) cocok, input kode promo `false`.

## `lang`

**Untuk apa:** bahasa **elemen ini** dan turunannya, menimpa `lang` di `<html>`.

```html
<html lang="id">
  ...
  <p>Nama ilmiah: <i lang="la">Pterois volitans</i>.</p>
  <blockquote lang="en">
    <p>Do not stand on coral.</p>
  </blockquote>
</html>
```

Bantu pelafalan pembaca layar dan hyphenation CSS (`hyphens: auto`).

Kode: `id`, `en`, `id-ID` jarang perlu. Jangan `lang="idn"` (salah).

**Biasanya digabungkan dengan:** `html lang`, kutipan asing, `hreflang` pada tautan (bukan pengganti).

## `dir`

**Untuk apa:** arah tulis elemen.

| Nilai | Untuk apa |
| --- | --- |
| `ltr` | kiri ke kanan (Indonesia, Inggris) |
| `rtl` | kanan ke kiri (Arab, Ibrani) |
| `auto` | tebak dari karakter pertama yang kuat |

```html
<html lang="id" dir="ltr">
...
<p dir="rtl" lang="ar">مرحبا</p>
```

CSS `direction` meniru tampilan, tetapi `dir` di HTML lebih jujur untuk makna dan form (urutan kolom).

Untuk potongan yang campur angka dan Arab, `dir="auto"` atau elemen `bdi` kadang menolong.

**Biasanya digabungkan dengan:** situs multibahasa, `lang`, logical CSS (`margin-inline-start` bukan `margin-left`).

## Atribut global tetangga yang sering ketemu

Bukan daftar wajib dosen, tetapi muncul di HTML modern.

### `inert`

**Untuk apa:** membuat cabang pohon tidak bisa difokus, diklik, atau dibaca AT. Berguna saat modal terbuka: latar `inert`.

```html
<div id="aplikasi" inert>
  ...
</div>
<dialog open>Form</dialog>
```

Dukungan sudah baik di browser modern. Polyfill di proyek lama.

### `popover` / `popovertarget`

**Untuk apa:** popover native, tanpa JS untuk buka-tutup dasar.

```html
<button type="button" popovertarget="tips">Tips</button>
<div id="tips" popover>Bawa uang tunai.</div>
```

### `translate`

**Untuk apa:** `no` mencegah terjemahan otomatis pada nama merek / kode.

```html
<p>Kode booking: <span translate="no">AMPAT-4D</span></p>
```

### `enterkeyhint` / `inputmode` / `autocapitalize` / `autocomplete` / `autofocus`

Sudah dibahas di bab form. Secara teknis beberapa global atau hampir global pada elemen form.

### `is`

**Untuk apa:** custom built-in element. Di luar tugas biasa.

### `itemid` / `itemprop` / `itemscope` / `itemtype`

**Untuk apa:** microdata schema.org. Lebih sering orang memakai JSON-LD di `<script type="application/ld+json">`.

### `part` / `slot` / `exportparts`

**Untuk apa:** Shadow DOM / Web Component.

### `nonce`

**Untuk apa:** token CSP untuk skrip/gaya sebaris.

### `tabindex` sudah di atas; `role` dan `aria-*` di bab 08.

**Biasanya digabungkan dengan:** dialog native `<dialog>`, CSP Laravel, bukan dengan setiap tugas profil.

## `data-*`

**Untuk apa:** data kustom untuk JS, tanpa menyalahgunakan `id` atau `class` sebagai gudang nilai.

```html
<button type="button" data-paket-id="14" data-harga="8500000">
  Pilih 4 hari
</button>
```

```js
const btn = document.querySelector("[data-paket-id]");
const id = btn.dataset.paketId; // "14" — kebab jadi camelCase
const harga = Number(btn.dataset.harga);
```

Aturan:

- Nama setelah `data-`: huruf kecil, `-` boleh. Jangan `data-paketId` campur kapital di HTML.
- Nilai selalu string di DOM.
- Bukan untuk CSS kecuali kamu sadar (`[data-state="terbuka"]` sah dan berguna).
- Bukan rahasia.

Jangan `data-class` meniru sistem class. Jangan menaruh HTML besar di data attribute.

**Biasanya digabungkan dengan:** JS vanila, Alpine/kecil, tes `getByTestId` kadang `data-testid`. React lebih sering props/state daripada dataset, kecuali interop.

## Mana yang ke CSS, mana yang ke JS

| Kebutuhan | Atribut / tempat |
| --- | --- |
| Gaya berulang | `class` |
| Target unik tautan/label | `id` |
| Nilai untuk skrip | `data-*` atau state React |
| Sembunyi sekarang | `hidden` atau render bersyarat |
| Fokus programatik | `tabindex="-1"` + `.focus()` |
| Tooltip native | `title` (lemah) |
| Bahasa | `lang` |
| Arah | `dir` |
| CSS sekali jalan | `style` (hemat) |

Jangan menyimpan harga di `class="harga-8500000"`. Jangan memakai `id="kartu"` pada setiap kartu.

## Kesalahan atribut global

1. **`id` dobel.** Label dan `#fragmen` nyasar.
2. **CSS hanya lewat `#id`** sampai tidak bisa diulang.
3. **`class` pada `div` bernama `button`** tanpa `<button>`.
4. **Seluruh layout di `style=""`.**
5. **Informasi wajib hanya di `title`.**
6. **`tabindex="1"` ke atas** merusak urutan.
7. **`hidden` dilawan `display: flex` di CSS.**
8. **`contenteditable` sebagai form** tanpa `name`.
9. **`accesskey` bentrok** dengan AT.
10. **`data-*` berisi rahasia token.**

Latihan: pada halaman profil, beri `id` pada setiap `section` untuk navbar, `class` untuk kartu yang diulang, `lang` pada kutipan Inggris, dan nol `tabindex` positif.
