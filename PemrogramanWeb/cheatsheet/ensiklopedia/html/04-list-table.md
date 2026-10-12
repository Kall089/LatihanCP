# 04 · Daftar dan tabel

[← Tautan dan media](03-tautan-gambar-media.md) · [Daftar](README.md) · [Semantik →](05-semantik-sectioning.md)

**Untuk apa file ini:** menata item berulang dan data berkolom. Daftar untuk urutan atau kumpulan. Tabel untuk sel yang punya hubungan baris–kolom. Bukan untuk merapikan navbar.

## Daftar isi

- [`<ul>`](#ul)
- [`<ol>`](#ol)
- [`<li>`](#li)
- [Atribut `type`, `start`, `reversed`, `value`](#atribut-type-start-reversed-value)
- [Daftar bersarang](#daftar-bersarang)
- [`<dl>`, `<dt>`, `<dd>`](#dl-dt-dd)
- [`<menu>`](#menu)
- [`<table>`](#table)
- [`<caption>`](#caption)
- [`<thead>`, `<tbody>`, `<tfoot>`](#thead-tbody-tfoot)
- [`<tr>`](#tr)
- [`<th>`](#th)
- [`<td>`](#td)
- [`colspan` dan `rowspan`](#colspan-dan-rowspan)
- [`scope` dan `headers`](#scope-dan-headers)
- [`<colgroup>` dan `<col>`](#colgroup-dan-col)
- [Tabel yang ramah HP](#tabel-yang-ramah-hp)
- [Kapan daftar, kapan tabel, kapan kartu](#kapan-daftar-kapan-tabel-kapan-kartu)
- [Kesalahan daftar dan tabel](#kesalahan-daftar-dan-tabel)

## `<ul>`

**Untuk apa:** daftar **tidak berurut**. Urutan item tidak mengubah makna. Contoh: bekal, kelebihan paket, menu yang urutannya tidak wajib.

```html
<h2>Yang perlu dibawa</h2>
<ul>
  <li>Sunblock tahan air</li>
  <li>Uang tunai pecahan kecil</li>
  <li>KTP atau paspor</li>
</ul>
```

Anak langsung yang sah: `<li>` (plus `<script>` / `<template>`). Jangan menaruh `<p>` langsung di dalam `<ul>`.

```html
<!-- Salah -->
<ul>
  <p>Bekal</p>
  <li>Sunblock</li>
</ul>
```

Tampilan bullet diatur CSS, bukan dengan mengetik `-` di paragraf.

```css
ul {
  padding-inline-start: 1.25rem;
}

ul.polos {
  list-style: none;
  padding-inline-start: 0;
}
```

Jika kamu menghapus bullet untuk navbar, **tetap pakai `<ul>`/`<li>`**. Makna daftar tetap ada; hanya gayanya yang hilang.

**Biasanya digabungkan dengan:** CSS `list-style`, Flexbox untuk navbar, React `{items.map(item => <li key={item.id}>{item.nama}</li>)}`. Jangan lupa `key`.

## `<ol>`

**Untuk apa:** daftar **berurut**. Urutan bermakna: langkah, peringkat, itinerary hari.

```html
<h2>Urutan perjalanan</h2>
<ol>
  <li>Pesawat ke Sorong</li>
  <li>Kapal cepat ke Waisai</li>
  <li>Perahu ke dermaga penginapan</li>
</ol>
```

Jika kamu mengacak item dan maknanya rusak, itu `ol`. Jika tidak, itu `ul`.

Anak langsung: `<li>`, sama seperti `ul`.

**Biasanya digabungkan dengan:** langkah resep, ranking, CSS `list-style-type: decimal` (default), atribut `start` jika potongan daftar bersambung.

## `<li>`

**Untuk apa:** satu item di dalam `ul`, `ol`, atau `menu`.

```html
<ul>
  <li>Sunblock</li>
  <li>
    Uang tunai
    <ul>
      <li>Rupiah pecahan kecil</li>
      <li>Cadangan dolar hanya jika diminta operator</li>
    </ul>
  </li>
</ul>
```

Isi `li` boleh teks, paragraf, atau daftar bersarang. Jangan meletakkan `li` di luar `ul`/`ol`/`menu`.

Satu ide per item. Jika item berisi dua langkah yang berurutan, pecah atau ubah jadi `ol` dalam.

**Biasanya digabungkan dengan:** `key` di React, `class` untuk item aktif (`aria-current` di bab 08), CSS `::marker`.

## Atribut `type`, `start`, `reversed`, `value`

### `type` pada `ol` (dan historis pada `ul`)

**Untuk apa:** bentuk penanda. Lebih rapi diatur CSS `list-style-type`, tetapi atribut `type` pada `ol` masih sah.

```html
<ol type="1">
  <li>Desimal (default)</li>
</ol>
<ol type="a">
  <li>huruf kecil</li>
</ol>
<ol type="A">
  <li>huruf besar</li>
</ol>
<ol type="i">
  <li>romawi kecil</li>
</ol>
<ol type="I">
  <li>romawi besar</li>
</ol>
```

```css
ol.romawi {
  list-style-type: lower-roman;
}
ul.kosong {
  list-style-type: none;
}
```

`type` pada `ul` (`disc`, `circle`, `square`) usang. Pakai CSS.

### `start` pada `ol`

**Untuk apa:** nomor awal jika daftar adalah kelanjutan.

```html
<p>Lanjutan dari halaman sebelumnya:</p>
<ol start="4">
  <li>Snorkeling Arborek</li>
  <li>Kembali ke Waisai</li>
</ol>
```

### `reversed` pada `ol`

**Untuk apa:** menghitung mundur (10, 9, 8, …).

```html
<ol reversed>
  <li>Penutup: evaluasi</li>
  <li>Praktik</li>
  <li>Pengantar</li>
</ol>
```

### `value` pada `li` di dalam `ol`

**Untuk apa:** memaksa nomor item ini. Item berikutnya menyambung dari nilai itu.

```html
<ol>
  <li>Pendaftaran</li>
  <li value="5">Pengumuman (nomor 2–4 disembunyikan)</li>
  <li>Keberangkatan</li>
</ol>
```

Pakai hemat. Daftar yang nomornya meloncat membingungkan kecuali ada alasan (soal ujian nomor 5, dst).

**Biasanya digabungkan dengan:** dokumen hukum, kunci jawaban, CSS counter jika penanda sangat kustom. React: `start={halaman * 10 + 1}`.

## Daftar bersarang

**Untuk apa:** subitem. Daftar dalam harus di dalam `li`, bukan saudara `li`.

```html
<ul>
  <li>
    Dokumen
    <ul>
      <li>KTP</li>
      <li>Kartu vaksin jika diminta operator</li>
    </ul>
  </li>
  <li>
    Di perahu
    <ol>
      <li>Rompi</li>
      <li>Sunblock</li>
      <li>Air minum</li>
    </ol>
  </li>
</ul>
```

```html
<!-- Salah: ul jadi anak langsung ul -->
<ul>
  <ul>
    <li>KTP</li>
  </ul>
</ul>
```

Campur `ul` dan `ol` boleh jika makna benar: kelompok tidak berurut yang berisi langkah berurut.

**Biasanya digabungkan dengan:** CSS indent, menu dropdown (tetap daftar bersarang), hindari 4+ tingkat — pengguna tersesat.

## `<dl>`, `<dt>`, `<dd>`

**Untuk apa:** daftar **istilah → penjelasan**. FAQ, metadata, kamus singkat, spek produk.

```html
<h2>Istilah trip</h2>
<dl>
  <dt>Liveaboard</dt>
  <dd>Kapal yang sekaligus tempat tidur selama trip.</dd>

  <dt>Open trip</dt>
  <dd>Trip bersama peserta lain, bukan charter eksklusif.</dd>

  <dt>Tiket kawasan</dt>
  <dd>Biaya resmi masuk kawasan, terpisah dari paket operator.</dd>
</dl>
```

### `<dt>`

**Untuk apa:** istilah / nama / pertanyaan.

### `<dd>`

**Untuk apa:** definisi / nilai / jawaban.

Boleh beberapa `dt` berbagi `dd`, atau satu `dt` punya beberapa `dd`:

```html
<dl>
  <dt>PNG</dt>
  <dt>Portable Network Graphics</dt>
  <dd>Format gambar lossless yang sering dipakai untuk UI.</dd>
</dl>

<dl>
  <dt>Waisai</dt>
  <dd>Ibukota Kabupaten Raja Ampat.</dd>
  <dd>Titik tiba kapal cepat dari Sorong.</dd>
</dl>
```

Jangan memakai `dl` untuk merapikan form. Form punya `label`. Jangan memakai `dl` sebagai grid harga jika hubungan baris-kolom rumit — itu tabel.

CSS default menjorokkan `dd`. Boleh diubah jadi grid:

```css
dl.spek {
  display: grid;
  grid-template-columns: 10rem 1fr;
  gap: 0.5rem 1rem;
}

dl.spek dt {
  font-weight: 600;
}

dl.spek dd {
  margin-inline-start: 0;
}
```

**Biasanya digabungkan dengan:** halaman FAQ, spek di kartu produk, CSS Grid. Di React, map pasangan `{istilah, penjelasan}`.

## `<menu>`

**Untuk apa:** daftar perintah / aksi, secara semantik dekat dengan `ul`. Di HTML modern, `menu` di-render seperti daftar. Bukan “menu klik kanan native” secara ajaib.

```html
<menu>
  <li><button type="button">Edit</button></li>
  <li><button type="button">Hapus</button></li>
</menu>
```

Untuk navbar situs, `<nav><ul>` lebih umum dan lebih mudah dipahami dosen/pembaca. `menu` boleh jika kamu memang menandai sekelompok perintah.

**Biasanya digabungkan dengan:** toolbar, `button`, CSS `list-style: none; display: flex`. Dukungan makna “context menu” historis tidak perlu dikejar.

## `<table>`

**Untuk apa:** data **tabular**: sel yang dibaca menurut baris dan kolom. Jadwal, harga vs item, perbandingan fitur.

```html
<table>
  <caption>Harga paket 2026</caption>
  <thead>
    <tr>
      <th scope="col">Paket</th>
      <th scope="col">Durasi</th>
      <th scope="col">Harga</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th scope="row">Pianemo cepat</th>
      <td>1 hari</td>
      <td>Rp 1.500.000</td>
    </tr>
    <tr>
      <th scope="row">Jelajah 4 hari</th>
      <td>4 hari</td>
      <td>Rp 8.500.000</td>
    </tr>
  </tbody>
</table>
```

Bukan untuk:

- menyusun seluruh halaman jadi kolom (itu Grid/Flexbox)
- merapikan form jadi dua kolom
- menaruh navbar di sel

Tabel layout merusak urutan baca di HP dan pembaca layar.

**Biasanya digabungkan dengan:** CSS `border-collapse`, `width: 100%`, wrapper `overflow-x: auto`, Laravel `@foreach` baris, React map baris dengan `key`.

## `<caption>`

**Untuk apa:** judul tabel. Harus anak pertama `table`.

```html
<table>
  <caption>Jadwal kapal cepat Sorong–Waisai (ilustrasi)</caption>
  ...
</table>
```

Bukan `<h2>` di luar yang tidak terhubung. `caption` mengikat judul ke tabel untuk pembaca layar.

Boleh berisi teks dan inline. Gaya:

```css
caption {
  text-align: start;
  font-weight: 600;
  margin-block-end: 0.5rem;
}
```

Jika tabel di dalam `figure`, pilihan: `caption` atau `figcaption` — jangan dobel judul yang sama.

**Biasanya digabungkan dengan:** semua tabel data. Tugas yang dinilai semantik sering mencari `caption` atau heading yang jelas.

## `<thead>`, `<tbody>`, `<tfoot>`

**Untuk apa:** membagi baris menjadi kepala, badan, dan kaki.

```html
<table>
  <caption>Rekap biaya (ilustrasi)</caption>
  <thead>
    <tr>
      <th scope="col">Item</th>
      <th scope="col">Jumlah</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Paket</td>
      <td>Rp 8.500.000</td>
    </tr>
    <tr>
      <td>Tiket kawasan</td>
      <td>Rp 500.000</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th scope="row">Total</th>
      <td>Rp 9.000.000</td>
    </tr>
  </tfoot>
</table>
```

### `<thead>`

**Untuk apa:** baris judul kolom. Bisa di-`position: sticky` saat body di-scroll.

### `<tbody>`

**Untuk apa:** data. Boleh lebih dari satu `tbody` untuk kelompok baris.

### `<tfoot>`

**Untuk apa:** ringkasan / total. Boleh ditulis setelah `thead` sebelum `tbody` (HTML mengizinkan) atau di akhir; browser menaruhnya secara konsisten. Untuk manusia yang membaca kode, di akhir lebih jujur.

Tidak wajib untuk tabel 2×2 sederhana, tetapi `thead` + `tbody` adalah kebiasaan baik begitu ada judul kolom.

**Biasanya digabungkan dengan:** CSS `thead th { position: sticky; top: 0; }`, print stylesheet, Laravel total di kaki tabel.

## `<tr>`

**Untuk apa:** satu baris.

```html
<tr>
  <th scope="row">Pianemo cepat</th>
  <td>1 hari</td>
  <td>Rp 1.500.000</td>
</tr>
```

Anak `tr`: `th` dan `td`. Jangan menaruh `div` sebagai anak langsung `tr`.

Urutan sel di setiap baris harus selaras dengan judul kolom. Jangan “melompat sel” dengan CSS saja tanpa `colspan`.

**Biasanya digabungkan dengan:** `:nth-child` untuk zebra, `tr:hover` untuk tabel padat, React `key` pada `tr`.

## `<th>`

**Untuk apa:** sel **judul**. Bisa judul kolom atau judul baris.

```html
<thead>
  <tr>
    <th scope="col">Paket</th>
    <th scope="col">Harga</th>
  </tr>
</thead>
<tbody>
  <tr>
    <th scope="row">Jelajah 4 hari</th>
    <td>Rp 8.500.000</td>
  </tr>
</tbody>
```

Default biasanya tebal dan tengah. Ubah CSS, tetapi jangan ganti semua `th` jadi `td` + `font-weight`. Pembaca layar memakai `th` untuk mengumumkan “Harga, Rp 8.500.000”.

### Atribut khusus `th`

| Atribut | Untuk apa |
| --- | --- |
| `scope` | `col`, `row`, `colgroup`, `rowgroup` |
| `colspan` / `rowspan` | gabung sel |
| `abbr` | bentuk pendek untuk pembaca layar |
| `headers` | id `th` terkait (tabel rumit) |

```html
<th scope="col" abbr="Durasi">Durasi trip (hari)</th>
```

**Biasanya digabungkan dengan:** `scope`, CSS `text-align: start` agar judul tidak selalu center, sticky header.

## `<td>`

**Untuk apa:** sel data.

```html
<td>Rp 8.500.000</td>
<td>4 hari</td>
<td>
  <a href="paket-4-hari.html">Detail</a>
</td>
```

Boleh berisi teks, tautan, tombol, form kecil, daftar. Jika seluruh tabel berisi kartu rumit, mungkin kamu butuh daftar kartu, bukan tabel.

Atribut: `colspan`, `rowspan`, `headers`. Atribut usang `align`, `valign`, `bgcolor`, `width` — pindah ke CSS.

**Biasanya digabungkan dengan:** `text-align: end` untuk angka, `font-variant-numeric: tabular-nums` agar digit rapi, format rupiah dari Laravel `Number::currency`.

## `colspan` dan `rowspan`

**Untuk apa:** menggabungkan sel secara horizontal atau vertikal.

```html
<table>
  <caption>Kalender trip Oktober</caption>
  <thead>
    <tr>
      <th scope="col">Minggu</th>
      <th scope="col">Kegiatan</th>
      <th scope="col">Keterangan</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th scope="row">1–2</th>
      <td colspan="2">Tidak ada open trip (cuaca)</td>
    </tr>
    <tr>
      <th scope="row">3</th>
      <td rowspan="2">Liveaboard 4 hari</td>
      <td>Berangkat Senin</td>
    </tr>
    <tr>
      <th scope="row">4</th>
      <td>Berangkat Kamis</td>
    </tr>
  </tbody>
</table>
```

Hitung jumlah kolom setiap baris. Jika header 3 kolom, setiap baris harus menutupi 3 slot, termasuk yang diisi `colspan`/`rowspan`. Salah hitung = tabel “bolong” atau sel bergeser.

Jangan menggabungkan berlebihan sampai makna sel hilang. Pembaca layar lebih sulit menelusuri tabel yang banyak merge.

**Biasanya digabungkan dengan:** jadwal, `text-align: center` pada sel gabungan, uji dengan keyboard (panah di beberapa AT).

## `scope` dan `headers`

### `scope`

**Untuk apa:** menyatakan apakah `th` menjuduli kolom atau baris.

| Nilai | Untuk apa |
| --- | --- |
| `col` | judul untuk kolom di bawahnya |
| `row` | judul untuk baris di kanannya (LTR) |
| `colgroup` | judul untuk kelompok kolom |
| `rowgroup` | judul untuk kelompok baris (`tbody`) |

```html
<th scope="col">Harga</th>
<th scope="row">Jelajah 4 hari</th>
```

Untuk tabel sederhana satu baris header, banyak pembaca layar sudah menebak. `scope` tetap murah dan jelas.

### `headers`

**Untuk apa:** pada `td`/`th` rumit, menunjuk `id` judul terkait (bisa lebih dari satu, dipisah spasi).

```html
<table>
  <caption>Harga musim</caption>
  <thead>
    <tr>
      <td></td>
      <th id="puncak" scope="col">Musim puncak</th>
      <th id="tenang" scope="col">Musim tenang</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th id="paket4" scope="row">4 hari</th>
      <td headers="paket4 puncak">Rp 9.800.000</td>
      <td headers="paket4 tenang">Rp 8.500.000</td>
    </tr>
  </tbody>
</table>
```

Pakai jika merge sel membuat hubungan tidak linier. Untuk tabel tugas biasa, `scope` cukup.

**Biasanya digabungkan dengan:** laporan yang dinilai aksesibilitas, jangan ditambah jika tabel sudah sederhana — atribut salah lebih merusak.

## `<colgroup>` dan `<col>`

**Untuk apa:** menandai kolom agar CSS/`span` bisa diterapkan tanpa mengulang class di setiap sel.

```html
<table>
  <caption>Perbandingan paket</caption>
  <colgroup>
    <col />
    <col class="col-unggulan" span="1" />
    <col />
  </colgroup>
  <thead>
    <tr>
      <th scope="col">Fitur</th>
      <th scope="col">4 hari</th>
      <th scope="col">7 hari</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th scope="row">Liveaboard</th>
      <td>Tidak</td>
      <td>Ya</td>
    </tr>
  </tbody>
</table>
```

```css
col.col-unggulan {
  background: #f8fafc;
}
```

### Atribut `span` pada `col` / `colgroup`

**Untuk apa:** kolom ini mewakili n kolom.

Dukungan styling pada `col` terbatas (background dan width relatif aman; padding pada `col` tidak). Jangan mengandalkan `col` untuk semua gaya.

**Biasanya digabungkan dengan:** tabel lebar, highlight kolom “rekomendasi”. Opsional di tugas kecil.

## Tabel yang ramah HP

Tabel 6 kolom meledak di layar 320px. Pilihan jujur:

1. **Scroll horizontal** pada pembungkus, header tetap.
2. **Kartu** di HP, tabel di desktop (`display` diubah hati-hati — semantik tabel bisa rusak jika kamu mengubah `display: block` pada `tr`).
3. **Sembunyikan kolom sekunder** di HP dengan class, sediakan detail.

Pola paling aman untuk tugas:

```html
<div class="tabel-bungkus">
  <table>
    ...
  </table>
</div>
```

```css
.tabel-bungkus {
  overflow-x: auto;
  max-width: 100%;
}

table {
  border-collapse: collapse;
  min-width: 36rem;
  width: 100%;
}

th,
td {
  border: 1px solid #cbd5e1;
  padding: 0.5rem 0.75rem;
  text-align: start;
}

th {
  background: #f1f5f9;
}
```

Jangan memutar setiap `td` jadi `display: block` tanpa menguji pembaca layar.

**Biasanya digabungkan dengan:** media query, Tailwind `overflow-x-auto`, caption yang menjelaskan “geser ke samping untuk kolom lain”.

## Kapan daftar, kapan tabel, kapan kartu

| Data | Pakai | Alasan |
| --- | --- | --- |
| Bekal, menu, tag | `ul` | kumpulan |
| Langkah, ranking | `ol` | urutan bermakna |
| Istilah–definisi, FAQ | `dl` | pasangan nama-nilai |
| Harga vs durasi vs kuota | `table` | banding antar kolom |
| Produk dengan foto + tombol | kartu (`article` + isi) | bukan sel |
| Navbar | `nav` + `ul` | bukan tabel 1 baris |
| Layout 2 kolom halaman | Grid/Flex | bukan tabel |

Tes cepat: “Apakah sel ini hanya masuk akal karena kolomnya ‘Harga’ dan barisnya ‘Paket 4 hari’?” Jika ya, tabel. Jika setiap item adalah cerita sendiri, kartu atau daftar.

## Kesalahan daftar dan tabel

1. **Tabel untuk layout navbar / seluruh page.**
2. **`<ul>` berisi `<div>` tanpa `<li>`.**
3. **Daftar bersarang diletakkan sebagai anak `ul`, bukan di dalam `li`.**
4. **`ol` untuk item yang urutannya tidak penting**, atau sebaliknya.
5. **Semua sel `td`, termasuk judul kolom.** Pakai `th`.
6. **Tidak ada `caption` / heading** sehingga tabel “tiba-tiba ada”.
7. **`colspan` salah hitung** sampai kolom bergeser.
8. **Harga di `<p>` berjejer** yang sebenarnya tabel perbandingan.
9. **`list-style: none` pada navbar lalu item bukan `li`.** Tetap `ul > li`.
10. **Mengubah `table` jadi `display: block` di HP** tanpa uji aksesibilitas.

Latihan: ubah daftar harga “Paket A Rp … / Paket B Rp …” yang ditulis paragraf menjadi `table` ber-`caption` dan `th`, lalu buat versi `ul` kartu untuk HP jika kolomnya lebih dari empat.
