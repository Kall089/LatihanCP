# 04 — useEffect, useLayoutEffect, useInsertionEffect

[← List dan key](03-list-key-conditional.md) · [Daftar](README.md) · [Lanjut: ref →](05-useRef-useImperativeHandle-forwardRef.md)

Effect menyinkronkan komponen dengan **sistem di luar React**: timer, event browser, subscription, atau request jaringan. Bukan tempat menghitung turunan data. Tiga Hook berbeda waktu jalannya: setelah cat (paint), sebelum cat, atau sebelum DOM dimutasi untuk menyisipkan CSS.

## Daftar isi

- [Kapan Effect dibutuhkan](#kapan-effect-dibutuhkan)
- [useEffect dasar](#useeffect-dasar)
- [Array dependensi](#array-dependensi)
- [Cleanup](#cleanup)
- [Strict Mode dan Effect ganda](#strict-mode-dan-effect-ganda)
- [Jangan menyalin props ke state lewat Effect](#jangan-menyalin-props-ke-state-lewat-effect)
- [Event browser dan subscription](#event-browser-dan-subscription)
- [Timer](#timer)
- [Fetch sebagai sinkronisasi](#fetch-sebagai-sinkronisasi)
- [Object dan fungsi sebagai dependensi](#object-dan-fungsi-sebagai-dependensi)
- [useLayoutEffect](#uselayouteffect)
- [useInsertionEffect](#useinsertioneffect)
- [Urutan ketiga Effect](#urutan-ketiga-effect)
- [Effect vs event handler](#effect-vs-event-handler)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Satu Effect per urusan](#satu-effect-per-urusan)
- [Event handler di dalam Effect](#event-handler-di-dalam-effect)
- [Development: log berapa kali Effect jalan](#development-log-berapa-kali-effect-jalan)

## Kapan Effect dibutuhkan

**Untuk apa:** membedakan “hitung saat render” dari “bicara dengan dunia luar”.

Tidak perlu Effect:

```jsx
function Ringkasan({ item }) {
  const total = item.reduce((n, x) => n + x.harga, 0);
  const mahal = item.filter((x) => x.harga > 50000);
  return (
    <p>
      {item.length} barang, total Rp{total.toLocaleString("id-ID")}, {mahal.length} mahal
    </p>
  );
}
```

Perlu Effect:

- pasang `addEventListener` pada `window`
- `setInterval` / `setTimeout` yang harus dibersihkan
- subscribe ke WebSocket atau store luar
- ubah `document.title`
- integrasi library DOM (peta, chart) yang bukan React
- fetch di Client Component (ada pola khusus di [file 10](10-fetch-pola-loading-error.md))

Tidak perlu Effect hanya untuk merespons klik. Taruh logika di handler. Tidak perlu Effect untuk “jika `a` berubah, set `b`” jika `b` bisa dihitung dari `a`.

**Biasanya digabungkan dengan:** `useState` untuk menampung hasil sinkronisasi, dan cleanup agar tidak bocor. [Synchronizing with Effects](https://react.dev/learn/synchronizing-with-effects).

## useEffect dasar

**Untuk apa:** menjalankan kode setelah React menggambar UI ke layar.

```jsx
import { useEffect, useState } from "react";

export default function App() {
  const [judul] = useState("Toko Belajar");

  useEffect(() => {
    document.title = judul;
  }, [judul]);

  return <h1>{judul}</h1>;
}
```

Signature: `useEffect(setup, dependencies?)`.

- `setup` dijalankan setelah commit/paint (secara asinkron).
- Jika `setup` mengembalikan fungsi, itu cleanup.
- Dependensi menentukan kapan setup dijalankan ulang.

`useEffect` tidak memblokir lukisan layar. Pengguna melihat UI dulu, lalu Effect jalan. Itu alasan judul tab, fetch, dan listener diletakkan di sini.

Jangan membuat `useEffect` async secara langsung:

```jsx
// Hindari
useEffect(async () => {
  await muat();
}, []);
```

Fungsi async mengembalikan Promise, bukan fungsi cleanup. Bungkus:

```jsx
useEffect(() => {
  let hidup = true;
  async function muat() {
    const data = await ambil();
    if (hidup) setData(data);
  }
  muat();
  return () => {
    hidup = false;
  };
}, []);
```

Lebih baik `AbortController` untuk fetch. Lihat file 10.

**Biasanya digabungkan dengan:** `useState`, array dependensi, cleanup, dan Strict Mode.

## Array dependensi

**Untuk apa:** menyatakan nilai reaktif yang dibaca Effect. Jika salah satu berubah, sinkronisasi diulang.

```jsx
useEffect(() => {
  // setup
}, [id, status]);
```

Tiga bentuk:

| Dependensi | Perilaku |
| --- | --- |
| tidak ditulis | setup + cleanup setiap render (hampir selalu tidak diinginkan) |
| `[]` | setup sekali setelah mount, cleanup saat unmount (plus siklus ekstra di Strict Mode development) |
| `[a, b]` | setup ulang jika `a` atau `b` berubah menurut `Object.is` |

Sertakan **semua** nilai reaktif yang dibaca: props, state, dan fungsi/variabel dari tubuh komponen yang dipakai di dalam Effect. ESLint plugin `react-hooks/exhaustive-deps` mengingatkan ini.

Nilai yang stabil dan bukan reaktif (konstanta modul, setter `useState`) tidak wajib. Setter dari `useState` dijamin stabil.

Jika Effect harus jalan setiap render, biasanya desainnya salah: pindahkan ke handler atau pecah Effect.

**Biasanya digabungkan dengan:** `useCallback` hanya jika fungsi di dependensi memang perlu distabilkan, dan custom Hook yang menerima id.

## Cleanup

**Untuk apa:** membatalkan pekerjaan lama agar tidak menimpa tampilan baru atau membebani browser.

```jsx
import { useEffect, useState } from "react";

export default function App() {
  const [detik, setDetik] = useState(0);

  useEffect(() => {
    const id = setInterval(() => {
      setDetik((lama) => lama + 1);
    }, 1000);
    return () => clearInterval(id);
  }, []);

  return <p>Sudah berjalan {detik} detik.</p>;
}
```

Cleanup jalan:

- sebelum Effect berikutnya dengan dependensi yang sama/berubah
- saat komponen unmount
- di Strict Mode development: segera setelah setup pertama, lalu setup lagi

Tanpa `clearInterval`, tiap mount (atau tiap siklus Strict Mode) menambah interval baru.

Pola umum cleanup:

```jsx
// event
const onResize = () => setLebar(window.innerWidth);
window.addEventListener("resize", onResize);
return () => window.removeEventListener("resize", onResize);

// fetch
const kontrol = new AbortController();
fetch(url, { signal: kontrol.signal });
return () => kontrol.abort();

// subscription
const berhenti = store.subscribe(onGanti);
return berhenti;
```

Cleanup harus simetris dengan setup. Jangan membersihkan sesuatu yang belum dipasang.

**Biasanya digabungkan dengan:** timer, listener, WebSocket, dan fetch.

## Strict Mode dan Effect ganda

**Untuk apa:** tidak panik saat development terlihat “Effect jalan dua kali”.

Di React 18+ development, Strict Mode memicu: setup → cleanup → setup. Tujuannya menemukan Effect yang lupa cleanup. Produksi tidak melakukan siklus ekstra itu.

Jika fetch tanpa abort, kamu bisa melihat dua request di tab Network saat development. Itu normal. Pastikan cleanup membatalkan atau mengabaikan respons lama. Jangan “memperbaiki” dengan menonaktifkan Strict Mode.

```jsx
useEffect(() => {
  const kontrol = new AbortController();
  muat(kontrol.signal);
  return () => kontrol.abort();
}, [id]);
```

Dua request mungkin tetap terlihat (request kedua menggantikan), tetapi yang pertama tidak menulisi state setelah abort.

**Biasanya digabungkan dengan:** `<StrictMode>` di `main.jsx`, dan [katalog StrictMode](13-katalog-api-react.md#strictmode).

## Jangan menyalin props ke state lewat Effect

**Untuk apa:** menghindari pola yang membuat UI “terlambat satu langkah” atau loop.

Buruk:

```jsx
function Kartu({ judul }) {
  const [teks, setTeks] = useState(judul);
  useEffect(() => {
    setTeks(judul);
  }, [judul]);
  return <h2>{teks}</h2>;
}
```

Pakai `judul` langsung. Jika kamu butuh draft yang bisa diedit lalu direset saat id berubah, pakai `key` pada komponen (lihat [file 03](03-list-key-conditional.md#key-untuk-mereset-state)) atau inisialisasi state dari props **tanpa** Effect, lalu sediakan tombol reset.

Buruk: menghitung total di Effect lalu `setTotal`. Hitung `total` saat render.

Buruk: `useEffect(() => setX(x + 1))` tanpa syarat — loop tak hingga.

**Biasanya digabungkan dengan:** meninjau ulang apakah data memang turunan, dan `key` untuk mereset form.

## Event browser dan subscription

**Untuk apa:** memasang listener pada objek yang bukan milik React.

```jsx
import { useEffect, useState } from "react";

export default function App() {
  const [lebar, setLebar] = useState(() => window.innerWidth);

  useEffect(() => {
    function ubah() {
      setLebar(window.innerWidth);
    }
    window.addEventListener("resize", ubah);
    return () => window.removeEventListener("resize", ubah);
  }, []);

  return <p>Lebar jendela: {lebar}px</p>;
}
```

Inisialisasi `useState` dengan `window.innerWidth` hanya aman di client. Di Next.js Server Component / SSR, `window` tidak ada; pakai nilai awal `undefined` lalu isi di Effect, atau `useSyncExternalStore` yang punya `getServerSnapshot`. Lihat [file 07](07-useReducer-useSyncExternalStore.md).

Untuk store eksternal (Redux, Zustand, `matchMedia`), `useSyncExternalStore` lebih tepat daripada Effect + `setState`.

**Biasanya digabungkan dengan:** `useState`, custom Hook `useWindowWidth`, dan cleanup.

## Timer

**Untuk apa:** menunda atau mengulang pekerjaan, lalu membersihkan jika komponen pergi atau dependensi berubah.

```jsx
import { useEffect, useState } from "react";

export default function App({ delay = 1000 }) {
  const [tik, setTik] = useState(0);

  useEffect(() => {
    const id = setTimeout(() => {
      setTik((n) => n + 1);
    }, delay);
    return () => clearTimeout(id);
  }, [delay, tik]);

  return <p>Tik ke-{tik}</p>;
}
```

Contoh di atas menjadwalkan timeout berikutnya setelah `tik` berubah. Untuk interval tetap, pakai `setInterval` dengan dependensi `[]` dan setter bentuk fungsi.

Jangan memakai `setInterval` di handler klik tanpa menyimpan id di ref; unmount tidak otomatis membersihkan timer yang dibuat di handler kecuali kamu menaruh id di ref dan membersihkan di Effect.

**Biasanya digabungkan dengan:** `useRef` untuk id timer dari handler, dan tombol mulai/berhenti.

## Fetch sebagai sinkronisasi

**Untuk apa:** mengambil data ketika id atau filter berubah — ini sinkronisasi dengan server, bukan “hitung turunan”.

```jsx
import { useEffect, useState } from "react";

export default function DetailProduk({ id }) {
  const [produk, setProduk] = useState(null);
  const [status, setStatus] = useState("memuat");

  useEffect(() => {
    const kontrol = new AbortController();
    setStatus("memuat");
    setProduk(null);

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

  if (status === "memuat") return <p>Memuat…</p>;
  if (status === "gagal") return <p>Gagal memuat.</p>;
  return <h1>{produk.nama}</h1>;
}
```

Saat `id` berubah, cleanup membatalkan request lama. Tanpa itu, respons produk 1 bisa tiba setelah produk 2 dan menimpa tampilan.

Di Next.js App Router, daftar publik lebih cocok di-fetch di Server Component. Pola Effect tetap penting untuk filter interaktif di client.

**Biasanya digabungkan dengan:** [file 10](10-fetch-pola-loading-error.md), custom Hook `useProduk(id)`, dan empty/error UI.

## Object dan fungsi sebagai dependensi

**Untuk apa:** menghindari Effect yang jalan setiap render karena referensi baru.

```jsx
useEffect(() => {
  muat(opsi);
}, [opsi]);
```

Jika induk menulis `opsi={{ halaman: 1 }}` setiap render, `opsi` selalu “berubah”. Efek: request berulang.

Perbaikan:

- andalkan field primitif: `[halaman, urutan]`
- `useMemo` untuk object yang memang mahal/dibagikan
- pindahkan object statis ke luar komponen
- `useCallback` untuk fungsi yang masuk dependensi

```jsx
const opsi = useMemo(
  () => ({ halaman, urutan }),
  [halaman, urutan]
);
```

Lebih sederhana: jangan memasukkan object jika kamu bisa membaca `halaman` dan `urutan` langsung di dalam Effect.

**Biasanya digabungkan dengan:** `useMemo`, `useCallback`, dan meninjau apakah Effect masih diperlukan.

## useLayoutEffect

**Untuk apa:** membaca atau mengubah DOM **sebelum browser mengecat**, agar pengguna tidak melihat kedipan.

```jsx
import { useLayoutEffect, useRef, useState } from "react";

export default function Tooltip({ teks, sasaran }) {
  const ref = useRef(null);
  const [x, setX] = useState(0);

  useLayoutEffect(() => {
    const kotak = ref.current.getBoundingClientRect();
    const induk = sasaran.getBoundingClientRect();
    setX(induk.left + induk.width / 2 - kotak.width / 2);
  }, [teks, sasaran]);

  return (
    <div ref={ref} style={{ position: "absolute", left: x }}>
      {teks}
    </div>
  );
}
```

`useLayoutEffect` berjalan setelah DOM diperbarui, secara **sinkron**, sebelum paint. `setState` di dalamnya memicu render tambahan sebelum pengguna melihat frame.

Pakai hanya jika `useEffect` menyebabkan kedipan terukur: ukur posisi tooltip, sinkronkan scroll, fokus yang harus terjadi sebelum cat. Jangan pakai sebagai “useEffect yang lebih cepat” untuk fetch.

Di SSR (Next.js), `useLayoutEffect` memperingatkan karena tidak ada layout di server. Pakai `useEffect` atau jaga agar komponen hanya di client.

**Biasanya digabungkan dengan:** `useRef` ke elemen, pengukuran `getBoundingClientRect`, dan popover. [useLayoutEffect](https://react.dev/reference/react/useLayoutEffect).

## useInsertionEffect

**Untuk apa:** menyisipkan `<style>` dinamis **sebelum** layout Effect, khusus penulis library CSS-in-JS.

```jsx
import { useInsertionEffect } from "react";

function useCssDinamis(aturan) {
  useInsertionEffect(() => {
    const style = document.createElement("style");
    style.textContent = aturan;
    document.head.append(style);
    return () => style.remove();
  }, [aturan]);
}
```

Hook ini berjalan lebih awal daripada `useLayoutEffect`, saat DOM belum wajib dibaca. Tujuannya: CSS sudah ada sebelum library lain mengukur elemen.

Aplikasi produk/tugas kuliah **hampir tidak pernah** membutuhkannya. Pakai file CSS, CSS Modules, atau Tailwind. Jika kamu mengukur DOM, itu `useLayoutEffect`. Jika kamu fetch atau pasang listener, itu `useEffect`.

`useInsertionEffect` tidak boleh memanggil `setState` secara spekulatif; ia bukan tempat logika UI.

**Biasanya digabungkan dengan:** runtime CSS-in-JS (styled-components, emotion) dan injection stylesheet. [useInsertionEffect](https://react.dev/reference/react/useInsertionEffect).

## Urutan ketiga Effect

**Untuk apa:** memilih Hook yang tepat berdasarkan kapan kode harus jalan.

Urutan dalam satu commit:

1. React memperbarui DOM
2. `useInsertionEffect` — sisipkan CSS
3. `useLayoutEffect` — baca/tulis DOM, cegah kedip
4. Browser mengecat
5. `useEffect` — pekerjaan tidak mendesak (jaringan, listener, log)

Semua tetap Hooks: dipanggil di tingkat atas, punya dependensi dan cleanup.

Tabel keputusan:

| Kebutuhan | Hook |
| --- | --- |
| Fetch, timer, listener, title | `useEffect` |
| Ukur DOM, cegah flicker posisi | `useLayoutEffect` |
| Inject CSS sebelum ukur | `useInsertionEffect` |
| Hitung turunan dari props/state | tanpa Effect |
| Respons klik/submit | event handler |

**Biasanya digabungkan dengan:** pemahaman commit vs paint, dan menghindari overlay Hook “untuk jaga-jaga”.

## Effect vs event handler

**Untuk apa:** menaruh side effect pada tempat yang sesuai dengan **penyebabnya**.

```jsx
// Salah: Effect yang “mengawasi” klik lewat flag
const [harusKirim, setHarusKirim] = useState(false);
useEffect(() => {
  if (!harusKirim) return;
  kirimKeServer(data);
  setHarusKirim(false);
}, [harusKirim, data]);

// Benar: handler
function handleSubmit(event) {
  event.preventDefault();
  kirimKeServer(data);
}
```

Jika pengguna melakukan sesuatu, kerjakan di handler. Jika komponen harus **tetap selaras** dengan sistem luar selama ia tampil (id di URL, ukuran jendela, koneksi chat), kerjakan di Effect.

Analytics “halaman tampil” bisa Effect. Analytics “tombol beli diklik” adalah handler.

**Biasanya digabungkan dengan:** form, `fetch` POST, dan memisahkan GET sinkronisasi dari POST aksi.

## Kesalahan umum bab ini

- **Effect untuk menghitung turunan.** Hitung saat render.
- **Lupa cleanup timer/listener/fetch.**
- **`useEffect(async () => ...)`.**
- **Dependensi kosong padahal membaca `id`.** Data tidak terbarui saat id berubah; atau sebaliknya, stale closure.
- **Menonaktifkan eslint exhaustive-deps secara membabi buta.**
- **Object baru di dependensi setiap render → spam request.**
- **`useLayoutEffect` untuk fetch.** Memblokir cat tanpa alasan.
- **`useInsertionEffect` di aplikasi biasa.**
- **Mengira dua kali jalan di Strict Mode adalah bug produksi.**
- **`setState` di Effect yang selalu menghasilkan nilai baru → loop.**

Latihan: Hook `useDocumentTitle(judul)` dan `useInterval(callback, delay)` lengkap dengan cleanup. Lalu fetch detail produk berdasarkan `id` dengan abort.

## Satu Effect per urusan

**Untuk apa:** tidak menggabungkan title, listener, dan fetch dalam satu `useEffect`.

```jsx
useEffect(() => {
  document.title = judul;
}, [judul]);

useEffect(() => {
  const onKey = (e) => {
    if (e.key === "Escape") onTutup();
  };
  window.addEventListener("keydown", onKey);
  return () => window.removeEventListener("keydown", onKey);
}, [onTutup]);
```

Pemisahan membuat dependensi jujur: fetch tidak diulang hanya karena judul berubah. Cleanup juga tidak saling terkait.

Jika dua pekerjaan selalu hidup-mati bersama dan berbagi resource, baru gabungkan.

**Biasanya digabungkan dengan:** custom Hook per urusan (`useDocumentTitle`, `useEscape`).

## Event handler di dalam Effect

**Untuk apa:** membaca props terbaru tanpa memasang ulang listener setiap ketikan.

```jsx
import { useEffect, useRef } from "react";

export function useEscape(onEscape) {
  const ref = useRef(onEscape);
  ref.current = onEscape;

  useEffect(() => {
    function onKey(event) {
      if (event.key === "Escape") ref.current();
    }
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, []);
}
```

Dependensi `[]` memasang listener sekali. `ref.current = onEscape` saat render selalu menunjuk fungsi mutakhir. Tanpa ref, `[onEscape]` memasang ulang setiap kali induk membuat fungsi baru.

**Biasanya digabungkan dengan:** [useRef](05-useRef-useImperativeHandle-forwardRef.md), modal, dan menekan godaan memasukkan semua handler ke dependensi.

## Development: log berapa kali Effect jalan

**Untuk apa:** memastikan kamu tidak “memperbaiki” Strict Mode dengan flag global.

```jsx
useEffect(() => {
  console.log("setup", id);
  return () => console.log("cleanup", id);
}, [id]);
```

Di development + Strict Mode kamu melihat setup–cleanup–setup untuk `id` yang sama saat mount. Itu bukan dua pengguna sungguhan. Di produksi, satu setup sampai `id` berubah atau unmount.

Jika log setup tanpa cleanup lalu setup lagi, kamu mungkin lupa return cleanup, atau dependensi berubah setiap render.

**Biasanya digabungkan dengan:** React DevTools “Strict Mode” di akar, dan tab Network.
