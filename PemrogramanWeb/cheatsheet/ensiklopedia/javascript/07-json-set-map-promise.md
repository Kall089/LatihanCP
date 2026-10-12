# 07 — JSON, Set, Map, dan Promise

[← 06 String](06-string-number-math-date.md) · [Indeks](README.md) · [Lanjut 08 →](08-dom-selector-classlist-dataset.md)

JSON menukar data dengan teks. Set menyimpan nilai unik. Map menyimpan pasangan kunci-nilai. Promise menangani kerja yang selesai nanti.

## Daftar isi

- [JSON.stringify](#jsonstringify)
- [JSON.parse](#jsonparse)
- [replacer dan space](#replacer-dan-space)
- [reviver](#reviver)
- [batasan JSON](#batasan-json)
- [Set](#set)
- [Set.prototype.add](#setprototypeadd)
- [Set.prototype.has](#setprototypehas)
- [Set.prototype.delete](#setprototypedelete)
- [Set.prototype.clear](#setprototypeclear)
- [Set.prototype.size](#setprototypesize)
- [iterasi Set](#iterasi-set)
- [Set.prototype.union](#setprototypeunion)
- [Set.prototype.intersection](#setprototypeintersection)
- [Set.prototype.difference](#setprototypedifference)
- [Set.prototype.symmetricDifference](#setprototypesymmetricdifference)
- [Set.prototype.isSubsetOf](#setprototypeissubsetof)
- [Set.prototype.isSupersetOf](#setprototypeissupersetof)
- [Set.prototype.isDisjointFrom](#setprototypeisdisjointfrom)
- [WeakSet](#weakset)
- [Map](#map)
- [Map.prototype.set](#mapprototypeset)
- [Map.prototype.get](#mapprototypeget)
- [Map.prototype.has](#mapprototypehas)
- [Map.prototype.delete](#mapprototypedelete)
- [Map.prototype.clear](#mapprototypeclear)
- [Map.prototype.size](#mapprototypesize)
- [iterasi Map](#iterasi-map)
- [WeakMap](#weakmap)
- [Promise](#promise)
- [then](#then)
- [catch](#catch)
- [finally](#finally)
- [Promise.resolve](#promiseresolve)
- [Promise.reject](#promisereject)
- [Promise.all](#promiseall)
- [Promise.allSettled](#promiseallsettled)
- [Promise.race](#promiserace)
- [Promise.any](#promiseany)
- [Promise.withResolvers](#promisewithresolvers)
- [async / await](#async--await)
- [microtask singkat](#microtask-singkat)

## JSON.stringify

**Untuk apa:** mengubah nilai JavaScript menjadi teks JSON.

```js
const produk = { nama: "Buku", harga: 45000 };
const teks = JSON.stringify(produk);
// '{"nama":"Buku","harga":45000}'
```

Pakai sebelum `localStorage.setItem` atau body `fetch`.

Array dan object bersarang didukung jika isinya JSON-safe.

```js
JSON.stringify([{ id: 1 }, { id: 2 }]);
```

**Biasanya digabungkan dengan:** `localStorage`, `fetch`, dan `JSON.parse`.

## JSON.parse

**Untuk apa:** membaca teks JSON menjadi nilai JavaScript.

```js
const teks = '{"nama":"Buku","harga":45000}';
const produk = JSON.parse(teks);
console.log(produk.nama);
```

Teks rusak melempar `SyntaxError`. Bungkus `try/catch`.

```js
function bacaJson(teks, cadangan) {
  try {
    return JSON.parse(teks);
  } catch {
    return cadangan;
  }
}
```

**Biasanya digabungkan dengan:** `respons.json()` (sudah parse), storage, dan file 02.

## replacer dan space

**Untuk apa:** menyaring field atau merapikan output.

```js
JSON.stringify(produk, ["nama", "harga"]);
JSON.stringify(produk, null, 2); // indent 2 spasi
```

`replacer` fungsi:

```js
JSON.stringify(produk, (kunci, nilai) => {
  if (kunci === "rahasia") {
    return undefined; // field dihilangkan
  }
  return nilai;
});
```

**Biasanya digabungkan dengan:** log debug dan buang field sensitif.

## reviver

**Untuk apa:** mengubah nilai saat parse.

```js
const teks = '{"dibuat":"2026-09-22T00:00:00.000Z"}';
const data = JSON.parse(teks, (kunci, nilai) => {
  if (kunci === "dibuat") {
    return new Date(nilai);
  }
  return nilai;
});
```

**Biasanya digabungkan dengan:** Date, BigInt (hati-hati, JSON standar tidak punya BigInt).

## batasan JSON

**Untuk apa:** tahu apa yang hilang atau gagal.

Tidak didukung / berubah:

- `undefined` (field object hilang; di array jadi `null`)
- fungsi, `Symbol`
- `NaN`, `Infinity` menjadi `null`
- `Date` menjadi string ISO lewat `toJSON`
- `Map`/`Set` menjadi `{}` kecuali kamu ubah dulu
- referensi putar → `TypeError`

```js
JSON.stringify({ a: undefined, b: () => 1 }); // "{}"
JSON.stringify([undefined]); // "[null]"
```

Ubah Set/Map dulu:

```js
JSON.stringify({ tag: [...tagSet] });
JSON.stringify(Object.fromEntries(peta));
```

**Biasanya digabungkan dengan:** `Array.from`, `Object.fromEntries`, `structuredClone` untuk salin lokal.

## Set

**Untuk apa:** kumpulan nilai unik. Duplikat diabaikan.

```js
const tag = new Set(["buku", "alat", "buku"]);
console.log(tag.size); // 2
```

Perbandingan seperti `===`. Object berbeda meskipun isinya sama.

```js
new Set([{ id: 1 }, { id: 1 }]).size; // 2
```

Dari array ke unik:

```js
const unik = [...new Set(daftar)];
```

**Biasanya digabungkan dengan:** filter tag, id tercentang, dan hapus duplikat.

## Set.prototype.add

**Untuk apa:** menambah nilai. Mengembalikan Set itu sendiri.

```js
const tag = new Set();
tag.add("buku").add("alat");
tag.add("buku"); // tetap satu
```

**Biasanya digabungkan dengan:** klik checkbox dan chaining.

## Set.prototype.has

**Untuk apa:** mengecek keanggotaan, biasanya lebih jelas daripada `array.includes` untuk banyak cek.

```js
tag.has("buku"); // true
```

**Biasanya digabungkan dengan:** `filter` daftar produk menurut tag terpilih.

## Set.prototype.delete

**Untuk apa:** menghapus nilai. `true` jika sempat ada.

```js
tag.delete("alat");
```

**Biasanya digabungkan dengan:** uncentang filter.

## Set.prototype.clear

**Untuk apa:** mengosongkan semua.

```js
tag.clear();
```

**Biasanya digabungkan dengan:** tombol “Hapus filter”.

## Set.prototype.size

**Untuk apa:** jumlah anggota. Bukan `.length`.

```js
tag.size;
```

**Biasanya digabungkan dengan:** badge jumlah filter aktif.

## iterasi Set

**Untuk apa:** membaca anggota. Urutan = urutan insert.

```js
for (const nama of tag) {
  console.log(nama);
}
[...tag];
[...tag.values()];
[...tag.keys()]; // sama dengan values
[...tag.entries()]; // [nilai, nilai]
tag.forEach((nilai) => console.log(nilai));
```

**Biasanya digabungkan dengan:** `join`, render chip filter.

## Set.prototype.union

**Untuk apa:** Set baru gabungan dua set. Browser modern.

```js
const a = new Set([1, 2]);
const b = new Set([2, 3]);
[...a.union(b)]; // [1, 2, 3]
```

Cadangan lama: `new Set([...a, ...b])`.

**Biasanya digabungkan dengan:** menggabungkan hak atau tag.

## Set.prototype.intersection

**Untuk apa:** anggota yang ada di kedua set.

```js
[...a.intersection(b)]; // [2]
```

Cadangan:

```js
[...a].filter((x) => b.has(x));
```

**Biasanya digabungkan dengan:** produk yang punya semua tag terpilih.

## Set.prototype.difference

**Untuk apa:** ada di A, tidak di B.

```js
[...a.difference(b)]; // [1]
```

**Biasanya digabungkan dengan:** hak yang belum diberikan.

## Set.prototype.symmetricDifference

**Untuk apa:** ada di salah satu, tidak di keduanya.

```js
[...a.symmetricDifference(b)]; // [1, 3]
```

**Biasanya digabungkan dengan:** banding dua pilihan.

## Set.prototype.isSubsetOf

**Untuk apa:** apakah semua anggota ada di set lain.

```js
new Set([2]).isSubsetOf(b);
```

**Biasanya digabungkan dengan:** cek syarat tag wajib.

## Set.prototype.isSupersetOf

**Untuk apa:** apakah memuat semua anggota set lain.

```js
b.isSupersetOf(new Set([2]));
```

**Biasanya digabungkan dengan:** izin: punya semua kapabilitas.

## Set.prototype.isDisjointFrom

**Untuk apa:** tidak ada irisan.

```js
a.isDisjointFrom(new Set([9]));
```

**Biasanya digabungkan dengan:** konflik jadwal atau id tabrakan.

## WeakSet

**Untuk apa:** menandai object tanpa mencegah garbage collection. Hanya object/fungsi, tidak iterable.

```js
const pernahDilihat = new WeakSet();
pernahDilihat.add(produk);
pernahDilihat.has(produk);
```

Tidak ada `.size`, tidak bisa di-loop. Cocok untuk cap internal, bukan daftar tag UI.

**Biasanya digabungkan dengan:** cache “sudah diproses” pada object DOM/data.

## Map

**Untuk apa:** peta kunci → nilai. Kunci boleh object, number, string.

```js
const harga = new Map();
harga.set("buku", 45000);
harga.set("alat", 8000);
```

Beda dengan object: urutan insert terjaga, kunci bukan hanya string, tidak ada kunci warisan prototipe.

**Biasanya digabungkan dengan:** cache id → elemen, hitung frekuensi, dan pairing.

## Map.prototype.set

**Untuk apa:** menulis nilai. Mengembalikan Map.

```js
harga.set("buku", 47000).set("tas", 120000);
```

Kunci object dibandingkan referensi.

```js
const k = { id: 1 };
peta.set(k, "A");
peta.get({ id: 1 }); // undefined
peta.get(k); // "A"
```

**Biasanya digabungkan dengan:** `get` dan chaining.

## Map.prototype.get

**Untuk apa:** membaca nilai, atau `undefined` jika tidak ada.

```js
harga.get("buku");
harga.get("tidak-ada"); // undefined
```

Bedakan “tidak ada” dan “nilai `undefined`” dengan `has`.

**Biasanya digabungkan dengan:** `??` default.

## Map.prototype.has

**Untuk apa:** cek kunci.

```js
harga.has("buku");
```

**Biasanya digabungkan dengan:** `get` dan increment:

```js
const hitung = new Map();
hitung.set(tag, (hitung.get(tag) ?? 0) + 1);
```

## Map.prototype.delete

**Untuk apa:** hapus satu kunci.

```js
harga.delete("alat");
```

**Biasanya digabungkan dengan:** cache invalidasi.

## Map.prototype.clear

**Untuk apa:** kosongkan semua.

```js
harga.clear();
```

**Biasanya digabungkan dengan:** reset filter/cache.

## Map.prototype.size

**Untuk apa:** jumlah pasangan.

```js
harga.size;
```

**Biasanya digabungkan dengan:** cek cache kosong.

## iterasi Map

**Untuk apa:** membaca isi. Urutan insert.

```js
for (const [kunci, nilai] of harga) {
  console.log(kunci, nilai);
}
[...harga.keys()];
[...harga.values()];
[...harga.entries()];
harga.forEach((nilai, kunci) => console.log(kunci, nilai));
```

Ke object / dari object:

```js
Object.fromEntries(harga);
new Map(Object.entries(obj));
```

**Biasanya digabungkan dengan:** `Object.fromEntries`, JSON (setelah diubah).

## WeakMap

**Untuk apa:** kunci hanya object; tidak mencegah GC; tidak iterable.

```js
const meta = new WeakMap();
meta.set(elemen, { sudahInit: true });
meta.get(elemen);
```

Cocok menyimpan data tambahan pada DOM node tanpa bocor memori.

**Biasanya digabungkan dengan:** metadata elemen dan cache object.

## Promise

**Untuk apa:** mewakili hasil yang belum tentu siap: sukses atau gagal.

```js
const janji = new Promise((resolve, reject) => {
  const sukses = true;
  if (sukses) {
    resolve({ nama: "Buku" });
  } else {
    reject(new Error("Gagal"));
  }
});
```

Jangan bungkus jika API sudah mengembalikan Promise (`fetch`).

Executor jalan segera. `resolve`/`reject` sekali; sisanya diabaikan.

**Biasanya digabungkan dengan:** `then`, `await`, dan API async.

## then

**Untuk apa:** mendaftar saat terpenuhi (dan opsional saat ditolak).

```js
janji.then((data) => {
  console.log(data.nama);
});
```

Mengembalikan Promise baru. Return nilai diteruskan; return Promise ditunggu; throw jadi reject.

```js
fetch("/api/produk")
  .then((respons) => respons.json())
  .then((data) => data.map((p) => p.nama));
```

**Biasanya digabungkan dengan:** `catch`, chaining, dan kode tanpa `async`.

## catch

**Untuk apa:** menangkap reject / throw di rantai.

```js
janji
  .then((data) => data.nama)
  .catch((error) => {
    console.error(error.message);
    return "Cadangan";
  });
```

Setelah `catch` yang return nilai, rantai berikutnya sukses lagi.

**Biasanya digabungkan dengan:** `then`, pesan UI, dan cadangan data.

## finally

**Untuk apa:** jalan setelah selesai, sukses atau gagal. Tidak mengubah hasil kecuali melempar.

```js
ambil()
  .then(tampil)
  .catch(tampilError)
  .finally(() => sembunyikanLoading());
```

**Biasanya digabungkan dengan:** spinner, `disabled` tombol, dan tutup dialog.

## Promise.resolve

**Untuk apa:** Promise yang langsung terpenuhi.

```js
Promise.resolve(42);
Promise.resolve(fetch("/api")); // membungkus thenable
```

Berguna di tes atau cabang sync + async yang diseragamkan.

**Biasanya digabungkan dengan:** `Promise.all` dan fungsi yang kadang sync.

## Promise.reject

**Untuk apa:** Promise yang langsung ditolak.

```js
Promise.reject(new Error("Tidak valid"));
```

**Biasanya digabungkan dengan:** guard awal sebelum `fetch`.

## Promise.all

**Untuk apa:** menunggu semua sukses. Jika satu gagal, langsung gagal.

```js
const [produk, kategori] = await Promise.all([
  fetch("/api/produk").then((r) => r.json()),
  fetch("/api/kategori").then((r) => r.json()),
]);
```

Hasil array berurutan sama dengan input, bukan urutan selesai.

**Biasanya digabungkan dengan:** dashboard yang butuh beberapa endpoint.

## Promise.allSettled

**Untuk apa:** menunggu semua selesai, sukses atau gagal, tanpa berhenti di error pertama.

```js
const hasil = await Promise.allSettled([
  fetch("/api/a"),
  fetch("/api/b"),
]);
hasil.forEach((item) => {
  if (item.status === "fulfilled") {
    console.log(item.value);
  } else {
    console.error(item.reason);
  }
});
```

**Biasanya digabungkan dengan:** beberapa request independen, sebagian boleh gagal.

## Promise.race

**Untuk apa:** memakai yang pertama selesai (sukses atau gagal).

```js
const cepat = await Promise.race([
  fetch("/api/produk"),
  timeout(8000),
]);
```

Jika timeout reject lebih dulu, `fetch` tetap jalan di latar kecuali di-abort. Lihat `AbortController` file 12.

**Biasanya digabungkan dengan:** batas waktu dan sumber cadangan.

## Promise.any

**Untuk apa:** sukses pertama. Gagal hanya jika semua gagal (`AggregateError`).

```js
const data = await Promise.any([
  fetch("/mirror-1").then((r) => r.json()),
  fetch("/mirror-2").then((r) => r.json()),
]);
```

**Biasanya digabungkan dengan:** beberapa mirror API.

## Promise.withResolvers

**Untuk apa:** membuat Promise plus `resolve`/`reject` di luar executor. Browser modern.

```js
const { promise, resolve, reject } = Promise.withResolvers();
tombol.addEventListener("click", () => resolve("ok"), { once: true });
await promise;
```

Cadangan lama: simpan `resolve` dari dalam executor.

**Biasanya digabungkan dengan:** menunggu event sekali, dialog konfirmasi.

## async / await

**Untuk apa:** menulis alur Promise seperti kode berurut.

```js
async function ambilProduk() {
  const respons = await fetch("/api/produk");
  if (!respons.ok) {
    throw new Error(`HTTP ${respons.status}`);
  }
  return respons.json();
}
```

`async` selalu mengembalikan Promise. `return` jadi resolve; `throw` jadi reject.

Error ditangkap `try/catch` di sekitar `await`.

```js
try {
  const data = await ambilProduk();
  console.log(data);
} catch (error) {
  console.error(error.message);
}
```

Jangan `await` di dalam loop jika request bisa paralel; kumpulkan lalu `Promise.all`.

```js
const data = await Promise.all(ids.map((id) => ambilSatu(id)));
```

**Biasanya digabungkan dengan:** `fetch` file 10 dan `try/catch` file 02.

## microtask singkat

**Untuk apa:** memahami urutan: kode sync, lalu microtask (`then`/`queueMicrotask`), lalu timer.

```js
console.log("A");
Promise.resolve().then(() => console.log("B"));
setTimeout(() => console.log("C"), 0);
console.log("D");
// A D B C
```

Tidak perlu dihafal untuk toko, tetapi menjelaskan mengapa `then` jalan sebelum `setTimeout(0)`.

**Biasanya digabungkan dengan:** file 11 timer dan debug urutan log.

## Pola: cache Map + Promise

**Untuk apa:** jangan fetch id yang sama dua kali bersamaan.

```js
const cache = new Map();

function ambil(id) {
  if (!cache.has(id)) {
    cache.set(
      id,
      fetch(`/api/produk/${id}`).then((r) => {
        if (!r.ok) {
          cache.delete(id);
          throw new Error("Gagal");
        }
        return r.json();
      }),
    );
  }
  return cache.get(id);
}
```

**Biasanya digabungkan dengan:** detail produk yang dibuka berulang.

## Pola: Set id keranjang

**Untuk apa:** cek cepat apakah produk sudah ada.

```js
const idDiKeranjang = new Set(keranjang.map((item) => item.id));
if (idDiKeranjang.has(produk.id)) {
  console.log("Sudah ada");
}
```

**Biasanya digabungkan dengan:** file 05 `map` dan tombol “Tambah”.

## Kesalahan yang sering

- `JSON.parse` tanpa `try`.
- Men-stringify `Map`/`Set` langsung.
- `Promise.all` jika satu gagal menggugurkan semua, padahal tidak diinginkan.
- Lupa `return` di dalam `then`.
- `async` fungsi dipanggil tanpa `await`/`catch`.
- Mengira `await` mem-blok thread browser (tidak; hanya menunggu Promise).
- Memakai object sebagai kunci Map tanpa menyimpan referensi yang sama.
- Mengharap Set mengunikan object menurut isi.

**Biasanya digabungkan dengan:** file 10 dan 13.
