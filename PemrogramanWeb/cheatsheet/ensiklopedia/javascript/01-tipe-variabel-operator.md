# 01 — Tipe, variabel, dan operator

[← Indeks](README.md) · [Lanjut 02 →](02-kondisi-loop-error.md)

JavaScript menyimpan data di variabel, lalu menghitung atau membandingkannya dengan operator.

## Daftar isi

- [const](#const)
- [let](#let)
- [var](#var)
- [string](#string)
- [number](#number)
- [bigint](#bigint)
- [boolean](#boolean)
- [null](#null)
- [undefined](#undefined)
- [symbol](#symbol)
- [object dan array](#object-dan-array)
- [typeof](#typeof)
- [template literal](#template-literal)
- [operator aritmetika](#operator-aritmetika)
- [operator penugasan](#operator-penugasan)
- [++ dan --](#--dan---)
- [operator perbandingan](#operator-perbandingan)
- [operator ===](#operator--)
- [operator ==](#operator--)
- [operator logika](#operator-logika)
- [operator nullish ??](#operator-nullish--)
- [optional chaining ?.](#optional-chaining-)
- [operator in](#operator-in)
- [instanceof](#instanceof)
- [Object.is](#objectis)
- [konversi ke string](#konversi-ke-string)
- [konversi ke number](#konversi-ke-number)
- [konversi ke boolean](#konversi-ke-boolean)
- [truthy dan falsy](#truthy-dan-falsy)
- [NaN dan Infinity](#nan-dan-infinity)
- [Number.isNaN](#numberisnan)
- [Number.isFinite](#numberisfinite)
- [unary plus dan minus](#unary-plus-dan-minus)
- [void](#void)
- [delete](#delete)
- [operator koma](#operator-koma)
- [bitwise singkat](#bitwise-singkat)
- [prioritas operator](#prioritas-operator)
- [strict mode](#strict-mode)

## const

**Untuk apa:** menamai data yang referensinya tidak akan diganti.

```js
const namaToko = "Toko Belajar";
const produk = { nama: "Buku", harga: 45000 };
produk.harga = 50000; // boleh: isi object berubah
// namaToko = "Toko Baru"; // error: Assignment to constant variable
```

`const` melarang `= ulang`, bukan mengunci isi object/array. Isi tetap bisa diubah. Jika butuh object yang tidak boleh diubah, lihat `Object.freeze` di file 04.

**Biasanya digabungkan dengan:** hampir semua kode modern, destructure, dan hasil `fetch`.

## let

**Untuk apa:** menamai data yang akan ditugaskan ulang.

```js
let jumlah = 1;
jumlah = 2;
jumlah += 1;
console.log(jumlah); // 3
```

Pakai `let` untuk penghitung, status yang berganti, atau akumulator di loop. Jangan memakai `let` jika nilainya tidak pernah diganti; `const` lebih jelas.

`let` dan `const` bersifat block scope: hidup di dalam `{ }`.

```js
if (true) {
  let pesan = "di dalam if";
  console.log(pesan);
}
// console.log(pesan); // error: pesan is not defined
```

**Biasanya digabungkan dengan:** loop `for`, state halaman, dan penghitung keranjang.

## var

**Untuk apa:** cara lama membuat variabel. Hindari di kode baru.

```js
var stok = 10;
var stok = 8; // boleh dideklarasikan ulang, membingungkan
```

`var` bersifat function scope, bukan block scope. Ia juga di-hoist, sehingga bisa terlihat “sudah ada” sebelum baris tulisannya.

```js
function contoh() {
  console.log(nilai); // undefined, bukan error
  var nilai = 5;
}
```

**Biasanya digabungkan dengan:** kode lama. Di latihan baru, ganti ke `let`/`const`.

## string

**Untuk apa:** menyimpan teks: nama, judul, pesan, URL.

```js
const judul = "Buku Tulis";
const kutip = 'Toko "Belajar"';
const kosong = "";
console.log(judul.length); // 10
```

String bisa memakai tanda petik ganda atau tunggal. Untuk sisipan variabel, pakai template literal. Method lengkap ada di [file 06](06-string-number-math-date.md).

Indeks mulai dari 0:

```js
console.log(judul[0]); // "B"
console.log(judul.at(-1)); // "s"
```

**Biasanya digabungkan dengan:** `includes`, `trim`, template literal, dan tampilan DOM.

## number

**Untuk apa:** menyimpan angka: harga, stok, jumlah, skor.

```js
const harga = 45000;
const diskon = 0.1;
const negatif = -3;
const desimal = 12.5;
```

JavaScript tidak memisahkan integer dan float seperti beberapa bahasa lain. `1` dan `1.0` sama-sama `number`. Perhitungan desimal bisa tidak persis:

```js
console.log(0.1 + 0.2); // 0.30000000000000004
```

Untuk uang, hitung dalam satuan utuh (rupiah) atau bulatkan hasil tampilan. Lihat `toFixed` dan `Intl.NumberFormat` di file 06.

**Biasanya digabungkan dengan:** `Math`, `Number`, operator `+ - * / %`, dan validasi form.

## bigint

**Untuk apa:** bilangan bulat yang lebih besar dari batas aman `number`.

```js
const besar = 9007199254740993n;
const dariNumber = BigInt(100);
console.log(besar + 2n);
```

Jangan mencampur `bigint` dengan `number` biasa tanpa konversi. Untuk harga toko biasa, `number` sudah cukup.

```js
// console.log(1n + 1); // TypeError
console.log(1n + BigInt(1));
```

**Biasanya digabungkan dengan:** ID besar atau perhitungan khusus. Jarang dipakai di tugas web dasar.

## boolean

**Untuk apa:** benar atau salah: sudah login, stok ada, form valid.

```js
const sudahLogin = true;
const keranjangKosong = false;
```

Hasil perbandingan adalah boolean:

```js
const stok = 3;
const bisaBeli = stok > 0;
console.log(bisaBeli); // true
```

**Biasanya digabungkan dengan:** `if`, class `hidden`, dan atribut `disabled`.

## null

**Untuk apa:** menandai “sengaja kosong”.

```js
const kupon = null;
const pengguna = { profil: null };
```

Pakai `null` jika kamu tahu datanya belum ada. Beda dengan `undefined`, yang biasanya berarti “belum diisi sama sekali”.

Cek kosong yang mencakup keduanya:

```js
const kota = pengguna.profil?.kota ?? "Belum diisi";
```

**Biasanya digabungkan dengan:** `??`, optional chaining, dan field API yang kosong.

## undefined

**Untuk apa:** nilai default jika variabel atau properti belum ada.

```js
let alamat;
console.log(alamat); // undefined

const produk = { nama: "Pensil" };
console.log(produk.stok); // undefined
```

Parameter fungsi yang tidak dikirim juga `undefined`. Default parameter hanya aktif untuk `undefined`, bukan untuk `null`.

```js
function halo(nama = "Pengunjung") {
  return `Halo, ${nama}`;
}
console.log(halo()); // Halo, Pengunjung
console.log(halo(undefined)); // Halo, Pengunjung
console.log(halo(null)); // Halo, null
```

**Biasanya digabungkan dengan:** default parameter, `??`, dan pengecekan properti object.

## symbol

**Untuk apa:** membuat kunci object yang unik.

```js
const id = Symbol("id");
const produk = { nama: "Buku", [id]: 17 };
console.log(produk[id]); // 17
console.log(Object.keys(produk)); // ["nama"] — Symbol tidak ikut
```

Untuk tugas toko biasa, string sebagai kunci sudah cukup. Symbol berguna jika kamu tidak ingin kunci bentrok dengan properti lain.

**Biasanya digabungkan dengan:** metadata internal object. Jarang muncul di tugas dasar.

## object dan array

**Untuk apa:** object menyimpan data beratribut; array menyimpan daftar.

```js
const produk = {
  id: 1,
  nama: "Buku",
  harga: 45000,
};
const keranjang = ["Buku", "Pensil"];
```

Akses object:

```js
console.log(produk.nama);
console.log(produk["harga"]);
```

Akses array:

```js
console.log(keranjang[0]);
console.log(keranjang.length);
```

Katalog lengkap: [file 04](04-object-destructure-spread.md) dan [file 05](05-array-method-lengkap.md).

**Biasanya digabungkan dengan:** JSON API, `map`, dan destructure.

## typeof

**Untuk apa:** menanyakan tipe nilai.

```js
typeof "Buku"; // "string"
typeof 45000; // "number"
typeof true; // "boolean"
typeof undefined; // "undefined"
typeof null; // "object"  ← keanehan lama, tetap diingat
typeof {}; // "object"
typeof []; // "object"
typeof function () {}; // "function"
typeof 10n; // "bigint"
typeof Symbol("x"); // "symbol"
```

Jangan memakai `typeof` untuk membedakan array dan object biasa. Pakai `Array.isArray`.

```js
Array.isArray([]); // true
Array.isArray({}); // false
```

Untuk `null`, bandingkan langsung:

```js
nilai === null;
```

**Biasanya digabungkan dengan:** validasi masukan, guard di fungsi, dan debug Console.

## template literal

**Untuk apa:** menyusun teks dengan variabel di dalamnya.

```js
const nama = "Haikal";
const jumlah = 2;
const pesan = `${nama} membeli ${jumlah} barang`;
```

Bisa banyak baris:

```js
const kartu = `
  <article>
    <h2>${nama}</h2>
  </article>
`;
```

Ekspresi boleh di dalam `${ }`:

```js
const harga = 45000;
const total = `Rp${harga * 2}`;
```

**Biasanya digabungkan dengan:** `textContent`, pesan error, dan URL query.

## operator aritmetika

**Untuk apa:** menghitung angka.

```js
console.log(10 + 3); // 13
console.log(10 - 3); // 7
console.log(10 * 3); // 30
console.log(10 / 4); // 2.5
console.log(10 % 3); // 1  sisa bagi
console.log(2 ** 3); // 8  pangkat
```

`%` sering dipakai untuk kelipatan, genap/ganjil, atau index yang berputar.

```js
const genap = 8 % 2 === 0;
const index = 5 % 3; // 2, jika hanya ada 3 slot
```

`+` pada string justru menempelkan teks:

```js
console.log("4" + 5); // "45"
console.log("4" - 1); // 3  (string diubah ke number)
```

**Biasanya digabungkan dengan:** harga, diskon, stok, dan `Math.round`.

## operator penugasan

**Untuk apa:** mengisi atau memperbarui variabel.

```js
let total = 0;
total = 10000;
total += 5000; // 15000
total -= 2000; // 13000
total *= 2; // 26000
total /= 2; // 13000
total %= 10000; // 3000
let faktor = 2;
faktor **= 3; // 8
```

Ada juga penugasan logika:

```js
let judul = "";
judul ||= "Tanpa judul"; // isi jika judul falsy
let stok = 0;
stok ??= 10; // 0 tetap 0, karena 0 bukan null/undefined
```

**Biasanya digabungkan dengan:** penghitung, akumulator, dan default nilai.

## ++ dan --

**Untuk apa:** menambah atau mengurangi 1.

```js
let n = 5;
n++; // n menjadi 6
n--; // n menjadi 5
```

Bentuk depan mengembalikan nilai setelah perubahan; bentuk belakang mengembalikan nilai sebelum perubahan.

```js
let a = 1;
console.log(++a); // 2, a sudah 2
let b = 1;
console.log(b++); // 1, b kemudian 2
```

Di kode baru, `n += 1` lebih mudah dibaca daripada mengandalkan prefix/postfix.

**Biasanya digabungkan dengan:** loop `for` dan penghitung klik.

## operator perbandingan

**Untuk apa:** menghasilkan `true` atau `false`.

```js
console.log(5 > 3); // true
console.log(5 >= 5); // true
console.log(5 < 3); // false
console.log(5 <= 4); // false
console.log("Buku" < "Pensil"); // true, urutan kamus
```

String dibandingkan menurut urutan karakter. Untuk angka dari input form, ubah dulu ke number.

```js
const harga = Number(inputHarga.value);
if (harga >= 10000) {
  console.log("Di atas minimum");
}
```

**Biasanya digabungkan dengan:** `if`, `filter`, dan validasi.

## operator ===

**Untuk apa:** membandingkan nilai dan tipe tanpa konversi diam-diam.

```js
console.log(5 === 5); // true
console.log(5 === "5"); // false
console.log(true === 1); // false
console.log(null === undefined); // false
```

Ini perbandingan yang dipakai sehari-hari. `!==` adalah lawannya.

```js
if (status !== "habis") {
  console.log("Masih bisa dipesan");
}
```

**Biasanya digabungkan dengan:** hampir semua `if`, `find`, dan cek status.

## operator ==

**Untuk apa:** membandingkan dengan konversi tipe. Hindari kecuali kamu sengaja memakainya.

```js
console.log(5 == "5"); // true
console.log(true == 1); // true
console.log(null == undefined); // true
console.log("" == 0); // true
```

Hasilnya mudah mengecoh. Lebih aman:

```js
Number("5") === 5;
nilai == null; // satu-satunya pola == yang sering dianggap wajar: null atau undefined
```

**Biasanya digabungkan dengan:** kode lama. Di latihan baru, pakai `===`.

## operator logika

**Untuk apa:** menggabungkan atau membalik kondisi.

```js
const stok = 5;
const sudahLogin = true;

console.log(stok > 0 && sudahLogin); // true, keduanya
console.log(stok > 0 || sudahLogin); // true, salah satu
console.log(!sudahLogin); // false
```

`&&` dan `||` mengembalikan nilai, bukan selalu `true`/`false`.

```js
const judul = "" || "Tanpa judul";
const pengguna = sudahLogin && { nama: "Haikal" };
```

Urutan dibaca kiri ke kanan dan bisa berhenti lebih awal (short-circuit).

```js
const produk = null;
const nama = produk && produk.nama; // tidak error, hasil null
```

Untuk akses aman, `?.` lebih jelas daripada `&&`.

**Biasanya digabungkan dengan:** `if`, guard clause, dan class kondisi.

## operator nullish ??

**Untuk apa:** memberi cadangan hanya jika nilai `null` atau `undefined`.

```js
const stok = 0;
console.log(stok ?? 10); // 0
console.log(stok || 10); // 10  ← 0 dianggap kosong oleh ||

const judul = "";
console.log(judul ?? "Cadangan"); // ""
console.log(judul || "Cadangan"); // "Cadangan"
```

Pakai `??` untuk angka yang boleh 0 dan teks yang boleh kosong. Pakai `||` jika `0`, `""`, dan `false` memang harus diganti.

```js
const halaman = Number(params.halaman ?? 1);
```

**Biasanya digabungkan dengan:** default API, `?.`, dan pengaturan pengguna.

## optional chaining ?.

**Untuk apa:** mengakses properti tanpa error jika bagian kirinya `null`/`undefined`.

```js
const pengguna = { profil: null };
console.log(pengguna.profil?.kota); // undefined, tidak error
// console.log(pengguna.profil.kota); // TypeError
```

Bisa untuk method dan indeks:

```js
pengguna.cetak?.();
keranjang[0]?.nama;
```

Gabungan yang sering dipakai:

```js
const kota = pengguna.profil?.kota ?? "Belum diisi";
```

**Biasanya digabungkan dengan:** data API yang tidak lengkap dan `??`.

## operator in

**Untuk apa:** mengecek apakah kunci ada di object, termasuk rantai prototipe.

```js
const produk = { nama: "Buku", harga: 45000 };
console.log("nama" in produk); // true
console.log("stok" in produk); // false
console.log("toString" in produk); // true, dari prototipe
```

Untuk kunci milik object itu sendiri, lebih jelas `Object.hasOwn`.

```js
Object.hasOwn(produk, "nama"); // true
Object.hasOwn(produk, "toString"); // false
```

**Biasanya digabungkan dengan:** form dinamis dan object opsi.

## instanceof

**Untuk apa:** mengecek apakah nilai dibuat dari suatu class/konstruktor.

```js
console.log([] instanceof Array); // true
console.log(new Date() instanceof Date); // true
console.log({} instanceof Object); // true
```

Untuk array, `Array.isArray` lebih andal antar-frame/realm. Untuk error:

```js
try {
  throw new TypeError("Tipe salah");
} catch (error) {
  console.log(error instanceof TypeError);
}
```

**Biasanya digabungkan dengan:** `try/catch` dan pengecekan `Date`/`Error`.

## Object.is

**Untuk apa:** membandingkan dua nilai seperti `===`, dengan perbedaan pada `NaN` dan `-0`.

```js
Object.is(NaN, NaN); // true
NaN === NaN; // false

Object.is(0, -0); // false
0 === -0; // true
```

Untuk perbandingan sehari-hari, `===` cukup. `Object.is` berguna saat kamu peduli `NaN` atau tanda nol.

**Biasanya digabungkan dengan:** utilitas banding nilai dan tes.

## konversi ke string

**Untuk apa:** mengubah nilai menjadi teks.

```js
String(45); // "45"
String(true); // "true"
String(null); // "null"
(45).toString(); // "45"
`${45}`; // "45"
```

`toString` gagal pada `null`/`undefined` karena keduanya bukan object.

```js
// null.toString(); // error
String(null); // aman
```

**Biasanya digabungkan dengan:** `localStorage`, atribut HTML, dan gabungan teks.

## konversi ke number

**Untuk apa:** mengubah teks atau nilai lain menjadi angka.

```js
Number("45"); // 45
Number(""); // 0
Number(" "); // 0
Number("45px"); // NaN
Number(true); // 1
Number(false); // 0
Number(null); // 0
Number(undefined); // NaN
```

Untuk memotong angka di awal teks:

```js
parseInt("45px", 10); // 45
parseFloat("12.5cm"); // 12.5
```

Unary plus ringkas, tetapi kurang jelas untuk pemula:

```js
const harga = +"45000";
```

**Biasanya digabungkan dengan:** nilai form, query URL, dan perhitungan.

## konversi ke boolean

**Untuk apa:** memaksa nilai menjadi `true` atau `false`.

```js
Boolean("Buku"); // true
Boolean(""); // false
Boolean(0); // false
Boolean(1); // true
!!keranjang.length; // true jika ada item
```

`!!` adalah pola singkat. Untuk kondisi `if`, konversi terjadi otomatis.

**Biasanya digabungkan dengan:** class kondisi, `disabled`, dan filter “ada isinya”.

## truthy dan falsy

**Untuk apa:** memahami nilai mana yang dianggap kosong di `if`.

Nilai **falsy**:

```js
false;
0;
-0;
0n;
"";
null;
undefined;
NaN;
```

Selain itu **truthy**, termasuk:

```js
"0";
"false";
[];
{};
" ";
```

Akibat yang sering mengecoh:

```js
if ([]) {
  console.log("array kosong dianggap true");
}
if (stok) {
  // gagal jika stok 0 padahal 0 adalah angka sah
}
```

Untuk stok, bandingkan secara eksplisit: `stok === 0` atau `stok > 0`.

**Biasanya digabungkan dengan:** `if`, `||`, dan validasi.

## NaN dan Infinity

**Untuk apa:** menandai hasil hitung yang tidak sah atau tak hingga.

```js
console.log(Number("abc")); // NaN
console.log(1 / 0); // Infinity
console.log(-1 / 0); // -Infinity
```

`NaN` tidak sama dengan dirinya:

```js
NaN === NaN; // false
Number.isNaN(NaN); // true
```

Cek sebelum memakai hasil:

```js
const harga = Number(input.value);
if (!Number.isFinite(harga)) {
  console.log("Harga tidak valid");
}
```

**Biasanya digabungkan dengan:** `Number`, form angka, dan `Math`.

## Number.isNaN

**Untuk apa:** memastikan nilai benar-benar `NaN`.

```js
Number.isNaN(NaN); // true
Number.isNaN("abc"); // false
isNaN("abc"); // true  ← isNaN lama mengonversi dulu
```

Pakai `Number.isNaN`, bukan `isNaN` global.

**Biasanya digabungkan dengan:** `Number(...)` setelah membaca input.

## Number.isFinite

**Untuk apa:** memastikan nilai number yang wajar, bukan `NaN`/`Infinity`.

```js
Number.isFinite(45); // true
Number.isFinite(Infinity); // false
Number.isFinite("45"); // false, tidak mengonversi
isFinite("45"); // true  ← versi lama mengonversi
```

**Biasanya digabungkan dengan:** validasi harga, jumlah, dan halaman.

## unary plus dan minus

**Untuk apa:** `+` memaksa ke number; `-` membalik tanda.

```js
console.log(+"12"); // 12
console.log(-"12"); // -12
console.log(-(-5)); // 5
```

Jika teks tidak bisa jadi angka, hasilnya `NaN`.

**Biasanya digabungkan dengan:** input form dan rumus singkat. `Number(...)` lebih mudah dibaca.

## void

**Untuk apa:** mengevaluasi ekspresi lalu menghasilkan `undefined`.

```js
void 0; // undefined
void console.log("tetap jalan");
```

Jarang dibutuhkan di kode aplikasi. Kadang muncul di tautan lama `javascript:void(0)`.

**Biasanya digabungkan dengan:** kode warisan. Di aplikasi baru, abaikan.

## delete

**Untuk apa:** menghapus properti object.

```js
const produk = { nama: "Buku", diskon: 10 };
delete produk.diskon;
console.log(produk.diskon); // undefined
```

Jangan memakai `delete` pada elemen array jika kamu ingin daftar rapat; hasilnya lubang. Pakai `splice` atau `filter`.

```js
const daftar = ["A", "B", "C"];
delete daftar[1];
console.log(daftar); // ["A", empty, "C"]
```

**Biasanya digabungkan dengan:** object opsi. Untuk data daftar, lebih aman membuat object baru tanpa kunci itu.

## operator koma

**Untuk apa:** menjalankan beberapa ekspresi, lalu memakai yang terakhir.

```js
let a = 1;
const hasil = (a += 1, a * 2);
console.log(hasil); // 4
```

Sulit dibaca. Di `for`, koma masih wajar untuk dua penghitung.

```js
for (let i = 0, j = 9; i < j; i += 1, j -= 1) {
  console.log(i, j);
}
```

**Biasanya digabungkan dengan:** header `for`. Hindari di ekspresi biasa.

## bitwise singkat

**Untuk apa:** operasi bit. Jarang dipakai di tugas web biasa.

```js
console.log(5 & 1); // 1
console.log(5 | 2); // 7
console.log(5 ^ 1); // 4
console.log(~5); // -6
console.log(1 << 3); // 8
```

`| 0` kadang dipakai untuk memotong jadi integer 32-bit. Lebih jelas `Math.trunc`.

**Biasanya digabungkan dengan:** flag biner atau kode performa khusus. Bukan kebutuhan toko.

## prioritas operator

**Untuk apa:** memahami urutan hitung jika tanda kurung tidak ditulis.

```js
console.log(2 + 3 * 4); // 14, kali dulu
console.log((2 + 3) * 4); // 20
console.log(true || false && false); // true, && dulu
```

Jika ragu, tulis kurung. Jangan mengandalkan hafalan prioritas untuk kode yang dibaca orang lain.

Urutan yang sering ketemu, dari yang lebih dulu:

1. `()` `?.` `[]` `.`
2. `!` `++` `--` `typeof` unary `+` `-`
3. `**`
4. `*` `/` `%`
5. `+` `-`
6. `<` `<=` `>` `>=`
7. `===` `!==`
8. `&&`
9. `||` `??`
10. `=` `+=` dan kawan-kawannya

`??` tidak boleh dicampur langsung dengan `||` atau `&&` tanpa kurung.

```js
// const x = a ?? b || c; // SyntaxError
const x = (a ?? b) || c;
```

**Biasanya digabungkan dengan:** rumus harga dan kondisi panjang.

## strict mode

**Untuk apa:** menolak beberapa kebiasaan lama yang berbahaya.

```js
"use strict";
// nilaiTanpaDeklarasi = 1; // error
```

Module ES (`import`/`export`) dan class sudah otomatis strict. Kamu jarang perlu menulis `"use strict"` jika file sudah module.

Efek yang terasa:

- variabel tanpa `let`/`const`/`var` error
- `this` di fungsi biasa menjadi `undefined`, bukan `window`
- `delete` pada variabel error

**Biasanya digabungkan dengan:** file module dan kebiasaan `const`/`let`.

## Tabel cepat tipe

| Nilai | typeof | catatan |
| --- | --- | --- |
| `"Buku"` | `"string"` | teks |
| `45000` | `"number"` | termasuk `NaN`, `Infinity` |
| `10n` | `"bigint"` | jangan dicampur number |
| `true` | `"boolean"` | |
| `undefined` | `"undefined"` | belum diisi |
| `null` | `"object"` | cek dengan `=== null` |
| `{}` | `"object"` | |
| `[]` | `"object"` | pakai `Array.isArray` |
| `function () {}` | `"function"` | |
| `Symbol()` | `"symbol"` | |

## Pola yang sering ditulis

Baca angka form:

```js
const jumlah = Number(inputJumlah.value);
if (!Number.isInteger(jumlah) || jumlah < 1) {
  console.log("Jumlah tidak valid");
}
```

Default aman:

```js
const halaman = Number(params.halaman ?? 1);
const judul = nama?.trim() || "Tanpa judul";
```

Cek kosong object/array:

```js
if (Object.keys(filter).length === 0) {
  console.log("Tidak ada filter");
}
if (keranjang.length === 0) {
  console.log("Keranjang kosong");
}
```

**Biasanya digabungkan dengan:** file 02 untuk `if`, file 06 untuk `Number.isInteger`.
