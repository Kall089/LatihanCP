# 06 — Eloquent: CRUD dan query

[← Blade](05-blade-direktif-lengkap.md) · [Daftar](README.md) · [Berikutnya: relasi →](07-relasi-eager-load.md)

**Untuk apa Eloquent:** membaca dan menulis tabel lewat class model, bukan string SQL panjang. Satu class `Product` mewakili tabel `products` (jamak, snake_case).

Rujukan: [Eloquent](https://laravel.com/docs/13.x/eloquent), [query](https://laravel.com/docs/13.x/queries).

## Daftar isi

- [Model minimal](#model-minimal)
- [$fillable dan $guarded](#fillable-dan-guarded)
- [$casts dan $hidden](#casts-dan-hidden)
- [all](#all)
- [get](#get)
- [find](#find)
- [findOrFail](#findorfail)
- [first dan firstOrFail](#first-dan-firstorfail)
- [where](#where)
- [orWhere](#orwhere)
- [whereIn, whereNull, whereBetween](#wherein-wherenull-wherebetween)
- [when](#when)
- [orderBy dan latest](#orderby-dan-latest)
- [limit dan take](#limit-dan-take)
- [with](#with)
- [create](#create)
- [update](#update)
- [delete](#delete)
- [increment dan decrement](#increment-dan-decrement)
- [count, exists, sum](#count-exists-sum)
- [firstOrCreate dan updateOrCreate](#firstorcreate-dan-updateorcreate)
- [fresh dan refresh](#fresh-dan-refresh)
- [toArray dan toJson](#toarray-dan-tojson)
- [Query builder vs Eloquent](#query-builder-vs-eloquent)
- [N+1 sebagai pengingat](#n1-sebagai-pengingat)
- [Kesalahan Eloquent](#kesalahan-eloquent)

---

## Model minimal

**Untuk apa:** menghubungkan class ke tabel.

```php
<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Product extends Model
{
    protected $fillable = ['nama', 'harga', 'stok', 'category_id'];
}
```

Konvensi: `Product` → tabel `products`. Jika berbeda:

```php
protected $table = 'barang';
```

Kunci utama default `id`. Timestamps default `created_at`, `updated_at`. Matikan:

```php
public $timestamps = false;
```

**Biasanya digabungkan dengan:** migration, `$fillable`, dan relasi.

---

## $fillable dan $guarded

**Untuk apa:** daftar kolom yang boleh diisi lewat `create()` / `update($array)` / `fill()`.

```php
protected $fillable = ['nama', 'harga', 'stok'];
```

Atau kebalikan (semua kecuali):

```php
protected $guarded = ['id'];
```

Jangan `$guarded = []` di produksi jika request bisa masuk ke `create($request->all())`. Lebih aman `$fillable` eksplisit + hanya data tervalidasi.

Kolom seperti `is_admin`, `user_id` (pemilik) **jangan** di-fill dari form mentah. Set di controller: `'user_id' => $request->user()->id`.

Ini bukan validasi panjang/tipe.

**Biasanya digabungkan dengan:** `$request->validate()` / `validated()`.

---

## $casts dan $hidden

**Untuk apa:** `$casts` mengubah tipe saat dibaca/ditulis. `$hidden` menyembunyikan kolom saat model jadi JSON/array.

```php
protected $casts = [
    'aktif' => 'boolean',
    'harga' => 'integer',
    'terbit_pada' => 'datetime',
    'meta' => 'array',
    'password' => 'hashed',
];

protected $hidden = ['password', 'remember_token'];
```

`hashed` meng-hash otomatis saat diisi (User). Jangan hash dua kali secara manual.

**Biasanya digabungkan dengan:** API Resource (lebih eksplisit daripada mengandalkan `$hidden` saja) dan form `boolean`.

---

## all

**Untuk apa:** mengambil **semua** baris tabel sebagai Collection model.

```php
$products = Product::all();
```

Tidak ada `where`, tidak ada `limit`. Berbahaya pada tabel besar. Untuk drowpdown kecil (kategori 10 baris) masih wajar. Untuk produk toko, pakai `paginate` atau `get` + syarat.

`all()` menjalankan query segera. Tidak bisa di-chain `where` **setelah** `all()` pada query builder — hasilnya sudah Collection.

Salah: `Product::all()->where('harga', '>', 1000)` — itu filter Collection di PHP, bukan SQL. Untuk data besar, salah tempat.

**Biasanya digabungkan dengan:** tabel referensi kecil dan `@foreach` Blade.

---

## get

**Untuk apa:** menjalankan query yang sudah kamu rangkai, mengembalikan Collection.

```php
$products = Product::where('stok', '>', 0)
    ->orderBy('nama')
    ->get();
```

Tanpa `get()`/`first()`/`paginate()`, query belum dijalankan (masih builder). Lupa `get()` lalu dikirim ke `@foreach` = error atau perilaku aneh.

`get(['nama', 'harga'])` membatasi kolom. Hati-hati: relasi dan `$hidden` tetap berlaku; primary key sering tetap perlu untuk relasi.

**Biasanya digabungkan dengan:** `where`, `orderBy`, `with`, dan view daftar yang tidak perlu pagination (jumlah terjamin kecil).

---

## find

**Untuk apa:** mencari satu baris menurut **kunci utama**. Tidak ketemu → `null`.

```php
$product = Product::find(1);
$beberapa = Product::find([1, 2, 3]); // Collection
```

```php
if (! $product) {
    abort(404);
}
```

Lebih ringkas: `findOrFail`. Jangan `find` lalu mengakses `$product->nama` tanpa cek — error property on null.

**Biasanya digabungkan dengan:** cabang "jika ada", bukan halaman detail wajib. Untuk URL `{id}`, utamakan binding atau `findOrFail`.

---

## findOrFail

**Untuk apa:** seperti `find`, tetapi **404** jika tidak ada. Ini yang kamu inginkan untuk halaman detail/edit/hapus.

```php
$product = Product::findOrFail($id);
```

Route model binding sudah melakukan ini. Method `show(Product $product)` tidak perlu `findOrFail` lagi.

`findOrFail([1, 2])` melempar jika **salah satu** tidak ada (perilaku versi: cek dokumen jika memakai array).

**Biasanya digabungkan dengan:** controller tanpa binding, dan API yang mengembalikan 404 JSON.

---

## first dan firstOrFail

**Untuk apa:** satu baris pertama dari query, bukan menurut id.

```php
$product = Product::where('slug', $slug)->first();
$product = Product::where('slug', $slug)->firstOrFail();
```

Tanpa `orderBy`, "pertama" menurut urutan database — tidak dijamin. Tambah `orderBy` / `latest` jika makna "pertama" penting.

`first()` → `null` jika kosong. `firstOrFail()` → 404.

**Biasanya digabungkan dengan:** `where` pada kolom unik (`email`, `slug`).

---

## where

**Untuk apa:** filter SQL `WHERE` kolom dibandingkan nilai.

```php
Product::where('aktif', true)->get();
Product::where('harga', '>=', 10000)->get();
Product::where('nama', 'like', '%'.$q.'%')->get();
```

Tanda tangan:

- `where('kolom', $nilai)` → `=`
- `where('kolom', 'operator', $nilai)`

Jangan merangkai input ke `like` tanpa membatasi panjang (`max` validasi). Wildcard `%` di kedua sisi tidak memakai index dengan baik — cukup untuk latihan.

Beberapa syarat AND:

```php
Product::where('aktif', true)
    ->where('stok', '>', 0)
    ->get();
```

Group:

```php
Product::where('aktif', true)
    ->where(function ($query) use ($q) {
        $query->where('nama', 'like', '%'.$q.'%')
            ->orWhere('sku', 'like', '%'.$q.'%');
    })
    ->get();
```

**Biasanya digabungkan dengan:** `get` / `first` / `paginate` / `orWhere` / `when`.

---

## orWhere

**Untuk apa:** syarat ATAU.

```php
Product::where('nama', 'like', '%buku%')
    ->orWhere('sku', 'like', '%buku%')
    ->get();
```

Tanpa group, `orWhere` mudah "merusak" filter lain:

```php
// berbahaya: aktif=false bisa ikut karena OR
Product::where('aktif', true)
    ->orWhere('nama', 'like', '%x%')
    ->get();
```

Bungkus OR di dalam `where(function (...) { ... })`.

**Biasanya digabungkan dengan:** pencarian multi-kolom dan `when($q, ...)`.

---

## whereIn, whereNull, whereBetween

**Untuk apa:** filter daftar, kosong, dan rentang.

```php
Product::whereIn('id', [1, 2, 3])->get();
Product::whereNull('deleted_at')->get();
Product::whereNotNull('published_at')->get();
Product::whereBetween('harga', [1000, 50000])->get();
```

`whereIn` dengan array sangat besar bisa lambat. `whereNull` cocok kolom opsional.

Soft delete: trait `SoftDeletes` sudah menambahkan syarat `deleted_at` null secara otomatis.

**Biasanya digabungkan dengan:** filter form (harga min–max) dan id terpilih.

---

## when

**Untuk apa:** menambah `where` hanya jika syarat PHP benar. Menghindari `if` panjang.

```php
$products = Product::query()
    ->when($request->query('q'), function ($query, string $q) {
        $query->where('nama', 'like', '%'.$q.'%');
    })
    ->when($request->query('category_id'), function ($query, $id) {
        $query->where('category_id', $id);
    })
    ->paginate(10)
    ->withQueryString();
```

Argumen kedua `when` adalah nilai yang dianggap true. `when(0, ...)` tidak menjalankan callback — hati-hati jika 0 sah.

**Biasanya digabungkan dengan:** `query()` di `index` dan pagination.

---

## orderBy dan latest

**Untuk apa:** mengurutkan hasil.

```php
Product::orderBy('nama')->get();
Product::orderBy('harga', 'desc')->get();
Product::latest()->get();          // created_at desc
Product::latest('updated_at')->get();
Product::oldest()->get();          // created_at asc
```

Beberapa kolom: `orderBy('kategori')->orderBy('nama')`.

Tanpa order, urutan tidak dijanjikan. Pagination tanpa order bisa "loncat" antar halaman.

**Biasanya digabungkan dengan:** `paginate`, `first`, dan daftar admin.

---

## limit dan take

**Untuk apa:** membatasi jumlah baris.

```php
Product::latest()->limit(5)->get();
Product::latest()->take(5)->get(); // alias
Product::skip(10)->take(10)->get();
```

`limit` tanpa `orderBy` = 5 baris acak secara semantik. `paginate` lebih tepat untuk halaman daftar.

**Biasanya digabungkan dengan:** widget "terbaru", homepage, dan `latest()`.

---

## with

**Untuk apa:** eager load relasi dalam query yang sama (lebih tepat: query tambahan yang terencana), menghindari N+1.

```php
$products = Product::with('category')->get();
$products = Product::with(['category', 'comments.user'])->paginate(10);
```

Tanpa `with`, loop `$product->category->nama` menembak query per baris.

Detail relasi: [07-relasi-eager-load.md](07-relasi-eager-load.md). Dicantumkan di sini karena `with` adalah method query yang sering kamu tulis di `index`/`show`.

Constraint:

```php
Product::with(['comments' => function ($query) {
    $query->where('terbit', true)->latest();
}])->get();
```

**Biasanya digabungkan dengan:** `hasMany`/`belongsTo` dan `@foreach` yang menampilkan relasi.

---

## create

**Untuk apa:** insert satu baris dari array, mengembalikan model.

```php
$product = Product::create([
    'nama' => 'Buku CSS',
    'harga' => 40000,
    'stok' => 10,
]);
```

Kolom harus `$fillable`. `created_at`/`updated_at` terisi otomatis.

```php
Product::create($request->validated());
```

Jangan:

```php
Product::create($request->all());
```

Cara lain (dua langkah):

```php
$product = new Product;
$product->nama = 'Buku';
$product->harga = 40000;
$product->save();
```

`create` lebih pendek untuk data tervalidasi.

**Biasanya digabungkan dengan:** `store`, `$fillable`, dan `redirect`.

---

## update

**Untuk apa:** mengubah baris yang sudah dimuat, atau mass update query.

Satu model:

```php
$product->update([
    'nama' => 'Buku HTML',
    'harga' => 35000,
]);
```

atau:

```php
$product->nama = 'Buku HTML';
$product->save();
```

Mass update (tanpa event per model, hati-hati):

```php
Product::where('stok', 0)->update(['aktif' => false]);
```

`$product->update($data)` menghormati `$fillable`. Mass `Model::where->update` menulis kolom langsung — tetap hati-hati dengan array sumber.

**Biasanya digabungkan dengan:** `validated()`, unique ignore, dan `redirect` ke `show`.

---

## delete

**Untuk apa:** menghapus baris.

```php
$product->delete();
Product::destroy(1);
Product::destroy([1, 2, 3]);
Product::where('aktif', false)->delete();
```

`destroy($id)` mencari lalu delete (event model jalan). `query()->delete()` massal bisa melewati sebagian event.

Soft delete: `use SoftDeletes;` — `delete()` mengisi `deleted_at`. Pulihkan: `$product->restore()`. Paksa hapus: `forceDelete()`.

File terkait tidak ikut terhapus otomatis.

**Biasanya digabungkan dengan:** policy `delete`, `@method('DELETE')`, dan `cascadeOnDelete` di FK.

---

## increment dan decrement

**Untuk apa:** menambah/mengurangi kolom angka di database tanpa race "baca–hitung–tulis" yang mudah kalah saing.

```php
$product->increment('stok');
$product->increment('stok', 5);
$product->decrement('stok', 1);
```

SQL setara `stok = stok + 5`. Lebih aman daripada:

```php
$product->stok = $product->stok - 1;
$product->save();
```

pada stok yang diubah bersamaan.

Bisa menambah update kolom lain:

```php
$product->increment('terjual', 1, ['updated_at' => now()]);
```

**Biasanya digabungkan dengan:** stok, hitungan lihat (`views`), dan transaksi `DB::transaction`.

---

## count, exists, sum

**Untuk apa:** agregat tanpa mengambil semua baris.

```php
Product::count();
Product::where('aktif', true)->count();
Product::where('sku', $sku)->exists();
Product::sum('stok');
Product::where('category_id', 1)->avg('harga');
```

`exists()` lebih hemat daripada `count() > 0` jika kamu hanya butuh ya/tidak.

**Biasanya digabungkan dengan:** dashboard, unique manual, dan `@if` "sudah ada?".

---

## firstOrCreate dan updateOrCreate

**Untuk apa:** cari, kalau tidak ada buat; atau perbarui menurut kunci unik.

```php
$tag = Tag::firstOrCreate(['nama' => 'alat-tulis']);

$product = Product::updateOrCreate(
    ['sku' => 'PRD-0001'],
    ['nama' => 'Buku', 'harga' => 40000],
);
```

Argumen pertama = syarat cari. Kedua = nilai isi/ubah.

Hati-hati race: dua request bersamaan bisa gagal unique. Index unik di DB tetap perlu.

**Biasanya digabungkan dengan:** seeder, impor, dan sinkronisasi data.

---

## fresh dan refresh

**Untuk apa:** membaca ulang dari database.

```php
$product->increment('stok');
$product->refresh(); // property $product->stok ikut
$baru = $product->fresh(); // instance baru
```

Berguna setelah increment atau setelah relasi berubah.

**Biasanya digabungkan dengan:** tes dan alur stok.

---

## toArray dan toJson

**Untuk apa:** mengubah model jadi array/JSON mentah.

```php
$product->toArray();
$product->toJson();
```

Kolom `$hidden` hilang. Relasi yang sudah di-load ikut. Untuk API publik, utamakan API Resource agar bentuknya disengaja.

**Biasanya digabungkan dengan:** debug dan Resource `parent::toArray($request)` yang kemudian dipangkas.

---

## Query builder vs Eloquent

```php
use Illuminate\Support\Facades\DB;

DB::table('products')->where('stok', '>', 0)->get(); // stdClass, bukan model
Product::where('stok', '>', 0)->get();               // model Product
```

Pakai Eloquent jika butuh relasi, `$casts`, event. Pakai `DB::table` untuk laporan agregat berat yang tidak butuh model.

**Biasanya digabungkan dengan:** `select` + `join` pada laporan, Eloquent pada CRUD.

---

## N+1 sebagai pengingat

```php
$products = Product::all();
foreach ($products as $product) {
    echo $product->category->nama; // query category berulang
}
```

Obat:

```php
$products = Product::with('category')->get();
```

Di latihan, `Model::preventLazyLoading(! app()->isProduction())` di `AppServiceProvider` membantu ketahuan.

**Biasanya digabungkan dengan:** `with`, `hasMany`, Blade bersarang.

---

## Kesalahan Eloquent

| Gejala | Obat |
| --- | --- |
| Mass assignment | Tambah field ke `$fillable` atau jangan mass assign |
| SQL unknown column | Migration belum dijalankan / salah nama |
| `all()` lambat | `paginate` / filter |
| `find` null lalu error | `findOrFail` |
| `like` tidak ketemu | wildcard `%`, atau kolom salah |
| Data tidak berubah | Lupa `save()` / `update()` tidak di-return / validasi gagal |
| Soft deleted masih "hilang" | `withTrashed()` |
| `get()` lupa | `@foreach` pada builder |

Lanjut ke [relasi dan eager load](07-relasi-eager-load.md).
