# 10 — Fetch: loading, error, dan pola client

[← Custom Hook](09-custom-hook-pola.md) · [Daftar](README.md) · [Lanjut: portal dan Suspense →](11-portal-suspense-error-boundary.md)

Bab ini membahas pengambilan data **di browser** dengan `fetch` + `useEffect` + state status. Di Next.js App Router, daftar publik lebih cocok di Server Component. Pola client tetap perlu untuk filter hidup, tombol “muat lagi”, dan aksi POST.

## Daftar isi

- [Empat status](#empat-status)
- [GET dengan AbortController](#get-dengan-abortcontroller)
- [Race: respons lama](#race-respons-lama)
- [POST dari form](#post-dari-form)
- [Menonaktifkan tombol saat kirim](#menonaktifkan-tombol-saat-kirim)
- [Optimistic UI sederhana](#optimistic-ui-sederhana)
- [Polling](#polling)
- [Paginate dan muat lagi](#paginate-dan-muat-lagi)
- [JSON, teks, dan error HTTP](#json-teks-dan-error-http)
- [Header dan kredensial](#header-dan-kredensial)
- [Custom Hook useResource](#custom-hook-useresource)
- [Kapan tidak fetch di Effect](#kapan-tidak-fetch-di-effect)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Query string sebagai dependensi](#query-string-sebagai-dependensi)
- [File upload](#file-upload)
- [Membatalkan dari tombol](#membatalkan-dari-tombol)
- [Cache naif di modul (peringatan)](#cache-naif-di-modul-peringatan)

## Empat status

**Untuk apa:** tidak menampilkan daftar kosong saat data masih di jalan, atau diam saat server rusak.

```jsx
const STATUS = {
  idle: "idle",
  memuat: "memuat",
  sukses: "sukses",
  gagal: "gagal",
};
```

| Status | UI |
| --- | --- |
| `idle` | belum mulai (tunggu input) |
| `memuat` | skeleton / “Memuat…” |
| `sukses` | data, atau empty state jika array kosong |
| `gagal` | pesan + coba lagi |

`sukses` + array kosong ≠ `gagal`. `memuat` ≠ `idle`.

Boleh memakai beberapa boolean (`loading`, `error`) tetapi mudah mendapat kombinasi mustahil (`loading && error`). Satu enum lebih jujur.

**Biasanya digabungkan dengan:** early return, `role="status"`, `role="alert"`. Lihat [file 03](03-list-key-conditional.md).

## GET dengan AbortController

**Untuk apa:** membatalkan request saat komponen unmount atau parameter berubah.

```jsx
import { useEffect, useState } from "react";

export default function DaftarProduk() {
  const [produk, setProduk] = useState([]);
  const [status, setStatus] = useState("memuat");
  const [pesan, setPesan] = useState("");

  useEffect(() => {
    const kontrol = new AbortController();

    async function muat() {
      try {
        const response = await fetch("/api/produk", { signal: kontrol.signal });
        if (!response.ok) throw new Error("Gagal memuat");
        const data = await response.json();
        setProduk(data);
        setStatus("sukses");
      } catch (error) {
        if (error.name === "AbortError") return;
        setPesan("Data belum bisa dibuka.");
        setStatus("gagal");
      }
    }

    muat();
    return () => kontrol.abort();
  }, []);

  if (status === "memuat") return <p role="status">Memuat…</p>;
  if (status === "gagal") return <p role="alert">{pesan}</p>;
  if (produk.length === 0) return <p>Belum ada produk.</p>;

  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>{item.nama}</li>
      ))}
    </ul>
  );
}
```

`AbortError` bukan kegagalan pengguna: jangan menampilkan alert. Strict Mode development bisa memicu abort + fetch kedua.

**Biasanya digabungkan dengan:** dependensi `[id]`, custom Hook, dan backend Laravel/Next. [useEffect](https://react.dev/reference/react/useEffect).

## Race: respons lama

**Untuk apa:** mencegah produk #1 menimpa produk #2 jika jaringan tidak berurutan.

```jsx
useEffect(() => {
  const kontrol = new AbortController();
  setStatus("memuat");

  fetch(`/api/produk/${id}`, { signal: kontrol.signal })
    .then((res) => {
      if (!res.ok) throw new Error("Gagal");
      return res.json();
    })
    .then((data) => {
      setProduk(data);
      setStatus("sukses");
    })
    .catch((error) => {
      if (error.name === "AbortError") return;
      setStatus("gagal");
    });

  return () => kontrol.abort();
}, [id]);
```

Tanpa abort, skenario: buka id=1, cepat ganti id=2, respons 2 tiba dulu, lalu respons 1 tiba dan menimpa. Pengguna melihat barang salah.

Flag `let hidup = true` di cleanup juga mencegah `setState` setelah unmount, tetapi tidak membatalkan jaringan. Abort lebih lengkap.

**Biasanya digabungkan dengan:** route dinamis, tab detail, dan autocomplete.

## POST dari form

**Untuk apa:** mengirim data karena **aksi pengguna**, bukan karena komponen tampil.

```jsx
import { useState } from "react";

export default function FormKontak() {
  const [nama, setNama] = useState("");
  const [status, setStatus] = useState("idle");
  const [pesan, setPesan] = useState("");

  async function kirim(event) {
    event.preventDefault();
    setStatus("memuat");
    setPesan("");
    try {
      const response = await fetch("/api/kontak", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ nama }),
      });
      if (!response.ok) throw new Error("Gagal mengirim");
      setStatus("sukses");
      setPesan("Terkirim. Terima kasih.");
      setNama("");
    } catch {
      setStatus("gagal");
      setPesan("Belum terkirim. Coba lagi.");
    }
  }

  return (
    <form onSubmit={kirim}>
      <label htmlFor="nama">Nama</label>
      <input
        id="nama"
        value={nama}
        onChange={(e) => setNama(e.target.value)}
        required
      />
      <button type="submit" disabled={status === "memuat"}>
        {status === "memuat" ? "Mengirim…" : "Kirim"}
      </button>
      {pesan && <p role="status">{pesan}</p>}
    </form>
  );
}
```

Jangan menaruh POST di `useEffect` tanpa syarat: Effect bisa jalan dua kali di development dan mengirim dobel.

Jika komponen bisa unmount saat request, abaikan `setState` setelah abort atau pakai flag.

**Biasanya digabungkan dengan:** validasi, `preventDefault`, dan CSRF/token sesuai backend.

## Menonaktifkan tombol saat kirim

**Untuk apa:** mencegah klik ganda yang membuat dua pesanan.

```jsx
const [sedang, setSedang] = useState(false);

async function handleBeli() {
  if (sedang) return;
  setSedang(true);
  try {
    await fetch("/api/pesan", { method: "POST", body: JSON.stringify({ id }) });
  } finally {
    setSedang(false);
  }
}

<button type="button" onClick={handleBeli} disabled={sedang}>
  {sedang ? "Memproses…" : "Beli"}
</button>
```

`disabled` membantu, tetapi handler juga menjaga (aksesibilitas/keyboard bisa tetap memicu di beberapa kasus). `finally` memastikan tombol hidup lagi meski error.

Untuk pembayaran sungguhan, server harus idempotent (kunci request), bukan hanya UI.

**Biasanya digabungkan dengan:** `aria-busy`, spinner, dan pesan sukses.

## Optimistic UI sederhana

**Untuk apa:** memperbarui layar dulu, rollback jika server menolak.

```jsx
async function toggleSelesai(id) {
  const sebelumnya = tugas;
  setTugas((lama) =>
    lama.map((t) => (t.id === id ? { ...t, selesai: !t.selesai } : t))
  );
  try {
    const res = await fetch(`/api/tugas/${id}`, { method: "PATCH" });
    if (!res.ok) throw new Error("Gagal");
  } catch {
    setTugas(sebelumnya);
    setPesan("Perubahan dibatalkan.");
  }
}
```

Simpan snapshot sebelum ubah. Jika gagal, kembalikan. Jangan mengandalkan ini untuk uang tanpa konfirmasi server.

React 19 punya `useOptimistic` untuk pola serupa dengan transisi. Di React 18, snapshot + `setState` cukup untuk tugas.

**Biasanya digabungkan dengan:** `useTransition`, daftar todo, dan pesan error lembut.

## Polling

**Untuk apa:** menyegarkan data berkala (status pesanan), dengan berhenti saat tab tersembunyi atau unmount.

```jsx
useEffect(() => {
  let berhenti = false;

  async function tick() {
    if (document.hidden || berhenti) return;
    try {
      const res = await fetch("/api/status");
      if (!res.ok) return;
      const data = await res.json();
      if (!berhenti) setStatusData(data);
    } catch {
      // biarkan tick berikutnya
    }
  }

  tick();
  const id = setInterval(tick, 8000);
  return () => {
    berhenti = true;
    clearInterval(id);
  };
}, []);
```

Polling membebani server. Pertimbangkan jeda panjang, hentikan jika tab `hidden`, atau ganti WebSocket jika butuh realtime. Banyak tugas kuliah tidak perlu polling.

**Biasanya digabungkan dengan:** `useInterval`, banner offline, dan `document.visibilityState`.

## Paginate dan muat lagi

**Untuk apa:** menambah halaman tanpa membuang data lama.

```jsx
import { useEffect, useState } from "react";

export default function Katalog() {
  const [item, setItem] = useState([]);
  const [halaman, setHalaman] = useState(1);
  const [status, setStatus] = useState("memuat");
  const [habis, setHabis] = useState(false);

  useEffect(() => {
    const kontrol = new AbortController();
    setStatus("memuat");
    fetch(`/api/produk?halaman=${halaman}`, { signal: kontrol.signal })
      .then((res) => {
        if (!res.ok) throw new Error("Gagal");
        return res.json();
      })
      .then((data) => {
        setItem((lama) => (halaman === 1 ? data : [...lama, ...data]));
        setHabis(data.length === 0);
        setStatus("sukses");
      })
      .catch((e) => {
        if (e.name === "AbortError") return;
        setStatus("gagal");
      });
    return () => kontrol.abort();
  }, [halaman]);

  return (
    <>
      <ul>
        {item.map((x) => (
          <li key={x.id}>{x.nama}</li>
        ))}
      </ul>
      {status === "memuat" && <p>Memuat…</p>}
      {status === "gagal" && <p>Gagal memuat halaman.</p>}
      {!habis && status === "sukses" && (
        <button type="button" onClick={() => setHalaman((n) => n + 1)}>
          Muat lagi
        </button>
      )}
    </>
  );
}
```

Key item harus unik global, bukan unik per halaman. `halaman === 1` mengganti daftar (berguna jika nanti ada reset filter).

**Biasanya digabungkan dengan:** query string, `useMemo` tidak wajib, dan tombol di kaki daftar.

## JSON, teks, dan error HTTP

**Untuk apa:** tidak menganggap setiap respons adalah JSON sukses.

```jsx
async function bacaJson(response) {
  const teks = await response.text();
  const data = teks ? JSON.parse(teks) : null;
  if (!response.ok) {
    const pesan = data?.pesan || `HTTP ${response.status}`;
    throw new Error(pesan);
  }
  return data;
}
```

`response.ok` adalah status 200–299. `fetch` **tidak** throw pada 404/500; ia throw pada jaringan putus atau abort.

`response.json()` melempar jika body bukan JSON. Membaca `text()` dulu membantu menampilkan HTML error dari proxy.

Tipe lain: `response.blob()` untuk unduhan, `FormData` untuk multipart.

**Biasanya digabungkan dengan:** menampilkan `error.message` ke pengguna secara disaring (jangan bocorkan stack), dan log lengkap di console development.

## Header dan kredensial

**Untuk apa:** mengirim JSON dan cookie sesuai kebutuhan.

```jsx
fetch("/api/me", {
  method: "GET",
  headers: {
    Accept: "application/json",
  },
  credentials: "same-origin",
});

fetch("https://api.contoh.test/v1/item", {
  credentials: "include",
});
```

`Content-Type: application/json` dipakai saat ada body JSON. Untuk `FormData`, **jangan** set `Content-Type` manual: browser mengisi boundary.

Cookie lintas origin membutuhkan CORS dan `credentials: "include"`. Token di `Authorization` sering dipakai API Laravel Sanctum/Passport sesuai setup.

Jangan hardcode rahasia di frontend. Environment `VITE_*` / `NEXT_PUBLIC_*` terlihat ke klien.

**Biasanya digabungkan dengan:** backend [Laravel](../../laravel.md), CSRF header, dan Route Handler Next.js sebagai proxy.

## Custom Hook useResource

**Untuk apa:** satu Hook GET yang bisa dipakai ulang dengan `refresh`.

```jsx
import { useCallback, useEffect, useState } from "react";

export function useResource(url) {
  const [data, setData] = useState(null);
  const [status, setStatus] = useState("idle");
  const [error, setError] = useState(null);
  const [tik, setTik] = useState(0);

  const refresh = useCallback(() => setTik((n) => n + 1), []);

  useEffect(() => {
    if (!url) {
      setStatus("idle");
      setData(null);
      return undefined;
    }
    const kontrol = new AbortController();
    setStatus("memuat");
    setError(null);
    fetch(url, { signal: kontrol.signal })
      .then((res) => {
        if (!res.ok) throw new Error(`HTTP ${res.status}`);
        return res.json();
      })
      .then((json) => {
        setData(json);
        setStatus("sukses");
      })
      .catch((err) => {
        if (err.name === "AbortError") return;
        setError(err);
        setStatus("gagal");
      });
    return () => kontrol.abort();
  }, [url, tik]);

  return { data, status, error, refresh };
}
```

`refresh` menaikkan `tik` agar Effect jalan lagi dengan url yang sama. Tombol “Coba lagi” memanggil `refresh`.

**Biasanya digabungkan dengan:** empty/error UI, dan menonaktifkan refresh saat `status === "memuat"`.

## Kapan tidak fetch di Effect

**Untuk apa:** memilih tempat yang tepat.

- **Next.js Server Component:** `async function Page()` + `await fetch` untuk data awal publik.
- **Event:** POST, hapus, “suka”.
- **Library data:** jika proyek sudah memakai pola cache/revalidate.
- **Data statis kecil:** import JSON atau konstanta.

Effect + fetch adalah alat yang tepat untuk Client Component yang parameternya berubah di browser tanpa navigasi penuh.

Jangan fetch di tubuh komponen (saat render): itu side effect dan bisa loop.

**Biasanya digabungkan dengan:** [next-js.md](../../next-js.md) untuk server, dan file 04 untuk aturan Effect.

## Kesalahan umum bab ini

- **Tidak memeriksa `response.ok`.**
- **`useEffect` POST.**
- **Lupa abort / race id.**
- **Menampilkan `AbortError` sebagai kegagalan.**
- **`JSON.parse` tanpa jaga body kosong.**
- **Menyimpan token di `localStorage` lalu mengirim ke mana-mana.**
- **Infinite loop:** `setState` di Effect dengan dependensi object baru.
- **Menganggap array awal `[]` sebagai “tidak ada data” saat masih memuat.**
- **Dua sumber: fetch di Effect dan fetch di server tanpa kejelasan.**

Latihan: halaman detail `?id=` (atau prop `id`) dengan abort, empat status, tombol coba lagi, dan form komentar POST yang menonaktifkan submit.

## Query string sebagai dependensi

**Untuk apa:** men-fetch ulang saat filter di URL atau state pencarian berubah.

```jsx
const url = kata.trim()
  ? `/api/produk?q=${encodeURIComponent(kata.trim())}`
  : "/api/produk";

useEffect(() => {
  const kontrol = new AbortController();
  // fetch(url, { signal })
  return () => kontrol.abort();
}, [url]);
```

`encodeURIComponent` mencegah spasi/karakter rusak. Menyatukan parameter ke `url` membuat dependensi satu string, lebih mudah daripada `[kata, halaman, urutan]`.

Jangan membangun `url` di dalam Effect tanpa memasukkannya ke deps jika bagiannya berasal dari props/state.

**Biasanya digabungkan dengan:** debounce `kata`, dan Next.js `searchParams` jika filter harus bisa dibagikan.

## File upload

**Untuk apa:** mengirim `multipart/form-data` tanpa merusak boundary.

```jsx
async function unggah(file) {
  const body = new FormData();
  body.append("berkas", file);
  body.append("judul", "Sampul");
  const res = await fetch("/api/unggah", { method: "POST", body });
  if (!res.ok) throw new Error("Unggah gagal");
  return res.json();
}
```

Jangan set `Content-Type` manual. Input file: `ref` + `files[0]`, tidak controlled seperti teks. Tampilkan nama file dan status `mengunggah`.

**Biasanya digabungkan dengan:** [useRef file](05-useRef-useImperativeHandle-forwardRef.md), pratinjau `URL.createObjectURL`, dan `revokeObjectURL` saat selesai.

## Membatalkan dari tombol

**Untuk apa:** memberi pengguna kontrol, bukan hanya cleanup unmount.

```jsx
const kontrolRef = useRef(null);

function muat() {
  kontrolRef.current?.abort();
  const kontrol = new AbortController();
  kontrolRef.current = kontrol;
  fetch("/api/laporan", { signal: kontrol.signal });
}

function batal() {
  kontrolRef.current?.abort();
  setStatus("idle");
}
```

Request panjang (laporan, ekspor) pantas punya tombol Batal. `abort` memicu `AbortError`; jangan tampilkan sebagai kegagalan server.

**Biasanya digabungkan dengan:** `useRef`, status `memuat`, dan `disabled` pada tombol Muat.

## Cache naif di modul (peringatan)

**Untuk apa:** memahami batasan “simpan hasil fetch di variabel modul”.

```jsx
const cache = new Map();

export async function ambilProduk(id) {
  if (cache.has(id)) return cache.get(id);
  const p = fetch(`/api/produk/${id}`).then((r) => r.json());
  cache.set(id, p);
  return p;
}
```

Cache modul bertahan selama tab hidup, tidak tahu kapan stale, tidak ter-scope user, dan bisa membagikan Promise gagal. Cukup untuk demo. Aplikasi sungguhan: library data atau cache server.

**Biasanya digabungkan dengan:** kesadaran stale, tombol refresh yang menghapus `cache.delete(id)`, dan [file 09 `useFetch`](09-custom-hook-pola.md).
