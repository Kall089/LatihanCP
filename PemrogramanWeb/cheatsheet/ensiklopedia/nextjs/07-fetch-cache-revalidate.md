# 07 — fetch, cache, dan revalidate

[← 06 searchParams & status](06-searchParams-loading-error-not-found.md) · [Berikut: Route Handler →](08-route-handler-http.md)

**Untuk apa:** mengambil data di server, mengontrol apakah hasilnya boleh diingat, dan menyegarkan data setelah berubah.

File ini mengasumsikan **Cache Components tidak aktif**. Kebijakan cache `fetch` berubah antara Next 14 dan Next 15+. Baca subtitel versi sebelum menyalin opsi.

Rujukan: [Fetching data](https://nextjs.org/docs/app/getting-started/fetching-data).

## Daftar isi file ini

- [fetch di Server Component](#fetch-di-server-component)
- [Menangani respons yang gagal](#menangani-respons-yang-gagal)
- [Jangan fetch Route Handler sendiri dari server](#jangan-fetch-route-handler-sendiri-dari-server)
- [Perilaku default cache: Next 14 vs 15+](#perilaku-default-cache-next-14-vs-15)
- [cache: "no-store"](#cache-no-store)
- [cache: "force-cache"](#cache-force-cache)
- [next.revalidate](#nextrevalidate)
- [next.tags](#nexttags)
- [revalidatePath](#revalidatepath)
- [revalidateTag](#revalidatetag)
- [unstable_cache / cache function](#unstable_cache--cache-function)
- [cookies, headers, dan cache](#cookies-headers-dan-cache)
- [Deduplikasi fetch](#deduplikasi-fetch)
- [Parallel fetch](#parallel-fetch)
- [Segment config: dynamic, revalidate, fetchCache](#segment-config-dynamic-revalidate-fetchcache)
- [Resep toko + Laravel](#resep-toko--laravel)
- [Kesalahan umum](#kesalahan-umum)

## fetch di Server Component

**Untuk apa:** mengambil JSON sebelum HTML selesai.

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
      {produk.length === 0 ? (
        <p>Belum ada produk.</p>
      ) : (
        <ul>
          {produk.map((item) => (
            <li key={item.id}>{item.nama}</li>
          ))}
        </ul>
      )}
    </main>
  );
}
```

Satu per satu:

- Hanya di Server Component (atau Server Action / Route Handler).
- `API_BASE_URL` tanpa garis miring akhir.
- `cache: "no-store"` = selalu data baru; aman untuk latihan yang datanya sering berubah.
- `throw` memicu `error.js`.
- Array kosong ditampilkan sebagai pesan, bukan error.

Variabel lingkungan: [11](11-env-middleware-rewrite-redirect.md). Backend contoh: [Laravel](../../laravel.md).

**Biasanya digabungkan dengan:** `loading.js`, `error.js`, dan komponen kartu presentasi.

## Menangani respons yang gagal

**Untuk apa:** membedakan 404, 401, dan 500.

```jsx
import { notFound, redirect } from "next/navigation";

async function ambilProduk(id) {
  const baseUrl = process.env.API_BASE_URL;
  const response = await fetch(`${baseUrl}/api/produk/${id}`, { cache: "no-store" });

  if (response.status === 404) notFound();
  if (response.status === 401) redirect("/login");
  if (!response.ok) throw new Error("Data produk gagal dimuat");

  return response.json();
}
```

Jangan mengandalkan `response.json()` pada body HTML error. Cek `ok` dulu.

Timeout native `fetch` terbatas; untuk tugas kuliah, gagal jaringan cukup dilempar.

**Biasanya digabungkan dengan:** `notFound()`, `redirect()`, `error.js`.

## Jangan fetch Route Handler sendiri dari server

**Untuk apa:** menghindari hop HTTP ke host sendiri.

Salah pola latihan:

```jsx
// di app/produk/page.js pada http://localhost:3000
const res = await fetch("http://localhost:3000/api/produk");
```

Masalah: URL absolut rapuh di deploy, dan kamu memutar ke Route Handler yang mungkin hanya membungkus data yang bisa diakses langsung.

Benar:

- Server Component memanggil Laravel / database / modul `lib/ambil-produk.js`.
- Route Handler untuk **klien**, webhook, atau pihak luar.

Pengecualian: kamu memang butuh menguji HTTP publik, atau handler berisi logika yang tidak ingin diduplikasi — tetap pikirkan dua kali.

**Biasanya digabungkan dengan:** `app/lib/produk.js` yang dipakai page dan, jika perlu, `route.js`.

## Perilaku default cache: Next 14 vs 15+

**Untuk apa:** tidak kaget ketika data “aneh-aneh tidak berubah”.

| Versi | Default `fetch` di App Router |
| --- | --- |
| Next 14 | Sering **di-cache** (mirip `force-cache`) kecuali dinamis |
| Next 15+ | **Tidak di-cache** secara default (lebih mirip `no-store`) |

Karena itu:

- Contoh latihan di ensiklopedia ini **menulis opsi secara eksplisit**.
- Jangan menggabungkan `cache: "no-store"` dengan `next: { revalidate: 60 }` pada permintaan yang sama.
- Cocokkan dengan versi di `package.json`.

Jika data latihan “macet”, tambahkan `cache: "no-store"` atau `router.refresh()` / `revalidatePath` setelah mutasi.

**Biasanya digabungkan dengan:** membaca output `next build` untuk melihat route static vs dynamic.

## cache: "no-store"

**Untuk apa:** selalu mengambil ulang. Cocok untuk stok, sesi, keranjang, dashboard.

```js
await fetch(url, { cache: "no-store" });
```

Efek samping: segmen cenderung dinamis. `loading.js` lebih sering terlihat.

**Biasanya digabungkan dengan:** data yang berubah tiap permintaan, dan halaman di belakang login.

## cache: "force-cache"

**Untuk apa:** mengingat respons sebagai data statis sampai diinvalidasi.

```js
await fetch(url, { cache: "force-cache" });
```

Cocok untuk:

- daftar kategori yang jarang berubah;
- copy halaman “tentang”;
- data publik yang boleh usang beberapa waktu jika digabung `revalidate`.

Tidak cocok untuk harga yang harus real-time, kecuali kamu punya strategi invalidasi.

**Biasanya digabungkan dengan:** `revalidatePath` setelah admin mengubah kategori.

## next.revalidate

**Untuk apa:** ISR-style — cache, lalu anggap usang setelah N detik.

```js
await fetch(url, { next: { revalidate: 60 } });
```

Artinya: paling lama 60 detik memakai salinan lama (perilaku tepat tergantung versi dan runtime). Jangan memakai ini bersama `no-store`.

`revalidate: 0` mendekati selalu dinamis. `revalidate: false` (di segment config) berarti hampir permanen.

**Biasanya digabungkan dengan:** katalog publik, berita, dan halaman marketing.

## next.tags

**Untuk apa:** menamai cache agar bisa diinvalidasi selektif.

```js
await fetch(url, { next: { tags: ["produk"] } });

await fetch(`${url}/${id}`, { next: { tags: ["produk", `produk-${id}`] } });
```

Kemudian di Server Action setelah simpan:

```js
import { revalidateTag } from "next/cache";

revalidateTag("produk");
```

Satu tag bisa menempel di banyak fetch. Jangan membuat tag per-user yang tak terbatas tanpa rencana.

**Biasanya digabungkan dengan:** `revalidateTag` di action create/update/delete.

## revalidatePath

**Untuk apa:** menandai path App Router agar request berikutnya mengambil data baru.

```js
"use server";

import { revalidatePath } from "next/cache";

export async function setelahTambahProduk() {
  revalidatePath("/produk");
  revalidatePath("/produk", "layout");
}
```

Satu per satu:

- Argumen pertama: path, misalnya `/produk` atau `/produk/1`.
- Argumen kedua opsional: `"page"` (default) atau `"layout"` (ikutkan layout).
- Tidak mengirim pengguna ke path itu; hanya invalidasi cache.
- Untuk pindah URL, tetap `redirect()`.

Pakai setelah mutasi jika page memakai cache / data server yang tertinggal.

**Biasanya digabungkan dengan:** Server Action form tambah produk.

## revalidateTag

**Untuk apa:** invalidasi berdasarkan tag, bukan path.

```js
"use server";

import { revalidateTag } from "next/cache";

export async function setelahUbahProduk(id) {
  revalidateTag("produk");
  revalidateTag(`produk-${id}`);
}
```

Cocok jika satu tag dipakai di beranda, daftar, dan sitemap.

Pada Next 15, beberapa overloads menambah opsi profil cache. Untuk latihan, panggilan satu argumen cukup; cocokkan dokumentasi versi jika TypeScript mengeluh.

**Biasanya digabungkan dengan:** `next: { tags }` pada `fetch`.

## unstable_cache / cache function

**Untuk apa:** meng-cache hasil fungsi yang **bukan** `fetch` (query database, hitung mahal).

Nama API bergeser antarversi (`unstable_cache` di `next/cache`). Pola konseptual:

```js
import { unstable_cache } from "next/cache";

export const ambilProdukCached = unstable_cache(
  async () => {
    const response = await fetch(process.env.API_BASE_URL + "/api/produk");
    return response.json();
  },
  ["daftar-produk"],
  { revalidate: 60, tags: ["produk"] }
);
```

Pakai jika sumber datanya bukan `fetch` (misalnya client DB). Jika hanya HTTP, `fetch` + `next.revalidate` biasanya cukup.

Jangan meng-cache data yang bergantung pada cookie user tanpa memasukkan identitas ke kunci cache — kebocoran antar-user.

**Biasanya digabungkan dengan:** query Eloquent lewat API yang sudah kamu bungkus, atau modul Node database.

## cookies, headers, dan cache

**Untuk apa:** memahami mengapa halaman tiba-tiba “dinamis”.

Memanggil `cookies()` atau `headers()` di pohon render menandai permintaan sebagai dinamis. Cache `fetch` di sekitarnya bisa ikut terpengaruh.

```jsx
import { cookies } from "next/headers";

export default async function Page() {
  const jar = await cookies();
  const sesi = jar.get("sesi")?.value;
  // halaman ini bergantung pada cookie
}
```

Jangan membaca cookie “sekadarnya” di layout root jika kamu ingin banyak halaman tetap statis.

`draftMode()` juga memaksa dinamis.

**Biasanya digabungkan dengan:** [11](11-env-middleware-rewrite-redirect.md) dan halaman admin.

## Deduplikasi fetch

**Untuk apa:** memanggil URL yang sama dua kali dalam satu render tanpa dua hop jaringan.

```jsx
async function ambil(id) {
  const res = await fetch(`${process.env.API_BASE_URL}/api/produk/${id}`, {
    next: { revalidate: 60 },
  });
  return res.json();
}

export async function generateMetadata({ params }) {
  const { id } = await params;
  const item = await ambil(id);
  return { title: item.nama };
}

export default async function Page({ params }) {
  const { id } = await params;
  const item = await ambil(id);
  return <h1>{item.nama}</h1>;
}
```

Next mendeduplikasi `fetch` dengan URL + opsi yang sama selama render. Tetap ekstrak fungsi `ambil` agar tidak menyalin URL.

**Biasanya digabungkan dengan:** `generateMetadata` + page.

## Parallel fetch

**Untuk apa:** tidak menunggu beruntun jika dua sumber independen.

Lambat:

```jsx
const produk = await ambilProduk();
const kategori = await ambilKategori();
```

Lebih baik:

```jsx
const [produk, kategori] = await Promise.all([ambilProduk(), ambilKategori()]);
```

Atau pecah ke dua komponen async + `Suspense` agar yang cepat tampil dulu — [06](06-searchParams-loading-error-not-found.md).

**Biasanya digabungkan dengan:** beranda yang memuat katalog + banner.

## Segment config: dynamic, revalidate, fetchCache

**Untuk apa:** memaksa perilaku segmen dari file `page.js` / `layout.js`.

```jsx
export const dynamic = "force-dynamic";
export const revalidate = 60;
export const fetchCache = "default-no-store";
```

Satu per satu (nilai umum):

### `dynamic`

- `"auto"` — biarkan Next menyimpulkan.
- `"force-dynamic"` — selalu dinamis.
- `"error"` — error jika sesuatu memaksa dinamis (berguna untuk menangkap kebocoran).
- `"force-static"` — paksa statis jika memungkinkan.

### `revalidate` (segment)

Angka detik default untuk segmen. Berbeda dengan opsi per-`fetch`, tetapi tujuannya mirip.

### `fetchCache`

Mengontrol default cache fetch di segmen, misalnya `"default-cache"` atau `"default-no-store"`. Nama nilai bisa berbeda tipis antarversi; cek docs versi terpasang.

Untuk tugas kuliah, **lebih jelas menulis opsi di tiap `fetch`** daripada menumpuk segment config.

**Biasanya digabungkan dengan:** halaman yang harus selalu fresh (`force-dynamic`) seperti keranjang.

## Resep toko + Laravel

`.env.local`:

```dotenv
API_BASE_URL=http://127.0.0.1:8000
```

`app/lib/produk.js`:

```js
function basis() {
  const baseUrl = process.env.API_BASE_URL;
  if (!baseUrl) throw new Error("API_BASE_URL belum diatur");
  return baseUrl;
}

export async function daftarProduk(q = "") {
  const url = new URL("/api/produk", basis());
  if (q) url.searchParams.set("q", q);
  const response = await fetch(url, { cache: "no-store" });
  if (!response.ok) throw new Error("Data produk gagal dimuat");
  return response.json();
}

export async function detailProduk(id) {
  const response = await fetch(`${basis()}/api/produk/${id}`, {
    next: { tags: [`produk-${id}`] },
  });
  if (response.status === 404) return null;
  if (!response.ok) throw new Error("Data produk gagal dimuat");
  return response.json();
}
```

Page daftar memakai `daftarProduk`. Page detail memakai `detailProduk` lalu `notFound()` jika `null`. Action ubah memanggil `revalidateTag("produk-" + id)`.

**Biasanya digabungkan dengan:** CORS/API Laravel, dan tidak memakai `NEXT_PUBLIC_` untuk URL server-only kecuali klien juga harus memanggilnya.

## Kesalahan umum

- Menggabungkan `no-store` + `revalidate` pada satu fetch.
- Fetch ke `localhost:3000/api/...` dari Server Component.
- Menyimpan data user di cache tanpa kunci identitas.
- Lupa invalidasi setelah POST, lalu UI lama.
- Mengira `router.refresh()` menghapus cache HTTP di luar Next.
- `await response.json()` pada 500 HTML.
- Memakai `NEXT_PUBLIC_API` di server lalu terkejut URL terbaca browser.
- Tutorial Next 14 di proyek Next 15 tanpa menyesuaikan default cache.
- `try/catch` yang menelan `notFound()` / `redirect()`.

## Tabel keputusan cache

| Data | Opsi awal |
| --- | --- |
| Latihan yang sering diubah | `cache: "no-store"` |
| Katalog publik, boleh terlambat 1 menit | `next: { revalidate: 60 }` |
| Jarang berubah, invalidasi manual | `force-cache` + `tags` + `revalidateTag` |
| Bergantung cookie/sesi | baca `cookies()`, jangan di-cache lintas user |
| Query bukan HTTP | `unstable_cache` dengan tag |

## Lihat juga

- [08 — Route Handler](08-route-handler-http.md)
- [09 — action + revalidate](09-server-actions-form.md)
- [Cheatsheet ringkas: mengambil data](../../next-js.md)

---

Sebelum: [06 — searchParams & status](06-searchParams-loading-error-not-found.md) · Berikut: [08 — Route Handler HTTP](08-route-handler-http.md)
