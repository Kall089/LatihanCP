# 09 — Server Actions dan form

[← 08 Route Handler](08-route-handler-http.md) · [Berikut: metadata, image, font →](10-metadata-image-font.md)

**Untuk apa:** menjalankan fungsi di server dari form atau klik, tanpa menulis Route Handler terpisah untuk setiap aksi.

Server Action adalah fungsi async yang ditandai `"use server"`. Next memasangnya sebagai endpoint tersembunyi. Validasi tetap wajib; jangan percaya input.

## Daftar isi file ini

- ["use server" di file terpisah](#use-server-di-file-terpisah)
- ["use server" di dalam Server Component](#use-server-di-dalam-server-component)
- [Form action={fn}](#form-actionfn)
- [FormData, satu field per satu](#formdata-satu-field-per-satu)
- [Hidden fields dan bind](#hidden-fields-dan-bind)
- [return nilai ke UI](#return-nilai-ke-ui)
- [useActionState](#useactionstate)
- [useFormStatus](#useformstatus)
- [useOptimistic](#useoptimistic)
- [redirect dan revalidate dari action](#redirect-dan-revalidate-dari-action)
- [Memanggil action dari onClick](#memanggil-action-dari-onclick)
- [Progressive enhancement](#progressive-enhancement)
- [Keamanan](#keamanan)
- [Action versus Route Handler](#action-versus-route-handler)
- [Resep form tambah produk](#resep-form-tambah-produk)
- [Kesalahan umum](#kesalahan-umum)

## "use server" di file terpisah

**Untuk apa:** mengekspor beberapa action yang bisa diimpor page dan Client Component.

`app/aksi.js`:

```js
"use server";

export async function simpanNama(formData) {
  const nama = String(formData.get("nama") ?? "").trim();
  if (!nama) return { ok: false, pesan: "Nama wajib" };
  return { ok: true, pesan: `Tersimpan: ${nama}` };
}
```

Direktif di **atas file** berarti semua ekspor fungsi adalah Server Action.

Aturan, satu per satu:

- File ini berjalan di server. Boleh `cookies()`, `fetch` ke Laravel, baca env rahasia.
- Jangan menaruh komponen React di file yang seluruhnya `"use server"` kecuali kamu paham batasnya — lebih bersih: action terpisah dari UI.
- Impor action ke Server Component langsung, atau ke Client Component (Next mengirim referensi aman, bukan source).

`app/page.js`:

```jsx
import { simpanNama } from "./aksi";

export default function Halaman() {
  return (
    <form action={simpanNama}>
      <label>
        Nama
        <input name="nama" required />
      </label>
      <button type="submit">Simpan</button>
    </form>
  );
}
```

**Biasanya digabungkan dengan:** `revalidatePath` setelah mutasi sungguhan.

## "use server" di dalam Server Component

**Untuk apa:** action lokal yang tidak dipakai file lain.

```jsx
export default function Halaman() {
  async function simpanNama(formData) {
    "use server";
    const nama = String(formData.get("nama") ?? "").trim();
    console.log(nama);
  }

  return (
    <form action={simpanNama}>
      <input name="nama" />
      <button type="submit">Simpan</button>
    </form>
  );
}
```

Direktif di **dalam fungsi**, bukan di puncak file. File tetap Server Component.

Jangan mendefinisikan inline action di Client Component. Pindahkan ke `aksi.js`.

**Biasanya digabungkan dengan:** halaman kecil satu form.

## Form action={fn}

**Untuk apa:** HTML form native yang POST ke action.

Ciri:

- `<form action={simpanNama}>` tanpa `method` — Next menangani.
- Field harus punya `name` atau tidak terkirim.
- `button` default adalah `submit`. `type="button"` tidak mengirim form.
- Boleh beberapa tombol submit dengan `name`/`value` berbeda.

```jsx
<form action={ubahStatus}>
  <input type="hidden" name="id" value={id} />
  <button type="submit" name="status" value="terbit">Terbitkan</button>
  <button type="submit" name="status" value="draf">Simpan draf</button>
</form>
```

Di action: `formData.get("status")`.

Jangan menaruh `onSubmit={e => e.preventDefault()}` jika kamu ingin action + progressive enhancement, kecuali kamu sadar mengendalikan semuanya di klien.

**Biasanya digabungkan dengan:** input `required`, `type="email"`, dan validasi ulang di server.

## FormData, satu field per satu

**Untuk apa:** membaca payload form.

```js
"use server";

export async function daftarAkun(formData) {
  const nama = String(formData.get("nama") ?? "").trim();
  const email = String(formData.get("email") ?? "").trim();
  const setuju = formData.get("setuju") === "on";
  const minat = formData.getAll("minat"); // checkbox sama name

  if (!nama || !email.includes("@")) {
    return { ok: false, pesan: "Nama dan email wajib" };
  }

  return { ok: true, nama, email, setuju, minat };
}
```

Metode `FormData`:

- `get("nama")` — nilai pertama atau `null`
- `getAll("minat")` — array
- `has("setuju")`
- `set` / `append` / `delete` — lebih sering di klien sebelum kirim

File:

```js
const gambar = formData.get("gambar");
if (gambar && typeof gambar !== "string") {
  const bytes = await gambar.arrayBuffer();
  const ukuran = gambar.size;
  const tipe = gambar.type;
  // unggah ke penyimpanan — jangan simpan di repo tugas
}
```

Angka:

```js
const harga = Number(formData.get("harga"));
if (!Number.isFinite(harga) || harga < 0) {
  return { ok: false, pesan: "Harga tidak valid" };
}
```

**Biasanya digabungkan dengan:** `<input type="file">` + validasi mime/ukuran.

## Hidden fields dan bind

**Untuk apa:** mengirim id tanpa input terlihat, atau mengikat argumen tambahan.

### Hidden

```jsx
<form action={hapusProduk}>
  <input type="hidden" name="id" value={id} />
  <button type="submit">Hapus</button>
</form>
```

Pengguna bisa mengubah hidden di DevTools. Server harus cek izin: “bolehkah user ini menghapus id ini?”

### bind

```js
const hapusIni = hapusProduk.bind(null, id);
```

```jsx
<form action={hapusIni}>
  <button type="submit">Hapus</button>
</form>
```

```js
"use server";

export async function hapusProduk(id, formData) {
  const konfirmasi = String(formData.get("konfirmasi") ?? "");
  // id dari bind, bukan dari user hidden — tetap validasi id
}
```

Urutan: argumen `bind` masuk **sebelum** `formData`.

`bind` juga berguna untuk extra argument non-string (tetap harus serial).

**Biasanya digabungkan dengan:** daftar produk yang tiap baris punya tombol hapus.

## return nilai ke UI

**Untuk apa:** menampilkan pesan tanpa `redirect`.

Action boleh `return` objek serial (JSON-plain). Form mentah tanpa hook **tidak otomatis** menampilkan return itu. Kamu perlu:

- `useActionState` / `useFormState` (nama bergantung versi React), atau
- Client Component yang `await aksi()` lalu `setState`, atau
- `redirect` ke halaman dengan query `?ok=1`.

Jangan `return` kelas, fungsi, atau koneksi DB.

**Biasanya digabungkan dengan:** `useActionState` di bawah.

## useActionState

**Untuk apa:** menyimpan hasil action terakhir (pesan error/sukses) dan status pending.

Nama API: React 19 `useActionState`. Beberapa contoh lama memakai `useFormState` dari `react-dom`. Di proyek baru, utamakan `useActionState`.

`app/components/FormNama.js`:

```jsx
"use client";

import { useActionState } from "react";
import { simpanNama } from "../aksi";

const awal = { ok: null, pesan: "" };

export default function FormNama() {
  const [state, formAction, pending] = useActionState(simpanNama, awal);

  return (
    <form action={formAction}>
      <input name="nama" disabled={pending} />
      <button type="submit" disabled={pending}>
        {pending ? "Menyimpan…" : "Simpan"}
      </button>
      {state.pesan ? <p>{state.pesan}</p> : null}
    </form>
  );
}
```

Action harus menerima `(stateSebelumnya, formData)` jika dipakai dengan `useActionState`:

```js
"use server";

export async function simpanNama(stateSebelumnya, formData) {
  const nama = String(formData.get("nama") ?? "").trim();
  if (!nama) return { ok: false, pesan: "Nama wajib" };
  return { ok: true, pesan: `Tersimpan: ${nama}` };
}
```

Tanpa hook, signature cukup `(formData)`. **Sesuaikan parameter** dengan cara pemanggilan.

**Biasanya digabungkan dengan:** validasi field dan menonaktifkan tombol saat pending.

## useFormStatus

**Untuk apa:** membaca status submit **dari dalam** form (anak), tanpa props drilling.

```jsx
"use client";

import { useFormStatus } from "react-dom";

export function TombolKirim() {
  const { pending } = useFormStatus();
  return (
    <button type="submit" disabled={pending}>
      {pending ? "Mengirim…" : "Kirim"}
    </button>
  );
}
```

`useFormStatus` harus dipanggil di komponen anak dari `<form>`, bukan di komponen yang sama tempat `<form>` ditulis, kecuali strukturmu memang memisahkannya.

`pending` true selama action berjalan.

**Biasanya digabungkan dengan:** form server yang ingin spinner tanpa mengubah seluruh page jadi klien.

## useOptimistic

**Untuk apa:** menampilkan perubahan UI sebelum server selesai.

```jsx
"use client";

import { useOptimistic } from "react";

export default function DaftarSuka({ sukaAwal, aksi }) {
  const [suka, setOptimistik] = useOptimistic(sukaAwal);

  async function handle(formData) {
    const id = formData.get("id");
    setOptimistik(true);
    await aksi(formData);
  }

  return (
    <form action={handle}>
      <input type="hidden" name="id" value="1" />
      <button type="submit">{suka ? "Disukai" : "Sukai"}</button>
    </form>
  );
}
```

Jika action gagal, kamu perlu mengembalikan UI (sering lewat state dari server setelah refresh). Untuk tugas awal, `useFormStatus` lebih penting daripada optimistic.

**Biasanya digabungkan dengan:** like, keranjang, dan daftar yang terasa instan.

## redirect dan revalidate dari action

**Untuk apa:** setelah sukses, segarkan data dan/atau pindah halaman.

```js
"use server";

import { redirect } from "next/navigation";
import { revalidatePath, revalidateTag } from "next/cache";

export async function tambahProduk(formData) {
  const nama = String(formData.get("nama") ?? "").trim();
  if (!nama) return { ok: false, pesan: "Nama wajib" };

  const baseUrl = process.env.API_BASE_URL;
  const response = await fetch(`${baseUrl}/api/produk`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ nama }),
  });

  if (!response.ok) return { ok: false, pesan: "Gagal menyimpan" };

  revalidatePath("/produk");
  revalidateTag("produk");
  redirect("/produk");
}
```

`redirect()` melempar. Letakkan **setelah** mutasi sukses. Jangan `try/catch` yang menelan redirect.

Jika tidak `redirect`, pengguna tetap di form; panggil `revalidatePath` agar daftar di layout/page terbarui.

**Biasanya digabungkan dengan:** Laravel `POST /api/produk` dan halaman daftar.

## Memanggil action dari onClick

**Untuk apa:** aksi tanpa form, tetap di server.

```jsx
"use client";

import { hapusProduk } from "../aksi";

export default function TombolHapus({ id }) {
  return (
    <button
      type="button"
      onClick={async () => {
        if (!confirm("Hapus produk ini?")) return;
        await hapusProduk(id);
      }}
    >
      Hapus
    </button>
  );
}
```

```js
"use server";

import { revalidatePath } from "next/cache";

export async function hapusProduk(id) {
  const aman = String(id);
  // cek izin + hapus
  revalidatePath("/produk");
}
```

Tanpa form, progressive enhancement hilang: tanpa JS, tombol tidak jalan. Untuk hapus penting, form + tombol submit lebih tangguh.

**Biasanya digabungkan dengan:** `router.refresh()` jika invalidasi tidak terasa.

## Progressive enhancement

**Untuk apa:** form tetap mengirim meski JavaScript belum hidup.

Syarat kasar:

- `<form action={serverAction}>` di Server Component atau Client yang tidak `preventDefault`.
- Field native `name`.
- Action tidak bergantung pada `window`.

`useActionState` tetap berfungsi setelah hydrate; sebelum JS, form tetap POST.

Ini beda dengan SPA murni yang `onSubmit` + `fetch`.

**Biasanya digabungkan dengan:** tugas yang dinilai “jalan tanpa error konsol”, dan aksesibilitas.

## Keamanan

Satu per satu, wajib dipikirkan:

1. **Validasi ulang di server.** `required` HTML bisa dihapus.
2. **Otorisasi.** Hidden `id` bukan bukti kepemilikan.
3. **CSRF.** Server Action Next dirancang dengan pemeriksaan origin/header. Tetap jangan menonaktifkan proteksi. Jangan membuka action ke situs lain tanpa sadar.
4. **Rate limit** untuk form publik (komentar, login) — minimal sadari risikonya.
5. **Jangan `eval` input.**
6. **Unggahan file:** cek tipe, ukuran, nama; simpan di luar `public/` jika tidak boleh diunduh bebas.
7. **Error:** jangan kembalikan stack / query SQL ke klien.
8. **Env rahasia** hanya di action, bukan sebagai props klien.

**Biasanya digabungkan dengan:** cookie sesi + cek di awal action.

## Action versus Route Handler

| | Server Action | Route Handler |
| --- | --- | --- |
| Pemanggil utama | form / komponen Next | `fetch`, mobile, webhook |
| Kontrak | fungsi JS | HTTP publik |
| URL | tersembunyi | `/api/...` yang kamu pilih |
| Cocok CRUD UI toko | Ya | Ya, jika klien terpisah |
| Cocok webhook Laravel | Kurang | Ya |

Kamu boleh keduanya: action untuk UI, handler untuk integrasi.

**Biasanya digabungkan dengan:** [08](08-route-handler-http.md) untuk API JSON.

## Resep form tambah produk

`app/aksi-produk.js`:

```js
"use server";

import { redirect } from "next/navigation";
import { revalidatePath } from "next/cache";

export async function tambahProduk(formData) {
  const nama = String(formData.get("nama") ?? "").trim();
  const harga = Number(formData.get("harga"));

  if (nama.length < 3) return { ok: false, pesan: "Nama minimal 3 huruf" };
  if (!Number.isFinite(harga) || harga < 0) {
    return { ok: false, pesan: "Harga tidak valid" };
  }

  const baseUrl = process.env.API_BASE_URL;
  if (!baseUrl) return { ok: false, pesan: "API belum dikonfigurasi" };

  const response = await fetch(`${baseUrl}/api/produk`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ nama, harga }),
  });

  if (!response.ok) return { ok: false, pesan: "Gagal menyimpan ke API" };

  revalidatePath("/produk");
  redirect("/produk");
}
```

`app/produk/baru/page.js`:

```jsx
import { tambahProduk } from "../../aksi-produk";

export const metadata = { title: "Produk baru" };

export default function ProdukBaru() {
  return (
    <main>
      <h1>Tambah produk</h1>
      <form action={tambahProduk}>
        <p>
          <label>
            Nama
            <input name="nama" required minLength={3} />
          </label>
        </p>
        <p>
          <label>
            Harga
            <input name="harga" type="number" min={0} required />
          </label>
        </p>
        <button type="submit">Simpan</button>
      </form>
    </main>
  );
}
```

Untuk menampilkan `pesan` tanpa redirect saat gagal, bungkus form dengan `useActionState` dan **jangan** `redirect` pada cabang error (contoh di atas sudah `return` dulu).

**Biasanya digabungkan dengan:** `app/produk/baru` sebagai folder statis di samping `[id]` — lihat [05](05-dynamic-route-catch-all-optional.md).

## File upload + action

```jsx
<form action={unggahSampul} encType="multipart/form-data">
  <input type="file" name="sampul" accept="image/png,image/jpeg" />
  <button type="submit">Unggah</button>
</form>
```

`encType` membantu jika form dikirim tanpa JS. Di action, baca `formData.get("sampul")`.

Jangan commit file hasil unggah ke git. Simpan ke folder di luar repo atau ke layanan objek.

**Biasanya digabungkan dengan:** `next/image` setelah URL publik tersedia.

## Kesalahan umum

- `"use server"` di Client Component body.
- Action `(formData)` dipakai `useActionState` tanpa parameter state.
- `useFormStatus` di komponen yang sama dengan `<form>` lalu `pending` selalu false.
- Percaya `required` saja.
- `try/catch` menelan `redirect`.
- Lupa `revalidatePath` — daftar tetap lama.
- Mengirim password ke `console.log` di production.
- Menyimpan array memori mengira itu database.
- Menamai file action `route.js`.

## Checklist form tugas

1. Field `name` lengkap.
2. Validasi server.
3. Pesan error ke pengguna.
4. `revalidatePath` / `redirect` setelah sukses.
5. Tombol `disabled` saat pending jika ada JS.
6. Tidak ada rahasia di HTML.

## Lihat juga

- [07 — revalidatePath / revalidateTag](07-fetch-cache-revalidate.md)
- [03 — redirect](03-link-navigation-hooks.md)
- [Cheatsheet ringkas: Server Action](../../next-js.md)

---

Sebelum: [08 — Route Handler](08-route-handler-http.md) · Berikut: [10 — metadata, image, font](10-metadata-image-font.md)
