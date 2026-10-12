# 03 — Link, hooks navigasi, redirect, notFound

[← 02 layout](02-layout-page-template-default.md) · [Berikut: Server dan Client Component →](04-server-client-component.md)

**Untuk apa:** memindahkan pengguna antar URL App Router, membaca URL saat ini, dan menghentikan render dengan pengalihan atau 404.

Daftar API di file ini, **satu per satu**:

1. [`Link`](#1-link)
2. [`useRouter`](#2-userouter)
3. [`usePathname`](#3-usepathname)
4. [`useSearchParams`](#4-usesearchparams)
5. [`useParams`](#5-useparams)
6. [`redirect`](#6-redirect)
7. [`notFound`](#7-notfound)
8. [`permanentRedirect`](#8-permanentredirect)

Impor yang benar:

```js
import Link from "next/link";
import { useRouter, usePathname, useSearchParams, useParams } from "next/navigation";
import { redirect, notFound, permanentRedirect } from "next/navigation";
```

Jangan mengimpor `useRouter` dari `next/router` — itu Pages Router.

## 1. Link

**Untuk apa:** tautan internal yang di-prefetch dan tidak me-reload seluruh dokumen.

```jsx
import Link from "next/link";

export default function Navigasi() {
  return (
    <nav aria-label="Navigasi utama">
      <Link href="/">Beranda</Link>{" "}
      <Link href="/produk">Produk</Link>{" "}
      <Link href="/produk/1">Detail contoh</Link>
    </nav>
  );
}
```

Simpan misalnya sebagai `app/components/Navigasi.js`, lalu render dari layout.

### `href` — tujuan

Wajib. String atau objek URL.

```jsx
<Link href="/produk">Produk</Link>
<Link href="/produk?q=buku">Cari buku</Link>
<Link href="/produk#katalog">Lompat ke katalog</Link>
<Link
  href={{
    pathname: "/produk",
    query: { q: "css", halaman: "2" },
  }}
>
  CSS halaman 2
</Link>
```

Dynamic:

```jsx
function TautanProduk({ id, nama }) {
  return <Link href={`/produk/${id}`}>{nama}</Link>;
}
```

### `replace`

**Untuk apa:** mengganti entri history, bukan menambah.

```jsx
<Link href="/login" replace>
  Masuk
</Link>
```

Cocok setelah alur yang tidak ingin pengguna kembali ke halaman kedaluwarsa lewat tombol Back.

### `scroll`

**Untuk apa:** mengontrol apakah viewport di-scroll ke atas (atau ke hash).

```jsx
<Link href="/produk" scroll={false}>
  Produk tanpa scroll ke atas
</Link>
```

Default `true`. `scroll={false}` berguna untuk filter di halaman panjang yang tidak boleh meloncat.

### `prefetch`

**Untuk apa:** menonaktifkan atau memaksa prefetch.

```jsx
<Link href="/admin" prefetch={false}>
  Admin
</Link>
```

Default: prefetch saat tautan mendekati viewport (perilaku bisa bergantung versi dan perangkat). Matikan untuk tautan jarang atau di belakang autentikasi jika kamu tidak ingin data admin di-prefetch.

### `passHref` dan `legacyBehavior`

Warisan Pages Router / komponen custom `<a>`. Di App Router modern, bungkus komponen yang sudah merender `<a>` dengan hati-hati, atau taruh `Link` sebagai induk dan pakai `className` langsung di `Link`.

```jsx
<Link href="/produk" className="teks-biru">
  Produk
</Link>
```

`Link` di App Router merender `<a>`. Kamu boleh memberi `className`, `aria-*`, `target`, `rel`.

### `target` dan tautan luar

```jsx
<Link href="https://nextjs.org/docs" target="_blank" rel="noreferrer">
  Dokumentasi Next.js
</Link>
```

Untuk URL luar, `<a href="...">` juga sah. `Link` tetap boleh.

### Menu aktif? Bukan tugas Link sendiri

`Link` tidak punya prop `active`. Baca path dengan `usePathname` (entri 3).

### Link di Server Component

Boleh. `Navigasi` tanpa hook adalah Server Component yang valid.

### Yang tidak boleh

- `href` kosong atau `href="#"` sebagai pengganti tombol.
- Menaruh `onClick` berat untuk navigasi biasa — utamakan `href`.
- Mengganti semua `<button>` dengan `Link`. Tombol = aksi; tautan = pindah URL.

**Biasanya digabungkan dengan:** `layout.js`, daftar produk, dan `usePathname` untuk gaya aktif.

---

## 2. useRouter

**Untuk apa:** memindahkan halaman dari **kode**, bukan dari tautan, di Client Component.

```jsx
"use client";

import { useRouter } from "next/navigation";

export default function TombolProduk() {
  const router = useRouter();

  return (
    <button type="button" onClick={() => router.push("/produk")}>
      Lihat produk
    </button>
  );
}
```

`useRouter` hanya jalan di Client Component. Memanggilnya di Server Component error.

### `router.push(href)`

Menambah history, seperti klik `Link`.

```js
router.push("/produk");
router.push("/produk?q=buku");
router.push(`/produk/${id}`);
```

### `router.replace(href)`

Mengganti history, analog `Link replace`.

```js
router.replace("/login");
```

Pakai setelah login berhasil agar tombol Back tidak kembali ke form login.

### `router.refresh()`

**Untuk apa:** merender ulang payload Server Component **tanpa** mengubah URL.

```jsx
"use client";

import { useRouter } from "next/navigation";

export default function TombolSegarkan() {
  const router = useRouter();
  return (
    <button type="button" onClick={() => router.refresh()}>
      Segarkan data
    </button>
  );
}
```

Berguna setelah mutasi jika kamu tidak memakai `revalidatePath` / `revalidateTag`. Tidak me-reload dokumen penuh seperti `location.reload()`.

### `router.back()`

Satu langkah mundur di history. Sama seperti tombol Back.

```js
router.back();
```

Jika tidak ada history dalam (misalnya pengguna buka detail dari tab baru), `back()` bisa keluar dari situs. Lebih aman:

```jsx
"use client";

import { useRouter } from "next/navigation";

export default function Kembali({ cadangan = "/produk" }) {
  const router = useRouter();

  function handleKembali() {
    if (window.history.length > 1) router.back();
    else router.push(cadangan);
  }

  return (
    <button type="button" onClick={handleKembali}>
      Kembali
    </button>
  );
}
```

`window.history.length` tidak selalu sempurna, tetapi cukup untuk latihan.

### `router.forward()`

Satu langkah maju. Jarang dipakai di UI toko.

### `router.prefetch(href)`

Prefetch manual.

```js
router.prefetch("/produk/1");
```

Umumnya tidak perlu; `Link` sudah mem-prefetch.

### Yang tidak ada di `next/navigation`

Objek `router` App Router **tidak** punya `router.query`, `router.pathname`, `router.asPath` seperti Pages Router. Ganti dengan:

- path → `usePathname`
- query → `useSearchParams`
- params dinamis → `useParams`

### Kapan Link cukup, kapan push

- Menu, kartu produk, breadcrumb → `Link` (bisa diklik kanan, dibuka tab baru, dibaca crawler).
- Setelah submit, setelah cek syarat, setelah timeout → `router.push` / `replace`.

**Biasanya digabungkan dengan:** `"use client"`, form, dan `router.refresh()` setelah ubah data.

---

## 3. usePathname

**Untuk apa:** membaca path saat ini, tanpa query string.

```jsx
"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";

export default function Navigasi() {
  const path = usePathname();

  return (
    <nav aria-label="Navigasi utama">
      <Link href="/" aria-current={path === "/" ? "page" : undefined}>
        Beranda
      </Link>{" "}
      <Link
        href="/produk"
        aria-current={path === "/produk" || path.startsWith("/produk/") ? "page" : undefined}
      >
        Produk
      </Link>
    </nav>
  );
}
```

Satu per satu:

- `/` → `"/"`
- `/produk` → `"/produk"`
- `/produk/1` → `"/produk/1"`
- `/produk?q=buku` → tetap `"/produk"` (query tidak ikut)
- Hash tidak ikut

### Menu aktif yang rapi

```jsx
const tautan = [
  { href: "/", label: "Beranda", exact: true },
  { href: "/produk", label: "Produk", exact: false },
  { href: "/tentang", label: "Tentang", exact: true },
];

function aktif(path, href, exact) {
  if (exact) return path === href;
  return path === href || path.startsWith(`${href}/`);
}
```

### Jangan dipakai di Server Component

Tidak ada `usePathname` di server. Untuk logika server berdasarkan URL, pakai `params` di page, atau `headers()` / middleware.

**Biasanya digabungkan dengan:** `Link`, layout navbar, dan CSS class kondisional / Tailwind.

---

## 4. useSearchParams

**Untuk apa:** membaca query string di Client Component, misalnya `?q=buku&halaman=2`.

```jsx
"use client";

import { useSearchParams } from "next/navigation";

export default function RingkasanCari() {
  const searchParams = useSearchParams();
  const q = searchParams.get("q") ?? "";
  const halaman = searchParams.get("halaman") ?? "1";

  return (
    <p>
      Kata: {q || "(kosong)"} — halaman {halaman}
    </p>
  );
}
```

### Metode `URLSearchParams`, satu per satu

Objeknya mirip `URLSearchParams`:

- `get("q")` — nilai pertama, atau `null`
- `getAll("tag")` — array, berguna untuk `?tag=js&tag=css`
- `has("q")` — boolean
- `keys()`, `values()`, `entries()` — iterator
- `toString()` — `"q=buku&halaman=2"`
- `size` — jumlah pasangan

Tidak ada `searchParams.q` sebagai properti biasa. Selalu `.get("q")`.

### Mengubah query tanpa merusak yang lain

`useSearchParams` **hanya baca**. Untuk menulis, gabungkan dengan `useRouter` + `usePathname`:

```jsx
"use client";

import { usePathname, useRouter, useSearchParams } from "next/navigation";

export default function Urutan() {
  const router = useRouter();
  const path = usePathname();
  const searchParams = useSearchParams();

  function ubahUrutan(nilai) {
    const params = new URLSearchParams(searchParams.toString());
    params.set("urut", nilai);
    router.push(`${path}?${params.toString()}`);
  }

  return (
    <select
      value={searchParams.get("urut") ?? "nama"}
      onChange={(event) => ubahUrutan(event.target.value)}
    >
      <option value="nama">Nama</option>
      <option value="harga">Harga</option>
    </select>
  );
}
```

`new URLSearchParams(searchParams.toString())` menyalin query lama agar `q` tidak hilang saat `urut` berubah.

### Wajib dibungkus Suspense

Di banyak versi App Router, `useSearchParams()` membuat subtree di-de-opt ke render klien dan **harus** dibungkus `<Suspense>` agar `loading.js` / static rendering tidak pecah.

`app/produk/page.js`:

```jsx
import { Suspense } from "react";
import RingkasanCari from "../components/RingkasanCari";

export default function HalamanProduk() {
  return (
    <main>
      <h1>Produk</h1>
      <Suspense fallback={<p>Menyiapkan filter…</p>}>
        <RingkasanCari />
      </Suspense>
    </main>
  );
}
```

Jika build memperingatkan tentang `useSearchParams` dan missing Suspense, ini penyebabnya.

### Alternatif server: prop `searchParams` di page

Untuk filter yang diolah di server, **lebih sederhana** await `searchParams` di `page.js` — lihat [06](06-searchParams-loading-error-not-found.md). Pakai hook ini jika interaksi klien (ketikan, select) harus membaca URL.

**Biasanya digabungkan dengan:** `useRouter`, `usePathname`, `<Suspense>`, dan form `GET`.

---

## 5. useParams

**Untuk apa:** membaca segmen dinamis di Client Component.

Untuk URL `/produk/1` dari `app/produk/[id]/page.js`:

```jsx
"use client";

import { useParams } from "next/navigation";

export default function LabelId() {
  const params = useParams();
  const id = params.id;

  return <p>ID produk: {id}</p>;
}
```

Satu per satu:

- `[id]` → `params.id` string, misalnya `"1"`
- `[...slug]` → `params.slug` **array**, misalnya `["buku", "js"]`
- `[[...slug]]` → `params.slug` array atau `undefined` jika URL tanpa sisa segmen

### Server versus klien

Di `page.js` / `layout.js` server:

```jsx
export default async function Detail({ params }) {
  const { id } = await params;
  return <main>{id}</main>;
}
```

Di Client Component anak: `useParams()`. Jangan mengharapkan hook di server, jangan mengharapkan `await params` di klien.

### Nilai selalu string (atau array of string)

`/produk/1` memberi `"1"`, bukan angka `1`. Bandingkan dengan data memakai `String(item.id) === id` atau `Number(id)`.

**Biasanya digabungkan dengan:** tombol klien di halaman detail, dan fetch klien ke `/api/produk/${id}` jika memang diperlukan.

---

## 6. redirect

**Untuk apa:** memaksa pindah URL dari **server** (komponen, Server Action, Route Handler) sebelum atau di tengah render.

```jsx
import { redirect } from "next/navigation";

export default function Admin() {
  const boleh = false;
  if (!boleh) redirect("/login");
  return <main>Panel admin</main>;
}
```

### Perilaku

- Melempar error khusus yang ditangkap Next.js — **jangan** bungkus `redirect()` dengan `try/catch` yang menelan semua error, atau pengalihan gagal.
- Mengirim status **307** (sementara) secara default.
- Boleh dipanggil sebelum `return`, termasuk setelah `await` data.

### Setelah cek data

```jsx
import { redirect } from "next/navigation";

export default async function HalamanLama({ params }) {
  const { slug } = await params;
  if (slug === "js-lama") redirect("/produk?q=javascript");
  return <main>Artikel {slug}</main>;
}
```

### Dari Server Action

```js
"use server";

import { redirect } from "next/navigation";

export async function masuk(formData) {
  const email = String(formData.get("email") ?? "");
  if (email === "admin@toko.test") {
    redirect("/admin");
  }
  redirect("/login?error=1");
}
```

### Bukan untuk klien

Di Client Component, pakai `router.push` / `router.replace`. Memanggil `redirect()` di event klik tidak didukung seperti di server.

### Versus middleware versus `next.config`

| Alat | Kapan |
| --- | --- |
| `redirect()` | Keputusan setelah baca data/sesi di server komponen atau action |
| `middleware.js` | Keputusan **sebelum** halaman, berdasarkan cookie/path |
| `next.config` `redirects` | URL lama → URL baru yang tetap |

**Biasanya digabungkan dengan:** cek cookie sesi, Server Action login, dan halaman yang sudah pindah slug.

---

## 7. notFound

**Untuk apa:** menghentikan halaman dan merender `not-found.js` terdekat (404).

```jsx
import { notFound } from "next/navigation";

const produk = [
  { id: "1", nama: "Buku JavaScript" },
  { id: "2", nama: "Buku CSS" },
];

export default async function DetailProduk({ params }) {
  const { id } = await params;
  const item = produk.find((row) => row.id === id);
  if (!item) notFound();
  return (
    <main>
      <h1>{item.nama}</h1>
    </main>
  );
}
```

### Perilaku

- Seperti `redirect`, `notFound()` melempar. Jangan ditelan `try/catch`.
- Next.js merender `not-found.js` di segmen terdekat, atau `app/not-found.js`.
- Status HTTP 404.

### Kapan dipanggil

- ID tidak ada di database.
- Slug salah eja dan tidak ada alias.
- Pengguna meminta sumber yang dihapus.

Jangan pakai `notFound()` untuk “belum boleh lihat” — itu biasanya 403 + `redirect("/login")` atau halaman terlarang. 404 = “tidak ada”.

### UI-nya di file terpisah

`app/not-found.js` atau `app/produk/not-found.js`. Lihat [06](06-searchParams-loading-error-not-found.md) dan [13](13-katalog-file-convention.md).

**Biasanya digabungkan dengan:** `find()`, `fetch` yang 404, dan `not-found.js` ramah.

---

## 8. permanentRedirect

**Untuk apa:** pengalihan **permanen** (308) agar penanda buku dan mesin telusur pindah ke URL baru.

```jsx
import { permanentRedirect } from "next/navigation";

export default async function SlugLama({ params }) {
  const { id } = await params;
  if (id === "buku-js-lama") {
    permanentRedirect("/produk/1");
  }
  return <main>Produk {id}</main>;
}
```

### `redirect` versus `permanentRedirect`

| Fungsi | Status | Arti |
| --- | --- | --- |
| `redirect(url)` | 307 | Sementara: “kali ini ke sini” |
| `permanentRedirect(url)` | 308 | Permanen: “URL ini pindah selamanya” |

Pakai permanen hanya jika URL lama **benar-benar** pensiun. Jangan memakai 308 untuk “belum login”. Browser dan cache bisa mengingat pengalihan permanen lebih lama dari yang kamu kira.

### Dari action

```js
"use server";

import { permanentRedirect } from "next/navigation";

export async function pindahToko() {
  permanentRedirect("/produk");
}
```

Sama-sama melempar; jangan di-`catch`.

**Biasanya digabungkan dengan:** migrasi slug, ganti struktur katalog, dan `redirects` di `next.config.mjs` untuk daftar tetap.

---

## Tabel keputusan cepat

| Kebutuhan | API |
| --- | --- |
| Tautan menu / kartu | `Link` |
| Menu aktif | `Link` + `usePathname` |
| Pindah setelah klik logika | `useRouter().push` |
| Ganti URL tanpa jejak | `Link replace` atau `router.replace` |
| Segarkan data server | `router.refresh` atau `revalidatePath` |
| Baca `?q=` di klien | `useSearchParams` |
| Baca `?q=` di server | `await searchParams` di `page.js` |
| Baca `[id]` di klien | `useParams` |
| Baca `[id]` di server | `await params` |
| Wajib login / pindah sementara | `redirect` |
| URL pensiun | `permanentRedirect` |
| Data tidak ada | `notFound` |

## Resep navbar lengkap

`app/components/Navigasi.js`:

```jsx
"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";

const menu = [
  { href: "/", label: "Beranda" },
  { href: "/produk", label: "Produk" },
  { href: "/tentang", label: "Tentang" },
];

export default function Navigasi() {
  const path = usePathname();

  return (
    <nav aria-label="Navigasi utama">
      {menu.map((item) => {
        const current =
          item.href === "/"
            ? path === "/"
            : path === item.href || path.startsWith(`${item.href}/`);
        return (
          <Link
            key={item.href}
            href={item.href}
            aria-current={current ? "page" : undefined}
            className={current ? "font-bold" : undefined}
          >
            {item.label}
          </Link>
        );
      })}
    </nav>
  );
}
```

**Biasanya digabungkan dengan:** root layout dan sedikit Tailwind.

## Resep “lihat detail” dari tombol klien

Hanya jika memang harus tombol, bukan kartu tautan:

```jsx
"use client";

import { useRouter } from "next/navigation";

export default function LihatDetail({ id }) {
  const router = useRouter();
  return (
    <button type="button" onClick={() => router.push(`/produk/${id}`)}>
      Detail
    </button>
  );
}
```

Lebih baik:

```jsx
import Link from "next/link";

export default function LihatDetail({ id }) {
  return <Link href={`/produk/${id}`}>Detail</Link>;
}
```

## Kesalahan umum navigasi

- Impor `next/router` di App Router.
- `useSearchParams` tanpa `Suspense`.
- `useRouter` di Server Component.
- Membandingkan `params.id === 1` (number) padahal `"1"`.
- `try/catch` di sekitar `redirect()` / `notFound()`.
- `permanentRedirect` untuk halaman login.
- Menggunakan `window.location.href` untuk pindah internal — kehilangan prefetch App Router.
- Mengira `usePathname()` menyertakan `?q=`.

**Biasanya digabungkan dengan:** [04](04-server-client-component.md) karena hampir semua hook di atas membutuhkan `"use client"`.

## Lihat juga

- [06 — searchParams, loading, error, not-found](06-searchParams-loading-error-not-found.md)
- [11 — middleware rewrite redirect](11-env-middleware-rewrite-redirect.md)

---

Sebelum: [02 — layout](02-layout-page-template-default.md) · Berikut: [04 — Server dan Client Component](04-server-client-component.md)
