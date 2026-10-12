# 01 — Instalasi dan struktur App Router

[← README](README.md) · [Berikut: layout, page, template, default →](02-layout-page-template-default.md)

**Untuk apa:** membuat proyek Next.js yang memakai App Router, JavaScript, dan folder `app/` yang bisa dikenali dari URL.

## Daftar isi file ini

- [Prasyarat Node.js](#prasyarat-nodejs)
- [Perintah create-next-app](#perintah-create-next-app)
- [Flag satu per satu](#flag-satu-per-satu)
- [Jawaban interaktif jika tidak memakai flag](#jawaban-interaktif-jika-tidak-memakai-flag)
- [Skrip npm](#skrip-npm)
- [Pohon folder proyek latihan](#pohon-folder-proyek-latihan)
- [File di root, satu per satu](#file-di-root-satu-per-satu)
- [File di dalam app/, satu per satu](#file-di-dalam-app-satu-per-satu)
- [Folder public/](#folder-public)
- [src/app/ versus app/](#srcapp-versus-app)
- [App Router versus Pages Router](#app-router-versus-pages-router)
- [next.config.mjs](#nextconfigmjs)
- [jsconfig.json](#jsconfigjson)
- [Cache Components dimatikan](#cache-components-dimatikan)
- [Menjalankan, membangun, dan memeriksa](#menjalankan-membangun-dan-memeriksa)
- [Kesalahan instalasi yang sering](#kesalahan-instalasi-yang-sering)

## Prasyarat Node.js

**Untuk apa:** memastikan perintah `npx` dan `npm run dev` tidak gagal karena versi Node terlalu lama.

Next.js 15/16 membutuhkan Node.js versi yang didukung resmi. Cek di mesin:

```bash
node -v
npm -v
```

Jika versi Node di bawah persyaratan [instalasi Next.js](https://nextjs.org/docs/app/getting-started/installation), instal ulang Node LTS. Jangan menjalankan `create-next-app` dari dalam folder cheatsheet ini; pilih folder latihan terpisah, misalnya `~/latihan/`.

**Biasanya digabungkan dengan:** manajer versi Node (`nvm`, `fnm`) jika satu mesin dipakai untuk banyak mata kuliah.

## Perintah create-next-app

**Untuk apa:** men-scaffold proyek App Router berbahasa JavaScript tanpa mengetik ulang seluruh konfigurasi.

Jalankan di folder induk, bukan di dalam proyek yang sudah ada:

```bash
npx create-next-app@latest latihan-next --js --app --eslint --no-tailwind --no-src-dir --use-npm
cd latihan-next
npm run dev
```

Buka URL yang dicetak terminal, biasanya `http://localhost:3000`. Hentikan server dengan `Ctrl+C`.

Jika kamu **ingin Tailwind** sejak awal (banyak tugas pakai ini):

```bash
npx create-next-app@latest latihan-next --js --app --eslint --tailwind --no-src-dir --use-npm
```

Jika kamu ingin folder `src/`:

```bash
npx create-next-app@latest latihan-next --js --app --eslint --no-tailwind --src-dir --use-npm
```

`@latest` mengikuti versi yang tersedia saat perintah dijalankan. Untuk mengunci versi tertentu, ganti menjadi `create-next-app@15` atau nomor yang diminta dosen.

**Biasanya digabungkan dengan:** `npm run dev` segera setelah `cd`, lalu mengganti `app/page.js` dengan halaman beranda toko.

## Flag satu per satu

**Untuk apa:** memahami setiap pilihan agar tidak salah menjawab prompt.

### `--js`

Memakai JavaScript. File halaman menjadi `page.js` / `layout.js`, bukan `page.tsx`.

### `--ts` (jangan dipakai di ensiklopedia ini)

Menghasilkan TypeScript. Hanya disebut supaya kamu mengenali proyek orang lain.

### `--app`

Mengaktifkan App Router. Folder `app/` menjadi sumber URL.

### `--no-app`

Menghasilkan Pages Router (`pages/`). **Jangan dipakai** untuk panduan ini.

### `--eslint`

Menambah ESLint. Berguna untuk `npm run lint`.

### `--tailwind` / `--no-tailwind`

Menginstal atau meniadakan Tailwind. File [12](12-tailwind-css-modules.md) membahas keduanya.

### `--src-dir` / `--no-src-dir`

Menaruh `app/` di dalam `src/` atau di root. Ensiklopedia ini menulis path tanpa `src/`.

### `--use-npm` / `--use-pnpm` / `--use-yarn` / `--use-bun`

Memilih manajer paket. Contoh kuliah memakai npm.

### `--import-alias`

Default biasanya `@/*` mengarah ke root proyek (atau `src/` jika `--src-dir`). Contoh:

```js
import Navigasi from "@/app/components/Navigasi";
```

Setara dengan impor relatif, hanya lebih pendek.

### `--turbopack` (jika tersedia di versimu)

Beberapa versi `create-next-app` menanyakan Turbopack untuk `next dev`. Untuk latihan, jawaban apa pun boleh; yang penting kamu tahu perintah yang tertulis di `package.json`.

**Biasanya digabungkan dengan:** catatan dosen “pakai JS, App Router, boleh Tailwind”.

## Jawaban interaktif jika tidak memakai flag

**Untuk apa:** tetap bisa menjawab jika kamu mengetik `npx create-next-app@latest` tanpa flag.

Urutan pertanyaan bisa berubah antarversi, tetapi makna tetap:

| Pertanyaan (kira-kira) | Jawaban latihan ini |
| --- | --- |
| TypeScript? | No |
| ESLint? | Yes |
| Tailwind CSS? | Sesuai tugas |
| `src/` directory? | No (kecuali kamu sudah terbiasa) |
| App Router? | Yes |
| Turbopack? | Default saja |
| Import alias? | Default `@/*` |
| Cache Components / React Compiler? | **No** untuk latihan ini |

Jika salah pilih TypeScript, lebih mudah mengulang `create-next-app` daripada mengonversi file satu-satu di minggu pertama.

**Biasanya digabungkan dengan:** menghapus folder hasil percobaan yang salah (`rm -rf latihan-next`) lalu menjalankan ulang perintah.

## Skrip npm

**Untuk apa:** menjalankan mode development, produksi, dan pemeriksaan.

`package.json` (potongan):

```json
{
  "scripts": {
    "dev": "next dev",
    "build": "next build",
    "start": "next start",
    "lint": "eslint"
  }
}
```

Satu per satu:

### `npm run dev`

Menyalakan server development dengan hot reload. Pakai ini saat menulis kode.

### `npm run build`

Membangun produksi dan melaporkan error kompilasi, tipe (jika TS), serta route yang dihasilkan. Wajib dicoba sebelum mengumpulkan tugas besar.

### `npm run start`

Menjalankan hasil `build`. Tidak punya hot reload. Hanya berguna setelah `build` sukses.

### `npm run lint`

Menjalankan ESLint sesuai konfigurasi proyek.

Jangan menjalankan `build` dari folder cheatsheet; folder itu tidak berisi `node_modules` Next.js.

**Biasanya digabungkan dengan:** memperbaiki error merah di terminal `dev` sebelum mencoba `build`.

## Pohon folder proyek latihan

**Untuk apa:** menautkan nama folder ke URL yang akan muncul di browser.

```text
latihan-next/
├── app/
│   ├── favicon.ico
│   ├── globals.css
│   ├── layout.js
│   ├── page.js
│   ├── not-found.js          kamu buat sendiri
│   ├── components/           bukan route
│   │   └── Navigasi.js
│   ├── produk/
│   │   ├── page.js           /produk
│   │   ├── loading.js
│   │   ├── error.js
│   │   └── [id]/
│   │       └── page.js       /produk/1
│   └── api/
│       └── produk/
│           └── route.js      /api/produk
├── public/
│   └── buku.jpg
├── .env.local                jangan di-commit
├── .gitignore
├── jsconfig.json
├── next.config.mjs
├── package.json
└── package-lock.json
```

Hanya folder yang berisi `page.js` atau `route.js` yang menjadi URL. Folder `components/` tidak muncul di address bar.

**Biasanya digabungkan dengan:** [katalog file convention](13-katalog-file-convention.md) ketika ragu file mana yang wajib ada.

## File di root, satu per satu

### `package.json`

Daftar dependensi (`next`, `react`, `react-dom`) dan skrip. Jangan menghapus `next` hanya karena “tugasnya cuma React”.

### `package-lock.json`

Mengunci versi paket. Commit file ini di tugas git agar teman/dosen memasang versi yang sama.

### `next.config.mjs`

Konfigurasi bundler, gambar remote, redirect, rewrite. Dibahas di bawah.

### `jsconfig.json`

Alias impor dan opsi editor. Contoh bawaan:

```json
{
  "compilerOptions": {
    "paths": {
      "@/*": ["./*"]
    }
  }
}
```

Jika proyek memakai `src/`, path biasanya `"@/*": ["./src/*"]`.

### `.gitignore`

Memastikan `node_modules/`, `.next/`, dan `.env*` tidak ter-commit. Periksa bahwa `.env.local` masuk daftar ignore.

### `.env.local`

Rahasia dan URL mesin lokal. Lihat [11](11-env-middleware-rewrite-redirect.md).

### `README.md` bawaan create-next-app

Boleh diganti dengan instruksi tugasmu. Bukan file convention Next.js.

### `.next/` (dibuat otomatis)

Hasil kompilasi. Jangan diedit. Dihapus dengan `rm -rf .next` jika cache development aneh, lalu `npm run dev` lagi.

### `node_modules/`

Paket terinstal. Jangan diedit. Diisi ulang dengan `npm install`.

**Biasanya digabungkan dengan:** `git init` di folder proyek latihan, bukan di folder cheatsheet.

## File di dalam app/, satu per satu

### `app/layout.js`

Wajib. Root layout. Harus memuat `<html>` dan `<body>`. Tanpa file ini, Next.js menolak App Router.

### `app/page.js`

Halaman `/`. Tanpa `page.js` di `app/`, URL `/` 404.

### `app/globals.css`

CSS yang diimpor root layout. Tempat reset, variabel, atau direktif Tailwind.

### `app/favicon.ico`

Ikon tab. Bisa diganti file gambar. Alternatif modern: `app/icon.png` — lihat [10](10-metadata-image-font.md).

### `app/not-found.js`

UI 404 kustom. Tidak wajib di awal, sangat berguna sejak ada dynamic route.

### `app/error.js` dan `app/global-error.js`

Batas error. `error.js` membutuhkan `"use client"`. `global-error.js` mengganti root layout saat root gagal.

### `app/loading.js`

Fallback saat segmen ditangguhkan (Suspense). Muncul otomatis untuk `page.js` async di segmen yang sama.

### `app/template.js`

Seperti layout tetapi **mount ulang** setiap navigasi. Jarang wajib.

### `app/default.js`

Fallback slot parallel route. Hanya relevan jika kamu memakai `@folder`.

### `app/route.js`

Route Handler di URL `/`. Jarang; biasanya `app/api/.../route.js`.

### `app/middleware.js` — salah tempat

`middleware.js` **bukan** di dalam `app/`. Letaknya di root proyek, sejajar `app/`. Lihat [11](11-env-middleware-rewrite-redirect.md) dan [13](13-katalog-file-convention.md).

**Biasanya digabungkan dengan:** habit “satu folder = satu URL, satu `page.js` = satu halaman”.

## Folder public/

**Untuk apa:** menyajikan file statis apa adanya.

```text
public/
├── buku.jpg
├── logo.svg
└── dokumen/
    └── silabus.pdf
```

Pemakaian:

```jsx
<img src="/buku.jpg" alt="Sampul buku" />
```

atau `next/image` dengan `src="/buku.jpg"`.

Jangan mengimpor file `public/` sebagai modul JavaScript. Jangan menaruh rahasia di `public/`; isinya bisa diunduh siapa saja.

**Biasanya digabungkan dengan:** `next/image`, tautan unduhan, dan favicon cadangan.

## src/app/ versus app/

**Untuk apa:** tidak tersesat saat tutorial memakai path berbeda.

Dua proyek ini setara secara routing:

```text
app/page.js
src/app/page.js
```

Keduanya menghasilkan `/`. Yang berubah hanya path di disk.

Jika memakai `src/`:

- `middleware.js` tetap di root (sejajar `src/`), atau kadang `src/middleware.js` — cocokkan dengan versi; uji dengan `console.log`.
- `public/` tetap di root, bukan `src/public/`.
- `.env.local` tetap di root.

Ensiklopedia ini menulis `app/page.js`. Terjemahkan sendiri jika foldermu `src/app/page.js`.

**Biasanya digabungkan dengan:** alias `@/` yang sudah menunjuk ke `src/` pada `jsconfig.json`.

## App Router versus Pages Router

**Untuk apa:** mengenali tutorial yang tidak bisa disalin mentah-mentah.

| Topik | App Router (`app/`) | Pages Router (`pages/`) |
| --- | --- | --- |
| Halaman beranda | `app/page.js` | `pages/index.js` |
| Halaman `/produk` | `app/produk/page.js` | `pages/produk.js` atau `pages/produk/index.js` |
| Dynamic | `app/produk/[id]/page.js` | `pages/produk/[id].js` |
| Data server | `async` Server Component + `fetch` | `getServerSideProps` / `getStaticProps` |
| API | `app/api/produk/route.js` | `pages/api/produk.js` |
| Layout bersarang | `layout.js` di tiap segmen | `_app.js` + `_document.js` (terbatas) |
| Navigasi | `next/link`, `next/navigation` | `next/link`, `next/router` |

`useRouter` dari `next/router` **bukan** untuk App Router. Pakai `next/navigation`.

Jika dosen meminta App Router, jangan membuat folder `pages/` kecuali untuk migrasi sadar.

**Biasanya digabungkan dengan:** membaca judul tutorial sampai ketemu kata “App Router” sebelum menyalin kode.

## next.config.mjs

**Untuk apa:** mengatur perilaku build yang tidak bisa diekspresikan lewat file `app/`.

Contoh minimal yang sering dibutuhkan tugas (gambar dari luar):

```js
/** @type {import('next').NextConfig} */
const nextConfig = {
  images: {
    remotePatterns: [
      {
        protocol: "https",
        hostname: "images.unsplash.com",
        pathname: "/**",
      },
    ],
  },
};

export default nextConfig;
```

Opsi yang sering muncul di tugas, satu per satu:

### `images.remotePatterns`

Daftar host yang boleh dipakai `next/image` untuk URL eksternal.

### `redirects`

Pengalihan permanen/sementara di level konfigurasi. Alternatif: `middleware.js` atau `redirect()` di server.

```js
async redirects() {
  return [
    { source: "/toko", destination: "/produk", permanent: true },
  ];
}
```

### `rewrites`

Menyembunyikan URL internal atau mem-proxy API.

```js
async rewrites() {
  return [
    {
      source: "/backend/:path*",
      destination: "http://127.0.0.1:8000/:path*",
    },
  ];
}
```

### `env` (kurang disarankan)

Menyisipkan nilai ke bundle. Lebih jelas memakai `.env.local` + `process.env`.

### `reactStrictMode`

Default aktif. Komponen development bisa “jalan dua kali” — itu disengaja, bukan bug state.

### `output: "standalone"` atau `output: "export"`

Khusus deploy statis/kontainer. Jangan diaktifkan kecuali tugas memintanya. `output: "export"` menonaktifkan banyak fitur server.

Restart `npm run dev` setelah mengubah `next.config.mjs`.

**Biasanya digabungkan dengan:** `next/image` remote, proxy Laravel, dan redirect URL lama.

## jsconfig.json

**Untuk apa:** membuat impor `@/` hidup di editor dan di bundler.

```json
{
  "compilerOptions": {
    "baseUrl": ".",
    "paths": {
      "@/*": ["./*"]
    }
  }
}
```

Contoh pemakaian:

```jsx
import Navigasi from "@/app/components/Navigasi";
import { simpanNama } from "@/app/aksi";
```

Jika alias tidak terasa, cek apakah file benar-benar ada dan apakah `baseUrl` cocok. Restart language server editor jika path merah palsu.

**Biasanya digabungkan dengan:** folder `app/components/` yang tidak boleh menjadi route.

## Cache Components dimatikan

**Untuk apa:** menjaga contoh rendering dan cache di file 07 tetap bisa diprediksi.

Beberapa versi `create-next-app` menanyakan Cache Components atau menambahkan flag terkait `"use cache"`. Untuk latihan kuliah yang mengikuti cheatsheet ringkas:

- pilih **tidak mengaktifkan** Cache Components;
- jangan menambah `"use cache"` di contoh kecuali kamu sadar sedang bereksperimen;
- anggap `fetch` dikontrol lewat `{ cache }` dan `{ next: { revalidate, tags } }` seperti di [07](07-fetch-cache-revalidate.md).

Jika proyek temanmu sudah mengaktifkannya, baca dokumentasi versi itu terpisah. Jangan campur resep.

**Biasanya digabungkan dengan:** catatan “contoh cache: no-store versus revalidate 60”.

## Menjalankan, membangun, dan memeriksa

### Development

```bash
cd latihan-next
npm run dev
```

Ubah `app/page.js`, simpan, lihat browser. Jika port 3000 terpakai, Next.js menawarkan port berikutnya (`3001`, …).

### Produksi lokal

```bash
npm run build
npm run start
```

`build` mencetak daftar route: halaman statis, dinamis, dan Route Handler. Baca keluaran itu ketika URL 404 padahal file sudah ada — sering nama foldernya salah.

### Lint

```bash
npm run lint
```

### Membersihkan cache aneh

```bash
rm -rf .next
npm run dev
```

**Biasanya digabungkan dengan:** memeriksa terminal, bukan hanya UI browser, setiap kali halaman kosong.

## Kesalahan instalasi yang sering

- **`command not found: npx`:** Node belum terinstal atau PATH belum di-refresh.
- **EACCES / permission npm:** jangan `sudo npm`. Perbaiki prefix npm atau pakai nvm.
- **Proyek dibuat di dalam cheatsheet:** pindahkan; cheatsheet bukan tempat `node_modules`.
- **Campur `pages/` dan `app/` tanpa rencana:** pilih satu. Panduan ini hanya `app/`.
- **Mengedit file di `.next/`:** perubahan hilang saat compile ulang.
- **Lupa `cd latihan-next`:** `npm run dev` gagal karena tidak ada `package.json`.
- **Node terlalu lama:** error aneh saat `create-next-app` atau saat `next build`.
- **Pilih TypeScript lalu menyalin contoh JS mentah ke `.tsx` tanpa menyesuaikan:** lebih aman ulang scaffold, atau rename sadar ke `.js` jika proyek memang JS.

**Biasanya digabungkan dengan:** [14 — kesalahan dan resep](14-kesalahan-dan-resep.md) setelah proyek sudah jalan.

## Checklist pertama kali

1. `node -v` memenuhi syarat.
2. `create-next-app` dengan `--js --app`.
3. `npm run dev` membuka `/`.
4. `app/layout.js` berisi `<html>` dan `<body>`.
5. `app/page.js` bisa diganti tanpa merusak layout.
6. Tidak ada folder `pages/` yang tidak kamu sengaja.

## Lihat juga

- [02 — layout, page, template, default](02-layout-page-template-default.md)
- [13 — katalog file convention](13-katalog-file-convention.md)
- [Cheatsheet ringkas: persiapan](../../next-js.md)

---

Sebelum: [README](README.md) · Berikut: [02 — layout, page, template, default](02-layout-page-template-default.md)
