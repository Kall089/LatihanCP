# 04 — Object, destructure, dan spread

[← 03 Fungsi](03-fungsi-scope-this-closure.md) · [Indeks](README.md) · [Lanjut 05 →](05-array-method-lengkap.md)

Object menyimpan data beratribut. Destructuring mengambil field. Spread menyalin atau menggabungkan.

## Daftar isi

- [object literal](#object-literal)
- [akses titik](#akses-titik)
- [akses kurung](#akses-kurung)
- [shorthand properti](#shorthand-properti)
- [computed property](#computed-property)
- [method singkat](#method-singkat)
- [tambah dan ubah properti](#tambah-dan-ubah-properti)
- [hapus properti](#hapus-properti)
- [object bersarang](#object-bersarang)
- [destructuring object](#destructuring-object)
- [ganti nama saat destructure](#ganti-nama-saat-destructure)
- [default saat destructure](#default-saat-destructure)
- [destructure bersarang](#destructure-bersarang)
- [rest object](#rest-object)
- [spread object](#spread-object)
- [Object.assign](#objectassign)
- [Object.keys](#objectkeys)
- [Object.values](#objectvalues)
- [Object.entries](#objectentries)
- [Object.fromEntries](#objectfromentries)
- [Object.hasOwn](#objecthasown)
- [hasOwnProperty](#hasownproperty)
- [Object.freeze](#objectfreeze)
- [Object.seal](#objectseal)
- [Object.create](#objectcreate)
- [Object.getPrototypeOf](#objectgetprototypeof)
- [structuredClone](#structuredclone)
- [optional chaining pada object](#optional-chaining-pada-object)
- [penggabungan opsi](#penggabungan-opsi)
- [object sebagai kamus](#object-sebagai-kamus)

## object literal

**Untuk apa:** membuat satu paket data dengan nama field.

```js
const produk = {
  id: 1,
  nama: "Buku Tulis",
  harga: 45000,
  tersedia: true,
};
```

Kunci biasanya identifier. Jika ada spasi atau karakter aneh, tulis string:

```js
const label = {
  "nama lengkap": "Buku Tulis 58",
};
```

**Biasanya digabungkan dengan:** array produk, JSON API, dan state halaman.

## akses titik

**Untuk apa:** membaca atau menulis field yang namanya identifier valid.

```js
console.log(produk.nama);
produk.harga = 50000;
```

Tidak bisa memakai variabel sebagai nama field. Tidak nyaman jika kuncinya `"nama-lengkap"`.

Jika kiri `null`/`undefined`, error. Pakai `?.`.

**Biasanya digabungkan dengan:** field yang sudah diketahui: `id`, `nama`, `harga`.

## akses kurung

**Untuk apa:** memakai kunci dari string atau variabel.

```js
const kunci = "harga";
console.log(produk[kunci]);
console.log(produk["nama"]);
```

Wajib untuk kunci dinamis, misalnya nilai `name` pada form.

```js
function ambil(obj, kunci) {
  return obj[kunci];
}
```

**Biasanya digabungkan dengan:** form, query, dan loop `Object.keys`.

## shorthand properti

**Untuk apa:** menulis field dari variabel bernama sama.

```js
const nama = "Pensil";
const harga = 8000;
const produk = { nama, harga };
```

Sama dengan `{ nama: nama, harga: harga }`.

**Biasanya digabungkan dengan:** `return` object, factory, dan `JSON.stringify`.

## computed property

**Untuk apa:** nama field dihitung saat object dibuat.

```js
const field = "stok";
const produk = {
  nama: "Buku",
  [field]: 12,
  [`label-${field}`]: "Ada",
};
```

Berguna saat merakit object dari form atau query.

**Biasanya digabungkan dengan:** reducer, filter URL, dan kamus dinamis.

## method singkat

**Untuk apa:** menaruh fungsi di object tanpa kata `function`.

```js
const keranjang = {
  item: [],
  tambah(nama) {
    this.item.push(nama);
  },
};
```

`this` merujuk object pemanggil. Lihat [file 03](03-fungsi-scope-this-closure.md#this-di-method).

**Biasanya digabungkan dengan:** `this`, `bind`, dan model kecil tanpa class.

## tambah dan ubah properti

**Untuk apa:** mengisi field baru atau menimpa yang ada.

```js
const produk = { nama: "Buku" };
produk.harga = 45000;
produk["stok"] = 10;
```

`const` tidak mencegah ini. Yang dilarang adalah `produk = ...` ulang.

Untuk tidak mengubah object lama, buat salinan:

```js
const diperbarui = { ...produk, harga: 50000 };
```

**Biasanya digabungkan dengan:** spread, state, dan form edit.

## hapus properti

**Untuk apa:** membuang field.

```js
const produk = { nama: "Buku", sementara: true };
delete produk.sementara;
```

Alternatif tanpa `delete`:

```js
const { sementara, ...sisa } = produk;
```

`sisa` adalah object baru tanpa `sementara`.

**Biasanya digabungkan dengan:** rest object dan sanitasi data sebelum dikirim.

## object bersarang

**Untuk apa:** menaruh object di dalam object.

```js
const pesanan = {
  id: 9,
  pembeli: {
    nama: "Haikal",
    alamat: { kota: "Bandung" },
  },
};
console.log(pesanan.pembeli.alamat.kota);
```

Akses dalam mudah error jika ada yang null. Pakai `?.`.

Menyalin dangkal (`{ ...pesanan }`) tidak menyalin `alamat` secara terpisah; keduanya masih berbagi object dalam.

**Biasanya digabungkan dengan:** `?.`, `structuredClone`, dan destructure bersarang.

## destructuring object

**Untuk apa:** mengambil field menjadi variabel.

```js
const produk = { nama: "Buku", harga: 45000, stok: 4 };
const { nama, harga } = produk;
console.log(nama, harga);
```

Field yang tidak disebutkan diabaikan. Nama di kiri harus sama dengan kunci, kecuali diganti.

Boleh di parameter fungsi:

```js
function label({ nama, harga }) {
  return `${nama} — ${harga}`;
}
```

**Biasanya digabungkan dengan:** hasil API, props, dan `map`.

## ganti nama saat destructure

**Untuk apa:** menghindari bentrok nama atau memperjelas.

```js
const { nama: namaProduk, harga: hargaJual } = produk;
```

Pola dari `import` mirip secara ide: ambil, lalu panggil dengan nama lokal.

**Biasanya digabungkan dengan:** dua object yang sama-sama punya `nama`.

## default saat destructure

**Untuk apa:** mengisi jika field `undefined`.

```js
const { stok = 0, kategori = "umum" } = produk;
```

Tidak mengganti `null`. Gabungkan jika perlu:

```js
const { diskon } = produk;
const persen = diskon ?? 0;
```

**Biasanya digabungkan dengan:** `??` dan opsi yang opsional.

## destructure bersarang

**Untuk apa:** mengambil field dalam sekaligus.

```js
const {
  pembeli: {
    alamat: { kota },
  },
} = pesanan;
```

Jika `pembeli` kosong, error. Lebih aman pecah atau pakai default:

```js
const { pembeli: { alamat: { kota } = {} } = {} } = pesanan;
```

Untuk data tidak pasti, `pesanan.pembeli?.alamat?.kota` sering lebih mudah dibaca.

**Biasanya digabungkan dengan:** JSON bersarang yang strukturnya kamu yakini.

## rest object

**Untuk apa:** mengumpulkan sisa field ke object baru.

```js
const { id, ...dataPublik } = produk;
```

`id` terpisah; `dataPublik` tanpa `id`. Berguna saat membuang field rahasia sebelum ditampilkan.

Rest harus di akhir.

**Biasanya digabungkan dengan:** spread, API response, dan clone sebagian.

## spread object

**Untuk apa:** menyalin field ke object baru, menimpa yang disebut belakangan.

```js
const dasar = { nama: "Buku", harga: 45000 };
const promo = { ...dasar, harga: 40000, label: "promo" };
```

Urutan penting: yang kanan menang.

```js
const gabung = { ...defaultOpsi, ...opsiPengguna };
```

Spread object adalah salinan dangkal. Object/array di dalam masih berbagi referensi.

```js
const a = { filter: { kota: "Bandung" } };
const b = { ...a };
b.filter.kota = "Jakarta";
console.log(a.filter.kota); // "Jakarta"
```

**Biasanya digabungkan dengan:** update state, opsi, dan `fetch` body.

## Object.assign

**Untuk apa:** menyalin field ke object tujuan, mengubah tujuan itu.

```js
const tujuan = { nama: "Buku" };
Object.assign(tujuan, { harga: 45000 }, { stok: 3 });
```

`Object.assign({}, sumber)` membuat object baru, mirip spread.

```js
const salinan = Object.assign({}, produk);
```

Spread lebih umum di kode baru. `assign` berguna jika target sudah ada.

**Biasanya digabungkan dengan:** mengisi object yang sudah dibuat, mixin sederhana.

## Object.keys

**Untuk apa:** array berisi nama field milik sendiri (string).

```js
const produk = { nama: "Buku", harga: 45000 };
console.log(Object.keys(produk)); // ["nama", "harga"]
```

Tidak menyertakan Symbol. Urutan mengikuti urutan integer-index lalu field lain sesuai pembuatan.

```js
if (Object.keys(filter).length === 0) {
  console.log("Filter kosong");
}
```

**Biasanya digabungkan dengan:** `map`, loop form, dan cek object kosong.

## Object.values

**Untuk apa:** array berisi nilai field.

```js
Object.values(produk); // ["Buku", 45000]
```

Berguna menjumlahkan nilai numerik di object kamus.

```js
const stokPerKota = { bandung: 3, jakarta: 5 };
const total = Object.values(stokPerKota).reduce((a, b) => a + b, 0);
```

**Biasanya digabungkan dengan:** `reduce`, `some`, dan statistik sederhana.

## Object.entries

**Untuk apa:** array pasangan `[kunci, nilai]`.

```js
for (const [kunci, nilai] of Object.entries(produk)) {
  console.log(kunci, nilai);
}
```

Mudah diubah ke `Map` atau sebaliknya lewat `fromEntries`.

```js
Object.entries(produk).map(([kunci, nilai]) => `${kunci}=${nilai}`);
```

**Biasanya digabungkan dengan:** `for...of`, `map`, dan query string.

## Object.fromEntries

**Untuk apa:** merakit object dari daftar pasangan.

```js
const pasangan = [
  ["nama", "Buku"],
  ["harga", 45000],
];
const produk = Object.fromEntries(pasangan);
```

Sering dipakai setelah `filter` pada entries:

```js
const bersih = Object.fromEntries(
  Object.entries(produk).filter(([kunci]) => kunci !== "rahasia"),
);
```

Juga dari `URLSearchParams` atau `Map`.

**Biasanya digabungkan dengan:** `Object.entries`, `Map`, dan query URL.

## Object.hasOwn

**Untuk apa:** mengecek kunci milik object itu sendiri, bukan prototipe.

```js
Object.hasOwn(produk, "nama"); // true
Object.hasOwn(produk, "toString"); // false
```

Lebih aman daripada `obj.hasOwnProperty("nama")` jika object tidak punya prototipe normal.

**Biasanya digabungkan dengan:** `for...in` dan validasi kunci form.

## hasOwnProperty

**Untuk apa:** cara lama mengecek kunci milik sendiri.

```js
Object.prototype.hasOwnProperty.call(produk, "nama");
```

Pakai `Object.hasOwn` di kode baru.

**Biasanya digabungkan dengan:** kode warisan.

## Object.freeze

**Untuk apa:** mencegah tambah, hapus, dan ubah field tingkat atas.

```js
const konfigurasi = Object.freeze({
  mataUang: "IDR",
  pajak: 11,
});
// konfigurasi.pajak = 12; // diabaikan atau error di strict
```

Dangkal: object dalam masih bisa berubah. Untuk data konfigurasi sederhana sudah cukup.

**Biasanya digabungkan dengan:** konstanta konfigurasi dan mencegah ubah tidak sengaja.

## Object.seal

**Untuk apa:** mencegah tambah/hapus field, tetapi nilai yang ada masih bisa diubah.

```js
const produk = Object.seal({ nama: "Buku", harga: 45000 });
produk.harga = 50000; // boleh
// produk.stok = 1; // tidak ditambahkan
```

Lebih longgar daripada `freeze`. Jarang dibutuhkan di tugas toko.

**Biasanya digabungkan dengan:** model yang fieldnya tetap.

## Object.create

**Untuk apa:** membuat object dengan prototipe yang dipilih.

```js
const proto = {
  label() {
    return this.nama;
  },
};
const produk = Object.create(proto);
produk.nama = "Buku";
console.log(produk.label());
```

`Object.create(null)` membuat object tanpa prototipe: tidak ada `toString` warisan. Berguna untuk kamus murni.

**Biasanya digabungkan dengan:** kamus aman dan pewarisan manual. Class lebih umum untuk model.

## Object.getPrototypeOf

**Untuk apa:** melihat prototipe object.

```js
Object.getPrototypeOf([]) === Array.prototype;
```

Untuk debug rantai warisan. Bukan kebutuhan harian toko.

**Biasanya digabungkan dengan:** `instanceof` dan penyelidikan object.

## structuredClone

**Untuk apa:** menyalin object/array secara dalam untuk data terstruktur.

```js
const asli = { filter: { kota: "Bandung" }, tag: ["buku"] };
const salinan = structuredClone(asli);
salinan.filter.kota = "Jakarta";
console.log(asli.filter.kota); // "Bandung"
```

Tidak menyalin fungsi, DOM node, atau beberapa tipe khusus. Untuk JSON-like data, ini lebih aman daripada spread bertingkat.

Alternatif lama: `JSON.parse(JSON.stringify(obj))` — kehilangan `Date` asli, `undefined`, fungsi.

**Biasanya digabungkan dengan:** state yang bersarang dan undo sederhana.

## optional chaining pada object

**Untuk apa:** membaca rantai field yang mungkin putus.

```js
const kota = pesanan.pembeli?.alamat?.kota ?? "Tidak ada";
const metode = pesanan.cetak?.();
```

Jangan menaruh `?.` di setiap titik tanpa alasan; hanya di bagian yang memang bisa kosong.

**Biasanya digabungkan dengan:** `??` dan data API.

## penggabungan opsi

**Untuk apa:** default + opsi pengguna.

```js
const defaultOpsi = { halaman: 1, ukuran: 12, urut: "nama" };

function bacaOpsi(opsi = {}) {
  return { ...defaultOpsi, ...opsi };
}

console.log(bacaOpsi({ halaman: 3 }));
```

Field `undefined` pada spread masih menimpa. Jika pengguna mengirim `{ halaman: undefined }`, default hilang. Bersihkan dulu atau pakai `??` per field.

```js
function bacaOpsi(opsi = {}) {
  return {
    halaman: opsi.halaman ?? defaultOpsi.halaman,
    ukuran: opsi.ukuran ?? defaultOpsi.ukuran,
    urut: opsi.urut ?? defaultOpsi.urut,
  };
}
```

**Biasanya digabungkan dengan:** fungsi helper, fetch query, dan komponen.

## object sebagai kamus

**Untuk apa:** peta kunci → nilai.

```js
const hargaKategori = {
  buku: 45000,
  alat: 8000,
};
console.log(hargaKategori.buku);
```

Jika kunci sering ditambah/hapus atau kuncinya bukan string sederhana, `Map` lebih tepat. Lihat [file 07](07-json-set-map-promise.md).

Hati-hati kunci `"__proto__"`. Untuk masukan pengguna, `Map` atau `Object.create(null)` lebih aman.

**Biasanya digabungkan dengan:** lookup status, warna label, dan terjemahan singkat.

## destructure array (singkat)

**Untuk apa:** mengambil item menurut posisi.

```js
const pasangan = ["Buku", 45000];
const [nama, harga] = pasangan;
const [pertama, ...sisa] = ["A", "B", "C"];
```

Sering dari `Object.entries` atau `split`.

```js
const [kunci, nilai] = ["stok", 4];
```

Detail array ada di [file 05](05-array-method-lengkap.md).

**Biasanya digabungkan dengan:** `entries()`, `split`, dan tukar variabel.

## tukar variabel

**Untuk apa:** menukar dua nilai tanpa variabel ketiga.

```js
let a = 1;
let b = 2;
[a, b] = [b, a];
```

**Biasanya digabungkan dengan:** urutan tampilan dan algoritma sederhana.

## pola salin dan ubah

**Untuk apa:** immutable update: object baru, field berubah.

```js
function ubahHarga(produk, hargaBaru) {
  return { ...produk, harga: hargaBaru };
}

function ubahKota(pesanan, kota) {
  return {
    ...pesanan,
    pembeli: {
      ...pesanan.pembeli,
      alamat: {
        ...pesanan.pembeli.alamat,
        kota,
      },
    },
  };
}
```

Bersarang dalam terasa berisik. `structuredClone` lalu ubah salinan juga sah untuk data lokal sederhana.

**Biasanya digabungkan dengan:** React state dan history undo.

## cek object kosong

**Untuk apa:** mengetahui tidak ada field enumerable.

```js
function kosong(obj) {
  return obj == null || Object.keys(obj).length === 0;
}
```

`{}` truthy, jadi `if (obj)` tidak cukup.

**Biasanya digabungkan dengan:** filter, query, dan validasi payload.

## JSON dan object

**Untuk apa:** object JS ↔ teks untuk dikirim.

```js
const teks = JSON.stringify(produk);
const balik = JSON.parse(teks);
```

Kunci dan aturan ada di [file 07](07-json-set-map-promise.md). Ingat: `undefined` dan fungsi hilang saat stringify.

**Biasanya digabungkan dengan:** `fetch`, `localStorage`, dan API Laravel.

## Kesalahan object yang sering

Mengira spread menyalin dalam. Mengakses rantai tanpa `?.`. Memakai `for...in` tanpa `hasOwn`. Membandingkan object dengan `===` mengharapkan isi sama:

```js
{ nama: "Buku" } === { nama: "Buku" }; // false, beda referensi
```

Bandingkan field, atau pakai JSON (hati-hati urutan/kunci) / fungsi pembanding.

Menimpa default dengan `undefined` lewat spread.

**Biasanya digabungkan dengan:** file 13 dan pengujian di Console.
