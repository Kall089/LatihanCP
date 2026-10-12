# 06 — searchParams, loading, error, not-found

[← 05 dynamic route](05-dynamic-route-catch-all-optional.md) · [Berikut: fetch dan cache →](07-fetch-cache-revalidate.md)

**Untuk apa:** membaca query string di server, menampilkan status menunggu, menangkap kegagalan, dan merender 404 yang ramah.

Empat topik ini sering datang bersamaan: halaman daftar memakai `?q=`, bersifat async, bisa gagal, dan detail bisa tidak ketemu.

## Daftar isi file ini

- [searchParams di page.js](#searchparams-di-pagejs)
- [Form GET yang menulis query](#form-get-yang-menulis-query)
- [searchParams versus useSearchParams](#searchparams-versus-usesearchparams)
- [loading.js](#loadingjs)
- [Suspense manual](#suspense-manual)
- [error.js](#errorjs)
- [global-error.js](#global-errorjs)
- [not-found.js](#not-foundjs)
- [reset, notFound, dan error — kapan mana](#reset-notfound-dan-error--kapan-mana)
- [Resep daftar + filter + loading + error](#resep-daftar--filter--loading--error)
- [Kesalahan umum](#kesalahan-umum)

## searchParams di page.js

**Untuk apa:** mengolah `/produk?q=buku&urut=harga` di Server Component.

```jsx
export default async function HalamanProduk({ searchParams }) {
  const { q = "", urut = "nama" } = await searchParams;
  const kata = String(q).toLowerCase();
  const kunciUrut = String(urut);

  return (
    <main>
      <h1>Hasil untuk: {kata || "semua"}</h1>
      <p>Urutan: {kunciUrut}</p>
    </main>
  );
}
```

Satu per satu:

- `searchParams` adalah Promise di Next 15+ — **wajib await**.
- Nilai query adalah string, array of string (jika kunci berulang), atau `undefined`.
- `?q=buku` → `{ q: "buku" }`
- `?tag=js&tag=css` bisa menjadi `{ tag: ["js", "css"] }` — selalu normalkan dengan `Array.isArray` atau `String()`.
- Query tidak membuat folder baru. File tetap `app/produk/page.js`.
- **Tidak tersedia di `layout.js`.**

### Normalisasi aman

```js
function satuNilai(nilai) {
  if (Array.isArray(nilai)) return String(nilai[0] ?? "");
  return String(nilai ?? "");
}

export default async function Halaman({ searchParams }) {
  const sp = await searchParams;
  const q = satuNilai(sp.q);
  const halaman = Number(satuNilai(sp.halaman) || "1");
  return <p>{q} / {halaman}</p>;
}
```

`Number("")` adalah `0`; lebih aman `|| "1"`.

### Filter di server

```jsx
const semua = [
  { id: "1", nama: "Buku JavaScript" },
  { id: "2", nama: "Buku CSS" },
  { id: "3", nama: "Buku Laravel" },
];

export default async function HalamanProduk({ searchParams }) {
  const { q = "" } = await searchParams;
  const kata = String(q).toLowerCase();
  const hasil = semua.filter((item) => item.nama.toLowerCase().includes(kata));

  return (
    <main>
      <h1>Produk</h1>
      {hasil.length === 0 ? <p>Tidak ada yang cocok.</p> : (
        <ul>
          {hasil.map((item) => (
            <li key={item.id}>{item.nama}</li>
          ))}
        </ul>
      )}
    </main>
  );
}
```

Ini pencarian yang bisa di-bookmark dan di-refresh. Untuk ketikan per huruf tanpa pindah URL, tetap pakai state klien.

**Biasanya digabungkan dengan:** `<form action="/produk" method="get">` dan `Link href="/produk?q=buku"`.

## Form GET yang menulis query

**Untuk apa:** mengubah URL tanpa JavaScript.

```jsx
export default async function HalamanProduk({ searchParams }) {
  const { q = "" } = await searchParams;

  return (
    <main>
      <form action="/produk" method="get">
        <label>
          Cari
          <input name="q" defaultValue={String(q)} />
        </label>
        <button type="submit">Cari</button>
      </form>
    </main>
  );
}
```

`action="/produk"` + `method="get"` menghasilkan `/produk?q=...`. Input tanpa `name` tidak ikut.

Beberapa filter:

```jsx
<form action="/produk" method="get">
  <input name="q" defaultValue={String(q)} />
  <select name="urut" defaultValue={String(urut)}>
    <option value="nama">Nama</option>
    <option value="harga">Harga</option>
  </select>
  <button type="submit">Terapkan</button>
</form>
```

`defaultValue` (uncontrolled) cocok karena setiap submit me-reload page server. Jangan campur `value` + `onChange` tanpa `"use client"`.

**Biasanya digabungkan dengan:** `loading.js` karena navigasi query memicu render ulang segmen.

## searchParams versus useSearchParams

| | Prop `searchParams` | Hook `useSearchParams` |
| --- | --- | --- |
| Tempat | `page.js` server (juga `generateMetadata`) | Client Component |
| Await | Ya (Next 15+) | Tidak; objek `URLSearchParams` |
| Akses | `const { q } = await searchParams` | `searchParams.get("q")` |
| Suspense | Tidak wajib khusus hook | Sering wajib bungkus Suspense |
| Tulis URL | Tidak; render saja | Gabung `useRouter` |

Pilih server jika hasil filter dirender sebagai HTML awal. Pilih hook jika widget klien harus membaca URL yang berubah-ubah.

Rincian hook: [03](03-link-navigation-hooks.md#4-usesearchparams).

**Biasanya digabungkan dengan:** satu sumber kebenaran = URL, bukan state yang menyimpang dari address bar.

## loading.js

**Untuk apa:** fallback otomatis saat `page.js` (atau children) ditangguhkan.

`app/produk/loading.js`:

```jsx
export default function Loading() {
  return <p role="status">Memuat produk...</p>;
}
```

Satu per satu:

- Nama harus `loading.js` / `loading.jsx`.
- Berlaku untuk segmen folder itu dan anaknya, sebagai batas Suspense.
- Tidak perlu `"use client"` jika hanya markup statis.
- Muncul saat navigasi ke segmen itu jika page async belum selesai.
- **Tidak** menggantikan layout segmen yang sama. Layout tetap terlihat; yang diganti biasanya page.
- Boleh skeleton, bukan hanya teks.

Skeleton sederhana:

```jsx
export default function Loading() {
  return (
    <section aria-busy="true" aria-live="polite">
      <p className="sr-only">Memuat produk</p>
      <div className="h-8 w-48 animate-pulse bg-slate-200" />
      <div className="mt-4 h-24 animate-pulse bg-slate-200" />
      <div className="mt-2 h-24 animate-pulse bg-slate-200" />
    </section>
  );
}
```

`loading.js` di `app/produk/` tidak menutupi `app/layout.js`. Navbar tetap ada.

Jika fetch sangat cepat, pengguna mungkin tidak melihat loading. Itu normal.

**Biasanya digabungkan dengan:** page async + `fetch`, dan skeleton yang meniru layout daftar.

## Suspense manual

**Untuk apa:** membagi bagian lambat tanpa menunggu seluruh page.

```jsx
import { Suspense } from "react";
import DaftarProduk from "./DaftarProduk";
import Ulasan from "./Ulasan";

export default function HalamanProduk() {
  return (
    <main>
      <h1>Produk</h1>
      <Suspense fallback={<p>Memuat daftar…</p>}>
        <DaftarProduk />
      </Suspense>
      <Suspense fallback={<p>Memuat ulasan…</p>}>
        <Ulasan />
      </Suspense>
    </main>
  );
}
```

`DaftarProduk` dan `Ulasan` adalah Server Component async. Page bisa segera mengirim kerangka.

`loading.js` adalah Suspense implisit untuk seluruh page segmen. Suspense manual lebih halus.

Komponen yang memakai `useSearchParams` juga sering wajib dibungkus Suspense — lihat [03](03-link-navigation-hooks.md).

**Biasanya digabungkan dengan:** streaming HTML dan beberapa fetch independen.

## error.js

**Untuk apa:** menangkap error render di segmen (dan anaknya), lalu menampilkan UI pulih.

`app/produk/error.js`:

```jsx
"use client";

export default function ErrorProduk({ error, reset }) {
  return (
    <section>
      <h2>Produk belum bisa dimuat</h2>
      <p>{error?.message ?? "Terjadi kesalahan."}</p>
      <button type="button" onClick={() => reset()}>
        Coba lagi
      </button>
    </section>
  );
}
```

Satu per satu:

- **Wajib `"use client"`.**
- Props: `error` (objek Error) dan `reset` (fungsi).
- `reset()` mencoba merender ulang isi batas error.
- Menangkap error di **page dan komponen anak**, bukan otomatis error di `layout.js` **segmen yang sama**. Error layout ditangani batas di atasnya.
- Tidak menangkap error event klik / fetch klien yang kamu tulis sendiri — itu tetap `try/catch` di handler.
- Jangan menampilkan stack trace ke pengguna di produksi. `error.message` pun bisa terlalu teknis; lebih aman pesan generik + log.

Contoh tanpa membocorkan detail:

```jsx
"use client";

import { useEffect } from "react";

export default function ErrorProduk({ error, reset }) {
  useEffect(() => {
    console.error(error);
  }, [error]);

  return (
    <section>
      <h2>Produk belum bisa dimuat</h2>
      <button type="button" onClick={() => reset()}>Coba lagi</button>
    </section>
  );
}
```

Lempar error dari page agar batas ini hidup:

```jsx
export default async function HalamanProduk() {
  const response = await fetch("https://contoh.test/api/produk", { cache: "no-store" });
  if (!response.ok) throw new Error("Data produk gagal dimuat");
  const produk = await response.json();
  return <ul>{produk.map((item) => <li key={item.id}>{item.nama}</li>)}</ul>;
}
```

`throw` di Server Component → `error.js`. `notFound()` → `not-found.js`, bukan `error.js`.

**Biasanya digabungkan dengan:** `fetch` yang bisa gagal, dan tombol reset.

## global-error.js

**Untuk apa:** menangkap error yang meruntuhkan **root layout**.

`app/global-error.js`:

```jsx
"use client";

export default function GlobalError({ error, reset }) {
  return (
    <html lang="id">
      <body>
        <h1>Aplikasi bermasalah</h1>
        <p>Coba muat ulang.</p>
        <button type="button" onClick={() => reset()}>Coba lagi</button>
      </body>
    </html>
  );
}
```

Satu per satu:

- Wajib `"use client"`.
- Wajib membawa `<html>` dan `<body>` sendiri karena menggantikan root layout.
- Jarang terpanggil jika `app/error.js` sudah ada dan error-nya di page.
- `error` jangan ditampilkan mentah ke pengguna.

Tanpa `global-error.js`, kegagalan root memakai UI default Next.js.

**Biasanya digabungkan dengan:** root layout yang juga fetch (umumnya hindari fetch rapuh di root).

## not-found.js

**Untuk apa:** UI 404, baik URL tidak cocok maupun `notFound()` dipanggil.

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

`app/produk/not-found.js` hanya untuk cabang `/produk/*` ketika `notFound()` dipanggil di cabang itu. URL yang sama sekali tidak cocok ke file mana pun memakai `app/not-found.js`.

Satu per satu:

- Boleh Server Component (tidak wajib `"use client"`).
- Dipicu `notFound()` dari `next/navigation`.
- Juga dipicu jika tidak ada `page.js` yang cocok (404 kerangka).
- Boleh `Link`, tidak boleh mengandalkan `useRouter` tanpa jadi klien.
- Status HTTP 404.

Detail produk:

```jsx
import { notFound } from "next/navigation";

export default async function Detail({ params }) {
  const { id } = await params;
  const item = await ambilProduk(id);
  if (!item) notFound();
  return <main><h1>{item.nama}</h1></main>;
}
```

Jangan memakai `error.js` untuk “id tidak ada”. Itu bukan kegagalan teknis; itu 404.

**Biasanya digabungkan dengan:** dynamic route dan pesan tautan pulang.

## reset, notFound, dan error — kapan mana

| Situasi | Mekanisme | File UI |
| --- | --- | --- |
| Jaringan/API 500 | `throw new Error(...)` | `error.js` |
| Root layout pecah | throw di root | `global-error.js` |
| ID tidak ada | `notFound()` | `not-found.js` |
| URL tidak terdaftar | otomatis | `app/not-found.js` |
| Sedang menunggu | Suspense | `loading.js` atau fallback |
| Data sukses tetapi kosong | **bukan** error | UI “Belum ada produk” di page |

Daftar kosong ≠ error ≠ 404. Contoh: `/produk?q=xyzxyz` menampilkan “Tidak ada yang cocok”, status 200.

**Biasanya digabungkan dengan:** keputusan sadar di `if` sebelum throw.

## Resep daftar + filter + loading + error

Struktur:

```text
app/produk/
├── page.js
├── loading.js
├── error.js
└── not-found.js
```

`page.js`:

```jsx
import Link from "next/link";

async function ambilProduk(q) {
  const baseUrl = process.env.API_BASE_URL;
  if (!baseUrl) throw new Error("API_BASE_URL belum diatur");
  const url = new URL("/api/produk", baseUrl);
  if (q) url.searchParams.set("q", q);
  const response = await fetch(url, { cache: "no-store" });
  if (!response.ok) throw new Error("Data produk gagal dimuat");
  return response.json();
}

export default async function HalamanProduk({ searchParams }) {
  const { q = "" } = await searchParams;
  const kata = String(q);
  const produk = await ambilProduk(kata);

  return (
    <main>
      <h1>Produk</h1>
      <form action="/produk" method="get">
        <input name="q" defaultValue={kata} />
        <button type="submit">Cari</button>
      </form>
      {produk.length === 0 ? (
        <p>Tidak ada yang cocok.</p>
      ) : (
        <ul>
          {produk.map((item) => (
            <li key={item.id}>
              <Link href={`/produk/${item.id}`}>{item.nama}</Link>
            </li>
          ))}
        </ul>
      )}
    </main>
  );
}
```

`loading.js` dan `error.js` seperti contoh di atas. `not-found.js` di folder ini berguna jika kamu memanggil `notFound()` dari page daftar (jarang). Lebih sering `not-found.js` ada di `[id]/`.

**Biasanya digabungkan dengan:** backend Laravel yang menerima `?q=`.

## loading.js tidak jalan?

Periksa:

- File ada di folder segmen yang dinavigasi, bukan hanya di root, jika kamu berharap skeleton cabang.
- Page memang async / ditangguhkan. Page sinkron tanpa await hampir tidak pernah menampilkan loading.
- Navigasi memakai `Link` / router App Router, bukan `<a>` full reload — full reload tetap bisa menampilkan loading, tetapi rasanya seperti dokumen baru.
- Fetch di Client Component `useEffect` **tidak** memicu `loading.js`. Itu state lokal; tulis `if (loading)` sendiri.

**Biasanya digabungkan dengan:** memindahkan fetch ke Server Component.

## error.js tidak menangkap?

- Error di event handler klien.
- Error di `setTimeout` tanpa batas.
- Error di root layout (butuh `global-error` atau `error.js` di atasnya — root tidak punya “atas” kecuali global).
- `notFound()` — sengaja bukan error boundary.

**Biasanya digabungkan dengan:** `try/catch` di `onClick` dan pesan inline.

## Kesalahan umum

- Lupa `await searchParams`.
- Membaca `searchParams` di layout.
- Memakai `value={q}` pada input di Server Component tanpa handler.
- Menganggap daftar kosong sebagai 404.
- `error.js` tanpa `"use client"`.
- `global-error.js` tanpa `<html>`/`<body>`.
- Menampilkan `error.stack` ke pengguna.
- Mengira `loading.js` memantau fetch klien.
- `try/catch` yang menelan `notFound()` / `redirect()`.

## Lihat juga

- [03 — notFound, useSearchParams](03-link-navigation-hooks.md)
- [07 — kapan throw karena fetch](07-fetch-cache-revalidate.md)
- [13 — kamus file](13-katalog-file-convention.md)

---

Sebelum: [05 — dynamic route](05-dynamic-route-catch-all-optional.md) · Berikut: [07 — fetch, cache, revalidate](07-fetch-cache-revalidate.md)
