# Pembahasan — Katalog Produk Next.js

Salin file ke proyek `create-next-app` (TypeScript, Tailwind, App Router).
Jangan mengharapkan folder kunci ini bisa `npm run dev` sendiri — tidak ada
`node_modules` / `package.json` sengaja, agar tidak bentrok versi.

## Arsitektur yang ditaati

```text
lib/data.ts          satu-satunya array Produk
lib/format.ts        formatRupiah — dipakai kartu DAN detail
components/ProdukCard  bodoh: hanya props, tidak import daftar
components/KatalogClient  "use client" — filter
app/page.tsx         server: slice(0,3) unggulan
app/produk/page.tsx  server: kirim array ke island
app/produk/[id]      await params + Number(id) + notFound()
```

`lib/` tidak mengimpor komponen. Kartu tidak mengimpor `daftarProduk`.
Kalau nama minuman berubah, cukup satu file data.

## Data flow

1. Server membaca `daftarProduk`.
2. Props (objek polos) menyeberang ke client.
3. `useState` kategori hanya di island; layout/navbar tetap server.
4. Detail: `params.id` string → `Number` sebelum `find`. Tanpa konversi,
   `/produk/1` tidak ketemu.

`generateStaticParams` memakai `String(p.id)` karena segmen URL adalah
string.

## Kualitas

- Grid `grid-cols-1 sm:grid-cols-2 lg:grid-cols-3`
- Empty state filter
- `not-found.tsx` untuk id 999 dan rute liar
- Satu `h1` per halaman (hero vs "Menu lengkap" vs nama produk)
- `focus-visible:ring` pada CTA

## Deployment (yang diharapkan mahasiswa)

`npm run build` di proyek mereka, push GitHub, import Vercel. Kunci ini
tidak menyertakan `.env` karena tidak ada rahasia.

## Perbedaan dengan praktikum 08

Praktikum 08 = Learning Tracker (materi kuliah, slug). Studi kasus ini =
katalog UMKM (`id` numerik, kategori, harga). Polanya identik: data
terpusat, kartu reusable, island filter, dynamic route.
