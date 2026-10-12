# 12 — Tailwind, CSS Modules, dan CSS global

[← 11 env & middleware](11-env-middleware-rewrite-redirect.md) · [Berikut: katalog file convention →](13-katalog-file-convention.md)

**Untuk apa:** mengatur tampilan di App Router tanpa mengubah file menjadi Client Component.

Class Tailwind, CSS Modules, dan CSS global **boleh** dipakai di Server Component. `"use client"` tidak wajib hanya karena ada `className`.

Cheatsheet utilitas: [css.md — Tailwind](../../css.md).

## Daftar isi file ini

- [globals.css](#globalscss)
- [Tailwind v4](#tailwind-v4)
- [Tailwind v3](#tailwind-v3)
- [Class di JSX](#class-di-jsx)
- [Class kondisional](#class-kondisional)
- [CSS Modules](#css-modules)
- [Menyusun: global + Tailwind + module](#menyusun-global--tailwind--module)
- [styled-jsx dan CSS lain](#styled-jsx-dan-css-lain)
- [Gambar dan font bersama CSS](#gambar-dan-font-bersama-css)
- [Kesalahan umum](#kesalahan-umum)

## globals.css

**Untuk apa:** reset, variabel, dan perintah Tailwind yang berlaku di seluruh situs.

Impor **sekali** dari root layout:

```jsx
import "./globals.css";

export default function RootLayout({ children }) {
  return (
    <html lang="id">
      <body>{children}</body>
    </html>
  );
}
```

Jangan mengimpor `globals.css` di setiap page. Duplikasi bisa terjadi.

Isi minimal tanpa Tailwind:

```css
*,
*::before,
*::after {
  box-sizing: border-box;
}

body {
  margin: 0;
  font-family: system-ui, sans-serif;
  line-height: 1.5;
}
```

**Biasanya digabungkan dengan:** `next/font` yang menaruh `className` di `<html>`.

## Tailwind v4

**Untuk apa:** proyek `create-next-app` baru yang memakai pipeline Tailwind 4.

`app/globals.css` biasanya:

```css
@import "tailwindcss";
```

Tidak selalu ada `tailwind.config.js`. Konfigurasi tema bisa di CSS:

```css
@import "tailwindcss";

@theme {
  --color-toko: #1d4ed8;
  --font-sans: var(--font-inter), system-ui, sans-serif;
}
```

Pakai class seperti biasa:

```jsx
export default function Kartu({ judul }) {
  return (
    <article className="rounded-xl border border-slate-200 bg-white p-4">
      <h2 className="text-lg font-bold text-slate-900">{judul}</h2>
    </article>
  );
}
```

Jika class baru tidak muncul: restart `npm run dev`, pastikan file JSX ada di folder yang di-scan (biasanya seluruh proyek).

**Biasanya digabungkan dengan:** Server Component kartu, navbar, form.

## Tailwind v3

**Untuk apa:** proyek yang masih memakai direktif lama.

`app/globals.css`:

```css
@tailwind base;
@tailwind components;
@tailwind utilities;
```

`tailwind.config.js`:

```js
/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./app/**/*.{js,jsx,mdx}",
    "./components/**/*.{js,jsx,mdx}",
  ],
  theme: {
    extend: {
      colors: {
        toko: "#1d4ed8",
      },
    },
  },
  plugins: [],
};
```

`content` wajib mencakup path file yang menulis class. Jika komponen ada di `src/`, tambahkan `./src/**/*.{js,jsx}`. Class yang hanya disusun di string aneh kadang tidak terdeteksi.

**Biasanya digabungkan dengan:** PostCSS `postcss.config.js` bawaan `create-next-app`.

## Class di JSX

**Untuk apa:** utilitas langsung di markup.

```jsx
export default function Tombol({ children }) {
  return (
    <button
      type="button"
      className="rounded-lg bg-blue-700 px-3 py-2 text-white hover:bg-blue-800"
    >
      {children}
    </button>
  );
}
```

Pola yang sering:

| Kebutuhan | Contoh class |
| --- | --- |
| Jarak | `p-4`, `mt-2`, `gap-3` |
| Flex | `flex items-center justify-between` |
| Grid katalog | `grid gap-4 sm:grid-cols-2 lg:grid-cols-3` |
| Teks | `text-sm font-medium text-slate-700` |
| Lebar | `mx-auto max-w-5xl px-4` |
| Sembunyi visual | `sr-only` |

Responsif: `md:flex`, `lg:grid-cols-3` (mobile first).

**Biasanya digabungkan dengan:** `Link` di navbar dan kartu `article`.

## Class kondisional

**Untuk apa:** menu aktif, tombol disabled, state error.

Tanpa pustaka:

```jsx
function gabung(...bagian) {
  return bagian.filter(Boolean).join(" ");
}

<Link
  href="/produk"
  className={gabung("px-2", current && "font-bold text-blue-700")}
>
  Produk
</Link>
```

`filter(Boolean)` membuang `false`. Jangan menulis `className={"px-2 " + current}` yang menghasilkan `"px-2 false"`.

Pustaka `clsx` atau `classnames` (jika terinstal):

```jsx
import clsx from "clsx";

<button className={clsx("btn", pending && "opacity-50")} />
```

Ini membutuhkan Client Component hanya jika `current` / `pending` berasal dari hook. Page server boleh menyusun class dari data.

**Biasanya digabungkan dengan:** `usePathname` di [03](03-link-navigation-hooks.md).

## CSS Modules

**Untuk apa:** class yang di-hash per file, tidak tabrakan global.

`app/produk/produk.module.css`:

```css
.judul {
  color: #1d4ed8;
}

.daftar {
  display: grid;
  gap: 1rem;
}

.daftar > li {
  border: 1px solid #e2e8f0;
  padding: 0.75rem;
}
```

```jsx
import styles from "./produk.module.css";

export default function JudulProduk() {
  return <h1 className={styles.judul}>Produk</h1>;
}
```

Aturan, satu per satu:

- Nama file harus `*.module.css`.
- Impor objek `styles`; pakai `styles.judul`, bukan string `"judul"` (kecuali kamu tahu `:global`).
- Class `daftar` menjadi sesuatu seperti `produk_daftar_abc123`.
- Komposisi: `className={`${styles.judul} ${styles.tebal}`}` atau `clsx(styles.judul, besar && styles.besar)`.
- `:global(.prose h1)` untuk menembus ke class global — jarang perlu.

Modul cocok untuk animasi atau layout yang capek ditulis utilitas.

**Biasanya digabungkan dengan:** CSS global untuk reset dan Tailwind untuk jarak cepat.

## Menyusun: global + Tailwind + module

Rekomendasi latihan:

1. **Global:** reset, variabel, `@import "tailwindcss"` / `@tailwind`.
2. **Tailwind:** navbar, grid, tombol, form, responsif.
3. **Module:** widget khusus (slider buatan sendiri, efek rumit).

Jangan menulis ulang seluruh Tailwind di module. Jangan menaruh puluhan `:global` di module.

Boleh mencampur di satu elemen:

```jsx
import styles from "./kartu.module.css";

<article className={`rounded-xl p-4 ${styles.bayangan}`}>
```

**Biasanya digabungkan dengan:** desain sistem kecil (warna toko di `@theme` atau `theme.extend`).

## styled-jsx dan CSS lain

Next mendukung `styled-jsx`:

```jsx
export default function Lencana() {
  return (
    <>
      <span className="lencana">Baru</span>
      <style jsx>{`
        .lencana {
          background: #1d4ed8;
          color: white;
          padding: 0.125rem 0.5rem;
        }
      `}</style>
    </>
  );
}
```

Untuk tugas kuliah, Tailwind atau CSS Modules lebih selaras dengan cheatsheet. `styled-jsx` disebut agar tidak kaget jika melihatnya di contoh lama.

CSS-in-JS lain (Emotion, styled-components) sering membutuhkan Client Component dan setup tambahan. Hindari kecuali tugas memaksa.

**Biasanya digabungkan dengan:** migrasi bertahap dari contoh lama.

## Gambar dan font bersama CSS

- `next/image` + `className="rounded-lg object-cover"`
- `fill` + induk `relative h-60`
- Font: [10](10-metadata-image-font.md) — `className={inter.className}` atau CSS variable + Tailwind `font-sans`

```css
@theme {
  --font-sans: var(--font-inter), ui-sans-serif, system-ui;
}
```

**Biasanya digabungkan dengan:** kartu produk yang punya gambar dan judul.

## Dark mode singkat

Tailwind class `dark:bg-slate-900` membutuhkan strategi `class` atau `media`.

v3 `tailwind.config.js`:

```js
module.exports = {
  darkMode: "class",
};
```

Lalu `<html className={gelap ? "dark" : ""}>` dari Client Component tema. Untuk tugas singkat, mode terang saja sudah cukup.

**Biasanya digabungkan dengan:** Context tema di [04](04-server-client-component.md).

## Kesalahan umum

- Class tidak muncul: file tidak masuk `content` (v3) atau server belum di-restart.
- Mengira Tailwind mewajibkan `"use client"`.
- `class` bukan `className` di JSX.
- Mengimpor `styles.judul` sebagai `"judul"` sehingga class tidak terpasang.
- Mengimpor CSS module sebagai side-effect tanpa memakai `styles`.
- Dua sistem warna (hex acak + token Tailwind) yang tidak konsisten.
- `globals.css` diimpor di Client Component dalam, memicu urutan CSS aneh.
- Menulis `hover:bg-blue-700` di string yang dipecah secara dinamis sehingga scanner v3 tidak melihat class utuh.

Scanner Tailwind (terutama v3) membaca teks sumber. Ini bisa gagal:

```js
const warna = "blue";
className={`bg-${warna}-700`}
```

Tulis class utuh: `bg-blue-700`.

**Biasanya digabungkan dengan:** [14](14-kesalahan-dan-resep.md) jika layout “pecah” setelah menambahkan Tailwind.

## Resep kerangka toko

`app/layout.js` body:

```jsx
<body className="min-h-screen bg-slate-50 text-slate-900 antialiased">
  <header className="border-b bg-white">
    <div className="mx-auto flex max-w-5xl items-center justify-between px-4 py-3">
      <Navigasi />
    </div>
  </header>
  <div className="mx-auto max-w-5xl px-4 py-6">{children}</div>
</body>
```

`app/produk/page.js` daftar:

```jsx
<ul className="grid gap-4 sm:grid-cols-2">
  {produk.map((item) => (
    <li key={item.id} className="rounded-xl border bg-white p-4 shadow-sm">
      <h2 className="font-semibold">{item.nama}</h2>
    </li>
  ))}
</ul>
```

**Biasanya digabungkan dengan:** `Link` mengelilingi kartu atau judul.

## Lihat juga

- [css.md](../../css.md)
- [10 — font dan image](10-metadata-image-font.md)
- [02 — class di layout](02-layout-page-template-default.md)

---

Sebelum: [11 — env & middleware](11-env-middleware-rewrite-redirect.md) · Berikut: [13 — katalog file convention](13-katalog-file-convention.md)
