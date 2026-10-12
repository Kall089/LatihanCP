# Studi Kasus 00 — Profil Saya

Brief dosen: halaman **Profil Saya** milik satu mahasiswa. Dikerjakan dua
tahap. Tidak boleh menyalin kunci di
`../../5-kunci-jawaban-latihan/studi-kasus/00-profil-mahasiswa/`.

Bekal: Modul 01 (HTML semantik, gambar, tabel, form), Modul 02 (CSS
external, box model, tipografi), Modul 03 (flexbox, media query 768px).

## Tahap 1 — HTML semantik, TANPA CSS

Isi `index.html`. Halaman harus mengandung **10 komponen** ini (boleh
ditambah, tidak boleh dikurangi):

| # | Komponen | Syarat |
|---|---|---|
| 1 | Judul halaman | `<h1>` di dalam `<header>` — mis. "Profil Saya" |
| 2 | Nama lengkap | teks terlihat, bukan hanya `<title>` |
| 3 | NIM | teks biasa atau `<p>` |
| 4 | Foto | `<img>` path **relatif** (siapkan `img/foto.jpg` atau placeholder), `alt` wajib |
| 5 | Deskripsi singkat | `<p>` 2–4 kalimat tentang diri |
| 6 | Hobi | `<ul>` minimal 3 item |
| 7 | Mata kuliah | `<ol>` urutan prioritas / favorit, minimal 3 |
| 8 | Tautan | minimal satu internal (`#kontak`) dan satu eksternal `target="_blank" rel="noopener"` |
| 9 | Tabel | data tabular (jadwal / nilai / organisasi) dengan `<thead>`, `<th scope="col">`, `<tbody>` |
| 10 | Form kontak | `label` terhubung `for`/`id`: nama, email, pesan, tombol submit |

Kerangka: `header` + `nav` + `main` (section-section) + `footer`. Satu
`<main>`. Satu `<h1>`. Jangan pakai CSS internal/inline di tahap 1 — dosen
akan cek bahwa struktur tetap masuk akal saat CSS dimatikan.

## Tahap 2 — CSS external

Buat `css/style.css` dan tautkan dari `<head>`:

```html
<link rel="stylesheet" href="css/style.css">
```

Wajib ada:

1. **Header / nav** — flexbox, tautan berjajar, `space-between` atau gap rapi.
2. **Kartu** — foto + identitas dalam wadah ber-padding, radius, bayangan.
3. **Tipografi** — `font-family` di `body`, hierarki `h1`/`h2`, `line-height` nyaman.
4. **Flexbox** — minimal satu deret (hobi sebagai chip, atau nav, atau kartu).
5. **Responsif ≤768px** — media query `max-width: 768px` *atau* mobile-first
   `min-width: 768px`: nav boleh turun kolom, kartu tidak overflow, tabel
   bisa scroll horizontal jika perlu.

Reset `box-sizing: border-box`. Jangan layout memakai `<table>`.

## Cara mengumpulkan

Buka `index.html` di browser. Uji lebar 360px dan 1280px. Form: klik label
harus memfokuskan input. Gambar tidak 404.

## Penilaian (rubrik ringkas)

| Aspek | Bobot |
|---|---|
| 10 komponen HTML lengkap & semantik | 30% |
| Label, alt, path relatif, tabel benar | 20% |
| CSS external memenuhi 5 wajib tahap 2 | 30% |
| Responsif 768px, tidak pecah di HP | 20% |
