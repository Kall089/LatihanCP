# 12 — Aturan Hooks dan kesalahan yang sering muncul

[← Portal dan Suspense](11-portal-suspense-error-boundary.md) · [Daftar](README.md) · [Lanjut: katalog API →](13-katalog-api-react.md)

Hooks adalah fungsi `use*` yang React kaitkan ke **instance komponen** berdasarkan **urutan panggilan**. Melanggar urutan membuat state tertukar. Bab ini merangkum aturan resmi dan bug harian.

## Daftar isi

- [Dua aturan resmi](#dua-aturan-resmi)
- [Mengapa urutan penting](#mengapa-urutan-penting)
- [Early return setelah Hooks](#early-return-setelah-hooks)
- [Custom Hook dan aturan yang sama](#custom-hook-dan-aturan-yang-sama)
- [ESLint react-hooks](#eslint-react-hooks)
- [Stale closure](#stale-closure)
- [Loop render](#loop-render)
- [Dependensi Effect](#dependensi-effect)
- [Event handler yang salah](#event-handler-yang-salah)
- [Mutasi dan identitas](#mutasi-dan-identitas)
- [Hidrasi dan browser-only API](#hidrasi-dan-browser-only-api)
- [Strict Mode yang “aneh”](#strict-mode-yang-aneh)
- [Daftar periksa debug](#daftar-periksa-debug)
- [Kesalahan campuran yang sering di tugas](#kesalahan-campuran-yang-sering-di-tugas)
- [Hooks di dalam useMemo/useEffect](#hooks-di-dalam-usememouseeffect)
- [Objek di dependency yang “selalu baru”](#objek-di-dependency-yang-selalu-baru)
- [State yang saling menimpa](#state-yang-saling-menimpa)
- [Pesan error runtime yang sering](#pesan-error-runtime-yang-sering)
- [Latihan debug terarah](#latihan-debug-terarah)

## Dua aturan resmi

**Untuk apa:** mengingat batas yang tidak dinegosiasikan.

1. Panggil Hooks hanya di **tingkat atas** function component atau custom Hook. Bukan di loop, `if`, `try` bersyarat, event handler, atau fungsi biasa.
2. Panggil Hooks hanya dari React function (komponen / custom Hook), bukan class, bukan `useMemo` callback sebagai tempat `useState`.

```jsx
function Salah({ user }) {
  if (!user) return null;
  const [x, setX] = useState(0); // dilarang: setelah return bersyarat
}

function Benar({ user }) {
  const [x, setX] = useState(0);
  if (!user) return null;
  return <p>{x}</p>;
}
```

```jsx
function jugaSalah() {
  for (const id of ids) {
    useState(id); // dilarang
  }
}
```

**Biasanya digabungkan dengan:** plugin ESLint, dan memindahkan cabang ke komponen anak yang selalu memanggil Hooks-nya sendiri. [Rules of Hooks](https://react.dev/reference/rules/rules-of-hooks).

## Mengapa urutan penting

**Untuk apa:** memahami bahwa React tidak melihat nama variabel, hanya panggilan ke-n.

```jsx
function Contoh({ mode }) {
  const [a, setA] = useState(0);
  if (mode === "penuh") {
    const [b, setB] = useState(1);
  }
  const [c, setC] = useState(2);
}
```

Saat `mode` berubah, jumlah `useState` berubah. Render berikutnya, panggilan ke-2 yang tadinya `b` bisa menjadi `c`. Nilai tertukar, bug sulit dilacak.

React menyimpan slot Hook dalam daftar. Kamu wajib membuat daftar itu sama setiap render instance tersebut.

Komponen **berbeda** punya daftar sendiri. Dua `<Contoh />` tidak berbagi state.

**Biasanya digabungkan dengan:** tidak menyembunyikan Hook di helper tanpa nama `use`, dan memecah komponen daripada `if` di sekitar Hook.

## Early return setelah Hooks

**Untuk apa:** tetap boleh keluar awal untuk UI, setelah semua Hook dipanggil.

```jsx
function Profil({ id }) {
  const [data, setData] = useState(null);
  const [status, setStatus] = useState("memuat");

  useEffect(() => {
    // fetch id
  }, [id]);

  if (status === "memuat") return <p>Memuat…</p>;
  if (!data) return <p>Tidak ada.</p>;
  return <h1>{data.nama}</h1>;
}
```

Semua Hook di atas `if`. Jumlah panggilan tetap.

Jika logika Hook hanya relevan saat `id` ada, tetap panggil Hook: `useEffect` boleh return cepat di dalamnya, `useState` boleh menyimpan `null`.

**Biasanya digabungkan dengan:** empat status fetch, dan [file 03](03-list-key-conditional.md).

## Custom Hook dan aturan yang sama

**Untuk apa:** tidak mengira prefix `use` memberi kebebasan.

```jsx
function useNama(aktif) {
  if (!aktif) return ""; // jika di bawah ada useState, ini bermasalah
  const [nama, setNama] = useState("");
  return nama;
}
```

Jika kadang `aktif` true kadang false, jumlah Hook berubah. Perbaikan:

```jsx
function useNama(aktif) {
  const [nama, setNama] = useState("");
  return aktif ? nama : "";
}
```

Atau pecah: komponen induk tidak memanggil Hook jika tidak perlu, dengan merender anak yang memanggil Hook secara konsisten.

Fungsi pembantu tanpa `use` **tidak boleh** memanggil Hook. Jika perlu Hook, ubah menjadi custom Hook.

**Biasanya digabungkan dengan:** [file 09](09-custom-hook-pola.md).

## ESLint react-hooks

**Untuk apa:** menangkap pelanggaran sebelum runtime aneh.

Dua aturan utama:

- `rules-of-hooks`: lokasi panggilan
- `exhaustive-deps`: dependensi Effect/Memo/Callback

Vite + template React biasanya sudah memasang plugin. Jangan menonaktifkan sebaris tanpa alasan tertulis.

```jsx
useEffect(() => {
  muat(id);
  // eslint-disable-next-line react-hooks/exhaustive-deps
}, []);
```

Disable seperti ini menyembunyikan stale `id`. Lebih baik `[id]` atau baca mengapa kamu ingin sekali jalan (mungkin logika harusnya di handler).

**Biasanya digabungkan dengan:** membaca peringatan sebagai sinyal desain, bukan gangguan.

## Stale closure

**Untuk apa:** mengenali handler/Effect yang melihat nilai lama.

```jsx
function App() {
  const [n, setN] = useState(0);

  useEffect(() => {
    const id = setInterval(() => {
      setN(n + 1); // n tertahan di 0
    }, 1000);
    return () => clearInterval(id);
  }, []);

  return <p>{n}</p>;
}
```

Interval terpasang sekali, menutup `n === 0`. Setiap detik: `setN(0 + 1)`. Layar tetap 1.

Perbaikan: `setN((lama) => lama + 1)` atau masukkan `n` ke dependensi (memasang interval ulang — biasanya tidak diinginkan).

Pola sama: `fetch` di Effect dengan `[]` tetapi memakai `filter` dari props; subscription yang memanggil callback lama.

Ref untuk nilai mutakhir: `nRef.current = n` lalu baca di interval. Lihat [file 05](05-useRef-useImperativeHandle-forwardRef.md).

**Biasanya digabungkan dengan:** setter fungsional, dependensi benar, `useRef`.

## Loop render

**Untuk apa:** menghentikan “Maximum update depth exceeded”.

Penyebab umum:

```jsx
function App() {
  const [n, setN] = useState(0);
  setN(n + 1); // setiap render menambah, render lagi
}

<button onClick={setN(n + 1)} /> // memanggil setter saat render

useEffect(() => {
  setData({ ...data });
}, [data]); // object baru selalu, Effect selalu

useEffect(() => {
  setOpsi({ halaman });
}, [opsi, halaman]);
```

Perbaikan: setter hanya di handler/Effect dengan syarat berhenti; `onClick={() => setN(n + 1)}`; jangan menaruh object yang baru dibuat ke dependensi yang juga di-set di Effect yang sama.

`useMemo` yang dependensinya salah bisa ikut serta, tetapi loop klasik hampir selalu `setState` sinkron di body atau Effect tanpa pintu keluar.

**Biasanya digabungkan dengan:** React DevTools “Highlight updates”, dan membaca stack “setState”.

## Dependensi Effect

**Untuk apa:** menyeimbangkan “lengkap” dan “tidak spam”.

Baca di dalam Effect → masukkan ke array, atau jangan baca (pakai fungsional setter / ref).

Object/fungsi dari render induk: pecah jadi primitif, atau `useCallback`/`useMemo` dengan alasan.

`[]` berarti “setelah mount (dan siklus Strict Mode)”. Cocok untuk listener `window` yang tidak bergantung props. Tidak cocok jika kamu membaca `id`.

Tidak menulis array sama sekali: Effect setiap render. Hampir selalu tidak diinginkan (pasang listener berulang).

**Biasanya digabungkan dengan:** [file 04](04-useEffect-useLayoutEffect-useInsertionEffect.md), dan meninjau apakah Effect bisa dihapus.

## Event handler yang salah

**Untuk apa:** mengingat bentuk yang benar.

```jsx
onClick={handle}           // benar: lulus fungsi
onClick={() => handle()}   // benar jika perlu membungkus
onClick={() => handle(id)} // benar: argumen
onClick={handle(id)}       // salah: jalan saat render
onClick={handle()}         // salah
onSubmit={kirim}           // benar; di dalam kirim: preventDefault
```

`onChange` tanpa `setState` pada input controlled = macet.

`onClick` pada `<div>` tanpa peran keyboard: kurang aksesibel. Pakai `<button>` untuk aksi.

**Biasanya digabungkan dengan:** [file 02](02-state-event-form.md).

## Mutasi dan identitas

**Untuk apa:** React membandingkan state dengan `Object.is`.

```jsx
item.push(baru);
setItem(item); // referensi sama, bisa tidak rerender

setItem([...item, baru]); // baru
```

```jsx
profil.nama = "A";
setProfil(profil); // berbahaya

setProfil({ ...profil, nama: "A" });
```

`sort` dan `reverse` memutasi: salin dulu.

`memo` dan dependensi Effect memakai identitas. Object baru `{}` setiap render = “berubah”.

**Biasanya digabungkan dengan:** update array/object di file 02, dan `useReducer` murni.

## Hidrasi dan browser-only API

**Untuk apa:** menghindari teks server ≠ teks client.

```jsx
const [jam, setJam] = useState(Date.now()); // SSR dan client bisa beda
const lebar = window.innerWidth; // crash di server
```

Pola aman:

- nilai awal tetap (`null`, `0`, `false`)
- isi nilai browser di `useEffect`
- atau `useSyncExternalStore` + `getServerSnapshot`

`useId` ada untuk id yang cocok server/client. Jangan `Math.random()` untuk id label.

**Biasanya digabungkan dengan:** Next.js, [file 07](07-useReducer-useSyncExternalStore.md), [file 08](08-context-useContext-useId.md).

## Strict Mode yang “aneh”

**Untuk apa:** tidak “memperbaiki” development dengan mematikan Strict Mode.

Gejala: Effect jalan dua kali, fetch dobel di Network, constructor class dua kali.

Itu disengaja di development. Pastikan cleanup benar. Produksi tidak menggandakan seperti itu.

Jika fetch dobel merusak backend (membuat dua resource), endpoint-nya tidak idempotent — perbaiki server atau pindahkan POST ke handler, bukan Effect.

**Biasanya digabungkan dengan:** [katalog StrictMode](13-katalog-api-react.md#strictmode).

## Daftar periksa debug

**Untuk apa:** urutan cek saat UI “tidak jalan”.

1. Apakah komponen ter-render? `console.log` di tubuh, atau DevTools.
2. Apakah `return` mengembalikan JSX yang kamu kira?
3. Apakah state berubah? Log di handler sebelum/sesudah `set`.
4. Apakah kamu memutasi array/object?
5. Apakah `key` stabil pada daftar?
6. Apakah Effect dependensinya benar / loop?
7. Apakah input punya `value` + `onChange`?
8. Apakah error di console (Hook, hidrasi, key)?
9. Apakah kamu mengedit file yang memang diimpor `App`?
10. Apakah cache/HMR aneh — refresh penuh sekali.

**Biasanya digabungkan dengan:** React DevTools Components (melihat props/state), Profiler jika lambat.

## Kesalahan campuran yang sering di tugas

**Untuk apa:** daftar cepat sebelum mengumpulkan.

- Komponen huruf kecil: `<headerToko />`
- `class` bukan `className`
- `{daftar.map(item => { <li /> })}` tanpa `return`
- `key={index}` pada todo yang dihapus
- `useEffect(() => setTotal(harga * qty), [harga, qty])` — hitung saat render
- Context tanpa Provider
- Fetch tanpa `ok` check
- Menyimpan turunan filter ke state + Effect, lalu filter “terlambat”
- `import { useState } from "react"` terlupa, runtime error
- Mencampur controlled `value` dan `defaultValue`

Latihan: buka kode tugasmu dan tandai tiap item di atas. Perbaiki satu per satu, bukan sekaligus tanpa menguji.

**Biasanya digabungkan dengan:** membaca ulang file 01–03 sebelum API lanjut, karena sebagian besar nilai tugas ada di sana.

## Hooks di dalam useMemo/useEffect

**Untuk apa:** menolak godaan “Hook di dalam Hook callback”.

```jsx
useEffect(() => {
  const [x, setX] = useState(0); // dilarang
}, []);

useMemo(() => {
  useRef(null); // dilarang
}, []);
```

Callback Effect/Memo adalah fungsi biasa. Panggil Hook di tubuh komponen atau di custom Hook yang dipanggil dari tubuh itu.

Jika kamu butuh state yang hanya “hidup” saat modal terbuka, buat komponen `IsiModal` yang di-mount hanya saat `terbuka`, dan taruh Hooks di `IsiModal`. Unmount menghapus state itu — sering justru yang diinginkan.

**Biasanya digabungkan dengan:** memecah komponen, bukan menyembunyikan Hook.

## Objek di dependency yang “selalu baru”

**Untuk apa:** melihat pola yang membuat Effect atau memo seolah rusak.

```jsx
function App({ halaman }) {
  const opsi = { halaman, urutan: "nama" };
  useEffect(() => {
    muat(opsi);
  }, [opsi]);
}
```

Setiap render, `opsi` adalah object baru. `Object.is` gagal. Effect jalan terus.

Perbaikan bertingkat:

```jsx
useEffect(() => {
  muat({ halaman, urutan: "nama" });
}, [halaman]);
```

Atau `useMemo` pada `opsi` jika object itu juga dikirim ke anak bermemo.

Fungsi `muat` yang didefinisikan di tubuh juga baru setiap kali. Jika ia masuk dependensi, Effect ikut. Pindahkan `muat` ke modul jika murni, atau bungkus `useCallback` dengan dependensi primitif.

**Biasanya digabungkan dengan:** [file 04](04-useEffect-useLayoutEffect-useInsertionEffect.md) dan [file 06](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md).

## State yang saling menimpa

**Untuk apa:** dua setter dari data yang sama tanpa sumber tunggal.

```jsx
const [produk, setProduk] = useState([]);
const [jumlah, setJumlah] = useState(0);

useEffect(() => {
  setJumlah(produk.length);
}, [produk]);
```

`jumlah` adalah turunan. Hapus state dan Effect: `const jumlah = produk.length`.

Bentuk lain: `kata` dan `hasilFilter` keduanya state, `hasilFilter` diisi Effect saat `kata` berubah. Cukup `const hasil = data.filter(...)`.

**Biasanya digabungkan dengan:** prinsip “hitung saat render” di file 04 dan 06.

## Pesan error runtime yang sering

| Pesan (ringkas) | Arti khas | Arah perbaikan |
| --- | --- | --- |
| Invalid hook call | Hook di luar komponen / dua salinan React | Panggil di komponen; cek `npm ls react` |
| Rendered more hooks | Jumlah Hook berubah | Pindahkan Hook ke atas `if` |
| Too many re-renders | `setState` saat render | Pindahkan ke handler |
| Objects are not valid as a React child | Merender object mentah | Ambil field / `JSON.stringify` sadar |
| Each child should have a unique key | `map` tanpa key / key dobel | `id` data |
| Cannot update unmounted component | `setState` setelah unmount (peringatan lama) | abort / flag hidup |
| Hydration failed | HTML server ≠ client | `useId`, snapshot server, jangan `Date.now()` di render |

**Biasanya digabungkan dengan:** membaca stack penuh, bukan baris pertama saja.

## Latihan debug terarah

1. Buat sengaja `onClick={setN(1)}` dan lihat loop. Perbaiki.
2. Buat `useEffect` fetch tanpa abort, ganti `id` cepat, saksikan race. Tambah abort.
3. Buat daftar dengan `key={index}`, hapus item tengah yang checkbox-nya tercentang. Ganti ke `id`.
4. Panggil `useState` setelah `if (!user) return null`. Lihat peringatan. Pindahkan Hook ke atas.

Tulis catatan satu kalimat per percobaan: gejala, sebab, perbaikan. Itu lebih berguna daripada menghafal daftar API.
