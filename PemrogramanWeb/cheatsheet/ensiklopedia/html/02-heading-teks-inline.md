# 02 · Heading dan teks inline

[← Kerangka](01-kerangka-doctype-meta.md) · [Daftar](README.md) · [Tautan dan media →](03-tautan-gambar-media.md)

**Untuk apa file ini:** menyusun bacaan. Heading membentuk kerangka, paragraf menampung kalimat, tag inline menandai makna di dalam kalimat. Ukuran huruf diatur CSS, bukan dengan meloncat dari `h1` ke `h5`.

## Daftar isi

- [Heading `h1`–`h6`](#heading-h1h6)
- [`<p>`](#p)
- [`<br>`](#br)
- [`<hr>`](#hr)
- [`<strong>`](#strong)
- [`<em>`](#em)
- [`<mark>`](#mark)
- [`<small>`](#small)
- [`<sub>`](#sub)
- [`<sup>`](#sup)
- [`<span>`](#span)
- [`<b>`](#b)
- [`<i>`](#i)
- [`<u>`](#u)
- [`<s>`](#s)
- [`<code>`](#code)
- [`<pre>`](#pre)
- [`<blockquote>`](#blockquote)
- [`<q>`](#q)
- [`<abbr>`](#abbr)
- [`<time>`](#time)
- [`<wbr>`](#wbr)
- [Tag teks tetangga yang sering ketemu](#tag-teks-tetangga-yang-sering-ketemu)
- [Mana yang semantik, mana yang hanya tampilan](#mana-yang-semantik-mana-yang-hanya-tampilan)
- [Kesalahan teks yang sering muncul](#kesalahan-teks-yang-sering-muncul)

## Heading `h1`–`h6`

**Untuk apa:** menandai judul dan subjudul menurut tingkat, bukan menurut ketebalan. Pembaca layar memakai heading untuk loncat bagian. Mesin pencari memakai heading untuk memahami topik.

```html
<h1>Jelajah Raja Ampat</h1>
<h2>Cara menuju Waisai</h2>
<h3>Dari bandara Domine Eduard Osok</h3>
<h4>Jemputan kapal cepat</h4>
<h5>Catatan musim gelombang</h5>
<h6>Catatan internal panitia</h6>
```

### `h1`

**Untuk apa:** judul utama halaman. Idealnya **satu** per halaman (atau satu per `<article>` yang mandiri).

```html
<main>
  <h1>Paket 4 hari Raja Ampat</h1>
</main>
```

Jangan memakai `h1` hanya karena “ingin huruf paling besar”. Jika yang kamu butuhkan adalah logo besar di header, itu boleh `<p>` atau `<span>` yang di-style, atau `h1` hanya jika logo itu memang judul dokumen.

### `h2`

**Untuk apa:** bagian besar di bawah `h1`. Contoh: “Itinerary”, “Harga”, “FAQ”.

```html
<h2>Itinerary</h2>
<h2>Harga</h2>
```

### `h3`

**Untuk apa:** subbagian di bawah `h2`. Contoh: “Hari 1” di bawah “Itinerary”.

```html
<h2>Itinerary</h2>
<h3>Hari 1 — Sorong ke Waisai</h3>
<h3>Hari 2 — Pianemo</h3>
```

### `h4`, `h5`, `h6`

**Untuk apa:** tingkat lebih dalam. Jarang dibutuhkan di tugas 1–2 halaman. Jika kamu sudah sampai `h6`, cek apakah struktur bisa diratakan.

Jangan loncat tingkat hanya karena ukuran default browser:

```html
<!-- Salah niat: loncat ke h4 karena h2 “terlalu besar” -->
<h1>Jelajah</h1>
<h4>Kontak</h4>

<!-- Benar: tetap h2, kecilkan dengan CSS -->
<h1>Jelajah</h1>
<h2 class="judul-bagian">Kontak</h2>
```

```css
.judul-bagian {
  font-size: 1.25rem;
}
```

Heading adalah elemen blok. Jangan membungkus heading dengan `<p>`. Boleh berisi tag inline (`<span>`, `<strong>`, `<a>`), bukan `<div>` atau heading lain.

**Biasanya digabungkan dengan:** CSS `font-size`, `font-weight`, `scroll-margin-top` jika ada navbar sticky, tautan `#id` (bab 03), outline di tugas profil. Di React, heading tetap tag yang sama: `<h1>{judul}</h1>`. Di Laravel Blade: `<h1>{{ $paket->nama }}</h1>`.

## `<p>`

**Untuk apa:** satu paragraf. Bukan wadah layout. Bukan pengganti `<div>`.

```html
<p>Raja Ampat terdiri atas ribuan pulau kecil di ujung barat laut Papua.</p>
<p>Musim paling tenang untuk perahu kecil biasanya sekitar Oktober sampai April.</p>
```

Satu ide per paragraf. Jangan menaruh seluruh artikel dalam satu `<p>` raksasa yang dipotong `<br><br>`.

Yang **tidak boleh** ada di dalam `<p>`: `<div>`, `<section>`, `<h1>`–`<h6>`, `<ul>`, `<table>`, `<p>` lain. Browser akan menutup `<p>` lebih awal, dan pohon DOM tidak seperti yang kamu tulis.

```html
<!-- Browser akan memotong p sebelum div -->
<p>Teks
  <div>Ini keluar dari paragraf</div>
</p>
```

Atribut yang relevan: atribut global (`id`, `class`, `lang`). Tidak ada atribut khusus `p`.

**Biasanya digabungkan dengan:** CSS `max-width` 60–70 karakter agar enak dibaca, `line-height: 1.6`, `margin-block`. Di React, `{paragraf.map(...)}` menghasilkan banyak `<p>`. Di Blade, `{!! nl2br(e($teks)) !!}` kadang dipakai — lebih rapi pecah ke array paragraf.

## `<br>`

**Untuk apa:** **putus baris sadar**, bukan “spasi vertikal”. Elemen void, tidak ada `</br>`.

```html
<p>
  Jl. Yos Sudarso<br />
  Sorong, Papua Barat Daya
</p>

<p>Puisi atau lirik:<br />
baris dua<br />
baris tiga</p>
```

Bukan untuk menjauhkan dua bagian halaman:

```html
<!-- Salah -->
<h2>Harga</h2>
<br /><br /><br />
<p>Rp 8.500.000</p>
```

Jarak itu tugas CSS `margin` / `gap`. Tiga `<br>` beruntun adalah tanda layout dipaksa.

Jangan memakai `<br>` di dalam elemen yang seharusnya daftar. Jika ada tiga baris alamat yang berulang di banyak halaman, pertimbangkan `<address>` (bab 05) atau satu `<p>` dengan `<br>`.

**Biasanya digabungkan dengan:** alamat, bait lagu, pecahan nama di kartu nama. Bukan dengan Flexbox. Di React tulis `<br />`. Di Blade, `nl2br` menghasilkan `<br>` dari enter pengguna — sanitasi dulu.

## `<hr>`

**Untuk apa:** **pemisah tematik** di antara topik, bukan garis dekoratif semata. Elemen void.

```html
<p>Paket 4 hari mencakup kapal dan makan siang di laut.</p>
<hr />
<p>Paket 7 hari menambah Wayag dan malam di liveaboard.</p>
```

Makna: “topik berganti, tapi masih satu dokumen”. Kalau kamu hanya ingin garis di bawah judul, pakai CSS `border-bottom` pada elemen itu.

```css
hr {
  border: 0;
  border-block-start: 1px solid #cbd5e1;
  margin-block: 2rem;
}
```

Atribut lama `width`, `align`, `color`, `noshade` sudah usang. Atur tampilan di CSS.

**Biasanya digabungkan dengan:** CSS border, kadang `role` tidak perlu karena `hr` sudah punya makna. Di desain kartu, banyak orang memakai `<div class="garis">` — `hr` lebih jujur jika memang memisahkan topik.

## `<strong>`

**Untuk apa:** menandai teks yang **penting / mendesak**, bukan sekadar tebal.

```html
<p>
  <strong>Perhatian:</strong> jangan menyentuh karang. Denda kawasan bisa dikenakan.
</p>
```

Pembaca layar bisa mengubah intonasi. Mesin pencari tidak ajaib hanya karena ada `strong`, tapi makna tetap lebih jujur daripada `<b>` atau `<span class="tebal">`.

Jangan membungkus seluruh paragraf. Jika semua penting, tidak ada yang penting.

**Biasanya digabungkan dengan:** CSS `font-weight` (default sudah lebih tebal), peringatan form, badge “Wajib”. Di React tetap `<strong>`. Jangan mengganti dengan `<b>` hanya karena namanya lebih pendek.

## `<em>`

**Untuk apa:** **penekanan** yang mengubah makna kalimat, biasanya miring.

```html
<p>Kapal berangkat <em>hanya</em> jika cuaca memungkinkan.</p>
<p>Bukan “bisa berangkat”, melainkan <em>wajib konfirmasi malam sebelumnya</em>.</p>
```

Bandingkan:

| Tag | Makna | Tampilan default |
| --- | --- | --- |
| `em` | penekanan | miring |
| `i` | suara/istilah berbeda, tanpa penekanan | miring |
| `strong` | penting | tebal |
| `b` | perhatian visual tanpa urgensi | tebal |

```html
<!-- em: jika diucapkan, kata ini ditonjolkan -->
<p>Saya <em>tidak</em> menyarankan snorkeling mandiri di kanal itu.</p>

<!-- i: nama ilmiah / istilah, bukan penekanan -->
<p>Ikan <i lang="la">Pterois volitans</i> adalah spesies invasif di beberapa wilayah.</p>
```

**Biasanya digabungkan dengan:** CSS `font-style`, `lang` pada istilah asing. Di UI, tombol “penting” tetap `<strong>` atau teks biasa + warna, bukan `<em>` di seluruh navbar.

## `<mark>`

**Untuk apa:** menandai teks sebagai **sorotan / hasil pencarian / highlight**, seolah spidol kuning.

```html
<p>Hasil cari “Pianemo”: pulau berbentuk <mark>tumpukan karst</mark> yang sering difoto dari puncak.</p>
```

Bukan untuk “peringatan penting” (`strong`) dan bukan untuk “sudah tidak berlaku” (`s`).

Tampilan default kuning kehijauan. Ganti lewat CSS:

```css
mark {
  background: #fde68a;
  color: inherit;
}
```

**Biasanya digabungkan dengan:** JavaScript pencarian yang membungkus kecocokan dengan `<mark>`, React saat merender cuplikan hasil `filter`. Jangan hardcode `<mark>` hanya karena ingin latar kuning — itu tugas `background` pada `span` jika tidak ada makna highlight.

## `<small>`

**Untuk apa:** **catatan samping yang lebih rendah kepentingannya**: disclaimer, hak cipta, keterangan legal singkat. Bukan “buat huruf kecil karena cantik”.

```html
<p>Harga mulai Rp 8.500.000.</p>
<p><small>Belum termasuk tiket pesawat ke Sorong. Berlaku hingga 31 Desember.</small></p>

<footer>
  <small>© 2026 Jelajah Raja Ampat. Peta hanya ilustrasi.</small>
</footer>
```

Ukuran default memang lebih kecil, tapi makna utamanya “keterangan turunan”. Untuk memperkecil heading, ubah `font-size` heading itu, jangan bungkus `h1` dengan `small` sebagai trik desain.

**Biasanya digabungkan dengan:** `<footer>`, teks di bawah tombol submit, copyright. CSS `font-size: 0.875rem`. Di form, pesan bantuan lebih rapi sebagai `<p class="bantuan">` yang diikat `aria-describedby` (bab 08).

## `<sub>`

**Untuk apa:** subscript: indeks kimia, matematika, catatan kaki sederhana.

```html
<p>Karbon dioksida ditulis CO<sub>2</sub>.</p>
<p>Air: H<sub>2</sub>O.</p>
```

Jangan memakai `<sub>` hanya untuk merapatkan angka ke bawah pada desain logo. Itu `vertical-align` / SVG.

**Biasanya digabungkan dengan:** teks sains, rumus sederhana. Untuk rumus rumit, MathML atau gambar ber-`alt`. CSS `vertical-align: sub; font-size: smaller` adalah default yang bisa dituning.

## `<sup>`

**Untuk apa:** superscript: pangkat, ordinal, catatan kaki.

```html
<p>Luas kira-kira 4,6 juta km<sup>2</sup> untuk kawasan laut yang sering disebut.</p>
<p>Catatan<sup><a href="#cat1">1</a></sup></p>
<p id="cat1"><small>1. Angka ilustrasi untuk tugas, bukan kutipan resmi.</small></p>
```

Jangan meniru `1st` dengan `<sup>st</sup>` jika tipografi situs tidak membutuhkan itu. Di Indonesia jarang diperlukan.

**Biasanya digabungkan dengan:** tautan catatan kaki, satuan m²/cm³, CSS yang menjaga `line-height` agar superscript tidak memotong baris atas.

## `<span>`

**Untuk apa:** wadah **tanpa makna**. Inline. Dipakai agar CSS atau JS punya target di tengah kalimat.

```html
<p>Sisa kuota: <span id="sisa-kuota" class="angka">12</span> kursi.</p>
<p>Status: <span class="lencana lencana-ok">Tersedia</span></p>
```

Jika potongan itu penting, pakai `strong`. Jika itu judul, pakai heading. Jika itu sekelompok blok, pakai `div` (bab 05).

`span` boleh bersarang. `span` tidak boleh berisi elemen blok (`div`, `p`, `ul`).

Atribut yang paling sering: `class`, `id`, `hidden`, `data-*`. Tidak ada atribut khusus `span`.

**Biasanya digabungkan dengan:** CSS badge, JS `textContent` pada `#sisa-kuota`, React `<span className="lencana">`. Ini tag yang paling sering “kebanyakan” — jika kamu bisa hapus `span` tanpa kehilangan makna dan gaya, hapus.

## `<b>`

**Untuk apa:** menarik perhatian **secara visual** tanpa mengklaim urgensi `strong`. Contoh: kata kunci di ringkasan, nama produk di kalimat, lead-in.

```html
<p><b>Pianemo.</b> Gugusan karst yang dipotret dari puncak kayu.</p>
<p>Bawa <b>uang tunai</b> karena tidak semua dermaga menerima kartu.</p>
```

Jika menghapus ketebalan tidak mengubah makna penting, `b` bisa diterima. Jika penghapusan membuat peringatan hilang, pakai `strong`.

Tutorial lama menyamakan `b` dengan “bold tag”. Di HTML modern, `b` tetap ada, tetapi `strong` lebih sering benar untuk tugas yang dinilai semantik.

**Biasanya digabungkan dengan:** CSS `font-weight`. Di desain, banyak yang langsung `span` + class. `b` berguna saat kamu tidak ingin membuat class baru untuk satu-dua kata.

## `<i>`

**Untuk apa:** teks yang **berbeda suaranya** dari sekitar: istilah teknis, nama ilmiah, judul karya dalam konteks tertentu, pikiran dalam narasi. Default miring, tetapi makna bukan “italic Cosmetics”.

```html
<p>Spesies <i lang="la">Pterois volitans</i> sering disebut lionfish.</p>
<p>Kata <i>liveaboard</i> di sini berarti kapal yang sekaligus penginapan.</p>
```

Bukan untuk ikon. Ikon Font Awesome lama memakai `<i class="fa fa-star">` — itu kebiasaan, bukan semantik. Lebih rapi `<span aria-hidden="true">` atau SVG.

Untuk penekanan makna, pakai `em`. Untuk judul karya yang dikutip sebagai sumber, lihat `<cite>` di bagian tetangga.

**Biasanya digabungkan dengan:** `lang` untuk istilah asing, CSS `font-style`. React/Laravel tidak mengubah tag ini.

## `<u>`

**Untuk apa:** anotasi yang secara historis digarisbawahi, misalnya **kesalahan ejaan yang ditandai** atau label proper name di teks khusus. **Bukan** untuk membuat tautan palsu.

```html
<p>Koreksi: tulis <u class="salah">Pulai</u> sebagai Pulau.</p>
```

Pengguna sudah dilatih: garis bawah = tautan. Menggarisbawahi harga atau judul membingungkan.

```html
<!-- Jangan -->
<p>Klik <u>di sini</u> untuk harga. (Ini bukan tautan.)</p>
```

Pakai `<a>` untuk tautan. Pakai `border-bottom` CSS jika desain butuh garis hias.

**Biasanya digabungkan dengan:** hampir tidak pernah di UI modern. Jika dosen meminta “underline”, tanyakan apakah maksudnya tautan atau `text-decoration`. Di Tailwind, `underline` adalah CSS, bukan alasan memakai tag `<u>`.

## `<s>`

**Untuk apa:** teks yang **tidak lagi akurat / sudah dicoret secara makna**. Bukan sekadar coretan dekoratif.

```html
<p>Harga <s>Rp 9.800.000</s> <strong>Rp 8.500.000</strong></p>
<p><s>Trip 12 Mei penuh.</s> Kuota dibuka lagi untuk 19 Mei.</p>
```

Ada juga `<del>` (teks yang dihapus dari dokumen, sering bersama `datetime`) dan `<ins>` (sisipan). Untuk harga diskon, `s` sudah cukup dan paling sering dipakai.

```html
<p>
  Revisi itinerary:
  <del datetime="2026-03-01">Hari 3: Wayag</del>
  <ins datetime="2026-03-02">Hari 3: Arborek</ins>
</p>
```

**Biasanya digabungkan dengan:** CSS `text-decoration: line-through`, kartu produk, React saat `hargaCoret` tidak null. Tambahkan teks “diskon” atau persentase — jangan andalkan coretan saja (aksesibilitas, bab 08).

## `<code>`

**Untuk apa:** potongan kode atau nilai yang diketik apa adanya: nama tag, perintah, path file, kode promo pendek.

```html
<p>Tulis <code>lang="id"</code> pada <code>&lt;html&gt;</code>.</p>
<p>Kode promo: <code>AMPAT20</code></p>
```

Default biasanya font monospasi. Untuk blok banyak baris, bungkus dengan `<pre>` (lihat bawah). `<code>` sendiri bersifat inline.

Jangan memakai `<code>` untuk menonjolkan kata biasa. Itu `strong` atau `b`.

**Biasanya digabungkan dengan:** CSS `font-family: ui-monospace, monospace`, `background` lembut, library syntax highlight (Prism, Shiki) di dokumentasi. Di React, isi harus di-escape. Di Blade, `{{ $cuplikan }}` aman; `{!! $html !!}` tidak otomatis aman.

## `<pre>`

**Untuk apa:** teks **praformat**: spasi dan enter dipertahankan. Cocok blok kode, ASCII, atau contoh file.

```html
<pre><code>npm create vite@latest latihan -- --template react
cd latihan
npm install
npm run dev</code></pre>
```

Tanpa `<code>` di dalam, `<pre>` tetap menjaga spasi, tetapi gabungan `pre > code` adalah pola yang benar untuk kode.

```html
<pre>
Waisai     06.00
Pianemo    09.30
Pulau kembali 16.00
</pre>
```

CSS yang sering lupa:

```css
pre {
  overflow-x: auto;
  white-space: pre;
}
```

Tanpa `overflow-x`, blok kode merusak lebar HP.

Jangan memakai `<pre>` untuk merapikan layout halaman. Spasi di HTML biasa sudah dilipat; layout adalah Flexbox/Grid.

**Biasanya digabungkan dengan:** `<code>`, CSS scroll horizontal, komponen `<pre>` di dokumen tugas. Di React, template string menjaga enter: `<pre>{`baris1\nbaris2`}</pre>`.

## `<blockquote>`

**Untuk apa:** kutipan **blok** yang diambil dari sumber lain, biasanya beberapa kalimat.

```html
<blockquote cite="https://contoh.test/laporan-terumbu">
  <p>Tutupan karang hidup di stasiun pantau A tercatat 62 persen pada survei terakhir.</p>
  <footer>— Tim pemantau, 2025</footer>
</blockquote>
```

### Atribut `cite`

**Untuk apa:** URL sumber. Tidak ditampilkan browser. Bukan pengganti teks atribusi yang kelihatan.

```html
<blockquote cite="https://contoh.test/artikel">
  <p>Jangan memberi makan ikan untuk foto.</p>
</blockquote>
```

Teks siapa yang berkata memakai `<footer>` di dalam kutipan atau `<cite>` (nama karya). Jangan memakai `blockquote` hanya untuk membuat kotak indent besar pada tips milikmu sendiri. Tips milik penulis halaman lebih jujur sebagai `<aside>` atau `<p class="tips">`.

**Biasanya digabungkan dengan:** CSS padding kiri + border, `<cite>`, artikel berita. Di Laravel, kutipan dari database tetap perlu atribusi yang kelihatan, bukan hanya URL di atribut.

## `<q>`

**Untuk apa:** kutipan **inline** pendek. Browser sering menambah tanda kutip otomatis.

```html
<p>Pemandu bilang <q lang="id">air jernihnya seperti kaca</q> saat kami di Arborek.</p>
```

### Atribut `cite`

Sama seperti `blockquote`: URL sumber, tidak tampil.

```html
<p>Menurut catatan lapangan, <q cite="https://contoh.test/catatan">arus pagi lebih jinak</q>.</p>
```

Jangan bersarang berlebihan. Untuk dialog panjang, pecah ke `blockquote` atau paragraf biasa dengan tanda kutip yang kamu tulis sendiri — lebih mudah dikontrol di CSS.

CSS:

```css
q::before,
q::after {
  /* default browser sudah menambah kutip */
}
```

Jika desain tidak ingin kutip ganda (browser + karakter yang kamu ketik), jangan ketik `"` di dalam `<q>`.

**Biasanya digabungkan dengan:** kalimat berita, `lang` jika kutipan beda bahasa. Di React, hati-hati: anak `<q>` tidak perlu tanda kutip literal.

## `<abbr>`

**Untuk apa:** singkatan atau akronim, dengan kepanjangan di `title`.

```html
<p>
  Tiket
  <abbr title="Taman Nasional">TN</abbr>
  bisa dibeli sebelum ke dermaga.
</p>
<p>
  Bawa
  <abbr title="Kartu Tanda Penduduk">KTP</abbr>
  atau paspor.
</p>
```

### Atribut `title` pada `abbr`

**Untuk apa:** kepanjangan. Muncul sebagai tooltip mouse. **Tidak** dijamin terbaca di HP (tidak ada hover).

Praktik ramah:

```html
<p>Bawa <abbr title="Kartu Tanda Penduduk">KTP</abbr> (Kartu Tanda Penduduk) saat pendaftaran pertama.</p>
```

Atau kepanjangan di teks, singkatan di belakang. Jangan mengandalkan tooltip saja.

Gaya putus-putus default bisa diatur:

```css
abbr[title] {
  text-decoration: underline dotted;
  cursor: help;
}
```

**Biasanya digabungkan dengan:** atribut global `title` (bab 07), teks FAQ, istilah regulasi. Pembaca layar bisa membacakan `title`, tetapi perilaku bervariasi — tetap tulis kepanjangan di teks saat pertama muncul.

## `<time>`

**Untuk apa:** menandai waktu atau tanggal yang bisa dibaca mesin di `datetime`, sementara isi elemen tetap ramah manusia.

```html
<p>Open trip berikutnya <time datetime="2026-10-12">12 Oktober 2026</time>.</p>
<p>Kumpul jam <time datetime="06:30">06.30 WIT</time> di dermaga.</p>
<p>Acara berlangsung <time datetime="2026-10-12T06:30+09:00">12 Oktober, 06.30 WIT</time>.</p>
```

### Atribut `datetime`

**Untuk apa:** nilai mesin. Format yang sering dipakai:

| Isi manusia | `datetime` |
| --- | --- |
| 12 Oktober 2026 | `2026-10-12` |
| Oktober 2026 | `2026-10` |
| 2026 | `2026` |
| 06.30 | `06:30` |
| 12 Oktober 06.30 WIT | `2026-10-12T06:30+09:00` |
| 4 hari | `P4D` (durasi ISO-8601, lebih jarang) |

Tanpa `datetime`, browser dan skrip hanya melihat teks bebas “minggu depan” yang sulit diurut.

```html
<!-- Lemah untuk diurut JS -->
<p>Minggu depan</p>

<!-- Bisa diurut -->
<p><time datetime="2026-10-12">minggu depan</time></p>
```

Bukan pengganti `<input type="date">`. `time` untuk menampilkan, input untuk meminta.

**Biasanya digabungkan dengan:** JS `new Date(el.dateTime)`, React `{formatTanggal(iso)}` di dalam `<time dateTime={iso}>` (perhatikan `dateTime` camelCase), Laravel `{{ $trip->starts_at->iso8601 }}` di atribut dan `translatedFormat('d F Y')` di isi. CSS tidak wajib.

## `<wbr>`

**Untuk apa:** **kesempatan putus baris** di tengah kata panjang. Void. Tidak menampilkan tanda hubung (beda dengan `&shy;`).

```html
<p>
  Unduh berkas
  https://contoh.test/files/<wbr />itinerary-raja-ampat-2026-revisi-panitia.pdf
</p>
<p>Nama kelas CSS: <code>kartu__judul<wbr />--unggulan</code></p>
```

URL dan identifier panjang sering merusak layout HP. `wbr` mengizinkan browser memotong di titik yang kamu pilih, tanpa memaksa potong jika masih muat.

Bandingkan:

| Cara | Efek |
| --- | --- |
| `<wbr>` | boleh putus di sini, tanpa karakter |
| `&shy;` | boleh putus dan bisa muncul tanda hubung |
| `word-break: break-all` | potong di huruf mana pun, sering jelek |
| `<br>` | **wajib** pindah baris |

**Biasanya digabungkan dengan:** CSS `overflow-wrap: anywhere` sebagai jaring pengaman, tabel yang berisi URL, dokumentasi API. Jarang dibutuhkan di paragraf biasa berbahasa Indonesia.

## Tag teks tetangga yang sering ketemu

Bukan daftar wajib dosen, tetapi sering muncul di dokumentasi dan perlu dibedakan.

### `<cite>`

**Untuk apa:** judul karya (buku, artikel, film), bukan nama orang.

```html
<p>Ringkasan dari <cite>Laporan Terumbu 2025</cite>.</p>
```

### `<dfn>`

**Untuk apa:** istilah yang sedang didefinisikan.

```html
<p>
  <dfn id="istilah-liveaboard">Liveaboard</dfn>
  adalah kapal yang dipakai menginap selama trip.
</p>
```

### `<kbd>`

**Untuk apa:** tombol keyboard yang harus ditekan.

```html
<p>Simpan dengan <kbd>Ctrl</kbd> + <kbd>S</kbd>.</p>
```

### `<var>`

**Untuk apa:** variabel dalam penjelasan.

```html
<p>Hitung <var>harga</var> × <var>jumlah</var> tamu.</p>
```

### `<samp>`

**Untuk apa:** keluaran program.

```html
<p>Terminal menulis <samp>Server running at http://localhost:5173</samp>.</p>
```

### `<data>`

**Untuk apa:** teks manusia + nilai mesin di `value`, jika bukan tanggal (tanggal pakai `<time>`).

```html
<p>Produk <data value="SKU-AMPAT-4D">Paket 4 hari</data></p>
```

**Biasanya digabungkan dengan:** dokumentasi tugas pemrograman, CSS `font-family: monospace` untuk `kbd`/`samp`.

## Mana yang semantik, mana yang hanya tampilan

| Kebutuhan | Pakai | Jangan hanya |
| --- | --- | --- |
| Judul halaman | `h1` | `p` ber-`font-size: 40px` |
| Penting / peringatan | `strong` | `b` atau `span` merah |
| Penekanan ucapan | `em` | `i` |
| Highlight pencarian | `mark` | `span` kuning tanpa makna |
| Tidak berlaku lagi | `s` / `del` | coretan CSS pada harga tanpa teks “diskon” |
| Kode | `code` / `pre` | `span` font mono |
| Wadah tanpa makna | `span` / `div` | heading palsu |
| Kutipan blok | `blockquote` | `div` indent |
| Tanggal bermakna | `time` | teks bebas jika perlu diurut |

Tampilan default browser (tebal, miring, kuning, kecil) hanyalah petunjuk. CSS boleh mengubah semuanya. Makna di pohon HTML tetap.

## Kesalahan teks yang sering muncul

1. **Banyak `h1`.** Satu judul halaman, lalu `h2` untuk bagian.
2. **Loncat `h1` → `h4`** karena ukuran default. Atur CSS.
3. **`<p>` berisi `<div>` / `<ul>`.** DOM dipotong browser.
4. **Tiga `<br>` untuk jarak.** Pakai `margin` / `gap`.
5. **`<u>` sebagai tautan palsu.** Pakai `<a>`.
6. **Seluruh paragraf di-`<strong>`.** Tidak ada hierarki kepentingan.
7. **`<pre>` untuk merapikan kolom halaman.** Pakai Grid.
8. **Mengandalkan `abbr title` di HP.** Tulis kepanjangan di teks.
9. **`<time>` tanpa `datetime` lalu diurut di JS.** Parsing “12 Okt” rapuh.
10. **`span` di mana-mana** sampai makna heading/paragraf hilang.

Latihan pendek: tulis ulang satu halaman profil dengan tepat satu `h1`, dua `h2`, paragraf terpisah, satu peringatan `strong`, satu tanggal `time`, dan tanpa `<br><br>` untuk jarak.
