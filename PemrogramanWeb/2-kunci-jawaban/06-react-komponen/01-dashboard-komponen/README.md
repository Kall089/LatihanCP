# 06 — React: Component, Props, dan State

## Persiapan

Buat proyek Next.js latihan dari folder ini:

```bash
npx create-next-app@latest latihan-react
```

Pilih pengaturan bawaan yang direkomendasikan, lalu salin isi folder `starter` ke proyek tersebut sesuai jalurnya.

## Tujuan

- Memecah UI menjadi component.
- Mengirim data melalui props.
- Memahami state dan event pada Client Component.

## Tugas

1. Lengkapi `CourseCard.tsx` agar menerima props judul, deskripsi, dan status.
2. Lengkapi `StudyCounter.tsx` menggunakan `useState`.
3. Render minimal tiga `CourseCard` dari array menggunakan `map()`.
4. Pastikan setiap item hasil `map()` memiliki `key` yang stabil.

Jalankan dengan `npm run dev` dari folder proyek hasil `create-next-app`.
