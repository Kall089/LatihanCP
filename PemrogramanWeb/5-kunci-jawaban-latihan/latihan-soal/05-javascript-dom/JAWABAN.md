# Jawaban 05 — JavaScript & DOM

---

## A. Konsep

### A1 — b

`const` mengunci *binding*, bukan kedalaman objek. `arr.push` legal;
`arr = []` tidak. `var` tidak disarankan.

### A2

`hasil` = `[8, 9]`. `filter` lolos 80 dan 90, `map` bagi 10. Array `nilai`
**tidak** berubah (`filter`/`map` menghasilkan array baru).

### A3

Salah. JS mengubah **pohon DOM di memori**. File di disk utuh. Refresh
parse ulang file → state variabel hilang.

### A4 — b

`querySelector` = elemen **pertama**. `querySelectorAll` = semua (NodeList).

### A5

`querySelector` mengembalikan `null` (body belum di-parse) → TypeError.
Perbaikan: pindahkan `<script>` ke akhir `body`, atau `defer` pada
`<script src>`, atau bungkus di `DOMContentLoaded`.

### A6

XSS: input berisi markup/skrip ikut dieksekusi. Pakai `textContent` /
`createElement`. `innerHTML` pantas untuk template yang **seluruhnya** kamu
kendalikan (bukan string pengguna).

### A7

Enter di input dalam form memicu **submit** bawaan → reload, listener
`click` pada tombol bisa terlewati. Pasang `submit` di `<form>` dan
`preventDefault()` agar validasi JS jalan dan halaman tidak refresh.

### A8 — b

Event → ubah state → `render()` dari state. Itulah `UI = f(state)`.

### A9

`"51"` (concat string). `Number(n) + 1` atau `parseInt(n, 10) + 1`.

### A10

`"5" == 5` true, `"5" === 5` false. `==` melakukan coercion yang sulit
dinalar (`"" == 0`, dll.). Selalu `===`.

---

## B. Praktik

Cuplikan logika (HTML: `#skor`, `#daftar`, form sesuai soal). File murni
tanpa `document` tetap bisa mengekspresikan fungsi yang sama.

### B1

```js
let skor = 0;
const skorEl = document.querySelector("#skor");

function render() {
  skorEl.textContent = skor;
}
function naik() {
  skor += 1;
  render();
}
function turun() {
  skor = Math.max(0, skor - 1);
  render();
}

document.querySelector("#naik").addEventListener("click", naik);
document.querySelector("#turun").addEventListener("click", turun);
render();
```

### B2

```js
form.addEventListener("submit", (e) => {
  e.preventDefault();
  const nama = namaInput.value.trim();
  const email = emailInput.value.trim();
  if (nama.length < 3) {
    info.textContent = "Nama minimal 3 karakter.";
    return;
  }
  if (!email) {
    info.textContent = "Email wajib diisi.";
    return;
  }
  info.textContent = `Terdaftar: ${nama}`;
  form.reset();
});
```

### B3

Pola sama dengan kunci praktikum daftar dinamis: array + `createElement` +
`textContent` + `splice` + `render()`. Lihat juga studi kasus 02.
