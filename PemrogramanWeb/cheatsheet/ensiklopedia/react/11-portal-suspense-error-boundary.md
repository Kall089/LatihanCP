# 11 — Portal, Suspense, dan Error Boundary

[← Fetch](10-fetch-pola-loading-error.md) · [Daftar](README.md) · [Lanjut: aturan Hooks →](12-aturan-hooks-kesalahan.md)

Tiga alat untuk kasus “di luar alur render biasa”: Portal merender anak ke node DOM lain, Suspense menunda tampilan sampai sesuatu siap, Error Boundary menangkap error render di subtree.

## Daftar isi

- [createPortal](#createportal)
- [Modal dengan portal](#modal-dengan-portal)
- [Fokus, escape, dan scroll](#fokus-escape-dan-scroll)
- [lazy](#lazy)
- [Suspense](#suspense)
- [Batas Suspense](#batas-suspense)
- [Error Boundary (class)](#error-boundary-class)
- [Pola pemakaian Error Boundary](#pola-pemakaian-error-boundary)
- [Suspense + Error Boundary](#suspense--error-boundary)
- [Fallback yang ramah](#fallback-yang-ramah)
- [React 19: use dan Activity secara singkat](#react-19-use-dan-activity-secara-singkat)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Toast dan tumpukan portal](#toast-dan-tumpukan-portal)
- [Preload lazy](#preload-lazy)
- [Error di handler vs error di render](#error-di-handler-vs-error-di-render)
- [Nested modal dan z-index](#nested-modal-dan-z-index)

## createPortal

**Untuk apa:** merender JSX ke `document.body` (atau node lain) tetap dengan event dan Context dari pohon React asal.

```jsx
import { createPortal } from "react-dom";

export function Tooltip({ anak, teks }) {
  return createPortal(
    <div className="tooltip">{teks}</div>,
    document.body
  );
}
```

Tanpa portal, `position: fixed` di dalam induk `transform`/`overflow: hidden` bisa terpotong. Modal dan toast hampir selalu ke `body`.

Portal **tetap** anak React: Context berlaku, event bubbling di React naik ke induk React (bukan hanya DOM visual). Klik di dalam modal masih bisa ditangkap induk di pohon React — rancang `stopPropagation` jika perlu.

Jangan portal ke node yang React juga kendalikan isinya secara penuh, atau dua sumber akan berebut.

**Biasanya digabungkan dengan:** state `terbuka`, `useId` untuk `aria-labelledby`, dan CSS overlay. [createPortal](https://react.dev/reference/react-dom/createPortal).

## Modal dengan portal

**Untuk apa:** dialog di atas halaman tanpa merusak layout.

```jsx
import { useEffect } from "react";
import { createPortal } from "react-dom";

export function Modal({ terbuka, judul, onTutup, children }) {
  if (!terbuka) return null;

  return createPortal(
    <div
      className="modal-latar"
      role="presentation"
      onClick={onTutup}
    >
      <div
        className="modal-kotak"
        role="dialog"
        aria-modal="true"
        aria-labelledby="judul-modal"
        onClick={(e) => e.stopPropagation()}
      >
        <h2 id="judul-modal">{judul}</h2>
        {children}
        <button type="button" onClick={onTutup}>
          Tutup
        </button>
      </div>
    </div>,
    document.body
  );
}
```

Klik latar menutup; klik kotak tidak menutup. `aria-modal` menandai dialog. Untuk produksi, tambahkan focus trap (library atau rumus sendiri).

SSR: `document.body` tidak ada di server. Render modal hanya setelah mount, atau pakai cek `typeof document !== "undefined"` plus Effect. Di Vite SPA murni, `document` ada saat modul client jalan.

```jsx
const [siap, setSiap] = useState(false);
useEffect(() => setSiap(true), []);
if (!siap) return null;
return createPortal(..., document.body);
```

**Biasanya digabungkan dengan:** `useToggle`, form di dalam dialog, dan `useEffect` untuk Escape.

## Fokus, escape, dan scroll

**Untuk apa:** membuat modal tidak menyiksa keyboard dan tidak menggeser body.

```jsx
import { useEffect, useRef } from "react";

export function useKunciModal(terbuka, onTutup, kotakRef) {
  const sebelumnya = useRef(null);

  useEffect(() => {
    if (!terbuka) return undefined;
    sebelumnya.current = document.activeElement;
    kotakRef.current?.focus();
    const overflowAsal = document.body.style.overflow;
    document.body.style.overflow = "hidden";

    function onKey(event) {
      if (event.key === "Escape") onTutup();
    }
    window.addEventListener("keydown", onKey);
    return () => {
      window.removeEventListener("keydown", onKey);
      document.body.style.overflow = overflowAsal;
      if (sebelumnya.current instanceof HTMLElement) {
        sebelumnya.current.focus();
      }
    };
  }, [terbuka, onTutup, kotakRef]);
}
```

Kotak dialog butuh `tabIndex={-1}` agar bisa `focus()`. Kembalikan fokus ke tombol pemicu saat tutup.

Scroll lock kasar lewat `overflow: hidden`. Di halaman panjang, perhatikan lebar scrollbar (geser layout). Cukup untuk tugas; aplikasi besar memakai library dialog.

**Biasanya digabungkan dengan:** `useRef`, `useImperativeHandle` (`fokus()`), dan portal.

## lazy

**Untuk apa:** memuat kode komponen hanya saat dibutuhkan, memecah bundle.

```jsx
import { lazy, Suspense } from "react";

const EditorMap = lazy(() => import("./EditorMap.jsx"));

export default function App({ tampilPeta }) {
  return (
    <Suspense fallback={<p>Memuat peta…</p>}>
      {tampilPeta ? <EditorMap /> : <p>Peta disembunyikan.</p>}
    </Suspense>
  );
}
```

`import()` mengembalikan Promise modul dengan `export default` komponen. `lazy` membuat komponen yang “ditangguhkan”.

Pakai untuk rute jarang, editor berat, chart, atau modal besar — bukan untuk tombol 10 baris.

Error pemuatan (jaringan) perlu Error Boundary di sekitar `Suspense`.

Named export:

```jsx
const Chart = lazy(() =>
  import("./Chart.jsx").then((m) => ({ default: m.Chart }))
);
```

**Biasanya digabungkan dengan:** `Suspense`, pemisahan rute (Next.js sudah memecah per `page.js`), dan indikator. [lazy](https://react.dev/reference/react/lazy). Lihat [katalog](13-katalog-api-react.md#lazy).

## Suspense

**Untuk apa:** menampilkan fallback sementara anak “menunggu”.

```jsx
<Suspense fallback={<p role="status">Memuat bagian ini…</p>}>
  <BagianBerat />
</Suspense>
```

Anak menunggu jika:

- komponen `lazy` belum tiba
- di React 19, `use(promise)` belum resolve
- framework (Next.js) menangguhkan Server Component / data

`useEffect` + `fetch` **tidak** otomatis memicu Suspense. Kamu tetap memakai status `memuat` sendiri, kecuali memakai API yang terintegrasi Suspense.

Fallback mengganti **seluruh** subtree yang ditangguhkan sampai siap. Batasi cakupan: jangan bungkus seluruh aplikasi dengan satu fallback, atau satu komponen kecil men-blank halaman.

Beberapa `Suspense` bersarang: yang dalam menangani bagiannya, yang luar menangani yang lain.

**Biasanya digabungkan dengan:** `lazy`, skeleton CSS, dan Error Boundary. [Suspense](https://react.dev/reference/react/Suspense).

## Batas Suspense

**Untuk apa:** merancang mana yang boleh diganti fallback.

```jsx
export default function HalamanProduk() {
  return (
    <main>
      <h1>Detail produk</h1>
      <Suspense fallback={<p>Memuat info…</p>}>
        <InfoProduk />
      </Suspense>
      <Suspense fallback={<p>Memuat ulasan…</p>}>
        <Ulasan />
      </Suspense>
    </main>
  );
}
```

Judul tetap terlihat. Dua bagian independen tidak saling menahan.

Jika `Ulasan` selalu berat dan jarang dibuka, gabungkan dengan `lazy`.

`fallback={null}` menyembunyikan tanpa placeholder; bisa membuat layout loncat. Skeleton seukuran konten lebih nyaman.

**Biasanya digabungkan dengan:** layout tetap, dan Next.js `loading.js` (kerangka route, konsep serupa).

## Error Boundary (class)

**Untuk apa:** menangkap error JavaScript saat **render** di subtree, lalu menampilkan UI cadangan, bukan layar putih.

React belum menyediakan Error Boundary berupa function component + Hook resmi. Ini **satu** tempat class masih diperlukan (kecuali library yang membungkusnya).

```jsx
import { Component } from "react";

export class ErrorBoundary extends Component {
  constructor(props) {
    super(props);
    this.state = { error: null };
  }

  static getDerivedStateFromError(error) {
    return { error };
  }

  componentDidCatch(error, info) {
    console.error("Error Boundary", error, info.componentStack);
  }

  render() {
    if (this.state.error) {
      return this.props.fallback ?? (
        <p role="alert">Bagian ini bermasalah.</p>
      );
    }
    return this.props.children;
  }
}
```

```jsx
<ErrorBoundary fallback={<p>Kartu gagal ditampilkan.</p>}>
  <KartuBerisiko />
</ErrorBoundary>
```

Yang **tidak** ditangkap:

- error di event handler (pakai `try/catch` sendiri)
- error di `setTimeout` asynchronous (kecuali kamu `setState` yang lalu melempar saat render)
- Error Boundary itu sendiri
- error di server (tergantung framework)

Untuk mereset, ubah `key` pada Boundary saat pengguna menekan “Coba lagi”, atau simpan `resetKey` di state induk.

**Biasanya digabungkan dengan:** log layanan, `lazy`/`Suspense`, dan membatasi cakupan ke widget, bukan seluruh app tanpa judul. [Error boundaries](https://react.dev/reference/react/Component#catching-rendering-errors-with-an-error-boundary).

## Pola pemakaian Error Boundary

**Untuk apa:** menaruh jaring pada batas yang masuk akal.

```jsx
export default function App() {
  return (
    <>
      <Kepala />
      <ErrorBoundary fallback={<p>Daftar gagal.</p>}>
        <DaftarProduk />
      </ErrorBoundary>
      <ErrorBoundary fallback={<p>Keranjang gagal.</p>}>
        <Keranjang />
      </ErrorBoundary>
    </>
  );
}
```

Satu widget rusak tidak merobohkan header. Terlalu banyak Boundary membuat kode ramai; pecah di batas fitur.

Reset:

```jsx
function Panel({ children }) {
  const [kunci, setKunci] = useState(0);
  return (
    <div>
      <ErrorBoundary
        key={kunci}
        fallback={
          <button type="button" onClick={() => setKunci((n) => n + 1)}>
            Coba lagi
          </button>
        }
      >
        {children}
      </ErrorBoundary>
    </div>
  );
}
```

`key` baru membuat instance Boundary baru; state error hilang.

**Biasanya digabungkan dengan:** `key`, logging, dan tidak menelan error diam-diam tanpa pesan.

## Suspense + Error Boundary

**Untuk apa:** membedakan “masih menunggu” dari “gagal”.

```jsx
<ErrorBoundary fallback={<p role="alert">Gagal memuat peta.</p>}>
  <Suspense fallback={<p role="status">Memuat peta…</p>}>
    <PetaLazy />
  </Suspense>
</ErrorBoundary>
```

Urutan yang umum: Error Boundary di luar, Suspense di dalam. Jika `lazy` gagal import, error tertangkap. Jika masih unduh, fallback Suspense.

Jangan memakai Error Boundary sebagai pengganti `catch` pada `fetch` di Effect: fetch error adalah state, bukan error render, kecuali kamu melempar saat render (pola yang membingungkan).

**Biasanya digabungkan dengan:** `lazy`, dan status fetch untuk data biasa.

## Fallback yang ramah

**Untuk apa:** menulis placeholder yang tidak berbohong dan tidak meloncat jauh.

Baik:

- teks “Memuat daftar produk…”
- skeleton dengan tinggi kira-kira sama
- `role="status"` / `aria-busy`

Kurang baik:

- spinner tanpa konteks
- `fallback={null}` pada blok besar
- pesan error teknis (`undefined is not a function`) ke pengguna

Untuk error: apa yang rusak, apa yang bisa dilakukan (“Muat ulang”, “Kembali”).

**Biasanya digabungkan dengan:** CSS skeleton, dan copywriting singkat.

## React 19: use dan Activity secara singkat

**Untuk apa:** mengetahui API baru tanpa wajib memakainya di tugas React 18.

`use(promise)` membaca Promise di Client Component dan menangguhkan ke Suspense terdekat sampai selesai. Bukan pengganti sembarangan untuk `useEffect` fetch: Promise harus stabil (cache), atau kamu mendapat loop.

`use(context)` alternatif `useContext` yang boleh dipanggil setelah `if` dalam batasan tertentu — tetap pelajari aturan Hooks klasik dulu.

Fitur Activity / View Transition berkembang di dokumentasi resmi. Untuk ensiklopedia ini, kuasai Portal, `lazy`, Suspense, dan Error Boundary terlebih dahulu.

**Biasanya digabungkan dengan:** membaca [react.dev](https://react.dev/) sesuai versi `package.json` proyekmu.

## Kesalahan umum bab ini

- **Modal tanpa portal** terpotong `overflow` induk.
- **Portal ke `document.body` saat SSR tanpa penjagaan.**
- **`lazy` tanpa `Suspense`.** React melempar.
- **Satu Suspense untuk seluruh halaman** berkedip semuanya.
- **Mengira `useEffect` fetch memicu Suspense.**
- **Error Boundary function component tanpa library.** Tidak menangkap.
- **Mengandalkan Boundary untuk error `onClick`.**
- **Lupa mengembalikan fokus saat modal tutup.**

Latihan: modal konfirmasi hapus (portal + Escape + kunci scroll) dan halaman yang `lazy` memuat komponen chart palsu di dalam Suspense + Error Boundary.

## Toast dan tumpukan portal

**Untuk apa:** menampilkan pesan singkat di sudut layar tanpa menggeser layout halaman.

```jsx
import { createContext, useCallback, useContext, useState } from "react";
import { createPortal } from "react-dom";

const ToastContext = createContext(null);

export function ToastProvider({ children }) {
  const [pesan, setPesan] = useState([]);

  const tampil = useCallback((teks) => {
    const id = crypto.randomUUID();
    setPesan((lama) => [...lama, { id, teks }]);
    setTimeout(() => {
      setPesan((lama) => lama.filter((x) => x.id !== id));
    }, 3000);
  }, []);

  return (
    <ToastContext.Provider value={tampil}>
      {children}
      {createPortal(
        <div className="toast-rak" aria-live="polite">
          {pesan.map((x) => (
            <p key={x.id} className="toast">{x.teks}</p>
          ))}
        </div>,
        document.body
      )}
    </ToastContext.Provider>
  );
}

export function useToast() {
  const tampil = useContext(ToastContext);
  if (!tampil) throw new Error("useToast di dalam ToastProvider");
  return tampil;
}
```

`aria-live="polite"` membacakan toast ke pembaca layar tanpa merebut fokus. Timer di Provider harus dibersihkan saat unmount jika tugas menuntut ketelitian (simpan id timeout di ref).

**Biasanya digabungkan dengan:** Context, `createPortal`, dan form “Tersimpan”.

## Preload lazy

**Untuk apa:** mulai mengunduh chunk sebelum pengguna membuka tab, agar fallback singkat.

```jsx
const Editor = lazy(() => import("./Editor.jsx"));

function tautkanEditor() {
  import("./Editor.jsx");
}

export default function App() {
  const [buka, setBuka] = useState(false);
  return (
    <>
      <button
        type="button"
        onMouseEnter={tautkanEditor}
        onFocus={tautkanEditor}
        onClick={() => setBuka(true)}
      >
        Buka editor
      </button>
      {buka && (
        <Suspense fallback={<p>Memuat editor…</p>}>
          <Editor />
        </Suspense>
      )}
    </>
  );
}
```

`import()` yang sama di-cache bundler: hover dan `lazy` berbagi unduhan. Jangan preload semua chunk di awal; itu mengalahkan tujuan memecah.

**Biasanya digabungkan dengan:** `lazy`, rute yang bisa ditebak, dan jaringan hemat.

## Error di handler vs error di render

**Untuk apa:** tidak salah tempat memasang jaring.

```jsx
function TombolBerbahaya() {
  function handleKlik() {
    try {
      JSON.parse("bukan-json");
    } catch {
      alert("Data rusak");
    }
  }
  return <button type="button" onClick={handleKlik}>Uji</button>;
}

function RenderBerbahaya({ data }) {
  if (!data.nama) {
    throw new Error("Data produk tidak lengkap");
  }
  return <h1>{data.nama}</h1>;
}
```

`handleKlik` tidak tertangkap Error Boundary. `RenderBerbahaya` tertangkap jika `data` jelek saat render. Untuk fetch, lebih baik `status === "gagal"` daripada `throw` di render — kecuali kamu sengaja memakai batas error untuk widget opsional.

**Biasanya digabungkan dengan:** [file 10](10-fetch-pola-loading-error.md) untuk error jaringan, Boundary untuk bug render.

## Nested modal dan z-index

**Untuk apa:** dua overlay tidak saling menutup secara tidak sengaja.

Portal ke `body` menempatkan modal sebagai anak terakhir `body` secara default, sehingga biasanya di atas konten. Dua modal sekaligus: yang belakangan di DOM biasanya di atas. Kendalikan dengan:

- hanya satu modal “aktif”
- atau `z-index` terencana di CSS
- atau satu host `#modal-root` di `index.html`

Event bubbling React tetap ke induk React, bukan ke visual `body`. Klik overlay modal dalam bisa sampai ke handler overlay luar jika tidak `stopPropagation` — uji sebelum mengumpulkan.

**Biasanya digabungkan dengan:** CSS stacking context, dan menolak membuka dua dialog konfirmasi sekaligus.
