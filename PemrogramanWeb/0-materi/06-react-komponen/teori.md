# Modul 06 — React: Komponen, Props, State

> Praktikum terkait: [`../../1-pembelajaran/06-react-komponen/`](../../1-pembelajaran/06-react-komponen/)
> (3 bab: dashboard komponen, form controlled, filter daftar).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menjelaskan komponen sebagai fungsi yang mengembalikan UI, dan menyusunnya
  jadi pohon.
- Menulis JSX yang valid (`className`, satu induk, ekspresi di `{}`).
- Mengalirkan data lewat **props** (turun) dan **callback** (naik).
- Memakai `useState` dengan benar: tidak mutasi, selalu salinan baru.
- Merender list dengan `map` + `key`, form terkontrol, dan filter turunan.

**Prasyarat**: Modul 05. React **mengotomatiskan** pola state → render yang
kamu tulis manual di counter dan daftar dinamis. Kalau pola itu belum
nyaman, ulangi praktikum 05 dulu.

React di praktikum ini dijalankan lewat **Next.js** (Modul 07). Salin folder
`starter/` ke proyek yang sudah `create-next-app`.

---

## 1. Mengapa tidak terus memanipulasi DOM?

Di Modul 05 kamu sendiri yang:

1. Menyimpan data di variabel.
2. Menulis `render()` yang mengosongkan `<ul>` lalu mengisinya lagi.
3. Mengingat untuk memanggil `render()` setiap kali data berubah.

Lupa satu langkah = bug. React mengambil alih langkah 2–3: kamu hanya
mengubah *state*, React menghitung UI baru dan menambal DOM.

Rumus yang sama:

```text
          UI = f(state)
```

Bedanya: `f` adalah fungsi komponenmu, dan React yang memanggilnya ulang.

React adalah **library UI**, bukan framework utuh. Routing, folder, server —
itu Next.js (Modul 07). Di sini kita fokus: komponen, props, state.

---

## 2. Komponen = fungsi yang mengembalikan UI

```text
                    <App />
                   ╱   │   ╲
          <Header/> <Dashboard/> <Footer/>
                    ╱         ╲
            <StatCard          <StatCard
              judul="Sesi"       judul="Nilai"
              nilai={12} />      nilai={88} />
```

Setiap kotak adalah **satu fungsi**. Nama komponen **wajib huruf besar** —
`<StatCard />` adalah komponen; `<statCard />` dianggap tag HTML tak dikenal.

Satu komponen = satu tanggung jawab. Kartu statistik tidak mengurus navbar.

```jsx
function StatCard({ judul, nilai, satuan }) {
  return (
    <article className="kartu">
      <h2>{judul}</h2>
      <p>
        {nilai} <span>{satuan}</span>
      </p>
    </article>
  );
}

function Dashboard() {
  return (
    <main>
      <StatCard judul="Sesi Belajar" nilai={12} satuan="sesi" />
      <StatCard judul="Rata-rata" nilai={88} satuan="poin" />
    </main>
  );
}
```

Dua `<StatCard>` = **satu definisi, dua pemakaian** dengan props berbeda.
Ubah markup kartu sekali, semua pemakaian ikut.

Praktikum `01-dashboard-komponen` meminta kamu memecah halaman jadi
`CourseCard` dan `StudyCounter` persis karena ini.

---

## 3. JSX — HTML yang sebenarnya JavaScript

JSX ditranspilasi menjadi panggilan `React.createElement`. Karena itu ia
mengikuti aturan JS, bukan HTML murni.

| HTML | JSX | Mengapa |
|---|---|---|
| `class` | `className` | `class` kata kunci JS |
| `for` | `htmlFor` | `for` kata kunci loop |
| `<img>` | `<img />` | semua tag harus tertutup |
| teks saja | `{variabel}` | kurung kurawal = ekspresi JS |

Aturan lain:

1. **Satu elemen induk** per `return`. Bungkus dengan `<div>` atau fragment
   `<>...</>`.
2. Komentar: `{/* seperti ini */}`.
3. `style` adalah objek: `style={{ color: "red" }}` — kurung ganda: JSX `{}`
   + objek JS `{}`.
4. Boolean: `<input disabled />` sama dengan `disabled={true}`.

```jsx
// SALAH: dua elemen sejajar tanpa induk
return (
  <h1>Judul</h1>
  <p>Isi</p>
);

// BENAR
return (
  <>
    <h1>Judul</h1>
    <p>Isi</p>
  </>
);
```

---

## 4. Props — data dari induk ke anak

Props adalah **parameter fungsi**. Induk mengirim, anak menerima. Anak
**tidak boleh mengubah props** (read-only). Butuh mengubah? Minta induk lewat
callback (bagian 7).

```jsx
// string: kutip biasa
<Kartu judul="Kopi Susu" />

// angka, boolean, objek, fungsi: kurung kurawal
<Kartu nilai={12} aktif={true} onHapus={handleHapus} />
```

### `children`

Isi di antara tag pembuka/penutup masuk sebagai `props.children`:

```jsx
function Kartu({ judul, children }) {
  return (
    <div className="kartu">
      <h2>{judul}</h2>
      {children}
    </div>
  );
}

<Kartu judul="Pengumuman">
  <p>Praktikum dikumpulkan Jumat.</p>
</Kartu>
```

Destructuring di parameter (`{ judul, nilai }`) lebih ringkas daripada
`props.judul` berulang.

---

## 5. State — data yang berubah di dalam komponen

```jsx
import { useState } from "react";

function Counter() {
  const [jumlah, setJumlah] = useState(0);

  return (
    <div>
      <p>Sesi: {jumlah}</p>
      <button onClick={() => setJumlah(jumlah + 1)}>Tambah</button>
      <button onClick={() => setJumlah(0)}>Reset</button>
    </div>
  );
}
```

Anatomi:

```text
const [nilai, setNilai] = useState(nilaiAwal);
         │        │                 └── render pertama
         │        └── fungsi: "ganti nilai DAN render ulang"
         └── snapshot state saat render ini
```

Aturan yang paling sering dilanggar:

| Dilarang | Wajib |
|---|---|
| `jumlah++` / `jumlah += 1` | `setJumlah(jumlah + 1)` |
| `arr.push(x)` | `setArr([...arr, x])` |
| `obj.nama = "x"` | `setObj({ ...obj, nama: "x" })` |
| `items[i].done = true` | `setItems(items.map(...salinan item...))` |

Mutasi langsung **tidak memicu render** — React membandingkan referensi baru
vs lama. Array/objek yang sama di memori = "tidak ada yang berubah".

### Hook hanya di level atas

`useState` (dan hook lain) **tidak** boleh di dalam `if`, loop, atau fungsi
bersarang. Urutan panggilan hook harus identik setiap render.

```jsx
// SALAH
if (siap) {
  const [x, setX] = useState(0);
}

// BENAR
const [x, setX] = useState(0);
if (!siap) return null;
```

---

## 6. Event di React dan form terkontrol

Nama event: camelCase. Berikan **fungsi**, bukan hasil panggilan.

```jsx
<button onClick={handleClick}>        {/* referensi — BENAR */}
<button onClick={() => hapus(id)}>    {/* bungkus kalau perlu argumen */}
<button onClick={handleClick()}>      {/* LANGSUNG JALAN saat render — SALAH */}
```

`handleClick()` dengan `()` memanggil fungsi *sekarang*, saat komponen
dirender, bukan saat diklik.

### Controlled input

Nilai input dikendalikan state — satu sumber kebenaran. Pola:

```jsx
function FormPendaftaran() {
  const [nama, setNama] = useState("");
  const [error, setError] = useState("");

  function handleSubmit(e) {
    e.preventDefault();
    if (nama.trim() === "") {
      setError("Nama wajib diisi");
      return;
    }
    setError("");
    // ... kirim data
  }

  return (
    <form onSubmit={handleSubmit}>
      <input
        value={nama}
        onChange={(e) => setNama(e.target.value)}
      />
      {error && <p role="alert">{error}</p>}
      <button type="submit">Daftar</button>
    </form>
  );
}
```

Tanpa `value={nama}`, input "liar" (uncontrolled) — React tidak tahu isinya
sampai submit. Controlled memudahkan validasi *live* dan menonaktifkan tombol
saat kosong.

Ini isi praktikum `02-form-controlled`.

### Conditional rendering

```jsx
{error && <p>{error}</p>}
{aktif ? <PanelA /> : <PanelB />}
{daftar.length === 0 ? <p>Belum ada data.</p> : <ul>...</ul>}
```

`&&` menampilkan kanan hanya jika kiri *truthy*. Hati-hati `{count && <p>}`
jika `count` bisa `0` — nol bersifat falsy, jadi paragraf hilang. Lebih aman
`{count > 0 && ...}` atau ternary.

---

## 7. List, key, dan aliran data satu arah

```jsx
function DaftarProduk({ items }) {
  return (
    <ul>
      {items.map((p) => (
        <li key={p.id}>
          {p.nama} — Rp{p.harga.toLocaleString("id-ID")}
        </li>
      ))}
    </ul>
  );
}
```

`key` harus **unik dan stabil** (id dari data), bukan index array. React
memakai key untuk mencocokkan item lama vs baru. Index sebagai key rusak saat
urut berubah atau item dihapus di tengah: state input di baris 2 "nyangkut"
ke item yang salah.

Filter sebelum map (derived state — tidak perlu `useState` kedua):

```jsx
{items
  .filter((p) => p.harga <= budget)
  .map((p) => (
    <li key={p.id}>{p.nama}</li>
  ))}
```

Praktikum `03-filter-daftar` adalah ini: query di state, daftar tampil =
`filter` dari data.

### Data down, events up

```text
            state: [query, setQuery]
                 ┌──────────┐
                 │  <App/>  │
                 └──────────┘
        props ↓ query     ↑ onChange(q)
     ┌──────────────┐  ┌───────────────┐
     │ <DaftarItem  │  │ <SearchBox    │
     │   query={q}/>│  │  onChange={f}/>│
     └──────────────┘  └───────────────┘

  1. User mengetik di SearchBox
  2. SearchBox memanggil props.onChange(teks)
  3. App setQuery(teks) → state berubah
  4. React render ulang → DaftarItem menerima query baru
```

Kalau dua anak perlu data yang sama, **naikkan state** ke induk terdekat
(*lifting state up*). Anak yang butuh mengubah mengirim fungsi.

Props turun. Kejadian naik. Hafalkan kalimat itu untuk ujian.

---

## 8. Hook lain (intuisi, belum semua dipraktikkan)

| Hook | Kegunaan | Contoh |
|---|---|---|
| `useState` | Data lokal yang berubah | `const [x, setX] = useState(0)` |
| `useEffect` | Efek samping (fetch, timer, subscribe) | `useEffect(() => {...}, [dep])` |
| `useRef` | Referensi DOM / nilai yang persist tanpa render | `const inputRef = useRef(null)` |
| `useContext` | Data global tanpa props drilling dalam-dalam | `useContext(TemaContext)` |
| `useMemo` | Cache perhitungan berat | `useMemo(() => hitung(), [data])` |

Untuk praktikum 06, **`useState` cukup**. `useEffect` muncul kalau kamu fetch
API; di proyek kuliah data masih array lokal (Modul 08).

Array dependensi `useEffect`: `[]` = sekali setelah mount; `[query]` = setiap
`query` berubah; tanpa array = setiap render (hampir selalu salah).

---

## 9. Kesalahan umum

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | Mutasi state (`push`, `++`) | Tidak re-render / bug aneh | `setX` + salinan `[...arr]` |
| 2 | `onClick={fn()}` | Fungsi jalan saat render | `onClick={fn}` atau `() => fn(x)` |
| 3 | `key={index}` | Item salah pasang saat urut berubah | `key={item.id}` |
| 4 | Hook di dalam `if`/loop | Error Rules of Hooks | Panggil di level atas |
| 5 | `class=` di JSX | Peringatan, class tidak terpasang | `className` |
| 6 | Anak mengubah props | Anti-pola, data kacau | Callback ke parent |
| 7 | Dua sumber kebenaran input | Tampilan ≠ data | Controlled: `value` + `onChange` |
| 8 | Komponen huruf kecil | Diperlakukan sebagai HTML | `function Kartu` bukan `kartu` |

---

## 10. Cheatsheet

```jsx
// Komponen + props
function Kartu({ judul, children }) {
  return (
    <div className="kartu">
      <h2>{judul}</h2>
      {children}
    </div>
  );
}

// State
const [x, setX] = useState(0);
setX(x + 1);
setArr([...arr, baru]);
setObj({ ...obj, nama: "Sinta" });

// Event
<button onClick={handleClick} />
<input value={v} onChange={(e) => setV(e.target.value)} />
<form onSubmit={(e) => { e.preventDefault(); /* ... */ }}>

// List & kondisi
{items.map((i) => <li key={i.id}>{i.nama}</li>)}
{error && <p>{error}</p>}
{on ? <A /> : <B />}

// JSX
className  htmlFor  <img />  <>...</>  {ekspresi}
```

## Lanjut ke praktikum

Salin `starter/` ke proyek Next/React, lalu kerjakan di
[`../../1-pembelajaran/06-react-komponen/`](../../1-pembelajaran/06-react-komponen/):

1. `01-dashboard-komponen` — pecah UI, props, counter state (bagian 2, 4, 5).
2. `02-form-controlled` — `value`/`onChange`/`onSubmit` (bagian 6).
3. `03-filter-daftar` — derived list, lifting state (bagian 7).

Uji diri: [`../../3-latihan-soal/06-react-komponen/soal.md`](../../3-latihan-soal/06-react-komponen/soal.md).
Lanjut kerangka produksi di Modul 07.
