# Modul 07 — Next.js App Router

> Praktikum terkait: [`../../1-pembelajaran/07-nextjs-app-router/`](../../1-pembelajaran/07-nextjs-app-router/)
> (3 bab: App Router dasar, dynamic route, server vs client component).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menjelaskan manfaat framework seperti Next.js untuk routing, rendering,
  metadata, dan optimasi produksi.
- Membaca struktur folder `app/` sebagai peta URL.
- Menulis `layout.tsx`, `page.tsx`, metadata, dan navigasi `<Link>`.
- Membuat dynamic route `[slug]`, `await params`, dan `notFound()`.
- Memilih Server vs Client Component dengan alasan, lalu menyusunnya.

**Prasyarat**: Modul 06. Next.js adalah **framework** di atas React: routing,
render di server, optimasi gambar/font, bundling.

Butuh **Node.js 20.9+**. Lihat README root paket ini untuk instalasi.

---

## 1. React murni vs Next.js

React yang dikonfigurasi sebagai aplikasi client-only (*Client-Side Rendering*):

1. Browser mengunduh HTML hampir kosong.
2. Mengunduh bundle JavaScript besar.
3. React baru membangun halaman.

Dampaknya dapat berupa loading awal lebih berat, konten awal kurang lengkap
untuk crawler tertentu, dan routing harus dipasang sendiri. Ini bukan
keterbatasan React sebagai library; hasilnya bergantung pada arsitektur dan
tooling yang dipilih.

Next.js menambahkan rangka:

| Aplikasi React client-only | Dengan Next.js |
|---|---|
| HTML awal hampir kosong | Server mengirim HTML utuh |
| Routing? pasang sendiri | Folder `app/` = URL |
| HTML awal dapat minim | Konten dapat dikirim sebagai HTML dari server |
| Optimasi manual | Image, font, code splitting bawaan |

```text
  Next.js = React UI
          + file-based routing
          + Server Components (default)
          + build produksi (`next build`)
```

Dua mode rendering yang perlu dibedakan di ujian:

- **CSR** (*Client-Side Rendering*): UI dibangun di browser. React murni.
- **SSR / RSC** (*Server-Side Rendering* / *React Server Components*): HTML
  disusun di server per request atau saat build, lalu dikirim. Next App
  Router memakai ini sebagai default.

---

## 2. Membuat proyek

```bash
npx create-next-app@latest tracker --typescript --tailwind --app
cd tracker
npm run dev          # http://localhost:3000
```

Saat wizard: App Router = ya, Tailwind = ya, TypeScript = ya, `src/` = tidak
perlu untuk praktikum (lebih sederhana tanpa `src/`).

Struktur minimum:

```text
tracker/
├── app/
│   ├── layout.tsx       kerangka SEMUA halaman (wajib)
│   ├── page.tsx         → URL /
│   └── globals.css      CSS global + directive Tailwind
├── package.json         script: dev, build, start, lint
├── next.config.ts
├── tsconfig.json
└── tailwind.config.ts   (atau @tailwind di CSS, tergantung versi)
```

Perintah:

| Perintah | Fungsi |
|---|---|
| `npm run dev` | Server pengembangan, hot reload |
| `npm run build` | Build produksi — **wajib sukses** sebelum deploy |
| `npm start` | Jalankan hasil build (simulasi produksi) |
| `npm run lint` | Cek kualitas kode bila script ESLint/Biome tersedia |

> **Catatan versi:** pada Next.js modern, gunakan linter melalui script
> proyek (`eslint` atau `biome`). `next build` dan lint adalah dua pemeriksaan
> berbeda; jalankan keduanya sebelum mengumpulkan.

---

## 3. File-based routing: folder = URL

Hanya folder yang berisi `page.tsx` (atau `page.js`) yang menjadi rute.

```text
app/
├── layout.tsx              kerangka semua halaman
├── page.tsx                →  /
├── tentang/
│   └── page.tsx            →  /tentang
├── materi/
│   ├── page.tsx            →  /materi
│   └── [slug]/
│       └── page.tsx        →  /materi/html-dasar
│                              /materi/css-dasar
├── not-found.tsx           halaman 404 kustom
└── components/             BUKAN route — tidak ada page.tsx
    └── Navbar.tsx
```

`components/` di dalam `app/` tidak jadi `/components` selama tidak ada
`page.tsx`. Banyak proyek menaruh komponen di `components/` di *root proyek*
(sejajar `app/`) agar lebih jelas. Kedua-duanya valid.

Segment dinamis memakai **kurung siku**: `[slug]`, `[id]`. Satu file
melayani banyak URL.

---

## 4. `layout.tsx`, `page.tsx`, `<Link>`, metadata

Layout membungkus page lewat `children`. Saat pindah halaman, layout
**tidak di-render ulang** — navbar tidak kedip, state layout (kalau ada)
bertahan.

```tsx
// app/layout.tsx
import type { Metadata } from "next";
import Link from "next/link";
import "./globals.css";

export const metadata: Metadata = {
  title: "Learning Tracker",
  description: "Catat progres belajar web.",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="id">
      <body>
        <header>
          <nav aria-label="Navigasi utama">
            <Link href="/">Beranda</Link>
            <Link href="/tentang">Tentang</Link>
          </nav>
        </header>
        <main>{children}</main>
      </body>
    </html>
  );
}
```

```tsx
// app/tentang/page.tsx
export default function TentangPage() {
  return <h1>Tentang Kami</h1>;
}
```

### Mengapa `<Link>`, bukan `<a>`?

`<a href="/tentang">` memicu **navigasi penuh**: unduh HTML baru, JS
dieksekusi ulang, state React hilang. `<Link>` dari `next/link` melakukan
*client-side navigation*: hanya segmen page yang berganti, plus **prefetch**
saat tautan terlihat di viewport.

Pakai `<a>` hanya untuk tautan **keluar** situs (`https://...`, `mailto:`).

### Metadata

Objek `metadata` di `layout.tsx` / `page.tsx` menjadi `<title>` dan
`<meta name="description">` — fondasi SEO. Layout mengisi default; page
bisa menimpa. Di dynamic route, pakai `generateMetadata` (fungsi async)
kalau judul tergantung data.

Ini isi praktikum `01-app-router-dasar`.

---

## 5. Dynamic route: `[slug]`

URL `/materi/css-dasar` dicocokkan ke `app/materi/[slug]/page.tsx`. Nilai
`"css-dasar"` masuk `params.slug`.

**Next.js 15+**: `params` adalah **Promise**. Wajib `await`.

```tsx
import { notFound } from "next/navigation";
import { daftarMateri } from "@/lib/data";

export function generateStaticParams() {
  return daftarMateri.map((m) => ({ slug: m.slug }));
}

export default async function DetailPage({
  params,
}: {
  params: Promise<{ slug: string }>;
}) {
  const { slug } = await params;
  const materi = daftarMateri.find((m) => m.slug === slug);
  if (!materi) notFound();

  return <h1>{materi.judul}</h1>;
}
```

Alur:

```text
1. User buka /materi/css-dasar
2. Next cocokkan folder [slug]
3. params = { slug: "css-dasar" }
4. Cari data; ketemu → render; tidak → notFound() → 404
```

`generateStaticParams` memberi tahu Next *slug mana yang diketahui saat
build*. Halaman itu bisa di-generate statis (cepat, murah di-hosting). Slug
tak dikenal tetap bisa di-handle runtime + `notFound()`.

`@/` adalah alias ke root proyek (diatur `tsconfig` `paths`). `import from
"@/lib/data"` sama dengan relatif yang panjang, lebih stabil saat file
dipindah.

Praktikum: `02-dynamic-route`.

---

## 6. Server vs Client Component

**Default = Server Component.** Tidak ada directive. File dirender di
server, JavaScript komponen itu **tidak dikirim** ke browser (kecuali yang
memang client).

Tulis `"use client"` di **baris pertama file** hanya jika butuh interaktivitas
browser.

```text
 Browser                     Server (Next.js)
    │  GET /materi/css  ──────────▶│
    │                              │ 1. cocokkan route app/
    │                              │ 2. render layout + page
    │                              │    (server component,
    │                              │     boleh await data)
    │ ◀───── HTML utuh + CSS ──────│
    │  (langsung terlihat!)        │
    │ ◀── JS client component ─────│
    │  3. hydration: tombol dkk    │
    │     jadi interaktif          │
```

| | Server (default) | Client (`"use client"`) |
|---|---|---|
| Di mana render awal? | Server | Dapat diprarender, lalu di-hydrate di browser |
| `useState` / `onClick` | Tidak | Ya |
| `async/await` data, DB, file | Ya, termasuk resource server | `fetch` boleh; DB/file server tidak boleh langsung |
| Rahasia (API key) | Aman di server | **Bocor** ke bundle |
| Cocok untuk | Halaman, daftar, detail | Form, tombol, filter, chart |

Pertanyaan kunci: *butuh `useState` atau event handler?* Tidak → biarkan
server. Ya → pecah jadi client component **kecil**, jangan seluruh halaman.

### Komposisi: server membungkus client

```tsx
// app/produk/page.tsx  — SERVER
import { getProduk } from "@/lib/data";
import TombolSuka from "@/components/TombolSuka";

export default async function Page() {
  const produk = await getProduk();
  return (
    <ul>
      {produk.map((p) => (
        <li key={p.id}>
          {p.nama}
          <TombolSuka id={p.id} />
        </li>
      ))}
    </ul>
  );
}
```

```tsx
// components/TombolSuka.tsx — CLIENT
"use client";

import { useState } from "react";

export default function TombolSuka({ id }: { id: number }) {
  const [suka, setSuka] = useState(false);
  return (
    <button onClick={() => setSuka(!suka)}>
      {suka ? "Disukai" : "Suka"} #{id}
    </button>
  );
}
```

Aturan:

- Server **boleh** import dan me-render client.
- Client **tidak** boleh import server component secara langsung. Solusi:
  kirim `children` dari server ke client wrapper.
- Props yang menyeberang batas harus **serializable** (angka, string, objek
  polos). Jangan kirim fungsi server atau instance class.

Sinyal butuh `"use client"`: `useState`, `useEffect`, `onClick`/`onChange`,
`localStorage`, `window`.

Praktikum: `03-server-client-component` (`LikeButton`).

---

## 7. Nested layout dan pengelompokan

Selain root `app/layout.tsx`, kamu bisa menaruh `layout.tsx` di dalam folder
rute. `app/materi/layout.tsx` membungkus `/materi` dan `/materi/[slug]` —
sidebar materi tetap, hanya isi yang berganti.

```text
RootLayout
  └── MateriLayout          ← hanya untuk /materi/*
        └── page atau [slug]
```

`loading.tsx` di folder yang sama menampilkan fallback saat server masih
mengambil data. `error.tsx` harus Client Component (butuh `reset` error
boundary). Untuk praktikum, `not-found.tsx` lebih prioritas daripada
`error.tsx`.

---

## 8. Kesalahan umum

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | `"use client"` di hampir semua file | Kehilangan SSR, bundle membengkak | Default server; client seperlunya |
| 2 | `useState` di server component | Error compile/runtime | Pindahkan ke file `"use client"` |
| 3 | `<a>` untuk rute internal | Full reload | `import Link from "next/link"` |
| 4 | Lupa `await params` | Object Promise ter-render / error | `const { slug } = await params` |
| 5 | Mengira setiap folder = URL | Bingung `/components` 404 atau sebaliknya | Hanya yang ada `page.tsx` |
| 6 | API key di client component | Bocor di bundle browser | Server / `.env` tanpa `NEXT_PUBLIC_` |
| 7 | Dynamic route tanpa `notFound()` | Halaman kosong/crash untuk id salah | `if (!data) notFound()` |
| 8 | Nama file `Page.tsx` | Kadang tidak terdeteksi sebagai rute | `page.tsx` huruf kecil (konvensi) |

---

## 9. Cheatsheet

```text
# Struktur
app/layout.tsx         kerangka (wajib)
app/page.tsx           → /
app/x/page.tsx         → /x
app/x/[id]/page.tsx    → /x/:id
app/not-found.tsx      404
components/            UI, bukan route

# Perintah
npx create-next-app@latest
npm run dev            localhost:3000
npm run build          produksi
```

```tsx
import Link from "next/link";
<Link href="/materi">Materi</Link>

const { slug } = await params;
if (!data) notFound();

export function generateStaticParams() {
  return daftar.map((d) => ({ slug: d.slug }));
}

export const metadata = { title: "...", description: "..." };

// Client — BARIS PERTAMA file:
"use client";
```

## Lanjut ke praktikum

Kerjakan di [`../../1-pembelajaran/07-nextjs-app-router/`](../../1-pembelajaran/07-nextjs-app-router/):

1. `01-app-router-dasar` — layout, metadata, `Link`, halaman `/tentang`.
2. `02-dynamic-route` — `[slug]`, `await params`, `notFound`, `generateStaticParams`.
3. `03-server-client-component` — `LikeButton` sebagai island client.

Uji diri: [`../../3-latihan-soal/07-nextjs-app-router/soal.md`](../../3-latihan-soal/07-nextjs-app-router/soal.md).
Gabungkan semuanya di Modul 08 dan studi kasus
[`../../4-studi-kasus/03-katalog-produk-nextjs/`](../../4-studi-kasus/03-katalog-produk-nextjs/).

## Referensi versi

- [Instalasi Next.js](https://nextjs.org/docs/app/getting-started/installation)
  — syarat Node.js, script proyek, ESLint/Biome.
- [Dynamic Segments](https://nextjs.org/docs/app/api-reference/file-conventions/dynamic-routes)
  — bentuk `params` dan akses asynchronous.
- [`generateStaticParams`](https://nextjs.org/docs/app/api-reference/functions/generate-static-params)
  — prerender rute dinamis dan perilaku parameter yang tidak didaftarkan.
