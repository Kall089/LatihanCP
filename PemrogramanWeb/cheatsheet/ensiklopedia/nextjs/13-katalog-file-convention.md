# 13 — Katalog file convention App Router

[← 12 Tailwind](12-tailwind-css-modules.md) · [Berikut: kesalahan dan resep →](14-kesalahan-dan-resep.md)

**Untuk apa:** kamus cepat. Satu file khusus = satu peran. Nama harus tepat; `Page.js` atau `halaman.js` tidak dihitung.

Rujukan resmi: [File-system conventions](https://nextjs.org/docs/app/api-reference/file-conventions).

File yang dibahas **satu per satu** di katalog ini:

1. [`page.js`](#1-pagejs)
2. [`layout.js`](#2-layoutjs)
3. [`loading.js`](#3-loadingjs)
4. [`error.js`](#4-errorjs)
5. [`global-error.js`](#5-global-errorjs)
6. [`not-found.js`](#6-not-foundjs)
7. [`route.js`](#7-routejs)
8. [`template.js`](#8-templatejs)
9. [`default.js`](#9-defaultjs)
10. [`middleware.js`](#10-middlewarejs)

File terkait yang sering ketemu (bukan sepuluh besar di atas) ada di [Lampiran file lain](#lampiran-file-lain).

Ekstensi: `.js` atau `.jsx` (latihan ini). `.ts` / `.tsx` setara di proyek TypeScript.

---

## Tabel ringkas

| File | URL? | Wajib? | Default server? | `"use client"`? |
| --- | --- | --- | --- | --- |
| `page.js` | Ya, jadi halaman | Agar URL ada | Ya | Hanya jika perlu hook |
| `layout.js` | Tidak sendiri | Root wajib | Ya | Jangan jika ekspor metadata |
| `loading.js` | Tidak | Tidak | Ya | Opsional |
| `error.js` | Tidak | Tidak | Tidak — wajib klien | **Wajib** |
| `global-error.js` | Tidak | Tidak | Wajib klien + html/body | **Wajib** |
| `not-found.js` | Tidak (UI 404) | Tidak | Ya | Opsional |
| `route.js` | Ya, jadi HTTP | Tidak | Server | Bukan komponen |
| `template.js` | Tidak | Tidak | Ya | Opsional |
| `default.js` | Tidak (slot) | Untuk `@slot` | Ya | Opsional |
| `middleware.js` | Tidak | Tidak | Edge | Bukan komponen React |

---

## 1. page.js

**Untuk apa:** isi sebuah URL.

### Lokasi dan URL

```text
app/page.js                 /
app/produk/page.js          /produk
app/produk/[id]/page.js     /produk/1
app/tentang/page.js         /tentang
```

Tanpa `page.js`, folder tidak menjadi halaman (kecuali `route.js`).

### Tanda tangan

```jsx
export default async function Halaman({ params, searchParams }) {
  const p = await params;
  const s = await searchParams;
  return <main>Halaman</main>;
}
```

- Default export wajib.
- `params` / `searchParams` di-await (Next 15+).
- `searchParams` hanya di page (dan metadata), bukan layout.
- Boleh sync jika tidak ada await.

### Boleh mengekspor

- `metadata` atau `generateMetadata`
- `generateStaticParams` (jika dinamis)
- `dynamic`, `revalidate`, `dynamicParams`, `fetchCache`

### Tidak boleh

- Dua `page.js` merebut URL yang sama (termasuk lewat route group).
- Bergantung pada `index.js` seperti Pages Router.

### Contoh minimal

```jsx
export const metadata = { title: "Beranda" };

export default function Beranda() {
  return <main><h1>Toko Belajar</h1></main>;
}
```

**Biasanya digabungkan dengan:** `layout.js` di atasnya, `Link` menuju URL ini, kadang `loading.js`.

Rincian: [02](02-layout-page-template-default.md).

---

## 2. layout.js

**Untuk apa:** kerangka yang bertahan saat anak berganti.

### Lokasi

```text
app/layout.js                 wajib, root, harus html+body
app/produk/layout.js          kerangka cabang /produk
app/(auth)/layout.js          kerangka group, URL tidak bertambah
app/produk/[id]/layout.js     kerangka detail
```

### Tanda tangan

```jsx
export default async function Layout({ children, params }) {
  const { id } = await params;
  return (
    <section>
      {children}
    </section>
  );
}
```

Root:

```jsx
export default function RootLayout({ children }) {
  return (
    <html lang="id">
      <body>{children}</body>
    </html>
  );
}
```

Jika ada parallel route, props tambahan `@slot` menjadi nama slot (`modal`, dll).

### Perilaku

- Tidak unmount saat navigasi di dalam cabang.
- Tidak menerima `searchParams`.
- Boleh async / fetch.
- Boleh ekspor `metadata`.
- Jangan ulangi `<html>` di nested layout.

### Wajib di root

Tanpa `app/layout.js`, App Router invalid.

**Biasanya digabungkan dengan:** navbar, `globals.css`, `next/font`, metadata default.

Rincian: [02](02-layout-page-template-default.md).

---

## 3. loading.js

**Untuk apa:** fallback Suspense otomatis saat page/anak ditangguhkan.

### Lokasi

```text
app/loading.js              fallback hampir seluruh app (di dalam root layout)
app/produk/loading.js       fallback cabang produk
```

### Tanda tangan

```jsx
export default function Loading() {
  return <p role="status">Memuat…</p>;
}
```

Tidak menerima `params` sebagai kontrak utama. Tidak wajib async.

### Perilaku

- Mengganti **page** (isi), layout segmen biasanya tetap.
- Tidak memantau `useEffect` fetch klien.
- Page sinkron tanpa suspense hampir tidak menampilkannya.

### Server atau klien?

Default server. Jadikan klien hanya jika skeleton memakai hook (jarang perlu).

**Biasanya digabungkan dengan:** `page.js` async + `fetch`.

Rincian: [06](06-searchParams-loading-error-not-found.md).

---

## 4. error.js

**Untuk apa:** batas error UI untuk page dan anak segmen.

### Lokasi

```text
app/error.js
app/produk/error.js
```

### Tanda tangan

```jsx
"use client";

export default function ErrorBatas({ error, reset }) {
  return (
    <section>
      <h2>Terjadi kesalahan</h2>
      <button type="button" onClick={() => reset()}>Coba lagi</button>
    </section>
  );
}
```

### Wajib

- `"use client"` di puncak.
- Default export komponen.

### Tidak menangkap

- Error di `layout.js` **folder yang sama** (naik ke atas).
- `notFound()` (pergi ke `not-found.js`).
- Error di onClick klien yang kamu tulis sendiri.

`reset()` merender ulang batas, bukan me-reload dokumen.

**Biasanya digabungkan dengan:** `throw` setelah `fetch` gagal.

Rincian: [06](06-searchParams-loading-error-not-found.md).

---

## 5. global-error.js

**Untuk apa:** batas error ketika **root layout** gagal.

### Lokasi

Hanya bermakna di `app/global-error.js` (akar).

### Tanda tangan

```jsx
"use client";

export default function GlobalError({ error, reset }) {
  return (
    <html lang="id">
      <body>
        <h1>Aplikasi bermasalah</h1>
        <button type="button" onClick={() => reset()}>Coba lagi</button>
      </body>
    </html>
  );
}
```

### Wajib

- `"use client"`
- `<html>` dan `<body>` sendiri, karena menggantikan root layout

Tanpa file ini, kegagalan root memakai UI default Next.

Jangan mengandalkan CSS layout toko; ia mungkin tidak terpasang.

**Biasanya digabungkan dengan:** root layout yang melakukan pekerjaan berisiko (sebaiknya dikurangi).

Rincian: [06](06-searchParams-loading-error-not-found.md).

---

## 6. not-found.js

**Untuk apa:** UI status 404.

### Lokasi

```text
app/not-found.js              404 global / URL tidak cocok
app/produk/not-found.js       saat notFound() di cabang produk
app/produk/[id]/not-found.js  404 detail
```

### Tanda tangan

```jsx
import Link from "next/link";

export default function TidakKetemu() {
  return (
    <main>
      <h1>Tidak ditemukan</h1>
      <Link href="/">Beranda</Link>
    </main>
  );
}
```

### Pemicu

- `notFound()` dari `next/navigation`
- Tidak ada route yang cocok (kerangka 404)

Bukan untuk daftar kosong hasil pencarian.

Boleh Server Component. Boleh `Link`.

**Biasanya digabungkan dengan:** `[id]/page.js` yang `find()` gagal.

Rincian: [03](03-link-navigation-hooks.md#7-notfound) dan [06](06-searchParams-loading-error-not-found.md).

---

## 7. route.js

**Untuk apa:** endpoint HTTP, bukan HTML.

### Lokasi

```text
app/api/produk/route.js         /api/produk
app/api/produk/[id]/route.js    /api/produk/1
```

Jangan sefolder dengan `page.js`.

### Tanda tangan

```js
export async function GET(request, { params }) {
  const { id } = await params;
  return Response.json({ id });
}

export async function POST(request) {
  const body = await request.json();
  return Response.json(body, { status: 201 });
}
```

Ekspor yang dikenali: `GET`, `POST`, `PUT`, `PATCH`, `DELETE`, `HEAD`, `OPTIONS`.

Bukan komponen React. Tidak ada JSX (kecuali kamu sengaja mengembalikan HTML `Response`).

**Biasanya digabungkan dengan:** `fetch` klien, webhook, cookies.

Rincian: [08](08-route-handler-http.md).

---

## 8. template.js

**Untuk apa:** pembungkus yang **di-mount ulang** setiap navigasi.

### Lokasi

Sama seperti layout: `app/template.js`, `app/produk/template.js`, …

### Tanda tangan

```jsx
export default function Template({ children }) {
  return <div className="template">{children}</div>;
}
```

### Versus layout

| | layout | template |
| --- | --- | --- |
| State bertahan | Ya | Tidak |
| `useEffect` ulang | Tidak | Ya |
| Kasus tugas biasa | **Pilih ini** | Jarang |

Bukan pengganti `layout.js`. Root tetap butuh layout.

**Biasanya digabungkan dengan:** animasi enter, form yang harus reset.

Rincian: [02](02-layout-page-template-default.md).

---

## 9. default.js

**Untuk apa:** fallback slot **parallel route** (`@nama`) ketika tidak ada page yang cocok, terutama hard reload.

### Lokasi

```text
app/@modal/default.js
```

### Tanda tangan

```jsx
export default function DefaultSlot() {
  return null;
}
```

Tanpa parallel route, file ini tidak melakukan apa yang biasanya kamu harapkan.

Root layout harus menerima props slot:

```jsx
export default function RootLayout({ children, modal }) {
  return (
    <html lang="id">
      <body>
        {children}
        {modal}
      </body>
    </html>
  );
}
```

**Biasanya digabungkan dengan:** `@modal` + intercepting route.

Rincian: [02](02-layout-page-template-default.md).

---

## 10. middleware.js

**Untuk apa:** pagar request sebelum page/handler.

### Lokasi — penting

```text
middleware.js                 benar (root)
src/middleware.js             benar jika pakai src/
app/middleware.js             SALAH, tidak jalan
```

### Tanda tangan

```js
import { NextResponse } from "next/server";

export function middleware(request) {
  return NextResponse.next();
}

export const config = {
  matcher: ["/admin/:path*"],
};
```

Boleh `async`. Runtime Edge: jangan `fs`, jangan query berat.

Kembalikan:

- `NextResponse.next()`
- `NextResponse.redirect(url)`
- `NextResponse.rewrite(url)`
- atau Response biasa

Baca `request.nextUrl`, `request.cookies`, `request.headers`.

**Biasanya digabungkan dengan:** cookie sesi, `matcher` sempit, cek ulang di page.

Rincian: [11](11-env-middleware-rewrite-redirect.md).

---

## Satu folder, banyak convention

Contoh `app/produk/`:

```text
app/produk/
├── layout.js          kerangka katalog
├── template.js        opsional
├── page.js            /produk
├── loading.js         skeleton daftar
├── error.js           gagal fetch daftar
├── not-found.js       jika notFound() di cabang
├── [id]/
│   ├── page.js
│   └── not-found.js
└── baru/
    └── page.js
```

Tidak semua harus ada. Mulai dari `page.js` (+ root `layout.js`).

Tidak boleh: `page.js` + `route.js` di `app/produk/` bersamaan.

---

## Nama yang sering salah

| Ditulis | Yang terjadi |
| --- | --- |
| `Page.js` | Bukan convention (case-sensitive di banyak host) |
| `index.js` di `app/produk/` | Bukan halaman `/produk` |
| `pages/produk.js` | Pages Router |
| `app/api/produk.js` | Bukan handler; harus folder + `route.js` |
| `app/middleware.js` | Middleware tidak aktif |
| `[id].js` di `app/produk/` | Bukan dynamic App Router |
| `Error.js` | Tidak dikenali |
| `loading.jsx` | **Sah** (ekstensi JSX) |
| `notfound.js` | Tidak dikenali; harus `not-found.js` |
| `globalError.js` | Tidak; harus `global-error.js` |

---

## Lampiran file lain

Bukan sepuluh besar, tetapi convention resmi yang sering muncul.

### `icon.png`, `favicon.ico`, `apple-icon.png`

Ikon tab. Letak `app/`. Lihat [10](10-metadata-image-font.md).

### `opengraph-image.png`, `twitter-image.png`

Gambar pratinjau sosial.

### `robots.js` / `robots.txt`

Aturan crawler.

### `sitemap.js`

Daftar URL.

### `manifest.js`

PWA manifest.

### `opengraph-image.js` + `ImageResponse`

Gambar OG dinamis (`next/og`).

### intercepting route: `(.)`, `(..)`, `(..)(..)`, `(...)`

Menyadap navigasi untuk modal. Lanjutan; gabung `@slot` + `default.js`.

### Route group `(nama)`

Bukan file, tetapi folder convention. Lihat [02](02-layout-page-template-default.md).

### Private folder `_nama`

Folder diawali `_` tidak menjadi segmen URL. Berguna untuk colocation. Tetap hindari menaruh `page.js` di dalamnya jika tidak ingin URL.

---

## Urutan bersarang (mental model)

Untuk `/produk/1`:

1. `middleware.js` jika matcher cocok
2. `app/layout.js`
3. `app/template.js` jika ada
4. `app/produk/layout.js`
5. `app/produk/template.js` jika ada
6. `app/produk/[id]/layout.js` jika ada
7. `app/produk/[id]/page.js`
8. Jika page suspend → `loading.js` terdekat
9. Jika throw → `error.js` terdekat (bukan layout sama)
10. Jika `notFound()` → `not-found.js` terdekat
11. Jika root layout throw → `global-error.js`

**Biasanya digabungkan dengan:** membaca output `next build` untuk memastikan file terdaftar.

---

## Checklist “file apa yang kuharus buat?”

| Kebutuhan | File |
| --- | --- |
| URL baru | `page.js` di folder itu |
| Navbar bersama | `layout.js` |
| Skeleton | `loading.js` |
| API rusak | `error.js` |
| ID tidak ada | `notFound()` + `not-found.js` |
| JSON API | `route.js` |
| Pagar /admin | `middleware.js` di root |
| Reset state setiap pindah | `template.js` |
| Modal slot | `@modal` + `default.js` |

---

## Lihat juga

- [01 — pohon folder](01-install-struktur-app.md)
- [02 — layout/page/template/default](02-layout-page-template-default.md)
- [14 — error saat file salah nama](14-kesalahan-dan-resep.md)

---

Sebelum: [12 — Tailwind](12-tailwind-css-modules.md) · Berikut: [14 — kesalahan dan resep](14-kesalahan-dan-resep.md)
