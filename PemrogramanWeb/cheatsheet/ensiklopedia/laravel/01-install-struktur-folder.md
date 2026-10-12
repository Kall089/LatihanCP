# 01 — Instalasi dan struktur folder

[← Bekal PHP](00-php-bekal.md) · [Daftar](README.md) · [Berikutnya: routing →](02-routing-web-api-resource.md)

**Untuk apa file ini:** membuat proyek Laravel latihan dan tahu file mana yang kamu edit setiap hari. Salah folder = class tidak ketemu, view tidak ketemu, atau perubahan tidak jalan.

Pola di sini mengikuti Laravel 11/13: aplikasi di-bootstrap dari `bootstrap/app.php`, route web di `routes/web.php`, konfigurasi rahasia di `.env`.

Rujukan: [instalasi Laravel](https://laravel.com/docs/13.x/installation), [struktur direktori](https://laravel.com/docs/13.x/structure).

## Daftar isi

- [Persyaratan](#persyaratan)
- [composer create-project](#composer-create-project)
- [laravel new](#laravel-new)
- [php artisan serve](#php-artisan-serve)
- [SQLite cepat](#sqlite-cepat)
- [MySQL atau PostgreSQL](#mysql-atau-postgresql)
- [APP_KEY](#app_key)
- [.env dan .env.example](#env-dan-envexample)
- [composer.json dan vendor](#composerjson-dan-vendor)
- [artisan](#artisan)
- [bootstrap/app.php](#bootstrapappphp)
- [bootstrap/providers.php](#bootstrapprovidersphp)
- [public/](#public)
- [public/index.php](#publicindexphp)
- [app/](#app)
- [app/Http/Controllers](#apphttpcontrollers)
- [app/Http/Requests](#apphttprequests)
- [app/Http/Resources](#apphttpresources)
- [app/Models](#appmodels)
- [app/Policies](#apppolicies)
- [app/Providers](#appproviders)
- [config/](#config)
- [database/migrations](#databasemigrations)
- [database/seeders](#databaseseeders)
- [database/factories](#databasefactories)
- [database/database.sqlite](#databasedatabasesqlite)
- [resources/views](#resourcesviews)
- [resources/css dan js](#resourcescss-dan-js)
- [routes/web.php](#routeswebphp)
- [routes/api.php](#routesapiphp)
- [routes/console.php](#routesconsolephp)
- [storage/](#storage)
- [tests/](#tests)
- [Yang tidak kamu edit](#yang-tidak-kamu-edit)
- [Checklist proyek baru](#checklist-proyek-baru)

---

## Persyaratan

**Untuk apa:** memastikan PHP, Composer, dan ekstensi cukup sebelum `create-project`.

Yang biasanya dibutuhkan:

- PHP sesuai dokumen versi Laravel (11/13: PHP 8.2 atau lebih baru)
- Ekstensi umum: `mbstring`, `openssl`, `pdo`, `tokenizer`, `xml`, `ctype`, `json`, `fileinfo`, `bcmath`
- Composer 2
- Node.js + npm **jika** kamu membangun CSS/JS lewat Vite
- Database: SQLite (paling mudah latihan) atau MySQL/PostgreSQL

Cek versi:

```bash
php -v
composer -V
```

Jika `php` tidak dikenali, pasang PHP dan pastikan PATH terminal benar. Error "could not find driver" saat migrate biasanya ekstensi PDO/SQLite/MySQL belum aktif.

**Biasanya digabungkan dengan:** satu proyek latihan terpisah, bukan folder tugas HTML yang sudah ada.

---

## composer create-project

**Untuk apa:** mengunduh kerangka Laravel resmi ke folder baru.

```bash
composer create-project laravel/laravel latihan-laravel "^13.0"
cd latihan-laravel
```

- `latihan-laravel` adalah nama folder. Jangan memakai nama folder yang sudah berisi file.
- `"^13.0"` mengunci keluarga versi 13. Untuk Laravel 11: `"^11.0"`.
- Perintah ini **bukan** untuk menimpa proyek yang sedang dikerjakan.

Setelah selesai, folder berisi `artisan`, `app/`, `routes/`, `.env` (biasanya disalin dari `.env.example` oleh installer).

**Biasanya digabungkan dengan:** `php artisan serve` dan pengaturan database di `.env`.

---

## laravel new

**Untuk apa:** cara resmi lain lewat Laravel Installer. Hasilnya sama: proyek baru.

```bash
laravel new latihan-laravel
```

Installer bisa menanyakan starter kit, testing (Pest/PHPUnit), dan database. Untuk ensiklopedia ini, proyek kosong tanpa starter sudah cukup.

Jika perintah `laravel` tidak ada, pakai `composer create-project`. Keduanya sah.

**Biasanya digabungkan dengan:** pilihan SQLite saat ditanya database, agar tidak perlu server MySQL dulu.

---

## php artisan serve

**Untuk apa:** menjalankan server pengembangan bawaan. Bukan untuk produksi.

```bash
cd latihan-laravel
php artisan serve
```

Buka URL yang dicetak terminal, biasanya `http://127.0.0.1:8000`.

- Biarkan terminal ini berjalan. Buka terminal kedua untuk `artisan migrate` atau `make:model`.
- Hentikan dengan `Ctrl+C`.
- Port dipakai? `php artisan serve --port=8001`.

Untuk halaman Blade murni tanpa `@vite`, kamu tidak wajib menjalankan `npm run dev`. Jika layout memakai `@vite(['resources/css/app.css', 'resources/js/app.js'])`, jalankan juga Vite atau build aset.

**Biasanya digabungkan dengan:** `php artisan migrate` sebelum fitur database dicoba.

---

## SQLite cepat

**Untuk apa:** database file tunggal, cocok latihan kuliah.

Di `.env`:

```env
DB_CONNECTION=sqlite
```

Hapus atau jangan biarkan `DB_DATABASE` menunjuk nama database MySQL jika kamu ingin file SQLite default. Laravel 11+ biasanya memakai `database/database.sqlite`.

Jika file belum ada:

```bash
touch database/database.sqlite
php artisan migrate
```

Satu file = satu database. Jangan commit data sensitif. Boleh commit file kosong di proyek latihan jika dosen meminta.

**Biasanya digabungkan dengan:** `php artisan db:seed` setelah factory/seeder siap.

---

## MySQL atau PostgreSQL

**Untuk apa:** database server terpisah, mendekati banyak tugas/produksi.

```env
DB_CONNECTION=mysql
DB_HOST=127.0.0.1
DB_PORT=3306
DB_DATABASE=latihan_laravel
DB_USERNAME=root
DB_PASSWORD=
```

Database `latihan_laravel` harus **sudah dibuat** di server MySQL. Laravel tidak selalu membuat databasenya sendiri (kecuali kamu memakai perintah yang memang membuatnya).

Setelah mengubah `.env`:

```bash
php artisan config:clear
php artisan migrate
```

**Biasanya digabungkan dengan:** user MySQL yang haknya cukup untuk `CREATE TABLE`, dan password yang tidak di-commit.

---

## APP_KEY

**Untuk apa:** kunci enkripsi cookie, session, dan data terenkripsi lain.

```bash
php artisan key:generate
```

Installer biasanya sudah mengisi `APP_KEY` di `.env`. Jika halaman error "No application encryption key has been specified", jalankan perintah di atas.

Jangan menyalin `APP_KEY` produksi ke repositori publik. Setiap lingkungan (latihan, staging, produksi) punya kunci sendiri.

**Biasanya digabungkan dengan:** `APP_DEBUG=true` hanya di lokal.

---

## .env dan .env.example

**Untuk apa:** konfigurasi yang berbeda di tiap komputer. `.env` tidak ikut version control. `.env.example` adalah daftar kunci tanpa rahasia.

Kunci yang sering disentuh:

```env
APP_NAME=Latihan
APP_ENV=local
APP_DEBUG=true
APP_URL=http://127.0.0.1:8000

DB_CONNECTION=sqlite
```

- `APP_DEBUG=true` menampilkan jejak error. Wajib `false` di produksi.
- `APP_URL` dipakai generator URL (`url()`, asset, verifikasi email).
- Setelah mengubah `.env` yang sudah di-cache, `php artisan config:clear`.

Membaca di kode:

```php
env('APP_DEBUG');
config('app.debug');
```

Di dalam class aplikasi, utamakan `config('...')` karena `env()` tidak andal setelah config di-cache. Lihat [13-helper-umum.md](13-helper-umum.md).

**Biasanya digabungkan dengan:** `config/app.php`, `config/database.php` (nilai default + pemanggilan `env()` di file config).

---

## composer.json dan vendor

**Untuk apa:** `composer.json` mencatat paket PHP. `vendor/` berisi kode paket. Jangan mengedit isi `vendor/`.

```bash
composer install   # pasang sesuai lock, untuk clone proyek
composer update    # hati-hati: bisa menaikkan versi
composer require laravel/sanctum
```

`composer.lock` mengunci versi. Commit `composer.json` + `composer.lock`. Jangan commit `vendor/` jika `.gitignore` sudah mengabaikannya (standar Laravel).

Autoload PSR-4:

```json
"App\\": "app/",
```

Artinya `App\Models\Product` = `app/Models/Product.php`.

**Biasanya digabungkan dengan:** `composer dump-autoload` jika class baru tidak ketemu padahal path sudah benar.

---

## artisan

**Untuk apa:** pintu perintah Laravel: migrate, make:model, serve, tinker, route:list.

```bash
php artisan list
php artisan help migrate
```

File `artisan` di root proyek adalah skrip PHP. Jalankan dari root, bukan dari `public/`.

Katalog perintah: [12-artisan-katalog.md](12-artisan-katalog.md).

**Biasanya digabungkan dengan:** terminal kedua saat `serve` masih jalan.

---

## bootstrap/app.php

**Untuk apa:** (Laravel 11/13) tempat merakit aplikasi: file route, middleware, exception.

Contoh pola modern:

```php
<?php

use Illuminate\Foundation\Application;
use Illuminate\Foundation\Configuration\Exceptions;
use Illuminate\Foundation\Configuration\Middleware;

return Application::configure(basePath: dirname(__DIR__))
    ->withRouting(
        web: __DIR__.'/../routes/web.php',
        commands: __DIR__.'/../routes/console.php',
        health: '/up',
    )
    ->withMiddleware(function (Middleware $middleware): void {
        // alias middleware, CSRF kecuali, dll.
    })
    ->withExceptions(function (Exceptions $exceptions): void {
        //
    })->create();
```

Route API ditambahkan setelah `install:api`, biasanya `api: __DIR__.'/../routes/api.php'`.

Di sinilah kamu memasang alias middleware sendiri, bukan di `Kernel.php` (file lama).

**Biasanya digabungkan dengan:** `routes/web.php` dan middleware `auth` / `verified`.

---

## bootstrap/providers.php

**Untuk apa:** daftar service provider aplikasi (Laravel 11+).

```php
<?php

return [
    App\Providers\AppServiceProvider::class,
];
```

Provider lama seperti `RouteServiceProvider` tidak wajib ada. Jangan menghapus `AppServiceProvider` kecuali kamu tahu penggantinya.

**Biasanya digabungkan dengan:** `AppServiceProvider` untuk `Gate`, `Model::unguard()` di lokal, atau `Paginator::useBootstrapFive()`.

---

## public/

**Untuk apa:** satu-satunya folder yang "terlihat" web server di produksi. Berisi `index.php`, `favicon`, dan aset hasil build.

Jangan menaruh logika aplikasi di sini. Jangan menaruh `.env` di sini.

File unggahan publik biasanya di-`storage/app/public` lalu di-symlink ke `public/storage`:

```bash
php artisan storage:link
```

**Biasanya digabungkan dengan:** helper `asset()` dan `Storage::url()`.

---

## public/index.php

**Untuk apa:** front controller. Semua request HTTP masuk ke sini lalu ke kernel Laravel.

Kamu hampir tidak mengedit file ini. Jika URL rewrite mati, membuka `/public` secara kasar bisa "berjalan" di latihan, tetapi atur document root ke `public/` dengan benar.

**Biasanya digabungkan dengan:** `php artisan serve` yang sudah mengarah ke `public/`.

---

## app/

**Untuk apa:** kode aplikasi milikmu: controller, model, policy, request.

Subfolder standar yang sering kamu buat:

| Folder | Isi |
| --- | --- |
| `app/Http/Controllers` | Alur request |
| `app/Http/Requests` | Form Request / validasi |
| `app/Http/Resources` | Bentuk JSON |
| `app/Models` | Eloquent |
| `app/Policies` | Izin per model |
| `app/Providers` | Registrasi layanan |

Boleh menambah `app/Services` atau `app/Actions` jika dosen/proyek butuh, tetapi bukan wajib.

**Biasanya digabungkan dengan:** namespace `App\...` yang mencerminkan folder.

---

## app/Http/Controllers

**Untuk apa:** class yang dipanggil route.

```bash
php artisan make:controller ProductController
php artisan make:controller ProductController --resource
php artisan make:controller Api/ProductController --api
```

File: `app/Http/Controllers/ProductController.php`. Namespace: `App\Http\Controllers`.

Detail method: [03-controller-request-response.md](03-controller-request-response.md).

**Biasanya digabungkan dengan:** `use App\Http\Controllers\ProductController;` di `routes/web.php`.

---

## app/Http/Requests

**Untuk apa:** memindah aturan validasi keluar dari controller.

```bash
php artisan make:request StoreProductRequest
```

File: `app/Http/Requests/StoreProductRequest.php`. Method `rules()` dan `authorize()`.

**Biasanya digabungkan dengan:** `store(StoreProductRequest $request)` di controller.

---

## app/Http/Resources

**Untuk apa:** merapikan JSON API agar tidak membocorkan semua kolom model.

```bash
php artisan make:resource ProductResource
```

Lihat [10-api-resource-cors.md](10-api-resource-cors.md).

**Biasanya digabungkan dengan:** `routes/api.php` dan `ProductResource::collection($products)`.

---

## app/Models

**Untuk apa:** class yang mewakili tabel.

```bash
php artisan make:model Product -m
php artisan make:model Product -mfsc
```

Bendera umum:

- `-m` migration
- `-f` factory
- `-s` seeder
- `-c` controller
- `--requests` form request (bergantung versi artisan)

**Biasanya digabungkan dengan:** `$fillable`, relasi, dan `$casts`.

---

## app/Policies

**Untuk apa:** "siapa boleh mengubah produk ini?"

```bash
php artisan make:policy ProductPolicy --model=Product
```

Lihat [09-middleware-auth-gate-policy.md](09-middleware-auth-gate-policy.md).

**Biasanya digabungkan dengan:** `Gate` / `$this->authorize('update', $product)` / middleware `can`.

---

## app/Providers

**Untuk apa:** menyalakan pengaturan saat aplikasi boot.

`AppServiceProvider` sering dipakai untuk:

```php
use Illuminate\Support\Facades\Gate;

public function boot(): void
{
    // Gate::define(...);
}
```

Jangan menaruh query bisnis panjang di sini.

**Biasanya digabungkan dengan:** Gate, pagination view, dan observasi model jika ada.

---

## config/

**Untuk apa:** pengaturan yang dibaca lewat `config('app.name')`. File di sini boleh di-commit. Rahasia tetap di `.env`.

File yang sering dibuka:

| File | Isi |
| --- | --- |
| `config/app.php` | nama, timezone, locale, debug |
| `config/database.php` | koneksi DB |
| `config/auth.php` | guard, provider user |
| `config/filesystems.php` | disk `local`, `public`, `s3` |
| `config/cors.php` | muncul setelah kebutuhan API/CORS |
| `config/session.php` | driver session |
| `config/mail.php` | pengiriman email |

Jangan menaruh password mentah di `config/`. Pakai `env('DB_PASSWORD')` di file config, lalu `config('database.connections.mysql.password')` di kode.

**Biasanya digabungkan dengan:** helper `config()` dan `php artisan config:clear`.

---

## database/migrations

**Untuk apa:** riwayat struktur tabel. Satu perubahan besar = satu file baru jika tabel sudah dipakai bersama.

```bash
php artisan make:migration create_products_table
php artisan migrate
php artisan migrate:status
```

Lihat [08-migration-seeder-factory.md](08-migration-seeder-factory.md).

**Biasanya digabungkan dengan:** model Eloquent dan `php artisan migrate:fresh --seed` di **latihan** (menghapus data).

---

## database/seeders

**Untuk apa:** mengisi data awal: kategori, user admin latihan, produk contoh.

```bash
php artisan make:seeder ProductSeeder
php artisan db:seed
php artisan db:seed --class=ProductSeeder
```

**Biasanya digabungkan dengan:** factory agar tidak menulis 20 baris array manual.

---

## database/factories

**Untuk apa:** cetakan data palsu yang masuk akal.

```bash
php artisan make:factory ProductFactory --model=Product
```

**Biasanya digabungkan dengan:** `Product::factory()->count(20)->create()` di seeder atau test.

---

## database/database.sqlite

**Untuk apa:** file database SQLite. Bukan kode. Jangan mengedit dengan teks sembarangan.

Backup = salin file. Reset = hapus file + `migrate` ulang, atau `migrate:fresh`.

**Biasanya digabungkan dengan:** `DB_CONNECTION=sqlite`.

---

## resources/views

**Untuk apa:** template Blade. Nama file `index.blade.php` dipanggil `view('products.index')` jika ada di `resources/views/products/index.blade.php`.

Titik pada nama view = folder. `view('layouts.app')` = `resources/views/layouts/app.blade.php`.

**Biasanya digabungkan dengan:** `@extends`, `@section`, `@include` — [05-blade-direktif-lengkap.md](05-blade-direktif-lengkap.md).

---

## resources/css dan js

**Untuk apa:** sumber aset Vite. Bukan wajib untuk contoh Blade polos.

```bash
npm install
npm run dev      # watch lokal
npm run build    # produksi
```

`package.json` dan `vite.config.js` mengatur bundling. `@vite` di layout memuat hasilnya.

**Biasanya digabungkan dengan:** Tailwind atau CSS biasa, dan layout Blade.

---

## routes/web.php

**Untuk apa:** URL halaman dan form. Grup `web`: session, cookie, CSRF.

```php
<?php

use Illuminate\Support\Facades\Route;

Route::get('/', function () {
    return view('welcome');
});
```

Jangan menaruh query panjang di sini. Pindah ke controller.

**Biasanya digabungkan dengan:** controller + `->name('products.index')`.

---

## routes/api.php

**Untuk apa:** endpoint JSON. Prefix `/api` (default setelah `install:api`). Stateless: tidak memakai CSRF seperti form web.

```bash
php artisan install:api
```

Jika file belum ada, jangan membuatnya asal tanpa memasang routing API di `bootstrap/app.php`.

**Biasanya digabungkan dengan:** `Route::apiResource`, Sanctum/token, dan API Resource.

---

## routes/console.php

**Untuk apa:** perintah Artisan tertutup / jadwal. Bukan URL browser.

```php
Artisan::command('halo', function () {
    $this->info('Halo');
});
```

**Biasanya digabungkan dengan:** `php artisan schedule:list` jika memakai penjadwalan.

---

## storage/

**Untuk apa:** file yang ditulis aplikasi: log, cache, unggahan, view ter-compile.

| Path | Isi |
| --- | --- |
| `storage/app` | file privat |
| `storage/app/public` | file yang boleh di-link ke publik |
| `storage/logs` | `laravel.log` |
| `storage/framework` | cache, session, view compiled |

Folder ini harus bisa ditulis PHP. Error "Permission denied" / "failed to open stream" sering karena hak `storage/` dan `bootstrap/cache/`.

Jangan commit log besar. `.gitignore` sudah mengabaikan banyak isinya.

**Biasanya digabungkan dengan:** `storage:link`, `Log::info()`, dan unggah file.

---

## tests/

**Untuk apa:** tes otomatis. Pest atau PHPUnit, tergantung pilihan proyek.

```bash
php artisan test
```

Bukan syarat membaca ensiklopedia ini, tetapi factory + tes sangat cocok.

**Biasanya digabungkan dengan:** `Product::factory()` dan `$this->get('/produk')`.

---

## Yang tidak kamu edit

- `vendor/` — kode paket
- `public/build` hasil Vite (dihasilkan ulang)
- `storage/framework/views` — cache Blade
- file migration lama yang sudah dijalankan di lingkungan bersama (buat migration baru)

Boleh dibaca, jangan "diperbaiki" isinya secara langsung.

**Biasanya digabungkan dengan:** `composer require` untuk menambah paket, bukan copy file ke `vendor/`.

---

## Checklist proyek baru

1. `composer create-project` ke folder kosong.
2. Cek `.env`: `APP_KEY`, `APP_DEBUG=true`, database.
3. `touch database/database.sqlite` jika SQLite dan file belum ada.
4. `php artisan migrate`.
5. `php artisan serve`.
6. Buka `/` — halaman welcome.
7. Baru kemudian `make:model`, route, view.

Kalau welcome tidak muncul: PHP salah versi, port salah, atau kamu tidak berada di root proyek.

Lanjut ke [routing](02-routing-web-api-resource.md) setelah folder terasa familiar.
