# Teori fondasi lintas bahasa

[← Indeks ensiklopedia](README.md) · [Versi cepat CP](../cp.md)

Bab ini **melengkapi** ensiklopedia per bahasa. Jangan menimpa bab lama di `html/`, `css/`, `javascript/`, `python/`, `cpp/`, `java/`, dan yang lain. Isinya teori yang sering bolong: kompleksitas, memori, cara argumen dikirim, mutasi, error, memilih bahasa, dan cara baca dokumentasi.

Bahasa di contoh sengaja dicampur sedikit supaya pola yang sama kelihatan. Detail API tetap di bab asalnya.

## Daftar isi

- [Kenapa bab ini ada](#kenapa-bab-ini-ada)
- [Kompleksitas waktu](#kompleksitas-waktu)
- [Kompleksitas memori](#kompleksitas-memori)
- [Cara baca batasan soal dan tugas](#cara-baca-batasan-soal-dan-tugas)
- [Tipe data versus memori](#tipe-data-versus-memori)
- [Stack, heap, dan hidupnya data](#stack-heap-dan-hidupnya-data)
- [Pass-by-value dan pass-by-reference](#pass-by-value-dan-pass-by-reference)
- [Referensi, pointer, dan alias](#referensi-pointer-dan-alias)
- [Mutasi versus salinan](#mutasi-versus-salinan)
- [Kesamaan nilai versus kesamaan identitas](#kesamaan-nilai-versus-kesamaan-identitas)
- [Error, exception, dan status](#error-exception-dan-status)
- [Kapan pilih Python, Java, C++, atau JavaScript](#kapan-pilih-python-java-c-atau-javascript)
- [Cara baca dokumentasi](#cara-baca-dokumentasi)
- [Cara meniru contoh resmi tanpa nyalin buta](#cara-meniru-contoh-resmi-tanpa-nyalin-buta)
- [Peta ke bab ensiklopedia](#peta-ke-bab-ensiklopedia)

## Kenapa bab ini ada

**Untuk apa:** menyatukan gagasan yang muncul di semua bahasa, supaya tidak diulang (dan tidak bentrok) di tiap katalog API.

Ensiklopedia Python menjelaskan `list.append`. Ensiklopedia Java menjelaskan `ArrayList.add`. Keduanya adalah **mutasi koleksi**. Tanpa teori bersama, mudah mengira “Python beda alam” padahal modelnya sama: nama variabel menunjuk objek, objek bisa diubah.

**Contoh implementasi:** bandingkan tiga baris yang kelihatan berbeda:

```python
angka = [1, 2]
angka.append(3)
```

```java
List<Integer> angka = new ArrayList<>(List.of(1, 2));
angka.add(3);
```

```js
const angka = [1, 2];
angka.push(3);
```

**Yang terjadi:** tiga bahasa menambah elemen ke objek yang sama. Yang tidak sama: penulisannya, tipenya, dan apakah `const`/`final` mengunci **nama** atau **isi**.

**Biasanya digabungkan dengan:** bab tipe di tiap bahasa, plus bagian mutasi di bawah.

**Jangan:** menghapus atau menimpa `python/01-dasar-tipe-variabel.md` dan kawan-kawannya. Bab ini hanya penghubung.

## Kompleksitas waktu

**Untuk apa:** memperkirakan berapa kali langkah diulang jika input membesar, tanpa menjalankan program sampai hang.

Big-O menyebut **laju pertumbuhan**, bukan detik persis. `O(n)` berarti jika `n` dikali 10, kerja kira-kira dikali 10. Konstanta tersembunyi (bahasa lambat, cache, I/O) tetap ada, tapi urutan besarnya yang menolong memilih algoritma.

```text
O(1)        tetap: ambil a[i], hash map rata-rata
O(log n)    potong dua: binary search, tinggi pohon
O(n)        satu lintasan: jumlah array
O(n log n)  urut + cari: sort, banyak struktur
O(n^2)      pasangan: dua loop bersarang
O(2^n)      himpunan bagian: n ~ 20
O(n!)       semua urutan: n ~ 10
```

**Contoh implementasi:** hitung pasangan di daftar `n` angka.

```python
def jumlah_naif(a):
    total = 0
    for i in range(len(a)):
        for j in range(i + 1, len(a)):
            total += a[i] + a[j]
    return total
```

**Yang terjadi:** loop dalam berjalan ~ `n^2 / 2` kali. Untuk `n = 1e5` itu miliaran langkah. Di Python bisa menit; di C++ masih berat untuk 1 detik.

Versi `O(n)` memakai rumus, bukan pasangan:

```python
def jumlah_cepat(a):
    n = len(a)
    return sum(x * (n - 1) for x in a)
```

**Yang terjadi:** tiap elemen dihitung sekali. Hasil sama untuk rumus itu, waktunya linier.

**Biasanya digabungkan dengan:** tabel `n` versus algoritma di [versi cepat CP](../cp.md).

**Jangan:** mengira `O(n log n)` selalu lebih lambat dari `O(n)` di `n` kecil. Untuk `n = 20`, semuanya instan.

## Kompleksitas memori

**Untuk apa:** memperkirakan RAM sebelum array 2D atau rekursi dalam membuat program ditolak atau crash.

Aturan kasar:

- `bool` / `char` ≈ 1 byte (di Java `boolean[]` bisa lebih).
- `int` / `float` 32-bit ≈ 4 byte.
- `long` / `double` 64-bit ≈ 8 byte.
- Pointer / referensi di 64-bit ≈ 8 byte, plus objek yang ditunjuk.
- String menyimpan tiap karakter (UTF-16 di Java, byte di Python 3 lebih rumit).

**Contoh implementasi:** tabel DP `n × n` bertipe `int`, `n = 5000`.

```text
5000 * 5000 * 4 byte = 100_000_000 byte ≈ 95 MB
```

**Yang terjadi:** di kontes berbatas 64–128 MB, satu tabel sudah hampir penuh. Di browser, array raksasa bisa memperlambat tab. Di Python, list of int jauh lebih boros (tiap `int` objek).

Rekursi memakai stack bingkai. DFS rekursif pada `n = 1e5` di C++ sering **stack overflow**; di Python default recursion limit ~1000.

**Biasanya digabungkan dengan:** Fenwick/segtree (hemat dari matriks), DP 1D mundur (hemat dari `dp[i][w]`).

**Jangan:** mengukur memori hanya dari “berapa variabel di kode”. Array dan objek di heap yang menentukan.

## Cara baca batasan soal dan tugas

**Untuk apa:** menerjemahkan angka di soal (`1 ≤ n ≤ 2·10^5`) menjadi pilihan algoritma, sebelum menulis loop.

```text
Waktu 1 detik, n = 2e5
  2e5 * 2e5 = 4e10  → O(n^2) ditolak
  2e5 * 18          → O(n log n) masuk akal

Memori 64 MB, long long dp[n][n], n = 4000
  4000*4000*8 ≈ 128 MB → ditolak
```

**Contoh implementasi:** tugas web “filter 20 produk di browser” tidak butuh Big-O kontes. Tugas CP “q = 1e5 query jumlah rentang” butuh prefix atau pohon.

**Yang terjadi:** kamu memilih alat yang sesuai **domain**. Kompleksitas tetap benar di web, tapi `n` biasanya kecil kecuali daftar sangat panjang.

**Biasanya digabungkan dengan:** [Kompleksitas waktu](#kompleksitas-waktu) dan peta senjata di `cp.md`.

**Jangan:** memakai knapsack `O(nW)` jika `W = 1e9`. `n` kecil tidak menolong jika dimensi lain raksasa.

## Tipe data versus memori

**Untuk apa:** membedakan **apa yang boleh dilakukan** (tipe) dan **berapa ruang plus rentang nilainya** (representasi).

Tipe adalah kontrak: `int` dijumlah, `string` digabung, fungsi tidak mengira-ngira. Memori adalah wujud kontrak itu di mesin: lebar bit, signed/unsigned, heap atau stack.

Rentang yang sering bikin WA atau bug sunyi:

| Jenis | Khas | Pecah jika |
|---|---|---|
| `int` 32-bit | −2·10^9 .. 2·10^9 | `n * n` untuk `n = 1e5` |
| `long` / `i64` | ±9·10^18 | faktorial besar, perkalian matriks |
| IEEE `double` | ~15 digit | uang, banding `== 0.1 + 0.2` |
| `boolean` | 1 bit logika | dipakai sebagai angka 2 atau 3 |
| teks | byte / code point | indeks karakter multibyte |

**Contoh implementasi:** overflow vs pecahan.

```cpp
int n = 100000;
int salah = n * n;          // overflow
long long benar = 1LL * n * n;
```

```js
console.log(0.1 + 0.2 === 0.3); // false
console.log(Number.isInteger(1e16 + 1)); // hati-hati: presisi
```

```python
print(10**50)          # int Python membesar
print(0.1 + 0.2)       # tetap pecahan IEEE
```

**Yang terjadi:**

- C++/`int` Java membungkus bit; hasil bisa negatif tanpa error.
- JavaScript `number` adalah `double`; integer aman kira-kira sampai `2^53 − 1`.
- Python `int` tidak overflow, tapi lambat dan boros jika dipakai di loop ketat.
- `0.1 + 0.2` di semua bahasa yang memakai IEEE 754 tidak persis `0.3`.

**Biasanya digabungkan dengan:** tipe primitif di [Java 01](java/01-tipe-primitif-wrapper.md), [C++ 01](cpp/01-dasar-tipe-variabel.md), [JS 01](javascript/01-tipe-variabel-operator.md), [Python 01](python/01-dasar-tipe-variabel.md).

**Jangan:** menyimpan uang sebagai `float`/`double` tanpa strategi (desimal, sen sebagai `int`).

## Stack, heap, dan hidupnya data

**Untuk apa:** mengerti kapan data mati sendiri, kapan harus dikelola, dan kenapa “sudah return tapi masih kepakai” berbahaya di C++.

Kira-kira:

- **Stack bingkai:** variabel lokal fungsi. Hilang saat fungsi selesai.
- **Heap:** objek yang hidup selama masih ada yang menunjuk (GC di Java/JS/Python) atau sampai `delete` / smart pointer (C++).
- **Statis / global:** hidup sepanjang program.

**Contoh implementasi:**

```cpp
int* bahaya() {
    int x = 7;
    return &x; // x mati saat return
}
```

```java
List<Integer> aman() {
    List<Integer> x = new ArrayList<>();
    x.add(7);
    return x; // objek di heap, hidup selama ada referensi
}
```

```python
def aman():
    x = [7]
    return x
```

**Yang terjadi:** di C++, pemanggil dapat alamat sampah. Di Java/Python/JS, yang dikembalikan adalah referensi ke objek heap; fungsi selesai tidak membunuh objek itu.

Array besar di stack C++ (`int a[2000000];` lokal) bisa stack overflow. Taruh di `vector` (heap) atau `static`.

**Biasanya digabungkan dengan:** [C++ memori](cpp/06-memory-smart-pointer.md). Bahasa ber-GC: kamu tetap bisa “bocor” secara logis jika menyimpan referensi di cache global tanpa batas.

**Jangan:** menyamakan `new` Java dengan `new` C++. Java `new` selalu heap + GC. C++ `new` wajib dipasangkan penghapusan atau smart pointer.

## Pass-by-value dan pass-by-reference

**Untuk apa:** meramal apakah fungsi yang mengubah parameter akan mengubah variabel pemanggil.

Istilah yang membingungkan karena tiap bahasa memakai kata yang sama untuk hal berbeda.

Ringkas yang dipakai di tugas:

| Bahasa | Argumen biasa | Objek / array | Cara mengubah pemanggil |
|---|---|---|---|
| C++ | salin nilai | `T&` alias, `T*` alamat, `T` salin | `void f(int& x)` atau pointer |
| Java | salin **referensi** | isi objek bisa diubah; nama pemanggil tidak bisa diarahkan ulang | `list.add` berubah; `x = new ...` di dalam method tidak mengganti variabel luar |
| Python | salin **referensi** (binding) | list/dict berubah; `x = 3` hanya lokal | mutasi objek vs assignment |
| JavaScript | seperti Java | `obj.x = 1` berubah; `obj = {}` tidak mengganti luar | sama |

**Contoh implementasi:**

```cpp
void tambah_salin(int x) { x += 1; }
void tambah_ref(int& x) { x += 1; }

int a = 4;
tambah_salin(a); // a tetap 4
tambah_ref(a);   // a jadi 5
```

```python
def tambah_angka(x):
    x = x + 1  # nama lokal baru

def tambah_list(xs):
    xs.append(1)  # objek yang sama

n = 4
tambah_angka(n)   # n tetap 4
data = [4]
tambah_list(data) # data jadi [4, 1]
```

```js
function gantiNama(obj) {
  obj = { nama: "Baru" }; // hanya lokal
}
function gantiIsi(obj) {
  obj.nama = "Baru";      // objek luar berubah
}
const p = { nama: "Lama" };
gantiNama(p);
gantiIsi(p);
```

**Yang terjadi:**

- Angka, boolean, dan (di Java) primitif selalu disalin.
- “Objek dikirim by reference” di Java/JS/Python lebih jujur disebut: **yang disalin adalah alamat/referensi**.
- Assignment ke parameter (`x = ...`) mengganti nama lokal, bukan nama pemanggil, kecuali C++ `T&`.
- Mutasi isi (`append`, `add`, `push`, `obj.field =`) terlihat di luar.

**Biasanya digabungkan dengan:** [Mutasi versus salinan](#mutasi-versus-salinan).

**Jangan:** menulis `void tukar(int a, int b)` di C++ dan berharap pemanggil tertukar. Butuh referensi atau pointer.

## Referensi, pointer, dan alias

**Untuk apa:** membedakan **nama lain** (referensi C++), **kotak alamat** (pointer), dan **referensi objek** (Java/JS/Python).

```cpp
int stok = 5;
int& alias = stok;   // wajib hidup, tidak null
int* p = &stok;      // boleh p = nullptr
alias = 7;           // stok jadi 7
*p = 8;              // stok jadi 8
```

```java
String s = null;           // referensi boleh kosong
s = new String("toko");
```

**Yang terjadi:** `alias` tidak punya identitas terpisah; itu `stok`. `p` menyimpan alamat; `*p` adalah isi di alamat itu. Di Java, `s` adalah referensi; belum ada operator `*` untuk dereferensi.

C++ `const T&` mengirim objek besar tanpa salin dan tanpa izinkan ubah. Pola ini tidak ada di Java (tidak ada const objek yang ketat di tipe), di JS `const` hanya mengunci binding, di Python tidak ada padanan langsung.

**Contoh implementasi:** fungsi yang hanya membaca string panjang.

```cpp
int panjang(const std::string& s) { return int(s.size()); }
```

**Yang terjadi:** tidak menyalin isi string, tidak bisa `s += "x"` di dalam fungsi.

**Biasanya digabungkan dengan:** [C++ 01](cpp/01-dasar-tipe-variabel.md) dan [C++ 06](cpp/06-memory-smart-pointer.md).

**Jangan:** mengembalikan referensi ke lokal. Lihat [Stack, heap](#stack-heap-dan-hidupnya-data).

## Mutasi versus salinan

**Untuk apa:** memilih apakah mengubah objek yang ada, atau membuat nilai baru. Ini sumber bug berbagi state di React, dan sumber lambat jika menyalin besar-besaran di C++.

Objek **mutable:** list, dict, array, `StringBuilder`, `vector`.
Nilai **immutable:** `int`, `tuple` Python, `str` Python, `String` Java, banyak `const` C++.

```python
a = [1, 2]
b = a          # b dan a nama untuk list yang sama
c = a.copy()   # list baru
b.append(3)    # a juga [1, 2, 3]
c.append(9)    # a tidak berubah
```

```js
const a = { harga: 10 };
const b = a;
b.harga = 20; // a.harga juga 20
const c = { ...a, harga: 30 }; // salinan dangkal
```

```java
String s = "ab";
s.concat("c"); // hasil dibuang; s tetap "ab"
s = s + "c";   // s menunjuk String baru
```

**Yang terjadi:**

- Assignment `b = a` pada objek **tidak** menyalin isi; dua nama, satu objek.
- Method yang mengembalikan nilai baru (`concat`, `replace`, slice string) tidak mengubah aslinya kecuali kamu menugaskan ulang.
- Method yang `void` / mengembalikan `None` (`append`, `sort` Python, `push`) biasanya memutasi.
- Salinan dangkal (`copy()`, `{...a}`) tidak menyalin objek di dalamnya. List di dalam list masih dibagi.

**Contoh implementasi:** React state. Jangan `keranjang.push(item)` lalu `setKeranjang(keranjang)`. Mutasi diam-diam membuat React sulit mendeteksi perubahan. Buat array baru.

**Biasanya digabungkan dengan:** [React state](react/02-state-event-form.md), [JS object](javascript/04-object-destructure-spread.md), [Python list](python/01-dasar-tipe-variabel.md).

**Jangan:** mengira `const` di JS atau `final` di Java mengunci isi objek.

## Kesamaan nilai versus kesamaan identitas

**Untuk apa:** menghindari `==` yang salah makna saat membandingkan objek, teks, atau pecahan.

```python
a = [1, 2]
b = [1, 2]
print(a == b)   # True: nilai sama
print(a is b)   # False: objek berbeda
print(a is a)   # True
```

```java
String x = new String("toko");
String y = new String("toko");
boolean salah = (x == y);      // identitas
boolean benar = x.equals(y);   // isi
```

```js
console.log(1 == "1");   // true: koersi
console.log(1 === "1");  // false
console.log(Object.is(NaN, NaN)); // true, beda dengan ===
```

**Yang terjadi:**

- Identitas: apakah ini kotak memori yang sama?
- Nilai: apakah isinya dianggap sama menurut aturan tipe?
- JS `==` menambah konversi tipe. Pakai `===` di kode baru.
- `NaN != NaN` di IEEE; `Object.is` / `math.isnan` / `Number.isNaN` untuk cek.

**Biasanya digabungkan dengan:** operator di bab 01 tiap bahasa.

**Jangan:** memakai `==` untuk `String` Java atau pecahan uang.

## Error, exception, dan status

**Untuk apa:** membedakan “nilai tidak valid yang masih bisa dilanjutkan” dengan “kejadian yang memutus alur normal”.

Tiga gaya yang campur di proyek nyata:

1. **Nilai khusus:** `null`, `undefined`, `None`, `-1`, `optional`.
2. **Kode status:** HTTP 404, `errno`, `Result` / `std::optional`.
3. **Exception:** `throw` / `raise` yang meloncat ke `catch` / `except`.

```python
def bagi(a, b):
    if b == 0:
        raise ValueError("pembagi nol")
    return a / b

try:
    print(bagi(8, 0))
except ValueError as e:
    print("gagal:", e)
```

```java
try {
    int x = Integer.parseInt("bukan-angka");
} catch (NumberFormatException e) {
    System.out.println("bukan integer");
}
```

```js
try {
  JSON.parse("{");
} catch (e) {
  console.log("JSON rusak");
}
```

```cpp
// C++ banyak API yang tidak throw. Cek sendiri.
if (!cin) { /* input gagal */ }
```

**Yang terjadi:**

- Exception **bukan** pengganti `if`. Validasi input pengguna sering lebih jelas dengan pesan, bukan stack trace.
- Exception yang tidak ditangkap menghentikan thread / proses (atau menampilkan error overlay di Next.js).
- Error jaringan (`fetch` gagal) berbeda dari HTTP 404: yang pertama mungkin exception / reject, yang kedua respons sah dengan status.
- Di C++ kontes, exception jarang dipakai; WA/TLE lebih sering dari logika dan overflow.

Pilih gaya:

| Situasi | Lebih cocok |
|---|---|
| input user salah | validasi, pesan, kode status |
| file tidak ada | exception atau `optional` + pesan |
| invariant internal pecah | exception / panic / assert |
| API HTTP | status + body error, jangan 200 + “gagal” diam-diam |
| loop ketat CP | cek `if`, bukan `throw` |

**Contoh implementasi:** form web. Kosongnya email → tampilkan teks di bawah input. Jangan `throw` sampai server. Server yang sama boleh mengembalikan 422 jika klien menembak API langsung.

**Biasanya digabungkan dengan:** [JS kondisi dan error](javascript/02-kondisi-loop-error.md), [Java exception](java/06-exception-file-io.md), [React fetch](react/10-fetch-pola-loading-error.md), [Laravel validasi](laravel/04-validasi-rules-lengkap.md).

**Jangan:** menelan exception kosong (`except: pass` / `catch (e) {}`). Bug menghilang tanpa jejak.

## Kapan pilih Python, Java, C++, atau JavaScript

**Untuk apa:** memilih alat dari **pekerjaan**, bukan dari bahasa yang kebetulan sedang dibuka.

```text
Tampil di browser, klik, form, DOM
  → JavaScript (lalu React/Next jika UI tumbuh)

Data CSV, hitung, grafik, skrip cepat
  → Python + pandas / matplotlib

Tugas PBO, Android, backend JVM, tipe ketat
  → Java

Kontes, game native, Unreal, kontrol memori
  → C++

API + database + halaman server klasik
  → PHP/Laravel (lihat ensiklopedia Laravel), atau Java/JS di stack lain
```

**Contoh implementasi:** empat tugas seminggu.

1. Filter produk di halaman statis → JS + HTML, bukan C++.
2. Analisis nilai ujian dari CSV → Python.
3. Class `Pembayaran` dan turunannya → Java (atau C++ jika itu mata kuliah PBO C++).
4. Soal `n = 2e5` jumlah rentang + update → C++ (Python sering TLE).

**Yang terjadi:** bahasa yang “lebih hebat” tidak ada. Yang ada: runtime (browser / JVM / interpreter / native), ekosistem, dan kecepatan menulis versus kecepatan jalan.

Perbandingan jujur untuk mahasiswa:

| | Python | Java | C++ | JavaScript |
|---|---|---|---|---|
| Mulai ngetik | sangat cepat | sedang (boilerplate) | sedang | cepat di browser |
| Tipe | dinamis | statis | statis | dinamis (+ TS opsional) |
| Memori | boros, GC | GC | kamu atur | GC |
| Loop 1e8 | lambat | sedang | cepat | sedang di engine modern |
| Tempat jalan | terminal, notebook | JVM | native | browser atau Node |
| Bahaya khas | indent, mutable default | `==` String, null | UB, pointer, overflow | `==`, async, DOM null |

**Biasanya digabungkan dengan:** versi cepat [python.md](../python.md), [java.md](../java.md), [cpp.md](../cpp.md), [javascript.md](../javascript.md).

**Jangan:** memaksa satu bahasa untuk semua. Skrip 20 baris pembersih CSV di C++ membuang waktu. Dijkstra `n = 1e5` di Python murni sering melewati limit.

## Cara baca dokumentasi

**Untuk apa:** menemukan kontrak sebuah fungsi: nama, argumen, hasil, efek samping, dan kapan gagal — tanpa menghafal seluruh situs.

Dokumentasi resmi hampir selalu punya bagian yang sama, hanya judulnya beda:

1. **Signature / prototipe** — nama, parameter, tipe kembali.
2. **Deskripsi satu paragraf** — untuk apa, bukan tutorial panjang.
3. **Parameter** — unit, boleh null?, rentang.
4. **Return** — apa yang dijanjikan; `void` / `None` / `undefined` berarti “tidak ada nilai berguna”.
5. **Throws / Raises / Errors** — kegagalan.
6. **Contoh** — potongan minimal.
7. **See also** — fungsi tetangga yang lebih tepat.

**Contoh implementasi:** kamu ingin “cari posisi angka di list terurut”.

- Python: buka docs `bisect`. Baca `bisect_left(a, x)` → indeks sisip agar tetap terurut. Bukan `list.index` (`O(n)`, harus ada).
- C++: `std::lower_bound` butuh rentang **terurut**. Return **iterator**, bukan indeks. Kurangi `begin()` untuk indeks.
- Java: `Collections.binarySearch` return negatif jika tidak ketemu; rumusnya `-(insertionPoint) - 1`.
- JS: `Array.prototype.findIndex` linier; tidak ada binary search di standar. Jangan mengira nama mirip = kompleksitas mirip.

**Yang terjadi:** setelah membaca **return** dan **prasyarat**, kamu tidak salah memakai hasil. Banyak bug lahir dari mengira fungsi mengembalikan objek, padahal `None`, atau mengira ia menyalin, padahal memutasi.

Cara praktis 5 menit:

```text
1. Cari nama persis di docs resmi, bukan hasil blog acak dulu.
2. Baca prototipe keras-keras: f(koleksi, nilai) -> indeks
3. Cari kata: mutate, in-place, copy, thread-safe, O(
4. Jalankan contoh resmi utuh, lalu ubah SATU argumen.
5. Baru buka ensiklopedia lokal untuk terjemahan Indonesia.
```

Tempat docs yang dipakai catatan ini:

- Python: docs.python.org, NumPy/pandas reference.
- Java: docs.oracle.com / Javadoc modul yang diinstal.
- C++: cppreference.com (bukan tutorial acak yang masih C++98 tanpa catatan).
- JavaScript: developer.mozilla.org (MDN).
- React / Next: react.dev, nextjs.org/docs.
- Laravel: laravel.com/docs versi yang diinstal.

**Biasanya digabungkan dengan:** ensiklopedia setempat sebagai terjemahan + contoh toko/kuliah, bukan sebagai pengganti kontrak resmi.

**Jangan:** menyalin contoh Stack Overflow yang tidak menyebut versi. Method yang dihapus di Java 21 atau API Next yang ganti di App Router akan menyesatkan.

## Cara meniru contoh resmi tanpa nyalin buta

**Untuk apa:** mengubah contoh dokumentasi menjadi punya, supaya kamu tahu baris mana yang wajib dan mana yang hiasan.

Langkah yang sama untuk semua bahasa:

1. Jalankan contoh **tanpa ubah**. Jika gagal, masalahnya lingkungan (versi, import, path), bukan logikamu.
2. Ganti literal (`"Alice"` → namamu, `42` → angka soal).
3. Cetak tipe / `sizeof` / `typeof` / `type()` dari hasil.
4. Masukkan nilai aneh: kosong, nol, negatif, `null`.
5. Baru bungkus jadi fungsi dengan nama domain (`jumlah_rentang`, `label_stok`).

**Contoh implementasi:** docs `sort` biasanya mengurut naik. Tugasmu butuh turun. Yang diubah hanya comparator / `reverse`, bukan algoritma baru.

```python
angka = [3, 1, 2]
print(sorted(angka))           # [1, 2, 3] — salinan
angka.sort(reverse=True)       # mutasi: [3, 2, 1]
```

**Yang terjadi:** kamu belajar dari docs bahwa ada dua API: `sorted` (baru) dan `list.sort` (in-place). Itu lebih berharga daripada menghafal lima tutorial.

**Biasanya digabungkan dengan:** [Cara baca dokumentasi](#cara-baca-dokumentasi) dan format **Untuk apa / contoh / Yang terjadi** di tiap bab ensiklopedia.

**Jangan:** menempel banyak contoh ke satu file lalu “tidak ada yang jalan”. Satu contoh, satu percobaan.

## Peta ke bab ensiklopedia

**Untuk apa:** kembali ke katalog API setelah teori ini cukup.

| Gagasan di bab ini | Lanjut ke |
|---|---|
| Tipe dan operator | Python/JS/C++/Java bab 01 |
| Fungsi, scope | [JS 03](javascript/03-fungsi-scope-this-closure.md), [Python 02](python/02-kontrol-fungsi-modul.md), [C++ 02](cpp/02-kontrol-fungsi-class.md) |
| Koleksi mutable | [Python 01 list/dict](python/01-dasar-tipe-variabel.md), [Java Collections](java/05-collections-list-set-map.md), [C++ STL](cpp/03-stl-vector-string-array.md) |
| Memori native | [C++ 06](cpp/06-memory-smart-pointer.md) |
| Exception file | [Java 06](java/06-exception-file-io.md), [Python 03](python/03-file-pathlib-json-csv.md) |
| Error UI / fetch | [JS 02](javascript/02-kondisi-loop-error.md), [React 10](react/10-fetch-pola-loading-error.md) |
| Kompleksitas + algoritma | [cp.md](../cp.md), [ensiklopedia/cp](cp/README.md) |
| Latihan algoritma harian | `KULIAH/ComprogLearning/CP` (jangan disalin ke sini) |

**Contoh implementasi:** setelah membaca [Mutasi](#mutasi-versus-salinan), buka `list.append` di ensiklopedia Python dan `ArrayList.add` di Java. Bandingkan **Yang terjadi**.

**Yang terjadi:** katalog per bahasa terasa sebagai contoh, bukan agama terpisah.

**Biasanya digabungkan dengan:** [README ensiklopedia](README.md) untuk jumlah baris dan urutan bab. Versi cepat tetap di folder atas: `python.md`, `cpp.md`, `java.md`, `javascript.md`, `cp.md`.

---

Bab lama tidak diubah oleh file ini. Jika suatu API butuh contoh baru, tambah di bab bahasanya; jika suatu gagasan lintas bahasa bolong, tambah di sini.
