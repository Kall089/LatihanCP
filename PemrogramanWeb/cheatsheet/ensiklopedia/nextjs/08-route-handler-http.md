# 08 — Route Handler: GET POST PUT PATCH DELETE

[← 07 fetch & cache](07-fetch-cache-revalidate.md) · [Berikut: Server Actions →](09-server-actions-form.md)

**Untuk apa:** menyediakan endpoint HTTP dari proyek Next.js lewat file `route.js`, bukan `page.js`.

URL `/api/produk` berasal dari `app/api/produk/route.js`. Browser memanggilnya dengan `fetch("/api/produk")` dari origin yang sama.

## Daftar isi file ini

- [File route.js](#file-routejs)
- [GET](#get)
- [POST](#post)
- [PUT](#put)
- [PATCH](#patch)
- [DELETE](#delete)
- [Argumen Request](#argumen-request)
- [Context params](#context-params)
- [headers() dan request.headers](#headers-dan-requestheaders)
- [cookies() dan request.cookies](#cookies-dan-requestcookies)
- [NextRequest dan NextResponse](#nextrequest-dan-nextresponse)
- [Response.json dan status](#responsejson-dan-status)
- [Membaca body: json, formData, text](#membaca-body-json-formdata-text)
- [Query string di handler](#query-string-di-handler)
- [Validasi dan error HTTP](#validasi-dan-error-http)
- [CORS, webhook, dan cache GET](#cors-webhook-dan-cache-get)
- [Resep CRUD array statis](#resep-crud-array-statis)
- [Kesalahan umum](#kesalahan-umum)

## File route.js

**Untuk apa:** menandai folder sebagai endpoint, bukan halaman HTML.

```text
app/api/produk/route.js          →  /api/produk
app/api/produk/[id]/route.js     →  /api/produk/1
app/api/webhooks/laravel/route.js →  /api/webhooks/laravel
```

Aturan, satu per satu:

- Nama file **tepat** `route.js` (atau `route.tsx`).
- Ekspor fungsi bernama metode HTTP: `GET`, `POST`, `PUT`, `PATCH`, `DELETE`, `HEAD`, `OPTIONS`.
- Jangan menaruh `page.js` dan `route.js` di folder yang sama — konflik.
- Folder `api/` hanya konvensi; `app/produk/route.js` akan menimpa kemungkinan halaman `/produk`. Utamakan `/api/...` untuk JSON.
- Handler berjalan di server. Boleh baca env tanpa `NEXT_PUBLIC_`.

**Biasanya digabungkan dengan:** frontend React/Next klien, webhook, dan proksi ke Laravel.

## GET

**Untuk apa:** membaca data. Seharusnya tanpa efek samping.

`app/api/produk/route.js`:

```js
export async function GET() {
  return Response.json([
    { id: 1, nama: "Buku JavaScript", harga: 45000 },
    { id: 2, nama: "Buku CSS", harga: 40000 },
  ]);
}
```

Buka `/api/produk` di browser: JSON. Dari klien:

```jsx
"use client";

import { useEffect, useState } from "react";

export default function DaftarClient() {
  const [produk, setProduk] = useState([]);

  useEffect(() => {
    fetch("/api/produk")
      .then((r) => r.json())
      .then(setProduk);
  }, []);

  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>{item.nama}</li>
      ))}
    </ul>
  );
}
```

GET dengan query: lihat [Query string di handler](#query-string-di-handler).

Pada Next 15+, GET Route Handler **tidak** di-cache secara default. Tetap tulis `cache: "no-store"` di pemanggil jika perlu.

**Biasanya digabungkan dengan:** daftar, detail, dan pencarian `?q=`.

## POST

**Untuk apa:** membuat sumber baru, atau aksi yang tidak idempoten.

```js
export async function POST(request) {
  const body = await request.json();
  const nama = String(body.nama ?? "").trim();

  if (!nama) {
    return Response.json({ pesan: "Nama wajib" }, { status: 400 });
  }

  const item = { id: Date.now(), nama };
  return Response.json(item, { status: 201 });
}
```

Pemanggil klien:

```js
await fetch("/api/produk", {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ nama: "Buku HTML" }),
});
```

`Date.now()` sebagai id hanya untuk latihan memori. Data hilang saat server restart. Tugas sungguhan: simpan ke Laravel/database.

**Biasanya digabungkan dengan:** form klien, validasi, dan `revalidatePath("/produk")` jika page server harus segar.

## PUT

**Untuk apa:** mengganti sumber **utuh**. Idempoten: mengirim body yang sama berulang kali menghasilkan keadaan yang sama.

`app/api/produk/[id]/route.js` (potongan PUT):

```js
export async function PUT(request, { params }) {
  const { id } = await params;
  const body = await request.json();
  const nama = String(body.nama ?? "").trim();
  const harga = Number(body.harga);

  if (!nama || Number.isNaN(harga)) {
    return Response.json({ pesan: "Nama dan harga wajib" }, { status: 400 });
  }

  const item = { id, nama, harga };
  // simpan pengganti utuh
  return Response.json(item);
}
```

Klien:

```js
await fetch(`/api/produk/${id}`, {
  method: "PUT",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ nama: "Buku CSS", harga: 42000 }),
});
```

PUT mengirim semua field. Field yang tidak dikirim dianggap tidak ada / default, bukan “biarkan lama”.

**Biasanya digabungkan dengan:** form edit lengkap.

## PATCH

**Untuk apa:** mengubah **sebagian** field.

```js
export async function PATCH(request, { params }) {
  const { id } = await params;
  const body = await request.json();
  const patch = {};

  if (body.nama != null) patch.nama = String(body.nama).trim();
  if (body.harga != null) patch.harga = Number(body.harga);

  if (patch.nama === "") {
    return Response.json({ pesan: "Nama tidak boleh kosong" }, { status: 400 });
  }
  if (patch.harga != null && Number.isNaN(patch.harga)) {
    return Response.json({ pesan: "Harga tidak valid" }, { status: 400 });
  }

  const item = { id, ...patch };
  return Response.json(item);
}
```

Klien:

```js
await fetch(`/api/produk/${id}`, {
  method: "PATCH",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ harga: 39000 }),
});
```

**Biasanya digabungkan dengan:** ubah satu kolom (stok, status, harga).

## DELETE

**Untuk apa:** menghapus sumber.

```js
export async function DELETE(_request, { params }) {
  const { id } = await params;
  const ada = true; // ganti dengan cek penyimpanan
  if (!ada) {
    return Response.json({ pesan: "Tidak ada" }, { status: 404 });
  }
  return new Response(null, { status: 204 });
}
```

`204` = sukses tanpa body. Alternatif: `200` + `{ ok: true }`.

Klien:

```js
await fetch(`/api/produk/${id}`, { method: "DELETE" });
```

**Biasanya digabungkan dengan:** tombol hapus + konfirmasi, lalu `router.refresh()`.

## Argumen Request

**Untuk apa:** membaca URL, header, body, dan method dari Web `Request`.

```js
export async function GET(request) {
  const url = new URL(request.url);
  const q = url.searchParams.get("q") ?? "";
  const accept = request.headers.get("accept");
  return Response.json({ q, accept });
}
```

Properti yang sering dipakai, satu per satu:

- `request.url` — URL lengkap string
- `request.method` — `"GET"` dll. (sudah tersirat dari nama fungsi)
- `request.headers` — `Headers`
- `request.json()` — parse JSON (sekali baca body)
- `request.formData()` — `multipart` / `application/x-www-form-urlencoded`
- `request.text()` — string mentah
- `request.blob()` / `request.arrayBuffer()` — biner

Body hanya bisa dibaca **satu kali**. Jangan `await request.json()` lalu `await request.text()`.

**Biasanya digabungkan dengan:** validasi dan logging sederhana (tanpa data sensitif).

## Context params

**Untuk apa:** mengambil segmen dinamis folder.

```js
export async function GET(request, context) {
  const { id } = await context.params;
  return Response.json({ id });
}
```

Next 15+: `context.params` di-await, sama seperti page.

Catch-all: `params.slug` array.

Argumen kedua jangan diabaikan namanya; pola resmi `{ params }`.

**Biasanya digabungkan dengan:** `app/api/produk/[id]/route.js`.

## headers() dan request.headers

**Untuk apa:** membaca header permintaan.

Dua cara:

### 1. Dari objek Request — paling jelas di Route Handler

```js
export async function GET(request) {
  const contentType = request.headers.get("content-type");
  const authorization = request.headers.get("authorization");
  return Response.json({ contentType, authorization });
}
```

### 2. Dari `next/headers` — berguna juga di Server Component

```js
import { headers } from "next/headers";

export async function GET() {
  const h = await headers();
  const ua = h.get("user-agent");
  return Response.json({ ua });
}
```

`headers()` di Next 15+ di-await.

Jangan percaya header `x-forwarded-user` mentah-mentah sebagai autentikasi. Header bisa dipalsukan kecuali di belakang proxy yang kamu kendalikan.

Menulis header respons:

```js
return Response.json(
  { ok: true },
  {
    status: 200,
    headers: {
      "Cache-Control": "no-store",
      "X-Toko": "Belajar",
    },
  }
);
```

**Biasanya digabungkan dengan:** cek `Authorization`, `Content-Type`, dan cookie sesi.

## cookies() dan request.cookies

**Untuk apa:** membaca dan menulis cookie HTTP.

### Baca di handler dengan next/headers

```js
import { cookies } from "next/headers";

export async function GET() {
  const jar = await cookies();
  const sesi = jar.get("sesi")?.value ?? null;
  return Response.json({ masuk: Boolean(sesi) });
}
```

`cookies()` Next 15+ di-await. Metode: `get`, `getAll`, `has`, `set`, `delete`.

### Set cookie di Route Handler

```js
import { cookies } from "next/headers";

export async function POST() {
  const jar = await cookies();
  jar.set("sesi", "latihan-abc", {
    httpOnly: true,
    sameSite: "lax",
    path: "/",
    maxAge: 60 * 60,
  });
  return Response.json({ ok: true });
}
```

Opsi cookie, satu per satu:

- `httpOnly: true` — tidak terbaca `document.cookie` (lebih aman untuk sesi).
- `secure: true` — hanya HTTPS. Di `localhost` http, sering dimatikan saat dev.
- `sameSite: "lax" | "strict" | "none"`
- `path: "/"`
- `maxAge` detik, atau `expires` Date
- `name` dan `value`

### Set lewat NextResponse

```js
import { NextResponse } from "next/server";

export async function POST() {
  const response = NextResponse.json({ ok: true });
  response.cookies.set("sesi", "latihan-abc", { httpOnly: true, path: "/" });
  return response;
}
```

### Hapus

```js
jar.delete("sesi");
// atau
response.cookies.delete("sesi");
```

Jangan menyimpan password di cookie. Simpan id sesi / token yang bisa dicabut.

**Biasanya digabungkan dengan:** login latihan, middleware yang membaca cookie, dan `redirect` jika belum masuk.

## NextRequest dan NextResponse

**Untuk apa:** API Next di atas Web Request/Response.

```js
import { NextResponse } from "next/server";

export async function GET(request) {
  const q = request.nextUrl?.searchParams.get("q") ?? new URL(request.url).searchParams.get("q");
  return NextResponse.json({ q });
}
```

Jika memakai tipe/kelas `NextRequest`, tersedia `nextUrl`, `cookies`, `geo` (kadang deprecated), `ip` (tergantung host).

`NextResponse` pembantu:

```js
NextResponse.json({ ok: true }, { status: 200 });
NextResponse.redirect(new URL("/login", request.url));
NextResponse.rewrite(new URL("/produk", request.url));
NextResponse.next(); // lebih ke middleware
```

Di Route Handler, `Response.json` standar sudah cukup untuk tugas kuliah.

**Biasanya digabungkan dengan:** middleware ([11](11-env-middleware-rewrite-redirect.md)) yang memakai API yang sama.

## Response.json dan status

**Untuk apa:** kontrak HTTP yang bisa diprediksi klien.

```js
return Response.json({ pesan: "Nama wajib" }, { status: 400 });
return Response.json({ item }, { status: 201 });
return new Response(null, { status: 204 });
return Response.json({ pesan: "Tidak ada" }, { status: 404 });
return Response.json({ pesan: "Tidak boleh" }, { status: 403 });
return Response.json({ pesan: "Belum masuk" }, { status: 401 });
return Response.json({ pesan: "Server error" }, { status: 500 });
```

Jangan selalu 200 + `{ error: true }` jika kamu bisa memakai status. Klien mengecek `response.ok`.

**Biasanya digabungkan dengan:** `if (!response.ok)` di pemanggil.

## Membaca body: json, formData, text

### JSON

```js
const body = await request.json();
```

Gagal parse → lempar; tangkap:

```js
let body;
try {
  body = await request.json();
} catch {
  return Response.json({ pesan: "JSON tidak valid" }, { status: 400 });
}
```

### FormData (form HTML ke API)

```js
export async function POST(request) {
  const form = await request.formData();
  const nama = String(form.get("nama") ?? "").trim();
  return Response.json({ nama });
}
```

Klien:

```js
const form = new FormData();
form.append("nama", "Buku HTML");
await fetch("/api/produk", { method: "POST", body: form });
```

Jangan set `Content-Type` manual saat mengirim `FormData` di browser; boundary diisi otomatis.

### text

```js
const mentah = await request.text();
```

Berguna untuk webhook yang verifikasi HMAC dari body mentah.

**Biasanya digabungkan dengan:** validasi field dan file upload sederhana (`form.get("gambar")` sebagai `File`).

## Query string di handler

```js
export async function GET(request) {
  const { searchParams } = new URL(request.url);
  const q = (searchParams.get("q") ?? "").toLowerCase();
  const halaman = Number(searchParams.get("halaman") ?? "1");

  const semua = [
    { id: 1, nama: "Buku JavaScript" },
    { id: 2, nama: "Buku CSS" },
  ];
  const hasil = semua.filter((item) => item.nama.toLowerCase().includes(q));

  return Response.json({ halaman, hasil });
}
```

Ini bukan prop `searchParams` milik `page.js`. Di handler, baca dari URL.

**Biasanya digabungkan dengan:** autocomplete klien.

## Validasi dan error HTTP

**Untuk apa:** tidak percaya input.

```js
function validasiProduk(body) {
  const nama = String(body?.nama ?? "").trim();
  const harga = Number(body?.harga);
  const error = [];
  if (nama.length < 3) error.push("Nama minimal 3 huruf");
  if (!Number.isFinite(harga) || harga < 0) error.push("Harga tidak valid");
  return { nama, harga, error };
}

export async function POST(request) {
  const body = await request.json();
  const { nama, harga, error } = validasiProduk(body);
  if (error.length) {
    return Response.json({ pesan: error }, { status: 422 });
  }
  return Response.json({ id: 3, nama, harga }, { status: 201 });
}
```

422 = validasi gagal (umum di API Laravel). 400 juga diterima di tugas.

**Biasanya digabungkan dengan:** pesan field di form klien.

## CORS, webhook, dan cache GET

### Origin sama

`fetch("/api/produk")` dari halaman Next yang sama **tidak** butuh CORS.

### Origin lain (Laravel memanggil Next, atau sebaliknya)

Tambahkan header jika memang diperlukan:

```js
export async function OPTIONS() {
  return new Response(null, {
    status: 204,
    headers: {
      "Access-Control-Allow-Origin": "http://127.0.0.1:8000",
      "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
      "Access-Control-Allow-Headers": "Content-Type",
    },
  });
}
```

Jangan `*` + cookie.

### Webhook

- Pakai `POST`.
- Baca `request.text()` jika perlu tanda tangan.
- Balas cepat 200 setelah valid.
- Jangan mengandalkan UI.

### Cache GET

Next 14 kadang men-cache GET handler. Next 15+ default tidak. Jika GET “membeku”:

```js
export const dynamic = "force-dynamic";

export async function GET() {
  return Response.json({ waktu: Date.now() });
}
```

atau set header `Cache-Control: no-store`.

**Biasanya digabungkan dengan:** pengembangan lokal dua port (3000 dan 8000).

## Resep CRUD array statis

**Untuk apa:** memahami metode tanpa database. Data hilang saat reload server — itu disengaja.

`app/api/produk/route.js`:

```js
let produk = [
  { id: "1", nama: "Buku JavaScript", harga: 45000 },
  { id: "2", nama: "Buku CSS", harga: 40000 },
];

export async function GET(request) {
  const q = new URL(request.url).searchParams.get("q") ?? "";
  const kata = q.toLowerCase();
  const hasil = produk.filter((item) => item.nama.toLowerCase().includes(kata));
  return Response.json(hasil);
}

export async function POST(request) {
  const body = await request.json();
  const nama = String(body.nama ?? "").trim();
  const harga = Number(body.harga);
  if (!nama || Number.isNaN(harga)) {
    return Response.json({ pesan: "Nama dan harga wajib" }, { status: 400 });
  }
  const item = { id: String(Date.now()), nama, harga };
  produk = [...produk, item];
  return Response.json(item, { status: 201 });
}
```

`app/api/produk/[id]/route.js`:

```js
// impor array yang sama tidak mudah jika `let` di modul lain.
// Untuk latihan, pindahkan `produk` ke app/lib/store-produk.js

import { cari, ganti, potong } from "../../../lib/store-produk";

export async function GET(_request, { params }) {
  const { id } = await params;
  const item = cari(id);
  if (!item) return Response.json({ pesan: "Tidak ada" }, { status: 404 });
  return Response.json(item);
}

export async function PUT(request, { params }) {
  const { id } = await params;
  const body = await request.json();
  const nama = String(body.nama ?? "").trim();
  const harga = Number(body.harga);
  if (!nama || Number.isNaN(harga)) {
    return Response.json({ pesan: "Nama dan harga wajib" }, { status: 400 });
  }
  const item = ganti(id, { id, nama, harga });
  if (!item) return Response.json({ pesan: "Tidak ada" }, { status: 404 });
  return Response.json(item);
}

export async function PATCH(request, { params }) {
  const { id } = await params;
  const lama = cari(id);
  if (!lama) return Response.json({ pesan: "Tidak ada" }, { status: 404 });
  const body = await request.json();
  const item = ganti(id, { ...lama, ...body, id });
  return Response.json(item);
}

export async function DELETE(_request, { params }) {
  const { id } = await params;
  const ok = potong(id);
  if (!ok) return Response.json({ pesan: "Tidak ada" }, { status: 404 });
  return new Response(null, { status: 204 });
}
```

`app/lib/store-produk.js` mengekspor array + fungsi. Ini tetap memori proses; di serverless tiap instance bisa beda. Untuk tugas nyata, ganti dengan Laravel.

**Biasanya digabungkan dengan:** [09](09-server-actions-form.md) sebagai alternatif tanpa `fetch` klien.

## Route Handler versus Server Action versus Laravel

| Kebutuhan | Pilih |
| --- | --- |
| Form di halaman Next, mutasi sederhana | Server Action |
| API dikonsumsi klien/mobile/pihak ketiga | Route Handler |
| Bisnis + database tugas backend | Laravel |
| Webhook | Route Handler |
| Halaman HTML | `page.js`, bukan `route.js` |

Jangan menduplikasi seluruh domain di Next dan Laravel tanpa alasan.

## Kesalahan umum

- `page.js` + `route.js` sefolder.
- Lupa `await params` / `await cookies()` / `await headers()`.
- Membaca body dua kali.
- GET yang mengubah data.
- Selalu status 200.
- Mengira array di modul bersifat database.
- Fetch handler sendiri dari Server Component.
- CORS `*` plus cookie sesi.
- Menaruh `middleware.js` di `app/api/middleware.js` mengira itu “middleware API”.

## Lihat juga

- [09 — Server Action sebagai alternatif form](09-server-actions-form.md)
- [11 — env, cookie, middleware](11-env-middleware-rewrite-redirect.md)

---

Sebelum: [07 — fetch](07-fetch-cache-revalidate.md) · Berikut: [09 — Server Actions dan form](09-server-actions-form.md)
