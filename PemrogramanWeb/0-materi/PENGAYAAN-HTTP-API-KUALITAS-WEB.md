# Pengayaan Web — HTTP, API, Async UI, dan Kualitas Produksi

Materi ini adalah jembatan setelah Modul 05–08. Proyek sebelumnya memakai data
lokal; aplikasi nyata sering menunggu server, menerima kegagalan jaringan, dan
harus tetap dapat dipakai pada setiap keadaan.

## Capaian pembelajaran

Setelah materi ini, kamu mampu:

- menjelaskan alur request/response dan arti kelompok status HTTP;
- memakai `fetch` + `async/await` dengan pemeriksaan `response.ok`;
- merancang UI untuk loading, error, empty, dan success;
- membedakan error jaringan, error HTTP, dan error parsing/data;
- menjelaskan same-origin, CORS, dan batas validasi di client;
- mencegah XSS dasar saat menampilkan data;
- memeriksa aksesibilitas, performa, dan kualitas sebelum deploy.

## 1. Model mental HTTP

```text
Browser                         Server/API
   │  GET /api/produk              │
   │  Accept: application/json     │
   ├──────────────────────────────▶│
   │                               │ cari/olah data
   │  200 OK                       │
   │  Content-Type: application/json
   │  [{"id":1,"nama":"Kopi"}]  │
   │◀──────────────────────────────┤
```

Request membawa method, URL, header, dan kadang body. Response membawa status,
header, dan body.

| Method | Maksud umum | Contoh |
|---|---|---|
| `GET` | membaca | daftar produk |
| `POST` | membuat/proses baru | membuat pesanan |
| `PUT`/`PATCH` | mengganti/memperbarui | mengubah profil |
| `DELETE` | menghapus | menghapus item |

Kelompok status yang wajib dikenali:

- `2xx`: request diproses berhasil;
- `4xx`: request client bermasalah, misalnya `400`, `401`, `403`, `404`;
- `5xx`: server gagal memproses request;
- kegagalan DNS/offline/timeout: tidak ada response HTTP sama sekali.

## 2. `fetch` yang benar

`fetch` hanya menolak Promise pada kegagalan jaringan tertentu. Response `404`
atau `500` tetap harus diperiksa sendiri.

```js
async function ambilProduk() {
  const response = await fetch("/api/produk");

  if (!response.ok) {
    throw new Error(`HTTP ${response.status}`);
  }

  const data = await response.json();

  if (!Array.isArray(data)) {
    throw new Error("Format data tidak sesuai");
  }

  return data;
}
```

Pisahkan fungsi mengambil data dari fungsi menggambar UI. Ini membuat keduanya
lebih mudah diuji.

## 3. Empat state UI wajib

```text
idle → loading ─┬→ success (ada data)
                ├→ empty   (berhasil, data kosong)
                └→ error   (request/parsing gagal)
```

Contoh DOM aman:

```js
const statusEl = document.querySelector("#status");
const listEl = document.querySelector("#produk");

function tampilkanPesan(pesan) {
  statusEl.textContent = pesan;
}

function renderProduk(items) {
  listEl.replaceChildren();

  for (const item of items) {
    const li = document.createElement("li");
    li.textContent = item.nama;
    listEl.append(li);
  }
}

async function muat() {
  tampilkanPesan("Memuat produk…");

  try {
    const items = await ambilProduk();
    if (items.length === 0) {
      tampilkanPesan("Belum ada produk.");
      return;
    }

    tampilkanPesan("");
    renderProduk(items);
  } catch (error) {
    console.error(error);
    tampilkanPesan("Data gagal dimuat. Coba lagi.");
  }
}
```

Pesan error untuk pengguna menjelaskan tindakan berikutnya. Detail teknis tetap
di Console/log, bukan ditumpahkan ke UI.

## 4. Request tumpang tindih dan pembatalan

Pencarian cepat dapat membuat response lama datang setelah response baru.
Batalkan request sebelumnya dengan `AbortController`:

```js
let controller;

async function cariProduk(query) {
  controller?.abort();
  controller = new AbortController();

  try {
    const response = await fetch(
      `/api/produk?q=${encodeURIComponent(query)}`,
      { signal: controller.signal },
    );
    if (!response.ok) throw new Error(`HTTP ${response.status}`);
    return await response.json();
  } catch (error) {
    if (error.name === "AbortError") return null;
    throw error;
  }
}
```

`encodeURIComponent` mencegah spasi dan karakter khusus merusak query URL.

## 5. CORS dan same-origin

Origin tersusun dari skema, host, dan port. Browser membatasi JavaScript yang
membaca response lintas-origin kecuali server mengizinkan lewat header CORS.

```text
http://localhost:3000  ≠  http://localhost:8080
        origin A                    origin B
```

CORS bukan error yang dapat “diperbaiki” dengan menambah header sembarang di
frontend. Izin harus diberikan server/API. Solusi yang sehat:

- gunakan API yang memang mengizinkan origin aplikasi;
- panggil API dari Server Component/Route Handler bila sesuai;
- buat proxy server yang terkontrol;
- jangan menonaktifkan keamanan browser untuk solusi tugas.

## 6. Validasi dan keamanan dasar

Validasi client membantu pengalaman pengguna, tetapi penyerang dapat melewati
browser. Server tetap harus memvalidasi dan mengotorisasi setiap operasi.

Aturan minimum:

- tampilkan teks tidak tepercaya dengan `textContent`, bukan `innerHTML`;
- di React, hindari `dangerouslySetInnerHTML` untuk data pengguna;
- jangan taruh secret di JavaScript browser atau variabel `NEXT_PUBLIC_*`;
- jangan menganggap tombol tersembunyi sebagai otorisasi;
- validasi tipe, panjang, rentang, dan format di batas sistem;
- jangan menampilkan pesan error server mentah kepada pengguna.

XSS sederhana yang harus dihindari:

```js
hasil.innerHTML = input.value;   // berbahaya
hasil.textContent = input.value; // teks literal, lebih aman
```

## 7. Aksesibilitas untuk UI async

State async perlu dapat dipahami pengguna pembaca layar:

```html
<p id="status" role="status" aria-live="polite"></p>
<button id="coba-lagi" type="button">Coba lagi</button>
```

- gunakan `role="status"`/`aria-live="polite"` untuk perubahan status yang
  penting tetapi tidak mendesak;
- tombol retry harus elemen `<button>`, bukan `<div>`;
- jangan mengandalkan warna saja untuk membedakan sukses/error;
- ketika tombol sedang memproses, gunakan `disabled` dan teks yang jelas;
- pertahankan fokus keyboard; jangan memindahkannya tanpa alasan.

## 8. Strategi tes berlapis

| Lapisan | Pertanyaan | Cara sederhana |
|---|---|---|
| Fungsi murni | filter/format menghasilkan nilai benar? | panggil fungsi dengan input normal & batas |
| Komponen | props/state menghasilkan UI benar? | render, interaksi, periksa output |
| Integrasi | UI menangani response API? | mock sukses, kosong, 404, 500, offline |
| Alur pengguna | tugas utama selesai dari awal ke akhir? | buka → cari → detail → kembali |

Jangan hanya mengetes *happy path*. Matriks minimum:

| Skenario | Harapan |
|---|---|
| response 200 + data | daftar tampil |
| response 200 + `[]` | empty state tampil |
| response 404/500 | error state + retry |
| offline | pesan ramah, aplikasi tidak blank |
| response lambat | loading terlihat, tombol ganda dicegah |
| data aneh/panjang | layout tidak pecah |

## 9. Tantangan mini — Pencarian produk

Buat halaman kecil yang mengambil produk dari API latihan atau Route Handler.
Wajib memiliki:

1. form pencarian ber-label;
2. loading, error, empty, dan success state;
3. tombol “Coba lagi”;
4. pembatalan request lama saat query berubah cepat;
5. output aman tanpa `innerHTML`/`dangerouslySetInnerHTML`;
6. pengujian manual enam skenario pada tabel sebelumnya;
7. catatan `PENGUJIAN.md` berisi input, harapan, hasil, dan perbaikan.

### Rubrik 100 poin

| Aspek | Poin |
|---|---:|
| Alur request dan pemeriksaan status | 20 |
| Empat state UI | 25 |
| Ketahanan terhadap request gagal/tumpang tindih | 15 |
| Aksesibilitas keyboard dan status | 15 |
| Keamanan output dan secret | 15 |
| Bukti pengujian | 10 |

## Checklist akhir

- [ ] `response.ok` diperiksa sebelum parsing dianggap berhasil.
- [ ] UI membedakan loading, empty, error, dan success.
- [ ] Pengguna tahu cara mencoba lagi.
- [ ] Query URL di-encode.
- [ ] Data tidak tepercaya tidak dimasukkan ke `innerHTML`.
- [ ] Secret tidak masuk bundle client.
- [ ] Navigasi keyboard dan pembaruan status dapat dipahami.
- [ ] Kasus offline, lambat, kosong, dan server error sudah diuji.
