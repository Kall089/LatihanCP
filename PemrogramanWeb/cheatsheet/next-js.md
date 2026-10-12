# Cheatsheet Next.js — App Router

[← Daftar panduan](README.md) · [Dasar React](react-js.md)

Next.js adalah framework berbasis React. Gunakan ketika kamu membutuhkan **halaman berdasarkan URL, pengambilan data di server, metadata, atau endpoint HTTP** dalam satu proyek.

## Daftar isi

- [Persiapan](#persiapan)
- [Routing dan layout](#routing-dan-layout)
- [Link dan navigasi](#link-dan-navigasi)
- [Server dan Client Component](#server-dan-client-component)
- [Dynamic route](#dynamic-route)
- [Halaman 404](#halaman-404)
- [searchParams](#searchparams)
- [Mengambil data di server](#mengambil-data-di-server)
- [Loading dan error](#loading-dan-error)
- [Tailwind di Next.js](#tailwind-di-nextjs)
- [Route Handler](#route-handler)
- [CSS Modules](#css-modules)
- [Metadata dan gambar](#metadata-dan-gambar)
- [Environment variable](#environment-variable)
- [Navigasi di Client Component](#navigasi-di-client-component)
- [Server Action](#server-action)
- [generateMetadata dan generateStaticParams](#generatemetadata-dan-generatestaticparams)
- [redirect dan middleware](#redirect-dan-middleware)
- [Kesalahan umum](#kesalahan-umum)

## Persiapan

**Untuk apa:** membuat proyek Next.js memakai JavaScript agar sejalan dengan contoh React.

```bash
npx create-next-app@latest latihan-next --js --app --eslint --no-tailwind --no-src-dir --use-npm
cd latihan-next
npm run dev
```

Jika masih muncul pertanyaan tambahan, pilihan default cukup untuk latihan ini. Siapkan Node.js yang sesuai [persyaratan Next.js](https://nextjs.org/docs/app/getting-started/installation). Buka alamat yang dicetak terminal, umumnya `http://localhost:3000`.

Contoh memakai `app/` di root. Jika proyekmu memakai `src/`, sesuaikan menjadi `src/app/`. Gunakan App Router untuk panduan ini. Biarkan **Cache Components tidak diaktifkan** agar contoh rendering dan cache berikut sesuai dengan konfigurasi latihan.

**Biasanya digabungkan dengan:** React, CSS/CSS Modules, serta database atau API backend seperti Laravel. Next.js sudah memakai React; keduanya bukan dua frontend terpisah.

## Routing dan layout

**Untuk apa:** membuat halaman dari struktur folder.

```text
app/
├── layout.js              pembungkus semua halaman
├── page.js                URL /
├── globals.css            CSS global
└── produk/
    ├── page.js            URL /produk
    └── [id]/
        └── page.js        URL /produk/1, /produk/2, ...
```

`app/layout.js`:

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

`app/page.js`:

```jsx
export default function Beranda() {
  return <main><h1>Toko Belajar</h1></main>;
}
```

`app/produk/page.js`:

```jsx
export default function HalamanProduk() {
  return <main><h1>Daftar produk</h1></main>;
}
```

Root layout harus memiliki `<html>` dan `<body>`. `children` berisi halaman atau layout anak yang sedang aktif. Buat `globals.css` jika belum tersedia.

**Biasanya digabungkan dengan:** navbar pada layout, komponen React bersama, dan folder bersarang untuk bagian aplikasi.

## Link dan navigasi

**Untuk apa:** berpindah halaman dalam aplikasi.

```jsx
import Link from "next/link";

export default function Navigasi() {
  return (
    <nav aria-label="Navigasi utama">
      <Link href="/">Beranda</Link>{" "}
      <Link href="/produk">Produk</Link>
    </nav>
  );
}
```

Simpan, misalnya, sebagai `app/components/Navigasi.js`, lalu impor dan render di layout. Gunakan `Link` untuk navigasi internal. Untuk navigasi setelah tindakan dalam Client Component, tersedia `useRouter` dari `next/navigation`, misalnya `router.push("/produk")`.

**Biasanya digabungkan dengan:** layout, detail produk, dan route dinamis.

## Server dan Client Component

**Untuk apa:** menentukan bagian yang mengerjakan data di server dan bagian yang merespons interaksi pengguna.

`page.js` dan `layout.js` secara default merupakan Server Components. Gunakan Client Component untuk state, event, dan API browser. Direktif `"use client"` diletakkan paling atas sebelum import. [Rujukan batas server/client](https://nextjs.org/docs/app/getting-started/server-and-client-components).

`app/components/TombolSuka.js`:

```jsx
"use client";

import { useState } from "react";

export default function TombolSuka() {
  const [suka, setSuka] = useState(false);
  return (
    <button type="button" aria-pressed={suka} onClick={() => setSuka((lama) => !lama)}>
      {suka ? "Disukai" : "Sukai produk"}
    </button>
  );
}
```

Ganti `app/produk/page.js` untuk mencoba pemakaiannya:

```jsx
import TombolSuka from "../components/TombolSuka";

export default function HalamanProduk() {
  return <main><h1>Buku JavaScript</h1><TombolSuka /></main>;
}
```

Server Component boleh merender Client Component. Props yang menyeberangi batas tersebut harus dapat diserialisasi React; string, angka, dan object data sederhana cocok untuk latihan. Jangan mengirim rahasia server sebagai props. Client Component juga dapat diprarender di server, jadi akses `window`/`localStorage` melalui event atau Effect.

**Biasanya digabungkan dengan:** halaman server yang mengambil data dan komponen kecil yang menangani tombol/form.

## Dynamic route

**Untuk apa:** satu file halaman melayani banyak URL berdasarkan ID/slug.

`app/produk/[id]/page.js`:

```jsx
import { notFound } from "next/navigation";

const produk = [
  { id: "1", nama: "Buku JavaScript" },
  { id: "2", nama: "Buku CSS" },
];

export default async function DetailProduk({ params }) {
  const { id } = await params;
  const item = produk.find((produk) => produk.id === id);

  if (!item) notFound();
  return <main><h1>{item.nama}</h1><p>ID: {id}</p></main>;
}
```

Folder `[id]` menangkap segmen URL, misalnya `/produk/1`. Pada pola Next.js modern, `params` dibaca secara asinkron. [Rujukan dynamic routes](https://nextjs.org/docs/app/api-reference/file-conventions/dynamic-routes).

**Biasanya digabungkan dengan:** ``<Link href={`/produk/${item.id}`}>Detail</Link>``, pencarian data berdasarkan ID, dan halaman 404.

## Halaman 404

**Untuk apa:** menampilkan pesan ramah ketika URL tidak ketemu, bukan halaman default kosong.

`app/not-found.js`:

```jsx
import Link from "next/link";

export default function TidakKetemu() {
  return (
    <main>
      <h1>Halaman tidak ada</h1>
      <p>Periksa URL atau kembali ke daftar produk.</p>
      <Link href="/produk">Lihat produk</Link>
    </main>
  );
}
```

Panggil `notFound()` dari `next/navigation` di halaman detail jika id tidak ada. File `not-found.js` di `app/` berlaku global; yang di `app/produk/` hanya untuk cabang itu.

**Biasanya digabungkan dengan:** dynamic route dan `find()` yang bisa gagal.

## searchParams

**Untuk apa:** membaca query string, misalnya `/produk?q=buku`.

```jsx
export default async function HalamanProduk({ searchParams }) {
  const { q = "" } = await searchParams;
  const kata = String(q).toLowerCase();
  return <main><h1>Hasil untuk: {kata || "semua"}</h1></main>;
}
```

Di pola Next modern, `searchParams` juga di-`await` seperti `params`. Cocok untuk pencarian yang ingin bisa di-refresh atau di-bookmark. Untuk ketikan per huruf tanpa pindah URL, tetap pakai state di Client Component.

**Biasanya digabungkan dengan:** `<form action="/produk">`, `Link href="/produk?q=buku"`, dan filter di server.

## Mengambil data di server

**Untuk apa:** mengambil data sebelum tampilan halaman selesai dibuat. Contoh ini merupakan **alternatif** isi `app/produk/page.js`, bukan tambahan di bawah export yang lama.

Siapkan backend dari [panduan Laravel](laravel.md#endpoint-api-untuk-frontend), lalu tambahkan `.env.local` seperti bagian environment variable.

```jsx
export default async function HalamanProduk() {
  const baseUrl = process.env.API_BASE_URL;
  if (!baseUrl) throw new Error("API_BASE_URL belum diatur");

  const response = await fetch(`${baseUrl}/api/produk`, { cache: "no-store" });
  if (!response.ok) throw new Error("Data produk gagal dimuat");

  const produk = await response.json();

  return (
    <main>
      <h1>Daftar produk</h1>
      {produk.length === 0 ? <p>Belum ada produk.</p> : (
        <ul>{produk.map((item) => <li key={item.id}>{item.nama}</li>)}</ul>
      )}
    </main>
  );
}
```

`cache: "no-store"` meminta data tanpa memakai cache persisten fetch. Untuk data publik yang boleh tertunda, opsi alternatif adalah `next: { revalidate: 60 }`; jangan digabung dengan `no-store` pada permintaan yang sama. Kebijakan cache harus disesuaikan dengan versi dan konfigurasi proyek. [Rujukan fetching data](https://nextjs.org/docs/app/getting-started/fetching-data).

**Biasanya digabungkan dengan:** API Laravel, `loading.js`, `error.js`, dan komponen presentasi React. Dalam Server Component, biasanya akses sumber data langsung, bukan memanggil Route Handler milik aplikasi sendiri.

## Loading dan error

**Untuk apa:** memberi tampilan saat menunggu dan saat terjadi kegagalan.

`app/produk/loading.js`:

```jsx
export default function Loading() {
  return <p role="status">Memuat produk...</p>;
}
```

`app/produk/error.js`:

```jsx
"use client";

export default function ErrorProduk({ reset }) {
  return (
    <section>
      <h2>Produk belum bisa dimuat</h2>
      <button type="button" onClick={() => reset()}>Coba lagi</button>
    </section>
  );
}
```

`error.js` menjadi batas penanganan error untuk anak segmennya; error pada layout segmen yang sama ditangani oleh batas di atasnya. Error dari handler klik/fetch client tetap perlu ditangani di kode interaksi. `reset()` mencoba merender ulang isi batas tersebut.

**Biasanya digabungkan dengan:** halaman async, API eksternal, dan pesan kosong ketika permintaan sukses tetapi tidak ada data.

## Route Handler

**Untuk apa:** menyediakan endpoint HTTP dari proyek Next.js.

`app/api/produk/route.js`:

```js
export async function GET() {
  return Response.json([
    { id: 1, nama: "Buku JavaScript", harga: 45000 },
    { id: 2, nama: "Buku CSS", harga: 40000 },
  ]);
}
```

Buka `/api/produk` untuk melihat JSON. Browser dari origin yang sama dapat meminta endpoint dengan `fetch("/api/produk")`. Contoh menggunakan array statis; data belum berasal dari database.

**Biasanya digabungkan dengan:** frontend React, webhook, atau lapisan perantara menuju layanan lain. Laravel adalah alternatif backend; tidak wajib menulis logika bisnis yang sama di dua tempat. Untuk endpoint perubahan data, tambahkan validasi, autentikasi, dan pemeriksaan izin sesuai kebutuhan.

## CSS Modules

**Untuk apa:** memberi nama class yang cakupannya dibatasi per file komponen.

`app/produk/produk.module.css`:

```css
.judul { color: #1d4ed8; }
```

Pemakaian pada komponen di folder yang sama:

```jsx
import styles from "./produk.module.css";

export default function JudulProduk() {
  return <h1 className={styles.judul}>Produk</h1>;
}
```

**Biasanya digabungkan dengan:** CSS global untuk reset/tema dan CSS Module untuk tampilan komponen.

## Tailwind di Next.js

**Untuk apa:** memakai utility class di App Router, cara yang dipakai banyak tugas proyek.

Saat `create-next-app`, pilih Tailwind. Class ditulis di JSX:

```jsx
export default function Kartu({ judul }) {
  return (
    <article className="rounded-xl border border-slate-200 bg-white p-4">
      <h2 className="text-lg font-bold text-slate-900">{judul}</h2>
    </article>
  );
}
```

`globals.css` biasanya berisi perintah `@import "tailwindcss";` (v4) atau direktif `@tailwind` (v3). Restart `npm run dev` jika class baru tidak muncul.

Navbar, grid katalog, dan tombol sering Tailwind. `"use client"` tidak wajib hanya karena ada class Tailwind.

**Biasanya digabungkan dengan:** Server Component, `Link`, dan sedikit CSS Module untuk animasi yang capek ditulis utilitas.

## Metadata dan gambar

**Untuk apa:** memberikan judul/deskripsi halaman serta menampilkan gambar dengan ukuran yang jelas.

Contoh alternatif `app/page.js`; siapkan gambar milikmu di `public/buku.jpg`:

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

Ekspor metadata dari Server Component. Ukuran gambar membantu menyiapkan ruang layout; sesuaikan rasio dengan gambar asli. Gambar dari host eksternal membutuhkan konfigurasi `remotePatterns`.

**Biasanya digabungkan dengan:** halaman produk, artikel, dan layout.

## Environment variable

**Untuk apa:** memisahkan konfigurasi antarmesin/lingkungan.

`.env.local`, di root proyek Next.js:

```dotenv
API_BASE_URL=http://127.0.0.1:8000
NEXT_PUBLIC_NAMA_TOKO=Toko Belajar
```

`API_BASE_URL` tanpa garis miring di akhir dipakai oleh fetch server pada contoh sebelumnya. Nilai berawalan `NEXT_PUBLIC_` dapat masuk ke bundle browser, jadi gunakan hanya untuk informasi publik. Simpan kredensial di variabel server, jangan kirim ke komponen client, dan jangan commit file berisi rahasia. Restart server development setelah mengubah konfigurasi jika nilainya belum terbaca.

**Biasanya digabungkan dengan:** URL backend, konfigurasi database, dan layanan server.

## Navigasi di Client Component

**Untuk apa:** pindah halaman setelah klik/logika, bukan hanya tautan statis.

```jsx
"use client";

import { usePathname, useRouter } from "next/navigation";

export default function TombolProduk() {
  const router = useRouter();
  const path = usePathname();

  return (
    <button type="button" onClick={() => router.push("/produk")}>
      Sekarang di {path}
    </button>
  );
}
```

`Link` tetap pilihan pertama untuk menu. `router.push` untuk setelah submit atau syarat terpenuhi. `usePathname` berguna menandai menu aktif.

**Biasanya digabungkan dengan:** form client, `"use client"`, dan layout navbar.

## Server Action

**Untuk apa:** menjalankan fungsi di server dari form, tanpa menulis Route Handler terpisah.

`app/aksi.js`:

```js
"use server";

export async function simpanNama(formData) {
  const nama = String(formData.get("nama") ?? "").trim();
  if (!nama) return { ok: false, pesan: "Nama wajib" };
  return { ok: true, pesan: `Tersimpan: ${nama}` };
}
```

`app/page.js`:

```jsx
import { simpanNama } from "./aksi";

export default function Halaman() {
  return (
    <form action={simpanNama}>
      <input name="nama" required />
      <button type="submit">Simpan</button>
    </form>
  );
}
```

Validasi tetap wajib. Jangan percaya input. Untuk data penting, simpan ke database/Laravel, bukan hanya `return`.

**Biasanya digabungkan dengan:** form Blade-like di Next, dan revalidate path setelah mutasi.

## generateMetadata dan generateStaticParams

**Untuk apa:** judul tab per produk, dan (opsional) pra-bangun halaman id yang sudah diketahui.

```jsx
export async function generateMetadata({ params }) {
  const { id } = await params;
  return { title: `Produk ${id}` };
}

export async function generateStaticParams() {
  return [{ id: "1" }, { id: "2" }];
}
```

Tanpa `generateStaticParams`, halaman dinamis tetap bisa dirender saat diminta.

**Biasanya digabungkan dengan:** `[id]/page.js` dan SEO sederhana.

## redirect dan middleware

**Untuk apa:** mengalihkan URL atau menjaga rute.

Di Server Component:

```jsx
import { redirect } from "next/navigation";

export default function Admin() {
  const boleh = false;
  if (!boleh) redirect("/login");
  return <main>Panel</main>;
}
```

`middleware.js` di root (sejajar `app/`):

```js
import { NextResponse } from "next/server";

export function middleware(request) {
  if (request.nextUrl.pathname.startsWith("/admin")) {
    return NextResponse.redirect(new URL("/login", request.url));
  }
}

export const config = { matcher: ["/admin/:path*"] };
```

Contoh di atas hanya pola; cek cookie/sesi sungguhan sebelum dipakai tugas login.

**Biasanya digabungkan dengan:** auth, dan halaman yang sudah pindah URL.

## Kesalahan umum

- **`useState` ditolak:** letakkan interaksi dalam Client Component dengan `"use client"`.
- **`window is not defined`:** kode mengakses API browser saat render server.
- **Halaman 404:** periksa folder route dan nama file `page.js`.
- **Tutorial berbeda:** periksa apakah memakai `pages/` (Pages Router) atau `app/` (App Router).
- **Hydration mismatch:** keluaran awal client berbeda dengan HTML server; hindari nilai acak/waktu atau storage browser langsung saat render awal.
- **Data tidak sesuai dugaan:** periksa kontrak JSON, cache, dan proses backend yang sedang berjalan.

Untuk memeriksa proyek latihan, jalankan `npm run build` dan script lint yang tersedia di `package.json`. Jangan menjalankan build dari folder cheatsheet ini karena tidak berisi aplikasi Next.js terinstal.

Latihan: buat `/tentang`, tambahkan tautannya di navigasi, lalu buat detail produk yang tidak ditemukan menampilkan 404.
