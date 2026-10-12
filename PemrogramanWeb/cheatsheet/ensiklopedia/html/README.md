# Ensiklopedia Cheatsheet HTML

[← Cheatsheet HTML ringkas](../../html.md) · [Cheatsheet utama](../../README.md)

Ini adalah ensiklopedia HTML. Setiap tag dan atribut dijawab dengan tiga pertanyaan yang sama:

1. **Untuk apa** tag atau atribut ini?
2. Bagaimana **contoh HTML**-nya, plus penjelasan singkat?
3. **Biasanya digabungkan dengan** CSS, JavaScript, React, atau Laravel?

Bukan ringkasan satu halaman. File di folder ini membedah tag dan atribut **satu per satu**. Cheatsheet ringkas tetap ada di [html.md](../../html.md). Pakai folder ini kalau kamu butuh “tag ini ada, atributnya apa, biasanya dipasang bareng apa”.

HTML adalah **kerangka dan makna** halaman. Ia tidak mengatur warna, jarak, atau animasi. Ia mengatakan: ini judul, ini tombol, ini tautan, ini form. CSS mengatur tampilan. JavaScript mengatur perilaku. React menyusun UI dari komponen. Laravel mengolah data di server.

## Cara baca

1. Buka Markdown Preview di editor.
2. Mulai dari [kerangka, doctype, dan meta](01-kerangka-doctype-meta.md) kalau file HTML-mu baru kosong.
3. Lanjut ke teks, tautan, daftar, lalu semantik. Itu urutan yang paling sering dipakai di tugas.
4. Form ada di [bab 06](06-form-kontrol-lengkap.md). Semua `type` pada `<input>` dibahas terpisah.
5. Kalau elemennya “ada tapi tidak bisa di-Tab / tidak kebaca pembaca layar”, buka [aksesibilitas](08-aksesibilitas-aria.md).
6. Kalau tugasnya “bikin halaman profil / navbar / form kontak”, buka [resep dan kesalahan](09-resep-dan-kesalahan.md).

Format tiap entri:

```text
**Untuk apa:**
contoh HTML
penjelasan singkat
**Biasanya digabungkan dengan:**
```

Contoh kode adalah potongan terpisah, bukan satu proyek utuh. Jangan menempelkan semua contoh ke satu file HTML.

## Daftar bab

| File | Isi |
| --- | --- |
| [01-kerangka-doctype-meta.md](01-kerangka-doctype-meta.md) | `<!doctype>`, `<html>`, `<head>`, `<body>`, `<title>`, semua `<meta>` yang sering dipakai, Open Graph, `<link>`, `<script>`, `<base>`, `<noscript>` |
| [02-heading-teks-inline.md](02-heading-teks-inline.md) | `h1`–`h6`, `p`, `br`, `hr`, `strong`, `em`, `mark`, `small`, `sub`, `sup`, `span`, `b`, `i`, `u`, `s`, `code`, `pre`, `blockquote`, `q`, `abbr`, `time`, `wbr` |
| [03-tautan-gambar-media.md](03-tautan-gambar-media.md) | `a`, `img`, `picture`, `source`, `figure`, `figcaption`, `audio`, `video`, `track`, `iframe` |
| [04-list-table.md](04-list-table.md) | `ul`, `ol`, `li`, `dl`, `dt`, `dd`, `table`, `caption`, `thead`, `tbody`, `tfoot`, `tr`, `th`, `td`, `colgroup`, `col` |
| [05-semantik-sectioning.md](05-semantik-sectioning.md) | `header`, `nav`, `main`, `section`, `article`, `aside`, `footer`, `address`, `hgroup` |
| [06-form-kontrol-lengkap.md](06-form-kontrol-lengkap.md) | `form`, `label`, semua `type` pada `input`, `textarea`, `select`, `option`, `optgroup`, `datalist`, `fieldset`, `legend`, `button`, `output`, `meter`, `progress` |
| [07-atribut-global.md](07-atribut-global.md) | `id`, `class`, `style`, `title`, `hidden`, `tabindex`, `accesskey`, `contenteditable`, `draggable`, `spellcheck`, `lang`, `dir` |
| [08-aksesibilitas-aria.md](08-aksesibilitas-aria.md) | Label, `alt`, landmark, keyboard, ARIA yang aman dipakai di tugas, dan yang justru merusak |
| [09-resep-dan-kesalahan.md](09-resep-dan-kesalahan.md) | Resep halaman yang sering diminta plus kesalahan yang bikin nilai praktikum potong |

## Urutan belajar yang masuk akal

1. Kerangka halaman — biar file-mu valid dan huruf Indonesia tidak rusak.
2. Heading dan teks — biar hierarki bacaan benar, bukan hanya “huruf besar”.
3. Tautan dan gambar — biar bisa pindah halaman dan gambar punya `alt`.
4. Daftar dan tabel — biar data berurut atau berkolom, bukan tabel untuk layout.
5. Semantik — biar `header`/`main`/`footer` menggantikan tumpukan `div`.
6. Form — biar setiap input punya `label` dan `name`.
7. Atribut global — biar `id`/`class`/`hidden` dipakai di tempat yang benar.
8. Aksesibilitas — biar keyboard dan pembaca layar tidak dikorbankan.
9. Resep — biar tugas profil, navbar, dan form kontak tidak mulai dari kosong.

## HTML murni, React, atau Laravel Blade?

Ketiganya menulis tag yang sama. Yang berubah hanya cara menyusunnya.

| Tempat menulis | Contoh | Catatan |
| --- | --- | --- |
| File `.html` biasa | `<label for="nama">Nama</label>` | Cocok tugas pertemuan awal |
| React / Next.js | `<label htmlFor="nama">Nama</label>` | `class` jadi `className`, `for` jadi `htmlFor` |
| Laravel Blade | `<label for="nama">{{ $user->name }}</label>` | Data dari server; form POST butuh `@csrf` |

Jangan campur ketiga cara itu di satu file tanpa sadar. Satu halaman HTML statis tidak butuh `htmlFor`. Satu komponen React tidak memakai `@csrf` di dalam JSX kecuali kamu memang mengirim form HTML klasik.

## Yang tidak dibahas di sini

- Cara menginstal Node, React, Next, atau Composer. Itu ada di cheatsheet teknologi masing-masing.
- CSS selector dan Flexbox. Itu ada di [ensiklopedia CSS](../css/README.md) dan [css.md](../../css.md).
- `useState` dan Hooks. Itu ada di [ensiklopedia React](../react/README.md).
- Web Component, Custom Element, atau HTML Houdini tingkat dalam.

## Rujukan resmi

- [HTML di MDN](https://developer.mozilla.org/en-US/docs/Web/HTML)
- [HTML Living Standard](https://html.spec.whatwg.org/)
- [WAI-ARIA](https://www.w3.org/TR/wai-aria/)

Dicek ulang **22 September 2026**. Nama tag dan atribut mengikuti HTML Living Standard yang dipakai browser modern. Fitur usang (`<font>`, `<center>`, `<marquee>`, `<blink>`) hanya disebut sebagai peringatan, bukan resep.

## Pintasan per masalah

- Huruf `é` atau `–` rusak → [01](01-kerangka-doctype-meta.md) `charset`.
- CSS responsif tidak jalan di HP → [01](01-kerangka-doctype-meta.md) `viewport`.
- Judul terlalu banyak yang “paling besar” → [02](02-heading-teks-inline.md) `h1`.
- Gambar tidak kebaca pembaca layar → [03](03-tautan-gambar-media.md) `alt`.
- Tabel dipakai untuk menyusun navbar → [04](04-list-table.md) dan [05](05-semantik-sectioning.md).
- Form terkirim tapi server tidak dapat data → [06](06-form-kontrol-lengkap.md) atribut `name`.
- Label tidak terhubung ke input → [06](06-form-kontrol-lengkap.md) `for` + `id`.
- `class` vs `id` bingung → [07](07-atribut-global.md).
- Tombol dari `<div onclick>` → [08](08-aksesibilitas-aria.md) dan [09](09-resep-dan-kesalahan.md).
- Tugas “halaman profil lengkap” → [09](09-resep-dan-kesalahan.md).
