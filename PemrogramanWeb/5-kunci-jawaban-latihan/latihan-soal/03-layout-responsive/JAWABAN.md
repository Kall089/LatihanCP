# Jawaban 03 — Layout Responsif

---

## A. Konsep

### A1 — b

`justify-content` = distribusi di **main axis**. Default `row` → main axis
horizontal.

### A2

`flex-direction: column` membuat main axis **vertikal**. Jadi
`justify-content: center` menengahkan **vertikal**; `align-items: flex-end`
menggeser ke ujung **cross axis** = kanan (horizontal, LTR). Ini jebakan
ujian nomor satu: orang mengira `justify` selalu kiri-kanan.

### A3

Flex: navbar, deret tombol, meta (satu dimensi, ukuran mengikuti konten).
Grid: kerangka halaman, galeri, dashboard (dua dimensi, layout menentukan
track). Praktik umum: grid untuk kerangka, flex untuk isi bagian.

### A4

Logo kiri, menu kanan, tinggi item di-center di cross axis (vertikal pada
row). `align-items` **bukan** sumbu kiri-kanan pada `row`. Tengahkan
horizontal pakai `justify-content: center` (tapi itu menumpuk semua ke
tengah, bukan space-between).

### A5 — b

Mobile-first: tanpa prefix/media = HP 1 kolom. `min-width: 768px` = dari
tablet portrait ke atas 2 kolom. Bukan hanya tepat 768. `min-width` bukan
`max-width`.

### A6

HP mensimulasikan lebar ~980px lalu zoom-out. Media query 768px "sudah
cocok" padahal fisiknya 360px — layout desktop dipaksa ke layar sempit.
Viewport meta (Modul 01) wajib agar 1 CSS pixel ≈ 1 device pixel lebar.

### A7

`minmax(250px, 1fr)`: kolom minimal 250px, maksimal bagi rata sisa.
`auto-fit`: sebanyak mungkin track yang muat. ~400px → 1 kolom; ~800px → 3
(3×250=750); ~1200px → 4. Angka persis tergantung gap; yang dinilai cara
baca, bukan pixel eksak.

### A8 — b

`gap` hanya antar item. Margin kanan pada setiap kartu menyisakan lubang di
item terakhir kecuali di-reset.

### A9

Pada layar 1100px, **kedua** `min-width` cocok. Yang ditulis **terakhir**
menang jika specificity sama. Jika 1024 ditulis sebelum 640, rule 640
menimpa desktop jadi 2 kolom. Urutkan breakpoint naik.

### A10

Sisa 900px dibagi 3 bagian: `2fr` = 600px, `1fr` = 300px.

---

## B. Praktik

### B1

```css
.toolbar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 12px;
}
```

### B2

```css
.kartu-grid {
  display: grid;
  grid-template-columns: 1fr;
  gap: 16px;
}
@media (min-width: 768px) {
  .kartu-grid { grid-template-columns: 1fr 1fr; }
}
```

### B3

```css
.halaman {
  display: grid;
  min-height: 100vh;
  grid-template-areas:
    "header"
    "sidebar"
    "konten"
    "footer";
}
@media (min-width: 768px) {
  .halaman {
    grid-template-columns: 240px 1fr;
    grid-template-areas:
      "header header"
      "sidebar konten"
      "footer footer";
  }
}
.header  { grid-area: header; }
.sidebar { grid-area: sidebar; }
.konten  { grid-area: konten; }
.footer  { grid-area: footer; }
```
