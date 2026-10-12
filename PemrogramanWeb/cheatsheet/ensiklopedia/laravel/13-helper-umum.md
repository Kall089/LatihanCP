# 13 — Helper umum

[← Artisan](12-artisan-katalog.md) · [Daftar](README.md) · [Berikutnya: kesalahan →](14-kesalahan-resep.md)

**Untuk apa helper:** fungsi global yang disediakan Laravel agar tidak menulis path/konfigurasi/debug secara manual. Boleh dipanggil dari controller, Blade, dan banyak class — tetap jangan menaruh logika bisnis besar di dalamnya.

Rujukan: [helpers](https://laravel.com/docs/13.x/helpers).

## Daftar isi

- [route](#route)
- [url](#url)
- [asset](#asset)
- [secure_asset dan secure_url](#secure_asset-dan-secure_url)
- [config](#config)
- [env](#env)
- [old](#old)
- [abort](#abort)
- [abort_if dan abort_unless](#abort_if-dan-abort_unless)
- [dd](#dd)
- [dump](#dump)
- [logger / Log / info](#logger--log--info)
- [now dan today](#now-dan-today)
- [collect](#collect)
- [optional](#optional)
- [session](#session)
- [auth](#auth)
- [csrf_token dan csrf_field](#csrf_token-dan-csrf_field)
- [redirect](#redirect)
- [view](#view)
- [response](#response)
- [request](#request)
- [blank dan filled](#blank-dan-filled)
- [rescue](#rescue)
- [tap](#tap)
- [throw_if](#throw_if)
- [fake](#fake)
- [Str dan Arr](#str-dan-arr)
- [data_get](#data_get)
- [report](#report)
- [Kesalahan helper](#kesalahan-helper)

---

## route

**Untuk apa:** membangun URL dari **nama** route, bukan path tertulis.

```php
route('products.index');
route('products.show', $product);
route('products.show', ['product' => $product]);
route('products.index', ['q' => 'buku']); // query string
route('products.index', absolute: false); // path relatif
```

```blade
<a href="{{ route('products.edit', $product) }}">Ubah</a>
<form action="{{ route('products.store') }}" method="POST">
```

Jika nama tidak ada: exception `RouteNotFoundException`. Cek `route:list`.

**Biasanya digabungkan dengan:** `->name('...')` di file route dan `redirect()->route()`.

---

## url

**Untuk apa:** URL dari path mentah, memakai `APP_URL` sebagai asal.

```php
url('/produk');
url('/produk', ['segmen']);
url()->current();
url()->full();      // termasuk query
url()->previous();
```

Utamakan `route()` jika route punya nama. `url('/produk')` mudah usang saat path berubah.

**Biasanya digabungkan dengan:** redirect kasar dan tautan ke path yang memang tidak bernama.

---

## asset

**Untuk apa:** URL file di folder `public/`.

```php
asset('css/app.css');
asset('images/logo.png');
```

```blade
<link rel="stylesheet" href="{{ asset('css/app.css') }}">
<img src="{{ asset('images/logo.png') }}" alt="">
```

Bukan untuk file di `storage/app/public` secara langsung — pakai `Storage::url` setelah `storage:link` (sering menghasilkan `/storage/...`).

Dengan Vite, CSS/JS modern memakai `@vite`, bukan `asset('build/...')` manual (kecuali kamu tahu outputnya).

**Biasanya digabungkan dengan:** file statis di `public/` dan `APP_URL` yang benar (agar tidak salah host).

---

## secure_asset dan secure_url

**Untuk apa:** memaksa `https://`.

```php
secure_asset('css/app.css');
secure_url('/produk');
```

Di lokal HTTP, ini bisa merusak (browser blokir campuran). Pakai jika produksi wajib HTTPS dan `APP_URL` sudah https.

**Biasanya digabungkan dengan:** produksi di belakang TLS.

---

## config

**Untuk apa:** membaca nilai dari `config/*.php` (yang biasanya mengambil `.env`).

```php
config('app.name');
config('app.debug');
config('database.default');
config('filesystems.default');
config('app.timezone', 'UTC'); // default jika kunci tidak ada
```

Ini cara **benar** di dalam class aplikasi. Bisa di-cache.

Menambah kunci: tulis di file `config/`, baca `env()` **hanya di file config**.

**Biasanya digabungkan dengan:** `config:clear` setelah ubah `.env` yang sudah ter-cache, dan jangan `env()` di controller.

---

## env

**Untuk apa:** membaca `.env` langsung. **Hanya aman di file `config/`.**

```php
// config/app.php
'debug' => (bool) env('APP_DEBUG', false),
```

```php
// JANGAN di controller setelah config:cache
env('APP_DEBUG'); // bisa null
```

Di controller/model/Blade: `config('app.debug')`.

Jangan `env('DB_PASSWORD')` di view. Jangan commit `.env`.

**Biasanya digabungkan dengan:** file config + helper `config()`.

---

## old

**Untuk apa:** mengisi ulang input setelah validasi gagal (atau `withInput()`).

```php
old('nama');
old('nama', $product->nama); // cadangan saat edit
old('tag', []);              // array
```

```blade
<input name="nama" value="{{ old('nama', $product->nama ?? '') }}">
<textarea name="deskripsi">{{ old('deskripsi') }}</textarea>
```

File upload tidak punya `old()` yang bermakna — pengguna pilih ulang.

Nama harus sama dengan `name` input dan kunci validasi.

**Biasanya digabungkan dengan:** `@error`, `$request->validate()`, dan form edit.

---

## abort

**Untuk apa:** menghentikan request dengan kode HTTP + halaman error.

```php
abort(404);
abort(403, 'Anda tidak boleh menghapus produk ini.');
abort(400, 'Parameter tidak lengkap.');
```

Melempar exception yang ditangkap kerangka. Kode setelah `abort` tidak jalan.

**Biasanya digabungkan dengan:** pemeriksaan kasar, dan policy (`authorize` lebih semantik untuk izin).

---

## abort_if dan abort_unless

**Untuk apa:** `abort` bersyarat, lebih pendek daripada `if`.

```php
abort_if($product->stok < 1, 422, 'Stok habis.');
abort_unless($request->user()?->id === $product->user_id, 403);
```

**Biasanya digabungkan dengan:** guard cepat sebelum logika mahal.

---

## dd

**Untuk apa:** *dump and die* — cetak nilai lalu **hentikan** request. Hanya latihan/debug.

```php
dd($product);
dd($request->all());
dd(Product::with('category')->first());
```

Jangan meninggalkan `dd` di kode yang dikumpulkan/dinilai sebagai selesai, apalagi produksi. Halaman berhenti, JSON putus.

Di Tinker, `dd` juga menghentikan sesi.

**Biasanya digabungkan dengan:** menyelidiki object vs array, dan `dump` jika ingin lanjut.

---

## dump

**Untuk apa:** cetak nilai **tanpa** menghentikan.

```php
dump($products);
// kode berikutnya tetap jalan
```

Di Blade latihan: `@dump($product)` (jika tersedia) / jangan di produksi.

**Biasanya digabungkan dengan:** beberapa titik di satu request untuk melihat perubahan.

---

## logger / Log / info

**Untuk apa:** menulis ke `storage/logs/laravel.log` tanpa mematikan request.

```php
use Illuminate\Support\Facades\Log;

logger('Produk dibuat', ['id' => $product->id]);
logger()->info('Pesan');
Log::info('Pesan', ['user' => $request->user()?->id]);
Log::warning('Stok rendah', ['product' => $product->id]);
Log::error('Gagal unggah', ['path' => $path]);
info('Helper info()', ['x' => 1]);
```

Jangan menaruh password di log. Jangan `Log::info($request->all())` jika ada token/sandi.

**Biasanya digabungkan dengan:** `report($e)` pada exception yang kamu gunakan kembali, dan `tail -f storage/logs/laravel.log`.

---

## now dan today

**Untuk apa:** waktu aplikasi sebagai Carbon, menurut `config('app.timezone')`.

```php
now();
now()->addDays(7);
now()->toDateString();
today();
today()->endOfDay();
```

```php
Product::where('created_at', '>=', now()->subDay())->get();
```

Jangan `new DateTime('now')` jika kamu sudah di Laravel — timezone mudah salah.

`now()` bisa di-freeze di tes: `Carbon::setTestNow(...)`.

**Biasanya digabungkan dengan:** `$casts` datetime, `after:today`, dan `timestamps()`.

---

## collect

**Untuk apa:** membungkus array menjadi Collection Laravel: `map`, `filter`, `pluck`, `groupBy`.

```php
collect([1, 2, 3])->map(fn ($n) => $n * 2)->all();

collect($request->input('tag', []))
    ->filter()
    ->unique()
    ->values();

Product::all()->pluck('nama', 'id');
```

Hasil Eloquent `get()` sudah Collection. Jangan `collect()` lagi kecuali dari array biasa.

Collection **bukan** query builder. `Product::all()->where('harga', '>', 10)` memfilter di memori.

**Biasanya digabungkan dengan:** merapikan input array sebelum `sync`, dan API yang menyusun daftar kecil.

---

## optional

**Untuk apa:** mengakses property/method pada nilai yang mungkin `null` tanpa error. Mirip `?->`.

```php
optional($product->category)->nama;
optional($user)->email;
optional($user)->isAdmin();
```

PHP 8: `$product->category?->nama` lebih langsung. `optional()` tetap ada di banyak kode lama.

```php
optional($category, function ($c) {
    return strtoupper($c->nama);
});
```

**Biasanya digabungkan dengan:** relasi `belongsTo` nullable dan tampilan cadangan `?? '—'`.

---

## session

**Untuk apa:** baca/tulis session (grup `web`).

```php
session('success');
session(['success' => 'Tersimpan']);
session()->forget('success');
session()->flash('success', 'Tersimpan'); // hidup sampai request berikutnya
```

`redirect()->with('success', ...)` memakai flash.

API token murni biasanya tidak mengandalkan session.

**Biasanya digabungkan dengan:** Blade `@if (session('success'))` dan login.

---

## auth

**Untuk apa:** helper guard.

```php
auth()->check();
auth()->guest();
auth()->id();
auth()->user();
auth()->logout();
```

**Biasanya digabungkan dengan:** middleware `auth` dan `@auth`.

---

## csrf_token dan csrf_field

**Untuk apa:** token CSRF jika tidak memakai direktif Blade.

```php
csrf_token();
csrf_field(); // HTML hidden input
```

Di Blade, `@csrf` lebih jelas.

Fetch:

```js
headers: { 'X-CSRF-TOKEN': document.querySelector('meta[name="csrf-token"]').content }
```

**Biasanya digabungkan dengan:** layout yang punya `<meta name="csrf-token" content="{{ csrf_token() }}">`.

---

## redirect

**Untuk apa:** helper respons pindah URL.

```php
redirect('/produk');
redirect()->route('products.index');
redirect()->back();
redirect()->intended('dashboard');
```

**Biasanya digabungkan dengan:** `with()`, PRG (Post/Redirect/Get).

---

## view

**Untuk apa:** merender Blade.

```php
view('products.index', compact('products'));
view()->share('appNama', config('app.name')); // jarang; hati-hati global
```

**Biasanya digabungkan dengan:** `compact` dan nama view titik.

---

## response

**Untuk apa:** membangun respons non-view.

```php
response('OK', 200);
response()->json(['ok' => true]);
response()->noContent();
response()->download($path);
response()->redirectToRoute('products.index');
```

**Biasanya digabungkan dengan:** API dan unduhan privat.

---

## request

**Untuk apa:** mengakses request saat ini tanpa injection — berguna di helper/Blade, kurang eksplisit di controller.

```php
request('nama');
request()->query('q');
request()->user();
```

Di controller, utamakan `Request $request` agar mudah ditest.

**Biasanya digabungkan dengan:** Blade yang perlu query (`request('q')`) secara hemat.

---

## blank dan filled

**Untuk apa:** cek "kosong" gaya Laravel: `null`, string kosong, string hanya spasi, array kosong — **bukan** `0` atau `false` secara sama dengan `empty()`.

```php
blank(null);   // true
blank('');     // true
blank('  ');   // true
blank(0);      // false
filled('a');   // true
```

Lebih aman daripada `empty()` untuk field yang boleh 0.

**Biasanya digabungkan dengan:** `when(filled($q), ...)` pada filter.

---

## rescue

**Untuk apa:** menjalankan callback, tangkap exception, kembalikan cadangan.

```php
$nilai = rescue(fn () => json_decode($teks, true, 512, JSON_THROW_ON_ERROR), []);
```

Jangan menelan semua error bisnis dengan `rescue`. Log bisa hilang.

**Biasanya digabungkan dengan:** parsing yang boleh gagal, plus `report`.

---

## tap

**Untuk apa:** menyentuh objek lalu mengembalikannya (rantai).

```php
$product = tap($product, function ($p) {
    $p->increment('views');
});
```

Bisa membuat kode lebih sulit dibaca. Opsional.

**Biasanya digabungkan dengan:** rantai fluent yang butuh efek samping.

---

## throw_if

**Untuk apa:** melempar exception jika syarat benar.

```php
throw_if($product->stok < 1, \RuntimeException::class, 'Stok habis');
```

Untuk HTTP, `abort_if` biasanya lebih tepat.

**Biasanya digabungkan dengan:** domain exception di service class.

---

## fake

**Untuk apa:** faker di luar factory (seeder cepat, tinker).

```php
fake()->name();
fake()->unique()->safeEmail();
fake()->numberBetween(1000, 50000);
```

**Biasanya digabungkan dengan:** factory `definition()`.

---

## Str dan Arr

**Untuk apa:** utilitas string dan array.

```php
use Illuminate\Support\Str;
use Illuminate\Support\Arr;

Str::slug('Buku CSS Dasar');
Str::limit($teks, 80);
Str::uuid();
Arr::get($data, 'alamat.kota');
Arr::only($data, ['nama', 'harga']);
Arr::except($data, ['password']);
```

**Biasanya digabungkan dengan:** slug artikel dan memangkas array tervalidasi.

---

## data_get

**Untuk apa:** mengambil nilai bersarang dengan titik, default jika tidak ada.

```php
data_get($array, 'alamat.kota', '—');
data_get($object, 'category.nama');
```

Tidak error jika kunci tengah hilang.

**Biasanya digabungkan dengan:** JSON/`$casts` array dan input bersarang.

---

## report

**Untuk apa:** mengirim exception ke logger/handler tanpa menghentikan request (kecuali kamu melempar lagi).

```php
try {
    // ...
} catch (\Throwable $e) {
    report($e);
    return back()->with('error', 'Gagal memproses.');
}
```

**Biasanya digabungkan dengan:** `Log` dan halaman error ramah pengguna.

---

## Kesalahan helper

| Gejala | Obat |
| --- | --- |
| `route()` error | nama salah / parameter binding kurang |
| `env()` null | pakai `config()`, `config:clear` |
| `old()` kosong | validasi tidak lewat kerangka / salah nama |
| `asset` 404 | file tidak di `public/` |
| `dd` tertinggal | hapus sebelum kumpul |
| Collection vs query | `where` setelah `get()` memfilter memori |

Lanjut ke [kesalahan dan resep](14-kesalahan-resep.md).
