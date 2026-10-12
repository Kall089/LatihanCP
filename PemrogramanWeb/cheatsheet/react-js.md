# Cheatsheet React.js

[← Daftar panduan](README.md) · [Lanjut Next.js →](next-js.md)

React adalah library untuk membuat **antarmuka dari komponen**. Kamu menjelaskan tampilan berdasarkan data saat ini; React memperbarui DOM ketika data state berubah.

## Daftar isi

- [Persiapan](#persiapan)
- [Komponen dan JSX](#komponen-dan-jsx)
- [Props dan children](#props-dan-children)
- [State dan event](#state-dan-event)
- [Kondisi dan daftar](#kondisi-dan-daftar)
- [Form controlled](#form-controlled)
- [Update array dan object](#update-array-dan-object)
- [Effect dan cleanup](#effect-dan-cleanup)
- [Fetch di Client Component](#fetch-di-client-component)
- [Custom Hook](#custom-hook)
- [Ref](#ref)
- [Berbagi state](#berbagi-state)
- [Resep pencarian produk](#resep-pencarian-produk)
- [Context](#context)
- [useReducer](#usereducer)
- [useMemo dan useCallback](#usememo-dan-usecallback)
- [Kesalahan umum](#kesalahan-umum)

## Persiapan

**Untuk apa:** membuat proyek latihan React dengan Vite. Siapkan Node.js yang memenuhi persyaratan Vite dan npm; [panduan instalasi Vite](https://vite.dev/guide/) memuat persyaratan versi.

Jalankan di folder tempat kamu menyimpan proyek latihan:

```bash
npm create vite@latest latihan-react -- --template react
cd latihan-react
npm install
npm run dev
```

Buka URL yang ditampilkan terminal. Ganti isi `src/App.jsx` dengan **satu** contoh `export default` di bawah. CSS dapat ditulis di `src/App.css`, lalu diimpor melalui `import "./App.css";` dalam `App.jsx`. Hapus gaya demo bawaan bila mengganggu latihan.

**Biasanya digabungkan dengan:** CSS/CSS Modules, backend API, dan Next.js jika membutuhkan kerangka routing serta rendering server. JSX perlu diproses oleh tool proyek; file JSX tidak cukup dibuka langsung di browser.

## Komponen dan JSX

**Untuk apa:** memecah halaman menjadi bagian yang bisa dipakai kembali.

```jsx
function Sapaan() {
  const nama = "Haikal";
  return <h1 className="judul">Halo, {nama}!</h1>;
}

export default function App() {
  return (
    <main>
      <Sapaan />
      <p>Selamat belajar React.</p>
    </main>
  );
}
```

Nama komponen diawali huruf besar. `{...}` menyisipkan ekspresi JavaScript ke JSX. Gunakan `className` untuk class CSS dan `htmlFor` untuk label input. Tag harus ditutup, misalnya `<input />`. Jika tidak perlu elemen pembungkus, gunakan Fragment `<>...</>`.

**Biasanya digabungkan dengan:** props, CSS, dan komponen lain untuk menyusun halaman. [Dasar JSX dan komponen](https://react.dev/learn).

## Props dan children

**Untuk apa:** mengirim data dari komponen induk ke anak.

```jsx
function Kartu({ judul, children }) {
  return (
    <section className="kartu">
      <h2>{judul}</h2>
      {children}
    </section>
  );
}

export default function App() {
  return (
    <Kartu judul="Buku JavaScript">
      <p>Harga: Rp45.000</p>
      <button type="button">Lihat stok</button>
    </Kartu>
  );
}
```

`judul` adalah prop; `children` adalah isi di antara tag pembuka/penutup `Kartu`. Tombol pada contoh ini baru tampilan, belum memiliki handler. Props dibaca oleh anak; perubahan data dikelola pemilik state.

**Biasanya digabungkan dengan:** komponen kartu, modal, layout, dan callback agar anak dapat meminta induk melakukan perubahan.

## State dan event

**Untuk apa:** menyimpan data yang memengaruhi tampilan dan berubah selama interaksi.

```jsx
import { useState } from "react";

export default function App() {
  const [jumlah, setJumlah] = useState(0);

  return (
    <div>
      <p aria-live="polite">Jumlah: {jumlah}</p>
      <button type="button" onClick={() => setJumlah((lama) => lama + 1)}>
        Tambah
      </button>
      <button type="button" onClick={() => setJumlah(0)}>Reset</button>
    </div>
  );
}
```

`jumlah` adalah nilai untuk render saat ini; `setJumlah` meminta pembaruan render berikutnya. Bentuk fungsi `(lama) => lama + 1` tepat saat nilai baru bergantung pada nilai sebelumnya. `onClick` menerima fungsi, bukan hasil menjalankan fungsi.

**Biasanya digabungkan dengan:** counter, menu terbuka/tertutup, input, filter, dan indikator loading.

## Kondisi dan daftar

**Untuk apa:** memilih tampilan dan menghasilkan banyak elemen dari array.

```jsx
const produk = [
  { id: 1, nama: "Buku", stok: 3 },
  { id: 2, nama: "Pensil", stok: 0 },
];

export default function App() {
  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>
          {item.nama} — {item.stok > 0 ? "Tersedia" : "Habis"}
          {item.stok === 0 && <span> (Pesan lagi nanti)</span>}
        </li>
      ))}
    </ul>
  );
}
```

`key` membantu React mengenali item antarrender. Pilih ID stabil dari data, bukan nilai acak. Indeks array berisiko jika item diurutkan, disisipkan, atau dihapus. Gunakan `jumlah > 0 && ...`, karena `jumlah && ...` dapat menampilkan angka `0`.

**Biasanya digabungkan dengan:** `map`, `filter`, respons API, dan komponen kartu.

## Form controlled

**Untuk apa:** membuat state React menjadi sumber nilai input.

```jsx
import { useState } from "react";

export default function App() {
  const [nama, setNama] = useState("");
  const [pesan, setPesan] = useState("");

  function kirim(event) {
    event.preventDefault();
    setPesan(nama.trim() ? `Halo, ${nama.trim()}!` : "Nama perlu diisi.");
  }

  return (
    <form onSubmit={kirim}>
      <label htmlFor="nama">Nama</label>
      <input
        id="nama"
        value={nama}
        onChange={(event) => setNama(event.target.value)}
        required
      />
      <button type="submit">Sapa</button>
      <p role="status">{pesan}</p>
    </form>
  );
}
```

`value` menampilkan state; `onChange` memperbaruinya. Untuk checkbox gunakan pasangan `checked` dan `event.target.checked`. Untuk input angka, nilai dari `event.target.value` tetap string sehingga perlu dikonversi saat dihitung/dikirim.

**Biasanya digabungkan dengan:** pencarian, validasi, dan `fetch` untuk mengirim formulir ke backend.

## Update array dan object

**Untuk apa:** memperbarui data state tanpa memutasi nilai yang sedang dipakai React.

Potongan berikut diletakkan di dalam komponen; hubungkan fungsinya ke tombol/form sesuai kebutuhan:

```jsx
const [produk, setProduk] = useState([{ id: 1, nama: "Buku", stok: 3 }]);
const [profil, setProfil] = useState({ nama: "Haikal", kota: "Bandung" });

function tambah(itemBaru) {
  setProduk((lama) => [...lama, itemBaru]);
}

function hapus(id) {
  setProduk((lama) => lama.filter((item) => item.id !== id));
}

function ubahStok(id, stok) {
  setProduk((lama) => lama.map((item) =>
    item.id === id ? { ...item, stok } : item
  ));
}

function pindahKota() {
  setProfil((lama) => ({ ...lama, kota: "Jakarta" }));
}
```

Tambahkan `import { useState } from "react";` di bagian atas file. Hindari `produk.push(...)` atau `profil.kota = ...` langsung pada state. Salin juga tingkat object bersarang yang hendak diubah.

**Biasanya digabungkan dengan:** CRUD di antarmuka, daftar tugas, dan keranjang belanja. Update state lokal belum menyimpan perubahan ke database.

## Effect dan cleanup

**Untuk apa:** menyinkronkan komponen dengan sistem di luar React, seperti timer atau event browser.

```jsx
import { useEffect, useState } from "react";

export default function App() {
  const [detik, setDetik] = useState(0);

  useEffect(() => {
    const timer = setInterval(() => {
      setDetik((lama) => lama + 1);
    }, 1000);

    return () => clearInterval(timer);
  }, []);

  return <p>Sudah berjalan {detik} detik.</p>;
}
```

Cleanup menghentikan timer saat Effect dibersihkan. `[]` berarti Effect tidak bergantung pada nilai reaktif komponen; `[id]` berarti sinkronisasi diulang ketika `id` berubah. Sertakan semua dependensi reaktif yang dibaca Effect. Strict Mode dapat menjalankan siklus setup–cleanup tambahan saat development. [Rujukan Effect](https://react.dev/reference/react/useEffect).

Untuk hasil yang bisa dihitung langsung, cukup hitung saat render, misalnya `const total = harga * jumlah`; tidak perlu Effect untuk menyalin hasil ke state baru.

**Biasanya digabungkan dengan:** subscription, timer, atau fetch di sisi client. Jika fetch dilakukan dalam Effect, gunakan cleanup/AbortController atau mekanisme lain untuk mencegah respons lama menimpa data baru.

## Fetch di Client Component

**Untuk apa:** mengambil data setelah komponen tampil di browser, lengkap dengan status loading dan error.

```jsx
import { useEffect, useState } from "react";

export default function DaftarProduk() {
  const [produk, setProduk] = useState([]);
  const [status, setStatus] = useState("memuat");

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
        setStatus("gagal");
      }
    }

    muat();
    return () => kontrol.abort();
  }, []);

  if (status === "memuat") return <p role="status">Memuat...</p>;
  if (status === "gagal") return <p>Data belum bisa dibuka.</p>;
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

Empat tampilan: memuat, gagal, kosong, sukses. `AbortController` membatalkan fetch jika pengguna pindah halaman sebelum selesai.

Di Next.js App Router, fetch daftar publik lebih cocok di Server Component. Pola ini tetap penting untuk tombol “muat lagi” atau filter yang berubah-ubah di client.

**Biasanya digabungkan dengan:** endpoint Laravel/Next, `useState`, dan CSS untuk skeleton/loading.

## Custom Hook

**Untuk apa:** memindahkan logika state yang dipakai lebih dari satu komponen.

```jsx
import { useState } from "react";

export function useToggle(awal = false) {
  const [nyala, setNyala] = useState(awal);
  function toggle() {
    setNyala((lama) => !lama);
  }
  return [nyala, toggle];
}
```

Nama harus diawali `use`. Di dalam Hook, aturan Hooks tetap berlaku.

```jsx
import { useToggle } from "./useToggle";

export default function App() {
  const [terbuka, toggle] = useToggle();
  return (
    <button type="button" onClick={toggle}>
      {terbuka ? "Tutup menu" : "Buka menu"}
    </button>
  );
}
```

**Biasanya digabungkan dengan:** menu, tema, dan fetch yang diulang di banyak halaman.

## Ref

**Untuk apa:** menyimpan referensi yang tidak membutuhkan render ulang, misalnya elemen input yang ingin difokuskan.

```jsx
import { useRef } from "react";

export default function App() {
  const inputRef = useRef(null);

  return (
    <>
      <label htmlFor="cari">Cari produk</label>
      <input id="cari" ref={inputRef} />
      <button type="button" onClick={() => inputRef.current?.focus()}>
        Fokus pencarian
      </button>
    </>
  );
}
```

Mengubah `.current` tidak meminta render ulang. Gunakan state untuk data yang harus terlihat di layar.

**Biasanya digabungkan dengan:** fokus formulir, kontrol video, dan integrasi library DOM.

## Berbagi state

**Untuk apa:** membuat dua komponen membaca data yang sama.

Mulai dengan menyimpan state pada induk bersama, lalu kirim nilai dan callback lewat props:

```jsx
import { useState } from "react";

function TombolTambah({ onTambah }) {
  return <button type="button" onClick={onTambah}>Tambah barang</button>;
}

export default function App() {
  const [jumlah, setJumlah] = useState(0);
  return (
    <>
      <p>Keranjang: {jumlah}</p>
      <TombolTambah onTambah={() => setJumlah((lama) => lama + 1)} />
    </>
  );
}
```

Jika data dibutuhkan banyak komponen yang berjauhan, Context dapat mengurangi pengoperan props berantai. Tetap tempatkan state sedekat mungkin dengan pemakainya.

**Biasanya digabungkan dengan:** keranjang, tema, dan informasi pengguna. Context membagikan nilai; state tetap perlu dikelola dengan `useState`, `useReducer`, atau mekanisme lain.

## Resep pencarian produk

Gabungan **state + controlled input + filter + map + props**. Ganti `src/App.jsx` dengan contoh utuh ini:

```jsx
import { useState } from "react";

const daftarProduk = [
  { id: 1, nama: "Buku JavaScript", harga: 45000 },
  { id: 2, nama: "Buku CSS", harga: 40000 },
  { id: 3, nama: "Tas Kuliah", harga: 90000 },
];

function KartuProduk({ produk }) {
  return (
    <li>
      <h2>{produk.nama}</h2>
      <p>Rp{produk.harga.toLocaleString("id-ID")}</p>
    </li>
  );
}

export default function App() {
  const [kataKunci, setKataKunci] = useState("");
  const hasil = daftarProduk.filter((produk) =>
    produk.nama.toLowerCase().includes(kataKunci.trim().toLowerCase())
  );

  return (
    <main>
      <h1>Katalog produk</h1>
      <label htmlFor="cari">Cari nama produk</label>
      <input
        id="cari"
        value={kataKunci}
        onChange={(event) => setKataKunci(event.target.value)}
      />
      <p role="status">{hasil.length} produk ditemukan.</p>
      {hasil.length === 0 ? (
        <p>Coba kata kunci lain.</p>
      ) : (
        <ul>{hasil.map((produk) => <KartuProduk key={produk.id} produk={produk} />)}</ul>
      )}
    </main>
  );
}
```

Saat input berubah, React merender ulang, menghitung `hasil` baru, lalu memperbarui daftar. `hasil` tidak perlu state terpisah karena dapat dihitung dari `kataKunci` dan data produk.

## Context

**Untuk apa:** berbagi nilai ke banyak komponen tanpa mengoper props berantai (tema, user yang login).

`src/TemaContext.jsx`:

```jsx
import { createContext, useContext, useState } from "react";

const TemaContext = createContext(null);

export function TemaProvider({ children }) {
  const [tema, setTema] = useState("terang");
  return (
    <TemaContext.Provider value={{ tema, setTema }}>
      {children}
    </TemaContext.Provider>
  );
}

export function useTema() {
  const nilai = useContext(TemaContext);
  if (!nilai) throw new Error("useTema harus di dalam TemaProvider");
  return nilai;
}
```

Bungkus `App` dengan `<TemaProvider>`, lalu di anak jauh:

```jsx
const { tema, setTema } = useTema();
```

Jangan masukkan ke Context data yang hanya dipakai 2 komponen berdekatan; props lebih jelas.

**Biasanya digabungkan dengan:** tema, keranjang global, dan custom hook.

## useReducer

**Untuk apa:** state yang punya beberapa aksi terkait, misalnya keranjang.

```jsx
import { useReducer } from "react";

function reducer(state, action) {
  switch (action.type) {
    case "tambah":
      return { ...state, jumlah: state.jumlah + 1 };
    case "reset":
      return { ...state, jumlah: 0 };
    default:
      return state;
  }
}

export default function App() {
  const [state, dispatch] = useReducer(reducer, { jumlah: 0 });
  return (
    <>
      <p>{state.jumlah}</p>
      <button type="button" onClick={() => dispatch({ type: "tambah" })}>+</button>
      <button type="button" onClick={() => dispatch({ type: "reset" })}>Reset</button>
    </>
  );
}
```

`useState` tetap cukup untuk satu nilai. Pindah ke reducer jika `setX` sudah saling terkait dan sulit dibaca.

**Biasanya digabungkan dengan:** Context (nilai + dispatch), dan form bertahap.

## useMemo dan useCallback

**Untuk apa:** mengingat hasil hitung atau fungsi, **hanya jika** ada alasan (list besar, anak yang di-memo).

```jsx
import { useMemo, useCallback } from "react";

const hasil = useMemo(
  () => daftar.filter((item) => item.nama.includes(kata)),
  [daftar, kata]
);

const onHapus = useCallback((id) => {
  setDaftar((lama) => lama.filter((item) => item.id !== id));
}, []);
```

Jangan membungkus semua hitungan. Filter 10 produk tidak butuh `useMemo`.

**Biasanya digabungkan dengan:** daftar panjang dan komponen anak yang `React.memo`.

## Kesalahan umum

- **Hooks dipanggil di dalam `if`/loop:** panggil di tingkat atas komponen atau custom Hook.
- **Tombol langsung berjalan saat render:** tulis `onClick={fungsi}` atau `onClick={() => fungsi(id)}`.
- **Input tidak bisa diketik:** `value` diberikan tetapi `onChange` tidak memperbarui state.
- **Infinite render:** setter dipanggil tanpa syarat saat render, atau Effect terus memperbarui dependensinya sendiri.
- **JSX tidak tampil:** pastikan fungsi komponen mengembalikan JSX, bukan hanya membuatnya.

Latihan: tambahkan tombol “Harga termurah” pada katalog dengan menyalin array sebelum `.sort()`.
