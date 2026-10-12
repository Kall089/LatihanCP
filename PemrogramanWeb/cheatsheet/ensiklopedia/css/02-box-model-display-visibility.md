# 02 — Box model, display, visibility

[← Kaskade](01-kaskade-selector-spesifisitas.md) · [Indeks](README.md) · [Satuan →](03-satuan-sizing-overflow.md)

Setiap elemen yang terlihat adalah kotak. Urutan dari dalam: **content → padding → border → margin**. Layout Flexbox dan Grid mengatur kotak-kotak ini, bukan “teks melayang”.

## Daftar isi

- [Peta box model](#peta-box-model)
- [box-sizing](#box-sizing)
- [width dan height](#width-dan-height)
- [min-width max-width min-height max-height](#min-width-max-width-min-height-max-height)
- [padding](#padding)
- [margin](#margin)
- [border sebagai bagian kotak](#border-sebagai-bagian-kotak)
- [display](#display)
- [visibility](#visibility)
- [opacity](#opacity)
- [content-visibility](#content-visibility)
- [overflow di kotak](#overflow-di-kotak)
- [aspect-ratio](#aspect-ratio)
- [object-fit dan object-position](#object-fit-dan-object-position)
- [isolation](#isolation)
- [contain](#contain)
- [writing-mode dan arah kotak](#writing-mode-dan-arah-kotak)
- [logical properties](#logical-properties)

## Peta box model

**Untuk apa:** menghitung ruang yang benar-benar dipakai di halaman.

```css
.kotak {
  width: 20rem;
  padding: 1rem;
  border: 4px solid #0f172a;
  margin: 2rem;
}
```

Dengan `content-box` (bawaan lama): lebar total = 20rem + 2rem padding + 8px border. Margin tidak masuk lebar, tetapi mendorong tetangga. Dengan `border-box`: `width: 20rem` sudah termasuk padding dan border.

**Biasanya digabungkan dengan:** `box-sizing: border-box` di `*`.

## box-sizing

### content-box

**Untuk apa:** `width`/`height` hanya menghitung area konten.

```css
.iklan-legacy {
  box-sizing: content-box;
  width: 300px;
  padding: 10px;
}
```

Lebar visual jadi 320px. Jarang diinginkan di layout modern.

**Biasanya digabungkan dengan:** widget pihak ketiga yang mengasumsikan model lama.

### border-box

**Untuk apa:** `width` sudah termasuk padding dan border.

```css
*,
*::before,
*::after {
  box-sizing: border-box;
}

.kartu {
  width: 100%;
  padding: 1rem;
  border: 1px solid #cbd5e1;
}
```

Kartu selebar wadah, tidak 2rem lebih lebar karena padding.

**Biasanya digabungkan dengan:** `width: 100%`, form, grid kolom.

## width dan height

### width

**Untuk apa:** lebar kotak.

```css
.kontainer {
  width: min(100% - 2rem, 70rem);
}

.sidebar {
  width: 16rem;
}

.gambar {
  width: 100%;
}
```

`auto` (bawaan block) berarti “ambil ruang yang tersedia”. `100%` berarti “100% lebar acuan”, biasanya induk.

**Biasanya digabungkan dengan:** `max-width`, `margin-inline: auto`.

### height

**Untuk apa:** tinggi kotak. Hindari tinggi tetap pada teks yang bisa membungkus.

```css
.hero {
  min-height: 100dvh;
}

.thumb {
  height: 12rem;
  object-fit: cover;
}
```

`height: 100%` hanya jalan jika induk punya tinggi yang terhitung, bukan `auto`.

**Biasanya digabungkan dengan:** `min-height`, `object-fit`, Flexbox `align-items: stretch`.

### inline-size dan block-size

**Untuk apa:** lebar/tinggi logis mengikuti arah tulisan.

```css
.kartu {
  inline-size: min(100%, 24rem);
  block-size: auto;
}
```

Di tulisan LTR, `inline-size` = lebar. Di mode vertikal, ia jadi tinggi.

**Biasanya digabungkan dengan:** `margin-inline`, proyek multibahasa.

## min-width max-width min-height max-height

### max-width

**Untuk apa:** membatasi lebar maksimum tanpa memaksa layar kecil.

```css
.prosa {
  max-width: 65ch;
}

.halaman {
  max-width: 70rem;
  width: 100%;
  margin-inline: auto;
}
```

`65ch` kira-kira 65 karakter; nyaman dibaca.

**Biasanya digabungkan dengan:** `width: 100%` atau `width: min(...)`.

### min-width

**Untuk apa:** mencegah kotak lebih sempit dari batas. Sering jadi biang overflow.

```css
.tabel-bungkus {
  min-width: 0;
}

.logo-teks {
  min-width: 8rem;
}
```

Item flex/grid secara bawaan `min-width: auto` (tidak boleh lebih kecil dari konten). `min-width: 0` mengizinkan menyusut.

**Biasanya digabungkan dengan:** `flex: 1`, `minmax(0, 1fr)`, `overflow: auto`.

### min-height

**Untuk apa:** tinggi minimal, boleh tumbuh.

```css
.halaman {
  min-height: 100dvh;
  display: flex;
  flex-direction: column;
}

.footer {
  margin-top: auto;
}
```

Footer ke bawah layar meski konten pendek. `dvh` mengikuti tinggi viewport dinamis di HP.

**Biasanya digabungkan dengan:** flex kolom + `margin-top: auto`.

### max-height

**Untuk apa:** membatasi tinggi lalu scroll di dalam.

```css
.dialog-badan {
  max-height: min(70vh, 40rem);
  overflow: auto;
}
```

**Biasanya digabungkan dengan:** `overflow: auto`, modal.

## padding

**Untuk apa:** jarak isi ke border. Latar dan border mengikuti padding.

```css
.kartu {
  padding: 1rem;
}

.kartu-rapat {
  padding: 0.5rem 1rem;
}

.kartu-detail {
  padding: 1rem 1.25rem 1.5rem;
}

.kartu-empat {
  padding: 1rem 1.25rem 1.5rem 0.75rem;
}
```

Shorthand: 1 nilai = semua sisi; 2 = atas-bawah + kiri-kanan; 3 = atas + kiri-kanan + bawah; 4 = atas kanan bawah kiri (jarum jam).

```css
.kartu {
  padding-block: 1rem;
  padding-inline: 1.25rem;
}
```

Logical: `padding-block` = atas-bawah di LTR.

**Biasanya digabungkan dengan:** `background`, `border`, `border-radius`.

### padding per sisi

**Untuk apa:** menyentuh satu sisi tanpa merusak yang lain.

```css
.nav-tautan {
  padding-inline: 0.75rem;
  padding-block: 0.5rem;
}

.prosa h2 {
  padding-top: 0.5em;
}
```

**Biasanya digabungkan dengan:** tap target minimal ~44px di HP.

## margin

**Untuk apa:** jarak di luar border. Latar tidak mengecat margin.

```css
.kartu + .kartu {
  margin-top: 1rem;
}

.tengah {
  width: min(100% - 2rem, 40rem);
  margin-inline: auto;
}
```

`auto` di kiri dan kanan (atau `margin-inline: auto`) menengahkan block yang lebih sempit dari induk.

**Biasanya digabungkan dengan:** `width`/`max-width`, bukan dengan flex item yang sudah di-`gap`.

### margin collapse

**Untuk apa:** memahami kenapa `margin-top` anak dan `margin-bottom` induk bisa “menyatu”.

```css
.artikel h2 {
  margin-block: 1.5em 0.5em;
}

.artikel p {
  margin-block: 0.75em;
}
```

Dua margin vertikal yang bertemu sering mengambil yang lebih besar, bukan jumlah. Collapse tidak terjadi pada flex/grid item, atau jika ada padding/border/overflow yang memisahkan.

**Biasanya digabungkan dengan:** `gap` di flex/grid agar jarak tidak collapse.

### margin negatif

**Untuk apa:** menarik kotak mendekati tetangga atau keluar wadah.

```css
.full-bleed {
  width: 100vw;
  margin-left: calc(50% - 50vw);
}
```

Gambar artikel melebar sampai tepi viewport. Rapuh jika ada scrollbar. Alternatif modern: grid full-bleed.

**Biasanya digabungkan dengan:** `overflow-x: hidden` di induk hanya jika terpaksa.

## border sebagai bagian kotak

**Untuk apa:** ketebalan border menambah ukuran di `content-box`, atau memakan ruang konten di `border-box`.

```css
.tombol {
  border: 2px solid #0f172a;
}

.tombol:hover {
  border-color: #334155;
}
```

`border: none` atau `border-width: 0` menghilangkan ketebalan. Mengganti `border` jadi `transparent` menjaga ukuran saat hover.

**Biasanya digabungkan dengan:** `box-sizing: border-box`, lihat [bab 07](07-background-border-outline-shadow.md).

## display

### block

**Untuk apa:** kotak selebar induk, mulai di baris baru.

```css
.bagian { display: block; }
```

Bawaan `div`, `p`, `h1`, `section`. Boleh set `width`/`height`.

**Biasanya digabungkan dengan:** `width`, `margin`.

### inline

**Untuk apa:** ikut alur teks. `width`/`height` diabaikan. Padding vertikal tidak mendorong baris lain secara penuh.

```css
a { display: inline; }
```

Bawaan `span`, `a`, `em`, `strong`.

**Biasanya digabungkan dengan:** `color`, `text-decoration`, bukan `width`.

### inline-block

**Untuk apa:** duduk di baris teks tetapi hormati width, height, padding.

```css
.lencana {
  display: inline-block;
  padding: 0.15rem 0.5rem;
  border-radius: 999px;
}
```

Spasi HTML antar elemen inline-block bisa muncul sebagai celah. Flex/grid lebih bersih untuk deretan lencana.

**Biasanya digabungkan dengan:** badge, tombol kecil di kalimat.

### none

**Untuk apa:** melepas elemen dari layout. Tidak kena klik, tidak kebaca screen reader secara visual, tidak makan ruang.

```css
.menu-panel { display: none; }
.menu-panel.terbuka { display: flex; }
```

Jangan animasikan `display`. Untuk animasi, pakai `visibility`, `opacity`, atau `grid-template-rows`.

**Biasanya digabungkan dengan:** class yang di-toggle JavaScript, hamburger.

### contents

**Untuk apa:** menghilangkan kotak elemen, anak-anaknya naik seolah jadi anak kakek.

```css
.bungkus-semu { display: contents; }
```

Berguna agar wrapper React tidak merusak grid. Hati-hati aksesibilitas: beberapa browser memperlakukan elemen `contents` aneh untuk role.

**Biasanya digabungkan dengan:** Grid/Flex yang terpecah oleh wrapper.

### list-item

**Untuk apa:** kotak plus marker daftar.

```css
.langkah { display: list-item; list-style: decimal; }
```

Bawaan `li`. Marker bisa diatur `list-style`.

**Biasanya digabungkan dengan:** `list-style-position`, `padding-left`.

### flow-root

**Untuk apa:** block yang membuat formatting context baru; merangkul float dan mencegah margin collapse ke luar.

```css
.kartu { display: flow-root; }
```

Pengganti klasik `overflow: hidden` sebagai clearfix.

**Biasanya digabungkan dengan:** konten yang masih memakai float gambar.

### flex dan inline-flex

**Untuk apa:** menjadikan elemen flex container. Anak jadi flex item.

```css
.baris { display: flex; }
.lencana-grup { display: inline-flex; align-items: center; gap: 0.35rem; }
```

`inline-flex` selebar isi, duduk di alur teks. Detail properti: [bab 04](04-flexbox-semua-properti.md).

**Biasanya digabungkan dengan:** `gap`, `align-items`, `justify-content`.

### grid dan inline-grid

**Untuk apa:** menjadikan elemen grid container.

```css
.papan { display: grid; }
.meta { display: inline-grid; grid-auto-flow: column; gap: 0.5rem; }
```

Detail: [bab 05](05-grid-semua-properti.md).

**Biasanya digabungkan dengan:** `grid-template-columns`, `gap`.

### table, table-row, table-cell

**Untuk apa:** meniru model tabel CSS, termasuk elemen non-tabel.

```css
.baris { display: table; width: 100%; }
.sel { display: table-cell; vertical-align: middle; }
```

Berguna untuk email HTML lama. Untuk layout halaman, pakai Flex/Grid.

**Biasanya digabungkan dengan:** `border-collapse` pada tabel sungguhan.

## visibility

### visible

**Untuk apa:** nilai bawaan; elemen terlihat.

```css
.tip { visibility: visible; }
```

**Biasanya digabungkan dengan:** toggle dari `hidden`.

### hidden

**Untuk apa:** tidak terlihat, tetap memakan ruang, tidak kena pointer.

```css
.placeholder-icon {
  visibility: hidden;
}
```

Layout tidak loncat. Screen reader umumnya tetap bisa baca, berbeda dari `display: none`.

**Biasanya digabungkan dengan:** reservasi ruang ikon atau skeleton.

### collapse

**Untuk apa:** pada baris/kolom tabel, menghilangkan baris dan merapatkan. Pada flex item, mirip `hidden` di banyak browser.

```css
tr.arsip { visibility: collapse; }
```

**Biasanya digabungkan dengan:** tabel data, bukan kartu.

## opacity

**Untuk apa:** transparansi seluruh kotak termasuk anak. Nilai `0`–`1`.

```css
.habis { opacity: 0.55; }
.fade { opacity: 0; }
.fade.masuk { opacity: 1; transition: opacity 200ms; }
```

Elemen `opacity: 0` masih bisa diklik kecuali `pointer-events: none`. `opacity` selain `1` membuat stacking context baru.

**Biasanya digabungkan dengan:** `transition`, `pointer-events`, `disabled`.

## content-visibility

**Untuk apa:** menunda rendering isi di luar layar.

```css
.artikel-panjang > section {
  content-visibility: auto;
  contain-intrinsic-size: auto 20rem;
}
```

Halaman artikel panjang jadi lebih ringan. Tinggi harus diperkirakan agar scrollbar tidak loncat.

**Biasanya digabungkan dengan:** `contain-intrinsic-size`.

## overflow di kotak

**Untuk apa:** memutus apakah konten boleh keluar kotak.

```css
.kartu { overflow: hidden; }
.daftar { overflow: auto; }
.kode { overflow-x: auto; overflow-y: hidden; }
```

`hidden` potong. `auto` scrollbar jika perlu. `scroll` selalu sediakan gutter scrollbar (bergantung OS). `clip` potong tanpa programatik scroll.

`overflow` selain `visible` bisa membuat block formatting context dan jadi containing block untuk `absolute`/`fixed` dalam kasus tertentu (`transform` juga).

**Biasanya digabungkan dengan:** `max-height`, `border-radius` (agar anak mengikuti sudut).

## aspect-ratio

**Untuk apa:** mengunci perbandingan lebar:tinggi.

```css
.thumb {
  aspect-ratio: 16 / 9;
  width: 100%;
  object-fit: cover;
}

.avatar {
  aspect-ratio: 1;
  width: 3rem;
}
```

Kalau `width` dan `height` keduanya sudah set, `aspect-ratio` bisa dikalahkan.

**Biasanya digabungkan dengan:** `object-fit: cover`, `width: 100%`.

## object-fit dan object-position

**Untuk apa:** mengatur bagaimana `<img>` atau `<video>` mengisi kotak yang sudah berukuran.

```css
.thumb {
  width: 100%;
  height: 12rem;
  object-fit: cover;
  object-position: center top;
}
```

`cover` isi kotak, potong sisa. `contain` utuh, mungkin ada letterbox. `fill` regang. `none` ukuran intrinsik. `scale-down` pilih `none` atau `contain` yang lebih kecil.

**Biasanya digabungkan dengan:** `aspect-ratio`, `border-radius`.

## isolation

**Untuk apa:** memaksa stacking context baru tanpa `opacity` atau `z-index`.

```css
.kartu { isolation: isolate; }
```

`z-index` anak tidak “bocor” menimpa kartu sebelah.

**Biasanya digabungkan dengan:** `z-index` di badge, overlay kartu.

## contain

**Untuk apa:** berjanji ke browser bahwa layout/cat/ukuran anak tidak memengaruhi luar.

```css
.kartu {
  contain: layout paint;
}

.feed-item {
  contain: content;
}
```

`strict` paling ketat. Salah pakai bisa memotong `box-shadow` atau `position: fixed` yang tidak kamu duga.

**Biasanya digabungkan dengan:** daftar panjang, `content-visibility`.

## writing-mode dan arah kotak

**Untuk apa:** mengubah sumbu block dan inline.

```css
.spesial {
  writing-mode: vertical-rl;
}
```

Flex `row` mengikuti arah inline. Logical properties (`margin-inline-start`) tetap benar saat arah berubah.

**Biasanya digabungkan dengan:** `direction`, `unicode-bidi`, properti logis.

## logical properties

**Untuk apa:** padding/margin/border yang mengikuti arah tulisan, bukan “kiri” kaku.

```css
.kartu {
  margin-inline: auto;
  padding-inline-start: 1rem;
  border-inline-end: 1px solid #e2e8f0;
}

.icon-teks {
  margin-inline-end: 0.5rem;
}
```

Di LTR, `inline-start` = kiri. Di RTL, ia jadi kanan. Navbar multibahasa tidak perlu rewrite.

**Biasanya digabungkan dengan:** `dir="rtl"`, `gap`, Flexbox.
