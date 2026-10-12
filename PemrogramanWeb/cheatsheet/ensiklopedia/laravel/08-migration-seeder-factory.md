# 08 — Migration, seeder, factory

[← Relasi](07-relasi-eager-load.md) · [Daftar](README.md) · [Berikutnya: middleware →](09-middleware-auth-gate-policy.md)

**Untuk apa migration:** mencatat struktur tabel dalam kode agar semua orang (dan kamu di komputer lain) bisa `php artisan migrate` dan mendapat bentuk database yang sama.

**Untuk apa seeder:** mengisi data awal atau data latihan.

**Untuk apa factory:** cetakan data palsu yang masuk akal, dipakai seeder dan tes.

Rujukan: [migrations](https://laravel.com/docs/13.x/migrations), [seeding](https://laravel.com/docs/13.x/seeding), [factories](https://laravel.com/docs/13.x/eloquent-factories).

## Daftar isi

- [make:migration dan make:model -m](#makemigration-dan-makemodel--m)
- [up dan down](#up-dan-down)
- [id](#id)
- [timestamps](#timestamps)
- [string](#string)
- [text](#text)
- [integer dan unsignedInteger](#integer-dan-unsignedinteger)
- [boolean](#boolean)
- [date dan datetime](#date-dan-datetime)
- [foreignId dan constrained](#foreignid-dan-constrained)
- [nullable](#nullable)
- [unique dan index](#unique-dan-index)
- [enum](#enum)
- [json](#json)
- [softDeletes](#softdeletes)
- [foreignId morphs](#foreignid-morphs)
- [tabel pivot](#tabel-pivot)
- [alter tabel yang sudah ada](#alter-tabel-yang-sudah-ada)
- [migrate, rollback, fresh](#migrate-rollback-fresh)
- [Factory](#factory)
- [state factory](#state-factory)
- [relasi di factory](#relasi-di-factory)
- [Seeder](#seeder)
- [DatabaseSeeder](#databaseseeder)
- [Urutan relasi saat seed](#urutan-relasi-saat-seed)
- [Kesalahan migration/seeder](#kesalahan-migrationseeder)

---

## make:migration dan make:model -m

**Untuk apa:** membuat file timestamp di `database/migrations`.

```bash
php artisan make:model Product -m
php artisan make:migration create_products_table
php artisan make:migration add_stok_to_products_table --table=products
```

Nama `create_..._table` membuat kerangka `Schema::create`. Nama `add_..._to_...` membuat kerangka `Schema::table`.

Jangan mengedit migration yang sudah dijalankan di lingkungan bersama. Buat file baru.

**Biasanya digabungkan dengan:** model Eloquent dan `php artisan migrate`.

---

## up dan down

**Untuk apa:** `up()` menerapkan perubahan. `down()` membalik saat rollback.

```php
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
```

`down()` yang kosong membuat `migrate:rollback` tidak mengembalikan struktur. Untuk latihan, `dropIfExists` pada `create` sudah cukup.

Rollback menghapus data tabel itu. Jangan andalkan rollback di produksi sebagai "undo bisnis".

**Biasanya digabungkan dengan:** `migrate` dan kontrol versi git.

---

## id

**Untuk apa:** kunci utama bigint auto increment `id`.

```php
$table->id();
```

Setara `bigIncrements('id')`. Relasi `foreignId('product_id')` merujuk ini.

UUID:

```php
$table->uuid('id')->primary();
```

Maka model perlu `$incrementing = false` dan `$keyType = 'string'` plus generate UUID. Untuk tugas dasar, `id()` cukup.

**Biasanya digabungkan dengan:** route model binding dan `exists:products,id`.

---

## timestamps

**Untuk apa:** kolom `created_at` dan `updated_at`. Eloquent mengisinya otomatis.

```php
$table->timestamps();
```

Tanpa ini, model default akan error saat save (kecuali `$timestamps = false`).

Hanya `created_at`:

```php
$table->timestamp('created_at')->nullable();
```

tapi lebih baik `timestamps()` lengkap.

**Biasanya digabungkan dengan:** `latest()`, `oldest()`, dan tampilan "dibuat pada".

---

## string

**Untuk apa:** teks pendek. Default panjang 255.

```php
$table->string('nama');
$table->string('nama', 100);
$table->string('email')->unique();
$table->string('slug', 100)->unique();
```

Samakan `max:100` di validasi dengan panjang kolom.

Jangan `string` untuk artikel panjang — pakai `text`.

**Biasanya digabungkan dengan:** rule `string|max:...` dan `unique`.

---

## text

**Untuk apa:** teks panjang: deskripsi, isi komentar, bio.

```php
$table->text('deskripsi');
$table->longText('konten');
```

Tidak punya "panjang 100" seperti string. Validasi tetap `string|max:5000` agar tidak kebablasan.

**Biasanya digabungkan dengan:** textarea Blade dan rule `nullable|string`.

---

## integer dan unsignedInteger

**Untuk apa:** bilangan bulat. `unsigned` menolak negatif di level DB (berguna untuk harga/stok).

```php
$table->unsignedInteger('harga');
$table->unsignedInteger('stok')->default(0);
$table->integer('urutan')->default(0);
$table->unsignedTinyInteger('rating'); // 0–255
$table->bigInteger('views')->default(0);
```

Harga uang: banyak tugas memakai integer rupiah (45000) agar terhindar dari pecahan float. Kalau butuh desimal: `decimal('harga', 12, 2)`.

**Biasanya digabungkan dengan:** validasi `integer|min:0` dan `increment('stok')`.

---

## boolean

**Untuk apa:** ya/tidak. Disimpan kecil (0/1).

```php
$table->boolean('aktif')->default(true);
$table->boolean('terbit')->default(false);
```

```php
protected $casts = ['aktif' => 'boolean'];
```

**Biasanya digabungkan dengan:** checkbox, `$request->boolean('aktif')`, rule `boolean`.

---

## date dan datetime

**Untuk apa:** tanggal tanpa jam, atau tanggal+jam.

```php
$table->date('tanggal_lahir')->nullable();
$table->dateTime('deadline')->nullable();
$table->timestamp('terbit_pada')->nullable();
```

`$casts` `'deadline' => 'datetime'` memberi Carbon.

**Biasanya digabungkan dengan:** rule `date` / `after:today`.

---

## foreignId dan constrained

**Untuk apa:** kolom FK + constraint ke tabel induk.

```php
$table->foreignId('category_id')->constrained();
$table->foreignId('user_id')->constrained()->cascadeOnDelete();
$table->foreignId('category_id')->nullable()->constrained()->nullOnDelete();
```

`constrained()` mengasumsikan tabel `categories` dari `category_id`. Jika nama tabel beda:

```php
$table->foreignId('category_id')->constrained('kategori');
```

`cascadeOnDelete()`: hapus induk → anak ikut terhapus.  
`nullOnDelete()`: hapus induk → FK anak jadi null (kolom harus `nullable`).  
`restrict` (default banyak DB): hapus induk ditolak jika masih ada anak.

Urutan migrate: tabel induk dulu. Nama file timestamp menentukan urutan.

**Biasanya digabungkan dengan:** `belongsTo` / `hasMany` dan `exists:categories,id`.

---

## nullable

**Untuk apa:** kolom boleh SQL `NULL`.

```php
$table->string('catatan', 500)->nullable();
$table->foreignId('category_id')->nullable()->constrained();
```

Field form opsional harus `nullable` di validasi **dan** di schema, atau insert `null` gagal.

Default tanpa `nullable()` = `NOT NULL`. `create` tanpa field itu akan error kecuali ada `default()`.

**Biasanya digabungkan dengan:** rule `nullable` dan `??` di Blade.

---

## unique dan index

**Untuk apa:** `unique` menolak duplikat. `index` mempercepat pencarian tanpa menolak sama.

```php
$table->string('email')->unique();
$table->string('sku', 40)->unique();
$table->index('nama');
$table->index(['category_id', 'aktif']);
```

Validasi `unique` tidak menggantikan index unique.

**Biasanya digabungkan dengan:** `Rule::unique` dan login by email.

---

## enum

**Untuk apa:** kumpulan nilai tetap di DB.

```php
$table->enum('status', ['draft', 'terbit', 'arsip'])->default('draft');
```

Alternatif lebih fleksibel: `string('status', 20)` + validasi `in:`. Mengubah enum di sebagian DB merepotkan.

**Biasanya digabungkan dengan:** rule `in:draft,terbit,arsip`.

---

## json

**Untuk apa:** menyimpan struktur kecil yang tidak perlu ditabelkan.

```php
$table->json('meta')->nullable();
```

```php
protected $casts = ['meta' => 'array'];
```

Jangan menaruh data yang sering dicari di JSON jika kamu butuh `where` cepat — buat kolom biasa.

**Biasanya digabungkan dengan:** `$casts` array dan validasi `array`.

---

## softDeletes

**Untuk apa:** kolom `deleted_at`. `delete()` tidak menghapus fisik.

```php
$table->softDeletes();
```

```php
use Illuminate\Database\Eloquent\SoftDeletes;

class Product extends Model
{
    use SoftDeletes;
}
```

Query biasa menyembunyikan yang terhapus. `Product::withTrashed()->get()`.

**Biasanya digabungkan dengan:** `restore()`, policy, dan daftar "arsip".

---

## foreignId morphs

**Untuk apa:** dua kolom polimorfik.

```php
$table->morphs('commentable'); // commentable_id + commentable_type + index
$table->nullableMorphs('imageable');
```

**Biasanya digabungkan dengan:** `morphMany` / `morphTo`.

---

## tabel pivot

**Untuk apa:** many-to-many.

```php
Schema::create('product_tag', function (Blueprint $table) {
    $table->id();
    $table->foreignId('product_id')->constrained()->cascadeOnDelete();
    $table->foreignId('tag_id')->constrained()->cascadeOnDelete();
    $table->timestamps();

    $table->unique(['product_id', 'tag_id']);
});
```

Tanpa unique pasangan, `attach` dua kali membuat baris ganda.

Bisa tanpa `$table->id()` (composite primary). `id()` memudahkan sebagian kasus.

**Biasanya digabungkan dengan:** `belongsToMany` dan `sync`.

---

## alter tabel yang sudah ada

**Untuk apa:** menambah/mengubah kolom setelah tabel terpakai.

```bash
php artisan make:migration add_stok_to_products_table --table=products
```

```php
public function up(): void
{
    Schema::table('products', function (Blueprint $table) {
        $table->unsignedInteger('stok')->default(0)->after('harga');
    });
}

public function down(): void
{
    Schema::table('products', function (Blueprint $table) {
        $table->dropColumn('stok');
    });
}
```

SQLite punya keterbatasan alter. Di latihan, `migrate:fresh` sering lebih cepat daripada alter rumit.

**Biasanya digabungkan dengan:** model `$fillable` yang ikut diubah.

---

## migrate, rollback, fresh

```bash
php artisan migrate
php artisan migrate --pretend
php artisan migrate:status
php artisan migrate:rollback
php artisan migrate:rollback --step=1
php artisan migrate:reset
php artisan migrate:fresh          # HAPUS semua tabel lalu migrate
php artisan migrate:fresh --seed
php artisan migrate:refresh --seed
```

`fresh` **menghapus data**. Hanya di lokal/latihan, atau jika kamu sadar.

Jangan `fresh` di produksi.

**Biasanya digabungkan dengan:** factory/seeder setelah struktur berubah besar.

---

## Factory

**Untuk apa:** menghasilkan atribut palsu yang valid.

```bash
php artisan make:factory ProductFactory --model=Product
```

```php
<?php

namespace Database\Factories;

use App\Models\Category;
use App\Models\Product;
use Illuminate\Database\Eloquent\Factories\Factory;

/** @extends Factory<Product> */
class ProductFactory extends Factory
{
    public function definition(): array
    {
        return [
            'nama' => fake()->words(3, true),
            'harga' => fake()->numberBetween(1000, 200000),
            'stok' => fake()->numberBetween(0, 50),
            'category_id' => Category::factory(),
        ];
    }
}
```

Model:

```php
use HasFactory;
```

Pakai:

```php
Product::factory()->create();
Product::factory()->count(20)->create();
Product::factory()->make(); // tidak disimpan
```

`fake()` adalah faker. Jangan memakai factory untuk data produksi nyata.

**Biasanya digabungkan dengan:** `HasFactory`, seeder, dan tes.

---

## state factory

**Untuk apa:** variasi: habis, nonaktif, mahal.

```php
public function habis(): static
{
    return $this->state(fn () => ['stok' => 0]);
}

public function nonaktif(): static
{
    return $this->state(fn () => ['aktif' => false]);
}
```

```php
Product::factory()->habis()->create();
Product::factory()->count(5)->nonaktif()->create();
```

**Biasanya digabungkan dengan:** tes yang butuh kondisi spesifik.

---

## relasi di factory

```php
'category_id' => Category::factory(),
```

Membuat kategori baru per produk — bisa kebanyakan. Lebih terkendali:

```php
$kategori = Category::factory()->create();
Product::factory()->count(10)->create([
    'category_id' => $kategori->id,
]);
```

atau:

```php
Category::factory()
    ->has(Product::factory()->count(5))
    ->create();
```

```php
Product::factory()
    ->for($kategori)
    ->create();
```

Many-to-many:

```php
Product::factory()
    ->hasAttached(Tag::factory()->count(3))
    ->create();
```

**Biasanya digabungkan dengan:** `hasMany`/`belongsTo` yang sudah terpasang.

---

## Seeder

**Untuk apa:** class yang memanggil factory atau `create` manual.

```bash
php artisan make:seeder ProductSeeder
```

```php
<?php

namespace Database\Seeders;

use App\Models\Product;
use Illuminate\Database\Seeder;

class ProductSeeder extends Seeder
{
    public function run(): void
    {
        Product::factory()->count(20)->create();

        Product::factory()->create([
            'nama' => 'Buku CSS wajib',
            'harga' => 40000,
        ]);
    }
}
```

```bash
php artisan db:seed --class=ProductSeeder
```

Menjalankan seeder dua kali bisa menggandakan data (kecuali kamu `firstOrCreate` / `fresh`).

**Biasanya digabungkan dengan:** `DatabaseSeeder` dan `migrate:fresh --seed`.

---

## DatabaseSeeder

**Untuk apa:** pusat urutan seeder.

```php
public function run(): void
{
    $this->call([
        UserSeeder::class,
        CategorySeeder::class,
        ProductSeeder::class,
    ]);
}
```

```bash
php artisan db:seed
```

User admin latihan:

```php
use App\Models\User;
use Illuminate\Support\Facades\Hash;

User::factory()->create([
    'name' => 'Admin Latihan',
    'email' => 'admin@contoh.test',
    'password' => 'password', // di-hash oleh cast hashed
]);
```

Jangan memakai password ini di produksi.

**Biasanya digabungkan dengan:** urutan FK (user/kategori sebelum produk).

---

## Urutan relasi saat seed

1. Tabel tanpa FK: users, categories, tags.
2. Tabel anak: products (`category_id`).
3. Pivot: attach tag.
4. Anak lain: comments (`product_id`, `user_id`).

Salah urutan → error FK.

**Biasanya digabungkan dengan:** `foreignId()->constrained()` yang ketat.

---

## Kesalahan migration/seeder

| Gejala | Obat |
| --- | --- |
| could not find driver | ekstensi PDO/SQLite/MySQL |
| table already exists | sudah migrate; jangan create ulang |
| cannot add foreign key | urutan tabel / tipe id tidak cocok / tabel induk belum ada |
| unique violation saat seed | seeder dijalankan dua kali |
| factory Class not found | `HasFactory` / namespace / dump-autoload |
| SQLite alter gagal | `fresh` di latihan atau migration create ulang |
| data hilang | kamu menjalankan `fresh` |

Lanjut ke [middleware, auth, gate, policy](09-middleware-auth-gate-policy.md).
