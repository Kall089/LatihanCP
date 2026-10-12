# Modul 08 — Proyek Next.js + Tailwind: Arsitektur, Data Flow, Deployment

> Praktikum terkait: [`../../1-pembelajaran/08-proyek-nextjs-tailwind/`](../../1-pembelajaran/08-proyek-nextjs-tailwind/)
> (4 tahap: perencanaan data, daftar komponen, routing detail, proyek akhir).
> Slide ringkasan: [`slides.pptx`](slides.pptx).
> Studi kasus: [`../../4-studi-kasus/03-katalog-produk-nextjs/`](../../4-studi-kasus/03-katalog-produk-nextjs/).

## Tujuan setelah membaca materi ini

- Merancang struktur folder tiga layer (`lib/`, `components/`, `app/`) yang
  bisa dinilai dan ditumbuhkan.
- Menjelaskan data flow satu arah: data terpusat → server page → props.
- Menjaga kualitas: responsif, aksesibel, empty state, 404.
- Men-deploy ke Vercel lewat Git, dengan env yang aman.

Modul ini **bukan** sintaks baru. Ia adalah cara menggabungkan Modul 01–07
menjadi satu produk. Praktikum 08 membangun *Learning Tracker*; studi kasus
03 membangun *katalog produk* dengan pola yang sama.

---

## 1. Dari latihan bab ke produk

Latihan bab sengaja sempit: satu file, satu konsep. Produk sungguhan gagal
kalau semua konsep ditumpuk di `page.tsx` 500 baris. Yang dinilai dosen
(dan rekan kerja) sering bukan "apakah Tailwind-nya bagus", melainkan:

1. Apakah data punya **satu sumber**?
2. Apakah komponen **dipakai ulang**, bukan di-copy?
3. Apakah rute detail dan 404 masuk akal?
4. Apakah HP tidak merusak layout?
5. Apakah `npm run build` lolos?

Empat tahap praktikum 08:

| Tahap | Fokus | Output |
|---|---|---|
| 01 perencanaan data | Tipe + array di `data/` atau `lib/` | `Material[]` lengkap field |
| 02 daftar komponen | Kartu + grid Tailwind | Beranda memetakan data |
| 03 routing detail | `[slug]` + `notFound` | Halaman per materi |
| 04 proyek akhir | Filter, progres, island client | Interaksi tanpa merusak layer |

---

## 2. Arsitektur tiga layer

```text
katalog-produk/
├── app/                         ← ROUTING + halaman
│   ├── layout.tsx                  navbar/footer global
│   ├── page.tsx                    /          beranda
│   ├── globals.css                 Tailwind directives
│   ├── produk/
│   │   ├── page.tsx                /produk    daftar + filter
│   │   └── [id]/page.tsx           /produk/3  detail
│   └── not-found.tsx               404 kustom
├── components/                  ← UI dipakai ulang
│   ├── Navbar.tsx
│   ├── ProdukCard.tsx
│   └── FilterKategori.tsx          "use client" (interaktif)
├── lib/                         ← DATA & logika murni
│   ├── data.ts                     array + getProduk / getById
│   └── format.ts                   formatRupiah
├── package.json
└── tailwind.config  tsconfig
```

Aturan impor **searah**:

```text
app/  ──────▶  components/  ──x──▶  (tidak ke app/)
  │                 │
  └──▶ lib/ ◀───────┘

lib/ TIDAK mengimpor React/komponen.
```

Kalau `lib/data.ts` mulai `import ProdukCard`, arsitektur sudah bocor: data
layer tidak boleh tahu soal UI.

### Tanggung jawab tiap layer

| Layer | Boleh | Jangan |
|---|---|---|
| `lib/` | Tipe, array, `getById`, `formatRupiah` | JSX, `useState`, class Tailwind |
| `components/` | Markup + props; client hanya yang perlu | Fetch/copy array sendiri; hardcode data |
| `app/` | Ambil data, susun komponen, metadata | Logika berat, kartu di-copy-paste |

Analogi rumah (lanjutan Modul 01): `lib/` = inventaris barang, `components/`
= furnitur jadi, `app/` = denah ruangan yang menata furnitur.

Konvensi nama: komponen PascalCase (`ProdukCard.tsx`), fungsi helper camelCase
(`getProdukById`), rute folder huruf kecil (`produk/[id]`).

---

## 3. Data flow: satu sumber, satu arah

```text
 lib/data.ts          app/produk/page.tsx       components/
 ┌───────────┐  impor  ┌────────────────┐ props ┌──────────────┐
 │ produk[]  │ ──────▶ │ SERVER comp.   │ ────▶ │ ProdukCard   │
 │ getProduk │         │ ambil + susun  │       │ (server OK)  │
 └───────────┘         │                │       ├──────────────┤
                       │                │ ────▶ │ FilterKateg. │
                       └────────────────┘       │ "use client" │
                                                │ useState     │
                                                └──────────────┘
```

Dua strategi filter yang sah:

1. **Client island** — seluruh array dikirim ke komponen client; `useState`
   kategori; `filter()` di browser. Cocok untuk data kecil (katalog kuliah).
2. **URL search param** — `/produk?kategori=kopi`. Server membaca `searchParams`,
   memfilter sebelum render. Cocok jika data besar / ingin tautan bisa di-share.

Untuk tugas, strategi 1 lebih sederhana dan selaras Modul 06. Yang penting:
**jangan** menyalin array produk di beranda *dan* di halaman detail dengan
isi berbeda. Satu `lib/data.ts`.

### Tipe sebagai kontrak

```ts
// lib/data.ts
export type Produk = {
  id: number;
  nama: string;
  kategori: "kopi" | "nonkopi" | "snack";
  harga: number;
  deskripsi: string;
};

export const daftarProduk: Produk[] = [
  {
    id: 1,
    nama: "Kopi Susu Senja",
    kategori: "kopi",
    harga: 18000,
    deskripsi: "Susu fresh dan gula aren.",
  },
];

export function getProdukById(id: number) {
  return daftarProduk.find((p) => p.id === id);
}

export function getProdukByKategori(kategori: Produk["kategori"] | "semua") {
  if (kategori === "semua") return daftarProduk;
  return daftarProduk.filter((p) => p.kategori === kategori);
}
```

Union `"kopi" | "nonkopi" | "snack"` mencegah typo `"Kopi"` yang lolos di
runtime tapi merusak filter. TypeScript mengganti sebagian tes manual.

Format uang di `lib/format.ts` agar kartu dan halaman detail tidak merakit
string berbeda:

```ts
export function formatRupiah(n: number) {
  return new Intl.NumberFormat("id-ID", {
    style: "currency",
    currency: "IDR",
    maximumFractionDigits: 0,
  }).format(n);
}
```

Besok data diganti fetch API: yang berubah cukup isi `getProdukById`. Kartu
tetap menerima `Produk`. Itulah arti "satu sumber".

---

## 4. Halaman merangkai, komponen menampilkan

```tsx
// app/page.tsx — SERVER
import { daftarProduk } from "@/lib/data";
import ProdukCard from "@/components/ProdukCard";
import Link from "next/link";

export default function Beranda() {
  const unggulan = daftarProduk.slice(0, 3);
  return (
    <main>
      <h1>Warung Kopi Senja</h1>
      <section aria-labelledby="unggulan">
        <h2 id="unggulan">Unggulan minggu ini</h2>
        <ul>
          {unggulan.map((p) => (
            <li key={p.id}>
              <ProdukCard produk={p} />
            </li>
          ))}
        </ul>
        <Link href="/produk">Lihat semua menu</Link>
      </section>
    </main>
  );
}
```

`ProdukCard` **tidak** mengimpor `daftarProduk`. Ia bodoh dalam arti baik:
terima props, tampilkan. Karena itu kartu yang sama dipakai beranda dan
`/produk`.

Halaman detail:

```tsx
// app/produk/[id]/page.tsx
import { notFound } from "next/navigation";
import { daftarProduk, getProdukById } from "@/lib/data";
import { formatRupiah } from "@/lib/format";

export function generateStaticParams() {
  // id di URL adalah string
  return daftarProduk.map((p) => ({ id: String(p.id) }));
}

export default async function DetailProduk({
  params,
}: {
  params: Promise<{ id: string }>;
}) {
  const { id } = await params;
  const produk = getProdukById(Number(id));
  if (!produk) notFound();
  return (
    <article>
      <h1>{produk.nama}</h1>
      <p>{formatRupiah(produk.harga)}</p>
      <p>{produk.deskripsi}</p>
    </article>
  );
}
```

`Number(id)` wajib: param URL selalu string. `getProdukById(id)` tanpa
konversi tidak akan ketemu.

---

## 5. Client island: interaktivitas tanpa mengorbankan server

Halaman `/produk` tetap Server Component. Filter adalah anak kecil:

```tsx
"use client";

import { useState } from "react";
import type { Produk } from "@/lib/data";
import ProdukCard from "./ProdukCard";

export default function Katalog({ items }: { items: Produk[] }) {
  const [kategori, setKategori] = useState<"semua" | Produk["kategori"]>("semua");
  const tampil =
    kategori === "semua"
      ? items
      : items.filter((p) => p.kategori === kategori);

  return (
    <div>
      {/* tombol filter: setKategori(...) */}
      {tampil.length === 0 ? (
        <p>Tidak ada produk di kategori ini.</p>
      ) : (
        <ul>
          {tampil.map((p) => (
            <li key={p.id}>
              <ProdukCard produk={p} />
            </li>
          ))}
        </ul>
      )}
    </div>
  );
}
```

Server mengirim `items` sebagai props (serializable). State filter hidup
hanya di island. Navbar, footer, metadata tetap server.

Ini pola tahap 04 praktikum (Learning Tracker: filter selesai/belum) dan
studi kasus katalog.

---

## 6. Checklist kualitas sebelum dikumpulkan

### Responsif

Uji di DevTools: **360px**, **768px**, **1280px**.

```text
grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6
```

Tidak boleh ada scroll horizontal. Gambar: `next/image` atau
`max-w-full h-auto`. Navbar di HP: tumpuk (`flex-col`) atau menu sederhana;
jangan biarkan tautan terpotong.

Breakpoint 768px (`md:`) adalah yang sama dengan media query Modul 03.

### Aksesibilitas

- Satu `<h1>` per halaman; turun ke `h2`/`h3` tanpa loncat.
- Semua `<img>` ber-`alt`; dekoratif: `alt=""`.
- Form (kalau ada) ber-`<label for>`.
- Fokus keyboard: `focus-visible:ring-2` — jangan `outline-none` polos.
- Kontras: `text-slate-600` di putih biasanya lolos; `text-slate-300` sering
  gagal.

### Edge case

| Situasi | Perilaku yang diharapkan |
|---|---|
| Array kosong / filter tidak ketemu | Pesan "belum ada data", bukan halaman putih |
| `/produk/999` | `notFound()` → `app/not-found.tsx` |
| Nama produk sangat panjang | `truncate` atau `break-words`, kartu tidak pecah |
| Data lambat (nanti API) | `loading.tsx` opsional |

Tanpa empty state dan 404, proyek terasa demo, bukan produk.

---

## 7. Deployment: dari laptop ke URL publik

```text
 Laptop                GitHub                 Vercel
 ┌──────────┐  push   ┌──────────┐  webhook  ┌──────────────┐
 │ kode +   │ ──────▶ │ repo     │ ────────▶ │ npm install  │
 │ git      │         │ main     │           │ npm run build│
 └──────────┘         └──────────┘           │ deploy CDN   │
      │                    │                 └──────┬───────┘
      │                    │ branch/PR              │
      │                    └──────▶ PREVIEW URL     ▼
      │                            (uji dulu!)  https://
      └── npm run build (cek lokal              proyekmu
          sebelum push!)                        .vercel.app
```

Langkah praktis:

1. `npm run build` **lolos di laptop**. Error tipe/import yang lolos `dev`
   sering baru muncul di sini.
2. Buat repo GitHub, `git push`.
3. Daftar di [vercel.com](https://vercel.com), *Import Project*, framework
   terdeteksi Next.js.
4. Setiap push ke `main` = produksi. Setiap pull request = **preview URL**
   untuk diuji dosen/teman tanpa merusak situs live.

Vercel adalah pembuat Next.js; konfigurasinya paling sedikit. Alternatif:
Netlify, Cloudflare Pages — konsepnya sama: build command `next build`.

### Environment variable

```text
.env.local          rahasia lokal (git-ignored)
.env.example        nama variabel tanpa nilai — boleh di-commit

NEXT_PUBLIC_NAMA    ikut ke bundle browser — hanya data publik
NAMA_LAIN           server-only
```

**Jangan** commit API key. Pastikan `.gitignore` memuat `.env*`. Di Vercel,
isi variabel lewat dashboard (Production / Preview / Development).

Untuk proyek kuliah tanpa API, kamu mungkin tidak butuh env sama sekali —
itu normal.

---

## 8. Alur kerja yang disarankan saat membangun

1. Tulis tipe + 6–10 item palsu di `lib/data.ts` (jangan kejar desain dulu).
2. Kartu paling jelek sekalipun di `ProdukCard` — yang penting data tampil.
3. Rute daftar dan detail + 404.
4. Baru Tailwind rapi, hover, grid responsif.
5. Filter client.
6. `npm run build`, uji 360px, Tab merambat fokus.
7. Push & preview deploy.

Membalik urutan (menghabiskan hari di gradient hero sebelum data ada) adalah
jebakan klasik proyek akhir.

---

## 9. Kesalahan umum

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | Semua kode di `page.tsx` | Tidak terbaca, tidak reusable | Pecah layer |
| 2 | Data di-copy per halaman | Beranda ≠ detail | Satu `lib/data.ts` |
| 3 | Tak pernah `npm run build` | Gagal di Vercel | Build lokal dulu |
| 4 | `.env` ter-commit | Kunci bocor di git history | `.gitignore` + rotate key |
| 5 | Uji hanya desktop | Layout hancur di HP dosen | 360 / 768 / 1280 |
| 6 | Tanpa 404 / empty state | Crash atau blank | `notFound()` + pesan |
| 7 | `"use client"` di `layout.tsx` | Seluruh app jadi client | Layout server; island kecil |
| 8 | `params.id` tanpa `Number()` | `find` selalu gagal | Konversi tipe |

---

## 10. Cheatsheet

```text
# Setup
npx create-next-app@latest katalog --typescript --tailwind --app
cd katalog && npm run dev

# Layer
lib/          data + logika murni (tanpa JSX)
components/   UI reusable via props
app/          halaman merangkai + metadata

# Data flow
lib/data.ts → page.tsx (server, boleh await) → props → komponen
Filter/tombol: island "use client"

# Kualitas
alt, label, h1→h2, focus-visible
uji 360 / 768 / 1280
empty state, notFound(), truncate

# Deploy
npm run build     WAJIB lolos
git push          → GitHub → Vercel
PR                → preview URL
.env.local        jangan di-commit
NEXT_PUBLIC_*     boleh ke browser; selain itu server-only
```

## Lanjut ke praktikum dan studi kasus

Empat tahap di [`../../1-pembelajaran/08-proyek-nextjs-tailwind/`](../../1-pembelajaran/08-proyek-nextjs-tailwind/)
adalah *Learning Tracker* (materi kuliah sebagai data).

Studi kasus [`../../4-studi-kasus/03-katalog-produk-nextjs/`](../../4-studi-kasus/03-katalog-produk-nextjs/)
memakai arsitektur yang sama untuk katalog UMKM. Kerjakan tanpa membuka
[`../../5-kunci-jawaban-latihan/studi-kasus/03-katalog-produk-nextjs/`](../../5-kunci-jawaban-latihan/studi-kasus/03-katalog-produk-nextjs/).

Uji konsep: [`../../3-latihan-soal/08-proyek-nextjs-tailwind/soal.md`](../../3-latihan-soal/08-proyek-nextjs-tailwind/soal.md).
