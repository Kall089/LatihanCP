# 07 — Next.js App Router

## Persiapan

```bash
npx create-next-app@latest belajar-nextjs
cd belajar-nextjs
npm run dev
```

Pengaturan bawaan terbaru sudah menyertakan TypeScript, Tailwind CSS, ESLint, App Router, dan Turbopack. Setelah proyek terbentuk, gunakan file di `starter/app` sebagai latihan.

## Tujuan

- Memahami fungsi `app/layout.tsx` dan `app/page.tsx`.
- Membuat route berdasarkan struktur folder.
- Berpindah halaman menggunakan component `Link`.
- Mengatur metadata halaman.

## Tugas

1. Lengkapi metadata di `layout.tsx`.
2. Buat navigasi menuju `/` dan `/tentang` memakai `Link`.
3. Lengkapi halaman utama.
4. Lengkapi route `/tentang`.
5. Pastikan URL dapat dibuka langsung dan navigasi tidak menghasilkan 404.

## Checklist

- Beranda tersedia di `/`.
- Halaman tentang tersedia di `/tentang`.
- Navigasi menggunakan `Link`, bukan elemen `a` untuk route internal.
- Judul tab browser sesuai metadata.
