# 02 — Routing: web, API, resource

[← Instalasi](01-install-struktur-folder.md) · [Daftar](README.md) · [Berikutnya: controller →](03-controller-request-response.md)

**Untuk apa routing:** memetakan **metode HTTP + URL** ke kode (closure atau controller). Tanpa route, URL tidak memanggil apa pun.

File utama: `routes/web.php` (halaman + form, ada session & CSRF). File API: `routes/api.php` setelah `php artisan install:api`.

Rujukan: [routing](https://laravel.com/docs/13.x/routing).

## Daftar isi

- [Route::get](#routeget)
- [Route::post](#routepost)
- [Route::put dan Route::patch](#routeput-dan-routepatch)
- [Route::delete](#routedelete)
- [Route::match dan Route::any](#routematch-dan-routeany)
- [Route::view](#routeview)
- [Route::redirect](#routeredirect)
- [Closure vs controller](#closure-vs-controller)
- [Parameter wajib](#parameter-wajib)
- [Parameter opsional](#parameter-opsional)
- [where — batasan parameter](#where--batasan-parameter)
- [Nama route](#nama-route)
- [Route::resource](#routeresource)
- [Route::apiResource](#routeapiresource)
- [Hanya sebagian aksi resource](#hanya-sebagian-aksi-resource)
- [Route model binding implisit](#route-model-binding-implisit)
- [Binding dengan kolom lain](#binding-dengan-kolom-lain)
- [scoped binding](#scoped-binding)
- [Grup prefix](#grup-prefix)
- [Grup name](#grup-name)
- [Grup middleware](#grup-middleware)
- [Grup controller](#grup-controller)
- [routes/api.php](#routesapiphp)
- [fallback](#fallback)
- [route:list](#routelist)
- [CSRF pada route web](#csrf-pada-route-web)
- [Urutan route](#urutan-route)
- [Kesalahan routing](#kesalahan-routing)

---

## Route::get

**Untuk apa:** membaca halaman atau data. Browser yang membuka URL, tautan `<a>`, dan `fetch` GET memakai ini. **Tidak** untuk menyimpan form (form simpan pakai POST).

```php
use Illuminate\Support\Facades\Route;

Route::get('/produk', function () {
    return 'Daftar produk';
});
```

Dengan controller:

```php
use App\Http\Controllers\ProductController;

Route::get('/produk', [ProductController::class, 'index']);
```

GET boleh punya query string (`/produk?q=buku`) tanpa ditulis di path. Baca di controller: `$request->query('q')`.

**Biasanya digabungkan dengan:** `view()`, `paginate()`, dan `->name('products.index')`.

---

## Route::post

**Untuk apa:** membuat data baru atau mengirim form. Browser mengirim body. Route web POST wajib token CSRF (`@csrf`).

```php
Route::post('/produk', [ProductController::class, 'store'])
    ->name('products.store');
```

Form:

```blade
<form method="POST" action="{{ route('products.store') }}">
    @csrf
    <input name="nama" required>
    <button type="submit">Simpan</button>
</form>
```

Jangan memakai GET untuk menulis database. GET bisa di-prefetch, di-cache, atau tersimpan di riwayat.

**Biasanya digabungkan dengan:** `$request->validate()`, `Model::create()`, `redirect()->route(...)`.

---

## Route::put dan Route::patch

**Untuk apa:** memperbarui data yang sudah ada. `PUT` sering diartikan "ganti utuh", `PATCH` "sebagian". Di form HTML biasa keduanya disimulasikan dengan `@method` karena HTML hanya mudah mengirim GET/POST.

```php
Route::put('/produk/{product}', [ProductController::class, 'update'])
    ->name('products.update');

Route::patch('/produk/{product}', [ProductController::class, 'update']);
```

Form:

```blade
<form method="POST" action="{{ route('products.update', $product) }}">
    @csrf
    @method('PUT')
    <input name="nama" value="{{ old('nama', $product->nama) }}">
    <button type="submit">Ubah</button>
</form>
```

API JSON bisa mengirim `PUT`/`PATCH` langsung tanpa spoofing.

**Biasanya digabungkan dengan:** `@method('PUT')`, validasi, `$product->update($data)`.

---

## Route::delete

**Untuk apa:** menghapus data.

```php
Route::delete('/produk/{product}', [ProductController::class, 'destroy'])
    ->name('products.destroy');
```

Form hapus:

```blade
<form method="POST" action="{{ route('products.destroy', $product) }}">
    @csrf
    @method('DELETE')
    <button type="submit">Hapus {{ $product->nama }}</button>
</form>
```

Jangan membuat tautan GET `/produk/1/hapus` yang langsung menghapus. Bot/prefetch bisa memicu penghapusan.

**Biasanya digabungkan dengan:** policy `delete`, konfirmasi di UI, dan `$product->delete()`.

---

## Route::match dan Route::any

**Untuk apa:** satu URL untuk beberapa metode, atau (jarang) semua metode.

```php
Route::match(['get', 'post'], '/kontak', [ContactController::class, 'handle']);

Route::any('/webhook-latihan', [WebhookController::class, 'handle']);
```

`any` terlalu longgar untuk halaman biasa. Lebih jelas menulis `get`/`post` terpisah.

**Biasanya digabungkan dengan:** webhook atau form yang sama untuk tampil + kirim (tetap lebih rapi dipisah `create` + `store`).

---

## Route::view

**Untuk apa:** menampilkan view statis tanpa controller.

```php
Route::view('/tentang', 'pages.tentang');
Route::view('/halo', 'pages.halo', ['nama' => 'Haikal']);
```

Hanya untuk halaman tanpa query database. Kalau butuh data dari model, pakai controller.

**Biasanya digabungkan dengan:** halaman kebijakan, tentang, atau placeholder.

---

## Route::redirect

**Untuk apa:** memindahkan URL lama ke URL baru.

```php
Route::redirect('/produk-lama', '/produk');
Route::permanentRedirect('/blog', '/artikel'); // 301
```

Bukan pengganti `redirect()` di controller setelah simpan data.

**Biasanya digabungkan dengan:** mengganti path tanpa memutus bookmark.

---

## Closure vs controller

**Untuk apa:** memilih tempat menaruh logika.

Closure (cepat, latihan kecil):

```php
Route::get('/halo/{nama}', function (string $nama) {
    return response()->json(['pesan' => "Halo, {$nama}"]);
});
```

Controller (tugas nyata):

```php
Route::get('/produk', [ProductController::class, 'index']);
```

Kalau closure sudah berisi validasi + query + redirect, pindahkan. File route harus mudah dibaca sebagai daftar URL.

**Biasanya digabungkan dengan:** `make:controller` dan import class sekali di atas file.

---

## Parameter wajib

**Untuk apa:** mengambil potongan URL, misalnya id atau slug.

```php
Route::get('/produk/{id}', function (string $id) {
    return $id;
});
```

Nama `{id}` harus sama dengan parameter fungsi. Dengan binding model:

```php
Route::get('/produk/{product}', [ProductController::class, 'show'])
    ->name('products.show');
```

```php
public function show(Product $product)
{
    return view('products.show', compact('product'));
}
```

`{product}` + `Product $product` → Laravel mencari id, 404 jika tidak ada.

**Biasanya digabungkan dengan:** `findOrFail` jika tidak memakai binding, atau policy `view`.

---

## Parameter opsional

**Untuk apa:** potongan URL yang boleh tidak ada.

```php
Route::get('/laporan/{tahun?}', function (?string $tahun = null) {
    return $tahun ?? 'tahun ini';
});
```

Parameter opsional harus di **belakang**. `{tahun?}/{bulan}` membingungkan router.

**Biasanya digabungkan dengan:** nilai default di controller dan query filter (`?tahun=2026` sering lebih fleksibel daripada path opsional).

---

## where — batasan parameter

**Untuk apa:** menolak URL yang bentuknya salah sebelum masuk controller. Bukan pengganti validasi form.

```php
Route::get('/produk/{id}', [ProductController::class, 'show'])
    ->whereNumber('id');

Route::get('/halaman/{slug}', [PageController::class, 'show'])
    ->where('slug', '[a-z0-9-]+');
```

Helper: `whereNumber`, `whereAlpha`, `whereAlphaNumeric`, `whereUuid`.

Jika tidak cocok, Laravel mencari route lain atau 404 — bukan 422 validasi.

**Biasanya digabungkan dengan:** slug artikel dan id numerik.

---

## Nama route

**Untuk apa:** menyebut route tanpa mengulang path di Blade/controller. Path bisa berubah; nama tetap.

```php
Route::get('/produk', [ProductController::class, 'index'])
    ->name('products.index');
```

Pakai:

```php
route('products.index');
route('products.show', $product);
route('products.show', ['product' => $product]);
redirect()->route('products.index');
```

```blade
<a href="{{ route('products.index') }}">Daftar</a>
```

Jangan hardcode `/produk` di banyak view. Nama yang bentrok (`->name` sama dua kali) membuat yang satu menimpa.

**Biasanya digabungkan dengan:** `redirect()->route()`, `action` form, dan tes `$this->get(route('...'))`.

---

## Route::resource

**Untuk apa:** memasang tujuh route CRUD web sekaligus: index, create, store, show, edit, update, destroy.

```php
Route::resource('produk', ProductController::class)
    ->parameters(['produk' => 'product']);
```

Tanpa `parameters`, nama parameter mengikuti nama resource (`produk` → `{produk}`). Model `Product` lebih nyaman dengan `{product}`.

Nama resource `products` (Inggris, jamak) adalah konvensi umum:

```php
Route::resource('products', ProductController::class);
```

Tujuh URL (nama resource `products`):

| Metode | Path | Nama | Method controller |
| --- | --- | --- | --- |
| GET | `/products` | `products.index` | `index` |
| GET | `/products/create` | `products.create` | `create` |
| POST | `/products` | `products.store` | `store` |
| GET | `/products/{product}` | `products.show` | `show` |
| GET | `/products/{product}/edit` | `products.edit` | `edit` |
| PUT/PATCH | `/products/{product}` | `products.update` | `update` |
| DELETE | `/products/{product}` | `products.destroy` | `destroy` |

Buat controller: `php artisan make:controller ProductController --resource`.

**Biasanya digabungkan dengan:** view `create`/`edit`/`index`/`show` dan policy.

---

## Route::apiResource

**Untuk apa:** resource tanpa halaman form (`create`/`edit`). Cocok JSON.

```php
Route::apiResource('products', Api\ProductController::class);
```

Method yang dipasang: `index`, `store`, `show`, `update`, `destroy`.

Controller: `php artisan make:controller Api/ProductController --api`.

**Biasanya digabungkan dengan:** `ProductResource`, validasi, dan middleware `auth:sanctum`.

---

## Hanya sebagian aksi resource

**Untuk apa:** tidak memasang URL yang tidak kamu tulis.

```php
Route::resource('products', ProductController::class)
    ->only(['index', 'store', 'destroy']);

Route::resource('products', ProductController::class)
    ->except(['show']);
```

Lebih aman daripada memasang `show` kosong yang 500.

**Biasanya digabungkan dengan:** tugas yang hanya daftar + tambah + hapus.

---

## Route model binding implisit

**Untuk apa:** mengganti `findOrFail($id)` manual.

```php
Route::get('/produk/{product}', [ProductController::class, 'show']);
```

```php
use App\Models\Product;

public function show(Product $product)
{
    return $product;
}
```

Syarat:

- Nama parameter route ≈ nama variabel (`{product}` dan `$product`)
- Type hint class model
- Kunci default: kolom `id` (atau `getRouteKeyName()`)

Jika tidak ketemu: 404. Tidak perlu `if (! $product)`.

**Biasanya digabungkan dengan:** policy dan `compact('product')` ke Blade.

---

## Binding dengan kolom lain

**Untuk apa:** URL memakai slug, bukan id.

```php
Route::get('/artikel/{article:slug}', [ArticleController::class, 'show']);
```

Atau di model:

```php
public function getRouteKeyName(): string
{
    return 'slug';
}
```

Pastikan kolom unik. Dua slug sama = baris yang salah bisa terambil (`first`).

**Biasanya digabungkan dengan:** `unique` pada `slug` di validasi/migration.

---

## scoped binding

**Untuk apa:** memastikan anak milik induk. Contoh: komentar hanya dari post terkait.

```php
Route::get('/posts/{post}/comments/{comment}', [CommentController::class, 'show'])
    ->scopeBindings();
```

Laravel mengecek `$post->comments` berisi `$comment`. Jika komentar id 5 milik post lain, 404.

**Biasanya digabungkan dengan:** relasi `hasMany` / `belongsTo` yang konsisten.

---

## Grup prefix

**Untuk apa:** menambahkan awalan path ke banyak route.

```php
Route::prefix('admin')->group(function () {
    Route::get('/produk', [Admin\ProductController::class, 'index']);
    // URL: /admin/produk
});
```

**Biasanya digabungkan dengan:** `middleware('auth')` dan `name('admin.')`.

---

## Grup name

**Untuk apa:** awalan nama route.

```php
Route::name('admin.')->prefix('admin')->group(function () {
    Route::get('/produk', [Admin\ProductController::class, 'index'])
        ->name('products.index');
    // nama: admin.products.index
});
```

Pakai `route('admin.products.index')`.

**Biasanya digabungkan dengan:** layout admin dan middleware.

---

## Grup middleware

**Untuk apa:** memasang pemeriksa ke banyak URL.

```php
Route::middleware(['auth'])->group(function () {
    Route::resource('products', ProductController::class);
});
```

Satu route:

```php
Route::get('/profil', [ProfileController::class, 'edit'])
    ->middleware('auth')
    ->name('profile.edit');
```

Detail middleware: [09-middleware-auth-gate-policy.md](09-middleware-auth-gate-policy.md).

**Biasanya digabungkan dengan:** `can:update,product`, `verified`, `throttle`.

---

## Grup controller

**Untuk apa:** menghindari mengulang nama class.

```php
Route::controller(ProductController::class)->group(function () {
    Route::get('/produk', 'index')->name('products.index');
    Route::post('/produk', 'store')->name('products.store');
});
```

**Biasanya digabungkan dengan:** resource yang tidak penuh atau rute tambahan di luar resource.

---

## routes/api.php

**Untuk apa:** endpoint untuk frontend terpisah (React/Next) atau klien JSON.

Setelah `php artisan install:api`, route di file ini biasanya berprefix `/api` dan memakai middleware grup `api` (throttle, binding, tanpa CSRF form).

```php
use App\Http\Controllers\Api\ProductController;
use Illuminate\Support\Facades\Route;

Route::get('/produk', [ProductController::class, 'index']);
// URL: /api/produk
```

Klien mengirim header `Accept: application/json` agar error validasi jadi JSON 422, bukan redirect.

**Biasanya digabungkan dengan:** CORS, API Resource, dan token (Sanctum) jika bukan publik.

---

## fallback

**Untuk apa:** menangkap URL yang tidak cocok route lain. Harus di **paling bawah**.

```php
Route::fallback(function () {
    return response()->view('errors.404', [], 404);
});
```

Laravel sudah punya halaman 404. Fallback hanya jika kamu ingin perilaku khusus.

**Biasanya digabungkan dengan:** log URL aneh, bukan untuk mengganti `show` yang 404 karena id tidak ada.

---

## route:list

**Untuk apa:** melihat semua URL yang benar-benar terdaftar.

```bash
php artisan route:list
php artisan route:list --path=produk
php artisan route:list --name=products
```

Kolom: method, URI, nama, aksi, middleware. Jika 404 padahal "sudah ditulis", cek typo path atau file route yang tidak dimuat.

**Biasanya digabungkan dengan:** debugging "kenapa halaman tidak ketemu".

---

## CSRF pada route web

**Untuk apa:** menolak POST/PUT/PATCH/DELETE dari form tanpa token. Grup `web` mengaktifkannya.

Gejala: status **419** Page Expired.

Obat form: `@csrf`. Jangan mematikan CSRF untuk halaman login/form biasa.

Route API token-based tidak memakai CSRF form yang sama. SPA first-party Sanctum punya alur cookie + CSRF sendiri — ikuti dokumen Sanctum jika itu tugasmu.

**Biasanya digabungkan dengan:** `@method` dan session login.

---

## Urutan route

**Untuk apa:** menghindari route umum menelan route khusus.

```php
// Salah urutan: {product} bisa menelan "create" sebagai id
Route::get('/produk/{product}', [ProductController::class, 'show']);
Route::get('/produk/create', [ProductController::class, 'create']);
```

`Route::resource` sudah mengurutkan `create` sebelum `{product}`. Jika menulis manual, taruh path statis dulu.

**Biasanya digabungkan dengan:** `whereNumber('product')` sebagai jaring pengaman.

---

## Kesalahan routing

| Gejala | Cek |
| --- | --- |
| 404 | Path, method, `route:list`, prefix `/api` |
| 405 Method Not Allowed | POST ke route yang hanya GET, atau sebaliknya |
| 419 | Lupa `@csrf` |
| Class not found | Lupa `use` controller |
| Binding 404 | Id tidak ada, atau nama parameter ≠ variabel |
| Nama route salah | Typo di `route('...')` |

Lanjut ke [controller, request, response](03-controller-request-response.md).
