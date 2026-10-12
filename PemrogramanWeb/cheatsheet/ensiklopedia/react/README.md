# Ensiklopedia Cheatsheet React.js

[← Cheatsheet React ringkas](../../react-js.md) · [Cheatsheet utama](../../README.md)

Ini adalah ensiklopedia React untuk menjawab tiga pertanyaan setiap API:

1. **Untuk apa** API ini dipakai?
2. Bagaimana **kodenya** dalam function component + Hooks?
3. **Biasanya digabungkan dengan** API atau pola mana?

Contoh memakai **function component** dan **Hooks**. Class component hanya muncul sebagai perbandingan singkat. Bahasa disusun agar mudah dibaca; tiap potongan kode adalah contoh terpisah kecuali dinyatakan sebagai rangkaian.

Dokumentasi resmi yang relevan: [react.dev](https://react.dev/). Contoh di sini merujuk pola React modern (React 18/19): function component, Hooks, batching otomatis, dan Concurrent Features. Cocokkan versi `react` di `package.json` dengan perilaku yang kamu uji.

## Cara memakai folder ini

- Buka file sesuai topik, lalu cari nama API (`useState`, `useEffect`, `key`, `createPortal`).
- Jangan menempelkan semua contoh ke satu `App.jsx`. Salin **satu** contoh, jalankan, ubah satu nilai, amati hasilnya.
- Nama file di atas blok kode (jika ada) menunjukkan tempat menulisnya di proyek latihanmu. Folder ini berisi referensi, bukan proyek yang bisa dijalankan langsung.
- Untuk proyek latihan cepat: `npm create vite@latest latihan-react -- --template react` lalu ganti isi `src/App.jsx`.
- Setelah React, lanjut ke [Next.js](../../next-js.md) jika kamu membutuhkan routing, Server Component, atau endpoint API.

## Daftar file

| File | Isi utama |
| --- | --- |
| [01-jsx-komponen-props-children.md](01-jsx-komponen-props-children.md) | JSX, function component, props, `children`, Fragment, komposisi |
| [02-state-event-form.md](02-state-event-form.md) | `useState`, event, form controlled, update object/array |
| [03-list-key-conditional.md](03-list-key-conditional.md) | `map`, `key`, render bersyarat, daftar kosong |
| [04-useEffect-useLayoutEffect-useInsertionEffect.md](04-useEffect-useLayoutEffect-useInsertionEffect.md) | Effect, cleanup, dependensi, layout, CSS-in-JS |
| [05-useRef-useImperativeHandle-forwardRef.md](05-useRef-useImperativeHandle-forwardRef.md) | Ref DOM, nilai mutable, `forwardRef`, API imperatif |
| [06-useMemo-useCallback-memo-useDeferredValue-useTransition.md](06-useMemo-useCallback-memo-useDeferredValue-useTransition.md) | Mengingat hasil, menunda update, transisi |
| [07-useReducer-useSyncExternalStore.md](07-useReducer-useSyncExternalStore.md) | State beraksi, store eksternal |
| [08-context-useContext-useId.md](08-context-useContext-useId.md) | Context, ID unik untuk aksesibilitas |
| [09-custom-hook-pola.md](09-custom-hook-pola.md) | Pola custom Hook yang sering dipakai |
| [10-fetch-pola-loading-error.md](10-fetch-pola-loading-error.md) | Fetch client, loading, error, abort |
| [11-portal-suspense-error-boundary.md](11-portal-suspense-error-boundary.md) | Portal, `lazy`, Suspense, Error Boundary |
| [12-aturan-hooks-kesalahan.md](12-aturan-hooks-kesalahan.md) | Aturan Hooks dan kesalahan yang sering muncul |
| [13-katalog-api-react.md](13-katalog-api-react.md) | Katalog API: `createElement`, Fragment, StrictMode, dan lainnya |

## Peta belajar singkat

Urutan yang nyaman:

1. JSX dan komponen (file 01)
2. State, event, form (file 02)
3. Daftar dan kondisi (file 03)
4. Effect (file 04) lalu fetch (file 10)
5. Ref bila perlu menyentuh DOM (file 05)
6. Context dan reducer bila state mulai menyebar (file 07–08)
7. Custom Hook agar logika tidak diduplikasi (file 09)
8. Memo/transisi hanya jika ada alasan ukurannya (file 06)
9. Portal, Suspense, Error Boundary untuk kasus khusus (file 11)
10. Katalog API untuk mencari nama fungsi (file 13)

Jangan menghafal semua API sekaligus. `useState`, JSX, props, `map` + `key`, dan form controlled sudah cukup untuk banyak tugas kuliah.

## Function component vs class (satu paragraf)

Class component (`class Toko extends React.Component`) adalah cara lama: state lewat `this.state` / `this.setState`, siklus hidup lewat `componentDidMount`, dan event perlu diikat ke `this`. Function component + Hooks menggantikannya untuk kode baru: satu fungsi mengembalikan JSX, state lewat `useState`/`useReducer`, sinkronisasi lewat `useEffect`. Ensiklopedia ini memakai function component. Class masih muncul di Error Boundary klasik dan di codebase lama; kamu tidak perlu menulis class untuk fitur harian.

## Konvensi contoh

- Nama komponen diawali huruf besar: `KartuProduk`, bukan `kartuProduk`.
- Event handler memakai `type="button"` kecuali tombol itu memang mengirim form.
- Input punya `label` dan `id`/`htmlFor`.
- Daftar memakai `key` dari ID data, bukan indeks, kecuali daftar statis yang tidak diurut/dihapus.
- Fetch di client memakai `AbortController` bila request bisa ketinggalan zaman.
- Pesan status memakai `role="status"` atau `aria-live` bila relevan.

## Yang tidak dibahas di sini

- Routing, Server Component, dan metadata: lihat [next-js.md](../../next-js.md).
- CSS murni dan Tailwind: lihat [css.md](../../css.md).
- JavaScript dasar (`map`, `filter`, `fetch`): lihat [javascript.md](../../javascript.md).
- Backend Laravel: lihat [laravel.md](../../laravel.md).

React mengatur **antarmuka**. Data tetap perlu sumber: array lokal, `fetch` ke API, atau Server Component di Next.js.

## Glosarium singkat

| Istilah | Arti di folder ini |
| --- | --- |
| Komponen | Fungsi berhuruf besar yang mengembalikan JSX |
| Props | Data dari induk ke anak; hanya dibaca anak |
| State | Data milik komponen yang memicu render saat berubah |
| Render | React memanggil komponenmu dan membandingkan hasilnya dengan layar |
| Commit | React menerapkan perubahan ke DOM |
| Hook | Fungsi `use*` yang terikat urutan panggilan instance |
| Effect | Sinkronisasi ke sistem luar setelah (atau sebelum) cat |
| Ref | Object `{ current }` yang berubah tanpa render |
| Context | Saluran nilai ke keturunan tanpa props berantai |
| Key | Identitas item daftar untuk rekonsiliasi |
| Controlled | Nilai input dipegang state React |
| Concurrent | React boleh menyela/menunda pekerjaan render tidak mendesak |
| Hidrasi | Menempelkan event ke HTML yang sudah ada dari server |
| Portal | JSX terpasang di node DOM lain, tetap anak React |
| Suspense | Menampilkan fallback sementara anak menunggu |
| Error Boundary | Menangkap error render di subtree (class) |

## API wajib vs belakangan

Wajib untuk tugas awal: JSX, props, `children`, `useState`, event, form controlled, `map` + `key`, render bersyarat.

Sering perlu: `useEffect` + fetch + abort, custom Hook kecil, lifting state.

Belakangan: Context, `useReducer`, ref DOM, portal/modal.

Hanya jika ada alasan: `useMemo`/`memo`/`useTransition`, `useSyncExternalStore`, `useInsertionEffect`, `flushSync`, `cloneElement`.

## Cara membaca tiap bab

Setiap bab mengikuti pola yang sama:

1. **Untuk apa** — masalah yang diselesaikan, bukan definisi kamus semata.
2. Blok kode yang bisa disalin ke `App.jsx` (satu contoh per percobaan).
3. Penjelasan jebakan di bawah kode.
4. **Biasanya digabungkan dengan** — API pasangan, agar tidak dipelajari terisolasi.

Tautan `[react.dev]` di banyak bagian mengarah ke rujukan resmi. Jika contoh di sini dan dokumen resmi berbeda karena versi, ikuti versi di `package.json`.

## Proyek latihan yang disarankan

```bash
npm create vite@latest latihan-react -- --template react
cd latihan-react
npm install
npm run dev
```

Ganti `src/App.jsx`. Impor CSS di `src/App.css` bila perlu. Jangan menumpuk 13 bab ke satu file.

Setelah nyaman, buat tiga halaman mental (atau rute Next.js): katalog produk, form kontak, dan modal konfirmasi. Itu sudah menyentuh file 01–05, 10, dan 11.
