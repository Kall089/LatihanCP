# 13 — Resep dan kesalahan

[← 12 Web API](12-web-api-singkat.md) · [Indeks](README.md)

Kumpulan pola siap pakai dan jebakan yang sama berulang. Tiap resep merujuk method di file lain.

## Daftar isi

- [Resep: total keranjang](#resep-total-keranjang)
- [Resep: tambah item unik](#resep-tambah-item-unik)
- [Resep: hapus item](#resep-hapus-item)
- [Resep: cari nama](#resep-cari-nama)
- [Resep: urut harga](#resep-urut-harga)
- [Resep: kelompokkan kategori](#resep-kelompokkan-kategori)
- [Resep: format uang](#resep-format-uang)
- [Resep: baca angka form](#resep-baca-angka-form)
- [Resep: render daftar aman](#resep-render-daftar-aman)
- [Resep: delegation hapus](#resep-delegation-hapus)
- [Resep: submit + fetch](#resep-submit--fetch)
- [Resep: simpan localStorage](#resep-simpan-localstorage)
- [Resep: filter ke URL](#resep-filter-ke-url)
- [Resep: debounce cari](#resep-debounce-cari)
- [Resep: loading dan disabled](#resep-loading-dan-disabled)
- [Resep: default bersarang](#resep-default-bersarang)
- [Resep: unik array](#resep-unik-array)
- [Resep: clamp](#resep-clamp)
- [Resep: paginasi](#resep-paginasi)
- [Resep: deep copy data](#resep-deep-copy-data)
- [Kesalahan: == vs ===](#kesalahan--vs-)
- [Kesalahan: sort angka](#kesalahan-sort-angka)
- [Kesalahan: map tanpa return](#kesalahan-map-tanpa-return)
- [Kesalahan: fetch 404](#kesalahan-fetch-404)
- [Kesalahan: innerHTML pengguna](#kesalahan-innerhtml-pengguna)
- [Kesalahan: this hilang](#kesalahan-this-hilang)
- [Kesalahan: const object](#kesalahan-const-object)
- [Kesalahan: async tanpa catch](#kesalahan-async-tanpa-catch)
- [Kesalahan: listener dobel](#kesalahan-listener-dobel)
- [Kesalahan: bulan Date](#kesalahan-bulan-date)
- [Tabel cepat “jangan / pakai”](#tabel-cepat-jangan--pakai)

## Resep: total keranjang

**Untuk apa:** menjumlah harga × jumlah.

```js
const total = keranjang.reduce(
  (sum, item) => sum + item.harga * item.jumlah,
  0,
);
```

Selalu beri awal `0`. Item harus number, bukan string.

**Biasanya digabungkan dengan:** [reduce](05-array-method-lengkap.md#reduce), [Number](06-string-number-math-date.md#number-fungsi), [Intl.NumberFormat](06-string-number-math-date.md#intlnumberformat).

## Resep: tambah item unik

**Untuk apa:** jika id sudah ada, naikkan jumlah; jika belum, tambah baris.

```js
function tambah(keranjang, produk) {
  const i = keranjang.findIndex((item) => item.id === produk.id);
  if (i === -1) {
    return [...keranjang, { ...produk, jumlah: 1 }];
  }
  return keranjang.with(i, {
    ...keranjang[i],
    jumlah: keranjang[i].jumlah + 1,
  });
}
```

Cadangan tanpa `with`:

```js
return keranjang.map((item, indeks) =>
  indeks === i ? { ...item, jumlah: item.jumlah + 1 } : item,
);
```

**Biasanya digabungkan dengan:** [findIndex](05-array-method-lengkap.md#findindex), [with](05-array-method-lengkap.md#with), [spread](04-object-destructure-spread.md#spread-object).

## Resep: hapus item

**Untuk apa:** membuang baris menurut id.

```js
const sisa = keranjang.filter((item) => item.id !== id);
```

Jangan `splice` pada salinan yang sedang di-render di React tanpa niat mutasi.

**Biasanya digabungkan dengan:** [filter](05-array-method-lengkap.md#filter) dan delegation.

## Resep: cari nama

**Untuk apa:** saring daftar dari kotak teks.

```js
function cari(daftar, q) {
  const kunci = q.trim().toLowerCase();
  if (kunci === "") {
    return daftar;
  }
  return daftar.filter((item) => item.nama.toLowerCase().includes(kunci));
}
```

**Biasanya digabungkan dengan:** [trim](06-string-number-math-date.md#trim--trimstart--trimend), [includes](06-string-number-math-date.md#includesstring), event `input`.

## Resep: urut harga

**Untuk apa:** naik atau turun tanpa merusak array asli.

```js
function urutHarga(daftar, arah = "naik") {
  const tanda = arah === "turun" ? -1 : 1;
  return daftar.toSorted((a, b) => (a.harga - b.harga) * tanda);
}
```

Tanpa `toSorted`: `daftar.slice().sort((a, b) => a.harga - b.harga)`.

**Biasanya digabungkan dengan:** [toSorted](05-array-method-lengkap.md#tosorted) dan `<select>`.

## Resep: kelompokkan kategori

**Untuk apa:** object `kategori → array`.

```js
const kelompok = produk.reduce((akum, item) => {
  const kunci = item.kategori ?? "lain";
  akum[kunci] ??= [];
  akum[kunci].push(item);
  return akum;
}, {});
```

**Biasanya digabungkan dengan:** [reduce](05-array-method-lengkap.md#reduce), [??](01-tipe-variabel-operator.md#operator-nullish--), [Object.entries](04-object-destructure-spread.md#objectentries).

## Resep: format uang

**Untuk apa:** tampilan rupiah.

```js
const rupiah = new Intl.NumberFormat("id-ID", {
  style: "currency",
  currency: "IDR",
  maximumFractionDigits: 0,
});

export function formatRupiah(nilai) {
  return rupiah.format(nilai);
}
```

Jangan menghitung dengan hasil `format` (itu string).

**Biasanya digabungkan dengan:** module [export](11-module-timer-console.md#export-named) dan `map` label.

## Resep: baca angka form

**Untuk apa:** menolak teks kosong dan non-angka.

```js
function bacaJumlah(teks) {
  const n = Number(String(teks).trim());
  if (!Number.isInteger(n) || n < 1 || n > 99) {
    throw new Error("Jumlah 1–99");
  }
  return n;
}
```

Atau `input.valueAsNumber` + cek `Number.isInteger`.

**Biasanya digabungkan dengan:** [Number.isInteger](06-string-number-math-date.md#numberisinteger), [throw](02-kondisi-loop-error.md#throw), form 09.

## Resep: render daftar aman

**Untuk apa:** data → elemen tanpa `innerHTML` dari field.

```js
function render(daftar, root) {
  const frag = document.createDocumentFragment();
  for (const item of daftar) {
    const li = document.createElement("li");
    li.dataset.id = String(item.id);
    const nama = document.createElement("span");
    nama.textContent = item.nama;
    const tombol = document.createElement("button");
    tombol.type = "button";
    tombol.dataset.aksi = "hapus";
    tombol.dataset.id = String(item.id);
    tombol.textContent = "Hapus";
    li.append(nama, tombol);
    frag.append(li);
  }
  root.replaceChildren(frag);
}
```

**Biasanya digabungkan dengan:** [createElement](08-dom-selector-classlist-dataset.md#createelement), [textContent](08-dom-selector-classlist-dataset.md#textcontent), [replaceChildren](08-dom-selector-classlist-dataset.md#replacechildren).

## Resep: delegation hapus

**Untuk apa:** satu listener untuk semua tombol hapus.

```js
daftar.addEventListener("click", (event) => {
  const tombol = event.target.closest("[data-aksi='hapus']");
  if (!tombol || !daftar.contains(tombol)) {
    return;
  }
  const id = Number(tombol.dataset.id);
  state.keranjang = state.keranjang.filter((item) => item.id !== id);
  simpan(state.keranjang);
  render(state.keranjang, daftar);
});
```

**Biasanya digabungkan dengan:** [closest](08-dom-selector-classlist-dataset.md#closest), [dataset](08-dom-selector-classlist-dataset.md#dataset), [filter](05-array-method-lengkap.md#filter).

## Resep: submit + fetch

**Untuk apa:** kirim form JSON tanpa reload.

```js
form.addEventListener("submit", async (event) => {
  event.preventDefault();
  const data = Object.fromEntries(new FormData(form));
  data.nama = String(data.nama ?? "").trim();
  if (data.nama === "") {
    pesan.textContent = "Nama wajib diisi";
    return;
  }
  tombol.disabled = true;
  try {
    const respons = await fetch("/api/pesan", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    });
    if (!respons.ok) {
      throw new Error(`HTTP ${respons.status}`);
    }
    form.reset();
    pesan.textContent = "Terkirim";
  } catch (error) {
    pesan.textContent = error.message;
  } finally {
    tombol.disabled = false;
  }
});
```

**Biasanya digabungkan dengan:** [FormData](09-event-form-delegation.md#formdata), [fetch POST](10-fetch-async-storage.md#fetch-post-json), [finally](07-json-set-map-promise.md#finally).

## Resep: simpan localStorage

**Untuk apa:** baca/tulis array dengan cadangan rusak.

```js
const KUNCI = "keranjang";

export function baca() {
  try {
    const mentah = localStorage.getItem(KUNCI);
    const data = mentah ? JSON.parse(mentah) : [];
    return Array.isArray(data) ? data : [];
  } catch {
    return [];
  }
}

export function simpan(daftar) {
  try {
    localStorage.setItem(KUNCI, JSON.stringify(daftar));
  } catch {
    console.warn("Gagal menyimpan");
  }
}
```

**Biasanya digabungkan dengan:** [JSON](07-json-set-map-promise.md#jsonparse), [localStorage](10-fetch-async-storage.md#localstorage), [Array.isArray](05-array-method-lengkap.md#arrayisarray).

## Resep: filter ke URL

**Untuk apa:** kotak cari yang bisa di-refresh.

```js
function sinkronUrl(q) {
  const u = new URL(location.href);
  if (q.trim()) {
    u.searchParams.set("q", q.trim());
  } else {
    u.searchParams.delete("q");
  }
  history.replaceState(null, "", u);
}

const awal = new URLSearchParams(location.search).get("q") ?? "";
cari.value = awal;
render(cariNama(produk, awal));
```

**Biasanya digabungkan dengan:** [URLSearchParams](12-web-api-singkat.md#urlsearchparams), [history](12-web-api-singkat.md#history).

## Resep: debounce cari

**Untuk apa:** menunggu berhenti mengetik.

```js
function debounce(fn, jeda = 300) {
  let id;
  return (...args) => {
    clearTimeout(id);
    id = setTimeout(() => fn(...args), jeda);
  };
}

const terapkan = debounce((teks) => {
  sinkronUrl(teks);
  render(cariNama(produk, teks));
});

cari.addEventListener("input", () => terapkan(cari.value));
```

Baca `cari.value` saat timer jalan, atau kirim string terbaru sebagai argumen seperti di atas.

**Biasanya digabungkan dengan:** [setTimeout](11-module-timer-console.md#settimeout), [input](09-event-form-delegation.md#input).

## Resep: loading dan disabled

**Untuk apa:** mencegah klik ganda saat request.

```js
async function muat() {
  tombol.disabled = true;
  status.hidden = false;
  status.textContent = "Memuat…";
  try {
    const data = await ambilProduk();
    render(data);
    status.hidden = true;
  } catch (error) {
    status.textContent = error.message;
  } finally {
    tombol.disabled = false;
  }
}
```

**Biasanya digabungkan dengan:** [hidden](08-dom-selector-classlist-dataset.md#hidden), [async](07-json-set-map-promise.md#async--await).

## Resep: default bersarang

**Untuk apa:** kota dari profil yang bisa kosong.

```js
const kota = pengguna.profil?.alamat?.kota ?? "Belum diisi";
```

**Biasanya digabungkan dengan:** [?.](01-tipe-variabel-operator.md#optional-chaining-), [??](01-tipe-variabel-operator.md#operator-nullish--).

## Resep: unik array

**Untuk apa:** membuang duplikat nilai primitif.

```js
const unik = [...new Set(tag)];
```

Untuk object menurut id:

```js
const peta = new Map(daftar.map((item) => [item.id, item]));
const unik = [...peta.values()];
```

Yang belakangan menimpa jika id sama.

**Biasanya digabungkan dengan:** [Set](07-json-set-map-promise.md#set), [Map](07-json-set-map-promise.md#map).

## Resep: clamp

**Untuk apa:** memaksa angka di antara min dan max.

```js
function clamp(n, min, max) {
  return Math.min(max, Math.max(min, n));
}

const halaman = clamp(mentah, 1, halamanMaks);
```

**Biasanya digabungkan dengan:** [Math.min](06-string-number-math-date.md#mathmin--mathmax), paginasi.

## Resep: paginasi

**Untuk apa:** potong daftar di klien.

```js
function halamanOf(daftar, halaman, ukuran = 12) {
  const maks = Math.max(1, Math.ceil(daftar.length / ukuran));
  const h = clamp(halaman, 1, maks);
  const awal = (h - 1) * ukuran;
  return {
    item: daftar.slice(awal, awal + ukuran),
    halaman: h,
    totalHalaman: maks,
  };
}
```

**Biasanya digabungkan dengan:** [slice](05-array-method-lengkap.md#slice), [Math.ceil](06-string-number-math-date.md#mathceil).

## Resep: deep copy data

**Untuk apa:** salin keranjang bersarang.

```js
const salinan = structuredClone(keranjang);
```

Jika hanya JSON-safe dan `Date` boleh jadi string: `JSON.parse(JSON.stringify(x))` — biasanya lebih buruk.

**Biasanya digabungkan dengan:** [structuredClone](04-object-destructure-spread.md#structuredclone), undo.

## Kesalahan: == vs ===

**Untuk apa:** menghindari konversi diam-diam.

```js
5 == "5"; // true, mengecoh
5 === "5"; // false
```

Ubah tipe dulu, lalu `===`.

**Biasanya digabungkan dengan:** [===](01-tipe-variabel-operator.md#operator--).

## Kesalahan: sort angka

**Untuk apa:** mengingat sort default adalah string.

```js
[10, 2, 3].sort(); // salah
[10, 2, 3].toSorted((a, b) => a - b); // benar
```

**Biasanya digabungkan dengan:** [sort](05-array-method-lengkap.md#sort).

## Kesalahan: map tanpa return

**Untuk apa:** kurung kurawal butuh `return`.

```js
produk.map((p) => {
  p.nama;
}); // [undefined, undefined, ...]

produk.map((p) => p.nama);
```

**Biasanya digabungkan dengan:** [map](05-array-method-lengkap.md#map), [arrow](03-fungsi-scope-this-closure.md#arrow-function).

## Kesalahan: fetch 404

**Untuk apa:** status HTTP tidak melempar.

```js
const respons = await fetch("/api/produk/999");
// tidak masuk catch
if (!respons.ok) {
  throw new Error("Tidak ketemu");
}
```

**Biasanya digabungkan dengan:** [respons.ok](10-fetch-async-storage.md#responsok-dan-status).

## Kesalahan: innerHTML pengguna

**Untuk apa:** mencegah XSS.

```js
// jangan
el.innerHTML = input.value;

// pakai
el.textContent = input.value;
```

**Biasanya digabungkan dengan:** [textContent](08-dom-selector-classlist-dataset.md#textcontent).

## Kesalahan: this hilang

**Untuk apa:** method jadi callback.

```js
// setTimeout(obj.metode, 0); // this rusak
setTimeout(() => obj.metode(), 0);
```

**Biasanya digabungkan dengan:** [bind](03-fungsi-scope-this-closure.md#bind), arrow.

## Kesalahan: const object

**Untuk apa:** `const` tidak mengunci isi.

```js
const produk = { harga: 1 };
produk.harga = 2; // boleh
```

Pakai object baru + spread jika ingin alur tidak mutasi.

**Biasanya digabungkan dengan:** [const](01-tipe-variabel-operator.md#const), [freeze](04-object-destructure-spread.md#objectfreeze).

## Kesalahan: async tanpa catch

**Untuk apa:** Promise ditolak yang tidak ditangani.

```js
muat(); // jika muat async dan gagal, error tidak tertangkap di sini
muat().catch(console.error);
```

Di handler, bungkus `try/catch` di dalam `async`.

**Biasanya digabungkan dengan:** [async](07-json-set-map-promise.md#async--await).

## Kesalahan: listener dobel

**Untuk apa:** `render` memasang `click` tiap kali, aksi berulang.

Pasang listener sekali di induk, atau `cloneNode` + delegation.

```js
// di inisialisasi, bukan di dalam render
daftar.addEventListener("click", onHapus);
```

**Biasanya digabungkan dengan:** [delegation](09-event-form-delegation.md#event-delegation).

## Kesalahan: bulan Date

**Untuk apa:** `getMonth()` 0–11.

```js
const d = new Date(2026, 8, 22); // September
String(d.getMonth() + 1).padStart(2, "0"); // "09"
```

ISO tanggal-only bisa bergeser zona.

**Biasanya digabungkan dengan:** [Date](06-string-number-math-date.md#new-date).

## Tabel cepat “jangan / pakai”

| Jangan | Pakai |
| --- | --- |
| `var` | `const` / `let` |
| `==` | `===` setelah konversi |
| `for...in` array | `for...of` / method |
| `sort()` angka | pembanding `a - b` |
| `innerHTML` input | `textContent` |
| `typeof []` | `Array.isArray` |
| `isNaN("x")` | `Number.isNaN` / `Number.isFinite` |
| `fetch` tanpa `ok` | `if (!respons.ok)` |
| `localStorage` object mentah | `JSON.stringify` |
| `Math.random` id aman | `crypto.randomUUID` |
| `onclick` menimpa | `addEventListener` |
| listener per item | delegation |
| `getMonth()` + 0 | + 1 untuk tampilan manusia |
| mutasi di `map` | object baru |
| `Promise.all` jika sebagian boleh gagal | `allSettled` |

## Alur toko mini

1. Baca `produk` dari API ([fetch](10-fetch-async-storage.md#fetch-get)).
2. Saring dengan `input` ([cari](#resep-cari-nama)).
3. Render ke `ul` ([render aman](#resep-render-daftar-aman)).
4. Klik tambah lewat delegation ([file 09](09-event-form-delegation.md)).
5. Ubah array dengan `filter`/`with` ([file 05](05-array-method-lengkap.md)).
6. Simpan ([localStorage](#resep-simpan-localstorage)).
7. Format total ([uang](#resep-format-uang)).

Jika satu langkah gagal, cek kesalahan di tabel, bukan menulis ulang semua.

## Checklist debug

1. Console: ada error merah? Baca baris file.
2. `typeof` / `Array.isArray` / `console.table` data.
3. Network: status, body, CORS.
4. Elements: kelas dan `data-*` terpasang?
5. Apakah listener terpasang dua kali? `console.count`.
6. Apakah state yang dirender bukan state yang diubah (salah referensi)?

**Biasanya digabungkan dengan:** [console](11-module-timer-console.md#consolelog) dan DevTools.

## Indeks method yang paling sering

- Data: `const`, `===`, `?.`, `??`, destructure, spread
- Daftar: `map`, `filter`, `find`, `reduce`, `some`, `includes`, `toSorted`, `slice`
- Teks: `trim`, `toLowerCase`, `includes`, `slice`, `split`, `join`
- Angka: `Number`, `Number.isFinite`, `Math.min`, `Math.round`, `Intl.NumberFormat`
- Async: `async/await`, `fetch`, `respons.ok`, `JSON.parse`
- DOM: `querySelector`, `textContent`, `classList`, `dataset`, `addEventListener`, `closest`
- Simpan: `localStorage`, `JSON.stringify`
- Browser: `URLSearchParams`, `AbortController`, `crypto.randomUUID`

Buka file 01–12 untuk katalog lengkap tiap nama itu.
