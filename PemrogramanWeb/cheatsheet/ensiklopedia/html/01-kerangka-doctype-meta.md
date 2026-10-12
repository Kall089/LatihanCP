# 01 · Kerangka, doctype, dan meta

[← Daftar ensiklopedia HTML](README.md) · [Lanjut heading dan teks →](02-heading-teks-inline.md)

**Untuk apa file ini:** setiap halaman HTML yang dibuka browser butuh kerangka yang sama. Tanpa doctype, `charset`, dan `viewport`, huruf Indonesia bisa rusak dan CSS responsif bisa “tidak jalan di HP” tanpa sebab yang kelihatan.

## Daftar isi

- [Kerangka lengkap yang paling sering dipakai](#kerangka-lengkap-yang-paling-sering-dipakai)
- [`<!doctype html>`](#doctype-html)
- [`<html>`](#html)
- [`lang`](#lang)
- [`<head>`](#head)
- [`<body>`](#body)
- [`<title>`](#title)
- [`<meta>`](#meta)
- [`charset`](#charset)
- [`viewport`](#viewport)
- [`description`](#description)
- [`robots`](#robots)
- [`author` dan `application-name`](#author-dan-application-name)
- [`theme-color` dan `color-scheme`](#theme-color-dan-color-scheme)
- [`referrer`](#referrer)
- [`http-equiv`](#http-equiv)
- [Open Graph dan kartu sosial](#open-graph-dan-kartu-sosial)
- [`<link>`](#link)
- [`rel="stylesheet"`](#relstylesheet)
- [`rel="icon"`](#relicon)
- [`rel="canonical"`](#relcanonical)
- [`rel="preconnect"` / `dns-prefetch` / `preload`](#relpreconnect--dns-prefetch--preload)
- [`<script>`](#script)
- [`defer` dan `async`](#defer-dan-async)
- [`type="module"`](#typemodule)
- [`<base>`](#base)
- [`<noscript>`](#noscript)
- [Komentar HTML](#komentar-html)
- [Elemen void dan aturan susunan](#elemen-void-dan-aturan-susunan)
- [Entitas karakter](#entitas-karakter)
- [Kesalahan kerangka yang sering muncul](#kesalahan-kerangka-yang-sering-muncul)

## Kerangka lengkap yang paling sering dipakai

**Untuk apa:** titik awal hampir semua tugas HTML statis.

```html
<!doctype html>
<html lang="id">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="description" content="Panduan singkat menyelam di Raja Ampat." />
    <title>Jelajah Raja Ampat</title>
    <link rel="icon" href="favicon.svg" type="image/svg+xml" />
    <link rel="stylesheet" href="style.css" />
  </head>
  <body>
    <h1>Halo, Raja Ampat</h1>
    <script src="script.js" defer></script>
  </body>
</html>
```

Urutan yang aman:

1. Doctype paling atas.
2. `<html lang="id">` membungkus semuanya.
3. Di `<head>`: `charset` dulu, lalu `viewport`, lalu `title`, lalu CSS.
4. Di `<body>`: isi yang kelihatan.
5. JavaScript klasik di akhir `body` atau pakai `defer`.

**Biasanya digabungkan dengan:** [css.md](../../css.md) untuk `style.css`, [javascript.md](../../javascript.md) untuk `script.js`. Di React/Next, kerangka ini ditulis framework (`app/layout.js` atau `index.html` Vite). Di Laravel Blade, kerangka ini biasanya ada di `resources/views/layouts/app.blade.php`.

## `<!doctype html>`

**Untuk apa:** memberitahu browser “ini HTML modern”. Bukan tag biasa. Tidak punya penutup. Tidak punya atribut.

```html
<!doctype html>
```

Tanpa doctype, browser bisa masuk *quirks mode*: box model lama, `width` terhitung aneh, dan CSS yang di kelas kelihatan “benar” jadi bergeser.

Penulisan yang juga diterima:

```html
<!DOCTYPE HTML>
```

Huruf besar atau kecil tidak masalah. Yang penting ada, dan ada di baris pertama. Jangan taruh komentar atau BOM aneh di atasnya.

Jangan meniru doctype HTML4 kecuali kamu merawat situs museum:

```html
<!-- Jangan dipakai untuk tugas baru -->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
```

**Biasanya digabungkan dengan:** tidak ada CSS/JS khusus. Ini saklar mode browser. Di Next.js dan Vite, doctype sudah disediakan. Di Blade, tulis sekali di layout, bukan di setiap view anak.

## `<html>`

**Untuk apa:** akar dokumen. Semua tag lain (kecuali doctype) hidup di dalamnya.

```html
<html lang="id">
  <head>...</head>
  <body>...</body>
</html>
```

Anak langsung yang sah: satu `<head>` dan satu `<body>`. Jangan menaruh `<div>` sebagai saudara `head`.

### Atribut yang relevan di `<html>`

#### `lang`

Lihat bagian [`lang`](#lang) di bawah. Ini atribut paling penting di `<html>`.

#### `dir`

**Untuk apa:** arah tulis default seluruh halaman.

```html
<html lang="id" dir="ltr">
```

Nilai: `ltr` (kiri ke kanan, default untuk Indonesia), `rtl` (kanan ke kiri, Arab/Ibrani), `auto`. Pembahasan lengkap ada di [07-atribut-global.md](07-atribut-global.md).

#### `class` dan `data-*` di `<html>`

**Untuk apa:** menandai tema atau status halaman dari akar.

```html
<html lang="id" class="theme-gelap" data-js="siap">
```

Pola umum: JavaScript menambah `class` di `<html>` untuk *dark mode* atau “JS sudah aktif”. CSS lalu menulis `html.theme-gelap { ... }`.

**Biasanya digabungkan dengan:** CSS custom property di `:root` / `html`, React `document.documentElement.classList`, Laravel middleware yang menyuntik kelas tema dari session.

## `lang`

**Untuk apa:** menyatakan bahasa utama dokumen. Membantu pembaca layar mengucapkan kata, membantu terjemahan otomatis, dan membantu hyphenation.

```html
<html lang="id">
```

Nilai yang sering dipakai di kelas:

| Nilai | Bahasa |
| --- | --- |
| `id` | Indonesia |
| `en` | Inggris |
| `id-ID` | Indonesia, wilayah Indonesia (jarang diperlukan) |
| `en-US` / `en-GB` | Inggris Amerika / Inggris Britania |

Kalau satu frasa beda bahasa, taruh `lang` di elemen itu, bukan mengganti seluruh halaman:

```html
<p>Nama ilmiahnya <i lang="la">Pterois volitans</i>.</p>
```

Tanpa `lang`, pembaca layar bisa memakai pelafalan bahasa sistem. Tugas yang dinilai aksesibilitas biasanya memotong nilai jika `lang` kosong.

**Biasanya digabungkan dengan:** atribut global `lang` di elemen dalam (bab 07), `hreflang` pada tautan (bab 03), dan meta `og:locale`.

## `<head>`

**Untuk apa:** metadata. Isinya **tidak kelihatan sebagai artikel**, tapi menentukan judul tab, encoding, CSS, ikon, dan skrip yang dimuat awal.

```html
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Jelajah Raja Ampat</title>
  <link rel="stylesheet" href="style.css" />
</head>
```

Yang biasa masuk `<head>`:

- `<meta>`
- `<title>` (wajib, tepat satu)
- `<link>`
- `<script>` (boleh, tapi baca bagian `defer`)
- `<style>` (CSS tertanam; hindari jika file terpisah lebih rapi)
- `<base>` (jarang, hati-hati)
- `<noscript>` (opsional)

Yang **jangan** masuk `<head>`: `<h1>`, `<p>`, `<img>`, `<div>` sebagai isi halaman. Itu milik `<body>`. Browser sering “mengoreksi” dan memindahkannya, lalu layout jadi aneh.

**Biasanya digabungkan dengan:** Next.js `export const metadata` / `generateMetadata`, React Helmet hanya di proyek lama, Laravel `@section('title')` di layout.

## `<body>`

**Untuk apa:** semua yang pengguna lihat dan pakai: heading, teks, form, gambar, dan skrip yang berjalan setelah dokumen mulai dilukis.

```html
<body>
  <header>...</header>
  <main>
    <h1>Jelajah Raja Ampat</h1>
  </main>
  <footer>...</footer>
  <script src="script.js" defer></script>
</body>
```

Satu `<body>` per dokumen. Jangan membuat `<body>` kedua. Jangan membungkus seluruh isi dengan `<body>` di dalam komponen React: di aplikasi SPA, `<body>` sudah ada di `index.html`.

Atribut yang kadang dipakai di `<body>`:

```html
<body class="halaman-beranda" id="atas">
```

- `class` untuk gaya khusus satu jenis halaman (`halaman-login` vs `halaman-katalog`).
- `id="atas"` sebagai target tautan “kembali ke atas”.

**Biasanya digabungkan dengan:** CSS `body { margin: 0; min-height: 100dvh; }`, JS yang memasang listener di `document`/`window`, Blade `@yield('content')` di dalam body layout.

## `<title>`

**Untuk apa:** teks di tab browser, hasil bookmark, dan judul default di hasil pencarian.

```html
<title>Paket 4 Hari — Jelajah Raja Ampat</title>
```

Aturan praktis:

- Tepat **satu** `<title>` di `<head>`.
- Unik per halaman. Jangan semua halaman berjudul `Document` atau `Tugas`.
- Pendek dan spesifik: `Kontak — Jelajah Raja Ampat` lebih berguna daripada `Halaman`.
- Bukan tempat menaruh CSS atau skrip.

```html
<!-- Lemah -->
<title>Document</title>

<!-- Lebih baik -->
<title>Form pemesanan — Jelajah Raja Ampat</title>
```

**Biasanya digabungkan dengan:** Next.js `metadata.title` / `title.template`, React tidak mengubah tab kecuali kamu set `document.title` atau pakai API metadata framework, Laravel `@yield('title', 'Situs')`.

## `<meta>`

**Untuk apa:** data tentang halaman yang tidak tampil sebagai paragraf. Bentuknya elemen void: tidak ada `</meta>`.

Ada tiga “keluarga” utama:

| Pola | Untuk apa | Contoh |
| --- | --- | --- |
| `charset` | encoding huruf | `<meta charset="UTF-8">` |
| `name` + `content` | deskripsi, viewport, robots | `<meta name="description" content="...">` |
| `property` + `content` | Open Graph | `<meta property="og:title" content="...">` |
| `http-equiv` + `content` | meniru header HTTP | `<meta http-equiv="refresh" content="...">` |

Bagian berikut membedah yang paling sering dipakai, **satu atribut / satu nama**.

## `charset`

**Untuk apa:** memberitahu browser cara membaca byte menjadi huruf. Wajib UTF-8 untuk teks Indonesia, simbol `—`, dan emoji.

```html
<meta charset="UTF-8" />
```

Letakkan di awal `<head>`, sebelum `<title>` dan sebelum teks lain. Kalau encoding salah, kamu melihat `Raja Ampat` jadi `Raja Ampat` yang rusak, atau `â€”` menggantikan `—`.

Nilai yang benar untuk tugas baru: `UTF-8`. Jangan `ISO-8859-1` kecuali merawat arsip lama.

File-nya juga harus benar-benar tersimpan sebagai UTF-8. Meta saja tidak menolong jika editor menyimpan ANSI.

**Biasanya digabungkan dengan:** editor yang set encoding UTF-8, HTTP header `Content-Type: text/html; charset=utf-8` di Laravel / Next, dan tidak perlu CSS/JS.

## `viewport`

**Untuk apa:** mengatur lebar “jendela logis” di HP. Tanpa ini, HP sering menyusutkan halaman desktop jadi kecil, lalu CSS media query seolah tidak pernah jalan.

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
```

### Potongan `content` satu per satu

#### `width=device-width`

**Untuk apa:** lebar layout = lebar layar perangkat, bukan 980px warisan desktop lama.

#### `initial-scale=1.0`

**Untuk apa:** skala awal 100 persen. Pengguna masih bisa pinch-zoom.

#### `minimum-scale` / `maximum-scale` / `user-scalable=no`

**Untuk apa:** membatasi zoom. **Hindari** `user-scalable=no` dan `maximum-scale=1` di tugas yang dinilai aksesibilitas. Orang yang butuh membesarkan teks jadi terkunci.

```html
<!-- Jangan, kecuali ada alasan sangat kuat -->
<meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no" />
```

#### `viewport-fit=cover`

**Untuk apa:** mengizinkan warna menembus *notch* / *safe area* di iPhone. Hanya berguna jika CSS memakai `env(safe-area-inset-*)`.

```html
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover" />
```

**Biasanya digabungkan dengan:** CSS media query, Tailwind breakpoint `sm:`/`md:`, `padding` yang memakai `env(safe-area-inset-bottom)` untuk navbar bawah.

## `description`

**Untuk apa:** ringkasan halaman untuk mesin pencari dan kadang pratinjau tautan.

```html
<meta
  name="description"
  content="Itinerary 4 hari di Raja Ampat: Sorong, Waisai, Pianemo, dan Pulau Arborek."
/>
```

Tulis 1–2 kalimat jujur. Bukan tempat menjejalkan kata kunci. Halaman berbeda = deskripsi berbeda.

**Biasanya digabungkan dengan:** `og:description` (isi boleh sama), Next.js `metadata.description`, Blade `@section('meta')`.

## `robots`

**Untuk apa:** meminta mesin pencari mengindeks atau tidak.

```html
<meta name="robots" content="index, follow" />
<meta name="robots" content="noindex, nofollow" />
```

| Nilai | Artinya |
| --- | --- |
| `index` | boleh masuk hasil pencarian |
| `noindex` | jangan indekskan halaman ini |
| `follow` | boleh mengikuti tautan keluar |
| `nofollow` | jangan memakai tautan sebagai sinyal |
| `noarchive` | jangan simpan salinan cache publik |

Untuk tugas kuliah lokal, meta ini tidak mengubah nilai. Berguna saat halaman *staging* atau form internal tidak ingin muncul di Google.

**Biasanya digabungkan dengan:** header HTTP `X-Robots-Tag` di Laravel, `robots.txt` di folder `public`.

## `author` dan `application-name`

**Untuk apa:** mencatat penulis atau nama aplikasi. Dampak ke tampilan hampir nol.

```html
<meta name="author" content="Haikal Muzhoffar" />
<meta name="application-name" content="Jelajah Raja Ampat" />
```

`keywords` masih kadang ditiru dari tutorial lama. Mesin pencari besar sudah lama mengabaikannya. Tidak wajib.

```html
<!-- Tidak perlu untuk nilai praktikum modern -->
<meta name="keywords" content="raja ampat, papua, diving" />
```

**Biasanya digabungkan dengan:** tidak ada CSS. Boleh diisi dari data user Laravel jika layout memang menampilkannya di tempat lain.

## `theme-color` dan `color-scheme`

### `theme-color`

**Untuk apa:** mewarnai bilah UI browser di HP (Chrome Android, beberapa browser lain).

```html
<meta name="theme-color" content="#0f172a" />
<meta name="theme-color" content="#f8fafc" media="(prefers-color-scheme: light)" />
```

### `color-scheme`

**Untuk apa:** memberitahu browser apakah halaman punya tema terang, gelap, atau keduanya. Mempengaruhi warna scrollbar default dan form native.

```html
<meta name="color-scheme" content="light dark" />
```

Setara CSS:

```css
:root {
  color-scheme: light dark;
}
```

**Biasanya digabungkan dengan:** CSS `prefers-color-scheme`, class `dark` di Tailwind, `document.documentElement.classList.toggle('dark')`.

## `referrer`

**Untuk apa:** mengontrol berapa banyak URL asal yang dikirim saat pengguna mengklik tautan keluar.

```html
<meta name="referrer" content="strict-origin-when-cross-origin" />
```

Nilai yang sering dibahas:

| Nilai | Perilaku kasar |
| --- | --- |
| `no-referrer` | tidak mengirim Referer |
| `origin` | hanya `https://situsmu.test` |
| `strict-origin-when-cross-origin` | default modern yang wajar |
| `unsafe-url` | kirim path lengkap; hindari |

**Biasanya digabungkan dengan:** `rel="noreferrer"` pada tautan `target="_blank"` (bab 03), header Laravel `Referrer-Policy`.

## `http-equiv`

**Untuk apa:** meniru beberapa header HTTP dari dalam HTML. Pakai hemat.

### `refresh`

```html
<!-- Pindah ke /selesai setelah 5 detik. Hindari untuk konten utama. -->
<meta http-equiv="refresh" content="5; url=/selesai.html" />
```

Bisa mengejutkan pengguna dan pembaca layar. Lebih baik tautan biasa atau redirect server (Laravel `redirect()`, Next `redirect()`).

### `X-UA-Compatible`

```html
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
```

Hanya relevan untuk Internet Explorer lama. Tidak perlu di tugas 2026.

### `content-security-policy` di meta

**Untuk apa:** membatasi dari mana skrip dan gaya boleh dimuat. Lebih rapi sebagai header HTTP.

```html
<meta
  http-equiv="Content-Security-Policy"
  content="default-src 'self'; img-src 'self' https://images.contoh.test"
/>
```

Salah tulis satu token, CSS/JS tiba-tiba diblokir. Di kelas, biasanya cukup pahami bahwa CSP itu ada.

**Biasanya digabungkan dengan:** middleware Laravel, header Next.js, bukan dengan CSS visual.

## Open Graph dan kartu sosial

**Untuk apa:** mengatur judul, deskripsi, dan gambar saat tautan dibagikan ke chat atau media sosial. Bukan tag HTML semantik untuk pembaca layar.

```html
<meta property="og:title" content="Jelajah Raja Ampat" />
<meta property="og:description" content="Itinerary 4 hari, peta, dan paket kapal." />
<meta property="og:type" content="website" />
<meta property="og:url" content="https://contoh.test/raja-ampat" />
<meta property="og:image" content="https://contoh.test/images/pianemo.jpg" />
<meta property="og:locale" content="id_ID" />
<meta property="og:site_name" content="Jelajah" />

<meta name="twitter:card" content="summary_large_image" />
<meta name="twitter:title" content="Jelajah Raja Ampat" />
<meta name="twitter:description" content="Itinerary 4 hari, peta, dan paket kapal." />
<meta name="twitter:image" content="https://contoh.test/images/pianemo.jpg" />
```

### Atribut / properti satu per satu

#### `og:title`

**Untuk apa:** judul kartu. Boleh sama dengan `<title>`, boleh lebih pendek.

#### `og:description`

**Untuk apa:** satu-dua kalimat di bawah judul kartu.

#### `og:type`

**Untuk apa:** jenis objek. `website` untuk halaman biasa, `article` untuk berita.

#### `og:url`

**Untuk apa:** URL kanonik yang ingin kamu anggap “alamat resmi” halaman.

#### `og:image`

**Untuk apa:** gambar pratinjau. Pakai URL absolut. Ukuran yang aman: paling tidak 1200×630.

#### `og:locale`

**Untuk apa:** locale. Formatnya `id_ID`, bukan `id-ID`.

#### `twitter:card`

**Untuk apa:** bentuk kartu. `summary` = ikon kecil. `summary_large_image` = gambar lebar.

**Biasanya digabungkan dengan:** Next.js `metadata.openGraph` dan `metadata.twitter`, URL publik (localhost tidak bisa di-scrape oleh bot sosial), file gambar yang tidak diblokir login.

## `<link>`

**Untuk apa:** menghubungkan dokumen ini ke berkas lain: CSS, ikon, URL kanonik, atau petunjuk unduh awal.

```html
<link rel="stylesheet" href="style.css" />
```

Atribut inti:

| Atribut | Untuk apa |
| --- | --- |
| `rel` | hubungan: `stylesheet`, `icon`, `canonical`, ... |
| `href` | alamat berkas atau URL |
| `type` | MIME opsional (`text/css`, `image/svg+xml`) |
| `media` | CSS hanya untuk kondisi tertentu |
| `as` | petunjuk jenis unduhan untuk `preload` |
| `crossorigin` | CORS saat perlu hash / font |
| `integrity` | hash SRI untuk CDN |

Bagian berikut membedah `rel` yang paling sering.

## `rel="stylesheet"`

**Untuk apa:** memasang file CSS.

```html
<link rel="stylesheet" href="style.css" />
<link rel="stylesheet" href="print.css" media="print" />
```

Path relatif dihitung dari file HTML, bukan dari imajinasi folder proyek. Jika HTML di `/tugas/index.html` dan CSS di `/tugas/style.css`, tulis `href="style.css"`. Jika CSS di `/tugas/css/style.css`, tulis `href="css/style.css"`.

`media` menunda penerapan sampai kondisi cocok. `media="print"` tidak mewarnai layar.

**Biasanya digabungkan dengan:** semua bab CSS, Tailwind `@import` atau file build, Vite `/src/index.css` yang diimpor dari JS (bukan selalu lewat `<link>`), Blade `{{ asset('css/app.css') }}`.

## `rel="icon"`

**Untuk apa:** ikon tab.

```html
<link rel="icon" href="favicon.ico" sizes="any" />
<link rel="icon" href="favicon.svg" type="image/svg+xml" />
<link rel="apple-touch-icon" href="apple-touch-icon.png" />
```

Satu `favicon.ico` di akar situs masih diduga-duga browser meski kamu lupa menulis `<link>`. Tetap lebih jelas jika ditulis.

**Biasanya digabungkan dengan:** file di `public/` Laravel atau `app/` Next (`app/icon.png` bisa otomatis). Tidak butuh JS.

## `rel="canonical"`

**Untuk apa:** menunjuk URL resmi jika halaman yang sama bisa dicapai dari beberapa alamat (`/ampat`, `/ampat/`, `/index.html?utm=...`).

```html
<link rel="canonical" href="https://contoh.test/raja-ampat" />
```

**Biasanya digabungkan dengan:** `og:url`, Next.js `metadata.alternates.canonical`.

## `rel="preconnect"` / `dns-prefetch` / `preload`

**Untuk apa:** memberi petunjuk unduh, bukan menampilkan apa-apa.

```html
<link rel="preconnect" href="https://fonts.googleapis.com" />
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
<link rel="dns-prefetch" href="https://images.contoh.test" />
<link rel="preload" href="fonts/inter.woff2" as="font" type="font/woff2" crossorigin />
<link rel="preload" href="hero.jpg" as="image" />
<link rel="modulepreload" href="/assets/app.js" />
```

### Satu per satu

#### `preconnect`

**Untuk apa:** buka koneksi TCP/TLS lebih awal ke origin yang pasti dipakai (font, API).

#### `dns-prefetch`

**Untuk apa:** hanya resolusi DNS. Lebih ringan, lebih lemah daripada `preconnect`.

#### `preload`

**Untuk apa:** unduh berkas yang kamu tahu akan segera dipakai. Wajib `as`.

#### `prefetch`

**Untuk apa:** unduh untuk **navigasi berikutnya**, prioritas rendah.

#### `modulepreload`

**Untuk apa:** unduh modul ES lebih awal.

Jangan preload semua aset. Salah tebak = malah merebut bandwidth dari CSS penting.

**Biasanya digabungkan dengan:** Google Fonts, CDN gambar, `next/font` (sering menggantikan preload manual), `crossorigin` wajib untuk font.

## `<script>`

**Untuk apa:** menjalankan JavaScript atau menunjuk file JS.

```html
<script src="script.js" defer></script>
```

Atau sebaris (hindari jika file terpisah lebih rapi):

```html
<script>
  console.log("siap");
</script>
```

### Atribut satu per satu

#### `src`

**Untuk apa:** alamat file JS. Jika `src` ada, isi dalam tag diabaikan.

#### `type`

**Untuk apa:** jenis skrip.

| Nilai | Artinya |
| --- | --- |
| (kosong / `text/javascript`) | skrip klasik |
| `module` | ES module: `import`/`export`, default `defer` |
| `importmap` | peta import di browser |
| `application/ld+json` | data terstruktur JSON-LD, bukan kode yang dijalankan |

#### `defer`

**Untuk apa:** unduh paralel, jalankan setelah HTML selesai di-parse, urutan sesuai urutan tag. Pilihan paling aman untuk skrip yang menyentuh DOM.

#### `async`

**Untuk apa:** unduh paralel, jalankan segera setelah siap. Urutan tidak dijamin. Cocok analitik. Berbahaya jika skrip A butuh skrip B.

#### `nomodule`

**Untuk apa:** hanya dijalankan browser lama yang tidak paham `type="module"`.

#### `integrity`

**Untuk apa:** hash SRI. Browser menolak file CDN yang berubah.

```html
<script
  src="https://cdn.contoh.test/lib.js"
  integrity="sha384-....."
  crossorigin="anonymous"
></script>
```

#### `crossorigin`

**Untuk apa:** mode CORS. `anonymous` paling sering. Perlu agar `integrity` dan error stack lintas origin lengkap.

#### `referrerpolicy`

**Untuk apa:** Referer khusus permintaan skrip ini.

#### `blocking` (baru, dukungan bervariasi)

**Untuk apa:** menandai skrip yang boleh memblokir rendering. Jangan dipakai tanpa baca dukungan browser.

#### Tanpa `src`, dengan `type="module"`

```html
<script type="module">
  import { siap } from "./siap.js";
  siap();
</script>
```

**Biasanya digabungkan dengan:** [javascript.md](../../javascript.md), event `DOMContentLoaded` jika tidak pakai `defer`, React `main.jsx` yang di-bundle Vite, Next yang menyembunyikan tag script hasil build, Blade `@vite(['resources/js/app.js'])`.

## `defer` dan `async`

**Untuk apa:** mengatur kapan file JS berjalan relatif terhadap parsing HTML.

```html
<!-- Paling sering benar untuk script.js milikmu -->
<script src="script.js" defer></script>

<!-- Analitik yang boleh datang kapan saja -->
<script src="https://stat.contoh.test/a.js" async></script>
```

Perilaku kasar:

| Atribut | Parse HTML | Urutan | Menyentuh DOM aman? |
| --- | --- | --- | --- |
| (tidak ada) di tengah `head` | terblokir | berurutan | belum tentu, DOM bisa belum siap |
| `defer` | tidak terblokir | berurutan | ya, setelah dokumen ter-parse |
| `async` | tidak terblokir | tidak dijamin | hati-hati |
| `type="module"` | seperti `defer` | berurutan antar module | ya |

Kesalahan klasik: skrip di `<head>` tanpa `defer`, lalu `document.querySelector('button')` mengembalikan `null` karena tombol belum ada.

**Biasanya digabungkan dengan:** `querySelector` dan `addEventListener` di [javascript.md](../../javascript.md). React jarang menulis `defer` manual karena bundler menyisipkannya.

## `type="module"`

**Untuk apa:** mengaktifkan `import`/`export` di browser. Skrip module otomatis *deferred* dan berjalan dalam mode ketat.

```html
<script type="module" src="app.js"></script>
```

```js
// app.js
import { formatRupiah } from "./uang.js";
console.log(formatRupiah(150000));
```

Keterbatasan: file harus disajikan lewat HTTP (`npx serve`, Laravel, Vite). Membuka `index.html` sebagai `file://` sering gagal CORS untuk module.

**Biasanya digabungkan dengan:** JavaScript ES modules, Vite, bukan dengan `<script>` klasik yang mengandalkan variabel global.

## `<base>`

**Untuk apa:** mengubah URL dasar untuk semua `href`/`src` relatif di halaman.

```html
<base href="https://contoh.test/paket/" />
<a href="4-hari.html">Paket 4 hari</a>
<!-- jadi https://contoh.test/paket/4-hari.html -->
```

Mudah merusak tautan `#id` dan path CSS. Hindari kecuali kamu paham seluruh tautan relatif di halaman.

Hanya satu `<base>` yang dipakai, di `<head>`.

**Biasanya digabungkan dengan:** situs yang di-deploy di subfolder. Di Next/Laravel, *base path* biasanya diatur di config (`assetPrefix`, `ASSET_URL`), bukan tag `<base>`.

## `<noscript>`

**Untuk apa:** cadangan jika JavaScript dimatikan.

```html
<noscript>
  <p>Peta interaktif perlu JavaScript. <a href="peta-statis.html">Buka peta statis</a>.</p>
</noscript>
```

Boleh di `head` (terbatas, misalnya `<link>`) atau `body` (konten). Jangan mengandalkan ini sebagai “halaman utama”.

**Biasanya digabungkan dengan:** aplikasi yang memang butuh JS (React). Untuk tugas HTML murni, `<noscript>` jarang wajib.

## Komentar HTML

**Untuk apa:** catatan untuk manusia yang membaca kode. Tidak ditampilkan sebagai teks halaman, tetapi **tetap terkirim** ke browser. Jangan taruh rahasia.

```html
<!-- Formulir kontak, tugas pertemuan 5 -->
<form>...</form>
```

Bukan komentar:

```html
<!-- Salah: CSS di dalam HTML comment tidak “menonaktifkan” dengan rapi jika bersarang -->
```

Komentar tidak boleh bersarang. `--` di dalam komentar bisa memutus parser.

Di React, komentar JSX adalah `{/* ... */}`. Di Blade, komentar `{{-- ... --}}` tidak terkirim ke browser — lebih aman untuk catatan internal.

**Biasanya digabungkan dengan:** tidak ada. Jangan memakai komentar sebagai pengganti `hidden` atau `display: none`.

## Elemen void dan aturan susunan

**Untuk apa:** menghindari error “tag tidak tertutup” yang sebetulnya memang tidak boleh ditutup.

Elemen void umum (tidak ada tag penutup):

`area`, `base`, `br`, `col`, `embed`, `hr`, `img`, `input`, `link`, `meta`, `source`, `track`, `wbr`.

```html
<meta charset="UTF-8" />
<img src="peta.png" alt="Peta Waisai" />
<br />
```

Garis miring penutup `/>` opsional di HTML5, wajib-ish di JSX.

Aturan susunan yang sering dilanggar:

- `<p>` tidak boleh berisi `<div>`, `<h1>`, atau `<p>` lain.
- `<a>` tidak boleh berisi `<a>` lain.
- `<button>` tidak boleh berisi `<button>` atau tautan interaktif lain.
- `<ul>` / `<ol>` anak langsungnya `<li>` (bukan `<p>` telanjang).
- `<table>` punya model anak yang ketat: `caption`, `colgroup`, `thead`, `tbody`, `tr`, ...

Browser akan “memperbaiki” HTML rusak. Hasil perbaikan tidak selalu seperti yang kamu maksud.

**Biasanya digabungkan dengan:** validator HTML, DevTools Elements (lihat pohon yang *sebenarnya* terbentuk), linter JSX.

## Entitas karakter

**Untuk apa:** menulis karakter yang bermakna khusus di HTML, atau simbol yang susah diketik.

| Entitas | Hasil | Untuk apa |
| --- | --- | --- |
| `&amp;` | `&` | ampersand di teks |
| `&lt;` | `<` | tanda kurang dari |
| `&gt;` | `>` | tanda lebih dari |
| `&quot;` | `"` | kutip di atribut |
| `&apos;` | `'` | kutip satu |
| `&nbsp;` | spasi tidak putus | jarang perlu; jangan dipakai merapikan layout |
| `&mdash;` | — | garis em |
| `&ndash;` | – | garis en |
| `&copy;` | © | hak cipta |
| `&times;` | × | ikon kali |

```html
<p>Pakai &lt;strong&gt; untuk teks penting, bukan huruf tebal palsu.</p>
<p>Paket A &amp; B sudah termasuk tiket.</p>
```

Di React, teks dalam JSX sudah di-escape otomatis. `{foo}` yang berisi `<` tidak jadi tag.

**Biasanya digabungkan dengan:** konten dari Laravel `{{ $teks }}` (escape otomatis) vs `{!! $html !!}` (berbahaya jika data tidak dipercaya).

## Kesalahan kerangka yang sering muncul

1. **Tidak ada `charset`.** Huruf Indonesia dan tanda kutip pintar rusak.
2. **Tidak ada `viewport`.** Media query dan Flexbox “hancur” di HP.
3. **`<title>` masih `Document`.** Tab tidak terbaca saat banyak file terbuka.
4. **CSS 404.** `href="style.css"` salah folder. Cek Network di DevTools.
5. **JS di `head` tanpa `defer`.** `querySelector` dapat `null`.
6. **Dua `<html>` atau dua `<body>`.** Biasanya hasil *copy* kerangka ke tengah file.
7. **Membuka HTML module lewat `file://`.** `import` gagal.
8. **`<base href>` yang terlupakan.** Semua gambar tiba-tiba salah folder.
9. **Rahasia di komentar HTML.** Komentar terlihat di “View Source”.
10. **Mengira Next/Laravel tidak punya `head`.** Punya, hanya ditulis lewat layout/metadata.

Resep kerangka tugas kuliah: salin blok “kerangka lengkap” di atas, ganti judul, pastikan `style.css` dan `script.js` sefolder atau path-nya jujur, baru tulis isi di `<body>`.
