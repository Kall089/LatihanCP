# 🛠 Proyek Blok 1 — Class `Pecahan`

**Estimasi:** 2–3 jam
**Berkas kerja:** `starter/pecahan.cpp`
**Jangan buka** `referensi/` sebelum bagian utama jalan.

---

## Kenapa Pecahan

Pecahan adalah contoh terkecil yang punya **invariant sungguhan**. Tidak seperti
`Titik2D` di Latihan 1 yang sebenarnya tidak butuh enkapsulasi, pecahan punya
tiga aturan yang harus dijaga terus-menerus — dan menjaganya secara manual dari
luar kelas adalah mimpi buruk yang persis digambarkan di teori bagian 1.4.

---

## Bagian 1 — Invariant

Class `Pecahan` **harus** menjaga ketiga aturan ini setiap saat, tanpa kecuali,
setelah operasi apa pun:

```
1. penyebut_ != 0                 tidak pernah nol
2. penyebut_ > 0                  tandanya selalu dibawa pembilang
                                  jadi -1/2 dan 1/-2 keduanya disimpan sebagai -1/2
3. FPB(|pembilang_|, penyebut_) == 1
                                  selalu dalam bentuk paling sederhana
                                  jadi 2/4 disimpan sebagai 1/2
```

Aturan 2 penting dan sering terlewat. Tanpanya, `1/-2` dan `-1/2` adalah dua
objek berbeda yang nilainya sama — dan perbandingan kesamaan jadi rusak.

**Kasus khusus nol:** `0/5` harus disimpan sebagai `0/1`, bukan `0/5`.
Pikirkan kenapa perhitungan FPB biasa tidak otomatis menghasilkan ini.

---

## Bagian 2 — Antarmuka yang Diminta

```cpp
class Pecahan {
public:
    // ── Pembuatan ────────────────────────────────
    Pecahan();                                  // 0/1
    explicit Pecahan(int bulat);                // bulat/1
    Pecahan(int pembilang, int penyebut);       // disederhanakan otomatis

    // ── Aritmetika (mengembalikan hasil BARU, tidak mengubah diri) ──
    Pecahan tambah(const Pecahan& lain) const;
    Pecahan kurang(const Pecahan& lain) const;
    Pecahan kali  (const Pecahan& lain) const;
    Pecahan bagi  (const Pecahan& lain) const;

    // ── Perbandingan ─────────────────────────────
    bool samaDengan (const Pecahan& lain) const;
    bool lebihKecil (const Pecahan& lain) const;

    // ── Query ────────────────────────────────────
    int    pembilang() const;
    int    penyebut()  const;
    double keDouble()  const;
    bool   negatif()   const;
    Pecahan kebalikan() const;                  // a/b -> b/a

    // ── Keluaran ─────────────────────────────────
    void cetak() const;                         // "3/4", tapi "5" kalau penyebutnya 1

private:
    int pembilang_;
    int penyebut_;
};
```

### Aturan tambahan

- **Semua fungsi yang tidak mengubah objek WAJIB `const`.** Tanpa itu,
  `tambah(const Pecahan&)` sendiri tidak akan bisa dikompilasi.
- **Aritmetika mengembalikan objek baru**, tidak mengubah `this`. Ini disebut
  *value semantics*, dan itu perilaku yang orang harapkan dari bilangan:
  `a.tambah(b)` tidak seharusnya mengubah `a`, sama seperti `3 + 4` tidak
  mengubah `3`.
- **Constructor satu-parameter harus `explicit`.**
- **Penyederhanaan dilakukan di SATU tempat** — sebuah fungsi `private`. Kalau
  kamu menuliskannya di beberapa constructor, kamu sudah mengulangi kesalahan
  yang persis dijelaskan di teori 1.4.

### Kasus tepi yang harus ditangani

| Masukan | Harus jadi | Kenapa |
|---|---|---|
| `Pecahan(1, 0)` | terserah kamu, tapi **harus konsisten** | tulis alasannya di komentar |
| `Pecahan(2, 4)` | `1/2` | penyederhanaan |
| `Pecahan(1, -2)` | `-1/2` | tanda dibawa pembilang |
| `Pecahan(-1, -2)` | `1/2` | dua negatif |
| `Pecahan(0, 5)` | `0/1` | kasus khusus nol |
| `a.bagi(Pecahan(0,1))` | terserah, **konsisten** | pembagian dengan nol |

Untuk dua kasus "terserah kamu": pilih satu pendekatan, terapkan di seluruh
kelas, dan **tulis alasannya di komentar kelas**. Yang dinilai bukan pilihanmu,
melainkan konsistensinya. (Di Blok 7 kamu akan kembali ke sini dan menggantinya
dengan exception.)

---

## Bagian 3 — Program Uji

`starter/pecahan.cpp` sudah berisi `main()` yang menguji semuanya. Keluaran yang
benar:

```
=== Pembuatan ===
0
5
3/4
1/2
-1/2
1/2
0

=== Aritmetika ===
3/4 + 1/2 = 5/4
3/4 - 1/2 = 1/4
3/4 * 1/2 = 3/8
3/4 : 1/2 = 3/2

=== Perbandingan ===
1/2 == 2/4 ? ya
1/2 < 2/3 ? ya
2/3 < 1/2 ? tidak

=== Query ===
3/4 sebagai desimal = 0.75
-1/2 negatif? ya
kebalikan 3/4 = 4/3

=== Penyederhanaan otomatis ===
6/8 = 3/4
100/25 = 4
1/2 + 1/2 = 1
```

Perhatikan tiga baris terakhir. `1/2 + 1/2` harus mencetak `1`, bukan `2/2` atau
`1/1`. Kalau kelasmu benar, ketiganya jalan tanpa usaha tambahan — karena
penyederhanaan dan pencetakan sudah dijaga di dalam kelas.

---

## Bagian 4 — Perubahan Requirement

> **Ini bagian terpenting dari proyek ini. Jangan dilewati.**
>
> Di CP, judge yang bilang solusimu benar. Di OOP tidak ada judge yang bisa
> bilang "desainmu buruk". Umpan baliknya datang dari sini: **desain yang baik
> membuat perubahan terasa mudah; desain yang buruk membuatnya menyakitkan.**
>
> Kerjakan setelah Bagian 1–3 jalan. Untuk setiap perubahan, **hitung berapa
> baris di luar class yang harus kamu sentuh** — itu angka yang mengukur
> desainmu.

### Perubahan A — Ganti representasi internal ke `long long`

`3/4 + ...` berulang kali bisa membuat pembilang meledak melebihi `int`. Ubah
`pembilang_` dan `penyebut_` menjadi `long long`.

**Pertanyaan:** berapa baris **di luar** `class Pecahan` yang harus diubah?

Kalau jawabannya **nol**, enkapsulasimu bekerja — persis seperti yang dijanjikan
teori bagian 1.5. Kalau jawabannya lebih dari nol, cari tahu kenapa: kemungkinan
besar ada anggota yang bocor keluar, atau getter yang mengembalikan `int`
sehingga memaksa pemanggil ikut berubah.

### Perubahan B — Tambah `Pecahan::dariDesimal(double nilai, int presisi)`

*Named constructor* yang mengubah desimal ke pecahan. `dariDesimal(0.75, 100)`
menghasilkan `3/4`; `dariDesimal(0.333, 1000)` menghasilkan `333/1000`.

**Pertanyaan:** kenapa ini harus `static`, dan kenapa ia tidak boleh jadi
constructor `Pecahan(double)`? (Jawabannya ada di solusi Latihan 6.)

### Perubahan C — Tambah `pangkat(int n)`

`Pecahan(2,3).pangkat(2)` → `4/9`. Tangani `n` negatif: `pangkat(-1)` sama
dengan kebalikannya. Tangani `n == 0` → `1/1`.

**Pertanyaan:** apakah kamu perlu menyentuh bagian lain dari kelas untuk
menambahkan ini? Kalau tidak, kenapa? (Petunjuk: kamu bisa menyusunnya hanya
dari `kali()` dan `kebalikan()` yang sudah ada — itu tanda antarmukamu cukup.)

### Perubahan D — Requirement yang berubah, bukan bertambah

Klien baru menginginkan pecahan **tidak** disederhanakan otomatis. Mereka mau
`2/4` tetap tersimpan sebagai `2/4`, tapi perbandingan `1/2 == 2/4` **tetap**
harus `true`.

Ini perubahan yang jahat, dan sengaja. Kerjakan sebagai **percobaan pikiran**,
tidak perlu diimplementasikan:

1. Bagian mana saja dari kelasmu yang harus berubah?
2. Apakah `samaDengan()` masih bisa membandingkan pembilang dan penyebut
   secara langsung? Apa penggantinya?
3. Invariant nomor 3 hilang. Apakah kelas ini masih layak jadi `class`, atau
   sudah cukup jadi `struct`?
4. Bisakah kamu mendukung **kedua** perilaku dalam satu kelas? Apakah itu ide
   yang bagus, atau justru tanda seharusnya ada dua tipe berbeda?

Pertanyaan 4 adalah pertanyaan desain sungguhan yang akan kamu temui berulang
kali. Tidak ada jawaban yang benar untuk semua kasus.

---

## Checklist Selesai

- [ ] Ketiga invariant terjaga setelah **setiap** operasi, termasuk aritmetika
- [ ] Penyederhanaan ditulis di **satu** fungsi `private`
- [ ] Semua fungsi yang tidak mengubah objek sudah `const`
- [ ] Constructor satu-parameter sudah `explicit`
- [ ] `cetak()` mencetak `5`, bukan `5/1`
- [ ] Keluaran program uji cocok persis
- [ ] Kompilasi bersih dengan `g++ -std=c++17 -Wall -Wextra`
- [ ] Perubahan A dikerjakan, dan kamu **tahu angka** berapa baris luar yang berubah
- [ ] Perubahan B dan C dikerjakan
- [ ] Perubahan D dijawab tertulis, meski tidak diimplementasikan

---

## Cara Menilai Desainmu Sendiri

Setelah selesai, tanyakan lima hal ini:

1. **Bisakah seseorang membuat `Pecahan` yang tidak valid?** Kalau ya, dari mana
   celahnya?
2. **Berapa tempat yang tahu cara menyederhanakan pecahan?** Jawaban yang benar: satu.
3. **Kalau saya ganti `int` jadi `long long`, berapa baris di luar kelas yang berubah?**
   Jawaban yang benar: nol.
4. **Apakah ada fungsi publik yang tidak akan pernah dipakai siapa pun?**
   Antarmuka yang terlalu lebar juga masalah, bukan cuma yang terlalu sempit.
5. **Apakah `cetak()` sebaiknya ada di dalam kelas?** Ini pertanyaan jebakan yang
   jujur — mencetak ke `cout` mengikat kelas ini ke konsol. Kamu akan
   memperbaikinya di Blok 2 dengan `operator<<`, dan mempertanyakannya lagi di
   Blok 9 saat membahas Single Responsibility.
