# 02 — layout, page, template, default

[← 01 instalasi](01-install-struktur-app.md) · [Berikut: Link dan navigasi →](03-link-navigation-hooks.md)

**Untuk apa:** menyusun kerangka URL. Next.js tidak memakai daftar route manual; ia membaca nama folder dan file khusus di `app/`.

Empat file di bab ini sering tertukar:

| File | Tetap hidup saat pindah anak? | Kapan dibuat ulang? | Wajib? |
| --- | --- | --- | --- |
| `layout.js` | Ya, state layout bertahan | Hanya saat segmentenya sendiri berganti | Root wajib |
| `page.js` | Tidak — ini isi URL | Setiap navigasi ke URL itu | Wajib agar URL ada |
| `template.js` | Tidak | Setiap navigasi, meski layout sama | Tidak |
| `default.js` | Fallback slot paralel | Saat slot tidak cocok | Hanya parallel route |

## Daftar isi file ini

- [page.js — halaman sebuah URL](#pagejs--halaman-sebuah-url)
- [layout.js — pembungkus yang bertahan](#layoutjs--pembungkus-yang-bertahan)
- [Root layout wajib html dan body](#root-layout-wajib-html-dan-body)
- [Nested layout](#nested-layout)
- [children satu per satu](#children-satu-per-satu)
- [Route group (folder)](#route-group-folder)
- [template.js](#templatejs)
- [default.js dan parallel route](#defaultjs-dan-parallel-route)
- [Menggabungkan layout + page + navigasi](#menggabungkan-layout--page--navigasi)
- [Yang bukan route](#yang-bukan-route)
- [Kesalahan umum layout dan page](#kesalahan-umum-layout-dan-page)

## page.js — halaman sebuah URL

**Untuk apa:** menampilkan isi sebuah alamat.

`app/page.js` menjadi `/`. `app/produk/page.js` menjadi `/produk`. `app/tentang/page.js` menjadi `/tentang`.

```jsx
export default function Beranda() {
  return (
    <main>
      <h1>Toko Belajar</h1>
      <p>Katalog buku pemrograman web.</p>
    </main>
  );
}
```

Aturan `page.js`, satu per satu:

### Nama file harus `page.js` (atau `page.jsx`)

`Page.js`, `halaman.js`, `index.js` di dalam `app/` **bukan** halaman. Huruf kecil, nama tepat `page`.

### Satu `page.js` per folder

Dua halaman di folder yang sama tidak didukung. Pecah folder.

### Default export wajib

Named export `export function Halaman()` tanpa default **tidak** jadi halaman.

### Boleh async

```jsx
export default async function HalamanProduk() {
  const data = await ambilProduk();
  return <main><h1>{data.length} produk</h1></main>;
}
```

Halaman async adalah Server Component. Cocok untuk `fetch`. Lihat [04](04-server-client-component.md) dan [07](07-fetch-cache-revalidate.md).

### Props yang dikirim Next.js

Pada Next 15+:

```jsx
export default async function Halaman({ params, searchParams }) {
  const { id } = await params;
  const { q = "" } = await searchParams;
  return <main><p>{id} / {String(q)}</p></main>;
}
```

- `params` hanya ada jika folder punya segmen dinamis (`[id]`, `[...slug]`, …).
- `searchParams` ada di `page.js` (dan beberapa API metadata), **bukan** di `layout.js`.
- Keduanya Promise — wajib `await`.

### `page.js` tidak boleh jadi Client Component hanya karena ada teks

Tulis `"use client"` hanya jika butuh state/event/hook browser. Halaman statis lebih baik tetap server.

### Metadata boleh diekspor dari page

```jsx
export const metadata = {
  title: "Produk",
  description: "Daftar buku Toko Belajar",
};

export default function HalamanProduk() {
  return <main><h1>Produk</h1></main>;
}
```

Lihat [10](10-metadata-image-font.md).

**Biasanya digabungkan dengan:** `layout.js` di folder yang sama atau di atasnya, `Link` menuju URL itu, dan kadang `loading.js`.

## layout.js — pembungkus yang bertahan

**Untuk apa:** memasang kerangka yang dipakai banyak halaman: `<html>`, navbar, footer, sidebar.

`app/layout.js`:

```jsx
import "./globals.css";
import Navigasi from "./components/Navigasi";

export const metadata = {
  title: {
    default: "Toko Belajar",
    template: "%s — Toko Belajar",
  },
};

export default function RootLayout({ children }) {
  return (
    <html lang="id">
      <body>
        <Navigasi />
        {children}
      </body>
    </html>
  );
}
```

Aturan `layout.js`, satu per satu:

### Root layout wajib

Tanpa `app/layout.js`, App Router tidak valid.

### Root layout wajib `<html>` dan `<body>`

Nested layout **jangan** mengulang `<html>` / `<body>`.

### `children` wajib dirender

Jika lupa `{children}`, semua halaman kosong.

### Layout **tidak menerima** `searchParams`

Jangan tulis:

```jsx
// SALAH
export default function Layout({ children, searchParams }) {
  // searchParams di layout tidak diisi seperti di page
}
```

Baca query di `page.js`, atau di Client Component dengan `useSearchParams`.

### Layout menerima `params` (Next 15+: di-await)

```jsx
export default async function LayoutProduk({ children, params }) {
  const { id } = await params;
  return (
    <section>
      <p>Konteks produk {id ?? "daftar"}</p>
      {children}
    </section>
  );
}
```

Pada folder tanpa segmen dinamis, `params` berupa objek kosong.

### Layout bertahan saat navigasi anak

Pindah `/produk` → `/produk/1` tidak me-remount `app/layout.js`. State Client Component di navbar **tetap**. Itu bedanya dengan `template.js`.

### Layout boleh async dan fetch

```jsx
export default async function LayoutToko({ children }) {
  const kategori = await ambilKategori();
  return (
    <div>
      <aside>
        <ul>
          {kategori.map((item) => (
            <li key={item.id}>{item.nama}</li>
          ))}
        </ul>
      </aside>
      {children}
    </div>
  );
}
```

Hati-hati: data layout di-cache mengikuti aturan fetch. Jangan menaruh data user yang sangat privat tanpa memahami cache — lihat [07](07-fetch-cache-revalidate.md).

### Layout tidak boleh jadi Client Component jika masih mengekspor `metadata`

Pecah: layout tetap server, navbar kecil `"use client"`.

**Biasanya digabungkan dengan:** komponen `Navigasi`, `globals.css`, dan nested layout per cabang (`produk`, `admin`).

## Root layout wajib html dan body

**Untuk apa:** mencegah error “missing html/body” dan memastikan `lang` serta CSS global terpasang sekali.

```jsx
export default function RootLayout({ children }) {
  return (
    <html lang="id">
      <body className="min-h-screen bg-slate-50 text-slate-900">
        {children}
      </body>
    </html>
  );
}
```

Satu per satu:

- `lang="id"` membantu aksesibilitas dan terjemahan browser.
- Impor CSS global hanya di root layout, atau kamu berisiko duplikasi aneh.
- Jangan membungkus `<html>` dengan Fragment atau `<div>`.
- Script analitik pihak ketiga sering diletakkan di sini sebagai Client Component kecil, atau lewat `metadata` / `Script` dari `next/script`.

Contoh `next/script` di root layout:

```jsx
import Script from "next/script";

export default function RootLayout({ children }) {
  return (
    <html lang="id">
      <body>
        {children}
        <Script src="https://example.com/analytics.js" strategy="afterInteractive" />
      </body>
    </html>
  );
}
```

`strategy` yang tersedia: `beforeInteractive`, `afterInteractive`, `lazyOnload`, `worker` (eksperimental). Untuk tugas kuliah, `afterInteractive` biasanya cukup.

**Biasanya digabungkan dengan:** `globals.css`, font `next/font`, dan metadata default.

## Nested layout

**Untuk apa:** kerangka khusus satu cabang tanpa merusak root.

`app/produk/layout.js`:

```jsx
import Link from "next/link";

export default function LayoutProduk({ children }) {
  return (
    <section>
      <header>
        <h1>Katalog</h1>
        <nav aria-label="Katalog">
          <Link href="/produk">Semua</Link>{" "}
          <Link href="/produk?q=javascript">JavaScript</Link>
        </nav>
      </header>
      {children}
    </section>
  );
}
```

Saat URL `/produk/1`:

1. `app/layout.js` membungkus semua.
2. `app/produk/layout.js` membungkus cabang produk.
3. `app/produk/[id]/page.js` menjadi `children` terdalam.

Layout tidak menumpuk diri sendiri: `app/produk/layout.js` tidak membungkus `app/layout.js`; yang terjadi sebaliknya.

Nested layout **tidak** perlu `<html>`.

**Biasanya digabungkan dengan:** sidebar cabang, breadcrumb, dan `loading.js` di folder yang sama.

## children satu per satu

**Untuk apa:** memahami apa yang sebenarnya masuk ke `{children}`.

- Di root layout, `children` = layout anak atau page yang aktif.
- Di `app/produk/layout.js`, `children` = `app/produk/page.js` atau layout/page di bawahnya.
- Kamu boleh menyelipkan markup di kiri/kanan `children`, tetapi jangan mengganti `children` dengan `null` kecuali sengaja menyembunyikan halaman.

Contoh kerangka dua kolom:

```jsx
export default function LayoutProduk({ children }) {
  return (
    <div className="grid gap-4 md:grid-cols-[16rem_1fr]">
      <aside>Filter</aside>
      <div>{children}</div>
    </div>
  );
}
```

**Biasanya digabungkan dengan:** Tailwind grid dan Client Component filter di aside.

## Route group (folder)

**Untuk apa:** mengelompokkan layout tanpa menambah segmen URL.

Folder `(nama)` **tidak** muncul di URL.

```text
app/
├── layout.js                 root
├── page.js                   /
├── (toko)/
│   ├── layout.js             navbar toko
│   ├── produk/
│   │   └── page.js           /produk   (bukan /toko/produk)
│   └── tentang/
│       └── page.js           /tentang
└── (auth)/
    ├── layout.js             layout minim, tanpa navbar toko
    ├── login/
    │   └── page.js           /login
    └── daftar/
        └── page.js           /daftar
```

`app/(toko)/layout.js`:

```jsx
import Navigasi from "../components/Navigasi";

export default function LayoutToko({ children }) {
  return (
    <div>
      <Navigasi />
      {children}
    </div>
  );
}
```

`app/(auth)/layout.js`:

```jsx
export default function LayoutAuth({ children }) {
  return (
    <div className="mx-auto max-w-sm py-16">
      {children}
    </div>
  );
}
```

Aturan route group, satu per satu:

- Nama bebas: `(toko)`, `(marketing)`, `(dashboard)`.
- Dua `page.js` jangan memperebutkan URL yang sama. `(toko)/page.js` dan `(auth)/page.js` keduanya ingin `/` — konflik.
- Root `app/page.js` dan `(toko)/page.js` juga konflik untuk `/`.
- Group boleh bersarang.

**Biasanya digabungkan dengan:** layout berbeda untuk area publik versus login, tanpa mengubah URL.

## template.js

**Untuk apa:** membungkus anak seperti layout, tetapi **instance baru setiap navigasi**.

Pakai jika kamu butuh:

- state form ter-reset saat pindah halaman di cabang yang sama;
- animasi enter/exit yang bergantung pada mount ulang;
- `useEffect` yang harus jalan lagi setiap pindah page.

`app/produk/template.js`:

```jsx
export default function TemplateProduk({ children }) {
  return <div className="template-produk">{children}</div>;
}
```

Perbedaan dengan layout, satu per satu:

| Perilaku | `layout.js` | `template.js` |
| --- | --- | --- |
| State input di pembungkus | Bertahan | Hilang (remount) |
| `useEffect` di pembungkus | Tidak ulang saat pindah anak | Ulang |
| DOM pembungkus | Di-reuse | Dibuat ulang |
| Kasus default tugas | Pakai ini | Jarang perlu |

Client template dengan key animasi sederhana:

```jsx
"use client";

import { useEffect } from "react";

export default function TemplateProduk({ children }) {
  useEffect(() => {
    document.documentElement.dataset.halaman = "produk";
    return () => {
      delete document.documentElement.dataset.halaman;
    };
  }, []);

  return <div className="animate-masuk">{children}</div>;
}
```

Jangan mengganti `layout.js` dengan `template.js` hanya karena namanya terdengar rapi. Default yang benar adalah layout.

**Biasanya digabungkan dengan:** CSS animasi, form wizard yang harus reset, dan `"use client"` jika butuh Effect.

## default.js dan parallel route

**Untuk apa:** mengisi slot `@folder` ketika tidak ada kecocokan, terutama saat hard reload.

Parallel route memakai folder `@nama`. Ini fitur lanjutan; banyak tugas kuliah tidak memintanya. Tetap dicatat karena `default.js` hanya berarti dalam konteks ini.

```text
app/
├── layout.js
├── page.js
├── @modal/
│   ├── default.js
│   └── produk/
│       └── [id]/
│           └── page.js
└── produk/
    └── [id]/
        └── page.js
```

`app/layout.js` menerima slot sebagai props:

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

`app/@modal/default.js`:

```jsx
export default function ModalKosong() {
  return null;
}
```

Tanpa `default.js`, hard reload di URL yang tidak mengisi slot `@modal` bisa error.

Intercepting route (`(.)produk`, `(..)produk`) sering digabung dengan `@modal` untuk modal detail produk. Jika tugas tidak meminta modal URL, tunda fitur ini.

**Biasanya digabungkan dengan:** intercepting route, modal, dan `default.js` yang mengembalikan `null`.

## Menggabungkan layout + page + navigasi

**Untuk apa:** resep minimal yang sudah “terasa aplikasi”.

`app/components/Navigasi.js` — boleh Server Component jika hanya `Link`:

```jsx
import Link from "next/link";

export default function Navigasi() {
  return (
    <nav aria-label="Navigasi utama">
      <Link href="/">Beranda</Link>{" "}
      <Link href="/produk">Produk</Link>{" "}
      <Link href="/tentang">Tentang</Link>
    </nav>
  );
}
```

`app/layout.js` mengimpor navigasi. `app/page.js` hanya isi beranda. `app/produk/page.js` hanya daftar. `app/tentang/page.js`:

```jsx
export const metadata = { title: "Tentang" };

export default function Tentang() {
  return (
    <main>
      <h1>Tentang Toko Belajar</h1>
      <p>Catatan latihan pemrograman web.</p>
    </main>
  );
}
```

Jangan menaruh seluruh isi setiap halaman di dalam `layout.js`. Layout = kerangka; page = isi.

**Biasanya digabungkan dengan:** `usePathname` di Client Component jika menu aktif perlu kelas CSS — lihat [03](03-link-navigation-hooks.md).

## Yang bukan route

**Untuk apa:** menaruh komponen tanpa menciptakan URL tak sengaja.

Folder atau file berikut **tidak** menjadi URL:

- `app/components/`
- `app/lib/`
- `app/utils/`
- `app/actions.js` / `app/aksi.js`
- file CSS, `*.module.css`
- `_folder` (kadang dipakai konvensi privat — utamakan nama jelas seperti `components`)

Aman:

```text
app/components/KartuProduk.js     bukan /components
app/lib/ambil-produk.js           bukan /lib
```

Berbahaya jika tidak sengaja:

```text
app/components/page.js            menjadi /components
```

Jangan menaruh `page.js` di folder komponen.

**Biasanya digabungkan dengan:** alias `@/app/components/...` dan Server Action di `app/aksi.js`.

## Kesalahan umum layout dan page

- **Lupa `{children}`** di layout: semua halaman putih.
- **Nested layout mengulang `<html>`:** error hydrate / invalid document.
- **Mencari `searchParams` di layout:** selalu kosong/undefined; pindahkan ke page atau hook.
- **Menamai file `index.js` di `app/produk/`:** URL `/produk` tidak muncul.
- **Route group bentrok URL:** dua group menyediakan `/`.
- **Mengubah layout menjadi `"use client"` lalu mengekspor metadata:** metadata hilang/error.
- **Mengira `template.js` wajib:** tidak; hampir semua tugas cukup layout + page.
- **`default.js` tanpa parallel route:** file tidak melakukan apa pun yang kamu kira.
- **Menaruh middleware di `app/middleware.js`:** tidak jalan; pindahkan ke root.

**Biasanya digabungkan dengan:** [13](13-katalog-file-convention.md) sebagai kamus cepat dan [14](14-kesalahan-dan-resep.md) untuk pesan error lengkap.

## Ringkasan keputusan

1. Selalu ada `app/layout.js` + `app/page.js`.
2. Tambah `app/nama/page.js` untuk URL baru.
3. Tambah `layout.js` di cabang hanya jika kerangka cabang berbeda.
4. Pakai `(group)` jika kerangka berbeda tetapi URL tidak boleh bertambah.
5. Pakai `template.js` hanya jika kamu butuh remount.
6. Pakai `default.js` hanya bersama `@slot`.

## Lihat juga

- [03 — Link, hooks navigasi, redirect, notFound](03-link-navigation-hooks.md)
- [13 — katalog file convention](13-katalog-file-convention.md)

---

Sebelum: [01 — instalasi](01-install-struktur-app.md) · Berikut: [03 — Link dan navigasi](03-link-navigation-hooks.md)
