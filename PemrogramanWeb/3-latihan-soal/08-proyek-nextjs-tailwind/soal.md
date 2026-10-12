# Latihan Soal 08 — Proyek Next.js + Tailwind

Kerjakan tanpa kunci. Materi:
[`../../0-materi/08-proyek-nextjs-tailwind/teori.md`](../../0-materi/08-proyek-nextjs-tailwind/teori.md).
Fokus: arsitektur, data flow, kualitas, deployment — bukan mengulang
sintaks JSX.

---

## A. Soal konsep (10)

### A1. Pilihan ganda — tiga layer

- a. `lib/` boleh mengimpor `ProdukCard` agar data sadar UI.
- b. `app/` merangkai halaman; `components/` UI reusable via props; `lib/` data & helper tanpa JSX.
- c. Semua fetch dan kartu harus di `layout.tsx`.
- d. `components/` adalah rute URL otomatis.

### A2. Prediksi impor

Manakah panah yang **melanggar** aturan?

```text
app/page.tsx        → components/ProdukCard.tsx
app/page.tsx        → lib/data.ts
components/Kartu.tsx → lib/format.ts
lib/data.ts         → components/ProdukCard.tsx
```

### A3. Esai — satu sumber data

Beranda menampilkan 3 produk unggulan, halaman `/produk/2` menampilkan
detail. Mengapa menyalin array di dua file berbahaya? Apa yang berubah
saat kamu "ganti ke API" jika helper sudah terpusat?

### A4. Prediksi tipe URL

```ts
export function getProdukById(id: number) {
  return daftarProduk.find((p) => p.id === id);
}
// di page:
const { id } = await params; // id dari /produk/3
getProdukById(id);
```

Mengapa `find` bisa gagal meskipun produk id 3 ada? Perbaikan satu baris?

### A5. Pilihan ganda — client island

Filter kategori paling sesuai diletakkan di…

- a. `"use client"` pada seluruh `app/layout.tsx`.
- b. Server page mengambil data, lalu komponen client kecil menerima array lewat props dan mem-filter.
- c. `lib/data.ts` dengan `useState`.
- d. File CSS saja.

### A6. Esai — empty state dan 404

Bedakan perilaku: (1) filter tidak menghasilkan item, vs (2) URL
`/produk/999`. Komponen/fungsi apa yang menangani masing-masing?

### A7. Prediksi responsive

Proyek memakai `grid-cols-1 md:grid-cols-2 lg:grid-cols-3`. Dosen menguji
di iPhone 360px. Apa yang harus terlihat? Apa yang sering rusak jika
mahasiswa hanya menguji laptop?

### A8. Pilihan ganda — build

- a. `npm run dev` cukup sebagai bukti produksi.
- b. `npm run build` wajib lolos lokal karena Vercel menjalankan perintah yang sama; error tipe sering hanya muncul di sini.
- c. `build` hanya untuk Android.
- d. Preview URL tidak butuh build.

### A9. Esai — env

Bedakan `.env.local`, variabel `NEXT_PUBLIC_*`, dan variabel tanpa prefix.
Mana yang boleh di-commit ke GitHub?

### A10. Prediksi alur deploy

Urutkan langkah: `git push`, `npm run build` lokal, import Vercel, buka
preview PR, push ke `main` produksi. Mana yang harus **paling awal**
setelah fitur selesai?

---

## B. Soal praktik kecil (3)

### B1. `lib/data.ts`

Tulis tipe `Produk` (id, nama, kategori union 3 nilai, harga, deskripsi),
array minimal 3 item, dan `getProdukById`. Tanpa JSX.

### B2. Kartu reusable

Tulis kerangka `ProdukCard({ produk }: { produk: Produk })` yang
menampilkan nama, harga (lewat helper `formatRupiah`), dan `Link` ke
`/produk/${produk.id}`. Tidak mengimpor array data.

### B3. 404 custom

Tulis `app/not-found.tsx` berisi `<h1>` dan tautan kembali ke beranda
(`Link`). Jelaskan di komentar kapan file ini tampil.
