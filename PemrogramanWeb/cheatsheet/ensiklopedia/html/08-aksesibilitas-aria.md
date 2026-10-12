# 08 · Aksesibilitas dan ARIA

[← Atribut global](07-atribut-global.md) · [Daftar](README.md) · [Resep dan kesalahan →](09-resep-dan-kesalahan.md)

**Untuk apa file ini:** agar halaman bisa dipakai dengan keyboard, pembaca layar, zoom, dan tanpa mengandalkan warna saja. Aturan emas: **pakai HTML yang benar dulu**. ARIA hanya menambal yang tidak bisa diungkapkan tag native.

## Daftar isi

- [Aturan emas ARIA](#aturan-emas-aria)
- [Keyboard dan fokus](#keyboard-dan-fokus)
- [Skip link](#skip-link)
- [Nama aksesibel: label, `alt`, teks tautan](#nama-aksesibel-label-alt-teks-tautan)
- [`aria-label`](#aria-label)
- [`aria-labelledby`](#aria-labelledby)
- [`aria-describedby`](#aria-describedby)
- [`aria-hidden`](#aria-hidden)
- [`aria-expanded` dan `aria-controls`](#aria-expanded-dan-aria-controls)
- [`aria-current`](#aria-current)
- [`aria-live`, `aria-atomic`, `role="status"`](#aria-live-aria-atomic-rolestatus)
- [`aria-invalid` dan `aria-required`](#aria-invalid-dan-aria-required)
- [`aria-disabled` vs `disabled`](#aria-disabled-vs-disabled)
- [`role` yang aman dan yang berbahaya](#role-yang-aman-dan-yang-berbahaya)
- [Landmark](#landmark)
- [Gambar, ikon, dan SVG](#gambar-ikon-dan-svg)
- [Warna dan gerak](#warna-dan-gerak)
- [Dialog dan fokus terperangkap](#dialog-dan-fokus-terperangkap)
- [Tabel dan heading](#tabel-dan-heading)
- [Pengujian singkat tanpa alat mahal](#pengujian-singkat-tanpa-alat-mahal)
- [Kesalahan aksesibilitas yang sering muncul](#kesalahan-aksesibilitas-yang-sering-muncul)

## Aturan emas ARIA

**Untuk apa:** menahan diri. ARIA yang salah lebih berbahaya daripada tidak ada ARIA.

1. **Jangan pakai ARIA jika HTML native sudah cukup.** `<button>` lebih baik daripada `<div role="button">`.
2. **Jangan mengubah makna native tanpa perlu.** `role="button"` pada `<h1>` merusak heading.
3. **Semua kontrol ARIA harus bisa keyboard.**
4. **Jangan `aria-hidden="true"` pada elemen yang bisa difokus.**
5. **Nama harus ada.** Tombol ikon tanpa teks, tanpa `aria-label`, tanpa `title` yang andal = “button” kosong.

```html
<!-- Benar -->
<button type="button">Tutup</button>

<!-- Boleh jika ikon saja -->
<button type="button" aria-label="Tutup">
  <span aria-hidden="true">×</span>
</button>

<!-- Salah -->
<div onclick="tutup()">Tutup</div>
```

**Biasanya digabungkan dengan:** bab 05–07, pengujian Tab, VoiceOver/NVDA jika ada.

## Keyboard dan fokus

**Untuk apa:** banyak pengguna tidak memakai mouse: motor, pembaca layar, remote TV, preferensi.

Urutan Tab mengikuti urutan sumber HTML, minus `tabindex` positif (jangan).

Elemen yang sudah bisa difokus tanpa usaha:

- `a[href]`
- `button` (jika tidak `disabled`)
- `input`, `select`, `textarea` (jika tidak `disabled`)
- `summary` dalam `details`
- iframe
- elemen `tabindex="0"` atau positif

Fokus harus **kelihatan**:

```css
:focus-visible {
  outline: 3px solid #0f766e;
  outline-offset: 2px;
}
```

Jangan `outline: none` tanpa pengganti. `:focus-visible` menjaga klik mouse tidak selalu cincin tebal, tetapi keyboard tetap terlihat.

Enter mengaktifkan tombol dan tautan. Space mengaktifkan tombol dan checkbox, menggulir halaman jika fokus di `body`. Jangan menelan Space di `div` aneh.

**Biasanya digabungkan dengan:** CSS di atas, urutan HTML yang logis, skip link.

## Skip link

**Untuk apa:** tautan pertama yang hanya “muncul saat difokus”, menuju `main`. Menghindari 20 tautan navbar setiap kali.

```html
<body>
  <a class="skip" href="#konten-utama">Loncat ke konten</a>
  <header>...</header>
  <main id="konten-utama" tabindex="-1">
    <h1>...</h1>
  </main>
</body>
```

```css
.skip {
  position: absolute;
  inset-inline-start: 0.5rem;
  top: 0.5rem;
  transform: translateY(-200%);
}

.skip:focus {
  transform: none;
}
```

`tabindex="-1"` pada `main` membantu beberapa browser benar-benar memindahkan fokus, bukan hanya menggulir.

**Biasanya digabungkan dengan:** satu `main`, navbar panjang. Wajib di banyak checklist kampus.

## Nama aksesibel: label, `alt`, teks tautan

**Untuk apa:** kata yang diucapkan alat bantu saat fokus tiba.

Sumber nama (disederhanakan, prioritas kasar):

1. `aria-labelledby` (jika ada)
2. `aria-label`
3. label native (`<label>`, `<legend>`, teks tombol, `alt` gambar)
4. `title` (cadangan lemah)

```html
<!-- Teks tautan jujur -->
<a href="harga.html">Lihat tabel harga paket</a>

<!-- Lemah -->
<a href="harga.html">Klik di sini</a>
```

Gambar dalam tautan: `alt` menjadi nama tautan jika tidak ada teks lain.

```html
<a href="index.html">
  <img src="logo.svg" alt="Beranda Jelajah Raja Ampat" />
</a>
```

Input: lihat bab 06. Jangan andalkan `placeholder`.

**Biasanya digabungkan dengan:** `for`/`id`, `alt` jujur, hindari ikon telanjang.

## `aria-label`

**Untuk apa:** memberi nama dari atribut, jika nama tidak (boleh) tampil di layar.

```html
<nav aria-label="Utama">...</nav>
<nav aria-label="Footer">...</nav>

<button type="button" aria-label="Tutup dialog syarat">
  <span aria-hidden="true">×</span>
</button>
```

Jangan meniru teks yang sudah kelihatan — dobel. Jangan `aria-label` pada `div` statis tanpa peran.

`aria-label` tidak selalu diterjemahkan mesin terjemah. Teks terlihat lebih aman untuk nama panjang.

Untuk `nav` kedua, `aria-label` hampir wajib agar rotor tidak berisi dua “Navigation” identik.

**Biasanya digabungkan dengan:** landmark ganda, tombol ikon, pencarian (`aria-label="Cari paket"` jika label visual disembunyikan — lebih baik label terlihat).

## `aria-labelledby`

**Untuk apa:** nama diambil dari **elemen lain** (bisa beberapa id, dipisah spasi).

```html
<section aria-labelledby="judul-harga">
  <h2 id="judul-harga">Harga</h2>
  ...
</section>

<div role="dialog" aria-labelledby="judul-dialog" aria-modal="true">
  <h2 id="judul-dialog">Syarat trip</h2>
</div>
```

Lebih baik daripada menyalin teks ke `aria-label`: satu sumber kebenaran. Jika judul berubah, nama landmark ikut.

Id harus ada. Typo = nama kosong.

Boleh merujuk elemen yang `hidden` — hati-hati, pastikan teksnya tetap masuk akal.

**Biasanya digabungkan dengan:** `section`/`dialog`/`figure` yang judulnya sudah tampil.

## `aria-describedby`

**Untuk apa:** **keterangan tambahan**, bukan nama. Pesan bantuan, error, satuan.

```html
<label for="tamu">Jumlah tamu</label>
<input
  id="tamu"
  name="tamu"
  type="number"
  min="1"
  max="12"
  aria-describedby="tamu-bantuan tamu-error"
  aria-invalid="true"
/>
<p id="tamu-bantuan">Maksimal 12 orang per perahu.</p>
<p id="tamu-error">Isi antara 1 dan 12.</p>
```

Pembaca layar membaca nama dulu (label), lalu deskripsi (sering saat fokus). Jangan menaruh novel.

Beberapa id = gabung urutan.

**Biasanya digabungkan dengan:** error Laravel/React, teks bantuan, `aria-invalid`.

## `aria-hidden`

**Untuk apa:** menyembunyikan dari pohon aksesibilitas, **bukan** selalu dari tampilan.

```html
<button type="button" aria-label="Favorit">
  <span aria-hidden="true">★</span>
</button>

<img src="ornamen.svg" alt="" aria-hidden="true" />
```

`alt=""` pada gambar dekoratif sudah cukup; `aria-hidden` pada ikon di dalam tombol ber-label mencegah “bintang Favorit” dobel.

Jangan:

```html
<button aria-hidden="true">Kirim</button>
<!-- Bisa jadi masih bisa di-Tab di beberapa kasus, atau hilang maknanya -->
```

Jangan `aria-hidden="true"` pada induk yang berisi kontrol yang bisa difokus. Fokus “masuk ke lubang hitam”.

`hidden` HTML sudah menyembunyikan dari AT. Tidak perlu dobel kecuali kamu menyembunyikan secara visual dengan CSS tanpa `hidden`.

**Biasanya digabungkan dengan:** ikon dekoratif, SVG sprite, modal (latar lebih aman `inert`).

## `aria-expanded` dan `aria-controls`

**Untuk apa:** tombol yang membuka/menutup wilayah: hamburger, accordion, combobox.

```html
<button
  type="button"
  aria-expanded="false"
  aria-controls="menu-utama"
  id="tombol-menu"
>
  Menu
</button>
<ul id="menu-utama" hidden>
  <li><a href="#home">Beranda</a></li>
</ul>
```

```js
tombol.addEventListener("click", () => {
  const buka = tombol.getAttribute("aria-expanded") !== "true";
  tombol.setAttribute("aria-expanded", String(buka));
  menu.hidden = !buka;
});
```

`aria-expanded` harus **di-update**. Nilai statis `true` selamanya = dusta.

`aria-controls` menunjuk id wilayah. Dukungan pengumuman bervariasi, tetap berguna sebagai hubungan.

Accordion:

```html
<h2>
  <button type="button" aria-expanded="false" aria-controls="faq-1">
    Apakah tiket kawasan termasuk?
  </button>
</h2>
<div id="faq-1" hidden>
  <p>Tidak. Dijelaskan di hari keberangkatan.</p>
</div>
```

`details`/`summary` memberi pola native tanpa ARIA:

```html
<details>
  <summary>Apakah tiket kawasan termasuk?</summary>
  <p>Tidak. Dijelaskan di hari keberangkatan.</p>
</details>
```

**Biasanya digabungkan dengan:** JS toggle, CSS hamburger, React `useState` + `aria-expanded={buka}`.

## `aria-current`

**Untuk apa:** menandai item **sekarang** di himpunan: halaman, langkah, tanggal.

```html
<nav aria-label="Utama">
  <ul>
    <li><a href="index.html" aria-current="page">Beranda</a></li>
    <li><a href="harga.html">Harga</a></li>
  </ul>
</nav>
```

| Nilai | Untuk apa |
| --- | --- |
| `page` | halaman aktif di nav |
| `step` | langkah wizard |
| `location` | lokasi di peta/breadcrumb |
| `date` / `time` | kalender |
| `true` | umum |

CSS:

```css
[aria-current="page"] {
  font-weight: 700;
}
```

Lebih semantik daripada hanya `class="aktif"`. Boleh keduanya.

**Biasanya digabungkan dengan:** Next.js `usePathname()`, Laravel `request()->routeIs()`, breadcrumb.

## `aria-live`, `aria-atomic`, `role="status"`

**Untuk apa:** mengumumkan perubahan yang **tidak** memindahkan fokus: hasil filter, “tersimpan”, sisa karakter, error setelah submit AJAX.

```html
<p role="status" aria-live="polite" id="status-cari"></p>
```

```js
status.textContent = "12 paket cocok.";
```

| Nilai `aria-live` | Untuk apa |
| --- | --- |
| `off` | default, tidak diumumkan |
| `polite` | tunggu jeda bicara (paling sering) |
| `assertive` | potong — hanya error mendesak |

`role="status"` implisit `aria-live="polite"`. `role="alert"` implisit `assertive`.

`aria-atomic="true"`: bacakan seluruh wilayah, bukan hanya bagian yang berubah.

Jangan `assertive` pada setiap ketikan pencarian — bising. Debounce dulu.

Jangan live region untuk konten panjang. Jangan menaruh seluruh daftar 50 kartu di live.

**Biasanya digabungkan dengan:** filter JS (contoh-praktik cheatsheet), form AJAX, React `role="status"` di dekat hasil.

## `aria-invalid` dan `aria-required`

### `aria-invalid`

**Untuk apa:** menandai kontrol gagal validasi setelah dicek.

```html
<input
  id="email"
  name="email"
  type="email"
  aria-invalid="true"
  aria-describedby="email-error"
/>
<p id="email-error">Email belum berisi @ yang valid.</p>
```

Nilai: `true`, `false`, kadang `grammar` / `spelling`. Jangan `true` sejak halaman load kosong.

`:invalid` CSS bisa merah sebelum pengguna menyentuh. Lebih sopan set `aria-invalid` setelah submit / blur.

### `aria-required`

**Untuk apa:** menandai wajib jika kamu **tidak** memakai `required` native. Jika sudah `required`, biasanya tidak perlu dobel.

Tanda bintang visual `*` bukan nama. Tulis “(wajib)” atau andalkan `required` + teks di legend.

**Biasanya digabungkan dengan:** Laravel `@error`, React state error, jangan warna merah saja.

## `aria-disabled` vs `disabled`

`disabled` native: tidak fokus, tidak terkirim, gaya pucat.

`aria-disabled="true"`: **masih bisa fokus**, kamu harus menahan aktivasi di JS. Dipakai jika kamu ingin pengguna menemukan tombol mati dan mendengar alasannya.

```html
<button type="submit" disabled>Kirim (isi form dulu)</button>
```

Untuk tugas, `disabled` native hampir selalu cukup.

Jangan `pointer-events: none` pada tautan sebagai satu-satunya “disable”. Keyboard masih bisa mengaktifkannya.

**Biasanya digabungkan dengan:** state loading `disabled` + teks “Mengirim…”.

## `role` yang aman dan yang berbahaya

**Untuk apa:** menimpa peran native. Mahal. Salah = rusak.

### Yang kadang sah

| `role` | Untuk apa | Syarat |
| --- | --- | --- |
| `status` / `alert` | pengumuman | teks berubah, tidak fokus paksa kecuali alert mendesak |
| `dialog` / `alertdialog` | modal | fokus, tutup Escape, `aria-modal`, label |
| `switch` | sakelar on/off | keyboard, `aria-checked` |
| `tab` / `tablist` / `tabpanel` | tab | panah, `aria-selected`, hubungan |
| `listbox` / `option` | daftar kustom | panah, `aria-activedescendant` atau tabindex |
| `img` pada SVG | grafik bermakna | `aria-label` / `title` |
| `presentation` / `none` | buang makna | misalnya `alt=""` sudah cukup untuk img |

### Yang biasanya salah di tugas

```html
<!-- Jangan -->
<div role="button">Kirim</div>
<h2 role="banner">Judul</h2>
<ul role="navigation">...</ul>
<!-- nav sudah landmark; ul role=navigation aneh -->
<table role="presentation">...data harga...</table>
<!-- jangan buang semantik tabel jika itu data -->
```

Jika kamu menulis `role="button"`, kamu harus meniru seluruh tombol. Pakai `<button>`.

**Biasanya digabungkan dengan:** desain sistem yang terpaksa custom widget. Untuk kuliah: native dulu.

## Landmark

Sudah di bab 05. Ringkas ARIA:

```html
<header><!-- banner --></header>
<nav aria-label="Utama"></nav>
<main></main>
<aside aria-label="Tips cuaca"></aside>
<footer><!-- contentinfo --></footer>
```

`role="banner"` pada `header` situs tidak perlu — sudah implisit. Dobel role membingungkan.

`role="main"` pada `div` hanya jika kamu **tidak** bisa memakai `<main>` (template kuno).

Beri nama jika landmark sejenis lebih dari satu.

**Biasanya digabungkan dengan:** skip link, rotor VoiceOver.

## Gambar, ikon, dan SVG

| Situasi | Pola |
| --- | --- |
| Foto bermakna | `<img alt="deskripsi jujur">` |
| Dekorasi | `alt=""` atau CSS background |
| Ikon di tombol berteks | `aria-hidden="true"` pada ikon |
| Ikon sendirian | `aria-label` pada tombol / `alt` pada img |
| SVG bermakna | `<svg role="img" aria-label="...">` atau `<title>` di SVG |
| SVG dekoratif | `aria-hidden="true"` + `focusable="false"` |

```html
<svg role="img" aria-labelledby="judul-svg" width="24" height="24">
  <title id="judul-svg">Peringatan cuaca</title>
  ...
</svg>
```

Jangan `alt=" "` (spasi) sebagai trik. `alt=""`.

**Biasanya digabungkan dengan:** bab 03, komponen ikon React.

## Warna dan gerak

Jangan andalkan warna saja:

```html
<!-- Lemah: hanya titik merah -->
<span class="titik-merah"></span>

<!-- Lebih baik -->
<span class="lencana lencana-habis">Habis</span>
```

Kontras teks vs latar: target kasar WCAG AA 4.5:1 untuk teks biasa, 3:1 untuk teks besar dan UI. Tailwind `text-slate-300` di `bg-white` sering gagal.

Gerak:

```html
<video autoplay muted loop playsinline></video>
```

Hormati:

```css
@media (prefers-reduced-motion: reduce) {
  * {
    animation: none !important;
    transition: none !important;
  }
}
```

Jangan autoplay bersuara. Jangan carousel cepat tanpa tombol jeda.

**Biasanya digabungkan dengan:** CSS bab warna, desain token, uji di DevTools contrast.

## Dialog dan fokus terperangkap

Pola modern:

```html
<button type="button" id="buka">Baca syarat</button>
<dialog id="syarat" aria-labelledby="judul-syarat">
  <h2 id="judul-syarat">Syarat trip</h2>
  <p>...</p>
  <button type="button" id="tutup">Tutup</button>
</dialog>
```

```js
const d = document.getElementById("syarat");
document.getElementById("buka").onclick = () => d.showModal();
document.getElementById("tutup").onclick = () => d.close();
```

`<dialog>` + `showModal()` menangani overlay, fokus, dan Escape di browser modern. Latar bisa `inert` otomatis.

Jika `div role="dialog"`:

- `aria-modal="true"`
- `aria-labelledby`
- pindahkan fokus ke dialog saat buka
- kembalikan fokus ke tombol pemicu saat tutup
- Tab berputar di dalam
- Escape menutup

Itu banyak pekerjaan. Pakai `<dialog>` jika diizinkan.

**Biasanya digabungkan dengan:** `hidden` / `open`, React `ref` + `showModal()`, jangan `alert()` untuk syarat panjang.

## Tabel dan heading

- Satu `h1` halaman, tingkat tidak meloncat (bab 02).
- `th` + `scope` (bab 04).
- Jangan tabel layout.
- Jangan `div` ber-heading-visual tanpa tag heading jika itu awal bagian.

Daftar isi di halaman panjang adalah `nav` + tautan ke `id` heading.

**Biasanya digabungkan dengan:** bab 02 dan 04.

## Pengujian singkat tanpa alat mahal

1. Cabut mouse. Tab seluruh halaman. Apakah urutannya masuk akal? Fokus kelihatan?
2. Enter/Space pada tombol dan tautan.
3. Perbesar 200%. Teks tidak terpotong parah?
4. Matikan gambar. `alt` masih menjelaskan?
5. Matikan CSS sejenak. Urutan baca masih masuk akal?
6. Inspector aksesibilitas di DevTools: nama, peran, nilai.
7. Jika ada NVDA/VoiceOver: rotor heading, landmark, form.

Tidak perlu sempurna WCAG AAA untuk tugas. Yang sering dinilai: `lang`, `alt`, `label`, tombol asli, fokus, satu `h1`, landmark dasar.

**Biasanya digabungkan dengan:** Lighthouse (petunjuk, bukan hakim tunggal), axe DevTools.

## Kesalahan aksesibilitas yang sering muncul

1. **`div` + `onclick` sebagai tombol.**
2. **`outline: none` tanpa pengganti.**
3. **Gambar tanpa `alt`.**
4. **Input tanpa `label`.**
5. **Dua `nav` tanpa nama.**
6. **`aria-label` menduplikasi teks** atau dusta.
7. **`aria-hidden` pada induk yang berisi fokus.**
8. **`aria-expanded` tidak di-update.**
9. **Warna saja untuk error / stok.**
10. **Iframe tanpa `title`.**
11. **`target="_blank"` tanpa peringatan** (tambahan, bukan selalu gagal).
12. **Menambah `role` pada elemen yang sudah benar** sampai makna dobel/rusak.

Latihan: ambil form bab 06, tambahkan `aria-describedby` untuk bantuan dan error, skip link, `aria-current` di nav, dan tombol menu dengan `aria-expanded`. Uji dengan Tab saja.
