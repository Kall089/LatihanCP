# Latihan Soal 05 — JavaScript & DOM

Kerjakan tanpa kunci. Materi:
[`../../0-materi/05-javascript-dom/teori.md`](../../0-materi/05-javascript-dom/teori.md).
Praktikum: counter, validasi, daftar dinamis.

---

## A. Soal konsep (10)

### A1. Pilihan ganda — `const` vs `let`

- a. `const` membuat objek membeku (tidak bisa `push`).
- b. `const` menolak *reassignment*; isi objek/array masih bisa berubah.
- c. `let` hanya untuk fungsi, `const` hanya untuk angka.
- d. `var` disarankan di kode baru karena function-scope lebih aman.

### A2. Prediksi array

```js
const nilai = [80, 55, 90, 60];
const hasil = nilai.filter((n) => n >= 70).map((n) => n / 10);
```

Isi `hasil`? Apakah `nilai` asli berubah?

### A3. Esai — DOM bukan file

"JavaScript mengubah `index.html` di disk." Benar atau salah? Jelaskan
apa yang sebenarnya diubah, dan mengapa refresh mengembalikan tampilan
awal.

### A4. Pilihan ganda — seleksi

Untuk mengambil **semua** elemen `.item` sekaligus:

- a. `document.querySelector(".item")`
- b. `document.querySelectorAll(".item")`
- c. `document.getElementByClass(".item")`
- d. `document.find(".item")`

### A5. Prediksi — script di head

```html
<head>
  <script>
    document.querySelector("#app").textContent = "Halo";
  </script>
</head>
<body>
  <div id="app"></div>
</body>
```

Apa yang terjadi? Dua cara memperbaiki.

### A6. Esai — `textContent` vs `innerHTML`

Mengapa memasukkan `input.value` ke `innerHTML` berbahaya (istilah XSS)?
Kapan `innerHTML` masih pantas?

### A7. Prediksi event form

```js
tombolKirim.addEventListener("click", () => {
  const nama = input.value.trim();
  if (!nama) pesan.textContent = "Wajib";
});
```

Pengguna menekan **Enter** di input. Apa yang biasanya terjadi? Mengapa
listener harus di `submit` pada `<form>` plus `event.preventDefault()`?

### A8. Pilihan ganda — pola state → render

Urutan yang benar setelah tombol "Tambah" diklik:

- a. Ubah DOM dulu, lalu update variabel jika sempat.
- b. Ubah state (variabel/array), lalu panggil `render()` yang menggambar UI dari state.
- c. `location.reload()` agar HTML segar.
- d. `innerHTML += ...` tanpa menyentuh array.

### A9. Prediksi tipe

```js
const n = document.querySelector("#jumlah").value; // pengguna mengetik 5
console.log(n + 1);
```

Apa yang tercetak? Perbaikan?

### A10. Esai — `===`

Berikan satu contoh di mana `==` bernilai true tetapi `===` false. Mengapa
mata kuliah ini melarang `==`?

---

## B. Soal praktik kecil (3)

Tulis di `latihan.js` (boleh plus HTML minimal). Nanti bisa dicek
`node --check latihan.js` untuk file tanpa `document`.

### B1. Counter

Variabel `let skor = 0`. Fungsi `naik()`, `turun()` (minimum 0), `render()`
yang mengeset `textContent` elemen `#skor`. Pasang tiga tombol. Pola state →
render, bukan mengedit DOM di masing-masing listener tanpa fungsi bersama.

### B2. Validasi

Form `#daftar` dengan nama dan email. Submit: `preventDefault`, nama
minimal 3 karakter setelah `trim`, email tidak kosong. Pesan di `#info`.

### B3. Daftar dari array

Array `const hobi = ["Membaca"]`. Render ke `<ul id="daftar">` memakai
`createElement` + `textContent` (bukan merangkai innerHTML dari input).
Submit menambah item; tiap baris punya tombol Hapus yang `splice` +
`render`.
