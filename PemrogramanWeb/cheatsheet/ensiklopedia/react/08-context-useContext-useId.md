# 08 — Context, useContext, dan useId

[← Reducer](07-useReducer-useSyncExternalStore.md) · [Daftar](README.md) · [Lanjut: custom Hook →](09-custom-hook-pola.md)

Context mengirim nilai ke keturunan tanpa props berantai. `useContext` membacanya. `useId` membuat identitas unik yang stabil antara server dan client, terutama untuk menghubungkan label dan input.

## Daftar isi

- [Masalah props drilling](#masalah-props-drilling)
- [createContext dan Provider](#createcontext-dan-provider)
- [useContext](#usecontext)
- [Nilai default vs null](#nilai-default-vs-null)
- [Custom Hook pemakai Context](#custom-hook-pemakai-context)
- [Memecah Context](#memecah-context)
- [Menstabilkan value](#menstabilkan-value)
- [Tema dan user](#tema-dan-user)
- [Kapan jangan Context](#kapan-jangan-context)
- [useId](#useid)
- [useId untuk banyak field](#useid-untuk-banyak-field)
- [useId dan CSS identifier](#useid-dan-css-identifier)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Provider bersarang dan jarak baca](#provider-bersarang-dan-jarak-baca)
- [Context untuk locale, bukan untuk setiap string](#context-untuk-locale-bukan-untuk-setiap-string)
- [useId di daftar field dinamis](#useid-di-daftar-field-dinamis)
- [Checklist memasang Context](#checklist-memasang-context)

## Masalah props drilling

**Untuk apa:** mengenali kapan data melewati komponen yang tidak memakainya.

```jsx
function App() {
  const user = { nama: "Haikal" };
  return <Halaman user={user} />;
}
function Halaman({ user }) {
  return <Dasbor user={user} />;
}
function Dasbor({ user }) {
  return <Menu user={user} />;
}
function Menu({ user }) {
  return <p>{user.nama}</p>;
}
```

`Halaman` dan `Dasbor` hanya meneruskan `user`. Jika banyak nilai (tema, locale, keranjang), daftar props membengkak.

Drilling **boleh** untuk 1–2 tingkat. Context berguna jika banyak cabang jauh membutuhkan data yang sama, atau library harus menyediakan nilai tanpa kamu mengubah tiap perantara.

**Biasanya digabungkan dengan:** lifting state dulu (naikkan ke nenek terdekat), baru Context jika jaraknya jauh. [Passing data with context](https://react.dev/learn/passing-data-deeply-with-context).

## createContext dan Provider

**Untuk apa:** membuat saluran nilai dan menempatkan sumbernya di pohon.

```jsx
import { createContext, useState } from "react";

export const TemaContext = createContext(null);

export function TemaProvider({ children }) {
  const [tema, setTema] = useState("terang");
  return (
    <TemaContext.Provider value={{ tema, setTema }}>
      {children}
    </TemaContext.Provider>
  );
}
```

`createContext(defaultValue)` dipanggil di **modul**, bukan di dalam komponen. Satu Context = satu “jenis” data.

Provider menentukan nilai untuk keturunannya. Provider bersarang menimpa nilai kakek untuk cucu di dalamnya. Saudara di luar Provider tidak melihat nilai itu.

Bungkus dekat pemakai, bukan selalu di akar jika hanya satu halaman yang butuh.

```jsx
export default function App() {
  return (
    <TemaProvider>
      <Isi />
    </TemaProvider>
  );
}
```

**Biasanya digabungkan dengan:** `useContext`, custom Hook, dan `children` pada Provider.

## useContext

**Untuk apa:** membaca nilai Provider terdekat di atas komponen pemanggil.

```jsx
import { useContext } from "react";
import { TemaContext } from "./TemaContext";

export function TombolTema() {
  const { tema, setTema } = useContext(TemaContext);

  return (
    <button
      type="button"
      onClick={() => setTema(tema === "terang" ? "gelap" : "terang")}
    >
      Tema: {tema}
    </button>
  );
}
```

Jika tidak ada Provider, `useContext` mengembalikan default dari `createContext`. Jika default `null`, destructuring meledak — itu alasan custom Hook memeriksa.

Komponen yang memanggil `useContext` rerender saat `value` Provider berubah (menurut `Object.is`). Itu sebabnya object baru `{ tema, setTema }` setiap render Provider membuat semua konsumen rerender.

`useContext` harus dipanggil di tingkat atas, seperti Hook lain.

**Biasanya digabungkan dengan:** Provider di induk, dan memecah Context jika sebagian konsumen terlalu sering rerender. [useContext](https://react.dev/reference/react/useContext).

## Nilai default vs null

**Untuk apa:** memilih default yang jujur.

```jsx
const TemaContext = createContext({
  tema: "terang",
  setTema: () => {},
});
```

Default object membuat komponen “berjalan” tanpa Provider, tetapi `setTema` kosong menyembunyikan kesalahan pemasangan.

```jsx
const TemaContext = createContext(null);
```

`null` memaksa kamu menulis Provider, dan Hook bisa melempar pesan jelas. Lebih aman untuk tugas dan aplikasi.

Default berguna untuk Context yang memang opsional (misalnya “kepadatan UI”) dengan fallback masuk akal.

Jangan memakai default untuk data yang harus unik per sesi (user login). Tanpa Provider, kamu tidak punya user sungguhan.

**Biasanya digabungkan dengan:** error di custom Hook, dan tes yang sengaja tidak memasang Provider untuk memastikan error muncul.

## Custom Hook pemakai Context

**Untuk apa:** menyembunyikan `useContext` dan memberi pesan jika Provider ketinggalan.

```jsx
import { createContext, useContext, useState } from "react";

const TemaContext = createContext(null);

export function TemaProvider({ children }) {
  const [tema, setTema] = useState("terang");
  const value = { tema, setTema };
  return <TemaContext.Provider value={value}>{children}</TemaContext.Provider>;
}

export function useTema() {
  const nilai = useContext(TemaContext);
  if (!nilai) {
    throw new Error("useTema harus dipakai di dalam TemaProvider");
  }
  return nilai;
}
```

Pemakai hanya `const { tema, setTema } = useTema()`. File lain tidak perlu mengimpor object Context.

Pola yang sama untuk `useAuth`, `useKeranjang`, `useLocale`.

**Biasanya digabungkan dengan:** [custom Hook](09-custom-hook-pola.md), dan mengekspor hanya Provider + Hook (Context tetap privat).

## Memecah Context

**Untuk apa:** mengurangi rerender: yang hanya mengirim aksi tidak perlu membaca state.

```jsx
const StateContext = createContext(null);
const DispatchContext = createContext(null);

export function TokoProvider({ children }) {
  const [state, dispatch] = useReducer(reducer, awal);
  return (
    <StateContext.Provider value={state}>
      <DispatchContext.Provider value={dispatch}>
        {children}
      </DispatchContext.Provider>
    </StateContext.Provider>
  );
}
```

Atau pecah menurut domain: `UserContext` dan `TemaContext` terpisah, bukan satu object raksasa `{ user, tema, keranjang, locale }`. Perubahan tema tidak perlu merender seluruh pemakai user — masih merender pemakai object gabungan jika digabung.

Memecah tidak otomatis mencegah rerender anak DOM; itu mencegah komponen yang **memanggil** Context yang berubah.

**Biasanya digabungkan dengan:** `useReducer`, `memo` pada tombol, dan [file 07](07-useReducer-useSyncExternalStore.md).

## Menstabilkan value

**Untuk apa:** menghindari object `value` baru setiap render Provider.

```jsx
import { useMemo, useState } from "react";

export function TemaProvider({ children }) {
  const [tema, setTema] = useState("terang");
  const value = useMemo(() => ({ tema, setTema }), [tema]);
  return <TemaContext.Provider value={value}>{children}</TemaContext.Provider>;
}
```

`setTema` stabil. `value` hanya baru saat `tema` berubah. Tanpa `useMemo`, `value={{ tema, setTema }}` baru setiap kali Provider rerender karena parent-nya.

Di React 19, compiler bisa mengotomatiskan sebagian memo. Tetap pahami masalahnya: identitas `value` adalah sinyal untuk konsumen.

Jangan `useMemo` tanpa dependensi yang benar (`[]` padahal berisi `tema`).

**Biasanya digabungkan dengan:** `useMemo`, `useCallback` untuk fungsi tambahan di value, dan memecah Context.

## Tema dan user

**Untuk apa:** dua resep yang paling sering diminta tugas.

Tema (class pada `document` atau pembungkus):

```jsx
export function TemaProvider({ children }) {
  const [tema, setTema] = useState("terang");
  return (
    <TemaContext.Provider value={{ tema, setTema }}>
      <div className={`app tema-${tema}`}>{children}</div>
    </TemaContext.Provider>
  );
}
```

User:

```jsx
const AuthContext = createContext(null);

export function AuthProvider({ children }) {
  const [user, setUser] = useState(null);

  function masuk(data) {
    setUser(data);
  }

  function keluar() {
    setUser(null);
  }

  const value = { user, masuk, keluar, sudahMasuk: Boolean(user) };
  return <AuthContext.Provider value={value}>{children}</AuthContext.Provider>;
}
```

`sudahMasuk` bisa dihitung di pemakai. Menyertakannya di value menambah field tetapi memudahkan JSX.

Jangan menyimpan password di Context. Jangan menganggap Context menggantikan cookie/session server.

**Biasanya digabungkan dengan:** `localStorage` (hati-hati XSS), fetch profil, dan route terlindungi di Next.js (cek di server lebih aman).

## Kapan jangan Context

**Untuk apa:** menolak godaan “global state untuk semua”.

Jangan Context jika:

- hanya dua komponen berdekatan — kirim props
- data berasal dari server untuk satu halaman — fetch di halaman itu
- kamu ingin menghindari menulis props “karena malas”
- setiap input form dimasukkan ke Context global

Context bukan pengganti URL. Filter yang ingin bisa di-share tautannya lebih cocok `searchParams` (Next.js) daripada Context.

Context juga bukan cache jaringan. Library data (atau Server Component) menangani cache, status, dan revalidate.

**Biasanya digabungkan dengan:** props, reducer lokal, dan URL sebagai sumber kebenaran navigasi.

## useId

**Untuk apa:** menghasilkan id unik yang **cocok antara HTML server dan client**, untuk atribut aksesibilitas.

```jsx
import { useId } from "react";

export function InputNama({ label, value, onChange }) {
  const id = useId();
  return (
    <div>
      <label htmlFor={id}>{label}</label>
      <input id={id} value={value} onChange={onChange} />
    </div>
  );
}
```

Tanpa `useId`, `id="nama"` bentrok jika dua `InputNama` ada di halaman. `id={Math.random()}` pecah hidrasi karena server dan client berbeda.

`useId` menghasilkan string seperti `:r1:` (format bisa berbeda). Jangan memakainya sebagai key daftar — key harus dari data.

Panggil `useId` di tingkat atas. Satu panggilan per id dasar; turunkan dengan sufiks jika perlu beberapa id terkait.

**Biasanya digabungkan dengan:** `htmlFor`, `aria-describedby`, `aria-labelledby`, form terbungkus. [useId](https://react.dev/reference/react/useId).

## useId untuk banyak field

**Untuk apa:** menghubungkan input, pesan error, dan petunjuk tanpa tabrakan.

```jsx
import { useId } from "react";

export function InputEmail({ value, onChange, error }) {
  const dasar = useId();
  const idInput = `${dasar}-input`;
  const idError = `${dasar}-error`;
  const idHint = `${dasar}-hint`;

  return (
    <div>
      <label htmlFor={idInput}>Email</label>
      <input
        id={idInput}
        type="email"
        value={value}
        onChange={onChange}
        aria-describedby={`${idHint} ${error ? idError : ""}`.trim()}
        aria-invalid={Boolean(error)}
      />
      <p id={idHint}>Kami tidak membagikan email.</p>
      {error && (
        <p id={idError} role="alert">
          {error}
        </p>
      )}
    </div>
  );
}
```

Satu `useId` + sufiks menjaga hubungan tetap unik per instance komponen, dan tetap stabil.

Untuk daftar field dinamis, `useId` di tiap item komponen sudah cukup. Jangan membuat id dari indeks saja jika daftar berubah.

**Biasanya digabungkan dengan:** validasi form, `role="alert"`, dan desain sistem input.

## useId dan CSS identifier

**Untuk apa:** menghindari selector CSS yang rusak karena karakter di id.

Id dari `useId` bisa mengandung tanda yang tidak nyaman di CSS (`:`). Jika kamu membutuhkan id untuk `url(#id)` pada SVG (clipPath, gradient):

```jsx
function Ikon({ judul }) {
  const id = useId().replace(/:/g, "");
  return (
    <svg>
      <title>{judul}</title>
      <defs>
        <linearGradient id={id}>
          <stop offset="0%" stopColor="#333" />
          <stop offset="100%" stopColor="#999" />
        </linearGradient>
      </defs>
      <rect fill={`url(#${id})`} width="24" height="24" />
    </svg>
  );
}
```

Dokumentasi React merekomendasikan `useId` untuk aksesibilitas dan hubungan aria, bukan sebagai pengganti `key` atau id database.

Jangan mengandalkan format string spesifik antarversi React.

**Biasanya digabungkan dengan:** SVG, `aria-*`, dan menghindari `id` global hardcode di komponen reusable.

## Kesalahan umum bab ini

- **`createContext` di dalam komponen.** Setiap render membuat Context baru; Provider dan konsumen tidak bertemu.
- **Object `value` baru setiap render tanpa kebutuhan.**
- **Satu Context raksasa untuk seluruh aplikasi.**
- **Memakai Context menggantikan props untuk komponen presentasi murni.** Sulit diuji dan dilacak.
- **`useId` sebagai `key` pada `map`.**
- **Id hardcode di komponen yang dipakai dua kali.** Label mengarah ke input yang salah.
- **Membaca Context di Server Component Next.js tanpa memahami batasan.** Banyak Context user/tema adalah Client Component.
- **Lupa Provider lalu heran nilai selalu default.**

Latihan: `TemaProvider` + `useTema` + tombol toggle. Dua `InputNama` di satu halaman memakai `useId` agar label tidak bentrok.

## Provider bersarang dan jarak baca

**Untuk apa:** memahami Provider mana yang “menang” jika ada dua nilai sejenis.

```jsx
<TemaProvider>
  <Halaman>
    <TemaContext.Provider value={{ tema: "gelap", setTema: () => {} }}>
      <Kartu />
    </TemaContext.Provider>
    <Kartu />
  </Halaman>
</TemaProvider>
```

`Kartu` di dalam Provider dalam membaca `"gelap"`. `Kartu` saudara di luarnya membaca nilai `TemaProvider` luar. `useContext` selalu mengambil Provider **terdekat ke atas**.

Jangan menumpuk Provider palsu hanya untuk tes di produksi. Di tes, membungkus `Kartu` dengan Provider khusus justru berguna: kamu memberi user/tema palsu tanpa merender seluruh app.

**Biasanya digabungkan dengan:** story/tes komponen, dan menghindari Provider global yang sulit di-override.

## Context untuk locale, bukan untuk setiap string

**Untuk apa:** membagikan `locale` (`id-ID`) agar format uang/tanggal konsisten.

```jsx
const LocaleContext = createContext("id-ID");

export function useRupiah(angka) {
  const locale = useContext(LocaleContext);
  return angka.toLocaleString(locale, {
    style: "currency",
    currency: "IDR",
    maximumFractionDigits: 0,
  });
}
```

Komponen tampilan tetap menerima `harga` lewat props. Yang dari Context hanya **cara memformat**. Itu batas yang sehat: data item tetap eksplisit, preferensi global lewat Context.

Jangan memasukkan seluruh kamus terjemahan ke Context jika library i18n sudah mengurusnya.

**Biasanya digabungkan dengan:** `toLocaleString`, dan props untuk data bisnis.

## useId di daftar field dinamis

**Untuk apa:** setiap baris form dinamis punya hubungan label–input sendiri.

```jsx
function BarisTamu({ index, nama, onGanti, onHapus }) {
  const id = useId();
  return (
    <div>
      <label htmlFor={id}>Tamu {index + 1}</label>
      <input
        id={id}
        value={nama}
        onChange={(e) => onGanti(e.target.value)}
      />
      <button type="button" onClick={onHapus}>Hapus</button>
    </div>
  );
}
```

`useId` per instance `BarisTamu` cukup. `key` pada `BarisTamu` tetap dari data (`tamu.id`), bukan dari `useId`. Jika baris dihapus di tengah, `key` data menjaga state input yang benar.

**Biasanya digabungkan dengan:** [file 03](03-list-key-conditional.md) tentang key vs id aksesibilitas.

## Checklist memasang Context

1. `createContext(null)` di file modul.
2. Provider dengan state/`useReducer` di dekat akar fitur.
3. `value` distabilkan atau dipecah.
4. Hook `useX` melempar jika `null`.
5. Komponen dalam memanggil Hook, komponen luar tidak perlu tahu object Context.
6. Jangan memasukkan fungsi fetch ke Context kecuali memang cache sesi; lebih baik Hook data.

Jika langkah 6 meragukan: mulai dari props. Context bisa ditambah nanti tanpa mengubah bentuk data, hanya cara mengantarnya.
