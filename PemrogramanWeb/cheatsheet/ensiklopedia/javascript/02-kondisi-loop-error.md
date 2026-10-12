# 02 — Kondisi, loop, dan error

[← 01 Tipe](01-tipe-variabel-operator.md) · [Indeks](README.md) · [Lanjut 03 →](03-fungsi-scope-this-closure.md)

Kondisi memilih jalan. Loop mengulang langkah. `try/catch` menangkap error agar halaman tidak berhenti diam-diam.

## Daftar isi

- [if](#if)
- [else](#else)
- [else if](#else-if)
- [guard clause](#guard-clause)
- [operator ternary](#operator-ternary)
- [if singkat dengan &&](#if-singkat-dengan-)
- [switch](#switch)
- [while](#while)
- [do...while](#dowhile)
- [for](#for)
- [for...of](#forof)
- [for...in](#forin)
- [forEach sebagai perulangan](#foreach-sebagai-perulangan)
- [break](#break)
- [continue](#continue)
- [label loop](#label-loop)
- [loop bersarang](#loop-bersarang)
- [try / catch / finally](#try--catch--finally)
- [throw](#throw)
- [Error](#error)
- [TypeError](#typeerror)
- [RangeError](#rangeerror)
- [SyntaxError](#syntaxerror)
- [ReferenceError](#referenceerror)
- [optional catch binding](#optional-catch-binding)
- [error async](#error-async)
- [pola validasi](#pola-validasi)

## if

**Untuk apa:** menjalankan blok hanya jika syarat benar.

```js
const stok = 5;
if (stok > 0) {
  console.log("Bisa dibeli");
}
```

Syarat diubah ke boolean. Ingat nilai falsy: `0`, `""`, `null`, `undefined`, `NaN`, `false`.

```js
if (stok) {
  // gagal jika stok 0, padahal 0 sah
}
if (stok > 0) {
  // lebih jelas
}
```

Satu baris tanpa kurung kurawal legal, tetapi mudah error jika nanti ditambah baris. Biasakan selalu memakai `{ }`.

**Biasanya digabungkan dengan:** operator `===`, `&&`, `||`, dan `classList`.

## else

**Untuk apa:** jalan cadangan jika `if` tidak terpenuhi.

```js
if (stok > 0) {
  console.log("Tersedia");
} else {
  console.log("Habis");
}
```

`else` tidak wajib. Jika tidak ada yang perlu dilakukan, cukup `if`.

**Biasanya digabungkan dengan:** label status, pesan form, dan tampilan kosong.

## else if

**Untuk apa:** menguji syarat berikutnya, berurutan.

```js
const nilai = 78;
if (nilai >= 85) {
  console.log("A");
} else if (nilai >= 70) {
  console.log("B");
} else if (nilai >= 55) {
  console.log("C");
} else {
  console.log("Belum lulus");
}
```

Hanya satu cabang yang jalan. Urutan penting: syarat sempit atau lebih besar dulu jika memakai `>=`.

Untuk banyak teks tetap, `switch` bisa lebih rapi. Untuk rentang angka, `else if` lebih wajar.

**Biasanya digabungkan dengan:** status pesanan, peran pengguna, dan skor.

## guard clause

**Untuk apa:** keluar lebih awal agar isi fungsi tidak menjorok dalam.

```js
function checkout(pengguna, keranjang) {
  if (!pengguna) {
    return "Login dulu";
  }
  if (keranjang.length === 0) {
    return "Keranjang kosong";
  }
  return "Lanjut bayar";
}
```

Ini lebih mudah dibaca daripada `if` di dalam `if` di dalam `if`.

**Biasanya digabungkan dengan:** fungsi, validasi form, dan handler klik.

## operator ternary

**Untuk apa:** memilih satu dari dua nilai dalam satu ekspresi.

```js
const stok = 0;
const label = stok > 0 ? "Tersedia" : "Habis";
```

Bentuknya: `syarat ? jikaBenar : jikaSalah`. Cocok untuk nilai, bukan untuk banyak perintah.

Ternary bersarang sulit dibaca. Ganti ke `if` atau fungsi kecil.

```js
const labelPanjang =
  stok > 10 ? "Banyak" : stok > 0 ? "Terbatas" : "Habis"; // hindari
```

**Biasanya digabungkan dengan:** `className`, teks tombol, dan `map` di React.

## if singkat dengan &&

**Untuk apa:** menjalankan sesuatu hanya jika syarat truthy.

```js
const sudahLogin = true;
sudahLogin && console.log("Menu akun tampil");
```

Hasil `&&` adalah nilai terakhir yang dinilai. Jangan memakainya jika syarat bisa 0 atau string kosong dan itu nilai sah.

Di UI, pola ini sering muncul:

```js
keranjang.length && renderDaftar(keranjang);
```

Jika `length` 0, hasilnya `0`, bukan `false`. Untuk tampilan, bandingkan `length > 0`.

**Biasanya digabungkan dengan:** render bersyarat. Untuk logika bisnis, `if` lebih jelas.

## switch

**Untuk apa:** memilih cabang berdasarkan satu nilai tetap.

```js
const status = "dikirim";
switch (status) {
  case "baru":
    console.log("Pesanan masuk");
    break;
  case "dibayar":
    console.log("Siap dikemas");
    break;
  case "dikirim":
  case "selesai":
    console.log("Sudah di perjalanan atau sampai");
    break;
  default:
    console.log("Status tidak dikenal");
}
```

Tanpa `break`, eksekusi jatuh ke `case` berikutnya (fall-through). Itu berguna jika beberapa kasus sama, tetapi mudah terlupa.

`switch` memakai perbandingan ketat seperti `===`.

```js
switch (5) {
  case "5":
    console.log("tidak ketemu");
    break;
  default:
    console.log("beda tipe");
}
```

**Biasanya digabungkan dengan:** status string, menu, dan pemetaan peran.

## while

**Untuk apa:** mengulang selama syarat masih benar.

```js
let sisa = 3;
while (sisa > 0) {
  console.log("Menunggu", sisa);
  sisa -= 1;
}
```

Syarat dicek sebelum masuk. Jika awalnya sudah salah, isi tidak pernah jalan.

Wajib ada perubahan yang membuat syarat menjadi salah. Jika tidak, loop tak berhingga.

```js
// while (true) { } // membekukan tab jika tidak ada break
```

**Biasanya digabungkan dengan:** proses yang berhenti karena syarat, bukan karena panjang array.

## do...while

**Untuk apa:** menjalankan isi minimal sekali, baru mengecek syarat.

```js
let percobaan = 0;
let valid = false;
do {
  percobaan += 1;
  valid = percobaan >= 1;
} while (!valid && percobaan < 3);
```

Jarang dibutuhkan. Jika isi boleh dilewati, pakai `while` atau `for`.

**Biasanya digabungkan dengan:** menu berulang atau percobaan ulang sederhana.

## for

**Untuk apa:** mengulang dengan penghitung.

```js
const nama = ["Buku", "Pensil", "Tas"];
for (let i = 0; i < nama.length; i += 1) {
  console.log(i, nama[i]);
}
```

Tiga bagian: mulai; syarat; langkah. Pakai ini jika kamu butuh indeks, mundur, atau loncat.

Mundur:

```js
for (let i = nama.length - 1; i >= 0; i -= 1) {
  console.log(nama[i]);
}
```

Loncat 2:

```js
for (let i = 0; i < nama.length; i += 2) {
  console.log(nama[i]);
}
```

**Biasanya digabungkan dengan:** indeks, paginasi, dan array 2 dimensi.

## for...of

**Untuk apa:** mengambil tiap nilai dari array, string, `Set`, `Map`, atau iterable lain.

```js
const produk = ["Buku", "Pensil"];
for (const item of produk) {
  console.log(item);
}
```

Tidak memberi indeks secara langsung. Jika butuh indeks:

```js
for (const [i, item] of produk.entries()) {
  console.log(i, item);
}
```

Pada string, ia berjalan per karakter (lebih aman untuk beberapa huruf Unicode daripada indeks `[i]`).

```js
for (const huruf of "Hai") {
  console.log(huruf);
}
```

**Biasanya digabungkan dengan:** array, `Set`, `Map`, dan proses yang butuh `break`.

## for...in

**Untuk apa:** mengunjungi kunci enumerable object.

```js
const produk = { nama: "Buku", harga: 45000 };
for (const kunci in produk) {
  if (Object.hasOwn(produk, kunci)) {
    console.log(kunci, produk[kunci]);
  }
}
```

Jangan memakai `for...in` untuk array. Urutan dan kunci warisan bisa mengecoh. Untuk array pakai `for...of` atau method.

```js
const daftar = ["A", "B"];
for (const kunci in daftar) {
  console.log(kunci); // "0", "1" — string, bukan pola terbaik
}
```

**Biasanya digabungkan dengan:** object biasa. Alternatif lebih rapi: `Object.keys` / `Object.entries`.

## forEach sebagai perulangan

**Untuk apa:** menjalankan fungsi untuk tiap item array.

```js
const harga = [45000, 8000];
harga.forEach((nilai, indeks) => {
  console.log(indeks, nilai);
});
```

Tidak bisa `break`. Tidak menghasilkan array baru. Detail ada di [file 05](05-array-method-lengkap.md#foreach).

Jika kamu mungkin berhenti di tengah, pakai `for...of` atau `some`.

**Biasanya digabungkan dengan:** efek samping: menampilkan, menambahkan listener, mengisi DOM.

## break

**Untuk apa:** keluar dari loop atau `switch` segera.

```js
const daftar = [2, 4, 7, 8];
let ketemu = null;
for (const n of daftar) {
  if (n % 2 === 1) {
    ketemu = n;
    break;
  }
}
console.log(ketemu); // 7
```

`break` hanya keluar dari loop terdekat, bukan semua loop bersarang, kecuali memakai label.

**Biasanya digabungkan dengan:** pencarian, `switch`, dan batas percobaan.

## continue

**Untuk apa:** melewati sisa isi loop, lalu lanjut iterasi berikutnya.

```js
const angka = [1, 2, 3, 4];
for (const n of angka) {
  if (n % 2 === 0) {
    continue;
  }
  console.log(n); // 1, 3
}
```

Sering bisa diganti `filter` jika tujuannya membuat daftar baru.

**Biasanya digabungkan dengan:** melewati item tidak valid tanpa `if` dalam.

## label loop

**Untuk apa:** `break`/`continue` ke loop luar.

```js
luar: for (let i = 0; i < 3; i += 1) {
  for (let j = 0; j < 3; j += 1) {
    if (i === 1 && j === 1) {
      break luar;
    }
    console.log(i, j);
  }
}
```

Jarang dipakai. Jika logikanya rumit, pecah ke fungsi dan `return`.

**Biasanya digabungkan dengan:** pencarian di tabel 2 dimensi.

## loop bersarang

**Untuk apa:** memproses pasangan data, misalnya ukuran dan warna.

```js
const ukuran = ["S", "M"];
const warna = ["merah", "navy"];
const varian = [];
for (const u of ukuran) {
  for (const w of warna) {
    varian.push(`${u}-${w}`);
  }
}
console.log(varian);
```

Kompleksitas naik cepat. Untuk array besar, pikirkan apakah data bisa diolah lebih datar.

**Biasanya digabungkan dengan:** kombinasi opsi produk dan tabel.

## try / catch / finally

**Untuk apa:** menangkap error agar program bisa menampilkan pesan, bukan berhenti.

```js
try {
  const data = JSON.parse("{ rusak");
  console.log(data);
} catch (error) {
  console.error("JSON tidak valid", error.message);
} finally {
  console.log("Selesai dicoba");
}
```

- `try`: kode yang mungkin gagal
- `catch`: jalan jika ada error
- `finally`: selalu jalan, sukses atau gagal

Jangan membungkus seluruh aplikasi dalam satu `try`. Bungkus titik yang memang bisa gagal: `JSON.parse`, `fetch`, akses storage.

`catch` hanya menangkap error sinkron di blok itu, atau error yang di-`await` di dalam `try`.

**Biasanya digabungkan dengan:** `JSON.parse`, `fetch`, dan `localStorage`.

## throw

**Untuk apa:** melempar error sendiri jika syarat bisnis dilanggar.

```js
function hitungTotal(harga, jumlah) {
  if (jumlah < 1) {
    throw new Error("Jumlah minimal 1");
  }
  return harga * jumlah;
}
```

Bisa melempar apa saja, tetapi lempar `Error` (atau turunannya) agar ada `message` dan stack.

```js
throw new Error("Stok tidak cukup");
```

**Biasanya digabungkan dengan:** validasi fungsi, `try/catch`, dan helper API.

## Error

**Untuk apa:** objek error standar dengan pesan.

```js
const error = new Error("Gagal menyimpan");
console.log(error.message);
console.log(error.name); // "Error"
```

Properti yang sering dipakai:

```js
error.message;
error.name;
error.stack; // jejak baris, berguna di Console
```

**Biasanya digabungkan dengan:** `throw`, `catch`, dan log.

## TypeError

**Untuk apa:** menandai nilai dipakai dengan cara yang salah.

```js
try {
  const produk = null;
  console.log(produk.nama);
} catch (error) {
  console.log(error instanceof TypeError); // true
}
```

Muncul jika memanggil yang bukan fungsi, atau membaca properti `null`.

```js
const cetak = undefined;
// cetak(); // TypeError: cetak is not a function
```

**Biasanya digabungkan dengan:** `?.`, pengecekan fungsi, dan data API.

## RangeError

**Untuk apa:** menandai nilai di luar jangkauan yang diizinkan.

```js
try {
  const list = new Array(-1);
} catch (error) {
  console.log(error instanceof RangeError);
}
```

Juga muncul pada `toFixed` dengan digit aneh atau stack rekursi terlalu dalam.

**Biasanya digabungkan dengan:** argument numerik dan array berukuran.

## SyntaxError

**Untuk apa:** kode atau teks yang di-`eval`/`JSON.parse` tidak valid.

```js
try {
  JSON.parse("bukan json");
} catch (error) {
  console.log(error instanceof SyntaxError);
}
```

Syntax error di file JS biasanya menghentikan file sebelum jalan, jadi tidak tertangkap `try` di file yang sama.

**Biasanya digabungkan dengan:** `JSON.parse` dan data dari server/storage.

## ReferenceError

**Untuk apa:** variabel yang belum ada dipakai.

```js
try {
  console.log(namaTokoBelumAda);
} catch (error) {
  console.log(error instanceof ReferenceError);
}
```

Sering karena typo nama variabel atau memakai `let` sebelum barisnya (temporal dead zone).

**Biasanya digabungkan dengan:** debug nama variabel dan scope.

## optional catch binding

**Untuk apa:** menulis `catch` tanpa nama error jika pesannya tidak dipakai.

```js
try {
  JSON.parse(teks);
} catch {
  console.log("Data rusak, pakai cadangan");
}
```

Pakai jika kamu tidak perlu `error.message`. Jika perlu log, tetap beri nama.

**Biasanya digabungkan dengan:** fallback data lokal.

## error async

**Untuk apa:** menangkap kegagalan `await` / `fetch`.

```js
async function ambilProduk() {
  try {
    const respons = await fetch("/api/produk");
    if (!respons.ok) {
      throw new Error(`HTTP ${respons.status}`);
    }
    return await respons.json();
  } catch (error) {
    console.error(error.message);
    return [];
  }
}
```

`try/catch` di luar fungsi async tidak menangkap Promise yang tidak di-`await`.

```js
ambilProduk(); // error dalamnya tidak tertangkap di sini
ambilProduk().catch((error) => console.error(error));
```

Detail Promise ada di [file 07](07-json-set-map-promise.md) dan [file 10](10-fetch-async-storage.md).

**Biasanya digabungkan dengan:** `async/await`, `fetch`, dan pesan UI.

## pola validasi

**Untuk apa:** menolak masukan buruk sebelum memproses.

```js
function bacaJumlah(teks) {
  const jumlah = Number(teks);
  if (!Number.isInteger(jumlah)) {
    throw new Error("Jumlah harus bilangan bulat");
  }
  if (jumlah < 1 || jumlah > 99) {
    throw new Error("Jumlah 1 sampai 99");
  }
  return jumlah;
}

try {
  const jumlah = bacaJumlah("2");
  console.log("OK", jumlah);
} catch (error) {
  console.log(error.message);
}
```

Validasi berlapis:

1. tipe dan format
2. rentang
3. aturan bisnis (stok, login)

**Biasanya digabungkan dengan:** form, file 09, dan pesan error di DOM.

## Kapan pakai apa

| Kebutuhan | Alat |
| --- | --- |
| Dua cabang nilai | ternary atau `if` |
| Banyak string tetap | `switch` |
| Rentang angka | `else if` |
| Daftar array | `for...of` atau method |
| Butuh indeks | `for` atau `entries()` |
| Berhenti di tengah | `for` + `break` |
| Efek ke tiap item | `forEach` |
| JSON/fetch bisa gagal | `try/catch` |

## Kesalahan loop yang sering

Mengubah array sambil `forEach` maju bisa mengacaukan indeks. Untuk hapus item, kumpulkan dulu atau pakai `filter`.

```js
const keranjang = [
  { id: 1, nama: "Buku" },
  { id: 2, nama: "Pensil" },
];
const sisa = keranjang.filter((item) => item.id !== 1);
```

Loop tak berhingga:

```js
let i = 0;
while (i < 5) {
  console.log(i);
  // lupa i += 1
}
```

Off-by-one:

```js
// i <= daftar.length  → indeks terakhir undefined
for (let i = 0; i < daftar.length; i += 1) {
  console.log(daftar[i]);
}
```

**Biasanya digabungkan dengan:** file 05 untuk `filter`/`map` sebagai ganti loop manual.
