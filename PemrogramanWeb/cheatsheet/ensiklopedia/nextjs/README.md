# Ensiklopedia Next.js — App Router

[← Cheatsheet ringkas](../../next-js.md) · [Dasar React](../../react-js.md) · [Cara menggabungkan teknologi](../../kombinasi-teknologi.md)

Ini adalah **ensiklopedia** Next.js App Router berbahasa Indonesia. Isinya lebih panjang dari [cheatsheet ringkas](../../next-js.md): setiap file convention dan setiap API ditulis satu per satu, lengkap dengan contoh JavaScript/JSX, catatan kapan dipakai, dan resep gabungan.

Bukan instalasi Next.js. Folder ini hanya referensi. Salin contoh ke proyek latihanmu.

## Untuk siapa

- Mahasiswa yang sudah bisa HTML, CSS, JavaScript, dan komponen React.
- Siapa pun yang memakai **App Router** (`app/`), bukan Pages Router (`pages/`).
- Siapa pun yang ingin melihat **satu file = satu topik**, bukan satu halaman yang mencampur semua.

## Cara memakai

1. Mulai dari [01 — instalasi dan struktur](01-install-struktur-app.md) jika proyek belum ada.
2. Lanjut ke [02](02-layout-page-template-default.md) sampai [12](12-tailwind-css-modules.md) sesuai kebutuhan.
3. Pakai [13 — katalog file convention](13-katalog-file-convention.md) sebagai kamus: `page.js`, `layout.js`, `loading.js`, dan seterusnya.
4. Pakai [14 — kesalahan dan resep](14-kesalahan-dan-resep.md) saat error atau saat merakit fitur utuh.

Setiap entri mengikuti pola yang sama:

- **Untuk apa:** alasan memakai potongan ini.
- **Kode JavaScript/JSX:** contoh yang bisa disalin. TypeScript hanya muncul jika API-nya memang menuntut tipe.
- **Biasanya digabungkan dengan:** file, hook, atau pola yang sering menempel.

Contoh adalah potongan terpisah, kecuali dinyatakan sebagai rangkaian. Jangan menempelkan semua contoh ke satu file.

## Versi dan aturan yang dipakai di sini

- Next.js **15/16 App Router**.
- `params` dan `searchParams` di-**`await`**.
- `cookies()`, `headers()`, dan `draftMode()` juga dianggap asinkron (pola Next 15+).
- Contoh memakai **JavaScript**, bukan TypeScript, agar sejalan dengan cheatsheet kuliah.
- Struktur contoh: `app/` di root (bukan `src/app/`). Jika proyekmu memakai `src/`, sisipkan `src/` di depan setiap path.
- **Cache Components** (`use cache`) dianggap **tidak aktif**, sesuai konfigurasi latihan di cheatsheet ringkas.
- Perilaku cache `fetch` berbeda antara Next 14 dan Next 15+. File [07](07-fetch-cache-revalidate.md) menjelaskan keduanya secara eksplisit.
- Dokumentasi resmi yang relevan: [App Router](https://nextjs.org/docs/app), [file conventions](https://nextjs.org/docs/app/api-reference/file-conventions), [functions](https://nextjs.org/docs/app/api-reference/functions).

## Daftar file

| No | File | Isi ringkas |
| --- | --- | --- |
| 00 | [README.md](README.md) | Peta ensiklopedia, versi, dan cara baca |
| 01 | [01-install-struktur-app.md](01-install-struktur-app.md) | `create-next-app`, folder `app/`, skrip, `next.config` |
| 02 | [02-layout-page-template-default.md](02-layout-page-template-default.md) | `layout.js`, `page.js`, `template.js`, `default.js`, route group |
| 03 | [03-link-navigation-hooks.md](03-link-navigation-hooks.md) | `Link`, `useRouter`, `usePathname`, `useSearchParams`, `useParams`, `redirect`, `notFound`, `permanentRedirect` |
| 04 | [04-server-client-component.md](04-server-client-component.md) | Server Component, `"use client"`, serialisasi props, komposisi |
| 05 | [05-dynamic-route-catch-all-optional.md](05-dynamic-route-catch-all-optional.md) | `[id]`, `[...slug]`, `[[...slug]]`, `generateStaticParams` |
| 06 | [06-searchParams-loading-error-not-found.md](06-searchParams-loading-error-not-found.md) | Query string, `loading.js`, `error.js`, `not-found.js` |
| 07 | [07-fetch-cache-revalidate.md](07-fetch-cache-revalidate.md) | `fetch`, cache, `revalidate`, `revalidatePath`, `revalidateTag` |
| 08 | [08-route-handler-http.md](08-route-handler-http.md) | `GET` `POST` `PUT` `PATCH` `DELETE`, `Request`, `headers`, `cookies` |
| 09 | [09-server-actions-form.md](09-server-actions-form.md) | `"use server"`, form, `useActionState`, `useFormStatus` |
| 10 | [10-metadata-image-font.md](10-metadata-image-font.md) | `metadata`, `generateMetadata`, `next/image`, `next/font` |
| 11 | [11-env-middleware-rewrite-redirect.md](11-env-middleware-rewrite-redirect.md) | `.env`, `middleware.js`, rewrite, redirect |
| 12 | [12-tailwind-css-modules.md](12-tailwind-css-modules.md) | Tailwind v3/v4, CSS Modules, CSS global |
| 13 | [13-katalog-file-convention.md](13-katalog-file-convention.md) | Kamus `page`, `layout`, `loading`, `error`, `global-error`, `not-found`, `route`, `template`, `default`, `middleware` |
| 14 | [14-kesalahan-dan-resep.md](14-kesalahan-dan-resep.md) | Error umum, resep toko, gabungan Laravel |

## Peta belajar cepat

Urutan yang paling aman untuk tugas kuliah:

1. Instal proyek dan kenali folder `app/`.
2. Buat `layout.js` + `page.js` + `Link`.
3. Pisahkan Server Component dan Client Component.
4. Tambah dynamic route `[id]` dan `not-found.js`.
5. Ambil data dengan `fetch` di server, lalu `loading.js` / `error.js`.
6. Baru kemudian: Route Handler, Server Action, metadata, middleware.

Jika kamu hanya butuh “nama file apa yang harus dibuat”, buka [katalog file convention](13-katalog-file-convention.md).

## Yang tidak dibahas di sini

- Pages Router (`pages/index.js`, `getServerSideProps`, `getStaticProps`) — hanya disebut sebagai pembeda.
- TypeScript mendalam, tRPC, Prisma, Auth.js lengkap, testing Playwright.
- Cache Components (`"use cache"`) sebagai mode utama.
- Deploy mendalam (Vercel/Node/Docker) — hanya resep singkat di file 14.

## Konvensi contoh

Contoh berulang memakai toko buku fiktif **Toko Belajar**:

- URL `/` beranda.
- URL `/produk` daftar.
- URL `/produk/1` detail.
- URL `/produk?q=buku` pencarian.
- Backend latihan sering Laravel di `http://127.0.0.1:8000`.

Nama file di atas blok kode adalah lokasi di **proyek latihan**, bukan di folder ensiklopedia ini.

## Navigasi antar file

- Berikut: [01 — instalasi dan struktur App Router](01-install-struktur-app.md)
