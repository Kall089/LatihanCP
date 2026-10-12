# Modul 02 — CSS Dasar

> Praktikum terkait: [`../../1-pembelajaran/02-css-dasar/`](../../1-pembelajaran/02-css-dasar/)
> (4 bab: kartu profil, selector & specificity, box model, pseudo-class).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menghubungkan CSS ke HTML dengan tiga cara dan tahu kapan memakai yang mana.
- Menulis selector yang tepat dan memprediksi pemenang saat dua rule bertabrakan
  (cascade & specificity).
- Menggambar dan menghitung box model, termasuk efek `box-sizing`.
- Memakai unit (`px`, `rem`, `%`), warna, dan properti tipografi dengan alasan.
- Membuat state interaktif `:hover`/`:focus` yang halus dan aksesibel.

---

## 1. Cara kerja CSS: rule, selector, deklarasi

CSS (*Cascading Style Sheets*) bekerja dengan pola sederhana: **pilih elemen,
lalu atur tampilannya**.

```text
     selector          deklarasi (properti: nilai;)
   ┌────────────┐    ┌──────────────────────────────┐
   .kartu-profil {
       background-color: #ffffff;
       padding: 24px;
       border-radius: 12px;
   }
   └───── satu RULE = selector + blok deklarasi ─────┘
```

### Tiga cara memasang CSS

```html
<!-- 1. EXTERNAL (terbaik): satu file untuk banyak halaman -->
<link rel="stylesheet" href="style.css">

<!-- 2. INTERNAL: di <head>, untuk demo/halaman tunggal -->
<style> p { color: teal; } </style>

<!-- 3. INLINE: hindari — tercecer, specificity tertinggi, tak reusable -->
<p style="color: red">...</p>
```

**Mengapa external menang?** Reusable (satu `style.css` → semua halaman),
cache oleh browser, dan pemisahan tanggung jawab. Seluruh praktikum
menggunakan cara ini.

---

## 2. Selector: memilih elemen dengan tepat

```css
/* Elemen — semua <p> di halaman */
p { line-height: 1.6; }

/* Class — bisa dipakai berulang; PILIHAN UTAMA */
.tombol { padding: 8px 16px; }

/* ID — unik satu per halaman; untuk anchor/JS, hindari untuk styling */
#menu-utama { position: sticky; }

/* Turunan (descendant) — <a> di mana pun di dalam <nav> */
nav a { text-decoration: none; }

/* Anak langsung (child) — hanya level pertama */
.kartu > h2 { margin-top: 0; }

/* Gabungan — <p> yang PUNYA class info */
p.info { color: #0369a1; }

/* Grup — beberapa selector, satu gaya */
h1, h2, h3 { font-family: Georgia, serif; }

/* Atribut */
input[type="email"] { border-color: skyblue; }

/* Universal */
* { box-sizing: border-box; }
```

Panduan memilih:

- **Class** untuk hampir semuanya — reusable dan specificity rendah yang sehat.
- **Selector elemen** untuk gaya dasar global (`body`, `p`, `a`).
- **ID** jangan untuk styling: specificity terlalu tinggi, susah dioverride.
- Selector turunan jangan terlalu dalam (`div ul li a span` = rapuh).

---

## 3. Cascade & specificity: siapa yang menang?

"Cascading" pada CSS berarti banyak rule bisa mengenai elemen yang sama, dan
ada aturan baku untuk menentukan pemenang. Ini materi ujian favorit.

Urutan keputusan browser:

1. **Origin & `!important`** — `!important` mengalahkan semuanya (karena itu
   jangan dipakai kecuali terpaksa).
2. **Specificity** — dihitung sebagai tiga angka `(ID, CLASS, ELEMEN)`:

```text
p              → (0,0,1)
.info          → (0,1,0)
p.info         → (0,1,1)
nav a          → (0,0,2)
#header .menu  → (1,1,0)
:hover, [attr] → dihitung sebagai CLASS → (0,1,0)
```

   Bandingkan dari kiri: `(1,0,0)` menang atas `(0,9,9)` — ID mengalahkan
   berapa pun class.
3. **Urutan penulisan** — skor sama? Rule yang ditulis **terakhir** menang.

Contoh soal ujian:

```css
p { color: black; }          /* (0,0,1) */
.merah { color: red; }       /* (0,1,0) ← menang */
p { color: blue; }           /* (0,0,1) — kalah walau terakhir, skor lebih kecil */
```

```html
<p class="merah">Warna saya MERAH.</p>
```

### Inheritance (pewarisan)

Properti teks (`color`, `font-family`, `font-size`, `line-height`) **menurun**
ke anak-anaknya — set sekali di `body`, seluruh halaman ikut. Properti kotak
(`margin`, `padding`, `border`, `width`) **tidak menurun**. Karena itulah
`body { font-family: ... }` cukup sekali.

---

## 4. Box model: setiap elemen adalah kotak

```text
┌─────────────────────────────────────┐
│           margin (transparan)       │  ← jarak ANTAR elemen
│  ┌───────────────────────────────┐  │
│  │  border (garis tepi)          │  │
│  │  ┌─────────────────────────┐  │  │
│  │  │  padding (jarak dalam)  │  │  │  ← ruang napas DI DALAM
│  │  │  ┌───────────────────┐  │  │  │
│  │  │  │      content      │  │  │  │
│  │  │  │   teks / gambar   │  │  │  │
│  │  │  └───────────────────┘  │  │  │
│  │  └─────────────────────────┘  │  │
│  └───────────────────────────────┘  │
└─────────────────────────────────────┘
```

### `box-sizing` — hitungan lebar yang waras

Default browser (`content-box`): `width` hanya mengukur *content*.

```css
.kartu { width: 300px; padding: 24px; border: 2px solid; }
/* content-box: lebar total = 300 + 24×2 + 2×2 = 352px  😱 */
/* border-box : lebar total = 300px, content menyusut    ✅ */
```

Karena hitungan `content-box` menyiksa, baris pertama hampir semua proyek:

```css
* { box-sizing: border-box; }
```

### Shorthand margin/padding

```css
padding: 16px;                /* semua sisi */
padding: 8px 16px;            /* vertikal | horizontal */
padding: 8px 16px 24px;       /* atas | kiri-kanan | bawah */
padding: 1px 2px 3px 4px;     /* atas kanan bawah kiri (searah jarum jam) */
margin: 0 auto;               /* auto kiri-kanan = blok ber-width jadi DI TENGAH */
```

### Margin collapse

Dua margin **vertikal** yang bertemu tidak dijumlah — diambil yang terbesar.
`h2 { margin-bottom: 24px }` di atas `p { margin-top: 16px }` menghasilkan
jarak 24px, bukan 40px. Sumber kebingungan pemula nomor satu; solusinya cukup
tahu perilakunya (atau atur margin satu arah saja).

### display: block vs inline

| | `block` | `inline` | `inline-block` |
|---|---|---|---|
| Mulai baris baru | ya | tidak | tidak |
| width/height bisa diatur | ya | **tidak** | ya |
| Contoh default | `div`, `p`, `h1`, `section` | `a`, `span`, `strong` | `img` (mirip) |

Sering muncul di ujian: "mengapa `width` pada `<span>` tidak berpengaruh?" —
karena span `inline`; ubah ke `inline-block` atau `block`.

---

## 5. Unit dan warna

| Unit | Contoh | Kapan dipakai — dan mengapa |
|---|---|---|
| `px` | `border: 1px` | Detail presisi (border, shadow) yang tak perlu ikut skala |
| `rem` | `font-size: 1.25rem` | Ukuran teks & spacing; 1rem = 16px default, **ikut setelan font pengguna** (aksesibilitas) |
| `em` | `padding: 0.5em` | Relatif ke font elemen itu — hati-hati efek berantai |
| `%` | `width: 50%` | Relatif terhadap parent |
| `vw`/`vh` | `min-height: 100vh` | Relatif viewport — hero section setinggi layar |

Warna:

```css
color: #0ea5e9;                  /* hex — paling umum */
color: #0ea5e980;                /* hex + alpha */
color: rgb(14 165 233);          /* rgb */
color: rgba(0, 0, 0, 0.5);       /* rgb + transparansi */
color: hsl(199 89% 48%);         /* hue-saturation-lightness: mudah diatur terang/gelap */
```

**Kontras**: teks harus terbaca — rasio kontras minimal 4.5:1 (WCAG AA).
Abu terang di atas putih (`#ccc` on `#fff`) tidak lolos.

---

## 6. Tipografi

Empat properti menentukan sebagian besar kenyamanan baca:

```css
body {
  font-family: "Inter", system-ui, sans-serif; /* selalu beri fallback */
  font-size: 1rem;
  line-height: 1.6;        /* tanpa unit = kelipatan font-size; 1.5–1.7 ideal */
  color: #1f2937;
}

h1 { font-size: 2rem; font-weight: 700; letter-spacing: -0.02em; }

.badge   { text-transform: uppercase; }
.tautan  { text-decoration: underline; }
.tengah  { text-align: center; }
```

Mengapa `line-height` tanpa unit? Nilai `1.6` diwariskan sebagai *faktor*
sehingga setiap elemen menghitung dari font-nya sendiri; `24px` diwariskan
mentah dan merusak heading besar.

---

## 7. Pseudo-class: state interaktif

Pseudo-class memilih elemen berdasarkan **keadaannya** — bukan atributnya.

```css
.tombol {
  background: #0ea5e9;
  color: white;
  /* transition ditaruh di state NORMAL agar berlaku dua arah */
  transition: background 150ms ease, transform 150ms ease;
}

.tombol:hover  { background: #0284c7; transform: translateY(-1px); }
.tombol:active { transform: translateY(0); }

/* Fokus keyboard: JANGAN dihilangkan, ganti dengan yang lebih jelas */
.tombol:focus-visible {
  outline: 3px solid #38bdf8;
  outline-offset: 2px;
}

/* State form */
input:focus    { border-color: #0ea5e9; }
input:invalid  { border-color: #ef4444; }
input:disabled { opacity: 0.5; cursor: not-allowed; }

/* Struktur */
li:first-child     { font-weight: bold; }
li:nth-child(odd)  { background: #f8fafc; }   /* zebra table! */
a:visited          { color: purple; }
```

Aturan aksesibilitas yang sering dilanggar: `outline: none` tanpa pengganti
membuat pengguna keyboard tidak tahu posisi fokus. Pakai `:focus-visible`
dengan outline khusus — hanya muncul untuk navigasi keyboard, tidak saat klik.

`::before`/`::after` (dua titik dua) adalah **pseudo-element** — membuat konten
tambahan, beda kategori dengan pseudo-class (satu titik dua, memilih state).

---

## 8. Contoh utuh: kartu profil

Persis pola bab `01-kartu-profil` di praktikum:

```css
* { box-sizing: border-box; }

body {
  margin: 0;
  font-family: system-ui, sans-serif;
  background: #f1f5f9;
  min-height: 100vh;
  display: flex;                 /* menengahkan kartu (detail di Modul 03) */
  justify-content: center;
  align-items: center;
}

.kartu {
  width: min(360px, 90vw);       /* tak pernah lebih lebar dari layar */
  background: white;
  padding: 32px;
  border: 1px solid #e2e8f0;
  border-radius: 16px;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.08);
  text-align: center;
}

.kartu img {
  width: 96px;
  height: 96px;
  border-radius: 50%;            /* lingkaran */
  object-fit: cover;             /* crop rapi, tidak gepeng */
}

.kartu h1 { font-size: 1.5rem; margin: 16px 0 4px; }
.kartu p  { color: #64748b; margin: 0 0 24px; }

.kartu .tombol {
  display: inline-block;
  padding: 10px 24px;
  background: #0ea5e9;
  color: white;
  border-radius: 8px;
  text-decoration: none;
  transition: background 150ms ease;
}
.kartu .tombol:hover         { background: #0284c7; }
.kartu .tombol:focus-visible { outline: 3px solid #7dd3fc; outline-offset: 2px; }
```

Perilaku yang diharapkan: kartu putih di tengah layar, foto bulat, tombol
berubah warna saat hover, dan cincin fokus terlihat saat Tab.

---

## 9. Kesalahan umum

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | Menumpuk `!important` | Konflik gaya tak terkendali | Perbaiki specificity/urutan |
| 2 | Lupa `box-sizing: border-box` | Lebar meledak saat diberi padding | Reset universal di baris pertama |
| 3 | Selector terlalu dalam | Rapuh saat HTML berubah | Class langsung di target |
| 4 | `font-size` semua dalam `px` | Mengabaikan setelan pengguna | `rem` untuk teks |
| 5 | Styling pakai ID | Sulit dioverride | Class untuk styling |
| 6 | `outline: none` tanpa ganti | Navigasi keyboard buta | `:focus-visible` + outline custom |
| 7 | Layout pakai margin manual | Rapuh, tidak responsif | Flexbox/grid (Modul 03) |
| 8 | Lupa fallback font | Tampilan kacau jika font gagal | `..., system-ui, sans-serif` |

---

## 10. Cheatsheet

```css
/* Reset minimal */
* { box-sizing: border-box; }
body { margin: 0; font-family: system-ui, sans-serif; line-height: 1.6; }

/* Specificity: inline > #id (1,0,0) > .class/:hover (0,1,0) > elemen (0,0,1) */
/* Skor sama → rule terakhir menang. Hindari !important. */

/* Box model */
padding: 8px 16px;        /* v | h */
margin: 0 auto;           /* tengah horizontal (elemen ber-width) */
border: 1px solid #e2e8f0;
border-radius: 12px;
box-shadow: 0 4px 12px rgba(0,0,0,0.08);

/* Unit: rem = teks/spacing, px = detail, % = relatif parent, vh = layar */

/* Tipografi */
font-family: "Inter", system-ui, sans-serif;
font-size: 1rem;  line-height: 1.6;  font-weight: 700;

/* State */
.btn:hover { ... }
.btn:focus-visible { outline: 3px solid ...; outline-offset: 2px; }
input:invalid { border-color: red; }
li:nth-child(odd) { ... }
transition: background 150ms ease;
```

## Lanjut ke praktikum

Kerjakan berurutan di [`../../1-pembelajaran/02-css-dasar/`](../../1-pembelajaran/02-css-dasar/):

1. `01-kartu-profil` — pasang CSS + styling dasar (bagian 1, 8).
2. `02-selector-specificity` — cascade & specificity (bagian 2–3).
3. `03-box-model` — padding/border/margin/box-sizing (bagian 4).
4. `04-pseudo-class` — hover/focus/state form (bagian 7).

Lalu uji diri dengan [`../../3-latihan-soal/02-css-dasar/soal.md`](../../3-latihan-soal/02-css-dasar/soal.md).
