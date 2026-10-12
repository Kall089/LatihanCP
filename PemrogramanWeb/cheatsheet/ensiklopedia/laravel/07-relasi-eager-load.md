# 07 — Relasi Eloquent dan eager load

[← Eloquent](06-eloquent-crud-query.md) · [Daftar](README.md) · [Berikutnya: migration →](08-migration-seeder-factory.md)

**Untuk apa relasi:** menyatakan bahwa baris di satu tabel **milik** atau **punya banyak** baris di tabel lain, lalu mengaksesnya sebagai property: `$product->category`, `$category->products`.

Relasi bukan magic. Kolom foreign key di database tetap wajib. Relasi Eloquent hanya memudahkan query.

Rujukan: [relationships](https://laravel.com/docs/13.x/eloquent-relationships), [eager loading](https://laravel.com/docs/13.x/eloquent-relationships#eager-loading).

## Daftar isi

- [Syarat sebelum menulis relasi](#syarat-sebelum-menulis-relasi)
- [belongsTo](#belongsto)
- [hasMany](#hasmany)
- [hasOne](#hasone)
- [belongsToMany](#belongstomany)
- [withPivot dan pivot](#withpivot-dan-pivot)
- [sync, attach, detach](#sync-attach-detach)
- [morphOne](#morphone)
- [morphMany](#morphmany)
- [morphTo](#morphto)
- [morphToMany / morphedByMany](#morphtomany--morphedbymany)
- [hasOneThrough / hasManyThrough](#hasonethrough--hasmanythrough)
- [with](#with)
- [load dan loadMissing](#load-dan-loadmissing)
- [withCount](#withcount)
- [whereHas](#wherehas)
- [Lazy loading dan N+1](#lazy-loading-dan-n1)
- [Membuat relasi lewat model](#membuat-relasi-lewat-model)
- [Relasi nullable](#relasi-nullable)
- [Kesalahan relasi](#kesalahan-relasi)

---

## Syarat sebelum menulis relasi

**Untuk apa:** menghindari relasi yang "ada di model" tetapi query gagal.

1. Migration punya kolom FK atau tabel pivot.
2. Nama method relasi jelas: `category()`, `products()`, `comments()`.
3. Foreign key mengikuti konvensi: `category_id` untuk `belongsTo(Category::class)`.
4. Jika nama kolom menyimpang, tulis argumen kedua/ketiga relasi.

```php
public function category()
{
    return $this->belongsTo(Category::class, 'id_kategori', 'id');
}
```

Jangan lupa `return`. Tanpa `return`, `$product->category` tidak bekerja.

**Biasanya digabungkan dengan:** `foreignId()->constrained()` di migration.

---

## belongsTo

**Untuk apa:** sisi **anak** yang menyimpan FK. Produk milik satu kategori. Komentar milik satu user.

Tabel `products` punya `category_id`.

```php
// app/Models/Product.php
public function category()
{
    return $this->belongsTo(Category::class);
}
```

Pakai:

```php
$product->category;          // Category|null
$product->category?->nama;
$product->category()->associate($category);
$product->save();
```

`associate` mengisi FK tanpa save sampai `save()`.

Query:

```php
Product::where('category_id', $id)->get();
Product::whereBelongsTo($category)->get();
```

**Biasanya digabungkan dengan:** `hasMany` di model induk, `exists:categories,id` pada validasi, dan `with('category')`.

---

## hasMany

**Untuk apa:** sisi **induk** yang punya banyak anak. Satu kategori punya banyak produk.

```php
// app/Models/Category.php
public function products()
{
    return $this->hasMany(Product::class);
}
```

Pakai:

```php
$category->products; // Collection
$category->products()->where('aktif', true)->get();
$category->products()->create([
    'nama' => 'Pensil',
    'harga' => 5000,
]);
```

`create` pada relasi mengisi `category_id` otomatis.

Jangan `Product::where(...)` panjang jika kamu sudah punya `$category` — `$category->products()` lebih jelas.

**Biasanya digabungkan dengan:** `belongsTo` di anak, `with('products')`, dan `withCount('products')`.

---

## hasOne

**Untuk apa:** induk punya **tepat satu** anak, atau "satu yang dianggap utama". Contoh: user punya satu profil. Satu produk punya satu stok gudang utama.

```php
// app/Models/User.php
public function profile()
{
    return $this->hasOne(Profile::class);
}
```

```php
// app/Models/Profile.php
public function user()
{
    return $this->belongsTo(User::class);
}
```

Tabel `profiles` punya `user_id` **unik**.

```php
$user->profile;
$user->profile()->create(['bio' => 'Halo']);
```

Jika sebenarnya bisa banyak, jangan `hasOne` — pakai `hasMany`. `hasOne` bisa disalahgunakan sebagai "ambil first dari hasMany"; lebih jujur `hasMany` + syarat.

**Biasanya digabungkan dengan:** `belongsTo` kebalikan, unique index `user_id`, dan `with('profile')`.

---

## belongsToMany

**Untuk apa:** banyak ke banyak. Produk punya banyak tag; tag punya banyak produk. Tidak ada FK di salah satu tabel utama — ada **tabel pivot**.

Tabel `product_tag`: `product_id`, `tag_id`. Nama pivot default: nama model diurutkan alfabet + underscore.

```php
// Product
public function tags()
{
    return $this->belongsToMany(Tag::class);
}

// Tag
public function products()
{
    return $this->belongsToMany(Product::class);
}
```

Jika nama pivot tidak standar:

```php
return $this->belongsToMany(Tag::class, 'produk_tag', 'id_produk', 'id_tag');
```

Pakai:

```php
$product->tags;
$product->tags->pluck('nama');
```

**Biasanya digabungkan dengan:** migration pivot, `attach`/`sync`, `with('tags')`, dan checkbox `tag_id[]`.

---

## withPivot dan pivot

**Untuk apa:** kolom tambahan di pivot, misalnya `jumlah` atau `created_at`.

```php
return $this->belongsToMany(Product::class)
    ->withPivot('jumlah')
    ->withTimestamps();
```

```php
foreach ($order->products as $product) {
    $product->pivot->jumlah;
}
```

Tanpa `withPivot`, kolom extra tidak tersedia (kecuali id FK default).

**Biasanya digabungkan dengan:** `belongsToMany` dan `sync` yang membawa array data pivot.

---

## sync, attach, detach

**Untuk apa:** mengubah isi relasi many-to-many.

```php
$product->tags()->attach($tagId);
$product->tags()->attach([1, 2, 3]);
$product->tags()->attach([1 => ['jumlah' => 2]]);

$product->tags()->detach($tagId);
$product->tags()->detach(); // semua

$product->tags()->sync([1, 2, 3]); // hasil akhir persis daftar ini
$product->tags()->syncWithoutDetaching([4]);
$product->tags()->toggle([1, 2]);
```

`sync` **menghapus** relasi yang tidak disebut. Cocok form edit checkbox: kirim semua id terpilih.

Validasi: `'tag_id' => ['array']`, `'tag_id.*' => ['integer', 'exists:tags,id']`.

**Biasanya digabungkan dengan:** `belongsToMany` dan `validated()['tag_id'] ?? []`.

---

## morphOne

**Untuk apa:** satu model "punya satu" relasi yang **bisa dimiliki banyak jenis induk**. Contoh: `Image` milik `User` **atau** `Product`, satu gambar utama.

Tabel `images`:

- `url`
- `imageable_id`
- `imageable_type` — nama class, misalnya `App\Models\Product`

```php
// Image
public function imageable()
{
    return $this->morphTo();
}

// Product
public function image()
{
    return $this->morphOne(Image::class, 'imageable');
}

// User
public function image()
{
    return $this->morphOne(Image::class, 'imageable');
}
```

**Biasanya digabungkan dengan:** `morphTo` di model gambar, dan unggah file.

---

## morphMany

**Untuk apa:** seperti `hasMany`, tetapi anak bisa menempel ke banyak jenis induk. Contoh: komentar pada artikel **dan** pada video.

```php
// Comment
public function commentable()
{
    return $this->morphTo();
}

// Article / Video
public function comments()
{
    return $this->morphMany(Comment::class, 'commentable');
}
```

```php
$article->comments()->create([
    'isi' => 'Bagus',
    'user_id' => $request->user()->id,
]);
```

Kolom: `commentable_id`, `commentable_type`.

**Biasanya digabungkan dengan:** `morphTo`, `with('comments.user')`, dan policy komentar.

---

## morphTo

**Untuk apa:** sisi anak polimorfik: "induk saya jenis apa?".

```php
public function commentable()
{
    return $this->morphTo();
}
```

```php
$comment->commentable; // Article atau Video, dll.
```

Nama method `commentable` harus cocok awalan kolom `commentable_id` + `commentable_type`.

**Biasanya digabungkan dengan:** `morphMany`/`morphOne` di induk, dan `MorphTo` eager load:

```php
Comment::with('commentable')->get();
```

---

## morphToMany / morphedByMany

**Untuk apa:** tag polimorfik: satu tabel `tags` menandai produk, artikel, dll.

Tabel pivot `taggables`: `tag_id`, `taggable_id`, `taggable_type`.

```php
// Tag
public function products()
{
    return $this->morphedByMany(Product::class, 'taggable');
}

// Product
public function tags()
{
    return $this->morphToMany(Tag::class, 'taggable');
}
```

Hanya pakai jika `belongsToMany` biasa tidak cukup (lebih dari satu jenis model tertag).

**Biasanya digabungkan dengan:** `sync` dan API Resource yang menampilkan daftar tag.

---

## hasOneThrough / hasManyThrough

**Untuk apa:** menembus satu tabel perantara. Contoh: `Supplier` → `products` → `orders` (banyak order lewat produk).

```php
public function orders()
{
    return $this->hasManyThrough(Order::class, Product::class);
}
```

Argumen FK bisa disebut jika tidak standar. Baca dokumen saat nama kolom aneh.

**Biasanya digabungkan dengan:** laporan, bukan pengganti query eksplisit jika join rumit.

---

## with

**Untuk apa:** eager load saat query induk.

```php
Category::with('products')->get();
Product::with('category')->paginate(10);
Product::with(['category', 'tags', 'comments.user'])->findOrFail($id);
```

Dot `comments.user` = komentar + user tiap komentar.

Array bersyarat:

```php
Product::with([
    'comments' => fn ($q) => $q->where('terbit', true)->latest()->limit(5),
])->get();
```

`limit` pada relasi eager constrained berlaku per query relasi, bukan selalu "5 per induk" di semua versi/pola — untuk "5 terbaru per produk" sering butuh pola lebih lanjut. Untuk daftar penuh, jangan `limit` di constraint jika makna tidak kamu uji.

**Biasanya digabungkan dengan:** `index`/`show` dan Blade yang menampilkan relasi.

---

## load dan loadMissing

**Untuk apa:** eager load pada model yang **sudah** diambil.

```php
public function show(Product $product)
{
    $product->load('category', 'tags');
    $product->loadMissing('comments.user');

    return view('products.show', compact('product'));
}
```

`loadMissing` tidak mengulang jika sudah ada. Berguna di helper yang tidak tahu apakah caller sudah `with`.

**Biasanya digabungkan dengan:** route model binding (binding tidak otomatis `with`).

---

## withCount

**Untuk apa:** menambah atribut `{relasi}_count` tanpa memuat semua anak.

```php
$categories = Category::withCount('products')->get();
$categories[0]->products_count;
```

Syarat:

```php
Category::withCount(['products' => fn ($q) => $q->where('aktif', true)])->get();
```

Nama default bisa diubah: `withCount(['products as jumlah_aktif' => ...])`.

**Biasanya digabungkan dengan:** daftar kategori di sidebar dan urut `orderBy('products_count', 'desc')`.

---

## whereHas

**Untuk apa:** filter induk yang **punya** anak sesuai syarat.

```php
Category::whereHas('products', function ($q) {
    $q->where('stok', '>', 0);
})->get();

Product::whereHas('tags', fn ($q) => $q->where('nama', 'diskon'))->get();
```

`whereDoesntHave` = tidak punya.

`has('products')` = punya minimal satu, tanpa syarat extra.

Ini berbeda dengan `with`. `with` hanya memuat. `whereHas` memfilter.

**Biasanya digabungkan dengan:** filter toko "kategori yang masih ada stok" dan pencarian tag.

---

## Lazy loading dan N+1

**Lazy load:** pertama kali `$product->category` diakses, query jalan. Dalam loop 50 produk = 1 + 50 query.

```php
$products = Product::all(); // 1 query
foreach ($products as $p) {
    $p->category->nama; // +1 per produk
}
```

**Eager:**

```php
$products = Product::with('category')->get(); // 1 + 1 query
```

Deteksi di lokal:

```php
// AppServiceProvider::boot
Model::preventLazyLoading(! app()->isProduction());
```

Exception saat lazy load membantu menemukan view yang lupa `with`.

**Biasanya digabungkan dengan:** `with` di controller, bukan di dalam `@foreach`.

---

## Membuat relasi lewat model

```php
$category->products()->create($data);

$product->comments()->create([
    'isi' => $data['isi'],
    'user_id' => $request->user()->id,
]);

$user->profile()->create(['bio' => '']);
```

FK terisi dari induk. Jangan mengandalkan `category_id` dari form jika URL sudah scoped ke kategori — lebih aman dari induk.

`save` pada relasi:

```php
$product = new Product($data);
$category->products()->save($product);
```

**Biasanya digabungkan dengan:** `validated()` tanpa menyertakan FK mentah jika tidak perlu.

---

## Relasi nullable

`belongsTo` bisa `null` jika FK `nullable`.

```blade
{{ $product->category?->nama ?? 'Tanpa kategori' }}
```

```php
$product->category()->dissociate();
$product->save();
```

Jangan `$product->category->nama` tanpa `?->`.

**Biasanya digabungkan dengan:** `nullable|exists` dan tampilan cadangan.

---

## Kesalahan relasi

| Gejala | Obat |
| --- | --- |
| `null` terus | FK salah, nama method salah, lupa `return` |
| Table pivot not found | Nama pivot tidak standar, sebut argumen kedua |
| Attribute pivot missing | `withPivot` |
| N+1 / lambat | `with` / `withCount` |
| `call to a member function add() on null` | Relasi tidak mengembalikan relation |
| Salah anak ter-load (scoped) | `scopeBindings()` di route |
| `imageable_type` aneh | Pastikan morph map jika nama class berubah |

Lanjut ke [migration, seeder, factory](08-migration-seeder-factory.md).
