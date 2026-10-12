# Jawaban 08 — Proyek Next.js + Tailwind

---

## A. Konsep

### A1 — b

Tiga layer: `app/` halaman, `components/` UI props, `lib/` data tanpa JSX.
`lib` tidak mengimpor kartu.

### A2

Yang melanggar: `lib/data.ts → components/ProdukCard.tsx`. Data layer tidak
boleh tahu UI.

### A3

Copy array = dua kebenaran; edit satu, yang lain basi. Helper terpusat:
ganti isi `getProdukById` ke `fetch` tanpa mengubah kartu.

### A4

`params.id` **string** `"3"`; `p.id` number `3`; `===` gagal. Perbaikan:
`getProdukById(Number(id))`.

### A5 — b

Island client menerima array serializable. Jangan `"use client"` di root
layout (seluruh app jadi client).

### A6

(1) Empty state di komponen daftar (`tampil.length === 0`). (2)
`notFound()` → `app/not-found.tsx`. Jangan samakan filter kosong dengan 404.

### A7

360px = 1 kolom, tidak scroll horizontal. Yang sering rusak: nav overflow,
grid kaku 3 kolom, gambar melebar.

### A8 — b

Vercel ≈ `npm run build`. `dev` lebih longgar (error tipe/import kadang
tertunda).

### A9

`.env.local` rahasia lokal, git-ignore. `NEXT_PUBLIC_*` bocor ke browser
(hanya data publik). Tanpa prefix = server. Yang boleh di-commit:
`.env.example` tanpa nilai, **bukan** `.env.local`.

### A10

Paling awal setelah fitur: **`npm run build` lokal**. Baru commit/push,
preview PR, merge `main` produksi.

---

## B. Praktik

### B1

```ts
export type Produk = {
  id: number;
  nama: string;
  kategori: "kopi" | "nonkopi" | "snack";
  harga: number;
  deskripsi: string;
};

export const daftarProduk: Produk[] = [
  { id: 1, nama: "Kopi Susu", kategori: "kopi", harga: 18000, deskripsi: "Gula aren." },
  { id: 2, nama: "Teh Tarik", kategori: "nonkopi", harga: 12000, deskripsi: "Berbuih." },
  { id: 3, nama: "Roti Bakar", kategori: "snack", harga: 15000, deskripsi: "Cokelat keju." },
];

export function getProdukById(id: number) {
  return daftarProduk.find((p) => p.id === id);
}
```

### B2

```tsx
import Link from "next/link";
import type { Produk } from "@/lib/data";
import { formatRupiah } from "@/lib/format";

export default function ProdukCard({ produk }: { produk: Produk }) {
  return (
    <article>
      <h2>{produk.nama}</h2>
      <p>{formatRupiah(produk.harga)}</p>
      <Link href={`/produk/${produk.id}`}>Detail</Link>
    </article>
  );
}
```

### B3

```tsx
import Link from "next/link";

export default function NotFound() {
  return (
    <main>
      <h1>Halaman tidak ditemukan</h1>
      <Link href="/">Kembali ke beranda</Link>
    </main>
  );
}
```

Tampil saat `notFound()` dipanggil atau URL tidak cocok rute mana pun.
