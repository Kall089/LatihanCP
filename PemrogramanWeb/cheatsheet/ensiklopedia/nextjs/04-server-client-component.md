# 04 — Server Component dan Client Component

[← 03 navigasi](03-link-navigation-hooks.md) · [Berikut: dynamic route →](05-dynamic-route-catch-all-optional.md)

**Untuk apa:** membagi pekerjaan. Server mengambil data dan merakit HTML. Klien menangani state, event, dan API browser.

Default App Router: **setiap file adalah Server Component**, kecuali ada `"use client"` di baris paling atas.

## Daftar isi file ini

- [Server Component](#server-component)
- [Client Component dan "use client"](#client-component-dan-use-client)
- [Yang boleh dan tidak boleh, satu per satu](#yang-boleh-dan-tidak-boleh-satu-per-satu)
- [Komposisi: server merender klien](#komposisi-server-merender-klien)
- [Children sebagai pola lubang](#children-sebagai-pola-lubang)
- [Serialisasi props](#serialisasi-props)
- [Jangan kirim rahasia](#jangan-kirim-rahasia)
- [Hydration](#hydration)
- [Library pihak ketiga](#library-pihak-ketiga)
- [Context, hook, dan batas](#context-hook-dan-batas)
- [fetch di server versus fetch di klien](#fetch-di-server-versus-fetch-di-klien)
- [use client versus use server](#use-client-versus-use-server)
- [Kesalahan umum](#kesalahan-umum)

## Server Component

**Untuk apa:** merender UI di server, mengakses sumber data langsung, dan tidak mengirim JavaScript komponen itu ke browser.

`app/produk/page.js`:

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
      <ul>
        {produk.map((item) => (
          <li key={item.id}>{item.nama}</li>
        ))}
      </ul>
    </main>
  );
}
```

Ciri Server Component, satu per satu:

- Boleh `async/await` langsung di komponen.
- Boleh membaca `process.env` tanpa awalan `NEXT_PUBLIC_`.
- Boleh mengimpor modul Node (fs, path) — hati-hati di hosting serverless.
- Boleh memanggil database atau Laravel dari server.
- **Tidak** boleh `useState`, `useEffect`, `onClick`.
- **Tidak** boleh `window`, `document`, `localStorage` saat render.
- Tidak menambah bundle klien untuk komponen itu sendiri.

`page.js`, `layout.js`, `loading.js` (tanpa hook), `not-found.js` (tanpa hook), dan komponen tanpa direktif adalah server secara default.

**Biasanya digabungkan dengan:** `fetch`, `params`/`searchParams` yang di-await, dan Client Component kecil untuk tombol.

## Client Component dan "use client"

**Untuk apa:** menandai file sebagai batas klien. File itu dan imporannya (kecuali dipisah sadar) masuk model klien.

`app/components/TombolSuka.js`:

```jsx
"use client";

import { useState } from "react";

export default function TombolSuka() {
  const [suka, setSuka] = useState(false);

  return (
    <button
      type="button"
      aria-pressed={suka}
      onClick={() => setSuka((lama) => !lama)}
    >
      {suka ? "Disukai" : "Sukai produk"}
    </button>
  );
}
```

Aturan `"use client"`, satu per satu:

- Harus **baris pertama** file (boleh setelah komentar? Utamakan paling atas sebelum impor).
- Berlaku untuk **seluruh file**, bukan satu fungsi.
- Tidak membuat file “hanya jalan di browser”. Client Component **tetap di-prerender di server** untuk HTML awal, lalu dihidrasi.
- Karena tetap di-prerender, `window` saat render awal tetap berbahaya — taruh di event atau `useEffect`.

### Kapan wajib "use client"

- `useState`, `useReducer`, `useEffect`, `useRef`, `useContext` (yang kamu buat di klien), dan hook React lain yang bergantung pada state klien.
- Hook Next: `useRouter`, `usePathname`, `useSearchParams`, `useParams`.
- Event: `onClick`, `onChange`, `onSubmit` (controlled), `onScroll`.
- API browser: `localStorage`, `IntersectionObserver`, `matchMedia`.
- Library yang memakai hook/event di dalam (banyak date picker, carousel).

### Kapan tidak perlu

- Hanya menampilkan props dan teks.
- Hanya `Link` dan gambar.
- Hanya class Tailwind.
- Hanya `map` daftar yang datanya sudah diambil server.

**Biasanya digabungkan dengan:** halaman server yang mengirim data sebagai props.

## Yang boleh dan tidak boleh, satu per satu

| Kebutuhan | Server | Client |
| --- | --- | --- |
| `async` komponen | Ya | Tidak (komponen klien biasa sync; data lewat effect/action) |
| `useState` / `onClick` | Tidak | Ya |
| `fetch` ke API | Ya, langsung | Ya, di effect atau event |
| `cookies()` / `headers()` | Ya | Tidak |
| `next/headers` | Ya | Tidak |
| `localStorage` | Tidak | Ya, setelah mount |
| Ekspor `metadata` | Ya | Tidak |
| Server Action sebagai prop | Boleh dikirim ke klien | Boleh dipanggil |
| Impor Client Component | Ya | Ya |
| Impor Server Component | — | **Tidak langsung** (pakai children) |

Bacaan resmi: [Server and Client Components](https://nextjs.org/docs/app/getting-started/server-and-client-components).

## Komposisi: server merender klien

**Untuk apa:** halaman tetap server, tombol tetap klien.

`app/produk/page.js`:

```jsx
import TombolSuka from "../components/TombolSuka";

export default function HalamanProduk() {
  return (
    <main>
      <h1>Buku JavaScript</h1>
      <TombolSuka />
    </main>
  );
}
```

Arah impor yang diizinkan:

```text
Server Component  -->  Client Component     boleh
Client Component  -->  Client Component     boleh
Server Component  -->  Server Component     boleh
Client Component  -->  Server Component     tidak (langsung)
```

Jika file klien menulis `import ServerBesar from "./ServerBesar"`, `ServerBesar` ikut jadi klien (atau error jika `ServerBesar` async/pakai API server).

**Biasanya digabungkan dengan:** folder `app/components/` untuk tombol, form, dan slider.

## Children sebagai pola lubang

**Untuk apa:** memasukkan Server Component ke dalam kerangka klien tanpa mengimpor file server dari file klien.

`app/components/KerangkaKlien.js`:

```jsx
"use client";

import { useState } from "react";

export default function KerangkaKlien({ children }) {
  const [buka, setBuka] = useState(true);

  return (
    <section>
      <button type="button" onClick={() => setBuka((n) => !n)}>
        {buka ? "Sembunyikan" : "Tampilkan"}
      </button>
      {buka ? children : null}
    </section>
  );
}
```

`app/produk/page.js` (server):

```jsx
import KerangkaKlien from "../components/KerangkaKlien";
import DaftarServer from "../components/DaftarServer";

export default function Halaman() {
  return (
    <KerangkaKlien>
      <DaftarServer />
    </KerangkaKlien>
  );
}
```

`DaftarServer` tetap Server Component. Yang dikirim ke klien adalah **hasil render** (HTML/payload), bukan modul servernya.

Ini pola resmi: Client Component sebagai kerangka, Server Component sebagai `children`.

**Biasanya digabungkan dengan:** tab, accordion, dan modal yang isinya data server.

## Serialisasi props

**Untuk apa:** memahami data apa yang boleh menyeberang batas server → klien.

Boleh:

- string, number, boolean, `null`
- array dan object JSON-plain
- Date (diperlakukan khusus oleh React; tetap lebih jelas kirim ISO string)
- Server Action (fungsi yang ditandai `"use server"`)

Tidak boleh / bermasalah:

- fungsi biasa (`onClick` buatanmu yang didefinisikan di server)
- class instance
- `Map` / `Set` / `Symbol`
- objek yang berisi method
- koneksi database, stream Node

Salah:

```jsx
// page.js server
<TombolSuka onSuka={() => console.log("suka")} />
```

Fungsi anonim tidak bisa diseberangkan. Pindahkan handler ke dalam Client Component, atau kirim Server Action.

Benar (handler di klien):

```jsx
"use client";

export default function TombolSuka() {
  function handleSuka() {
    console.log("suka");
  }
  return <button type="button" onClick={handleSuka}>Suka</button>;
}
```

Benar (action dari server):

```jsx
import TombolSuka from "../components/TombolSuka";
import { catatSuka } from "../aksi";

export default function Halaman() {
  return <TombolSuka aksi={catatSuka} />;
}
```

**Biasanya digabungkan dengan:** data produk `{ id, nama, harga }` sebagai props, bukan seluruh objek ORM.

## Jangan kirim rahasia

**Untuk apa:** mencegah token bocor ke HTML dan bundle.

Salah:

```jsx
<PanelAdmin token={process.env.RAHASIA_ADMIN} />
```

Jika `PanelAdmin` klien, nilai env server bisa ikut terkirim.

Benar:

- olah rahasia di Server Component / Server Action / Route Handler;
- kirim ke klien hanya data yang boleh publik;
- env klien harus berawalan `NEXT_PUBLIC_` dan memang publik.

**Biasanya digabungkan dengan:** [11](11-env-middleware-rewrite-redirect.md).

## Hydration

**Untuk apa:** menyambungkan HTML server dengan JavaScript klien.

Alur:

1. Server merender HTML (termasuk Client Component).
2. Browser menampilkan HTML.
3. JavaScript klien “menghidrasi” komponen interaktif.
4. Event mulai hidup.

Jika HTML server ≠ render klien pertama, muncul **hydration mismatch**.

Penyebab umum:

- `new Date().toLocaleString()` berbeda zona / waktu render.
- `Math.random()` di render.
- Membaca `localStorage` langsung di body komponen.
- `window.innerWidth` saat render.
- Markup tidak valid (`<p><div>`) yang dibetulkan browser.

Pola aman untuk “hanya di klien”:

```jsx
"use client";

import { useEffect, useState } from "react";

export default function NamaTersimpan() {
  const [nama, setNama] = useState("");

  useEffect(() => {
    setNama(window.localStorage.getItem("nama") ?? "");
  }, []);

  return <p>{nama || "Belum ada nama tersimpan"}</p>;
}
```

Render pertama server dan klien sama (`""`), baru effect mengisi.

**Biasanya digabungkan dengan:** `suppressHydrationWarning` hanya pada teks waktu di `<html>`/`<body>` jika terpaksa — bukan obat untuk seluruh halaman.

## Library pihak ketiga

**Untuk apa:** memakai paket yang belum siap Server Component.

Pola:

```jsx
"use client";

import { Carousel } from "beberapa-carousel";

export default function Slider({ gambar }) {
  return <Carousel slides={gambar} />;
}
```

Halaman server:

```jsx
import Slider from "../components/Slider";

export default function Halaman() {
  return <Slider gambar={["/buku.jpg"]} />;
}
```

Jika library mengakses `window` di tingkat modul (saat diimpor), kamu mungkin perlu `dynamic` + `ssr: false`:

```jsx
"use client";

import dynamic from "next/dynamic";

const Peta = dynamic(() => import("./PetaDalam"), { ssr: false });

export default function BungkusPeta() {
  return <Peta />;
}
```

`ssr: false` meniadakan HTML server untuk komponen itu. Pakai hemat; SEO dan LCP bisa terdampak.

**Biasanya digabungkan dengan:** `next/dynamic`, fallback “Memuat peta…”, dan data marker sebagai props.

## Context, hook, dan batas

**Untuk apa:** menaruh Provider di tempat yang benar.

Provider React Context harus Client Component:

```jsx
"use client";

import { createContext, useContext, useState } from "react";

const KeranjangContext = createContext(null);

export function PenyediaKeranjang({ children }) {
  const [item, setItem] = useState([]);
  return (
    <KeranjangContext.Provider value={{ item, setItem }}>
      {children}
    </KeranjangContext.Provider>
  );
}

export function useKeranjang() {
  const ctx = useContext(KeranjangContext);
  if (!ctx) throw new Error("useKeranjang di luar penyedia");
  return ctx;
}
```

Pasang di layout (server) sebagai kerangka:

```jsx
import { PenyediaKeranjang } from "./components/Keranjang";

export default function RootLayout({ children }) {
  return (
    <html lang="id">
      <body>
        <PenyediaKeranjang>{children}</PenyediaKeranjang>
      </body>
    </html>
  );
}
```

`children` halaman tetap bisa Server Component. Jangan membungkus seluruh toko sebagai satu file `"use client"` raksasa.

**Biasanya digabungkan dengan:** keranjang, tema, dan status UI global — bukan data produk dari database.

## fetch di server versus fetch di klien

### Server (diutamakan untuk data awal halaman)

- Tidak menunggu JS klien.
- Rahasia tidak bocor.
- Bisa digabung `loading.js`.
- Cache/revalidate dikontrol Next — [07](07-fetch-cache-revalidate.md).

### Klien

Pakai jika:

- data bergantung pada interaksi (infinite scroll, autocomplete per ketikan);
- sumber mensyaratkan token browser;
- widget pihak ketiga.

```jsx
"use client";

import { useEffect, useState } from "react";

export default function CariHidup() {
  const [q, setQ] = useState("");
  const [hasil, setHasil] = useState([]);

  useEffect(() => {
    if (!q) {
      setHasil([]);
      return;
    }
    let hidup = true;
    fetch(`/api/produk?q=${encodeURIComponent(q)}`)
      .then((r) => r.json())
      .then((data) => {
        if (hidup) setHasil(data);
      });
    return () => {
      hidup = false;
    };
  }, [q]);

  return (
    <div>
      <input value={q} onChange={(e) => setQ(e.target.value)} />
      <ul>
        {hasil.map((item) => (
          <li key={item.id}>{item.nama}</li>
        ))}
      </ul>
    </div>
  );
}
```

Jangan memanggil Route Handler milik sendiri dari Server Component di host yang sama hanya untuk “berputar-putar”; akses sumber data langsung. Pengecualian: kamu memang butuh HTTP publik.

**Biasanya digabungkan dengan:** Route Handler di [08](08-route-handler-http.md) untuk endpoint yang dikonsumsi klien.

## use client versus use server

Dua direktif berbeda:

| Direktif | Arti |
| --- | --- |
| `"use client"` | File ini komponen klien (batas bundle) |
| `"use server"` | Fungsi-fungsi ini Server Action (jalan di server) |

Boleh:

- file `"use client"` memanggil fungsi dari file `"use server"`;
- file server mengekspor action dan merender form.

Tidak boleh:

- menulis keduanya di baris atas seolah sinonim;
- mengira `"use server"` membuat komponen menjadi Server Component (itu sudah default).

Lihat [09](09-server-actions-form.md).

**Biasanya digabungkan dengan:** form `action={fn}` tanpa menulis endpoint manual.

## Memecah file yang terlalu klien

Gejala: `page.js` diawali `"use client"` lalu `fetch` di `useEffect` untuk data utama.

Perbaikan:

1. Hapus `"use client"` dari `page.js`.
2. `await fetch` di page.
3. Pindahkan input/tombol ke `KomponenKecil.js` dengan `"use client"`.
4. Kirim data awal lewat props jika klien masih butuh.

Ukuran bundle turun, LCP biasanya naik.

## Kesalahan umum

- **`useState` ditolak:** tambah `"use client"` di file yang memakai hook, bukan di layout root kecuali terpaksa.
- **`window is not defined`:** akses browser saat render server / prerender. Pindahkan ke effect/event.
- **Hydration mismatch:** output awal beda; hindari random/waktu/storage di render.
- **Impor server dari klien:** pecah dengan `children` atau pindahkan data-fetch ke page.
- **Props fungsi biasa:** tidak serial. Pakai action atau handler di klien.
- **Seluruh `app/` jadi klien:** kehilangan manfaat App Router.
- **Metadata di file klien:** pindahkan ekspor metadata ke `page.js`/`layout.js` server.
- **Membandingkan “CSR vs SSR” secara kaku:** Client Component tetap bisa prerender.

## Checklist keputusan

1. Apakah ada hook atau event? Jika tidak, tetap server.
2. Apakah data rahasia? Olah di server.
3. Apakah hanya satu tombol yang interaktif? Buat file klien kecil.
4. Apakah kerangka interaktif mengelilingi data server? Pakai `children`.
5. Apakah perlu metadata? Jaga file page/layout tetap server.

## Lihat juga

- [07 — fetch dan cache](07-fetch-cache-revalidate.md)
- [09 — Server Action](09-server-actions-form.md)
- [Cheatsheet React](../../react-js.md)

---

Sebelum: [03 — navigasi](03-link-navigation-hooks.md) · Berikut: [05 — dynamic route](05-dynamic-route-catch-all-optional.md)
