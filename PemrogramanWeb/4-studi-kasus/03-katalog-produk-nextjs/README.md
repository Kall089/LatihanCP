# Studi Kasus 03 — Katalog Produk Next.js + Tailwind

Bangun aplikasi katalog (contoh: menu Warung Kopi Senja) dengan **App
Router**, tiga layer (`lib/`, `components/`, `app/`), dan Tailwind.
Bekal: Modul 06–08.

Folder ini adalah **kerangka ber-TODO**, tanpa `node_modules`.

Kunci: [`../../5-kunci-jawaban-latihan/studi-kasus/03-katalog-produk-nextjs/`](../../5-kunci-jawaban-latihan/studi-kasus/03-katalog-produk-nextjs/).

## Setup

```bash
npx create-next-app@latest katalog-senja --typescript --tailwind --app
cd katalog-senja
# salin isi folder studi kasus ini (app/, components/, lib/) menimpa starter
# atau copy file satu-satu
npm run dev
```

Pastikan `tsconfig.json` punya alias `@/*`. Jangan commit `node_modules`.

## Fitur wajib

| Rute | Isi |
|---|---|
| `/` | Hero singkat + 3 produk unggulan (`ProdukCard`) |
| `/produk` | Daftar semua + **filter kategori** (client island) |
| `/produk/[id]` | Detail; `notFound()` jika id salah |
| 404 | `app/not-found.tsx` |

Data **hanya** di `lib/data.ts` (tipe + array ≥ 6 item + `getProdukById`).
Format uang di `lib/format.ts`. Kartu tidak mengimpor array.

Navbar di `layout.tsx` memakai `<Link>`. Layout tetap Server Component.
`FilterKategori` / `KatalogClient` boleh `"use client"`.

## Kualitas

- Grid `grid-cols-1 sm:grid-cols-2 lg:grid-cols-3`
- `alt` jika ada gambar; heading berjenjang
- Empty state saat filter kosong
- `npm run build` lolos

## Penilaian

Arsitektur layer 25% · data flow 25% · rute + 404 20% · UI responsif 20% ·
build 10%.
