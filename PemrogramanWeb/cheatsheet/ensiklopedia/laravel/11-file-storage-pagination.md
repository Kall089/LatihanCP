# 11 — File storage dan pagination

[← API Resource](10-api-resource-cors.md) · [Daftar](README.md) · [Berikutnya: Artisan →](12-artisan-katalog.md)

**Untuk apa storage:** menyimpan unggahan dan file yang dihasilkan aplikasi di disk (`local`, `public`, S3), bukan di dalam `public/` secara langsung tanpa kendali.

**Untuk apa pagination:** memotong daftar besar menjadi halaman agar query dan HTML/JSON tidak memuat ribuan baris.

Rujukan: [filesystem](https://laravel.com/docs/13.x/filesystem), [pagination](https://laravel.com/docs/13.x/pagination).

## Daftar isi

- [Disk local dan public](#disk-local-dan-public)
- [storage:link](#storagelink)
- [Form enctype](#form-enctype)
- [Validasi file sebelum simpan](#validasi-file-sebelum-simpan)
- [store dan storeAs](#store-dan-storeas)
- [storePublicly](#storepublicly)
- [Storage::url dan asset](#storageurl-dan-asset)
- [Storage::get, exists, delete](#storageget-exists-delete)
- [Mengganti file saat update](#mengganti-file-saat-update)
- [File privat](#file-privat)
- [paginate](#paginate)
- [simplePaginate dan cursorPaginate](#simplepaginate-dan-cursorpaginate)
- [links di Blade](#links-di-blade)
- [withQueryString](#withquerystring)
- [appends](#appends)
- [Metode paginator](#metode-paginator)
- [Pagination JSON](#pagination-json)
- [Tampilan Bootstrap/Tailwind](#tampilan-bootstraptailwind)
- [Kesalahan unggah dan halaman](#kesalahan-unggah-dan-halaman)

---

## Disk local dan public

**Untuk apa:** memilih tempat file.

| Disk | Path default | Terlihat publik? |
| --- | --- | --- |
| `local` | `storage/app/private` (atau `storage/app` tergantung versi) | tidak |
| `public` | `storage/app/public` | ya, setelah `storage:link` |
| `s3` | bucket cloud | sesuai ACL/URL |

```php
use Illuminate\Support\Facades\Storage;

Storage::disk('public')->put('halo.txt', 'isi');
Storage::disk('local')->put('rahasia.txt', 'isi');
```

Foto produk yang ditampilkan di `<img>` biasanya disk `public`. Dokumen KTP latihan (jangan data nyata sensitif) → `local` + diunduh lewat controller ber-`auth`.

Konfigurasi: `config/filesystems.php`, kunci `.env` `FILESYSTEM_DISK`.

**Biasanya digabungkan dengan:** `store(..., 'public')` dan `storage:link`.

---

## storage:link

**Untuk apa:** membuat tautan `public/storage` → `storage/app/public` agar URL `/storage/produk/a.jpg` berfungsi.

```bash
php artisan storage:link
```

Tanpa ini, path di database ada tetapi gambar 404.

Jalankan sekali per lingkungan. Jangan commit symlink rusak; di server baru jalankan lagi.

**Biasanya digabungkan dengan:** `Storage::url($path)` dan `<img src="...">`.

---

## Form enctype

**Untuk apa:** memberitahu browser mengirim file, bukan hanya teks.

```blade
<form method="POST" action="{{ route('products.store') }}" enctype="multipart/form-data">
    @csrf
    <input type="file" name="foto" accept="image/*">
    <button type="submit">Unggah</button>
</form>
```

Tanpa `enctype`, `$request->file('foto')` kosong. Validasi `required|image` gagal misterius.

**Biasanya digabungkan dengan:** `@csrf`, rule `image`, dan `old()` yang **tidak** bisa mengisi ulang file — pengguna harus pilih file lagi jika validasi field lain gagal.

---

## Validasi file sebelum simpan

**Untuk apa:** menolak tipe/ukuran berbahaya sebelum `store`.

```php
$data = $request->validate([
    'nama' => ['required', 'string', 'max:100'],
    'foto' => ['required', 'image', 'mimes:jpg,jpeg,png,webp', 'max:2048'],
]);
```

`max:2048` = kilobyte. `php.ini` `upload_max_filesize` / `post_max_size` harus lebih besar, atau unggah gagal sebelum validasi Laravel.

**Biasanya digabungkan dengan:** `hasFile` + `isValid()` sebagai jaring, dan rule di file 04.

---

## store dan storeAs

**Untuk apa:** menyimpan unggahan. `store` membuat nama acak (aman, tidak tabrakan). `storeAs` memakai nama yang kamu tentukan.

```php
$path = $request->file('foto')->store('produk', 'public');
// contoh: produk/XyZ123.jpg
```

```php
$path = $request->file('foto')->storeAs(
    'produk',
    $product->id.'.jpg',
    'public'
);
```

`storeAs` rawan tabrakan dan rawan karakter aneh dari nama asli. Utamakan `store` + simpan `$path` di kolom `foto`.

Jangan memakai `$file->getClientOriginalName()` mentah sebagai nama file publik tanpa sanitasi.

```php
$product = Product::create([
    ...$request->safe()->except('foto'),
    'foto' => $path,
]);
```

**Biasanya digabungkan dengan:** `$fillable` memuat `foto`, disk `public`, dan `storage:link`.

---

## storePublicly

**Untuk apa:** alias menyimpan ke disk yang terlihat publik.

```php
$path = $request->file('foto')->storePublicly('produk');
```

Setara niat `store(..., 'public')` pada banyak setup. Tetap cek disk default.

**Biasanya digabungkan dengan:** unggahan yang memang untuk `<img>`.

---

## Storage::url dan asset

**Untuk apa:** membangun URL yang bisa dipakai browser.

```php
Storage::disk('public')->url($product->foto);
// /storage/produk/XyZ123.jpg
```

```blade
@if ($product->foto)
    <img src="{{ Storage::url($product->foto) }}" alt="{{ $product->nama }}">
@endif
```

`asset('storage/'.$product->foto)` sering berhasil setelah link, tetapi `Storage::url` mengikuti disk (termasuk S3).

Jangan `asset($product->foto)` jika nilai kolom sudah `produk/abc.jpg` tanpa prefix storage — hasil 404.

**Biasanya digabungkan dengan:** helper `asset` untuk file di `public/` yang bukan unggahan (css/js/favicon).

---

## Storage::get, exists, delete

**Untuk apa:** baca, cek, hapus file di disk.

```php
if (Storage::disk('public')->exists($product->foto)) {
    $isi = Storage::disk('public')->get($product->foto);
    Storage::disk('public')->delete($product->foto);
}
```

Hapus file saat produk dihapus, atau file lama menumpuk.

```php
public function destroy(Product $product)
{
    if ($product->foto) {
        Storage::disk('public')->delete($product->foto);
    }
    $product->delete();

    return redirect()->route('products.index');
}
```

`delete` pada path yang tidak ada biasanya tidak meledak — tetap cek jika perlu.

**Biasanya digabungkan dengan:** `destroy`, ganti foto, dan observer model.

---

## Mengganti file saat update

**Untuk apa:** unggah baru opsional; jika ada, hapus lama.

```php
$data = $request->validate([
    'nama' => ['required', 'string', 'max:100'],
    'foto' => ['nullable', 'image', 'max:2048'],
]);

if ($request->hasFile('foto')) {
    if ($product->foto) {
        Storage::disk('public')->delete($product->foto);
    }
    $data['foto'] = $request->file('foto')->store('produk', 'public');
}

$product->update($data);
```

Tanpa `nullable`, edit tanpa ganti foto gagal validasi.

**Biasanya digabungkan dengan:** form `enctype` dan `@error('foto')`.

---

## File privat

**Untuk apa:** file yang tidak boleh ditebak URL-nya.

Simpan di disk `local`. Jangan `storage:link` untuk folder itu. Sajikan lewat controller:

```php
public function unduh(Document $document)
{
    Gate::authorize('view', $document);

    return Storage::disk('local')->download($document->path, $document->nama_asli);
}
```

Jangan `return Storage::download($request->query('path'))` — directory traversal.

**Biasanya digabungkan dengan:** `auth`, policy, dan `response()->download`.

---

## paginate

**Untuk apa:** membagi hasil query menjadi halaman. Default memakai `?page=2`.

```php
$products = Product::latest()->paginate(10);
```

10 = jumlah per halaman. Objek paginator **bukan** array biasa, tetapi bisa di-`@foreach`.

Jangan `Product::all()` lalu potong di PHP untuk tabel besar.

Selalu `orderBy` / `latest` agar halaman stabil.

**Biasanya digabungkan dengan:** `with('category')`, `when` filter, dan `links()`.

---

## simplePaginate dan cursorPaginate

**Untuk apa:** alternatif yang lebih hemat.

```php
Product::latest()->simplePaginate(10); // next/prev, tanpa hitung total
Product::orderBy('id')->cursorPaginate(10); // kursor, bagus tabel raksasa
```

`paginate` menjalankan `COUNT(*)` — mahal di tabel sangat besar. `simplePaginate` cukup untuk "berikutnya".

`cursorPaginate` tidak memakai nomor halaman lompat bebas seperti `page=9`.

**Biasanya digabungkan dengan:** API feed dan daftar admin sederhana.

---

## links di Blade

**Untuk apa:** mencetak navigasi halaman.

```blade
{{ $products->links() }}
```

atau:

```blade
<nav aria-label="Halaman produk">
    @if ($products->onFirstPage())
        {{-- tidak ada prev --}}
    @else
        <a href="{{ $products->previousPageUrl() }}">Sebelumnya</a>
    @endif
    <span>Halaman {{ $products->currentPage() }}</span>
    @if ($products->hasMorePages())
        <a href="{{ $products->nextPageUrl() }}">Berikutnya</a>
    @endif
</nav>
```

Letakkan **di luar** `@forelse` item, masih di dalam section.

**Biasanya digabungkan dengan:** `@forelse` dan view pagination sesuai CSS framework.

---

## withQueryString

**Untuk apa:** membawa `?q=` dan filter lain saat pindah halaman.

```php
$products = Product::query()
    ->when($request->query('q'), fn ($q, $term) => $q->where('nama', 'like', '%'.$term.'%'))
    ->paginate(10)
    ->withQueryString();
```

Tanpa ini, halaman 2 menghilangkan kata kunci pencarian.

**Biasanya digabungkan dengan:** form GET search dan `old` tidak berlaku (itu POST); filter memakai `query('q')`.

---

## appends

**Untuk apa:** menambahkan query tertentu secara manual.

```php
$products->appends(['q' => $request->query('q'), 'sort' => 'nama']);
```

`withQueryString()` biasanya cukup. `appends` jika kamu ingin memilih kunci.

**Biasanya digabungkan dengan:** sort custom.

---

## Metode paginator

| Method | Arti |
| --- | --- |
| `currentPage()` | nomor halaman sekarang |
| `lastPage()` | halaman terakhir (`paginate` saja) |
| `perPage()` | ukuran halaman |
| `total()` | jumlah semua (`paginate`) |
| `count()` | item di halaman ini |
| `hasPages()` | lebih dari satu halaman? |
| `hasMorePages()` | ada berikutnya? |
| `onFirstPage()` | halaman 1? |
| `nextPageUrl()` | URL next atau null |
| `previousPageUrl()` | URL prev atau null |
| `path()` | path dasar |
| `isEmpty()` / `isNotEmpty()` | isi halaman |

```blade
<p>{{ $products->total() }} produk, halaman {{ $products->currentPage() }}</p>
```

**Biasanya digabungkan dengan:** empty state `@forelse`.

---

## Pagination JSON

Resource collection pada paginator sudah menyertakan `links` + `meta`. Frontend:

```js
const page = await fetch('/api/products?page=2', {
  headers: { Accept: 'application/json' },
}).then((r) => r.json());
```

Jangan mengirim `Product::all()` ke API publik.

**Biasanya digabungkan dengan:** `ProductResource::collection` dan `withQueryString`.

---

## Tampilan Bootstrap/Tailwind

**Untuk apa:** menyesuaikan HTML `links()` dengan CSS yang kamu pakai.

```php
// AppServiceProvider::boot
use Illuminate\Pagination\Paginator;

Paginator::useBootstrapFive();
// atau default Tailwind pada Laravel modern
```

Tanpa ini, markup default mungkin tidak cocok tema.

**Biasanya digabungkan dengan:** layout Blade dan CSS tugas.

---

## Kesalahan unggah dan halaman

| Gejala | Obat |
| --- | --- |
| file null | `enctype`, nama input, `post_max_size` |
| 404 gambar | `storage:link`, disk salah, path salah |
| file menumpuk | hapus lama saat update/destroy |
| XSS lewat nama file | `store()` acak, bukan nama asli |
| halaman 2 kosong aneh | lupa `orderBy`, data berubah |
| filter hilang | `withQueryString` |
| `links()` error | variabel bukan hasil `paginate` |
| COUNT lambat | `simplePaginate` |

Lanjut ke [katalog Artisan](12-artisan-katalog.md).
