# Cheatsheet PHP (bekal Laravel)

[← Daftar panduan](README.md) · [Lanjut Laravel →](laravel.md)

PHP berjalan di **server**. Browser tidak menjalankan file `.php` sendiri; web server (atau `php artisan serve`) yang mengeksekusinya lalu mengirim HTML/JSON.

## Daftar isi

- [Sintaks dasar](#sintaks-dasar)
- [Array dan loop](#array-dan-loop)
- [Fungsi dan class](#fungsi-dan-class)
- [Superglobal](#superglobal)
- [Kesalahan umum](#kesalahan-umum)

## Sintaks dasar

**Untuk apa:** menyimpan dan menampilkan nilai.

```php
<?php
$nama = "Haikal";
$jumlah = 2;
$aktif = true;

echo "Halo, $nama";          // string berinterpolasi
echo htmlspecialchars($nama, ENT_QUOTES, 'UTF-8');
```

Variabel diawali `$`. Titik koma wajib. Jangan `echo` data mentah dari pengguna; pakai `htmlspecialchars` atau `{{ }}` Blade (sudah di-escape).

**Biasanya digabungkan dengan:** Blade dan controller Laravel.

## Array dan loop

**Untuk apa:** daftar produk, hasil query.

```php
$produk = [
    ['nama' => 'Buku', 'harga' => 45000],
    ['nama' => 'Pensil', 'harga' => 5000],
];

foreach ($produk as $item) {
    echo $item['nama'];
}

$angka = [1, 2, 3];
array_map(fn ($n) => $n * 2, $angka);
```

Array asosiatif pakai kunci string. Eloquent mengembalikan object: `$item->nama`, bukan `$item['nama']` (kecuali diubah ke array).

**Biasanya digabungkan dengan:** `@foreach` Blade dan `Collection` Laravel.

## Fungsi dan class

**Untuk apa:** mengelompokkan logika.

```php
function formatRupiah(int $nilai): string
{
    return 'Rp' . number_format($nilai, 0, ',', '.');
}

class Produk
{
    public function __construct(public string $nama, public int $harga)
    {
    }
}

$buku = new Produk('Buku CSS', 40000);
```

`namespace App\Models;` di Laravel menaruh class di folder yang sesuai PSR-4. `use App\Models\Produk;` mengimpornya.

**Biasanya digabungkan dengan:** model, controller, dan helper.

## Superglobal

**Untuk apa:** data dari luar script. Di Laravel hampir selalu lewat `Request`, bukan `$_POST` langsung.

```php
$_GET['q'] ?? '';
$_POST['nama'] ?? '';
$_SERVER['REQUEST_METHOD'];
```

Latihan Laravel: pakai `$request->input('nama')` / `$request->query('q')`. Lebih aman dan seragam.

**Biasanya digabungkan dengan:** form HTML dan validasi.

## Kesalahan umum

- **Blank page:** error PHP; nyalakan debug di `.env` latihan (`APP_DEBUG=true`), jangan di produksi.
- **Undefined variable:** nama `$` salah atau view tidak dikirimi data `compact`.
- **Array vs object:** cek `dd($item)` di Tinker/controller.

Latihan: tulis fungsi `formatRupiah`, lalu pakai hasilnya di Blade Laravel.
