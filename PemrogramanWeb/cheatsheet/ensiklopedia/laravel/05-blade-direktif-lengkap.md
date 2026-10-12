# 05 — Blade: direktif satu per satu

[← Validasi](04-validasi-rules-lengkap.md) · [Daftar](README.md) · [Berikutnya: Eloquent →](06-eloquent-crud-query.md)

**Untuk apa Blade:** menulis HTML dengan data PHP tanpa mencampur `echo` mentah. File berakhiran `.blade.php` di `resources/views`.

Dua keluaran teks:

- `{{ $nama }}` — aman (escape HTML). **Utamakan ini.**
- `{!! $html !!}` — mentah. Hanya HTML yang kamu percayai.

Rujukan: [Blade](https://laravel.com/docs/13.x/blade).

## Daftar isi

- [{{ }} dan {!! !!}](#--dan-)
- [@if](#if)
- [@elseif dan @else](#elseif-dan-else)
- [@unless](#unless)
- [@foreach](#foreach)
- [$loop](#loop)
- [@forelse](#forelse)
- [@isset](#isset)
- [@empty](#empty)
- [@csrf](#csrf)
- [@method](#method)
- [@error](#error)
- [@extends](#extends)
- [@section](#section)
- [@yield](#yield)
- [@parent](#parent)
- [@include](#include)
- [@auth](#auth)
- [@guest](#guest)
- [@php](#php)
- [@json](#json)
- [@class](#class)
- [@style](#style)
- [@checked @selected @disabled](#checked-selected-disabled)
- [@vite](#vite)
- [Komentar Blade](#komentar-blade)
- [Layout resep lengkap](#layout-resep-lengkap)
- [Kesalahan Blade](#kesalahan-blade)

---

## {{ }} dan {!! !!}

**Untuk apa:** mencetak nilai ke HTML.

```blade
<p>{{ $product->nama }}</p>
<p>{{ old('nama') }}</p>
<title>{{ $judul ?? 'Toko latihan' }}</title>
```

Input `Buku <b>tebal</b>` tampil sebagai teks, bukan tebal.

```blade
{!! $htmlDariCmsYangSudahDisanitasi !!}
```

Jangan `{!! $request->q !!}`. Jangan `{!! old('nama') !!}`.

**Biasanya digabungkan dengan:** `compact` dari controller dan `e()` yang sudah otomatis.

---

## @if

**Untuk apa:** menampilkan potongan HTML hanya jika syarat benar.

```blade
@if (session('success'))
    <p role="status">{{ session('success') }}</p>
@endif
```

```blade
@if ($product->stok > 0)
    <p>Tersedia</p>
@endif
```

Syarat adalah ekspresi PHP. Jangan menulis `@if $product` tanpa kurung.

Tutup dengan `@endif`. Lupa tutup = error compile Blade.

**Biasanya digabungkan dengan:** `session()`, `$product->relasi`, `@else`, dan pesan flash dari `with('success')`.

---

## @elseif dan @else

**Untuk apa:** cabang alternatif.

```blade
@if ($stok <= 0)
    <p>Habis</p>
@elseif ($stok < 5)
    <p>Hampir habis</p>
@else
    <p>Tersedia</p>
@endif
```

**Biasanya digabungkan dengan:** status pesanan dan badge.

---

## @unless

**Untuk apa:** `@if (! ...)` yang lebih mudah dibaca.

```blade
@unless ($product->aktif)
    <p>Produk nonaktif</p>
@endunless
```

**Biasanya digabungkan dengan:** flag boolean model.

---

## @foreach

**Untuk apa:** mengulang HTML untuk setiap item daftar.

```blade
<ul>
    @foreach ($products as $product)
        <li>{{ $product->nama }} — Rp{{ number_format($product->harga, 0, ',', '.') }}</li>
    @endforeach
</ul>
```

`$products` harus iterable: Collection, paginator, array. `null` memicu error. Kirim Collection kosong, bukan `null`.

Akses model: `$product->nama`. Akses array: `$product['nama']`.

Berhenti lebih awal: `@break`. Loncat: `@continue`.

**Biasanya digabungkan dengan:** `get()` / `paginate()` di controller, dan `$loop`.

---

## $loop

**Untuk apa:** info putaran di dalam `@foreach` / `@forelse`.

```blade
@foreach ($products as $product)
    <li class="{{ $loop->first ? 'pertama' : '' }}">
        {{ $loop->iteration }}. {{ $product->nama }}
    </li>
@endforeach
```

| Properti | Arti |
| --- | --- |
| `$loop->index` | 0, 1, 2, ... |
| `$loop->iteration` | 1, 2, 3, ... |
| `$loop->first` | item pertama? |
| `$loop->last` | item terakhir? |
| `$loop->count` | jumlah total |
| `$loop->parent` | loop luar (nested) |

**Biasanya digabungkan dengan:** zebra row, koma di antara tag, nested komentar.

---

## @forelse

**Untuk apa:** loop + cabang jika daftar kosong. Lebih tepat daripada `@foreach` + `@if (count == 0)` terpisah.

```blade
<ul>
    @forelse ($products as $product)
        <li>{{ $product->nama }}</li>
    @empty
        <li>Belum ada produk.</li>
    @endforelse
</ul>
```

Paginator kosong tetap objek: `@forelse` bekerja. Jangan `if ($products)` pada paginator untuk cek isi — pakai `$products->isEmpty()` atau `@forelse`.

**Biasanya digabungkan dengan:** `paginate()`, pesan empty state, dan form tambah di atas daftar.

---

## @isset

**Untuk apa:** menampilkan blok hanya jika variabel ada dan bukan `null`. Setara `isset($x)`.

```blade
@isset($q)
    <p>Pencarian: {{ $q }}</p>
@endisset
```

Tidak mengecek string kosong. `$q = ''` masih "isset". Untuk kosong, pakai `@empty` atau `@if ($q !== '')`.

Controller yang selalu mengirim `'q' => $request->query('q', '')` membuat `@isset` kurang berguna — variabel selalu ada.

**Biasanya digabungkan dengan:** data opsional yang tidak selalu di-`compact`.

---

## @empty

**Untuk apa:** blok jika nilai dianggap kosong (`empty()` PHP): `null`, `''`, `0`, `'0'`, `[]`, `false`.

```blade
@empty($catatan)
    <p>Tidak ada catatan.</p>
@endempty
```

Hati-hati: harga `0` dianggap empty. Jangan `@empty($product->harga)` jika 0 sah.

Untuk Collection: `@empty($products)` true jika tidak ada item.

**Biasanya digabungkan dengan:** field teks opsional, bukan angka yang boleh nol.

---

## @csrf

**Untuk apa:** menyisipkan hidden input token CSRF. Wajib di setiap form web `POST`/`PUT`/`PATCH`/`DELETE`.

```blade
<form method="POST" action="{{ route('products.store') }}">
    @csrf
    <button type="submit">Simpan</button>
</form>
```

Menghasilkan kira-kira:

```html
<input type="hidden" name="_token" value="...">
```

Tanpa ini: **419** Page Expired.

Jangan menaruh `@csrf` di luar `<form>`. Satu form satu `@csrf`.

Fetch ke route web: kirim header `X-XSRF-TOKEN` / `_token`. Route API token biasanya tidak memakai ini.

**Biasanya digabungkan dengan:** `@method`, `route()`, dan session login.

---

## @method

**Untuk apa:** menyiasati HTML yang hanya mudah mengirim GET/POST. Laravel membaca `_method`.

```blade
<form method="POST" action="{{ route('products.update', $product) }}">
    @csrf
    @method('PUT')
    <button type="submit">Ubah</button>
</form>

<form method="POST" action="{{ route('products.destroy', $product) }}">
    @csrf
    @method('DELETE')
    <button type="submit">Hapus</button>
</form>
```

Nilai umum: `PUT`, `PATCH`, `DELETE`. Huruf besar biasa dipakai.

Tanpa `@method('DELETE')`, route `Route::delete` tidak cocok → 405.

**Biasanya digabungkan dengan:** `@csrf` (wajib mendahului/berdekatan) dan `Route::put` / `delete`.

---

## @error

**Untuk apa:** menampilkan pesan validasi untuk **satu field**.

```blade
<label for="nama">Nama</label>
<input id="nama" name="nama" value="{{ old('nama') }}" required>
@error('nama')
    <p role="alert">{{ $message }}</p>
@enderror
```

`$message` hanya hidup di dalam blok `@error`. Nama field harus sama dengan kunci validasi (`nama`, `items.0.qty`, `email`).

Semua error:

```blade
@if ($errors->any())
    <ul>
        @foreach ($errors->all() as $error)
            <li>{{ $error }}</li>
        @endforeach
    </ul>
@endif
```

`$errors` selalu ada di view web (ErrorBag kosong jika tidak ada error).

**Biasanya digabungkan dengan:** `old()`, `$request->validate()`, dan `role="alert"`.

---

## @extends

**Untuk apa:** memakai kerangka layout. File anak mewarisi HTML luar.

`resources/views/layouts/app.blade.php` adalah induk. Halaman:

```blade
@extends('layouts.app')

@section('judul', 'Daftar produk')

@section('konten')
    <h1>Produk</h1>
@endsection
```

Argumen adalah **nama view** dengan titik = folder: `layouts.app` → `layouts/app.blade.php`.

Satu file halaman biasanya satu `@extends` di paling atas. Jangan `@extends` di tengah HTML.

**Biasanya digabungkan dengan:** `@section` di anak dan `@yield` di induk.

---

## @section

**Untuk apa:** mengisi lubang yang didefinisikan layout.

Dua bentuk:

```blade
@section('judul', 'Produk')  {{-- satu baris --}}

@section('konten')
    <p>Isi panjang</p>
@endsection
```

Nama section harus sama dengan `@yield('konten')` atau `@section` di layout.

**Biasanya digabungkan dengan:** `@extends` dan `@yield`.

---

## @yield

**Untuk apa:** titik sisipan di layout. Layout tidak tahu isi halaman.

```blade
{{-- resources/views/layouts/app.blade.php --}}
<!doctype html>
<html lang="id">
<head>
    <meta charset="utf-8">
    <title>@yield('judul', 'Latihan Laravel')</title>
</head>
<body>
    <main>
        @yield('konten')
    </main>
</body>
</html>
```

Argumen kedua = default jika halaman tidak mengirim section.

**Biasanya digabungkan dengan:** `@section` di view anak.

---

## @parent

**Untuk apa:** menambah isi section layout, bukan menimpa seluruhnya.

Layout:

```blade
@section('skrip')
    <script src="/js/app.js"></script>
@endsection
```

Anak:

```blade
@section('skrip')
    @parent
    <script src="/js/produk.js"></script>
@endsection
```

Tanpa `@parent`, skrip layout hilang.

**Biasanya digabungkan dengan:** `@section` skrip/css tambahan.

---

## @include

**Untuk apa:** menyisipkan potongan view berulang: form field, kartu, nav.

```blade
@include('partials.nav')
@include('products._form', ['product' => $product])
```

File `resources/views/partials/nav.blade.php`. Partial menerima variabel halaman + array yang dikirim.

`@includeIf`, `@includeWhen($ok, 'partials.x')` untuk bersyarat.

Beda dengan `@extends`: include menempel di tempat dipanggil; extends membungkus seluruh halaman.

**Biasanya digabungkan dengan:** form create/edit yang berbagi `_form.blade.php`.

---

## @auth

**Untuk apa:** HTML hanya untuk pengguna yang sudah login.

```blade
@auth
    <a href="{{ route('products.create') }}">Tambah produk</a>
    <form method="POST" action="{{ route('logout') }}">
        @csrf
        <button type="submit">Keluar</button>
    </form>
@endauth
```

Guard lain: `@auth('admin')`.

Tidak menggantikan middleware. Tanpa `auth` di route, URL tetap bisa dibuka. `@auth` hanya menyembunyikan tombol.

**Biasanya digabungkan dengan:** `@guest`, middleware `auth`, dan `auth()->user()->name`.

---

## @guest

**Untuk apa:** HTML untuk pengunjung yang belum login.

```blade
@guest
    <a href="{{ route('login') }}">Masuk</a>
@endguest
```

```blade
@guest
    <p>Silakan masuk untuk menulis ulasan.</p>
@else
    <form method="POST" action="{{ route('reviews.store') }}">
        @csrf
        <textarea name="isi" required></textarea>
        <button type="submit">Kirim</button>
    </form>
@endguest
```

`@else` di sini adalah cabang "sudah login".

**Biasanya digabungkan dengan:** tautan login/register dan `@auth`.

---

## @php

**Untuk apa:** menulis PHP mentah di view. **Hindari.** Logika hitung, query, dan otorisasi milik controller/model.

```blade
@php
    $label = $product->stok > 0 ? 'Ada' : 'Habis';
@endphp
<p>{{ $label }}</p>
```

Lebih baik kirim `$label` dari controller, accessor model, atau `@if` langsung.

Diperbolehkan sesaat untuk debug latihan, lalu hapus.

**Biasanya digabungkan dengan:** hampir tidak ada di kode bersih. Pakai accessor:

```php
public function getLabelStokAttribute(): string
{
    return $this->stok > 0 ? 'Ada' : 'Habis';
}
```

---

## @json

**Untuk apa:** mencetak nilai sebagai JSON aman ke dalam HTML/JS.

```blade
<div id="app" data-produk='@json($product)'></div>

<script>
    const produk = @json($product);
</script>
```

Jangan `{{ json_encode($product) }}` di dalam `<script>` tanpa hati-hati — escape Blade berbeda. `@json` ditujukan untuk ini.

Data masih terlihat di sumber halaman. Jangan menaruh password atau token rahasia.

**Biasanya digabungkan dengan:** JavaScript di halaman Blade, bukan API murni (API pakai `response()->json()`).

---

## @class

**Untuk apa:** merakit atribut `class` dari syarat boolean, tanpa merangkai string ruwet.

```blade
<span @class([
    'badge',
    'badge-habis' => $product->stok <= 0,
    'badge-ada' => $product->stok > 0,
])>
    {{ $product->stok > 0 ? 'Ada' : 'Habis' }}
</span>
```

Kunci tanpa syarat (`'badge'`) selalu dipakai. Kunci `=> true/false` dipakai hanya jika benar.

**Biasanya digabungkan dengan:** status, `$loop->first`, dan Tailwind/CSS biasa.

---

## @style

**Untuk apa:** sama seperti `@class`, untuk atribut `style`. Jarang diperlukan jika kamu memakai class.

```blade
<div @style([
    'display: none' => ! $visible,
])></div>
```

**Biasanya digabungkan dengan:** kasus sempit; utamakan class.

---

## @checked @selected @disabled

**Untuk apa:** atribut HTML boolean yang benar saat form diisi ulang.

```blade
<input type="checkbox" name="aktif" value="1"
    @checked(old('aktif', $product->aktif))>

<select name="status">
    <option value="draft" @selected(old('status', $product->status) === 'draft')>Draft</option>
    <option value="terbit" @selected(old('status', $product->status) === 'terbit')>Terbit</option>
</select>

<button type="submit" @disabled($product->stok <= 0)>Pesan</button>
```

**Biasanya digabungkan dengan:** `old()`, form edit, dan rule `in` / `boolean`.

---

## @vite

**Untuk apa:** memuat CSS/JS hasil Vite di layout.

```blade
@vite(['resources/css/app.css', 'resources/js/app.js'])
```

Butuh `npm run dev` atau `npm run build`. Contoh ensiklopedia Blade polos bisa tanpa ini.

**Biasanya digabungkan dengan:** layout `layouts.app` dan Tailwind.

---

## Komentar Blade

**Untuk apa:** catatan yang **tidak** tampil di HTML hasil.

```blade
{{-- Hanya terlihat di file sumber Blade --}}
```

`<!-- komentar HTML -->` tetap terkirim ke browser.

**Biasanya digabungkan dengan:** menandai TODO di view latihan.

---

## Layout resep lengkap

`resources/views/layouts/app.blade.php`:

```blade
<!doctype html>
<html lang="id">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>@yield('judul', 'Latihan')</title>
</head>
<body>
    <header>
        <a href="{{ route('products.index') }}">Toko</a>
        @auth
            <span>{{ auth()->user()->name }}</span>
        @else
            <a href="{{ route('login') }}">Masuk</a>
        @endauth
    </header>
    <main>
        @if (session('success'))
            <p role="status">{{ session('success') }}</p>
        @endif
        @yield('konten')
    </main>
</body>
</html>
```

`resources/views/products/index.blade.php`:

```blade
@extends('layouts.app')

@section('judul', 'Produk')

@section('konten')
    <h1>Daftar produk</h1>

    <form method="POST" action="{{ route('products.store') }}">
        @csrf
        <label for="nama">Nama</label>
        <input id="nama" name="nama" value="{{ old('nama') }}" maxlength="100" required>
        @error('nama') <p role="alert">{{ $message }}</p> @enderror
        <button type="submit">Simpan</button>
    </form>

    <ul>
        @forelse ($products as $product)
            <li @class(['item', 'item-habis' => $product->stok <= 0])>
                {{ $product->nama }}
                <form method="POST" action="{{ route('products.destroy', $product) }}">
                    @csrf
                    @method('DELETE')
                    <button type="submit">Hapus</button>
                </form>
            </li>
        @empty
            <li>Belum ada produk.</li>
        @endforelse
    </ul>

    {{ $products->links() }}
@endsection
```

**Biasanya digabungkan dengan:** controller `index` + `store` + `destroy`.

---

## Kesalahan Blade

| Gejala | Obat |
| --- | --- |
| Undefined variable | Controller tidak mengirim nama yang sama |
| View not found | Nama `products.index` ≠ path file |
| 419 | Lupa `@csrf` |
| 405 pada hapus | Lupa `@method('DELETE')` |
| HTML "rusak" dari input | Pakai `{{ }}` bukan `{!! !!}` |
| `@endsection` error | Section tidak dibuka / salah pasangan |
| `$message` undefined | Dipakai di luar `@error` |
| Class not found di view | Jangan `use` di Blade; kirim data siap pakai |

Lanjut ke [Eloquent CRUD dan query](06-eloquent-crud-query.md).
