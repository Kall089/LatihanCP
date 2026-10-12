# Cheatsheet JavaScript

[← Daftar panduan](README.md) · [CSS](css.md) · [Lanjut React →](react-js.md)

JavaScript mengolah **data dan perilaku**. Contohnya: menghitung total belanja, mengubah teks saat tombol diklik, atau meminta daftar produk dari server.

## Daftar isi

- [Menjalankan JavaScript](#menjalankan-javascript)
- [Variabel dan tipe data](#variabel-dan-tipe-data)
- [Kondisi dan operator](#kondisi-dan-operator)
- [Perulangan](#perulangan)
- [Fungsi](#fungsi)
- [Array dan object](#array-dan-object)
- [JSON](#json)
- [Destructuring dan spread](#destructuring-dan-spread)
- [DOM dan event](#dom-dan-event)
- [querySelectorAll dan classList](#queryselectorall-dan-classlist)
- [Formulir](#formulir)
- [Timer](#timer)
- [Async dan fetch](#async-dan-fetch)
- [Local storage](#local-storage)
- [Import dan export](#import-dan-export)
- [Truthy, switch, dan try/catch](#truthy-switch-dan-trycatch)
- [String, angka, dan tanggal](#string-angka-dan-tanggal)
- [Event delegation](#event-delegation)
- [Set dan Map](#set-dan-map)
- [Debug di Console](#debug-di-console)
- [Kesalahan umum](#kesalahan-umum)

## Menjalankan JavaScript

**Untuk apa:** menghubungkan perilaku JavaScript ke HTML.

```html
<script src="script.js" defer></script>
```

`defer` membuat script klasik dijalankan setelah HTML selesai diparsing. Tulis kode berikut di `script.js`, lalu buka Console browser:

```js
console.log("JavaScript sudah terhubung");
```

Browser menyediakan `document` untuk mengakses HTML. Node.js menjalankan JavaScript di luar browser, tetapi tidak menyediakan DOM browser secara langsung.

**Biasanya digabungkan dengan:** HTML + CSS untuk interaksi sederhana, atau React untuk antarmuka berbasis komponen.

## Variabel dan tipe data

**Untuk apa:** memberi nama pada data agar bisa digunakan kembali.

```js
const nama = "Haikal"; // string: teks
let jumlah = 2; // number: angka, boleh diganti
const sudahLogin = true; // boolean: benar/salah
const kategori = ["Buku", "Alat"]; // array: daftar
const produk = { nama: "Buku", harga: 45000 }; // object: data beratribut
const pilihan = null; // sengaja belum ada pilihan
let alamat; // undefined: belum diberi nilai

jumlah += 1;
console.log(`${nama} membeli ${jumlah} barang`);
```

Pakai `const` jika variabel tidak akan ditugaskan ulang; pakai `let` jika akan berubah. `const` tidak membuat isi object/array kebal perubahan, hanya melarang penggantian referensinya.

**Biasanya digabungkan dengan:** semua logika aplikasi, termasuk props React dan respons API JSON.

## Kondisi dan operator

**Untuk apa:** memilih tindakan berdasarkan keadaan.

```js
const stok = 5;
const sudahLogin = true;

if (stok > 0 && sudahLogin) {
  console.log("Bisa membeli");
} else {
  console.log("Periksa stok atau login dulu");
}

const label = stok > 0 ? "Tersedia" : "Habis";
console.log(label);
console.log(5 === "5"); // false: tipe berbeda

const pengguna = { profil: null };
const kota = pengguna.profil?.kota ?? "Belum diisi";
console.log(kota);
```

`&&` berarti dan, `||` berarti atau, `!` membalik kondisi. `===` membandingkan tanpa konversi tipe. `?.` menghentikan akses jika bagian kirinya `null`/`undefined`. `??` memberi nilai cadangan hanya untuk `null`/`undefined`, sehingga angka `0` dan string kosong tetap dipertahankan.

**Biasanya digabungkan dengan:** validasi, label status, dan conditional rendering React.

## Perulangan

**Untuk apa:** mengulang langkah untuk tiap item atau sampai syarat terpenuhi.

```js
const nama = ["Buku", "Pensil", "Tas"];

for (const item of nama) {
  console.log(item);
}

for (let i = 0; i < nama.length; i += 1) {
  console.log(i, nama[i]);
}

nama.forEach((item) => {
  console.log(item);
});
```

`for...of` paling nyaman untuk array. `for` dengan indeks dipakai jika kamu butuh nomor urut. `while` dipakai jika berhenti berdasarkan syarat, bukan panjang array.

Hindari mengandalkan `for...in` untuk array; itu mengunjungi kunci, bukan pola terbaik untuk daftar.

**Biasanya digabungkan dengan:** merender daftar ke DOM, menjumlahkan harga, dan contoh tanpa `.map()`.

## Fungsi

**Untuk apa:** membungkus langkah yang akan dipakai berkali-kali.

```js
function hitungTotal(harga, jumlah = 1) {
  return harga * jumlah;
}

const formatRupiah = (nilai) =>
  new Intl.NumberFormat("id-ID", {
    style: "currency",
    currency: "IDR",
    maximumFractionDigits: 0,
  }).format(nilai);

console.log(formatRupiah(hitungTotal(45000, 2))); // Rp90.000
```

Parameter adalah masukan, `return` adalah keluaran. `jumlah = 1` menjadi nilai default ketika argumen tidak diberikan atau bernilai `undefined`. Format spasi mata uang bisa berbeda antarlingkungan.

**Biasanya digabungkan dengan:** handler klik, `.map()`, perhitungan harga, dan helper yang diimpor banyak file.

## Array dan object

**Untuk apa:** menyimpan serta mengolah daftar data.

```js
const produk = [
  { id: 1, nama: "Buku", harga: 45000, stok: 3 },
  { id: 2, nama: "Pensil", harga: 5000, stok: 0 },
  { id: 3, nama: "Tas", harga: 90000, stok: 2 },
];

const namaProduk = produk.map((item) => item.nama);
// ["Buku", "Pensil", "Tas"] — mengubah tiap item menjadi bentuk lain

const tersedia = produk.filter((item) => item.stok > 0);
// Buku dan Tas — mengambil semua yang lolos kondisi

const pilihan = produk.find((item) => item.id === 2);
// Object Pensil — mengambil kecocokan pertama, atau undefined

const totalStok = produk.reduce((total, item) => total + item.stok, 0);
// 5 — merangkum banyak item menjadi satu nilai

const adaYangHabis = produk.some((item) => item.stok === 0); // true
const termurah = [...produk].sort((a, b) => a.harga - b.harga);
// Salin dahulu karena sort() mengubah array yang dipanggil
```

`map()` menghasilkan array baru. `forEach()` cocok untuk melakukan tindakan per item, tetapi tidak menghasilkan array hasil pemetaan. `find()` harus diantisipasi ketika hasilnya `undefined`.

**Biasanya digabungkan dengan:** hasil `fetch`, daftar JSX React, pencarian, dan keranjang belanja.

## JSON

**Untuk apa:** menukar data dengan server. JSON adalah teks; object JavaScript adalah data di memori.

```js
const produk = { nama: "Buku", harga: 45000 };
const teks = JSON.stringify(produk);
// '{"nama":"Buku","harga":45000}' — siap dikirim di body fetch

const kembali = JSON.parse(teks);
console.log(kembali.nama);
```

`response.json()` pada `fetch` sudah melakukan parse. `JSON.parse` melempar error jika teks rusak; bungkus dengan `try/catch` jika sumbernya tidak terpercaya.

**Biasanya digabungkan dengan:** `fetch`, Laravel `response()->json()`, dan `localStorage`.

## Destructuring dan spread

**Untuk apa:** mengambil properti dan membuat versi data yang diperbarui tanpa mengubah data awal.

```js
const produk = { id: 1, nama: "Buku", harga: 45000 };
const { nama, harga } = produk;
const diskon = { ...produk, harga: harga - 5000 };

const keranjang = [produk];
const keranjangBaru = [...keranjang, { id: 2, nama: "Pensil", harga: 5000 }];
console.log(nama, diskon, keranjangBaru);
```

`...` menyalin isi satu tingkat. Object bersarang tetap berbagi referensi kecuali ikut disalin. Properti yang ditulis belakangan menimpa properti bernama sama.

**Biasanya digabungkan dengan:** update state React, props, dan pengolahan data API.

## DOM dan event

**Untuk apa:** membaca/mengubah HTML dan merespons tindakan pengguna.

HTML:

```html
<button id="tambah" type="button">Tambah</button>
<p id="hasil" aria-live="polite">Jumlah: 0</p>
<script src="script.js" defer></script>
```

`script.js`:

```js
const tombol = document.querySelector("#tambah");
const hasil = document.querySelector("#hasil");
let jumlah = 0;

tombol.addEventListener("click", () => {
  jumlah += 1;
  hasil.textContent = `Jumlah: ${jumlah}`;
  hasil.classList.toggle("aktif", jumlah >= 3);
});
```

`querySelector()` mengambil elemen pertama yang cocok. `addEventListener()` mendaftarkan fungsi yang baru dijalankan ketika event terjadi. `textContent` memasukkan teks tanpa menganggapnya HTML. Class `aktif` dapat kamu beri gaya di CSS.

**Biasanya digabungkan dengan:** selector CSS dan elemen HTML. Dalam komponen React, gunakan state dan event JSX agar perubahan tampilan tetap dikelola React.

## querySelectorAll dan classList

**Untuk apa:** menyentuh banyak elemen sekaligus, dan menambah/menghapus class tanpa merusak class lain.

```js
const kartu = document.querySelectorAll(".kartu");

kartu.forEach((el) => {
  el.classList.add("siap");
  el.classList.toggle("aktif", el.dataset.stok === "0");
  el.classList.remove("tersembunyi");
});
```

`querySelectorAll` mengembalikan daftar, bukan satu elemen. Memanggil `.addEventListener` langsung padanya akan gagal; looping dulu. `classList` lebih aman daripada `className = "..."` yang menimpa semua class.

`data-stok` di HTML dibaca sebagai `dataset.stok`.

**Biasanya digabungkan dengan:** CSS `.kartu.aktif`, menu, dan daftar yang sudah ada di HTML.

## Formulir

**Untuk apa:** membaca isian tanpa memuat ulang halaman.

```html
<form id="form-nama">
  <label for="nama">Nama</label>
  <input id="nama" name="nama" required />
  <button type="submit">Sapa</button>
</form>
<p id="pesan" aria-live="polite"></p>
```

JavaScript, dimuat dengan `defer`:

```js
const form = document.querySelector("#form-nama");
const pesan = document.querySelector("#pesan");

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const data = new FormData(form);
  const nama = String(data.get("nama") ?? "").trim();
  pesan.textContent = nama ? `Halo, ${nama}!` : "Nama perlu diisi.";
});
```

`name="nama"` menentukan kunci yang dibaca `FormData`, sedangkan `id` menghubungkan input dengan label. `.trim()` membuang spasi di awal/akhir. Nilai input angka tetap perlu dikonversi, misalnya `Number(input.value)`, dan diperiksa dengan `Number.isFinite()`.

**Biasanya digabungkan dengan:** `fetch` POST, validasi server Laravel, atau controlled input React. Validasi browser membantu pengguna; server tetap harus memvalidasi data yang diterima.

## Timer

**Untuk apa:** menunda atau mengulang kerja, misalnya menutup pesan setelah 2 detik.

```js
const id = setTimeout(() => {
  console.log("Dua detik kemudian");
}, 2000);

// clearTimeout(id); // batalkan jika pengguna sudah menutup pesan

const jam = setInterval(() => {
  console.log("tiap 1 detik");
}, 1000);

// clearInterval(jam);
```

Tanpa `clearTimeout` / `clearInterval`, timer tetap jalan meski elemen sudah hilang. Di React, bersihkan di cleanup `useEffect`.

**Biasanya digabungkan dengan:** notifikasi, slideshow, dan Effect React.

## Async dan fetch

**Untuk apa:** menunggu pekerjaan seperti permintaan HTTP tanpa menghentikan seluruh antarmuka.

Contoh ini membutuhkan server dengan endpoint `/api/produk` yang mengembalikan array JSON:

```js
async function ambilProduk() {
  try {
    const response = await fetch("/api/produk", {
      headers: { Accept: "application/json" },
    });

    if (!response.ok) {
      throw new Error(`Permintaan gagal (${response.status})`);
    }

    const produk = await response.json();
    console.log(produk);
    return produk;
  } catch (error) {
    console.error("Tidak dapat memuat produk:", error);
    return null; // null berarti gagal; [] dapat berarti sukses tetapi kosong
  }
}

ambilProduk();
```

`async` membuat fungsi mengembalikan Promise. `await` menunggu hasil Promise dalam fungsi tersebut. `fetch()` tidak otomatis melempar error untuk status 404/500, sehingga `response.ok` diperiksa. [Rujukan perilaku Fetch](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API/Using_Fetch).

Mengirim JSON ke endpoint yang memang menerima POST:

```js
async function kirimProduk(produk) {
  const response = await fetch("/api/produk", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
      Accept: "application/json",
    },
    body: JSON.stringify(produk),
  });

  if (!response.ok) throw new Error(`Gagal menyimpan (${response.status})`);
  return response.json(); // Endpoint contoh diasumsikan mengembalikan JSON
}
```

Tangani error dari `kirimProduk()` dengan `try/catch` saat memanggilnya. Endpoint POST, autentikasi, dan CSRF perlu disiapkan sesuai backend; contoh endpoint GET di panduan Next.js tidak otomatis menyediakan POST.

**Biasanya digabungkan dengan:** API Laravel/Next.js serta tampilan loading, error, kosong, dan sukses.

## Local storage

**Untuk apa:** menyimpan preferensi kecil di browser, misalnya tema.

```js
try {
  localStorage.setItem("tema", "gelap");
  const tema = localStorage.getItem("tema") ?? "terang";
  console.log(tema);
  localStorage.removeItem("tema");
} catch (error) {
  console.warn("Penyimpanan browser tidak tersedia", error);
}
```

Storage menyimpan string. Object perlu `JSON.stringify()` saat disimpan dan `JSON.parse()` saat dibaca; parsing data yang rusak juga bisa gagal. Data ini milik browser/origin tersebut, bukan database bersama. Jangan menyimpan password atau rahasia server di sini.

**Biasanya digabungkan dengan:** tema, preferensi tampilan, dan draft lokal. Di Next.js akses melalui event atau Effect pada Client Component, bukan saat render server.

## Import dan export

**Untuk apa:** membagi program menjadi file yang punya tanggung jawab jelas.

`format.js`:

```js
export function kapital(teks) {
  return teks.toUpperCase();
}
```

`script.js`:

```js
import { kapital } from "./format.js";
console.log(kapital("belajar")); // BELAJAR
```

HTML:

```html
<script type="module" src="script.js"></script>
```

Jalankan lewat server lokal, misalnya `python3 -m http.server 8080` dari folder contoh. Buka `http://localhost:8080`. Module browser ditunda secara default dan perlu path import yang valid.

**Biasanya digabungkan dengan:** React, Next.js, Vite, dan helper lintasfile.

## Truthy, switch, dan try/catch

**Untuk apa:** memutuskan cabang dan menangkap error tanpa merobohkan seluruh script.

Nilai **falsy** di `if`: `false`, `0`, `""`, `null`, `undefined`, `NaN`. Sisanya truthy, termasuk `[]` dan `{}`.

```js
const stok = 0;
if (stok) {
  // tidak jalan, 0 dianggap falsy
}
if (stok > 0) {
  // bandingkan secara eksplisit
}

const peran = "admin";
switch (peran) {
  case "admin":
    console.log("Boleh hapus");
    break;
  case "tamu":
    console.log("Hanya lihat");
    break;
  default:
    console.log("Peran tidak dikenal");
}

try {
  const data = JSON.parse("{ rusak");
} catch (error) {
  console.error("JSON tidak valid", error);
}
```

`??` lebih aman daripada `||` jika `0` atau `""` boleh dipakai.

**Biasanya digabungkan dengan:** validasi form, parse localStorage, dan `fetch`.

## String, angka, dan tanggal

**Untuk apa:** merapikan teks dan hitungan yang sering salah tipe.

```js
const nama = "  Buku CSS  ";
nama.trim().toLowerCase().includes("css"); // true
"Raja Ampat".slice(0, 4); // "Raja"
["A", "B"].join(" · "); // "A · B"

Number("90.000"); // NaN — titik di ID bukan desimal JS
Number("45000"); // 45000
Number.isFinite(45000); // true
Math.max(3, 8, 2); // 8
Math.round(4.6); // 5

const hari = new Date();
hari.toLocaleDateString("id-ID");
```

Input form selalu string. Kalikan harga hanya setelah `Number(...)` dan cek `Number.isFinite`.

**Biasanya digabungkan dengan:** `filter` pencarian, `Intl.NumberFormat`, dan field harga.

## Event delegation

**Untuk apa:** satu listener di induk, bukan puluhan di tiap tombol daftar.

```html
<ul id="daftar">
  <li><button type="button" data-id="1">Hapus</button></li>
</ul>
```

```js
document.querySelector("#daftar").addEventListener("click", (event) => {
  const tombol = event.target.closest("button[data-id]");
  if (!tombol) return;
  console.log("Hapus id", tombol.dataset.id);
});
```

Item baru yang ditambah nanti ikut tertangani. `closest` mencari elemen terdekat yang cocok.

**Biasanya digabungkan dengan:** daftar dinamis dan `data-*`.

## Set dan Map

**Untuk apa:** kumpulan unik, atau pasangan kunci-nilai yang kuncinya bukan hanya string.

```js
const favorit = new Set();
favorit.add(1);
favorit.has(1); // true
favorit.delete(1);

const stok = new Map();
stok.set("buku", 3);
stok.get("buku"); // 3
```

`Set` dipakai di [contoh praktik](contoh-praktik/script.js) untuk id favorit.

**Biasanya digabungkan dengan:** toggle suka, dan cache kecil di memori.

## Debug di Console

**Untuk apa:** melihat nilai, bukan menebak.

```js
console.log("produk", produk);
console.table(produk);
console.warn("stok menipis");
console.error("gagal fetch");
```

Di DevTools: tab **Console** untuk error, **Network** untuk `fetch`, **Elements** untuk HTML/CSS. Tulis `debugger` di baris yang ingin dihentikan.

**Biasanya digabungkan dengan:** semua tugas JS. Jangan biarkan `console.log` menumpuk di tugas yang dikumpulkan jika dosen melarang.

## Kesalahan umum

- **`Cannot read properties of null`:** selector tidak cocok atau HTML belum tersedia.
- **`"2" + 1` menjadi `"21"`:** data masih string; konversi dan validasi dahulu.
- **Hasil `fetch` belum bisa dipakai:** tunggu Promise dengan `await`.
- **Data API gagal:** lihat Network, status HTTP, bentuk JSON, dan alamat endpoint.
- **CORS:** server tujuan perlu mengizinkan origin frontend; `mode: "no-cors"` tidak membuat JSON bebas dibaca.
- **Array berubah tak sengaja:** cek operasi mutasi seperti `sort`, `push`, dan `splice`.

Latihan: pada [contoh praktik](contoh-praktik/index.html), tambahkan filter produk dengan harga di bawah Rp50.000.

Referensi: [MDN JavaScript Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide).
