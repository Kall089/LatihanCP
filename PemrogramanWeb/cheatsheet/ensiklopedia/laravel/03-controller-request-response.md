# 03 — Controller, Request, Response

[← Routing](02-routing-web-api-resource.md) · [Daftar](README.md) · [Berikutnya: validasi →](04-validasi-rules-lengkap.md)

**Untuk apa controller:** mengatur alur satu permintaan: baca input, validasi, query, lalu kirim HTML/JSON/redirect. Controller **bukan** tempat HTML panjang dan **bukan** tempat SQL acak tanpa model.

**Untuk apa Request:** objek data masuk.

**Untuk apa Response:** jawaban yang dikirim ke browser/klien.

Rujukan: [controller](https://laravel.com/docs/13.x/controllers), [request](https://laravel.com/docs/13.x/requests), [response](https://laravel.com/docs/13.x/responses).

## Daftar isi

- [Membuat controller](#membuat-controller)
- [Method index](#method-index)
- [Method create](#method-create)
- [Method store](#method-store)
- [Method show](#method-show)
- [Method edit](#method-edit)
- [Method update](#method-update)
- [Method destroy](#method-destroy)
- [Controller invokable](#controller-invokable)
- [Dependency injection](#dependency-injection)
- [Request $request](#request-request)
- [all dan input](#all-dan-input)
- [query](#query)
- [only dan except](#only-dan-except)
- [has, filled, missing, boolean](#has-filled-missing-boolean)
- [file dan hasFile](#file-dan-hasfile)
- [header, method, wantsJson](#header-method-wantsjson)
- [validate di controller](#validate-di-controller)
- [Form Request](#form-request)
- [view dan compact](#view-dan-compact)
- [redirect](#redirect)
- [back dan with](#back-dan-with)
- [response json](#response-json)
- [abort](#abort)
- [download dan file](#download-dan-file)
- [Single action flow lengkap](#single-action-flow-lengkap)
- [Kesalahan controller](#kesalahan-controller)

---

## Membuat controller

**Untuk apa:** menghasilkan class di `app/Http/Controllers` dengan nama dan namespace yang benar.

```bash
php artisan make:controller ProductController
php artisan make:controller ProductController --resource
php artisan make:controller ProductController --invokable
php artisan make:controller Api/ProductController --api
```

`--resource` menyiapkan tujuh method web. `--api` tanpa `create`/`edit`.

Contoh kerangka:

```php
<?php

namespace App\Http\Controllers;

use App\Models\Product;
use Illuminate\Http\Request;
use Illuminate\View\View;
use Illuminate\Http\RedirectResponse;

class ProductController extends Controller
{
    //
}
```

Di Laravel 11/13, class dasar `Controller` bisa sangat tipis. Helper `view()` dan `redirect()` tetap tersedia sebagai fungsi global.

**Biasanya digabungkan dengan:** `Route::resource` atau pendaftaran method satu-satu.

---

## Method index

**Untuk apa:** menampilkan **daftar**. GET. Tidak mengubah data.

```php
public function index(): View
{
    $products = Product::latest()->paginate(10);

    return view('products.index', compact('products'));
}
```

- `latest()` mengurutkan `created_at` menurun.
- `paginate(10)` memotong halaman; jangan `all()` untuk tabel besar.
- Nama variabel di `compact` harus sama dengan yang dipakai Blade: `$products`.

**Biasanya digabungkan dengan:** `@forelse`, `{{ $products->links() }}`, dan filter `$request->query('q')`.

---

## Method create

**Untuk apa:** menampilkan **form kosong** untuk data baru. GET. Belum menyimpan.

```php
public function create(): View
{
    return view('products.create');
}
```

Jika form butuh daftar kategori:

```php
public function create(): View
{
    $categories = Category::orderBy('nama')->get();

    return view('products.create', compact('categories'));
}
```

**Biasanya digabungkan dengan:** `old()` di input, `@csrf`, dan route `products.store`.

---

## Method store

**Untuk apa:** **menyimpan** data baru. POST.

```php
public function store(Request $request): RedirectResponse
{
    $data = $request->validate([
        'nama' => ['required', 'string', 'max:100'],
        'harga' => ['required', 'integer', 'min:0', 'max:1000000000'],
    ]);

    Product::create($data);

    return redirect()
        ->route('products.index')
        ->with('success', 'Produk berhasil ditambahkan.');
}
```

Hanya `$data` hasil validasi yang di-`create()`. Jangan `Product::create($request->all())` — mass assignment + field siluman.

Jika validasi gagal (request web): kembali ke form, input lama di `old()`, error di `@error`. Request JSON: 422.

**Biasanya digabungkan dengan:** `$fillable`, flash session, dan Form Request jika aturan panjang.

---

## Method show

**Untuk apa:** menampilkan **satu** data. GET.

```php
public function show(Product $product): View
{
    return view('products.show', compact('product'));
}
```

Binding sudah 404 jika id tidak ada. Eager load jika halaman butuh relasi:

```php
public function show(Product $product): View
{
    $product->load('category', 'comments.user');

    return view('products.show', compact('product'));
}
```

**Biasanya digabungkan dengan:** policy `view` dan `@auth` untuk tombol ubah.

---

## Method edit

**Untuk apa:** form **terisi** data lama. GET. Belum menulis database.

```php
public function edit(Product $product): View
{
    return view('products.edit', compact('product'));
}
```

Input:

```blade
<input name="nama" value="{{ old('nama', $product->nama) }}">
```

`old()` menang jika validasi update gagal; kalau tidak, pakai nilai model.

**Biasanya digabungkan dengan:** `@method('PUT')` dan route `products.update`.

---

## Method update

**Untuk apa:** menyimpan perubahan. PUT/PATCH.

```php
public function update(Request $request, Product $product): RedirectResponse
{
    $data = $request->validate([
        'nama' => ['required', 'string', 'max:100'],
        'harga' => ['required', 'integer', 'min:0'],
    ]);

    $product->update($data);

    return redirect()
        ->route('products.show', $product)
        ->with('success', 'Produk diperbarui.');
}
```

Unique saat update harus mengabaikan baris sendiri — lihat rule `unique` di file validasi.

**Biasanya digabungkan dengan:** `authorize('update', $product)` dan `unique:products,nama,'.$product->id`.

---

## Method destroy

**Untuk apa:** menghapus. DELETE.

```php
public function destroy(Product $product): RedirectResponse
{
    $product->delete();

    return redirect()
        ->route('products.index')
        ->with('success', 'Produk dihapus.');
}
```

Jika ada file di storage, hapus file dulu atau pakai observer. Relasi: tentukan `cascade` di migration atau hapus anak secara sadar.

**Biasanya digabungkan dengan:** policy `delete` dan `@method('DELETE')`.

---

## Controller invokable

**Untuk apa:** satu class = satu aksi. Cocok halaman khusus (dashboard kecil, export).

```bash
php artisan make:controller ShowLandingController --invokable
```

```php
public function __invoke(): View
{
    return view('landing');
}
```

```php
Route::get('/', ShowLandingController::class);
```

Tidak perlu menyebut method.

**Biasanya digabungkan dengan:** route tunggal yang tidak masuk resource.

---

## Dependency injection

**Untuk apa:** meminta Laravel mengisi parameter method dari container: `Request`, Form Request, service.

```php
public function store(StoreProductRequest $request): RedirectResponse
{
    Product::create($request->validated());

    return redirect()->route('products.index');
}
```

Jangan `new Request()`. Jangan mengambil `$_POST`.

Urutan parameter bebas selama type hint jelas. Tetap biasakan: request dulu, model kemudian — sesuai banyak contoh resmi.

**Biasanya digabungkan dengan:** route model binding dan interface service.

---

## Request $request

**Untuk apa:** satu objek untuk input, file, header, query, dan user.

```php
use Illuminate\Http\Request;

public function index(Request $request): View
{
    $q = $request->query('q', '');
    // ...
}
```

`$request->user()` adalah user login, atau `null` jika tamu.

**Biasanya digabungkan dengan:** validasi, `auth` middleware, dan query filter.

---

## all dan input

**Untuk apa:** membaca body/form/JSON.

```php
$request->all();                 // semua input (hati-hati)
$request->input('nama');         // satu kunci, web atau JSON
$request->input('alamat.kota');  // titik = bersarang
$request->input('nama', '');     // default
$request->string('nama')->trim(); // stringable (berguna merapikan)
$request->integer('harga');
```

`input()` melihat query + body. Untuk query saja, pakai `query()`.

**Biasanya digabungkan dengan:** `validate()` / `validated()`, bukan `create($request->all())`.

---

## query

**Untuk apa:** membaca `?kunci=nilai` pada URL.

```php
$q = $request->query('q');
$page = $request->query('page', 1);
```

Filter daftar:

```php
$products = Product::query()
    ->when($request->query('q'), function ($query, string $q) {
        $query->where('nama', 'like', '%'.$q.'%');
    })
    ->paginate(10)
    ->withQueryString();
```

`withQueryString()` menjaga `?q=` saat pindah halaman.

**Biasanya digabungkan dengan:** `paginate` dan form GET pencarian.

---

## only dan except

**Untuk apa:** mengambil sebagian kunci.

```php
$request->only(['nama', 'harga']);
$request->except(['_token', '_method']);
```

Ini **bukan** validasi. Kunci yang diminta tetap bisa berisi sampah. Tetap `validate` dulu, atau `only` setelah `validated()`:

```php
$data = $request->validate([...]);
// $data sudah terpotong ke kunci yang divalidasi
```

**Biasanya digabungkan dengan:** `$fillable` sebagai lapis kedua, bukan satu-satunya lapis.

---

## has, filled, missing, boolean

**Untuk apa:** memeriksa keberadaan dan isi tanpa ambiguitas `empty()`.

```php
$request->has('nama');      // kunci ada, meski ''
$request->filled('nama');   // ada dan tidak kosong
$request->missing('nama');  // kunci tidak ada
$request->boolean('aktif'); // "1", "true", "on", "yes" → true
```

Checkbox HTML yang tidak dicentang **tidak terkirim**. `boolean('aktif')` jadi `false` — cocok.

Hidden + checkbox:

```blade
<input type="hidden" name="aktif" value="0">
<input type="checkbox" name="aktif" value="1">
```

**Biasanya digabungkan dengan:** filter opsional dan field `nullable`.

---

## file dan hasFile

**Untuk apa:** unggahan.

```php
if ($request->hasFile('foto') && $request->file('foto')->isValid()) {
    $path = $request->file('foto')->store('produk', 'public');
}
```

Validasi dulu dengan `image`, `mimes`, `max` (kilobyte). Detail: [11-file-storage-pagination.md](11-file-storage-pagination.md).

**Biasanya digabungkan dengan:** `enctype="multipart/form-data"` pada form dan `storage:link`.

---

## header, method, wantsJson

**Untuk apa:** membaca meta request.

```php
$request->method();          // GET, POST, ...
$request->header('Accept');
$request->wantsJson();       // klien menginginkan JSON
$request->isMethod('post');
```

`wantsJson()` mempengaruhi apakah validasi gagal redirect atau 422 JSON.

**Biasanya digabungkan dengan:** API dan Inertia/fetch.

---

## validate di controller

**Untuk apa:** memeriksa input di tempat, cepat untuk aturan pendek.

```php
$data = $request->validate([
    'nama' => ['required', 'string', 'max:100'],
    'harga' => ['required', 'integer', 'min:0'],
]);
```

Bisa juga:

```php
$validated = $request->safe()->only(['nama', 'harga']);
```

setelah validate. Katalog rule: [04-validasi-rules-lengkap.md](04-validasi-rules-lengkap.md).

**Biasanya digabungkan dengan:** `create($data)` / `update($data)` dan pesan kustom.

---

## Form Request

**Untuk apa:** memindah aturan + otorisasi ke class sendiri jika controller mulai padat.

```bash
php artisan make:request StoreProductRequest
```

```php
<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;

class StoreProductRequest extends FormRequest
{
    public function authorize(): bool
    {
        return true; // atau $this->user()?->can('create', Product::class)
    }

    public function rules(): array
    {
        return [
            'nama' => ['required', 'string', 'max:100'],
            'harga' => ['required', 'integer', 'min:0'],
        ];
    }
}
```

```php
public function store(StoreProductRequest $request): RedirectResponse
{
    Product::create($request->validated());

    return redirect()->route('products.index');
}
```

Jika `authorize()` `false`: 403.

**Biasanya digabungkan dengan:** policy dan pesan `messages()` / `attributes()`.

---

## view dan compact

**Untuk apa:** merender Blade.

```php
return view('products.index', compact('products'));

return view('products.index', [
    'products' => $products,
    'q' => $q,
]);
```

`compact('products')` = `['products' => $products]`. Variabel harus sudah ada.

Salah: `compact($products)` (tanpa tanda kutip nama).

**Biasanya digabungkan dengan:** `@extends` layout dan data yang sudah di-paginate.

---

## redirect

**Untuk apa:** setelah **menulis** data, jangan tampilkan view dari POST (hindari resubmit). Arahkan ke GET.

```php
return redirect('/produk');
return redirect()->route('products.index');
return redirect()->route('products.show', $product);
return redirect()->action([ProductController::class, 'index']);
return redirect()->away('https://contoh.test'); // hati-hati, URL luar
```

Utamakan `route()` bernama.

**Biasanya digabungkan dengan:** `with('success', '...')` dan method `store`/`update`/`destroy`.

---

## back dan with

**Untuk apa:** kembali ke halaman sebelumnya, sering setelah gagal atau sukses kecil.

```php
return back()->with('success', 'Tersimpan');
return back()->withErrors(['nama' => 'Sudah dipakai']);
return back()->withInput(); // biasanya otomatis saat validasi gagal
```

Baca flash:

```blade
@if (session('success'))
    <p role="status">{{ session('success') }}</p>
@endif
```

`with()` memakai session. Request API murni biasanya tidak mengandalkan ini.

**Biasanya digabungkan dengan:** form web dan `@if (session('success'))`.

---

## response json

**Untuk apa:** API atau fetch.

```php
return response()->json(['data' => $products], 200);
return response()->json(['message' => 'Tersimpan'], 201);
return response()->json(['message' => 'Tidak boleh'], 403);
```

Lebih rapi: API Resource (file 10). Jangan `echo json_encode`.

**Biasanya digabungkan dengan:** `apiResource` dan header `Accept: application/json`.

---

## abort

**Untuk apa:** menghentikan request dengan kode HTTP.

```php
abort(404);
abort(403, 'Tidak boleh menghapus.');
abort_unless($product->aktif, 404);
abort_if($request->user()?->id !== $product->user_id, 403);
```

`findOrFail` sudah `abort(404)` secara internal.

**Biasanya digabungkan dengan:** pemeriksaan kasar sebelum policy lengkap, dan helper `abort` di file 13.

---

## download dan file

**Untuk apa:** mengirim file sebagai unduhan atau tampilan.

```php
return response()->download(storage_path('app/laporan.pdf'));
return response()->file(storage_path('app/public/foto.jpg'));
```

Pastikan path di dalam storage yang kamu kendalikan. Jangan `download($request->input('path'))` tanpa daftar putih.

**Biasanya digabungkan dengan:** disk `local` privat dan `auth`.

---

## Single action flow lengkap

Rangkaian yang sama dengan cheatsheet ringkas, dikumpulkan agar terlihat utuh.

```php
public function store(Request $request): RedirectResponse
{
    $data = $request->validate([
        'nama' => ['required', 'string', 'max:100'],
        'harga' => ['required', 'integer', 'min:0', 'max:1000000000'],
    ]);

    Product::create($data);

    return redirect()
        ->route('products.index')
        ->with('success', 'Produk berhasil ditambahkan.');
}
```

Urutan yang dijaga:

1. Validasi
2. Tulis database
3. Redirect + pesan
4. GET `index` membaca data baru

**Biasanya digabungkan dengan:** Blade form + `@error` + `@forelse`.

---

## Kesalahan controller

| Gejala | Penyebab umum |
| --- | --- |
| View error undefined variable | Lupa `compact` / salah nama |
| 404 di show | Binding gagal atau id salah |
| 419 di store | Lupa `@csrf` |
| Data tidak tersimpan | Gagal validasi (kembali diam-diam) atau `$fillable` kosong |
| Mass assignment exception | Field tidak di `$fillable` / `$guarded` |
| Halaman kosong setelah POST | Lupa `return` redirect/view |
| JSON jadi HTML login | Route web + session, bukan API |

Lanjut ke [aturan validasi](04-validasi-rules-lengkap.md).
