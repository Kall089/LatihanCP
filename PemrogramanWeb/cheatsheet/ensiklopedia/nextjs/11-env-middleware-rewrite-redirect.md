# 11 — Env, middleware, rewrite, redirect

[← 10 metadata](10-metadata-image-font.md) · [Berikut: Tailwind dan CSS Modules →](12-tailwind-css-modules.md)

**Untuk apa:** memisahkan konfigurasi per mesin, menjaga rute sebelum halaman dirender, dan mengalihkan atau mem-proxy URL.

Tiga lapisan pengalihan yang sering tertukar:

| Lapisan | File | Kapan jalan | Cocok untuk |
| --- | --- | --- | --- |
| `redirect()` / `permanentRedirect()` | komponen, action, handler | Saat kode server jalan | Cek data/sesi |
| `middleware.js` | root proyek | Sebelum banyak request | Cookie + path |
| `redirects` / `rewrites` di config | `next.config.mjs` | Saat match URL | URL lama, proxy API |

## Daftar isi file ini

- [.env dan nama file](#env-dan-nama-file)
- [NEXT_PUBLIC_ versus server-only](#next_public_-versus-server-only)
- [Membaca process.env](#membaca-processenv)
- [middleware.js](#middlewarejs)
- [matcher](#matcher)
- [NextResponse.next, redirect, rewrite](#nextresponsenext-redirect-rewrite)
- [Membaca cookie dan header di middleware](#membaca-cookie-dan-header-di-middleware)
- [redirects di next.config](#redirects-di-nextconfig)
- [rewrites di next.config](#rewrites-di-nextconfig)
- [Urutan eksekusi](#urutan-eksekusi)
- [Resep jaga /admin](#resep-jaga-admin)
- [Kesalahan umum](#kesalahan-umum)

## .env dan nama file

**Untuk apa:** tidak menuliskan URL dan rahasia di kode.

Letak: **root proyek** (sejajar `package.json`), bukan di `app/`.

| File | Dipakai | Commit? |
| --- | --- | --- |
| `.env` | Semua lingkungan, nilai non-rahasia | Kadang, jika tidak ada secret |
| `.env.local` | Mesinmu, menimpa `.env` | **Tidak** |
| `.env.development` | Hanya `next dev` | Opsional |
| `.env.production` | `next build` / `next start` | Hati-hati |
| `.env.example` | Daftar kunci tanpa nilai rahasia | Ya |

Contoh `.env.local`:

```dotenv
API_BASE_URL=http://127.0.0.1:8000
NEXT_PUBLIC_NAMA_TOKO=Toko Belajar
```

Tanpa spasi di sekitar `=`. Tanpa tanda kutip kecuali nilai membutuhkannya. Tanpa garis miring akhir pada URL jika kamu menuliskan `${baseUrl}/api/...`.

Restart `npm run dev` setelah mengubah env. Nilai lama tetap di proses yang sudah hidup.

`.gitignore` harus memuat `.env*.local` dan biasanya `.env`. Commit `.env.example`:

```dotenv
API_BASE_URL=
NEXT_PUBLIC_NAMA_TOKO=
```

**Biasanya digabungkan dengan:** fetch server dan teks merek di UI.

## NEXT_PUBLIC_ versus server-only

**Untuk apa:** mencegah rahasia masuk bundle browser.

- **Tanpa awalan** (`API_BASE_URL`, `DATABASE_URL`, `RAHASIA_WEBHOOK`): hanya server (Server Component, Route Handler, Server Action, middleware terbatas).
- **`NEXT_PUBLIC_`**: disisipkan ke bundle klien. Anggap publik. Siapa pun bisa membaca di DevTools.

Salah:

```dotenv
NEXT_PUBLIC_KUNCI_ADMIN=rahasia123
```

Benar:

```dotenv
KUNCI_ADMIN=rahasia123
NEXT_PUBLIC_NAMA_TOKO=Toko Belajar
```

Jangan mengirim `process.env.KUNCI_ADMIN` sebagai props ke Client Component.

Di middleware Edge, tidak semua env otomatis tersedia tergantung versi/host. Uji `process.env.API_BASE_URL` di middleware; jika kosong, pakai cookie-only guard atau dukung env di config host.

**Biasanya digabungkan dengan:** [04](04-server-client-component.md) tentang serialisasi.

## Membaca process.env

```jsx
export default async function Halaman() {
  const baseUrl = process.env.API_BASE_URL;
  if (!baseUrl) throw new Error("API_BASE_URL belum diatur");
  const namaToko = process.env.NEXT_PUBLIC_NAMA_TOKO ?? "Toko";
  return <h1>{namaToko}</h1>;
}
```

Klien:

```jsx
"use client";

export default function Cap() {
  return <p>{process.env.NEXT_PUBLIC_NAMA_TOKO}</p>;
}
```

Nilai di-inline saat build untuk `NEXT_PUBLIC_*`. Mengubah `.env.production` tanpa rebuild tidak mengubah bundle lama.

**Biasanya digabungkan dengan:** pesan error yang jelas jika env hilang, memicu `error.js`.

## middleware.js

**Untuk apa:** menjalankan kode **sebelum** request selesai ke page/handler, berdasarkan path.

Letak: **root** (`middleware.js` sejajar `app/`), atau `src/middleware.js` jika memakai `src/`. Bukan `app/middleware.js`.

```js
import { NextResponse } from "next/server";

export function middleware(request) {
  if (request.nextUrl.pathname.startsWith("/admin")) {
    return NextResponse.redirect(new URL("/login", request.url));
  }
}

export const config = { matcher: ["/admin/:path*"] };
```

Ini **contoh pola**, bukan auth sungguhan. Tanpa cek cookie, semua orang yang tahu `/login` masih belum terlindungi, dan `/admin` selalu dialihkan — termasuk admin sah.

Middleware berjalan di runtime Edge (umumnya). Batasan:

- Tidak semua modul Node (`fs`, beberapa paket berat).
- Hindari pekerjaan mahal / query DB langsung.
- Jaga cepat; dijalankan di banyak request.

**Biasanya digabungkan dengan:** cookie sesi dan `matcher` sempit.

## matcher

**Untuk apa:** membatasi middleware agar tidak jalan di semua aset.

```js
export const config = {
  matcher: ["/admin/:path*", "/login"],
};
```

Atau menghindari file statis:

```js
export const config = {
  matcher: ["/((?!_next/static|_next/image|favicon.ico).*)"],
};
```

`:path*` artinya sisa segmen. `/admin` dan `/admin/produk` cocok ke `/admin/:path*` tergantung pola; uji.

Matcher terlalu luas + redirect ceroboh = loop (`/login` → `/login` → …). Selalu kecualikan tujuan redirect.

**Biasanya digabungkan dengan:** daftar path yang benar-benar perlu dijaga.

## NextResponse.next, redirect, rewrite

### `NextResponse.next()`

Lanjutkan ke tujuan semula. Boleh menyisipkan header:

```js
export function middleware(request) {
  const response = NextResponse.next();
  response.headers.set("x-toko", "belajar");
  return response;
}
```

### `NextResponse.redirect(url)`

Ubah URL di address bar (klien mengikuti pengalihan).

```js
return NextResponse.redirect(new URL("/login", request.url));
```

Status default 307. Argumen kedua bisa `{ status: 308 }` untuk permanen — jarang di middleware auth.

### `NextResponse.rewrite(url)`

Tetap menampilkan URL lama, tetapi isi dari URL lain.

```js
if (request.nextUrl.pathname === "/katalog") {
  return NextResponse.rewrite(new URL("/produk", request.url));
}
```

Pengguna melihat `/katalog`, page yang jalan `app/produk/page.js`.

Rewrite ke backend:

```js
const url = request.nextUrl.clone();
// hati-hati: rewrite ke origin lain bergantung host
return NextResponse.rewrite(new URL("http://127.0.0.1:8000/api/produk"));
```

Untuk proxy API yang tetap, `rewrites` di `next.config` lebih jelas.

**Biasanya digabungkan dengan:** A/B path, URL cantik, dan jaga admin.

## Membaca cookie dan header di middleware

```js
import { NextResponse } from "next/server";

export function middleware(request) {
  const sesi = request.cookies.get("sesi")?.value;
  const path = request.nextUrl.pathname;

  const menujuAdmin = path.startsWith("/admin");
  const menujuLogin = path.startsWith("/login");

  if (menujuAdmin && !sesi) {
    const login = new URL("/login", request.url);
    login.searchParams.set("dari", path);
    return NextResponse.redirect(login);
  }

  if (menujuLogin && sesi) {
    return NextResponse.redirect(new URL("/admin", request.url));
  }

  return NextResponse.next();
}

export const config = {
  matcher: ["/admin/:path*", "/login"],
};
```

Set cookie sesi di Route Handler / Server Action login, bukan di middleware kecuali kamu tahu dampaknya.

Baca header:

```js
const ua = request.headers.get("user-agent");
```

Jangan memakai middleware sebagai tempat bisnis berat.

**Biasanya digabungkan dengan:** [08](08-route-handler-http.md) `cookies().set` saat POST login.

## redirects di next.config

**Untuk apa:** daftar pengalihan tetap, tanpa cookie.

```js
/** @type {import('next').NextConfig} */
const nextConfig = {
  async redirects() {
    return [
      { source: "/toko", destination: "/produk", permanent: true },
      { source: "/buku/:id", destination: "/produk/:id", permanent: true },
      { source: "/lama/:path*", destination: "/baru/:path*", permanent: false },
    ];
  },
};

export default nextConfig;
```

- `permanent: true` → 308
- `permanent: false` → 307
- Parameter `:id` dan `:path*` diteruskan

Pakai ini untuk URL yang sudah diumumkan / dicatat mesin telusur. Jangan pakai untuk “jika belum login”.

**Biasanya digabungkan dengan:** [03](03-link-navigation-hooks.md) `permanentRedirect` untuk kasus per-data.

## rewrites di next.config

**Untuk apa:** proxy atau alias tanpa mengubah address bar.

```js
const nextConfig = {
  async rewrites() {
    return [
      {
        source: "/backend/:path*",
        destination: "http://127.0.0.1:8000/:path*",
      },
    ];
  },
};

export default nextConfig;
```

`fetch("/backend/api/produk")` dari klien menuju Laravel, menghindari CORS di development jika dikonfigurasi benar.

Rewrites bisa dibagi `beforeFiles`, `afterFiles`, `fallback` pada bentuk lanjutan. Untuk latihan, array datar cukup.

Risiko: mengekspos backend secara tidak sengaja. Jangan me-rewrite seluruh `/` ke asal tak dikenal.

**Biasanya digabungkan dengan:** Laravel di port 8000 dan fetch klien.

## Urutan eksekusi

Gambaran praktis (disederhanakan):

1. Headers / redirects / rewrites di `next.config` (sebagian sebelum file).
2. `middleware.js` jika matcher cocok.
3. Route Handler atau render App Router (`layout` → `page`).
4. `redirect()` / `notFound()` di dalam render/action.

Jika middleware redirect ke `/login` dan config juga rewrite `/login`, uji manual. Loop hampir selalu matcher + redirect ke path yang masih di-match dengan kondisi yang sama.

**Biasanya digabungkan dengan:** log sementara `console.log(request.nextUrl.pathname)` di middleware (hapus sebelum kumpul jika berisik).

## Resep jaga /admin

1. Login action/handler set cookie `sesi` httpOnly.
2. Middleware: tanpa cookie + path `/admin` → `/login?dari=...`.
3. Page `/admin` **tetap** cek sesi di server (cookie bisa dipalsu jika nilainya lemah). Middleware adalah pagar pertama, bukan satu-satunya.
4. Logout: hapus cookie + `redirect("/")`.

`app/login/page.js`:

```jsx
import { masuk } from "../aksi-auth";

export const metadata = { title: "Masuk", robots: { index: false } };

export default async function Login({ searchParams }) {
  const { dari = "/admin" } = await searchParams;
  return (
    <main>
      <h1>Masuk</h1>
      <form action={masuk}>
        <input type="hidden" name="dari" value={String(dari)} />
        <input name="email" type="email" required />
        <input name="sandi" type="password" required />
        <button type="submit">Masuk</button>
      </form>
    </main>
  );
}
```

`app/aksi-auth.js` (latihan, **bukan** produksi):

```js
"use server";

import { cookies } from "next/headers";
import { redirect } from "next/navigation";

export async function masuk(formData) {
  const email = String(formData.get("email") ?? "");
  const sandi = String(formData.get("sandi") ?? "");
  const dari = String(formData.get("dari") ?? "/admin");

  if (email !== "admin@toko.test" || sandi !== "rahasia") {
    redirect("/login?error=1");
  }

  const jar = await cookies();
  jar.set("sesi", "latihan", {
    httpOnly: true,
    sameSite: "lax",
    path: "/",
    maxAge: 60 * 60,
  });

  const tujuan = dari.startsWith("/") ? dari : "/admin";
  redirect(tujuan);
}

export async function keluar() {
  const jar = await cookies();
  jar.delete("sesi");
  redirect("/");
}
```

Jangan memakai sandi hardcoded di tugas yang di-deploy publik. Ini hanya kerangka.

**Biasanya digabungkan dengan:** `robots: noindex` dan layout admin tanpa navbar toko (`(auth)` group).

## Environment di Docker / CI

Set kunci yang sama di panel host (Vercel/env CI). `.env.local` tidak ikut ke server orang lain.

Bedakan:

- `API_BASE_URL` di server Next menuju Laravel internal
- `NEXT_PUBLIC_API_BASE_URL` hanya jika browser harus memanggil Laravel langsung (CORS)

**Biasanya digabungkan dengan:** `.env.example` di repositori tugas.

## Kesalahan umum

- Commit `.env.local` berisi rahasia.
- `NEXT_PUBLIC_` pada kunci admin.
- `app/middleware.js` — tidak jalan.
- Redirect loop `/login`.
- Mengandalkan middleware saja tanpa cek di page.
- Rewrite ke Laravel lalu heran cookie domain beda.
- Lupa restart setelah ubah env.
- `redirects` permanen saat masih eksperimen — cache browser menahan 308.
- Membaca `cookies()` di middleware dari `next/headers` dengan cara page; di middleware pakai `request.cookies`.

## Checklist

1. `.env.example` ada; `.env.local` tidak di git.
2. Server-only untuk URL backend.
3. Middleware matcher sempit.
4. Tidak ada loop.
5. Page terlindungi tetap memverifikasi sesi.
6. URL lama memakai `next.config` redirects, bukan middleware rumit.

## Lihat juga

- [03 — redirect, permanentRedirect](03-link-navigation-hooks.md)
- [08 — cookies di Route Handler](08-route-handler-http.md)
- [01 — next.config](01-install-struktur-app.md)

---

Sebelum: [10 — metadata](10-metadata-image-font.md) · Berikut: [12 — Tailwind dan CSS Modules](12-tailwind-css-modules.md)
