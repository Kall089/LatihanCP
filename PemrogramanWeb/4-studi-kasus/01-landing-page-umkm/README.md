# Studi Kasus 01 — Landing Page UMKM

Bangun satu halaman pemasaran untuk UMKM fiktif (contoh: Warung Kopi Senja,
Toko Sambal Bu Rini, atau ide sendiri). **Tanpa JavaScript.** Bekal: HTML
semantik + CSS layout responsif (Modul 01–03).

Kunci (jangan dibuka dulu):
`../../5-kunci-jawaban-latihan/studi-kasus/01-landing-page-umkm/`

## Yang harus ada

1. **Header + nav** — nama usaha, tautan ke section (`#menu`, `#tentang`,
   `#lokasi`, `#kontak`).
2. **Hero** — judul, kalimat singkat, tombol menuju `#menu`.
3. **Tentang** — 1–2 paragraf cerita UMKM.
4. **Menu / produk** — minimal 3 item. Boleh kartu flex/grid, bukan tabel
   layout.
5. **Lokasi / jam buka** — alamat + daftar jam.
6. **Kontak** — tautan `mailto:` / `tel:` dan form singkat (nama, pesan)
   dengan label.
7. **Footer** — hak cipta.

Gambar boleh placeholder (https://picsum.photos atau folder `img/`). Setiap
`<img>` punya `alt`. Satu `<h1>` (nama usaha di hero atau header — jangan
dua-duanya h1).

## CSS (`style.css`)

- External only. `box-sizing: border-box`.
- Tipografi konsisten (satu font stack).
- Header/nav flexbox.
- Kartu produk: padding, radius, bayangan.
- Hero menonjol (latar, min-height, teks kontras).
- **Responsif ≤768px**: nav dan kartu menumpuk; tidak ada scroll horizontal.

## Cara uji

Buka `index.html`. Resize ke ~360px dan ~1280px. Klik tautan nav harus
loncat ke section. Klik label form memfokuskan input.
