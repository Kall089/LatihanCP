# 13 — Katalog API React

[← Aturan Hooks](12-aturan-hooks-kesalahan.md) · [Daftar](README.md)

Katalog ini merangkum API yang sering muncul di impor `react` dan `react-dom`. Tiap entri: **Untuk apa**, contoh, **Biasanya digabungkan dengan**. File 01–12 membahas yang harian secara dalam; di sini fokus **mencari nama** dan melihat pasangan.

## Daftar isi

- [Tabel cepat](#tabel-cepat)
- [createElement](#createelement)
- [Fragment](#fragment)
- [StrictMode](#strictmode)
- [lazy](#lazy)
- [startTransition](#starttransition)
- [flushSync](#flushsync)
- [Children](#children)
- [cloneElement](#cloneelement)
- [isValidElement](#isvalidelement)
- [Component dan PureComponent](#component-dan-purecomponent)
- [memo](#memo)
- [createContext](#createcontext)
- [createRef dan createFactory](#createref-dan-createfactory)
- [Hooks: indeks](#hooks-indeks)
- [react-dom: createRoot](#react-dom-createroot)
- [react-dom: hydrateRoot](#react-dom-hydrateroot)
- [react-dom: createPortal](#react-dom-createportal)
- [API form React 19 (ringkas)](#api-form-react-19-ringkas)
- [Peta “ingin X, pakai Y”](#peta-ingin-x-pakai-y)
- [Impor yang disarankan](#impor-yang-disarankan)
- [act, Scheduler, dan API tes (bukan UI)](#act-scheduler-dan-api-tes-bukan-ui)
- [version dan default export](#version-dan-default-export)
- [Tabel gabungan wajib](#tabel-gabungan-wajib)

## Tabel cepat

| API | Paket | Untuk apa secara singkat |
| --- | --- | --- |
| `createElement` | `react` | Membuat elemen tanpa JSX |
| `Fragment` | `react` | Mengelompokkan anak tanpa node DOM; bisa `key` |
| `StrictMode` | `react` | Pemeriksaan development (Effect ganda, API usang) |
| `lazy` | `react` | Memuat komponen lewat `import()` |
| `startTransition` | `react` | Menandai update tidak mendesak |
| `flushSync` | `react-dom` | Memaksa DOM sinkron sebelum baris berikutnya |
| `Children` | `react` | Utilitas memetakan/menghitung `props.children` |
| `cloneElement` | `react` | Menyalin elemen dan menimpa props |
| `isValidElement` | `react` | Mengecek apakah nilai adalah elemen React |
| `memo` | `react` | Melewati render jika props dangkal sama |
| `createContext` | `react` | Membuat saluran Context |
| `createRef` | `react` | Object ref untuk class; di function pakai `useRef` |
| `createRoot` | `react-dom/client` | Titik masuk aplikasi client |
| `hydrateRoot` | `react-dom/client` | Menghidrasi HTML server |
| `createPortal` | `react-dom` | Merender ke node DOM lain |
| `useState` | `react` | State lokal |
| `useReducer` | `react` | State beraksi |
| `useEffect` | `react` | Sinkronisasi setelah paint |
| `useLayoutEffect` | `react` | Sinkronisasi sebelum paint |
| `useInsertionEffect` | `react` | Sisip CSS (library) |
| `useRef` | `react` | Nilai mutable / node DOM |
| `useImperativeHandle` | `react` | API ref terbatas |
| `useMemo` | `react` | Mengingat hasil hitung |
| `useCallback` | `react` | Mengingat fungsi |
| `useContext` | `react` | Membaca Context |
| `useId` | `react` | Id unik hidrasi-aman |
| `useTransition` | `react` | Transisi + `isPending` |
| `useDeferredValue` | `react` | Menunda nilai berat |
| `useSyncExternalStore` | `react` | Baca store luar |

## createElement

**Untuk apa:** membuat elemen React secara programatik. JSX dikompilasi menjadi ini (atau `jsx()` dari jsx-runtime).

```jsx
import { createElement } from "react";

const judul = createElement("h1", { className: "judul" }, "Toko Belajar");

const kartu = createElement(
  "article",
  { className: "kartu" },
  createElement("h2", null, "Buku"),
  createElement("p", null, "Rp45.000")
);

function Sapaan({ nama }) {
  return createElement("p", null, "Halo, ", nama);
}

export default function App() {
  return createElement(
    "main",
    null,
    judul,
    createElement(Sapaan, { nama: "Haikal" })
  );
}
```

Argument:

1. tipe: string tag DOM atau fungsi/class komponen
2. props: object atau `null`
3. …children: sisa argument

`key` dan (di React 18) `ref` diletakkan di object props untuk `createElement`, tetapi `key` tidak sampai ke komponen sebagai `props.key`.

Kamu jarang menulis ini di aplikasi. Berguna saat:

- membangun elemen dari konfigurasi (tipe dinamis)
- membaca stack trace
- memahami `cloneElement`

Tipe dinamis:

```jsx
const peta = { h1: "h1", h2: "h2" };
function Judul({ tingkat, children }) {
  return createElement(peta[tingkat] || "h2", null, children);
}
```

Di JSX, tipe dinamis harus berupa variabel berhuruf besar: `const Tag = "h2"; return <Tag>{children}</Tag>;`.

**Biasanya digabungkan dengan:** JSX (sebagai hasil kompilasi), `cloneElement`, tes yang membandingkan `type`/`props`, dan [bab 01](01-jsx-komponen-props-children.md). [createElement](https://react.dev/reference/react/createElement).

## Fragment

**Untuk apa:** mengembalikan beberapa saudara tanpa menambah elemen DOM.

```jsx
import { Fragment } from "react";

export function MetaProduk({ nama, sku }) {
  return (
    <Fragment>
      <dt>Nama</dt>
      <dd>{nama}</dd>
      <dt>SKU</dt>
      <dd>{sku}</dd>
    </Fragment>
  );
}

export function DaftarMeta({ item }) {
  return (
    <dl>
      {item.map((x) => (
        <Fragment key={x.sku}>
          <dt>{x.nama}</dt>
          <dd>{x.sku}</dd>
        </Fragment>
      ))}
    </dl>
  );
}
```

Bentuk singkat `<>...</>` setara Fragment tanpa `key` dan tanpa props. Tidak bisa `< key={id}>`.

`Fragment` boleh punya `key`. Props lain tidak didukung.

Kapan **tidak** memakai Fragment: jika kamu butuh kelas CSS, landmark (`<main>`), atau target `querySelector`. Pakai elemen semantik.

**Biasanya digabungkan dengan:** `map` yang mengembalikan pasangan elemen, tabel yang tidak boleh dibungkus `div`, dan [bab 01](01-jsx-komponen-props-children.md#fragment). [Fragment](https://react.dev/reference/react/Fragment).

## StrictMode

**Untuk apa:** mengaktifkan pemeriksaan tambahan **hanya di development**.

```jsx
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import App from "./App.jsx";

createRoot(document.getElementById("root")).render(
  <StrictMode>
    <App />
  </StrictMode>
);
```

Yang dilakukan di development (perilaku rinci bergantung versi):

- merender ulang ekstra untuk menemukan side effect saat render
- menjalankan Effect: setup → cleanup → setup
- memperingatkan API usang (beberapa lifecycle class)
- membantu menemukan ketidakmurnian

Tidak mengubah perilaku produksi. Tidak “mengoptimasi” aplikasi.

Jangan menonaktifkannya agar fetch tidak dobel. Perbaiki cleanup/abort. Jangan menaruh POST di Effect.

Boleh membungkus subtree, bukan seluruh app, jika kamu mengisolasi percobaan — biasanya bungkus akar saja.

**Biasanya digabungkan dengan:** `createRoot`, Effect ber-cleanup, reducer murni, dan [bab 04](04-useEffect-useLayoutEffect-useInsertionEffect.md#strict-mode-dan-effect-ganda). [StrictMode](https://react.dev/reference/react/StrictMode).

## lazy

**Untuk apa:** code splitting: unduh JS komponen saat pertama kali dirender.

```jsx
import { lazy, Suspense } from "react";

const Statistik = lazy(() => import("./Statistik.jsx"));

export default function App({ tab }) {
  return (
    <Suspense fallback={<p>Memuat tab…</p>}>
      {tab === "statistik" ? <Statistik /> : <p>Beranda</p>}
    </Suspense>
  );
}
```

Modul harus `export default` komponen, atau kamu memetakan named export (lihat [bab 11](11-portal-suspense-error-boundary.md#lazy)).

`lazy` tidak untuk data. Itu untuk **kode**. Data memakai fetch/server.

Jangan `lazy` di dalam komponen (setiap render komponen lazy baru, state hilang):

```jsx
function Salah() {
  const X = lazy(() => import("./X.jsx")); // jangan
  return <X />;
}
```

Taruh `const X = lazy(...)` di modul.

**Biasanya digabungkan dengan:** `Suspense`, Error Boundary, rute jarang, chart/peta. [lazy](https://react.dev/reference/react/lazy).

## startTransition

**Untuk apa:** membungkus `setState` yang boleh ditunda agar input/klik tetap mulus.

```jsx
import { startTransition, useState } from "react";

export default function App({ semua }) {
  const [teks, setTeks] = useState("");
  const [daftar, setDaftar] = useState(semua);

  function onUbah(event) {
    const nilai = event.target.value;
    setTeks(nilai);
    startTransition(() => {
      setDaftar(
        semua.filter((x) => x.nama.toLowerCase().includes(nilai.toLowerCase()))
      );
    });
  }

  return (
    <>
      <input value={teks} onChange={onUbah} />
      <ul>
        {daftar.map((x) => (
          <li key={x.id}>{x.nama}</li>
        ))}
      </ul>
    </>
  );
}
```

Beda dengan `useTransition`: tidak ada `isPending`. Bisa dipanggil di luar komponen (helper).

Jangan membungkus update nilai input controlled. Ketikan harus mendesak.

Tidak ada jaminan waktu. Bukan debounce.

**Biasanya digabungkan dengan:** `useTransition` jika perlu spinner, `useDeferredValue` sebagai alternatif satu-state, daftar besar, [bab 06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md). [startTransition](https://react.dev/reference/react/startTransition).

## flushSync

**Untuk apa:** memaksa React menerapkan update **sekarang**, sebelum baris berikutnya membaca DOM.

```jsx
import { useRef, useState } from "react";
import { flushSync } from "react-dom";

export default function App() {
  const [item, setItem] = useState(["A", "B"]);
  const akhirRef = useRef(null);

  function tambah() {
    flushSync(() => {
      setItem((lama) => [...lama, `Item ${lama.length + 1}`]);
    });
    akhirRef.current?.scrollIntoView();
  }

  return (
    <>
      <button type="button" onClick={tambah}>Tambah</button>
      <ul>
        {item.map((x) => (
          <li key={x}>{x}</li>
        ))}
      </ul>
      <div ref={akhirRef} />
    </>
  );
}
```

Tanpa `flushSync`, `scrollIntoView` bisa jalan sebelum item baru ada di DOM (batching).

`flushSync` merusak keunggulan batching dan bisa memaksa layout. Pakai jarang: ukur/scroll/fokus yang **harus** melihat DOM hasil `setState` di handler yang sama.

Jangan membungkus seluruh aplikasi. Jangan di dalam Effect tanpa alasan kuat. Jangan di SSR.

**Biasanya digabungkan dengan:** `useRef` ke elemen, chat yang auto-scroll, dan integrasi library DOM. [flushSync](https://react.dev/reference/react-dom/flushSync).

## Children

**Untuk apa:** utilitas untuk mengolah `props.children` yang bisa berupa satu elemen, array, atau string.

```jsx
import { Children } from "react";

function DaftarNomor({ children }) {
  const jumlah = Children.count(children);
  return (
    <div>
      <p>{jumlah} langkah</p>
      <ol>
        {Children.map(children, (anak, i) => (
          <li>
            {i + 1}. {anak}
          </li>
        ))}
      </ol>
    </div>
  );
}

export default function App() {
  return (
    <DaftarNomor>
      <span>Siapkan bahan</span>
      <span>Masak</span>
      <span>Sajikan</span>
    </DaftarNomor>
  );
}
```

Metode yang masih dibahas:

| Metode | Kegunaan |
| --- | --- |
| `Children.map` | Memetakan tiap anak; mengabaikan `null`/`boolean` |
| `Children.forEach` | Sama tanpa array hasil |
| `Children.count` | Jumlah anak yang “ada” |
| `Children.toArray` | Meratakan dan memberi key |
| `Children.only` | Memastikan tepat satu anak; lempar jika tidak |

`Children.toArray` berguna sebelum `filter`/`sort` pada children.

Dokumentasi modern menyarankan **menghindari** `Children` untuk API baru: lebih jelas menerima array props (`langkah={['A','B']}`) atau komposisi eksplisit. `Children` sulit di-type dan mengejutkan jika anak adalah komponen yang mengembalikan banyak elemen.

`Children.map` vs `array.map`: children belum tentu array. Satu anak bukan array; `children.map` bisa meledak. `Children.map` aman.

**Biasanya digabungkan dengan:** layout slot, `cloneElement` (pola lama), dan lebih baik diganti props array. [Children](https://react.dev/reference/react/Children).

## cloneElement

**Untuk apa:** menyalin elemen dan menambahkan/menimpa props.

```jsx
import { cloneElement, Children } from "react";

function Toolbar({ children }) {
  return (
    <div className="toolbar">
      {Children.map(children, (anak) =>
        cloneElement(anak, { className: "toolbar-item" })
      )}
    </div>
  );
}
```

Pola ini rapuh: `className` menimpa milik anak, anak harus elemen yang menerima prop itu, dan Fragmen/komponen pembungkus tidak bekerja seperti yang dikira.

Alternatif lebih jelas: render props, `children` fungsi, atau Context.

Kapan masih wajar: library yang harus menyuntikkan `ref`/`id` ke elemen yang diberikan pengguna, dan kamu tidak mengendalikan sumbernya. Tetap pertimbangkan `cloneElement` sebagai pelarian.

```jsx
function GabungClass({ anak, className }) {
  return cloneElement(anak, {
    className: [anak.props.className, className].filter(Boolean).join(" "),
  });
}
```

Jangan `cloneElement` untuk mengubah children di dalam komponen yang kamu tulis sendiri — ubah JSX di sumber.

**Biasanya digabungkan dengan:** `Children.map`, `isValidElement`, desain sistem lama. [cloneElement](https://react.dev/reference/react/cloneElement).

## isValidElement

**Untuk apa:** memastikan nilai adalah elemen React sebelum `cloneElement`.

```jsx
import { Children, cloneElement, isValidElement } from "react";

function SuntikDisabled({ children, disabled }) {
  return Children.map(children, (anak) => {
    if (!isValidElement(anak)) return anak;
    return cloneElement(anak, { disabled });
  });
}
```

String dan angka bukan elemen. `isValidElement("teks")` adalah false. Tanpa cek, `cloneElement` melempar.

**Biasanya digabungkan dengan:** `cloneElement`, `Children`, library slot.

## Component dan PureComponent

**Untuk apa:** basis class component. Hanya perlu dikenali saat membaca kode lama atau menulis Error Boundary.

```jsx
import { Component } from "react";

class Penghitung extends Component {
  state = { n: 0 };
  render() {
    return (
      <button type="button" onClick={() => this.setState({ n: this.state.n + 1 })}>
        {this.state.n}
      </button>
    );
  }
}
```

`PureComponent` menambahkan perbandingan props/state dangkal sebelum render, mirip gagasan `memo`.

Kode baru: function + Hooks. Class: Error Boundary, atau maintenance.

**Biasanya digabungkan dengan:** [bab 11 Error Boundary](11-portal-suspense-error-boundary.md), dan migrasi bertahap ke function.

## memo

**Untuk apa:** lihat [bab 06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md#reactmemo). Entri katalog:

```jsx
import { memo } from "react";

const Kartu = memo(function Kartu({ judul }) {
  return <h2>{judul}</h2>;
});
```

**Biasanya digabungkan dengan:** `useCallback`, `useMemo`, daftar panjang. [memo](https://react.dev/reference/react/memo).

## createContext

**Untuk apa:** lihat [bab 08](08-context-useContext-useId.md). Entri katalog:

```jsx
import { createContext } from "react";

export const LocaleContext = createContext("id-ID");
```

Panggil di modul. Provider + `useContext` / `use`.

**Biasanya digabungkan dengan:** `useContext`, `useMemo` pada `value`, custom Hook. [createContext](https://react.dev/reference/react/createContext).

## createRef dan createFactory

**Untuk apa:** mengenali API lama agar tidak dipilih di kode baru.

```jsx
import { createRef, Component } from "react";

class FormLama extends Component {
  inputRef = createRef();
  render() {
    return <input ref={this.inputRef} />;
  }
}
```

Di function component, `useRef` mengembalikan object yang sama setiap render. `createRef()` di tubuh function **membuat object baru setiap render** — salah untuk menyimpan nilai.

`createFactory` sudah dihapus/dihindari; gunakan JSX atau `createElement`.

**Biasanya digabungkan dengan:** class lama. Kode baru: `useRef` + `forwardRef`.

## Hooks: indeks

**Untuk apa:** menautkan nama Hook ke file pembahasan.

| Hook | File |
| --- | --- |
| `useState` | [02](02-state-event-form.md) |
| `useReducer` | [07](07-useReducer-useSyncExternalStore.md) |
| `useEffect` | [04](04-useEffect-useLayoutEffect-useInsertionEffect.md) |
| `useLayoutEffect` | [04](04-useEffect-useLayoutEffect-useInsertionEffect.md) |
| `useInsertionEffect` | [04](04-useEffect-useLayoutEffect-useInsertionEffect.md) |
| `useRef` | [05](05-useRef-useImperativeHandle-forwardRef.md) |
| `useImperativeHandle` | [05](05-useRef-useImperativeHandle-forwardRef.md) |
| `useMemo` | [06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md) |
| `useCallback` | [06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md) |
| `useContext` | [08](08-context-useContext-useId.md) |
| `useId` | [08](08-context-useContext-useId.md) |
| `useTransition` | [06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md) |
| `useDeferredValue` | [06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md) |
| `useSyncExternalStore` | [07](07-useReducer-useSyncExternalStore.md) |
| `useDebugValue` | DevTools untuk custom Hook (bawah) |
| `use` | React 19, Promise/Context |

### useDebugValue

**Untuk apa:** menampilkan label di React DevTools pada custom Hook.

```jsx
import { useDebugValue, useState } from "react";

export function useOnlineStatus() {
  const [online, setOnline] = useState(navigator.onLine);
  useDebugValue(online ? "online" : "offline");
  return online;
}
```

Tidak memengaruhi UI pengguna. Opsional.

**Biasanya digabungkan dengan:** custom Hook yang dibagikan tim. [useDebugValue](https://react.dev/reference/react/useDebugValue).

## react-dom: createRoot

**Untuk apa:** menempelkan pohon React ke node DOM di SPA.

```jsx
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import App from "./App.jsx";

const el = document.getElementById("root");
createRoot(el).render(
  <StrictMode>
    <App />
  </StrictMode>
);
```

`createRoot` menggantikan `ReactDOM.render` (React 17). Mengaktifkan concurrent features.

Satu root per node. Jangan `createRoot` berulang pada node yang sama tanpa `root.unmount()`.

`root.render` bisa dipanggil lagi untuk mengganti pohon (jarang; biasanya state di dalam `App`).

**Biasanya digabungkan dengan:** `StrictMode`, Vite `main.jsx`, dan `index.html` yang punya `<div id="root">`. [createRoot](https://react.dev/reference/react-dom/client/createRoot).

## react-dom: hydrateRoot

**Untuk apa:** menempelkan event handler ke HTML yang sudah dirender server.

```jsx
import { hydrateRoot } from "react-dom/client";
import App from "./App.jsx";

hydrateRoot(document.getElementById("root"), <App />);
```

Pakai di framework SSR/SSG. Jangan `createRoot` pada HTML server: React membuang markup lalu menggambar ulang (lambat, kedip).

Markup server dan client harus cocok. Perbedaan memicu peringatan hidrasi.

**Biasanya digabungkan dengan:** Next.js (sudah diurus framework), `useId`, `getServerSnapshot`. [hydrateRoot](https://react.dev/reference/react-dom/client/hydrateRoot).

## react-dom: createPortal

**Untuk apa:** lihat [bab 11](11-portal-suspense-error-boundary.md#createportal).

```jsx
import { createPortal } from "react-dom";

createPortal(<div className="toast">Tersimpan</div>, document.body);
```

**Biasanya digabungkan dengan:** modal, toast, tooltip, Context tetap mengalir. [createPortal](https://react.dev/reference/react-dom/createPortal).

## API form React 19 (ringkas)

**Untuk apa:** mengenal nama jika proyek sudah React 19, tanpa mengganti seluruh tugas 18.

| API | Untuk apa |
| --- | --- |
| `useActionState` | State hasil action form (pending, error, data) |
| `useFormStatus` | Membaca status submit form terdekat (pending) |
| `useOptimistic` | Tampilan optimistis selama request |
| `use(promise)` | Membaca Promise dengan Suspense |

```jsx
import { useFormStatus } from "react-dom";

function TombolKirim() {
  const { pending } = useFormStatus();
  return (
    <button type="submit" disabled={pending}>
      {pending ? "Mengirim…" : "Kirim"}
    </button>
  );
}
```

`useFormStatus` harus di **anak** dari `<form>`, bukan di komponen yang sama tempat `<form>` ditulis.

Di Next.js, sering digabung Server Action. Lihat [next-js.md](../../next-js.md).

**Biasanya digabungkan dengan:** `<form action={fn}>`, transisi otomatis, dan validasi server.

## Peta “ingin X, pakai Y”

| Kamu ingin | Pakai |
| --- | --- |
| Tampil berubah karena klik | `useState` |
| Banyak aksi pada satu object | `useReducer` |
| Data dari nenek jauh | Context |
| Data dari server, halaman publik, Next | Server Component + `fetch` |
| Data dari server, filter hidup di client | `useEffect` + abort / Hook fetch |
| Fokus ke input | `useRef` + `focus()` |
| Id label unik | `useId` |
| Modal di atas halaman | `createPortal` |
| Pecah bundle tab berat | `lazy` + `Suspense` |
| Widget error tidak merobohkan app | Error Boundary |
| Filter 5000 baris tanpa macet ketik | `useDeferredValue` / `useTransition` |
| Scroll setelah item tertambah | `flushSync` + ref (jarang) |
| Listener `matchMedia` | `useSyncExternalStore` |
| Logika dipakai 3 komponen | custom Hook |
| Beberapa elemen tanpa `div` | `Fragment` |
| Cek Effect bocor | `StrictMode` |
| Paksa update sekarang ke DOM | `flushSync` |
| Elemen tanpa JSX | `createElement` |
| Tambah props ke elemen jadi | `cloneElement` (hindari jika bisa) |

## Impor yang disarankan

```jsx
import {
  Fragment,
  StrictMode,
  Suspense,
  lazy,
  memo,
  startTransition,
  createContext,
  createElement,
  Children,
  cloneElement,
  isValidElement,
  useState,
  useReducer,
  useEffect,
  useLayoutEffect,
  useRef,
  useMemo,
  useCallback,
  useContext,
  useId,
  useTransition,
  useDeferredValue,
  useSyncExternalStore,
  useImperativeHandle,
} from "react";

import { createPortal, flushSync } from "react-dom";
import { createRoot, hydrateRoot } from "react-dom/client";
```

Jangan mengimpor semuanya di setiap file. Impor yang terpakai saja.

`forwardRef` dari `react` di React 18. Di 19, `ref` bisa jadi prop.

Default export `React` (`import React from "react"`) tidak wajib untuk JSX modern (`jsx-runtime`). Tetap muncul di kode lama: `React.useState`.

**Biasanya digabungkan dengan:** bundler (Vite/Next) yang memetakan `react`/`react-dom` ke versi di `package.json`. Cocokkan dokumen resmi dengan versi itu.

---

Latihan katalog: buka `main.jsx` proyek Vite, tunjuk `createRoot` dan `StrictMode`. Tambahkan satu komponen `lazy`. Buat modal `createPortal`. Jelaskan kapan kamu **tidak** memakai `flushSync` dan `cloneElement`.

## act, Scheduler, dan API tes (bukan UI)

**Untuk apa:** tidak mengimpor API internal saat menulis komponen.

- `act(...)` dipakai tes untuk menggelapkan update agar assert melihat DOM akhir. Di React 18+ Testing Library sering membungkusnya.
- Scheduler internal bukan untuk aplikasi.
- `unstable_*` di impor React: jangan dipakai tugas kuliah.

Jika dokumentasi menyebut `act` warning, perbaiki tes (tunggu `findBy`, bungkus event), bukan menonaktifkan peringatan diam-diam tanpa paham.

**Biasanya digabungkan dengan:** React Testing Library, bukan `App.jsx`.

## version dan default export

**Untuk apa:** mengenali sisa kode lama.

```jsx
import React from "react";

React.useState(0);
React.createElement("div", null, "Halo");
```

JSX modern tidak membutuhkan `import React` kecuali plugin lama. `react/package.json` punya `version`; log itu saat debug “dua salinan React”:

```jsx
import { version } from "react";
console.log(version);
```

Dua salinan memicu “Invalid hook call”.

**Biasanya digabungkan dengan:** `npm ls react`, dan menyelaraskan `react` + `react-dom` versi sama.

## Tabel gabungan wajib

| API | Digabung dengan | Jangan digabung sembarangan dengan |
| --- | --- | --- |
| `createElement` | tipe dinamis, tes | menulis seluruh app tanpa JSX |
| `Fragment` | `map` + `key` | CSS yang butuh wrapper |
| `StrictMode` | `createRoot`, Effect ber-cleanup | mematikan agar fetch tidak dobel |
| `lazy` | `Suspense`, Error Boundary | dipanggil di dalam komponen |
| `startTransition` | filter berat, ganti tab | `setState` input controlled |
| `flushSync` | scroll/ukur setelah setState | fetch, Effect rutin |
| `Children` | `count`/`map` children tak pasti array | API komponen baru (lebih baik props array) |
| `cloneElement` | menyuntik props ke elemen jadi | mengubah anak yang kamu tulis sendiri |
| `createPortal` | modal, toast, `useId` | node yang dikelola React lain |
| `createRoot` | `StrictMode`, `App` | `hydrateRoot` pada HTML server |
| `hydrateRoot` | SSR, `useId` | `Date.now()` saat render |
| `memo` | `useCallback`, daftar | `children` yang selalu baru |
| `createContext` | Provider, `useContext` | dipanggil di dalam komponen |

Simpan tabel ini sebagai peta; detail ada di bagian atas file dan di bab 01–12.
