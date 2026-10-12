# Cheatsheet Laravel

[← Daftar panduan](README.md) · [Bekal PHP](php.md) · [Cara menggabungkan teknologi](kombinasi-teknologi.md)

Laravel adalah framework PHP untuk pekerjaan **di server**: menerima permintaan, memeriksa input, membaca/menyimpan database, dan mengembalikan HTML atau JSON.

## Daftar isi

- [Persiapan](#persiapan)
- [Alur request dan lokasi kode](#alur-request-dan-lokasi-kode)
- [Routing](#routing)
- [Membuat model migration dan controller](#membuat-model-migration-dan-controller)
- [Migration](#migration)
- [Model dan mass assignment](#model-dan-mass-assignment)
- [Controller dan validasi](#controller-dan-validasi)
- [Blade dan formulir](#blade-dan-formulir)
- [Query Eloquent](#query-eloquent)
- [Endpoint API untuk frontend](#endpoint-api-untuk-frontend)
- [Relasi database](#relasi-database)
- [Autentikasi dan otorisasi](#autentikasi-dan-otorisasi)
- [Route resource](#route-resource)
- [Form Request](#form-request)
- [Pagination](#pagination)
- [Factory dan seeder](#factory-dan-seeder)
- [Unggah file](#unggah-file)
- [API Resource](#api-resource)
- [Perintah praktis](#perintah-praktis)
- [Kesalahan umum](#kesalahan-umum)

Bagian model sampai Blade membentuk **satu contoh berurutan**: menampilkan, menambah, dan menghapus produk. Jalankan di proyek latihan lokal. Contoh belum memakai akun/izin pengguna, sehingga belum ditujukan menjadi panel admin publik.

## Persiapan

**Untuk apa:** membuat proyek backend PHP. Siapkan PHP dan Composer yang memenuhi persyaratan Laravel pilihanmu, serta ekstensi database yang dipakai. Node/npm dibutuhkan jika membangun aset frontend lewat Vite. [Panduan instalasi Laravel](https://laravel.com/docs/13.x/installation).

```bash
composer create-project laravel/laravel latihan-laravel "^13.0"
cd latihan-laravel
php artisan serve
```

Perintah di atas membuat proyek baru; jangan dijalankan dengan nama folder proyek yang sudah berisi pekerjaanmu. Buka URL terminal, biasanya `http://127.0.0.1:8000`. Untuk contoh Blade sederhana di sini, kita tidak memakai `@vite`, sehingga server frontend terpisah tidak diperlukan.

Contoh memakai SQLite. Pastikan `.env` berisi `DB_CONNECTION=sqlite`, file `database/database.sqlite` tersedia, dan tidak ada `DB_DATABASE` yang menunjuk lokasi lain. Jika file belum dibuat oleh installer, buat file kosong tersebut. Database MySQL/PostgreSQL dapat dipakai dengan mengubah konfigurasi koneksi dan membuat database yang sesuai.

**Biasanya digabungkan dengan:** Blade + CSS/JavaScript untuk satu aplikasi web, atau React/Next.js sebagai frontend yang meminta API Laravel.

## Alur request dan lokasi kode

```text
Browser → route → controller → model → database
                         ↓
                  Blade (HTML) atau JSON → browser
```

- `routes/web.php`: route halaman dan formulir web.
- `routes/api.php`: route API setelah dukungan API dipasang.
- `app/Http/Controllers/`: tempat menangani permintaan.
- `app/Models/`: representasi data/tabel melalui Eloquent.
- `database/migrations/`: riwayat perubahan struktur database.
- `resources/views/`: template Blade, berakhiran `.blade.php`.
- `.env`: konfigurasi lingkungan lokal; jangan commit kredensial.

**Biasanya digabungkan dengan:** pola MVC (Model–View–Controller), agar urusan database, tampilan, dan penanganan request lebih terpisah.

## Routing

**Untuk apa:** menentukan kode yang dijalankan untuk URL dan metode HTTP tertentu.

Tambahkan ke `routes/web.php`, setelah `<?php` yang sudah ada:

```php
use Illuminate\Support\Facades\Route;

Route::get('/halo/{nama}', function (string $nama) {
    return response()->json(['pesan' => "Halo, {$nama}!"]);
});
```

Jika import `Route` sudah ada, jangan tulis dua kali. Kunjungi `/halo/Haikal`. `GET` digunakan untuk membaca, `POST` membuat, `PATCH/PUT` memperbarui, dan `DELETE` menghapus. Metode ini menunjukkan maksud request; implementasi tetap perlu ditulis.

**Biasanya digabungkan dengan:** controller, nama route untuk tautan/form, dan middleware. [Rujukan routing](https://laravel.com/docs/13.x/routing).

## Membuat model migration dan controller

**Untuk apa:** menghasilkan kerangka file dari terminal agar penamaan/lokasinya konsisten.

Di root proyek Laravel, buka terminal kedua jika server masih berjalan:

```bash
php artisan make:model Product -m
php artisan make:controller ProductController
```

`-m` membuat migration bersama model. Kita memakai nama model `Product`, tabel `products`, dan atribut bahasa Indonesia seperti `nama`/`harga`.

**Biasanya digabungkan dengan:** migration untuk struktur tabel dan controller untuk alur request berikutnya.

## Migration

**Untuk apa:** mencatat bentuk tabel dalam kode sehingga struktur database bisa dibuat secara konsisten.

Ganti isi `database/migrations/..._create_products_table.php` yang baru dibuat:

```php
<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration {
    public function up(): void
    {
        Schema::create('products', function (Blueprint $table) {
            $table->id();
            $table->string('nama', 100);
            $table->unsignedInteger('harga');
            $table->timestamps();
        });
    }

    public function down(): void
    {
        Schema::dropIfExists('products');
    }
};
```

Lalu jalankan:

```bash
php artisan migrate
```

`id()` membuat kunci utama. `timestamps()` menambah `created_at` dan `updated_at`. `harga` disimpan sebagai bilangan bulat rupiah pada contoh ini. `up()` menerapkan perubahan; `down()` membaliknya ketika migration di-rollback, sehingga bisa menghapus data tabel terkait.

**Biasanya digabungkan dengan:** model Eloquent dan sistem kontrol versi. Jika migration sudah dipakai di lingkungan bersama, buat migration baru untuk perubahan berikutnya.

## Model dan mass assignment

**Untuk apa:** membaca/menulis tabel melalui object PHP.

Ganti `app/Models/Product.php`:

```php
<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Product extends Model
{
    protected $fillable = ['nama', 'harga'];
}
```

Secara konvensi `Product` memakai tabel `products`. `$fillable` menentukan atribut yang boleh diisi lewat operasi mass assignment seperti `create()`/`update()` dengan array. Ini bukan validasi; data masih perlu diperiksa di controller. [Rujukan Eloquent](https://laravel.com/docs/13.x/eloquent).

**Biasanya digabungkan dengan:** controller, validasi, query, dan relasi.

## Controller dan validasi

**Untuk apa:** mengatur alur permintaan: baca data, validasi, simpan, lalu kirim respons.

Ganti `app/Http/Controllers/ProductController.php`:

```php
<?php

namespace App\Http\Controllers;

use App\Models\Product;
use Illuminate\Http\Request;

class ProductController extends Controller
{
    public function index()
    {
        $products = Product::latest()->paginate(10);
        return view('products.index', compact('products'));
    }

    public function store(Request $request)
    {
        $data = $request->validate([
            'nama' => ['required', 'string', 'max:100'],
            'harga' => ['required', 'integer', 'min:0', 'max:1000000000'],
        ]);

        Product::create($data);
        return redirect()->route('products.index')
            ->with('success', 'Produk berhasil ditambahkan.');
    }

    public function destroy(Product $product)
    {
        $product->delete();
        return redirect()->route('products.index')
            ->with('success', 'Produk berhasil dihapus.');
    }
}
```

`compact('products')` mengirim variabel ke view. `paginate(10)` membatasi jumlah item per halaman. `$request->validate()` mengembalikan data tervalidasi; hanya data itu yang diteruskan ke `create()`. Jika request web gagal validasi, Laravel mengarahkan kembali dengan pesan error; request yang mengharapkan JSON memperoleh respons validasi 422. [Rujukan validasi](https://laravel.com/docs/13.x/validation).

Tambahkan ke `routes/web.php` dengan import masing-masing hanya sekali:

```php
use App\Http\Controllers\ProductController;

Route::get('/produk', [ProductController::class, 'index'])->name('products.index');
Route::post('/produk', [ProductController::class, 'store'])->name('products.store');
Route::delete('/produk/{product}', [ProductController::class, 'destroy'])->name('products.destroy');
```

`{product}` dipasangkan dengan parameter `Product $product`; route model binding mencari data berdasarkan ID dan menghasilkan 404 jika tidak ada. Tipe dan nama parameter perlu sesuai.

**Biasanya digabungkan dengan:** Form Request ketika validasi makin besar, Blade untuk HTML, dan policy untuk pemeriksaan izin.

## Blade dan formulir

**Untuk apa:** menghasilkan HTML menggunakan data PHP dari controller.

Buat `resources/views/products/index.blade.php`:

```blade
<!doctype html>
<html lang="id">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Produk latihan</title>
</head>
<body>
    <main>
        <h1>Daftar produk</h1>

        @if (session('success'))
            <p role="status">{{ session('success') }}</p>
        @endif

        <form method="POST" action="{{ route('products.store') }}">
            @csrf
            <div>
                <label for="nama">Nama produk</label>
                <input id="nama" name="nama" value="{{ old('nama') }}" maxlength="100" required>
                @error('nama') <p role="alert">{{ $message }}</p> @enderror
            </div>
            <div>
                <label for="harga">Harga rupiah</label>
                <input id="harga" name="harga" type="number" min="0" max="1000000000"
                       step="1" value="{{ old('harga') }}" required>
                @error('harga') <p role="alert">{{ $message }}</p> @enderror
            </div>
            <button type="submit">Simpan</button>
        </form>

        <ul>
            @forelse ($products as $product)
                <li>
                    {{ $product->nama }} — Rp{{ number_format($product->harga, 0, ',', '.') }}
                    <form method="POST" action="{{ route('products.destroy', $product) }}">
                        @csrf
                        @method('DELETE')
                        <button type="submit">Hapus {{ $product->nama }}</button>
                    </form>
                </li>
            @empty
                <li>Belum ada produk.</li>
            @endforelse
        </ul>

        <nav aria-label="Halaman produk">
            @if ($products->previousPageUrl())
                <a href="{{ $products->previousPageUrl() }}">Sebelumnya</a>
            @endif
            <span>Halaman {{ $products->currentPage() }}</span>
            @if ($products->hasMorePages())
                <a href="{{ $products->nextPageUrl() }}">Berikutnya</a>
            @endif
        </nav>
    </main>
</body>
</html>
```

- `{{ ... }}` menampilkan nilai dengan escaping HTML. Hindari output mentah `{!! ... !!}` untuk masukan pengguna.
- `@csrf` menyertakan token perlindungan form web.
- `@method('DELETE')` menyatakan metode yang dituju meskipun form HTML dikirim sebagai POST.
- `old()` mengisi ulang data setelah validasi gagal.
- `@error` menampilkan error sebuah field; `@forelse` menyediakan keadaan daftar kosong.

Buka `/produk`, tambahkan dua produk, lalu hapus salah satunya. Muat ulang halaman: data yang tersimpan tetap ada karena berada di database.

**Biasanya digabungkan dengan:** CSS, JavaScript seperlunya, dan controller. Dengan Blade saja kamu sudah bisa membangun banyak aplikasi CRUD.

## Query Eloquent

**Untuk apa:** mencari, mengurutkan, dan mengubah data. Potongan berikut adalah resep terpisah yang dijalankan di kode controller atau Tinker, dengan `Product` sudah diimpor:

```php
use App\Models\Product;

$murah = Product::where('harga', '<', 50000)->orderBy('harga')->get();
$halaman = Product::orderBy('nama')->paginate(10);
$produk = Product::findOrFail(1);
$produk->update(['harga' => 42000]);
$jumlah = Product::count();
```

`get()` mengambil kumpulan hasil; `first()` mengambil satu hasil atau `null`; `findOrFail()` mencari primary key dan gagal dengan 404 pada request HTTP jika tidak ditemukan. Contoh update akan mengubah produk ID 1 bila tersedia; untuk input request tetap lakukan validasi dan otorisasi.

**Biasanya digabungkan dengan:** pencarian, filter, pagination, dan tampilan daftar. Gunakan parameter query builder untuk nilai masukan pengguna; jangan merangkai input menjadi SQL mentah.

## Endpoint API untuk frontend

**Untuk apa:** mengirim data JSON ke JavaScript/React/Next.js, tanpa membuat halaman HTML.

Jika proyek baru belum menyediakan `routes/api.php`, jalankan satu kali:

```bash
php artisan install:api
```

Perintah memasang dukungan API/Sanctum dan route terkait; ikuti instruksi migrasi yang ditampilkan. Tambahkan ke `routes/api.php`, di bawah `<?php`, tanpa menggandakan import yang sudah ada:

```php
use App\Models\Product;
use Illuminate\Support\Facades\Route;

Route::get('/produk', function () {
    return Product::query()
        ->select(['id', 'nama', 'harga'])
        ->orderBy('id')
        ->limit(50)
        ->get();
});
```

URL-nya `/api/produk` karena prefix API ditambahkan oleh konfigurasi standar. Endpoint contoh bersifat publik dan membatasi hasil sampai 50 item. Bentuk JSON berupa array yang cocok dengan contoh fetch pada panduan Next.js. Untuk daftar besar, pakai pagination dan sesuaikan frontend karena bentuk respons berubah, biasanya memiliki properti `data`.

**Biasanya digabungkan dengan:** fetch, API Resources untuk bentuk respons konsisten, serta Sanctum/policy untuk data terlindungi. Jika browser memanggil Laravel dari origin lain, konfigurasikan CORS di backend. Permintaan server Next.js ke Laravel tidak terkena aturan CORS browser.

## Relasi database

**Untuk apa:** menghubungkan data, misalnya satu kategori memiliki banyak produk.

Ini pengembangan lanjutan, **bukan bagian yang sudah tersedia pada contoh di atas**. Buat model/tabel `Category` (`categories`) dan kolom foreign key `products.category_id` terlebih dahulu; bila tabel sudah berisi data, rencanakan nilai awal atau gunakan kolom nullable.

Di class `Product`:

```php
public function category()
{
    return $this->belongsTo(\App\Models\Category::class);
}
```

Di class `Category`:

```php
public function products()
{
    return $this->hasMany(\App\Models\Product::class);
}
```

Di controller, setelah skema dan relasi tersedia:

```php
$products = \App\Models\Product::with('category')->paginate(10);
```

`with()` memuat relasi bersama daftar sehingga tidak perlu satu query kategori untuk setiap produk, pola masalah yang disebut N+1.

**Biasanya digabungkan dengan:** foreign key migration, halaman detail, dan eager loading.

## Autentikasi dan otorisasi

**Untuk apa:** membedakan “siapa pengguna ini?” dengan “bolehkah dia melakukan tindakan ini?”.

- Autentikasi: pengguna sudah login atau belum.
- Otorisasi: pengguna tersebut berhak melihat/mengubah data tertentu atau tidak.

Setelah sistem login dipasang, route dapat diberi middleware `auth`. Untuk API terlindungi gunakan mekanisme autentikasi yang sesuai, misalnya `auth:sanctum`. Di controller, cek policy melalui Gate sebelum mengubah data:

```php
\Illuminate\Support\Facades\Gate::authorize('delete', $product);
```

Potongan tersebut membutuhkan policy `ProductPolicy` dengan aturan `delete` yang sudah dibuat dan dikenali Laravel. Menambahkan baris ini saja bukan implementasi sistem izin. Lihat [autentikasi](https://laravel.com/docs/13.x/authentication) dan [otorisasi Laravel](https://laravel.com/docs/13.x/authorization) untuk pengembangan.

**Biasanya digabungkan dengan:** starter kit autentikasi, middleware, Sanctum, dan policy sesuai kepemilikan/role.

## Route resource

**Untuk apa:** tujuh URL CRUD tanpa menulis satu-satu.

```php
Route::resource('produk', ProdukController::class);
```

Laravel menyiapkan: `index`, `create`, `store`, `show`, `edit`, `update`, `destroy`. Cek dengan `php artisan route:list`.

Hanya sebagian:

```php
Route::resource('produk', ProdukController::class)->only(['index', 'show']);
```

**Biasanya digabungkan dengan:** controller resource dan form Blade `PUT`/`DELETE` (`@method('DELETE')`).

## Form Request

**Untuk apa:** memindahkan aturan validasi keluar controller agar controller pendek.

```bash
php artisan make:request StoreProdukRequest
```

```php
public function rules(): array
{
    return [
        'nama' => ['required', 'string', 'max:100'],
        'harga' => ['required', 'integer', 'min:0'],
    ];
}

public function authorize(): bool
{
    return true; // latihan; produksi: cek user
}
```

Di controller: `store(StoreProdukRequest $request)` lalu `$request->validated()`.

**Biasanya digabungkan dengan:** `store`/`update` dan `$fillable`.

## Pagination

**Untuk apa:** memecah daftar panjang jadi halaman.

```php
$produk = Produk::orderBy('nama')->paginate(10);
return view('produk.index', compact('produk'));
```

Blade:

```blade
@foreach ($produk as $item)
  <p>{{ $item->nama }}</p>
@endforeach
{{ $produk->links() }}
```

API: `paginate()` mengembalikan `data`, `current_page`, `last_page`. Jangan `all()` untuk 10.000 baris.

**Biasanya digabungkan dengan:** katalog dan tabel admin.

## Factory dan seeder

**Untuk apa:** data palsu untuk latihan dan tes.

```bash
php artisan make:factory ProdukFactory --model=Produk
```

Di factory:

```php
public function definition(): array
{
    return [
        'nama' => fake('id_ID')->words(2, true),
        'harga' => fake()->numberBetween(10000, 90000),
        'stok' => fake()->numberBetween(0, 20),
    ];
}
```

Di seeder: `Produk::factory()->count(20)->create();`

```bash
php artisan db:seed
```

**Biasanya digabungkan dengan:** `migrate:fresh --seed` di database latihan.

## Unggah file

**Untuk apa:** menerima gambar/dokumen dari form.

```php
$request->validate([
    'foto' => ['required', 'image', 'max:2048'],
]);

$path = $request->file('foto')->store('produk', 'public');
```

Form wajib `enctype="multipart/form-data"`. Simpan `$path` di kolom tabel. Jalankan `php artisan storage:link` agar file di `storage/app/public` bisa diakses lewat `/storage/...`.

Jangan percaya nama file asli; `store()` membuat nama aman.

**Biasanya digabungkan dengan:** kolom `foto`, Blade `<img src="{{ asset('storage/'.$produk->foto) }}">`.

## API Resource

**Untuk apa:** merapikan bentuk JSON (jangan kirim semua kolom mentah).

```bash
php artisan make:resource ProdukResource
```

```php
public function toArray(Request $request): array
{
    return [
        'id' => $this->id,
        'nama' => $this->nama,
        'harga' => $this->harga,
    ];
}
```

Controller: `return ProdukResource::collection($produk);` atau `new ProdukResource($produk)`.

**Biasanya digabungkan dengan:** Next.js `fetch` dan kontrak field yang stabil.

## Perintah praktis

Jalankan dari root aplikasi Laravel:

```bash
php artisan route:list       # Lihat URL, metode HTTP, dan handler
php artisan migrate:status   # Lihat migration yang sudah dijalankan
php artisan tinker           # Konsol PHP dalam konteks aplikasi
php artisan optimize:clear   # Bersihkan cache aplikasi saat debugging
php artisan test             # Jalankan test yang tersedia
```

`migrate:fresh` menghapus seluruh tabel sebelum membuatnya ulang. Jangan jadikan perintah ini kebiasaan untuk memperbaiki error pada database yang datanya ingin dipertahankan.

## Kesalahan umum

- **419 pada form:** periksa `@csrf`, sesi, cookie, dan domain yang digunakan.
- **422 dari API:** baca error validasi field; pastikan nama dan tipe input sesuai.
- **MassAssignmentException:** cocokkan `$fillable` dengan atribut tervalidasi yang ingin disimpan.
- **Table not found:** cek koneksi database dan jalankan migration yang belum diterapkan.
- **View not found:** `view('products.index')` mencari `resources/views/products/index.blade.php`.
- **404 route model binding:** periksa nama parameter route dan keberadaan ID.
- **405 Method Not Allowed:** metode request tidak cocok dengan route; GET tidak otomatis menerima POST.

Latihan: tambahkan kolom `stok` melalui migration baru, validasi sebagai integer minimal 0, dan tampilkan di Blade serta JSON API.
