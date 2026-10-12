# 09 — Middleware, auth, Gate, Policy

[← Migration](08-migration-seeder-factory.md) · [Daftar](README.md) · [Berikutnya: API Resource →](10-api-resource-cors.md)

**Untuk apa middleware:** pemeriksa yang berjalan **sebelum** (dan kadang sesudah) controller. Contoh: "sudah login?", "terlalu banyak request?", "user terverifikasi?".

**Untuk apa auth:** mengidentifikasi siapa yang request (`$request->user()`).

**Untuk apa Gate/Policy:** otorisasi — *bolehkah* user ini melakukan aksi pada data ini? Auth ≠ izin. Login hanya menjawab "siapa". Policy menjawab "boleh hapus produk ini?".

Rujukan: [middleware](https://laravel.com/docs/13.x/middleware), [authentication](https://laravel.com/docs/13.x/authentication), [authorization](https://laravel.com/docs/13.x/authorization).

Di Laravel 11/13, alias middleware didaftarkan di `bootstrap/app.php`, bukan `Kernel.php`.

## Daftar isi

- [Memasang middleware pada route](#memasang-middleware-pada-route)
- [auth](#auth)
- [guest](#guest)
- [verified](#verified)
- [can](#can)
- [throttle](#throttle)
- [Middleware sendiri](#middleware-sendiri)
- [Alias di bootstrap/app.php](#alias-di-bootstrapappphp)
- [Grup web dan api](#grup-web-dan-api)
- [starter autentikasi](#starter-autentikasi)
- [auth() dan $request->user()](#auth-dan-requestuser)
- [attempt login](#attempt-login)
- [logout](#logout)
- [password hash](#password-hash)
- [Gate::define](#gatedefine)
- [Gate::allows dan authorize](#gateallows-dan-authorize)
- [Policy](#policy)
- [Method policy umum](#method-policy-umum)
- [authorize di controller](#authorize-di-controller)
- [AuthorizesRequests / Gate::authorize](#authorizesrequests--gateauthorize)
- [@can di Blade](#can-di-blade)
- [Superadmin via Gate::before](#superadmin-via-gatebefore)
- [Kesalahan auth/izin](#kesalahan-authizin)

---

## Memasang middleware pada route

**Untuk apa:** melindungi URL tertentu.

```php
Route::get('/produk/create', [ProductController::class, 'create'])
    ->middleware('auth')
    ->name('products.create');

Route::middleware(['auth'])->group(function () {
    Route::resource('products', ProductController::class)
        ->except(['index', 'show']);
});
```

Beberapa sekaligus: `middleware(['auth', 'verified'])`.

Urutan penting: `auth` sebelum `can`, karena `can` butuh user.

**Biasanya digabungkan dengan:** `name()`, resource, dan redirect ke login bawaan.

---

## auth

**Untuk apa:** menolak tamu. Belum login → redirect ke route `login` (web) atau 401 (JSON).

```php
Route::middleware('auth')->group(function () {
    Route::get('/profil', [ProfileController::class, 'edit']);
});
```

Guard: `auth:sanctum` untuk API token/SPA Sanctum (setelah paket dipasang).

```php
Route::middleware('auth:sanctum')->get('/user', function (Request $request) {
    return $request->user();
});
```

`auth` tidak memeriksa pemilik data. User A yang login tetap bisa menebak URL `/produk/9/edit` milik B, kecuali ada policy.

**Biasanya digabungkan dengan:** `@auth` di nav, `can` / policy, dan starter login.

---

## guest

**Untuk apa:** kebalikan `auth`. User yang sudah login tidak boleh membuka halaman login/register lagi — dialihkan ke dashboard/home.

```php
Route::middleware('guest')->group(function () {
    Route::get('/login', [SessionController::class, 'create']);
    Route::post('/login', [SessionController::class, 'store']);
});
```

Starter kit sudah memasang ini. Jika kamu menulis login sendiri, pasang `guest` pada form masuk.

**Biasanya digabungkan dengan:** `@guest` di Blade dan route `login`.

---

## verified

**Untuk apa:** menolak user yang belum verifikasi email. Butuh `MustVerifyEmail` pada model User dan notifikasi email.

```php
Route::middleware(['auth', 'verified'])->group(function () {
    Route::get('/checkout', [CheckoutController::class, 'create']);
});
```

Tanpa infrastruktur email, middleware ini mengganggu latihan. Jangan pasang jika tugas tidak meminta verifikasi.

**Biasanya digabungkan dengan:** `auth` (wajib di depan) dan `User implements MustVerifyEmail`.

---

## can

**Untuk apa:** middleware otorisasi singkat: ability + model dari route.

```php
Route::put('/produk/{product}', [ProductController::class, 'update'])
    ->middleware(['auth', 'can:update,product']);
```

`update` = nama method policy. `product` = nama parameter route.

Untuk create tanpa instance:

```php
Route::post('/produk', [ProductController::class, 'store'])
    ->middleware(['auth', 'can:create,App\Models\Product']);
```

Gagal → 403.

**Biasanya digabungkan dengan:** `ProductPolicy` dan route model binding (nama harus cocok).

---

## throttle

**Untuk apa:** membatasi jumlah request. Melindungi login dan API dari brute force / spam.

```php
Route::post('/login', [SessionController::class, 'store'])
    ->middleware('throttle:5,1'); // 5 per 1 menit (pola umum; cek versi)
```

API grup sering sudah punya throttle default.

Jangan mematikan throttle pada login publik tanpa pengganti.

**Biasanya digabungkan dengan:** route login, `api`, dan RateLimiter di `AppServiceProvider` / `bootstrap/app.php` jika butuh aturan kustom.

---

## Middleware sendiri

**Untuk apa:** aturan yang tidak tertutup `auth`/`can`, misalnya "hanya admin", "maintenance kecuali ip".

```bash
php artisan make:middleware EnsureUserIsAdmin
```

```php
<?php

namespace App\Http\Middleware;

use Closure;
use Illuminate\Http\Request;
use Symfony\Component\HttpFoundation\Response;

class EnsureUserIsAdmin
{
    public function handle(Request $request, Closure $next): Response
    {
        if (! $request->user() || $request->user()->peran !== 'admin') {
            abort(403);
        }

        return $next($request);
    }
}
```

Daftarkan alias (Laravel 11/13) di `bootstrap/app.php`:

```php
->withMiddleware(function (Middleware $middleware): void {
    $middleware->alias([
        'admin' => \App\Http\Middleware\EnsureUserIsAdmin::class,
    ]);
})
```

```php
Route::middleware(['auth', 'admin'])->group(function () {
    //
});
```

Untuk izin per model, policy lebih tepat daripada menumpuk middleware.

**Biasanya digabungkan dengan:** `auth` di depan dan kolom `peran` / `is_admin` yang **tidak** mass assign dari form.

---

## Alias di bootstrap/app.php

**Untuk apa:** nama pendek middleware.

```php
use Illuminate\Foundation\Configuration\Middleware;

->withMiddleware(function (Middleware $middleware): void {
    $middleware->alias([
        'admin' => \App\Http\Middleware\EnsureUserIsAdmin::class,
    ]);

    // contoh: CSRF kecuali webhook
    // $middleware->validateCsrfTokens(except: ['stripe/webhook']);
})
```

Jangan menonaktifkan CSRF untuk form biasa.

**Biasanya digabungkan dengan:** `Route::middleware('admin')`.

---

## Grup web dan api

**Untuk apa:** paket middleware default.

| Grup | Isi khas |
| --- | --- |
| `web` | cookie, session, CSRF, binding |
| `api` | throttle, binding, tanpa CSRF form |

`routes/web.php` otomatis grup `web`. `routes/api.php` grup `api`.

Jangan memindah form HTML ke `api.php` lalu heran session/CSRF hilang.

**Biasanya digabungkan dengan:** pilihan "halaman Blade" vs "JSON".

---

## starter autentikasi

**Untuk apa:** halaman login/register siap pakai. Bukan wajib untuk memahami policy.

Opsi umum (sesuai paket yang didukung versimu):

- Laravel Breeze — ringan
- Jetstream — lebih lengkap
- starter resmi lain di installer Laravel 11+

Pasang hanya di proyek latihan yang memang butuh akun. Ensiklopedia ini memakai `auth` secara konseptual: ada model `User`, session login, `Auth::check()`.

Tanpa starter, kamu bisa membuat:

- `User` (sudah ada di proyek default)
- form login + `Auth::attempt`
- route `login`, `logout`

**Biasanya digabungkan dengan:** migration `users` bawaan dan `Hash`.

---

## auth() dan $request->user()

**Untuk apa:** mengambil user saat ini.

```php
auth()->check();
auth()->id();
auth()->user();
auth()->user()?->email;

$request->user();
```

Sama makna di request HTTP yang sudah lewat guard. `null` jika tamu.

Jangan mengandalkan `auth()->user()` di command Artisan tanpa login.

**Biasanya digabungkan dengan:** mengisi `user_id` saat `store`, dan `@auth`.

---

## attempt login

**Untuk apa:** memeriksa email/password lalu menyalakan session.

```php
$ok = auth()->attempt(
    $request->validate([
        'email' => ['required', 'email'],
        'password' => ['required', 'string'],
    ]),
    $request->boolean('remember')
);

if (! $ok) {
    return back()->withErrors([
        'email' => 'Email atau kata sandi salah.',
    ])->onlyInput('email');
}

$request->session()->regenerate();

return redirect()->intended('/produk');
```

`regenerate()` mencegah session fixation. Jangan memberi tahu "email tidak terdaftar" vs "password salah" secara terpisah jika kamu ingin mengurangi enumerasi akun — pesan gabungan lebih aman.

**Biasanya digabungkan dengan:** `guest` middleware, `throttle`, `@csrf`, dan `Hash` di penyimpanan password.

---

## logout

**Untuk apa:** mematikan session.

```php
auth()->logout();
$request->session()->invalidate();
$request->session()->regenerateToken();

return redirect('/');
```

Pakai POST + `@csrf`, bukan GET `/logout`.

**Biasanya digabungkan dengan:** `@auth` tombol keluar.

---

## password hash

**Untuk apa:** tidak menyimpan password polos.

```php
use Illuminate\Support\Facades\Hash;

Hash::make('rahasia');
Hash::check('rahasia', $user->password);
```

Model User modern:

```php
protected $casts = [
    'password' => 'hashed',
    'email_verified_at' => 'datetime',
];
```

Jangan `Hash::make` lagi jika cast `hashed` sudah meng-hash saat assignment.

**Biasanya digabungkan dengan:** `confirmed`, `Password::defaults()`, `current_password`.

---

## Gate::define

**Untuk apa:** izin sederhana tanpa class policy. Cocok ability global: "akses panel", "ekspor laporan".

```php
// AppServiceProvider::boot
use Illuminate\Support\Facades\Gate;
use App\Models\User;

Gate::define('akses-admin', function (User $user) {
    return $user->peran === 'admin';
});
```

```php
if (Gate::allows('akses-admin')) {
    //
}

Gate::authorize('akses-admin'); // 403 jika tidak
```

```blade
@can('akses-admin')
    <a href="{{ url('/admin') }}">Admin</a>
@endcan
```

Untuk izin "ubah produk ini", utamakan Policy.

**Biasanya digabungkan dengan:** `abort(403)` otomatis lewat `authorize`, dan kolom peran.

---

## Gate::allows dan authorize

**Untuk apa:** memeriksa di PHP.

```php
use Illuminate\Support\Facades\Gate;

Gate::allows('update', $product);   // bool
Gate::denies('update', $product);
Gate::authorize('update', $product); // void atau 403
```

User lain (jarang di request biasa):

```php
Gate::forUser($user)->allows('update', $product);
```

**Biasanya digabungkan dengan:** Policy yang didaftarkan otomatis (`Product` → `ProductPolicy`) di Laravel modern.

---

## Policy

**Untuk apa:** kumpulan izin satu model.

```bash
php artisan make:policy ProductPolicy --model=Product
```

Laravel 11+ sering men-discover policy secara konvensi `App\Policies\ProductPolicy` untuk `App\Models\Product`. Jika tidak, daftar di `AppServiceProvider` / `Gate::policy`.

```php
<?php

namespace App\Policies;

use App\Models\Product;
use App\Models\User;

class ProductPolicy
{
    public function viewAny(?User $user): bool
    {
        return true; // daftar publik
    }

    public function view(?User $user, Product $product): bool
    {
        return $product->aktif || $user?->id === $product->user_id;
    }

    public function create(User $user): bool
    {
        return $user->peran !== 'banned';
    }

    public function update(User $user, Product $product): bool
    {
        return $user->id === $product->user_id;
    }

    public function delete(User $user, Product $product): bool
    {
        return $user->id === $product->user_id;
    }
}
```

`?User $user` jika tamu boleh melihat. Method `create` biasanya `User $user` wajib (sudah lewat `auth`).

**Biasanya digabungkan dengan:** kolom `user_id` pada produk, `can:update,product`, dan `@can`.

---

## Method policy umum

| Method | Dipakai untuk |
| --- | --- |
| `viewAny` | index |
| `view` | show |
| `create` | create/store |
| `update` | edit/update |
| `delete` | destroy |
| `restore` | soft delete |
| `forceDelete` | hapus permanen |

Nama harus cocok dengan `authorize('update', $product)` / `can:update,product`.

**Biasanya digabungkan dengan:** resource controller yang memanggil `authorize` di tiap aksi, atau `authorizeResource`.

---

## authorize di controller

**Untuk apa:** menolak di awal method.

```php
public function update(Request $request, Product $product)
{
    $this->authorize('update', $product);
    // ...
}

public function store(Request $request)
{
    $this->authorize('create', Product::class);
    // ...
}
```

`authorizeResource(Product::class)` di constructor memasang otomatis untuk resource.

Form Request:

```php
public function authorize(): bool
{
    return $this->user()->can('create', Product::class);
}
```

atau untuk update, `$this->user()->can('update', $this->route('product'))`.

**Biasanya digabungkan dengan:** validasi setelah izin (atau sebaliknya: izin dulu agar tidak membocorkan error validasi pada data orang lain — izin dulu lebih aman).

---

## AuthorizesRequests / Gate::authorize

Jika controller tidak punya `$this->authorize` (class dasar tipis):

```php
use Illuminate\Support\Facades\Gate;

Gate::authorize('update', $product);
```

Sama hasil: 403.

**Biasanya digabungkan dengan:** Laravel 11 controller tanpa trait otomatis.

---

## @can di Blade

**Untuk apa:** menyembunyikan tombol yang tidak berguna. **Bukan** perlindungan URL.

```blade
@can('update', $product)
    <a href="{{ route('products.edit', $product) }}">Ubah</a>
@endcan

@can('delete', $product)
    <form method="POST" action="{{ route('products.destroy', $product) }}">
        @csrf
        @method('DELETE')
        <button type="submit">Hapus</button>
    </form>
@endcan

@cannot('create', App\Models\Product::class)
    <p>Anda tidak boleh menambah produk.</p>
@endcannot
```

Tanpa policy di route, orang tetap bisa POST ke URL hapus. Pasang middleware/`authorize`.

**Biasanya digabungkan dengan:** `auth` + policy + `@method('DELETE')`.

---

## Superadmin via Gate::before

**Untuk apa:** admin lolos semua pemeriksaan.

```php
Gate::before(function (User $user, string $ability) {
    if ($user->peran === 'admin') {
        return true;
    }

    return null; // lanjut ke policy
});
```

`true` = izinkan. `false` = tolak semua. `null` = biarkan policy memutuskan.

Jangan menaruh `peran` di `$fillable` form publik.

**Biasanya digabungkan dengan:** policy pemilik data untuk user biasa.

---

## Kesalahan auth/izin

| Gejala | Obat |
| --- | --- |
| Redirect ke login terus | belum login / session domain salah / `APP_URL` |
| 403 tak terduga | policy ketat / `authorize` salah ability |
| 403 tidak muncul, data orang lain terubah | tidak ada policy sama sekali |
| `can:update,product` gagal | nama parameter route bukan `product` |
| Login berhasil tapi `auth()->user()` null | salah guard / session tidak tersimpan |
| 419 logout/login | lupa `@csrf` |
| Password tidak cocok padahal "benar" | hash ganda / kolom terpotong |

Lanjut ke [API Resource dan CORS](10-api-resource-cors.md).
