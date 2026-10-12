# 09 — requests, datetime, dan regex

[← 08 Grafik](08-matplotlib-seaborn.md) · [Indeks](README.md) · [Lanjut 10 →](10-resep-analisis-kesalahan.md)

Tiga alat yang sering menempel di tugas web + data: mengambil HTTP, menghitung tanggal, dan mengekstrak pola dari teks. `datetime` dan `re` bawaan. `requests` dipasang: `python -m pip install requests`.

Contoh `requests` butuh internet. Kalau gagal, cek Wi-Fi atau ganti URL. Jangan hardcode token rahasia di file tugas.

## Daftar isi

- [requests.get](#requestsget)
- [status_code](#status_code)
- [raise_for_status](#raise_for_status)
- [Response.text](#responsetext)
- [Response.json](#responsejson)
- [Response.content](#responsecontent)
- [headers](#headers)
- [params](#params)
- [timeout](#timeout)
- [requests.post](#requestspost)
- [Session](#session)
- [datetime.datetime](#datetimedatetime)
- [datetime.date](#datetimedate)
- [datetime.time](#datetimetime)
- [timedelta](#timedelta)
- [strftime](#strftime)
- [strptime](#strptime)
- [timezone](#timezone)
- [date.today](#datetoday)
- [datetime.now](#datetimenow)
- [re.search](#research)
- [re.match](#rematch)
- [re.fullmatch](#refullmatch)
- [re.findall](#refindall)
- [re.finditer](#refinditer)
- [re.sub](#resub)
- [re.split](#resplit)
- [re.compile](#recompile)
- [grup regex](#grup-regex)
- [pola sering](#pola-sering)

## requests.get

**Tipe:** fungsi `requests`

**Untuk apa:** mengirim permintaan HTTP GET dan mengembalikan `Response`. Ini cara paling umum mengambil JSON API atau halaman.

**Contoh implementasi:**

```python
import requests

url = "https://httpbin.org/get"
try:
    r = requests.get(url, timeout=10)
    print(r.status_code)
    print("url akhir", r.url)
    print("kunci json", sorted(r.json().keys())[:5])
except requests.RequestException as e:
    print("jaringan gagal:", type(e).__name__)
```

**Yang terjadi:**

- Jika jaringan oke: `status_code` `200`, URL tercetak, JSON httpbin berisi kunci seperti `args`, `headers`, `origin`, `url`.
- Jika offline/timeout: cabang `except` mencetak nama error, skrip tidak meledak.

**Biasanya digabungkan dengan:** `params`, `headers`, `r.json()`, pandas `json_normalize`.

**Jangan:** GET tanpa `timeout`. Program bisa menggantung diam-diam.

## status_code

**Tipe:** atribut `Response` (int)

**Untuk apa:** kode HTTP. `200` sukses, `404` tidak ketemu, `401`/`403` otorisasi, `500` server error. Jangan hanya cek “ada teks”.

**Contoh implementasi:**

```python
import requests

r = requests.get("https://httpbin.org/status/404", timeout=10)
print(r.status_code)
print(r.ok)
```

**Yang terjadi:**

- `status_code` → `404`.
- `ok` → `False` (True hanya untuk 2xx).

**Biasanya digabungkan dengan:** `raise_for_status`, cabang `if r.status_code == 200`.

**Jangan:** mengira `requests` melempar error otomatis pada 404. Default: kamu dapat `Response`, harus cek sendiri.

## raise_for_status

**Tipe:** method `Response`

**Untuk apa:** melempar `HTTPError` jika status 4xx/5xx. Pola bersih: `r.raise_for_status()` lalu baru `r.json()`.

**Contoh implementasi:**

```python
import requests

r = requests.get("https://httpbin.org/status/500", timeout=10)
try:
    r.raise_for_status()
except requests.HTTPError as e:
    print("gagal HTTP:", e)
    print("kode", r.status_code)
```

**Yang terjadi:**

- Status 500 memicu `HTTPError`.
- Pesan memuat URL dan kode.
- `r.status_code` tetap `500` untuk dicatat.

**Biasanya digabungkan dengan:** `try/except`, retry sederhana (jangan infinite).

**Jangan:** `raise_for_status` lalu mengira body error hilang. `r.text` masih bisa dibaca di `except`.

## Response.text

**Tipe:** properti `Response` (str)

**Untuk apa:** tubuh respons sebagai teks, sudah di-decode menurut encoding. Untuk HTML atau CSV mentah.

**Contoh implementasi:**

```python
import requests

r = requests.get("https://httpbin.org/html", timeout=10)
print(r.encoding)
print(r.text[:60].replace("\n", " "))
```

**Yang terjadi:**

- Encoding biasanya `utf-8`.
- 60 karakter pertama HTML httpbin (potong supaya output pendek).

**Biasanya digabungkan dengan:** `re`, `Path.write_text`, parser HTML (di luar stack wajib).

**Jangan:** `text` pada file biner (gambar). Rusak. Pakai `content`.

## Response.json

**Tipe:** method `Response`

**Untuk apa:** parse tubuh sebagai JSON → dict/list Python. Lebih aman daripada `json.loads(r.text)` karena menangani encoding.

**Contoh implementasi:**

```python
import requests

r = requests.get("https://httpbin.org/json", timeout=10)
r.raise_for_status()
data = r.json()
print(type(data))
print(list(data.keys())[:5])
```

**Yang terjadi:**

- `type` → `dict` (pada endpoint itu).
- Beberapa kunci tingkat atas tercetak.

**Biasanya digabungkan dengan:** `pd.DataFrame(data["items"])`, cek `isinstance`.

**Jangan:** `r.json()` pada HTML error page. `JSONDecodeError`. Cek status dan `Content-Type`.

## Response.content

**Tipe:** atribut `Response` (bytes)

**Untuk apa:** tubuh mentah. Untuk gambar, PDF, zip, atau file yang kamu tulis `wb`.

**Contoh implementasi:**

```python
import requests
from pathlib import Path

r = requests.get("https://httpbin.org/bytes/16", timeout=10)
r.raise_for_status()
print(len(r.content), type(r.content))
path = Path("_contoh.bin")
path.write_bytes(r.content)
print(path.stat().st_size)
path.unlink()
```

**Yang terjadi:**

- 16 byte, tipe `bytes`.
- File tertulis 16 byte, lalu dihapus.

**Biasanya digabungkan dengan:** `Path.write_bytes`, cek header `Content-Type`.

**Jangan:** `write_text(r.content)` — `content` bukan str.

## headers

**Tipe:** dict-like di request dan response

**Untuk apa:** metadata HTTP. Request: `User-Agent`, `Authorization`, `Accept`. Response: `Content-Type`, `Retry-After`. Beberapa API menolak tanpa User-Agent.

**Contoh implementasi:**

```python
import requests

hdr = {"User-Agent": "kuliah-pemrograman-web/1.0", "Accept": "application/json"}
r = requests.get("https://httpbin.org/headers", headers=hdr, timeout=10)
r.raise_for_status()
terkirim = r.json()["headers"]
print(terkirim.get("User-Agent"))
print(r.headers.get("Content-Type"))
```

**Yang terjadi:**

- httpbin memantulkan header: User-Agent sesuai yang kita kirim.
- Respons biasanya `application/json`.

**Biasanya digabungkan dengan:** token `Bearer`, `params`.

**Jangan:** menaruh API key di repo publik. Pakai environment variable.

## params

**Tipe:** parameter `requests` (query string)

**Untuk apa:** menambahkan `?kunci=nilai&...` dengan encoding aman. Jangan merangkai URL pakai f-string + spasi mentah.

**Contoh implementasi:**

```python
import requests

r = requests.get(
    "https://httpbin.org/get",
    params={"q": "pemrograman web", "page": 2},
    timeout=10,
)
r.raise_for_status()
print(r.url)
print(r.json()["args"])
```

**Yang terjadi:**

- URL mengandung `q=pemrograman+web` (spasi ter-encode) dan `page=2`.
- `args` di JSON: `{'q': 'pemrograman web', 'page': '2'}` (nilai query biasanya string).

**Biasanya digabungkan dengan:** pagination loop, filter API.

**Jangan:** `url + "?q=" + user`. Karakter `&` di input memecah query. Pakai `params`.

## timeout

**Tipe:** parameter `requests` (detik)

**Untuk apa:** batas tunggu. Bisa satu angka (keduanya), atau tuple `(connect, read)`. Wajib di skrip yang dijalankan dosen.

**Contoh implementasi:**

```python
import requests

try:
    requests.get("https://httpbin.org/delay/10", timeout=2)
except requests.Timeout as e:
    print("timeout:", type(e).__name__)
```

**Yang terjadi:**

- Server httpbin menunda 10 detik, kita hanya menunggu 2 → `Timeout` / `ReadTimeout`.
- Pesan `timeout: ...` tercetak.

**Biasanya digabungkan dengan:** `try/except`, `raise_for_status`.

**Jangan:** `timeout=None` (default historis) di production. Bisa menggantung selamanya.

## requests.post

**Tipe:** fungsi `requests`

**Untuk apa:** mengirim data ke server. JSON: `json=dict`. Form: `data=dict`. File: `files=`.

**Contoh implementasi:**

```python
import requests

badan = {"nama": "Haikal", "nilai": 88}
r = requests.post("https://httpbin.org/post", json=badan, timeout=10)
r.raise_for_status()
echo = r.json()["json"]
print(echo)
print(r.json()["headers"].get("Content-Type"))
```

**Yang terjadi:**

- httpbin mengembalikan JSON yang kita kirim: `{'nama': 'Haikal', 'nilai': 88}`.
- `Content-Type` request biasanya `application/json`.

**Biasanya digabungkan dengan:** API login (latihan), webhook, `Session`.

**Jangan:** `data=json.dumps(...)` tanpa header JSON kecuali kamu sadar. Lebih jelas `json=`.

## Session

**Tipe:** class `requests.Session`

**Untuk apa:** menyimpan cookie dan header default antar permintaan. Lebih efisien (koneksi diulang) untuk banyak GET ke host yang sama.

**Contoh implementasi:**

```python
import requests

s = requests.Session()
s.headers.update({"User-Agent": "kuliah-web/1.0"})
r = s.get("https://httpbin.org/cookies/set?k=v", timeout=10, allow_redirects=True)
print("cookie jar", s.cookies.get_dict())
r2 = s.get("https://httpbin.org/cookies", timeout=10)
print(r2.json())
s.close()
```

**Yang terjadi:**

- Set cookie `k=v` (httpbin redirect).
- Permintaan kedua membawa cookie; JSON memuat `{"cookies": {"k": "v"}}` (jika layanan berperilaku standar).

**Biasanya digabungkan dengan:** crawl bertahap, login form latihan.

**Jangan:** satu `Session` global tanpa `close` di proses panjang. Pakai `with requests.Session() as s:`.

## datetime.datetime

**Tipe:** class `datetime.datetime`

**Untuk apa:** stempel tanggal **dan** jam. Komponen: year, month, day, hour, minute, second, microsecond, tzinfo.

**Contoh implementasi:**

```python
from datetime import datetime

t = datetime(2026, 9, 22, 11, 30, 0)
print(t)
print(t.year, t.month, t.day, t.hour)
print(t.weekday())  # Senin=0
```

**Yang terjadi:**

- Cetak `2026-09-22 11:30:00`.
- Komponen terpisah: 2026, 9, 22, 11.
- `weekday()` untuk 22 Sep 2026 = 1 (Selasa).

**Biasanya digabungkan dengan:** `timedelta`, pandas `to_datetime`, `strftime`.

**Jangan:** `datetime.datetime.now` tanpa kurung saat kamu butuh nilai. Itu objek fungsi, bukan waktu.

## datetime.date

**Tipe:** class `datetime.date`

**Untuk apa:** kalender saja, tanpa jam. Cocok deadline tugas, tanggal lahir, hari kuliah.

**Contoh implementasi:**

```python
from datetime import date

d = date(2026, 9, 22)
print(d.isoformat())
print(d.replace(month=10))
print(date.min, date.max)
```

**Yang terjadi:**

- `isoformat` → `2026-09-22`.
- `replace` → `2026-10-22` (objek baru).
- Rentang min/max tercetak (batas Gregorian yang didukung).

**Biasanya digabungkan dengan:** `today()`, selisih `date - date` → `timedelta`.

**Jangan:** mengurangkan `date` dengan `datetime`. Tipe harus sejenis, atau samakan dulu.

## datetime.time

**Tipe:** class `datetime.time`

**Untuk apa:** jam dalam sehari, tanpa tanggal. Jam buka lab, jam kuliah.

**Contoh implementasi:**

```python
from datetime import time, datetime, date

jam = time(13, 45)
print(jam)
gabung = datetime.combine(date(2026, 9, 22), jam)
print(gabung)
```

**Yang terjadi:**

- `13:45:00`.
- `combine` → `2026-09-22 13:45:00`.

**Biasanya digabungkan dengan:** `combine`, jadwal.

**Jangan:** menambah `time + timedelta` di semua versi secara naif (lebih aman gabung ke `datetime` dulu).

## timedelta

**Tipe:** class selisih waktu

**Untuk apa:** durasi: hari, detik, mikrodetik. Hasil `datetime - datetime`. Bisa ditambah/dikurangi ke stempel.

**Contoh implementasi:**

```python
from datetime import datetime, timedelta

mulai = datetime(2026, 9, 1, 8, 0)
akhir = datetime(2026, 9, 22, 11, 30)
selisih = akhir - mulai
print(selisih)
print(selisih.days, selisih.total_seconds())
print(mulai + timedelta(days=7, hours=2))
```

**Yang terjadi:**

- Selisih sekitar 21 hari lebih beberapa jam.
- `days` bagian hari utuh; `total_seconds` semua dalam detik.
- Plus 7 hari 2 jam → `2026-09-08 10:00:00`.

**Biasanya digabungkan dengan:** deadline, `range` tanggal.

**Jangan:** `timedelta(months=1)`. Tidak ada `months` (bulan panjangnya beda). Pakai `dateutil.relativedelta` (bukan bawaan) atau ganti bulan manual hati-hati.

## strftime

**Tipe:** method datetime/date

**Untuk apa:** format ke string. Pola: `%Y` tahun 4 digit, `%m` bulan, `%d` hari, `%H` jam 24, `%M` menit, `%S` detik, `%A` nama hari.

**Contoh implementasi:**

```python
from datetime import datetime

t = datetime(2026, 9, 22, 11, 30)
print(t.strftime("%Y-%m-%d"))
print(t.strftime("%d/%m/%Y %H:%M"))
print(t.strftime("%A"))
```

**Yang terjadi:**

- `2026-09-22`.
- `22/09/2026 11:30`.
- `Tuesday` (nama English, tergantung locale bisa beda).

**Biasanya digabungkan dengan:** nama file `laporan_2026-09-22.csv`, label grafik.

**Jangan:** `f"{t.day}/{t.month}/{t.year}"` tanpa zero-padding jika kamu butuh `09`. `%m` sudah dua digit.

## strptime

**Tipe:** method class `datetime`

**Untuk apa:** kebalikan `strftime`: string + pola → objek datetime. Wajib saat CSV tanggal masih teks.

**Contoh implementasi:**

```python
from datetime import datetime

teks = "22/09/2026 11:30"
t = datetime.strptime(teks, "%d/%m/%Y %H:%M")
print(t)
print(t.date())
```

**Yang terjadi:**

- Parse berhasil → `2026-09-22 11:30:00`.
- `.date()` membuang jam → `2026-09-22`.

**Biasanya digabungkan dengan:** pandas `to_datetime`, validasi input.

**Jangan:** pola terbalik `%m/%d` vs `%d/%m`. `12/09` bisa diam-diam jadi Desember jika pola salah.

## timezone

**Tipe:** `datetime.timezone` / aware vs naive

**Untuk apa:** membedakan waktu “polos” (naive) dan yang punya zona (aware). `timezone.utc` paling aman untuk simpan. Waktu lokal Indonesia: UTC+7 (`timedelta(hours=7)`).

**Contoh implementasi:**

```python
from datetime import datetime, timezone, timedelta

utc = datetime(2026, 9, 22, 4, 30, tzinfo=timezone.utc)
wib = timezone(timedelta(hours=7))
print(utc)
print(utc.astimezone(wib))
print(datetime.now(timezone.utc))
```

**Yang terjadi:**

- UTC 04:30 tercetak dengan `+00:00`.
- `astimezone` WIB → `11:30+07:00` (4:30 UTC + 7 jam).
- `now(timezone.utc)` aware, bukan naive.

**Biasanya digabungkan dengan:** API timestamp, `pandas` `tz_localize`.

**Jangan:** mengurangkan naive dan aware. `TypeError`. Samakan dulu.

## date.today

**Tipe:** method class `date`

**Untuk apa:** tanggal kalender lokal mesin hari ini, tanpa jam.

**Contoh implementasi:**

```python
from datetime import date, timedelta

hari = date.today()
print(hari)
print(hari + timedelta(days=1))
print(hari.isoformat())
```

**Yang terjadi:**

- Cetak tanggal mesin (saat dokumen ini ditulis contohnya 2026-09-22, di komputermu ikut hari ini).
- Besok = +1 hari.
- ISO `YYYY-MM-DD`.

**Biasanya digabungkan dengan:** filter `df["tgl"] <= date.today()`, umur kasar.

**Jangan:** memakai `today` sebagai kunci acak unik. Dua proses di hari yang sama bentrok.

## datetime.now

**Tipe:** method class `datetime`

**Untuk apa:** tanggal + jam sekarang. Naive jika tanpa tz. Lebih baik `datetime.now(timezone.utc)`.

**Contoh implementasi:**

```python
from datetime import datetime, timezone

print(datetime.now())
print(datetime.now(timezone.utc))
```

**Yang terjadi:**

- Pertama: waktu lokal naive (tanpa offset).
- Kedua: waktu UTC aware.

**Biasanya digabungkan dengan:** log, nama file unik plus `strftime`.

**Jangan:** mengukur durasi dengan `datetime.now` minus-minus di loop ketat. Untuk stopwatch, `time.perf_counter()` lebih tepat.

## re.search

**Tipe:** fungsi `re`

**Untuk apa:** mencari pola **di mana saja** di string. Mengembalikan `Match` atau `None`. Ini fungsi regex yang paling sering.

**Contoh implementasi:**

```python
import re

teks = "NIM saya 2106123 di kelas Web"
m = re.search(r"\d{7}", teks)
print(m.group() if m else None)
print(re.search(r"Basis", teks))
```

**Yang terjadi:**

- Pola 7 digit ketemu `2106123`.
- `"Basis"` tidak ada → `None` tercetak.

**Biasanya digabungkan dengan:** `group`, `findall`, pandas `str.extract`.

**Jangan:** lupa prefix `r"..."` pada pola berisi `\`. `"\d"` bisa bukan digit; `r"\d"` yang benar.

## re.match

**Tipe:** fungsi `re`

**Untuk apa:** hanya cocok di **awal** string. Bukan “cocok seluruhnya” (itu `fullmatch`).

**Contoh implementasi:**

```python
import re

print(re.match(r"NIM", "NIM 2106"))
print(re.match(r"2106", "NIM 2106"))
print(re.search(r"2106", "NIM 2106"))
```

**Yang terjadi:**

- `match("NIM"...)` sukses (awal).
- `match("2106"...)` gagal (`None`) karena tidak di awal.
- `search("2106")` sukses.

**Biasanya digabungkan dengan:** validasi awalan, token.

**Jangan:** memakai `match` mengira ia mencari di tengah. Itu jebakan nomor satu regex Python.

## re.fullmatch

**Tipe:** fungsi `re`

**Untuk apa:** seluruh string harus cocok. Ideal validasi format: NIM persis 7 digit, bukan “ada 7 digit di dalam kalimat”.

**Contoh implementasi:**

```python
import re

print(bool(re.fullmatch(r"\d{7}", "2106123")))
print(bool(re.fullmatch(r"\d{7}", "NIM 2106123")))
```

**Yang terjadi:**

- Persis 7 digit → `True`.
- Ada prefiks teks → `False`.

**Biasanya digabungkan dengan:** form input, penjaga fungsi.

**Jangan:** `^pola$` di `search` jika ada `fullmatch`. `fullmatch` lebih jelas.

## re.findall

**Tipe:** fungsi `re`

**Untuk apa:** mengembalikan **semua** kecocokan sebagai list string (atau tuple jika ada grup).

**Contoh implementasi:**

```python
import re

teks = "nilai 88, 70, dan 91"
print(re.findall(r"\d+", teks))
print(re.findall(r"(\d+)", "a=1 b=2"))
```

**Yang terjadi:**

- `['88', '70', '91']` — masih string.
- Dengan satu grup: `['1', '2']`.

**Biasanya digabungkan dengan:** `map(int, ...)`, ekstrak semua URL.

**Jangan:** `findall` lalu `match.group` — hasilnya sudah string, bukan `Match`.

## re.finditer

**Tipe:** fungsi `re`

**Untuk apa:** iterator `Match`, lengkap dengan posisi `start()`/`end()`. Saat kamu butuh konteks, bukan hanya teks.

**Contoh implementasi:**

```python
import re

teks = "Web 88, Basis 70"
for m in re.finditer(r"(\w+)\s+(\d+)", teks):
    print(m.group(1), m.group(2), "di", m.start(), m.end())
```

**Yang terjadi:**

- Pasangan `Web 88` di rentang indeks pertama, `Basis 70` di rentang berikutnya.
- Posisi `start/end` tercetak.

**Biasanya digabungkan dengan:** highlight teks, potong string.

**Jangan:** menelan `finditer` dua kali. Iterator habis.

## re.sub

**Tipe:** fungsi `re`

**Untuk apa:** ganti semua kecocokan. Bisa string pengganti atau fungsi. Lebih kuat daripada `str.replace` untuk pola.

**Contoh implementasi:**

```python
import re

teks = "NIM 2106123 dan 2106999"
print(re.sub(r"\d{7}", "XXXXXXX", teks))
print(re.sub(r"\s+", " ", "Pemrograman    Web").strip())
```

**Yang terjadi:**

- Kedua NIM disensor: `NIM XXXXXXX dan XXXXXXX`.
- Spasi ganda merapat jadi satu: `Pemrograman Web`.

**Biasanya digabungkan dengan:** bersihkan CSV, `str.replace` untuk literal.

**Jangan:** `sub` pola terlalu lapar `.*` yang menelan seluruh baris. Uji dulu dengan `findall`.

## re.split

**Tipe:** fungsi `re`

**Untuk apa:** memecah string menurut pola, bukan hanya satu pemisah tetap.

**Contoh implementasi:**

```python
import re

print(re.split(r"[,;]\s*", "88, 70; 91"))
```

**Yang terjadi:**

- Pemisah koma atau titik koma plus spasi opsional → `['88', '70', '91']`.

**Biasanya digabungkan dengan:** parser kasar, normalisasi daftar.

**Jangan:** `split` pola yang menangkap grup: hasil menyertakan pemisah. Pakai grup non-capturing `(?:...)` jika tidak ingin itu.

## re.compile

**Tipe:** fungsi `re`

**Untuk apa:** mengompilasi pola sekali, dipakai berkali. Lebih rapi jika pola panjang, dan sedikit lebih cepat di loop ketat.

**Contoh implementasi:**

```python
import re

nim = re.compile(r"\b\d{7}\b")
print(nim.search("user 2106123 ok").group())
print(nim.findall("2106123 123 2106999"))
```

**Yang terjadi:**

- `search` → `2106123`.
- `findall` → dua NIM 7 digit; `123` tidak lolos.

**Biasanya digabungkan dengan:** konstanta di atas file, `Pattern.sub`.

**Jangan:** compile di dalam loop yang sama tanpa alasan. Compile di luar.

## grup regex

**Tipe:** fitur `Match`

**Untuk apa:** menangkap bagian pola. `group(0)` seluruh match, `group(1)` grup pertama. Named group `(?P<nama>...)`.

**Contoh implementasi:**

```python
import re

m = re.search(r"(?P<huruf>[A-Za-z]+)-(?P<angka>\d+)", "IF-4021")
print(m.group(0), m.group(1), m.group(2))
print(m.group("huruf"), m.group("angka"))
```

**Yang terjadi:**

- `group(0)` → `IF-4021`.
- Grup 1/2 = `IF` dan `4021`.
- Nama: sama, lebih mudah dibaca.

**Biasanya digabungkan dengan:** `str.extract` pandas, parse kode MK.

**Jangan:** `group(1)` tanpa cek `if m:`. `AttributeError: 'NoneType'`.

## pola sering

**Tipe:** kumpulan pola (referensi)

**Untuk apa:** titik start, bukan validator sempurna. Email/URL sungguhan jauh lebih rumit dari satu regex.

**Contoh implementasi:**

```python
import re

email = r"^[\w.+-]+@[\w-]+\.[\w.]+$"
print(bool(re.fullmatch(email, "haikal@kampus.ac.id")))
print(bool(re.fullmatch(email, "bukan-email")))

baris = "Haikal,88,A"
print(re.fullmatch(r"[^,]+,\d+,[A-E]$", baris) is not None)
```

**Yang terjadi:**

- Email contoh → `True`.
- `"bukan-email"` → `False`.
- CSV sederhana nama,angka,huruf A–E → `True`.

**Biasanya digabungkan dengan:** `fullmatch`, validasi kasar sebelum pandas.

**Jangan:** mengklaim regex email ini menolak semua alamat ilegal. Untuk produksi, pakai library validator atau kirim email konfirmasi.

---

Resep utuh dan kesalahan umum di [10-resep-analisis-kesalahan.md](10-resep-analisis-kesalahan.md).
