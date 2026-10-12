# 04 — Validasi: rule satu per satu

[← Controller](03-controller-request-response.md) · [Daftar](README.md) · [Berikutnya: Blade →](05-blade-direktif-lengkap.md)

**Untuk apa validasi:** menolak input yang tidak masuk akal **sebelum** menulis database. Validasi bukan `$fillable`. `$fillable` hanya membatasi kolom mass assignment. Validasi memeriksa isi.

Dua cara menulis aturan:

```php
'nama' => 'required|string|max:100',
'nama' => ['required', 'string', 'max:100'],
```

Utamakan **array**. Lebih mudah menambah `Rule::unique(...)` dan tidak bentrok dengan `|` di dalam regex.

Rujukan: [validation](https://laravel.com/docs/13.x/validation).

## Daftar isi

- [Cara menjalankan validasi](#cara-menjalankan-validasi)
- [required](#required)
- [string](#string)
- [integer](#integer)
- [numeric](#numeric)
- [min](#min)
- [max](#max)
- [email](#email)
- [unique](#unique)
- [exists](#exists)
- [confirmed](#confirmed)
- [nullable](#nullable)
- [array](#array)
- [date](#date)
- [file](#file)
- [image](#image)
- [in](#in)
- [regex](#regex)
- [Rule tambahan yang sering menempel](#rule-tambahan-yang-sering-menempel)
- [Pesan dan atribut kustom](#pesan-dan-atribut-kustom)
- [Form Request messages](#form-request-messages)
- [after validation / withValidator](#after-validation--withvalidator)
- [Kombinasi resep per field](#kombinasi-resep-per-field)
- [Validasi API 422](#validasi-api-422)
- [Kesalahan validasi](#kesalahan-validasi)

---

## Cara menjalankan validasi

**Untuk apa:** memilih tempat aturan hidup.

Di controller:

```php
$data = $request->validate([
    'nama' => ['required', 'string', 'max:100'],
]);
```

Form Request: `$request->validated()` setelah type hint.

Manual:

```php
use Illuminate\Support\Facades\Validator;

$validator = Validator::make($request->all(), [
    'nama' => ['required'],
]);

if ($validator->fails()) {
    return back()->withErrors($validator)->withInput();
}
```

Request web yang gagal: redirect back + error bag. JSON: 422 `{ message, errors }`.

**Biasanya digabungkan dengan:** `@error` di Blade dan `old()`.

---

## required

**Untuk apa:** field **wajib ada dan tidak kosong**. String kosong `''`, `null`, dan array kosong gagal. File kosong gagal.

```php
'nama' => ['required'],
```

Contoh lolos: `"Buku"`, `0` (angka nol **lolos** required — nol bukan kosong).  
Contoh gagal: tidak dikirim, `""`, `null`.

Checkbox yang tidak dicentang tidak terkirim → gagal jika `required`. Untuk checkbox opsional, jangan `required`; pakai `boolean` / `nullable`.

`required` tidak menjamin tipe. Tambah `string` / `integer`.

**Biasanya digabungkan dengan:** `string`, `integer`, `email`, `file`, dan hampir semua field wajib.

Tidak digabung dengan `nullable` pada field yang sama kecuali ada kondisi (`required_if`). `nullable` + `required` saling meniadakan makna.

---

## string

**Untuk apa:** memastikan nilai adalah **teks**. Menolak array, file, atau object. Berguna karena form HTML selalu mengirim string — rule ini menolak penyusup yang mengirim array ke field nama (`nama[]`) untuk membingungkan query.

```php
'nama' => ['required', 'string'],
```

Lolos: `"Haikal"`, `""` (jika tidak `required`).  
Gagal: `["Haikal"]`, `123` sebagai integer murni di JSON (tergantung cara parse; body JSON `{"nama": 123}` bisa gagal `string`).

`string` tidak memotong panjang. Tambah `max` / `min`.

**Biasanya digabungkan dengan:** `required` atau `nullable`, plus `max:255` (cocok kolom `string` default migration), `min:3`, kadang `alpha`, `alpha_dash`, `lowercase`.

---

## integer

**Untuk apa:** bilangan **bulat**. Cocok id, stok, harga rupiah tanpa sen, jumlah item.

```php
'harga' => ['required', 'integer'],
'stok' => ['required', 'integer', 'min:0'],
```

Lolos: `10`, `"10"` (string angka dari form).  
Gagal: `"10.5"`, `"10 rupiah"`, `""`, array.

Beda dengan `numeric`: `numeric` menerima pecahan.

Beda dengan `int` PHP: ini rule validasi input, bukan type hint method.

Untuk id yang merujuk tabel lain, tambah `exists:tabel,id` — `integer` saja tidak memastikan baris ada.

**Biasanya digabungkan dengan:** `required`/`nullable`, `min`, `max`, `exists`, kadang `gt:0`.

---

## numeric

**Untuk apa:** angka, **boleh pecahan**. Berat, rating, persentase, harga dengan desimal.

```php
'berat' => ['required', 'numeric', 'min:0'],
'rating' => ['required', 'numeric', 'between:1,5'],
```

Lolos: `12`, `12.5`, `"12.5"`.  
Gagal: `"12kg"`, `null` (kecuali `nullable`).

Kalau field harus bulat, jangan `numeric` sendirian — pakai `integer`.

**Biasanya digabungkan dengan:** `min`, `max`, `between`, `decimal:0,2` (jika versi mendukung dan kamu butuh jumlah desimal).

---

## min

**Untuk apa:** batas bawah. Makna bergantung tipe nilai setelah rule tipe:

| Tipe field | `min:3` berarti |
| --- | --- |
| string | panjang minimal 3 karakter |
| integer / numeric | nilai numerik ≥ 3 |
| array | minimal 3 anggota |
| file | ukuran minimal 3 **kilobyte** |

```php
'nama' => ['required', 'string', 'min:3'],
'harga' => ['required', 'integer', 'min:0'],
'tag' => ['required', 'array', 'min:1'],
'berkas' => ['required', 'file', 'min:10'],
```

Tanpa `string`/`integer`/`array`/`file`, `min` bisa menafsirkan salah. **Selalu tulis rule tipe di dekat `min`/`max`.**

`min:0` pada harga mengizinkan gratis. `min:1` menolak 0.

**Biasanya digabungkan dengan:** `string` + `max`, atau `integer` + `max`, atau `array`.

---

## max

**Untuk apa:** batas atas. Makna sama seperti `min` menurut tipe.

```php
'nama' => ['required', 'string', 'max:100'],
'harga' => ['required', 'integer', 'max:1000000000'],
'foto' => ['nullable', 'image', 'max:2048'], // 2048 KB ≈ 2 MB
```

`max:100` pada string mencegah teks lebih panjang dari kolom `string('nama', 100)` — mengurangi error SQL "too long".

`max` pada file dalam **kilobyte**, bukan pixel.

**Biasanya digabungkan dengan:** `min` (rentang), `string`/`integer`/`image`, dan panjang kolom migration.

---

## email

**Untuk apa:** memeriksa bentuk alamat surel. Tidak menjamin kotak surat benar-benar ada.

```php
'email' => ['required', 'email'],
'email' => ['required', 'email:rfc,dns'], // dns mengecek domain; butuh jaringan
```

Lolos: `a@b.co`.  
Gagal: `haikal`, `a@b`, sering juga spasi.

Untuk login/register: gabung `unique:users,email` saat **buat**, dan `unique:...` ignore id saat **ubah**.

`email` sudah menyiratkan bentuk string. Tetap boleh menambah `max:255`.

**Biasanya digabungkan dengan:** `required`/`nullable`, `max:255`, `unique:users,email`, `confirmed` (jika ada `email_confirmation` — jarang; yang umum `password` + `confirmed`).

---

## unique

**Untuk apa:** nilai belum dipakai di kolom tabel. Email, slug, SKU, username.

```php
'email' => ['required', 'email', 'unique:users,email'],
'slug' => ['required', 'string', 'max:100', 'unique:articles,slug'],
```

Format: `unique:nama_tabel,nama_kolom`.

Jika nama field = nama kolom, kolom bisa diisi implisit, tetapi **lebih jelas ditulis**.

Saat **update**, abaikan baris sendiri:

```php
use Illuminate\Validation\Rule;

'email' => [
    'required',
    'email',
    Rule::unique('users', 'email')->ignore($user->id),
],
```

Tanpa `ignore`, pengguna tidak bisa menyimpan profil tanpa mengubah email.

`unique` bukan pengganti index unik di database. Race condition: dua request bersamaan bisa lolos validasi. Tetap pasang `$table->unique('email')` di migration.

**Biasanya digabungkan dengan:** `required`/`nullable`, `email` atau `string`, index unique di schema, dan `Rule::unique()->ignore()`.

---

## exists

**Untuk apa:** nilai **harus merujuk baris yang ada**. Foreign key dari form: `category_id`, `user_id`, `product_id`.

```php
'category_id' => ['required', 'integer', 'exists:categories,id'],
```

Lolos: id 5 ada di `categories`.  
Gagal: 999 tidak ada, atau `"abc"` (gagal integer dulu).

Opsi lebih ketat:

```php
use Illuminate\Validation\Rule;

'category_id' => [
    'required',
    Rule::exists('categories', 'id')->where(fn ($q) => $q->where('aktif', true)),
],
```

`exists` tidak memasang relasi Eloquent. Itu hanya cek SQL. Relasi tetap ditulis di model.

**Biasanya digabungkan dengan:** `integer`, `nullable` (jika FK boleh kosong), `belongsTo`, dan kolom `foreignId` di migration.

---

## confirmed

**Untuk apa:** field harus sama dengan `{nama}_confirmation`. Password, kadang email baru.

```php
'password' => ['required', 'string', 'min:8', 'confirmed'],
```

Form harus punya:

```blade
<input type="password" name="password">
<input type="password" name="password_confirmation">
```

`password_confirmation` **tidak** perlu divalidasi terpisah. Rule `confirmed` yang membandingkan.

Jika tidak sama: error pada `password`, bukan pada confirmation.

Tidak meng-hash. Hash di model `User` dengan `$casts` `'password' => 'hashed'` atau `Hash::make()`.

**Biasanya digabungkan dengan:** `required`, `min:8`, kadang `Password::defaults()`, dan field `password_confirmation` di form saja (tidak disimpan ke DB).

---

## nullable

**Untuk apa:** mengizinkan kosong / tidak dikirim. Rule lain **dilewati** jika nilai kosong.

```php
'catatan' => ['nullable', 'string', 'max:500'],
'foto' => ['nullable', 'image', 'max:2048'],
'category_id' => ['nullable', 'integer', 'exists:categories,id'],
```

Tanpa `nullable`, field opsional yang dikirim sebagai `null` (JSON) atau `""` bisa gagal `string`/`integer`/`exists`.

Urutan: tulis `nullable` di depan agar mudah dibaca.

Jangan `required` + `nullable` pada field yang sama kecuali kamu memakai `required_if` / `required_without`.

**Biasanya digabungkan dengan:** semua rule tipe untuk field opsional, dan kolom DB yang `nullable()`.

---

## array

**Untuk apa:** nilai harus array. Form daftar, tag, `items[]`, JSON array.

```php
'tag' => ['required', 'array', 'min:1', 'max:10'],
'tag.*' => ['string', 'max:30'],
```

Form:

```blade
<input name="tag[]" value="alat">
<input name="tag[]" value="tulis">
```

Bersarang:

```php
'items' => ['required', 'array', 'min:1'],
'items.*.produk_id' => ['required', 'integer', 'exists:products,id'],
'items.*.qty' => ['required', 'integer', 'min:1'],
```

Tanpa `array`, `tag.*` tidak punya induk yang jelas. Tanpa `tag.*`, isi array tidak diperiksa.

**Biasanya digabungkan dengan:** `min`/`max` jumlah anggota, `*.`, dan `@foreach` untuk mengulang input.

---

## date

**Untuk apa:** tanggal/waktu yang bisa di-parse. Deadline, tanggal lahir, jadwal.

```php
'tanggal_lahir' => ['required', 'date'],
'deadline' => ['required', 'date', 'after:today'],
'mulai' => ['required', 'date'],
'selesai' => ['required', 'date', 'after_or_equal:mulai'],
```

Lolos: `2026-09-22`, banyak format yang `strtotime` pahami.  
Lebih ketat:

```php
'tanggal' => ['required', 'date_format:Y-m-d'],
'jam' => ['required', 'date_format:H:i'],
```

`date` tidak otomatis mengubah kolom jadi Carbon sampai kamu `$casts` `'deadline' => 'datetime'` di model.

**Biasanya digabungkan dengan:** `after`, `before`, `after_or_equal`, `date_format`, `nullable`, dan `$casts`.

---

## file

**Untuk apa:** memastikan input adalah **unggahan sah**, bukan string path. PDF, dokumen, zip — yang bukan wajib gambar.

```php
'berkas' => ['required', 'file', 'mimes:pdf,doc,docx', 'max:5120'],
```

`max:5120` = 5 MB (kilobyte).

Form wajib:

```blade
<form method="POST" action="..." enctype="multipart/form-data">
    @csrf
    <input type="file" name="berkas">
</form>
```

Tanpa `enctype`, file tidak sampai.

`file` tidak menyimpan. Setelah lolos: `$request->file('berkas')->store('dokumen', 'public')`.

**Biasanya digabungkan dengan:** `mimes` / `mimetypes`, `max`, `nullable`, dan `Storage`.

---

## image

**Untuk apa:** unggahan harus gambar (jpeg, png, bmp, gif, svg, webp — sesuai aturan versi). Lebih spesifik daripada `file`.

```php
'foto' => ['required', 'image', 'max:2048'],
'foto' => ['nullable', 'image', 'mimes:jpg,jpeg,png,webp', 'max:2048'],
```

Dimensi:

```php
'foto' => ['required', 'image', 'dimensions:min_width=200,min_height=200'],
```

`image` sudah termasuk sifat file. Tetap butuh `enctype`.

SVG bisa berisi skrip. Untuk unggahan publik dari orang tak dikenal, pertimbangkan hanya `jpg,png,webp`.

**Biasanya digabungkan dengan:** `nullable` (saat edit tanpa ganti foto), `max`, `mimes`, `store('...', 'public')`, `storage:link`.

---

## in

**Untuk apa:** nilai harus salah satu daftar yang kamu izinkan. Status, peran, opsi `<select>` tetap.

```php
'status' => ['required', 'in:draft,terbit,arsip'],
'peran' => ['required', Rule::in(['admin', 'editor', 'member'])],
```

Lolos: `draft`.  
Gagal: `Draft` (huruf berbeda), `hapus_semua`, nilai siluman dari request palsu.

`<select>` di HTML **bisa dipalsukan**. `in` melindungi server.

Untuk daftar dari database, `exists` lebih tepat daripada menyalin semua id ke `in`.

**Biasanya digabungkan dengan:** `required`/`nullable`, `string`, dan `<select>` yang opsi-nya sama.

---

## regex

**Untuk apa:** pola karakter yang tidak tertutup rule lain. Slug, kode, nomor telepon sederhana, SKU.

```php
'slug' => ['required', 'string', 'max:100', 'regex:/^[a-z0-9]+(?:-[a-z0-9]+)*$/'],
'kode' => ['required', 'regex:/^PRD-[0-9]{4}$/'],
```

Wajib memakai **array rules**, bukan string `'regex:/a|b/'` — tanda `|` memotong rule.

Pola salah = exception. Uji dulu di lingkungan latihan.

`regex` tidak menggantikan `string`. Tetap tulis `string` + `max`.

Jangan memakai regex untuk email — pakai `email`. Jangan untuk HTML lengkap.

**Biasanya digabungkan dengan:** `string`, `max`, kadang `unique`, dan `alpha_dash` jika pola cukup sederhana (`huruf-angka-_-`).

---

## Rule tambahan yang sering menempel

Bukan daftar tugas utama, tetapi sering muncul bersama rule di atas.

### required_if / required_with

**Untuk apa:** wajib hanya dalam kondisi.

```php
'kurir' => ['required_if:metode,pengiriman', 'string'],
'kota' => ['required_with:alamat', 'string'],
```

**Biasanya digabungkan dengan:** `nullable` pada field yang saling bergantung.

### boolean

**Untuk apa:** menerima `true`/`false`/`1`/`0`/`"1"`/`"0"`/`"yes"`/`"no"`/`"on"`/`"off"`.

```php
'aktif' => ['sometimes', 'boolean'],
```

**Biasanya digabungkan dengan:** checkbox dan `$casts` `'aktif' => 'boolean'`.

### same / different

```php
'email_baru' => ['required', 'email', 'different:email_lama'],
```

`confirmed` lebih tepat untuk password.

### between

```php
'rating' => ['required', 'numeric', 'between:1,5'],
```

Setara `min` + `max` dalam satu rule.

### alpha, alpha_num, alpha_dash

```php
'username' => ['required', 'alpha_dash', 'min:3', 'max:30'],
```

`alpha_dash`: huruf, angka, `-`, `_`.

### url / active_url

```php
'situs' => ['nullable', 'url'],
```

`active_url` mengecek DNS — butuh jaringan, bisa lambat/gagal di lokal.

### Password::defaults()

```php
use Illuminate\Validation\Rules\Password;

'password' => ['required', 'confirmed', Password::min(8)->mixedCase()],
```

**Biasanya digabungkan dengan:** `confirmed` dan cast `hashed`.

### current_password

```php
'password_lama' => ['required', 'current_password'],
```

**Biasanya digabungkan dengan:** form ganti password.

### distinct

```php
'items.*.produk_id' => ['required', 'distinct', 'exists:products,id'],
```

Mencegah id produk duplikat dalam satu array.

### present

Field harus **ada** di request, boleh kosong. Berbeda dengan `required`.

---

## Pesan dan atribut kustom

**Untuk apa:** mengganti teks Inggris/default menjadi bahasa yang dipahami pengguna.

```php
$data = $request->validate([
    'nama' => ['required', 'string', 'max:100'],
], [
    'nama.required' => 'Nama produk wajib diisi.',
    'nama.max' => 'Nama paling panjang 100 karakter.',
], [
    'nama' => 'nama produk',
]);
```

Atau di `lang/id/validation.php` (jika locale `id`).

**Biasanya digabungkan dengan:** `@error` yang menampilkan `$message`.

---

## Form Request messages

```php
public function messages(): array
{
    return [
        'harga.integer' => 'Harga harus bilangan bulat rupiah.',
        'foto.image' => 'Berkas harus berupa gambar.',
    ];
}

public function attributes(): array
{
    return [
        'nama' => 'nama produk',
        'category_id' => 'kategori',
    ];
}
```

**Biasanya digabungkan dengan:** `authorize()` dan `rules()`.

---

## after validation / withValidator

**Untuk apa:** cek yang tidak muat di satu rule, misalnya stok vs gudang.

```php
public function withValidator($validator): void
{
    $validator->after(function ($validator) {
        if ($this->integer('harga') === 13) {
            $validator->errors()->add('harga', 'Harga ini tidak diizinkan.');
        }
    });
}
```

Jangan menaruh query berat tanpa perlu. Tetap utamakan rule bawaan.

**Biasanya digabungkan dengan:** Form Request dan pesan field tertentu.

---

## Kombinasi resep per field

### Nama produk

```php
'nama' => ['required', 'string', 'min:3', 'max:100'],
```

**Untuk apa:** teks wajib, panjang sesuai kolom.  
**Biasanya digabungkan dengan:** `unique:products,nama` jika nama tidak boleh kembar.

### Harga rupiah

```php
'harga' => ['required', 'integer', 'min:0', 'max:1000000000'],
```

**Untuk apa:** bulat, tidak negatif.  
**Biasanya digabungkan dengan:** `unsignedInteger` di migration.

### Email daftar akun

```php
'email' => ['required', 'email', 'max:255', 'unique:users,email'],
```

Update: `Rule::unique('users', 'email')->ignore($user->id)`.

### Password daftar

```php
'password' => ['required', 'string', 'min:8', 'confirmed'],
```

### Foreign key opsional

```php
'category_id' => ['nullable', 'integer', 'exists:categories,id'],
```

### Status tetap

```php
'status' => ['required', 'string', 'in:draft,terbit,arsip'],
```

### Slug

```php
'slug' => ['required', 'string', 'max:100', 'regex:/^[a-z0-9-]+$/', 'unique:articles,slug'],
```

### Foto profil

```php
'foto' => ['nullable', 'image', 'mimes:jpg,jpeg,png,webp', 'max:2048'],
```

### Tanggal acara

```php
'mulai' => ['required', 'date', 'after_or_equal:today'],
'selesai' => ['required', 'date', 'after_or_equal:mulai'],
```

### Daftar item pesanan

```php
'items' => ['required', 'array', 'min:1'],
'items.*.product_id' => ['required', 'integer', 'exists:products,id'],
'items.*.qty' => ['required', 'integer', 'min:1', 'max:99'],
```

### Pencarian (query string)

```php
'q' => ['nullable', 'string', 'max:100'],
```

Jangan `required` pada form GET yang boleh kosong.

---

## Validasi API 422

Klien harus mengirim `Accept: application/json` (banyak klien HTTP sudah). Respons gagal:

```json
{
  "message": "The nama field is required.",
  "errors": {
    "nama": ["The nama field is required."]
  }
}
```

Frontend menampilkan `errors.nama[0]`. Jangan mengandalkan redirect.

**Biasanya digabungkan dengan:** API Resource untuk respons sukses, dan pesan kustom agar JSON berbahasa Indonesia.

---

## Kesalahan validasi

| Gejala | Obat |
| --- | --- |
| Kembali ke form tanpa pesan | Lupa `@error` / tidak ada `@if($errors)` |
| `old()` kosong | Validasi tidak jalan lewat `$request->validate()` (exception tidak di-handle kerangka) |
| Unique gagal saat edit | Lupa `ignore($id)` |
| exists gagal padahal data ada | Nama tabel/kolom salah, atau koneksi DB beda |
| regex error saat compile | Pakai array rules; cek delimiter `/.../` |
| File selalu gagal | Lupa `enctype`, atau `max` terlalu kecil (KB) |
| `min:3` pada angka 10 gagal aneh | Lupa `integer` sehingga dihitung sebagai panjang string `"10"` = 2 |
| Array tidak masuk | Nama input bukan `tag[]` |

Ingat: lolos validasi ≠ aman otorisasi. Orang bisa mengirim `user_id` orang lain. Pakai policy.

Lanjut ke [direktif Blade](05-blade-direktif-lengkap.md).
