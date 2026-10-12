# 10 — Fetch, async, dan storage

[← 09 Event](09-event-form-delegation.md) · [Indeks](README.md) · [Lanjut 11 →](11-module-timer-console.md)

`fetch` meminta data ke jaringan. Storage menyimpan string di browser. Keduanya sering gagal: bungkus dengan `try/catch` dan cek status.

## Daftar isi

- [fetch GET](#fetch-get)
- [respons.ok dan status](#responsok-dan-status)
- [respons.json](#responsjson)
- [respons.text](#responstext)
- [respons.blob](#responsblob)
- [respons.arrayBuffer](#responsarraybuffer)
- [respons.formData](#responsformdata)
- [respons.headers](#responsheaders)
- [respons.clone](#responsclone)
- [fetch POST JSON](#fetch-post-json)
- [fetch POST FormData](#fetch-post-formdata)
- [fetch PUT / PATCH / DELETE](#fetch-put--patch--delete)
- [Headers](#headers)
- [credentials](#credentials)
- [mode dan cors singkat](#mode-dan-cors-singkat)
- [cache opsi fetch](#cache-opsi-fetch)
- [AbortSignal dengan fetch](#abortsignal-dengan-fetch)
- [timeout fetch](#timeout-fetch)
- [query string](#query-string)
- [error jaringan vs HTTP](#error-jaringan-vs-http)
- [async helper](#async-helper)
- [localStorage](#localstorage)
- [sessionStorage](#sessionstorage)
- [StorageEvent](#storageevent)
- [kuota dan pengecualian storage](#kuota-dan-pengecualian-storage)
- [cookie singkat](#cookie-singkat)
- [indexedDB sangat singkat](#indexeddb-sangat-singkat)

## fetch GET

**Untuk apa:** mengambil sumber daya. Default method `GET`.

```js
const respons = await fetch("/api/produk");
const data = await respons.json();
```

URL relatif terhadap halaman. URL mutlak untuk domain lain (perlu CORS).

`fetch` mengembalikan Promise. Di event handler:

```js
tombol.addEventListener("click", async () => {
  try {
    const respons = await fetch("/api/produk");
    if (!respons.ok) {
      throw new Error(`HTTP ${respons.status}`);
    }
    const data = await respons.json();
    render(data);
  } catch (error) {
    pesan.textContent = error.message;
  }
});
```

**Biasanya digabungkan dengan:** `async/await`, `try/catch`, dan render DOM.

## respons.ok dan status

**Untuk apa:** mengetahui hasil HTTP. `ok` true untuk 200–299.

```js
respons.ok;
respons.status; // 200, 404, 500
respons.statusText;
respons.redirected;
respons.url; // URL akhir setelah redirect
respons.type;
```

**Penting:** `404` dan `500` **tidak** melempar. Hanya kegagalan jaringan, abort, atau URL salah yang reject.

```js
if (!respons.ok) {
  const teks = await respons.text();
  throw new Error(teks || `HTTP ${respons.status}`);
}
```

**Biasanya digabungkan dengan:** pesan error pengguna dan cabang login `401`.

## respons.json

**Untuk apa:** membaca body sebagai JSON (sudah `JSON.parse`).

```js
const data = await respons.json();
```

Body hanya bisa dibaca sekali. Jika JSON rusak, melempar. Jika status error tetap `json()`, bisa gagal jika body kosong.

```js
async function bacaJsonAman(respons) {
  const teks = await respons.text();
  if (!teks) {
    return null;
  }
  return JSON.parse(teks);
}
```

**Biasanya digabungkan dengan:** API Laravel/Next dan `Array.isArray` guard.

## respons.text

**Untuk apa:** body sebagai string.

```js
const html = await respons.text();
```

Cocok HTML/CSV/plain. Untuk JSON, `json()` lebih langsung.

**Biasanya digabungkan dengan:** debug body error dan unduhan teks.

## respons.blob

**Untuk apa:** body sebagai `Blob` (berkas di memori).

```js
const blob = await respons.blob();
const url = URL.createObjectURL(blob);
tautan.download = "daftar.csv";
tautan.href = url;
```

**Biasanya digabungkan dengan:** unduh file dan pratinjau gambar.

## respons.arrayBuffer

**Untuk apa:** byte mentah.

```js
const buf = await respons.arrayBuffer();
```

Untuk file biner atau WebCrypto. Jarang di toko kuliah.

**Biasanya digabungkan dengan:** pemrosesan biner.

## respons.formData

**Untuk apa:** membaca body `multipart/form-data`.

```js
const data = await respons.formData();
```

Jarang dari API JSON. Lebih sering kamu **mengirim** FormData.

**Biasanya digabungkan dengan:** endpoint khusus.

## respons.headers

**Untuk apa:** membaca header respons.

```js
respons.headers.get("content-type");
respons.headers.get("x-total-count");
respons.headers.has("etag");
```

Header tertentu disembunyikan CORS kecuali diizinkan server.

**Biasanya digabungkan dengan:** paginasi lewat header dan cek `json`.

## respons.clone

**Untuk apa:** menyalin respons agar body bisa dibaca dua kali.

```js
const salinan = respons.clone();
const sebagaiTeks = await salinan.text();
const sebagaiJson = await respons.json();
```

Berguna debug atau cache.

**Biasanya digabungkan dengan:** service worker / cache. Di tugas kecil, baca sekali.

## fetch POST JSON

**Untuk apa:** mengirim object sebagai JSON.

```js
const respons = await fetch("/api/produk", {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ nama: "Buku", harga: 45000 }),
});
```

Tanpa `JSON.stringify`, body bukan JSON valid. Tanpa header, server mungkin tidak membaca sebagai JSON.

**Biasanya digabungkan dengan:** form JS, validasi, Laravel API.

## fetch POST FormData

**Untuk apa:** mengirim field dan berkas seperti form HTML.

```js
const data = new FormData(form);
const respons = await fetch("/api/pesan", {
  method: "POST",
  body: data,
});
```

Jangan set `Content-Type` sendiri.

**Biasanya digabungkan dengan:** upload dan field campuran.

## fetch PUT / PATCH / DELETE

**Untuk apa:** memperbarui atau menghapus di API REST.

```js
await fetch(`/api/produk/${id}`, {
  method: "PUT",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify(produk),
});

await fetch(`/api/produk/${id}`, { method: "PATCH", body: JSON.stringify({ harga }) });

await fetch(`/api/produk/${id}`, { method: "DELETE" });
```

`PATCH` sebagian; `PUT` biasanya utuh. Ikuti kontrak server.

**Biasanya digabungkan dengan:** halaman admin dan `csrf`/`credentials` jika perlu.

## Headers

**Untuk apa:** merakit header terpisah.

```js
const headers = new Headers();
headers.set("Accept", "application/json");
headers.set("X-Requested-With", "fetch");
headers.append("X-Custom", "a");
headers.get("Accept");
headers.delete("X-Custom");
```

Bisa juga object biasa di opsi `fetch`. `Headers` berguna jika dibangun bersyarat.

**Biasanya digabungkan dengan:** token (hati-hati XSS) dan API version.

## credentials

**Untuk apa:** mengirim cookie pada request.

```js
await fetch("/api/saya", { credentials: "include" });
```

Nilai: `omit`, `same-origin` (sering default), `include` (lintas origin + CORS credentials).

Server harus mengizinkan credentials. Jangan menggabungkan `*` ACAO dengan credentials.

**Biasanya digabungkan dengan:** sesi login cookie, bukan localStorage token (beda pola).

## mode dan cors singkat

**Untuk apa:** mengatur aturan lintas origin.

```js
await fetch(url, { mode: "cors" });
```

Browser memblokir baca respons lintas origin jika server tidak mengirim header CORS. Error yang terlihat: gagal jaringan / blocked, bukan JSON 403 yang kamu harapkan.

`mode: "no-cors"` memberi respons opaque yang hampir tidak bisa dibaca — hampir tidak berguna untuk API JSON.

**Biasanya digabungkan dengan:** backend Laravel CORS dan URL yang benar.

## cache opsi fetch

**Untuk apa:** memengaruhi cache HTTP.

```js
await fetch("/api/produk", { cache: "no-store" });
```

Nilai yang sering: `default`, `reload`, `no-store`, `force-cache`.

**Biasanya digabungkan dengan:** data yang harus selalu baru.

## AbortSignal dengan fetch

**Untuk apa:** membatalkan request.

```js
const ac = new AbortController();
const janji = fetch("/api/produk", { signal: ac.signal });
ac.abort();
```

Request yang di-abort menolak dengan error `AbortError`. Jangan tampilkan sebagai kegagalan jaringan jika pengguna pindah halaman.

```js
try {
  await fetch(url, { signal });
} catch (error) {
  if (error.name === "AbortError") {
    return;
  }
  throw error;
}
```

Detail `AbortController` di [file 12](12-web-api-singkat.md).

**Biasanya digabungkan dengan:** ganti query search dan unmount.

## timeout fetch

**Untuk apa:** membatasi waktu tunggu.

```js
const respons = await fetch("/api/produk", {
  signal: AbortSignal.timeout(8000),
});
```

`AbortSignal.timeout` di browser modern. Cadangan: `AbortController` + `setTimeout` + `abort`.

**Biasanya digabungkan dengan:** jaringan lambat dan UX loading.

## query string

**Untuk apa:** mengirim filter di URL GET.

```js
const params = new URLSearchParams({ q: "buku", halaman: "2" });
const respons = await fetch(`/api/produk?${params}`);
```

Jangan merangkai manual dengan `&` jika nilai bisa berisi karakter khusus. `URLSearchParams` meng-encode.

Lihat [file 12](12-web-api-singkat.md#urlsearchparams).

**Biasanya digabungkan dengan:** form cari dan `history.replaceState`.

## error jaringan vs HTTP

**Untuk apa:** membedakan dua jenis gagal.

```js
async function ambil(url) {
  let respons;
  try {
    respons = await fetch(url);
  } catch (error) {
    throw new Error("Jaringan bermasalah atau request dibatalkan");
  }
  if (!respons.ok) {
    throw new Error(`Server ${respons.status}`);
  }
  return respons.json();
}
```

Tampilkan pesan berbeda: offline vs “tidak ketemu”.

**Biasanya digabungkan dengan:** `navigator.onLine` (tidak selalu andal) dan UI toast.

## async helper

**Untuk apa:** satu fungsi yang dipakai banyak halaman.

```js
async function api(jalur, opsi = {}) {
  const respons = await fetch(jalur, {
    headers: { Accept: "application/json", ...opsi.headers },
    ...opsi,
  });
  if (!respons.ok) {
    throw new Error(`HTTP ${respons.status}`);
  }
  if (respons.status === 204) {
    return null;
  }
  return respons.json();
}
```

**Biasanya digabungkan dengan:** module file 11 dan REST CRUD.

## localStorage

**Untuk apa:** menyimpan string yang bertahan setelah tab ditutup, per origin.

```js
localStorage.setItem("keranjang", JSON.stringify(keranjang));
const mentah = localStorage.getItem("keranjang");
const keranjang = mentah ? JSON.parse(mentah) : [];
localStorage.removeItem("keranjang");
localStorage.clear();
localStorage.key(0);
localStorage.length;
```

Hanya string. Object harus di-JSON-kan. `getItem` yang tidak ada → `null`.

Tidak aman untuk sandi atau token sensitif (XSS bisa membaca). Kuota terbatas (~beberapa MB). Sinkron: jangan simpan data raksasa di path klik.

Private mode bisa melempar. Bungkus `try`.

```js
function bacaKeranjang() {
  try {
    const mentah = localStorage.getItem("keranjang");
    const data = mentah ? JSON.parse(mentah) : [];
    return Array.isArray(data) ? data : [];
  } catch {
    return [];
  }
}
```

**Biasanya digabungkan dengan:** `JSON`, keranjang, preferensi tema.

## sessionStorage

**Untuk apa:** seperti `localStorage`, tetapi hilang saat tab ditutup. Tiap tab punya salinan sendiri.

```js
sessionStorage.setItem("draft", teks);
sessionStorage.getItem("draft");
```

Cocok wizard form atau filter sementara di tab itu.

**Biasanya digabungkan dengan:** draf form dan langkah checkout.

## StorageEvent

**Untuk apa:** mendengar perubahan storage dari **tab lain** origin yang sama.

```js
window.addEventListener("storage", (event) => {
  if (event.key === "keranjang") {
    render(bacaKeranjang());
  }
});
```

Tidak terpicu di tab yang menulis. `event.newValue`, `event.oldValue` adalah string/null.

**Biasanya digabungkan dengan:** sinkron keranjang antar tab.

## kuota dan pengecualian storage

**Untuk apa:** menangani penuh atau diblokir.

```js
try {
  localStorage.setItem("x", teks);
} catch (error) {
  console.warn("Storage tidak tersedia", error);
}
```

`QuotaExceededError` jika penuh. Jangan diam-diam kehilangan data pengguna tanpa pesan.

**Biasanya digabungkan dengan:** `try/catch` dan cadangan memori saja.

## cookie singkat

**Untuk apa:** potongan kecil yang bisa dikirim otomatis ke server.

```js
document.cookie; // baca semua, string mentah
document.cookie = "tampilan=gelap; Path=/; Max-Age=31536000; SameSite=Lax";
```

API-nya canggung. Untuk data murni klien, `localStorage` lebih mudah. Cookie `HttpOnly` tidak terlihat di JS — itu bagus untuk sesi.

**Biasanya digabungkan dengan:** backend sesi. Jangan simpan data besar.

## indexedDB sangat singkat

**Untuk apa:** basis data klien untuk data lebih besar, async.

```js
// API verbose; biasanya lewat wrapper
```

Untuk tugas toko kuliah, `localStorage` + JSON hampir selalu cukup. IndexedDB jika butuh banyak record atau indeks.

**Biasanya digabungkan dengan:** aplikasi offline. Di luar cakupan katalog ini.

## pola loading UI

**Untuk apa:** menandai permintaan sedang jalan.

```js
async function muat() {
  tombol.disabled = true;
  status.textContent = "Memuat…";
  try {
    const data = await api("/api/produk");
    render(data);
    status.textContent = "";
  } catch (error) {
    status.textContent = error.message;
  } finally {
    tombol.disabled = false;
  }
}
```

**Biasanya digabungkan dengan:** `finally` file 07 dan `disabled` file 08.

## pola simpan keranjang

**Untuk apa:** data di memori + salinan storage.

```js
function simpanKeranjang(daftar) {
  try {
    localStorage.setItem("keranjang", JSON.stringify(daftar));
  } catch {
    console.warn("Tidak bisa menyimpan keranjang");
  }
}
```

Simpan setelah setiap perubahan, atau debounce jika sangat sering.

**Biasanya digabungkan dengan:** `reduce` total dan render.

## Kesalahan fetch/storage yang sering

- Tidak cek `respons.ok`.
- `await fetch` lalu `respons.json()` pada 500 HTML.
- Body JSON tanpa `stringify`.
- `Content-Type` salah pada FormData.
- CORS dikira bug JS.
- `localStorage` object tanpa JSON.
- Percaya storage selalu ada.
- Token rahasia di `localStorage`.
- Race: respons lama menimpa yang baru (abort request lama).

**Biasanya digabungkan dengan:** file 07, 12, 13.
