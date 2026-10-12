# 03 · Tautan, gambar, dan media

[← Heading dan teks](02-heading-teks-inline.md) · [Daftar](README.md) · [Daftar dan tabel →](04-list-table.md)

**Untuk apa file ini:** memindahkan pengguna ke tempat lain, menampilkan gambar yang jujur, dan memasang audio/video/iframe tanpa merusak aksesibilitas.

## Daftar isi

- [`<a>`](#a)
- [`href`](#href)
- [`target`](#target)
- [`rel`](#rel)
- [`download`](#download)
- [`hreflang`, `type`, `ping`](#hreflang-type-ping)
- [`<img>`](#img)
- [`src` dan `alt`](#src-dan-alt)
- [`width` dan `height`](#width-dan-height)
- [`srcset` dan `sizes`](#srcset-dan-sizes)
- [`loading`, `decoding`, `fetchpriority`](#loading-decoding-fetchpriority)
- [`<picture>` dan `<source>`](#picture-dan-source)
- [`<figure>` dan `<figcaption>`](#figure-dan-figcaption)
- [`<audio>`](#audio)
- [`<video>`](#video)
- [`<track>`](#track)
- [`<iframe>`](#iframe)
- [Peta gambar dan embed lama](#peta-gambar-dan-embed-lama)
- [Kesalahan media yang sering muncul](#kesalahan-media-yang-sering-muncul)

## `<a>`

**Untuk apa:** tautan. Memindahkan ke URL lain, ke `#id` di halaman yang sama, atau ke skema khusus seperti email.

```html
<a href="harga.html">Lihat harga</a>
<a href="#faq">Loncat ke FAQ</a>
<a href="https://contoh.test" target="_blank" rel="noreferrer">Situs luar</a>
```

Isi `<a>` harus bisa dikenali sebagai tautan: teks yang jujur, atau gambar yang `alt`-nya jujur. Hindari “klik di sini” tanpa konteks.

`<a>` tanpa `href` bukan tautan yang bisa di-Tab secara default. Itu “placeholder” tautan. Jika kamu butuh tombol aksi (buka modal, hitung, submit lewat JS), pakai `<button>`.

`<a>` tidak boleh berisi `<a>` lain. `<a>` tidak boleh berisi tombol interaktif.

**Biasanya digabungkan dengan:** CSS `:hover` / `:focus-visible`, `scroll-margin-top` pada target `#id`, React `href` biasa atau Next.js `<Link>`, Laravel `{{ route('paket.show', $paket) }}`.

## `href`

**Untuk apa:** tujuan tautan. Atribut paling penting pada `<a>`.

```html
<a href="index.html">Beranda</a>
<a href="/paket/4-hari">Paket 4 hari</a>
<a href="https://contoh.test/peta">Peta</a>
<a href="#info">Informasi</a>
<a href="mailto:halo@contoh.test">Kirim email</a>
<a href="tel:+629521234567">Telepon</a>
```

### Nilai satu per satu

#### Path relatif

**Untuk apa:** pindah relatif ke file sekarang.

```html
<!-- Dari /tugas/index.html -->
<a href="kontak.html">Kontak</a>
<a href="halaman/faq.html">FAQ</a>
<a href="../index.html">Naik folder</a>
```

#### Path absolut di origin yang sama

**Untuk apa:** mulai dari akar situs.

```html
<a href="/kontak">Kontak</a>
```

Berguna di Laravel/Next. Di file HTML yang dibuka sebagai file lokal atau di subfolder tugas, `/kontak` bisa nyasar ke akar disk atau akar server yang salah.

#### URL penuh

**Untuk apa:** situs lain atau URL pasti.

```html
<a href="https://developer.mozilla.org/">MDN</a>
```

Pakai `https://`. Tautan `http://` ke situs modern sering di-upgrade atau diblokir.

#### `#id` (fragmen)

**Untuk apa:** loncat ke elemen bertuliskan `id` yang sama.

```html
<a href="#harga">Harga</a>
...
<section id="harga">
  <h2>Harga</h2>
</section>
```

`id` harus unik. Target yang ketutup navbar sticky perlu `scroll-margin-top` (lihat resep bab 09).

#### `mailto:`

**Untuk apa:** membuka aplikasi email.

```html
<a href="mailto:halo@contoh.test?subject=Tanya%20paket">Tanya paket</a>
```

Tidak semua perangkat punya aplikasi email. Sediakan juga form atau nomor lain jika ini satu-satunya cara kontak.

#### `tel:`

**Untuk apa:** menelepon dari HP.

```html
<a href="tel:+629521234567">+62 952 1234 567</a>
```

#### `javascript:`

**Untuk apa:** jangan. Campur perilaku ke dalam URL. Pakai `<button>` + event listener.

#### `href="#"` dan `href="javascript:void(0)"`

**Untuk apa:** trik lama “tautan yang tidak ke mana-mana”. Mengotori riwayat dan membingungkan. Pakai `<button type="button">`.

**Biasanya digabungkan dengan:** `id` target, Next.js `Link href="/paket/4-hari"`, Laravel `url()` / `route()`, CSS `:target`.

## `target`

**Untuk apa:** di mana dokumen tujuan dibuka.

```html
<a href="harga.html">Tetap di tab ini</a>
<a href="https://contoh.test" target="_blank" rel="noreferrer">Tab baru</a>
```

| Nilai | Untuk apa |
| --- | --- |
| `_self` | tab/jendela sekarang (default) |
| `_blank` | tab/jendela baru |
| `_parent` | frame induk |
| `_top` | keluar dari semua frame |
| nama frame | ke `iframe` bernama itu |

`target="_blank"` tanpa `rel` yang tepat punya risiko keamanan lama (`window.opener`). Selalu pasang `rel="noopener"` atau `rel="noreferrer"`.

Jangan membuka tab baru untuk navigasi internal tanpa alasan. Pengguna yang tidak mengira tab baru bisa tersesat, terutama di HP.

**Biasanya digabungkan dengan:** `rel="noreferrer"`, teks “(buka tab baru)” jika penting, CSS tidak wajib. Di React: `target="_blank"` `rel="noreferrer"`.

## `rel`

**Untuk apa:** hubungan dokumen sekarang dengan tujuan. Pada tautan, yang paling sering:

```html
<a href="https://contoh.test" target="_blank" rel="noreferrer">Sumber</a>
<a href="https://sponsor.test" rel="nofollow sponsored">Sponsor</a>
```

### Nilai satu per satu

#### `noopener`

**Untuk apa:** jangan berikan `window.opener` ke tab baru.

#### `noreferrer`

**Untuk apa:** jangan kirim Referer, dan di banyak browser juga implikasi `noopener`. Pilihan praktis untuk tautan luar + `_blank`.

#### `nofollow`

**Untuk apa:** minta mesin pencari tidak memakai tautan sebagai sinyal peringkat.

#### `sponsored`

**Untuk apa:** tautan berbayar / iklan.

#### `ugc`

**Untuk apa:** tautan dari konten pengguna (komentar).

#### `next` / `prev` / `license` / `me` / `help`

**Untuk apa:** hubungan semantik yang lebih jarang di tugas kuliah.

Boleh menulis beberapa nilai, dipisah spasi: `rel="noreferrer nofollow"`.

**Biasanya digabungkan dengan:** `target="_blank"`, kebijakan SEO, sanitasi tautan user-generated di Laravel.

## `download`

**Untuk apa:** mengusulkan unduhan, bukan navigasi, untuk berkas same-origin.

```html
<a href="berkas/itinerary.pdf" download>Unduh itinerary</a>
<a href="berkas/itinerary.pdf" download="itinerary-raja-ampat.pdf">Unduh PDF</a>
```

Tanpa nilai, browser memakai nama file asli. Dengan nilai, kamu mengusulkan nama simpan.

Tidak dijamin untuk URL beda origin (CDN). Tidak mengubah file yang butuh login menjadi publik.

**Biasanya digabungkan dengan:** file di `public/` Laravel (`Storage::url`), header `Content-Disposition` di server jika nama harus dipaksa.

## `hreflang`, `type`, `ping`

### `hreflang`

**Untuk apa:** bahasa tujuan tautan, bukan bahasa teks tautan.

```html
<a href="https://contoh.test/en/ampat" hreflang="en">English version</a>
```

### `type`

**Untuk apa:** petunjuk MIME tujuan. Opsional.

```html
<a href="data.csv" type="text/csv">Unduh CSV</a>
```

### `ping`

**Untuk apa:** browser mengirim POST ke URL ini saat tautan diklik (pelacakan). Banyak pengguna memblokir. Jangan andalkan untuk analitik penting; lebih jujur event JS atau analitik server.

```html
<a href="/paket/4-hari" ping="/hit?dari=banner">Paket 4 hari</a>
```

**Biasanya digabungkan dengan:** situs multibahasa (`hreflang`), hampir tidak pernah `ping` di tugas kuliah.

## `<img>`

**Untuk apa:** menanam gambar. Elemen void.

```html
<img
  src="images/pianemo.jpg"
  alt="Gugusan pulau karst Pianemo dilihat dari puncak"
  width="1200"
  height="800"
/>
```

Bukan latar belakang CSS. Jika gambar punya makna (foto produk, peta, karya), pakai `<img>`. Jika murni dekorasi tekstur, CSS `background-image` boleh, atau `<img alt="">`.

**Biasanya digabungkan dengan:** `figure`/`figcaption`, CSS `max-width: 100%; height: auto`, Next.js `next/image`, Laravel `asset('images/pianemo.jpg')`.

## `src` dan `alt`

### `src`

**Untuk apa:** alamat berkas gambar. Wajib agar ada yang ditampilkan.

```html
<img src="images/pianemo.jpg" alt="Pianemo dari puncak" />
<img src="https://images.contoh.test/pianemo.jpg" alt="Pianemo dari puncak" />
```

Path salah = ikon rusak + teks `alt`. Cek Network. Huruf besar/kecil di nama file penting di server Linux.

### `alt`

**Untuk apa:** teks pengganti. Dibaca pembaca layar. Tampil jika gambar gagal. Bukan tempat menjejalkan kata kunci.

```html
<!-- Informatif -->
<img src="peta.png" alt="Peta jalur kapal dari Waisai ke Pianemo" />

<!-- Dekoratif murni: alt kosong, bukan tanpa atribut -->
<img src="ornamen-ombak.svg" alt="" />

<!-- Jangan -->
<img src="peta.png" />
<img src="peta.png" alt="gambar" />
<img src="peta.png" alt="image.jpg" />
```

Cara menulis `alt` yang berguna:

- Katakan isi yang relevan, bukan “gambar dari”.
- Jika gambar adalah tautan dan tidak ada teks lain, `alt` harus menjelaskan tujuan tautan.
- Jika informasi sudah ada di `figcaption` tepat di samping dan sama persis, `alt` bisa lebih singkat atau kosong — jangan dibacakan dua kali. Lebih aman: `alt` ringkas, caption lebih panjang.

Panjang: satu kalimat biasanya cukup. Infografis kompleks butuh deskripsi panjang di dekatnya, bukan novel di `alt`.

**Biasanya digabungkan dengan:** penilaian aksesibilitas tugas, `figure`, Next.js `alt` wajib di `<Image>`.

## `width` dan `height`

**Untuk apa:** cadangan rasio di layout agar halaman tidak “loncat” saat gambar selesai diunduh. Bukan pengganti CSS ukuran tampilan.

```html
<img src="pianemo.jpg" alt="Pianemo" width="1200" height="800" />
```

```css
img {
  max-width: 100%;
  height: auto;
}
```

`width`/`height` di HTML memakai piksel intrinsik (atau rasio). CSS mengatur ukuran di halaman. Keduanya boleh hidup bersama: HTML menjaga aspek, CSS menyesuaikan lebar kolom.

Tanpa cadangan ukuran, teks di bawah gambar meloncat turun — buruk untuk CLS dan nilai “halaman tidak bergeser”.

**Biasanya digabungkan dengan:** CSS di atas, `aspect-ratio`, `next/image` yang mengisi width/height otomatis dari file.

## `srcset` dan `sizes`

**Untuk apa:** menyediakan beberapa berkas agar HP tidak mengunduh foto 4000px.

```html
<img
  src="pianemo-800.jpg"
  srcset="pianemo-400.jpg 400w, pianemo-800.jpg 800w, pianemo-1600.jpg 1600w"
  sizes="(min-width: 768px) 50vw, 100vw"
  alt="Pianemo dari puncak"
/>
```

### `srcset` dengan `w`

**Untuk apa:** daftar “berkas + lebar aslinya”.

### `sizes`

**Untuk apa:** kira-kira selebar apa gambar akan tampil di viewport. Browser memilih berkas dari `srcset`.

### `srcset` dengan `x`

**Untuk apa:** kerapatan piksel (`1x`, `2x`) jika ukuran tampilan tetap.

```html
<img
  src="logo.png"
  srcset="logo.png 1x, ethan.p@example.com 2x"
  alt="Jelajah Raja Ampat"
  width="160"
  height="40"
/>
```

`src` tetap ada sebagai cadangan.

**Biasanya digabungkan dengan:** `<picture>` jika formatnya juga beda (AVIF/WebP), `next/image` yang menulis `srcset` otomatis, plugin pengolah gambar Laravel.

## `loading`, `decoding`, `fetchpriority`

### `loading`

**Untuk apa:** kapan unduh dimulai.

| Nilai | Untuk apa |
| --- | --- |
| `eager` | segera (default untuk banyak kasus) |
| `lazy` | tunda sampai dekat viewport |

```html
<img src="hero.jpg" alt="Laut Raja Ampat" width="1600" height="900" />
<img src="galeri-12.jpg" alt="Dermaga Arborek" loading="lazy" width="800" height="600" />
```

Jangan `lazy` pada gambar hero di atas lipatan: pengguna justru menunggu lebih lama.

### `decoding`

**Untuk apa:** petunjuk decode. `async` = jangan blokir render teks. `sync` = utamakan gambar ini. `auto` = biar browser.

```html
<img src="hero.jpg" alt="Laut Raja Ampat" decoding="async" />
```

### `fetchpriority`

**Untuk apa:** `high` untuk hero, `low` untuk yang tidak mendesak. Dukungan sudah luas di browser modern, tetap opsional.

```html
<img src="hero.jpg" alt="Laut Raja Ampat" fetchpriority="high" />
```

Atribut lain yang kadang muncul: `crossorigin`, `referrerpolicy`, `ismap`, `usemap` (peta gambar).

**Biasanya digabungkan dengan:** hero vs galeri, Lighthouse, `next/image` `priority`.

## `<picture>` dan `<source>`

**Untuk apa:** memilih **berkas berbeda** menurut format atau media query. Lebih kuat daripada `srcset` sendirian.

```html
<picture>
  <source type="image/avif" srcset="pianemo.avif" />
  <source type="image/webp" srcset="pianemo.webp" />
  <img src="pianemo.jpg" alt="Gugusan karst Pianemo" width="1200" height="800" />
</picture>
```

Art direction (potong beda di HP vs desktop):

```html
<picture>
  <source media="(min-width: 768px)" srcset="pianemo-lebar.jpg" />
  <img src="pianemo-potret.jpg" alt="Puncak Pianemo" width="800" height="1000" />
</picture>
```

### `<source>` di dalam `picture`

**Untuk apa:** kandidat. Browser memakai yang pertama ia dukung dan cocok.

Atribut:

| Atribut | Untuk apa |
| --- | --- |
| `type` | MIME (`image/webp`, `image/avif`) |
| `srcset` | berkas + deskriptor |
| `sizes` | sama seperti di `img` |
| `media` | kondisi viewport / media |

`source` di picture **tidak** memakai `src` (itu pola video/audio). Wajib ada `<img>` terakhir sebagai cadangan dan tempat `alt`.

**Biasanya digabungkan dengan:** build yang menghasilkan WebP/AVIF, CSS tidak menggantikan `media` di `source` (keduanya bisa, tetapi art direction lebih jujur di `picture`). Next.js sering menyembunyikan ini di `<Image>`.

## `<figure>` dan `<figcaption>`

**Untuk apa:** mengelompokkan media (gambar, bagan, kode, kutipan) dengan keterangan yang menjadi satu unit.

```html
<figure>
  <img src="images/pianemo.jpg" alt="Karst Pianemo dari puncak kayu" width="1200" height="800" />
  <figcaption>Puncak Pianemo, foto pagi sebelum kabut turun.</figcaption>
</figure>
```

`figcaption` boleh di awal atau akhir `figure`, tetapi hanya satu. Isi `figure` tidak harus gambar:

```html
<figure>
  <pre><code>npm run dev</code></pre>
  <figcaption>Perintah menjalankan server Vite.</figcaption>
</figure>
```

Jangan membungkus setiap gambar dekoratif. Pakai `figure` jika keterangan adalah bagian dari memahami media itu.

**Biasanya digabungkan dengan:** CSS `max-width` + `margin-inline: auto`, `figcaption { font-size: 0.9rem; }`, artikel blog, tugas laporan.

## `<audio>`

**Untuk apa:** memutar suara di halaman.

```html
<audio controls src="audio/ombak.mp3">
  Browser Anda tidak memutar audio.
  <a href="audio/ombak.mp3">Unduh ombak.mp3</a>
</audio>
```

Beberapa sumber:

```html
<audio controls preload="metadata">
  <source src="audio/ombak.mp3" type="audio/mpeg" />
  <source src="audio/ombak.ogg" type="audio/ogg" />
  Tidak mendukung audio. <a href="audio/ombak.mp3">Unduh</a>
</audio>
```

### Atribut satu per satu

#### `src`

**Untuk apa:** berkas tunggal. Alternatif: anak `<source>`.

#### `controls`

**Untuk apa:** tampilkan play/pause/volume native. Tanpa ini, audio tersembunyi kecuali kamu buat kontrol JS. Untuk tugas, **pasang `controls`**.

#### `autoplay`

**Untuk apa:** mainkan otomatis. Browser sering memblokir jika ada suara. Jangan pakai di tugas tanpa alasan sangat kuat. Mengganggu.

#### `loop`

**Untuk apa:** ulang terus.

#### `muted`

**Untuk apa:** mulai tanpa suara. Lebih relevan di video autoplay.

#### `preload`

| Nilai | Untuk apa |
| --- | --- |
| `none` | jangan unduh dulu |
| `metadata` | unduh durasi/header |
| `auto` | boleh unduh lebih awal |

#### `controlslist` (tidak di semua browser)

**Untuk apa:** menyembunyikan sebagian kontrol native (`nodownload`, dll). Jangan andalkan.

Isi teks di dalam `<audio>` hanya tampil jika elemen tidak didukung. Bukan “judul lagu”. Judul taruh di dekatnya sebagai `<p>` atau `figcaption`.

**Biasanya digabungkan dengan:** JS `play()`/`pause()` pada `HTMLAudioElement`, React `ref`, file di `public/`. Autoplay + suara = nilai aksesibilitas potong.

## `<video>`

**Untuk apa:** memutar video di halaman.

```html
<video
  controls
  width="640"
  height="360"
  poster="images/cuplikan-poster.jpg"
  preload="metadata"
>
  <source src="video/arborek.mp4" type="video/mp4" />
  <source src="video/arborek.webm" type="video/webm" />
  <track kind="captions" src="video/arborek-id.vtt" srclang="id" label="Indonesia" default />
  Video tidak dapat diputar. <a href="video/arborek.mp4">Unduh MP4</a>.
</video>
```

### Atribut satu per satu

#### `src` atau `<source>`

Sama seperti audio. MP4 (H.264) paling aman sebagai cadangan.

#### `controls`

**Untuk apa:** kontrol native. Wajib jika kamu tidak membuat kontrol sendiri yang lengkap (play, pause, seek, volume, fullscreen, teks).

#### `poster`

**Untuk apa:** gambar sebelum video diputar. Tetap tulis keterangan di dekat video; poster bukan `alt`.

#### `width` / `height`

**Untuk apa:** cadangan rasio. CSS: `max-width: 100%; height: auto`.

#### `autoplay`, `muted`, `loop`, `playsinline`

**Untuk apa:** pola “video latar”. Banyak browser hanya mengizinkan autoplay jika `muted`. `playsinline` mencegah iOS membuka fullscreen otomatis.

```html
<video autoplay muted loop playsinline poster="hero.jpg" aria-hidden="true">
  <source src="hero.mp4" type="video/mp4" />
</video>
```

Video latar dekoratif: sediakan `prefers-reduced-motion` (matikan di CSS/JS) dan jangan jadi satu-satunya cara menyampaikan informasi.

#### `preload`

Sama seperti audio.

#### `disablepictureinpicture`, `controlslist`

Opsional, dukungan bervariasi.

Jangan menanam video 200MB tanpa kompresi. Tugas cukup cuplikan kecil atau tautan unduh.

**Biasanya digabungkan dengan:** `<track>` untuk takarir, CSS aspect-ratio 16/9, JS jika kontrol kustom. Di React, `muted` harus sering ditulis `muted={true}` dan kadang `autoPlay` camelCase.

## `<track>`

**Untuk apa:** menambahkan trek teks ke video/audio: takarir, subtitle, bab, metadata. Elemen void, anak `video`/`audio`.

```html
<track
  kind="captions"
  src="video/arborek-id.vtt"
  srclang="id"
  label="Indonesia"
  default
/>
<track kind="subtitles" src="video/arborek-en.vtt" srclang="en" label="English" />
```

### Atribut satu per satu

#### `kind`

| Nilai | Untuk apa |
| --- | --- |
| `subtitles` | terjemahan dialog (bahasa lain) |
| `captions` | dialog + isyarat suara, untuk dengar terbatas |
| `descriptions` | deskripsi audio |
| `chapters` | bab navigasi |
| `metadata` | data untuk skrip, tidak ditampil default |

#### `src`

**Untuk apa:** file WebVTT (`.vtt`).

```vtt
WEBVTT

00:00:01.000 --> 00:00:04.000
Selamat datang di Arborek.

00:00:04.500 --> 00:00:08.000
Jangan menginjak karang.
```

#### `srclang`

**Untuk apa:** kode bahasa trek.

#### `label`

**Untuk apa:** nama di menu trek.

#### `default`

**Untuk apa:** aktifkan trek ini secara default.

Tanpa takarir, video berbicara tidak aksesibel. Untuk tugas yang menampilkan wawancara, siapkan `.vtt` meski sederhana.

**Biasanya digabungkan dengan:** `<video controls>`, folder `public/video/`, editor VTT. React: `<track default />`.

## `<iframe>`

**Untuk apa:** menanam dokumen lain: peta, video YouTube, halaman preview. Bukan untuk “menyisipkan sepotong HTML milikmu” — itu komponen atau include.

```html
<iframe
  title="Peta lokasi Waisai"
  src="https://www.openstreetmap.org/export/embed.html?bbox=...&amp;layer=mapnik"
  width="600"
  height="400"
  loading="lazy"
  referrerpolicy="no-referrer-when-downgrade"
></iframe>
```

### Atribut satu per satu

#### `src`

**Untuk apa:** URL dokumen yang ditanam. Banyak situs menolak di-embed (header `X-Frame-Options` / CSP `frame-ancestors`).

#### `title`

**Untuk apa:** nama iframe untuk pembaca layar. **Wajib secara praktik.** Tanpa `title`, pengguna dengar “frame” tanpa konteks.

#### `width` / `height`

**Untuk apa:** ukuran awal. CSS `width: 100%` + rasio lebih rapi di HP.

#### `loading="lazy"`

**Untuk apa:** tunda unduh iframe di bawah lipatan (peta, embed berat).

#### `name`

**Untuk apa:** target tautan `target="namaFrame"`.

#### `sandbox`

**Untuk apa:** kurangi kuasa halaman dalam iframe.

```html
<iframe
  title="Pratinjau HTML mahasiswa"
  src="/preview/123"
  sandbox="allow-scripts allow-forms"
></iframe>
```

Tanpa nilai, `sandbox` paling ketat. Token ditambah hanya yang dibutuhkan: `allow-scripts`, `allow-same-origin`, `allow-forms`, `allow-popups`, ...

`allow-scripts` + `allow-same-origin` bersama-sama melemahkan sandbox (halaman bisa menghapus sandbox-nya sendiri). Hati-hati.

#### `allow`

**Untuk apa:** Permissions Policy: kamera, geolokasi, fullscreen, autoplay, dll.

```html
<iframe
  title="Video lapangan"
  src="https://player.contoh.test/v/123"
  allow="fullscreen; picture-in-picture"
  allowfullscreen
></iframe>
```

#### `allowfullscreen`

**Untuk apa:** izin fullscreen klasik, masih sering dibutuhkan pemutar video.

#### `referrerpolicy`

**Untuk apa:** Referer untuk permintaan iframe.

#### `srcdoc`

**Untuk apa:** HTML inline sebagai isi iframe, bukan `src`. Berguna demo kecil. Tetap pasang `sandbox` jika isinya tidak dipercaya.

Jangan iframe-kan seluruh situs milikmu sebagai trik layout. Mahal dan merusak riwayat/aksesibilitas.

**Biasanya digabungkan dengan:** YouTube “embed”, Google Maps, CSS rasio 16/9, `title` wajib. Next.js kadang `next/script` untuk pemutar, bukan iframe mentah. Laravel harus mengirim header frame jika ingin *boleh* di-embed.

## Peta gambar dan embed lama

### `<map>` dan `<area>`

**Untuk apa:** hotspot di gambar. Jarang untuk UI modern; SVG + tautan lebih fleksibel.

```html
<img src="peta-pulau.png" alt="Peta tiga pulau" usemap="#peta-pulau" width="600" height="400" />
<map name="peta-pulau">
  <area shape="rect" coords="10,10,200,180" href="pianemo.html" alt="Pianemo" />
  <area shape="circle" coords="400,200,60" href="arborek.html" alt="Arborek" />
</map>
```

`alt` pada setiap `area` wajib secara praktik.

### `<embed>` dan `<object>`

**Untuk apa:** menanam PDF atau plugin lama. Untuk PDF, sering lebih jelas: tautan unduh + pratinjau gambar, atau iframe jika memang diperlukan.

```html
<embed src="itinerary.pdf" type="application/pdf" width="600" height="800" title="Itinerary PDF" />
```

Dukungan dan aksesibilitas PDF tertanam tidak merata. Sediakan tautan unduh.

**Biasanya digabungkan dengan:** tugas peta hotspot (jika dosen meminta), selain itu hindari.

## Kesalahan media yang sering muncul

1. **`<img>` tanpa `alt`.** Potong nilai. Dekorasi = `alt=""`, bukan atribut dihapus.
2. **`alt="gambar1.jpg"`.** Bukan deskripsi.
3. **Path `src`/`href` salah.** Cek relatif ke file HTML.
4. **`target="_blank"` tanpa `rel`.** Pasang `noreferrer`.
5. **`href="#"` + JS.** Itu tombol.
6. **Gambar hero `loading="lazy"`.** Lipatan atas justru telat.
7. **`<picture>` tanpa `<img>`.** Tidak ada cadangan dan tidak ada `alt`.
8. **Video autoplay bersuara.** Diblokir browser dan mengganggu.
9. **`<iframe>` tanpa `title`.** Frame anonim.
10. **Menanam seluruh halaman lewat iframe** sebagai “komponen”.

Resep aman tautan luar:

```html
<a href="https://contoh.test" target="_blank" rel="noreferrer">
  Laporan terumbu 2025
  <span class="sr-only">(buka tab baru)</span>
</a>
```

Resep aman gambar artikel: `figure` + `img` ber-`alt` + `figcaption` + `width`/`height` + `max-width: 100%`.
