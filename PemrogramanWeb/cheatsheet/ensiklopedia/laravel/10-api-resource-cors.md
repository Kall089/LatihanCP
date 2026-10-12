# 10 — API Resource dan CORS

[← Middleware](09-middleware-auth-gate-policy.md) · [Daftar](README.md) · [Berikutnya: file & pagination →](11-file-storage-pagination.md)

**Untuk apa API Resource:** merapikan JSON yang dikirim ke frontend. Model `toArray()` mudah membocorkan kolom (`password` terlupakan di `$hidden`, relasi berat, nama internal). Resource memilih field secara sadar.

**Untuk apa CORS:** mengizinkan browser di origin lain (misalnya `http://localhost:3000`) memanggil API Laravel (`http://127.0.0.1:8000`). Tanpa CORS, `fetch` lintas origin ditolak browser.

Rujukan: [eloquent-resources](https://laravel.com/docs/13.x/eloquent-resources), [Sanctum](https://laravel.com/docs/13.x/sanctum) (jika butuh auth SPA), dokumentasi CORS Laravel pada versi yang kamu pasang.

## Daftar isi

- [install:api](#installapi)
- [Membuat Resource](#membuat-resource)
- [toArray satu model](#toarray-satu-model)
- [Resource::collection](#resourcecollection)
- [ResourceCollection khusus](#resourcecollection-khusus)
- [when dan whenLoaded](#when-dan-whenloaded)
- [whenHas dan mergeWhen](#whenhas-dan-mergewhen)
- [additional meta](#additional-meta)
- [wrap data](#wrap-data)
- [Pagination + Resource](#pagination--resource)
- [Controller API contoh](#controller-api-contoh)
- [Status HTTP API](#status-http-api)
- [Header Accept](#header-accept)
- [CORS untuk apa](#cors-untuk-apa)
- [Mengatur CORS](#mengatur-cors)
- [SPA same-domain vs beda origin](#spa-same-domain-vs-beda-origin)
- [Kesalahan API/CORS](#kesalahan-apicors)

---

## install:api

**Untuk apa:** memasang routing API di proyek Laravel 11/13 yang belum punya `routes/api.php`.

```bash
php artisan install:api
```

Setelah itu `bootstrap/app.php` memuat file API. Prefix default `/api`.

Tanpa langkah ini, menulis `routes/api.php` sendiri bisa tidak terdaftar.

**Biasanya digabungkan dengan:** `Route::apiResource` dan `auth:sanctum` jika endpoint tidak publik.

---

## Membuat Resource

**Untuk apa:** class yang mengubah model jadi array JSON.

```bash
php artisan make:resource ProductResource
php artisan make:resource ProductCollection
```

File: `app/Http/Resources/ProductResource.php`.

**Biasanya digabungkan dengan:** model `Product` dan controller API.

---

## toArray satu model

**Untuk apa:** menentukan field satu produk.

```php
<?php

namespace App\Http\Resources;

use Illuminate\Http\Request;
use Illuminate\Http\Resources\Json\JsonResource;

class ProductResource extends JsonResource
{
    public function toArray(Request $request): array
    {
        return [
            'id' => $this->id,
            'nama' => $this->nama,
            'harga' => $this->harga,
            'stok' => $this->stok,
            'kategori' => $this->whenLoaded('category', fn () => [
                'id' => $this->category->id,
                'nama' => $this->category->nama,
            ]),
            'dibuat' => $this->created_at?->toIso8601String(),
        ];
    }
}
```

Di dalam Resource, `$this->nama` adalah `$this->resource->nama`.

Pakai:

```php
return new ProductResource($product);
```

**Biasanya digabungkan dengan:** `whenLoaded` agar N+1 tidak terjadi diam-diam, dan `$product->load('category')` / `with('category')`.

---

## Resource::collection

**Untuk apa:** membungkus daftar.

```php
return ProductResource::collection($products);
```

`$products` boleh Collection atau paginator. Jangan loop `new ProductResource` manual kecuali ada alasan.

**Biasanya digabungkan dengan:** `index` API dan `paginate()`.

---

## ResourceCollection khusus

**Untuk apa:** menambah ringkasan di sekeliling daftar.

```php
class ProductCollection extends ResourceCollection
{
    public function toArray(Request $request): array
    {
        return [
            'data' => ProductResource::collection($this->collection),
            'meta_toko' => ['mata_uang' => 'IDR'],
        ];
    }
}
```

```php
return new ProductCollection($products);
```

**Biasanya digabungkan dengan:** daftar yang butuh statistik tambahan, bukan hanya item.

---

## when dan whenLoaded

**Untuk apa:** menyertakan kunci hanya jika syarat terpenuhi / relasi sudah di-load.

```php
'email' => $this->when($request->user()?->id === $this->user_id, $this->email),

'kategori' => new CategoryResource($this->whenLoaded('category')),
```

Tanpa `whenLoaded`, mengakses `$this->category` memicu lazy load (N+1).

**Biasanya digabungkan dengan:** field sensitif dan relasi opsional.

---

## whenHas dan mergeWhen

**Untuk apa:** field yang hanya ada kadang (aksesor, count).

```php
'jumlah_komentar' => $this->whenCounted('comments'),

$this->mergeWhen($request->user()?->peran === 'admin', [
    'catatan_internal' => $this->catatan_internal,
]);
```

**Biasanya digabungkan dengan:** `withCount('comments')` di query.

---

## additional meta

**Untuk apa:** menempel meta tanpa mengubah `toArray` item.

```php
return (new ProductResource($product))
    ->additional(['meta' => ['versi' => '1']]);
```

**Biasanya digabungkan dengan:** versi API atau tautan terkait.

---

## wrap data

**Untuk apa:** membungkus output dengan kunci `data` (default banyak Resource).

```php
class ProductResource extends JsonResource
{
    public static $wrap = 'data';
}
```

Matikan:

```php
JsonResource::withoutWrapping(); // AppServiceProvider
```

Pilih satu gaya dan tetap konsisten agar frontend tidak bingung `data` vs objek datar.

**Biasanya digabungkan dengan:** kontrak frontend (TypeScript/interface).

---

## Pagination + Resource

**Untuk apa:** JSON daftar yang punya `links` dan `meta` halaman.

```php
$products = Product::with('category')->paginate(10);

return ProductResource::collection($products);
```

Bentuk khas:

```json
{
  "data": [ { "id": 1, "nama": "Buku" } ],
  "links": { "first": "...", "last": "...", "prev": null, "next": "..." },
  "meta": { "current_page": 1, "per_page": 10, "total": 23 }
}
```

Frontend memakai `meta.current_page` / `links.next`. Jangan merakit pagination manual jika sudah ada.

**Biasanya digabungkan dengan:** `withQueryString()` jika ada filter, dan file pagination 11.

---

## Controller API contoh

```php
<?php

namespace App\Http\Controllers\Api;

use App\Http\Controllers\Controller;
use App\Http\Resources\ProductResource;
use App\Models\Product;
use Illuminate\Http\Request;

class ProductController extends Controller
{
    public function index(Request $request)
    {
        $products = Product::query()
            ->with('category')
            ->when($request->query('q'), fn ($q, $term) => $q->where('nama', 'like', '%'.$term.'%'))
            ->latest()
            ->paginate(10)
            ->withQueryString();

        return ProductResource::collection($products);
    }

    public function store(Request $request)
    {
        $data = $request->validate([
            'nama' => ['required', 'string', 'max:100'],
            'harga' => ['required', 'integer', 'min:0'],
        ]);

        $product = Product::create($data);

        return (new ProductResource($product))
            ->response()
            ->setStatusCode(201);
    }

    public function show(Product $product)
    {
        $product->load('category');

        return new ProductResource($product);
    }

    public function update(Request $request, Product $product)
    {
        $data = $request->validate([
            'nama' => ['required', 'string', 'max:100'],
            'harga' => ['required', 'integer', 'min:0'],
        ]);

        $product->update($data);

        return new ProductResource($product->fresh('category'));
    }

    public function destroy(Product $product)
    {
        $product->delete();

        return response()->noContent();
    }
}
```

```php
Route::apiResource('products', \App\Http\Controllers\Api\ProductController::class);
```

URL: `/api/products`.

**Biasanya digabungkan dengan:** `auth:sanctum` pada `store`/`update`/`destroy` jika tidak publik.

---

## Status HTTP API

| Kode | Kapan |
| --- | --- |
| 200 | Baca / update sukses |
| 201 | Store sukses |
| 204 | Hapus tanpa body |
| 401 | Belum autentikasi |
| 403 | Autentikasi ada, izin tidak |
| 404 | Binding gagal |
| 422 | Validasi gagal |
| 429 | Throttle |
| 500 | Bug server |

Jangan mengembalikan 200 untuk semua, termasuk error.

**Biasanya digabungkan dengan:** `abort(403)` dan validasi otomatis 422.

---

## Header Accept

**Untuk apa:** meminta Laravel merespons JSON saat error.

```http
Accept: application/json
Content-Type: application/json
```

Tanpa `Accept: application/json`, validasi gagal pada route web-like bisa berupa redirect HTML — klien `fetch` bingung.

**Biasanya digabungkan dengan:** `fetch` / Axios di React/Next dan CORS.

---

## CORS untuk apa

Browser memblokir JS di origin A yang membaca respons origin B, kecuali B mengizinkan lewat header CORS.

Contoh:

- Frontend Vite/React: `http://localhost:5173`
- Laravel: `http://127.0.0.1:8000`

Ini beda origin. `fetch('http://127.0.0.1:8000/api/products')` butuh CORS.

Bukan masalah jika:

- Blade disajikan Laravel yang sama
- Next.js memanggil Laravel lewat server (bukan browser) — CORS tidak berlaku di server-ke-server

**Biasanya digabungkan dengan:** API JSON dan frontend terpisah.

---

## Mengatur CORS

**Untuk apa:** menyebut origin, method, dan header yang diizinkan.

Proyek Laravel modern memakai konfigurasi CORS (file `config/cors.php` setelah dipublikasikan, atau default framework). Pola umum:

```php
'paths' => ['api/*', 'sanctum/csrf-cookie'],
'allowed_methods' => ['*'],
'allowed_origins' => ['http://localhost:5173', 'http://localhost:3000'],
'allowed_headers' => ['*'],
'supports_credentials' => true, // jika cookie/Sanctum
```

Jangan `allowed_origins = ['*']` plus `supports_credentials = true` — browser menolak kombinasi itu, dan itu longgar untuk produksi.

Setelah ubah config: `php artisan config:clear`.

**Biasanya digabungkan dengan:** `APP_URL`, daftar origin frontend, dan Sanctum `stateful` domains jika cookie.

---

## SPA same-domain vs beda origin

| Pola | CORS | Auth khas |
| --- | --- | --- |
| Blade di Laravel | tidak perlu | session + CSRF |
| SPA + API beda port | perlu | token atau Sanctum cookie + origin |
| Next server fetch Laravel | tidak (server) | token rahasia di server |

Untuk kuliah: jika frontend terpisah, izinkan origin latihan secara eksplisit. Jangan meniru `*` di produksi.

**Biasanya digabungkan dengan:** `auth:sanctum` atau token Bearer sederhana sesuai tugas.

---

## Kesalahan API/CORS

| Gejala | Obat |
| --- | --- |
| HTML login saat fetch | `Accept: application/json` / route API + token |
| 404 `/products` | lupa prefix `/api` |
| CORS error di console browser | origin belum diizinkan, atau preflight OPTIONS gagal |
| Cookie tidak terkirim | `credentials: 'include'` + origin + `supports_credentials` |
| Password bocor di JSON | Resource + `$hidden`, jangan `return $user` mentah |
| N+1 di API | `with` + `whenLoaded` |
| 201 tanpa Location | opsional; status 201 sudah cukup banyak tugas |

Lanjut ke [file storage dan pagination](11-file-storage-pagination.md).
