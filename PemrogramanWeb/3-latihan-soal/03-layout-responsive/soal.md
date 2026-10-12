# Latihan Soal 03 — Layout Responsif

Kerjakan tanpa kunci. Materi:
[`../../0-materi/03-layout-responsive/teori.md`](../../0-materi/03-layout-responsive/teori.md).
Konsep slide yang diuji: **main vs cross axis**, **media query 768px**,
flex vs grid, mobile-first.

---

## A. Soal konsep (10)

### A1. Pilihan ganda — dua sumbu

Pada `display: flex` dengan `flex-direction: row` (default),
`justify-content` mengatur posisi di…

- a. Cross axis (tegak lurus baris).
- b. Main axis (searah baris, kiri → kanan pada mode LTR).
- c. Kedua axis sekaligus.
- d. Hanya jika ada `align-items: center`.

### A2. Prediksi — column menukar sumbu

```css
.hero {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: flex-end;
  min-height: 100vh;
}
```

Ke mana item digeser secara **vertikal**, dan ke mana secara **horizontal**?
Jelaskan dengan menyebut mana yang jadi main axis.

### A3. Esai — kapan flex, kapan grid

Berikan satu contoh UI yang lebih cocok flexbox dan satu yang lebih cocok
grid. Kunci jawaban yang dinilai: siapa yang menentukan ukuran (konten vs
layout) dan jumlah dimensi (1 vs 2).

### A4. Prediksi — navbar

```css
.navbar {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
```

Logo adalah anak pertama, menu anak kedua. Apa layout yang terjadi?
Mengapa `align-items: center` tidak menaruh logo di tengah **horizontal**?

### A5. Pilihan ganda — media query 768px

Dalam pendekatan **mobile-first**, rule berikut berarti…

```css
.galeri { display: grid; grid-template-columns: 1fr; }
@media (min-width: 768px) {
  .galeri { grid-template-columns: repeat(2, 1fr); }
}
```

- a. HP (< 768px) dua kolom; tablet ke atas satu kolom.
- b. Gaya dasar (termasuk HP) satu kolom; layar **≥ 768px** (tablet portrait ke atas) dua kolom.
- c. Tepat 768px saja yang dua kolom; 767 dan 769 kembali satu kolom.
- d. 768px adalah `max-width`, jadi desktop yang satu kolom.

### A6. Esai — viewport meta

Apa yang terjadi di HP jika `<meta name="viewport" content="width=device-width, initial-scale=1.0">`
dihilangkan, meski media query 768px sudah ditulis? Kaitkan dengan Modul 01.

### A7. Prediksi grid

```css
.produk {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  gap: 20px;
}
```

Tanpa media query, kira-kira berapa kolom pada viewport 400px, 800px, dan
1200px? Jelaskan cara baca `minmax`.

### A8. Pilihan ganda — `gap`

Mengapa `gap` pada flex/grid biasanya lebih rapi daripada `margin-right`
pada tiap item?

- a. `gap` diwariskan ke cucu.
- b. `gap` hanya jarak **antar** item, tidak menyisakan margin di tepi yang harus di-reset `:last-child`.
- c. `margin` tidak bekerja di flex item.
- d. `gap` menonaktifkan wrapping.

### A9. Esai — urutan breakpoint

Mengapa menulis `@media (min-width: 1024px)` **sebelum**
`@media (min-width: 640px)` untuk properti yang sama bisa membuat tablet
"salah kolom"? Ingat cascade: skor sama → yang terakhir menang.

### A10. Prediksi `fr`

`grid-template-columns: 2fr 1fr` pada container 900px tanpa gap. Lebar
kolom pertama dan kedua?

---

## B. Soal praktik kecil (3)

### B1. Sumbu flex

Buat `.toolbar` berisi tiga tombol dalam satu baris, rata kiri-kanan
(`space-between`), tegak tengah di cross axis, `gap: 12px`.

### B2. Mobile-first 768px

`.kartu-grid` satu kolom di HP. Mulai **768px** menjadi dua kolom sama
lebar. Pakai `min-width` (bukan `max-width`).

### B3. Kerangka halaman grid

Layout: header penuh, sidebar 240px + konten `1fr`, footer penuh. Pakai
`grid-template-areas`. Tambahkan media query ≤768px (atau mobile-first:
dasar satu kolom, `md` dua kolom) agar sidebar di atas konten, bukan
terjepit.
