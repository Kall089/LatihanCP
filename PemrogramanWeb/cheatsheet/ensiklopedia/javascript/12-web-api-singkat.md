# 12 — Web API singkat

[← 11 Module](11-module-timer-console.md) · [Indeks](README.md) · [Lanjut 13 →](13-resep-dan-kesalahan.md)

Selain DOM dan `fetch`, browser menyediakan objek siap pakai. Di bawah: `URL`, `URLSearchParams`, `AbortController`, `IntersectionObserver`, `matchMedia`, `crypto.randomUUID`, plus API tetangga yang sering ketemu.

## Daftar isi

- [URL](#url)
- [URL.origin / protocol / host](#urlorigin--protocol--host)
- [URL.pathname](#urlpathname)
- [URL.search / searchParams](#urlsearch--searchparams)
- [URL.hash](#urlhash)
- [URL.href](#urlhref)
- [URL.toString / toJSON](#urltostring--tojson)
- [new URL relatif](#new-url-relatif)
- [URL.canParse](#urlcanparse)
- [URL.parse](#urlparse)
- [URL.createObjectURL](#urlcreateobjecturl)
- [URL.revokeObjectURL](#urlrevokeobjecturl)
- [URLSearchParams](#urlsearchparams)
- [get / getAll / has](#get--getall--has)
- [set / append / delete](#set--append--delete)
- [keys / values / entries](#keys--values--entries)
- [sort dan toString](#sort-dan-tostring)
- [AbortController](#abortcontroller)
- [AbortSignal](#abortsignal)
- [AbortSignal.timeout](#abortsignaltimeout)
- [AbortSignal.any](#abortsignalany)
- [IntersectionObserver](#intersectionobserver)
- [unobserve / disconnect](#unobserve--disconnect)
- [matchMedia](#matchmedia)
- [MediaQueryList.onchange](#mediaquerylistonchange)
- [crypto.randomUUID](#cryptorandomuuid)
- [crypto.getRandomValues](#cryptogetrandomvalues)
- [location](#location)
- [history](#history)
- [navigator](#navigator)
- [structuredClone](#structuredclone-ulang)
- [ResizeObserver](#resizeobserver)
- [MutationObserver](#mutationobserver)
- [performance.now](#performancenow)
- [queue](#queue)

## URL

**Untuk apa:** membedah dan merakit alamat.

```js
const u = new URL("https://toko.test/produk?q=buku#detail");
```

Jika string tidak valid, `TypeError`. Untuk input pengguna, bungkus `try` atau pakai `URL.canParse`.

**Biasanya digabungkan dengan:** `searchParams`, `fetch`, dan tautan dinamis.

## URL.origin / protocol / host

**Untuk apa:** bagian situs.

```js
u.protocol; // "https:"
u.host; // "toko.test" atau host:port
u.hostname;
u.port;
u.origin; // "https://toko.test"
```

`origin` berguna membandingkan tautan internal vs eksternal.

```js
const internal = new URL(href, location.href).origin === location.origin;
```

**Biasanya digabungkan dengan:** filter tautan dan keamanan rel.

## URL.pathname

**Untuk apa:** jalur setelah host.

```js
u.pathname; // "/produk"
u.pathname = "/keranjang";
```

Tidak termasuk query dan hash. Segmen:

```js
u.pathname.split("/").filter(Boolean);
```

**Biasanya digabungkan dengan:** routing sederhana tanpa framework.

## URL.search / searchParams

**Untuk apa:** query string dan objek parameternya.

```js
u.search; // "?q=buku"
u.searchParams.get("q"); // "buku"
u.searchParams.set("halaman", "2");
```

Mengubah `searchParams` memperbarui `search` dan `href`.

**Biasanya digabungkan dengan:** filter halaman dan `history.replaceState`.

## URL.hash

**Untuk apa:** bagian `#...`.

```js
u.hash; // "#detail"
u.hash = "ulasan";
```

Perubahan hash di halaman saat ini tidak me-reload. Event `hashchange`.

**Biasanya digabungkan dengan:** tab dalam halaman dan tautan heading.

## URL.href

**Untuk apa:** URL lengkap sebagai string.

```js
u.href;
```

Bisa di-set untuk mengganti semua bagian.

**Biasanya digabungkan dengan:** `fetch(u.href)` dan `a.href`.

## URL.toString / toJSON

**Untuk apa:** menghasilkan string URL.

```js
String(u);
u.toString();
JSON.stringify({ next: u }); // href
```

**Biasanya digabungkan dengan:** template tautan.

## new URL relatif

**Untuk apa:** menyelesaikan jalur relatif terhadap basis.

```js
new URL("/api/produk", "https://toko.test/app/");
new URL("../aset/logo.svg", import.meta.url);
new URL("?q=buku", location.href);
```

Argumen kedua wajib jika yang pertama relatif. Tanpa basis, relatif → error.

**Biasanya digabungkan dengan:** `import.meta.url` dan merakit API.

## URL.canParse

**Untuk apa:** cek valid tanpa `try`. Browser modern.

```js
URL.canParse(teks, location.href);
```

**Biasanya digabungkan dengan:** validasi field URL.

## URL.parse

**Untuk apa:** seperti `new URL` tetapi mengembalikan `null` jika gagal, bukan throw. Browser sangat baru.

```js
const u = URL.parse(teks, location.href);
if (!u) {
  console.log("URL tidak valid");
}
```

Cadangan: `try { new URL(...) } catch`.

**Biasanya digabungkan dengan:** input pengguna.

## URL.createObjectURL

**Untuk apa:** membuat URL sementara untuk `Blob`/`File`.

```js
const url = URL.createObjectURL(berkas);
img.src = url;
```

Setiap panggilan mengalokasi. Cabut jika tidak dipakai.

**Biasanya digabungkan dengan:** input file dan unduhan blob `fetch`.

## URL.revokeObjectURL

**Untuk apa:** membebaskan URL object.

```js
img.onload = () => URL.revokeObjectURL(url);
```

**Biasanya digabungkan dengan:** pratinjau gambar.

## URLSearchParams

**Untuk apa:** membaca/menulis `?a=1&b=2` tanpa merangkai manual.

```js
const p = new URLSearchParams("q=buku&halaman=1");
const dariObject = new URLSearchParams({ q: "buku", halaman: "1" });
const dariForm = new URLSearchParams(new FormData(form));
```

Nilai diubah ke string. `undefined` menjadi teks `"undefined"` jika kamu set ceroboh — filter dulu.

**Biasanya digabungkan dengan:** `fetch` GET, `location.search`, form.

## get / getAll / has

**Untuk apa:** membaca parameter.

```js
p.get("q"); // string atau null
p.getAll("tag"); // array
p.has("q");
p.has("halaman", "2"); // nilai spesifik, browser modern
```

Kunci tanpa nilai: `?flag=` → `""`. Kunci tidak ada → `null`.

**Biasanya digabungkan dengan:** `??` default halaman.

## set / append / delete

**Untuk apa:** menulis parameter.

```js
p.set("q", "pensil"); // ganti semua q
p.append("tag", "alat"); // tambah
p.delete("tag");
p.delete("tag", "alat"); // hapus nilai tertentu (modern)
```

`set` menimpa; `append` menumpuk kunci sama.

**Biasanya digabungkan dengan:** checkbox banyak nilai dan ganti halaman.

## keys / values / entries

**Untuk apa:** iterasi.

```js
for (const [kunci, nilai] of p.entries()) {
  console.log(kunci, nilai);
}
Object.fromEntries(p);
```

`fromEntries` kehilangan duplikat kunci (sisakan terakhir).

**Biasanya digabungkan dengan:** debug dan object filter.

## sort dan toString

**Untuk apa:** mengurutkan kunci dan menghasilkan query tanpa `?`.

```js
p.sort();
p.toString(); // "halaman=1&q=buku"
```

Tempel:

```js
const url = `${location.pathname}?${p}`;
```

Atau `u.search = p.toString()`.

**Biasanya digabungkan dengan:** URL kanonik dan banding query.

## AbortController

**Untuk apa:** tombol batal yang bisa dibagikan ke `fetch` dan listener.

```js
const ac = new AbortController();
fetch("/api/produk", { signal: ac.signal });
ac.abort("ganti query");
```

Setelah abort, signal tidak bisa dipakai ulang untuk hidup lagi. Buat controller baru.

`abort()` berulang aman.

**Biasanya digabungkan dengan:** search hidup, ganti halaman, file 09 `signal`.

## AbortSignal

**Untuk apa:** sinyal yang didengar operasi async.

```js
ac.signal.aborted; // boolean
ac.signal.reason;
ac.signal.addEventListener("abort", () => {
  console.log("dibatalkan");
});
```

Jangan fetch jika sudah aborted:

```js
if (signal.aborted) {
  return;
}
```

**Biasanya digabungkan dengan:** `fetch` dan event.

## AbortSignal.timeout

**Untuk apa:** signal yang auto-abort setelah ms.

```js
await fetch("/api/produk", { signal: AbortSignal.timeout(5000) });
```

Error nama biasanya `TimeoutError` atau `AbortError` tergantung lingkungan.

**Biasanya digabungkan dengan:** batas waktu jaringan.

## AbortSignal.any

**Untuk apa:** gabung beberapa signal. Abort jika salah satu abort. Modern.

```js
const gabung = AbortSignal.any([ac.signal, AbortSignal.timeout(8000)]);
await fetch(url, { signal: gabung });
```

**Biasanya digabungkan dengan:** timeout + batal pengguna.

## IntersectionObserver

**Untuk apa:** tahu kapan elemen masuk/keluar area tampak (atau kontainer).

```js
const io = new IntersectionObserver(
  (entries) => {
    for (const entry of entries) {
      if (entry.isIntersecting) {
        muatGambar(entry.target);
        io.unobserve(entry.target);
      }
    }
  },
  { root: null, rootMargin: "200px", threshold: 0.25 },
);

gambar.forEach((img) => io.observe(img));
```

`entry.intersectionRatio` 0–1. `root: null` = viewport.

Menggantikan cek `scroll` + `getBoundingClientRect` yang boros.

**Biasanya digabungkan dengan:** lazy image, infinite scroll, animasi masuk.

## unobserve / disconnect

**Untuk apa:** berhenti mengamati satu atau semua.

```js
io.unobserve(el);
io.disconnect();
```

Setelah lazy load, `unobserve` agar callback tidak berulang sia-sia.

**Biasanya digabungkan dengan:** teardown halaman.

## matchMedia

**Untuk apa:** menanyakan media query CSS dari JS.

```js
const mql = window.matchMedia("(min-width: 768px)");
if (mql.matches) {
  console.log("layar sedang/lebar");
}
```

Jangan hanya cek `innerWidth` jika kamu ingin sinkron dengan CSS.

**Biasanya digabungkan dengan:** pindah carousel ↔ daftar dan `classList`.

## MediaQueryList.onchange

**Untuk apa:** mendengar perubahan query (resize, zoom, orientasi).

```js
mql.addEventListener("change", (event) => {
  console.log(event.matches);
});
```

Cara lama `addListener` usang.

**Biasanya digabungkan dengan:** layout responsif di JS dan `matchMedia`.

## crypto.randomUUID

**Untuk apa:** string UUID v4 acak, cukup unik untuk id klien.

```js
const id = crypto.randomUUID();
// "3f1c0a2e-...."
```

Pakai untuk kunci item lokal, id permintaan, bukan sebagai rahasia otentikasi semata.

Tersedia di konteks aman (`https` atau `localhost`).

**Biasanya digabungkan dengan:** item keranjang lokal dan kunci React/`data-id`.

## crypto.getRandomValues

**Untuk apa:** mengisi array integer dengan byte kriptografis.

```js
const buf = new Uint32Array(1);
crypto.getRandomValues(buf);
const dadu = (buf[0] % 6) + 1; // bias modulo: cukup untuk UI, bukan kriptografi ketat
```

Lebih baik daripada `Math.random` untuk token. Untuk UUID, `randomUUID` lebih langsung.

**Biasanya digabungkan dengan:** token CSRF klien (tetap pikirkan model ancaman) dan undian.

## location

**Untuk apa:** URL halaman saat ini.

```js
location.href;
location.pathname;
location.search;
location.hash;
location.origin;
location.assign("/keranjang");
location.replace("/login"); // tanpa entri history
location.reload();
```

`assign` bisa kembali lewat tombol back. `replace` menimpa entri.

Membaca query:

```js
const q = new URLSearchParams(location.search).get("q") ?? "";
```

**Biasanya digabungkan dengan:** `URLSearchParams` dan sinkron filter ke URL.

## history

**Untuk apa:** menumpuk entri tanpa reload penuh.

```js
history.pushState({ q: "buku" }, "", "?q=buku");
history.replaceState({ q: "buku" }, "", "?q=buku");
history.back();
history.forward();
```

Argumen state bisa dibaca di `popstate`. Judul (argumen kedua) diabaikan banyak browser.

```js
window.addEventListener("popstate", (event) => {
  terapkanState(event.state);
});
```

Ini dasar routing klien. Next.js menyembunyikannya.

**Biasanya digabungkan dengan:** filter yang bisa di-bookmark dan tombol back.

## navigator

**Untuk apa:** info lingkungan.

```js
navigator.userAgent;
navigator.language;
navigator.languages;
navigator.onLine;
navigator.clipboard.writeText("teks"); // perlu izin/konteks aman
```

`onLine` tidak selalu berarti internet benar-benar ada.

Jangan mengandalkan `userAgent` untuk fitur; cek API-nya (`if (navigator.clipboard)`).

**Biasanya digabungkan dengan:** salin kode promo dan pesan offline.

## structuredClone (ulang)

**Untuk apa:** salin dalam data terstruktur. Sudah di file 04; sering dianggap Web API.

```js
const salinan = structuredClone(keranjang);
```

**Biasanya digabungkan dengan:** undo dan worker (bukan topik ini).

## ResizeObserver

**Untuk apa:** tahu elemen berubah ukuran.

```js
const ro = new ResizeObserver((entries) => {
  for (const entry of entries) {
    const lebar = entry.contentRect.width;
    el.dataset.lebar = lebar > 400 ? "lebar" : "sempit";
  }
});
ro.observe(panel);
```

Lebih tepat daripada `window.resize` untuk kartu/sidebar.

**Biasanya digabungkan dengan:** `classList` dan chart yang menyesuaikan.

## MutationObserver

**Untuk apa:** mendengar perubahan pohon DOM.

```js
const mo = new MutationObserver((mutations) => {
  for (const m of mutations) {
    console.log(m.type, m.addedNodes);
  }
});
mo.observe(daftar, { childList: true, subtree: true });
```

Berat jika disalahgunakan. Untuk UI yang kamu kendalikan, lebih baik panggil fungsi setelah render.

**Biasanya digabungkan dengan:** integrasi widget pihak ketiga.

## performance.now

**Untuk apa:** timestamp beresolusi tinggi sejak halaman dimuat, tidak terpengaruh jam sistem.

```js
const t0 = performance.now();
kerja();
console.log(performance.now() - t0);
```

Lebih cocok ukur durasi daripada `Date.now` untuk animasi.

**Biasanya digabungkan dengan:** debug performa dan `requestAnimationFrame`.

## queue

**Untuk apa:** menunda ke macrotask.

```js
setTimeout(() => {}, 0);
```

Sudah dibahas di file 11. Disebut di sini karena sering dibanding `queueMicrotask`.

**Biasanya digabungkan dengan:** lulus tick agar layout sempat dihitung.

## pola filter ke URL

**Untuk apa:** search bisa di-refresh dan dibagikan.

```js
function tulisQuery(q) {
  const u = new URL(location.href);
  if (q) {
    u.searchParams.set("q", q);
  } else {
    u.searchParams.delete("q");
  }
  history.replaceState(null, "", u);
}

function bacaQuery() {
  return new URLSearchParams(location.search).get("q") ?? "";
}
```

**Biasanya digabungkan dengan:** input cari, `filter`, file 09.

## pola lazy gambar

**Untuk apa:** `data-src` jadi `src` saat mendekati viewport.

```js
const io = new IntersectionObserver((entries, obs) => {
  for (const entry of entries) {
    if (!entry.isIntersecting) {
      continue;
    }
    const img = entry.target;
    img.src = img.dataset.src;
    obs.unobserve(img);
  }
});
```

Alternatif modern: atribut HTML `loading="lazy"`. Observer tetap berguna untuk konten non-img.

**Biasanya digabungkan dengan:** `dataset` dan daftar panjang.

## Kesalahan Web API yang sering

- `new URL(relatif)` tanpa basis.
- Merangkai query dengan string mentah.
- Memakai ulang AbortController yang sudah abort.
- Lupa `unobserve`/`disconnect`.
- `matchMedia` dicek sekali, tidak mendengar `change`.
- `createObjectURL` tanpa `revoke`.
- `Math.random` untuk id yang dikira unik aman.
- `pushState` tanpa mendengar `popstate` (tombol back rusak).

**Biasanya digabungkan dengan:** file 10 dan 13.
