# 09 — Custom Hook dan polanya

[← Context](08-context-useContext-useId.md) · [Daftar](README.md) · [Lanjut: fetch →](10-fetch-pola-loading-error.md)

Custom Hook adalah fungsi yang namanya diawali `use` dan memanggil Hook lain. Tujuannya memindahkan **logika berstate** agar tidak diduplikasi, bukan memindahkan JSX.

## Daftar isi

- [Aturan nama dan isi](#aturan-nama-dan-isi)
- [useToggle](#usetoggle)
- [useBoolean](#useboolean)
- [useInput (controlled)](#useinput-controlled)
- [useLocalStorage](#uselocalstorage)
- [usePrevious](#useprevious)
- [useInterval](#useinterval)
- [useDebouncedValue](#usedebouncedvalue)
- [useMediaQuery](#usemediaquery)
- [useOnlineStatus](#useonlinestatus)
- [useFetch ringkas](#usefetch-ringkas)
- [Hook yang mengembalikan action](#hook-yang-mengembalikan-action)
- [Komposisi Hook](#komposisi-hook)
- [Bukan custom Hook](#bukan-custom-hook)
- [Menguji secara informal](#menguji-secara-informal)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [useEscape dan useOnClickOutside](#useescape-dan-useonclickoutside)
- [Nilai kembali: array vs object](#nilai-kembali-array-vs-object)
- [Jangan berbagi state lewat modul + useState](#jangan-berbagi-state-lewat-modul--usestate)

## Aturan nama dan isi

**Untuk apa:** membuat fungsi yang boleh memanggil `useState`/`useEffect` dan tetap mematuhi aturan Hooks.

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

Nama **harus** diawali `use`. Tanpa itu, linter tidak bisa menegakkan aturan, dan pembaca tidak tahu bahwa urutan panggilan penting.

Di dalam custom Hook:

- panggil Hooks di tingkat atas, tidak di dalam `if`
- boleh memanggil custom Hook lain
- boleh menerima argument dan mengembalikan apa saja (array, object, nilai tunggal)

Custom Hook **tidak** berbagi state antar komponen secara otomatis. Setiap pemanggil mendapat state sendiri. Untuk berbagi, naikkan state, pakai Context, atau store eksternal.

**Biasanya digabungkan dengan:** beberapa komponen yang punya logika sama, dan file `hooks/useToggle.js`. [Reusing logic with custom Hooks](https://react.dev/learn/reusing-logic-with-custom-hooks).

## useToggle

**Untuk apa:** boolean yang dibalik: menu, modal, accordion.

```jsx
import { useState, useCallback } from "react";

export function useToggle(awal = false) {
  const [nyala, setNyala] = useState(awal);
  const toggle = useCallback(() => {
    setNyala((lama) => !lama);
  }, []);
  const setTrue = useCallback(() => setNyala(true), []);
  const setFalse = useCallback(() => setNyala(false), []);
  return { nyala, toggle, setTrue, setFalse, setNyala };
}

export default function App() {
  const menu = useToggle();
  return (
    <>
      <button type="button" onClick={menu.toggle}>
        {menu.nyala ? "Tutup" : "Buka"} menu
      </button>
      {menu.nyala && <nav>Tautan…</nav>}
    </>
  );
}
```

Mengembalikan object lebih mudah diperluas daripada `[nyala, toggle]`. Array tetap bagus jika hanya dua nilai, karena bisa dinamai ulang: `const [terbuka, toggle] = useToggle()`.

**Biasanya digabungkan dengan:** `createPortal` untuk modal, dan `aria-expanded` pada tombol.

## useBoolean

**Untuk apa:** nama lain yang lebih eksplisit untuk flag, tanpa `toggle` jika kamu jarang membalik.

```jsx
export function useBoolean(awal = false) {
  const [value, setValue] = useState(awal);
  return {
    value,
    on: () => setValue(true),
    off: () => setValue(false),
    set: setValue,
  };
}
```

Cocok untuk `sedangKirim`, `terlihat`, `sudahSetuju`. Jangan membuat Hook baru jika `useState(false)` di satu tempat sudah cukup. Custom Hook berharga saat pola terulang atau API-nya membantu keterbacaan di banyak file.

**Biasanya digabungkan dengan:** form submit, toast, dan overlay.

## useInput (controlled)

**Untuk apa:** mengurangi boilerplate `value` + `onChange` pada form latihan.

```jsx
import { useState } from "react";

export function useInput(awal = "") {
  const [value, setValue] = useState(awal);
  const onChange = (event) => setValue(event.target.value);
  const reset = () => setValue(awal);
  return { value, onChange, reset, setValue };
}

export default function App() {
  const nama = useInput("");
  const kota = useInput("Bandung");

  function kirim(event) {
    event.preventDefault();
    console.log(nama.value, kota.value);
    nama.reset();
  }

  return (
    <form onSubmit={kirim}>
      <input aria-label="Nama" {...nama} />
      <input aria-label="Kota" {...kota} />
      <button type="submit">Kirim</button>
    </form>
  );
}
```

Hati-hati `reset` memakai `awal` dari render pertama jika `awal` berubah. Untuk form edit, `key` pada form atau `setValue` dari data baru lebih jelas.

Jangan menyebar `{...nama}` ke `<input>` jika object membawa `reset`/`setValue`: atribut DOM tidak valid. Ambil yang perlu:

```jsx
<input value={nama.value} onChange={nama.onChange} />
```

**Biasanya digabungkan dengan:** validasi, dan form yang fieldnya banyak tetapi sederhana.

## useLocalStorage

**Untuk apa:** menyimpan state yang bertahan setelah refresh, dengan sinkronisasi ke `localStorage`.

```jsx
import { useEffect, useState } from "react";

export function useLocalStorage(kunci, awal) {
  const [nilai, setNilai] = useState(() => {
    if (typeof window === "undefined") return awal;
    try {
      const mentah = window.localStorage.getItem(kunci);
      return mentah !== null ? JSON.parse(mentah) : awal;
    } catch {
      return awal;
    }
  });

  useEffect(() => {
    try {
      window.localStorage.setItem(kunci, JSON.stringify(nilai));
    } catch {
      // kuota penuh atau mode privat ketat
    }
  }, [kunci, nilai]);

  return [nilai, setNilai];
}
```

Inisialisasi malas membaca penyimpanan sekali. Effect menulis saat `nilai` berubah.

Keterbatasan:

- hanya string via JSON; `Date` dan `Map` perlu perawatan
- tab lain tidak otomatis tersinkron kecuali kamu listen `storage`
- data terlihat ke JavaScript di halaman — bukan tempat token rahasia
- SSR: `window` tidak ada; argument `awal` dipakai di server

Untuk sinkron antar-tab, tambahkan `useEffect` listener `storage` atau `useSyncExternalStore`.

**Biasanya digabungkan dengan:** tema, draft form, dan preferensi UI — bukan sesi login yang seharusnya httpOnly cookie.

## usePrevious

**Untuk apa:** mengingat nilai render sebelumnya (animasi, perbandingan).

```jsx
import { useEffect, useRef } from "react";

export function usePrevious(nilai) {
  const ref = useRef();
  useEffect(() => {
    ref.current = nilai;
  }, [nilai]);
  return ref.current;
}
```

Render pertama mengembalikan `undefined`. Setelah itu, nilai lama.

Seringkali kamu **tidak** membutuhkannya: hitung dari state sekarang, atau pakai `key` untuk reset. Pakai jika benar-benar perlu “dari X menjadi Y”.

**Biasanya digabungkan dengan:** transisi CSS, dan log debug perubahan props.

## useInterval

**Untuk apa:** `setInterval` yang mengikuti callback terbaru tanpa memasang ulang interval setiap render.

```jsx
import { useEffect, useRef } from "react";

export function useInterval(callback, delay) {
  const cbRef = useRef(callback);
  cbRef.current = callback;

  useEffect(() => {
    if (delay === null) return undefined;
    const id = setInterval(() => {
      cbRef.current();
    }, delay);
    return () => clearInterval(id);
  }, [delay]);
}
```

`delay === null` menjeda. Callback di ref menghindari `[callback]` yang berubah setiap render (jika induk tidak `useCallback`).

```jsx
export default function App() {
  const [n, setN] = useState(0);
  const [jalan, setJalan] = useState(true);
  useInterval(() => setN((x) => x + 1), jalan ? 1000 : null);
  return (
    <>
      <p>{n}</p>
      <button type="button" onClick={() => setJalan((v) => !v)}>
        {jalan ? "Jeda" : "Lanjut"}
      </button>
    </>
  );
}
```

**Biasanya digabungkan dengan:** countdown, polling lunak (lebih baik refetch sadar), dan cleanup otomatis.

## useDebouncedValue

**Untuk apa:** menunda nilai hingga pengguna berhenti mengetik, biasanya sebelum fetch.

```jsx
import { useEffect, useState } from "react";

export function useDebouncedValue(nilai, jeda = 300) {
  const [tertinggal, setTertinggal] = useState(nilai);

  useEffect(() => {
    const id = setTimeout(() => setTertinggal(nilai), jeda);
    return () => clearTimeout(id);
  }, [nilai, jeda]);

  return tertinggal;
}
```

```jsx
const [kata, setKata] = useState("");
const kataDebounce = useDebouncedValue(kata, 400);

useEffect(() => {
  if (!kataDebounce.trim()) return;
  // fetch `/api/cari?q=`
}, [kataDebounce]);
```

Input tetap memakai `kata` agar terasa instan. Request memakai `kataDebounce`.

Ini berbeda dari `useDeferredValue`: ada jeda waktu tetap, dan ada render tambahan saat timer selesai.

**Biasanya digabungkan dengan:** [file 10](10-fetch-pola-loading-error.md), autocomplete, dan `AbortController`.

## useMediaQuery

**Untuk apa:** membungkus `matchMedia` agar pemakaian di komponen satu baris.

```jsx
import { useSyncExternalStore } from "react";

export function useMediaQuery(query) {
  return useSyncExternalStore(
    (onStoreChange) => {
      const mql = window.matchMedia(query);
      mql.addEventListener("change", onStoreChange);
      return () => mql.removeEventListener("change", onStoreChange);
    },
    () => window.matchMedia(query).matches,
    () => false
  );
}
```

Lihat penjelasan SSR di [file 07](07-useReducer-useSyncExternalStore.md). Utamakan CSS untuk layout.

**Biasanya digabungkan dengan:** merender peta/chart hanya di layar lebar, bukan untuk menyembunyikan menu (CSS cukup).

## useOnlineStatus

**Untuk apa:** menampilkan banner “kamu offline”.

```jsx
import { useSyncExternalStore } from "react";

export function useOnlineStatus() {
  return useSyncExternalStore(
    (onChange) => {
      window.addEventListener("online", onChange);
      window.addEventListener("offline", onChange);
      return () => {
        window.removeEventListener("online", onChange);
        window.removeEventListener("offline", onChange);
      };
    },
    () => navigator.onLine,
    () => true
  );
}

export function BannerJaringan() {
  const online = useOnlineStatus();
  if (online) return null;
  return <p role="status">Tidak ada koneksi. Beberapa aksi gagal.</p>;
}
```

`navigator.onLine` bisa “online” secara teknis tanpa internet sungguhan. Banner adalah isyarat, bukan jaminan.

**Biasanya digabungkan dengan:** form antrian, dan menonaktifkan tombol “Simpan” secara sopan.

## useFetch ringkas

**Untuk apa:** pola minimal GET + status. Versi lengkap ada di file 10.

```jsx
import { useEffect, useState } from "react";

export function useFetch(url) {
  const [data, setData] = useState(null);
  const [status, setStatus] = useState(url ? "memuat" : "idle");
  const [error, setError] = useState(null);

  useEffect(() => {
    if (!url) {
      setStatus("idle");
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
  }, [url]);

  return { data, status, error };
}
```

Keterbatasan yang disadari: tidak ada cache, tidak ada mutate, `url` string harus lengkap. Untuk aplikasi besar, library data atau Server Component lebih tepat. Untuk praktikum, pola ini mengajarkan dependensi dan abort.

**Biasanya digabungkan dengan:** empat tampilan daftar, dan `url` yang dihitung dari id: `` `/api/produk/${id}` ``.

## Hook yang mengembalikan action

**Untuk apa:** menyembunyikan `dispatch` di API yang terbaca seperti bahasa domain.

```jsx
import { useReducer, useCallback } from "react";

function reducer(state, action) {
  switch (action.type) {
    case "push":
      return [...state, action.item];
    case "remove":
      return state.filter((x) => x.id !== action.id);
    case "clear":
      return [];
    default:
      return state;
  }
}

export function useDaftar(awal = []) {
  const [item, dispatch] = useReducer(reducer, awal);
  const tambah = useCallback((baris) => {
    dispatch({ type: "push", item: baris });
  }, []);
  const hapus = useCallback((id) => {
    dispatch({ type: "remove", id });
  }, []);
  const kosongkan = useCallback(() => dispatch({ type: "clear" }), []);
  return { item, tambah, hapus, kosongkan };
}
```

Komponen pemakai tidak perlu tahu bentuk aksi. Kamu bisa mengganti implementasi ke `useState` nanti.

**Biasanya digabungkan dengan:** Context yang hanya mengekspor Hook, dan tes reducer.

## Komposisi Hook

**Untuk apa:** membangun Hook khusus dari Hook kecil.

```jsx
export function useCariProduk(semua) {
  const kata = useInput("");
  const debounced = useDebouncedValue(kata.value, 250);
  const hasil = semua.filter((p) =>
    p.nama.toLowerCase().includes(debounced.toLowerCase())
  );
  return { kata, hasil, debounced };
}
```

Filter sinkron tidak perlu Effect. Hook ini menggabungkan input dan nilai tertunda.

Jangan menggabungkan terlalu banyak: `useHalamanToko` yang fetch, filter, keranjang, dan tema sulit diuji. Satu Hook ≈ satu masalah.

**Biasanya digabungkan dengan:** file 02 (input), file 03 (filter), file 10 (jika hasil dari server).

## Bukan custom Hook

**Untuk apa:** tidak memaksa prefix `use` pada fungsi biasa.

```jsx
export function formatRupiah(angka) {
  return `Rp${angka.toLocaleString("id-ID")}`;
}

export function hitungTotal(baris) {
  return baris.reduce((n, b) => n + b.harga * b.qty, 0);
}
```

Fungsi murni tanpa Hook **jangan** bernama `useFormatRupiah`. Nama `use` menjanjikan pemanggilan Hook dan aturan urutan.

Komponen yang mengembalikan JSX adalah komponen (`function Kartu`), bukan Hook.

Hook yang hanya memanggil `useState` sekali dan dipakai di satu file boleh tetap inline di komponen sampai terulang.

**Biasanya digabungkan dengan:** memisahkan `utils/` dari `hooks/`.

## Menguji secara informal

**Untuk apa:** memastikan Hook benar tanpa framework tes lengkap.

Reducer dan fungsi murni: panggil langsung.

Hook: pakai di komponen kecil `App` lalu klik. Atau React Testing Library `renderHook` jika proyek sudah memasangnya.

Cek yang sering dilupakan:

- unmount tidak melempar (cleanup fetch/timer)
- mengubah argument (`url`, `delay`) memicu ulang
- dua komponen memakai Hook yang sama tidak berbagi state

**Biasanya digabungkan dengan:** Strict Mode (ganda mount), dan React DevTools.

## Kesalahan umum bab ini

- **Nama tidak diawali `use` tetapi memanggil `useState`.**
- **Mengira dua `useToggle()` berbagi boolean.**
- **`if (x) useToggle()`.**
- **Custom Hook mengembalikan JSX besar** — itu komponen.
- **`useLocalStorage` menyimpan token rahasia.**
- **`useFetch` tanpa abort.**
- **Hook “dewa” yang melakukan semua hal halaman.**
- **Menyebar seluruh object Hook ke DOM.**

Latihan: pindahkan toggle menu, debounce cari, dan localStorage tema ke tiga Hook. Pakai semuanya di satu `App`.

## useEscape dan useOnClickOutside

**Untuk apa:** dua pelengkap modal yang sering diduplikasi.

```jsx
import { useEffect } from "react";

export function useEscape(aktif, onEscape) {
  useEffect(() => {
    if (!aktif) return undefined;
    function onKey(event) {
      if (event.key === "Escape") onEscape();
    }
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, [aktif, onEscape]);
}

export function useOnClickOutside(ref, aktif, onLuar) {
  useEffect(() => {
    if (!aktif) return undefined;
    function onPointer(event) {
      if (ref.current && !ref.current.contains(event.target)) {
        onLuar();
      }
    }
    document.addEventListener("pointerdown", onPointer);
    return () => document.removeEventListener("pointerdown", onPointer);
  }, [ref, aktif, onLuar]);
}
```

Stabilkan `onEscape`/`onLuar` dengan `useCallback` atau ref (lihat file 04) agar listener tidak dipasang ulang setiap render induk.

**Biasanya digabungkan dengan:** [portal](11-portal-suspense-error-boundary.md), `useToggle`, dan `useRef` pada kotak dialog.

## Nilai kembali: array vs object

**Untuk apa:** memilih bentuk API Hook.

```jsx
// mirip useState, mudah rename
const [nyala, toggle] = useToggle();

// banyak field, nama tetap
const { data, status, error, refresh } = useResource(url);
```

Array cocok 2–3 slot berurutan seperti React. Object cocok 4+ field agar pemakai tidak menghafal posisi. Jangan mengembalikan object baru yang ditaruh di dependensi Effect pemakai tanpa sadar: `{ data, status }` baru setiap render. Itu normal; pemakai harus bergantung pada `data`/`status`, bukan pada object pembungkus, atau kamu memoize return (jarang perlu).

**Biasanya digabungkan dengan:** dokumentasi singkat di komentar atas file Hook.

## Jangan berbagi state lewat modul + useState

**Untuk apa:** menghindari “singleton palsu”.

```jsx
let global = 0;
export function usePenghitungGlobal() {
  const [, setTick] = useState(0);
  function tambah() {
    global += 1;
    setTick((n) => n + 1);
  }
  return [global, tambah];
}
```

Pola ini rapuh (tidak ikut concurrent, sulit tes, tidak ter-scope). Untuk state bersama: Context, store + `useSyncExternalStore`, atau naikkan ke induk.

Custom Hook biasa = **cetakan** state, bukan satu instance global.

**Biasanya digabungkan dengan:** [file 08](08-context-useContext-useId.md) jika memang harus berbagi.
