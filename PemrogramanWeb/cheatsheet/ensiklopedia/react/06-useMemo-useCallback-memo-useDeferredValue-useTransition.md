# 06 — useMemo, useCallback, memo, useDeferredValue, useTransition

[← Ref](05-useRef-useImperativeHandle-forwardRef.md) · [Daftar](README.md) · [Lanjut: reducer →](07-useReducer-useSyncExternalStore.md)

Kelompok API ini berkaitan dengan **kapan** React menghitung ulang atau menampilkan update. Jangan membungkus semua hitungan. Mulai dari kode yang benar dan mudah dibaca; ukur dulu jika terasa lambat.

## Daftar isi

- [Prinsip: hitung saat render dulu](#prinsip-hitung-saat-render-dulu)
- [useMemo](#usememo)
- [useCallback](#usecallback)
- [React.memo](#reactmemo)
- [Ketiganya biasanya bersama](#ketiganya-biasanya-bersama)
- [useTransition](#usetransition)
- [startTransition](#starttransition)
- [useDeferredValue](#usedeferredvalue)
- [Transisi vs debounce](#transisi-vs-debounce)
- [useTransition dan pending UI](#usetransition-dan-pending-ui)
- [Kapan tidak mengoptimasi](#kapan-tidak-mengoptimasi)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [memo pada komponen yang menerima children](#memo-pada-komponen-yang-menerima-children)
- [Compiler React dan kebiasaan lama](#compiler-react-dan-kebiasaan-lama)
- [Perbandingan singkat tiga penunda](#perbandingan-singkat-tiga-penunda)

## Prinsip: hitung saat render dulu

**Untuk apa:** menahan diri dari `useMemo` pada filter 10 produk.

```jsx
function Katalog({ produk, kata }) {
  const hasil = produk.filter((item) =>
    item.nama.toLowerCase().includes(kata.toLowerCase())
  );
  return (
    <ul>
      {hasil.map((item) => (
        <li key={item.id}>{item.nama}</li>
      ))}
    </ul>
  );
}
```

Tanpa `useMemo`, kode sudah benar. React merender ulang saat `kata` atau `produk` berubah — saat itulah filter memang harus jalan. `useMemo` baru berguna jika:

- hitungan berat (ribuan item, parsing mahal) **dan** komponen sering rerender karena state lain yang tidak memengaruhi hasil
- object/array hasil harus **referensinya stabil** untuk anak yang di-`memo` atau dependensi Effect

Jangan mengoptimasi spekulatif. Optimasi dini menambah dependensi yang salah dan bug stale.

**Biasanya digabungkan dengan:** Profiler React DevTools jika kamu benar-benar mengukur. [Escape hatches](https://react.dev/learn/escape-hatches).

## useMemo

**Untuk apa:** mengingat hasil hitungan di antara render, menghitung ulang hanya jika dependensi berubah.

```jsx
import { useMemo, useState } from "react";

function DaftarMahal({ item, kata, tema }) {
  const [terbuka, setTerbuka] = useState(false);

  const hasil = useMemo(() => {
    const k = kata.trim().toLowerCase();
    return item.filter((x) => x.nama.toLowerCase().includes(k));
  }, [item, kata]);

  return (
    <section className={tema}>
      <button type="button" onClick={() => setTerbuka((v) => !v)}>
        {terbuka ? "Sembunyikan opsi" : "Opsi"}
      </button>
      <p>{hasil.length} hasil</p>
      <ul>
        {hasil.map((x) => (
          <li key={x.id}>{x.nama}</li>
        ))}
      </ul>
    </section>
  );
}
```

`tema` dan `terbuka` tidak masuk dependensi `hasil`. Tanpa `useMemo`, filter tetap jalan saat tombol opsi diklik. Dengan daftar kecil, perbedaan tidak terasa.

Signature: `useMemo(() => nilai, [deps])`. Fungsi **mengembalikan** nilai. Jangan menaruh side effect di dalamnya (fetch, tulis DOM).

`useMemo` adalah petunjuk. React boleh menghitung ulang. Jangan memakai `useMemo` untuk menjamin identitas demi kebenaran bisnis; pakai untuk performa.

Object yang dibuat untuk props:

```jsx
const opsi = useMemo(
  () => ({ locale: "id-ID", style: "currency", currency: "IDR" }),
  []
);
```

Konstanta statis lebih baik diletakkan di luar komponen, tanpa Hook.

**Biasanya digabungkan dengan:** `React.memo` pada anak yang menerima array/object, dan daftar panjang. [useMemo](https://react.dev/reference/react/useMemo).

## useCallback

**Untuk apa:** mengingat **fungsi** yang sama di antara render, agar anak yang di-`memo` atau Effect yang bergantung pada fungsi tidak menganggap props/deps berubah.

```jsx
import { useCallback, useState } from "react";

export default function App({ item }) {
  const [pilih, setPilih] = useState(null);

  const handlePilih = useCallback((id) => {
    setPilih(id);
  }, []);

  return (
    <ul>
      {item.map((x) => (
        <Baris key={x.id} item={x} onPilih={handlePilih} />
      ))}
    </ul>
  );
}
```

Tanpa `useCallback`, `handlePilih` adalah fungsi baru setiap render. `React.memo(Baris)` akan tetap rerender karena props `onPilih` berubah.

`useCallback(fn, deps)` setara `useMemo(() => fn, deps)`. Sertakan nilai yang dibaca fungsi, kecuali setter `useState` (stabil).

Jika fungsi memakai `pilih` lama:

```jsx
const handlePilih = useCallback((id) => {
  setPilih((lama) => (lama === id ? null : id));
}, []);
```

Bentuk fungsi setter menghindari `[pilih]` di dependensi.

Jangan membungkus setiap handler. Tanpa `memo` di anak, `useCallback` hampir tidak menghemat apa-apa.

**Biasanya digabungkan dengan:** `React.memo`, dependensi `useEffect`/`useMemo`, dan Context value yang berisi fungsi. [useCallback](https://react.dev/reference/react/useCallback).

## React.memo

**Untuk apa:** melewati render ulang komponen jika props-nya dangkal sama (`Object.is` per prop).

```jsx
import { memo } from "react";

const KartuProduk = memo(function KartuProduk({ nama, harga }) {
  return (
    <article>
      <h2>{nama}</h2>
      <p>Rp{harga.toLocaleString("id-ID")}</p>
    </article>
  );
});

export default function App({ produk, kataKunci }) {
  return (
    <>
      <p>Filter: {kataKunci}</p>
      <ul>
        {produk.map((item) => (
          <li key={item.id}>
            <KartuProduk nama={item.nama} harga={item.harga} />
          </li>
        ))}
      </ul>
    </>
  );
}
```

Jika `App` rerender karena `kataKunci` tetapi `nama`/`harga` item sama, `KartuProduk` yang di-memo bisa dilewati.

`memo` membandingkan props dangkal. `item={item}` berubah jika induk membuat object baru setiap kali. Kirim field primitif, atau memoize object.

Pembanding kustom (jarang):

```jsx
memo(Kartu, (prev, next) => prev.produk.id === next.produk.id && prev.produk.rev === next.produk.rev);
```

Jika pembanding mengembalikan `true`, React **melewati** render (props dianggap sama). Mudah salah; hindari kecuali terukur.

`memo` tidak membantu jika anak selalu menerima `children` elemen baru atau callback baru.

**Biasanya digabungkan dengan:** daftar panjang, `useCallback` untuk handler, `useMemo` untuk object. [memo](https://react.dev/reference/react/memo).

## Ketiganya biasanya bersama

**Untuk apa:** melihat satu resep utuh yang memang punya alasan.

```jsx
import { memo, useCallback, useMemo, useState } from "react";

const Baris = memo(function Baris({ item, onHapus }) {
  return (
    <li>
      {item.nama}
      <button type="button" onClick={() => onHapus(item.id)}>
        Hapus
      </button>
    </li>
  );
});

export default function App({ semua }) {
  const [kata, setKata] = useState("");
  const [terpilih, setTerpilih] = useState([]);

  const hasil = useMemo(() => {
    const k = kata.trim().toLowerCase();
    return semua.filter((x) => x.nama.toLowerCase().includes(k));
  }, [semua, kata]);

  const hapus = useCallback((id) => {
    setTerpilih((lama) => lama.filter((x) => x !== id));
  }, []);

  return (
    <>
      <input value={kata} onChange={(e) => setKata(e.target.value)} />
      <p>Terpilih: {terpilih.length}</p>
      <ul>
        {hasil.map((item) => (
          <Baris key={item.id} item={item} onHapus={hapus} />
        ))}
      </ul>
    </>
  );
}
```

Alur pikir:

1. `Baris` mahal atau banyak → `memo`
2. `onHapus` harus stabil → `useCallback`
3. `hasil` mahal atau dibagikan → `useMemo`

Jika `Baris` tidak di-`memo`, hapus `useCallback`. Jika filter murah, hapus `useMemo`.

**Biasanya digabungkan dengan:** DevTools Highlight Updates, dan daftar virtual (library) jika ribuan baris.

## useTransition

**Untuk apa:** menandai update state sebagai **tidak mendesak**, agar ketikan atau klik tetap terasa ringan.

```jsx
import { useState, useTransition } from "react";

export default function App({ semua }) {
  const [kata, setKata] = useState("");
  const [hasil, setHasil] = useState(semua);
  const [pending, startTransition] = useTransition();

  function handleUbah(event) {
    const nilai = event.target.value;
    setKata(nilai);
    startTransition(() => {
      setHasil(
        semua.filter((item) =>
          item.nama.toLowerCase().includes(nilai.toLowerCase())
        )
      );
    });
  }

  return (
    <>
      <input value={kata} onChange={handleUbah} />
      {pending && <p role="status">Menyaring…</p>}
      <ul>
        {hasil.map((item) => (
          <li key={item.id}>{item.nama}</li>
        ))}
      </ul>
    </>
  );
}
```

`setKata` mendesak: input tidak tertinggal. `setHasil` di dalam `startTransition` boleh ditunda jika perangkat sibuk. `pending` menjadi true selama transisi.

Pola yang lebih sederhana: satu state `kata`, filter di render, plus `useDeferredValue` (bawah). `useTransition` unggul saat kamu **sengaja** memisahkan state mendesak dan state berat, atau menavigasi (di Next.js).

Jangan membungkus event yang harus langsung (mengetik ke controlled input) di dalam transisi. Input akan terasa lambat.

**Biasanya digabungkan dengan:** daftar besar, tab yang isinya berat, `isPending` untuk opacity. [useTransition](https://react.dev/reference/react/useTransition).

## startTransition

**Untuk apa:** API yang sama dengan `startTransition` dari `useTransition`, tetapi tanpa `isPending`, dan bisa dipanggil di luar komponen.

```jsx
import { startTransition } from "react";

function pilihTab(setTab, nama) {
  startTransition(() => {
    setTab(nama);
  });
}
```

Pakai impor `startTransition` jika kamu tidak membutuhkan flag pending. Pakai Hook jika UI harus menampilkan spinner.

`startTransition` tidak menyediakan callback “sudah selesai”. Ia hanya menurunkan prioritas update.

Di React 19, Actions dan beberapa API form memakai transisi secara otomatis. Tetap relevan untuk update state lokal yang berat.

**Biasanya digabungkan dengan:** router, pergantian view, dan [katalog startTransition](13-katalog-api-react.md#starttransition).

## useDeferredValue

**Untuk apa:** menunda nilai yang dipakai hitungan berat, sambil tetap memakai nilai terkini untuk UI ringan.

```jsx
import { useDeferredValue, useMemo, useState } from "react";

export default function App({ semua }) {
  const [kata, setKata] = useState("");
  const kataTertunda = useDeferredValue(kata);

  const hasil = useMemo(() => {
    return semua.filter((item) =>
      item.nama.toLowerCase().includes(kataTertunda.toLowerCase())
    );
  }, [semua, kataTertunda]);

  const tertinggal = kata !== kataTertunda;

  return (
    <>
      <input value={kata} onChange={(e) => setKata(e.target.value)} />
      <ul style={{ opacity: tertinggal ? 0.6 : 1 }}>
        {hasil.map((item) => (
          <li key={item.id}>{item.nama}</li>
        ))}
      </ul>
    </>
  );
}
```

Input selalu menampilkan `kata`. Daftar memakai `kataTertunda`. Saat mengetik cepat, daftar boleh “ketinggalan” sejenak; opacity menandakan itu.

`useDeferredValue` cocok jika kamu tidak ingin memecah state menjadi dua setter. React menjadwalkan rerender dengan nilai baru saat ada waktu.

Nilai awal: render pertama `useDeferredValue(kata)` sama dengan `kata`. Tidak ada delay tetap (bukan debounce 300 ms).

**Biasanya digabungkan dengan:** `useMemo` pada filter mahal, `memo` pada daftar, dan indikator stale. [useDeferredValue](https://react.dev/reference/react/useDeferredValue).

## Transisi vs debounce

**Untuk apa:** tidak mencampur dua alat yang menjawab masalah berbeda.

| Alat | Perilaku | Cocok untuk |
| --- | --- | --- |
| Debounce (timer) | Menunggu jeda ketikan, lalu jalan sekali | Request ke server, hemat kuota API |
| `useDeferredValue` / `useTransition` | UI tetap update; pekerjaan berat ditunda di thread render | Filter **lokal** ribuan item |
| Throttle | Paling banyak sekali per N ms | Scroll, resize |

Debounce menunda **kapan logika jalan**. Transisi menunda **kapan hasil berat ditampilkan**, sementara input sudah baru.

Untuk kotak cari yang menembak API: debounce `fetch`, jangan mengandalkan transisi saja. Untuk filter array di memori: transisi/deferred lebih alami.

Boleh digabung: input controlled → debounce fetch → hasil ke state. Atau input → deferred → filter lokal.

**Biasanya digabungkan dengan:** [useRef timer](05-useRef-useImperativeHandle-forwardRef.md), dan [pola fetch](10-fetch-pola-loading-error.md).

## useTransition dan pending UI

**Untuk apa:** memberi umpan balik tanpa membekukan input.

```jsx
const [pending, startTransition] = useTransition();

function gantiHalaman(nomor) {
  startTransition(() => {
    setHalaman(nomor);
  });
}

return (
  <>
    <nav aria-busy={pending}>
      <button type="button" onClick={() => gantiHalaman(1)}>1</button>
      <button type="button" onClick={() => gantiHalaman(2)}>2</button>
    </nav>
    <section style={{ opacity: pending ? 0.7 : 1 }}>
      <DaftarBerat halaman={halaman} />
    </section>
  </>
);
```

`aria-busy` membantu teknologi bantu. Jangan menonaktifkan input yang harus tetap bisa diketik.

`pending` false jika update cepat. Jangan mengandalkannya untuk logika bisnis (menyimpan ke server). Itu isyarat render.

**Biasanya digabungkan dengan:** CSS opacity, skeleton yang tidak mengganti seluruh halaman, dan tab.

## Kapan tidak mengoptimasi

**Untuk apa:** daftar peringatan praktis.

- Kurang dari ~100 item sederhana: jangan `useMemo`/`memo` dulu.
- Komponen anak kecil (satu `<li>` teks): `memo` bisa lebih mahal daripada rerender.
- Membungkus `useMemo` di sekitar JSX besar hanya “supaya rapi”: tidak membantu.
- Menaruh object baru `style={{}}` atau `onClick={() => ...}` membatalkan `memo` anak.
- Context: jika `value={{ tema, setTema }}` baru setiap render, semua konsumen rerender. Memoize value atau pecah Context. Lihat [file 08](08-context-useContext-useId.md).
- `useCallback` dengan dependensi yang berubah setiap render sama saja dengan tanpa `useCallback`.

Urutan perbaikan yang lebih ampuh daripada memo:

1. Jangan simpan turunan di state
2. Pecah state agar bagian ringan tidak tinggal serumah dengan bagian berat
3. Virtualisasi daftar sangat panjang
4. Baru `memo` / transisi

**Biasanya digabungkan dengan:** mengukur dulu, bukan menebak.

## Kesalahan umum bab ini

- **`useMemo` tanpa dependensi yang benar.** Hasil basi atau dihitung terus.
- **Side effect di dalam `useMemo`.**
- **`useCallback` pada semua fungsi “karena best practice”.**
- **`memo` tetapi props object/fungsi baru setiap kali.**
- **Membungkus `setKata` (controlled input) di `startTransition`.** Ketikan tertinggal.
- **Mengira `useDeferredValue` adalah debounce berwaktu tetap.**
- **Membandingkan performa tanpa Profiler atau dataset realistis.**
- **`memo` pada komponen yang menerima `children` tidak stabil.**

Latihan: buat daftar 2.000 nama. Bandingkan filter langsung, `useDeferredValue`, dan `useTransition` + `isPending`. Rasakan ketikan pada input.

## memo pada komponen yang menerima children

**Untuk apa:** memahami mengapa `memo` sering “tidak mempan”.

```jsx
const Bingkai = memo(function Bingkai({ children }) {
  return <section className="bingkai">{children}</section>;
});

<Bingkai>
  <p>Isi {nama}</p>
</Bingkai>
```

Setiap render induk, `<p>Isi {nama}</p>` adalah elemen baru. Props `children` berubah. `memo` pada `Bingkai` hampir selalu rerender. Itu wajar: isi memang baru.

`memo` berharga jika props **data** stabil (string/angka/object termemo) dan anak tidak selalu `children` baru. Kartu daftar dengan `nama` + `harga` lebih cocok daripada layout pembungkus.

**Biasanya digabungkan dengan:** meninjau apakah yang mahal adalah anak di dalam, bukan pembungkus.

## Compiler React dan kebiasaan lama

**Untuk apa:** tidak menumpuk `useMemo` “untuk jaga-jaga” hanya karena mendengar compiler.

React Compiler (jika diaktifkan proyek) dapat mengotomatiskan sebagian memo. Tetap:

- tulis kode benar dulu
- jangan mutasi
- jangan side effect saat render

Ensiklopedia ini tetap menjelaskan `useMemo`/`useCallback` karena banyak tugas dan codebase belum memakai compiler, dan karena kamu harus membaca kodenya.

Jika compiler aktif, membungkus manual biasanya tidak salah, hanya ramai. Ikuti aturan proyekmu.

**Biasanya digabungkan dengan:** dokumentasi resmi versi React di `package.json`.

## Perbandingan singkat tiga penunda

```text
useMemo            : jangan hitung ulang jika deps sama
useCallback        : jangan buat fungsi baru jika deps sama
memo(Komponen)     : jangan render ulang jika props dangkal sama
useDeferredValue   : tampilkan nilai berat versi “agak lama”
useTransition      : update di dalam callback boleh ditunda
startTransition    : sama, tanpa isPending
```

Semua kecuali `memo` adalah Hook atau API render. Tidak ada yang menggantikan `key` yang benar atau menghindari kerja O(n²) di filter.

**Biasanya digabungkan dengan:** mengukur dengan data realistis, bukan 5 item dummy.
