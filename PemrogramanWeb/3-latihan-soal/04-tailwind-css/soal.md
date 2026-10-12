# Latihan Soal 04 — Tailwind CSS

Kerjakan tanpa kunci. Materi:
[`../../0-materi/04-tailwind-css/teori.md`](../../0-materi/04-tailwind-css/teori.md).

---

## A. Soal konsep (10)

### A1. Pilihan ganda — utility-first

Utility-first berbeda dari CSS tradisional karena…

- a. Tidak memakai class sama sekali.
- b. Gaya dirangkai dari class kecil satu-tugas di markup, bukan nama komponen di file CSS.
- c. Sama dengan inline `style=""` termasuk `hover` dan media query.
- d. Menghapus kebutuhan memahami flexbox.

### A2. Prediksi terjemahan

Tuliskan CSS setara (kira-kira) untuk:

```html
<div class="flex items-center justify-between gap-4 p-6 bg-white rounded-xl shadow">
```

### A3. Esai — bukan inline style

Berikan **dua** kemampuan Tailwind yang tidak dimiliki `style="color: red"`.

### A4. Pilihan ganda — skala spacing

`p-4` pada default Tailwind berarti…

- a. `padding: 4px`
- b. `padding: 1rem` (16px, karena 1 unit = 0.25rem = 4px, 4×4px)
- c. `padding: 4rem`
- d. `padding: 4%`

### A5. Prediksi responsive

```html
<section class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
```

Berapa kolom pada 360px, 800px, dan 1300px? Ingat: tanpa prefix = mobile;
`md` = 768px; `lg` = 1024px.

### A6. Esai — CDN vs build

Mengapa `cdn.tailwindcss.com` boleh untuk praktikum/studi kasus dashboard,
tetapi **tidak** untuk produksi Next.js? Sebut ukuran CSS dan scanner class.

### A7. Prediksi — class dinamis

```jsx
<div className={`bg-${warna}-500`}>
```

Apa yang terjadi saat `npm run build` (Tailwind JIT)? Bagaimana menulis
varian merah/biru dengan benar?

### A8. Pilihan ganda — state

Class untuk "saat di-hover, latar lebih gelap" pada tombol `bg-sky-600` adalah…

- a. `onHover:bg-sky-700`
- b. `hover:bg-sky-700`
- c. `:hover-bg-sky-700`
- d. `bg-sky-600-hover`

### A9. Esai — `hidden md:block`

Jelaskan perilaku elemen dengan class itu di HP vs tablet. Kaitkan dengan
mobile-first Modul 03.

### A10. Prediksi `mx-auto`

```html
<div class="w-full max-w-4xl mx-auto">
```

Apa yang terjadi pada layar 500px dan 1400px?

---

## B. Soal praktik kecil (3)

### B1. Kartu utility

Tulis satu `<article>` Tailwind: latar putih, padding `p-5`, `rounded-2xl`,
`shadow-sm`, judul `text-xl font-bold`, deskripsi `text-slate-600`, tombol
`bg-sky-600 text-white` dengan `hover:bg-sky-700` dan `transition`.

### B2. Grid responsif

Container tiga kartu: 1 kolom HP, 2 kolom `sm`, 3 kolom `lg`, `gap-6`.

### B3. Fokus aksesibel

Tambahkan pada tombol: `focus-visible:outline-none focus-visible:ring-2
focus-visible:ring-sky-400 focus-visible:ring-offset-2`. Jelaskan dalam
komentar HTML mengapa `focus-visible` dipilih, bukan menghapus outline
untuk semua fokus.
