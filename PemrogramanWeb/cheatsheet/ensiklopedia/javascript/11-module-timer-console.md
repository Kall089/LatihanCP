# 11 — Module, timer, dan console

[← 10 Fetch](10-fetch-async-storage.md) · [Indeks](README.md) · [Lanjut 12 →](12-web-api-singkat.md)

Module membagi kode per file. Timer menunda atau mengulang. Console membantu melihat data saat mengembangkan.

## Daftar isi

- [type=module](#typemodule)
- [export named](#export-named)
- [export default](#export-default)
- [export { } from](#export---from)
- [import named](#import-named)
- [import default](#import-default)
- [import namespace](#import-namespace)
- [import side effect](#import-side-effect)
- [alias import/export](#alias-importexport)
- [dynamic import](#dynamic-import)
- [import.meta](#importmeta)
- [defer dan async script](#defer-dan-async-script)
- [setTimeout](#settimeout)
- [clearTimeout](#cleartimeout)
- [setInterval](#setinterval)
- [clearInterval](#clearinterval)
- [debounce](#debounce)
- [throttle singkat](#throttle-singkat)
- [requestAnimationFrame](#requestanimationframe)
- [cancelAnimationFrame](#cancelanimationframe)
- [queueMicrotask](#queuemicrotask)
- [scheduler singkat](#scheduler-singkat)
- [console.log](#consolelog)
- [console.info / debug](#consoleinfo--debug)
- [console.warn](#consolewarn)
- [console.error](#consoleerror)
- [console.table](#consoletable)
- [console.dir](#consoledir)
- [console.group](#consolegroup)
- [console.time](#consoletime)
- [console.count](#consolecount)
- [console.assert](#consoleassert)
- [console.trace](#consoletrace)
- [console.clear](#consoleclear)
- [debugger](#debugger)

## type=module

**Untuk apa:** menjalankan file sebagai ES module: strict, scope sendiri, `import`/`export`.

```html
<script type="module" src="js/utama.js"></script>
```

Module otomatis `defer` (menunggu HTML). Path `import` harus relatif atau URL, biasanya berakhiran `.js`.

```js
import { formatRupiah } from "./uang.js";
```

Tanpa server, beberapa browser membatasi module dari `file://`. Pakai Live Server / `npx serve`.

**Biasanya digabungkan dengan:** memecah helper dan `defer` default.

## export named

**Untuk apa:** mengekspor nama yang diimpor dengan kurung kurawal.

```js
export const PAJAK = 11;

export function formatRupiah(nilai) {
  return new Intl.NumberFormat("id-ID", {
    style: "currency",
    currency: "IDR",
    maximumFractionDigits: 0,
  }).format(nilai);
}

export { bacaKeranjang, simpanKeranjang };
```

Satu file boleh banyak named export.

**Biasanya digabungkan dengan:** helper yang dipakai beberapa halaman.

## export default

**Untuk apa:** satu ekspor utama per file.

```js
export default function api(jalur, opsi) {
  return fetch(jalur, opsi);
}
```

Impor tanpa kurung, nama bebas. Campur default + named boleh, tetapi satu gaya per proyek lebih tenang.

**Biasanya digabungkan dengan:** satu kelas/fungsi utama file.

## export { } from

**Untuk apa:** meneruskan ekspor tanpa mengimpor ke logika lokal.

```js
export { formatRupiah } from "./uang.js";
export { default as api } from "./api.js";
```

Berguna file `index.js` sebagai pintu folder.

**Biasanya digabungkan dengan:** merapikan path impor.

## import named

**Untuk apa:** mengambil ekspor bernama. Nama harus cocok.

```js
import { formatRupiah, PAJAK } from "./uang.js";
```

Hanya yang dipakai (tree-shake di bundler). Typo nama → error saat muat.

**Biasanya digabungkan dengan:** banyak helper dari satu file util.

## import default

**Untuk apa:** mengambil default.

```js
import api from "./api.js";
import formatUang from "./uang.js";
```

**Biasanya digabungkan dengan:** file yang hanya punya satu fungsi utama.

## import namespace

**Untuk apa:** menampung semua named (dan `default`) dalam object.

```js
import * as Uang from "./uang.js";
Uang.formatRupiah(45000);
```

**Biasanya digabungkan dengan:** modul yang banyak fungsi, seperti namespace.

## import side effect

**Untuk apa:** menjalankan file demi efeknya, tanpa nama.

```js
import "./daftar-custom-element.js";
```

Pakai hemat; urutan efek sulit dilacak.

**Biasanya digabungkan dengan:** polyfill dan registrasi komponen.

## alias import/export

**Untuk apa:** mengganti nama agar tidak bentrok.

```js
import { filter as filterProduk } from "./produk.js";
export { formatRupiah as formatUang } from "./uang.js";
```

**Biasanya digabungkan dengan:** dua `filter` dari file berbeda.

## dynamic import

**Untuk apa:** memuat module saat dibutuhkan, mengembalikan Promise.

```js
tombol.addEventListener("click", async () => {
  const { bukaPeta } = await import("./peta.js");
  bukaPeta();
});
```

Default:

```js
const modul = await import("./api.js");
modul.default;
```

Berguna kode berat (grafik, peta) yang tidak selalu dipakai.

**Biasanya digabungkan dengan:** pecah bundle dan modal jarang dibuka.

## import.meta

**Untuk apa:** metadata module. `import.meta.url` adalah URL file ini.

```js
const urlAset = new URL("./gambar/logo.svg", import.meta.url);
```

Di Vite/bundler ada `import.meta.env`. Di browser polos, `url` paling berguna.

**Biasanya digabungkan dengan:** `URL` file 12 dan path aset relatif ke file JS.

## defer dan async script

**Untuk apa:** mengatur kapan skrip klasik jalan.

```html
<script src="a.js" defer></script>
<script src="b.js" async></script>
```

- klasik tanpa atribut: menghambat parsing
- `defer`: urut, setelah HTML terparse
- `async`: segera setelah unduh, urutan tidak dijamin
- `type="module"`: seperti defer

Jangan mengandalkan `async` jika file saling butuh urutan.

**Biasanya digabungkan dengan:** skrip analitik (`async`) dan aplikasi (`module`).

## setTimeout

**Untuk apa:** menjalankan fungsi sekali setelah jeda milidetik.

```js
const id = setTimeout(() => {
  pesan.hidden = true;
}, 3000);
```

Jeda `0` artinya “setelah tugas sync dan microtask”, bukan tepat 0 ms.

Argumen tambahan diteruskan ke callback (kurang populer daripada closure).

Mengembalikan id (angka di browser) untuk `clearTimeout`.

**Biasanya digabungkan dengan:** toast, debounce, dan timeout fetch.

## clearTimeout

**Untuk apa:** membatalkan timeout yang belum jalan.

```js
clearTimeout(id);
```

Aman dipanggil pada id yang sudah jalan atau `undefined` (tidak ada efek berarti).

**Biasanya digabungkan dengan:** debounce dan unmount.

## setInterval

**Untuk apa:** mengulang fungsi tiap jeda.

```js
const id = setInterval(() => {
  detak += 1;
  label.textContent = String(detak);
}, 1000);
```

Jika kerja lebih lama dari jeda, panggilan bisa menumpuk. Pertimbangkan `setTimeout` rekursif.

Tidak tepat untuk animasi visual; pakai `requestAnimationFrame`.

**Biasanya digabungkan dengan:** countdown dan polling kasar (lebih baik server push / refetch sadar).

## clearInterval

**Untuk apa:** menghentikan interval.

```js
clearInterval(id);
```

Wajib saat selesai, jika tidak timer jalan terus (boros, bug state).

**Biasanya digabungkan dengan:** `finally`, tutup halaman, dan kondisi selesai.

## debounce

**Untuk apa:** menunda kerja sampai event “tenang”.

```js
function debounce(fn, jeda = 300) {
  let id;
  return (...args) => {
    clearTimeout(id);
    id = setTimeout(() => {
      fn(...args);
    }, jeda);
  };
}

const onCari = debounce((teks) => {
  terapkanCari(teks);
}, 300);

cari.addEventListener("input", () => onCari(cari.value));
```

Cocok search dan resize.

**Biasanya digabungkan dengan:** `input`, `fetch`, `filter`.

## throttle singkat

**Untuk apa:** paling-paling sekali per jangka waktu.

```js
function throttle(fn, jeda = 200) {
  let terakhir = 0;
  return (...args) => {
    const sekarang = Date.now();
    if (sekarang - terakhir < jeda) {
      return;
    }
    terakhir = sekarang;
    fn(...args);
  };
}
```

Cocok scroll yang hanya perlu update berkala. Untuk visibilitas elemen, observer lebih baik.

**Biasanya digabungkan dengan:** `scroll` passive dan indikator.

## requestAnimationFrame

**Untuk apa:** menjalankan fungsi sebelum frame lukis berikutnya (~60x/detik).

```js
function loop(waktu) {
  // pakai waktu untuk animasi
  id = requestAnimationFrame(loop);
}
let id = requestAnimationFrame(loop);
```

Berhenti saat tab tersembunyi (hemat). Jangan `setInterval(16)` untuk animasi.

**Biasanya digabungkan dengan:** kanvas, progress, dan baca layout.

## cancelAnimationFrame

**Untuk apa:** membatalkan frame yang diminta.

```js
cancelAnimationFrame(id);
```

**Biasanya digabungkan dengan:** berhenti animasi dan tutup komponen.

## queueMicrotask

**Untuk apa:** menjalankan fungsi segera setelah kode sync, sebelum timer.

```js
queueMicrotask(() => {
  console.log("microtask");
});
```

Mirip `Promise.resolve().then(...)`. Pakai jika kamu perlu update setelah DOM mutation sinkron dalam satu tick.

**Biasanya digabungkan dengan:** urutan state yang sangat ketat. Jarang di toko sederhana.

## scheduler singkat

**Untuk apa:** API `scheduler.postTask` / `requestIdleCallback` untuk kerja tidak mendesak.

```js
if (typeof requestIdleCallback === "function") {
  requestIdleCallback(() => {
    prefetch();
  });
} else {
  setTimeout(prefetch, 200);
}
```

Tidak tersedia merata. Selalu sediakan cadangan `setTimeout`.

**Biasanya digabungkan dengan:** prefetch. Bukan kebutuhan tugas dasar.

## console.log

**Untuk apa:** mencetak nilai ke Console.

```js
console.log("siap");
console.log("produk", produk);
console.log({ stok, harga });
```

Bisa banyak argumen. Object yang dilog bisa “hidup” (nilai kemudian) di beberapa browser — salin field primitif jika perlu jejak waktu itu.

Jangan tinggalkan log rahasia di produksi jika data sensitif.

**Biasanya digabungkan dengan:** debug `fetch`, event, dan `JSON.stringify` rapi.

## console.info / debug

**Untuk apa:** log dengan tingkat berbeda. Tampilan tergantung filter Console.

```js
console.info("memuat daftar");
console.debug("payload", data);
```

`debug` kadang tersembunyi jika level log tidak “Verbose”.

**Biasanya digabungkan dengan:** jejak pengembangan bertingkat.

## console.warn

**Untuk apa:** peringatan, biasanya kuning.

```js
console.warn("Format tanggal tidak lengkap, pakai hari ini");
```

**Biasanya digabungkan dengan:** fallback dan API deprecated.

## console.error

**Untuk apa:** menampilkan error, sering beserta stack.

```js
console.error("Gagal memuat", error);
```

Tidak sama dengan `throw`; halaman tetap jalan.

**Biasanya digabungkan dengan:** `catch` dan laporan.

## console.table

**Untuk apa:** menampilkan array object sebagai tabel.

```js
console.table(produk, ["nama", "harga"]);
```

Nyaman membandingkan field.

**Biasanya digabungkan dengan:** array hasil `map`/`filter`.

## console.dir

**Untuk apa:** menelusuri object/DOM sebagai properti, bukan markup.

```js
console.dir(document.body);
console.dir(produk);
```

**Biasanya digabungkan dengan:** inspeksi elemen sebagai JS object.

## console.group

**Untuk apa:** mengelompokkan log.

```js
console.group("checkout");
console.log("item", 2);
console.log("total", 90000);
console.groupEnd();

console.groupCollapsed("detail");
console.log("panjang");
console.groupEnd();
```

**Biasanya digabungkan dengan:** alur berlangkah.

## console.time

**Untuk apa:** mengukur durasi.

```js
console.time("filter");
const hasil = produk.filter((p) => p.harga < 20000);
console.timeEnd("filter");
```

Label harus sama. `console.timeLog("filter")` mencetak antara.

**Biasanya digabungkan dengan:** cari bottleneck. Bukan patokan presisi tinggi.

## console.count

**Untuk apa:** menghitung berapa kali label dipanggil.

```js
console.count("render");
console.countReset("render");
```

**Biasanya digabungkan dengan:** mengecek render/dobel listener.

## console.assert

**Untuk apa:** log error jika syarat false.

```js
console.assert(Array.isArray(data), "data harus array");
```

Tidak melempar (di browser). Untuk kontrak keras, `throw`.

**Biasanya digabungkan dengan:** jaga asumsi saat mengembangkan.

## console.trace

**Untuk apa:** mencetak jejak pemanggilan.

```js
function dalam() {
  console.trace("siapa yang memanggil");
}
```

**Biasanya digabungkan dengan:** mencari sumber pemanggilan ganda.

## console.clear

**Untuk apa:** membersihkan Console.

```js
console.clear();
```

Pengaturan browser bisa mencegah clear. Jangan diandalkan di produksi.

**Biasanya digabungkan dengan:** sesi debug manual.

## debugger

**Untuk apa:** jeda jika DevTools terbuka.

```js
function total(keranjang) {
  debugger;
  return keranjang.reduce((s, i) => s + i.harga, 0);
}
```

Hapus sebelum kumpul tugas jika tidak sengaja. Breakpoint di Sources lebih rapi.

**Biasanya digabungkan dengan:** panel Sources dan watch variabel.

## pola module toko

**Untuk apa:** memisahkan tanggung jawab.

```text
js/
  utama.js
  api.js
  uang.js
  keranjang.js
  render.js
```

`utama.js` memasang event. Yang lain mengekspor fungsi murni atau DOM terbatas.

```js
import { formatRupiah } from "./uang.js";
import { baca, simpan, tambah } from "./keranjang.js";
import { renderDaftar } from "./render.js";
```

**Biasanya digabungkan dengan:** file 03 fungsi murni dan file 08 render.

## Kesalahan module/timer/console yang sering

- `import` tanpa `.js` di browser polos.
- Mencampur `require` CommonJS dengan ES module di skrip browser.
- Interval tidak di-clear.
- Debounce membuat `this`/event basi (baca `input.value` saat timer jalan, bukan event lama).
- Mengira `console.log` menggantikan UI pengguna.
- Dynamic import path harus dapat dianalisis / URL valid.

**Biasanya digabungkan dengan:** file 13.
