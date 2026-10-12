# Modul 05 — JavaScript & DOM

> Praktikum terkait: [`../../1-pembelajaran/05-javascript-dom/`](../../1-pembelajaran/05-javascript-dom/)
> (3 bab: counter DOM, validasi formulir, daftar dinamis).
> Slide ringkasan: [`slides.pptx`](slides.pptx).

## Tujuan setelah membaca materi ini

- Menulis JavaScript modern minimum: `const`/`let`, fungsi, array method.
- Menjelaskan DOM sebagai pohon objek di memori, bukan file `.html` di disk.
- Menyeleksi elemen, mengubah teks/class, dan merespons event pengguna.
- Menerapkan pola **state → render** (fondasi React di Modul 06).
- Memvalidasi formulir tanpa reload halaman, dengan aman terhadap XSS.

**Prasyarat**: Modul 01 (HTML, terutama formulir) dan 02 (selector CSS —
`querySelector` memakai syntax yang sama).

---

## 1. Mengapa JavaScript ada di halaman?

HTML memberi struktur, CSS memberi tampilan. Keduanya **statis**: setelah
browser menggambar, halaman diam sampai di-reload. JavaScript adalah bahasa
yang membuat halaman **bereaksi**: tombol menambah angka, form menolak input
kosong, daftar bertambah tanpa pindah halaman.

```text
  HTML  →  "ada tombol dan angka 0"
  CSS   →  "tombol biru, angka besar"
  JS    →  "saat diklik, angka jadi 1, 2, 3…"
```

JS **tidak** mengubah file `.html` di hard disk. Ia mengubah **pohon DOM di
memori**. Refresh mengembalikan halaman ke isi file asli — itu sebabnya data
yang hanya disimpan di variabel JS hilang saat reload (kecuali kamu simpan ke
`localStorage`, yang belum wajib di praktikum ini).

Di mata kuliah ini kita memakai **JavaScript murni di browser** (Modul 05),
lalu React (Modul 06) yang mengotomatiskan pola yang sama.

---

## 2. Dasar bahasa yang wajib hafal

### Variabel: `const` dulu, `let` jika perlu

```js
const nama = "Sinta";     // tidak di-assign ulang
let jumlahSesi = 0;       // akan berubah: jumlahSesi = jumlahSesi + 1

nama = "Andi";            // TypeError — const menolak reassignment
```

- **`const`**: default. Tidak bisa `=` ulang. Objek/array di dalamnya *tetap
  bisa diubah isinya* (`arr.push` masih jalan) — yang dilarang hanya
  mengganti bindernya.
- **`let`**: boleh di-assign ulang. Pakai untuk counter, flag, akumulator.
- **`var`**: cara lama, *function-scope* yang aneh. Lupakan untuk kode baru.

### Fungsi biasa vs arrow function

```js
function sapa(nama) {
  return `Halo, ${nama}!`;
}

const tambah = (a, b) => a + b;          // return implisit (satu ekspresi)
const sapaLagi = (nama) => {             // blok: butuh return eksplisit
  return `Halo, ${nama}!`;
};
```

Arrow function adalah yang paling sering kamu tulis sebagai *callback*
(`addEventListener`, `.map`). Hafalkan bentuk `(x) => x * 2`.

### Template literal

String dengan **backtick** `` ` ``, bukan kutip biasa. Bisa sisipkan ekspresi
dan multi-baris:

```js
const pesan = `${nama} sudah belajar ${jumlahSesi} sesi`;
```

Ini nenek moyang JSX di React: keduanya menyisipkan nilai ke markup lewat
kurung (`${}` di JS, `{}` di JSX).

### Objek, array, destructuring

```js
const mhs = { nama: "Andi", ipk: 3.7 };
const { ipk } = mhs;                     // ambil properti jadi variabel
console.log(mhs.nama, ipk);              // "Andi"  3.7

const nilai = [80, 90, 70];
const [pertama, kedua] = nilai;          // 80, 90
```

### Perbandingan: selalu `===`

`"5" == 5` bernilai `true` karena *coercion* (konversi tipe diam-diam).
`"5" === 5` bernilai `false`. **Selalu pakai `===` dan `!==`.**

### `input.value` selalu string

```js
input.value + 1          // "5" + 1 → "51"  😱
Number(input.value) + 1  // 6               ✅
```

---

## 3. Array method yang 80% pekerjaan data web

Trio **map / filter / find** akan muncul lagi di React, Next.js, dan studi
kasus. Mereka **tidak mengubah array asli** (kecuali kamu sengaja mutasi di
dalam callback) — mereka mengembalikan array/nilai baru.

| Method | Hasil | Contoh |
|---|---|---|
| `map(fn)` | Array baru, tiap item diubah | `harga.map((h) => h * 1000)` |
| `filter(fn)` | Array baru, item yang lolos tes | `mhs.filter((m) => m.ipk >= 3)` |
| `find(fn)` | **Satu** item pertama yang cocok, atau `undefined` | `produk.find((p) => p.id === 2)` |
| `forEach(fn)` | Efek samping, tanpa nilai balik berguna | `items.forEach(renderItem)` |
| `reduce(fn, awal)` | Satu nilai akumulasi | `angka.reduce((a, b) => a + b, 0)` |
| `some` / `every` | Boolean: ada / semua cocok | `nilai.some((n) => n < 60)` |
| `join(pemisah)` | String gabungan | `kelas.map(...).join("")` |

```js
const produk = [
  { id: 1, nama: "Kopi", harga: 18000 },
  { id: 2, nama: "Teh",  harga: 10000 },
];

const nama = produk.map((p) => p.nama);
// → ["Kopi", "Teh"]

const murah = produk.filter((p) => p.harga < 15000);
// → [{ id: 2, nama: "Teh", harga: 10000 }]

const teh = produk.find((p) => p.id === 2);
// → { id: 2, nama: "Teh", harga: 10000 }
```

`join("")` sering dipasangkan `map` untuk merakit HTML string. Hati-hati:
kalau isinya dari pengguna, jangan lewat `innerHTML` (lihat bagian 5).

---

## 4. DOM — HTML menjadi pohon objek

Browser *parse* HTML menjadi **Document Object Model**: pohon node. JavaScript
berbicara dengan pohon ini, bukan dengan teks file.

```text
HTML:                          DOM tree:
<body>                             body
  <h1>Judul</h1>                  ╱    ╲
  <ul id="daftar">              h1      ul#daftar
    <li>Apel</li>              │       ╱      ╲
    <li>Jeruk</li>          "Judul"  li        li
  </ul>                              │         │
</body>                           "Apel"    "Jeruk"

document.querySelector("#daftar")  → node ul
ul.children                        → [li, li]
li.parentElement                   → ul
```

DevTools **Elements** menampilkan DOM *hasil* (setelah JS jalan), bukan
sumber file. Itu sebabnya "Inspect" kadang beda dengan yang kamu ketik.

Hubungan dengan Modul 01: setiap tag jadi *element node*, teks jadi *text
node*, atribut jadi properti (`id`, `className`, `href`).

---

## 5. Seleksi dan manipulasi

`querySelector` menerima **selector CSS** apa pun yang sudah kamu pelajari di
Modul 02. `querySelectorAll` mengembalikan *NodeList* (mirip array; punya
`forEach`, bisa di-spread `[...nodeList]`).

```js
const judul  = document.querySelector("h1");
const tombol = document.querySelector("#tambah");
const items  = document.querySelectorAll(".item");

judul.textContent = "Skor: 5";           // teks murni — AMAN
kotak.innerHTML   = "<b>HTML</b>";       // di-parse sebagai HTML — hati-hati

kartu.classList.add("aktif");
kartu.classList.remove("hidden");
kartu.classList.toggle("terbuka");       // ada → hilang, tidak ada → muncul

const li = document.createElement("li");
li.textContent = "Item baru";
daftar.append(li);
```

### `textContent` vs `innerHTML`

| | `textContent` | `innerHTML` |
|---|---|---|
| Isi | Teks polos | String di-parse jadi HTML |
| `<b>Hai</b>` tampil | huruf `< b > Hai...` | **Hai** tebal |
| Input pengguna | ✅ aman | ❌ celah **XSS** jika mentah |

**XSS** (*Cross-Site Scripting*): penyerang mengetik
`<img src=x onerror="alert(1)">` di form. Kalau kamu taruh ke `innerHTML`,
skrip itu jalan di browser pengunjung lain. Praktikum daftar dinamis memakai
`createElement` + `textContent` justru karena ini.

Gaya lebih rapi diubah lewat **class**, bukan `el.style.color = ...` yang
menebarkan CSS di dalam JS.

---

## 6. Event — merespons aksi pengguna

Pola: *saat X terjadi pada elemen Y, jalankan fungsi Z*.

```js
const tombol = document.querySelector("#plus");
tombol.addEventListener("click", () => {
  jumlah++;
  render();
});
```

**Event object** adalah argumen pertama callback:

- `event.target` — elemen sumber (yang diklik/diketik).
- `event.preventDefault()` — batalkan aksi bawaan browser.

Event yang wajib dihafal:

| Event | Kapan | Dipasang di |
|---|---|---|
| `click` | Klik mouse/tap | tombol, kartu, apa saja |
| `submit` | Form dikirim (Enter atau klik submit) | **`<form>`**, bukan tombol |
| `input` | Setiap ketikan | `<input>`, `<textarea>` |
| `change` | Nilai selesai diubah (blur / pilih option) | select, checkbox |
| `keydown` | Tombol keyboard | dokumen / input |
| `DOMContentLoaded` | HTML selesai di-parse | `document` |

### Form: `submit` + `preventDefault`

Tanpa `preventDefault`, browser **reload** halaman — semua variabel JS
kembali ke nol. Ini bug nomor satu praktikum validasi.

```js
form.addEventListener("submit", (event) => {
  event.preventDefault();

  const nama = inputNama.value.trim();
  if (nama === "") {
    pesanError.textContent = "Nama wajib diisi";
    return;
  }
  // ... proses data valid
});
```

Pasang listener di **form**, bukan di tombol. Tombol `type="submit"` di dalam
form memicu event `submit`; menekan Enter di input juga. Kalau kamu hanya
listen `click` di tombol, Enter lolos tanpa validasi.

---

## 7. Pola emas: state → render

Ini DNA React, ditulis manual dulu agar kamu *merasakan* masalahnya.

```text
  EVENT (klik / submit / ketik)
           │
           ▼
     ubah STATE          ← satu sumber data (array, angka, objek)
           │
           ▼
      render()           ← gambar ULANG seluruh UI dari state
           │
           ▼
         DOM
```

```js
let daftarTugas = [];                    // STATE

function render() {                      // RENDER
  ul.innerHTML = daftarTugas
    .map((t) => `<li>${t}</li>`)
    .join("");
  info.textContent = `${daftarTugas.length} tugas`;
}

form.addEventListener("submit", (e) => {
  e.preventDefault();                    // EVENT
  daftarTugas.push(input.value);         // ubah state
  input.value = "";
  render();                              // gambar ulang
});

render();                                // gambar pertama kali
```

Mengapa tidak mengedit DOM "satu-satu"? Karena sinkronisasi manual rawan
lupa: total item di footer tidak di-update, tombol hapus menghilang, dll.
**UI = f(state)** — tampilan adalah fungsi murni dari data. Di React, langkah
`render()` menjadi otomatis setiap `setState`.

Praktikum yang memakai pola ini:

1. `01-counter-dom` — state = angka; render menulis teks + class sukses.
2. `02-validasi-formulir` — state sejenak di variabel lokal handler; output =
   pesan error/sukses.
3. `03-daftar-dinamis` — state = array string; render membangun `<li>` +
   tombol hapus.

---

## 8. Validasi formulir di JavaScript

HTML sudah punya `required`, `type="email"`, `minlength` (Modul 01). JS
dipakai ketika pesan harus berbahasa sendiri, aturan lebih rumit, atau data
diproses di klien tanpa kirim ke server.

Checklist handler submit:

1. `event.preventDefault()`.
2. Baca `.value.trim()` — spasi di ujung bukan data.
3. Cek aturan berurutan; `return` di error pertama (atau kumpulkan semua).
4. Tulis pesan ke elemen khusus (`#message`), jangan `alert()`.
5. Jika valid: proses (tambah ke array, tampilkan sapaan), lalu `form.reset()`.

```js
if (nama.length < 3) {
  pesan.textContent = "Nama minimal 3 karakter.";
  return;
}
if (!email || !emailInput.validity.valid) {
  pesan.textContent = "Masukkan email yang valid.";
  return;
}
pesan.textContent = `Selamat datang, ${nama}!`;
```

`input.validity.valid` memakai aturan HTML (`type="email"`, `required`).
Gabungan HTML + JS = pertahanan berlapis. HTML menahan submit "kasar"; JS
memberi umpan balik yang kamu kendalikan.

Untuk daftar dinamis, hapus item memakai **event delegation**: listener satu
di `<ul>`, cek `event.target.closest("button")`, baca `data-index`, `splice`
array, `render()`. Lebih hemat daripada pasang listener per tombol yang
terus-menerus dibuat ulang.

---

## 9. Kesalahan umum (dan cara menghindarinya)

| # | Kesalahan | Akibat | Perbaikan |
|---|---|---|---|
| 1 | `<script>` di `<head>` tanpa `defer` | `querySelector` = `null` (HTML belum ada) | Taruh script di **akhir body**, atau `defer` |
| 2 | `innerHTML` + input pengguna | XSS | `textContent` / `createElement` |
| 3 | `==` bukan `===` | `"0" == false` dan keanehan lain | Selalu `===` |
| 4 | Lupa `preventDefault` | Form reload, state hilang | Handler `submit` di form |
| 5 | Ubah DOM tanpa state | UI dan data tidak sinkron | State di variabel, DOM dari `render()` |
| 6 | `.value` dijumlah tanpa `Number()` | `"5" + 1 = "51"` | `Number(...)` atau `parseInt(..., 10)` |
| 7 | Listen `click` di tombol submit | Enter di input melewati validasi | Listen `submit` di form |
| 8 | Mutasi array lalu lupa `render()` | Tampilan basi | Setiap ubah state → `render()` |

Null dari `querySelector` hampir selalu berarti: (a) typo selector, (b) `id`
tidak cocok dengan HTML, (c) script jalan terlalu awal. Buka Console; error
`Cannot read properties of null` = selector gagal.

---

## 10. Cheatsheet

```js
// DATA
const x = ...;
let y = 0;
const f = (a, b) => a + b;
`Halo ${nama}`

// ARRAY
arr.map((x) => ...)
arr.filter((x) => ...)
arr.find((x) => ...)
arr.reduce((a, b) => a + b, 0)
arr.join("")

// SELEKSI
document.querySelector("#id")
document.querySelectorAll(".cls")

// MANIPULASI
el.textContent = "aman";
el.classList.add / remove / toggle
el.append(childEl)
document.createElement("li")

// EVENT
el.addEventListener("click", fn)
form.addEventListener("submit", (e) => {
  e.preventDefault();
  const v = input.value.trim();
});

// POLA
let state = [];
function render() { /* gambar dari state */ }
// event → ubah state → render()
```

## Lanjut ke praktikum

Kerjakan berurutan di [`../../1-pembelajaran/05-javascript-dom/`](../../1-pembelajaran/05-javascript-dom/):

1. `01-counter-dom` — selector, event klik, render angka (bagian 5–7).
2. `02-validasi-formulir` — submit, `preventDefault`, pesan error (bagian 6, 8).
3. `03-daftar-dinamis` — array + `render()` + hapus item (bagian 3, 7).

Buka DevTools Console sepanjang praktikum. Setelah itu uji diri dengan
[`../../3-latihan-soal/05-javascript-dom/soal.md`](../../3-latihan-soal/05-javascript-dom/soal.md)
dan terapkan di studi kasus
[`../../4-studi-kasus/02-dashboard-interaktif/`](../../4-studi-kasus/02-dashboard-interaktif/).
