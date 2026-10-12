# 08 — DOM, selector, classList, dan dataset

[← 07 JSON](07-json-set-map-promise.md) · [Indeks](README.md) · [Lanjut 09 →](09-event-form-delegation.md)

DOM adalah pohon elemen halaman. JavaScript mengambil node, mengubah teks, kelas, dan atribut.

## Daftar isi

- [document](#document)
- [getElementById](#getelementbyid)
- [querySelector](#queryselector)
- [querySelectorAll](#queryselectorall)
- [getElementsByClassName](#getelementsbyclassname)
- [getElementsByTagName](#getelementsbytagname)
- [getElementsByName](#getelementsbyname)
- [closest](#closest)
- [matches](#matches)
- [contains](#contains)
- [createElement](#createelement)
- [createTextNode](#createtextnode)
- [append](#append)
- [appendChild](#appendchild)
- [prepend](#prepend)
- [before / after](#before--after)
- [insertBefore](#insertbefore)
- [replaceWith / replaceChild](#replacewith--replacechild)
- [remove / removeChild](#remove--removechild)
- [cloneNode](#clonenode)
- [replaceChildren](#replacechildren)
- [innerHTML](#innerhtml)
- [outerHTML](#outerhtml)
- [textContent](#textcontent)
- [innerText](#innertext)
- [insertAdjacentHTML](#insertadjacenthtml)
- [insertAdjacentElement](#insertadjacentelement)
- [className](#classname)
- [classList.add](#classlistadd)
- [classList.remove](#classlistremove)
- [classList.toggle](#classlisttoggle)
- [classList.contains](#classlistcontains)
- [classList.replace](#classlistreplace)
- [dataset](#dataset)
- [getAttribute](#getattribute)
- [setAttribute](#setattribute)
- [removeAttribute](#removeattribute)
- [hasAttribute](#hasattribute)
- [toggleAttribute](#toggleattribute)
- [style](#style)
- [getComputedStyle](#getcomputedstyle)
- [hidden](#hidden)
- [parentElement / parentNode](#parentelement--parentnode)
- [children / childNodes](#children--childnodes)
- [firstElementChild / lastElementChild](#firstelementchild--lastelementchild)
- [nextElementSibling / previousElementSibling](#nextelementsibling--previouselementsibling)
- [document.documentElement / body / head](#documentdocumentelement--body--head)
- [template dan importNode](#template-dan-importnode)

## document

**Untuk apa:** pintu masuk ke halaman yang sedang dibuka.

```js
document.title;
document.URL;
document.documentElement; // <html>
document.body;
```

Hanya ada di browser. Script di `<head>` tanpa `defer`/`type="module"` bisa jalan sebelum `body` ada.

```html
<script src="script.js" defer></script>
```

**Biasanya digabungkan dengan:** selector, event, dan `DOMContentLoaded` jika tanpa `defer`.

## getElementById

**Untuk apa:** mengambil satu elemen menurut `id`.

```js
const form = document.getElementById("form-cari");
```

Hasil elemen atau `null`. Tidak perlu `#`.

Lebih cepat untuk id, tetapi `querySelector("#id")` lebih seragam jika kamu sudah memakai CSS selector.

**Biasanya digabungkan dengan:** form, modal, dan landmark halaman.

## querySelector

**Untuk apa:** elemen pertama yang cocok CSS selector.

```js
const judul = document.querySelector("h1");
const kartu = document.querySelector(".kartu");
const wajib = document.querySelector("input[required]");
const dalam = dokumenKartu.querySelector(".harga");
```

Tidak ketemu → `null`. Cek sebelum memakai.

```js
const el = document.querySelector(".kosong");
el?.classList.add("sembunyi");
```

**Biasanya digabungkan dengan:** CSS yang sama, `?.`, dan event.

## querySelectorAll

**Untuk apa:** semua kecocokan sebagai `NodeList` statis.

```js
const kartu = document.querySelectorAll(".kartu");
kartu.forEach((el) => {
  console.log(el.textContent);
});
```

Bukan array: ada `forEach`, tidak selalu ada `map`. Ubah jika perlu:

```js
const teks = [...kartu].map((el) => el.textContent.trim());
```

Tidak hidup: elemen baru yang ditambah nanti tidak ikut otomatis.

Selector dari elemen:

```js
artikel.querySelectorAll("a[href]");
```

**Biasanya digabungkan dengan:** `classList`, delegation alternatif, dan `Array.from`.

## getElementsByClassName

**Untuk apa:** koleksi hidup menurut kelas.

```js
const item = document.getElementsByClassName("item");
```

`HTMLCollection`, hidup: berubah saat DOM berubah. Tidak punya `forEach` di semua konteks lama. Konversi:

```js
Array.from(item).forEach((el) => el.classList.add("siap"));
```

Berbahaya di-loop sambil menghapus anggota (koleksi menyusut). Salin dulu.

**Biasanya digabungkan dengan:** kode lama. Untuk daftar tetap, `querySelectorAll`.

## getElementsByTagName

**Untuk apa:** koleksi hidup menurut tag.

```js
document.getElementsByTagName("li");
document.getElementsByTagName("p");
```

**Biasanya digabungkan dengan:** skrip generik. Selector CSS lebih fleksibel.

## getElementsByName

**Untuk apa:** elemen dengan atribut `name` (form).

```js
document.getElementsByName("warna");
```

**Biasanya digabungkan dengan:** radio group. Alternatif: `form.elements.warna`.

## closest

**Untuk apa:** diri sendiri atau leluhur terdekat yang cocok selector.

```js
tombol.closest(".kartu");
tautan.closest("article");
```

Tidak ketemu → `null`. Inti event delegation: dari `event.target` naik ke kartu.

**Biasanya digabungkan dengan:** file 09 delegation dan `dataset`.

## matches

**Untuk apa:** apakah elemen cocok selector.

```js
el.matches("button[data-id]");
el.matches(".aktif");
```

**Biasanya digabungkan dengan:** `if` di handler delegasi.

## contains

**Untuk apa:** apakah node ada di dalam node lain (termasuk diri).

```js
menu.contains(event.target);
```

Pakai untuk klik di luar: tutup dropdown jika klik bukan di menu.

```js
document.addEventListener("click", (event) => {
  if (!panel.contains(event.target) && !tombol.contains(event.target)) {
    panel.hidden = true;
  }
});
```

**Biasanya digabungkan dengan:** modal, dropdown, dan event document.

## createElement

**Untuk apa:** membuat elemen baru yang belum menempel di halaman.

```js
const li = document.createElement("li");
li.textContent = "Buku";
li.className = "item";
```

Belum terlihat sampai `append` ke node yang ada di dokumen.

**Biasanya digabungkan dengan:** `append`, `dataset`, dan `classList`.

## createTextNode

**Untuk apa:** node teks mentah, tanpa HTML.

```js
const teks = document.createTextNode("Buku <promo>");
el.append(teks);
```

`textContent` biasanya cukup.

**Biasanya digabungkan dengan:** merakit node manual.

## append

**Untuk apa:** menambah di akhir, menerima elemen atau string.

```js
ul.append(li);
ul.append("teks", li2);
```

String menjadi teks, bukan HTML. Aman dari injection jika isinya pengguna.

**Biasanya digabungkan dengan:** `createElement` dan daftar dinamis.

## appendChild

**Untuk apa:** cara lama: hanya node, mengembalikan node itu.

```js
ul.appendChild(li);
```

`append` lebih fleksibel. Tetap sering ketemu di contoh lama.

**Biasanya digabungkan dengan:** kode warisan.

## prepend

**Untuk apa:** menambah di depan anak-anak.

```js
ul.prepend(liBaru);
```

**Biasanya digabungkan dengan:** item terbaru di atas.

## before / after

**Untuk apa:** sisip sebagai saudara, bukan anak.

```js
kartu.before(badge);
kartu.after(catatan);
```

**Biasanya digabungkan dengan:** sisip pesan error setelah input.

## insertBefore

**Untuk apa:** cara lama menyisipkan sebelum node acuan.

```js
induk.insertBefore(baru, acuan);
induk.insertBefore(baru, null); // seperti appendChild
```

**Biasanya digabungkan dengan:** kode lama. `before` lebih jelas.

## replaceWith / replaceChild

**Untuk apa:** menukar node.

```js
lama.replaceWith(baru);
induk.replaceChild(baru, lama);
```

**Biasanya digabungkan dengan:** ganti skeleton menjadi kartu jadi.

## remove / removeChild

**Untuk apa:** melepas node dari pohon.

```js
li.remove();
ul.removeChild(li);
```

`remove` lebih langsung. Node yang dilepas masih ada di memori jika masih dipegang variabel.

**Biasanya digabungkan dengan:** hapus item keranjang dan tutup toast.

## cloneNode

**Untuk apa:** menyalin node.

```js
const dangkal = kartu.cloneNode(false); // tanpa anak
const dalam = kartu.cloneNode(true); // beserta anak
```

Listener yang dipasang lewat `addEventListener` **tidak** ikut tersalin. `id` ikut tersalin — ganti agar tidak dobel.

**Biasanya digabungkan dengan:** `<template>` dan daftar berulang.

## replaceChildren

**Untuk apa:** mengganti semua anak sekaligus.

```js
ul.replaceChildren(); // kosongkan
ul.replaceChildren(li1, li2);
```

Lebih jelas daripada `innerHTML = ""` + append berulang jika kamu sudah punya node.

**Biasanya digabungkan dengan:** render ulang daftar dari data.

## innerHTML

**Untuk apa:** membaca/menulis HTML dalam elemen.

```js
panel.innerHTML = "<p>Kosong</p>";
```

**Bahaya:** teks dari pengguna atau API yang tidak dipercaya bisa jadi skrip (XSS). Jangan menempelkan input mentah.

Untuk teks:

```js
panel.textContent = inputPengguna.value;
```

Membaca `innerHTML` memberi markup serialisasi, bukan selalu identik dengan sumber.

Menulis `innerHTML` merusak listener anak lama.

**Biasanya digabungkan dengan:** markup yang kamu tulis sendiri, tetap. Bukan komentar pengguna.

## outerHTML

**Untuk apa:** HTML elemen termasuk tagnya. Menulis `outerHTML` mengganti elemen itu.

```js
console.log(kartu.outerHTML);
```

Setelah di-set, variabel lama bisa merujuk node yang sudah terlepas.

**Biasanya digabungkan dengan:** debug markup. Untuk ganti, `replaceWith` lebih aman.

## textContent

**Untuk apa:** semua teks di dalam, termasuk yang tersembunyi, tanpa HTML.

```js
judul.textContent = "Toko Belajar";
console.log(kartu.textContent.trim());
```

Aman untuk data pengguna. Mengganti `textContent` membuang anak-anak.

**Biasanya digabungkan dengan:** label, pesan error, dan pencarian teks kartu.

## innerText

**Untuk apa:** teks kira-kira seperti yang terlihat, memperhatikan CSS.

```js
el.innerText;
```

Lebih mahal (layout). `hidden` tidak ikut. Untuk data, `textContent` lebih prediktabel.

**Biasanya digabungkan dengan:** salin teks yang terlihat. Hindari di loop besar.

## insertAdjacentHTML

**Untuk apa:** menyisipkan potongan HTML di posisi tertentu.

```js
el.insertAdjacentHTML("beforeend", "<li>Buku</li>");
```

Posisi: `beforebegin`, `afterbegin`, `beforeend`, `afterend`. Risiko XSS sama dengan `innerHTML`.

**Biasanya digabungkan dengan:** markup tepercaya. Untuk data, `createElement` + `textContent`.

## insertAdjacentElement

**Untuk apa:** menyisipkan elemen yang sudah ada.

```js
el.insertAdjacentElement("afterend", catatan);
```

**Biasanya digabungkan dengan:** `createElement` tanpa innerHTML.

## className

**Untuk apa:** seluruh atribut `class` sebagai satu string.

```js
el.className = "kartu aktif";
```

Menimpa semua kelas. Untuk menambah satu kelas, `classList.add`.

**Biasanya digabungkan dengan:** reset kelas ke set yang diketahui.

## classList.add

**Untuk apa:** menambah satu atau lebih kelas, tanpa duplikat.

```js
tombol.classList.add("aktif");
kartu.classList.add("kartu", "kartu--promo");
```

Tidak error jika sudah ada.

**Biasanya digabungkan dengan:** state UI, Tailwind/kelas BEM, dan event.

## classList.remove

**Untuk apa:** membuang kelas. Aman jika tidak ada.

```js
tombol.classList.remove("aktif");
```

**Biasanya digabungkan dengan:** menutup menu dan menonaktifkan tab.

## classList.toggle

**Untuk apa:** menambah jika belum ada, membuang jika ada. Boleh dipaksa.

```js
menu.classList.toggle("terbuka");
menu.classList.toggle("terbuka", harusBuka); // boolean paksa
```

Mengembalikan `true` jika kelas ada setelah panggilan.

**Biasanya digabungkan dengan:** accordion, dark mode, dan favorit.

## classList.contains

**Untuk apa:** cek kelas.

```js
if (menu.classList.contains("terbuka")) {
  console.log("Menu terbuka");
}
```

**Biasanya digabungkan dengan:** `if` sebelum animasi atau `aria`.

## classList.replace

**Untuk apa:** ganti satu kelas dengan yang lain. `false` jika sumber tidak ada.

```js
badge.classList.replace("stok-ada", "stok-habis");
```

**Biasanya digabungkan dengan:** status yang saling meniadakan.

## dataset

**Untuk apa:** membaca/menulis atribut `data-*` sebagai object.

```html
<button data-id="17" data-nama-produk="Buku">Tambah</button>
```

```js
tombol.dataset.id; // "17"  selalu string
tombol.dataset.namaProduk; // "Buku"
tombol.dataset.id = "18";
delete tombol.dataset.id;
```

Nama: `data-nama-produk` → `dataset.namaProduk` (camelCase).

Jangan simpan object; stringify jika perlu, atau pakai id lalu cari di array.

**Biasanya digabungkan dengan:** delegation, `JSON` data halaman, dan `find`.

## getAttribute

**Untuk apa:** nilai atribut mentah, atau `null`.

```js
tautan.getAttribute("href");
input.getAttribute("type");
```

Beberapa properti elemen sudah tercermin (`href` lengkap vs atribut relatif). `getAttribute` memberi apa yang tertulis di HTML.

**Biasanya digabungkan dengan:** atribut kustom dan debug.

## setAttribute

**Untuk apa:** menulis atribut.

```js
img.setAttribute("alt", "Sampul buku");
tombol.setAttribute("aria-expanded", "true");
```

Boolean HTML: ada/tidak ada. Untuk `disabled`, properti `el.disabled = true` lebih wajar.

**Biasanya digabungkan dengan:** a11y, `src`, dan `href`.

## removeAttribute

**Untuk apa:** menghapus atribut.

```js
input.removeAttribute("disabled");
```

**Biasanya digabungkan dengan:** mengaktifkan tombol dan membersihkan `aria`.

## hasAttribute

**Untuk apa:** apakah atribut tertulis.

```js
input.hasAttribute("required");
```

**Biasanya digabungkan dengan:** cabang validasi.

## toggleAttribute

**Untuk apa:** menambah/membuang atribut boolean.

```js
tombol.toggleAttribute("disabled", true);
```

**Biasanya digabungkan dengan:** state loading.

## style

**Untuk apa:** inline style.

```js
el.style.display = "none";
el.style.backgroundColor = "#0f766e";
el.style.setProperty("--harga", "45000");
el.style.removeProperty("display");
```

Nama CSS `background-color` menjadi `backgroundColor`. Variabel CSS pakai `setProperty`.

Jangan mengatur semua tampilan dari JS. Lebih baik kelas CSS.

**Biasanya digabungkan dengan:** posisi pointer, tinggi dinamis, dan custom property.

## getComputedStyle

**Untuk apa:** nilai CSS akhir setelah stylesheet.

```js
const gaya = getComputedStyle(el);
gaya.display;
gaya.getPropertyValue("color");
```

Hanya baca. Mengubah object ini tidak mengubah halaman.

**Biasanya digabungkan dengan:** ukur layout dan debug.

## hidden

**Untuk apa:** properti yang memetakan atribut `hidden`.

```js
panel.hidden = true;
panel.hidden = false;
```

Lebih jelas daripada `style.display` untuk buka/tutup.

**Biasanya digabungkan dengan:** modal, pesan kosong, dan tab.

## parentElement / parentNode

**Untuk apa:** naik satu tingkat.

```js
el.parentElement; // elemen atau null
el.parentNode; // bisa Document
```

**Biasanya digabungkan dengan:** `closest` (lebih kuat) dan traversal.

## children / childNodes

**Untuk apa:** anak-anak.

```js
ul.children; // hanya elemen
ul.childNodes; // termasuk teks/spasi
```

`children` biasanya yang diinginkan.

```js
[...ul.children].forEach((li) => console.log(li.textContent));
```

**Biasanya digabungkan dengan:** hitung kartu dan kosongkan daftar.

## firstElementChild / lastElementChild

**Untuk apa:** anak elemen pertama/terakhir.

```js
ul.firstElementChild;
ul.lastElementChild;
```

Ada juga `firstChild` yang bisa node teks kosong.

**Biasanya digabungkan dengan:** fokus item pertama dan hapus terakhir.

## nextElementSibling / previousElementSibling

**Untuk apa:** saudara elemen.

```js
li.nextElementSibling;
li.previousElementSibling;
```

**Biasanya digabungkan dengan:** keyboard naik/turun daftar.

## document.documentElement / body / head

**Untuk apa:** node utama.

```js
document.documentElement.classList.toggle("gelap");
document.body.append(toast);
document.head.append(tautanCss);
```

**Biasanya digabungkan dengan:** tema, portal toast, dan meta dinamis.

## template dan importNode

**Untuk apa:** markup cetakan yang tidak dirender.

```html
<template id="tpl-kartu">
  <li class="kartu"><span class="nama"></span></li>
</template>
```

```js
const tpl = document.getElementById("tpl-kartu");
const node = tpl.content.cloneNode(true);
node.querySelector(".nama").textContent = "Buku";
ul.append(node);
```

`importNode` untuk node dari dokumen lain. Di halaman sama, `cloneNode` pada `content` cukup.

**Biasanya digabungkan dengan:** daftar produk tanpa `innerHTML` string.

## Pola render daftar

**Untuk apa:** data → DOM tanpa XSS.

```js
function renderProduk(daftar, root) {
  const frag = document.createDocumentFragment();
  for (const item of daftar) {
    const li = document.createElement("li");
    li.className = "kartu";
    li.dataset.id = String(item.id);
    li.textContent = `${item.nama} — ${item.harga}`;
    frag.append(li);
  }
  root.replaceChildren(frag);
}
```

`DocumentFragment` menampung dulu agar halaman tidak di-reflow per item.

**Biasanya digabungkan dengan:** `filter`/`map` data dan event delegation.

## Kesalahan DOM yang sering

- Memakai elemen sebelum ada (`null`).
- `innerHTML` + teks pengguna.
- Mengira `NodeList` punya semua method array.
- Loop koleksi hidup sambil menghapus.
- Duplikat `id` setelah `cloneNode`.
- Mengatur tampilan lewat `style` padahal kelas cukup.
- Lupa `dataset` selalu string (`dataset.id + 1` jadi `"171"`).

**Biasanya digabungkan dengan:** `Number(el.dataset.id)` dan file 09.
