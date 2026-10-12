# 03 — Daftar, key, dan render bersyarat

[← State dan form](02-state-event-form.md) · [Daftar](README.md) · [Lanjut: Effect →](04-useEffect-useLayoutEffect-useInsertionEffect.md)

Daftar di React hampir selalu lahir dari `array.map` yang mengembalikan elemen. `key` membantu React mengenali item antarrender. Render bersyarat memilih cabang tampilan: memuat, kosong, error, atau isi.

## Daftar isi

- [map menghasilkan elemen](#map-menghasilkan-elemen)
- [key yang stabil](#key-yang-stabil)
- [Mengapa indeks berbahaya](#mengapa-indeks-berbahaya)
- [filter lalu map](#filter-lalu-map)
- [Daftar bersarang](#daftar-bersarang)
- [Early return](#early-return)
- [Ternary](#ternary)
- [Operator &&](#operator-)
- [Variabel elemen](#variabel-elemen)
- [Lookup object menggantikan switch](#lookup-object-menggantikan-switch)
- [Empat tampilan daftar](#empat-tampilan-daftar)
- [Menghapus dan menyisip tanpa merusak key](#menghapus-dan-menyisip-tanpa-merusak-key)
- [key pada komponen vs elemen DOM](#key-pada-komponen-vs-elemen-dom)
- [key untuk mereset state](#key-untuk-mereset-state)
- [Fragment bertingkat di daftar](#fragment-bertingkat-di-daftar)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Set dan Map sebagai sumber daftar](#set-dan-map-sebagai-sumber-daftar)
- [Render nothing dengan null](#render-nothing-dengan-null)
- [Daftar kosong vs null data](#daftar-kosong-vs-null-data)

## map menghasilkan elemen

**Untuk apa:** menampilkan satu elemen per item data.

```jsx
const produk = [
  { id: 1, nama: "Buku JavaScript", harga: 45000 },
  { id: 2, nama: "Buku CSS", harga: 40000 },
];

export default function App() {
  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>
          {item.nama} — Rp{item.harga.toLocaleString("id-ID")}
        </li>
      ))}
    </ul>
  );
}
```

`map` mengembalikan array elemen. React tahu cara merender array itu. Jangan memakai `for` di dalam JSX; hitung array di tubuh fungsi atau langsung di `{...}`.

Komponen terpisah lebih rapi jika item punya markup panjang:

```jsx
function BarisProduk({ item }) {
  return (
    <li>
      <strong>{item.nama}</strong>
      <span>Rp{item.harga.toLocaleString("id-ID")}</span>
    </li>
  );
}

export default function App() {
  return (
    <ul>
      {produk.map((item) => (
        <BarisProduk key={item.id} item={item} />
      ))}
    </ul>
  );
}
```

`key` diletakkan pada elemen **paling luar yang dihasilkan `map`**, yaitu `<BarisProduk />`, bukan di dalam `BarisProduk`.

**Biasanya digabungkan dengan:** `key`, `filter`, props item, dan state daftar. [Rendering lists](https://react.dev/learn/rendering-lists).

## key yang stabil

**Untuk apa:** memberi identitas item agar React bisa menambah, menghapus, dan menggeser tanpa mengacak state anak.

```jsx
{tugas.map((item) => (
  <li key={item.id}>{item.judul}</li>
))}
```

Syarat key yang baik:

- unik di antara saudara (bukan unik di seluruh aplikasi)
- stabil: tidak berubah setiap render
- berasal dari data: `id` database, SKU, slug

Key **bukan** prop. Komponen anak tidak menerima `props.key`. Jika anak butuh id, kirim `id={item.id}` terpisah.

Jangan memakai `Math.random()` atau `crypto.randomUUID()` di dalam `map` tanpa menyimpannya di data. Key baru setiap render membuat React merobohkan dan membangun ulang semua item: input kehilangan isi, animasi ulang, request ulang.

**Biasanya digabungkan dengan:** id dari API, `useState` daftar, dan komponen item yang punya state sendiri (checkbox, input).

## Mengapa indeks berbahaya

**Untuk apa:** memahami kapan `key={index}` masih boleh dan kapan merusak UI.

```jsx
// Berisiko jika daftar bisa diurut, disisip, atau dihapus
{produk.map((item, index) => (
  <li key={index}>{item.nama}</li>
))}
```

Indeks berubah saat item dihapus di tengah atau diurut. React mengira “item ke-0 masih item ke-0”, lalu memindahkan **state** ke baris yang salah. Gejala: checkbox pindah ke nama lain, input teks tertukar.

Indeks masih wajar jika:

- daftar statis (tidak pernah diubah urutan/isi)
- item tidak punya state internal
- kamu tidak punya id sama sekali dan daftar hanya tampilan

Untuk latihan CRUD, selalu buat id.

**Biasanya digabungkan dengan:** peringatan ESLint `react/no-array-index-key` sebagai pengingat, bukan larangan mutlak.

## filter lalu map

**Untuk apa:** menampilkan subset tanpa mengubah array sumber jika sumber itu props atau konstanta.

```jsx
import { useState } from "react";

const semua = [
  { id: 1, nama: "Buku JavaScript", kategori: "buku" },
  { id: 2, nama: "Pensil", kategori: "alat" },
  { id: 3, nama: "Buku CSS", kategori: "buku" },
];

export default function App() {
  const [kategori, setKategori] = useState("semua");

  const tampil = semua.filter((item) =>
    kategori === "semua" ? true : item.kategori === kategori
  );

  return (
    <>
      <select value={kategori} onChange={(e) => setKategori(e.target.value)}>
        <option value="semua">Semua</option>
        <option value="buku">Buku</option>
        <option value="alat">Alat</option>
      </select>
      <p role="status">{tampil.length} item</p>
      <ul>
        {tampil.map((item) => (
          <li key={item.id}>{item.nama}</li>
        ))}
      </ul>
    </>
  );
}
```

`tampil` dihitung saat render. Tidak perlu `useEffect` untuk menyalin hasil filter ke state lain. State yang perlu hanya `kategori` (input pengguna).

Pencarian teks:

```jsx
const hasil = semua.filter((item) =>
  item.nama.toLowerCase().includes(kata.trim().toLowerCase())
);
```

**Biasanya digabungkan dengan:** input controlled, `useMemo` hanya jika daftar besar dan terasa lambat, dan tampilan kosong.

## Daftar bersarang

**Untuk apa:** merender kategori yang masing-masing punya item.

```jsx
const katalog = [
  {
    id: "buku",
    judul: "Buku",
    item: [
      { id: 1, nama: "JavaScript" },
      { id: 2, nama: "CSS" },
    ],
  },
  {
    id: "alat",
    judul: "Alat",
    item: [{ id: 3, nama: "Pensil" }],
  },
];

export default function App() {
  return (
    <div>
      {katalog.map((kelompok) => (
        <section key={kelompok.id}>
          <h2>{kelompok.judul}</h2>
          <ul>
            {kelompok.item.map((produk) => (
              <li key={produk.id}>{produk.nama}</li>
            ))}
          </ul>
        </section>
      ))}
    </div>
  );
}
```

Setiap tingkat punya `key` sendiri. Key unik relatif terhadap saudara, jadi id item boleh bentrok antar kelompok jika memang terpisah, tetapi id global lebih aman.

**Biasanya digabungkan dengan:** data API berbentuk grup, accordion, dan `Fragment` jika kelompok tidak ingin `<section>`.

## Early return

**Untuk apa:** keluar lebih awal agar JSX utama tidak bersarang dalam banyak `if`.

```jsx
function DaftarProduk({ status, produk }) {
  if (status === "memuat") {
    return <p role="status">Memuat…</p>;
  }
  if (status === "gagal") {
    return <p role="alert">Data belum bisa dibuka.</p>;
  }
  if (produk.length === 0) {
    return <p>Belum ada produk.</p>;
  }
  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>{item.nama}</li>
      ))}
    </ul>
  );
}
```

Urutan penting: cek memuat dan gagal sebelum menganggap array kosong. Array awal `[]` saat masih memuat bukan berarti “tidak ada data”.

Early return di tengah komponen **setelah** Hooks dilarang jika membuat jumlah Hooks berubah. Panggil semua Hooks dulu, baru return cabang tampilan. Lihat [file 12](12-aturan-hooks-kesalahan.md).

**Biasanya digabungkan dengan:** fetch, skeleton, dan `role="status"`.

## Ternary

**Untuk apa:** memilih satu dari dua elemen di tengah JSX.

```jsx
export default function App({ sudahMasuk, nama }) {
  return (
    <header>
      {sudahMasuk ? <p>Halo, {nama}</p> : <a href="/masuk">Masuk</a>}
    </header>
  );
}
```

Ternary bersarang sulit dibaca:

```jsx
{status === "a" ? <A /> : status === "b" ? <B /> : <C />}
```

Lebih aman: early return, variabel elemen, atau lookup.

Jika salah satu cabang tidak merender apa-apa, kembalikan `null`:

```jsx
{terbuka ? <Menu /> : null}
```

**Biasanya digabungkan dengan:** header login, tombol alternatif, dan empty state pendek.

## Operator &&

**Untuk apa:** menampilkan elemen hanya jika kondisi benar.

```jsx
{stok === 0 && <p>Stok habis. Pesan lagi nanti.</p>}
{pesan && <p role="status">{pesan}</p>}
```

`&&` mengembalikan operand kanan jika kiri truthy. Jika kiri falsy, mengembalikan nilai kiri.

Jebakan angka:

```jsx
{jumlah && <p>{jumlah} barang</p>}
```

Jika `jumlah` adalah `0`, React merender teks `0`. Tulis:

```jsx
{jumlah > 0 && <p>{jumlah} barang</p>}
```

Jebakan string kosong biasanya aman (tidak tampil). `null` dan `undefined` tidak tampil. Object tidak boleh jadi anak JSX.

**Biasanya digabungkan dengan:** badge, pesan error, dan footer opsional.

## Variabel elemen

**Untuk apa:** menyusun cabang di JavaScript biasa, lalu menaruh hasilnya di JSX.

```jsx
function Panel({ status, data }) {
  let isi;
  if (status === "memuat") {
    isi = <p>Memuat…</p>;
  } else if (status === "gagal") {
    isi = <p>Gagal memuat.</p>;
  } else {
    isi = <pre>{JSON.stringify(data, null, 2)}</pre>;
  }

  return (
    <section>
      <h2>Detail</h2>
      {isi}
    </section>
  );
}
```

Cocok jika kerangka (`<section>`, judul) sama dan hanya isi yang berbeda.

**Biasanya digabungkan dengan:** layout tetap, tab, dan wizard langkah.

## Lookup object menggantikan switch

**Untuk apa:** memetakan nilai ke komponen tanpa ranting `switch` yang panjang.

```jsx
const ikonStatus = {
  dikemas: "Dikemas",
  dikirim: "Dikirim",
  selesai: "Selesai",
};

function StatusPesanan({ status }) {
  return <p>{ikonStatus[status] ?? "Tidak diketahui"}</p>;
}
```

Untuk komponen:

```jsx
const halaman = {
  beranda: <Beranda />,
  produk: <Produk />,
  tentang: <Tentang />,
};

function Isi({ nama }) {
  return halaman[nama] ?? <TidakDitemukan />;
}
```

Hati-hati: `<Beranda />` di object dibuat saat modul dimuat (atau saat object dibuat). Jika tiap halaman punya state yang harus segar, render di dalam fungsi:

```jsx
const buat = {
  beranda: () => <Beranda />,
  produk: () => <Produk />,
};

function Isi({ nama }) {
  const Gambar = buat[nama];
  return Gambar ? <Gambar /> : <TidakDitemukan />;
}
```

**Biasanya digabungkan dengan:** tab sederhana tanpa router, status enum, dan badge.

## Empat tampilan daftar

**Untuk apa:** tidak meninggalkan pengguna di layar kosong tanpa penjelasan.

```jsx
function Daftar({ status, item, onMuatLagi }) {
  if (status === "memuat") {
    return <p role="status">Memuat daftar…</p>;
  }
  if (status === "gagal") {
    return (
      <div role="alert">
        <p>Gagal memuat.</p>
        <button type="button" onClick={onMuatLagi}>Coba lagi</button>
      </div>
    );
  }
  if (item.length === 0) {
    return <p>Tidak ada hasil. Ubah kata kunci.</p>;
  }
  return (
    <ul>
      {item.map((baris) => (
        <li key={baris.id}>{baris.nama}</li>
      ))}
    </ul>
  );
}
```

Empat cabang: **memuat**, **gagal**, **kosong**, **sukses**. Kosong berbeda dari gagal. Memuat berbeda dari kosong.

Untuk filter client-side, “kosong” berarti filter tidak cocok, bukan server rusak.

**Biasanya digabungkan dengan:** [pola fetch](10-fetch-pola-loading-error.md), `aria-live`, dan tombol ulang.

## Menghapus dan menyisip tanpa merusak key

**Untuk apa:** memastikan state per-baris tetap menempel pada item yang benar.

```jsx
import { useState } from "react";

function Baris({ nama }) {
  const [centang, setCentang] = useState(false);
  return (
    <label>
      <input
        type="checkbox"
        checked={centang}
        onChange={(e) => setCentang(e.target.checked)}
      />
      {nama}
    </label>
  );
}

export default function App() {
  const [item, setItem] = useState([
    { id: "a", nama: "Buku" },
    { id: "b", nama: "Pensil" },
    { id: "c", nama: "Penghapus" },
  ]);

  return (
    <>
      <button
        type="button"
        onClick={() => setItem((lama) => lama.filter((x) => x.id !== "a"))}
      >
        Hapus Buku
      </button>
      <ul>
        {item.map((baris) => (
          <li key={baris.id}>
            <Baris nama={baris.nama} />
          </li>
        ))}
      </ul>
    </>
  );
}
```

Dengan `key={baris.id}`, checkbox “Pensil” tetap pada Pensil setelah Buku dihapus. Dengan `key={index}`, checkbox Buku bisa “pindah” ke Pensil.

Jika state centang harus bertahan bersama data, simpan `selesai` di object item, bukan di dalam `Baris`. State lokal anak hilang jika anak di-unmount.

**Biasanya digabungkan dengan:** todo list, keranjang, dan form dinamis (tambah baris).

## key pada komponen vs elemen DOM

**Untuk apa:** menaruh `key` di tempat React melihat daftar.

```jsx
// Benar: key di elemen hasil map
{item.map((x) => (
  <Kartu key={x.id} judul={x.nama} />
))}

// Salah: key di dalam Kartu, map tidak punya key
function Kartu({ judul }) {
  return <article key={judul}>{judul}</article>;
}
```

Key pada elemen di dalam komponen anak tidak membantu rekonsiliasi daftar induk. Induk yang memetakan harus memasang key.

Jika `map` mengembalikan Fragment bernama, key ada di Fragment:

```jsx
import { Fragment } from "react";

{item.map((x) => (
  <Fragment key={x.id}>
    <dt>{x.nama}</dt>
    <dd>{x.harga}</dd>
  </Fragment>
))}
```

**Biasanya digabungkan dengan:** komponen kartu, tabel (`<tr key={...}>`), dan definisi list.

## key untuk mereset state

**Untuk apa:** memaksa React membuang instance komponen dan membuat yang baru, lengkap dengan state awal.

```jsx
function EditorProfil({ userId }) {
  const [draft, setDraft] = useState("");
  return (
    <textarea
      value={draft}
      onChange={(e) => setDraft(e.target.value)}
    />
  );
}

export default function App({ userId }) {
  return <EditorProfil key={userId} userId={userId} />;
}
```

Saat `userId` berubah, `key` berubah, React unmount editor lama dan mount yang baru. `draft` tidak “bocor” ke pengguna lain.

Tanpa `key`, `useState("")` tidak jalan lagi; draft pengguna A bisa tampil di profil B. Alternatif: `useEffect` yang mereset saat `userId` berubah, tetapi `key` lebih langsung.

Pakai pola ini untuk wizard, tab editor, dan form yang terikat id entitas.

**Biasanya digabungkan dengan:** route dinamis (`/produk/[id]`), tab, dan form edit.

## Fragment bertingkat di daftar

**Untuk apa:** mengembalikan beberapa saudara per item tanpa wrapper DOM.

Sudah dicontohkan di bab JSX. Ingat: `<>...</>` tidak menerima key. Pakai `Fragment` bernama.

Tabel HTML sensitif terhadap wrapper. Jangan membungkus `<tr>` dengan `<div>`. Key diletakkan di `<tr>` atau `Fragment` yang anaknya adalah sel/baris yang sah.

```jsx
<table>
  <tbody>
    {baris.map((r) => (
      <tr key={r.id}>
        <td>{r.nama}</td>
        <td>{r.stok}</td>
      </tr>
    ))}
  </tbody>
</table>
```

**Biasanya digabungkan dengan:** `<dl>`, `<table>`, dan CSS grid yang mengandalkan anak langsung.

## Kesalahan umum bab ini

- **Lupa `key`.** Console development memperingatkan. Perbaiki, jangan dibiasakan.
- **Key random setiap render.**
- **Key duplikat.** React tidak bisa membedakan saudara.
- **`{daftar.map}` tanpa `return` implisit/eksplisit.** Body `{}` pada arrow function harus `return`.
- **`jumlah && <Komponen />` menampilkan 0.**
- **Menganggap array kosong saat loading sebagai empty state.**
- **`key` dikirim dan dibaca sebagai `props.key`.** Tidak sampai ke anak.
- **Mengubah urutan daftar yang di-key dengan indeks.**

Latihan: katalog produk dengan search + filter kategori + empty state + hapus item. Pastikan `key` memakai `id`.

## Set dan Map sebagai sumber daftar

**Untuk apa:** merender isi `Set`/`Map` yang tidak langsung punya `map` seperti array.

```jsx
function LabelTerpilih({ terpilih }) {
  const daftar = [...terpilih];
  if (daftar.length === 0) return <p>Belum memilih.</p>;
  return (
    <ul>
      {daftar.map((nama) => (
        <li key={nama}>{nama}</li>
      ))}
    </ul>
  );
}
```

`Set` cocok untuk kumpulan id unik. Ubah ke array saat render. Key memakai id/nama itu sendiri jika unik.

Untuk `Map`, `[...peta.entries()]` lalu `key={id}`.

Jangan memakai index object (`{ [id]: true }`) sebagai daftar tanpa `Object.keys` yang urutannya perlu kamu sadari.

**Biasanya digabungkan dengan:** checkbox multi-pilih di file 02.

## Render nothing dengan null

**Untuk apa:** komponen yang sah tidak menggambar apa-apa.

```jsx
function BannerAdmin({ user }) {
  if (!user?.admin) return null;
  return <p>Mode pengelola aktif.</p>;
}
```

`return null` tidak meninggalkan teks. `return false` dan `return undefined` juga tidak tampil, tetapi `null` adalah konvensi paling jelas.

Jangan `return` tanpa nilai jika kamu bermaksud eksplisit — tetap `null`.

**Biasanya digabungkan dengan:** hak akses di client (bukan keamanan sungguhan; server tetap memutuskan), dan Context user.

## Daftar kosong vs null data

**Untuk apa:** membedakan “belum di-fetch” dan “fetch sukses tanpa baris”.

```jsx
const [produk, setProduk] = useState(null);

if (produk === null) return <p>Memuat…</p>;
if (produk.length === 0) return <p>Kosong.</p>;
```

Awal `null` menghindari empty state palsu. Alternatif: enum `status` + array `[]` (lebih eksplisit, disarankan di file 10).

**Biasanya digabungkan dengan:** fetch, dan tidak memakai `produk &&` jika `[]` falsy tidak berlaku (array kosong truthy!).

`[]` adalah truthy. `{produk && <Daftar />}` tetap merender daftar kosong. Pakai `produk.length` atau status.
