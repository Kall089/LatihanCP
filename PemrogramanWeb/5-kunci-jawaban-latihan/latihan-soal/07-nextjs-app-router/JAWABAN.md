# Jawaban 07 — Next.js App Router

---

## A. Konsep

### A1 — b

CSR: HTML kosong + JS besar, SEO/routing/optimasi manual. Next menambah
file-based routing dan HTML dari server.

### A2

`/` , `/tentang` , `/materi/:slug`. `/components` **tidak** ada — tidak ada
`page.tsx` di folder itu.

### A3

`layout.tsx` = kerangka persisten (`<html>`, nav, `{children}`). `page.tsx`
= isi URL itu. Navbar di layout agar tidak di-copy dan **tidak re-mount**
saat `<Link>` (layout tetap).

### A4 — b

`next/link` client navigation + prefetch. `<a>` internal = reload penuh.

### A5

`slug === "css-dasar"`. Jika tidak ada di data: `notFound()` agar 404,
bukan page kosong.

### A6

Mengembalikan daftar params yang di-generate **saat build** (halaman
statis). Cepat, murah di CDN, error slug ketahuan lebih awal.

### A7

Error: hook di Server Component. Perbaikan: page tetap server; pecah tombol
ke `Counter.tsx` dengan `"use client"` di baris pertama.

### A8 — b

`"use client"` untuk state/event/API browser. `async` data + `metadata`
justru ciri server.

### A9

Bundle client terlihat siapa saja di DevTools. Simpan rahasia di server
atau env **tanpa** `NEXT_PUBLIC_`.

### A10

`<title>` dan `<meta name="description">`. Crawler dan tab browser membaca
head; `h1` di body tidak menggantikan metadata.

---

## B. Praktik

### B1

```tsx
import type { Metadata } from "next";
import Link from "next/link";

export const metadata: Metadata = { title: "Tracker" };

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="id">
      <body>
        <nav>
          <Link href="/">Beranda</Link>
          <Link href="/tentang">Tentang</Link>
        </nav>
        {children}
      </body>
    </html>
  );
}
```

### B2

```tsx
import { notFound } from "next/navigation";

const materi = [{ slug: "html", title: "HTML" }];

export default async function Page({
  params,
}: {
  params: Promise<{ slug: string }>;
}) {
  const { slug } = await params;
  const item = materi.find((m) => m.slug === slug);
  if (!item) notFound();
  return <h1>{item.title}</h1>;
}
```

### B3

```tsx
"use client";
import { useState } from "react";

export default function LikeButton({ initialLikes }: { initialLikes: number }) {
  const [likes, setLikes] = useState(initialLikes);
  return (
    <button type="button" onClick={() => setLikes(likes + 1)}>
      {likes} suka
    </button>
  );
}
```

Page server boleh me-render client child; JS tombol di-hydrate terpisah.
