# 05 — Dynamic route, catch-all, optional catch-all

[← 04 server/client](04-server-client-component.md) · [Berikut: searchParams, loading, error →](06-searchParams-loading-error-not-found.md)

**Untuk apa:** satu file halaman melayani banyak URL. Folder bertanda kurung siku menangkap potongan path.

## Daftar isi file ini

- [Segmen dinamis [id]](#segmen-dinamis-id)
- [Beberapa segmen dinamis](#beberapa-segmen-dinamis)
- [Catch-all [...slug]](#catch-all-slug)
- [Optional catch-all [[...slug]]](#optional-catch-all-slug)
- [generateStaticParams](#generatestaticparams)
- [dynamicParams](#dynamicparams)
- [generateMetadata pada route dinamis](#generatemetadata-pada-route-dinamis)
- [params di-await (Next 15+)](#params-di-await-next-15)
- [params di layout versus page](#params-di-layout-versus-page)
- [useParams di klien](#useparams-di-klien)
- [Route Handler dinamis](#route-handler-dinamis)
- [Prioritas pencocokan URL](#prioritas-pencocokan-url)
- [Kesalahan umum](#kesalahan-umum)

## Segmen dinamis [id]

**Untuk apa:** `/produk/1`, `/produk/2`, … tanpa membuat file per id.

```text
app/produk/[id]/page.js     →  /produk/1
                               /produk/apa-saja
```

`app/produk/[id]/page.js`:

```jsx
import { notFound } from "next/navigation";

const produk = [
  { id: "1", nama: "Buku JavaScript", harga: 45000 },
  { id: "2", nama: "Buku CSS", harga: 40000 },
];

export default async function DetailProduk({ params }) {
  const { id } = await params;
  const item = produk.find((row) => row.id === id);

  if (!item) notFound();

  return (
    <main>
      <h1>{item.nama}</h1>
      <p>ID: {id}</p>
      <p>Harga: {item.harga}</p>
    </main>
  );
}
```

Satu per satu:

- Nama folder `[id]` menentukan kunci `params.id`. `[slug]` → `params.slug`.
- Nilai selalu **string**.
- Satu segmen: `/produk/1/edit` **tidak** cocok ke `[id]` saja; itu butuh folder tambahan `edit/page.js` atau catch-all.
- `[id]` tidak mencocokkan `/produk` — itu `app/produk/page.js`.

Daftar yang menautkan detail:

```jsx
import Link from "next/link";

export default function Daftar({ produk }) {
  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>
          <Link href={`/produk/${item.id}`}>{item.nama}</Link>
        </li>
      ))}
    </ul>
  );
}
```

**Biasanya digabungkan dengan:** `notFound()`, `generateMetadata`, dan `Link` dari daftar.

## Beberapa segmen dinamis

**Untuk apa:** URL bersarang seperti `/kategori/buku/produk/1`.

```text
app/kategori/[kategori]/produk/[id]/page.js
```

```jsx
export default async function Detail({ params }) {
  const { kategori, id } = await params;
  return (
    <main>
      <p>Kategori: {kategori}</p>
      <p>Produk: {id}</p>
    </main>
  );
}
```

`/kategori/buku/produk/1` → `{ kategori: "buku", id: "1" }`.

Setiap `[nama]` menambah kunci. Jangan memakai dua folder dinamis dengan nama sama di rantai yang membingungkan tanpa perlu.

**Biasanya digabungkan dengan:** breadcrumb `Link` ke `/kategori/${kategori}`.

## Catch-all [...slug]

**Untuk apa:** menangkap **satu atau lebih** sisa segmen sebagai array.

```text
app/docs/[...slug]/page.js
```

| URL | `params.slug` |
| --- | --- |
| `/docs` | tidak cocok (404 kecuali ada `app/docs/page.js`) |
| `/docs/intro` | `["intro"]` |
| `/docs/react/hooks` | `["react", "hooks"]` |
| `/docs/a/b/c` | `["a", "b", "c"]` |

```jsx
import { notFound } from "next/navigation";

export default async function Docs({ params }) {
  const { slug } = await params;
  const jejak = slug.join("/");

  if (slug.length === 0) notFound();

  return (
    <main>
      <h1>Dokumentasi</h1>
      <p>Path: {jejak}</p>
      <ol>
        {slug.map((bagian) => (
          <li key={bagian}>{bagian}</li>
        ))}
      </ol>
    </main>
  );
}
```

`slug` adalah array. Jangan menulis `slug.toUpperCase()` — itu method string.

Halaman indeks `/docs` tetap butuh `app/docs/page.js` terpisah, atau pakai optional catch-all.

**Biasanya digabungkan dengan:** dokumentasi, CMS path, dan breadcrumb dari array.

## Optional catch-all [[...slug]]

**Untuk apa:** menangkap **nol atau lebih** segmen, termasuk URL induk.

```text
app/docs/[[...slug]]/page.js
```

| URL | `params.slug` |
| --- | --- |
| `/docs` | `undefined` (atau tidak ada) |
| `/docs/intro` | `["intro"]` |
| `/docs/react/hooks` | `["react", "hooks"]` |

```jsx
export default async function Docs({ params }) {
  const { slug } = await params;
  const bagian = slug ?? [];

  return (
    <main>
      <h1>{bagian.length === 0 ? "Indeks dokumentasi" : bagian.join(" / ")}</h1>
    </main>
  );
}
```

Jangan membuat `app/docs/page.js` **bersamaan** dengan `app/docs/[[...slug]]/page.js` — keduanya memperebutkan `/docs`.

Perbedaan cepat:

| Pola | `/docs` | `/docs/a` | `/docs/a/b` |
| --- | --- | --- | --- |
| `docs/page.js` + `docs/[id]/page.js` | indeks | satu segmen | 404 |
| `docs/[...slug]/page.js` | 404 | array | array |
| `docs/[[...slug]]/page.js` | cocok, slug kosong | array | array |

**Biasanya digabungkan dengan:** situs dokumentasi satu file, dan CMS yang path-nya bebas dalamnya.

## generateStaticParams

**Untuk apa:** memberitahu Next.js id mana yang boleh **dibangun di muka** saat `next build`.

```jsx
export async function generateStaticParams() {
  return [{ id: "1" }, { id: "2" }];
}

export default async function DetailProduk({ params }) {
  const { id } = await params;
  return <main>Produk {id}</main>;
}
```

Untuk catch-all, kembalikan array di kunci yang sama:

```jsx
export async function generateStaticParams() {
  return [
    { slug: ["intro"] },
    { slug: ["react", "hooks"] },
  ];
}
```

Satu per satu:

- Dipanggil saat build (dan bisa saat development, tergantung versi).
- Return **array of objects**; tiap objek adalah satu `params`.
- Tanpa fungsi ini, halaman dinamis tetap bisa dirender **saat diminta** (on demand), kecuali kamu mematikan itu lewat `dynamicParams`.
- Boleh `fetch` di dalamnya untuk daftar id dari API/Laravel.

```jsx
export async function generateStaticParams() {
  const baseUrl = process.env.API_BASE_URL;
  const response = await fetch(`${baseUrl}/api/produk`);
  const produk = await response.json();
  return produk.map((item) => ({ id: String(item.id) }));
}
```

Jika API gagal saat build, build gagal. Sediakan fallback atau data minimal untuk CI.

**Biasanya digabungkan dengan:** katalog yang id-nya sudah diketahui, dan `generateMetadata`.

## dynamicParams

**Untuk apa:** menolak atau mengizinkan id di luar daftar `generateStaticParams`.

```jsx
export const dynamicParams = false;

export async function generateStaticParams() {
  return [{ id: "1" }, { id: "2" }];
}
```

- `true` (default): id baru dirender saat diminta.
- `false`: id di luar daftar → 404.

Pakai `false` jika katalog tertutup (misalnya tugas dengan 5 produk tetap).

**Biasanya digabungkan dengan:** `generateStaticParams` dan `not-found.js`.

## generateMetadata pada route dinamis

**Untuk apa:** judul tab berbeda per id.

```jsx
export async function generateMetadata({ params }) {
  const { id } = await params;
  const item = await ambilProduk(id);
  if (!item) return { title: "Produk tidak ada" };
  return {
    title: item.nama,
    description: `Beli ${item.nama} di Toko Belajar`,
  };
}

export default async function Detail({ params }) {
  const { id } = await params;
  const item = await ambilProduk(id);
  if (!item) notFound();
  return <main><h1>{item.nama}</h1></main>;
}
```

`params` di-await di metadata juga. Hindari fetch dobel yang mahal jika kamu bisa membagi cache `fetch` — Next mendeduplikasi `fetch` URL sama dalam satu render.

**Biasanya digabungkan dengan:** [10](10-metadata-image-font.md) untuk Open Graph.

## params di-await (Next 15+)

**Untuk apa:** mengikuti kontrak Promise.

```jsx
export default async function Halaman({ params, searchParams }) {
  const { id } = await params;
  const { q = "" } = await searchParams;
  return <p>{id} {String(q)}</p>;
}
```

Salah di Next 15+:

```jsx
export default function Halaman({ params }) {
  const id = params.id; // bisa pecah atau peringatan
}
```

Jika kamu melihat kode lama `params.id` tanpa await, itu pola Next 14. Ensiklopedia ini memakai await.

`layout.js` juga:

```jsx
export default async function Layout({ children, params }) {
  const { id } = await params;
  return (
    <section>
      <p>Konteks {id}</p>
      {children}
    </section>
  );
}
```

**Biasanya digabungkan dengan:** semua `page.js` dinamis di tugas baru.

## params di layout versus page

- Layout `app/produk/layout.js` **tidak** punya `params.id` kecuali foldernya sendiri `[id]`, atau ia berada di dalam `[id]`.
- `app/produk/[id]/layout.js` menerima `{ id }`.
- `app/produk/layout.js` (di atas `[id]`) menerima params tanpa `id`.
- `searchParams` tidak masuk layout — ulangi dari [02](02-layout-page-template-default.md).

**Biasanya digabungkan dengan:** breadcrumb di `app/produk/[id]/layout.js`.

## useParams di klien

Sudah dirinci di [03](03-link-navigation-hooks.md#5-useparams). Ringkas:

```jsx
"use client";

import { useParams } from "next/navigation";

export default function Badge() {
  const { id } = useParams();
  return <span>#{id}</span>;
}
```

Catch-all: `const { slug } = useParams();` → array.

**Biasanya digabungkan dengan:** widget klien di halaman detail.

## Route Handler dinamis

**Untuk apa:** API `/api/produk/1`.

`app/api/produk/[id]/route.js`:

```js
const produk = [
  { id: "1", nama: "Buku JavaScript" },
  { id: "2", nama: "Buku CSS" },
];

export async function GET(_request, { params }) {
  const { id } = await params;
  const item = produk.find((row) => row.id === id);
  if (!item) {
    return Response.json({ pesan: "Tidak ada" }, { status: 404 });
  }
  return Response.json(item);
}
```

`params` di handler juga di-await. Lihat [08](08-route-handler-http.md).

**Biasanya digabungkan dengan:** `fetch` dari Client Component.

## Prioritas pencocokan URL

**Untuk apa:** meramal file mana yang menang jika beberapa pola bisa cocok.

Secara kasar, dari lebih spesifik ke lebih umum:

1. Segmen statis (`produk/baru/page.js` untuk `/produk/baru`)
2. Segmen dinamis (`[id]`)
3. Catch-all (`[...slug]`)
4. Optional catch-all (`[[...slug]]`)

Jadi `app/produk/baru/page.js` mengalahkan `app/produk/[id]/page.js` untuk URL `/produk/baru`. `params.id` tidak pernah `"baru"` jika folder statis `baru` ada.

Route group `(toko)` tidak memengaruhi prioritas URL.

**Biasanya digabungkan dengan:** halaman khusus `/produk/baru` di samping detail `[id]`.

## Contoh lengkap toko

```text
app/
├── produk/
│   ├── page.js                 /produk
│   ├── baru/
│   │   └── page.js             /produk/baru
│   └── [id]/
│       ├── page.js             /produk/1
│       └── not-found.js        404 khusus detail
└── docs/
    └── [[...slug]]/
        └── page.js             /docs, /docs/a, /docs/a/b
```

`app/produk/baru/page.js`:

```jsx
export const metadata = { title: "Produk baru" };

export default function ProdukBaru() {
  return <main><h1>Tambah produk</h1></main>;
}
```

Tanpa folder `baru`, URL `/produk/baru` akan dianggap id `"baru"` dan mungkin 404 dari `notFound()`.

## Kesalahan umum

- Membandingkan `id === 1` bukan `"1"`.
- Lupa `await params`.
- Mengira `[...slug]` mencakup `/docs` — tidak; pakai `[[...slug]]` atau `page.js` indeks.
- Dua file merebut URL yang sama.
- `generateStaticParams` mengembalikan `{ produkId: "1" }` padahal folder `[id]`.
- Menaruh `[id].js` seperti Pages Router di dalam `app/` — salah; harus folder `[id]/page.js`.
- Catch-all diperlakukan sebagai string, bukan array.
- `dynamicParams = false` lalu heran id baru 404.

## Checklist

1. Folder `[nama]` = satu segmen.
2. `[...nama]` = satu atau lebih, array, tanpa URL induk.
3. `[[...nama]]` = nol atau lebih, termasuk URL induk.
4. `await params` di page, layout, metadata, route handler.
5. `notFound()` jika data kosong.
6. Halaman statis khusus (`baru`, `edit`) diletakkan sebagai folder, bukan mengandalkan id cadangan.

## Lihat juga

- [03 — useParams, notFound](03-link-navigation-hooks.md)
- [06 — not-found.js](06-searchParams-loading-error-not-found.md)
- [Rujukan dynamic routes](https://nextjs.org/docs/app/api-reference/file-conventions/dynamic-routes)

---

Sebelum: [04 — server/client](04-server-client-component.md) · Berikut: [06 — searchParams dan UI status](06-searchParams-loading-error-not-found.md)
