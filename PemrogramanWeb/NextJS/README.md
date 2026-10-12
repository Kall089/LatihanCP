# Ultimate React Course — Versi Next.js

Folder ini berisi versi pembelajaran Next.js dari materi `ultimate-react-course`. Semua proyek menggunakan TypeScript dan sudah memiliki Tailwind CSS. Struktur bab, folder `starter`, dan folder `final` tetap dipertahankan agar mudah dibandingkan dengan materi asal.

## Persiapan

Jalankan instalasi sekali dari folder ini:

```bash
cd NextJS
npm install
```

Setelah itu, pilih proyek yang ingin dipelajari. Contoh membuka starter Pizza Menu:

```bash
npm run dev --workspace=next-course-03-pizza-menu-starter
```

Buka `http://localhost:3000`, lalu mulai menulis kode di `03-pizza-menu/starter/app/page.tsx`.

Untuk membandingkan hasil dengan versi final:

```bash
npm run dev --workspace=next-course-03-pizza-menu-final
```

Nama workspace mengikuti pola berikut:

```text
next-course-<nama-folder-bab>-starter
next-course-<nama-folder-bab>-final
```

Daftar lengkapnya dapat dilihat pada bagian `workspaces` di `package.json` root.

## Template starter

Setiap folder `starter` tingkat bab sudah siap dijalankan dan berisi:

- Next.js dengan App Router atau struktur bawaan materi jika starter tersebut sudah memiliki aplikasi
- TypeScript dan konfigurasi pemeriksaan tipe
- Tailwind CSS dan PostCSS
- `package.json` dengan perintah `dev`, `build`, dan `start`
- halaman awal yang menunjukkan file pertama yang perlu diedit

Template App Router dimulai dari:

```text
starter/
├── app/
│   ├── globals.css
│   ├── layout.tsx
│   └── page.tsx
├── package.json
├── postcss.config.cjs
├── tailwind.config.cjs
└── tsconfig.json
```

Tailwind dapat langsung dipakai melalui `className`, misalnya:

```tsx
export default function HomePage() {
  return <h1 className="text-3xl font-bold text-sky-500">Mulai belajar</h1>;
}
```

## Pemeriksaan kode

Periksa TypeScript untuk semua proyek sekaligus dari root `NextJS`:

```bash
npm run typecheck
```

Build satu proyek dengan:

```bash
npm run build --workspace=next-course-03-pizza-menu-starter
```

Beberapa proyek final memakai API atau layanan eksternal. Salin `.env.example` menjadi `.env.local` pada proyek terkait dan isi nilainya sebelum menjalankan fitur yang membutuhkan Supabase atau autentikasi.

Snapshot bertahap pada bab 17 memiliki halaman aktif berbasis Tailwind agar setiap tahap bisa dijalankan dengan stabil. Kode sumber lama tetap tersedia di dalam tahap tersebut sebagai bahan membandingkan perkembangan aplikasi.
