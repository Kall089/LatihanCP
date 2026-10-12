# 02 — Kontrol alur, fungsi, dan modul

[← 01 Dasar](01-dasar-tipe-variabel.md) · [Indeks](README.md) · [Lanjut 03 →](03-file-pathlib-json-csv.md)

Setelah punya data, kamu memilih cabang, mengulang, lalu membungkus langkah jadi fungsi. Modul adalah file yang bisa diimpor. Bab ini tidak membahas NumPy/pandas; fondasinya di sini dulu.

## Daftar isi

- [if](#if)
- [elif else](#elif-else)
- [ternary](#ternary)
- [match case](#match-case)
- [for](#for)
- [while](#while)
- [break](#break)
- [continue](#continue)
- [else pada loop](#else-pada-loop)
- [pass](#pass)
- [enumerate](#enumerate)
- [zip](#zip)
- [list comprehension](#list-comprehension)
- [dict comprehension](#dict-comprehension)
- [set comprehension](#set-comprehension)
- [generator expression](#generator-expression)
- [def](#def)
- [return](#return)
- [parameter default](#parameter-default)
- [*args](#args)
- [**kwargs](#kwargs)
- [lambda](#lambda)
- [map](#map)
- [filter](#filter)
- [any](#any)
- [all](#all)
- [import](#import)
- [from import](#from-import)
- [as alias](#as-alias)
- [if __name__](#if-__name__)
- [try except finally](#try-except-finally)
- [raise](#raise)
- [with](#with)
- [class](#class)
- [__init__](#__init__)
- [method](#method)
- [yield](#yield)
- [decorator sederhana](#decorator-sederhana)

## if

**Tipe:** pernyataan kontrol

**Untuk apa:** menjalankan blok hanya jika kondisi benar. Indentasi (spasi di depan) menentukan blok, bukan kurung kurawal. Satu `if` bisa berdiri sendiri tanpa `else`.

**Contoh implementasi:**

```python
nilai = 88
if nilai >= 70:
    print("lulus")
    print("nilai cukup")
print("selalu tercetak")
```

**Yang terjadi:**

- `88 >= 70` benar, jadi dua `print` di dalam `if` jalan: `lulus` lalu `nilai cukup`.
- `print` terakhir tidak menjorok, jadi selalu jalan.

**Biasanya digabungkan dengan:** `elif`/`else`, `and`/`or`, dan fungsi yang mengembalikan `bool`.

**Jangan:** lupa indentasi. `IndentationError` atau, lebih jahat, `print` yang kamu kira di dalam `if` ternyata di luar.

## elif else

**Tipe:** cabang lanjutan dari `if`

**Untuk apa:** memilih satu dari beberapa jalur. Python mengecek dari atas; cabang pertama yang benar dijalankan, sisanya dilewati. `else` menampung sisanya.

**Contoh implementasi:**

```python
nilai = 72
if nilai >= 85:
    predikat = "A"
elif nilai >= 70:
    predikat = "B"
elif nilai >= 60:
    predikat = "C"
else:
    predikat = "ulang"
print(predikat)
```

**Yang terjadi:**

- 72 tidak `>= 85`, lanjut.
- 72 `>= 70`, `predikat = "B"`, cabang bawah tidak dicek.
- Output: `B`.

**Biasanya digabungkan dengan:** fungsi `predikat(nilai)`, dan `dict` pemetaan jika banyak kasus datar.

**Jangan:** menulis `if` terpisah untuk rentang yang saling menimpa. `if nilai >= 70` setelah `if nilai >= 85` akan menimpa A jadi B. Pakai `elif`.

## ternary

**Tipe:** ekspresi kondisional

**Untuk apa:** memilih satu dari dua nilai dalam satu ekspresi. Enak di `return`, f-string, dan list comprehension. Jangan dirantai bertingkat sampai tidak terbaca.

**Contoh implementasi:**

```python
nilai = 88
status = "lulus" if nilai >= 70 else "ulang"
print(status)
print(f"hasil: {'A' if nilai >= 85 else 'bukan A'}")
```

**Yang terjadi:**

- Kondisi benar → `status` adalah `lulus`.
- f-string memakai ternary kedua: 88 ≥ 85 → `hasil: A`.

**Biasanya digabungkan dengan:** `return`, `print`, dict assignment.

**Jangan:** menaruh pernyataan `print` di dalam ternary. Ternary harus menghasilkan nilai, bukan menjalankan blok.

## match case

**Tipe:** pernyataan kontrol (Python 3.10+)

**Untuk apa:** membandingkan satu nilai ke beberapa pola. Lebih rapi daripada `if/elif` panjang untuk status HTTP, kode huruf, atau struktur tuple. Bukan `switch` C yang “jatuh” ke case berikutnya.

**Contoh implementasi:**

```python
kode = "B"
match kode:
    case "A":
        print("sangat baik")
    case "B" | "C":
        print("lulus")
    case _:
        print("perlu cek")
```

**Yang terjadi:**

- `kode` cocok `"B" | "C"` → cetak `lulus`.
- `_` adalah pola “sisanya”, tidak jadi dijalankan di contoh ini.

**Biasanya digabungkan dengan:** status `requests`, tuple `(jenis, nilai)`, dan Python 3.10 ke atas.

**Jangan:** memakai `match` di Python 3.9. `SyntaxError`. Cek `python3 --version`.

## for

**Tipe:** loop

**Untuk apa:** mengunjungi setiap item di iterable: list, string, dict, `range`, baris file. Ini loop default di Python. Jarang sekali kamu butuh indeks manual.

**Contoh implementasi:**

```python
mk = ["Web", "Basis", "Jaringan"]
for nama in mk:
    print("ambil", nama)

for i in range(3):
    print("i =", i)
```

**Yang terjadi:**

- Tiga iterasi: `ambil Web`, `ambil Basis`, `ambil Jaringan`.
- `range(3)` → `i = 0`, `i = 1`, `i = 2`.

**Biasanya digabungkan dengan:** `enumerate`, `zip`, `break`, list comprehension.

**Jangan:** `for i in range(len(mk)): print(mk[i])` jika kamu hanya butuh item. Langsung `for nama in mk`.

## while

**Tipe:** loop bersyarat

**Untuk apa:** mengulang selama kondisi benar, saat jumlah putaran tidak diketahui di awal: baca input sampai valid, proses antrian, polling. Mudah jadi loop abadi jika kondisi tidak pernah false.

**Contoh implementasi:**

```python
sisa = 3
while sisa > 0:
    print("nyawa", sisa)
    sisa -= 1
print("habis")
```

**Yang terjadi:**

- Mulai `sisa=3` → cetak `nyawa 3`, lalu 2, lalu 1.
- Setelah `sisa` jadi 0, kondisi gagal, cetak `habis`.

**Biasanya digabungkan dengan:** `break` sebagai pintu keluar, dan `input()` di tugas interaktif.

**Jangan:** lupa memperbarui variabel kondisi. `while True:` tanpa `break` merokok di CPU.

## break

**Tipe:** pernyataan loop

**Untuk apa:** keluar dari loop terdalam sekarang juga. Cocok saat item sudah ketemu dan sisa daftar tidak relevan.

**Contoh implementasi:**

```python
nilai = [60, 70, 88, 90]
ketemu = None
for n in nilai:
    if n >= 85:
        ketemu = n
        break
print("pertama >= 85:", ketemu)
```

**Yang terjadi:**

- 60 dan 70 dilewati.
- 88 memenuhi, disimpan, `break`.
- 90 tidak sempat dicek.
- Output: `pertama >= 85: 88`.

**Biasanya digabungkan dengan:** `else` pada loop, `while True`.

**Jangan:** mengira `break` keluar dari dua loop bersarang. Ia hanya memutus yang paling dalam. Untuk dua tingkat, pakai fungsi + `return` atau bendera.

## continue

**Tipe:** pernyataan loop

**Untuk apa:** lompat ke iterasi berikutnya, melewati sisa blok. Enak untuk “kalau data jelek, skip”.

**Contoh implementasi:**

```python
nilai = [80, None, 70, -1, 90]
bersih = []
for n in nilai:
    if n is None or n < 0:
        continue
    bersih.append(n)
print(bersih)
```

**Yang terjadi:**

- `80` lolos → masuk list.
- `None` dan `-1` di-skip.
- `70` dan `90` masuk.
- Hasil: `[80, 70, 90]`.

**Biasanya digabungkan dengan:** validasi, baca file baris kosong, filter kasar sebelum pandas.

**Jangan:** `continue` di luar loop. `SyntaxError`.

## else pada loop

**Tipe:** klausa loop (bukan else-if)

**Untuk apa:** blok `else` pada `for`/`while` jalan **jika loop tidak di-`break`**. Artinya “selesai normal, tidak ada yang ketemu lalu dipotong”. Nama `else` memang membingungkan; anggap “if no break”.

**Contoh implementasi:**

```python
kode = ["A3", "B1", "C2"]
cari = "B9"
for x in kode:
    if x == cari:
        print("ketemu")
        break
else:
    print("tidak ada", cari)
```

**Yang terjadi:**

- Tidak ada `"B9"`, loop habis tanpa `break`.
- `else` jalan → `tidak ada B9`.

**Biasanya digabungkan dengan:** pencarian, `break`.

**Jangan:** mengira `else` jalan ketika kondisi loop false di iterasi pertama `for`. Pada `for`, `else` jalan setelah iterable habis, kecuali ada `break`.

## pass

**Tipe:** pernyataan kosong

**Untuk apa:** mengisi blok yang wajib ada secara sintaks, tetapi isinya belum ditulis. `if`, `def`, `class`, `except` tidak boleh kosong.

**Contoh implementasi:**

```python
nilai = 40
if nilai < 70:
    pass  # nanti kirim email
print("lanjut")

def todo_nanti():
    pass

print(todo_nanti())
```

**Yang terjadi:**

- `if` tidak melakukan apa-apa, program tidak error.
- `lanjut` tercetak.
- Fungsi `todo_nanti` mengembalikan `None`.

**Biasanya digabungkan dengan:** kerangka class, `except` yang sengaja menelan (hati-hati), dan TODO.

**Jangan:** meninggalkan `except: pass` di produksi. Error tertelan, bug menghilang tanpa jejak.

## enumerate

**Tipe:** fungsi bawaan

**Untuk apa:** memberi pasangan `(indeks, item)` saat loop. Menggantikan `range(len(...))` yang berisik.

**Contoh implementasi:**

```python
mk = ["Web", "Basis", "Jaringan"]
for i, nama in enumerate(mk):
    print(i, nama)
print(list(enumerate(mk, start=1)))
```

**Yang terjadi:**

- Cetak `0 Web`, `1 Basis`, `2 Jaringan`.
- `start=1` membuat indeks manusia: `[(1, 'Web'), (2, 'Basis'), (3, 'Jaringan')]`.

**Biasanya digabungkan dengan:** `for`, tulis nomor baris, dan `dict(enumerate(...))`.

**Jangan:** `for i, nama in mk:` pada list string. String di-unpack jadi huruf. Pakai `enumerate`.

## zip

**Tipe:** fungsi bawaan

**Untuk apa:** menggabungkan beberapa iterable secara sejajar, berhenti di yang terpendek. Enak merakit dict atau loop dua list.

**Contoh implementasi:**

```python
nama = ["Haikal", "Siti", "Budi"]
nilai = [88, 70, 91]
print(list(zip(nama, nilai)))
for n, v in zip(nama, nilai):
    print(f"{n} = {v}")
print(dict(zip(nama, nilai)))
```

**Yang terjadi:**

- `zip` → `[('Haikal', 88), ('Siti', 70), ('Budi', 91)]`.
- Loop mencetak tiga baris `nama = nilai`.
- `dict(zip(...))` → `{'Haikal': 88, 'Siti': 70, 'Budi': 91}`.

**Biasanya digabungkan dengan:** `enumerate`, unpacking, `itertools.zip_longest` jika panjang beda dan ingin isi cadangan.

**Jangan:** mengira `zip` memotong diam-diam itu selalu aman. Kalau satu list lebih pendek, sisa data hilang tanpa error.

## list comprehension

**Tipe:** ekspresi (sintaks list)

**Untuk apa:** membuat list baru dari iterable, sering sekaligus filter. Lebih padat daripada `for` + `append`. Tetaplah pendek; kalau butuh 5 baris logika, pakai loop biasa.

**Contoh implementasi:**

```python
nilai = [60, 75, 88, 40, 90]
lulus = [n for n in nilai if n >= 70]
huruf = [f"n={n}" for n in lulus]
kuadrat = [n * n for n in range(5)]
print(lulus)
print(huruf)
print(kuadrat)
```

**Yang terjadi:**

- Filter: `[75, 88, 90]`.
- Transform: `['n=75', 'n=88', 'n=90']`.
- `range(5)` dikuadratkan: `[0, 1, 4, 9, 16]`.

**Biasanya digabungkan dengan:** `zip`, `enumerate`, `str` method, dan (hati-hati) comprehension bersarang.

**Jangan:** menaruh `print` di dalam comprehension untuk “melihat proses”. Kamu membuat list berisi `None`.

## dict comprehension

**Tipe:** ekspresi (sintaks dict)

**Untuk apa:** merakit dict baru dalam satu baris: kunci dan nilai dihitung dari iterable.

**Contoh implementasi:**

```python
mk = ["Web", "Basis", "Jaringan"]
panjang = {nama: len(nama) for nama in mk}
naik = {k: v + 5 for k, v in {"Web": 80, "Basis": 70}.items() if v < 85}
print(panjang)
print(naik)
```

**Yang terjadi:**

- `panjang` → `{'Web': 3, 'Basis': 5, 'Jaringan': 8}`.
- Hanya `"Basis": 70` yang `< 85`, jadi ditambah 5 → `{'Basis': 75}`.

**Biasanya digabungkan dengan:** `zip`, `json`, dan normalisasi data.

**Jangan:** kunci duplikat. Kunci yang sama menimpa diam-diam, bukan error.

## set comprehension

**Tipe:** ekspresi (sintaks set)

**Untuk apa:** himpunan hasil transform/filter, otomatis unik.

**Contoh implementasi:**

```python
nilai = [80, 81, 80, 90, 91]
puluhan = {n // 10 * 10 for n in nilai}
print(puluhan)
```

**Yang terjadi:**

- 80 dan 81 jadi 80, 90 dan 91 jadi 90.
- Set: `{80, 90}` (urutan cetak bebas).

**Biasanya digabungkan dengan:** `in` cepat, unique kode, irisan.

**Jangan:** `{x for x in ...}` lalu mengandalkan urutan saat diubah ke list. Urutkan sendiri dengan `sorted`.

## generator expression

**Tipe:** ekspresi lazy

**Untuk apa:** seperti list comprehension tapi tidak membuat list di memori. Dipakai sekali. Enak untuk `sum`, `any`, `all` pada data besar.

**Contoh implementasi:**

```python
nilai = [80, 70, 90]
gen = (n * 2 for n in nilai)
print(gen)
print(sum(gen))
print(sum(n * 2 for n in nilai))
```

**Yang terjadi:**

- `print(gen)` menampilkan objek generator, bukan angka.
- `sum(gen)` → `80*2 + 70*2 + 90*2 = 480`, generator habis.
- Bentuk kedua (tanpa variabel) adalah pola idiomatik untuk `sum`.

**Biasanya digabungkan dengan:** `sum`, `any`, `max`, baca file baris per baris.

**Jangan:** mengiterasi generator dua kali. Putaran kedua kosong.

## def

**Tipe:** pernyataan (deklarasi fungsi)

**Untuk apa:** menamai potongan langkah yang bisa dipanggil ulang. Argumen masuk, kerja di dalam, hasil keluar lewat `return`. Fungsi tanpa `return` mengembalikan `None`.

**Contoh implementasi:**

```python
def rata2(daftar):
    return sum(daftar) / len(daftar)

print(rata2([80, 70, 90]))
print(rata2)
```

**Yang terjadi:**

- Pemanggilan menghitung `(80+70+90)/3` → `80.0`.
- `print(rata2)` tanpa `()` menampilkan objek fungsi, bukan hasil hitung.

**Biasanya digabungkan dengan:** `return`, docstring, type hint, `if __name__`.

**Jangan:** menaruh `def` di dalam loop tanpa alasan. Definisikan sekali, panggil berkali.

## return

**Tipe:** pernyataan fungsi

**Untuk apa:** mengirim nilai kembali ke pemanggil dan **langsung keluar** dari fungsi. Bisa mengembalikan banyak nilai (sebenarnya satu tuple).

**Contoh implementasi:**

```python
def minmax(daftar):
    return min(daftar), max(daftar)

pasangan = minmax([80, 70, 90])
kecil, besar = minmax([80, 70, 90])
print(pasangan)
print(kecil, besar)

def awal(n):
    if n < 0:
        return None
    return n * 2

print(awal(-3), awal(4))
```

**Yang terjadi:**

- `pasangan` adalah tuple `(70, 90)`.
- Unpacking: `kecil=70`, `besar=90`.
- `awal(-3)` kena `return None` lebih dulu → `None`.
- `awal(4)` → `8`.

**Biasanya digabungkan dengan:** unpacking, `if` penjaga di awal fungsi (early return).

**Jangan:** menulis kode setelah `return` di cabang yang sama. Mati, tidak pernah jalan.

## parameter default

**Tipe:** fitur fungsi

**Untuk apa:** membuat argumen opsional. Pemanggil boleh mengirim, boleh tidak. Default dievaluasi **sekali** saat `def`, bukan setiap panggilan — itu jebakan list kosong.

**Contoh implementasi:**

```python
def sapaan(nama, gelar="mahasiswa"):
    return f"Halo {gelar} {nama}"

print(sapaan("Haikal"))
print(sapaan("Haikal", gelar="asisten"))
```

**Yang terjadi:**

- Tanpa `gelar`: `Halo mahasiswa Haikal`.
- Dengan keyword: `Halo asisten Haikal`.

**Biasanya digabungkan dengan:** `None` sebagai default untuk list/dict yang nanti diisi di dalam fungsi.

**Jangan:** `def tambah(item, wadah=[]):`. List default dipakai bersama semua panggilan. Tulis `wadah=None` lalu `if wadah is None: wadah = []`.

## *args

**Tipe:** parameter variadik posisi

**Untuk apa:** menerima sisa argumen posisi sebagai tuple. Berguna untuk pembungkus, `print`-like, atau jumlah input tidak tetap.

**Contoh implementasi:**

```python
def jumlah(*angka):
    print("args:", angka)
    return sum(angka)

print(jumlah(1, 2, 3))
print(jumlah())
```

**Yang terjadi:**

- `angka` adalah `(1, 2, 3)`, jumlah `6`.
- Tanpa argumen, tuple kosong, `sum` → `0`.

**Biasanya digabungkan dengan:** `**kwargs`, unpacking panggilan `f(*daftar)`.

**Jangan:** menaruh `*args` sebelum parameter wajib tanpa desain. Parameter setelah `*args` harus dipanggil sebagai keyword.

## **kwargs

**Tipe:** parameter variadik kata kunci

**Untuk apa:** menerima sisa argumen bernama sebagai dict. Sering di API wrapper, opsi plot, dan super().__init__.

**Contoh implementasi:**

```python
def buat_mhs(nama, **lain):
    data = {"nama": nama}
    data.update(lain)
    return data

print(buat_mhs("Haikal", nim="2106", nilai=88))
```

**Yang terjadi:**

- `lain` adalah `{'nim': '2106', 'nilai': 88}`.
- Digabung ke `data` → `{'nama': 'Haikal', 'nim': '2106', 'nilai': 88}`.

**Biasanya digabungkan dengan:** `dict.update`, matplotlib `ax.plot(..., **opsi)`, pandas.

**Jangan:** nama parameter bentrok. `def f(nama, **kwargs)` lalu panggil `f(nama="A", nama="B")` tidak sah.

## lambda

**Tipe:** ekspresi fungsi anonim

**Untuk apa:** fungsi pendek sekali pakai, biasanya sebagai `key` di `sorted` atau `key` di `min`. Tidak bisa berisi pernyataan, hanya satu ekspresi.

**Contoh implementasi:**

```python
pasangan = [("Web", 88), ("Basis", 70), ("AI", 91)]
print(sorted(pasangan, key=lambda x: x[1]))
naik = lambda n: n + 5
print(naik(80))
```

**Yang terjadi:**

- `sorted` memakai nilai (indeks 1): Basis 70, Web 88, AI 91.
- `naik(80)` → `85`.

**Biasanya digabungkan dengan:** `sorted`, `map`, `filter`, `apply` pandas (sering lebih jelas pakai `def`).

**Jangan:** menaruh lambda rumit di production. Kalau butuh nama dan dua baris, tulis `def`.

## map

**Tipe:** fungsi bawaan

**Untuk apa:** menerapkan fungsi ke setiap item, lazy. Di kode modern, list comprehension lebih sering dipilih karena lebih mudah dibaca.

**Contoh implementasi:**

```python
teks = ["80", "70", "90"]
angka = list(map(int, teks))
print(angka)
print(list(map(lambda n: n + 1, angka)))
```

**Yang terjadi:**

- `map(int, teks)` mengubah tiap string jadi int: `[80, 70, 90]`.
- Lambda menambah 1: `[81, 71, 91]`.
- Tanpa `list(...)`, kamu hanya punya objek `map`.

**Biasanya digabungkan dengan:** `int`, `str`, `filter`.

**Jangan:** mengira `map` sudah list. `print(map(...))` tidak menampilkan angka.

## filter

**Tipe:** fungsi bawaan

**Untuk apa:** menyaring item yang fungsi pen<jaga-nya truthy. Juga lazy. Comprehension `if` biasanya lebih jelas.

**Contoh implementasi:**

```python
nilai = [60, 75, 40, 90]
print(list(filter(lambda n: n >= 70, nilai)))
print([n for n in nilai if n >= 70])
```

**Yang terjadi:**

- Keduanya menghasilkan `[75, 90]`.
- Bentuk comprehension lebih gamblang untuk teman yang baca kodemu.

**Biasanya digabungkan dengan:** `map`, `None` sebagai fungsi (`filter(None, daftar)` membuang falsy).

**Jangan:** `filter` tanpa dibungkus `list` lalu kaget hasilnya “hilang” setelah diiterasi sekali.

## any

**Tipe:** fungsi bawaan

**Untuk apa:** `True` jika **minimal satu** elemen truthy. Berhenti di elemen pertama yang benar (short-circuit).

**Contoh implementasi:**

```python
nilai = [60, 55, 90]
print(any(n >= 85 for n in nilai))
print(any([]))
print(any([0, "", None]))
```

**Yang terjadi:**

- Ada 90 ≥ 85 → `True`.
- Iterable kosong → `False`.
- Semua falsy → `False`.

**Biasanya digabungkan dengan:** generator expression, validasi “ada yang kosong?”, NumPy `np.any`.

**Jangan:** `any(nilai >= 85)` pada list. Itu membandingkan list vs int, error atau makna aneh. Pakai generator di dalam.

## all

**Tipe:** fungsi bawaan

**Untuk apa:** `True` jika **semua** elemen truthy. Iterable kosong dianggap `True` (dari logika: tidak ada yang palsu).

**Contoh implementasi:**

```python
nilai = [80, 70, 90]
print(all(n >= 70 for n in nilai))
print(all(n >= 80 for n in nilai))
print(all([]))
```

**Yang terjadi:**

- Semua ≥ 70 → `True`.
- 70 tidak ≥ 80 → `False`.
- `all([])` → `True`.

**Biasanya digabungkan dengan:** validasi form, `isinstance` beruntun.

**Jangan:** mengandalkan `all([])` tanpa sadar. Loop kosong “lulus” semua syarat.

## import

**Tipe:** pernyataan modul

**Untuk apa:** memuat pustaka atau file `.py` lain. Nama setelah `import` jadi namespace: `math.sqrt`, bukan `sqrt` telanjang (kecuali `from`).

**Contoh implementasi:**

```python
import math
import json

print(math.sqrt(9))
print(math.pi)
print(json.dumps({"nilai": 88}))
```

**Yang terjadi:**

- `math.sqrt(9)` → `3.0`.
- `math.pi` ≈ `3.14159...`.
- `json.dumps` menghasilkan string `'{"nilai": 88}'`.

**Biasanya digabungkan dengan:** `as`, `from`, venv + pip.

**Jangan:** `import` di tengah fungsi berulang-ulang tanpa alasan (boleh kadang untuk hindari siklus, tapi bukan default). Letakkan di atas file.

## from import

**Tipe:** pernyataan modul

**Untuk apa:** menarik nama tertentu ke namespace lokal supaya tidak menulis prefiks. Enak untuk beberapa nama; berbahaya jika `from modul import *`.

**Contoh implementasi:**

```python
from math import sqrt, pi
from pathlib import Path

print(sqrt(16), pi)
print(Path("data") / "nilai.csv")
```

**Yang terjadi:**

- `sqrt(16)` → `4.0`, `pi` tercetak.
- `Path("data") / "nilai.csv"` → `data/nilai.csv` (objek Path).

**Biasanya digabungkan dengan:** `Path`, `datetime`, fungsi yang dipanggil berkali.

**Jangan:** `from math import *`. Nama `sum` atau `pow` bisa tertimpa tanpa kamu sadari.

## as alias

**Tipe:** klausa import

**Untuk apa:** menyingkat nama modul yang panjang atau mengikuti konvensi komunitas. `np`, `pd`, `plt`, `sns` hampir selalu ditulis begitu di tutorial data.

**Contoh implementasi:**

```python
import datetime as dt
import json as js

print(dt.date(2026, 9, 22))
print(js.dumps([1, 2]))
```

**Yang terjadi:**

- `dt.date(...)` → `2026-09-22`.
- `js.dumps` → `'[1, 2]'`.

**Biasanya digabungkan dengan:** `import numpy as np`, `import pandas as pd` (file 04–08).

**Jangan:** alias acak (`import pandas as pisang`) di tugas kelompok. Temanmu akan marah.

## if __name__

**Tipe:** idiom modul

**Untuk apa:** membedakan “file dijalankan langsung” vs “file diimpor”. Saat dijalankan langsung, `__name__` adalah `"__main__"`. Saat diimpor, `__name__` adalah nama modul. Taruh demo/tes di dalam blok ini.

**Contoh implementasi:**

```python
def rata2(daftar):
    return sum(daftar) / len(daftar)

if __name__ == "__main__":
    print("jalankan langsung")
    print(rata2([80, 70, 90]))
```

**Yang terjadi:**

- Jika `python file_ini.py`: kedua `print` jalan, rata-rata `80.0`.
- Jika file di-`import` dari file lain: fungsi terdefinisi, `print` tidak jalan.

**Biasanya digabungkan dengan:** `argparse`, skrip CLI, tes cepat.

**Jangan:** menaruh kode efek samping (hapus file, request jaringan) di level modul tanpa penjaga ini.

## try except finally

**Tipe:** penanganan eksepsi

**Untuk apa:** menangkap error yang bisa dipulihkan: file tidak ada, teks bukan angka, jaringan gagal. `finally` selalu jalan, ada error atau tidak — cocok tutup resource jika tidak pakai `with`.

**Contoh implementasi:**

```python
teks = "delapan"
try:
    angka = int(teks)
except ValueError as e:
    print("bukan angka:", e)
    angka = None
finally:
    print("selesai coba")
print("angka =", angka)
```

**Yang terjadi:**

- `int("delapan")` melempar `ValueError`.
- `except` mencetak pesan, `angka = None`.
- `finally` tetap mencetak `selesai coba`.
- Output terakhir: `angka = None`.

**Biasanya digabungkan dengan:** `raise`, `with`, `requests` timeout, baca file.

**Jangan:** `except:` atau `except Exception:` kosong yang menelan semua. Minimal cetak / log, atau tangkap tipe spesifik.

## raise

**Tipe:** pernyataan

**Untuk apa:** melempar error sendiri saat argumen tidak masuk akal. Lebih baik gagal cepat daripada hasil sampah.

**Contoh implementasi:**

```python
def rata2(daftar):
    if not daftar:
        raise ValueError("daftar nilai kosong")
    return sum(daftar) / len(daftar)

try:
    print(rata2([]))
except ValueError as e:
    print("tertangkap:", e)
```

**Yang terjadi:**

- Daftar kosong memicu `ValueError`.
- `except` menangkap → `tertangkap: daftar nilai kosong`.

**Biasanya digabungkan dengan:** validasi fungsi, `try`, class exception sendiri.

**Jangan:** `raise "pesan"`. Harus instance Exception: `raise ValueError("pesan")`.

## with

**Tipe:** context manager

**Untuk apa:** menyiapkan resource lalu menjamin pembersihan (tutup file, lepas kunci) meski ada error di tengah. Pola wajib untuk `open`.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_with.txt")
with path.open("w", encoding="utf-8") as f:
    f.write("halo kuliah\n")
print("tertutup?", f.closed)
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- File ditulis `halo kuliah` plus newline.
- Setelah blok `with`, `f.closed` → `True`.
- `read_text` membaca isi yang sama.
- `unlink` menghapus file percobaan.

**Biasanya digabungkan dengan:** `open`, `Path.open`, koneksi (di luar bab ini).

**Jangan:** `f = open(...)` lalu lupa `close()`, apalagi jika error muncul sebelum `close`.

## class

**Tipe:** pernyataan (definisi tipe)

**Untuk apa:** menggabungkan data dan perilaku. Di analisis data harian kamu lebih sering pakai class orang lain (`DataFrame`). Tetap perlu mengerti cara membuat yang sederhana.

**Contoh implementasi:**

```python
class Mahasiswa:
    jenjang = "S1"

    def deskripsi(self):
        return f"mahasiswa {self.jenjang}"

print(Mahasiswa.jenjang)
m = Mahasiswa()
print(m.deskripsi())
print(type(m))
```

**Yang terjadi:**

- `jenjang` adalah atribut class, dibagi semua instance: `S1`.
- `m.deskripsi()` → `mahasiswa S1`.
- `type(m)` → `<class '__main__.Mahasiswa'>`.

**Biasanya digabungkan dengan:** `__init__`, method, inheritance (tidak dibahas panjang di sini).

**Jangan:** lupa `self` sebagai parameter pertama method. `TypeError` saat dipanggil.

## __init__

**Tipe:** method khusus (konstruktor)

**Untuk apa:** mengisi data awal instance saat `NamaKelas(...)`. Bukan wajib, tapi hampir selalu ada jika objek punya state.

**Contoh implementasi:**

```python
class Nilai:
    def __init__(self, nama, angka):
        self.nama = nama
        self.angka = angka

    def lulus(self):
        return self.angka >= 70

n = Nilai("Haikal", 88)
print(n.nama, n.angka, n.lulus())
```

**Yang terjadi:**

- `Nilai("Haikal", 88)` memanggil `__init__`, mengisi atribut.
- `lulus()` memakai `self.angka` → `True`.
- Output: `Haikal 88 True`.

**Biasanya digabungkan dengan:** method lain, `dataclass` (ringkas, tidak wajib di sini).

**Jangan:** `return` nilai dari `__init__`. `__init__` harus `None`. Kalau ingin factory, tulis method `@classmethod`.

## method

**Tipe:** fungsi di dalam class

**Untuk apa:** perilaku yang menempel pada objek. Parameter pertama `self` adalah instance pemanggil. Dipanggil `objek.nama()`.

**Contoh implementasi:**

```python
class Antrian:
    def __init__(self):
        self.isi = []

    def masuk(self, nama):
        self.isi.append(nama)

    def keluar(self):
        return self.isi.pop(0)

q = Antrian()
q.masuk("Ana")
q.masuk("Budi")
print(q.keluar())
print(q.isi)
```

**Yang terjadi:**

- Dua nama masuk list.
- `keluar` mengambil depan: `Ana`.
- Sisa: `['Budi']`.

**Biasanya digabungkan dengan:** `__init__`, `@staticmethod` untuk fungsi tanpa `self` (jarang perlu di awal).

**Jangan:** memanggil method class tanpa instance jika butuh `self`: `Antrian.keluar()` error.

## yield

**Tipe:** pernyataan generator

**Untuk apa:** menghasilkan nilai satu per satu, menangguhkan fungsi. Memori hemat untuk deret panjang. Fungsi yang berisi `yield` mengembalikan generator, bukan menjalankan tubuhnya langsung.

**Contoh implementasi:**

```python
def hitung(n):
    for i in range(n):
        yield i * i

g = hitung(4)
print(g)
print(list(g))
```

**Yang terjadi:**

- `g` adalah objek generator.
- `list(g)` menarik semua: `[0, 1, 4, 9]`.

**Biasanya digabungkan dengan:** `for`, `next()`, baca file besar.

**Jangan:** mencampur `return` nilai bermakna dengan `yield` tanpa paham: `return` di generator menandai selesai (`StopIteration`).

## decorator sederhana

**Tipe:** pola fungsi (higher-order)

**Untuk apa:** membungkus fungsi lain tanpa mengubah cara panggil. `@nama` setara `fungsi = nama(fungsi)`. Di data, kamu lebih sering memakai decorator orang lain (`@app.get`). Ini versi telanjang.

**Contoh implementasi:**

```python
def jejak(fn):
    def pembungkus(*args, **kwargs):
        print("panggil", fn.__name__)
        return fn(*args, **kwargs)
    return pembungkus

@jejak
def rata2(daftar):
    return sum(daftar) / len(daftar)

print(rata2([80, 70, 90]))
```

**Yang terjadi:**

- `@jejak` membungkus `rata2`.
- Saat dipanggil, cetak `panggil rata2` dulu.
- Baru hasil `80.0`.

**Biasanya digabungkan dengan:** `functools.wraps`, framework web (di luar stack ini).

**Jangan:** lupa mengembalikan hasil `fn(...)`. Kalau `pembungkus` tidak `return`, fungsi asli seolah selalu `None`.

---

Lanjut ke file, path, JSON, dan CSV di [03-file-pathlib-json-csv.md](03-file-pathlib-json-csv.md).
