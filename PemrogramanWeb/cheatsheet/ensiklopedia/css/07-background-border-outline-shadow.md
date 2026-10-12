# 07 — Background, border, outline, shadow

[← Warna](06-warna-tipografi-list.md) · [Indeks](README.md) · [Position →](08-position-zindex-float-sticky.md)

Lapisan visual kotak: cat latar, bingkai, cincin fokus, dan bayangan. Outline tidak memakan box model; border iya.

## Daftar isi

- [background-color](#background-color)
- [background-image](#background-image)
- [background-size position repeat origin clip](#background-size-position-repeat-origin-clip)
- [background shorthand dan lapisan](#background-shorthand-dan-lapisan)
- [Gradien](#gradien)
- [background-attachment](#background-attachment)
- [border](#border)
- [border-radius](#border-radius)
- [border-image](#border-image)
- [outline](#outline)
- [outline-offset](#outline-offset)
- [box-shadow](#box-shadow)
- [text-shadow](#text-shadow)
- [filter drop-shadow](#filter-drop-shadow)
- [ring Tailwind vs outline](#ring-tailwind-vs-outline)

## background-color

**Untuk apa:** cat datar di belakang konten dan padding (tergantung `background-clip`).

```css
body { background-color: #f8fafc; }
.kartu { background-color: white; }
.chip { background-color: rgb(15 23 42 / 0.06); }
```

`transparent` bawaan. Warna di bawah gambar latar jika gambar tidak menutup penuh atau punya alpha.

**Biasanya digabungkan dengan:** `color` kontras, `border`, `border-radius`.

## background-image

**Untuk apa:** gambar atau gradien sebagai latar. Bisa bertumpuk, dipisah koma.

```css
.hero {
  background-image: url("/hero.jpg");
}

.hero-gelap {
  background-image:
    linear-gradient(rgb(15 23 42 / 0.55), rgb(15 23 42 / 0.55)),
    url("/hero.jpg");
}
```

Lapisan pertama yang ditulis ada di **atas**. Gradien gelap di atas foto membuat teks putih kebaca.

**Biasanya digabungkan dengan:** `background-size: cover`, `color` teks terang.

## background-size position repeat origin clip

### background-size

**Untuk apa:** skala gambar latar.

```css
.hero { background-size: cover; }
.pola { background-size: 16px 16px; }
.logo { background-size: contain; }
.asli { background-size: auto; }
.persen { background-size: 100% 100%; }
```

`cover` isi kotak, potong sisa (seperti `object-fit: cover`). `contain` utuh. Dua panjang = lebar tinggi.

**Biasanya digabungkan dengan:** `background-position: center`.

### background-position

**Untuk apa:** jangkar gambar.

```css
.hero { background-position: center; }
.hero { background-position: center top; }
.hero { background-position: 50% 20%; }
.hero { background-position: right 1rem bottom 1rem; }
```

Keyword atau persen (0% 0% = kiri atas).

**Biasanya digabungkan dengan:** `cover`.

### background-repeat

**Untuk apa:** ubin.

```css
.hero { background-repeat: no-repeat; }
.pola { background-repeat: repeat; }
.garis { background-repeat: repeat-x; }
```

Nilai lain: `repeat-y`, `space`, `round`.

**Biasanya digabungkan dengan:** `background-size`, pola kecil.

### background-origin

**Untuk apa:** kotak acuan posisi: `border-box`, `padding-box` (bawaan), `content-box`.

```css
.kartu { background-origin: content-box; }
```

**Biasanya digabungkan dengan:** padding tebal + gambar yang tidak boleh masuk padding.

### background-clip

**Untuk apa:** area cat. `border-box`, `padding-box`, `content-box`, `text`.

```css
.judul-gradien {
  background-image: linear-gradient(90deg, #0f766e, #0369a1);
  background-clip: text;
  color: transparent;
}
```

Teks jadi “jendela” ke gradien. Butuh `color: transparent`. Periksa kontras dan fallback.

**Biasanya digabungkan dengan:** `color: transparent`, `-webkit-background-clip: text` di browser lama.

## background shorthand dan lapisan

**Untuk apa:** merangkai image + position/size + repeat + clip dalam satu deklarasi.

```css
.hero {
  background:
    linear-gradient(rgb(15 23 42 / 0.5), rgb(15 23 42 / 0.5)) center / cover no-repeat,
    url("/hero.jpg") center / cover no-repeat;
  background-color: #0f172a;
}
```

Sintaks `position / size`. `background-color` biasanya di layer terakhir atau properti terpisah (warna tidak ikut koma layer dengan cara yang sama).

Reset trap: shorthand `background: red` menghapus `background-image` sebelumnya.

**Biasanya digabungkan dengan:** `min-height`, teks kontras.

## Gradien

### linear-gradient

**Untuk apa:** transisi warna sepanjang garis.

```css
.banner {
  background-image: linear-gradient(180deg, #0f766e, #134e4a);
}

.fade {
  background-image: linear-gradient(
    to right,
    #0f172a 0%,
    #0f172a 40%,
    transparent 100%
  );
}
```

Arah: sudut (`180deg`) atau `to top/right/...`. Color stop: warna + posisi.

**Biasanya digabungkan dengan:** overlay foto, progress.

### radial-gradient

**Untuk apa:** dari pusat ke luar.

```css
.spotlight {
  background-image: radial-gradient(circle at top, #f8fafc, #cbd5e1);
}
```

**Biasanya digabungkan dengan:** hero, kartu.

### conic-gradient

**Untuk apa:** berputar mengelilingi titik (pie chart).

```css
.pie {
  background-image: conic-gradient(#0f766e 0 40%, #e2e8f0 40% 100%);
  border-radius: 50%;
}
```

**Biasanya digabungkan dengan:** `border-radius: 50%`, chart CSS.

### repeating-*-gradient

**Untuk apa:** pola berulang.

```css
.stripes {
  background-image: repeating-linear-gradient(
    45deg,
    #e2e8f0 0 8px,
    #f8fafc 8px 16px
  );
}
```

**Biasanya digabungkan dengan:** state disabled, skeleton.

## background-attachment

**Untuk apa:** `scroll` (bawaan) ikut elemen; `fixed` relatif viewport; `local` ikut konten scroll elemen.

```css
.parallax-kasar {
  background-attachment: fixed;
  background-size: cover;
}
```

`fixed` mahal dan sering rusak di HP. Hindari sebagai syarat tugas kecuali diminta.

**Biasanya digabungkan dengan:** `cover`, hero desktop.

## border

### Shorthand sisi

**Untuk apa:** ketebalan + gaya + warna sekaligus.

```css
.kartu { border: 1px solid #cbd5e1; }
.tombol { border: 2px solid currentColor; }
.halus { border: 0; }
```

Gaya: `solid`, `dashed`, `dotted`, `double`, `none`, `hidden`, `groove`, `ridge`, `inset`, `outset`.

Tanpa `style`, border tidak kelihatan (`border-width` saja tidak cukup).

**Biasanya digabungkan dengan:** `border-radius`, `background`.

### Per sisi

**Untuk apa:** garis hanya di satu sisi.

```css
.kutipan { border-inline-start: 4px solid #0f766e; padding-inline-start: 1rem; }
.tab-aktif { border-bottom: 2px solid #0f172a; }
input.salah { border-color: #b91c1c; }
```

Logical: `border-block-start` dll.

**Biasanya digabungkan dengan:** `padding-inline-start`, state form.

### border-width style color

**Untuk apa:** memisahkan bagian shorthand agar hover hanya ganti warna.

```css
.tombol {
  border-width: 2px;
  border-style: solid;
  border-color: #0f172a;
}

.tombol:hover { border-color: #334155; }
```

Kalau hover `border: 2px solid ...` mengulang semuanya, ok. Kalau hover menambah border yang tadinya 0, ukuran tombol loncat — sediakan `border: 2px solid transparent` dari awal.

**Biasanya digabungkan dengan:** `box-sizing: border-box`.

### border-collapse dan border-spacing

**Untuk apa:** khusus tabel.

```css
table {
  border-collapse: collapse;
  width: 100%;
}

table.longgar {
  border-collapse: separate;
  border-spacing: 0 0.5rem;
}
```

`collapse` menyatukan border sel. `separate` + `border-spacing` membuat jarak antar baris.

**Biasanya digabungkan dengan:** `th`/`td` padding, `vertical-align`.

## border-radius

**Untuk apa:** sudut membulat. Persen mengacu ke ukuran kotak (50% pada persegi = lingkaran).

```css
.kartu { border-radius: 0.75rem; }
.tombol { border-radius: 0.5rem; }
.pill { border-radius: 999px; }
.avatar { border-radius: 50%; }
.khusus { border-radius: 0.25rem 0.75rem 0.75rem 0.25rem; }
.logical { border-start-start-radius: 0.75rem; }
```

Empat nilai: kiri-atas, kanan-atas, kanan-bawah, kiri-bawah. `999px` menjamin kapsul meski tinggi berubah.

Anak yang melewati sudut perlu `overflow: hidden` di induk, atau radius sendiri.

**Biasanya digabungkan dengan:** `overflow: hidden`, `background`, `box-shadow`.

## border-image

**Untuk apa:** memotong gambar menjadi bingkai 9-slice.

```css
.bingkai {
  border: 12px solid transparent;
  border-image: url("/bingkai.png") 12 / 12px / 0 round;
}
```

Sulit dikontrol di tugas UI modern. Gradien juga bisa jadi `border-image`.

```css
.gradien-bingkai {
  border: 2px solid transparent;
  border-image: linear-gradient(90deg, #0f766e, #0369a1) 1;
}
```

`border-image` biasanya menonaktifkan `border-radius`. Trik radius + gradien border: pseudo-element atau `background` ganda.

**Biasanya digabungkan dengan:** desain ornamental, bukan kartu tugas.

## outline

**Untuk apa:** cincin di luar border, **tidak mengubah ukuran kotak**. Standar fokus aksesibel.

```css
.tombol:focus-visible {
  outline: 2px solid #0369a1;
  outline-offset: 3px;
}

.rusak:focus { outline: none; }
```

Jangan menghapus outline tanpa pengganti (`box-shadow` / `outline` custom yang kontras). `outline: none` pada `:focus` selalu merugikan keyboard.

Shorthand sama seperti border: width style color. `outline-style: auto` memakai cincin native browser.

**Biasanya digabungkan dengan:** `:focus-visible`, `outline-offset`.

## outline-offset

**Untuk apa:** jarak outline dari tepi border. Boleh negatif.

```css
a:focus-visible {
  outline: 2px solid currentColor;
  outline-offset: 0.2em;
}
```

**Biasanya digabungkan dengan:** `border-radius` (outline mengikuti radius di browser modern).

## box-shadow

**Untuk apa:** bayangan kotak, atau cincin (shadow tanpa blur + spread).

```css
.kartu {
  box-shadow: 0 1px 2px rgb(15 23 42 / 0.08);
}

.kartu:hover {
  box-shadow: 0 8px 24px rgb(15 23 42 / 0.12);
}

.cincin {
  box-shadow: 0 0 0 3px #93c5fd;
}

.dalam {
  box-shadow: inset 0 0 0 1px rgb(15 23 42 / 0.12);
}

.ganda {
  box-shadow:
    0 1px 2px rgb(15 23 42 / 0.06),
    0 8px 16px rgb(15 23 42 / 0.08);
}
```

Urutan: `inset? offset-x offset-y blur spread color`. Spread positif membesarkan bayangan; berguna untuk ring.

`box-shadow` tidak memengaruhi layout. Bisa terpotong `overflow: hidden` induk.

**Biasanya digabungkan dengan:** `border-radius`, `transition`, hover kartu.

## text-shadow

**Untuk apa:** bayangan glif.

```css
.hero h1 {
  text-shadow: 0 1px 2px rgb(0 0 0 / 0.45);
}

.neon {
  text-shadow: 0 0 8px #22d3ee;
}
```

Banyak shadow pada teks panjang menurunkan keterbacaan.

**Biasanya digabungkan dengan:** teks di atas foto.

## filter drop-shadow

**Untuk apa:** bayangan mengikuti bentuk alfa (png/svg), bukan kotak.

```css
.logo {
  filter: drop-shadow(0 4px 8px rgb(15 23 42 / 0.25));
}
```

`box-shadow` pada PNG transparan tetap persegi. `drop-shadow` mengikuti siluet.

**Biasanya digabungkan dengan:** ikon, stiker. Lihat [bab 09](09-transform-filter-transition-animation.md).

## ring Tailwind vs outline

**Untuk apa:** memetakan class ring ke CSS.

Tailwind `ring-2 ring-sky-300` biasanya `box-shadow` (bukan `outline`), agar radius mengikuti dan bisa dianimasikan. `outline` tetap lebih aman untuk fokus karena tidak terpotong overflow dengan cara yang sama di semua kasus — tetapi `ring` + `ring-offset` sudah cukup jika kontrasnya benar.

```html
<button class="rounded-md focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-sky-500 focus-visible:ring-offset-2">
  Simpan
</button>
```

Hanya boleh `outline-none` jika `ring` muncul di `:focus-visible`.

**Biasanya digabungkan dengan:** `rounded-*`, `ring-offset-background`.
