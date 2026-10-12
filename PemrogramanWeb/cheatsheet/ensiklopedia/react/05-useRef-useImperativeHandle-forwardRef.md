# 05 — useRef, useImperativeHandle, dan forwardRef

[← Effect](04-useEffect-useLayoutEffect-useInsertionEffect.md) · [Daftar](README.md) · [Lanjut: memo dan transisi →](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md)

Ref menyimpan nilai yang **tidak memicu render** saat diubah. Dua pemakaian utama: menunjuk elemen DOM, dan menyimpan angka/id/nilai mutakhir untuk handler atau Effect. `forwardRef` meneruskan ref ke anak. `useImperativeHandle` membatasi API yang terlihat dari luar.

## Daftar isi

- [useRef untuk DOM](#useref-untuk-dom)
- [useRef untuk nilai mutable](#useref-untuk-nilai-mutable)
- [Ref bukan state](#ref-bukan-state)
- [Callback ref](#callback-ref)
- [forwardRef](#forwardref)
- [Ref sebagai prop (React 19)](#ref-sebagai-prop-react-19)
- [useImperativeHandle](#useimperativehandle)
- [Menggabungkan ref](#menggabungkan-ref)
- [File input dan media](#file-input-dan-media)
- [Menyimpan id timer dan prev props](#menyimpan-id-timer-dan-prev-props)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Ref ke banyak elemen](#ref-ke-banyak-elemen)
- [Jangan baca/tulis ref DOM untuk konten yang React kelola](#jangan-bacatulis-ref-dom-untuk-konten-yang-react-kelola)
- [forwardRef + TypeScript secara konsep](#forwardref--typescript-secara-konsep)

## useRef untuk DOM

**Untuk apa:** meminta React mengisi `.current` dengan node DOM setelah commit, lalu memanggil metode browser.

```jsx
import { useRef } from "react";

export default function App() {
  const inputRef = useRef(null);

  function fokusCari() {
    inputRef.current?.focus();
  }

  return (
    <>
      <label htmlFor="cari">Cari produk</label>
      <input id="cari" ref={inputRef} />
      <button type="button" onClick={fokusCari}>
        Fokus pencarian
      </button>
    </>
  );
}
```

`useRef(null)` membuat object `{ current: null }`. React menulis node ke `current` setelah elemen terpasang, dan menulis `null` saat dilepas.

Pakai `?.` karena `current` bisa null sebelum mount atau setelah unmount. Jangan membaca `inputRef.current` untuk merender teks; itu tugas state.

Operasi DOM yang wajar lewat ref:

- `focus()`, `blur()`, `select()`, `setSelectionRange`
- `scrollIntoView`, `scrollTo`
- `play()`, `pause()` pada media
- `getBoundingClientRect` (sering di `useLayoutEffect`)
- `click()` pada file input tersembunyi

Jangan memakai ref untuk mengubah `className` atau `innerHTML` jika React juga merender atribut yang sama: dua sumber kebenaran akan bentrok.

**Biasanya digabungkan dengan:** form, dialog, `useLayoutEffect` untuk ukur, dan library chart. [useRef](https://react.dev/reference/react/useRef).

## useRef untuk nilai mutable

**Untuk apa:** menyimpan angka, flag, atau fungsi yang harus tetap ada antar-render tanpa merender ulang.

```jsx
import { useEffect, useRef, useState } from "react";

export default function App() {
  const [ketik, setKetik] = useState("");
  const renderKe = useRef(0);

  useEffect(() => {
    renderKe.current += 1;
    console.log("Render ke", renderKe.current);
  });

  return (
    <input
      value={ketik}
      onChange={(e) => setKetik(e.target.value)}
    />
  );
}
```

Mengubah `renderKe.current` tidak meminta render. Cocok untuk:

- id `setTimeout` / `setInterval`
- instance library pihak ketiga
- flag “apakah request ini masih relevan” selain AbortController
- menyimpan callback terbaru agar Effect tidak bergantung pada fungsi

Object ref identitasnya stabil: `ref` yang sama setiap render. Hanya `.current` yang berubah.

**Biasanya digabungkan dengan:** Effect, debounce, dan handler yang butuh nilai mutakhir.

## Ref bukan state

**Untuk apa:** memilih dengan benar antara `useState` dan `useRef`.

| Pertanyaan | State | Ref |
| --- | --- | --- |
| Perubahan harus terlihat di layar? | Ya | Tidak |
| Mengubahnya memicu render? | Ya | Tidak |
| Boleh diubah saat render? | Tidak (kecuali pola khusus) | Hindari; ubah di handler/Effect |
| Nilai terbaru selalu di `.current`? | Snapshot per render | Ya |

Contoh: jumlah klik yang ditampilkan → state. Jumlah klik hanya untuk log internal → ref.

Salah memakai ref untuk teks input yang ditampilkan di `<p>`: paragraf tidak terbarui saat `.current` berubah.

Salah memakai state untuk id interval: setiap ganti id merender ulang tanpa manfaat.

Boleh memakai keduanya: state untuk UI, ref untuk nilai terkini yang dibaca timer:

```jsx
const [jumlah, setJumlah] = useState(0);
const jumlahRef = useRef(jumlah);
jumlahRef.current = jumlah;

useEffect(() => {
  const id = setInterval(() => {
    console.log("Jumlah mutakhir", jumlahRef.current);
  }, 1000);
  return () => clearInterval(id);
}, []);
```

Pola `jumlahRef.current = jumlah` saat render adalah pengecualian yang diterima: menyesuaikan ref dengan state tanpa memicu render tambahan.

**Biasanya digabungkan dengan:** interval, subscription, dan menghindari stale closure tanpa memasukkan nilai ke dependensi Effect.

## Callback ref

**Untuk apa:** menjalankan kode saat node terpasang atau dilepas, lebih fleksibel daripada object ref.

```jsx
import { useCallback, useState } from "react";

export default function App() {
  const [tinggi, setTinggi] = useState(0);

  const ukurRef = useCallback((node) => {
    if (node) {
      setTinggi(node.getBoundingClientRect().height);
    }
  }, []);

  return (
    <>
      <article ref={ukurRef}>Isi kartu yang tingginya diukur.</article>
      <p>Tinggi: {tinggi}px</p>
    </>
  );
}
```

React memanggil callback dengan node saat mount, dan dengan `null` saat unmount. Jika identitas callback berubah setiap render, React akan memanggil `null` lalu node lagi. Stabilkan dengan `useCallback` jika itu penting.

Callback ref berguna untuk daftar dinamis, elemen bersyarat (`{tampil && <div ref={...} />}`), dan menghubungkan library saat node tersedia.

**Biasanya digabungkan dengan:** pengukuran, `ResizeObserver`, dan komponen yang mount bersyarat.

## forwardRef

**Untuk apa:** membiarkan induk memasang ref ke elemen DOM di dalam komponen anak, karena ref tidak diteruskan seperti props biasa (pada React 18 ke bawah).

```jsx
import { forwardRef, useRef } from "react";

const InputCari = forwardRef(function InputCari({ label, id }, ref) {
  return (
    <div>
      <label htmlFor={id}>{label}</label>
      <input id={id} ref={ref} type="search" />
    </div>
  );
});

export default function App() {
  const ref = useRef(null);
  return (
    <>
      <InputCari ref={ref} id="cari" label="Cari" />
      <button type="button" onClick={() => ref.current?.focus()}>
        Fokus
      </button>
    </>
  );
}
```

Tanpa `forwardRef`, `ref={ref}` pada `InputCari` tidak sampai ke `<input>`. `forwardRef` memberi argument kedua: `ref`.

Nama fungsi di dalam `forwardRef` muncul di React DevTools. Komponen hasil `forwardRef` bisa menerima `displayName` jika perlu.

`ref` bukan bagian dari `props` pada React 18. Jangan menulis `function InputCari({ ref })` di versi itu.

**Biasanya digabungkan dengan:** desain sistem (Input, Button), fokus terprogram, dan `useImperativeHandle`. [forwardRef](https://react.dev/reference/react/forwardRef).

## Ref sebagai prop (React 19)

**Untuk apa:** menulis komponen yang menerima `ref` seperti prop biasa, tanpa `forwardRef`.

```jsx
function InputCari({ label, id, ref }) {
  return (
    <div>
      <label htmlFor={id}>{label}</label>
      <input id={id} ref={ref} type="search" />
    </div>
  );
}
```

React 19 memperlakukan `ref` sebagai prop biasa pada function component. `forwardRef` tetap didukung untuk kode lama. Jika proyekmu masih React 18, pakai `forwardRef`.

Contoh ensiklopedia ini tetap menunjukkan `forwardRef` karena banyak materi kuliah dan dependensi belum pindah. Baca `package.json`: `"react": "19.x"` vs `"18.x"`.

**Biasanya digabungkan dengan:** migrasi bertahap, dan library UI yang masih mengekspor `forwardRef`.

## useImperativeHandle

**Untuk apa:** mengekspos **sedikit metode** ke induk, bukan seluruh node DOM.

```jsx
import { forwardRef, useImperativeHandle, useRef } from "react";

const KotakKomentar = forwardRef(function KotakKomentar({ label, id }, ref) {
  const dalam = useRef(null);

  useImperativeHandle(ref, () => ({
    fokus() {
      dalam.current?.focus();
    },
    bersihkan() {
      if (dalam.current) dalam.current.value = "";
    },
  }));

  return (
    <div>
      <label htmlFor={id}>{label}</label>
      <textarea id={id} ref={dalam} rows={4} />
    </div>
  );
});

export default function App() {
  const komentarRef = useRef(null);
  return (
    <>
      <KotakKomentar ref={komentarRef} id="komentar" label="Komentar" />
      <button type="button" onClick={() => komentarRef.current?.fokus()}>
        Fokus
      </button>
      <button type="button" onClick={() => komentarRef.current?.bersihkan()}>
        Bersihkan
      </button>
    </>
  );
}
```

Induk memanggil `fokus()` dan `bersihkan()`, tidak mengutak-atik DOM seenaknya. Itu memudahkan kamu mengganti `<textarea>` menjadi editor lain nanti.

Argument ketiga opsional: dependensi, seperti `useEffect`. Jika kamu membaca props di dalam factory, sertakan.

Jangan memakai ini sebagai pengganti props/state. Kalau induk hanya perlu “apakah terbuka”, kirim `terbuka` + `onTutup`. API imperatif untuk fokus, scroll, animasi, atau reset library luar.

**Biasanya digabungkan dengan:** `forwardRef`, modal (“fokuskan tombol tutup”), dan form wizard. [useImperativeHandle](https://react.dev/reference/react/useImperativeHandle).

## Menggabungkan ref

**Untuk apa:** komponen yang harus memasang ref internal **dan** meneruskan ref dari luar.

```jsx
import { forwardRef, useRef } from "react";

function gabungRef(...refs) {
  return (node) => {
    for (const ref of refs) {
      if (!ref) continue;
      if (typeof ref === "function") ref(node);
      else ref.current = node;
    }
  };
}

const Input = forwardRef(function Input(props, refLuar) {
  const refDalam = useRef(null);

  function handleBlur() {
    console.log(refDalam.current?.value);
  }

  return (
    <input
      {...props}
      ref={gabungRef(refDalam, refLuar)}
      onBlur={handleBlur}
    />
  );
});
```

Pola `gabungRef` menulisi object ref dan memanggil callback ref. Library sering menyediakan `composeRefs`. Di React 19, beberapa kasus lebih sederhana karena `ref` adalah prop.

Jangan menugaskan `refLuar.current = refDalam` di badan render tanpa mempertimbangkan callback ref.

**Biasanya digabungkan dengan:** desain sistem, `useImperativeHandle` (sering lebih bersih: ref luar mendapat API, ref dalam tetap DOM), dan library animasi.

## File input dan media

**Untuk apa:** mengendalikan elemen yang API-nya memang imperatif.

File:

```jsx
import { useRef } from "react";

export default function App() {
  const fileRef = useRef(null);
  const [nama, setNama] = useState("");

  function pilih() {
    fileRef.current?.click();
  }

  function ganti(event) {
    const file = event.target.files?.[0];
    setNama(file ? file.name : "");
  }

  return (
    <>
      <input
        ref={fileRef}
        type="file"
        hidden
        onChange={ganti}
      />
      <button type="button" onClick={pilih}>Unggah gambar</button>
      {nama && <p>File: {nama}</p>}
    </>
  );
}
```

`type="file"` tidak dikontrol lewat `value` string seperti teks. Baca `files` saat `onChange`.

Video:

```jsx
function Pemutar({ src }) {
  const videoRef = useRef(null);
  return (
    <>
      <video ref={videoRef} src={src} />
      <button type="button" onClick={() => videoRef.current?.play()}>Putar</button>
      <button type="button" onClick={() => videoRef.current?.pause()}>Jeda</button>
    </>
  );
}
```

**Biasanya digabungkan dengan:** `URL.createObjectURL` untuk pratinjau, dan state `sedangMain` jika UI harus menampilkan ikon sesuai status ( dengarkan event `play`/`pause`).

## Menyimpan id timer dan prev props

**Untuk apa:** dua resep ref yang sering muncul di tugas.

Debounce ketikan tanpa library:

```jsx
import { useRef, useState } from "react";

export default function App({ onCari }) {
  const [teks, setTeks] = useState("");
  const timerRef = useRef(null);

  function handleUbah(event) {
    const nilai = event.target.value;
    setTeks(nilai);
    clearTimeout(timerRef.current);
    timerRef.current = setTimeout(() => {
      onCari(nilai);
    }, 300);
  }

  return <input value={teks} onChange={handleUbah} />;
}
```

Bersihkan timer saat unmount dengan Effect:

```jsx
useEffect(() => {
  return () => clearTimeout(timerRef.current);
}, []);
```

Nilai props sebelumnya (jarang diperlukan; pikirkan dulu apakah `key` atau turunan cukup):

```jsx
function usePrevious(nilai) {
  const ref = useRef();
  useEffect(() => {
    ref.current = nilai;
  }, [nilai]);
  return ref.current;
}
```

`usePrevious` mengembalikan nilai render lalu. Berguna untuk animasi “dari-ke”, bukan untuk logika bisnis sehari-hari.

**Biasanya digabungkan dengan:** pencarian live, `useEffect` cleanup, dan custom Hook.

## Kesalahan umum bab ini

- **Menulis `ref.current` lalu mengira UI berubah.** Pakai state.
- **Membaca ref DOM saat render untuk ditampilkan.** Node mungkin belum ada; ukur di Effect/layout Effect.
- **Memberi ref ke function component tanpa `forwardRef` (React 18).**
- **Mengekspos seluruh DOM lewat `useImperativeHandle` tanpa alasan.** Lebih baik teruskan ref ke elemen, atau batasi metode.
- **Membuat callback ref inline yang mengubah state tanpa stabilisasi**, sehingga loop pasang-lepas.
- **Menyimpan data server di ref** lalu heran mengapa anak tidak terbarui.
- **Menggunakan ref untuk “menghindari render” pada data yang sebenarnya terlihat.**

Latihan: komponen `InputUang` yang `forwardRef` ke input, plus `useImperativeHandle` dengan `fokus` dan `pilihSemua`. Di App, tombol memanggil keduanya.

## Ref ke banyak elemen

**Untuk apa:** menyimpan node per id tanpa membuat Hook di dalam loop (dilarang).

```jsx
import { useRef } from "react";

export default function App({ item }) {
  const petaRef = useRef(new Map());

  function daftar(id, node) {
    if (node) petaRef.current.set(id, node);
    else petaRef.current.delete(id);
  }

  function gulirKe(id) {
    petaRef.current.get(id)?.scrollIntoView({ behavior: "smooth" });
  }

  return (
    <>
      <button type="button" onClick={() => gulirKe(item[0]?.id)}>
        Ke item pertama
      </button>
      <ul>
        {item.map((x) => (
          <li key={x.id} ref={(node) => daftar(x.id, node)}>
            {x.nama}
          </li>
        ))}
      </ul>
    </>
  );
}
```

Callback ref menulis/menghapus Map. Jangan `item.map(() => useRef())`.

**Biasanya digabungkan dengan:** daftar panjang, “loncat ke pesan”, dan callback ref.

## Jangan baca/tulis ref DOM untuk konten yang React kelola

**Untuk apa:** menghindari dua dalang pada node yang sama.

```jsx
// Hindari jika React juga merender teks ini
ref.current.textContent = "Baru";
ref.current.classList.add("aktif");
```

Render berikutnya bisa menimpa perubahanmu, atau sebaliknya: React tidak tahu class yang kamu tambah. Untuk teks tampilan pakai state. Untuk class, `className` dari state. Ref untuk **metode** (`focus`, `play`) dan pengukuran.

Pengecualian: library yang memang menguasai subtree (peta). Mount di `div` kosong lewat ref, jangan biarkan React mengisi anak yang sama.

**Biasanya digabungkan dengan:** Effect setup/cleanup library pihak ketiga.

## forwardRef + TypeScript secara konsep

**Untuk apa:** di JavaScript tetap berguna tahu apa yang `ref` isikan.

Tanpa `useImperativeHandle`, `ref.current` adalah node (`HTMLInputElement`). Dengan `useImperativeHandle`, `ref.current` adalah object API (`{ fokus, bersihkan }`). Jangan mencampur harapan: induk yang memanggil `.focus()` pada API kustom akan gagal jika kamu menamai metodenya `fokus`.

Dokumentasikan API singkat di komentar atas komponen.

**Biasanya digabungkan dengan:** satu sumber nama metode, dan contoh pemakaian di `App`.
