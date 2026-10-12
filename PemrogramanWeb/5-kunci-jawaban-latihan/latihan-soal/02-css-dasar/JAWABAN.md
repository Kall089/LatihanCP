# Jawaban 02 — CSS Dasar

---

## A. Konsep

### A1 — b

Class reusable, specificity rendah yang sehat. ID unik (anchor/JS); styling
pakai ID menyulitkan override. Satu `id` tidak boleh diulang di banyak
elemen. Tailwind tetap class, bukan id.

### A2

Warna **merah**. Specificity: `p` = `(0,0,1)`, `.merah` = `(0,1,0)`, `p`
kedua tetap `(0,0,1)`. Class mengalahkan elemen meski rule elemen ditulis
kemudian. "Yang terakhir menang" hanya berlaku jika skor **sama**.

### A3

A `#header .menu` = `(1,1,0)` menang atas B `(0,0,2)` dan C `(0,0,1)`.
Teks **hijau**. Satu ID mengalahkan berapa pun selector elemen.

### A4

`!important` memotong cascade; konflik jadi perang spesifisitas yang tidak
bisa ditebak. Perbaiki urutan/specificity. Pengecualian langka: override
gaya pihak ketiga yang tidak bisa kamu ubah, atau utility sadar
(`.sr-only`). Bukan untuk "supaya menang".

### A5

`content-box`: lebar total = 300 + 24×2 + 2×2 = **352px**.
`border-box`: `width` sudah termasuk padding+border → **300px**, content
menyusut.

### A6 — b

Margin = jarak antar kotak (di luar border). Padding = ruang dalam.
Keduanya tetap ada di `border-box`; yang berubah hanya bagaimana `width`
dihitung.

### A7

Menurun: properti teks (`color`, `font-family`, `font-size`, `line-height`).
Tidak menurun: kotak (`margin`, `padding`, `border`, `width`). Karena
`font-family` diwariskan, set di `body` merambat ke hampir semua elemen
teks kecuali yang menimpa.

### A8

`width` pada `inline` **diabaikan**. Perbaikan terkecil: `display:
inline-block` (tetap dalam alur teks, `width`/`height` dipatuhi). `block`
juga mematuhi width tapi memaksa baris baru.

### A9 — b

External: satu file banyak halaman, cache, separation of concerns,
specificity tidak meledak seperti inline (inline = 1,0,0,0). Nama file
bebas, bukan harus `style.css`.

### A10

`outline: none` tanpa ganti = pengguna keyboard tidak tahu fokus. `:focus`
muncul juga saat klik mouse (kadang mengganggu desain). `:focus-visible`
hampir hanya navigasi keyboard, bisa dipasang outline/ring yang jelas
bersama `:hover` untuk mouse.

---

## B. Praktik

### B1

```css
.kartu {
  padding: 24px;
  border: 1px solid #e2e8f0;
  border-radius: 12px;
}
.kartu--unggul {
  border-color: #0ea5e9;
}
```

### B2

```css
.chip {
  box-sizing: border-box;
  width: 160px;
  padding: 12px;
  border: 1px solid #cbd5e1;
}
```

Tanpa `border-box`, lebar visual = 160+24+2.

### B3

```css
.tombol {
  background: #0ea5e9;
  color: #fff;
  border: 0;
  padding: 10px 20px;
  border-radius: 8px;
  transition: background 150ms ease;
}
.tombol:hover { background: #0284c7; }
.tombol:focus-visible {
  outline: 3px solid #38bdf8;
  outline-offset: 2px;
}
```

`transition` di state normal agar animasi jalan dua arah (masuk dan keluar
hover).
