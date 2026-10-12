# Ensiklopedia Cheatsheet JavaScript

Katalog method dan API JavaScript, satu per satu. Bukan esai teori. Setiap entri menjawab: **untuk apa, contoh pendek, biasanya digabungkan dengan apa.**

Bahasa Indonesia mudah. Contoh memakai toko, keranjang, form, dan daftar produk.

[← Cheatsheet utama](../../README.md) · [Ringkasan JS](../../javascript.md)

## Cara memakai folder ini

1. Buka file sesuai topik, lalu cari nama method di daftar isi.
2. Baca **Untuk apa** dulu, baru salin kode.
3. Contoh adalah potongan terpisah. Jangan menempelkan semua contoh ke satu file.
4. Setelah menyalin, ubah satu nilai dan lihat hasilnya di Console browser.

Urutan belajar: **01 tipe → 02 kondisi → 03 fungsi → 04 object → 05 array → 06 string/angka → 07 async dasar → 08 DOM → 09 event → 10 fetch → 11 module → 12 Web API → 13 resep**.

## Daftar file

| File | Isi |
| --- | --- |
| [01-tipe-variabel-operator.md](01-tipe-variabel-operator.md) | `let`, `const`, tipe data, operator, konversi, `typeof` |
| [02-kondisi-loop-error.md](02-kondisi-loop-error.md) | `if`, `switch`, loop, `break`, `try/catch`, `throw` |
| [03-fungsi-scope-this-closure.md](03-fungsi-scope-this-closure.md) | fungsi, parameter, `this`, `bind`, closure, callback |
| [04-object-destructure-spread.md](04-object-destructure-spread.md) | object, destructure, spread, `Object.keys` dan kawan-kawannya |
| [05-array-method-lengkap.md](05-array-method-lengkap.md) | `map`, `filter`, `reduce`, `sort`, `splice`, dan method array lain |
| [06-string-number-math-date.md](06-string-number-math-date.md) | method string, `Number`, `Math`, `Date`, `Intl` |
| [07-json-set-map-promise.md](07-json-set-map-promise.md) | `JSON`, `Set`, `Map`, `Promise`, `async/await` |
| [08-dom-selector-classlist-dataset.md](08-dom-selector-classlist-dataset.md) | selector, classList, dataset, node, atribut |
| [09-event-form-delegation.md](09-event-form-delegation.md) | event, form, `FormData`, event delegation |
| [10-fetch-async-storage.md](10-fetch-async-storage.md) | `fetch`, status HTTP, `localStorage`, `sessionStorage` |
| [11-module-timer-console.md](11-module-timer-console.md) | `import/export`, timer, `console` |
| [12-web-api-singkat.md](12-web-api-singkat.md) | `URL`, `AbortController`, observer, `matchMedia`, `crypto` |
| [13-resep-dan-kesalahan.md](13-resep-dan-kesalahan.md) | resep kerja dan kesalahan yang sering muncul |

## Peta cepat: “Saya ingin…”

### Menyimpan dan membandingkan data

- Nama data: [01 — `let` / `const`](01-tipe-variabel-operator.md#let)
- Bandingkan ketat: [01 — `===`](01-tipe-variabel-operator.md#operator--)
- Cadangan jika kosong: [01 — `??`](01-tipe-variabel-operator.md#operator-nullish--)
- Akses aman: [01 — `?.`](01-tipe-variabel-operator.md#optional-chaining-)

### Memilih dan mengulang

- Cabang: [02 — `if`](02-kondisi-loop-error.md#if)
- Banyak kasus: [02 — `switch`](02-kondisi-loop-error.md#switch)
- Daftar: [02 — `for...of`](02-kondisi-loop-error.md#forof)
- Error: [02 — `try/catch`](02-kondisi-loop-error.md#try--catch--finally)

### Membungkus langkah

- Fungsi biasa: [03 — deklarasi](03-fungsi-scope-this-closure.md#function-declaration)
- Fungsi pendek: [03 — arrow](03-fungsi-scope-this-closure.md#arrow-function)
- Mengingat lingkungan: [03 — closure](03-fungsi-scope-this-closure.md#closure)
- Mengikat `this`: [03 — `bind`](03-fungsi-scope-this-closure.md#bind)

### Mengolah object dan array

- Ambil properti: [04 — destructure](04-object-destructure-spread.md#destructuring-object)
- Salin object: [04 — spread](04-object-destructure-spread.md#spread-object)
- Ubah daftar: [05 — `map`](05-array-method-lengkap.md#map)
- Saring daftar: [05 — `filter`](05-array-method-lengkap.md#filter)
- Jumlahkan: [05 — `reduce`](05-array-method-lengkap.md#reduce)
- Cari satu item: [05 — `find`](05-array-method-lengkap.md#find)

### Teks, angka, tanggal

- Potong teks: [06 — `slice`](06-string-number-math-date.md#slicestring)
- Cari teks: [06 — `includes`](06-string-number-math-date.md#includesstring)
- Bulatkan: [06 — `Math.round`](06-string-number-math-date.md#mathround)
- Format uang: [06 — `Intl.NumberFormat`](06-string-number-math-date.md#intlnumberformat)

### Data dari server dan penyimpanan

- JSON: [07 — `JSON.parse`](07-json-set-map-promise.md#jsonparse)
- Janji async: [07 — `Promise`](07-json-set-map-promise.md#promise)
- Ambil API: [10 — `fetch`](10-fetch-async-storage.md#fetch-get)
- Simpan di browser: [10 — `localStorage`](10-fetch-async-storage.md#localstorage)

### Halaman dan klik

- Ambil elemen: [08 — `querySelector`](08-dom-selector-classlist-dataset.md#queryselector)
- Kelas CSS: [08 — `classList`](08-dom-selector-classlist-dataset.md#classlistadd)
- Klik: [09 — `addEventListener`](09-event-form-delegation.md#addeventlistener)
- Banyak tombol: [09 — delegation](09-event-form-delegation.md#event-delegation)

## Aturan singkat yang sering dipakai

- Pakai `const` dulu. Ganti ke `let` hanya jika nilainya akan ditugaskan ulang.
- Bandingkan dengan `===`, bukan `==`.
- Array diolah dengan method (`map`, `filter`, `find`), bukan `for...in`.
- Jangan memakai `innerHTML` untuk teks dari pengguna.
- `fetch` yang gagal jaringan melempar error; status `404` tidak otomatis melempar.
- `localStorage` hanya menyimpan string.

## Contoh yang saling terkait

Bayangkan toko:

1. Data produk adalah array object → file 04 dan 05.
2. Nama produk adalah string → file 06.
3. Halaman menampilkan kartu → file 08.
4. Tombol “Tambah” memakai event → file 09.
5. Daftar produk datang dari API → file 07 dan 10.
6. Keranjang disimpan di `localStorage` → file 10.

Resep lengkap ada di [13-resep-dan-kesalahan.md](13-resep-dan-kesalahan.md).

## Catatan ruang lingkup

Contoh memakai JavaScript modern (ES modules, `const`/`let`, optional chaining, `fetch`). Beberapa API hanya ada di browser, bukan di Node.js biasa: DOM, `localStorage`, `document`, `window`.

Dokumentasi dirujuk pada **22 September 2026**. Cocokkan perilaku dengan browser yang kamu pakai.
