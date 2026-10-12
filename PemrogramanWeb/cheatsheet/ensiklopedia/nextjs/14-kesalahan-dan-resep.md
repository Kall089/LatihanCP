# 14 — Kesalahan umum dan resep utuh

[← 13 katalog file](13-katalog-file-convention.md) · [README ensiklopedia](README.md)

**Untuk apa:** menandai gejala yang sering muncul di tugas, lalu merakit fitur toko dari file yang sudah dijelaskan satu per satu.

Baca pesan terminal `npm run dev` / `npm run build` sebelum menebak. Banyak “halaman putih” tertulis jelas di sana.

## Daftar isi file ini

- [Kesalahan: instalasi dan struktur](#kesalahan-instalasi-dan-struktur)
- [Kesalahan: Server versus Client](#kesalahan-server-versus-client)
- [Kesalahan: routing dan params](#kesalahan-routing-dan-params)
- [Kesalahan: data, cache, env](#kesalahan-data-cache-env)
- [Kesalahan: form dan action](#kesalahan-form-dan-action)
- [Kesalahan: CSS dan gambar](#kesalahan-css-dan-gambar)
- [Kesalahan: middleware dan auth latihan](#kesalahan-middleware-dan-auth-latihan)
- [Resep A — kerangka toko](#resep-a--kerangka-toko)
- [Resep B — daftar, cari, detail, 404](#resep-b--daftar-cari-detail-404)
- [Resep C — form tambah + Laravel](#resep-c--form-tambah--laravel)
- [Resep D — Route Handler CRUD latihan](#resep-d--route-handler-crud-latihan)
- [Resep E — navbar aktif + layout group](#resep-e--navbar-aktif--layout-group)
- [Cara memeriksa sebelum mengumpulkan](#cara-memeriksa-sebelum-mengumpulkan)
- [Yang tidak perlu dikerjakan](#yang-tidak-perlu-dikerjakan)

---

## Kesalahan: instalasi dan struktur

### `npm run dev` gagal: no package.json

Kamu tidak berada di folder proyek. `cd latihan-next`.

### Port 3000 terpakai

Pakai port yang ditawarkan, atau matikan proses lama. Jangan heran jika dosen membuka `3001`.

### Tutorial Pages Router tersalin ke `app/`

Gejala: `getServerSideProps`, `next/router`, file `pages/api`.

Perbaikan: ikuti App Router. `useRouter` dari `next/navigation`. Data lewat Server Component.

### `src/app` versus `app`

Gejala: file kamu ada, URL 404. Periksa di folder mana `create-next-app` menaruh `app/`.

### Mengedit `.next/`

Perubahan hilang. Edit sumber di `app/`.

### Build dari folder cheatsheet

Folder ensiklopedia bukan proyek Next. Jalankan perintah di `latihan-next`.

**Biasanya digabungkan dengan:** [01](01-install-struktur-app.md).

---

## Kesalahan: Server versus Client

### `useState` / `useRouter` ditolak

Tambah `"use client"` di **file yang memakai hook**, atau pindahkan hook ke komponen kecil. Jangan langsung menandai root `layout.js` kecuali sadar kehilangan metadata.

### `window is not defined`

Kode mengakses browser saat prerender. Pindahkan ke `useEffect` atau event.

### Hydration mismatch

HTML server ≠ render klien pertama. Hindari `Date.now()`, `Math.random()`, `localStorage` di render. Samakan markup awal.

### Fungsi tidak bisa dikirim sebagai props ke klien

Pakai handler di dalam Client Component, atau kirim Server Action.

### Metadata hilang setelah `"use client"` di page

Pecah: `page.js` server mengekspor metadata; anak klien terpisah.

### Seluruh halaman fetch di `useEffect`

Bekerja, tetapi membuang App Router. Pindahkan fetch awal ke server.

**Biasanya digabungkan dengan:** [04](04-server-client-component.md).

---

## Kesalahan: routing dan params

### 404 padahal file ada

- Nama harus `page.js`, bukan `index.js`.
- Folder salah (`src` vs root).
- Case: `Produk` vs `produk` di server Linux.
- Dynamic: file harus `app/produk/[id]/page.js`, bukan `app/produk/[id].js`.

### `params.id` undefined / Promise

`const { id } = await params;`

Sama untuk `searchParams`, `cookies()`, `headers()`.

### `id === 1` selalu false

`params` string. Bandingkan `"1"` atau `Number(id)`.

### Catch-all dianggap string

`[...slug]` → array. `slug.join("/")`.

### `/docs` 404 padahal ada `[...slug]`

Catch-all biasa tidak mencakup induk. Pakai `[[...slug]]` atau `docs/page.js`.

### `searchParams` di layout kosong

Pindahkan ke `page.js` atau `useSearchParams`.

### `useSearchParams` merusak build / loading

Bungkus komponen itu dengan `<Suspense>`.

### `redirect` / `notFound` tidak jalan

Ditangkap `try/catch` terlalu luas. Jangan menelan error Next.

**Biasanya digabungkan dengan:** [03](03-link-navigation-hooks.md), [05](05-dynamic-route-catch-all-optional.md).

---

## Kesalahan: data, cache, env

### `API_BASE_URL` undefined

Tidak ada `.env.local`, atau lupa restart, atau salah nama kunci.

### Fetch ke `localhost:3000/api` dari server

Hindari hop ke diri sendiri. Akses sumber data / Laravel langsung.

### Data tidak berubah setelah POST

Cache. Pakai `cache: "no-store"`, atau `revalidatePath` / `revalidateTag`, atau `router.refresh()`.

### `no-store` digabung `revalidate: 60`

Jangan pada fetch yang sama.

### `response.json()` pada 500 HTML

Cek `response.ok` dulu.

### Env rahasia di klien

Hilangkan `NEXT_PUBLIC_` dari kunci rahasia. Jangan kirim sebagai props.

### CORS saat browser memanggil Laravel

Pilih: rewrite Next `/backend`, atau atur CORS Laravel, atau fetch hanya di server Next.

**Biasanya digabungkan dengan:** [07](07-fetch-cache-revalidate.md), [11](11-env-middleware-rewrite-redirect.md).

---

## Kesalahan: form dan action

### Field tidak sampai ke action

Lupa `name` pada input.

### `useActionState` aneh

Signature action harus `(state, formData)` jika memakai hook itu.

### `useFormStatus` selalu `pending === false`

Hook dipanggil di komponen yang sama dengan `<form>`, bukan anak.

### `"use server"` di dalam Client Component

Pindahkan fungsi ke `aksi.js`.

### Setelah simpan, daftar lama

`revalidatePath("/produk")` atau `router.refresh()`.

### `confirm()` di Server Component

`confirm` adalah browser. Pakai Client Component.

**Biasanya digabungkan dengan:** [09](09-server-actions-form.md).

---

## Kesalahan: CSS dan gambar

### Class Tailwind tidak muncul

Restart; cek `content` v3; jangan pecah nama class dinamis `bg-${warna}-700`.

### `Image` error hostname

Tambah `remotePatterns`, restart.

### Layout shift gambar

Isi `width`/`height` atau `fill` + induk berukuran.

### `class` bukan `className`

JSX memakai `className`.

### CSS Module `undefined`

Pakai `styles.judul`, file `*.module.css`.

**Biasanya digabungkan dengan:** [10](10-metadata-image-font.md), [12](12-tailwind-css-modules.md).

---

## Kesalahan: middleware dan auth latihan

### Middleware tidak jalan

File di `app/middleware.js`. Pindahkan ke root.

### Loop redirect

`/login` ikut matcher dan selalu diarahkan ke `/login`. Kecualikan tujuan.

### 308 tertahan di browser

`permanent: true` atau `permanentRedirect` saat masih uji. Pakai sementara, atau uji mode penyamaran.

### Mengira middleware cukup

Page `/admin` tetap harus cek sesi. Cookie latihan mudah dipalsu.

**Biasanya digabungkan dengan:** [11](11-env-middleware-rewrite-redirect.md).

---

## Resep A — kerangka toko

**Untuk apa:** proyek baru yang sudah terasa aplikasi.

1. `create-next-app` dengan `--js --app` ([01](01-install-struktur-app.md)).
2. `app/layout.js`: `html lang="id"`, impor `globals.css`, render `Navigasi`.
3. `app/components/Navigasi.js`: tiga `Link` — `/`, `/produk`, `/tentang`.
4. `app/page.js`: judul Toko Belajar.
5. `app/produk/page.js`: teks “Daftar produk”.
6. `app/tentang/page.js`: paragraf singkat + `metadata.title`.

Belum perlu `"use client"`, fetch, atau Tailwind wajib — tetapi Tailwind mempercepat kerangka ([12](12-tailwind-css-modules.md)).

**Biasanya digabungkan dengan:** commit git pertama di folder latihan.

---

## Resep B — daftar, cari, detail, 404

**Untuk apa:** memenuhi tugas katalog.

Struktur:

```text
app/produk/page.js
app/produk/loading.js
app/produk/error.js
app/produk/[id]/page.js
app/not-found.js
```

Daftar memakai `await searchParams` + form GET `q` ([06](06-searchParams-loading-error-not-found.md)).

Detail `await params`, `find` / fetch, `notFound()` ([05](05-dynamic-route-catch-all-optional.md)).

`generateMetadata` di detail ([10](10-metadata-image-font.md)).

Data awal boleh array statis. Nanti ganti `fetch` Laravel `cache: "no-store"` ([07](07-fetch-cache-revalidate.md)).

**Biasanya digabungkan dengan:** `Link href={`/produk/${id}`}`.

---

## Resep C — form tambah + Laravel

**Untuk apa:** mutasi sungguhan.

1. Laravel menyediakan `POST /api/produk` — [laravel.md](../../laravel.md).
2. `.env.local`: `API_BASE_URL=http://127.0.0.1:8000`.
3. `app/aksi-produk.js` `"use server"`: baca `FormData`, validasi, `fetch` POST, `revalidatePath("/produk")`, `redirect("/produk")`.
4. `app/produk/baru/page.js` (folder statis, bukan `[id]`).
5. Form `action={tambahProduk}` dengan `name="nama"` dan `name="harga"`.
6. Untuk pesan error tanpa redirect, bungkus `useActionState` ([09](09-server-actions-form.md)).

Jangan duplikasi aturan bisnis yang sudah ada di `validate()` Laravel; tetap validasi ulang di Next sebagai pagar UI.

**Biasanya digabungkan dengan:** dua terminal — `php artisan serve` dan `npm run dev`.

---

## Resep D — Route Handler CRUD latihan

**Untuk apa:** memahami HTTP tanpa backend.

Ikuti [08](08-route-handler-http.md): `GET/POST` di `app/api/produk/route.js`, `GET/PUT/PATCH/DELETE` di `[id]/route.js`, store di `app/lib/store-produk.js`.

Client Component memanggil `fetch("/api/produk")`. Ingat: data memori hilang saat restart, dan serverless tidak konsisten. Tulis di README tugas jika ini sengaja.

**Biasanya digabungkan dengan:** Postman/Insomnia atau tab browser untuk GET.

---

## Resep E — navbar aktif + layout group

**Untuk apa:** login tanpa navbar toko, katalog dengan navbar.

```text
app/
├── layout.js                 html/body/font
├── (toko)/
│   ├── layout.js             Navigasi
│   ├── page.js               /
│   └── produk/...
└── (auth)/
    ├── layout.js             kartu tengah
    └── login/page.js
```

`Navigasi` memakai `usePathname` — file klien kecil ([03](03-link-navigation-hooks.md)).

Jangan buat `(toko)/page.js` dan `app/page.js` bersamaan.

**Biasanya digabungkan dengan:** middleware `/admin` jika ada panel.

---

## Resep F — checklist “mirip tugas UTS”

Gunakan sebagai daftar periksa, bukan file wajib dosen:

- [ ] `/` beranda + gambar `next/image`
- [ ] `/produk` filter `?q=`
- [ ] `/produk/[id]` + 404
- [ ] `loading.js` dan `error.js` di katalog
- [ ] Form tambah (action atau handler)
- [ ] Metadata title unik
- [ ] Env untuk API
- [ ] Tidak ada `"use client"` di page yang hanya menampilkan data
- [ ] `npm run build` sukses

**Biasanya digabungkan dengan:** [kombinasi-teknologi.md](../../kombinasi-teknologi.md).

---

## Cara memeriksa sebelum mengumpulkan

```bash
npm run lint
npm run build
```

Baca daftar route di keluaran build. Pastikan `/produk` dan `/produk/[id]` muncul.

Uji manual:

1. Klik semua menu (`Link`, bukan hanya mengetik URL).
2. Buka `/produk/id-yang-salah` → UI 404 kustom.
3. Submit form kosong → pesan validasi, bukan crash.
4. Matikan Laravel (jika dipakai) → `error.js`, bukan stack mentah.
5. Refresh di halaman detail: tidak 404 palsu (file `page.js` ada).
6. Jangan commit `.env.local`.

Jika browser tools tidak tersedia di mesin pemeriksa, setidaknya `build` + klik manual.

**Biasanya digabungkan dengan:** README proyek yang menjelaskan cara menjalankan Laravel + Next.

---

## Yang tidak perlu dikerjakan

Untuk tugas kuliah tipikal, ini boleh ditunda:

- Parallel route + modal intercept
- Cache Components `"use cache"`
- PWA lengkap
- Auth.js / NextAuth produksi
- TypeScript ketat
- Uji Playwright
- `output: "export"` kecuali diminta (mematikan banyak fitur server)

Kerjakan yang diminta spek. Ensiklopedia ini lebih luas dari satu tugas.

---

## Peta “saya lihat error ini”

| Cuplikan pesan / gejala | Buka |
| --- | --- |
| `useState` only in Client Component | [04](04-server-client-component.md) |
| `params` should be awaited | [05](05-dynamic-route-catch-all-optional.md) |
| missing required error components / error.js | [13](13-katalog-file-convention.md#4-errorjs) |
| `You cannot have two parallel pages` / conflict | [02](02-layout-page-template-default.md) |
| `hostname` not configured | [10](10-metadata-image-font.md) |
| Middleware not running | [11](11-env-middleware-rewrite-redirect.md) |
| Fetch failed / ECONNREFUSED 8000 | Laravel belum jalan, atau env salah |
| Hydration failed | [04](04-server-client-component.md#hydration) |
| `useSearchParams` / Suspense | [03](03-link-navigation-hooks.md) |
| `NEXT_PUBLIC` bocor | [11](11-env-middleware-rewrite-redirect.md) |

---

## Lihat juga

- [Cheatsheet Next.js ringkas](../../next-js.md)
- [React](../../react-js.md)
- [Laravel](../../laravel.md)
- [README ensiklopedia](README.md)

---

Sebelum: [13 — katalog file](13-katalog-file-convention.md) · Kembali: [README](README.md)
