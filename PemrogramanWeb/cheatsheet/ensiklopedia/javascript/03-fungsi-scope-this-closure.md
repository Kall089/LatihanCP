# 03 — Fungsi, scope, this, dan closure

[← 02 Kondisi](02-kondisi-loop-error.md) · [Indeks](README.md) · [Lanjut 04 →](04-object-destructure-spread.md)

Fungsi membungkus langkah agar bisa dipanggil ulang. Scope mengatur siapa yang melihat variabel. Closure mengingat lingkungan. `this` menunjuk “pemilik” pemanggilan.

## Daftar isi

- [function declaration](#function-declaration)
- [function expression](#function-expression)
- [arrow function](#arrow-function)
- [parameter](#parameter)
- [default parameter](#default-parameter)
- [rest parameter](#rest-parameter)
- [arguments](#arguments)
- [return](#return)
- [fungsi tanpa return](#fungsi-tanpa-return)
- [callback](#callback)
- [higher-order function](#higher-order-function)
- [IIFE](#iife)
- [hoisting fungsi](#hoisting-fungsi)
- [scope global](#scope-global)
- [scope fungsi](#scope-fungsi)
- [block scope](#block-scope)
- [lexical scope](#lexical-scope)
- [temporal dead zone](#temporal-dead-zone)
- [closure](#closure)
- [factory function](#factory-function)
- [this di method](#this-di-method)
- [this di fungsi biasa](#this-di-fungsi-biasa)
- [this di arrow](#this-di-arrow)
- [this di event DOM](#this-di-event-dom)
- [call](#call)
- [apply](#apply)
- [bind](#bind)
- [rekursi](#rekursi)
- [fungsi sebagai nilai](#fungsi-sebagai-nilai)
- [pure function](#pure-function)

## function declaration

**Untuk apa:** membuat fungsi bernama yang bisa dipanggil dari mana pun di scope-nya.

```js
function hitungTotal(harga, jumlah) {
  return harga * jumlah;
}

console.log(hitungTotal(45000, 2)); // 90000
```

Deklarasi di-hoist: bisa dipanggil sebelum baris tulisannya di file yang sama (dalam scope yang sama).

```js
console.log(formatSapa("Haikal"));

function formatSapa(nama) {
  return `Halo, ${nama}`;
}
```

Nama fungsi muncul di stack error, membantu debug.

**Biasanya digabungkan dengan:** helper harga, validasi, dan handler yang dipanggil dari banyak tempat.

## function expression

**Untuk apa:** menyimpan fungsi sebagai nilai variabel.

```js
const hitungTotal = function (harga, jumlah) {
  return harga * jumlah;
};
```

Tidak di-hoist seperti deklarasi. Tidak bisa dipanggil sebelum baris `const`.

Bisa diberi nama untuk debug:

```js
const hitungTotal = function hitungTotalDalam(harga, jumlah) {
  return harga * jumlah;
};
```

**Biasanya digabungkan dengan:** callback, object method, dan ekspor module.

## arrow function

**Untuk apa:** menulis fungsi pendek, terutama callback.

```js
const hitungTotal = (harga, jumlah) => harga * jumlah;
const double = (n) => n * 2;
const tanpaParam = () => "Toko Belajar";
```

Jika isi lebih dari satu pernyataan, pakai `{ }` dan `return` eksplisit.

```js
const ringkas = (produk) => {
  const pajak = 0.11;
  return Math.round(produk.harga * (1 + pajak));
};
```

Jika mengembalikan object langsung, bungkus dengan kurung:

```js
const buatItem = (nama) => ({ nama, jumlah: 1 });
```

Arrow tidak punya `this`, `arguments`, atau `new`. Cocok untuk `map`/`filter`, kurang cocok untuk method object yang butuh `this`.

**Biasanya digabungkan dengan:** `map`, `filter`, `find`, Promise `.then`, dan timer.

## parameter

**Untuk apa:** menerima masukan saat fungsi dipanggil.

```js
function labelProduk(nama, harga) {
  return `${nama}: Rp${harga}`;
}

labelProduk("Buku", 45000);
```

Jumlah argumen boleh kurang atau lebih. Yang tidak dikirim menjadi `undefined`. Yang berlebih diabaikan, kecuali ditangkap `rest`.

```js
function contoh(a, b) {
  console.log(a, b);
}
contoh(1); // 1 undefined
contoh(1, 2, 3); // 1 2
```

Parameter adalah variabel lokal. Mengganti parameter tidak mengubah variabel pemanggil untuk tipe primitif.

**Biasanya digabungkan dengan:** default, rest, dan destructure parameter.

## default parameter

**Untuk apa:** mengisi nilai jika argumen `undefined`.

```js
function hitungTotal(harga, jumlah = 1) {
  return harga * jumlah;
}

console.log(hitungTotal(45000)); // 45000
console.log(hitungTotal(45000, 3)); // 135000
```

Default tidak aktif untuk `null` atau `0`.

```js
function sapa(nama = "Pengunjung") {
  return nama;
}
sapa(null); // null
sapa(0); // 0
sapa(undefined); // "Pengunjung"
```

Default boleh memakai parameter sebelumnya:

```js
function pajak(harga, persen = 11, total = harga * (1 + persen / 100)) {
  return total;
}
```

**Biasanya digabungkan dengan:** opsi fungsi, `??`, dan API helper.

## rest parameter

**Untuk apa:** menampung sisa argumen menjadi array.

```js
function jumlahkan(...angka) {
  return angka.reduce((total, n) => total + n, 0);
}

console.log(jumlahkan(1, 2, 3, 4)); // 10
```

Rest harus parameter terakhir.

```js
function pesan(judul, ...isi) {
  return `${judul}: ${isi.join(", ")}`;
}
```

Beda dengan spread: rest **mengumpulkan**, spread **membentangkan**. Lihat file 04 dan 05.

**Biasanya digabungkan dengan:** `reduce`, helper log, dan fungsi variadic.

## arguments

**Untuk apa:** objek mirip array berisi semua argumen fungsi biasa.

```js
function lama() {
  console.log(arguments[0], arguments.length);
}
lama("Buku", 2);
```

Bukan array sungguhan. Tidak ada di arrow function. Di kode baru, pakai rest `...args`.

```js
const baru = (...args) => args.length;
```

**Biasanya digabungkan dengan:** kode warisan. Hindari di latihan baru.

## return

**Untuk apa:** mengeluarkan hasil dan menghentikan fungsi.

```js
function diskon(harga, persen) {
  return harga * (1 - persen / 100);
}
```

Tanpa `return`, hasil pemanggilan adalah `undefined`.

```js
function diam(nilai) {
  nilai * 2;
}
console.log(diam(4)); // undefined
```

`return` tanpa nilai juga `undefined`. Boleh ada banyak `return` (guard clause).

Setelah `return`, baris berikutnya di fungsi itu tidak jalan.

```js
function cek(stok) {
  if (stok <= 0) {
    return "Habis";
  }
  return "Ada";
}
```

**Biasanya digabungkan dengan:** helper murni, `map`, dan early exit.

## fungsi tanpa return

**Untuk apa:** efek samping: mengubah DOM, menulis log, menyimpan data.

```js
function tampilkanError(pesan) {
  console.error(pesan);
}
```

Sah, tetapi pisahkan jika bisa: fungsi penghitung mengembalikan nilai; fungsi tampilan menulis ke halaman.

**Biasanya digabungkan dengan:** event handler dan `forEach`.

## callback

**Untuk apa:** fungsi yang dikirim sebagai argumen, dipanggil nanti.

```js
function prosesBayar(total, onSukses) {
  if (total <= 0) {
    return;
  }
  onSukses(total);
}

prosesBayar(90000, (nilai) => {
  console.log("Berhasil", nilai);
});
```

Callback adalah dasar `addEventListener`, `map`, `setTimeout`, dan Promise `.then`.

Urutan argumen callback array biasanya `(item, indeks, array)`.

**Biasanya digabungkan dengan:** event, timer, dan method array.

## higher-order function

**Untuk apa:** fungsi yang menerima atau mengembalikan fungsi.

```js
function denganPajak(persen) {
  return (harga) => Math.round(harga * (1 + persen / 100));
}

const plusPpn = denganPajak(11);
console.log(plusPpn(45000));
```

`map`, `filter`, `setTimeout` adalah higher-order: mereka menerima fungsi.

**Biasanya digabungkan dengan:** closure, factory, dan utilitas berulang.

## IIFE

**Untuk apa:** langsung menjalankan fungsi agar variabel tidak bocor ke global.

```js
(() => {
  const rahasia = 123;
  console.log(rahasia);
})();
```

Dulu penting sebelum module dan block scope. Sekarang file module atau `{ }` biasa biasanya cukup.

**Biasanya digabungkan dengan:** skrip lama tanpa bundler. Di proyek baru, pakai module.

## hoisting fungsi

**Untuk apa:** memahami mengapa deklarasi bisa dipanggil di atas.

```js
jalan(); // aman

function jalan() {
  console.log("siap");
}
```

`const fn = function () {}` dan arrow tidak bisa dipanggil sebelum inisialisasi.

```js
// jalan(); // ReferenceError
const jalan = () => console.log("siap");
```

**Biasanya digabungkan dengan:** urutan tulis helper di satu file.

## scope global

**Untuk apa:** variabel di puncak file/script, terlihat luas.

```js
const NAMA_TOKO = "Toko Belajar";

function judul() {
  return NAMA_TOKO;
}
```

Terlalu banyak global membuat nama bentrok. Di browser tanpa module, `var` di puncak menempel ke `window`.

Di ES module, variabel puncak file tidak otomatis jadi `window.nama`.

**Biasanya digabungkan dengan:** konstanta konfigurasi. Jangan menaruh keranjang global jika bisa di-module.

## scope fungsi

**Untuk apa:** variabel di dalam fungsi hanya hidup di situ.

```js
function hitung() {
  const pajak = 0.11;
  return pajak;
}
// console.log(pajak); // error
```

Parameter juga lokal.

`var` mengabaikan block, tetap function scope:

```js
function tes() {
  if (true) {
    var x = 1;
  }
  console.log(x); // 1
}
```

**Biasanya digabungkan dengan:** helper dan isolasi data sementara.

## block scope

**Untuk apa:** `let`/`const` hidup di dalam `{ }`, `if`, `for`, `while`.

```js
for (let i = 0; i < 3; i += 1) {
  const label = `item-${i}`;
  console.log(label);
}
// console.log(i); // error
```

Setiap putaran `for (let i ...)` punya `i` sendiri. Itu penting untuk callback di loop.

```js
for (let i = 0; i < 3; i += 1) {
  setTimeout(() => console.log(i), 0); // 0 1 2
}
```

Dengan `var`, ketiganya sering mencetak `3`.

**Biasanya digabungkan dengan:** `if`, `for`, dan `try`.

## lexical scope

**Untuk apa:** fungsi dalam melihat variabel fungsi luar yang menulisnya, bukan yang memanggilnya.

```js
const pajak = 11;

function denganPajak(harga) {
  function rumus() {
    return harga * (1 + pajak / 100);
  }
  return rumus();
}
```

`rumus` memakai `harga` dan `pajak` dari tempat ia ditulis.

**Biasanya digabungkan dengan:** closure dan module.

## temporal dead zone

**Untuk apa:** zona sebelum `let`/`const` diinisialisasi, tidak boleh diakses.

```js
{
  // console.log(nama); // ReferenceError
  const nama = "Buku";
}
```

Beda dengan `var` yang memberi `undefined`.

**Biasanya digabungkan dengan:** urutan deklarasi di block.

## closure

**Untuk apa:** fungsi dalam mengingat variabel luar meski fungsi luar sudah selesai.

```js
function buatPenghitung(awal = 0) {
  let nilai = awal;
  return {
    naik() {
      nilai += 1;
      return nilai;
    },
    baca() {
      return nilai;
    },
  };
}

const keranjang = buatPenghitung();
console.log(keranjang.naik()); // 1
console.log(keranjang.naik()); // 2
console.log(keranjang.baca()); // 2
```

`nilai` tidak bisa disentuh langsung dari luar. Ini dasar private state sederhana.

Contoh event:

```js
function pasangSapa(nama) {
  return function () {
    console.log(`Halo, ${nama}`);
  };
}
tombol.addEventListener("click", pasangSapa("Haikal"));
```

**Biasanya digabungkan dengan:** factory, event, timer, dan module.

## factory function

**Untuk apa:** fungsi yang menghasilkan object dengan perilaku.

```js
function buatProduk(nama, harga) {
  return {
    nama,
    harga,
    label() {
      return `${nama} — Rp${harga}`;
    },
  };
}

const buku = buatProduk("Buku", 45000);
console.log(buku.label());
```

Setiap pemanggilan membuat closure/object baru. Untuk banyak instance dengan method bersama, class juga opsi; untuk tugas dasar, factory cukup.

**Biasanya digabungkan dengan:** closure dan object literal.

## this di method

**Untuk apa:** menunjuk object yang memanggil method.

```js
const produk = {
  nama: "Buku",
  harga: 45000,
  label() {
    return `${this.nama}: Rp${this.harga}`;
  },
};

console.log(produk.label());
```

Jika method dipisah, `this` bisa hilang:

```js
const fn = produk.label;
fn(); // this bukan produk
```

Perbaiki dengan `bind`, arrow pembungkus, atau panggil lewat object.

**Biasanya digabungkan dengan:** object, class, dan `bind`.

## this di fungsi biasa

**Untuk apa:** di module/strict, `this` adalah `undefined` jika dipanggil polos.

```js
function cetak() {
  console.log(this);
}
cetak(); // undefined di module
```

Di script non-module lama, `this` bisa menjadi `window`. Jangan mengandalkan itu.

**Biasanya digabungkan dengan:** alasan memakai arrow atau `bind` pada callback.

## this di arrow

**Untuk apa:** arrow memakai `this` leksikal dari luar, tidak punya `this` sendiri.

```js
const keranjang = {
  item: ["Buku"],
  cetak() {
    this.item.forEach((nama) => {
      console.log(this.item.length, nama);
    });
  },
};
```

Jika `forEach` memakai fungsi biasa, `this` di dalamnya bukan `keranjang` (kecuali kamu kirim argumen `thisArg`).

Jangan menulis method object sebagai arrow jika kamu butuh `this` object itu.

```js
const produk = {
  nama: "Buku",
  label: () => this.nama, // this bukan produk
};
```

**Biasanya digabungkan dengan:** callback di dalam method dan timer di dalam class.

## this di event DOM

**Untuk apa:** di handler fungsi biasa, `this` adalah elemen yang dipasangi listener.

```js
tombol.addEventListener("click", function () {
  console.log(this.id);
  this.classList.add("aktif");
});
```

Arrow tidak mengambil elemen sebagai `this`:

```js
tombol.addEventListener("click", () => {
  // this bukan tombol
});
```

Lebih jelas memakai `event.currentTarget` daripada mengandalkan `this`. Lihat [file 09](09-event-form-delegation.md).

**Biasanya digabungkan dengan:** `addEventListener` dan `classList`.

## call

**Untuk apa:** memanggil fungsi dengan `this` yang kamu tentukan, argumen berurutan.

```js
function label(awalan) {
  return `${awalan} ${this.nama}`;
}

const produk = { nama: "Buku" };
console.log(label.call(produk, "Item"));
```

**Biasanya digabungkan dengan:** meminjam method dan kode yang menerima `this`.

## apply

**Untuk apa:** seperti `call`, tetapi argumen dalam array.

```js
const angka = [3, 8, 2];
console.log(Math.max.apply(null, angka));
```

Di kode baru, spread lebih jelas:

```js
Math.max(...angka);
```

**Biasanya digabungkan dengan:** kode lama yang mengirim array argumen.

## bind

**Untuk apa:** membuat fungsi baru yang `this`-nya terikat tetap.

```js
const produk = {
  nama: "Buku",
  label() {
    return this.nama;
  },
};

const ambilNama = produk.label.bind(produk);
console.log(ambilNama());
```

Bisa mengikat argumen di depan (partial):

```js
function kali(a, b) {
  return a * b;
}
const double = kali.bind(null, 2);
console.log(double(5)); // 10
```

`bind` tidak mengubah fungsi asli.

**Biasanya digabungkan dengan:** callback method, event, dan timer.

## rekursi

**Untuk apa:** fungsi memanggil dirinya sampai syarat berhenti.

```js
function faktorial(n) {
  if (n <= 1) {
    return 1;
  }
  return n * faktorial(n - 1);
}
```

Wajib ada basis. Tanpa itu, stack overflow / `RangeError`.

Untuk daftar datar, loop atau method array biasanya lebih sederhana.

**Biasanya digabungkan dengan:** pohon menu, folder bersarang, dan struktur rekursif.

## fungsi sebagai nilai

**Untuk apa:** menyimpan, mengirim, dan mengembalikan fungsi seperti data.

```js
const operasi = {
  tambah: (a, b) => a + b,
  kali: (a, b) => a * b,
};

function jalankan(nama, a, b) {
  return operasi[nama](a, b);
}

console.log(jalankan("kali", 3, 4));
```

Ini dasar strategi: pilih perilaku dari peta, bukan `if` panjang.

**Biasanya digabungkan dengan:** `switch` alternatif, event map, dan plugin kecil.

## pure function

**Untuk apa:** hasil hanya bergantung pada argumen, tanpa mengubah data luar.

```js
function totalBaris(harga, jumlah) {
  return harga * jumlah;
}
```

Tidak pure:

```js
let pajak = 11;
function totalKotor(harga) {
  pajak += 1; // mengubah luar
  return harga * (1 + pajak / 100);
}
```

Fungsi pure mudah diuji dan dipakai di `map`. Efek DOM/storage biarkan di tepi program.

**Biasanya digabungkan dengan:** `map`/`filter`/`reduce` dan tes.

## destructure parameter

**Untuk apa:** langsung mengambil field object/array di daftar parameter.

```js
function labelProduk({ nama, harga }) {
  return `${nama} — Rp${harga}`;
}

labelProduk({ nama: "Buku", harga: 45000 });
```

Default object kosong mencegah error jika tidak dikirim:

```js
function tampil({ judul = "Tanpa judul" } = {}) {
  return judul;
}
tampil();
```

**Biasanya digabungkan dengan:** file 04, opsi fungsi, dan props React.

## Kesalahan fungsi yang sering

Lupa `return` di arrow berkurung kurawal:

```js
const salah = (n) => {
  n * 2;
};
const benar = (n) => n * 2;
```

Memanggil method sebagai callback tanpa `bind`:

```js
// setTimeout(produk.label, 0); // this hilang
setTimeout(() => produk.label(), 0);
```

Mengira default parameter menangkap `null`.

Menulis terlalu banyak tanggung jawab dalam satu fungsi: hitung + tampil + simpan. Pecah.

**Biasanya digabungkan dengan:** file 13 resep dan kesalahan.
