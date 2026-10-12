# 05 — Method array lengkap

[← 04 Object](04-object-destructure-spread.md) · [Indeks](README.md) · [Lanjut 06 →](06-string-number-math-date.md)

Array adalah daftar berurut. Method di bawah dikatalog satu per satu. Perhatikan mana yang **mengubah array asli** dan mana yang **menghasilkan array baru**.

## Daftar isi

- [Membuat array](#membuat-array)
- [length](#length)
- [akses indeks](#akses-indeks)
- [at](#at)
- [Array.isArray](#arrayisarray)
- [Array.from](#arrayfrom)
- [Array.of](#arrayof)
- [push](#push)
- [pop](#pop)
- [unshift](#unshift)
- [shift](#shift)
- [concat](#concat)
- [slice](#slice)
- [splice](#splice)
- [toSpliced](#tospliced)
- [join](#join)
- [includes](#includes)
- [indexOf](#indexof)
- [lastIndexOf](#lastindexof)
- [find](#find)
- [findIndex](#findindex)
- [findLast](#findlast)
- [findLastIndex](#findlastindex)
- [filter](#filter)
- [map](#map)
- [flat](#flat)
- [flatMap](#flatmap)
- [forEach](#foreach)
- [some](#some)
- [every](#every)
- [reduce](#reduce)
- [reduceRight](#reduceright)
- [sort](#sort)
- [toSorted](#tosorted)
- [reverse](#reverse)
- [toReversed](#toreversed)
- [with](#with)
- [fill](#fill)
- [copyWithin](#copywithin)
- [keys](#keys)
- [values](#values)
- [entries](#entries)
- [Array.fromAsync](#arrayfromasync)
- [toString dan toLocaleString](#tostring-dan-tolocalestring)
- [Peta mengubah vs tidak](#peta-mengubah-vs-tidak)

## Membuat array

**Untuk apa:** membuat daftar kosong atau berisi item.

```js
const kosong = [];
const nama = ["Buku", "Pensil", "Tas"];
const campuran = ["Buku", 45000, true];
```

`new Array(3)` membuat lubang sepanjang 3, bukan `[3]`.

```js
new Array(3); // [empty × 3]
Array.of(3); // [3]
```

Lubang membuat `map`/`forEach` melewatkan indeks. Hindari array berlobang.

**Biasanya digabungkan dengan:** `push`, `map`, dan JSON daftar produk.

## length

**Untuk apa:** jumlah slot array, dari 0 sampai indeks terakhir + 1.

```js
const nama = ["Buku", "Pensil"];
console.log(nama.length); // 2
```

Bisa ditulis untuk memotong:

```js
nama.length = 1; // ["Buku"]
```

Memperbesar `length` membuat lubang. Lebih aman `push`.

Cek kosong:

```js
if (nama.length === 0) {
  console.log("Daftar kosong");
}
```

**Biasanya digabungkan dengan:** `if`, loop `for`, dan pesan keranjang kosong.

## akses indeks

**Untuk apa:** mengambil atau mengganti item di posisi tertentu. Indeks mulai 0.

```js
const nama = ["Buku", "Pensil", "Tas"];
console.log(nama[0]); // "Buku"
console.log(nama[2]); // "Tas"
nama[1] = "Penghapus";
console.log(nama[9]); // undefined
```

Indeks negatif tidak berjalan dengan `[]`:

```js
nama[-1]; // undefined, bukan item terakhir
```

Pakai `at(-1)` untuk dari belakang.

**Biasanya digabungkan dengan:** `length`, `at`, dan loop indeks.

## at

**Untuk apa:** mengambil item, mendukung indeks negatif.

```js
const nama = ["Buku", "Pensil", "Tas"];
console.log(nama.at(0)); // "Buku"
console.log(nama.at(-1)); // "Tas"
console.log(nama.at(-2)); // "Pensil"
console.log(nama.at(9)); // undefined
```

Tidak mengubah array. Lebih jelas daripada `nama[nama.length - 1]`.

**Biasanya digabungkan dengan:** item terakhir keranjang, breadcrumb, dan histori.

## Array.isArray

**Untuk apa:** memastikan nilai benar-benar array.

```js
Array.isArray([]); // true
Array.isArray({}); // false
Array.isArray("Buku"); // false
Array.isArray(null); // false
```

`typeof []` adalah `"object"`, jadi `typeof` tidak cukup.

**Biasanya digabungkan dengan:** guard fungsi yang menerima daftar atau object.

## Array.from

**Untuk apa:** membuat array dari iterable atau array-like, boleh sambil memetakan.

```js
Array.from("Hai"); // ["H", "a", "i"]
Array.from(new Set([1, 1, 2])); // [1, 2]
Array.from({ length: 3 }, (_, i) => i + 1); // [1, 2, 3]
```

Array-like punya `length` dan indeks:

```js
const list = document.querySelectorAll(".kartu");
const teks = Array.from(list, (el) => el.textContent);
```

`querySelectorAll` bukan array; tidak punya `map` di semua alur lama. `Array.from` menormalkannya.

Bisa menyalin array dangkal:

```js
const salinan = Array.from(nama);
```

**Biasanya digabungkan dengan:** `NodeList`, `Set`, `keys()`, dan pembuatan deret.

## Array.of

**Untuk apa:** membuat array dari argumen, tanpa jebakan `new Array(n)`.

```js
Array.of(7); // [7]
Array.of(1, 2, 3); // [1, 2, 3]
Array.of(); // []
```

**Biasanya digabungkan dengan:** membungkus satu nilai menjadi daftar.

## push

**Untuk apa:** menambah item di akhir. Mengubah array asli. Mengembalikan panjang baru.

```js
const keranjang = ["Buku"];
const panjang = keranjang.push("Pensil", "Tas");
console.log(keranjang); // ["Buku", "Pensil", "Tas"]
console.log(panjang); // 3
```

Jangan menulis `keranjang = keranjang.push(...)` karena hasilnya angka.

Untuk gaya tidak mengubah asli:

```js
const baru = [...keranjang, "Penghapus"];
```

**Biasanya digabungkan dengan:** tombol “Tambah”, akumulasi di loop, dan stack.

## pop

**Untuk apa:** mengambil dan menghapus item terakhir. Mengubah array asli.

```js
const tumpukan = ["A", "B", "C"];
const terakhir = tumpukan.pop();
console.log(terakhir); // "C"
console.log(tumpukan); // ["A", "B"]
```

Array kosong: `pop()` → `undefined`.

**Biasanya digabungkan dengan:** undo sederhana dan tumpukan (LIFO).

## unshift

**Untuk apa:** menambah item di depan. Mengubah array asli.

```js
const antrean = ["B", "C"];
antrean.unshift("A");
console.log(antrean); // ["A", "B", "C"]
```

Lebih mahal daripada `push` pada array besar karena semua indeks bergeser.

**Biasanya digabungkan dengan:** notifikasi terbaru di atas dan antrean.

## shift

**Untuk apa:** mengambil dan menghapus item pertama. Mengubah array asli.

```js
const antrean = ["A", "B", "C"];
const pertama = antrean.shift();
console.log(pertama); // "A"
console.log(antrean); // ["B", "C"]
```

**Biasanya digabungkan dengan:** antrean (FIFO) dan pemrosesan berurut.

## concat

**Untuk apa:** menggabungkan array/nilai menjadi array baru. Tidak mengubah asli.

```js
const a = ["Buku"];
const b = ["Pensil"];
const gabung = a.concat(b, "Tas");
console.log(gabung); // ["Buku", "Pensil", "Tas"]
console.log(a); // ["Buku"]
```

Hanya datar satu tingkat: array dalam tetap array.

```js
[1].concat([2, [3]]); // [1, 2, [3]]
```

Spread modern: `[...a, ...b]`. `concat` tetap jelas untuk banyak daftar.

**Biasanya digabungkan dengan:** menggabungkan hasil filter dan daftar default.

## slice

**Untuk apa:** menyalin potongan `[mulai, akhir)` ke array baru. Tidak mengubah asli.

```js
const nama = ["Buku", "Pensil", "Tas", "Rautan"];
nama.slice(1, 3); // ["Pensil", "Tas"]
nama.slice(2); // ["Tas", "Rautan"]
nama.slice(-2); // ["Tas", "Rautan"]
nama.slice(); // salinan dangkal
```

`akhir` tidak ikut. Indeks negatif dihitung dari belakang.

Paginasi sederhana:

```js
const halaman = 2;
const ukuran = 10;
const potong = daftar.slice((halaman - 1) * ukuran, halaman * ukuran);
```

**Biasanya digabungkan dengan:** salinan, paginasi, dan `splice` (jangan tertukar).

## splice

**Untuk apa:** menyisipkan, mengganti, atau menghapus di tengah. **Mengubah array asli.**

```js
const nama = ["Buku", "Pensil", "Tas"];
const terhapus = nama.splice(1, 1);
console.log(terhapus); // ["Pensil"]
console.log(nama); // ["Buku", "Tas"]
```

Sisip tanpa hapus:

```js
nama.splice(1, 0, "Penghapus");
```

Ganti:

```js
nama.splice(0, 1, "Buku Gambar");
```

Argumen: `(mulai, jumlahHapus, ...itemBaru)`.

Jika kamu tidak ingin mengubah asli, pakai `toSpliced` atau `slice` + `concat` / filter.

**Biasanya digabungkan dengan:** hapus item keranjang menurut indeks dan sunting daftar.

## toSpliced

**Untuk apa:** seperti `splice`, tetapi mengembalikan array baru.

```js
const nama = ["Buku", "Pensil", "Tas"];
const tanpaPensil = nama.toSpliced(1, 1);
console.log(nama); // utuh
console.log(tanpaPensil); // ["Buku", "Tas"]
```

**Biasanya digabungkan dengan:** state yang tidak boleh dimutasi (React).

## join

**Untuk apa:** menggabungkan item menjadi string.

```js
["Buku", "Pensil"].join(", "); // "Buku, Pensil"
["2026", "09", "22"].join("-"); // "2026-09-22"
["A", "B"].join(); // "A,B"  default koma
[].join(", "); // ""
```

Item non-string diubah ke teks. `null` dan `undefined` menjadi string kosong.

```js
[1, null, 2].join("-"); // "1--2"
```

Kebalikan kasar: `teks.split(",")` — lihat file 06.

**Biasanya digabungkan dengan:** `map` dulu (ambil `.nama`), lalu `join` untuk tampilan.

## includes

**Untuk apa:** mengecek apakah nilai ada, memakai perbandingan seperti `===` (dan `NaN` ketemu).

```js
const tag = ["buku", "alat", "promo"];
tag.includes("alat"); // true
tag.includes("tas"); // false
tag.includes("alat", 2); // false, mulai indeks 2
```

Tidak cocok untuk object menurut isi:

```js
[{ id: 1 }].includes({ id: 1 }); // false
```

Untuk object, pakai `some` atau `find`.

**Biasanya digabungkan dengan:** filter tag, cek id primitif, dan `if`.

## indexOf

**Untuk apa:** indeks kemunculan pertama, atau `-1` jika tidak ada.

```js
const tag = ["buku", "alat", "buku"];
tag.indexOf("buku"); // 0
tag.indexOf("buku", 1); // 2
tag.indexOf("tas"); // -1
```

Pola cek lama:

```js
if (tag.indexOf("promo") !== -1) {
}
```

`includes` lebih jelas untuk ya/tidak. `indexOf` untuk posisi.

Tidak menemukan `NaN`. Pakai `findIndex` atau `includes`.

**Biasanya digabungkan dengan:** `splice(index, 1)` dan urutan item.

## lastIndexOf

**Untuk apa:** indeks kemunculan terakhir.

```js
["buku", "alat", "buku"].lastIndexOf("buku"); // 2
```

Argumen kedua adalah titik mulai mundur.

**Biasanya digabungkan dengan:** mencari duplikat dari belakang.

## find

**Untuk apa:** item pertama yang lolos uji, atau `undefined`.

```js
const produk = [
  { id: 1, nama: "Buku", harga: 45000 },
  { id: 2, nama: "Pensil", harga: 8000 },
];
const ketemu = produk.find((item) => item.id === 2);
console.log(ketemu?.nama); // "Pensil"
```

Berhenti segera setelah ketemu. Cocok untuk id unik.

Jika tidak ada:

```js
produk.find((item) => item.id === 9); // undefined
```

Callback: `(item, indeks, array) => boolean`.

**Biasanya digabungkan dengan:** `?.`, detail produk, dan klik kartu.

## findIndex

**Untuk apa:** indeks item pertama yang lolos uji, atau `-1`.

```js
const i = produk.findIndex((item) => item.id === 2); // 1
```

Lanjut hapus:

```js
if (i !== -1) {
  produk.splice(i, 1);
}
```

Atau tanpa mutasi:

```js
const sisa = produk.filter((item) => item.id !== 2);
```

**Biasanya digabungkan dengan:** `splice`, `with`, dan update satu baris.

## findLast

**Untuk apa:** seperti `find`, dari belakang.

```js
const log = [
  { id: 1, status: "baru" },
  { id: 2, status: "baru" },
];
const terakhirBaru = log.findLast((item) => item.status === "baru");
```

**Biasanya digabungkan dengan:** histori dan status terbaru.

## findLastIndex

**Untuk apa:** indeks dari belakang.

```js
log.findLastIndex((item) => item.status === "baru");
```

**Biasanya digabungkan dengan:** `toSpliced` / `with` pada entri terakhir yang cocok.

## filter

**Untuk apa:** array baru berisi item yang uji-nya `true`.

```js
const murah = produk.filter((item) => item.harga < 20000);
const tersedia = produk.filter((item) => item.stok > 0);
```

Tidak mengubah asli. Jika tidak ada yang lolos, hasil `[]`, bukan `undefined`.

Hapus satu id:

```js
const sisa = produk.filter((item) => item.id !== 1);
```

Pencarian nama:

```js
const q = "bu";
const hasil = produk.filter((item) =>
  item.nama.toLowerCase().includes(q.toLowerCase()),
);
```

**Biasanya digabungkan dengan:** `map`, input cari, dan checkbox kategori.

## map

**Untuk apa:** array baru sepanjang sama, tiap item diubah.

```js
const nama = produk.map((item) => item.nama);
const label = produk.map((item) => `${item.nama} — Rp${item.harga}`);
```

Tidak mengubah asli, kecuali kamu mengubah object yang sama di dalam (referensi).

```js
// berbahaya jika object dipakai di tempat lain
produk.map((item) => {
  item.harga *= 2;
  return item;
});

// lebih aman
produk.map((item) => ({ ...item, harga: item.harga * 2 }));
```

`map` wajib punya `return` jika memakai `{ }`.

Jangan memakai `map` jika kamu tidak butuh array hasil; pakai `forEach`.

**Biasanya digabungkan dengan:** `filter`, `join`, render daftar, dan React.

## flat

**Untuk apa:** meratakan array dalam, default 1 tingkat.

```js
[1, [2, 3], [4]].flat(); // [1, 2, 3, 4]
[1, [2, [3]]].flat(); // [1, 2, [3]]
[1, [2, [3]]].flat(2); // [1, 2, 3]
[1, [2, [3]]].flat(Infinity); // rata semua
```

Lubang dihilangkan. Tidak mengubah asli.

**Biasanya digabungkan dengan:** hasil `map` yang mengembalikan array, sebelum ada `flatMap`.

## flatMap

**Untuk apa:** `map` lalu `flat` satu tingkat.

```js
const kalimat = ["buku tulis", "pensil 2b"];
const kata = kalimat.flatMap((teks) => teks.split(" "));
// ["buku", "tulis", "pensil", "2b"]
```

Menghapus item dengan mengembalikan `[]`:

```js
produk.flatMap((item) => (item.stok > 0 ? [item.nama] : []));
```

Lebih datar daripada `map` + `filter` untuk “0 atau 1 hasil per item”.

**Biasanya digabungkan dengan:** `split`, pecah tag, dan daftar bersyarat.

## forEach

**Untuk apa:** menjalankan fungsi per item, tidak menghasilkan array berguna (`undefined`).

```js
produk.forEach((item, i) => {
  console.log(i, item.nama);
});
```

Tidak bisa `break`. `return` di callback hanya melewati item itu, seperti `continue`.

Jangan memakai `forEach` untuk membangun array; pakai `map`/`reduce`.

**Biasanya digabungkan dengan:** menaruh listener, mengisi DOM, dan log.

## some

**Untuk apa:** `true` jika minimal satu item lolos uji. Berhenti saat ketemu.

```js
const adaHabis = produk.some((item) => item.stok === 0);
const adaId = produk.some((item) => item.id === 2);
```

Array kosong → `false`.

Cocok mengganti `includes` untuk object.

**Biasanya digabungkan dengan:** validasi “ada yang invalid”, badge, dan izin.

## every

**Untuk apa:** `true` jika semua item lolos uji. Berhenti saat ada yang gagal.

```js
const semuaAdaStok = produk.every((item) => item.stok > 0);
```

Array kosong → `true` (tidak ada yang melanggar).

```js
[].every(() => false); // true
```

**Biasanya digabungkan dengan:** cek form baris, “semua tercentang”, dan syarat checkout.

## reduce

**Untuk apa:** merangkum array menjadi satu nilai: jumlah, object, array lain.

```js
const total = produk.reduce((akum, item) => akum + item.harga, 0);
```

Argumen: `(akumulator, item, indeks, array)`. Argumen kedua `reduce` adalah nilai awal.

Tanpa nilai awal, item pertama jadi awal dan iterasi mulai dari indeks 1. Array kosong tanpa awal → `TypeError`.

Selalu tulis nilai awal untuk jumlah (`0`) atau object (`{}`).

Kelompokkan:

```js
const perKategori = produk.reduce((akum, item) => {
  const kunci = item.kategori;
  akum[kunci] ??= [];
  akum[kunci].push(item);
  return akum;
}, {});
```

Hitung kemunculan:

```js
const hitung = ["buku", "alat", "buku"].reduce((akum, tag) => {
  akum[tag] = (akum[tag] ?? 0) + 1;
  return akum;
}, {});
```

`reduce` mudah sulit dibaca. Jika `map`+`filter` cukup, pakai itu.

**Biasanya digabungkan dengan:** total belanja, grouping, dan pipeline data.

## reduceRight

**Untuk apa:** seperti `reduce`, dari kanan ke kiri.

```js
["satu", "dua", "tiga"].reduceRight((akum, kata) => `${akum}-${kata}`);
```

Jarang dibutuhkan. Berguna untuk komposisi fungsi atau pohon dari belakang.

**Biasanya digabungkan dengan:** pipeline terbalik. Untuk jumlah, `reduce` biasa cukup.

## sort

**Untuk apa:** mengurutkan **di tempat**, mengubah array asli. Mengembalikan array yang sama.

```js
const nama = ["Tas", "Buku", "Pensil"];
nama.sort();
console.log(nama); // ["Buku", "Pensil", "Tas"]
```

Tanpa pembanding, item diubah ke string. Angka salah urut:

```js
[10, 2, 3].sort(); // [10, 2, 3]  "10" < "2" ? tidak — "10","2","3"
[10, 2, 3].sort((a, b) => a - b); // [2, 3, 10]
```

Pembanding:

- kembalikan negatif jika `a` sebelum `b`
- positif jika `a` sesudah `b`
- `0` jika setara

Harga turun:

```js
produk.sort((a, b) => b.harga - a.harga);
```

Teks lokal:

```js
nama.sort((a, b) => a.localeCompare(b, "id"));
```

Jika tidak ingin mengubah asli, pakai `toSorted` atau `slice().sort(...)`.

**Biasanya digabungkan dengan:** dropdown urutan dan `localeCompare`.

## toSorted

**Untuk apa:** mengurutkan ke array baru.

```js
const asli = [3, 1, 2];
const urut = asli.toSorted((a, b) => a - b);
console.log(asli); // [3, 1, 2]
```

**Biasanya digabungkan dengan:** state React dan salinan tampilan.

## reverse

**Untuk apa:** membalik urutan di tempat.

```js
const nama = ["A", "B", "C"];
nama.reverse(); // ["C", "B", "A"]
```

**Biasanya digabungkan dengan:** tampilan terbaru di atas setelah `sort` tanggal.

## toReversed

**Untuk apa:** membalik ke array baru.

```js
const asli = ["A", "B"];
const balik = asli.toReversed();
```

**Biasanya digabungkan dengan:** histori tanpa merusak data sumber.

## with

**Untuk apa:** array baru dengan satu indeks diganti.

```js
const nama = ["Buku", "Pensil", "Tas"];
const ganti = nama.with(1, "Penghapus");
console.log(nama); // utuh
console.log(ganti); // ["Buku", "Penghapus", "Tas"]
```

Indeks negatif didukung. Indeks di luar jangkauan → error.

```js
produk.with(i, { ...produk[i], jumlah: 2 });
```

**Biasanya digabungkan dengan:** update satu baris tanpa mutasi.

## fill

**Untuk apa:** mengisi semua atau potongan dengan nilai yang sama. Mengubah asli.

```js
const slot = [1, 2, 3, 4];
slot.fill(0); // [0, 0, 0, 0]
[1, 2, 3, 4].fill(9, 1, 3); // [1, 9, 9, 4]
```

Hati-hati object: semua slot berbagi referensi yang sama.

```js
const salah = Array(3).fill({ stok: 0 });
salah[0].stok = 5; // ketiga-tiganya 5
```

Isi object terpisah:

```js
Array.from({ length: 3 }, () => ({ stok: 0 }));
```

**Biasanya digabungkan dengan:** reset buffer dan papan permainan sederhana.

## copyWithin

**Untuk apa:** menyalin potongan di dalam array yang sama. Mengubah asli.

```js
const data = [1, 2, 3, 4, 5];
data.copyWithin(0, 3); // [4, 5, 3, 4, 5]
```

Argumen: `(target, mulai, akhir = length)`. Jarang di aplikasi toko.

**Biasanya digabungkan dengan:** manipulasi buffer. Untuk daftar produk, `slice` lebih jelas.

## keys

**Untuk apa:** iterator indeks.

```js
const nama = ["Buku", "Pensil"];
console.log([...nama.keys()]); // [0, 1]
```

Berguna membuat deret dari panjang:

```js
[...Array(5).keys()]; // [0, 1, 2, 3, 4]
```

**Biasanya digabungkan dengan:** `for...of` dan `Array.from`.

## values

**Untuk apa:** iterator nilai. `for...of` pada array memakai ini.

```js
for (const item of nama.values()) {
  console.log(item);
}
```

`[...nama.values()]` menyalin nilai tingkat atas.

**Biasanya digabungkan dengan:** `for...of` dan ubah ke array.

## entries

**Untuk apa:** iterator `[indeks, nilai]`.

```js
for (const [i, item] of nama.entries()) {
  console.log(i, item);
}
```

Ini cara nyaman dapat indeks tanpa `for` klasik.

**Biasanya digabungkan dengan:** `for...of`, destructure, dan render bernomor.

## Array.fromAsync

**Untuk apa:** seperti `Array.from`, tetapi untuk async iterable.

```js
const daftar = await Array.fromAsync(sumberAsync);
```

Tidak semua lingkungan tugas kuliah memakainya. Untuk `fetch` daftar biasa, `await respons.json()` cukup.

**Biasanya digabungkan dengan:** stream async. Untuk API JSON, file 10.

## toString dan toLocaleString

**Untuk apa:** mengubah array menjadi teks.

```js
[1, 2, 3].toString(); // "1,2,3"
[1000, 2000].toLocaleString("id-ID");
```

`join` lebih terkendali untuk pemisah. `toLocaleString` berguna untuk angka/tanggal di dalam array.

**Biasanya digabungkan dengan:** debug dan tampilan cepat. Untuk UI, `map` + format + `join`.

## Peta mengubah vs tidak

| Method | Ubah asli? | Hasil |
| --- | --- | --- |
| `push` `pop` `shift` `unshift` | ya | panjang atau item |
| `splice` `sort` `reverse` `fill` `copyWithin` | ya | array / item terhapus |
| `map` `filter` `slice` `concat` `flat` `flatMap` | tidak | array baru |
| `toSorted` `toReversed` `toSpliced` `with` | tidak | array baru |
| `find` `findLast` | tidak | item atau `undefined` |
| `findIndex` `indexOf` | tidak | angka |
| `some` `every` `includes` | tidak | boolean |
| `reduce` | tidak* | nilai ringkas |
| `forEach` | tidak* | `undefined` |

\*Callback bisa mengubah object di dalam.

## Pola kerja toko

Cari + urut + ambil nama:

```js
const q = "u";
const hasil = produk
  .filter((item) => item.nama.toLowerCase().includes(q))
  .toSorted((a, b) => a.harga - b.harga)
  .map((item) => item.nama);
```

Total keranjang:

```js
const total = keranjang.reduce(
  (sum, item) => sum + item.harga * item.jumlah,
  0,
);
```

Tambah atau naikkan jumlah:

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

Unik:

```js
const unik = [...new Set(tag)];
```

**Biasanya digabungkan dengan:** file 07 `Set`, file 08 render, file 09 klik.

## Kesalahan array yang sering

- Tertukar `slice` (salin) dan `splice` (ubah).
- `sort` tanpa pembanding untuk angka.
- `map` tanpa `return`.
- Mengira `filter` mengubah asli.
- `find` lalu akses field tanpa `?.`.
- `push` dianggap mengembalikan array.
- `includes` untuk object.
- `for...in` pada array.
- `fill` object yang sama.
- Mutasi di dalam `map` yang kelihatan “aman”.

**Biasanya digabungkan dengan:** file 13 dan pengujian di Console dengan data kecil.
