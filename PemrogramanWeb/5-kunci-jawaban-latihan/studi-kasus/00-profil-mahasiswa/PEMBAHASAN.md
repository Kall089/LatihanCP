# Pembahasan — Profil Mahasiswa

Solusi ini memenuhi brief dua tahap. Nama/NIM boleh diganti milikmu;
yang dinilai pola, bukan identitas.

## Tahap 1 — mengapa semantik dulu

Sepuluh komponen dipetakan ke landmark, bukan tumpukan `div`:

| Komponen | Markup |
|---|---|
| Judul | `<h1>` di `<header>` ("Profil Saya") — nama orang di `<h2>` kartu agar tidak ada dua h1 |
| Nama, NIM, deskripsi, foto | `<section id="tentang">` + `<img alt>` path/URL gambar |
| Hobi | `<ul>` (urutan tidak penting) |
| Mata kuliah | `<ol>` (peringkat/favorit) |
| Tautan | internal `#kontak`, eksternal `rel="noopener"` |
| Tabel | `caption`, `thead`, `th scope="col"` |
| Form | `label for` = `id` |

Kalau CSS dimatikan, dokumen masih bisa dibaca atas-bawah. Itulah tes
semantik dosen.

Foto memakai URL picsum agar kunci langsung terbuka tanpa file biner.
Di tugasmu, `img/foto.jpg` relatif lebih sesuai brief.

## Tahap 2 — keputusan CSS

- **External** `css/style.css` — satu tanggung jawab, path relatif dari
  HTML di folder induk (`css/style.css`).
- **Header/nav flex** `space-between`; di ≤768px `flex-direction: column`
  agar tautan tidak terpotong.
- **Kartu + foto bulat** `object-fit: cover` mencegah wajah gepeng.
- **Chip hobi** flex wrap — contoh main axis baris tanpa grid.
- **`box-sizing: border-box`** + `overflow-x: auto` pada tabel: HP tidak
  mendorong seluruh halaman melebar.
- **`:focus-visible`** pada tombol, bukan `outline: none` polos.

Media query memakai `max-width: 768px` sesuai brief "responsif ≤768".
Setara mobile-first: dasar = kolom, lalu `min-width: 768px` untuk baris.
Keduanya sah; yang penting breakpoint 768px (bukan 767 vs 769 yang
dibiarkan tanpa alasan).

## Yang sering salah

1. `src="C:\Users\..."` atau `/Users/...` — rusak di komputer dosen.
2. Label tanpa `for`.
3. Tabel layout untuk kartu identitas.
4. CSS internal di `<style>` padahal diminta external.
5. Dua `<h1>` (judul situs + nama).
