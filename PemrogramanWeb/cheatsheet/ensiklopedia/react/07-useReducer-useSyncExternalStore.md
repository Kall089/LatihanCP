# 07 — useReducer dan useSyncExternalStore

[← Memo dan transisi](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md) · [Daftar](README.md) · [Lanjut: Context →](08-context-useContext-useId.md)

`useReducer` mengelola state lewat **aksi** dan fungsi murni. `useSyncExternalStore` membaca data yang hidup di luar React (browser API, store) dengan cara yang aman untuk concurrent rendering.

## Daftar isi

- [Kapan useReducer](#kapan-usereducer)
- [Bentuk dasar](#bentuk-dasar)
- [Aksi bertipe dan payload](#aksi-bertipe-dan-payload)
- [Inisialisasi malas](#inisialisasi-malas)
- [Reducer murni](#reducer-murni)
- [Keranjang belanja](#keranjang-belanja)
- [Form bertahap](#form-bertahap)
- [useReducer + Context](#usereducer--context)
- [useSyncExternalStore](#usesyncexternalstore)
- [Subscribe ke matchMedia](#subscribe-ke-matchmedia)
- [Store mini buatan sendiri](#store-mini-buatan-sendiri)
- [getServerSnapshot](#getserversnapshot)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [useReducer vs useState: tabel keputusan](#usereducer-vs-usestate-tabel-keputusan)
- [Dispatch di event vs di Effect](#dispatch-di-event-vs-di-effect)
- [Snapshot identity pada useSyncExternalStore](#snapshot-identity-pada-usesyncexternalstore)

## Kapan useReducer

**Untuk apa:** menggantikan beberapa `useState` yang saling terkait dan sulit dibaca.

Pindah ke reducer jika:

- satu interaksi mengubah banyak field sekaligus
- ada banyak aksi bernama (`tambah`, `hapus`, `reset`, `centangSemua`)
- logika update ingin diuji terpisah dari JSX
- state berbentuk object dengan aturan (tidak boleh stok negatif)

Tetap di `useState` jika:

- satu boolean, satu string, satu angka
- update hanya `setX(nilaiBaru)` tanpa aturan

`useReducer` bukan Redux. Tidak ada store global otomatis. Itu Hook lokal, sama seperti `useState`, hanya cara menulis updatenya berbeda.

**Biasanya digabungkan dengan:** Context untuk membagikan `[state, dispatch]`, dan tes unit pada fungsi `reducer`. [useReducer](https://react.dev/reference/react/useReducer).

## Bentuk dasar

**Untuk apa:** melihat signature dan alur data.

```jsx
import { useReducer } from "react";

function reducer(state, action) {
  switch (action.type) {
    case "tambah":
      return { ...state, jumlah: state.jumlah + 1 };
    case "kurang":
      return { ...state, jumlah: Math.max(0, state.jumlah - 1) };
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
      <button type="button" onClick={() => dispatch({ type: "kurang" })}>-</button>
      <button type="button" onClick={() => dispatch({ type: "reset" })}>Reset</button>
    </>
  );
}
```

`dispatch(action)` meminta React memanggil `reducer(stateSekarang, action)` lalu merender jika hasilnya berbeda referensi/nilai. `dispatch` identitasnya stabil: aman diletakkan di dependensi kosong atau Context.

Jangan memanggil `reducer` sendiri di handler. Kirim aksi.

**Biasanya digabungkan dengan:** tombol, form, dan custom Hook `usePenghitung`.

## Aksi bertipe dan payload

**Untuk apa:** membawa data bersama nama aksi.

```jsx
function reducer(state, action) {
  switch (action.type) {
    case "setJumlah":
      return { ...state, jumlah: action.payload };
    case "tambahSebanyak":
      return { ...state, jumlah: state.jumlah + action.n };
    default:
      throw new Error(`Aksi tidak dikenal: ${action.type}`);
  }
}

dispatch({ type: "setJumlah", payload: 10 });
dispatch({ type: "tambahSebanyak", n: 5 });
```

Konvensi `type` + `payload` umum, tetapi tidak wajib. Yang penting reducer bisa membaca field yang kamu kirim.

`throw` pada aksi tidak dikenal membantu menemukan typo. Mengembalikan `state` diam-diam menyembunyikan bug.

TypeScript (opsional) memakai union:

```ts
type Aksi =
  | { type: "setJumlah"; payload: number }
  | { type: "tambahSebanyak"; n: number };
```

Di JavaScript, tetap tuliskan `type` sebagai string tetap.

**Biasanya digabungkan dengan:** helper `function tambahSebanyak(n) { dispatch({ type: "tambahSebanyak", n }); }` agar JSX pendek.

## Inisialisasi malas

**Untuk apa:** menghitung state awal sekali, terutama dari props atau penyimpanan.

```jsx
function init(awal) {
  return { jumlah: awal, riwayat: [awal] };
}

const [state, dispatch] = useReducer(reducer, props.awal, init);
```

Bentuk: `useReducer(reducer, argumenInit, init)`. React memanggil `init(argumenInit)` sekali. Berguna untuk `JSON.parse` dari localStorage atau membentuk struktur dari props.

Tanpa fungsi `init`, argument kedua adalah state awal langsung: `useReducer(reducer, { jumlah: 0 })`.

Jika props `awal` berubah kemudian dan kamu ingin mereset, pakai `key` pada komponen, bukan mengulang `init` otomatis.

**Biasanya digabungkan dengan:** localStorage, form edit dari data server, dan `key={id}`.

## Reducer murni

**Untuk apa:** menjaga reducer mudah diuji dan aman jika React memanggilnya dua kali.

```jsx
function reducer(state, action) {
  switch (action.type) {
    case "tambahItem":
      return {
        ...state,
        item: [...state.item, action.item],
      };
    default:
      return state;
  }
}
```

Reducer **murni**:

- tidak menulis ke luar (tidak `fetch`, tidak `localStorage.setItem`)
- tidak memutasi `state` (`state.item.push` dilarang)
- mengembalikan state baru atau state lama yang sama

Side effect diletakkan di handler setelah `dispatch`, atau di Effect yang bereaksi terhadap state, atau di middleware store eksternal.

Uji tanpa merender:

```jsx
const awal = { item: [] };
const hasil = reducer(awal, { type: "tambahItem", item: { id: 1, nama: "Buku" } });
console.assert(hasil.item.length === 1);
console.assert(awal.item.length === 0);
```

**Biasanya digabungkan dengan:** tes unit, Immer jika imutasi manual melelahkan (`useImmerReducer`), dan Strict Mode.

## Keranjang belanja

**Untuk apa:** contoh reducer yang mengubah array object.

```jsx
import { useReducer } from "react";

function reducer(state, action) {
  switch (action.type) {
    case "tambah": {
      const ada = state.baris.find((b) => b.id === action.produk.id);
      if (ada) {
        return {
          baris: state.baris.map((b) =>
            b.id === action.produk.id ? { ...b, qty: b.qty + 1 } : b
          ),
        };
      }
      return {
        baris: [...state.baris, { ...action.produk, qty: 1 }],
      };
    }
    case "ubahQty":
      return {
        baris: state.baris
          .map((b) => (b.id === action.id ? { ...b, qty: action.qty } : b))
          .filter((b) => b.qty > 0),
      };
    case "kosongkan":
      return { baris: [] };
    default:
      return state;
  }
}

export default function App() {
  const [state, dispatch] = useReducer(reducer, { baris: [] });
  const total = state.baris.reduce((n, b) => n + b.harga * b.qty, 0);

  return (
    <>
      <button
        type="button"
        onClick={() =>
          dispatch({
            type: "tambah",
            produk: { id: 1, nama: "Buku", harga: 45000 },
          })
        }
      >
        Tambah Buku
      </button>
      <ul>
        {state.baris.map((b) => (
          <li key={b.id}>
            {b.nama} × {b.qty}
            <button
              type="button"
              onClick={() => dispatch({ type: "ubahQty", id: b.id, qty: b.qty - 1 })}
            >
              −
            </button>
          </li>
        ))}
      </ul>
      <p>Total Rp{total.toLocaleString("id-ID")}</p>
    </>
  );
}
```

`total` dihitung saat render, bukan disimpan di state. Kurung kurawal pada `case "tambah": {` membuat `const ada` tidak bocor ke case lain.

**Biasanya digabungkan dengan:** Context keranjang, `localStorage` di Effect, dan halaman checkout.

## Form bertahap

**Untuk apa:** wizard yang langkah dan datanya di satu reducer.

```jsx
const awal = {
  langkah: 1,
  nama: "",
  alamat: "",
  error: "",
};

function reducer(state, action) {
  switch (action.type) {
    case "isi":
      return { ...state, [action.field]: action.nilai, error: "" };
    case "lanjut":
      if (state.langkah === 1 && !state.nama.trim()) {
        return { ...state, error: "Nama wajib." };
      }
      if (state.langkah === 2 && !state.alamat.trim()) {
        return { ...state, error: "Alamat wajib." };
      }
      return { ...state, langkah: state.langkah + 1, error: "" };
    case "kembali":
      return { ...state, langkah: Math.max(1, state.langkah - 1), error: "" };
    default:
      return state;
  }
}
```

Validasi yang hanya bergantung pada state cocok di reducer. Validasi async (cek email ke server) tetap di handler: `await cek()`, lalu `dispatch({ type: "error", pesan })`.

**Biasanya digabungkan dengan:** render bersyarat langkah, `aria-current`, dan tombol Kembali/Lanjut.

## useReducer + Context

**Untuk apa:** membagikan state rumit ke pohon yang dalam tanpa props berantai.

```jsx
import { createContext, useContext, useReducer } from "react";

const KeranjangState = createContext(null);
const KeranjangDispatch = createContext(null);

function reducer(state, action) {
  switch (action.type) {
    case "tambah":
      return { jumlah: state.jumlah + 1 };
    default:
      return state;
  }
}

export function KeranjangProvider({ children }) {
  const [state, dispatch] = useReducer(reducer, { jumlah: 0 });
  return (
    <KeranjangState.Provider value={state}>
      <KeranjangDispatch.Provider value={dispatch}>
        {children}
      </KeranjangDispatch.Provider>
    </KeranjangState.Provider>
  );
}

export function useKeranjang() {
  const state = useContext(KeranjangState);
  if (!state) throw new Error("useKeranjang di dalam provider");
  return state;
}

export function useKeranjangDispatch() {
  const dispatch = useContext(KeranjangDispatch);
  if (!dispatch) throw new Error("useKeranjangDispatch di dalam provider");
  return dispatch;
}
```

Memisah state dan dispatch mencegah komponen yang hanya memanggil `dispatch` rerender saat state berubah — jika kamu juga mem-`memo` mereka. `dispatch` stabil.

Jangan memasukkan reducer ke Context; yang dibagikan hasil dan pengirim aksi.

**Biasanya digabungkan dengan:** [file 08](08-context-useContext-useId.md), custom Hook, dan `memo` pada tombol aksi.

## useSyncExternalStore

**Untuk apa:** berlangganan data di luar React agar pembacaan konsisten saat render disela (concurrent).

```jsx
import { useSyncExternalStore } from "react";

function subscribe(callback) {
  window.addEventListener("online", callback);
  window.addEventListener("offline", callback);
  return () => {
    window.removeEventListener("online", callback);
    window.removeEventListener("offline", callback);
  };
}

function getSnapshot() {
  return navigator.onLine;
}

function getServerSnapshot() {
  return true;
}

export default function App() {
  const online = useSyncExternalStore(subscribe, getSnapshot, getServerSnapshot);
  return <p>{online ? "Online" : "Offline"}</p>;
}
```

Tiga argument:

1. `subscribe(callback)` — pasang listener, kembalikan unsubscribe
2. `getSnapshot()` — baca nilai sekarang di client
3. `getServerSnapshot()` — nilai saat SSR, wajib jika ada prerender

`getSnapshot` harus mengembalikan nilai yang `Object.is` sama jika data tidak berubah. Mengembalikan object baru setiap panggilan memicu loop.

Jangan memakai `useEffect` + `setState` untuk `navigator.onLine` jika kamu bisa memakai Hook ini: lebih tahan tearing (bagian UI melihat snapshot berbeda).

**Biasanya digabungkan dengan:** `matchMedia`, `localStorage` (hati-hati tab lain), Redux/`useStore`, Zustand. [useSyncExternalStore](https://react.dev/reference/react/useSyncExternalStore).

## Subscribe ke matchMedia

**Untuk apa:** merespons breakpoint tanpa CSS-only, misalnya memilih komponen berbeda.

```jsx
import { useSyncExternalStore } from "react";

function subscribeMedia(query, callback) {
  const mql = window.matchMedia(query);
  mql.addEventListener("change", callback);
  return () => mql.removeEventListener("change", callback);
}

function useMediaQuery(query) {
  return useSyncExternalStore(
    (callback) => subscribeMedia(query, callback),
    () => window.matchMedia(query).matches,
    () => false
  );
}

export default function App() {
  const sempit = useMediaQuery("(max-width: 640px)");
  return <p>{sempit ? "Tampilan sempit" : "Tampilan lebar"}</p>;
}
```

`getServerSnapshot` mengembalikan `false` agar HTML server deterministik. Client bisa menyesuaikan setelah hidrasi; siapkan tampilan yang tidak patah jika salah tebak.

Untuk layout, utamakan CSS. Hook ini untuk logika (tidak merender peta berat di mobile).

**Biasanya digabungkan dengan:** custom Hook, CSS sebagai jalur utama, dan `getServerSnapshot`.

## Store mini buatan sendiri

**Untuk apa:** memahami cara store eksternal terhubung, bukan untuk mengganti `useState` sehari-hari.

```jsx
import { useSyncExternalStore } from "react";

function buatStore(nilaiAwal) {
  let nilai = nilaiAwal;
  const pendengar = new Set();
  return {
    get() {
      return nilai;
    },
    set(berikutnya) {
      nilai = typeof berikutnya === "function" ? berikutnya(nilai) : berikutnya;
      pendengar.forEach((fn) => fn());
    },
    subscribe(fn) {
      pendengar.add(fn);
      return () => pendengar.delete(fn);
    },
  };
}

const temaStore = buatStore("terang");

export function useTema() {
  return useSyncExternalStore(temaStore.subscribe, temaStore.get, temaStore.get);
}

export function setTema(nilai) {
  temaStore.set(nilai);
}
```

Store hidup di modul, di luar komponen. Beberapa pohon React atau bahkan non-React bisa membaca. Itu berbeda dari Context: tidak perlu provider, tetapi lebih sulit men-scope per subtree (misalnya dua toko di satu halaman).

Untuk tugas kuliah, Context + `useReducer` biasanya cukup. Pakai store eksternal jika library sudah menyediakannya atau data harus di luar React.

**Biasanya digabungkan dengan:** `getServerSnapshot` yang sama jika nilai awal diketahui, dan menahan godaan membuat Redux mini tanpa kebutuhan.

## getServerSnapshot

**Untuk apa:** mencegah error hidrasi ketika snapshot client tidak ada di server.

```jsx
useSyncExternalStore(
  subscribe,
  () => window.innerWidth,
  () => 1024
);
```

Server tidak punya `window`. Tanpa argument ketiga, React 18+ memperingatkan atau melempar di lingkungan SSR.

Pilih snapshot server yang **tetap** untuk semua request, atau sesuai cookie/UA yang memang kamu baca di server. Jangan mengembalikan `Date.now()` atau nilai acak.

Setelah hidrasi, client memakai `getSnapshot` sungguhan. Boleh terjadi penyesuaian visual; kurangi geseran dengan CSS yang netral.

**Biasanya digabungkan dengan:** Next.js App Router, `useEffect` sebagai alternatif kasar (kedip lebih mungkin), dan dokumentasi library store.

## Kesalahan umum bab ini

- **Memutasi `state` di reducer.** `push` pada array state.
- **Fetch di dalam reducer.**
- **Melupakan `default` atau `throw` pada aksi tak dikenal.**
- **Menghitung `total` ke dalam state lewat aksi terpisah** padahal bisa dari `baris`.
- **`getSnapshot` mengembalikan `{ ...data }` baru setiap kali.**
- **`useEffect` + `setState` untuk `matchMedia` padahal Hook store lebih tepat.**
- **Membuat store global untuk state yang hanya dipakai satu form.**
- **Mengira `useReducer` otomatis mencegah rerender.** Tidak; itu hanya organisasi update.

Latihan: reducer todo (`tambah`, `toggle`, `hapus`, `bersihkanSelesai`) plus tes `console.assert`. Lalu Hook `useOnlineStatus` dengan `useSyncExternalStore`.

## useReducer vs useState: tabel keputusan

| Situasi | Pilihan |
| --- | --- |
| Satu boolean | `useState` |
| Satu string input | `useState` |
| Dua field yang tidak terkait | dua `useState` |
| Wizard 4 langkah + validasi + data | `useReducer` |
| Keranjang: tambah/ubah/hapus/kupon | `useReducer` |
| State dari server lalu diedit | `useState(object)` atau reducer `isi`/`reset` |
| Ingin tes logika tanpa render | reducer fungsi terpisah |

Boleh memulai `useState` lalu pindah ke reducer saat handler mulai salin-tempel. Jangan pindah hanya karena “terlihat lebih profesional”.

**Biasanya digabungkan dengan:** refactor bertahap, bukan rewrite besar.

## Dispatch di event vs di Effect

**Untuk apa:** menjaga reducer tetap murni.

```jsx
function handleKirim(event) {
  event.preventDefault();
  dispatch({ type: "mulaiKirim" });
  fetch("/api", { method: "POST", body: JSON.stringify(state.form) })
    .then((res) => {
      if (!res.ok) throw new Error("gagal");
      dispatch({ type: "suksesKirim" });
    })
    .catch(() => dispatch({ type: "gagalKirim" }));
}
```

Reducer hanya mengubah `status`. Jaringan di handler. Jangan `fetch` di dalam `function reducer`.

Jika GET harus jalan saat `id` berubah, Effect memanggil `fetch` lalu `dispatch({ type: "isi", data })`. Itu sinkronisasi, bukan aksi tombol.

**Biasanya digabungkan dengan:** [file 10](10-fetch-pola-loading-error.md) dan status enum di reducer.

## Snapshot identity pada useSyncExternalStore

**Untuk apa:** menuliskan `getSnapshot` yang tidak merusak performa.

```jsx
// Buruk: object baru setiap panggilan
function getSnapshot() {
  return { w: window.innerWidth, h: window.innerHeight };
}

// Baik: primitif, atau cache jika sama
let cache = { w: 0, h: 0 };
function getSnapshot() {
  const w = window.innerWidth;
  const h = window.innerHeight;
  if (cache.w === w && cache.h === h) return cache;
  cache = { w, h };
  return cache;
}
```

Lebih sederhana: dua Hook `useWindowWidth` dan `useWindowHeight` yang mengembalikan angka.

**Biasanya digabungkan dengan:** cache referensi, dan menghindari `JSON.parse(localStorage)` yang menghasilkan object baru tiap `getSnapshot` tanpa cache.
