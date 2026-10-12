# 06 · Form dan kontrol lengkap

[← Semantik](05-semantik-sectioning.md) · [Daftar](README.md) · [Atribut global →](07-atribut-global.md)

**Untuk apa file ini:** meminta data dari pengguna. Setiap kontrol punya `name` jika ingin terkirim, dan setiap input punya `label`. Browser bisa memvalidasi sebagian; server **tetap** harus memvalidasi ulang.

## Daftar isi

- [Kerangka form yang benar](#kerangka-form-yang-benar)
- [`<form>`](#form)
- [Atribut `action`, `method`, `enctype`](#atribut-action-method-enctype)
- [`novalidate`, `autocomplete`, `target`, `name` pada form](#novalidate-autocomplete-target-name-pada-form)
- [`<label>`](#label)
- [`<input>` — aturan bersama](#input--aturan-bersama)
- [Atribut bersama input](#atribut-bersama-input)
- [`type="text"`](#typetext)
- [`type="email"`](#typeemail)
- [`type="password"`](#typepassword)
- [`type="number"`](#typenumber)
- [`type="search"`](#typesearch)
- [`type="tel"`](#typetel)
- [`type="url"`](#typeurl)
- [`type="date"`](#typedate)
- [`type="datetime-local"`](#typedatetime-local)
- [`type="time"`](#typetime)
- [`type="month"`](#typemonth)
- [`type="week"`](#typeweek)
- [`type="color"`](#typecolor)
- [`type="file"`](#typefile)
- [`type="checkbox"`](#typecheckbox)
- [`type="radio"`](#typeradio)
- [`type="range"`](#typerange)
- [`type="hidden"`](#typehidden)
- [`type="submit"`](#typesubmit)
- [`type="reset"`](#typereset)
- [`type="button"`](#typebutton)
- [`<textarea>`](#textarea)
- [`<select>`, `<option>`, `<optgroup>`](#select-option-optgroup)
- [`<datalist>`](#datalist)
- [`<fieldset>` dan `<legend>`](#fieldset-dan-legend)
- [`<button>`](#button)
- [`<output>`](#output)
- [`<meter>`](#meter)
- [`<progress>`](#progress)
- [Validasi bawaan browser](#validasi-bawaan-browser)
- [Form di React dan Laravel](#form-di-react-dan-laravel)
- [Kesalahan form yang sering muncul](#kesalahan-form-yang-sering-muncul)

## Kerangka form yang benar

**Untuk apa:** pola yang bisa disalin untuk tugas kontak / daftar / pemesanan.

```html
<form action="/kirim" method="post">
  <p>
    <label for="nama">Nama</label>
    <input id="nama" name="nama" type="text" autocomplete="name" required />
  </p>

  <p>
    <label for="email">Email</label>
    <input id="email" name="email" type="email" autocomplete="email" required />
  </p>

  <p>
    <label>
      <input type="checkbox" name="setuju" value="ya" required />
      Saya setuju syarat trip
    </label>
  </p>

  <p>
    <button type="submit">Kirim</button>
    <button type="button">Batal</button>
  </p>
</form>
```

Yang wajib diingat:

- `for` pada label = `id` pada kontrol (kecuali label membungkus kontrol).
- `name` yang dibaca server / `FormData`.
- `id` unik di seluruh halaman.
- `type` pada tombol ditulis eksplisit.

**Biasanya digabungkan dengan:** CSS Grid satu kolom di HP, JS `preventDefault` + `FormData`, React controlled input, Laravel `@csrf` + `$request->validate()`.

## `<form>`

**Untuk apa:** mengelompokkan kontrol yang dikirim bersama. Menekan Enter di input teks biasanya mensubmit form ini.

```html
<form action="/kontak" method="post">
  ...
</form>
```

Kontrol di luar `<form>` tidak ikut terkirim, kecuali memakai atribut `form="idForm"` (lihat bawah).

Jangan bersarang: `<form>` di dalam `<form>` tidak sah. Browser akan merusak pohon.

Jangan memakai form untuk membungkus seluruh halaman jika hanya satu tombol pencarian dan satu form checkout — pecah jadi dua form, atau satu form dengan dua tombol `formaction`.

**Biasanya digabungkan dengan:** `addEventListener('submit')`, React `onSubmit`, Blade `<form method="POST">`, HTML `method="get"` untuk pencarian.

## Atribut `action`, `method`, `enctype`

### `action`

**Untuk apa:** URL tujuan kirim. Kosong atau tidak ditulis = halaman sekarang.

```html
<form action="/kontak" method="post"></form>
<form action="https://contoh.test/api/kontak" method="post"></form>
<form method="get"></form>
```

Di Laravel, `action="{{ route('kontak.store') }}"`. Di Next, sering tidak memakai navigasi form klasik melainkan `fetch` ke Route Handler.

### `method`

**Untuk apa:** kata kerja HTTP yang dipakai browser untuk form klasik.

| Nilai | Untuk apa | Isi ke server |
| --- | --- | --- |
| `get` | cari, filter, tautan yang boleh di-bookmark | query string `?q=ampat` |
| `post` | membuat/mengubah data, unggah, login | body permintaan |
| `dialog` | menutup `<dialog>` yang memuat form | tidak mengirim ke server |

```html
<form action="/cari" method="get">
  <label for="q">Cari</label>
  <input id="q" name="q" type="search" />
  <button type="submit">Cari</button>
</form>
```

Browser **tidak** mengirim `PUT`/`PATCH`/`DELETE` dari form HTML biasa. Laravel menyiasati dengan `_method` spoofing:

```html
<form action="/paket/4" method="post">
  @csrf
  @method('PUT')
  ...
</form>
```

### `enctype`

**Untuk apa:** cara mengkode body `post`.

| Nilai | Untuk apa |
| --- | --- |
| `application/x-www-form-urlencoded` | default, teks |
| `multipart/form-data` | **wajib** jika ada `input type="file"` |
| `text/plain` | hampir tidak berguna; jangan |

```html
<form action="/unggah" method="post" enctype="multipart/form-data">
  <label for="foto">Foto KTP</label>
  <input id="foto" name="foto" type="file" accept="image/*" />
  <button type="submit">Unggah</button>
</form>
```

Lupa `multipart` = file tidak sampai.

**Biasanya digabungkan dengan:** Laravel `Storage`, validasi `file`, fetch `FormData` (biarkan browser set `Content-Type` + boundary — jangan set manual ke `multipart` tanpa boundary).

## `novalidate`, `autocomplete`, `target`, `name` pada form

### `novalidate`

**Untuk apa:** mematikan validasi bawaan browser saat submit. Pakai jika kamu mengganti UI error sendiri, **tetap validasi di JS dan server**.

```html
<form action="/kirim" method="post" novalidate></form>
```

Ada juga `formnovalidate` pada tombol submit tertentu (misalnya “Simpan draf”).

### `autocomplete` pada form

**Untuk apa:** `on` / `off` default untuk kontrol di dalamnya. Lebih tepat set per input (`autocomplete="email"`). `off` tidak selalu dihormati browser.

### `target` pada form

**Untuk apa:** seperti tautan: `_blank` mengirim dan menampilkan hasil di tab baru. Jarang diperlukan.

### `name` pada form

**Untuk apa:** menamai form di `document.forms.nama`. Opsional. Jangan bentrok dengan `name` kontrol.

### `rel` / `accept-charset`

`accept-charset="UTF-8"` jarang perlu jika dokumen sudah UTF-8.

### Atribut `form` pada kontrol

**Untuk apa:** mengaitkan input di luar elemen `<form>` ke form ber-`id`.

```html
<form id="pesan" action="/pesan" method="post">...</form>
<label for="catatan">Catatan</label>
<textarea id="catatan" name="catatan" form="pesan"></textarea>
```

**Biasanya digabungkan dengan:** layout di mana tombol submit ada di footer visual yang terpisah, dialog, hati-hati jangan lupa `id` form.

## `<label>`

**Untuk apa:** nama kontrol yang **terhubung**. Klik label = fokus / centang kontrol. Pembaca layar membacakan label saat fokus ke input.

```html
<!-- Pola A: for + id (paling jelas) -->
<label for="nama">Nama</label>
<input id="nama" name="nama" type="text" />

<!-- Pola B: label membungkus -->
<label>
  Nama
  <input name="nama" type="text" />
</label>
```

Pola A lebih mudah di-style (label di atas, input di bawah) dan lebih mudah diuji. Pola B tidak wajib `id` jika hanya satu kontrol di dalam.

Jangan memakai `placeholder` sebagai pengganti label. Placeholder hilang saat mengetik dan kontrasnya sering lemah.

Jangan menulis:

```html
<!-- Tidak terhubung -->
<p>Nama</p>
<input name="nama" type="text" />
```

Satu label merujuk satu kontrol. Jangan `for` ke `id` yang tidak ada.

`label` tidak untuk menandai heading bagian; itu `legend` di dalam `fieldset`, atau `h2`.

**Biasanya digabungkan dengan:** CSS `display: grid; gap: 0.25rem`, React `htmlFor` (bukan `for`), `useId()` untuk `id` unik, Laravel `@error('nama')` di dekat label.

## `<input>` — aturan bersama

**Untuk apa:** kontrol sebaris. Elemen void: tidak ada `</input>`. Perilaku ditentukan `type`.

Jika `type` tidak dikenal, browser merawatnya sebagai `text`. Itu sebabnya typo `type="emial"` diam-diam jadi teks biasa.

Tanpa `name`, nilai **tidak** masuk submit klasik. Tetap bisa dibaca JS.

**Biasanya digabungkan dengan:** semua atribut di bagian berikutnya, CSS `width: 100%`, `:focus-visible`, `:user-invalid` / `:invalid`.

## Atribut bersama input

Dibahas satu per satu. Tidak semua atribut berlaku di semua `type`.

### `type`

**Untuk apa:** jenis kontrol. Lihat bagian per type di bawah.

### `name`

**Untuk apa:** kunci data. Radio sekelompok **wajib** `name` sama. Checkbox ganda boleh `name="fasilitas[]"` di PHP/Laravel.

### `id`

**Untuk apa:** target `label for`, `aria-describedby`, CSS, JS. Unik.

### `value`

**Untuk apa:** nilai awal (teks) atau nilai yang dikirim saat terpilih (checkbox/radio/submit).

### `required`

**Untuk apa:** wajib diisi / wajib terpilih sebelum submit. Browser menahan submit. Pesan error native tidak selalu bahasa Indonesia.

### `disabled`

**Untuk apa:** tidak bisa diubah, tidak ikut fokus, **tidak ikut terkirim**.

### `readonly`

**Untuk apa:** tidak bisa diubah, tetap bisa fokus, **tetap terkirim**. Tidak berlaku di checkbox/radio/file dengan cara yang sama.

### `placeholder`

**Untuk apa:** contoh isian. Bukan label. Hilang saat terisi.

### `autocomplete`

**Untuk apa:** petunjuk isi otomatis. Pakai token standar.

| Token | Untuk apa |
| --- | --- |
| `name` | nama lengkap |
| `given-name` / `family-name` | nama depan / keluarga |
| `email` | email |
| `username` | nama masuk |
| `new-password` / `current-password` | sandi |
| `tel` | telepon |
| `street-address` / `address-line1` | alamat |
| `postal-code` | kode pos |
| `country` | negara |
| `organization` | organisasi |
| `one-time-code` | OTP |
| `off` | mohon jangan isi otomatis |

### `minlength` / `maxlength`

**Untuk apa:** panjang karakter (teks, search, password, tel, url). `maxlength` menahan ketikan. `minlength` dicek saat submit.

### `min` / `max` / `step`

**Untuk apa:** rentang angka dan tanggal. `step` pada number default 1.

### `pattern`

**Untuk apa:** regex seluruh nilai. Hanya type teksual tertentu. Wajib ada petunjuk manusia — regex tidak dibaca awam.

```html
<label for="kode">Kode promo (5 huruf besar)</label>
<input
  id="kode"
  name="kode"
  type="text"
  pattern="[A-Z]{5}"
  title="Lima huruf kapital, tanpa spasi"
/>
```

### `multiple`

**Untuk apa:** beberapa email (`type="email"`) atau beberapa file (`type="file"`).

### `accept`

**Untuk apa:** petunjuk jenis file. Bukan keamanan.

### `checked`

**Untuk apa:** keadaan awal checkbox/radio.

### `size`

**Untuk apa:** lebar visual kira-kira n karakter. Lebih rapi CSS `width`.

### `list`

**Untuk apa:** id `datalist`.

### `inputmode`

**Untuk apa:** papan ketik HP (`numeric`, `decimal`, `tel`, `email`, `url`, `search`). Tidak memvalidasi.

### `enterkeyhint`

**Untuk apa:** label tombol enter HP (`search`, `send`, `done`, `next`).

### `autofocus`

**Untuk apa:** fokus saat halaman dimuat. Satu saja. Bisa mengganggu pembaca layar dan keyboard. Hindari di halaman panjang.

### `tabindex`

Lihat bab 07. Jangan menambal urutan form dengan `tabindex` positif.

### `formaction`, `formenctype`, `formmethod`, `formtarget`, `formnovalidate`

**Untuk apa:** menimpa atribut form pada **tombol submit** tertentu.

```html
<button type="submit">Kirim</button>
<button type="submit" formnovalidate formaction="/draf" name="aksi" value="draf">
  Simpan draf
</button>
```

**Biasanya digabungkan dengan:** validasi native + pesan sendiri, password manager, Laravel Request.

## `type="text"`

**Untuk apa:** teks sebaris umum: nama, kota, judul. Default jika `type` dihilangkan.

```html
<label for="nama">Nama lengkap</label>
<input
  id="nama"
  name="nama"
  type="text"
  autocomplete="name"
  minlength="2"
  maxlength="80"
  required
/>
```

Bukan untuk sandi, email, atau angka yang dihitung. Bukan untuk esai — itu `textarea`.

`pattern` boleh. `min`/`max` tidak berlaku (itu number/date).

**Biasanya digabungkan dengan:** CSS, React `value` + `onChange`, Laravel `'nama' => ['required', 'string', 'max:80']`.

## `type="email"`

**Untuk apa:** alamat surel. Browser memeriksa bentuk kasar (`a@b`). Keyboard HP menampilkan `@`.

```html
<label for="email">Email</label>
<input id="email" name="email" type="email" autocomplete="email" required />
```

Beberapa alamat:

```html
<label for="email-tim">Email tim (pisahkan koma)</label>
<input id="email-tim" name="email_tim" type="email" multiple />
```

Validasi browser longgar. `a@b` bisa lolos. Server harus memeriksa ulang.

Jangan memakai `type="text"` + `pattern` rumit jika `email` sudah cukup.

**Biasanya digabungkan dengan:** Laravel `email`, React controlled, `autocomplete="email"`.

## `type="password"`

**Untuk apa:** sandi. Karakter disembunyikan.

```html
<label for="sandi">Sandi</label>
<input
  id="sandi"
  name="sandi"
  type="password"
  autocomplete="current-password"
  required
  minlength="8"
/>
```

Pendaftaran:

```html
<label for="sandi-baru">Sandi baru</label>
<input id="sandi-baru" name="sandi" type="password" autocomplete="new-password" required />
```

Jangan `autocomplete="off"` tanpa alasan — pengelola sandi membantu. Jangan menampilkan sandi ke `value` dari server di HTML. Jangan meniru titik-titik dengan `text` + CSS.

`maxlength` pada sandi bisa merusak pengelola sandi jika terlalu pendek.

**Biasanya digabungkan dengan:** tombol “tampilkan sandi” (`type` diubah JS ke `text` sementara), Laravel `Hash::make`, `confirmed`.

## `type="number"`

**Untuk apa:** angka yang naik-turun dan punya `min`/`max`/`step`. Bukan nomor telepon.

```html
<label for="tamu">Jumlah tamu</label>
<input
  id="tamu"
  name="tamu"
  type="number"
  min="1"
  max="12"
  step="1"
  value="2"
  inputmode="numeric"
  required
/>
```

Spinner native tidak konsisten. Nilai non-angka bisa jadi `''`. Nomor panjang (NIK, kartu) lebih aman `type="text"` + `inputmode="numeric"` + `pattern` agar nol di depan tidak hilang.

`step="any"` mengizinkan desimal bebas.

**Biasanya digabungkan dengan:** Laravel `integer|min:1`, JS `valueAsNumber` (NaN jika kosong), jangan pakai untuk telepon.

## `type="search"`

**Untuk apa:** kotak pencarian. Sering ada tombol bersihkan native. Semantik sedikit berbeda dari `text` untuk alat bantu dan CSS (`input[type="search"]`).

```html
<search>
  <form action="/cari" method="get">
    <label for="q">Cari paket</label>
    <input id="q" name="q" type="search" placeholder="Contoh: Pianemo" />
    <button type="submit">Cari</button>
  </form>
</search>
```

`placeholder` di sini adalah contoh, label tetap ada.

**Biasanya digabungkan dengan:** `role="search"` / `<search>`, JS filter `input` event, Laravel `where like`.

## `type="tel"`

**Untuk apa:** nomor telepon. **Tidak** memvalidasi format internasional secara ketat. Membuka papan ketik telepon di banyak HP.

```html
<label for="wa">WhatsApp</label>
<input id="wa" name="wa" type="tel" autocomplete="tel" inputmode="tel" placeholder="08xx atau +62" />
```

Validasi format: `pattern` + teks bantuan, atau library di JS/server. Jangan `type="number"` (nol depan hilang, `+` tidak bisa).

**Biasanya digabungkan dengan:** `autocomplete="tel"`, Laravel regex, tautan `tel:` setelah tersimpan.

## `type="url"`

**Untuk apa:** URL. Browser mengharapkan skema (`https://...`).

```html
<label for="situs">Situs (opsional)</label>
<input id="situs" name="situs" type="url" autocomplete="url" placeholder="https://contoh.test" />
```

Pengguna sering mengetik `contoh.test` tanpa skema — validasi native gagal. Bantu dengan `placeholder` atau JS yang menambah `https://`.

**Biasanya digabungkan dengan:** Laravel `url`, embed pratinjau, bukan untuk path relatif internal.

## `type="date"`

**Untuk apa:** tanggal (kalender native). Nilai terkirim `YYYY-MM-DD`.

```html
<label for="berangkat">Tanggal berangkat</label>
<input
  id="berangkat"
  name="berangkat"
  type="date"
  min="2026-10-01"
  max="2026-12-31"
  required
/>
```

Tampilan mengikuti OS/browser, bukan format Indonesia. Yang terkirim tetap ISO. Jangan mengandalkan teks yang kelihatan.

Dukungan sudah luas. Jika butuh format bebas “12 Okt 2026”, `text` + library — lebih berat.

**Biasanya digabungkan dengan:** Laravel `date`, `after:today`, React `value={iso}`. `min`/`max` string ISO.

## `type="datetime-local"`

**Untuk apa:** tanggal + waktu tanpa zona. Nilai `YYYY-MM-DDTHH:MM`.

```html
<label for="kumpul">Waktu kumpul (waktu setempat)</label>
<input id="kumpul" name="kumpul" type="datetime-local" min="2026-10-12T06:00" />
```

Tidak membawa zona waktu. Tulis di label “Waktu Indonesia Timur” jika penting. Untuk zona yang benar, server harus tahu konteksnya.

**Biasanya digabungkan dengan:** Laravel `date` / `Carbon`, hati-hati parsing `T`.

## `type="time"`

**Untuk apa:** jam menit (kadang detik). Nilai `HH:MM`.

```html
<label for="jemput">Jam jemput</label>
<input id="jemput" name="jemput" type="time" min="05:00" max="18:00" step="300" />
```

`step` dalam detik. `300` = 5 menit.

**Biasanya digabungkan dengan:** jadwal, `datetime-local` jika tanggal juga diminta.

## `type="month"`

**Untuk apa:** bulan dan tahun. Nilai `YYYY-MM`.

```html
<label for="musim">Bulan trip</label>
<input id="musim" name="musim" type="month" min="2026-01" max="2026-12" />
```

Dukungan UI bervariasi. Cadangan: `select` bulan + tahun.

**Biasanya digabungkan dengan:** laporan bulanan, filter arsip.

## `type="week"`

**Untuk apa:** minggu ISO. Nilai seperti `2026-W42`. Paling jarang, UI tidak konsisten.

```html
<label for="minggu">Minggu keberangkatan</label>
<input id="minggu" name="minggu" type="week" />
```

Untuk tugas kuliah, `date` atau `select` lebih aman.

**Biasanya digabungkan dengan:** hampir tidak pernah di produk umum. Kenali agar tidak kaget.

## `type="color"`

**Untuk apa:** pemilih warna. Nilai `#rrggbb` (tanpa alfa).

```html
<label for="warna-tema">Warna tema kartu</label>
<input id="warna-tema" name="warna_tema" type="color" value="#0f172a" />
```

Tidak semua warna (HSL, alpha) didukung. Aksesibilitas: sediakan juga teks hex jika pengguna perlu ketik.

**Biasanya digabungkan dengan:** CSS `value` langsung ke `style.background`, editor tema sederhana.

## `type="file"`

**Untuk apa:** memilih berkas dari perangkat.

```html
<label for="foto">Foto KTP (JPG atau PDF, maks 2 MB)</label>
<input
  id="foto"
  name="foto"
  type="file"
  accept="image/jpeg,image/png,application/pdf"
/>
```

Beberapa berkas:

```html
<label for="galeri">Foto trip (boleh lebih dari satu)</label>
<input id="galeri" name="galeri[]" type="file" accept="image/*" multiple />
```

### `accept`

**Untuk apa:** filter di dialog. Pengguna masih bisa “Semua file”. Server wajib cek MIME/ukuran/isi.

### `multiple`

**Untuk apa:** banyak berkas. `name` di PHP biasanya `galeri[]`.

### `capture` (HP)

**Untuk apa:** usul kamera `user` / `environment`.

```html
<input type="file" accept="image/*" capture="environment" name="bukti" />
```

Form **wajib** `enctype="multipart/form-data"` dan `method="post"`.

Jangan set `value` file lewat HTML (keamanan). JS hanya bisa mengosongkan.

**Biasanya digabungkan dengan:** preview `URL.createObjectURL`, Laravel `store()`, validasi `image|max:2048`.

## `type="checkbox"`

**Untuk apa:** ya/tidak, atau banyak pilihan independen.

```html
<label>
  <input type="checkbox" name="setuju" value="ya" required />
  Saya setuju syarat trip
</label>
```

Kelompok:

```html
<fieldset>
  <legend>Fasilitas tambahan</legend>
  <label><input type="checkbox" name="fasilitas[]" value="snorkel" /> Sewa snorkel</label>
  <label><input type="checkbox" name="fasilitas[]" value="kamera" /> Sewa kamera</label>
  <label><input type="checkbox" name="fasilitas[]" value="tumpangan" /> Tumpangan bandara</label>
</fieldset>
```

Tanpa `value`, checkbox yang tercentang mengirim `on` (kurang jelas). Tulis `value` eksplisit.

Tidak tercentang = **tidak ada** pasangan name di submit. Server tidak menerima “tidak”. Laravel: anggap tidak ada = false.

`checked` untuk keadaan awal. `indeterminate` hanya lewat JS (bukan atribut HTML yang andal untuk submit).

**Biasanya digabungkan dengan:** `fieldset`+`legend`, array Laravel, React `checked` + `onChange` (controlled).

## `type="radio"`

**Untuk apa:** **satu** pilihan dari kelompok. Satu kelompok = `name` sama.

```html
<fieldset>
  <legend>Jenis paket</legend>
  <label><input type="radio" name="paket" value="4hari" required /> 4 hari</label>
  <label><input type="radio" name="paket" value="7hari" /> 7 hari</label>
  <label><input type="radio" name="paket" value="charter" /> Charter</label>
</fieldset>
```

`required` pada salah satu radio di kelompok membuat kelompok wajib punya pilihan.

`checked` pada satu radio sebagai default. Jangan `checked` dua dengan `name` sama.

Setiap radio butuh label sendiri. Jangan hanya meletakkan teks di `legend`.

**Biasanya digabungkan dengan:** `fieldset`, Laravel `in:4hari,7hari,charter`, jangan pakai radio untuk on/off tunggal (itu checkbox).

## `type="range"`

**Untuk apa:** slider angka. Nilai selalu ada (default di tengah jika tidak di-set).

```html
<label for="anggaran">Anggaran kasar: <output id="tampilan-anggaran" for="anggaran">5000000</output></label>
<input
  id="anggaran"
  name="anggaran"
  type="range"
  min="1000000"
  max="20000000"
  step="500000"
  value="5000000"
  oninput="document.getElementById('tampilan-anggaran').value = this.value"
/>
```

Tanpa `output` / teks, pengguna tidak tahu nilai. Slider kurang tepat untuk angka presisi (harga pas).

**Biasanya digabungkan dengan:** `<output>`, JS `input` event, CSS styling slider yang menyebalkan lintas browser.

## `type="hidden"`

**Untuk apa:** nilai yang dikirim tanpa ditampilkan: token, id, spoof method. Bukan rahasia.

```html
<input type="hidden" name="_token" value="..." />
<input type="hidden" name="paket_id" value="14" />
```

Pengguna bisa mengubahnya di DevTools. Jangan menyimpan harga final hanya di hidden. Server menghitung ulang.

Laravel `@csrf` menghasilkan hidden token. `@method('PUT')` menghasilkan `_method`.

Tidak punya label terlihat. Jangan `required` sebagai pengganti logika.

**Biasanya digabungkan dengan:** CSRF, id resource, React juga bisa menyimpan di state tanpa hidden — hidden perlu jika submit HTML klasik.

## `type="submit"`

**Untuk apa:** tombol mengirim form. Lebih disarankan `<button type="submit">` karena isinya bisa lebih dari teks polos.

```html
<input type="submit" value="Kirim pesan" />
```

`value` = label tombol dan bisa ikut terkirim jika ada `name`.

Jika ada beberapa submit:

```html
<input type="submit" name="aksi" value="kirim" />
<input type="submit" name="aksi" value="draf" />
```

Hanya tombol yang diklik yang mengirim `name`.

**Biasanya digabungkan dengan:** `formaction`, CSS (lebih mudah men-style `button`).

## `type="reset"`

**Untuk apa:** mengembalikan semua kontrol ke nilai **awal HTML**, bukan “kosongkan semuanya” dan bukan undo React state.

```html
<input type="reset" value="Kembalikan isian awal" />
```

Sering mengejutkan pengguna. Lebih aman tombol `type="button"` yang mengosongkan secara sadar, atau tidak ada reset sama sekali.

**Biasanya digabungkan dengan:** hampir tidak pernah di produk modern. Kenali agar tidak terkaget saat isian hilang.

## `type="button"` pada `input`

**Untuk apa:** tombol yang **tidak** mensubmit. Butuh JS untuk berguna.

```html
<input type="button" value="Hitung perkiraan" id="hitung" />
```

Lebih baik:

```html
<button type="button" id="hitung">Hitung perkiraan</button>
```

`<button>` menerima ikon + teks dan men-style lebih mudah.

**Biasanya digabungkan dengan:** `addEventListener`, bukan dengan `action` form.

## `<textarea>`

**Untuk apa:** teks banyak baris: pesan, alamat panjang, catatan.

```html
<label for="pesan">Pesan</label>
<textarea id="pesan" name="pesan" rows="5" cols="40" maxlength="1000" required></textarea>
```

### Atribut satu per satu

#### `rows` / `cols`

**Untuk apa:** ukuran awal kasar. CSS `width`/`min-height` lebih andal.

#### `maxlength` / `minlength` / `required` / `readonly` / `disabled` / `placeholder` / `autocomplete` / `name` / `id`

Sama ide dengan input teks.

#### `wrap`

| Nilai | Untuk apa |
| --- | --- |
| `soft` | default; enter visual tidak dikirim sebagai baris baru paksa |
| `hard` | menyisipkan baris baru sesuai `cols` saat submit (jarang diinginkan) |

Isi awal = teks di antara tag, bukan atribut `value`.

```html
<textarea name="pesan">Halo, saya ingin tanya kuota Oktober.</textarea>
```

Jangan taruh spasi/enter aneh di antara tag jika tidak ingin isian awal berawalan kosong.

**Biasanya digabungkan dengan:** CSS `resize: vertical`, hitung sisa karakter JS, Laravel `string|max:1000`. React: `value` + `onChange`, bukan anak teks.

## `<select>`, `<option>`, `<optgroup>`

**Untuk apa:** memilih dari daftar yang sudah kamu tentukan.

```html
<label for="paket">Paket</label>
<select id="paket" name="paket" required>
  <option value="" disabled selected>Pilih paket</option>
  <option value="4hari">4 hari — Rp 8.500.000</option>
  <option value="7hari">7 hari — Rp 14.000.000</option>
  <option value="charter">Charter</option>
</select>
```

### `<select>` atribut

| Atribut | Untuk apa |
| --- | --- |
| `name` | kunci submit |
| `required` | wajib pilih opsi yang `value`-nya tidak kosong |
| `multiple` | banyak opsi (Ctrl/Cmd). UX sering buruk; checkbox lebih jelas |
| `size` | tampil sebagai kotak daftar, bukan dropdown |
| `disabled` | seluruh select mati |
| `autocomplete` | misalnya `country` |

### `<option>`

**Untuk apa:** satu pilihan.

```html
<option value="4hari">4 hari — Rp 8.500.000</option>
<option value="4hari" selected>4 hari</option>
<option value="habis" disabled>7 hari (penuh)</option>
```

Jika `value` dihilangkan, yang terkirim adalah teks opsi. Lebih jelas tulis `value`.

Opsi pertama `value=""` + `disabled` + `selected` + `required` pada select = pengguna harus memilih sadar.

### `<optgroup>`

**Untuk apa:** kelompok opsi. Bukan opsi yang bisa dipilih.

```html
<label for="tujuan">Titik temu</label>
<select id="tujuan" name="tujuan">
  <optgroup label="Sorong">
    <option value="bandara">Bandara DEO</option>
    <option value="pelabuhan">Pelabuhan</option>
  </optgroup>
  <optgroup label="Waisai">
    <option value="waisai-dermaga">Dermaga Waisai</option>
  </optgroup>
</select>
```

`label` pada `optgroup` wajib secara praktik.

Jangan memakai `select` untuk 2 opsi yang perlu dibandingkan secara visual — radio lebih jelas. Jangan 200 opsi tanpa cari — itu combobox/`datalist`/library.

**Biasanya digabungkan dengan:** Laravel `old('paket')` + `selected`, React `value` pada `select` (controlled), jangan `multiple` tanpa UI bantu.

## `<datalist>`

**Untuk apa:** saran isian pada input, tetap bisa mengetik nilai lain.

```html
<label for="kota">Kota keberangkatan</label>
<input id="kota" name="kota" type="text" list="daftar-kota" autocomplete="off" />
<datalist id="daftar-kota">
  <option value="Sorong"></option>
  <option value="Jakarta"></option>
  <option value="Makassar"></option>
</datalist>
```

`list` pada input = `id` datalist.

Bukan pengganti `select` jika nilai harus salah satu dari daftar. Pengguna bisa mengetik “xyz”. Validasi server tetap perlu.

Dukungan dan UI bervariasi (terutama HP). Anggap sebagai bantuan, bukan kontrol ketat.

**Biasanya digabungkan dengan:** `input` text/search/email/tel, bukan dengan `select`. React: render `option` dari array.

## `<fieldset>` dan `<legend>`

**Untuk apa:** mengelompokkan kontrol terkait dan memberinya judul aksesibel. Sangat penting untuk radio/checkbox.

```html
<fieldset>
  <legend>Metode bayar</legend>
  <label><input type="radio" name="bayar" value="transfer" required /> Transfer</label>
  <label><input type="radio" name="bayar" value="tunai" /> Tunai di Sorong</label>
</fieldset>
```

### `<legend>`

**Untuk apa:** judul kelompok. Anak pertama `fieldset`. Bukan `label` dan bukan `h2` pengganti (meski kamu boleh menaruh heading di dalam legend, biasanya teks biasa cukup).

`disabled` pada `fieldset` menonaktifkan kontrol di dalamnya (perilaku historis: beberapa kontrol di luar `legend`).

Jangan `fieldset` untuk seluruh form tanpa alasan — satu legend “Form” tidak menambah makna. Pakai untuk kelompok yang memang set.

**Biasanya digabungkan dengan:** radio, checkbox, alamat (baris-baris), CSS `border: 0` jika desain datar tetapi makna tetap.

## `<button>`

**Untuk apa:** tombol. Isi bisa teks, `span`, SVG. **Selalu tulis `type`.**

```html
<button type="submit">Kirim</button>
<button type="button">Batal</button>
<button type="reset">Kembalikan awal</button>
```

### `type` satu per satu

| Nilai | Untuk apa |
| --- | --- |
| `submit` | kirim form terdekat (default **jika di dalam form** dan `type` lupa ditulis) |
| `button` | tidak mengirim; untuk JS |
| `reset` | reset native |

Kesalahan klasik: `<button>Batal</button>` di dalam form = submit, karena default `submit`.

### Atribut lain

`name` + `value` ikut terkirim jika tombol submit diklik. `disabled` mematikan. `form` mengait ke form lain. `formaction` menimpa `action`.

Jangan membungkus `button` dengan `a`. Jangan menaruh `div onclick` sebagai ganti tombol.

**Biasanya digabungkan dengan:** CSS `:disabled`, JS click, React `type="button"` hampir selalu kecuali submit, spinner `disabled` saat fetching.

## `<output>`

**Untuk apa:** hasil kalkulasi yang ditampilkan, terhubung ke kontrol lain lewat `for` (daftar id).

```html
<form id="kalkulator" oninput="hasil.value = Number(a.value) + Number(b.value)">
  <label for="a">Harga paket</label>
  <input id="a" name="a" type="number" value="8500000" />

  <label for="b">Tiket kawasan</label>
  <input id="b" name="b" type="number" value="500000" />

  <p>Perkiraan: <output id="hasil" name="hasil" for="a b">9000000</output></p>
</form>
```

Bukan input (tidak diketik). Boleh ikut terkirim jika punya `name`.

**Biasanya digabungkan dengan:** `type="range"`, kalkulator biaya, `aria-live="polite"` jika hasil penting (bab 08). React: biasanya `{total}` di `<output>` atau `<p>`.

## `<meter>`

**Untuk apa:** nilai dalam **skala diketahui**: skor 0–100, kuota 7/12, suhu di rentang. Bukan loading.

```html
<label for="kuota">Kuota terisi</label>
<meter id="kuota" min="0" max="12" low="3" high="10" optimum="6" value="7">7 dari 12</meter>
```

### Atribut satu per satu

| Atribut | Untuk apa |
| --- | --- |
| `value` | nilai sekarang |
| `min` / `max` | batas (default 0 dan 1) |
| `low` / `high` | ambang “rendah” / “tinggi” |
| `optimum` | daerah yang dianggap baik |

Isi teks = cadangan jika meter tidak dirender. Tetap tulis angka di dekatnya karena gaya native sulit distyle dan tidak selalu jelas.

**Biasanya digabungkan dengan:** dashboard, bukan `progress`. CSS terbatas pada meter native.

## `<progress>`

**Untuk apa:** kemajuan tugas: unduh, langkah 2/5, submit berjalan.

```html
<label for="unggah">Mengunggah foto</label>
<progress id="unggah" max="100" value="40">40%</progress>
```

Tanpa `value` = tak tentu (indeterminate).

Bukan untuk “skor kualitas” statis — itu `meter`.

**Biasanya digabungkan dengan:** JS meng-update `value`, `aria-valuetext`, React state unggah. CSS styling lintas browser merepotkan; banyak UI memakai `div` ber-role (hati-hati, bab 08).

## Validasi bawaan browser

Atribut yang menahan submit: `required`, `type` (email/url), `min`/`max`/`step`, `minlength`/`maxlength`, `pattern`.

Pseudo-class CSS: `:valid`, `:invalid`, `:required`, `:optional`, `:user-valid`, `:user-invalid` (yang `user-*` lebih sopan — tidak merah sebelum disentuh).

```css
input:user-invalid {
  border-color: #b91c1c;
}
```

`setCustomValidity("Pesan")` di JS mengganti pesan native. `reportValidity()` memunculkan UI native.

Validasi browser **bisa dimatikan**. Server adalah penjaga terakhir.

**Biasanya digabungkan dengan:** Laravel Form Request, React jangan andalkan native saja jika `preventDefault` + fetch.

## Form di React dan Laravel

### React (terkontrol)

```jsx
<label htmlFor={id}>Nama</label>
<input
  id={id}
  name="nama"
  type="text"
  value={nama}
  onChange={(e) => setNama(e.target.value)}
  required
/>
```

- `class` → `className`
- `for` → `htmlFor`
- checkbox: `checked={bool}` bukan `value` sebagai keadaan
- `defaultValue` / `defaultChecked` untuk form tidak terkontrol

### Laravel Blade

```html
<form action="{{ route('kontak.store') }}" method="post">
  @csrf
  <label for="nama">Nama</label>
  <input id="nama" name="nama" type="text" value="{{ old('nama') }}" required />
  @error('nama')
    <p id="nama-error" class="error">{{ $message }}</p>
  @enderror
  <button type="submit">Kirim</button>
</form>
```

Sambungkan error: `aria-describedby="nama-error"` dan `aria-invalid="true"` (bab 08).

**Biasanya digabungkan dengan:** Inertia/React form library di proyek besar; untuk tugas, pola di atas cukup.

## Kesalahan form yang sering muncul

1. **Tidak ada `label`.** Placeholder bukan label.
2. **`for` dan `id` tidak sama** (salah ketik, id dobel).
3. **Tidak ada `name`.** Server menerima array kosong.
4. **File tanpa `enctype="multipart/form-data"`.**
5. **`<button>Batal</button>` mensubmit** karena lupa `type="button"`.
6. **Radio beda `name`** sehingga bisa memilih semua.
7. **`type="number"` untuk telepon / NIK.**
8. **Mengandalkan `accept` / `required` saja** tanpa validasi server.
9. **`input type="hidden"` sebagai harga final.**
10. **Reset native** yang menghapus isian 10 menit.
11. **Select tanpa opsi kosong** sehingga nilai pertama terkirim tanpa sadar.
12. **Checkbox tanpa `value`** dan server bingung membedakan “on”.

Latihan: form pemesanan berisi nama, email, tel, tanggal, radio paket, checkbox setuju, textarea catatan, file bukti transfer, tombol submit + tombol hitung `type="button"`. Semua ber-label, `name`, dan `autocomplete` yang masuk akal.
