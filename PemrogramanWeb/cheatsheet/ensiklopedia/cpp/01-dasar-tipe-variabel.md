# 01 — Dasar: tipe, variabel, const, referensi, pointer

[← README](README.md) · [Lanjut: kontrol, fungsi, class →](02-kontrol-fungsi-class.md)

Program C++ menyimpan data di **variabel**. Setiap variabel punya **tipe**: bilangan, huruf, teks, atau alamat. Unreal memakai tipe yang sama di logika murni, plus tipe engine (`int32`, `float`, `FString`) yang dijelaskan di catatan tiap entri.

## Daftar isi

- [int](#int)
- [unsigned int](#unsigned-int)
- [long long](#long-long)
- [float](#float)
- [double](#double)
- [bool](#bool)
- [char](#char)
- [std::string](#stdstring)
- [auto](#auto)
- [const](#const)
- [constexpr](#constexpr)
- [referensi](#referensi)
- [pointer](#pointer)
- [nullptr](#nullptr)
- [size_t](#size_t)
- [std::int32_t](#stdint32_t)
- [enum class](#enum-class)
- [using alias](#using-alias)
- [sizeof](#sizeof)
- [static_cast](#static_cast)
- [std::string_view](#stdstring_view)
- [cin dan cout](#cin-dan-cout)
- [literal dan sufiks](#literal-dan-sufiks)
- [decltype](#decltype)
- [array C](#array-c)
- [static lokal](#static-lokal)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## int

**Tipe:** tipe data (bilangan bulat bertanda)

**Untuk apa:** menghitung stok, skor, indeks, umur — sesuatu yang tidak punya koma.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int stokBuku = 12;
    int terjual = 3;
    int sisa = stokBuku - terjual;
    int bonus = -1;  // int boleh negatif

    std::cout << "Sisa: " << sisa << '\n';
    std::cout << "Bonus contoh: " << bonus << '\n';
    return 0;
}
```

**Yang terjadi:** `stokBuku` dan `terjual` menampung bilangan bulat. Pengurangan menghasilkan `9`. `int` di hampir semua komputer sekarang 32-bit (kira-kira −2 miliar sampai 2 miliar). Overflow (melewati batas) *membungkus* secara tidak terdefinisi untuk `int` bertanda — jangan andalkan hasilnya.

Di Unreal, tipe yang setara dan lebih eksplisit adalah `int32` (`#include "CoreMinimal.h"`). Banyak API engine memakai `int32`, bukan `int` mentah.

**Biasanya digabungkan dengan:** loop `for`, indeks `vector`, `if` pembanding, dan `size_t` saat ukuran kontainer (lihat bawah).

**Jangan:** memakai `int` untuk uang pecahan (pakai `int` sen, atau `double` dengan hati-hati); jangan memakai `int` untuk ukuran memori yang bisa lebih besar dari 2 miliar di mesin 64-bit — pertimbangkan `size_t` atau `int64_t`.

## unsigned int

**Tipe:** tipe data (bilangan bulat tanpa tanda)

**Untuk apa:** nilai yang secara logika tidak negatif: jumlah item, flag bit, ukuran yang dijamin ≥ 0.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    unsigned int jumlahKursi = 4;
    unsigned int tamuDatang = 6;

    std::cout << "Kursi: " << jumlahKursi << '\n';

    // Bahaya klasik: pengurangan unsigned
    unsigned int kurang = jumlahKursi - tamuDatang;
    std::cout << "4u - 6u = " << kurang << '\n';
    return 0;
}
```

**Yang terjadi:** baris pertama mencetak `4`. Baris kedua **tidak** mencetak `-2`. Karena `unsigned` tidak punya negatif, `4 - 6` membungkus menjadi bilangan sangat besar (dekat `UINT_MAX`). Ini sumber bug loop yang “jalan selamanya”.

**Biasanya digabungkan dengan:** operasi bit, ukuran buffer, API C lama. Di Unreal: `uint32`, `uint8`.

**Jangan:** mencampur `unsigned` dan `signed` dalam perbandingan (`int i = -1; unsigned u = 1; i < u` bisa mengejutkan). Jangan memakai `unsigned` hanya “supaya tidak negatif” jika pengurangan masih mungkin — lebih aman `int` + cek.

## long long

**Tipe:** tipe data (bilangan bulat 64-bit, minimal)

**Untuk apa:** ID besar, timestamp dalam milidetik, skor yang bisa melewati 2 miliar.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    long long idPesanan = 1'000'000'000'000LL;  // C++14: pemisah '
    long long milidetik = 1'700'000'000'000LL;

    std::cout << "ID: " << idPesanan << '\n';
    std::cout << "ms: " << milidetik << '\n';
    return 0;
}
```

**Yang terjadi:** program mencetak ID 12 digit dan timestamp. `long long` dijamin minimal 64-bit. `int` biasa bisa overflow jika kamu menaruh angka sebesar itu.

Di Unreal: `int64`. Jangan bingung dengan `long` — ukuran `long` di Windows MSVC 32-bit, di Linux 64-bit.

**Biasanya digabungkan dengan:** file besar, hash, ID database, `std::chrono`.

**Jangan:** menganggap `long` selalu 64-bit. Tulis `long long` atau `std::int64_t` jika kamu butuh 64-bit di semua platform.

## float

**Tipe:** tipe data (pecahan presisi tunggal, biasanya 32-bit IEEE-754)

**Untuk apa:** posisi, kecepatan, persentase kasar, nilai yang butuh koma tetapi tidak butuh banyak digit.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <iomanip>

int main() {
    float harga = 19.99f;   // sufiks f = float, bukan double
    float diskon = 0.15f;
    float bayar = harga * (1.0f - diskon);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Bayar: " << bayar << '\n';
    std::cout << "0.1f + 0.2f = " << (0.1f + 0.2f) << '\n';
    return 0;
}
```

**Yang terjadi:** `bayar` sekitar `16.991501` — bukan uang yang “bersih”. `0.1f + 0.2f` **tidak** persis `0.3`. Itu sifat pecahan biner, bukan bug compiler. Unreal memakai `float` sangat intensif: `FVector` adalah tiga `float` (`X`, `Y`, `Z`).

**Biasanya digabungkan dengan:** `FVector`, `DeltaTime` di `Tick`, interpolasi, `std::sqrt`.

**Jangan:** membandingkan `float` dengan `==` untuk hasil hitungan (`if (x == 0.3f)`). Bandingkan selisih dengan epsilon, atau di Unreal pakai `FMath::IsNearlyEqual`. Jangan pakai `float` sebagai uang akunting.

## double

**Tipe:** tipe data (pecahan presisi ganda, biasanya 64-bit)

**Untuk apa:** hitungan ilmiah, rata-rata yang butuh lebih banyak digit, default literal koma di C++ (`3.14` adalah `double`, bukan `float`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    double jariJari = 6.5;
    double luas = 3.141592653589793 * jariJari * jariJari;
    double akar = std::sqrt(2.0);

    std::cout << std::setprecision(15);
    std::cout << "Luas: " << luas << '\n';
    std::cout << "sqrt(2): " << akar << '\n';
    return 0;
}
```

**Yang terjadi:** `luas` dan `akar` dicetak dengan banyak digit. `double` lebih teliti daripada `float`, tetapi tetap tidak sempurna untuk pecahan desimal seperti `0.1`.

Di Unreal, hampir semua transform dunia adalah `float`. `double` muncul di beberapa path presisi tinggi (large world coordinates di UE5). Jangan asal ganti semua `float` engine menjadi `double`.

**Biasanya digabungkan dengan:** `<cmath>`, statistik, file ilmiah.

**Jangan:** mencampur `float` dan `double` tanpa sadar (promosi implisit). Jangan mengira `double` “tepat” untuk uang.

## bool

**Tipe:** tipe data (benar / salah)

**Untuk apa:** flag: “apakah pintu terbuka”, “apakah stok habis”, hasil perbandingan.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int stok = 0;
    bool habis = (stok <= 0);
    bool tokoBuka = true;

    if (habis && tokoBuka) {
        std::cout << "Toko buka tetapi stok habis\n";
    }

    std::cout << std::boolalpha;  // cetak true/false, bukan 1/0
    std::cout << "habis: " << habis << '\n';
    return 0;
}
```

**Yang terjadi:** `habis` menjadi `true` karena `stok` 0. Kondisi `&&` terpenuhi, pesan pertama tercetak, lalu `habis: true`. Di C++, `true` dan `false` adalah kata kunci. Angka `0` dianggap false, selain itu true jika dikonversi — tetapi lebih jelas menulis `bool` sungguhan.

Di Unreal: `bool` dan `uint8` kadang dipakai di `UPROPERTY` (bitfield). `UPROPERTY` `bool` muncul sebagai checkbox di Details.

**Biasanya digabungkan dengan:** `if`, `while`, operator `&&` `||` `!`, `UPROPERTY` flag.

**Jangan:** menulis `if (habis == true)` — cukup `if (habis)`. Jangan memakai `int` 0/1 jika yang kamu maksud ya/tidak.

## char

**Tipe:** tipe data (satu karakter, biasanya 1 byte)

**Untuk apa:** huruf tunggal, kode ASCII, mengolah teks per karakter (lebih sering kamu butuh `std::string`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <cctype>

int main() {
    char inisial = 'H';
    char digit = '7';

    std::cout << "Inisial: " << inisial << '\n';
    std::cout << "Kode angka '7': " << static_cast<int>(digit) << '\n';
    std::cout << "Huruf kecil: " << static_cast<char>(std::tolower(inisial)) << '\n';
    return 0;
}
```

**Yang terjadi:** `'H'` tercetak sebagai huruf. `'7'` secara numerik adalah kode ASCII 55, bukan bilangan 7. `std::tolower` mengembalikan `int`; kita cast kembali ke `char` agar tercetak sebagai huruf `h`.

`char` bisa signed atau unsigned tergantung compiler. Untuk byte mentah, lebih jelas `unsigned char` atau `std::byte` (C++17).

Di Unreal, karakter lebar sering `TCHAR`; teks pakai `FString` / `FText` / `FName`.

**Biasanya digabungkan dengan:** `std::string`, loop karakter, `<cctype>`.

**Jangan:** memakai `char` untuk menyimpan teks panjang. Jangan membandingkan `char` dengan string (`c == "H"` salah; `"H"` adalah array).

## std::string

**Tipe:** class (pustaka standar, header `<string>`)

**Untuk apa:** teks yang bisa bertambah: nama produk, pesan, path file di program C++ biasa.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string merek = "Pensil";
    std::string tipe = "2B";
    std::string label = merek + " " + tipe;

    label += " (baru)";
    std::cout << label << '\n';
    std::cout << "Panjang: " << label.size() << '\n';
    std::cout << "Huruf 0: " << label.at(0) << '\n';

    if (label.find("2B") != std::string::npos) {
        std::cout << "Ketemu kode 2B\n";
    }
    return 0;
}
```

**Yang terjadi:** `+` menyambung string menjadi `Pensil 2B`, lalu `+=` menambah ` (baru)`. `size()` menghitung karakter. `at(0)` mengambil `P` dan melempar exception jika indeks liar (berbeda dari `[]` yang tidak mengecek). `find` mengembalikan posisi atau `npos` jika tidak ada.

Di Unreal, teks UI / nama asset memakai `FString`, `FName` (identitas cepat), `FText` (bisa dilokalisasi). `std::string` tetap sah di utilitas non-refleksi, tetapi `UPROPERTY` tidak mengerti `std::string`.

**Biasanya digabungkan dengan:** `std::getline`, `std::stringstream`, `std::vector<std::string>`, `std::map<std::string, int>`.

**Jangan:** membandingkan isi dengan `==` pada `char*` tanpa hati-hati; pada `std::string`, `==` membandingkan isi — itu yang kamu inginkan. Jangan memakai `std::string` sebagai `UPROPERTY`. Jangan mengira `size()` menghitung “huruf manusia” pada UTF-8 multibyte.

## auto

**Tipe:** penentu tipe (compiler menebak dari inisialisasi)

**Untuk apa:** mempersingkat tipe yang panjang (`std::map<std::string, int>::iterator`) tanpa kehilangan tipe sungguhan saat compile.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    auto jumlah = 10;            // int
    auto harga = 12.5;           // double (bukan float!)
    auto nama = std::string{"Buku"};
    auto daftar = std::vector<int>{3, 1, 4};

    std::cout << jumlah << ' ' << harga << ' ' << nama << '\n';
    std::cout << "Isi pertama: " << daftar.front() << '\n';
    return 0;
}
```

**Yang terjadi:** compiler menetapkan `jumlah` sebagai `int`, `harga` sebagai `double` (literal `12.5` adalah double), `nama` sebagai `std::string`, `daftar` sebagai `vector<int>`. `auto` bukan tipe dinamis seperti JavaScript. Setelah compile, tipenya kaku.

`auto&` mengikat referensi; `const auto&` membaca tanpa salin. `auto` sendirian pada objek besar bisa menyalin — mahal.

**Biasanya digabungkan dengan:** iterator, `std::make_unique`, structured binding (`auto [k, v]`), lambda.

**Jangan:** menulis `auto harga = 12.5f` lalu mengira itu `double`. Jangan memakai `auto` jika nama tipe penting untuk dibaca manusia (`auto x = f()` yang mengembalikan `HandleKhusus`). Jangan `auto` tanpa inisialisasi — tidak compile.

## const

**Tipe:** kualifier (nilai tidak boleh ditugaskan ulang lewat nama itu)

**Untuk apa:** menandai “ini tidak berubah”, supaya compiler menolak salah tulis dan orang lain tidak mengubah argumen.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int hitungPajak(const int harga) {
    // harga = harga + 1;  // error: const
    return harga / 10;
}

int main() {
    const int batasStok = 100;
    const std::string toko = "Toko Belajar";

    std::cout << toko << " batas " << batasStok << '\n';
    std::cout << "Pajak: " << hitungPajak(45000) << '\n';
    return 0;
}
```

**Yang terjadi:** `batasStok` dan `toko` tidak bisa di-`=` ulang. Argumen `harga` di fungsi juga dikunci. Program mencetak nama toko, `100`, dan pajak `4500`.

`const` pada pointer punya dua sisi: `const int* p` = integer-nya const; `int* const p` = pointer-nya const. Lihat entri pointer.

**Biasanya digabungkan dengan:** referensi `const T&`, method `const` pada class, `constexpr`.

**Jangan:** menandai `const` lalu memakai `const_cast` untuk mengubahnya (undefined behavior jika objeknya memang const). Jangan mengira `const std::string` mengunci string global di thread lain — itu bukan mutex.

## constexpr

**Tipe:** kualifier (nilai / fungsi bisa dihitung saat compile)

**Untuk apa:** konstanta yang sungguh-sungguh tetap, ukuran array, lookup tabel kecil.

**Contoh implementasi:**

```cpp
#include <iostream>

constexpr int kuadrat(int n) {
    return n * n;
}

int main() {
    constexpr int sisi = 8;
    constexpr int luas = kuadrat(sisi);
    int papan[luas];  // ukuran diketahui compile-time

    papan[0] = luas;
    std::cout << "Luas papan: " << papan[0] << '\n';
    return 0;
}
```

**Yang terjadi:** `kuadrat(8)` dihitung saat compile menjadi `64`. Array `papan` berukuran 64. Program mencetak `64`. Jika argumen `kuadrat` bukan konstan, fungsi masih bisa dipanggil saat runtime (sejak C++14 untuk banyak kasus).

**Biasanya digabungkan dengan:** `if constexpr` (C++17), template, konstanta matematika.

**Jangan:** memasukkan I/O atau `new` ke dalam `constexpr` (tidak boleh). Jangan memaksa semua fungsi menjadi `constexpr` tanpa manfaat.

## referensi

**Tipe:** alias nama lain untuk objek yang sudah hidup (`T&`)

**Untuk apa:** mengubah argumen di fungsi tanpa salin; menghindari copy `string` / `vector` besar; loop `for (auto& x)`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

void tambahLabel(std::string& teks) {
    teks += " [dicek]";
}

void cetak(const std::string& teks) {
    std::cout << teks << '\n';
}

int main() {
    std::string barang = "Penghapus";
    tambahLabel(barang);
    cetak(barang);

    int stok = 5;
    int& aliasStok = stok;
    aliasStok = 9;
    std::cout << "Stok: " << stok << '\n';
    return 0;
}
```

**Yang terjadi:** `tambahLabel` mengubah `barang` asli menjadi `Penghapus [dicek]` — tidak menyalin string hanya untuk menambah akhiran. `cetak` menerima `const&` jadi tidak menyalin dan tidak mengubah. `aliasStok` adalah nama lain `stok`; menaruh `9` ke alias mengubah `stok` menjadi `9`.

Referensi wajib diikat saat dibuat dan tidak bisa “dipindah” ke objek lain. Tidak ada referensi null yang legal.

**Biasanya digabungkan dengan:** `const`, range-for, operator, getter yang mengembalikan `const T&`.

**Jangan:** mengembalikan referensi ke variabel lokal (`int& f() { int x = 1; return x; }` — dangling). Jangan membuat referensi ke elemen `vector` lalu `push_back` (elemen bisa pindah). Jangan memakai referensi jika kamu butuh “boleh kosong” — pakai pointer atau `std::optional`.

## pointer

**Tipe:** tipe data (menyimpan alamat objek `T`)

**Untuk apa:** objek yang bisa tidak ada (`nullptr`), array dinamis klasik, API C, object Unreal (`AActor*`), traversal.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int skor = 80;
    int* pSkor = &skor;   // pSkor menunjuk ke skor

    std::cout << "Nilai: " << *pSkor << '\n';
    *pSkor = 95;
    std::cout << "Skor asli: " << skor << '\n';
    std::cout << "Alamat: " << pSkor << '\n';

    pSkor = nullptr;
    if (pSkor == nullptr) {
        std::cout << "Pointer kosong, tidak boleh di-* \n";
    }
    return 0;
}
```

**Yang terjadi:** `&skor` mengambil alamat. `*pSkor` *dereference*: baca/tulis objek yang ditunjuk. Menulis `95` lewat pointer mengubah `skor`. Setelah `nullptr`, dereference ilegal (crash). Alamat tercetak sebagai hex — berbeda tiap jalankan.

`const int* p` = tidak boleh ubah `int` lewat `p`. `int* const p` = tidak boleh pindahkan `p`. `const int* const p` = keduanya.

Di Unreal, hampir semua object adalah pointer: `AActor*`, `UStaticMeshComponent*`. Engine bisa menghancurkan object di balik pointer. Cek `IsValid(ptr)` atau `ptr != nullptr` plus aturan GC (lihat file 06 dan 07).

**Biasanya digabungkan dengan:** `nullptr`, `new`/`delete` (lebih baik smart pointer), `IsValid` di Unreal, array.

**Jangan:** dereference `nullptr`. Jangan `delete` pointer yang sudah `delete`. Jangan `delete` `UObject`. Jangan memakai pointer ke variabel yang sudah keluar scope.

## nullptr

**Tipe:** literal pointer kosong (C++11)

**Untuk apa:** menandai “tidak menunjuk ke mana pun” dengan tipe yang aman, menggantikan `NULL` atau `0`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

void laporan(const std::string* catatan) {
    if (catatan == nullptr) {
        std::cout << "(tidak ada catatan)\n";
        return;
    }
    std::cout << *catatan << '\n';
}

int main() {
    std::string isi = "Stok sudah dihitung";
    laporan(&isi);
    laporan(nullptr);
    return 0;
}
```

**Yang terjadi:** panggilan pertama mencetak teks. Panggilan kedua mencetak `(tidak ada catatan)` dan *tidak* mencoba `*catatan`. `nullptr` punya tipe `std::nullptr_t`, jadi tidak ambigu saat overload `void f(int)` vs `void f(char*)` — `NULL` sering berupa `0` dan salah pilih `f(int)`.

**Biasanya digabungkan dengan:** pointer mentah, `unique_ptr` `.get()`, pointer Unreal sebelum `IsValid`.

**Jangan:** menulis `if (!p)` tanpa dokumentasi jika `p` bisa tipe lain. Jangan memakai `NULL` di kode baru. Jangan menganggap pointer Unreal non-null hanya karena “baru di-spawn” — spawn bisa gagal.

## size_t

**Tipe:** tipe data (unsigned, ukuran objek / indeks, `<cstddef>`)

**Untuk apa:** hasil `.size()`, indeks loop yang mencocokkan API STL, `sizeof` dalam bentuk nilai.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> rak{"Buku A", "Buku B", "Buku C"};

    for (std::size_t i = 0; i < rak.size(); ++i) {
        std::cout << i << ": " << rak[i] << '\n';
    }

    std::cout << "Jumlah: " << rak.size() << '\n';
    return 0;
}
```

**Yang terjadi:** loop mencetak `0: Buku A` sampai `2: Buku C`. `i` bertipe sama dengan `rak.size()` sehingga perbandingan tidak mencampur signed/unsigned.

Jebakan: `for (int i = rak.size() - 1; i >= 0; --i)` aman untuk `int`, tetapi `for (size_t i = rak.size() - 1; ...)` pada vector kosong menjadikan `i` bilangan raksasa.

**Biasanya digabungkan dengan:** `vector`, `string`, `sizeof`, alokasi.

**Jangan:** mengurangi `size_t` tanpa cek kosong. Jangan memakai `int` untuk indeks jika warning signed/unsigned sudah muncul — perbaiki tipenya.

## std::int32_t

**Tipe:** tipe data alias (lebar pasti 32-bit, header `<cstdint>`)

**Untuk apa:** data yang harus sama di semua mesin: file biner, jaringan, save game sederhana, cocok dengan `int32` Unreal.

**Contoh implementasi:**

```cpp
#include <cstdint>
#include <iostream>

int main() {
    std::int32_t nyawa = 100;
    std::uint8_t level = 7;
    std::int64_t id = 42;

    std::cout << "Nyawa: " << nyawa << '\n';
    std::cout << "Level: " << static_cast<int>(level) << '\n';
    std::cout << "ID: " << id << '\n';
    return 0;
}
```

**Yang terjadi:** ketiga variabel tercetak. `uint8_t` dicetak sebagai `int` supaya tidak dianggap `char`. `int32_t` selalu 32-bit jika platform menyediakan (hampir semua desktop).

Di Unreal, pakai `int32`, `uint8`, `int64` dari `CoreMinimal.h` — itu yang dikenali UHT untuk `UPROPERTY`.

**Biasanya digabungkan dengan:** serialisasi, protokol, `UPROPERTY` angka.

**Jangan:** memakai `long` untuk “32-bit di mana-mana”. Jangan menaruh `int32_t` di `UPROPERTY` tanpa tipe Unreal jika UHT mengeluh — pakai `int32`.

## enum class

**Tipe:** tipe data enumerasi bertipe-kuat

**Untuk apa:** kumpulan nama tetap: status pesanan, jenis item, alasan mati, tanpa bentrok nama di namespace global.

**Contoh implementasi:**

```cpp
#include <iostream>

enum class StatusPesanan {
    Draf,
    Dibayar,
    Dikirim,
    Selesai
};

int main() {
    StatusPesanan s = StatusPesanan::Dibayar;

    if (s == StatusPesanan::Dibayar) {
        std::cout << "Siap dikemas\n";
    }

    // int x = s;            // error: tidak implisit ke int
    int kode = static_cast<int>(s);
    std::cout << "Kode: " << kode << '\n';
    return 0;
}
```

**Yang terjadi:** `s` hanya bisa diisi nilai enum itu. Perbandingan berhasil, mencetak `Siap dikemas`. Konversi ke `int` harus eksplisit; `Dibayar` biasanya `1` (urutan dari 0). `enum` lama (`enum Status { Draf };`) mencemari scope dan implisit jadi `int` — hindari di kode baru.

Di Unreal: `UENUM(BlueprintType) enum class EStatus : uint8 { ... }` supaya Blueprint melihatnya.

**Biasanya digabungkan dengan:** `switch`, `UENUM`, state machine sederhana.

**Jangan:** memakai `enum` biasa di API baru. Jangan mengandalkan nilai numerik jika kamu sering menyisipkan nilai di tengah — beri nilai eksplisit jika disimpan ke file.

## using alias

**Tipe:** alias tipe (`using Nama = Tipe`)

**Untuk apa:** memendekkan tipe panjang dan memberi makna (`using IdPelanggan = int`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

using IdBarang = int;
using NamaBarang = std::string;
using Katalog = std::unordered_map<IdBarang, NamaBarang>;

int main() {
    Katalog katalog;
    katalog[101] = "Buku C++";
    katalog[202] = "Penggaris";

    for (const auto& pasangan : katalog) {
        std::cout << pasangan.first << " -> " << pasangan.second << '\n';
    }
    return 0;
}
```

**Yang terjadi:** `Katalog` adalah peta `int → string`. Loop mencetak dua baris ID dan nama (urutan `unordered_map` tidak terjamin). `typedef` lama masih ada; `using` lebih mudah dibaca, terutama untuk pointer fungsi dan template.

**Biasanya digabungkan dengan:** `vector`/`map` panjang, template, `enum class` underlying.

**Jangan:** membuat alias yang menyembunyikan kepemilikan (`using Ptr = int*` tanpa kejelasan siapa `delete`). Jangan alias berbeda untuk tipe yang sama di banyak file tanpa satu header bersama.

## sizeof

**Tipe:** operator (hasil `size_t`, dihitung saat compile)

**Untuk apa:** mengetahui ukuran byte suatu tipe atau objek — berguna untuk buffer, alignment, dan pemahaman memori.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int main() {
    std::cout << "int: " << sizeof(int) << '\n';
    std::cout << "double: " << sizeof(double) << '\n';
    std::cout << "int*: " << sizeof(int*) << '\n';

    std::string s = "halo";
    std::cout << "sizeof string objek: " << sizeof(s) << '\n';
    std::cout << "panjang teks: " << s.size() << '\n';
    return 0;
}
```

**Yang terjadi:** di mesin 64-bit tipikal, `int` 4, `double` 8, pointer 8. `sizeof(s)` adalah ukuran **objek string di stack** (sering 24 atau 32), **bukan** 4 karakter `"halo"`. Panjang teks adalah `s.size()`.

**Biasanya digabungkan dengan:** array C, alokasi, serialisasi manual.

**Jangan:** memakai `sizeof` pada pointer lalu mengira itu ukuran array yang ditunjuk (`sizeof(ptr)` = ukuran pointer). Jangan memakai `sizeof` untuk panjang `std::string` / `vector`.

## static_cast

**Tipe:** operator konversi (dicek saat compile)

**Untuk apa:** konversi yang kamu maksudkan: `int` ← `float` (potong koma), `int` ← `enum class`, `void*` ← tipe (jarang), angka ke `size_t` dengan sadar.

**Contoh implementasi:**

```cpp
#include <iostream>

enum class Level { Mudah = 1, Sedang = 2, Sulit = 3 };

int main() {
    double harga = 19.99;
    int hargaBulat = static_cast<int>(harga);

    Level lv = Level::Sedang;
    int kode = static_cast<int>(lv);

    std::cout << "Bulat: " << hargaBulat << '\n';
    std::cout << "Kode level: " << kode << '\n';
    return 0;
}
```

**Yang terjadi:** `19.99` dipotong menjadi `19` (bukan dibulatkan). Enum menjadi `2`. `static_cast` lebih terlihat daripada `(int)harga` gaya C, dan menolak beberapa konversi berbahaya.

Di Unreal, *cast object* memakai `Cast<ACharacter>(aktor)` — itu **bukan** `static_cast` biasa; `Cast` mengecek tipe `UObject` saat runtime. `Cast<T>` mengembalikan `nullptr` jika gagal.

**Biasanya digabungkan dengan:** enum, `void*` API C, narrowing yang disengaja.

**Jangan:** memakai `static_cast` untuk memaksa pointer hierarki Unreal tanpa `Cast`. Jangan memakai `reinterpret_cast` “supaya compile” jika kamu tidak paham aliasing. Hindari C-style cast `(T)x` di kode baru.

## std::string_view

**Tipe:** class (tampilan baca-saja pada teks, C++17, `<string_view>`)

**Untuk apa:** menerima teks tanpa menyalin, baik dari `std::string` maupun literal `"..."`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::size_t hitungSpasi(std::string_view teks) {
    std::size_t n = 0;
    for (char c : teks) {
        if (c == ' ') {
            ++n;
        }
    }
    return n;
}

int main() {
    std::string judul = "Belajar C++ Dasar";
    std::cout << hitungSpasi(judul) << '\n';
    std::cout << hitungSpasi("satu dua tiga") << '\n';
    return 0;
}
```

**Yang terjadi:** fungsi tidak menyalin `judul` dan tidak membuat `std::string` dari literal. Hasil pertama `2`, kedua `2`. `string_view` **tidak punya** teks sendiri; ia menunjuk ke buffer orang lain.

**Biasanya digabungkan dengan:** parser, fungsi baca, API yang tidak menyimpan teks.

**Jangan:** menyimpan `string_view` yang menunjuk ke `string` sementara / lokal yang sudah mati. Jangan mengembalikan `string_view` ke literal dinamis yang hilang. Di Unreal, padanan dekat adalah `FStringView`.

## cin dan cout

**Tipe:** objek stream global (`<iostream>`)

**Untuk apa:** baca/tulis teks di konsol pada program C++ biasa. Bukan cara log Unreal.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string nama;
    int jumlah = 0;

    std::cout << "Nama barang: ";
    std::getline(std::cin, nama);

    std::cout << "Jumlah: ";
    std::cin >> jumlah;

    if (!std::cin) {
        std::cerr << "Jumlah tidak valid\n";
        return 1;
    }

    std::cout << "Catat: " << nama << " x" << jumlah << '\n';
    return 0;
}
```

**Yang terjadi:** program menunggu kamu mengetik nama (boleh ada spasi karena `getline`), lalu angka. Jika angka gagal dibaca, `cin` masuk keadaan error dan program keluar dengan pesan di `cerr`. Jika sukses, satu baris ringkasan tercetak.

`std::cin >> nama` berhenti di spasi. Campuran `>>` lalu `getline` sering menyisakan newline — buang dengan `std::cin.ignore(...)` jika kamu mencampur keduanya.

Di Unreal Editor, tidak ada konsol `cin`. Pakai `UE_LOG(LogTemp, Warning, TEXT("Stok %d"), stok);` atau `GEngine->AddOnScreenDebugMessage`.

**Biasanya digabungkan dengan:** `std::string`, `iomanip`, file `fstream`.

**Jangan:** memakai `std::cout` sebagai logger Unreal. Jangan mengabaikan kegagalan `cin`. Jangan memakai `scanf` di kode C++ baru tanpa alasan C-API.

## literal dan sufiks

**Tipe:** aturan bahasa (cara menulis nilai di sumber kode)

**Untuk apa:** memastikan tipe literal sesuai (`1.0f` vs `1.0`, `42u`, `100LL`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int main() {
    auto a = 42;       // int
    auto b = 42u;      // unsigned
    auto c = 42LL;     // long long
    auto d = 1.5;      // double
    auto e = 1.5f;     // float
    auto f = 'X';      // char
    auto g = "X";      // const char*  (bukan string!)
    auto h = std::string{"X"};

    std::cout << d << ' ' << e << '\n';
    std::cout << "g adalah C-string, h.size()=" << h.size() << '\n';
    return 0;
}
```

**Yang terjadi:** `1.5` dan `1.5f` tercetak mirip, tetapi tipenya beda. `"X"` adalah array karakter yang membus menjadi pointer, bukan `std::string`. `std::string{"X"}` membuat objek string sungguhan berukuran 1.

**Biasanya digabungkan dengan:** `auto`, overload fungsi (`f(float)` vs `f(double)`), Unreal `TEXT("...")` untuk `TCHAR`.

**Jangan:** menulis `float x = 1.0;` tanpa sadar ada konversi `double`→`float` (biasanya hanya warning). Di Unreal, literal teks object path memakai `TEXT("...")` atau `TEXTVIEW`.

## decltype

**Tipe:** penentu tipe (menyalin tipe suatu ekspresi)

**Untuk apa:** menulis tipe yang sama dengan variabel / ekspresi lain, sering di template.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nilai{70, 80, 90};
    decltype(nilai)::value_type pertama = nilai.front();
    decltype(nilai.size()) n = nilai.size();

    std::cout << "Pertama: " << pertama << " n=" << n << '\n';
    return 0;
}
```

**Yang terjadi:** `decltype(nilai)::value_type` adalah `int`. `decltype(nilai.size())` adalah `size_t`. Program mencetak `Pertama: 70 n=3`. Sehari-hari `auto` lebih pendek; `decltype` penting saat kamu belum punya nilai, hanya punya tipe.

**Biasanya digabungkan dengan:** template, `decltype(auto)` (C++14) untuk mengembalikan referensi dengan tepat.

**Jangan:** memakai `decltype` di kode aplikasi sederhana jika `auto` sudah jelas. Jangan bingung `decltype((x))` — kurung ekstra bisa menghasilkan referensi.

## array C

**Tipe:** tipe data bawaan (`T nama[N]`)

**Untuk apa:** sekumpulan elemen berukuran tetap di stack. Untuk daftar yang tumbuh, pakai `std::vector`. Untuk tetap + STL, pakai `std::array`.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int nilai[4] = {80, 75, 90, 88};
    int jumlah = 0;

    for (int i = 0; i < 4; ++i) {
        jumlah += nilai[i];
    }

    std::cout << "Rata-rata: " << (jumlah / 4.0) << '\n';
    std::cout << "sizeof array: " << sizeof(nilai) << '\n';
    return 0;
}
```

**Yang terjadi:** empat nilai dijumlahkan, rata-rata `83.25`. `sizeof(nilai)` adalah `4 * sizeof(int)` (16 di mesin tipikal) **hanya** selama `nilai` masih array, bukan pointer. Jika kamu menulis `void f(int nilai[4])`, parameter *membus* menjadi `int*` dan `sizeof` di dalam fungsi menjadi ukuran pointer.

**Biasanya digabungkan dengan:** buffer kecil, API C, `std::array` sebagai pengganti modern.

**Jangan:** mengembalikan array lokal. Jangan memakai array C jika ukuran berubah. Jangan melewati batas (`nilai[4]` pada array berukuran 4 — undefined behavior).

## static lokal

**Tipe:** durasi penyimpanan (variabel fungsi yang hidup sepanjang program)

**Untuk apa:** mengingat nilai antar-panggilan, inisialisasi sekali (lazy).

**Contoh implementasi:**

```cpp
#include <iostream>

int nomorAntrianBerikut() {
    static int terakhir = 0;
    ++terakhir;
    return terakhir;
}

int main() {
    std::cout << nomorAntrianBerikut() << '\n';
    std::cout << nomorAntrianBerikut() << '\n';
    std::cout << nomorAntrianBerikut() << '\n';
    return 0;
}
```

**Yang terjadi:** `terakhir` tidak direset tiap panggilan. Output: `1` lalu `2` lalu `3`. Inisialisasi `static` lokal di C++11 aman untuk satu thread (magic static). Tetap hati-hati jika banyak thread mengubah nilainya setelah itu.

Di Unreal, state game jangan disimpan di `static` global sembarangan — sulit di-reset saat PIE (Play In Editor) diulang. Simpan di actor / GameState.

**Biasanya digabungkan dengan:** cache sederhana, counter, Meyers’ singleton (pola lama).

**Jangan:** memakai `static` untuk state pertandingan Unreal. Jangan mengira `static` di class sama dengan `static` lokal — `static` member adalah satu variabel untuk semua instance.

## Kesalahan umum bab ini

**Tipe:** catatan praktik (bukan API)

**Untuk apa:** menyingkat bug yang paling sering muncul di tugas kuliah dan proyek Unreal pemula.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    // 1) Membandingkan float dengan ==
    float a = 0.1f + 0.2f;
    std::cout << "0.1+0.2 == 0.3 ? " << (a == 0.3f) << '\n';

    // 2) Unsigned wrap
    unsigned int n = 0;
    std::cout << "n - 1 unsigned: " << (n - 1u) << '\n';

    // 3) string vs C-string pointer
    std::string s = "halo";
    const char* p = s.c_str();
    s += "!!!!";  // s bisa merealokasi
    // std::cout << p;  // p mungkin dangling — jangan

    // 4) auto + literal
    auto x = 3.0;  // double, bukan float
    std::cout << "sizeof x: " << sizeof(x) << '\n';

    std::vector<int> v{1};
    std::cout << "contoh aman: " << v.front() << '\n';
    return 0;
}
```

**Yang terjadi:** perbandingan `float` sering mencetak `0` (false). `0u - 1u` mencetak angka raksasa. Setelah `s +=`, pointer `c_str()` lama tidak boleh dipakai. `auto x = 3.0` berukuran 8 byte (`double`).

**Biasanya digabungkan dengan:** semua entri di atas, plus file 06 untuk dangling.

**Jangan:** meniru keempat pola berbahaya itu di kode produksi. Di Unreal, ganti cek pecahan dengan `FMath::IsNearlyEqual`, dan ganti teks `UPROPERTY` dengan `FString`.
