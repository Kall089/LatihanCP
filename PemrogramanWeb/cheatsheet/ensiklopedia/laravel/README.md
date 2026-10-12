# Ensiklopedia Laravel + Bekal PHP

Catatan API Laravel satu per satu, berbahasa Indonesia mudah. Setiap entri menjawab tiga hal:

1. **Untuk apa** — kapan dipakai, masalah apa yang diselesaikan.
2. **Kode** — potongan PHP/Blade yang bisa disalin ke proyek latihan.
3. **Biasanya digabungkan dengan** — teman yang hampir selalu muncul bersama.

Ini **ensiklopedia**, bukan tutorial satu proyek. Contoh di tiap bagian berdiri sendiri kecuali tertulis sebagai rangkaian. Jangan menempelkan semua contoh ke satu file.

Pola mengikuti Laravel **11** dan **13**: `bootstrap/app.php` untuk middleware, `routes/web.php` untuk halaman, `routes/api.php` setelah `php artisan install:api`, Eloquent modern, Form Request, Blade, dan helper bawaan. Cocokkan versi PHP dan Composer dengan dokumentasi resmi versi yang kamu pasang.

Dokumentasi resmi yang sering dipakai: [Laravel 13.x](https://laravel.com/docs/13.x). Jika proyekmu Laravel 11, strukturnya sangat mirip; bedanya terutama di paket starter dan beberapa default.

## Cara memakai folder ini

- Mulai dari [00-php-bekal.md](00-php-bekal.md) jika belum terbiasa `$variabel`, array, `foreach`, fungsi, class, `namespace`, dan type hint.
- Lanjut [01-install-struktur-folder.md](01-install-struktur-folder.md) agar tahu file mana yang boleh diubah.
- Setelah itu lompat ke topik yang sedang kamu kerjakan. Tidak harus dibaca berurutan.
- Cari nama API di daftar isi file, misalnya `unique`, `findOrFail`, `@csrf`, `Route::resource`.
- Setelah menyalin, ubah satu nilai (nama tabel, field, route) lalu amati hasilnya.
- Contoh memakai nama model `Product`, tabel `products`, field `nama`/`harga` kecuali topik butuh contoh lain (user, komentar, unggahan).

## Daftar file

| File | Isi singkat |
| --- | --- |
| [00-php-bekal.md](00-php-bekal.md) | Variabel, tipe, array, loop, fungsi, class, namespace, type hint |
| [01-install-struktur-folder.md](01-install-struktur-folder.md) | Instalasi, folder proyek, `.env`, `bootstrap/app.php` |
| [02-routing-web-api-resource.md](02-routing-web-api-resource.md) | `Route::get/post`, parameter, resource, API, binding |
| [03-controller-request-response.md](03-controller-request-response.md) | Controller, `Request`, `response()`, redirect, view |
| [04-validasi-rules-lengkap.md](04-validasi-rules-lengkap.md) | Rule validasi satu per satu + kombinasi |
| [05-blade-direktif-lengkap.md](05-blade-direktif-lengkap.md) | Direktif Blade satu per satu |
| [06-eloquent-crud-query.md](06-eloquent-crud-query.md) | `all`, `get`, `find`, `where`, `create`, `update`, `delete` |
| [07-relasi-eager-load.md](07-relasi-eager-load.md) | `hasOne`, `hasMany`, `belongsTo`, `belongsToMany`, morph, `with` |
| [08-migration-seeder-factory.md](08-migration-seeder-factory.md) | Schema, seeder, factory |
| [09-middleware-auth-gate-policy.md](09-middleware-auth-gate-policy.md) | Middleware, `auth`, Gate, Policy |
| [10-api-resource-cors.md](10-api-resource-cors.md) | JSON Resource, CORS, header API |
| [11-file-storage-pagination.md](11-file-storage-pagination.md) | Unggah file, disk, `paginate` |
| [12-artisan-katalog.md](12-artisan-katalog.md) | Perintah Artisan umum satu per satu |
| [13-helper-umum.md](13-helper-umum.md) | `route`, `url`, `asset`, `config`, `env`, `old`, `dd` |
| [14-kesalahan-resep.md](14-kesalahan-resep.md) | Error umum dan resep perbaikannya |

## Alur request yang diingat di semua file

```text
Browser / frontend
    → routes/web.php atau routes/api.php
    → middleware (auth, csrf, throttle, ...)
    → controller (atau closure)
    → validasi
    → model / query Eloquent
    → database
    → Blade (HTML) atau JSON
```

Kalau halaman tidak muncul, cek urutan itu dari atas: URL salah, middleware menolak, validasi gagal, query kosong, atau view tidak dikirimi data.

## Konvensi di contoh

- Namespace aplikasi: `App\...` (standar Laravel).
- Controller di `app/Http/Controllers`.
- Model di `app/Models`.
- View di `resources/views`, ekstensi `.blade.php`.
- Route web butuh `@csrf` pada form `POST`/`PUT`/`PATCH`/`DELETE`.
- Route API biasanya mengembalikan JSON, bukan `view()`.
- `$fillable` di model **bukan** validasi. Validasi tetap di `$request->validate()` atau Form Request.
- `APP_DEBUG=true` hanya untuk latihan lokal. Jangan di produksi.
- Jangan commit `.env` yang berisi password atau `APP_KEY` produksi.

## Laravel 11 dan 13 — yang berubah dari versi lama

Jika kamu membuka tutorial Laravel 8/9, beberapa file sudah tidak dipakai dengan cara yang sama:

- Tidak ada `app/Http/Kernel.php` sebagai tempat utama middleware. Alias dan grup ada di `bootstrap/app.php`.
- `RouteServiceProvider` tidak lagi menjadi pusat semua route. `bootstrap/app.php` yang memuat `web.php` / `api.php`.
- Route API tidak otomatis ada di proyek baru. Pasang dulu dengan `php artisan install:api` bila perlu endpoint `/api/...`.
- Controller hasil `make:controller` bisa tanpa class dasar yang penuh helper; tetap sah memanggil `view()`, `redirect()`, dan `response()` sebagai helper.
- Starter kit (Breeze/Jetstream) opsional. Ensiklopedia ini tidak bergantung pada satu starter.

**Biasanya digabungkan dengan:** [cheatsheet Laravel ringkas](../../laravel.md) untuk alur satu contoh produk, dan [bekal PHP ringkas](../../php.md) jika ingin versi pendek.

## Apa yang tidak dibahas panjang di sini

- Vue/Livewire/Inertia sebagai SPA penuh (hanya disinggung jika berkaitan).
- Queue, event, job, notification, broadcasting — disebut jika perlu, bukan katalog lengkap.
- Deployment produksi (Nginx, Octane, Horizon) — di luar ruang lingkup kuliah dasar.
- SQL mentah yang panjang — fokus Eloquent dan query builder yang aman.

## Latihan cepat setelah baca

1. Buat proyek Laravel latihan, jangan menimpa folder yang sudah berisi pekerjaan.
2. Buat model `Product` + migration + controller.
3. Tampilkan daftar, form tambah, dan hapus (lihat contoh berantai di cheatsheet ringkas).
4. Tambahkan validasi `required|string|max:100` pada `nama`.
5. Ubah daftar menjadi `paginate(10)`.
6. Kalau sudah nyaman, buat relasi `Category` `hasMany` `Product`.

Kalau error, buka [14-kesalahan-resep.md](14-kesalahan-resep.md) sebelum menebak.

## Glosarium singkat

| Istilah | Arti praktis |
| --- | --- |
| Route | Peta URL + metode HTTP ke kode |
| Controller | Tempat mengatur alur request |
| Request | Objek data masuk (form, query, file, header) |
| Response | Jawaban server: HTML, JSON, redirect, file |
| Blade | Template HTML + direktif PHP yang aman |
| Eloquent | Cara Laravel membaca/menulis tabel lewat class |
| Migration | Riwayat perubahan struktur tabel |
| Seeder | Data awal / data latihan |
| Factory | Cetakan data palsu untuk seeder/test |
| Middleware | Pemeriksa sebelum/sesudah controller |
| Gate / Policy | Aturan “boleh atau tidak” |
| CSRF | Token anti-pengiriman form dari situs lain |
| Mass assignment | Mengisi banyak kolom sekaligus dari array |
| Eager load | Ambil relasi sekaligus agar tidak N+1 |
| API Resource | Bentuk JSON yang rapi dari model |

**Biasanya digabungkan dengan:** proyek latihan lokal + `php artisan serve` + database SQLite untuk mulai cepat.
