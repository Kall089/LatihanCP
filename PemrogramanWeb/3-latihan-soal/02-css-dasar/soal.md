# Latihan Soal 02 — CSS Dasar

Kerjakan tanpa membuka kunci. Materi:
[`../../0-materi/02-css-dasar/teori.md`](../../0-materi/02-css-dasar/teori.md).
Beberapa butir menyinggung fondasi layout yang muncul di slide dosen
(class vs id, cascade, box model) agar bentrok rule bisa kamu prediksi
sebelum Modul 03.

---

## A. Soal konsep (10)

### A1. Pilihan ganda — class vs id

Mana praktik yang **paling tepat** untuk styling?

- a. Pakai `id` untuk semua komponen karena specificity tinggi = "lebih kuat, lebih baik".
- b. Pakai `class` untuk hampir semua styling; `id` untuk anchor/JS (unik per halaman).
- c. `class` dan `id` boleh dipakai bergantian pada banyak elemen yang sama.
- d. Styling lewat `id` wajib di Tailwind.

### A2. Prediksi cascade — siapa yang menang?

```css
p { color: black; }
.merah { color: red; }
p { color: blue; }
```

```html
<p class="merah">Teks</p>
```

Warna teks akhir? Jelaskan memakai skor specificity `(ID, CLASS, ELEMEN)`,
bukan "yang terakhir selalu menang".

### A3. Prediksi specificity

Skor mana yang lebih tinggi, dan warna apa yang tampil?

```css
#header .menu { color: green; }   /* A */
nav a { color: orange; }          /* B */
a { color: navy; }                /* C */
```

```html
<header id="header">
  <nav>
    <a class="menu" href="/">Beranda</a>
  </nav>
</header>
```

### A4. Esai — `!important`

Mengapa menumpuk `!important` adalah tanda arsitektur CSS yang sakit?
Kapan (kalau pernah) ia masih bisa dibenarkan?

### A5. Prediksi box model — `content-box`

```css
.kartu {
  width: 300px;
  padding: 24px;
  border: 2px solid black;
}
```

Jika `box-sizing` default browser (`content-box`), berapa lebar total
kotak di layar? Tulis hitungan. Berapa lebar total jika `border-box`?

### A6. Pilihan ganda — box model

Margin berbeda dari padding karena…

- a. Margin ada di dalam border; padding di luar.
- b. Margin adalah jarak **antar** elemen (transparan); padding adalah ruang napas **di dalam** border.
- c. Keduanya sama; hanya nama yang berbeda di Flexbox.
- d. Padding tidak memengaruhi elemen dengan `box-sizing: border-box`.

### A7. Esai — inheritance

Properti mana yang **menurun** ke anak (`color`, `font-family`, …) dan mana
yang **tidak** (`margin`, `padding`, …)? Mengapa `body { font-family: ... }`
cukup sekali untuk hampir seluruh halaman?

### A8. Prediksi — `display: inline`

```css
span.badge {
  width: 200px;
  padding: 8px;
  background: gold;
}
```

```html
<span class="badge">Baru</span>
```

Apakah lebar 200px diterapkan? Mengapa? Perbaikan CSS apa yang paling
kecil untuk membuat `width` dipatuhi tanpa memaksa pindah baris baru
seperti `block`?

### A9. Pilihan ganda — memasang CSS

Mengapa praktikum memakai `<link rel="stylesheet" href="style.css">`
(external), bukan inline `style="..."`?

- a. Inline tidak bisa mengubah warna.
- b. External reusable, bisa di-cache, specificity lebih sehat, memisahkan tanggung jawab.
- c. File CSS wajib bernama `style.css` menurut HTML5.
- d. External selalu kalah dari selector elemen, jadi lebih aman.

### A10. Esai — `:hover` vs `:focus-visible`

Mengapa `outline: none` tanpa pengganti berbahaya? Apa kelebihan
`:focus-visible` dibanding `:focus` untuk tombol yang juga punya `:hover`?

---

## B. Soal praktik kecil (3)

### B1. Class, bukan id

Diberi HTML dua kartu testimoni. Tulis CSS yang menata **keduanya** lewat
class `.kartu` (padding, border, radius). Jangan pakai `#kartu1`. Tambah
modifier `.kartu--unggul` yang hanya mengubah `border-color`.

### B2. Hitung dan perbaiki box model

Elemen `.chip` harus **tepat** 160px di layar, termasuk padding 12px dan
border 1px. Tulis rule lengkap (`box-sizing` + `width` + `padding` +
`border`).

### B3. State tombol aksesibel

Styling `.tombol` dengan latar `#0ea5e9`, `:hover` lebih gelap, `transition`
di state normal, dan `:focus-visible` ber-outline 3px. Jangan hapus outline
tanpa pengganti.
