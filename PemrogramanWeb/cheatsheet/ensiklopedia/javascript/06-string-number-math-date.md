# 06 — String, Number, Math, dan Date

[← 05 Array](05-array-method-lengkap.md) · [Indeks](README.md) · [Lanjut 07 →](07-json-set-map-promise.md)

Teks, angka, dan tanggal punya method sendiri. Entri di bawah satu per satu.

## Daftar isi

### String

- [length string](#length-string)
- [akses karakter](#akses-karakter)
- [at (string)](#atstring)
- [charAt](#charat)
- [charCodeAt](#charcodeat)
- [codePointAt](#codepointat)
- [slice (string)](#slicestring)
- [substring](#substring)
- [substr](#substr)
- [indexOf (string)](#indexofstring)
- [lastIndexOf (string)](#lastindexofstring)
- [includes (string)](#includesstring)
- [startsWith](#startswith)
- [endsWith](#endswith)
- [toLowerCase / toUpperCase](#tolowercase--touppercase)
- [trim / trimStart / trimEnd](#trim--trimstart--trimend)
- [padStart / padEnd](#padstart--padend)
- [repeat](#repeat)
- [replace](#replace)
- [replaceAll](#replaceall)
- [split](#split)
- [concat (string)](#concatstring)
- [match](#match)
- [matchAll](#matchall)
- [search](#search)
- [normalize](#normalize)
- [localeCompare](#localecompare)
- [isWellFormed / toWellFormed](#iswellformed--towellformed)
- [String.fromCharCode](#stringfromcharcode)
- [String.fromCodePoint](#stringfromcodepoint)
- [String.raw](#stringraw)

### Number

- [Number()](#number-fungsi)
- [parseInt](#parseint)
- [parseFloat](#parsefloat)
- [toFixed](#tofixed)
- [toPrecision](#toprecision)
- [toExponential](#toexponential)
- [toString (number)](#tostring-number)
- [toLocaleString (number)](#tolocalestring-number)
- [Number.isNaN](#numberisnan)
- [Number.isFinite](#numberisfinite)
- [Number.isInteger](#numberisinteger)
- [Number.isSafeInteger](#numberissafeinteger)
- [konstanta Number](#konstanta-number)

### Math

- [Math.abs](#mathabs)
- [Math.sign](#mathsign)
- [Math.ceil](#mathceil)
- [Math.floor](#mathfloor)
- [Math.round](#mathround)
- [Math.trunc](#mathtrunc)
- [Math.min / Math.max](#mathmin--mathmax)
- [Math.random](#mathrandom)
- [Math.pow / **](#mathpow--)
- [Math.sqrt / Math.cbrt](#mathsqrt--mathcbrt)
- [Math.hypot](#mathhypot)
- [Math.PI dan konstanta](#mathpi-dan-konstanta)
- [trigometri singkat](#trigometri-singkat)
- [Math.log / Math.exp](#mathlog--mathexp)
- [Math.clz32 / Math.imul / Math.fround](#mathclz32--mathimul--mathfround)

### Date dan Intl

- [new Date](#new-date)
- [Date.now](#datenow)
- [Date.parse](#dateparse)
- [getFullYear / getMonth / getDate](#getfullyear--getmonth--getdate)
- [getDay](#getday)
- [getHours dan kawan](#gethours-dan-kawan)
- [getTime](#gettime)
- [versi UTC](#versi-utc)
- [setFullYear dan setter](#setfullyear-dan-setter)
- [toISOString](#toisostring)
- [toJSON](#tojson)
- [toLocaleDateString](#tolocaledatestring)
- [toLocaleTimeString](#tolocaletimestring)
- [toLocaleString (date)](#tolocalestring-date)
- [Intl.DateTimeFormat](#intldatetimeformat)
- [Intl.NumberFormat](#intlnumberformat)
- [Intl.RelativeTimeFormat](#intlrelativetimeformat)

## length string

**Untuk apa:** jumlah unit UTF-16, biasanya sama dengan jumlah karakter Latin.

```js
"Buku".length; // 4
"".length; // 0
```

Beberapa emoji memakai dua unit, jadi `length` bisa 2 untuk satu gambar. Untuk iterasi karakter, `for...of` atau `Array.from(teks)` lebih aman.

**Biasanya digabungkan dengan:** validasi panjang input dan `if (teks.length === 0)`.

## akses karakter

**Untuk apa:** mengambil huruf di indeks.

```js
const nama = "Buku";
nama[0]; // "B"
nama[9]; // undefined
```

String tidak bisa diubah:

```js
// nama[0] = "b"; tidak mengubah
```

Buat string baru dengan `slice` + gabung.

**Biasanya digabungkan dengan:** inisial nama dan cek huruf pertama.

## at (string)

**Untuk apa:** karakter di indeks, termasuk negatif.

```js
"Buku".at(-1); // "u"
"Buku".at(0); // "B"
```

**Biasanya digabungkan dengan:** cek tanda akhir, ekstensi file, dan sufiks.

## charAt

**Untuk apa:** karakter di indeks; jika di luar jangkauan mengembalikan `""`, bukan `undefined`.

```js
"Buku".charAt(0); // "B"
"Buku".charAt(9); // ""
```

Kode baru sering memakai `at` atau `[i]`.

**Biasanya digabungkan dengan:** kode lama. Untuk indeks negatif, `at`.

## charCodeAt

**Untuk apa:** kode UTF-16 di indeks.

```js
"A".charCodeAt(0); // 65
```

Untuk emoji/astral, bisa hanya setengah pasangan. `codePointAt` lebih lengkap.

**Biasanya digabungkan dengan:** tes huruf besar/kecil manual. Lebih mudah `toLowerCase`.

## codePointAt

**Untuk apa:** kode Unicode penuh di indeks.

```js
"A".codePointAt(0); // 65
```

**Biasanya digabungkan dengan:** validasi rentang karakter khusus.

## slice (string)

**Untuk apa:** potongan `[mulai, akhir)`, mendukung negatif. Tidak mengubah asli.

```js
const judul = "Buku Tulis";
judul.slice(0, 4); // "Buku"
judul.slice(5); // "Tulis"
judul.slice(-5); // "Tulis"
judul.slice(0, -1); // "Buku Tuli"
```

Ini method potong yang paling sering dipakai.

**Biasanya digabungkan dengan:** cuplikan kartu, `trim`, dan ekstensi file.

## substring

**Untuk apa:** potongan, tetapi indeks negatif dianggap 0 dan argumen bisa tertukar otomatis.

```js
"Buku".substring(1, 3); // "uk"
"Buku".substring(3, 1); // "uk"  tertukar
```

Kurang prediktabel daripada `slice`. Lebih baik `slice`.

**Biasanya digabungkan dengan:** kode warisan.

## substr

**Untuk apa:** mulai + panjang. Sudah usang.

```js
"Buku".substr(1, 2); // "uk"
```

Jangan dipakai di kode baru. Ganti `slice`.

**Biasanya digabungkan dengan:** file lama yang belum diubah.

## indexOf (string)

**Untuk apa:** posisi substring pertama, atau `-1`.

```js
"Buku Tulis".indexOf("Tulis"); // 5
"Buku Tulis".indexOf("x"); // -1
"Buku Tulis".indexOf("u", 2); // 3
```

Peka huruf besar/kecil.

**Biasanya digabungkan dengan:** `slice` setelah posisi, dan cek lama `!== -1`.

## lastIndexOf (string)

**Untuk apa:** posisi substring terakhir.

```js
"a.b.txt".lastIndexOf("."); // 3
```

Ekstensi file:

```js
const nama = "foto.akhir.png";
const ext = nama.slice(nama.lastIndexOf(".") + 1);
```

**Biasanya digabungkan dengan:** `slice` dan nama file.

## includes (string)

**Untuk apa:** apakah teks mengandung substring.

```js
"Buku Tulis".includes("Tulis"); // true
"Buku Tulis".includes("tulis"); // false
```

Pencarian longgar:

```js
judul.toLowerCase().includes(q.toLowerCase());
```

Argumen kedua: indeks mulai.

**Biasanya digabungkan dengan:** `filter` produk dan `toLowerCase`.

## startsWith

**Untuk apa:** apakah diawali substring.

```js
"https://contoh.test".startsWith("https://");
"ID-17".startsWith("ID-");
```

**Biasanya digabungkan dengan:** cek protokol, prefix kode, dan routing kasar.

## endsWith

**Untuk apa:** apakah diakhiri substring.

```js
"foto.png".endsWith(".png");
"halaman.js".endsWith(".js");
```

**Biasanya digabungkan dengan:** filter jenis file dan validasi ekstensi.

## toLowerCase / toUpperCase

**Untuk apa:** menyeragamkan huruf untuk banding atau tampilan.

```js
"Buku".toLowerCase(); // "buku"
"buku".toUpperCase(); // "BUKU"
```

Tidak mengubah asli. Ada juga `toLocaleLowerCase("id")` untuk aturan lokal khusus.

**Biasanya digabungkan dengan:** `includes`, `sort`, dan normalisasi email.

## trim / trimStart / trimEnd

**Untuk apa:** membuang spasi di ujung.

```js
"  Buku  ".trim(); // "Buku"
"  Buku".trimStart();
"Buku  ".trimEnd();
```

Penting sebelum membandingkan input form. `trim` tidak menghapus spasi di tengah.

```js
const q = input.value.trim();
if (q === "") {
  console.log("Kosong");
}
```

**Biasanya digabungkan dengan:** form, `includes`, dan validasi.

## padStart / padEnd

**Untuk apa:** menambah karakter sampai panjang tertentu.

```js
String(7).padStart(2, "0"); // "07"
"42".padStart(5, "0"); // "00042"
"Rp".padEnd(6, "."); // "Rp...."
```

Argumen: panjang target, pengisi (default spasi).

**Biasanya digabungkan dengan:** jam `09:05`, kode invoice, dan nomor urut.

## repeat

**Untuk apa:** mengulang teks.

```js
"*".repeat(3); // "***"
"ha".repeat(2); // "haha"
```

Jumlah negatif atau tak hingga → error. `0` → `""`.

**Biasanya digabungkan dengan:** pola sederhana dan padding manual.

## replace

**Untuk apa:** mengganti kecocokan pertama (string) atau sesuai regex.

```js
"Buku Tulis Buku".replace("Buku", "Novel");
// "Novel Tulis Buku"
```

Semua kemunculan: regex global atau `replaceAll`.

```js
"a-a-a".replace(/-/g, "/"); // "a/a/a"
```

Callback:

```js
"harga 45000".replace(/\d+/, (angka) => `Rp${angka}`);
```

String pencarian bukan regex: hanya pertama, dan karakter khusus literal.

**Biasanya digabungkan dengan:** bersihkan input, format, dan regex sederhana.

## replaceAll

**Untuk apa:** mengganti semua kemunculan substring atau regex global.

```js
"Buku Buku".replaceAll("Buku", "Novel");
"a.a.a".replaceAll(".", "-");
```

Jika argumen regex, wajib flag `g`, kalau tidak error.

**Biasanya digabungkan dengan:** normalisasi pemisah dan sensor kata.

## split

**Untuk apa:** memecah string menjadi array.

```js
"Buku,Pensil,Tas".split(","); // ["Buku", "Pensil", "Tas"]
"2026-09-22".split("-"); // ["2026", "09", "22"]
"halo".split(""); // ["h", "a", "l", "o"]
```

Batas jumlah:

```js
"a-b-c-d".split("-", 2); // ["a", "b"]
```

Regex:

```js
"satu  dua\ttiga".split(/\s+/);
```

Sering dilanjutkan `map(s => s.trim()).filter(Boolean)`.

**Biasanya digabungkan dengan:** `join`, tag, CSV sederhana, dan `trim`.

## concat (string)

**Untuk apa:** menempelkan string.

```js
"Toko".concat(" ", "Belajar");
```

Template literal atau `+` lebih umum.

```js
`Toko ${nama}`;
```

**Biasanya digabungkan dengan:** kode yang ingin method chaining. Di latihan, template cukup.

## match

**Untuk apa:** hasil regex pada string.

```js
"Kode ID-17".match(/\d+/); // ["17", index, input, ...]
"abc".match(/\d+/); // null
```

Dengan flag `g`, hasil array semua potongan, tanpa kelompok rinci.

```js
"a1 b23".match(/\d+/g); // ["1", "23"]
```

Jika tidak ketemu, `null` — jangan langsung `.length`.

**Biasanya digabungkan dengan:** `?.`, validasi pola, dan ekstrak angka.

## matchAll

**Untuk apa:** iterator semua kecocokan regex global, termasuk kelompok.

```js
const teks = "id=1 id=2";
const semua = [...teks.matchAll(/id=(\d+)/g)];
console.log(semua.map((m) => m[1])); // ["1", "2"]
```

Regex harus `g`. Lebih rapi daripada loop `exec`.

**Biasanya digabungkan dengan:** parsing pola berulang di teks.

## search

**Untuk apa:** indeks kecocokan regex, atau `-1`.

```js
"Buku 2026".search(/\d+/); // 5
```

Tidak mengembalikan teks, hanya posisi. Untuk teks, `match`.

**Biasanya digabungkan dengan:** `slice` dari posisi pola.

## normalize

**Untuk apa:** menyeragamkan bentuk Unicode (NFC/NFD).

```js
const a = "é";
const b = "e\u0301";
a === b; // sering false
a.normalize("NFC") === b.normalize("NFC");
```

Penting jika membandingkan nama yang diketik berbeda tetapi terlihat sama.

**Biasanya digabungkan dengan:** pencarian nama dan data internasional.

## localeCompare

**Untuk apa:** membandingkan urutan kamus menurut locale.

```js
"Buku".localeCompare("Pensil", "id"); // negatif jika sebelum
["Tas", "Buku"].sort((a, b) => a.localeCompare(b, "id"));
```

Opsi: `{ sensitivity: "base" }` mengabaikan huruf besar/aksen (tergantung locale).

**Biasanya digabungkan dengan:** `sort` / `toSorted` nama produk.

## isWellFormed / toWellFormed

**Untuk apa:** cek dan perbaiki string yang berisi pasangan surrogate rusak.

```js
"hai".isWellFormed(); // true
```

Jarang di tugas toko. Berguna jika merakit string dari kode mentah.

**Biasanya digabungkan dengan:** data biner/teks yang tidak terpercaya.

## String.fromCharCode

**Untuk apa:** membuat string dari kode UTF-16.

```js
String.fromCharCode(65, 66); // "AB"
```

**Biasanya digabungkan dengan:** `charCodeAt`. Untuk kode di atas 0xFFFF, `fromCodePoint`.

## String.fromCodePoint

**Untuk apa:** membuat string dari kode Unicode penuh.

```js
String.fromCodePoint(65, 0x1f4da);
```

**Biasanya digabungkan dengan:** `codePointAt`.

## String.raw

**Untuk apa:** template literal tanpa mengolah escape `\n` dan sejenis.

```js
String.raw`baris\nbaru`; // berisi \ dan n, bukan pindah baris
```

Berguna untuk pola regex atau path.

**Biasanya digabungkan dengan:** regex panjang. Jarang di UI toko.

## Number (fungsi)

**Untuk apa:** mengonversi ke number.

```js
Number("45"); // 45
Number("45.5"); // 45.5
Number(""); // 0
Number("45px"); // NaN
Number(true); // 1
Number(null); // 0
```

Lihat juga [file 01](01-tipe-variabel-operator.md#konversi-ke-number).

**Biasanya digabungkan dengan:** `input.value`, `Number.isFinite`, dan form.

## parseInt

**Untuk apa:** membaca bilangan bulat di awal teks.

```js
parseInt("45px", 10); // 45
parseInt("08", 10); // 8
parseInt("abc", 10); // NaN
parseInt("10.9", 10); // 10
```

Argumen kedua (radix) wajib ditulis, biasanya `10`. Tanpa itu, teks berawalan `0x` bisa terbaca heksadesimal.

`Number.parseInt` sama, menempel di `Number`.

**Biasanya digabungkan dengan:** `"12 item"`, CSS `"16px"`, dan radix 10.

## parseFloat

**Untuk apa:** membaca desimal di awal teks.

```js
parseFloat("12.5cm"); // 12.5
parseFloat("12.5.7"); // 12.5
```

**Biasanya digabungkan dengan:** ukuran, rating, dan input desimal.

## toFixed

**Untuk apa:** string dengan jumlah desimal tetap, membulatkan.

```js
(3.14159).toFixed(2); // "3.14"
(45000).toFixed(0); // "45000"
(1.005).toFixed(2); // hati-hati, desimal biner
```

Hasil **string**. Untuk hitung lanjut, `Number(...)` lagi. Untuk uang tampilan, `Intl.NumberFormat` lebih tepat.

Digit 0–100. Di luar itu `RangeError`.

**Biasanya digabungkan dengan:** tampilan, bukan penyimpanan uang jangka panjang.

## toPrecision

**Untuk apa:** string dengan jumlah digit signifikan.

```js
(1234.5).toPrecision(3); // "1.23e+3"
(1.23).toPrecision(4); // "1.230"
```

Jarang untuk UI toko. `toFixed` atau `Intl` lebih terprediksi.

**Biasanya digabungkan dengan:** sains/statistik singkat.

## toExponential

**Untuk apa:** notasi ilmiah.

```js
(45000).toExponential(2); // "4.50e+4"
```

**Biasanya digabungkan dengan:** angka sangat besar/kecil. Bukan harga rupiah.

## toString (number)

**Untuk apa:** angka menjadi teks, boleh basis lain.

```js
(255).toString(); // "255"
(255).toString(16); // "ff"
(6).toString(2); // "110"
```

**Biasanya digabungkan dengan:** `padStart`, kode warna, dan `localStorage`.

## toLocaleString (number)

**Untuk apa:** format angka menurut locale, versi singkat.

```js
(1500000).toLocaleString("id-ID"); // "1.500.000"
```

Untuk kontrol penuh (mata uang), pakai `Intl.NumberFormat`.

**Biasanya digabungkan dengan:** tabel angka dan cuplikan cepat.

## Number.isNaN

**Untuk apa:** `true` hanya jika nilainya `NaN`.

```js
Number.isNaN(NaN); // true
Number.isNaN("abc"); // false
```

**Biasanya digabungkan dengan:** hasil `Number` / `parseInt`.

## Number.isFinite

**Untuk apa:** number biasa, bukan `NaN`/`Infinity`.

```js
Number.isFinite(10); // true
Number.isFinite(Infinity); // false
Number.isFinite("10"); // false
```

**Biasanya digabungkan dengan:** validasi harga setelah `Number(teks)`.

## Number.isInteger

**Untuk apa:** apakah number bilangan bulat.

```js
Number.isInteger(5); // true
Number.isInteger(5.1); // false
Number.isInteger("5"); // false
```

**Biasanya digabungkan dengan:** jumlah barang dan nomor halaman.

## Number.isSafeInteger

**Untuk apa:** integer dalam rentang aman presisi (`-(2^53-1)` sampai `2^53-1`).

```js
Number.isSafeInteger(9007199254740991); // true
Number.isSafeInteger(9007199254740992); // false
```

ID sangat besar dari API kadang lebih aman disimpan sebagai string.

**Biasanya digabungkan dengan:** ID numerik besar dan `BigInt`.

## konstanta Number

**Untuk apa:** batas dan nilai khusus.

```js
Number.MAX_SAFE_INTEGER;
Number.MIN_SAFE_INTEGER;
Number.MAX_VALUE;
Number.MIN_VALUE; // positif terkecil yang mendekati 0
Number.EPSILON; // selisih presisi
Number.NaN;
Number.POSITIVE_INFINITY;
Number.NEGATIVE_INFINITY;
```

Banding desimal:

```js
function hampirSama(a, b) {
  return Math.abs(a - b) < Number.EPSILON * 16;
}
```

**Biasanya digabungkan dengan:** `Math.abs` dan tes hitung.

## Math.abs

**Untuk apa:** nilai mutlak (tanpa tanda).

```js
Math.abs(-8); // 8
Math.abs(8); // 8
```

**Biasanya digabungkan dengan:** selisih harga dan jarak.

## Math.sign

**Untuk apa:** `-1`, `0`, atau `1` menurut tanda.

```js
Math.sign(-10); // -1
Math.sign(0); // 0
Math.sign(4); // 1
```

**Biasanya digabungkan dengan:** arah urutan dan tren naik/turun.

## Math.ceil

**Untuk apa:** ke atas menuju +∞.

```js
Math.ceil(4.1); // 5
Math.ceil(-4.1); // -4
```

**Biasanya digabungkan dengan:** jumlah halaman: `Math.ceil(total / ukuran)`.

## Math.floor

**Untuk apa:** ke bawah menuju −∞.

```js
Math.floor(4.9); // 4
Math.floor(-4.1); // -5
```

**Biasanya digabungkan dengan:** indeks, pecahan paket, dan pembulatan ke bawah positif.

## Math.round

**Untuk apa:** ke bilangan terdekat; 0.5 menjauh dari 0 untuk positif.

```js
Math.round(4.4); // 4
Math.round(4.5); // 5
Math.round(-1.5); // -1
```

**Biasanya digabungkan dengan:** harga setelah pajak dan persentase.

## Math.trunc

**Untuk apa:** membuang desimal, menuju 0.

```js
Math.trunc(4.9); // 4
Math.trunc(-4.9); // -4
```

Beda dengan `floor` pada negatif.

**Biasanya digabungkan dengan:** potong desimal tanpa membulatkan.

## Math.min / Math.max

**Untuk apa:** nilai terkecil / terbesar dari argumen.

```js
Math.min(4, 9, 1); // 1
Math.max(4, 9, 1); // 9
Math.max(...produk.map((p) => p.harga));
```

Tanpa argumen: `Infinity` / `-Infinity`. Array kosong + spread hati-hati.

Batas nilai:

```js
const jumlah = Math.min(99, Math.max(1, mentah));
```

**Biasanya digabungkan dengan:** clamp, spread array, dan statistik.

## Math.random

**Untuk apa:** angka `0 <= x < 1`.

```js
Math.random();
```

Bilangan bulat `min..max` inklusif:

```js
function acakInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}
```

Pilih item:

```js
const item = daftar[Math.floor(Math.random() * daftar.length)];
```

Bukan untuk keamanan (token, otp). Pakai `crypto` di file 12.

**Biasanya digabungkan dengan:** demo, acak urutan sederhana, dan latihan.

## Math.pow / **

**Untuk apa:** pangkat.

```js
Math.pow(2, 3); // 8
2 ** 3; // 8
```

`**` lebih singkat. `Math.pow` berguna sebagai fungsi yang bisa dikirim.

**Biasanya digabungkan dengan:** rumus bunga sederhana dan geometri.

## Math.sqrt / Math.cbrt

**Untuk apa:** akar kuadrat / akar pangkat tiga.

```js
Math.sqrt(9); // 3
Math.sqrt(-1); // NaN
Math.cbrt(8); // 2
```

**Biasanya digabungkan dengan:** jarak (`hypot` lebih langsung untuk 2D).

## Math.hypot

**Untuk apa:** akar dari jumlah kuadrat; jarak Euclidean.

```js
Math.hypot(3, 4); // 5
```

**Biasanya digabungkan dengan:** drag pointer dan geometri kanvas.

## Math.PI dan konstanta

**Untuk apa:** π dan konstanta matematika.

```js
Math.PI;
Math.E;
Math.LN2;
Math.LN10;
Math.LOG2E;
Math.LOG10E;
Math.SQRT2;
Math.SQRT1_2;
```

Lingkaran:

```js
const keliling = 2 * Math.PI * r;
```

**Biasanya digabungkan dengan:** kanvas, derajat↔radian.

## trigometri singkat

**Untuk apa:** sinus/cosinus dalam **radian**.

```js
Math.sin(Math.PI / 2); // 1
Math.cos(0); // 1
Math.tan(Math.PI / 4);
Math.asin(1);
Math.acos(1);
Math.atan(1);
Math.atan2(y, x); // sudut dari koordinat
```

Derajat ke radian: `derajat * Math.PI / 180`.

**Biasanya digabungkan dengan:** animasi, kanvas, bukan toko.

## Math.log / Math.exp

**Untuk apa:** logaritma natural dan e^x.

```js
Math.log(Math.E); // 1
Math.exp(1); // e
Math.log10(100); // 2
Math.log2(8); // 3
```

**Biasanya digabungkan dengan:** skala, bukan harga harian.

## Math.clz32 / Math.imul / Math.fround

**Untuk apa:** operasi 32-bit: hitung nol di kiri, kali integer, float 32-bit.

```js
Math.clz32(1);
Math.imul(2, 4);
Math.fround(1.337);
```

Jarang di web toko. Ada juga `Math.sin` hyperbolic: `sinh`, `cosh`, `tanh`.

**Biasanya digabungkan dengan:** bit-twiddling. Lewati jika tidak butuh.

## new Date

**Untuk apa:** membuat titik waktu.

```js
new Date(); // sekarang
new Date("2026-09-22T00:00:00+07:00");
new Date(2026, 8, 22, 10, 30, 0); // bulan 0-11: 8 = September
new Date(0); // epoch UTC
```

Tanpa `new`, `Date()` mengembalikan string, bukan object Date.

ISO tanggal-only `"2026-09-22"` diinterpretasikan sebagai UTC, bisa mundur satu hari di zona WIB. Lebih aman sertakan waktu dan offset, atau pakai `new Date(y, m, d)`.

Invalid:

```js
const d = new Date("bukan-tanggal");
Number.isNaN(d.getTime()); // true
```

**Biasanya digabungkan dengan:** `Intl`, form tanggal, dan timestamp API.

## Date.now

**Untuk apa:** milidetik sejak 1 Jan 1970 UTC, angka.

```js
const t0 = Date.now();
// ...kerja
const durasi = Date.now() - t0;
```

Sama ide dengan `+new Date()` tetapi lebih jelas.

**Biasanya digabungkan dengan:** ukur durasi, id sementara, dan cache kadaluarsa.

## Date.parse

**Untuk apa:** parse string ke timestamp. Perilaku string non-ISO tidak konsisten antar browser.

```js
Date.parse("2026-09-22T10:00:00+07:00");
```

Lebih aman format ISO dengan offset. Jangan mengandalkan `"22/09/2026"`.

**Biasanya digabungkan dengan:** `new Date(teks)` dan validasi `NaN`.

## getFullYear / getMonth / getDate

**Untuk apa:** bagian tanggal di zona lokal.

```js
const d = new Date(2026, 8, 22);
d.getFullYear(); // 2026
d.getMonth(); // 8  ← September, 0 = Januari
d.getDate(); // 22  hari dalam bulan
```

`getYear()` usang (dua digit / offset). Jangan dipakai.

Format `YYYY-MM-DD` lokal:

```js
const yyyy = d.getFullYear();
const mm = String(d.getMonth() + 1).padStart(2, "0");
const dd = String(d.getDate()).padStart(2, "0");
const isoLokal = `${yyyy}-${mm}-${dd}`;
```

**Biasanya digabungkan dengan:** `padStart` dan input `type="date"`.

## getDay

**Untuk apa:** hari dalam minggu, 0 = Minggu … 6 = Sabtu.

```js
new Date(2026, 8, 22).getDay();
```

Bukan hari dalam bulan (`getDate`).

**Biasanya digabungkan dengan:** label hari dan cek akhir pekan.

## getHours dan kawan

**Untuk apa:** jam lokal.

```js
d.getHours(); // 0-23
d.getMinutes();
d.getSeconds();
d.getMilliseconds();
```

**Biasanya digabungkan dengan:** `padStart` untuk `10:05`.

## getTime

**Untuk apa:** timestamp milidetik, atau `NaN` jika invalid.

```js
d.getTime();
d.valueOf(); // sama
```

Banding dan urut:

```js
daftar.toSorted((a, b) => a.tanggal.getTime() - b.tanggal.getTime());
```

**Biasanya digabungkan dengan:** `sort`, selisih hari, dan `Date.now`.

## versi UTC

**Untuk apa:** getter/setter tanpa zona lokal.

```js
d.getUTCFullYear();
d.getUTCMonth();
d.getUTCDate();
d.getUTCHours();
```

Pakai jika data server UTC dan kamu tidak ingin bergeser.

**Biasanya digabungkan dengan:** `toISOString` dan API.

## setFullYear dan setter

**Untuk apa:** mengubah Date di tempat, mengembalikan timestamp baru.

```js
const d = new Date();
d.setFullYear(2026);
d.setMonth(8); // September
d.setDate(22);
d.setHours(10, 30, 0, 0);
```

Ada `setUTC*`. Overflow tanggal digeser (31 + 1 hari → bulan berikutnya).

Jika tidak ingin mutasi, buat `new Date(d.getTime())` lalu set salinan.

**Biasanya digabungkan dengan:** kalender dan batas rentang.

## toISOString

**Untuk apa:** string UTC `YYYY-MM-DDTHH:mm:ss.sssZ`.

```js
new Date().toISOString();
```

Invalid Date → `RangeError`. Cek `getTime()` dulu.

Cocok dikirim ke API. Bukan tampilan pengguna Indonesia.

**Biasanya digabungkan dengan:** `fetch` JSON dan `localStorage`.

## toJSON

**Untuk apa:** dipakai `JSON.stringify` pada Date; isinya seperti `toISOString`.

```js
JSON.stringify({ dibuat: new Date() });
```

Saat `parse`, itu string, bukan Date. Ubah manual jika perlu.

**Biasanya digabungkan dengan:** file 07 JSON.

## toLocaleDateString

**Untuk apa:** tanggal terformat untuk manusia.

```js
new Date().toLocaleDateString("id-ID", {
  day: "numeric",
  month: "long",
  year: "numeric",
});
```

**Biasanya digabungkan dengan:** kartu artikel dan daftar pesanan.

## toLocaleTimeString

**Untuk apa:** jam terformat.

```js
new Date().toLocaleTimeString("id-ID", {
  hour: "2-digit",
  minute: "2-digit",
});
```

**Biasanya digabungkan dengan:** stempel waktu chat.

## toLocaleString (date)

**Untuk apa:** tanggal + waktu.

```js
new Date().toLocaleString("id-ID");
```

**Biasanya digabungkan dengan:** log dan tabel admin.

## Intl.DateTimeFormat

**Untuk apa:** pemformat tanggal yang bisa dipakai ulang.

```js
const fmt = new Intl.DateTimeFormat("id-ID", {
  dateStyle: "medium",
  timeStyle: "short",
});
fmt.format(new Date());
```

Lebih efisien jika memformat banyak tanggal dengan opsi sama.

`formatToParts` memecah bagian untuk styling.

**Biasanya digabungkan dengan:** daftar pesanan dan i18n.

## Intl.NumberFormat

**Untuk apa:** format angka dan uang.

```js
const rupiah = new Intl.NumberFormat("id-ID", {
  style: "currency",
  currency: "IDR",
  maximumFractionDigits: 0,
});
rupiah.format(45000); // Rp45.000 atau varian spasi
```

Persen:

```js
new Intl.NumberFormat("id-ID", { style: "percent" }).format(0.11);
```

**Biasanya digabungkan dengan:** `map` harga dan keranjang.

## Intl.RelativeTimeFormat

**Untuk apa:** “3 hari lalu”, “dalam 2 jam”.

```js
const rtf = new Intl.RelativeTimeFormat("id", { numeric: "auto" });
rtf.format(-1, "day"); // kemarin
rtf.format(2, "hour");
```

Kamu menghitung selisih sendiri, API hanya memformat.

**Biasanya digabungkan dengan:** `Date.now`, feed, dan notifikasi.

## Pola gabungan yang sering

Cuplikan judul:

```js
function cuplikan(teks, max = 80) {
  const bersih = teks.trim();
  if (bersih.length <= max) {
    return bersih;
  }
  return `${bersih.slice(0, max).trimEnd()}…`;
}
```

Uang + tanggal kartu:

```js
const uang = new Intl.NumberFormat("id-ID", {
  style: "currency",
  currency: "IDR",
  maximumFractionDigits: 0,
});
const tgl = new Intl.DateTimeFormat("id-ID", { dateStyle: "medium" });
```

Baca angka form:

```js
const harga = Number(input.value.replaceAll(".", "").replace(",", "."));
if (!Number.isFinite(harga) || harga < 0) {
  throw new Error("Harga tidak valid");
}
```

**Biasanya digabungkan dengan:** file 05 `map` dan file 09 form.

## Kesalahan yang sering

- Membandingkan teks tanpa `trim` / `toLowerCase`.
- `replace` hanya mengganti sekali, dikira semua.
- `split` lalu lupa `trim` tiap potongan.
- `getMonth()` dikira 1–12.
- `new Date("2026-09-22")` bergeser zona.
- `toFixed` dipakai hitung uang berulang (hasil string + error desimal).
- `parseInt` tanpa radix.
- `Math.random` untuk token aman.
- Mengubah string seperti array (`s[0] = "X"`).

**Biasanya digabungkan dengan:** file 13.
