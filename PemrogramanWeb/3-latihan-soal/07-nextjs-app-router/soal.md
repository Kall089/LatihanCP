# Latihan Soal 07 — Next.js App Router

Kerjakan tanpa kunci. Materi:
[`../../0-materi/07-nextjs-app-router/teori.md`](../../0-materi/07-nextjs-app-router/teori.md).

---

## A. Soal konsep (10)

### A1. Pilihan ganda — mengapa Next.js

React murni (CSR) lemah untuk situs publik terutama karena…

- a. Tidak bisa membuat tombol.
- b. HTML awal hampir kosong, routing/SEO/optimasi harus dirakit sendiri.
- c. Tidak mendukung JavaScript.
- d. Tidak bisa memakai Tailwind.

### A2. Prediksi folder → URL

```text
app/
  layout.tsx
  page.tsx
  tentang/page.tsx
  materi/[slug]/page.tsx
  components/Navbar.tsx
```

Tuliskan URL untuk setiap `page.tsx`. Apakah `/components` ada? Mengapa?

### A3. Esai — layout vs page

Apa peran `app/layout.tsx` vs `app/page.tsx`? Mengapa navbar ditaruh di
layout, bukan di-copy ke setiap page? Apa yang terjadi pada layout saat
`<Link>` pindah rute?

### A4. Pilihan ganda — navigasi internal

- a. Selalu `<a href="/tentang">` karena standar HTML.
- b. `<Link href="/tentang">` dari `next/link` (tanpa reload penuh, prefetch).
- c. `window.location = "/tentang"` di Server Component.
- d. `<a to="/tentang">` seperti React Router v5.

### A5. Prediksi dynamic route

User membuka `/materi/css-dasar`. File `app/materi/[slug]/page.tsx` (Next 15).
Apa isi `slug` setelah `const { slug } = await params`? Apa yang harus
dilakukan jika data tidak ketemu?

### A6. Esai — `generateStaticParams`

Untuk apa fungsi ini? Apa keuntungan halaman yang di-generate saat build?

### A7. Prediksi server vs client

```tsx
export default function Page() {
  const [n, setN] = useState(0);
  return <button onClick={() => setN(n + 1)}>{n}</button>;
}
```

File **tanpa** `"use client"`. Apa yang terjadi? Perbaikan sesuai pola
"halaman server, tombol client kecil"?

### A8. Pilihan ganda — kapan `"use client"`

- a. Setiap `page.tsx` wajib client.
- b. Saat butuh `useState`, event handler, atau API browser (`localStorage`).
- c. Saat `async function` mengambil data di server.
- d. Saat menulis `export const metadata`.

### A9. Esai — rahasia

Mengapa API key di Client Component berbahaya? Di mana tempat yang benar
(server, env tanpa `NEXT_PUBLIC_`)?

### A10. Prediksi metadata

```tsx
export const metadata = {
  title: "Tentang | Tracker",
  description: "Profil tim.",
};
```

Tag HTML apa yang dihasilkan di `<head>`? Mengapa ini penting untuk SEO
dibanding hanya `<h1>` di body?

---

## B. Soal praktik kecil (3)

Bayangkan kamu di dalam proyek Next (tidak perlu `node_modules` di jawaban).

### B1. Layout + Link

Tulis `app/layout.tsx` minimal: `html lang="id"`, metadata title, nav dengan
dua `Link` ke `/` dan `/tentang`, `{children}`.

### B2. Dynamic + 404

Tulis `app/materi/[slug]/page.tsx`: `await params`, cari di array
`[{ slug: "html", title: "HTML" }]`, `notFound()` jika gagal, tampilkan
`title`.

### B3. Island client

Tulis `LikeButton.tsx`: baris pertama `"use client"`, props `initialLikes: number`,
`useState`, tombol menambah likes. Jelaskan dalam komentar mengapa page
yang memakai tombol ini tetap boleh Server Component.
