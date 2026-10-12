# 14 — Kesalahan dan resep

[← Helper](13-helper-umum.md) · [Daftar](README.md)

**Untuk apa file ini:** memetakan gejala yang sering muncul ke penyebab yang masuk akal dan langkah perbaikan. Bukan daftar "triik" ilegal. Setiap resep: **untuk apa** (kapan dipakai), contoh jika perlu, **biasanya digabungkan dengan** pemeriksaan lain.

Nyalakan `APP_DEBUG=true` hanya di lokal. Baca pesan exception dari atas: file + baris pertama milik kodemu (`app/`, `routes/`, `resources/views`) lebih penting daripada jejak `vendor/`.

Log: `storage/logs/laravel.log`.

## Daftar isi

- [Cara membaca error](#cara-membaca-error)
- [419 Page Expired](#419-page-expired)
- [405 Method Not Allowed](#405-method-not-allowed)
- [404 Not Found](#404-not-found)
- [403 Forbidden](#403-forbidden)
- [401 / redirect ke login](#401--redirect-ke-login)
- [422 Validasi](#422-validasi)
- [500 / halaman putih](#500--halaman-putih)
- [Class not found](#class-not-found)
- [View not found](#view-not-found)
- [Undefined variable di Blade](#undefined-variable-di-blade)
- [Undefined array key](#undefined-array-key)
- [Attempt to read property on null](#attempt-to-read-property-on-null)
- [Array vs object](#array-vs-object)
- [Mass assignment](#mass-assignment)
- [SQLSTATE / unknown column](#sqlstate--unknown-column)
- [SQLSTATE / table not found](#sqlstate--table-not-found)
- [could not find driver](#could-not-find-driver)
- [Foreign key constraint](#foreign-key-constraint)
- [Unique constraint](#unique-constraint)
- [Target class does not exist (controller)](#target-class-does-not-exist-controller)
- [Route not defined](#route-not-defined)
- [CSRF mismatch pada fetch](#csrf-mismatch-pada-fetch)
- [File upload kosong](#file-upload-kosong)
- [Gambar 404 setelah unggah](#gambar-404-setelah-unggah)
- [N+1 / lambat](#n1--lambat)
- [Validasi min/max "aneh"](#validasi-minmax-aneh)
- [unique gagal saat edit](#unique-gagal-saat-edit)
- [Session hilang / logout sendiri](#session-hilang--logout-sendiri)
- [env tidak berubah](#env-tidak-berubah)
- [Permission storage](#permission-storage)
- [Vite / @vite error](#vite--vite-error)
- [JSON malah HTML](#json-malah-html)
- [CORS](#cors)
- [Checklist 10 menit](#checklist-10-menit)

---

## Cara membaca error

**Untuk apa:** menghindari menebak.

1. Baca judul exception (`Illuminate\...` atau `ErrorException`).
2. Buka file di `app/` atau `resources/views` pada jejak paling atas yang milikmu.
3. Bandingkan dengan `php artisan route:list` / `migrate:status` jika HTTP/DB.
4. Reproduksi dengan satu request (bukan banyak tab).

**Biasanya digabungkan dengan:** `APP_DEBUG=true` lokal dan `tail` log.

---

## 419 Page Expired

**Untuk apa:** form web ditolak CSRF.

Resep:

1. Pastikan `@csrf` di dalam `<form>`.
2. Satu form = satu token. Jangan form bersarang (HTML tidak mendukung form dalam form dengan benar).
3. Session harus jalan (grup `web`, cookie tidak diblokir).
4. Jangan menonaktifkan CSRF untuk latihan form biasa.

```blade
<form method="POST" action="{{ route('products.store') }}">
    @csrf
```

**Biasanya digabungkan dengan:** `@method` dan session login.

---

## 405 Method Not Allowed

**Untuk apa:** URL ada, metodenya salah.

Resep:

- Hapus memakai GET? Ubah ke POST + `@method('DELETE')`.
- Form `method="POST"` menuju route yang hanya `Route::get`.
- `php artisan route:list --path=produk` — lihat kolom method.

**Biasanya digabungkan dengan:** spoofing method HTML.

---

## 404 Not Found

**Untuk apa:** router atau binding tidak menemukan sumber.

Resep:

1. Path typo: `/produk` vs `/products`.
2. Prefix API: `/api/products`.
3. `findOrFail` / binding: id tidak ada di DB (seeder belum jalan).
4. Route tidak terdaftar: file salah, atau `api.php` belum di-install.
5. Urutan route: `{product}` menelan `create`.

```bash
php artisan route:list --path=produk
```

**Biasanya digabungkan dengan:** `migrate` + `db:seed` dan nama parameter binding.

---

## 403 Forbidden

**Untuk apa:** terautentikasi (atau dikenali) tetapi **tidak diizinkan**.

Resep:

- Policy `update`/`delete` menolak (bukan pemilik).
- `authorize()` Form Request `false`.
- Middleware `can:...` nama parameter salah (`product` vs `produk`).
- `Gate::before` tidak mengizinkan admin yang kamu kira admin.

Ini **bukan** 404. Jangan "memperbaiki" dengan menonaktifkan semua policy di produksi.

**Biasanya digabungkan dengan:** `user_id` pada model dan `@can` hanya untuk UI.

---

## 401 / redirect ke login

**Untuk apa:** middleware `auth` tidak melihat user.

Resep web: buka `/login`, session cookie aktif, `APP_URL` cocok host.

Resep API: kirim token/Bearer atau cookie Sanctum; header `Accept: application/json` agar tidak menerima HTML login.

**Biasanya digabungkan dengan:** guard yang sama (`web` vs `sanctum`).

---

## 422 Validasi

**Untuk apa:** input gagal rule. Web: redirect back. JSON: body `errors`.

Resep:

- Tampilkan `@error('field')`.
- Cek `old()` untuk melihat nilai yang dikirim.
- `min`/`max` tanpa `string`/`integer` sering salah tafsir.
- File: `enctype` + `max` dalam KB.

Jangan menganggap 422 sebagai bug kerangka.

**Biasanya digabungkan dengan:** file 04 dan pesan kustom.

---

## 500 / halaman putih

**Untuk apa:** exception tidak tertangani, atau debug mati.

Resep:

1. `APP_DEBUG=true` di lokal.
2. Baca `storage/logs/laravel.log`.
3. Syntax PHP (titik koma, kurung).
4. Hak tulis `storage/` dan `bootstrap/cache/`.
5. Memory/limit unggah besar.

Halaman putih + debug false = sengaja tidak membocorkan jejak.

**Biasanya digabungkan dengan:** `optimize:clear` jika cache rusak.

---

## Class not found

**Untuk apa:** autoload atau namespace salah.

Resep:

- Namespace file = folder PSR-4 (`App\Models` → `app/Models`).
- Nama class = nama file.
- `use App\Models\Product;` di controller.
- `composer dump-autoload`.
- Typo `ProductController` vs `ProductsController`.

**Biasanya digabungkan dengan:** `make:model` / `make:controller` agar path benar.

---

## View not found

**Untuk apa:** `view('products.index')` tidak ketemu file.

Resep: file harus `resources/views/products/index.blade.php`. Bukan `index.php`. Bukan `Index.blade.php` di Linux (case-sensitive).

Nama titik = folder.

**Biasanya digabungkan dengan:** `return view(...)` yang ejaannya sama.

---

## Undefined variable di Blade

**Untuk apa:** view memakai `$products` yang tidak dikirim.

Resep:

```php
return view('products.index', compact('products'));
```

Salah: `compact($products)`. Salah: variabel `$produk` dikirim, view `$products`.

Paginator vs `null`: kirim `paginate()`, jangan lupa assign.

**Biasanya digabungkan dengan:** `@forelse` yang aman untuk collection kosong (bukan undefined).

---

## Undefined array key

**Untuk apa:** kunci form/array tidak ada.

Resep: validasi `required`/`nullable`, `??`, `$request->input('nama', '')`, `data_get`.

Jangan `$request->all()['nama']` mentah.

**Biasanya digabungkan dengan:** rule di file 04.

---

## Attempt to read property on null

**Untuk apa:** `$x->nama` padahal `$x` null.

Resep:

- `find` tanpa cek → `findOrFail`.
- `$product->category->nama` → `?->` atau eager load + cadangan.
- `auth()->user()->id` di halaman tamu → `auth()->id()` atau `@auth`.

```blade
{{ $product->category?->nama ?? 'Tanpa kategori' }}
```

**Biasanya digabungkan dengan:** relasi nullable dan policy.

---

## Array vs object

**Untuk apa:** `Cannot access offset` / `cannot use object as array`.

Resep:

| Jenis | Akses |
| --- | --- |
| Model | `->nama` |
| `toArray()` / `all()` | `['nama']` |
| `json_decode` tanpa `true` | `->nama` |

`dd($var)` sekali, pilih notasi, jangan campur.

**Biasanya digabungkan dengan:** `@foreach` yang konsisten.

---

## Mass assignment

**Untuk apa:** `Add [harga] to fillable` atau field diam-diam tidak tersimpan.

Resep: tambah ke `$fillable`, **dan** hanya `validated()`. Jangan `$guarded = []` plus `create($request->all())`.

Field `user_id` / `is_admin` jangan fillable dari form.

**Biasanya digabungkan dengan:** validasi dan policy.

---

## SQLSTATE / unknown column

**Untuk apa:** query memakai kolom yang tidak ada.

Resep:

- Typo `nama` vs `name`.
- Migration belum `migrate`.
- `$fillable` / form mengirim field yang tidak ada di tabel.
- `with('kategori')` padahal method relasi `category()`.

```bash
php artisan migrate:status
```

**Biasanya digabungkan dengan:** `model:show` / `db:table`.

---

## SQLSTATE / table not found

**Untuk apa:** tabel belum dibuat, atau nama salah.

Resep: `migrate`. Cek `protected $table`. SQLite file kosong vs MySQL DB lain di `.env`.

**Biasanya digabungkan dengan:** `about` dan `db:show`.

---

## could not find driver

**Untuk apa:** ekstensi PDO tidak aktif.

Resep: pasang/nyalakan `pdo_sqlite` atau `pdo_mysql` sesuai `DB_CONNECTION`. Restart PHP. Bukan salah kode model.

**Biasanya digabungkan dengan:** `.env` `DB_CONNECTION`.

---

## Foreign key constraint

**Untuk apa:** insert/hapus melanggar FK.

Resep:

- Seed anak sebelum induk? Balik urutan: induk dulu.
- `category_id` 99 tidak ada → validasi `exists`.
- Hapus kategori yang masih punya produk → `nullOnDelete` / `cascadeOnDelete` / tolak di policy.

**Biasanya digabungkan dengan:** `constrained()` dan `exists:`.

---

## Unique constraint

**Untuk apa:** email/slug kembar lolos validasi (race) atau seeder dobel.

Resep: index unique di migration. Seeder pakai `firstOrCreate` atau `fresh --seed`. Update form pakai `Rule::unique()->ignore($id)`.

**Biasanya digabungkan dengan:** rule `unique` (lapis UX) + index (lapis DB).

---

## Target class does not exist (controller)

**Untuk apa:** route merujuk class yang tidak ter-autoload.

Resep: `use App\Http\Controllers\ProductController;` — namespace lengkap. Folder `Api/ProductController` = `App\Http\Controllers\Api\ProductController`.

**Biasanya digabungkan dengan:** `route:list` kolom action.

---

## Route not defined

**Untuk apa:** `route('products.index')` tidak ada.

Resep: `->name('products.index')` belum ditulis, atau salah eja `product.index`. Resource memakai nama jamak sesuai argumen `Route::resource('products', ...)`.

**Biasanya digabungkan dengan:** `route:list --name=products`.

---

## CSRF mismatch pada fetch

**Untuk apa:** JS POST ke route `web` tanpa token.

Resep: kirim `_token` atau header `X-CSRF-TOKEN` dari meta. Atau pindah ke route API + token auth, jangan mematikan CSRF sembarangan.

**Biasanya digabungkan dengan:** `csrf_token()` di layout.

---

## File upload kosong

**Untuk apa:** `hasFile` false.

Resep: `enctype="multipart/form-data"`, `name` cocok, `post_max_size` / `upload_max_filesize`, input tidak disabled.

**Biasanya digabungkan dengan:** rule `file`/`image`.

---

## Gambar 404 setelah unggah

**Untuk apa:** path tersimpan, URL tidak.

Resep: `php artisan storage:link`, disk `public`, `Storage::url($path)`, `APP_URL` benar. Jangan menyimpan path absolut mesin lokal ke DB jika lingkungan bisa pindah — simpan path relatif disk.

**Biasanya digabungkan dengan:** file 11.

---

## N+1 / lambat

**Untuk apa:** loop + relasi tanpa `with`.

Resep: `Product::with('category')->paginate(10)`. `whenLoaded` di Resource. `preventLazyLoading` di lokal.

**Biasanya digabungkan dengan:** file 07.

---

## Validasi min/max "aneh"

**Untuk apa:** `min:3` pada angka 10 gagal karena dihitung sebagai string `"10"` panjang 2.

Resep: selalu tulis `integer`/`numeric`/`string`/`array`/`file` di samping `min`/`max`.

**Biasanya digabungkan dengan:** file 04 bagian min/max.

---

## unique gagal saat edit

**Untuk apa:** email lama dianggap bentrok dengan dirinya.

Resep:

```php
Rule::unique('users', 'email')->ignore($user->id)
```

**Biasanya digabungkan dengan:** Form Request update.

---

## Session hilang / logout sendiri

**Untuk apa:** cookie tidak tersimpan.

Resep: `APP_URL` = host yang kamu ketik (`127.0.0.1` ≠ `localhost`). `SESSION_DOMAIN`. Browser memblokir cookie. `config:cache` dengan URL salah.

**Biasanya digabungkan dengan:** login starter dan `session()->regenerate()`.

---

## env tidak berubah

**Untuk apa:** `.env` sudah diedit, aplikasi masih nilai lama.

Resep:

```bash
php artisan optimize:clear
php artisan config:clear
```

Pakai `config('...')` di kode.

**Biasanya digabungkan dengan:** file 13 `env` vs `config`.

---

## Permission storage

**Untuk apa:** `failed to open stream: Permission denied`.

Resep: folder `storage/` dan `bootstrap/cache/` harus bisa ditulis user PHP. Di macOS/Linux lokal, perbaiki owner/chmod secara wajar. Jangan 777 di produksi sebagai solusi tetap.

**Biasanya digabungkan dengan:** log dan view compiled.

---

## Vite / @vite error

**Untuk apa:** layout memanggil Vite tetapi `npm run dev` tidak jalan, atau `build` belum ada.

Resep: `npm install && npm run dev`, atau hapus `@vite` dari layout contoh Blade polos, atau `npm run build`.

**Biasanya digabungkan dengan:** `resources/css/app.css` dan `package.json`.

---

## JSON malah HTML

**Untuk apa:** `fetch` menerima halaman welcome/login.

Resep: URL salah (bukan `/api/...`). Lupa `Accept: application/json`. Middleware `auth` web mengalihkan ke HTML. Exception dengan debug menampilkan HTML.

**Biasanya digabungkan dengan:** file 10.

---

## CORS

**Untuk apa:** console browser: blocked by CORS policy.

Resep: izinkan origin frontend di config CORS. Preflight OPTIONS harus lolos. Jangan `*` + credentials. Server-side fetch (Next server) tidak butuh CORS.

**Biasanya digabungkan dengan:** file 10 bagian CORS.

---

## Checklist 10 menit

Jika "tidak jalan" tanpa pesan jelas:

1. `php artisan about` — PHP, env, DB.
2. `php artisan route:list` — URL terdaftar?
3. `php artisan migrate:status` — tabel ada?
4. `php artisan optimize:clear`
5. Form: `@csrf`, method, `enctype` jika file.
6. Controller: `return` view/redirect/json?
7. Model: `$fillable` + validasi.
8. View: nama variabel.
9. Relasi: `with` + `?->`.
10. Log terakhir di `storage/logs/laravel.log`.

**Biasanya digabungkan dengan:** mengubah **satu** hal per percobaan agar penyebabnya kelihatan.

Kembali ke [daftar ensiklopedia](README.md) atau cheatsheet ringkas [laravel.md](../../laravel.md).
