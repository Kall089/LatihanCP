# 03 — File, pathlib, JSON, dan CSV

[← 02 Kontrol](02-kontrol-fungsi-modul.md) · [Indeks](README.md) · [Lanjut 04 →](04-numpy-array-tipe.md)

Tugas data hampir selalu mulai dari file: teks, JSON dari API, CSV dari Excel. Bab ini memakai pustaka bawaan. Pandas `read_csv` ada di file 06; fondasi mentahnya di sini supaya kamu tahu apa yang terjadi di bawah.

Contoh menulis file kecil diawali garis bawah (`_contoh_...`) lalu dihapus di akhir skrip supaya folder tidak kotor. Jalankan dari folder yang boleh ditulis.

## Daftar isi

- [open](#open)
- [read](#read)
- [readline](#readline)
- [readlines](#readlines)
- [write](#write)
- [append mode](#append-mode)
- [with open](#with-open)
- [encoding](#encoding)
- [Path](#path)
- [operator / Path](#operator--path)
- [Path.exists](#pathexists)
- [Path.is_file](#pathis_file)
- [Path.mkdir](#pathmkdir)
- [Path.read_text](#pathread_text)
- [Path.write_text](#pathwrite_text)
- [Path.read_bytes](#pathread_bytes)
- [Path.unlink](#pathunlink)
- [Path.name suffix stem](#pathname-suffix-stem)
- [Path.parent](#pathparent)
- [Path.glob](#pathglob)
- [Path.iterdir](#pathiterdir)
- [json.dumps](#jsondumps)
- [json.loads](#jsonloads)
- [json.dump](#jsondump)
- [json.load](#jsonload)
- [indent dan ensure_ascii](#indent-dan-ensure_ascii)
- [csv.writer](#csvwriter)
- [csv.reader](#csvreader)
- [csv.DictWriter](#csvdictwriter)
- [csv.DictReader](#csvdictreader)
- [newline csv](#newline-csv)
- [shutil.copy](#shutilcopy)

## open

**Tipe:** fungsi bawaan

**Untuk apa:** membuka file dan mengembalikan objek file. Mode umum: `"r"` baca, `"w"` tulis (timpa), `"a"` tambah di ujung, `"b"` biner. Selalu pikirkan encoding teks.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_open.txt")
path.write_text("baris satu\n", encoding="utf-8")
f = open(path, "r", encoding="utf-8")
isi = f.read()
f.close()
print(repr(isi))
path.unlink()
```

**Yang terjadi:**

- File dibuat berisi satu baris.
- `open` mode baca, `read` mengambil seluruh teks: `'baris satu\n'`.
- `close` menutup handle.
- `unlink` menghapus file percobaan.

**Biasanya digabungkan dengan:** `with`, `Path`, `json.load`.

**Jangan:** membuka `"w"` pada file penting tanpa backup. `"w"` mengosongkan file segera setelah open berhasil.

## read

**Tipe:** method objek file

**Untuk apa:** membaca seluruh sisa file sebagai satu string (mode teks) atau `bytes` (mode biner). Enak untuk file kecil. File besar lebih baik dibaca per baris.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_read.txt")
path.write_text("A\nB\nC\n", encoding="utf-8")
with path.open("r", encoding="utf-8") as f:
    print(repr(f.read()))
    print(repr(f.read()))
path.unlink()
```

**Yang terjadi:**

- `read` pertama → `'A\nB\nC\n'`.
- `read` kedua → `''` (kursor sudah di akhir).
- File ditutup otomatis oleh `with`, lalu dihapus.

**Biasanya digabungkan dengan:** `splitlines`, `json.loads`, `seek(0)` untuk ulang dari awal.

**Jangan:** `read()` file ratusan MB di laptop kuliah. Memori bisa penuh. Iterasi `for baris in f:`.

## readline

**Tipe:** method objek file

**Untuk apa:** membaca satu baris, termasuk karakter `\n` di ujung (kecuali baris terakhir kadang tanpa newline). Berguna untuk header lalu sisanya diproses berbeda.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_readline.txt")
path.write_text("nama,nilai\nHaikal,88\n", encoding="utf-8")
with path.open("r", encoding="utf-8") as f:
    header = f.readline()
    isi = f.readline()
print(repr(header))
print(repr(isi))
path.unlink()
```

**Yang terjadi:**

- `header` → `'nama,nilai\n'`.
- `isi` → `'Haikal,88\n'`.
- Kursor maju per panggilan.

**Biasanya digabungkan dengan:** `strip`, `split(",")`, `csv.reader` (lebih aman).

**Jangan:** lupa `strip()`. Perbandingan `"nama,nilai\n" == "nama,nilai"` gagal.

## readlines

**Tipe:** method objek file

**Untuk apa:** membaca semua baris ke sebuah `list` of string. Nyaman, tapi menampung seluruh file di memori.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_readlines.txt")
path.write_text("satu\ndua\ntiga\n", encoding="utf-8")
with path.open("r", encoding="utf-8") as f:
    baris = f.readlines()
print(baris)
print([b.strip() for b in baris])
path.unlink()
```

**Yang terjadi:**

- `baris` → `['satu\n', 'dua\n', 'tiga\n']`.
- List comprehension `strip` → `['satu', 'dua', 'tiga']`.

**Biasanya digabungkan dengan:** list comprehension, filter baris kosong.

**Jangan:** `readlines` lalu `for i in range(len(baris))` jika cukup `for baris in f:`.

## write

**Tipe:** method objek file

**Untuk apa:** menulis string ke file (mode teks). Mengembalikan jumlah karakter yang ditulis. Tidak otomatis menambah `\n`.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_write.txt")
with path.open("w", encoding="utf-8") as f:
    n = f.write("halo")
    f.write("\n")
    f.write("kuliah\n")
print("karakter pertama:", n)
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- `write("halo")` mengembalikan `4`.
- Isi file: dua baris `halo` dan `kuliah`.
- Mode `"w"` menimpa jika file sudah ada.

**Biasanya digabungkan dengan:** `writelines`, `json.dump`, `print(..., file=f)`.

**Jangan:** `write(88)`. Harus string: `write(str(88))` atau f-string.

## append mode

**Tipe:** mode `open` (`"a"`)

**Untuk apa:** menambah di ujung file tanpa menghapus isi lama. Cocok untuk log, bukan untuk “edit baris tengah”.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_append.txt")
path.write_text("awal\n", encoding="utf-8")
with path.open("a", encoding="utf-8") as f:
    f.write("tambahan\n")
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- File awal: `awal\n`.
- Append menambah `tambahan\n`.
- Hasil cetak dua baris: `awal` lalu `tambahan`.

**Biasanya digabungkan dengan:** logging sederhana, jurnal error.

**Jangan:** membuka `"a"` lalu mengira bisa menimpa baris pertama. Kursor ada di akhir.

## with open

**Tipe:** idiom / context manager

**Untuk apa:** memastikan file tertutup. Ini bentuk yang harus menjadi reflex. `Path.open` sama saja, hanya path-nya objek Path.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_with_open.txt")
with open(path, "w", encoding="utf-8") as f:
    print("nilai", 88, file=f)
with open(path, "r", encoding="utf-8") as f:
    print(f.read().strip())
path.unlink()
```

**Yang terjadi:**

- `print(..., file=f)` menulis `nilai 88` plus newline.
- Baca ulang, `strip` membuang newline → `nilai 88`.

**Biasanya digabungkan dengan:** semua operasi file di bab ini.

**Jangan:** memakai `f` di luar blok `with`. File sudah ditutup; `ValueError: I/O operation on closed file`.

## encoding

**Tipe:** parameter `open` / Path

**Untuk apa:** menentukan cara byte jadi huruf. Di Indonesia sering ada `é`, `…`, atau file Excel yang `utf-8-sig` / `cp1252`. Default encoding bergantung OS — jangan andalkan.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_enc.txt")
path.write_text("nilai: 88 — lulus", encoding="utf-8")
print(path.read_text(encoding="utf-8"))
try:
    print(path.read_text(encoding="ascii"))
except UnicodeDecodeError as e:
    print("gagal ascii:", type(e).__name__)
path.unlink()
```

**Yang terjadi:**

- Tulis dan baca UTF-8 berhasil, em dash `—` utuh.
- Baca sebagai ASCII gagal → `UnicodeDecodeError`.

**Biasanya digabungkan dengan:** `utf-8-sig` (buang BOM Excel), pandas `encoding=`.

**Jangan:** membuka file Windows lama dengan `utf-8` lalu kaget karakter aneh. Coba `cp1252` atau `latin-1` saat darurat, lalu simpan ulang UTF-8.

## Path

**Tipe:** class `pathlib.Path`

**Untuk apa:** merepresentasikan path sebagai objek, bukan string yang kamu potong sendiri. Bekerja di macOS, Linux, Windows tanpa merakit `\\` vs `/` manual.

**Contoh implementasi:**

```python
from pathlib import Path

p = Path("data") / "nilai.csv"
print(p)
print(p.as_posix())
print(Path.cwd())
print(Path.home())
```

**Yang terjadi:**

- `p` tercetak `data/nilai.csv` di macOS.
- `as_posix()` selalu pakai `/`.
- `cwd()` folder kerja saat ini.
- `home()` folder rumahan user.

**Biasanya digabungkan dengan:** `read_text`, `glob`, pandas `read_csv(p)`.

**Jangan:** merangkai path dengan `folder + "/" + nama`. Gagal di beberapa kasus. Pakai `/` Path.

## operator / Path

**Tipe:** operator `pathlib`

**Untuk apa:** menambang path anak. Bukan pembagian angka. Operand kanan boleh string.

**Contoh implementasi:**

```python
from pathlib import Path

akar = Path("tugas")
file = akar / "data" / "nilai.csv"
print(file)
print(file.parts)
```

**Yang terjadi:**

- Hasil: `tugas/data/nilai.csv`.
- `parts` → `('tugas', 'data', 'nilai.csv')`.

**Biasanya digabungkan dengan:** `mkdir(parents=True)`, `exists`.

**Jangan:** `Path("tugas") / "/nilai.csv"`. Path kanan yang absolut (diawali `/`) bisa membuang kiri. Pakai nama relatif `"nilai.csv"`.

## Path.exists

**Tipe:** method `Path`

**Untuk apa:** cek apakah path ada (file atau folder). Tidak membedakan jenis; gabungkan dengan `is_file` / `is_dir` jika perlu.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_exists.txt")
print("sebelum", path.exists())
path.write_text("x", encoding="utf-8")
print("sesudah", path.exists())
path.unlink()
print("hapus", path.exists())
```

**Yang terjadi:**

- Sebelum tulis: `False`.
- Sesudah tulis: `True`.
- Setelah `unlink`: `False`.

**Biasanya digabungkan dengan:** `mkdir`, penjaga sebelum baca.

**Jangan:** `exists` lalu langsung `open` tanpa sadar race condition (jarang di tugas kuliah, penting di server). Untuk kuliah, tetap cukup.

## Path.is_file

**Tipe:** method `Path`

**Untuk apa:** `True` jika path ada **dan** berupa file biasa. `is_dir` untuk folder. Path yang tidak ada → `False`, bukan error.

**Contoh implementasi:**

```python
from pathlib import Path

folder = Path("_contoh_dir")
folder.mkdir(exist_ok=True)
file = folder / "a.txt"
file.write_text("x", encoding="utf-8")
print(file.is_file(), folder.is_dir(), Path("tidak_ada").is_file())
file.unlink()
folder.rmdir()
```

**Yang terjadi:**

- `file.is_file()` → `True`.
- `folder.is_dir()` → `True`.
- Path fiktif → `False`.

**Biasanya digabungkan dengan:** `iterdir`, filter `glob`.

**Jangan:** `is_file()` pada symlink tanpa sadar: mengikuti target. Untuk kuliah biasanya tidak masalah.

## Path.mkdir

**Tipe:** method `Path`

**Untuk apa:** membuat folder. `parents=True` membuat rantai folder. `exist_ok=True` tidak marah jika sudah ada.

**Contoh implementasi:**

```python
from pathlib import Path

folder = Path("_contoh_mkdir") / "data"
folder.mkdir(parents=True, exist_ok=True)
print(folder.is_dir())
folder.rmdir()
folder.parent.rmdir()
```

**Yang terjadi:**

- Folder `_contoh_mkdir/data` tercipta.
- `is_dir()` → `True`.
- Dua `rmdir` membersihkan (anak dulu, baru induk).

**Biasanya digabungkan dengan:** simpan PNG matplotlib, cache unduhan.

**Jangan:** `mkdir` tanpa `parents=True` saat induk belum ada. `FileNotFoundError`.

## Path.read_text

**Tipe:** method `Path`

**Untuk apa:** membaca seluruh file teks dalam satu panggilan. Lebih pendek daripada `open` + `read` + `close`.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_rt.txt")
path.write_text("Pemrograman Web\n", encoding="utf-8")
print(path.read_text(encoding="utf-8").strip())
path.unlink()
```

**Yang terjadi:**

- Isi dibaca, `strip` → `Pemrograman Web`.

**Biasanya digabungkan dengan:** `json.loads`, `splitlines`.

**Jangan:** `read_text()` tanpa `encoding` di kode yang berpindah OS. Tulis `encoding="utf-8"` eksplisit.

## Path.write_text

**Tipe:** method `Path`

**Untuk apa:** menimpa file dengan satu string. Mengembalikan jumlah karakter. Tidak ada mode append di method ini; untuk append pakai `open(..., "a")`.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_wt.txt")
n = path.write_text("A\nB\n", encoding="utf-8")
print("n =", n)
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- `n` adalah 4 di Unix (dua huruf + dua newline).
- Isi: baris `A` dan `B`.

**Biasanya digabungkan dengan:** `json.dumps`, template teks.

**Jangan:** `write_text` berulang di loop sebagai “tambah baris”. Setiap panggilan menimpa. Kumpulkan string, tulis sekali, atau append.

## Path.read_bytes

**Tipe:** method `Path`

**Untuk apa:** membaca file sebagai `bytes`. Wajib untuk gambar, zip, atau JSON yang kamu tidak ingin decode dulu.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_rb.bin")
path.write_bytes(b"ABC")
data = path.read_bytes()
print(data, list(data))
path.unlink()
```

**Yang terjadi:**

- `data` → `b'ABC'`.
- `list(data)` → `[65, 66, 67]` (kode ASCII).

**Biasanya digabungkan dengan:** `write_bytes`, unduhan `requests` `content`.

**Jangan:** `read_text` pada PNG. `UnicodeDecodeError` atau sampah.

## Path.unlink

**Tipe:** method `Path`

**Untuk apa:** menghapus file. Untuk folder kosong pakai `rmdir`; untuk pohon folder `shutil.rmtree` (berbahaya).

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_contoh_unlink.txt")
path.write_text("x", encoding="utf-8")
path.unlink()
print(path.exists())
```

**Yang terjadi:**

- File dihapus, `exists()` → `False`.

**Biasanya digabungkan dengan:** `exist_ok` di Python baru: `unlink(missing_ok=True)`.

**Jangan:** `unlink` folder. `IsADirectoryError` / `PermissionError`.

## Path.name suffix stem

**Tipe:** properti `Path`

**Untuk apa:** memecah nama file. `name` = nama + ekstensi, `stem` = tanpa ekstensi, `suffix` = ekstensi termasuk titik. `suffixes` untuk `.tar.gz`.

**Contoh implementasi:**

```python
from pathlib import Path

p = Path("data/nilai.akhir.csv")
print(p.name)
print(p.stem)
print(p.suffix)
print(p.suffixes)
```

**Yang terjadi:**

- `name` → `nilai.akhir.csv`.
- `stem` → `nilai.akhir` (hanya suffix terakhir yang dibuang).
- `suffix` → `.csv`.
- `suffixes` → `['.akhir', '.csv']`.

**Biasanya digabungkan dengan:** filter `if p.suffix == ".csv"`, ganti nama `p.with_suffix(".json")`.

**Jangan:** `nama[-4:] == ".csv"` pada `nilai.CSV`. Bandingkan `p.suffix.lower()`.

## Path.parent

**Tipe:** properti `Path`

**Untuk apa:** naik satu tingkat folder. `parents` adalah rantai ke atas.

**Contoh implementasi:**

```python
from pathlib import Path

p = Path("tugas/data/nilai.csv")
print(p.parent)
print(p.parent.parent)
print(list(p.parents)[:3])
```

**Yang terjadi:**

- `parent` → `tugas/data`.
- Dua kali → `tugas`.
- `parents` adalah urutan ke atas sampai akar.

**Biasanya digabungkan dengan:** simpan file di samping skrip: `Path(__file__).parent`.

**Jangan:** `parent` pada path relatif pendek lalu mengira itu folder nyata di disk. Ini hanya manipulasi string-path, belum tentu ada.

## Path.glob

**Tipe:** method `Path`

**Untuk apa:** mencari file dengan pola `*`, `?`, `[...]`. `rglob` mencari rekursif ke subfolder. Hasilnya generator Path.

**Contoh implementasi:**

```python
from pathlib import Path

akar = Path("_contoh_glob")
akar.mkdir(exist_ok=True)
(akar / "a.csv").write_text("x", encoding="utf-8")
(akar / "b.txt").write_text("y", encoding="utf-8")
print(sorted(p.name for p in akar.glob("*.csv")))
print(sorted(p.name for p in akar.rglob("*")))
for p in akar.glob("*"):
    p.unlink()
akar.rmdir()
```

**Yang terjadi:**

- `*.csv` → `['a.csv']`.
- `rglob("*")` menemukan kedua file (urutan di-sort).
- Cleanup menghapus file lalu folder.

**Biasanya digabungkan dengan:** pandas `concat` banyak CSV, batch gambar.

**Jangan:** `glob("*.csv")` di folder besar tanpa filter lalu menelan file `backup.csv.tmp` sesuai pola yang terlalu longgar. Uji pola dulu dengan `print`.

## Path.iterdir

**Tipe:** method `Path`

**Untuk apa:** mengiterasi isi **langsung** di dalam folder, tanpa pola. Tidak rekursif.

**Contoh implementasi:**

```python
from pathlib import Path

folder = Path("_contoh_iter")
folder.mkdir(exist_ok=True)
(folder / "satu.txt").write_text("1", encoding="utf-8")
print([p.name for p in folder.iterdir()])
(folder / "satu.txt").unlink()
folder.rmdir()
```

**Yang terjadi:**

- Daftar nama: `['satu.txt']`.

**Biasanya digabungkan dengan:** `is_file`, `suffix`.

**Jangan:** `iterdir` pada file. `NotADirectoryError`.

## json.dumps

**Tipe:** fungsi `json`

**Untuk apa:** mengubah objek Python (dict/list/str/angka/bool/None) menjadi **string** JSON. Huruf “s” = string. Ini yang kamu kirim lewat jaringan atau simpan sendiri.

**Contoh implementasi:**

```python
import json

data = {"nama": "Haikal", "nilai": [88, 70], "lulus": True, "catatan": None}
teks = json.dumps(data)
print(teks)
print(type(teks))
```

**Yang terjadi:**

- Output: `{"nama": "Haikal", "nilai": [88, 70], "lulus": true, "catatan": null}`.
- Perhatikan `true`/`null` huruf kecil — itu JSON, bukan Python.
- `type(teks)` → `<class 'str'>`.

**Biasanya digabungkan dengan:** `Path.write_text`, `requests` body, `indent`.

**Jangan:** `dumps` pada `datetime` atau `set` atau `Path`. `TypeError`. Konversi dulu ke str/list.

## json.loads

**Tipe:** fungsi `json`

**Untuk apa:** kebalikan `dumps`: string JSON → objek Python. `true` jadi `True`, `null` jadi `None`, objek jadi `dict`.

**Contoh implementasi:**

```python
import json

teks = '{"nama": "Haikal", "nilai": 88, "lulus": true}'
data = json.loads(teks)
print(data["nama"], data["lulus"], type(data))
```

**Yang terjadi:**

- `data` adalah dict.
- `nama` → `Haikal`, `lulus` → `True` (bool Python).
- `type(data)` → `<class 'dict'>`.

**Biasanya digabungkan dengan:** `requests.Response.text` (atau lebih baik `.json()`), baca file kecil.

**Jangan:** `loads` pada dict yang sudah jadi objek. Ia butuh string. Kalau sudah dict, langsung pakai.

## json.dump

**Tipe:** fungsi `json`

**Untuk apa:** menulis objek langsung ke file terbuka. Tanpa “s”: tujuan adalah file, bukan string.

**Contoh implementasi:**

```python
import json
from pathlib import Path

path = Path("_contoh.json")
data = {"mk": "Web", "sks": 3}
with path.open("w", encoding="utf-8") as f:
    json.dump(data, f, ensure_ascii=False)
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- File berisi `{"mk": "Web", "sks": 3}`.
- `ensure_ascii=False` membiarkan huruf non-ASCII utuh (di contoh ini semua ASCII).

**Biasanya digabungkan dengan:** `indent=2`, `Path`.

**Jangan:** `json.dump(data, path)` mengirim Path sebagai file fp di beberapa versi tanpa `open`. Buka file dulu, atau tulis `path.write_text(json.dumps(...))`.

## json.load

**Tipe:** fungsi `json`

**Untuk apa:** membaca JSON dari file terbuka menjadi objek Python.

**Contoh implementasi:**

```python
import json
from pathlib import Path

path = Path("_contoh_load.json")
path.write_text('{"ok": true, "n": 2}', encoding="utf-8")
with path.open("r", encoding="utf-8") as f:
    data = json.load(f)
print(data, data["ok"])
path.unlink()
```

**Yang terjadi:**

- `data` → `{'ok': True, 'n': 2}`.
- `data["ok"]` adalah `True`.

**Biasanya digabungkan dengan:** konfigurasi tugas, cache API.

**Jangan:** `json.load` pada file kosong atau ada koma terakhir `{"a": 1,}`. JSON ketat, `JSONDecodeError`.

## indent dan ensure_ascii

**Tipe:** parameter `dumps`/`dump`

**Untuk apa:** `indent` membuat JSON rapi (manusia bisa baca). `ensure_ascii=False` menjaga `nilai`, `nama`, aksen, dan huruf Indonesia tidak menjadi `\uXXXX`.

**Contoh implementasi:**

```python
import json

data = {"nama": "Haikal", "ket": "lulus"}
print(json.dumps(data, indent=2, ensure_ascii=False))
print(json.dumps(data, ensure_ascii=True))
```

**Yang terjadi:**

- Blok pertama multi-baris, huruf biasa.
- `ensure_ascii=True` (default) tetap ASCII di contoh ini karena huruf kita dalam rentang ASCII; kalau ada `“lulus”` tipografi, ia di-escape.

**Biasanya digabungkan dengan:** file konfigurasi, debug.

**Jangan:** `indent=2` untuk JSON raksasa yang hanya dibaca mesin. File membesar sia-sia.

## csv.writer

**Tipe:** class `csv`

**Untuk apa:** menulis baris CSV dengan aturan kutip yang benar. Lebih aman daripada `",".join` saat field berisi koma.

**Contoh implementasi:**

```python
import csv
from pathlib import Path

path = Path("_contoh_writer.csv")
with path.open("w", encoding="utf-8", newline="") as f:
    w = csv.writer(f)
    w.writerow(["nama", "nilai"])
    w.writerow(["Haikal", 88])
    w.writerow(["Siti, A.Md.", 70])
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- Header dan dua baris data tertulis.
- Nama berisi koma dikutip: `"Siti, A.Md.",70`.
- `newline=""` mencegah baris kosong ganda di Windows.

**Biasanya digabungkan dengan:** `DictWriter`, pandas `to_csv`.

**Jangan:** lupa `newline=""` di Windows. File jadi selang-seling baris kosong.

## csv.reader

**Tipe:** class `csv`

**Untuk apa:** membaca CSV sebagai list per baris. Setiap field string. Angka tetap teks sampai kamu konversi.

**Contoh implementasi:**

```python
import csv
from pathlib import Path

path = Path("_contoh_reader.csv")
path.write_text("nama,nilai\nHaikal,88\nSiti,70\n", encoding="utf-8")
with path.open("r", encoding="utf-8", newline="") as f:
    rows = list(csv.reader(f))
print(rows)
print(rows[1][1], type(rows[1][1]))
path.unlink()
```

**Yang terjadi:**

- `rows[0]` header `['nama', 'nilai']`.
- `rows[1]` → `['Haikal', '88']`.
- `'88'` bertipe `str`, bukan `int`.

**Biasanya digabungkan dengan:** `int()`, skip header `next(reader)`, `DictReader`.

**Jangan:** `split(",")` pada CSV sungguhan. Field berkutip akan pecah salah.

## csv.DictWriter

**Tipe:** class `csv`

**Untuk apa:** menulis CSV dari dict, dengan header tetap. Kolom tidak “nyasar” karena urutan kunci dict.

**Contoh implementasi:**

```python
import csv
from pathlib import Path

path = Path("_contoh_dw.csv")
field = ["nama", "nilai"]
with path.open("w", encoding="utf-8", newline="") as f:
    w = csv.DictWriter(f, fieldnames=field)
    w.writeheader()
    w.writerow({"nama": "Haikal", "nilai": 88})
    w.writerow({"nilai": 70, "nama": "Siti"})
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- Header `nama,nilai`.
- Urutan kunci di dict kedua terbalik, tapi kolom tetap benar: `Siti,70`.

**Biasanya digabungkan dengan:** list of dict, `extrasaction="ignore"`.

**Jangan:** lupa `writeheader()`. File tanpa nama kolom menyulitkan pandas.

## csv.DictReader

**Tipe:** class `csv`

**Untuk apa:** setiap baris jadi dict: kunci dari header. Paling nyaman untuk CSV berheader.

**Contoh implementasi:**

```python
import csv
from pathlib import Path

path = Path("_contoh_dr.csv")
path.write_text("nama,nilai\nHaikal,88\nSiti,70\n", encoding="utf-8")
with path.open("r", encoding="utf-8", newline="") as f:
    for row in csv.DictReader(f):
        print(row["nama"], int(row["nilai"]))
path.unlink()
```

**Yang terjadi:**

- Iterasi 1: `Haikal 88`.
- Iterasi 2: `Siti 70`.
- `int(...)` mengubah string nilai.

**Biasanya digabungkan dengan:** list comprehension, pandas `read_csv` untuk analisis.

**Jangan:** mengira semua kolom sudah angka. `DictReader` selalu string (atau `None` jika kolom kurang).

## newline csv

**Tipe:** parameter `open` khusus CSV

**Untuk apa:** di dokumentasi resmi, file CSV dibuka dengan `newline=""` agar modul `csv` yang mengatur line ending. Tanpa itu, Windows bisa menulis `\r\n` ganda.

**Contoh implementasi:**

```python
import csv
from pathlib import Path

path = Path("_contoh_nl.csv")
with path.open("w", encoding="utf-8", newline="") as f:
    csv.writer(f).writerows([["a", "b"], ["1", "2"]])
print(repr(path.read_bytes()))
path.unlink()
```

**Yang terjadi:**

- Byte file memakai `\r\n` atau `\n` sesuai dialek, tapi **satu** ending per baris.
- `repr` memperlihatkan byte mentah, berguna saat debug CSV “aneh”.

**Biasanya digabungkan dengan:** semua `csv.reader/writer`.

**Jangan:** membuka CSV dengan `newline="\n"` asal-asalan di Windows lalu mengirim ke teman; baris bisa bergeser di Excel.

## shutil.copy

**Tipe:** fungsi `shutil`

**Untuk apa:** menyalin file. `copy` meniru isi + permission dangkal; `copy2` menambah metadata. Untuk folder, `copytree`.

**Contoh implementasi:**

```python
import shutil
from pathlib import Path

src = Path("_contoh_src.txt")
dst = Path("_contoh_dst.txt")
src.write_text("asal\n", encoding="utf-8")
shutil.copy(src, dst)
print(dst.read_text(encoding="utf-8"))
src.unlink()
dst.unlink()
```

**Yang terjadi:**

- File tujuan berisi `asal` plus newline, sama dengan sumber.

**Biasanya digabungkan dengan:** backup sebelum menimpa, pipeline tugas.

**Jangan:** `copy` ke path folder tanpa nama file jika kamu mengira namanya otomatis — sebenarnya boleh jika `dst` folder; pastikan `dst` ada. Kalau `dst` folder belum ada, error.

---

Array NumPy dan dtype dibahas di [04-numpy-array-tipe.md](04-numpy-array-tipe.md).
