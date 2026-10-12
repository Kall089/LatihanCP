# 10 — Metadata, Image, dan Font

[← 09 Server Actions](09-server-actions-form.md) · [Berikut: env dan middleware →](11-env-middleware-rewrite-redirect.md)

**Untuk apa:** mengatur judul tab, deskripsi, ikon, gambar yang hemat layout shift, dan font yang tidak membuat teks “kedip”.

Hanya Server Component yang mengekspor `metadata` / `generateMetadata`. File `"use client"` tidak boleh mengekspor metadata.

## Daftar isi file ini

- [metadata statis](#metadata-statis)
- [title.default dan title.template](#titledefault-dan-titletemplate)
- [generateMetadata](#generatemetadata)
- [description, openGraph, twitter, robots](#description-opengraph-twitter-robots)
- [viewport dan themeColor](#viewport-dan-themecolor)
- [File convention metadata](#file-convention-metadata)
- [next/image](#nextimage)
- [Gambar remote](#gambar-remote)
- [next/font/google](#nextfontgoogle)
- [next/font/local](#nextfontlocal)
- [next/script singkat](#nextscript-singkat)
- [Kesalahan umum](#kesalahan-umum)

## metadata statis

**Untuk apa:** judul dan deskripsi yang tidak bergantung pada `params`.

`app/page.js`:

```jsx
import Image from "next/image";

export const metadata = {
  title: "Toko Belajar",
  description: "Katalog buku untuk belajar pemrograman web.",
};

export default function Beranda() {
  return (
    <main>
      <h1>Toko Belajar</h1>
      <Image src="/buku.jpg" alt="Sampul buku pemrograman" width={400} height={300} />
    </main>
  );
}
```

Siapkan `public/buku.jpg`.

Boleh diekspor dari `layout.js` sebagai default situs, lalu dioverride page.

**Biasanya digabungkan dengan:** root layout dan halaman tentang/produk.

## title.default dan title.template

**Untuk apa:** menambahkan nama toko di semua tab tanpa menulis ulang.

`app/layout.js`:

```jsx
export const metadata = {
  title: {
    default: "Toko Belajar",
    template: "%s — Toko Belajar",
  },
  description: "Toko buku pemrograman.",
};
```

`app/produk/page.js`:

```jsx
export const metadata = {
  title: "Produk",
};
```

Tab menjadi `Produk — Toko Belajar`. Halaman yang mengekspor `title: "Toko Belajar"` sebagai string utuh di root tetap memakai default.

`absolute` meniadakan template:

```jsx
export const metadata = {
  title: { absolute: "Checkout" },
};
```

**Biasanya digabungkan dengan:** nested layout cabang admin yang templatenya berbeda.

## generateMetadata

**Untuk apa:** metadata dari data dinamis.

```jsx
import { notFound } from "next/navigation";

async function ambil(id) {
  const baseUrl = process.env.API_BASE_URL;
  const response = await fetch(`${baseUrl}/api/produk/${id}`, { cache: "no-store" });
  if (response.status === 404) return null;
  if (!response.ok) throw new Error("Gagal metadata");
  return response.json();
}

export async function generateMetadata({ params, searchParams }) {
  const { id } = await params;
  const { q = "" } = await searchParams;
  const item = await ambil(id);
  if (!item) return { title: "Produk tidak ada" };
  const ekstra = String(q) ? ` (${String(q)})` : "";
  return {
    title: item.nama + ekstra,
    description: item.deskripsi ?? `Detail ${item.nama}`,
  };
}

export default async function Detail({ params }) {
  const { id } = await params;
  const item = await ambil(id);
  if (!item) notFound();
  return <main><h1>{item.nama}</h1></main>;
}
```

Satu per satu:

- Signature mirip page: `params` dan `searchParams` di-await.
- Return objek metadata, bukan JSX.
- Fetch yang sama dengan page di-dedup — [07](07-fetch-cache-revalidate.md).
- Boleh `parent` argument untuk merangkai metadata induk (lanjutan).

```jsx
export async function generateMetadata({ params }, parent) {
  const { id } = await params;
  const induk = await parent;
  return {
    title: `Produk ${id}`,
    openGraph: {
      images: induk.openGraph?.images ?? [],
    },
  };
}
```

**Biasanya digabungkan dengan:** `[id]/page.js` dan Open Graph.

## description, openGraph, twitter, robots

**Untuk apa:** cuplikan media sosial dan arahan crawler.

```jsx
export const metadata = {
  title: "Toko Belajar",
  description: "Katalog buku pemrograman web.",
  metadataBase: new URL("https://contoh-toko-belajar.test"),
  alternates: {
    canonical: "/",
  },
  openGraph: {
    title: "Toko Belajar",
    description: "Katalog buku pemrograman web.",
    url: "https://contoh-toko-belajar.test",
    siteName: "Toko Belajar",
    locale: "id_ID",
    type: "website",
    images: [{ url: "/buku.jpg", width: 800, height: 600, alt: "Sampul" }],
  },
  twitter: {
    card: "summary_large_image",
    title: "Toko Belajar",
    description: "Katalog buku pemrograman web.",
    images: ["/buku.jpg"],
  },
  robots: {
    index: true,
    follow: true,
  },
  keywords: ["buku", "javascript", "css", "nextjs"],
  authors: [{ name: "Tim Toko Belajar" }],
};
```

Satu per satu:

- `metadataBase` wajib dipikirkan agar URL relatif di OG jadi absolut. Tanpa ini, build bisa memperingatkan.
- `alternates.canonical` mencegah duplikat `/` vs `/index`.
- `openGraph.images` bisa string atau objek.
- `robots: { index: false }` untuk halaman login/admin.
- `keywords` pengaruh SEO-nya kecil; tidak wajib.

Halaman admin:

```jsx
export const metadata = {
  title: "Admin",
  robots: { index: false, follow: false },
};
```

**Biasanya digabungkan dengan:** `app/opengraph-image.png` atau `generateMetadata` per artikel.

## viewport dan themeColor

**Untuk apa:** viewport mobile dan warna UI browser.

Di Next modern, `viewport` sering diekspor terpisah, bukan di dalam `metadata`:

```jsx
export const viewport = {
  width: "device-width",
  initialScale: 1,
  themeColor: "#0f172a",
};
```

Jika gabung ke `metadata.viewport` ditolak versimu, pindahkan ke `export const viewport`.

**Biasanya digabungkan dengan:** PWA sederhana dan `app/theme-color` file convention jika ada.

## File convention metadata

**Untuk apa:** menaruh ikon dan gambar SEO sebagai file, tanpa objek.

Di `app/`:

| File | Hasil |
| --- | --- |
| `favicon.ico` | Favicon klasik |
| `icon.png` / `icon.svg` | Icon modern |
| `apple-icon.png` | Ikon iOS |
| `opengraph-image.png` | Gambar OG default |
| `twitter-image.png` | Gambar Twitter |
| `sitemap.js` / `sitemap.xml` | Peta situs |
| `robots.js` / `robots.txt` | Aturan crawler |
| `manifest.js` | Web app manifest |

Contoh `app/robots.js`:

```js
export default function robots() {
  return {
    rules: [{ userAgent: "*", allow: "/", disallow: "/admin" }],
    sitemap: "https://contoh-toko-belajar.test/sitemap.xml",
  };
}
```

Contoh `app/sitemap.js`:

```js
export default async function sitemap() {
  return [
    { url: "https://contoh-toko-belajar.test", lastModified: new Date() },
    { url: "https://contoh-toko-belajar.test/produk" },
  ];
}
```

`opengraph-image.js` dinamis (lanjutan) bisa memakai `ImageResponse` dari `next/og` untuk gambar per judul. Untuk tugas awal, file PNG di `app/` atau `public/` cukup.

**Biasanya digabungkan dengan:** `metadataBase` dan daftar URL produk.

## next/image

**Untuk apa:** menampilkan gambar dengan ukuran jelas, lazy load, dan optimasi.

```jsx
import Image from "next/image";

export default function Sampul() {
  return (
    <Image
      src="/buku.jpg"
      alt="Sampul buku pemrograman"
      width={400}
      height={300}
    />
  );
}
```

Props, satu per satu:

### `src`

Path `public/` (`/buku.jpg`), impor statis, atau URL remote yang diizinkan.

### `alt`

Wajib untuk aksesibilitas. Kosong `alt=""` hanya jika dekoratif.

### `width` dan `height`

Membantu cadangan ruang (kurangi layout shift). Sesuaikan rasio dengan file asli. Boleh dihitung dari rasio.

### `fill`

Mengisi induk yang `position: relative`. Jangan gabungkan dengan width/height angka dengan cara yang bertentangan.

```jsx
<div style={{ position: "relative", width: "100%", height: 240 }}>
  <Image src="/buku.jpg" alt="" fill sizes="100vw" style={{ objectFit: "cover" }} />
</div>
```

### `sizes`

Petunjuk lebar tampilan untuk pilih sumber. Contoh kartu grid: `sizes="(max-width: 768px) 100vw, 33vw"`.

### `priority`

Gambar LCP (hero beranda). Set `priority` agar preload. Jangan di semua gambar.

### `quality`

1–100, default sekitar 75. Naikkan hanya jika hasilnya jelek.

### `className` / `style`

Gaya pada `<img>` hasil.

### `onLoad` / `onError`

Hanya di Client Component.

### `unoptimized`

Matikan optimizer. Berguna untuk SVG tertentu atau host yang sudah mengoptimasi.

Jangan memakai `<img>` jika kamu butuh optimizer; `<img>` tetap sah untuk latihan cepat atau SVG inline.

**Biasanya digabungkan dengan:** kartu produk, hero, dan `public/`.

## Gambar remote

**Untuk apa:** `src` dari host luar.

`next.config.mjs`:

```js
const nextConfig = {
  images: {
    remotePatterns: [
      {
        protocol: "https",
        hostname: "images.unsplash.com",
        pathname: "/**",
      },
      {
        protocol: "http",
        hostname: "127.0.0.1",
        port: "8000",
        pathname: "/storage/**",
      },
    ],
  },
};

export default nextConfig;
```

```jsx
<Image
  src="https://images.unsplash.com/foto-contoh"
  alt="Contoh"
  width={800}
  height={500}
/>
```

Tanpa `remotePatterns` (atau `domains` lama), Next menolak. Restart `dev` setelah ubah config.

Jangan `hostname: "*"` semena-mena.

**Biasanya digabungkan dengan:** storage Laravel (`/storage/...`) dan Unsplash latihan.

## next/font/google

**Untuk apa:** mengunduh font saat build dan meniadakan request ke Google di runtime.

`app/layout.js`:

```jsx
import { Inter } from "next/font/google";
import "./globals.css";

const inter = Inter({
  subsets: ["latin"],
  display: "swap",
});

export default function RootLayout({ children }) {
  return (
    <html lang="id" className={inter.className}>
      <body>{children}</body>
    </html>
  );
}
```

Satu per satu:

- Impor nama font sebagai fungsi dari `next/font/google`.
- `subsets` kurangi ukuran.
- `weight` jika font bukan variable: `weight: ["400", "700"]`.
- `display: "swap"` teks tetap terlihat saat font siap.
- `variable: "--font-inter"` jika ingin memakai CSS variable, bukan `className` di `<html>`.

```jsx
const inter = Inter({ subsets: ["latin"], variable: "--font-inter" });

// html className={inter.variable}
```

```css
body {
  font-family: var(--font-inter), system-ui, sans-serif;
}
```

Beberapa font: `Roboto`, `Open_Sans` (underscore), `Merriweather`. Nama mengikuti paket.

**Biasanya digabungkan dengan:** Tailwind `font-sans` yang diarahkan ke variabel.

## next/font/local

**Untuk apa:** file font milikmu di repo.

```jsx
import localFont from "next/font/local";

const toko = localFont({
  src: [
    { path: "./fonts/Toko-Regular.woff2", weight: "400", style: "normal" },
    { path: "./fonts/Toko-Bold.woff2", weight: "700", style: "normal" },
  ],
  display: "swap",
  variable: "--font-toko",
});
```

Letakkan file di `app/fonts/` (bukan `public/` jika memakai path relatif impor). `public/` tetap bisa untuk unduhan, tetapi `next/font` lebih suka file terimpor.

**Biasanya digabungkan dengan:** lisensi font yang mengizinkan hosting sendiri.

## next/script singkat

**Untuk apa:** skrip pihak ketiga dengan strategi load.

```jsx
import Script from "next/script";

<Script src="https://example.com/analytics.js" strategy="afterInteractive" />
```

`strategy`: `beforeInteractive`, `afterInteractive`, `lazyOnload`. Jangan memasukkan skrip tak dikenal di tugas.

**Biasanya digabungkan dengan:** root layout.

## metadata dari layout versus page

Urutan gabung: root → nested layout → page. Page menang untuk `title` string. Objek seperti `openGraph` digabung mendalam (deep merge) pada banyak kunci.

Jangan mengekspor `metadata` dari Client Component. Jika page harus klien, pecah: `page.js` server mengekspor metadata dan merender anak klien, atau pakai `generateMetadata` di `page.js` yang hanya me-re-export layout anak.

Pola page klien penuh:

```text
app/produk/page.js          server, metadata + <Klien />
app/produk/Klien.js         "use client"
```

**Biasanya digabungkan dengan:** [04](04-server-client-component.md).

## Kesalahan umum

- `metadata` di file `"use client"`.
- Lupa `await params` di `generateMetadata`.
- `Image` tanpa width/height dan tanpa `fill`.
- `alt` kosong pada gambar bermakna.
- Remote image tanpa `remotePatterns`.
- `<link href="https://fonts.google...">` manual yang bertarung dengan `next/font`.
- `priority` di sepuluh gambar.
- `metadataBase` hilang lalu URL OG jadi localhost di produksi.
- Menyimpan foto besar 8 MB di `public/` tanpa kompresi.

## Checklist SEO latihan

1. Setiap page penting punya `title` unik.
2. `description` 1–2 kalimat.
3. Satu gambar hero `priority` jika ada.
4. Ikon `favicon.ico` atau `icon.png`.
5. Admin `robots: noindex`.

## Lihat juga

- [02 — metadata di layout](02-layout-page-template-default.md)
- [12 — Tailwind + class font](12-tailwind-css-modules.md)

---

Sebelum: [09 — Server Actions](09-server-actions-form.md) · Berikut: [11 — env, middleware, rewrite, redirect](11-env-middleware-rewrite-redirect.md)
