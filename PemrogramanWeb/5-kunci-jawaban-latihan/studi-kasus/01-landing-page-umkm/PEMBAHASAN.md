# Pembahasan — Landing Page UMKM

Satu halaman pemasaran: **meyakinkan pengunjung** (hero + menu), bukan
dashboard data.

## Struktur

- Merek di header memakai `<p class="merek">`, **bukan** `<h1>`, agar hanya
  ada satu h1 di hero. Dua h1 merusak outline.
- Menu produk = `<ul>` kartu, bukan tabel. Tabel hanya untuk data tabular.
- Nav memakai *anchor* `#menu` dll. `href` harus sama dengan `id` section.
- Kontak: `mailto:` / `tel:` plus form ber-label (meski `action="#"`).

## Layout

- Header sticky flex `space-between`.
- Hero flex column + `min-height: 70vh` + kontras gelap (bukan teks abu
  di atas foto ramai tanpa overlay).
- Kartu: **grid mobile-first** 1 kolom, `min-width: 768px` jadi 3 kolom.
  `max-width: 768px` pada header memaksa nav turun di HP.
- `clamp` pada h1: tipografi responsif tanpa media query tambahan.

## Yang sering salah

Hero pakai `<h1>` *dan* header juga `<h1>`. Gambar tanpa `alt`. Kartu
dipaksa `width: 33%` tanpa wrap — pecah di 360px. Form placeholder tanpa
label.
