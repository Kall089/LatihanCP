# 12 — Katalog perintah Artisan

[← File & pagination](11-file-storage-pagination.md) · [Daftar](README.md) · [Berikutnya: helper →](13-helper-umum.md)

**Untuk apa Artisan:** antarmuka terminal Laravel. Semua perintah dijalankan dari **root proyek** (folder yang berisi file `artisan`).

```bash
php artisan list
php artisan help migrate
```

Rujukan: `php artisan list` pada proyekmu adalah sumber paling akurat untuk versi terpasang.

Di bawah, setiap perintah: **untuk apa**, contoh, **biasanya digabungkan dengan**.

## Daftar isi

- [php artisan list](#php-artisan-list)
- [php artisan help](#php-artisan-help)
- [php artisan about](#php-artisan-about)
- [php artisan serve](#php-artisan-serve)
- [php artisan key:generate](#php-artisan-keygenerate)
- [php artisan make:model](#php-artisan-makemodel)
- [php artisan make:controller](#php-artisan-makecontroller)
- [php artisan make:request](#php-artisan-makerequest)
- [php artisan make:resource](#php-artisan-makeresource)
- [php artisan make:migration](#php-artisan-makemigration)
- [php artisan make:seeder](#php-artisan-makeseeder)
- [php artisan make:factory](#php-artisan-makefactory)
- [php artisan make:policy](#php-artisan-makepolicy)
- [php artisan make:middleware](#php-artisan-makemiddleware)
- [php artisan make:command](#php-artisan-makecommand)
- [php artisan make:job](#php-artisan-makejob)
- [php artisan make:event dan make:listener](#php-artisan-makeevent-dan-makelistener)
- [php artisan migrate](#php-artisan-migrate)
- [php artisan migrate:status](#php-artisan-migratestatus)
- [php artisan migrate:rollback](#php-artisan-migraterollback)
- [php artisan migrate:fresh](#php-artisan-migratefresh)
- [php artisan migrate:refresh](#php-artisan-migraterefresh)
- [php artisan db:seed](#php-artisan-dbseed)
- [php artisan db:wipe](#php-artisan-dbwipe)
- [php artisan db:show](#php-artisan-dbshow)
- [php artisan route:list](#php-artisan-routelist)
- [php artisan route:clear](#php-artisan-routeclear)
- [php artisan config:clear dan config:cache](#php-artisan-configclear-dan-configcache)
- [php artisan cache:clear](#php-artisan-cacheclear)
- [php artisan view:clear](#php-artisan-viewclear)
- [php artisan optimize dan optimize:clear](#php-artisan-optimize-dan-optimizeclear)
- [php artisan storage:link](#php-artisan-storagelink)
- [php artisan tinker](#php-artisan-tinker)
- [php artisan test](#php-artisan-test)
- [php artisan install:api](#php-artisan-installapi)
- [php artisan vendor:publish](#php-artisan-vendorpublish)
- [php artisan down dan up](#php-artisan-down-dan-up)
- [php artisan env](#php-artisan-env)
- [php artisan model:show](#php-artisan-modelshow)
- [php artisan queue:work](#php-artisan-queuework)
- [php artisan schedule:list](#php-artisan-schedulelist)
- [php artisan make:cast](#php-artisan-makecast)
- [Gabungan yang sering dipakai](#gabungan-yang-sering-dipakai)

---

## php artisan list

**Untuk apa:** menampilkan semua perintah yang tersedia di proyek ini.

```bash
php artisan list
php artisan list --raw
```

Nama perintah bisa berbeda setelah paket baru (`composer require`).

**Biasanya digabungkan dengan:** `help <perintah>` untuk opsi.

---

## php artisan help

**Untuk apa:** dokumen singkat satu perintah.

```bash
php artisan help migrate
php artisan help make:model
```

Lebih andal daripada menghafal semua bendera.

**Biasanya digabungkan dengan:** `list` saat lupa nama.

---

## php artisan about

**Untuk apa:** ringkasan lingkungan: versi Laravel/PHP, driver cache, DB.

```bash
php artisan about
```

Cocok memastikan `APP_ENV=local` dan koneksi DB yang sedang dipakai.

**Biasanya digabungkan dengan:** debugging "kok koneksi salah?".

---

## php artisan serve

**Untuk apa:** server HTTP latihan.

```bash
php artisan serve
php artisan serve --port=8001
php artisan serve --host=0.0.0.0
```

Bukan produksi. Terminal harus tetap terbuka.

**Biasanya digabungkan dengan:** terminal kedua untuk `migrate` / `make:*`.

---

## php artisan key:generate

**Untuk apa:** mengisi `APP_KEY` di `.env`.

```bash
php artisan key:generate
php artisan key:generate --show
```

Tanpa kunci: error enkripsi session/cookie. Jangan menimpa kunci produksi tanpa rencana (session lama invalid).

**Biasanya digabungkan dengan:** clone proyek + salin `.env.example`.

---

## php artisan make:model

**Untuk apa:** membuat class model, opsional migration/factory/controller.

```bash
php artisan make:model Product
php artisan make:model Product -m
php artisan make:model Product -mf
php artisan make:model Product -mfs
php artisan make:model Product -mfsc
```

Bendera umum: `-m` migration, `-f` factory, `-s` seeder, `-c` controller. Gabungan tergantung versi — `help make:model`.

**Biasanya digabungkan dengan:** mengisi `$fillable` dan `Schema::create`.

---

## php artisan make:controller

**Untuk apa:** class controller.

```bash
php artisan make:controller ProductController
php artisan make:controller ProductController --resource
php artisan make:controller ProductController --api
php artisan make:controller ProductController --invokable
php artisan make:controller Api/ProductController --api
```

`--resource` tujuh method web. `--api` tanpa form.

**Biasanya digabungkan dengan:** `Route::resource` / `apiResource`.

---

## php artisan make:request

**Untuk apa:** Form Request.

```bash
php artisan make:request StoreProductRequest
php artisan make:request UpdateProductRequest
```

Isi `rules()` dan `authorize()`.

**Biasanya digabungkan dengan:** `store(StoreProductRequest $request)`.

---

## php artisan make:resource

**Untuk apa:** API Resource / Collection.

```bash
php artisan make:resource ProductResource
php artisan make:resource ProductCollection --collection
```

**Biasanya digabungkan dengan:** `apiResource` dan `toArray`.

---

## php artisan make:migration

**Untuk apa:** file migration lepas (tanpa model baru).

```bash
php artisan make:migration create_products_table
php artisan make:migration add_stok_to_products_table --table=products
php artisan make:migration create_product_tag_table
```

**Biasanya digabungkan dengan:** `migrate` dan `down()` yang jujur.

---

## php artisan make:seeder

**Untuk apa:** class pengisi data.

```bash
php artisan make:seeder ProductSeeder
php artisan make:seeder CategorySeeder
```

Daftarkan di `DatabaseSeeder` jika ingin `db:seed` menjalankan semuanya.

**Biasanya digabungkan dengan:** factory dan `migrate:fresh --seed` (latihan).

---

## php artisan make:factory

**Untuk apa:** cetakan faker.

```bash
php artisan make:factory ProductFactory --model=Product
```

**Biasanya digabungkan dengan:** `HasFactory` dan `Product::factory()->count(10)`.

---

## php artisan make:policy

**Untuk apa:** class izin model.

```bash
php artisan make:policy ProductPolicy --model=Product
```

**Biasanya digabungkan dengan:** `authorize` / `can:update,product`.

---

## php artisan make:middleware

**Untuk apa:** pemeriksa request kustom.

```bash
php artisan make:middleware EnsureUserIsAdmin
```

Daftarkan alias di `bootstrap/app.php`.

**Biasanya digabungkan dengan:** `auth` di depan alias baru.

---

## php artisan make:command

**Untuk apa:** perintah Artisan milikmu.

```bash
php artisan make:command KirimLaporanMingguan
```

Pakai untuk tugas berulang di terminal, bukan untuk request HTTP.

**Biasanya digabungkan dengan:** `schedule:list` jika dijadwalkan.

---

## php artisan make:job

**Untuk apa:** pekerjaan antrean (kirim email, resize gambar) agar request HTTP tidak menunggu lama.

```bash
php artisan make:job ProsesFotoProduk
```

Tanpa worker, job tidak jalan. Untuk tugas kuliah CRUD, sering belum perlu.

**Biasanya digabungkan dengan:** `queue:work` dan driver `database`/`redis`.

---

## php artisan make:event dan make:listener

**Untuk apa:** memisahkan "sesuatu terjadi" dari "apa yang dilakukan".

```bash
php artisan make:event ProductCreated
php artisan make:listener KirimNotifikasiProduk --event=ProductCreated
```

Opsional di tugas dasar. Jangan menambah event hanya agar "terlihat lengkap".

**Biasanya digabungkan dengan:** `event(new ProductCreated($product))` setelah `create`.

---

## php artisan migrate

**Untuk apa:** menjalankan migration yang belum terpakai.

```bash
php artisan migrate
php artisan migrate --force   # produksi, tanpa konfirmasi; hati-hati
php artisan migrate --pretend
```

Gagal jika DB tidak nyambung atau FK salah urutan.

**Biasanya digabungkan dengan:** `migrate:status` dan backup sebelum produksi.

---

## php artisan migrate:status

**Untuk apa:** tabel mana yang sudah/ belum dijalankan.

```bash
php artisan migrate:status
```

**Biasanya digabungkan dengan:** debugging "tabel tidak ada".

---

## php artisan migrate:rollback

**Untuk apa:** membatalkan batch terakhir (`down()`).

```bash
php artisan migrate:rollback
php artisan migrate:rollback --step=1
```

Menghapus struktur + data terkait di `down()`. Bukan "undo bisnis" yang aman di produksi.

**Biasanya digabungkan dengan:** `down()` yang lengkap pada migration baru.

---

## php artisan migrate:fresh

**Untuk apa:** drop semua tabel, lalu migrate dari nol.

```bash
php artisan migrate:fresh
php artisan migrate:fresh --seed
```

**Menghapus semua data.** Hanya lokal/latihan, atau jika kamu sadar.

**Biasanya digabungkan dengan:** factory setelah ubah schema besar.

---

## php artisan migrate:refresh

**Untuk apa:** rollback semua lalu migrate lagi (data hilang). Mirip `fresh` pada banyak kasus; `fresh` lebih kasar (drop semua).

```bash
php artisan migrate:refresh --seed
```

**Biasanya digabungkan dengan:** eksperimen schema di lokal.

---

## php artisan db:seed

**Untuk apa:** menjalankan seeder.

```bash
php artisan db:seed
php artisan db:seed --class=ProductSeeder
```

Bisa menggandakan data jika seeder tidak idempoten.

**Biasanya digabungkan dengan:** `DatabaseSeeder` dan `fresh --seed`.

---

## php artisan db:wipe

**Untuk apa:** mengosongkan database (drop tabel) tanpa otomatis migrate.

```bash
php artisan db:wipe
```

Lebih berbahaya daripada kelihatan. Setelah wipe, `migrate` lagi.

**Biasanya digabungkan dengan:** reset total lokal.

---

## php artisan db:show

**Untuk apa:** info koneksi dan daftar tabel (bergantung versi).

```bash
php artisan db:show
php artisan db:table products
```

**Biasanya digabungkan dengan:** memastikan kamu tidak mengira-ngira nama kolom.

---

## php artisan route:list

**Untuk apa:** daftar URL terdaftar.

```bash
php artisan route:list
php artisan route:list --path=api
php artisan route:list --name=products
php artisan route:list --except-vendor
```

**Biasanya digabungkan dengan:** 404 / 405 debugging.

---

## php artisan route:clear

**Untuk apa:** menghapus cache route.

```bash
php artisan route:clear
```

Setelah `route:cache` di produksi, file route tidak dibaca satu-satu. Di lokal, cache route jarang perlu. Jika route baru tidak muncul, clear.

**Biasanya digabungkan dengan:** `config:clear` saat lingkungan aneh.

---

## php artisan config:clear dan config:cache

**Untuk apa:** `config:clear` membuang cache konfigurasi. `config:cache` menggabungkan config untuk produksi.

```bash
php artisan config:clear
php artisan config:cache
```

Setelah `config:cache`, `env()` di luar file `config/` bisa mengembalikan `null`. Di lokal, utamakan **jangan** cache config. Jika sudah terlanjur: `config:clear`.

**Biasanya digabungkan dengan:** mengubah `.env` yang "tidak mempan".

---

## php artisan cache:clear

**Untuk apa:** mengosongkan cache aplikasi (bukan config/route/view secara lengkap di semua versi — sering hanya default cache store).

```bash
php artisan cache:clear
```

Tidak menghapus `laravel.log`. Tidak mereset database.

**Biasanya digabungkan dengan:** `optimize:clear` jika ingin mereset hampir semua cache kerangka.

---

## php artisan view:clear

**Untuk apa:** menghapus Blade yang sudah dikompilasi di `storage/framework/views`.

```bash
php artisan view:clear
```

Berguna jika view "aneh" setelah ganti nama section, atau file compiled rusak.

**Biasanya digabungkan dengan:** mengubah banyak file Blade.

---

## php artisan optimize dan optimize:clear

**Untuk apa:** `optimize` menyiapkan cache (config/route/dll.) untuk produksi. `optimize:clear` membatalkan hampir semua itu.

```bash
php artisan optimize
php artisan optimize:clear
```

Di komputer kuliah, jika sesuatu "macet setelah kemarin cache", jalankan `optimize:clear`.

**Biasanya digabungkan dengan:** deploy (optimize) dan debugging lokal (clear).

---

## php artisan storage:link

**Untuk apa:** symlink `public/storage`.

```bash
php artisan storage:link
```

Error "link already exists" = sudah pernah. Jangan hapus folder `storage/app/public` kira-kira.

**Biasanya digabungkan dengan:** unggah disk `public`.

---

## php artisan tinker

**Untuk apa:** REPL PHP dengan bootstrap Laravel. Mencoba query tanpa menulis controller.

```bash
php artisan tinker
```

```php
App\Models\Product::count();
App\Models\Product::factory()->create(['nama' => 'Coba']);
User::first();
```

Ketik `exit` untuk keluar. Hati-hati `delete` di tinker — itu nyata.

**Biasanya digabungkan dengan:** factory dan pengecekan relasi.

---

## php artisan test

**Untuk apa:** menjalankan tes Pest/PHPUnit.

```bash
php artisan test
php artisan test --filter=Product
```

**Biasanya digabungkan dengan:** factory dan `RefreshDatabase`.

---

## php artisan install:api

**Untuk apa:** memasang kerangka route API di Laravel 11/13.

```bash
php artisan install:api
```

**Biasanya digabungkan dengan:** Sanctum jika installer menawarkannya, dan file 10.

---

## php artisan vendor:publish

**Untuk apa:** menyalin file config/view paket ke proyek agar bisa diubah.

```bash
php artisan vendor:publish
php artisan vendor:publish --tag=laravel-mail
php artisan vendor:publish --provider="..."
```

Tanpa ini, mengubah file di `vendor/` akan hilang saat update.

**Biasanya digabungkan dengan:** menyesuaikan `config/cors.php` atau template pagination.

---

## php artisan down dan up

**Untuk apa:** mode perawatan: pengunjung melihat 503. `up` mematikan mode itu.

```bash
php artisan down
php artisan down --secret="token-latihan"
php artisan up
```

Bukan untuk tugas CRUD harian.

**Biasanya digabungkan dengan:** deploy produksi.

---

## php artisan env

**Untuk apa:** menampilkan lingkungan saat ini (`local`, `production`).

```bash
php artisan env
```

**Biasanya digabungkan dengan:** memastikan `APP_ENV` sesuai harapan.

---

## php artisan model:show

**Untuk apa:** ringkasan model: kolom, relasi, observer (bergantung versi).

```bash
php artisan model:show Product
```

**Biasanya digabungkan dengan:** mengecek apakah relasi terdeteksi.

---

## php artisan queue:work

**Untuk apa:** menjalankan worker antrean.

```bash
php artisan queue:work
php artisan queue:listen
```

Tanpa ini, job `ShouldQueue` menumpuk. Butuh tabel `jobs` jika driver `database` (`make:queue-table` + migrate, nama perintah cek `help`).

**Biasanya digabungkan dengan:** `make:job` dan `.env` `QUEUE_CONNECTION`.

---

## php artisan schedule:list

**Untuk apa:** melihat jadwal yang terdaftar.

```bash
php artisan schedule:list
php artisan schedule:run
```

Agar jadwal jalan di server, cron memanggil `schedule:run` tiap menit. Di lokal, `run` manual.

**Biasanya digabungkan dengan:** `make:command`.

---

## php artisan make:cast

**Untuk apa:** cast kustom kolom model.

```bash
php artisan make:cast Rupiah
```

Untuk tugas dasar, `$casts` bawaan (`boolean`, `datetime`, `array`, `hashed`) biasanya cukup.

**Biasanya digabungkan dengan:** model yang menyimpan format khusus.

---

## Gabungan yang sering dipakai

Proyek baru latihan:

```bash
php artisan key:generate   # jika perlu
php artisan migrate
php artisan serve
```

Fitur produk:

```bash
php artisan make:model Product -mfsc
php artisan migrate
php artisan db:seed
php artisan route:list --path=produk
```

Lingkungan aneh:

```bash
php artisan optimize:clear
php artisan migrate:status
php artisan about
```

**Biasanya digabungkan dengan:** membaca error di `storage/logs/laravel.log` jika halaman putih.

Lanjut ke [helper umum](13-helper-umum.md).
