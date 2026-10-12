# 09 — Event, form, dan delegation

[← 08 DOM](08-dom-selector-classlist-dataset.md) · [Indeks](README.md) · [Lanjut 10 →](10-fetch-async-storage.md)

Event adalah kabar bahwa sesuatu terjadi: klik, ketik, kirim form. Delegation memasang satu pendengar untuk banyak anak.

## Daftar isi

- [addEventListener](#addeventlistener)
- [removeEventListener](#removeeventlistener)
- [opsi once / capture / passive / signal](#opsi-once--capture--passive--signal)
- [event.target](#eventtarget)
- [event.currentTarget](#eventcurrenttarget)
- [preventDefault](#preventdefault)
- [stopPropagation](#stoppropagation)
- [stopImmediatePropagation](#stopimmediatepropagation)
- [klik](#klik)
- [input](#input)
- [change](#change)
- [submit](#submit)
- [keydown / keyup](#keydown--keyup)
- [focus / blur](#focus--blur)
- [focusin / focusout](#focusin--focusout)
- [pointer dan mouse](#pointer-dan-mouse)
- [scroll dan resize](#scroll-dan-resize)
- [DOMContentLoaded](#domcontentloaded)
- [event delegation](#event-delegation)
- [CustomEvent dan dispatchEvent](#customevent-dan-dispatchevent)
- [form.elements](#formelements)
- [FormData](#formdata)
- [input.value / checked](#inputvalue--checked)
- [select](#select)
- [validity / checkValidity](#validity--checkvalidity)
- [setCustomValidity](#setcustomvalidity)
- [reportValidity](#reportvalidity)
- [reset](#reset)
- [label dan htmlFor](#label-dan-htmlfor)
- [file input](#file-input)

## addEventListener

**Untuk apa:** memasang fungsi yang jalan saat peristiwa terjadi.

```js
const tombol = document.querySelector("#tambah");
tombol.addEventListener("click", (event) => {
  console.log("diklik", event.target);
});
```

Bisa banyak listener untuk event yang sama. Tidak menimpa seperti `onclick = ...` (kecuali kamu memakai properti `onclick`).

Nama event tanpa `on`: `"click"`, `"submit"`, `"input"`.

Jika elemen `null`, error. Ambil elemen dulu, cek, baru pasang.

**Biasanya digabungkan dengan:** `querySelector`, `preventDefault`, dan delegation.

## removeEventListener

**Untuk apa:** melepas listener. Harus fungsi **yang sama** dan opsi capture yang sama.

```js
function onKlik() {
  console.log("klik");
}
tombol.addEventListener("click", onKlik);
tombol.removeEventListener("click", onKlik);
```

Arrow yang ditulis inline tidak bisa dilepas nanti karena referensinya berbeda.

```js
tombol.addEventListener("click", () => {});
tombol.removeEventListener("click", () => {}); // tidak melepas
```

**Biasanya digabungkan dengan:** teardown, SPA, dan `{ signal }` AbortController.

## opsi once / capture / passive / signal

**Untuk apa:** mengatur cara listener hidup.

```js
tombol.addEventListener("click", onKlik, { once: true });
```

- `once`: lepas sendiri setelah sekali
- `capture: true`: jalan di fase turun, sebelum anak
- `passive: true`: janji tidak `preventDefault` (berguna scroll/touch)
- `signal`: lepas saat aborted

```js
const ac = new AbortController();
document.addEventListener("keydown", onEsc, { signal: ac.signal });
ac.abort();
```

**Biasanya digabungkan dengan:** modal (Esc sekali), file 12 AbortController.

## event.target

**Untuk apa:** node paling dalam yang terkena peristiwa.

```js
daftar.addEventListener("click", (event) => {
  console.log(event.target);
});
```

Bisa berupa teks node atau anak di dalam tombol. Naikkan dengan `closest`.

```js
const tombol = event.target.closest("button[data-id]");
if (!tombol) {
  return;
}
```

**Biasanya digabungkan dengan:** delegation dan `dataset`.

## event.currentTarget

**Untuk apa:** elemen yang **dipasangi** listener.

```js
kartu.addEventListener("click", function (event) {
  console.log(event.currentTarget === kartu);
});
```

Lebih andal daripada `this` (arrow tidak mengikat `this` ke elemen).

**Biasanya digabungkan dengan:** handler yang dipasang di induk.

## preventDefault

**Untuk apa:** membatalkan aksi bawaan: pindah tautan, kirim form, centang, menu konteks, dll.

```js
form.addEventListener("submit", (event) => {
  event.preventDefault();
  // proses JS
});

tautan.addEventListener("click", (event) => {
  event.preventDefault();
});
```

Tidak menghentikan event ke induk. Itu tugas `stopPropagation`.

Tidak semua event bisa dicegah, terutama jika listener `passive`.

**Biasanya digabungkan dengan:** `submit`, validasi, dan fetch.

## stopPropagation

**Untuk apa:** mencegah event naik ke induk (atau turun, di fase capture).

```js
dalam.addEventListener("click", (event) => {
  event.stopPropagation();
});
```

Jangan dipakai sebagai pola utama; delegation justru butuh event naik. Pakai jika tombol dalam kartu tidak boleh memicu klik kartu.

**Biasanya digabungkan dengan:** widget di dalam widget.

## stopImmediatePropagation

**Untuk apa:** seperti `stopPropagation`, plus menghentikan listener lain di node yang sama.

```js
event.stopImmediatePropagation();
```

Jarang dibutuhkan. Sulit di-debug jika disalahgunakan.

**Biasanya digabungkan dengan:** plugin yang berebut event yang sama.

## klik

**Untuk apa:** pointer menekan dan melepaskan pada elemen.

```js
tombol.addEventListener("click", () => {
  keranjang.push(produk);
});
```

`dblclick` untuk klik ganda. `click` juga bisa dari keyboard pada tombol/tautan (aksesibilitas).

Koordinat: `event.clientX`, `event.clientY`.

**Biasanya digabungkan dengan:** `dataset.id`, `find`, dan `classList`.

## input

**Untuk apa:** nilai berubah saat pengguna mengetik atau mengubah kontrol.

```js
cari.addEventListener("input", () => {
  const q = cari.value.trim().toLowerCase();
  render(produk.filter((p) => p.nama.toLowerCase().includes(q)));
});
```

Jalan per ketikan. Untuk `<select>` dan checkbox, `change` sering lebih alami, tetapi `input` juga ada di banyak kontrol modern.

**Biasanya digabungkan dengan:** `filter`, debounce (file 11), dan live search.

## change

**Untuk apa:** nilai “selesai” berubah: keluar dari input teks, pilih opsi, centang.

```js
urut.addEventListener("change", () => {
  const mode = urut.value;
  render(urutkan(produk, mode));
});
```

Pada teks, `change` menunggu blur. Untuk pencarian hidup, `input`.

**Biasanya digabungkan dengan:** `<select>`, checkbox, dan filter form.

## submit

**Untuk apa:** form dikirim (klik submit atau Enter di input).

```js
form.addEventListener("submit", async (event) => {
  event.preventDefault();
  const data = new FormData(form);
  const nama = String(data.get("nama") ?? "").trim();
  if (nama === "") {
    pesan.textContent = "Nama wajib";
    return;
  }
  await kirim(data);
});
```

Pasang di `form`, bukan hanya di tombol. Enter di input tetap tertangkap.

**Biasanya digabungkan dengan:** `FormData`, `preventDefault`, `fetch`.

## keydown / keyup

**Untuk apa:** tombol keyboard ditekan / dilepas.

```js
document.addEventListener("keydown", (event) => {
  if (event.key === "Escape") {
    tutupModal();
  }
  if (event.key === "Enter" && (event.metaKey || event.ctrlKey)) {
    form.requestSubmit();
  }
});
```

Pakai `event.key` (`"Enter"`, `"Escape"`, `"a"`), bukan `keyCode` usang.

`event.repeat` true jika ditekan lama. `event.preventDefault()` bisa menahan scroll spasi, hati-hati.

**Biasanya digabungkan dengan:** pintasan, modal, dan daftar panah.

## focus / blur

**Untuk apa:** elemen mendapat / kehilangan fokus. Tidak menggelembung.

```js
input.addEventListener("focus", () => input.classList.add("fokus"));
input.addEventListener("blur", () => input.classList.remove("fokus"));
```

Karena tidak bubble, delegation biasa gagal. Pakai `focusin`/`focusout`.

**Biasanya digabungkan dengan:** gaya fokus kustom dan simpan draf saat blur.

## focusin / focusout

**Untuk apa:** seperti focus/blur tetapi menggelembung.

```js
form.addEventListener("focusout", (event) => {
  validasi(event.target);
});
```

**Biasanya digabungkan dengan:** validasi per field di induk form.

## pointer dan mouse

**Untuk apa:** gerakan dan tombol pointer.

```js
el.addEventListener("pointerdown", (event) => {
  event.pointerId;
  event.clientX;
});
```

Ada `mousedown`/`mouseup`/`mousemove`/`mouseover`/`mouseout`/`mouseenter`/`mouseleave`.

`mouseenter`/`mouseleave` tidak bubble dan tidak terpicu saat pindah anak. `mouseover`/`mouseout` lebih berisik.

Pointer events mencakup mouse, pena, sentuh. Untuk UI modern, `pointer*` lebih serbaguna.

**Biasanya digabungkan dengan:** drag sederhana dan kanvas.

## scroll dan resize

**Untuk apa:** mengamati gulir atau ukuran jendela.

```js
window.addEventListener("scroll", () => {
  const y = window.scrollY;
}, { passive: true });

window.addEventListener("resize", () => {
  console.log(window.innerWidth);
});
```

Sering jalan. Jangan kerja berat tiap event; debounce/throttle. Untuk elemen masuk layar, `IntersectionObserver` (file 12) lebih hemat.

**Biasanya digabungkan dengan:** sticky, `matchMedia`, observer.

## DOMContentLoaded

**Untuk apa:** HTML selesai diparsing, tanpa menunggu gambar.

```js
document.addEventListener("DOMContentLoaded", () => {
  inisialisasi();
});
```

Tidak perlu jika script `defer` atau `type="module"` di akhir/`head` — mereka sudah menunggu dokumen.

`window` `load` menunggu semua aset.

**Biasanya digabungkan dengan:** skrip klasik di `head` tanpa defer.

## event delegation

**Untuk apa:** satu listener di induk menangani banyak anak, termasuk yang ditambah nanti.

```js
daftar.addEventListener("click", (event) => {
  const tombol = event.target.closest("[data-aksi='hapus']");
  if (!tombol || !daftar.contains(tombol)) {
    return;
  }
  const id = Number(tombol.dataset.id);
  hapusDariKeranjang(id);
});
```

Langkah:

1. pasang di induk yang stabil
2. `closest` selector anak
3. pastikan masih di dalam induk
4. baca `dataset`
5. ubah data, lalu render

Mengapa: tidak perlu memasang listener ke tiap tombol baru.

**Biasanya digabungkan dengan:** `dataset`, `find`/`filter`, `replaceChildren`.

## CustomEvent dan dispatchEvent

**Untuk apa:** membuat peristiwa sendiri agar bagian halaman tidak saling memanggil fungsi secara kaku.

```js
const event = new CustomEvent("keranjang:ubah", {
  bubbles: true,
  detail: { total: 2 },
});
panel.dispatchEvent(event);

document.addEventListener("keranjang:ubah", (event) => {
  console.log(event.detail.total);
});
```

Tanpa `bubbles: true`, induk tidak mendengar. `detail` membawa payload.

**Biasanya digabungkan dengan:** widget lepas-kait dan badge keranjang.

## form.elements

**Untuk apa:** akses kontrol form menurut `name` atau indeks.

```js
const form = document.querySelector("#checkout");
form.elements.nama.value;
form.elements["alamat-kirim"].value;
```

Radio se-nama memberi `RadioNodeList`. Checkbox: `checked`.

**Biasanya digabungkan dengan:** `submit` dan validasi cepat.

## FormData

**Untuk apa:** kumpulan field form, mudah dikirim atau dibaca.

```js
const data = new FormData(form);
data.get("email");
data.getAll("tag");
data.set("waktu", new Date().toISOString());
data.append("sumber", "web");
data.delete("sementara");
```

Iterasi:

```js
for (const [kunci, nilai] of data.entries()) {
  console.log(kunci, nilai);
}
```

Object biasa:

```js
const obj = Object.fromEntries(data);
```

Catatan: `fromEntries` hanya menyimpan satu nilai per kunci; untuk checkbox banyak, `getAll`.

Kirim:

```js
await fetch("/api/pesan", { method: "POST", body: data });
```

Jangan set `Content-Type` manual untuk `FormData`; browser mengisi boundary.

**Biasanya digabungkan dengan:** `submit`, `fetch`, upload file.

## input.value / checked

**Untuk apa:** nilai kontrol.

```js
teks.value;
teks.value = "Buku";
kotak.checked;
kotak.checked = true;
angka.valueAsNumber; // NaN jika kosong
```

`value` selalu string (kecuali `valueAsNumber` / `valueAsDate` pada input tertentu).

```js
const jumlah = inputJumlah.valueAsNumber;
if (!Number.isInteger(jumlah)) {
  console.log("Jumlah tidak valid");
}
```

**Biasanya digabungkan dengan:** `Number`, `trim`, dan `filter`.

## select

**Untuk apa:** daftar pilihan.

```js
select.value;
select.selectedIndex;
select.options[select.selectedIndex].text;
```

Multiple: loop `select.selectedOptions`.

```js
[...select.selectedOptions].map((o) => o.value);
```

**Biasanya digabungkan dengan:** `change` dan query URL.

## validity / checkValidity

**Untuk apa:** memanfaatkan validasi HTML (`required`, `type="email"`, `min`).

```js
if (!form.checkValidity()) {
  form.reportValidity();
  return;
}

input.validity.valid;
input.validity.valueMissing;
input.validity.typeMismatch;
input.validity.tooShort;
```

`checkValidity` mengembalikan boolean dan memicu event `invalid` jika gagal.

**Biasanya digabungkan dengan:** atribut HTML form dan pesan native.

## setCustomValidity

**Untuk apa:** menaruh pesan error sendiri. String kosong = valid.

```js
if (sandi.value !== ulangi.value) {
  ulangi.setCustomValidity("Sandi tidak sama");
} else {
  ulangi.setCustomValidity("");
}
```

Harus dibersihkan saat sudah valid, atau form tetap tertahan.

**Biasanya digabungkan dengan:** `input` live dan `reportValidity`.

## reportValidity

**Untuk apa:** menampilkan UI validasi bawaan browser.

```js
input.reportValidity();
form.reportValidity();
```

**Biasanya digabungkan dengan:** `checkValidity` setelah `preventDefault`.

## reset

**Untuk apa:** mengembalikan form ke nilai awal HTML.

```js
form.reset();
form.addEventListener("reset", () => {
  pesan.textContent = "";
});
```

Tidak otomatis membersihkan error JS yang kamu tulis di elemen lain — resetkan manual.

**Biasanya digabungkan dengan:** tombol reset dan tutup modal form.

## label dan htmlFor

**Untuk apa:** klik label memfokuskan kontrol. Bukan method JS, tetapi penting agar event/form nyaman.

```html
<label for="q">Cari</label>
<input id="q" name="q" />
```

`label.htmlFor` di JS sama dengan `for`.

**Biasanya digabungkan dengan:** aksesibilitas dan area klik lebih besar.

## file input

**Untuk apa:** membaca berkas yang dipilih pengguna.

```js
inputFile.addEventListener("change", () => {
  const berkas = inputFile.files[0];
  if (!berkas) {
    return;
  }
  console.log(berkas.name, berkas.size, berkas.type);
});
```

`FormData` otomatis menyertakan file jika input ada di form. Pratinjau gambar:

```js
const url = URL.createObjectURL(berkas);
img.src = url;
// URL.revokeObjectURL(url) setelah tidak dipakai
```

**Biasanya digabungkan dengan:** `FormData`, `fetch`, file 12 `URL`.

## requestSubmit

**Untuk apa:** mengirim form seperti klik tombol submit, termasuk validasi HTML.

```js
form.requestSubmit();
form.requestSubmit(tombolSubmitKhusus);
```

Beda dengan `form.submit()` yang melewati event `submit` dan validasi constraint.

**Biasanya digabungkan dengan:** pintasan keyboard dan wizard multi-langkah.

## pola debounce di input

**Untuk apa:** menunggu berhenti mengetik sebelum menyaring/fetch.

```js
let timer;
cari.addEventListener("input", () => {
  window.clearTimeout(timer);
  timer = window.setTimeout(() => {
    terapkanCari(cari.value);
  }, 300);
});
```

Detail timer di [file 11](11-module-timer-console.md).

**Biasanya digabungkan dengan:** `filter` lokal atau `fetch` search.

## Kesalahan event/form yang sering

- `submit` tanpa `preventDefault` membuat halaman reload.
- Listener di tombol, lupa Enter di input.
- Delegation tanpa `closest`, gagal jika klik ikon dalam tombol.
- `removeEventListener` dengan fungsi berbeda.
- `FormData` → `Object.fromEntries` kehilangan field kembar.
- `value` dijumlahkan sebagai string (`"1" + "2" === "12"`).
- `setCustomValidity` tidak dikosongkan.
- Memasang listener di dalam render tanpa menghapus yang lama (dobel aksi). Delegation menghindari ini.

**Biasanya digabungkan dengan:** file 08, 10, 13.
