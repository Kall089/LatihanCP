# 01 — Dasar: tipe, variabel, dan operator

[← Indeks](README.md) · [Lanjut 02 →](02-kontrol-fungsi-modul.md)

Python menyimpan data di variabel. Tipe menentukan apa yang boleh dilakukan: angka dijumlah, teks digabung, daftar ditambah item. Bab ini mengkatalog tipe bawaan yang paling sering muncul di tugas kuliah, plus method yang menempel di tiap tipe.

Semua contoh bisa disalin ke `coba.py` lalu `python coba.py`. Tidak perlu paket tambahan.

## Daftar isi

- [print](#print)
- [type](#type)
- [variabel](#variabel)
- [int](#int)
- [int()](#int-konversi)
- [float](#float)
- [float()](#float-konversi)
- [str](#str)
- [f-string](#f-string)
- [str.upper](#strupper)
- [str.lower](#strlower)
- [str.strip](#strstrip)
- [str.split](#strsplit)
- [str.join](#strjoin)
- [str.replace](#strreplace)
- [str.find](#strfind)
- [str.startswith](#strstartswith)
- [bool](#bool)
- [bool()](#bool-konversi)
- [None](#none)
- [list](#list)
- [list.append](#listappend)
- [list.extend](#listextend)
- [list.insert](#listinsert)
- [list.remove](#listremove)
- [list.pop](#listpop)
- [list.index](#listindex)
- [list.sort](#listsort)
- [slicing list](#slicing-list)
- [tuple](#tuple)
- [dict](#dict)
- [dict.get](#dictget)
- [dict.keys](#dictkeys)
- [dict.values](#dictvalues)
- [dict.items](#dictitems)
- [dict.update](#dictupdate)
- [dict.pop](#dictpop)
- [set](#set)
- [set.add](#setadd)
- [set.union](#setunion)
- [set.intersection](#setintersection)
- [len](#len)
- [range](#range)
- [isinstance](#isinstance)
- [operator aritmetika](#operator-aritmetika)
- [pembagian // dan %](#pembagian--dan-)
- [pangkat **](#pangkat-)
- [perbandingan](#perbandingan)
- [and or not](#and-or-not)
- [in](#in)
- [is versus ==](#is-versus-)
- [unpacking](#unpacking)
- [min max sum](#min-max-sum)
- [round](#round)
- [abs](#abs)
- [sorted](#sorted)
- [indexing](#indexing)

## print

**Tipe:** fungsi bawaan

**Untuk apa:** menampilkan nilai ke terminal. Ini cara paling jujur untuk melihat isi variabel. Tanpa `print`, skrip yang hanya menghitung diam-diam selesai tanpa jejak. Di Jupyter, baris terakhir sel juga ditampilkan, tapi di file `.py` kamu harus `print`.

**Contoh implementasi:**

```python
nama = "Haikal"
sks = 3
print(nama)
print("SKS:", sks)
print(nama, sks, sep=" | ")
print("selesai", end="!\n")
```

**Yang terjadi:**

- Baris 1 menyimpan teks `Haikal`.
- Baris 2 menyimpan angka `3`.
- `print(nama)` menulis `Haikal` lalu pindah baris.
- `print("SKS:", sks)` menulis `SKS: 3` karena `print` memisahkan argumen dengan spasi.
- `sep=" | "` mengganti pemisah jadi `Haikal | 3`.
- `end="!\n"` mengganti akhir default `\n` menjadi `!` plus baris baru, jadi muncul `selesai!`.

**Biasanya digabungkan dengan:** f-string, `type()`, dan `repr()` saat debug.

**Jangan:** mengira `print` mengembalikan nilai yang bisa dihitung. `hasil = print(2 + 2)` membuat `hasil` menjadi `None`.

## type

**Tipe:** fungsi bawaan

**Untuk apa:** menanyakan kelas sebuah nilai. Berguna saat error “tidak bisa jumlahkan str dan int” dan kamu tidak yakin variabel itu apa. `type` tidak mengubah data, hanya mengintip.

**Contoh implementasi:**

```python
print(type(21))
print(type(3.5))
print(type("web"))
print(type(True))
print(type(None))
print(type([1, 2]))
print(type({"a": 1}))
```

**Yang terjadi:**

- `type(21)` → `<class 'int'>`.
- `type(3.5)` → `<class 'float'>`.
- `type("web")` → `<class 'str'>`.
- `type(True)` → `<class 'bool'>`. `bool` adalah turunan `int`, tapi `type` tetap bilang `bool`.
- `type(None)` → `<class 'NoneType'>`.
- List dan dict menampilkan `<class 'list'>` dan `<class 'dict'>`.

**Biasanya digabungkan dengan:** `isinstance`, konversi `int()`/`str()`, dan pesan error.

**Jangan:** membandingkan dengan string `"int"`. Tulis `type(x) is int` atau lebih aman `isinstance(x, int)`.

## variabel

**Tipe:** aturan bahasa (assignment)

**Untuk apa:** menamai nilai supaya bisa dipakai ulang. Nama di kiri, nilai di kanan. Python tidak perlu menulis tipe di depan. Nama yang jelas mengalahkan komentar panjang.

**Contoh implementasi:**

```python
mata_kuliah = "Pemrograman Web"
sks = 3
lulus = True
sks = sks + 1
print(mata_kuliah, sks, lulus)
```

**Yang terjadi:**

- `mata_kuliah` menunjuk ke string.
- `sks` menunjuk ke `3`, lalu diganti `4` karena `sks + 1`.
- `lulus` menunjuk ke `True`.
- Output: `Pemrograman Web 4 True`.

**Biasanya digabungkan dengan:** `const` tidak ada di Python; konvensi nama `HURUF_BESAR` untuk konstanta, tapi tetap bisa diubah.

**Jangan:** memakai nama `list`, `str`, `type`, `id`. Kamu menimpa fungsi bawaan dan error-nya membingungkan.

## int

**Tipe:** tipe data bawaan (bilangan utuh)

**Untuk apa:** menyimpan angka tanpa koma: SKS, jumlah mahasiswa, harga dalam rupiah utuh, indeks. Integer Python tidak overflow seperti `int` 32-bit di C; angka boleh sangat besar.

**Contoh implementasi:**

```python
sks = 3
tahun = 2026
negatif = -2
besar = 10**20
print(sks, type(sks))
print(tahun + 1)
print(negatif * 4)
print(besar)
print(0b1010, 0o17, 0xFF)
```

**Yang terjadi:**

- `sks` dan `tahun` adalah `int`.
- `tahun + 1` → `2027`.
- `negatif * 4` → `-8`.
- `10**20` tetap `int` (1 diikuti 20 nol), bukan error overflow.
- `0b1010` = 10, `0o17` = 15, `0xFF` = 255 (penulisan biner, oktal, heksadesimal).

**Biasanya digabungkan dengan:** `range`, indeks list, dan `//` untuk pembagian utuh.

**Jangan:** membagi dua `int` dengan `/` lalu mengira hasilnya `int`. `7 / 2` adalah `3.5` (`float`). Pakai `//` jika ingin utuh.

## int() konversi

**Tipe:** konstruktor / fungsi konversi

**Untuk apa:** mengubah teks atau float menjadi bilangan utuh. Sering dipakai setelah `input()` karena `input` selalu mengembalikan `str`.

**Contoh implementasi:**

```python
teks = "21"
print(int(teks))
print(int(3.9))
print(int("  7 "))
print(int("1010", 2))
```

**Yang terjadi:**

- `int("21")` → `21`.
- `int(3.9)` → `3` (potong ke arah nol, bukan dibulatkan).
- Spasi di tepi teks angka diabaikan: `7`.
- Argumen kedua adalah basis: `"1010"` basis 2 → `10`.

**Biasanya digabungkan dengan:** `input()`, `str.strip()`, dan `try/except ValueError`.

**Jangan:** `int("3.9")`. Teks berkoma ditolak. Tulis `int(float("3.9"))` atau `round`.

## float

**Tipe:** tipe data bawaan (bilangan pecahan)

**Untuk apa:** IPK, persentase, suhu, rata-rata. Dipakai saat ada koma desimal. Hati-hati: komputer menyimpan pecahan basis 2, jadi `0.1 + 0.2` tidak selalu persis `0.3`.

**Contoh implementasi:**

```python
ipk = 3.75
diskon = 0.1
print(type(ipk))
print(ipk * 2)
print(0.1 + 0.2)
print(1.5e3)
```

**Yang terjadi:**

- `type(ipk)` → `<class 'float'>`.
- `ipk * 2` → `7.5`.
- `0.1 + 0.2` → `0.30000000000000004` (bukan bug kodemu, sifat float).
- `1.5e3` adalah notasi ilmiah: `1500.0`.

**Biasanya digabungkan dengan:** `round`, `format`, dan NumPy `float64`.

**Jangan:** membandingkan dua float dengan `==` setelah banyak operasi. Bandingkan selisihnya: `abs(a - b) < 1e-9`.

## float() konversi

**Tipe:** konstruktor / fungsi konversi

**Untuk apa:** mengubah teks atau int menjadi pecahan. Berguna saat baca CSV yang masih string.

**Contoh implementasi:**

```python
print(float("3.75"))
print(float(3))
print(float("1e2"))
```

**Yang terjadi:**

- `"3.75"` menjadi `3.75`.
- `float(3)` menjadi `3.0` (tetap pecahan).
- `"1e2"` dibaca notasi ilmiah: `100.0`.

**Biasanya digabungkan dengan:** pandas `astype(float)`, `round`, dan `format`.

**Jangan:** `float("")` atau `float("tiga")`. Keduanya `ValueError`. Bersihkan dulu, atau tangkap error.

## str

**Tipe:** tipe data bawaan (teks)

**Untuk apa:** nama, NIM, path file, pesan error, isi HTML. String Python tidak bisa diubah di tempat (immutable): method seperti `replace` mengembalikan string baru.

**Contoh implementasi:**

```python
nama = "Pemrograman Web"
kutip = 'Toko "Belajar"'
kosong = ""
print(nama)
print(len(nama))
print(nama[0], nama[-1])
print(kutip)
print(kosong == "")
```

**Yang terjadi:**

- `len(nama)` → `16` (termasuk spasi).
- `nama[0]` → `P`, `nama[-1]` → `b` (indeks dari belakang).
- Petik tunggal dan ganda sama-sama `str`; pilih yang tidak bentrok dengan isi.
- `kosong == ""` → `True`.

**Biasanya digabungkan dengan:** f-string, `split`/`join`, dan regex di file 09.

**Jangan:** `nama[0] = "p"`. Error `TypeError: 'str' object does not support item assignment`. Buat string baru.

## f-string

**Tipe:** sintaks string (Python 3.6+)

**Untuk apa:** menyisipkan variabel ke teks tanpa `+` berantai. Lebih mudah dibaca daripada `"Halo " + nama + " nilai " + str(n)`.

**Contoh implementasi:**

```python
nama = "Haikal"
nilai = 88
print(f"Halo {nama}, nilai {nilai}")
print(f"nilai/100 = {nilai / 100:.2f}")
print(f"{nama:>10}")
```

**Yang terjadi:**

- Baris pertama: `Halo Haikal, nilai 88`.
- `:.2f` memaksa dua angka di belakang koma: `0.88`.
- `:>10` merapikan ke kanan dalam lebar 10 karakter (spasi di kiri).

**Biasanya digabungkan dengan:** `print`, log, dan label matplotlib.

**Jangan:** menaruh pernyataan `if` utuh di dalam `{}`. Hanya ekspresi. Untuk cabang, pakai ternary: `f"{'lulus' if nilai >= 70 else 'ulang'}"`.

## str.upper

**Tipe:** method `str`

**Untuk apa:** membuat huruf besar semua. Berguna untuk membandingkan input tanpa peduli kapital, atau menampilkan kode mata kuliah.

**Contoh implementasi:**

```python
kode = "if4021"
print(kode.upper())
print(kode)
```

**Yang terjadi:**

- `upper()` mengembalikan `IF4021`.
- `kode` tetap `if4021` karena string tidak berubah di tempat.

**Biasanya digabungkan dengan:** `lower`, `strip`, dan `==` saat cek input.

**Jangan:** mengira `kode` sudah jadi huruf besar setelah `kode.upper()` tanpa assignment. Tulis `kode = kode.upper()`.

## str.lower

**Tipe:** method `str`

**Untuk apa:** membuat huruf kecil semua. Pasangan `upper`. Sering dipakai sebelum membandingkan email atau nama file.

**Contoh implementasi:**

```python
email = "Haikal@Kampus.AC.ID"
print(email.lower())
print(email.lower() == "haikal@kampus.ac.id")
```

**Yang terjadi:**

- `lower()` → `haikal@kampus.ac.id`.
- Perbandingan jadi `True` meskipun aslinya campur kapital.

**Biasanya digabungkan dengan:** `strip`, `endswith`, dan validasi form.

**Jangan:** memakai `lower` untuk teks yang kapitalnya bermakna (kode negara, akronim yang harus tetap).

## str.strip

**Tipe:** method `str`

**Untuk apa:** membuang spasi (dan karakter kosong lain) di kiri dan kanan. Data dari CSV atau `input()` sering kebawa spasi tersembunyi.

**Contoh implementasi:**

```python
nim = "  2106123  \n"
print(repr(nim))
print(repr(nim.strip()))
print("xxABxx".strip("x"))
```

**Yang terjadi:**

- `repr(nim)` memperlihatkan spasi dan `\n`.
- `strip()` → `'2106123'` tanpa spasi dan tanpa newline.
- Argumen `"x"` membuang huruf `x` di tepi: `AB`.

**Biasanya digabungkan dengan:** `split`, `int()`, dan `dropna` di pandas setelah dibersihkan.

**Jangan:** mengira `strip` menghapus spasi di tengah. `"A  B".strip()` tetap `"A  B"`. Pakai `replace` atau `" ".join(teks.split())`.

## str.split

**Tipe:** method `str`

**Untuk apa:** memecah teks menjadi `list`. Default pemisah adalah spasi. Berguna untuk CSV sederhana, token, atau pecah nama lengkap.

**Contoh implementasi:**

```python
baris = "Haikal,88,A"
potong = baris.split(",")
print(potong)
print(potong[1])
kalimat = "  Pemrograman   Web  "
print(kalimat.split())
```

**Yang terjadi:**

- `split(",")` → `['Haikal', '88', 'A']`.
- `potong[1]` → `'88'` (masih string, bukan int).
- `split()` tanpa argumen merapatkan spasi ganda: `['Pemrograman', 'Web']`.

**Biasanya digabungkan dengan:** `int()`, unpacking, dan `csv` untuk file sungguhan.

**Jangan:** `split` CSV yang field-nya mengandung koma di dalam kutip. Pakai modul `csv` di file 03.

## str.join

**Tipe:** method `str`

**Untuk apa:** menggabungkan daftar teks menjadi satu string, dengan pemisah yang kamu pilih. Kebalikan `split`. Dipanggil pada **pemisah**, bukan pada list.

**Contoh implementasi:**

```python
mk = ["Pemrograman Web", "Basis Data", "Jaringan"]
print(" | ".join(mk))
print(",".join(["8", "8", "9"]))
```

**Yang terjadi:**

- `" | ".join(mk)` → `Pemrograman Web | Basis Data | Jaringan`.
- `",".join(...)` → `8,8,9`.

**Biasanya digabungkan dengan:** list comprehension, `map(str, angka)`, dan tulis file.

**Jangan:** `",".join([8, 8, 9])`. `join` hanya menerima string. Bungkus dulu: `",".join(str(x) for x in [8, 8, 9])`.

## str.replace

**Tipe:** method `str`

**Untuk apa:** mengganti potongan teks. Tidak memakai regex (itu tugas `re.sub`). Bagus untuk merapikan pemisah, menghapus karakter, atau standarisasi ejaan.

**Contoh implementasi:**

```python
path = "data\\nilai.csv"
print(path.replace("\\", "/"))
teks = "nilai nilai nilai"
print(teks.replace("nilai", "skor", 1))
```

**Yang terjadi:**

- Backslash Windows jadi `/`: `data/nilai.csv`.
- Argumen ketiga membatasi jumlah ganti: hanya kemunculan pertama yang berubah → `skor nilai nilai`.

**Biasanya digabungkan dengan:** `strip`, `split`, dan `Path` di file 03.

**Jangan:** mengira string asli berubah. `teks.replace(...)` tanpa disimpan ke variabel berarti hasilnya dibuang.

## str.find

**Tipe:** method `str`

**Untuk apa:** mencari posisi substring. Mengembalikan indeks, atau `-1` jika tidak ketemu. Lebih aman daripada `index` yang melempar error.

**Contoh implementasi:**

```python
url = "https://kampus.ac.id/nilai?nim=2106"
print(url.find("nilai"))
print(url.find("xyz"))
print("web" in url)
```

**Yang terjadi:**

- `"nilai"` mulai di indeks 23 (hitung dari 0).
- `"xyz"` tidak ada → `-1`.
- `"web" in url` → `False` (tidak ada kata `web` di URL itu).

**Biasanya digabungkan dengan:** `in`, `startswith`, dan slicing `url[posisi:]`.

**Jangan:** `if url.find("nilai"):` karena indeks `0` dianggap falsy. Pakai `if "nilai" in url:` atau `if url.find("nilai") != -1:`.

## str.startswith

**Tipe:** method `str`

**Untuk apa:** mengecek awalan teks. Enak untuk filter URL, nama file, atau NIM angkatan.

**Contoh implementasi:**

```python
nim = "2106123"
print(nim.startswith("21"))
print(nim.endswith("123"))
print("nilai.csv".endswith((".csv", ".tsv")))
```

**Yang terjadi:**

- `startswith("21")` → `True`.
- `endswith("123")` → `True`.
- `endswith` boleh menerima tuple akhiran: `.csv` cocok → `True`.

**Biasanya digabungkan dengan:** `lower`, `Path.suffix`, dan filter list comprehension.

**Jangan:** `nim.startswith("21", "22")` sebagai dua awalan. Untuk beberapa awalan, kirim tuple: `startswith(("21", "22"))`.

## bool

**Tipe:** tipe data bawaan (True/False)

**Untuk apa:** menandai ya atau tidak: lulus, aktif, sudah bayar. Hasil perbandingan juga `bool`. Dipakai di `if` dan filter pandas.

**Contoh implementasi:**

```python
lulus = True
mengulang = False
print(lulus, type(lulus))
print(88 >= 70)
print(True + True)
```

**Yang terjadi:**

- `type(lulus)` → `<class 'bool'>`.
- `88 >= 70` → `True`.
- `True + True` → `2` karena `bool` turunan `int`. Jangan diandalkan untuk aritmetika serius.

**Biasanya digabungkan dengan:** `if`, operator `and/or/not`, dan mask boolean pandas.

**Jangan:** menulis `if lulus == True:`. Cukup `if lulus:`.

## bool() konversi

**Tipe:** konstruktor / fungsi konversi

**Untuk apa:** menanyakan “apakah nilai ini dianggap benar?” Python punya aturan truthy/falsy. Berguna saat cek list kosong atau string kosong.

**Contoh implementasi:**

```python
print(bool(1), bool(0))
print(bool("halo"), bool(""))
print(bool([1]), bool([]))
print(bool(None))
```

**Yang terjadi:**

- `1` → `True`, `0` → `False`.
- String isi → `True`, `""` → `False`.
- List isi → `True`, `[]` → `False`.
- `None` → `False`.

**Biasanya digabungkan dengan:** `if daftar:`, `any`, `all`.

**Jangan:** mengira `bool("False")` adalah `False`. String tidak kosong selalu `True`, termasuk `"False"` dan `"0"`.

## None

**Tipe:** singleton `NoneType`

**Untuk apa:** menandai “tidak ada nilai”. Bukan nol, bukan string kosong. Fungsi tanpa `return` mengembalikan `None`. Data hilang di pandas sering `NaN`, bukan `None` — bedanya dibahas di file 07.

**Contoh implementasi:**

```python
nilai = None
print(nilai is None)
print(nilai == None)

def diam():
    pass

print(diam())
```

**Yang terjadi:**

- `nilai is None` → `True` (cara yang disarankan).
- `nilai == None` juga `True`, tapi gaya buruk.
- Fungsi `diam` tidak `return` → `print` menulis `None`.

**Biasanya digabungkan dengan:** `is`, `dict.get`, dan default argumen fungsi.

**Jangan:** `if nilai:` untuk membedakan `None` dan `0`. Nol juga falsy. Tulis `if nilai is None:`.

## list

**Tipe:** tipe data bawaan (daftar dinamis)

**Untuk apa:** menyimpan urutan yang bisa ditambah, dihapus, dan diubah. Ini wadah paling sering di tugas: daftar nilai, nama, baris file. Boleh campur tipe, tapi biasanya jangan.

**Contoh implementasi:**

```python
nilai = [80, 70, 90]
campur = ["Web", 3, True]
kosong = []
print(nilai[0], nilai[-1])
nilai[1] = 75
print(nilai)
print(len(nilai), campur, kosong)
```

**Yang terjadi:**

- `nilai[0]` → `80`, `nilai[-1]` → `90`.
- Assignment `nilai[1] = 75` mengubah list di tempat: `[80, 75, 90]`.
- `len(nilai)` → `3`.
- `campur` boleh berisi tipe berbeda; `kosong` adalah list tanpa item.

**Biasanya digabungkan dengan:** `for`, list comprehension, `append`, dan `pandas.Series`.

**Jangan:** menyalin dengan `b = a` lalu mengubah `b`. Itu dua nama untuk list yang sama. Pakai `a.copy()` atau `a[:]`.

## list.append

**Tipe:** method `list`

**Untuk apa:** menambah satu item di ujung. Paling sering dipakai di dalam loop saat mengumpulkan hasil.

**Contoh implementasi:**

```python
mk = ["Web"]
mk.append("Basis Data")
print(mk)
hasil = mk.append("Jaringan")
print(hasil)
print(mk)
```

**Yang terjadi:**

- Setelah append pertama: `['Web', 'Basis Data']`.
- `append` mengembalikan `None`, jadi `hasil` adalah `None`.
- List `mk` tetap bertambah: `['Web', 'Basis Data', 'Jaringan']`.

**Biasanya digabungkan dengan:** `for`, `extend` (untuk banyak item), dan `json.dump`.

**Jangan:** `mk = mk.append("X")`. Kamu menimpa list dengan `None`.

## list.extend

**Tipe:** method `list`

**Untuk apa:** menambahkan banyak item dari iterable lain, satu per satu. Beda dengan `append` yang menaruh seluruh list sebagai satu elemen.

**Contoh implementasi:**

```python
a = [80, 70]
b = [90, 85]
a.append(b)
print("append:", a)
c = [80, 70]
c.extend(b)
print("extend:", c)
```

**Yang terjadi:**

- `append` → `[80, 70, [90, 85]]` (list di dalam list).
- `extend` → `[80, 70, 90, 85]` (datar).

**Biasanya digabungkan dengan:** `+` untuk list baru (`a + b` tidak mengubah `a`), dan baca beberapa file.

**Jangan:** `extend(90)` — angka tidak iterable. `extend` butuh list/tuple/string.

## list.insert

**Tipe:** method `list`

**Untuk apa:** menyelipkan item di indeks tertentu. Item di kanan bergeser. Untuk sisipan di ujung, `append` lebih jelas.

**Contoh implementasi:**

```python
antrian = ["Budi", "Siti"]
antrian.insert(0, "Ana")
print(antrian)
antrian.insert(2, "Dedi")
print(antrian)
```

**Yang terjadi:**

- `insert(0, "Ana")` → `['Ana', 'Budi', 'Siti']`.
- `insert(2, "Dedi")` menyelip sebelum `Siti`: `['Ana', 'Budi', 'Dedi', 'Siti']`.

**Biasanya digabungkan dengan:** `index` untuk mencari posisi, lalu sisip.

**Jangan:** memakai `insert(0, x)` berulang di list panjang. Itu lambat. Pakai `collections.deque` jika sering sisip di depan.

## list.remove

**Tipe:** method `list`

**Untuk apa:** menghapus **kemunculan pertama** suatu nilai. Mencari isi, bukan indeks.

**Contoh implementasi:**

```python
nilai = [80, 70, 80, 90]
nilai.remove(80)
print(nilai)
```

**Yang terjadi:**

- `80` pertama hilang → `[70, 80, 90]`.
- `80` kedua masih ada.

**Biasanya digabungkan dengan:** `in` untuk cek dulu, atau list comprehension untuk hapus semua: `[x for x in nilai if x != 80]`.

**Jangan:** `remove` nilai yang tidak ada. `ValueError`. Cek `if x in daftar:` dulu.

## list.pop

**Tipe:** method `list`

**Untuk apa:** mengambil (dan menghapus) item di indeks. Default indeks terakhir. Berguna untuk tumpukan (stack): ambil dari ujung.

**Contoh implementasi:**

```python
tumpukan = ["buka", "edit", "simpan"]
terakhir = tumpukan.pop()
print(terakhir)
print(tumpukan)
depan = tumpukan.pop(0)
print(depan, tumpukan)
```

**Yang terjadi:**

- `pop()` → `'simpan'`, sisa `['buka', 'edit']`.
- `pop(0)` → `'buka'`, sisa `['edit']`.

**Biasanya digabungkan dengan:** `append` sebagai stack, dan `while daftar:`.

**Jangan:** `pop` list kosong. `IndexError`. Cek `if daftar:` dulu.

## list.index

**Tipe:** method `list`

**Untuk apa:** mencari indeks kemunculan pertama suatu nilai.

**Contoh implementasi:**

```python
mk = ["Web", "Basis Data", "Jaringan", "Web"]
print(mk.index("Web"))
print(mk.index("Web", 1))
```

**Yang terjadi:**

- `index("Web")` → `0`.
- Argumen kedua mulai cari dari indeks 1 → ketemu lagi di `3`.

**Biasanya digabungkan dengan:** `in` sebagai penjaga, dan slicing.

**Jangan:** `index` item yang tidak ada. `ValueError`. Untuk “ada atau tidak”, pakai `in`.

## list.sort

**Tipe:** method `list`

**Untuk apa:** mengurutkan list di tempat. Mengembalikan `None`. Untuk list baru tanpa merusak aslinya, pakai `sorted()`.

**Contoh implementasi:**

```python
nilai = [80, 70, 90, 65]
nilai.sort()
print(nilai)
nama = ["Siti", "Ana", "Budi"]
nama.sort(reverse=True)
print(nama)
pasangan = [("Web", 88), ("Basis", 70)]
pasangan.sort(key=lambda x: x[1])
print(pasangan)
```

**Yang terjadi:**

- Angka naik: `[65, 70, 80, 90]`.
- Nama menurun alfabet: `['Siti', 'Budi', 'Ana']`.
- `key` mengurutkan tuple berdasarkan nilai (indeks 1): Basis 70 dulu, baru Web 88.

**Biasanya digabungkan dengan:** `sorted`, `lambda`, dan `itemgetter`.

**Jangan:** `nilai = nilai.sort()`. `sort` mengembalikan `None`.

## slicing list

**Tipe:** sintaks urutan (`list`/`str`/`tuple`)

**Untuk apa:** mengambil potongan `[mulai:selesai:langkah]`. Indeks `selesai` tidak ikut. Sangat sering di NumPy dan pandas, polanya sama.

**Contoh implementasi:**

```python
nilai = [60, 70, 80, 90, 100]
print(nilai[1:4])
print(nilai[:3])
print(nilai[3:])
print(nilai[::2])
print(nilai[::-1])
```

**Yang terjadi:**

- `[1:4]` → `[70, 80, 90]` (indeks 1,2,3).
- `[:3]` → tiga pertama `[60, 70, 80]`.
- `[3:]` → dari indeks 3 sampai habis `[90, 100]`.
- `[::2]` → loncat 2: `[60, 80, 100]`.
- `[::-1]` membalik: `[100, 90, 80, 70, 60]`.

**Biasanya digabungkan dengan:** copy dangkal `nilai[:]`, dan slicing NumPy di file 04.

**Jangan:** mengira `nilai[1:4]` memuat indeks 4. Batas kanan terbuka.

## tuple

**Tipe:** tipe data bawaan (urutan tetap)

**Untuk apa:** daftar yang tidak boleh diubah setelah dibuat: pasangan `(nama, nilai)`, ukuran `(baris, kolom)`, record singkat. Bisa jadi kunci dict, list tidak bisa.

**Contoh implementasi:**

```python
poin = ("Haikal", 88)
satu = (7,)
bukan_tuple = (7)
print(poin[0], poin[1])
print(type(satu), type(bukan_tuple))
a, b = poin
print(a, b)
```

**Yang terjadi:**

- `poin[0]` → `Haikal`, `poin[1]` → `88`.
- `(7,)` adalah tuple satu elemen; `(7)` hanyalah int `7` karena kurung biasa.
- Unpacking: `a = "Haikal"`, `b = 88`.

**Biasanya digabungkan dengan:** `zip`, `enumerate`, return banyak nilai dari fungsi, `shape` NumPy.

**Jangan:** `poin[1] = 90`. `TypeError`. Kalau perlu ubah, pakai list atau buat tuple baru.

## dict

**Tipe:** tipe data bawaan (peta kunci → nilai)

**Untuk apa:** menyimpan data berlabel: satu mahasiswa, satu baris JSON, pengaturan. Kunci harus hashable (str, int, tuple), biasanya string. Sejak Python 3.7 urutan kunci mengikuti urutan masuk.

**Contoh implementasi:**

```python
mhs = {"nama": "Haikal", "nim": "2106123", "nilai": 88}
print(mhs["nama"])
mhs["nilai"] = 90
mhs["mk"] = "Web"
print(mhs)
print("nim" in mhs)
```

**Yang terjadi:**

- `mhs["nama"]` → `Haikal`.
- Nilai diubah jadi `90`, kunci baru `mk` ditambah.
- Output akhir: `{'nama': 'Haikal', 'nim': '2106123', 'nilai': 90, 'mk': 'Web'}`.
- `"nim" in mhs` mengecek kunci, bukan nilai → `True`.

**Biasanya digabungkan dengan:** `json`, `**kwargs`, dan `DataFrame` dari list of dict.

**Jangan:** `mhs["Nama"]` jika kuncinya `"nama"`. Kunci sensitif kapital. `KeyError` jika kunci tidak ada — pakai `get`.

## dict.get

**Tipe:** method `dict`

**Untuk apa:** mengambil nilai tanpa meledak jika kunci absen. Bisa kasih default.

**Contoh implementasi:**

```python
mhs = {"nama": "Haikal", "nilai": 88}
print(mhs.get("nama"))
print(mhs.get("ipk"))
print(mhs.get("ipk", 0.0))
```

**Yang terjadi:**

- `get("nama")` → `Haikal`.
- `get("ipk")` tanpa default → `None`.
- `get("ipk", 0.0)` → `0.0`.

**Biasanya digabungkan dengan:** JSON API yang field-nya kadang hilang, dan `or` untuk cadangan.

**Jangan:** mengira `get` menulis kunci baru. Untuk itu pakai `setdefault`.

## dict.keys

**Tipe:** method `dict`

**Untuk apa:** melihat semua kunci. Hasilnya view hidup: berubah jika dict berubah. Untuk list beku, bungkus `list(...)`.

**Contoh implementasi:**

```python
mhs = {"nama": "Haikal", "nilai": 88}
print(list(mhs.keys()))
print(list(mhs))
```

**Yang terjadi:**

- `keys()` → `['nama', 'nilai']`.
- Iterasi dict langsung juga berjalan di kunci, jadi `list(mhs)` sama.

**Biasanya digabungkan dengan:** `in`, loop `for kunci in mhs:`.

**Jangan:** mengindeks `mhs.keys()[0]` di Python 3. View bukan list. Bungkus `list` dulu.

## dict.values

**Tipe:** method `dict`

**Untuk apa:** melihat semua nilai, tanpa kunci.

**Contoh implementasi:**

```python
nilai = {"Web": 88, "Basis": 70, "Jaringan": 81}
print(list(nilai.values()))
print(sum(nilai.values()) / len(nilai))
```

**Yang terjadi:**

- Values: `[88, 70, 81]`.
- Rata-rata: `(88+70+81)/3` → `79.666...`.

**Biasanya digabungkan dengan:** `sum`, `max`, dan cek keanggotaan nilai (jarang; biasanya cek kunci).

**Jangan:** mengira urutan values acak di Python baru. Urutannya mengikuti kunci masuk, tapi jangan andalkan jika kode harus jalan di asumsi lama.

## dict.items

**Tipe:** method `dict`

**Untuk apa:** mengiterasi pasangan `(kunci, nilai)`. Ini loop dict yang paling sering kamu tulis.

**Contoh implementasi:**

```python
nilai = {"Web": 88, "Basis": 70}
for mk, n in nilai.items():
    print(f"{mk} = {n}")
```

**Yang terjadi:**

- Iterasi pertama: `mk="Web"`, `n=88` → cetak `Web = 88`.
- Iterasi kedua: `Basis = 70`.

**Biasanya digabungkan dengan:** f-string, list comprehension `[(k, v) for k, v in d.items() if v >= 80]`.

**Jangan:** `for mk, n in nilai:` — itu unpack string kunci menjadi dua huruf, atau error. Pakai `.items()`.

## dict.update

**Tipe:** method `dict`

**Untuk apa:** menimpa atau menambah banyak kunci sekaligus. Berguna menggabungkan default dengan data user.

**Contoh implementasi:**

```python
dasar = {"nilai": 0, "mk": "Web"}
baru = {"nilai": 88, "nim": "2106"}
dasar.update(baru)
print(dasar)
```

**Yang terjadi:**

- `nilai` ditimpa `88`.
- `nim` ditambah.
- `mk` tetap.
- Hasil: `{'nilai': 88, 'mk': 'Web', 'nim': '2106'}`.

**Biasanya digabungkan dengan:** `{**a, **b}` (dict baru), dan config JSON.

**Jangan:** mengira `update` mengembalikan dict baru. Ia mengubah di tempat dan mengembalikan `None`.

## dict.pop

**Tipe:** method `dict`

**Untuk apa:** mengambil nilai sekaligus menghapus kuncinya.

**Contoh implementasi:**

```python
mhs = {"nama": "Haikal", "nilai": 88, "tmp": 1}
tmp = mhs.pop("tmp")
print(tmp)
print(mhs)
print(mhs.pop("ipk", None))
```

**Yang terjadi:**

- `pop("tmp")` → `1`, kunci `tmp` hilang.
- Sisa: `{'nama': 'Haikal', 'nilai': 88}`.
- `pop("ipk", None)` kunci tidak ada, default `None` dikembalikan, tidak error.

**Biasanya digabungkan dengan:** membersihkan field sementara, dan `try/except KeyError` jika tanpa default.

**Jangan:** `pop` kunci absen tanpa default. `KeyError`.

## set

**Tipe:** tipe data bawaan (kumpulan unik tak berurut)

**Untuk apa:** membuang duplikat, cek keanggotaan cepat, irisan/gabungan himpunan. Tidak ada indeks `[0]`.

**Contoh implementasi:**

```python
angkatan = {21, 21, 22, 23, 22}
print(angkatan)
print(21 in angkatan)
print(set([80, 70, 80, 90]))
```

**Yang terjadi:**

- Duplikat hilang: `{21, 22, 23}` (urutan cetak bisa beda).
- `21 in angkatan` → `True`.
- `set([...])` dari list nilai → `{80, 70, 90}`.

**Biasanya digabungkan dengan:** `list` untuk kembali berurut, dan operasi `|` `&` `-`.

**Jangan:** `set([[1, 2]])`. List tidak hashable. Isi set harus immutable.

## set.add

**Tipe:** method `set`

**Untuk apa:** menambah satu anggota. Jika sudah ada, tidak terjadi apa-apa (bukan error).

**Contoh implementasi:**

```python
nim_hadir = {"2101", "2102"}
nim_hadir.add("2103")
nim_hadir.add("2101")
print(nim_hadir)
```

**Yang terjadi:**

- `"2103"` masuk.
- `"2101"` diabaikan karena sudah ada.
- Isi: `{'2101', '2102', '2103'}` (urutan tidak dijamin).

**Biasanya digabungkan dengan:** `remove`/`discard`, dan loop baca absensi.

**Jangan:** `add` banyak item sekaligus. Untuk itu `update({"2104", "2105"})`.

## set.union

**Tipe:** method `set` (juga operator `|`)

**Untuk apa:** menggabung dua himpunan tanpa duplikat. Tidak mengubah set asli jika memakai `union` / `|`.

**Contoh implementasi:**

```python
senin = {"Haikal", "Siti"}
rabu = {"Siti", "Budi"}
print(senin.union(rabu))
print(senin | rabu)
print(senin)
```

**Yang terjadi:**

- Gabungan: `{'Haikal', 'Siti', 'Budi'}`.
- `|` hasilnya sama.
- `senin` tetap `{'Haikal', 'Siti'}`.

**Biasanya digabungkan dengan:** `intersection`, `difference`, dan unique NIM dari beberapa kelas.

**Jangan:** `senin + rabu`. Set tidak mendukung `+`. Pakai `|`.

## set.intersection

**Tipe:** method `set` (juga operator `&`)

**Untuk apa:** mengambil anggota yang ada di kedua himpunan. “Siapa yang hadir di kedua hari?”

**Contoh implementasi:**

```python
senin = {"Haikal", "Siti", "Ana"}
rabu = {"Siti", "Budi", "Ana"}
print(senin.intersection(rabu))
print(senin & rabu)
print(senin - rabu)
```

**Yang terjadi:**

- Irisan: `{'Siti', 'Ana'}`.
- `&` sama.
- Selisih `senin - rabu`: yang hanya Senin → `{'Haikal'}`.

**Biasanya digabungkan dengan:** filter kehadiran, dan `len(irisan)` untuk hitung.

**Jangan:** membandingkan set dengan `==` lalu kaget urutan cetak berbeda. `==` pada set mengabaikan urutan.

## len

**Tipe:** fungsi bawaan

**Untuk apa:** menghitung jumlah item: karakter string, elemen list, kunci dict, anggota set. Tidak untuk menghitung “besar memori”.

**Contoh implementasi:**

```python
print(len("Web"))
print(len([80, 70, 90]))
print(len({"a": 1, "b": 2}))
print(len({1, 1, 2}))
```

**Yang terjadi:**

- String `"Web"` → `3`.
- List tiga nilai → `3`.
- Dict dua kunci → `2`.
- Set `{1, 1, 2}` hanya dua anggota → `2`.

**Biasanya digabungkan dengan:** `range(len(...))` (sering bisa diganti `enumerate`), dan cek kosong `if len(x) == 0`.

**Jangan:** `len(88)`. Angka tidak punya panjang. `TypeError`.

## range

**Tipe:** tipe data / konstruktor urutan lazy

**Untuk apa:** menghasilkan deret bilangan tanpa membuat list raksasa di memori. Bahan bakar `for` paling klasik.

**Contoh implementasi:**

```python
print(list(range(5)))
print(list(range(2, 7)))
print(list(range(0, 10, 2)))
print(list(range(5, 0, -1)))
```

**Yang terjadi:**

- `range(5)` → `0,1,2,3,4` (lima angka, tidak termasuk 5).
- `range(2, 7)` → `2,3,4,5,6`.
- Langkah 2: `0,2,4,6,8`.
- Mundur: `5,4,3,2,1`.

**Biasanya digabungkan dengan:** `for`, `enumerate`, `np.arange` (versi NumPy, hasil array).

**Jangan:** mengira `range(5)` memuat `5`. Pola batas kanan terbuka sama seperti slicing.

## isinstance

**Tipe:** fungsi bawaan

**Untuk apa:** cek tipe secara aman, termasuk pewarisan. Lebih disarankan daripada `type(x) is ...` karena `True` adalah instance `int` juga, dan subclass tetap lolos.

**Contoh implementasi:**

```python
print(isinstance(88, int))
print(isinstance(True, int))
print(isinstance(3.2, (int, float)))
print(isinstance("88", int))
```

**Yang terjadi:**

- `88` adalah `int` → `True`.
- `True` adalah subclass `int` → `True`.
- `3.2` cocok salah satu `(int, float)` → `True`.
- `"88"` string, bukan int → `False`.

**Biasanya digabungkan dengan:** validasi argumen fungsi, dan cabang konversi.

**Jangan:** `isinstance(x, type(list))` tanpa sadar. Untuk cek list: `isinstance(x, list)`.

## operator aritmetika

**Tipe:** operator bahasa (`+ - * /`)

**Untuk apa:** hitung biasa. `+` pada string/list berarti gabung, bukan jumlah matematika. Kenali tipenya dulu.

**Contoh implementasi:**

```python
print(10 + 3)
print(10 - 3)
print(10 * 3)
print(10 / 4)
print("ha" + "ikal")
print([1, 2] + [3])
print("na" * 3)
```

**Yang terjadi:**

- `13`, `7`, `30`.
- `10 / 4` → `2.5` (selalu float).
- String gabung: `haikal`.
- List gabung: `[1, 2, 3]`.
- `"na" * 3` → `nanana`.

**Biasanya digabungkan dengan:** `+=`, kurung untuk prioritas, NumPy (operasi per elemen).

**Jangan:** `"88" + 2`. `TypeError`. Konversi dulu: `int("88") + 2` atau `f"{88}{2}"`.

## pembagian // dan %

**Tipe:** operator bahasa

**Untuk apa:** `//` bagi lalu ambil utuh (floor division). `%` sisa bagi (modulo). Pasangan ini dipakai untuk pecah total menit, cek genap/ganjil, atau indeks berputar.

**Contoh implementasi:**

```python
print(17 // 5)
print(17 % 5)
print(17 / 5)
print(4 % 2 == 0)
menit = 130
print(menit // 60, "jam", menit % 60, "menit")
```

**Yang terjadi:**

- `17 // 5` → `3`.
- `17 % 5` → `2` karena `5*3 + 2 = 17`.
- `/` → `3.4`.
- `4 % 2 == 0` → `True` (genap).
- 130 menit = 2 jam 10 menit.

**Biasanya digabungkan dengan:** `divmod(17, 5)` yang mengembalikan `(3, 2)` sekaligus.

**Jangan:** memakai `%` pada float uang lalu mengira presisi persis. Untuk uang, hitung dalam rupiah `int`.

## pangkat **

**Tipe:** operator bahasa

**Untuk apa:** perpangkatan. `pow(a, b)` sama, `pow(a, b, m)` bisa modulo. Di NumPy, `**` bekerja per elemen.

**Contoh implementasi:**

```python
print(2 ** 10)
print(9 ** 0.5)
print(10 ** -2)
```

**Yang terjadi:**

- `2 ** 10` → `1024`.
- `9 ** 0.5` → `3.0` (akar, hasil float).
- `10 ** -2` → `0.01`.

**Biasanya digabungkan dengan:** `math.sqrt`, `math.pow`, NumPy.

**Jangan:** menulis `2 ^ 10` untuk pangkat. `^` adalah XOR bitwise, hasilnya `8`, bukan `1024`.

## perbandingan

**Tipe:** operator bahasa (`== != < > <= >=`)

**Untuk apa:** menghasilkan `bool`. Dipakai di `if`, loop, dan filter. Bisa dirantai: `70 <= n <= 100`.

**Contoh implementasi:**

```python
n = 88
print(n == 88)
print(n != 70)
print(70 <= n <= 100)
print("Ana" < "Budi")
print([1, 2] == [1, 2])
```

**Yang terjadi:**

- Sama nilai → `True`.
- Tidak sama 70 → `True`.
- Rantai: 88 di antara 70 dan 100 → `True`.
- String dibandingkan leksikografis: `Ana` sebelum `Budi` → `True`.
- List sama isi dan urutan → `True`.

**Biasanya digabungkan dengan:** `and`/`or`, mask pandas, `np.where`.

**Jangan:** `==` untuk float hasil hitungan panjang. Lihat catatan di entri `float`.

## and or not

**Tipe:** operator logika

**Untuk apa:** menggabungkan kondisi. `and`/`or` di Python mengembalikan **salah satu operand**, bukan selalu `True`/`False`. Itu sebabnya pola `nama = input() or "tamu"` jalan.

**Contoh implementasi:**

```python
nilai = 88
hadir = True
print(nilai >= 70 and hadir)
print(nilai >= 90 or hadir)
print(not hadir)
print("" or "cadangan")
print("isi" and "kedua")
```

**Yang terjadi:**

- Kedua benar → `True`.
- `or`: salah satu benar → `True`.
- `not True` → `False`.
- `"" or "cadangan"` → `"cadangan"` (operand kiri falsy).
- `"isi" and "kedua"` → `"kedua"` (kiri truthy, jadi kembalikan kanan).

**Biasanya digabungkan dengan:** `if`, ternary, filter.

**Jangan:** menulis `if 70 <= nilai <= 100 and nilai != None` tanpa `is`. Untuk None pakai `is not None`. Prioritas: `not` dulu, lalu `and`, lalu `or`. Pakai kurung jika ragu.

## in

**Tipe:** operator keanggotaan

**Untuk apa:** cek apakah item ada di urutan, atau kunci ada di dict, atau substring ada di string. Pada set/dict, cek ini cepat.

**Contoh implementasi:**

```python
mk = ["Web", "Basis", "Jaringan"]
print("Web" in mk)
print("AI" not in mk)
print("nim" in {"nama": "Haikal", "nim": "2106"})
print("Web" in "Pemrograman Web")
```

**Yang terjadi:**

- `"Web" in mk` → `True`.
- `"AI" not in mk` → `True`.
- `"nim" in dict` cek kunci → `True`.
- Substring `"Web"` ada di judul → `True`.

**Biasanya digabungkan dengan:** `if`, list comprehension, `str.find`.

**Jangan:** `'88' in [88]`. Tipe harus cocok. String `"88"` tidak sama dengan int `88`.

## is versus ==

**Tipe:** operator identitas vs kesetaraan

**Untuk apa:** `==` banding isi. `is` banding objek yang sama di memori. Pakai `is` terutama untuk `None`, `True`, `False`. Jangan pakai `is` untuk angka atau string hasil hitungan.

**Contoh implementasi:**

```python
a = [1, 2]
b = [1, 2]
c = a
print(a == b)
print(a is b)
print(a is c)
print(None is None)
```

**Yang terjadi:**

- `a == b` → `True` (isi sama).
- `a is b` → `False` (dua list berbeda).
- `c = a` menunjuk objek yang sama → `a is c` `True`.
- `None is None` → `True` (hanya ada satu `None`).

**Biasanya digabungkan dengan:** `None`, singleton, debug identitas.

**Jangan:** `if nilai is 88:`. Integer kecil kadang di-cache jadi kebetulan benar, lalu pecah di angka lain. Pakai `==`.

## unpacking

**Tipe:** sintaks assignment

**Untuk apa:** memecah urutan ke beberapa variabel dalam satu baris. Kelihatan di `for k, v in d.items()`, return fungsi, dan `*sisa`.

**Contoh implementasi:**

```python
nama, nilai = ("Haikal", 88)
print(nama, nilai)
depan, *tengah, belakang = [10, 20, 30, 40, 50]
print(depan, tengah, belakang)
x, y = 1, 2
x, y = y, x
print(x, y)
```

**Yang terjadi:**

- `nama="Haikal"`, `nilai=88`.
- `depan=10`, `tengah=[20, 30, 40]`, `belakang=50`.
- Tukar tanpa variabel ketiga: `x=2`, `y=1`.

**Biasanya digabungkan dengan:** `zip`, `enumerate`, `items()`, return banyak nilai.

**Jangan:** `a, b = [1, 2, 3]`. Jumlah kiri dan kanan harus cocok, atau pakai `*`.

## min max sum

**Tipe:** fungsi bawaan

**Untuk apa:** nilai terkecil, terbesar, dan jumlah. Bekerja pada list, tuple, set, generator. `sum` default awal `0`, jadi jangan `sum` list string.

**Contoh implementasi:**

```python
nilai = [80, 70, 90, 65]
print(min(nilai), max(nilai), sum(nilai))
print(sum(nilai) / len(nilai))
print(min("Web", "Basis", "AI"))
```

**Yang terjadi:**

- Min `65`, max `90`, jumlah `305`.
- Rata-rata `76.25`.
- `min` string memakai urutan kamus: `AI` (huruf A).

**Biasanya digabungkan dengan:** `len` untuk rata-rata, `key=`, NumPy `np.min` untuk array.

**Jangan:** `sum([])` sebenarnya `0` (aman), tapi `min([])` error. Cek kosong dulu.

## round

**Tipe:** fungsi bawaan

**Untuk apa:** membulatkan ke n digit. Default ke integer terdekat. Python memakai banker's rounding untuk `.5` persis (ke genap) — kadang mengejutkan.

**Contoh implementasi:**

```python
print(round(3.14159, 2))
print(round(2.5))
print(round(3.5))
print(round(88.765, 1))
```

**Yang terjadi:**

- Dua desimal: `3.14`.
- `2.5` → `2` (ke genap terdekat).
- `3.5` → `4` (4 genap).
- Satu desimal: `88.8`.

**Biasanya digabungkan dengan:** f-string `:.2f` (hanya tampilan), dan uang rupiah.

**Jangan:** mengira `round` memperbaiki semua error float. `round(1.335, 2)` bisa jadi `1.33` karena 1.335 tidak persis.

## abs

**Tipe:** fungsi bawaan

**Untuk apa:** nilai mutlak. Jarak dari nol. Berguna untuk selisih, toleransi float, dan error.

**Contoh implementasi:**

```python
print(abs(-7))
print(abs(3.2 - 3.2))
selisih = abs(80 - 88)
print(selisih)
```

**Yang terjadi:**

- `abs(-7)` → `7`.
- Selisih identik → `0.0`.
- Jarak 80 dan 88 → `8`.

**Biasanya digabungkan dengan:** perbandingan float, `math.hypot`, NumPy `np.abs`.

**Jangan:** `abs` untuk “buang tanda minus di teks”. `" -7 ".strip()` dulu, baru `abs(int(...))`.

## sorted

**Tipe:** fungsi bawaan

**Untuk apa:** mengembalikan **list baru** yang terurut. Asli tidak diubah. Beda dengan `list.sort`.

**Contoh implementasi:**

```python
nilai = [80, 70, 90]
print(sorted(nilai))
print(nilai)
print(sorted(nilai, reverse=True))
print(sorted(["Web", "ai", "Basis"], key=str.lower))
```

**Yang terjadi:**

- `sorted` → `[70, 80, 90]`.
- `nilai` tetap `[80, 70, 90]`.
- `reverse=True` → `[90, 80, 70]`.
- `key=str.lower` membuat `"ai"` di depan tanpa mengubah isi string.

**Biasanya digabungkan dengan:** `key=lambda`, `itemgetter`, dan `dict` (`sorted(d.items())`).

**Jangan:** mengira `sorted` mengembalikan tipe asal. `sorted((3, 1))` adalah **list** `[1, 3]`, bukan tuple.

## indexing

**Tipe:** sintaks urutan dan dict

**Untuk apa:** mengambil satu elemen. Urutan pakai angka dari 0. Dict pakai kunci. Indeks negatif menghitung dari belakang pada list/str/tuple.

**Contoh implementasi:**

```python
mk = ["Web", "Basis", "Jaringan"]
print(mk[0])
print(mk[-1])
mhs = {"nama": "Haikal"}
print(mhs["nama"])
```

**Yang terjadi:**

- `mk[0]` → `Web`.
- `mk[-1]` → `Jaringan`.
- `mhs["nama"]` → `Haikal`.

**Biasanya digabungkan dengan:** slicing, `get`, `loc`/`iloc` di pandas.

**Jangan:** `mk[3]` pada list tiga elemen. `IndexError`. Panjang 3 berarti indeks sah 0, 1, 2.

---

Bab berikutnya: cabang, loop, fungsi, dan modul di [02-kontrol-fungsi-modul.md](02-kontrol-fungsi-modul.md).
