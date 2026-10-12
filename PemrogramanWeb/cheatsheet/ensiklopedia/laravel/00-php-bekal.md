# 00 — Bekal PHP sebelum Laravel

[← Daftar ensiklopedia](README.md) · [Berikutnya: instalasi →](01-install-struktur-folder.md)

PHP berjalan di **server**. Browser tidak mengeksekusi file `.php` sendiri. Web server atau `php artisan serve` yang menjalankan skrip, lalu mengirim HTML atau JSON ke browser.

Laravel adalah kerangka di atas PHP. Kalau `$variabel`, array, `foreach`, fungsi, class, `namespace`, dan type hint belum nyaman, baca file ini dulu. Setiap potongan di bawah berdiri sendiri.

Dokumentasi bahasa: [php.net](https://www.php.net/manual/en/). Laravel modern butuh PHP sesuai persyaratan versi framework yang kamu pasang (Laravel 11/13 memakai PHP 8.2+).

## Daftar isi

- [Tag pembuka](#tag-pembuka)
- [Titik koma dan komentar](#titik-koma-dan-komentar)
- [Variabel](#variabel)
- [Tipe data](#tipe-data)
- [String](#string)
- [Operator](#operator)
- [Null coalescing dan nullsafe](#null-coalescing-dan-nullsafe)
- [Percabangan if](#percabangan-if)
- [match](#match)
- [Array indeks](#array-indeks)
- [Array asosiatif](#array-asosiatif)
- [Array bersarang](#array-bersarang)
- [isset, empty, count](#isset-empty-count)
- [array_key_exists dan in_array](#array_key_exists-dan-in_array)
- [array_map, array_filter, array_merge](#array_map-array_filter-array_merge)
- [foreach nilai](#foreach-nilai)
- [foreach kunci dan nilai](#foreach-kunci-dan-nilai)
- [foreach referensi](#foreach-referensi)
- [for dan while](#for-dan-while)
- [Fungsi](#fungsi)
- [Parameter default dan named argument](#parameter-default-dan-named-argument)
- [Return type dan void](#return-type-dan-void)
- [Arrow function](#arrow-function)
- [Variadic](#variadic)
- [Class](#class)
- [Constructor property promotion](#constructor-property-promotion)
- [Visibility](#visibility)
- [Inheritance](#inheritance)
- [Interface](#interface)
- [Trait](#trait)
- [Namespace](#namespace)
- [use untuk import](#use-untuk-import)
- [Type hint skalar](#type-hint-skalar)
- [Type hint nullable dan union](#type-hint-nullable-dan-union)
- [Type hint class dan array](#type-hint-class-dan-array)
- [strict_types](#strict_types)
- [Exception](#exception)
- [json_encode dan json_decode](#json_encode-dan-json_decode)
- [htmlspecialchars](#htmlspecialchars)
- [Superglobal](#superglobal)
- [Object vs array](#object-vs-array)
- [Kesalahan PHP yang sering ketemu di Laravel](#kesalahan-php-yang-sering-ketemu-di-laravel)

---

## Tag pembuka

**Untuk apa:** menandai bahwa file ini berisi kode PHP. File Blade Laravel memakai `{{ }}` dan `@direktif`, jadi jarang menulis `<?php` panjang di view. File class (controller, model) selalu diawali `<?php`.

```php
<?php

echo 'Halo dari server';
```

Jangan memakai tag pendek `<?` di proyek Laravel. Tag `<?= $nama ?>` setara `echo`, tetapi di Blade pakai `{{ $nama }}` agar ter-escape.

File class modern **tidak** memakai tag penutup `?>`. Tag penutup mudah menyisakan spasi tersembunyi yang merusak header HTTP.

**Biasanya digabungkan dengan:** `namespace` di baris berikutnya pada file class Laravel.

---

## Titik koma dan komentar

**Untuk apa:** mengakhiri pernyataan dan menulis catatan. PHP mewajibkan `;` di akhir pernyataan. Lupa titik koma menghasilkan parse error.

```php
<?php

$nama = 'Haikal'; // komentar satu baris
$harga = 45000;

/*
    Komentar beberapa baris.
    Tidak dijalankan.
*/
```

Di Laravel, komentar berguna di controller yang punya alur panjang, tetapi jangan menumpuk komentar yang hanya mengulang nama fungsi.

**Biasanya digabungkan dengan:** file class yang rapi: satu tanggung jawab per method.

---

## Variabel

**Untuk apa:** menyimpan nilai yang bisa berubah: nama produk, jumlah, status login, hasil query.

Nama variabel **selalu** diawali `$`. Huruf pertama setelah `$` tidak boleh angka. PHP membedakan huruf besar/kecil: `$Nama` bukan `$nama`.

```php
<?php

$nama = 'Buku CSS';
$harga = 40000;
$tersedia = true;
$deskripsi = null;

$nama = 'Buku HTML'; // nilai lama diganti
```

Variabel belum diisi lalu dibaca memicu peringatan "Undefined variable". Di Blade, data harus dikirim dari controller (`compact`, array, atau `view(..., [...])`).

Jangan memakai variabel tanpa `$`. Ini salah: `nama = 'Buku';`.

**Biasanya digabungkan dengan:** type hint pada parameter fungsi agar isi `$nama` tidak sembarang tipe.

---

## Tipe data

**Untuk apa:** membedakan teks, angka, ya/tidak, kosong, daftar, dan objek.

| Tipe | Contoh | Dipakai untuk |
| --- | --- | --- |
| `string` | `'Buku'` | Nama, email, slug |
| `int` | `45000` | Harga rupiah bulat, id, stok |
| `float` | `0.12` | Persentase, jika memang pecahan |
| `bool` | `true` / `false` | Status aktif, sudah bayar |
| `null` | `null` | Belum ada nilai |
| `array` | `['a', 'b']` | Daftar, form array, hasil `toArray()` |
| `object` | `$produk` | Model Eloquent, stdClass JSON |

```php
<?php

$judul = 'Pensil';          // string
$stok = 12;                 // int
$diskon = 0.1;              // float
$aktif = true;              // bool
$catatan = null;            // null
$tag = ['alat', 'tulis'];   // array
```

Laravel validasi membedakan `integer` dan `numeric`. `integer` menolak `"12.5"`. `numeric` menerima angka dalam bentuk string dari form.

Casting paksa:

```php
<?php

$id = (int) '15';     // 15
$teks = (string) 15;  // "15"
$flag = (bool) 0;     // false
```

**Biasanya digabungkan dengan:** rule validasi Laravel (`integer`, `numeric`, `string`, `boolean`) agar data form sesuai tipe yang diharapkan model.

---

## String

**Untuk apa:** menyimpan teks. Tanda kutip ganda men interpolasi variabel; tanda kutip tunggal tidak.

```php
<?php

$nama = 'Haikal';

$satu = "Halo, $nama";      // Halo, Haikal
$dua = 'Halo, $nama';       // Halo, $nama  (literal)
$tiga = 'Halo, ' . $nama;   // gabung dengan titik
```

String panjang di Laravel sering memakai interpolasi di dalam pesan flash atau JSON:

```php
<?php

$pesan = "Produk {$nama} berhasil disimpan.";
```

Kurung kurawal `{$nama}` membuat interpolasi jelas jika nama menempel kata lain.

Jangan menempelkan input pengguna ke HTML dengan `echo $nama`. Pakai `htmlspecialchars` atau `{{ $nama }}` di Blade.

**Biasanya digabungkan dengan:** helper `old()`, pesan validasi, dan `response()->json()`.

---

## Operator

**Untuk apa:** hitung, bandingkan, dan gabungkan nilai.

```php
<?php

$a = 10;
$b = 3;

$a + $b;   // 13
$a - $b;   // 7
$a * $b;   // 30
$a / $b;   // 3.333...
$a % $b;   // 1  sisa bagi
```

Perbandingan:

```php
<?php

$a == $b;   // sama nilai, tipe boleh beda ('10' == 10 → true)
$a === $b;  // sama nilai dan tipe
$a != $b;
$a !== $b;
$a > $b;
$a >= $b;
```

Di Laravel dan PHP modern, utamakan `===` / `!==` agar `"0"` tidak dianggap sama dengan `0` tanpa sadar, kecuali memang ingin perbandingan longgar.

Logika:

```php
<?php

$aktif && $stok > 0;
$aktif || $stok > 0;
! $aktif;
```

**Biasanya digabungkan dengan:** `@if` Blade dan query `where` (perbandingan di database, bukan di PHP, jika datanya banyak).

---

## Null coalescing dan nullsafe

**Untuk apa:** memberi cadangan jika nilai `null` atau kunci array tidak ada, tanpa error.

```php
<?php

$nama = $input['nama'] ?? 'Tamu';
$kota = $user['alamat']['kota'] ?? null;
```

`??` tidak mengganti `0` atau `''` (string kosong). Kalau ingin cadangan untuk nilai "kosong" secara longgar, pakai `empty()` atau helper Laravel `blank()`.

Nullsafe object:

```php
<?php

$kota = $user?->alamat?->kota;
```

Jika `$user` atau `alamat` `null`, hasilnya `null`, bukan error "attempt to read property on null".

**Biasanya digabungkan dengan:** `$request->input('q', '')`, `optional()`, dan relasi Eloquent yang boleh kosong.

---

## Percabangan if

**Untuk apa:** menjalankan kode hanya jika syarat terpenuhi.

```php
<?php

if ($stok <= 0) {
    $status = 'habis';
} elseif ($stok < 5) {
    $status = 'hampir habis';
} else {
    $status = 'tersedia';
}
```

Syarat yang menghasilkan nilai "truthy" di PHP: angka selain 0, string tidak kosong, array tidak kosong, `true`. Yang "falsy": `0`, `0.0`, `''`, `'0'`, `[]`, `null`, `false`.

`'0'` adalah falsy. Ini sering mengecoh saat mengecek input form. Lebih aman memakai `===` atau helper `filled()` di Laravel.

**Biasanya digabungkan dengan:** `@if` / `@elseif` / `@else` di Blade untuk tampilan, dan early return di controller (`if (! $ok) { abort(403); }`).

---

## match

**Untuk apa:** memilih nilai berdasarkan perbandingan ketat (`===`), lebih ringkas daripada `switch`.

```php
<?php

$label = match ($status) {
    'pending' => 'Menunggu',
    'paid' => 'Sudah bayar',
    'cancel' => 'Dibatalkan',
    default => 'Tidak diketahui',
};
```

Jika tidak ada `default` dan nilai tidak cocok, PHP melempar `UnhandledMatchError`. Tambahkan `default` untuk data dari luar yang tidak selalu lengkap.

**Biasanya digabungkan dengan:** menampilkan status pesanan di API Resource atau Blade.

---

## Array indeks

**Untuk apa:** daftar berurutan: daftar nama, id, atau hasil sederhana.

```php
<?php

$warna = ['merah', 'hijau', 'biru'];

$warna[0];      // merah
$warna[] = 'kuning'; // tambah di akhir
count($warna);  // 4
```

Indeks mulai dari 0. Mengakses indeks yang tidak ada memicu peringatan. Cek dulu dengan `isset($warna[3])` atau `array_key_exists(3, $warna)`.

**Biasanya digabungkan dengan:** `in` rule validasi (`in:merah,hijau,biru`) dan `@foreach` Blade.

---

## Array asosiatif

**Untuk apa:** data bernama: field form, satu baris tabel yang sudah diubah ke array, konfigurasi kecil.

```php
<?php

$produk = [
    'nama' => 'Buku',
    'harga' => 45000,
    'aktif' => true,
];

$produk['nama'];   // Buku
$produk['stok'] ?? 0;
```

Kunci adalah string. Ini mirip object JavaScript, tetapi aksesnya pakai `[]`, bukan `.`.

Di Eloquent, model adalah **object**: `$produk->nama`. Setelah `$produk->toArray()`, aksesnya `$produk['nama']`. Jangan mencampur keduanya tanpa sadar.

**Biasanya digabungkan dengan:** `$request->only(['nama', 'harga'])`, `$fillable`, dan `validate([...])`.

---

## Array bersarang

**Untuk apa:** daftar item, tiap item punya field. Hasil form `items[0][nama]` atau data seeder.

```php
<?php

$daftar = [
    ['nama' => 'Buku', 'harga' => 45000],
    ['nama' => 'Pensil', 'harga' => 5000],
];

$daftar[0]['nama']; // Buku
```

Validasi Laravel untuk ini memakai notasi titik: `daftar.*.nama` => `required|string`.

**Biasanya digabungkan dengan:** rule `array` + `*.` dan `@foreach` di Blade.

---

## isset, empty, count

**Untuk apa:** memeriksa apakah nilai ada, dianggap kosong, atau berapa banyak anggota array.

```php
<?php

$nama = 'Haikal';
$kosong = '';
$daftar = [];

isset($nama);     // true — variabel ada dan bukan null
isset($tidakAda); // false
empty($kosong);   // true — '' dianggap kosong
empty($daftar);   // true
count($daftar);   // 0
```

`isset` pada kunci array:

```php
<?php

isset($produk['nama']);
```

`empty(0)` adalah `true`. Jangan memakai `empty` untuk mengecek harga yang boleh 0 jika 0 adalah nilai sah.

Di Blade ada `@isset` dan `@empty`. Di request Laravel ada `$request->has()` dan `$request->filled()`.

**Biasanya digabungkan dengan:** tampilan "belum ada data" dan rule `nullable`.

---

## array_key_exists dan in_array

**Untuk apa:** `array_key_exists` cek kunci, meski nilainya `null`. `in_array` cek apakah nilai ada di daftar.

```php
<?php

$data = ['catatan' => null];

isset($data['catatan']);              // false — karena null
array_key_exists('catatan', $data);   // true

in_array('Buku', ['Buku', 'Pensil'], true);
```

Argumen ketiga `true` pada `in_array` membuat perbandingan ketat. Tanpa itu, `in_array(0, ['abc'])` bisa mengecoh di versi/konteks tertentu. Biasakan `true`.

**Biasanya digabungkan dengan:** rule `in:` di validasi Laravel (lebih jelas untuk input form).

---

## array_map, array_filter, array_merge

**Untuk apa:** mengubah daftar, menyaring, atau menggabungkan tanpa menulis `foreach` panjang.

```php
<?php

$angka = [1, 2, 3];

$ganda = array_map(fn (int $n): int => $n * 2, $angka);
// [2, 4, 6]

$genap = array_filter($angka, fn (int $n): bool => $n % 2 === 0);
// [2] — kunci asli bisa tidak berurutan

$gabung = array_merge(['a' => 1], ['b' => 2]);
```

Di Laravel, hasil Eloquent sering sudah berupa `Collection`. Collection punya `map`, `filter`, `merge` yang lebih nyaman dan tidak mengacaukan kunci seperti `array_filter`.

```php
collect([1, 2, 3])->map(fn ($n) => $n * 2);
```

**Biasanya digabungkan dengan:** helper `collect()` dan API Resource yang membentuk array respons.

---

## foreach nilai

**Untuk apa:** mengunjungi setiap anggota array atau Collection. Ini loop yang paling sering dipakai di Laravel.

```php
<?php

$produk = [
    ['nama' => 'Buku', 'harga' => 45000],
    ['nama' => 'Pensil', 'harga' => 5000],
];

foreach ($produk as $item) {
    echo $item['nama'];
}
```

`$item` adalah **salinan** nilai pada setiap putaran (kecuali memakai referensi). Mengubah `$item` di dalam loop tidak mengubah array asli.

Di Blade:

```blade
@foreach ($produk as $item)
    <li>{{ $item['nama'] }}</li>
@endforeach
```

Untuk Collection/model: `$item->nama`.

**Biasanya digabungkan dengan:** `@forelse` jika perlu cabang "kosong", dan `paginate()` di controller.

---

## foreach kunci dan nilai

**Untuk apa:** ketika kamu butuh nama kunci, misalnya menampilkan field error atau header tabel dinamis.

```php
<?php

$produk = ['nama' => 'Buku', 'harga' => 45000];

foreach ($produk as $kunci => $nilai) {
    echo $kunci . ': ' . $nilai;
}
```

Di Blade, `$loop` tersedia di dalam `@foreach`: `$loop->index`, `$loop->first`, `$loop->last`, `$loop->iteration`.

**Biasanya digabungkan dengan:** menampilkan `$errors` dan membangun opsi `<select>` dari array asosiatif.

---

## foreach referensi

**Untuk apa:** mengubah array asli dari dalam loop. Jarang diperlukan di Laravel; rawan bug jika lupa `unset`.

```php
<?php

$angka = [1, 2, 3];

foreach ($angka as &$n) {
    $n = $n * 2;
}
unset($n); // wajib agar $n tidak nyangkut
```

Tanpa `unset($n)`, variabel `$n` masih merujuk elemen terakhir. Assignment berikutnya ke `$n` bisa mengubah array tanpa kamu sadari.

Lebih aman: bangun array baru dengan `array_map` atau `collect()->map()`.

**Biasanya digabungkan dengan:** hampir tidak ada di controller Laravel modern. Utamakan `map`.

---

## for dan while

**Untuk apa:** loop dengan penghitung, atau loop sampai syarat berhenti. Di Laravel, `foreach` lebih sering tepat untuk daftar data.

```php
<?php

for ($i = 0; $i < 3; $i++) {
    echo $i;
}

$n = 3;
while ($n > 0) {
    $n--;
}
```

Hati-hati `while` yang tidak pernah mengubah syarat — loop tak berhingga.

**Biasanya digabungkan dengan:** seeder yang membuat N baris, meskipun factory `count(20)` lebih lazim.

---

## Fungsi

**Untuk apa:** mengelompokkan langkah yang dipakai berulang, misalnya format rupiah atau merapikan slug.

```php
<?php

function formatRupiah(int $nilai): string
{
    return 'Rp' . number_format($nilai, 0, ',', '.');
}

formatRupiah(45000); // Rp45.000
```

Nama fungsi tidak memakai `$`. Memanggil fungsi yang belum ada memicu error. Di Laravel, fungsi global seperti ini sering dipindah ke helper, class service, atau method model agar tidak bertabrakan nama.

Parameter diisi sesuai urutan, kecuali memakai named argument.

**Biasanya digabungkan dengan:** type hint parameter + return type, lalu dipanggil dari Blade atau API Resource.

---

## Parameter default dan named argument

**Untuk apa:** membuat argumen opsional, dan memanggil fungsi tanpa menghafal urutan.

```php
<?php

function diskon(int $harga, int $persen = 10): int
{
    return (int) round($harga * (100 - $persen) / 100);
}

diskon(100000);             // persen 10
diskon(harga: 100000, persen: 25);
```

Parameter yang punya default harus di belakang parameter wajib (aturan lama PHP). Named argument membantu saat banyak opsi.

**Biasanya digabungkan dengan:** pemanggilan query builder yang banyak argumen, meskipun Eloquent lebih sering method chaining.

---

## Return type dan void

**Untuk apa:** menjanjikan tipe hasil fungsi. Jika isi tidak sesuai, PHP melempar `TypeError`.

```php
<?php

function total(int $a, int $b): int
{
    return $a + $b;
}

function simpanLog(string $pesan): void
{
    // tidak mengembalikan nilai
}
```

`void` berarti tidak boleh `return $apaPun`. `return;` kosong diperbolehkan.

Di controller Laravel, return type sering `Illuminate\View\View`, `Illuminate\Http\RedirectResponse`, atau `Illuminate\Http\JsonResponse`. Boleh juga union: `View|RedirectResponse`.

**Biasanya digabungkan dengan:** type hint parameter agar kontrak fungsi lengkap.

---

## Arrow function

**Untuk apa:** fungsi pendek satu ekspresi, sering di `map`/`filter`.

```php
<?php

$ganda = fn (int $n): int => $n * 2;

array_map($ganda, [1, 2, 3]);
```

Arrow function **otomatis** memakai variabel luar (`use` implisit). Closure biasa perlu `use ($x)`:

```php
<?php

$pajak = 0.11;

$plusPajak = function (int $harga) use ($pajak): float {
    return $harga * (1 + $pajak);
};
```

**Biasanya digabungkan dengan:** `collect()->map()`, `array_map`, dan callback validasi.

---

## Variadic

**Untuk apa:** menerima jumlah argumen yang tidak tetap.

```php
<?php

function gabungNama(string ...$bagian): string
{
    return implode(' ', $bagian);
}

gabungNama('Haikal', 'Muzhoffar');
```

Di Laravel kamu lebih sering melihat `...$middleware` pada grup route atau `array` biasa.

**Biasanya digabungkan dengan:** helper yang menerima banyak kunci, misalnya pola mirip `only('nama', 'harga')`.

---

## Class

**Untuk apa:** menggabungkan data dan perilaku. Model, controller, Form Request, Policy — semuanya class.

```php
<?php

class Produk
{
    public string $nama;
    public int $harga;

    public function __construct(string $nama, int $harga)
    {
        $this->nama = $nama;
        $this->harga = $harga;
    }

    public function label(): string
    {
        return $this->nama . ' — ' . $this->harga;
    }
}

$buku = new Produk('Buku CSS', 40000);
$buku->label();
```

`$this` merujuk objek yang sedang dipakai. `new` membuat instance. Tanpa `new`, kamu hanya punya nama class.

Di Laravel, `Product::create([...])` adalah method **statis** pada class model (sebenarnya diteruskan ke query builder). Itu berbeda dengan `$product->delete()` pada instance.

**Biasanya digabungkan dengan:** `namespace App\Models` dan type hint `Product $product` di controller (route model binding).

---

## Constructor property promotion

**Untuk apa:** menulis property + assignment constructor dalam satu baris. Pola PHP 8 yang dipakai luas di Laravel 11/13.

```php
<?php

class Produk
{
    public function __construct(
        public string $nama,
        public int $harga,
    ) {
    }
}

$buku = new Produk(nama: 'Buku', harga: 40000);
$buku->nama;
```

Ini setara versi panjang yang menulis `public string $nama` lalu `$this->nama = $nama`.

**Biasanya digabungkan dengan:** Action class, DTO sederhana, dan job Laravel.

---

## Visibility

**Untuk apa:** membatasi siapa yang boleh membaca/menulis property atau memanggil method.

| Kata | Artinya |
| --- | --- |
| `public` | Bisa diakses dari mana saja |
| `protected` | Class ini dan turunannya |
| `private` | Hanya class ini |

```php
<?php

class Akun
{
    public function __construct(
        private string $password,
        public string $email,
    ) {
    }
}
```

`$fillable` dan `$casts` pada model Eloquent biasanya `protected` — dipakai Eloquent di dalam class, bukan diubah sembarangan dari luar.

**Biasanya digabungkan dengan:** model Eloquent (`$fillable`, `$hidden`, `$casts`) dan policy.

---

## Inheritance

**Untuk apa:** class anak mewarisi perilaku class induk. Model Laravel `extends Model`. Form Request `extends FormRequest`.

```php
<?php

class ModelDasar
{
    public function toArray(): array
    {
        return [];
    }
}

class Product extends ModelDasar
{
}
```

`parent::` memanggil method induk. Jangan membuat rantai warisan dalam hanya demi "rapi". Laravel lebih sering memakai trait dan komposisi.

**Biasanya digabungkan dengan:** `use Illuminate\Database\Eloquent\Model;` lalu `class Product extends Model`.

---

## Interface

**Untuk apa:** kontrak method tanpa isi. Class yang `implements` wajib menulis method tersebut.

```php
<?php

interface BisaDiformat
{
    public function formatRupiah(): string;
}

class Product implements BisaDiformat
{
    public function __construct(public int $harga)
    {
    }

    public function formatRupiah(): string
    {
        return 'Rp' . number_format($this->harga, 0, ',', '.');
    }
}
```

Di Laravel kamu akan melihat interface container, mailer, dan contract. Untuk tugas kuliah, cukup paham: interface = janji method.

**Biasanya digabungkan dengan:** type hint parameter `function cetak(BisaDiformat $item)`.

---

## Trait

**Untuk apa:** menyalin method ke banyak class tanpa pewarisan. Laravel memakai trait di model (`HasFactory`, `SoftDeletes`, `Notifiable`).

```php
<?php

trait HasLabel
{
    public function labelNama(): string
    {
        return strtoupper($this->nama);
    }
}

class Product
{
    use HasLabel;

    public function __construct(public string $nama)
    {
    }
}
```

`use HasLabel` di dalam class (bukan di atas file) memasang trait. `use App\Models\Product;` di atas file adalah import namespace — kata `use` yang sama, makna berbeda.

**Biasanya digabungkan dengan:** `use HasFactory;` pada model Eloquent.

---

## Namespace

**Untuk apa:** menaruh class di "alamat" agar nama `Product` di aplikasi tidak tabrakan dengan `Product` dari paket lain. Laravel mengikuti PSR-4: namespace `App\` = folder `app/`.

```php
<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Product extends Model
{
    protected $fillable = ['nama', 'harga'];
}
```

File ini harus berada di `app/Models/Product.php`. Nama class dan nama file sama. Salah folder atau salah namespace membuat error "Class not found" sampai `composer dump-autoload`.

Namespace ditulis di baris setelah `<?php`, sebelum `use` dan `class`.

Contoh lain:

| File | Namespace |
| --- | --- |
| `app/Http/Controllers/ProductController.php` | `App\Http\Controllers` |
| `app/Http/Requests/StoreProductRequest.php` | `App\Http\Requests` |
| `app/Policies/ProductPolicy.php` | `App\Policies` |

**Biasanya digabungkan dengan:** `use App\Models\Product;` di controller.

---

## use untuk import

**Untuk apa:** menyebut class luar tanpa menulis path lengkap setiap kali.

```php
<?php

namespace App\Http\Controllers;

use App\Models\Product;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route; // contoh; Route biasanya di file route
```

Tanpa `use`, kamu harus menulis `\App\Models\Product`. Backslash di depan berarti namespace global.

Import yang sama dua kali, atau import yang tidak dipakai, biasanya hanya peringatan linter — tetapi import yang **salah class** (misalnya `Request` dari namespace lain) merusak aplikasi secara senyap.

Di `routes/web.php` tidak ada namespace file (bukan class). Tetap boleh `use App\Http\Controllers\ProductController;`.

**Biasanya digabungkan dengan:** type hint `Request $request` dan `Product $product`.

---

## Type hint skalar

**Untuk apa:** memaksa parameter bertipe `string`, `int`, `float`, `bool`. Salah tipe → `TypeError`.

```php
<?php

function setStok(int $jumlah): void
{
}

setStok(10);      // oke
// setStok('10'); // tergantung coerce; dengan strict_types akan gagal
```

Tanpa `declare(strict_types=1)`, PHP sering men-cast `"10"` menjadi `10`. Dengan strict types, string ditolak.

Laravel sendiri tidak memaksa semua file memakai strict types, tetapi type hint tetap berguna.

**Biasanya digabungkan dengan:** validasi form dulu (`integer`) supaya string dari HTML sudah aman sebelum dihitung.

---

## Type hint nullable dan union

**Untuk apa:** mengizinkan `null` atau beberapa tipe.

```php
<?php

function judul(?string $teks): string
{
    return $teks ?? 'Tanpa judul';
}

function id(int|string $nilai): string
{
    return (string) $nilai;
}
```

`?string` sama dengan `string|null`. Relasi Eloquent yang boleh kosong sering bertipe `?Category`.

`mixed` berarti "tipe apa saja" — hindari jika bisa lebih spesifik.

**Biasanya digabungkan dengan:** return type controller `View|RedirectResponse` dan relasi `belongsTo` yang nullable.

---

## Type hint class dan array

**Untuk apa:** menjanjikan object class tertentu, atau array (tanpa merinci isi array di tipe dasar PHP).

```php
<?php

use App\Models\Product;

function terbitkan(Product $product): void
{
    $product->update(['aktif' => true]);
}

function ambilNama(array $produk): string
{
    return $produk['nama'] ?? '';
}
```

`Product $product` di method controller + parameter route `{product}` mengaktifkan **route model binding**: Laravel mencari baris tabel, atau 404.

PHP tidak menuliskan `array<string, int>` sebagai type hint runtime. Dokumentasi bisa memakai PHPDoc:

```php
/** @param array<string, int> $harga */
function total(array $harga): int
{
    return array_sum($harga);
}
```

**Biasanya digabungkan dengan:** Form Request `StoreProductRequest $request` dan policy `Product $product`.

---

## strict_types

**Untuk apa:** menolak konversi tipe implisit di **file itu saja**.

```php
<?php

declare(strict_types=1);

function lebar(int $n): int
{
    return $n;
}

// lebar('10'); // TypeError
```

Harus tepat di baris setelah `<?php`. Tidak menular ke file lain.

Di tugas kuliah, ini opsional. Yang lebih penting: validasi input dan type hint yang jujur.

**Biasanya digabungkan dengan:** file helper murni atau DTO, bukan syarat wajib setiap controller.

---

## Exception

**Untuk apa:** menghentikan alur ketika sesuatu gagal, lalu ditangkap atau ditampilkan sebagai halaman error.

```php
<?php

try {
    if ($stok < 1) {
        throw new RuntimeException('Stok habis');
    }
} catch (RuntimeException $e) {
    echo $e->getMessage();
}
```

Di Laravel kamu jarang menulis `try/catch` untuk "data tidak ketemu". Pakai `findOrFail()` (404) atau `abort(403)`. Exception yang tidak ditangkap menjadi halaman error (debug) atau halaman 500 (produksi).

**Biasanya digabungkan dengan:** `findOrFail`, `firstOrFail`, `abort`, dan `report($e)` / `logger()`.

---

## json_encode dan json_decode

**Untuk apa:** mengubah array/object menjadi teks JSON, atau sebaliknya. API Laravel biasanya memakai `response()->json()` yang sudah memanggil encoder.

```php
<?php

$teks = json_encode(['nama' => 'Buku', 'harga' => 40000], JSON_UNESCAPED_UNICODE);
$data = json_decode($teks, true); // true = array asosiatif
```

Tanpa `true`, `json_decode` menghasilkan `object` (`stdClass`): `$data->nama`. Dengan `true`: `$data['nama']`.

JSON rusak menghasilkan `null`. Cek `json_last_error()`.

**Biasanya digabungkan dengan:** `response()->json()`, API Resource, dan kolom `$casts` `'array'` di model.

---

## htmlspecialchars

**Untuk apa:** mencegah teks pengguna merusak HTML (XSS). Blade `{{ $nama }}` sudah melakukan escape. `{!! $html !!}` tidak — hanya untuk HTML yang kamu percayai.

```php
<?php

echo htmlspecialchars($nama, ENT_QUOTES, 'UTF-8');
```

Jangan `echo $_GET['q']` ke halaman.

**Biasanya digabungkan dengan:** `{{ }}` Blade dan `$request->input()` yang kemudian ditampilkan ulang lewat `old()`.

---

## Superglobal

**Untuk apa:** data dari luar skrip pada PHP mentah. Di Laravel, **jangan** mengandalkan `$_POST` / `$_GET` di controller. Pakai `Request`.

```php
<?php

$_GET['q'] ?? '';
$_POST['nama'] ?? '';
$_SERVER['REQUEST_METHOD'];
$_FILES['foto'] ?? null;
```

Alasan memakai `Request`:

- seragam antara web dan API
- mudah ditest
- terhubung validasi, file, dan session
- tidak mengabaikan JSON body

```php
$request->query('q');
$request->input('nama');
$request->file('foto');
$request->method();
```

**Biasanya digabungkan dengan:** validasi dan Form Request.

---

## Object vs array

**Untuk apa:** menghindari error "Trying to access array offset on object" atau sebaliknya.

```php
<?php

// object
$produk->nama;

// array
$produk['nama'];
```

| Sumber | Akses |
| --- | --- |
| Model Eloquent | `$product->nama` |
| `$product->toArray()` | `$row['nama']` |
| `$request->all()` | array |
| `json_decode($teks)` | object |
| `json_decode($teks, true)` | array |
| Collection | object Collection; item di dalamnya bisa model |

Kalau bingung, `dd($produk)` di controller latihan (jangan di produksi).

**Biasanya digabungkan dengan:** `@foreach` Blade yang menyesuaikan notasi akses.

---

## Kesalahan PHP yang sering ketemu di Laravel

### Undefined variable

View memakai `$products` tetapi controller tidak mengirimnya. Kirim lewat `compact('products')` atau `view('...', ['products' => $products])`. Nama harus sama.

### Undefined array key

Kunci form tidak dikirim. Pakai `??`, `isset`, atau validasi `required` / `nullable`.

### Class not found

Salah namespace, salah `use`, atau file belum di-autoload. Cek folder PSR-4 dan `composer dump-autoload`.

### TypeError

Type hint `int` menerima `null` atau string. Validasi dulu, atau pakai `?int`.

### Attempt to read property on null

`$product->kategori->nama` padahal `kategori` null. Pakai `?->`, `optional()`, atau pastikan relasi ada.

### Array to string conversion

`echo` pada array. Loop dulu, atau `json_encode` untuk debug.

### Cannot use object of type ... as array

Kamu menulis `$product['nama']` pada model. Ubah ke `$product->nama`.

---

## Mini latihan bekal

1. Tulis fungsi `formatRupiah(int $nilai): string`.
2. Buat array dua produk (nama + harga), loop dengan `foreach`.
3. Buat class `Produk` dengan constructor promotion `nama` dan `harga`.
4. Taruh class di namespace `App\Models` secara mental: file di `app/Models`.
5. Tambah type hint `?string` pada parameter yang boleh kosong.

Kalau keempat poin itu terasa wajar, lanjut ke [instalasi dan struktur folder](01-install-struktur-folder.md).
