# Modul 03 — Layout Responsif: Flexbox, Grid, Media Query

> Praktikum terkait: [`../../1-pembelajaran/03-layout-responsive/`](../../1-pembelajaran/03-layout-responsive/)
> (3 bab: flexbox, CSS grid, layout responsif).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menjelaskan konsep dua sumbu flexbox dan memakai `justify-content` /
  `align-items` tanpa tertukar.
- Menyusun grid dengan `fr`, `repeat()`, `minmax()`, dan `grid-template-areas`.
- Memilih flexbox vs grid dengan alasan yang bisa dipertanggungjawabkan.
- Menulis media query mobile-first yang konsisten.
- Men-debug masalah layout klasik: overflow, sumbu tertukar, breakpoint bentrok.

---

## 1. Mengapa butuh sistem layout?

Sebelum flexbox/grid, layout dibuat dengan `float` dan margin manual — rapuh
dan menyakitkan. Masalah mendasarnya: **ukuran layar pengguna tidak bisa kamu
kontrol** (320px HP lawas sampai 3440px ultrawide). Layout modern harus
*mengalir*: elemen menata diri berdasarkan aturan, bukan koordinat tetap.

Dua sistem modern yang saling melengkapi:

- **Flexbox** — satu dimensi (baris **atau** kolom). Konten menentukan ukuran.
- **Grid** — dua dimensi (baris **dan** kolom). Layout menentukan ukuran.

Plus **media query** untuk mengubah aturan pada ukuran layar berbeda.

---

## 2. Flexbox

Aktifkan pada **container** — anak-anak langsungnya otomatis jadi *flex item*:

```css
.container { display: flex; }
```

### Dua sumbu — konsep paling penting

```text
flex-direction: row (default)

        main axis ────────────────────▶
  ┌────────────────────────────────────┐
  │  ┌─────┐  ┌─────┐  ┌─────┐         │   cross
  │  │  1  │  │  2  │  │  3  │         │   axis
  │  └─────┘  └─────┘  └─────┘         │    │
  └────────────────────────────────────┘    ▼

  justify-content → mengatur posisi di MAIN axis
  align-items     → mengatur posisi di CROSS axis
```

**`flex-direction: column` menukar kedua sumbu**: main axis menjadi vertikal,
sehingga `justify-content` mengatur posisi **vertikal**. Ini jebakan ujian
nomor satu.

### Properti container

| Properti | Nilai umum | Fungsi |
|---|---|---|
| `flex-direction` | `row` / `column` | Arah main axis |
| `justify-content` | `flex-start`, `center`, `space-between`, `space-around`, `space-evenly` | Distribusi di main axis |
| `align-items` | `stretch` (default), `center`, `flex-start`, `flex-end` | Posisi di cross axis |
| `gap` | `16px` | Jarak antar item (tanpa margin!) |
| `flex-wrap` | `wrap` | Item boleh turun baris |

### Properti item

| Properti | Contoh | Fungsi |
|---|---|---|
| `flex-grow` | `1` | Porsi mengisi ruang sisa |
| `flex-shrink` | `0` | Boleh menyusut atau tidak |
| `flex-basis` | `240px` | Ukuran awal sebelum grow/shrink |
| `flex` (shorthand) | `flex: 1` = `1 1 0` | Berbagi ruang sama rata |
| `align-self` | `center` | Override align-items untuk satu item |
| `order` | `-1` | Ubah urutan visual |

### Tiga pola sehari-hari

```css
/* 1. Navbar: logo kiri, menu kanan, semuanya setinggi sama */
.navbar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 16px;
}

/* 2. Centering sempurna (horizontal + vertikal) */
.hero {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
}

/* 3. Sidebar tetap + konten mengisi sisa */
.layout  { display: flex; }
.sidebar { flex: 0 0 240px; }   /* tidak grow, tidak shrink, 240px */
.konten  { flex: 1; }           /* ambil semua sisa */
```

Mengapa `gap` lebih baik daripada `margin-right` per item? `gap` hanya memberi
jarak **antar** item — tidak ada margin sisa di tepi kanan/kiri yang harus
di-reset dengan `:last-child`.

---

## 3. CSS Grid

Aktifkan pada container, definisikan kolom (dan opsional baris):

```css
.galeri {
  display: grid;
  grid-template-columns: repeat(3, 1fr);   /* 3 kolom sama lebar */
  gap: 20px;
}
```

### Unit `fr` dan fungsi penting

- **`fr`** (*fraction*) = pecahan ruang tersisa. `2fr 1fr` = kolom pertama
  dua kali kolom kedua.
- **`repeat(n, x)`** = tulis `x` sebanyak `n` kali.
- **`minmax(min, max)`** = kolom minimal `min`, maksimal `max`.
- **`auto-fit`** = jumlah kolom menyesuaikan lebar container.

Kombinasi legendaris — **grid responsif tanpa media query**:

```css
.produk {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  gap: 20px;
}
```

Cara membacanya: "buat kolom sebanyak mungkin, masing-masing minimal 250px;
sisa ruang dibagi rata". Layar 800px → 3 kolom; layar 500px → 2 kolom;
HP → 1 kolom. Otomatis.

### Penempatan: span dan area

```css
.item-lebar { grid-column: span 2; }      /* melebar 2 kolom */
.item-tinggi { grid-row: 1 / 3; }         /* dari garis 1 ke 3 = 2 baris */
```

`grid-template-areas` — menggambar layout langsung di CSS:

```css
.halaman {
  display: grid;
  grid-template-columns: 240px 1fr;
  min-height: 100vh;
  grid-template-areas:
    "header header"        /*  ┌────────────────────┐  */
    "sidebar konten"       /*  │       header       │  */
    "footer footer";       /*  ├────────┬───────────┤  */
}                          /*  │sidebar │  konten   │  */
.header  { grid-area: header; }  /* │    │           │  */
.sidebar { grid-area: sidebar; } /* ├────┴───────────┤  */
.konten  { grid-area: konten; }  /* │     footer     │  */
.footer  { grid-area: footer; }  /* └────────────────┘  */
```

Nama area bebas, syaratnya tiap area membentuk persegi panjang utuh.

### Flexbox vs Grid — keputusan yang harus bisa kamu jelaskan

| Pertanyaan | Flexbox | Grid |
|---|---|---|
| Dimensi | 1 (baris ATAU kolom) | 2 (baris DAN kolom) |
| Siapa menentukan ukuran? | Konten | Layout |
| Kasus khas | Navbar, deret tombol, meta info | Kerangka halaman, galeri, dashboard |
| Responsif tanpa media query | `flex-wrap` (kasar) | `auto-fit + minmax` (presisi) |
| Penempatan presisi | Tidak | `grid-area`, span |

Praktik umum: **grid untuk kerangka halaman, flexbox untuk isi tiap bagian.**
Contoh: halaman = grid (header/sidebar/konten/footer), navbar di dalam header =
flexbox.

---

## 4. Media query & mobile-first

### Viewport meta — prasyarat mutlak

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

Tanpanya, browser HP mensimulasikan layar 980px lalu men-zoom-out — semua
media query-mu salah tembak. Sudah dibahas di Modul 01; di sinilah alasannya.

### Mobile-first dengan `min-width`

Filosofi: **gaya dasar = layar terkecil**, lalu *tambahkan* aturan saat layar
membesar. Mengapa? (1) mayoritas trafik dari HP; (2) gaya dasar jadi paling
sederhana; (3) aturan `min-width` menumpuk rapi tanpa saling membatalkan.

```css
/* Dasar (mobile): 1 kolom — TANPA media query */
.galeri {
  display: grid;
  grid-template-columns: 1fr;
  gap: 16px;
}

/* Tablet ke atas (≥640px): 2 kolom */
@media (min-width: 640px) {
  .galeri { grid-template-columns: repeat(2, 1fr); }
}

/* Desktop (≥1024px): 3 kolom */
@media (min-width: 1024px) {
  .galeri { grid-template-columns: repeat(3, 1fr); }
}
```

Di layar 1200px, **ketiga** rule cocok — yang terakhir (paling spesifik untuk
layar besar) menang karena urutan penulisan. Itulah mengapa urutan breakpoint
harus naik: 640 → 1024, jangan dibalik.

### Breakpoint standar (selaras Tailwind, Modul 04)

| Nama | `min-width` | Target umum |
|---|---|---|
| (dasar) | — | HP portrait |
| `sm` | 640px | HP landscape |
| `md` | 768px | Tablet portrait |
| `lg` | 1024px | Laptop |
| `xl` | 1280px | Desktop |
| `2xl` | 1536px | Layar lebar |

Breakpoint dipilih berdasarkan **kapan layout terlihat rusak**, bukan
berdasarkan daftar perangkat. Angka di atas hanyalah konvensi awal yang baik.

### Pola responsif pelengkap

```css
/* Gambar tidak pernah meluber */
img { max-width: 100%; height: auto; }

/* Konten dibatasi dan di tengah */
.wadah { max-width: 1100px; margin: 0 auto; padding: 0 16px; }

/* Sembunyikan menu desktop di HP (pasangan hamburger) */
.menu-desktop { display: none; }
@media (min-width: 768px) {
  .menu-desktop { display: flex; }
}
```

---

## 5. Contoh utuh: landing page mini

Menggabungkan semuanya — pola yang sama dengan studi kasus
`4-studi-kasus/01-landing-page-umkm`:

```css
* { box-sizing: border-box; }
body { margin: 0; font-family: system-ui, sans-serif; }

/* Header: flexbox */
.header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 16px 24px;
}
.nav { display: flex; gap: 24px; }

/* Hero: flexbox centering */
.hero {
  min-height: 60vh;
  display: flex;
  flex-direction: column;      /* main axis kini VERTIKAL */
  justify-content: center;     /* → menengahkan secara vertikal */
  align-items: center;         /* → horizontal */
  text-align: center;
  padding: 24px;
}

/* Galeri menu: grid responsif otomatis */
.menu-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
  gap: 20px;
  max-width: 1100px;
  margin: 0 auto;
  padding: 24px;
}

/* Footer 3 kolom → 1 kolom di HP (mobile-first) */
.footer-grid {
  display: grid;
  grid-template-columns: 1fr;
  gap: 24px;
}
@media (min-width: 768px) {
  .footer-grid { grid-template-columns: repeat(3, 1fr); }
}
```

Perilaku yang diharapkan: di HP semua satu kolom; menu menyusun diri 1→2→3–4
kolom seiring layar melebar; hero selalu di tengah; tidak ada scroll
horizontal pada lebar berapa pun.

---

## 6. Debugging layout

1. **DevTools → toggle device toolbar** (ikon HP) untuk menguji 360px, 768px,
   1280px.
2. Inspect elemen → badge `flex`/`grid` di panel Elements bisa diklik —
   browser menggambar garis bantunya.
3. Overflow horizontal misterius? Cari pelakunya:

```css
* { outline: 1px solid red; }   /* sementara — lihat kotak siapa yang bocor */
```

4. Item grid/flex meluber teks panjang? Tambahkan `min-width: 0` pada item
   atau ganti `1fr` menjadi `minmax(0, 1fr)` (default `min-width: auto`
   mencegah item menyusut di bawah ukuran kontennya).

---

## 7. Kesalahan umum

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | Lupa viewport meta | Media query "tidak jalan" di HP | Cek `<head>` dulu sebelum debug CSS |
| 2 | Width tetap (`width: 900px`) | Scroll horizontal di HP | `max-width: 900px; width: 100%` |
| 3 | `justify`/`align` tertukar saat `column` | Elemen "tidak mau ke tengah" | Ingat: direction menukar sumbu |
| 4 | Campur `min-width` & `max-width` | Aturan saling bertabrakan | Konsisten mobile-first |
| 5 | Jarak antar kolom pakai margin | Sisa margin di tepi, rapuh | `gap` di container |
| 6 | Gambar tanpa `max-width: 100%` | Meluber keluar kolom | Set global sejak awal |
| 7 | Breakpoint per perangkat spesifik | Terlalu banyak query | Breakpoint saat layout rusak |

---

## 8. Cheatsheet

```css
/* FLEXBOX */
.row {
  display: flex;
  flex-direction: row;             /* atau column (sumbu tertukar!) */
  justify-content: space-between;  /* main axis */
  align-items: center;             /* cross axis */
  gap: 16px;
  flex-wrap: wrap;
}
.isi-sisa { flex: 1; }
.tetap    { flex: 0 0 240px; }

/* CENTERING */
.center { display: flex; justify-content: center; align-items: center; }

/* GRID */
.grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 20px;
}
.grid-responsif {
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
}
.lebar-2 { grid-column: span 2; }

/* MEDIA QUERY — mobile-first, urutan naik */
@media (min-width: 640px)  { ... }
@media (min-width: 768px)  { ... }
@media (min-width: 1024px) { ... }

/* Anti-overflow */
img { max-width: 100%; height: auto; }
.wadah { max-width: 1100px; margin: 0 auto; }
```

## Lanjut ke praktikum

Kerjakan berurutan di [`../../1-pembelajaran/03-layout-responsive/`](../../1-pembelajaran/03-layout-responsive/):

1. `01-flexbox` — dua sumbu, justify/align, gap (bagian 2).
2. `02-css-grid` — fr, repeat, minmax, area (bagian 3).
3. `03-layout-responsif` — media query mobile-first (bagian 4–5).

Lalu uji diri dengan [`../../3-latihan-soal/03-layout-responsive/soal.md`](../../3-latihan-soal/03-layout-responsive/soal.md).
