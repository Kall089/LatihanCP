# 02 — Kontrol, fungsi, dan class

[← Tipe dan variabel](01-dasar-tipe-variabel.md) · [README](README.md) · [Lanjut: vector, string, array →](03-stl-vector-string-array.md)

Setelah data ada, program **memilih cabang**, **mengulang**, membungkus langkah dalam **fungsi**, dan mengelompokkan data + perilaku dalam **class**. Di Unreal, `AActor` adalah class C++ dengan aturan tambahan (file 07).

## Daftar isi

- [if](#if)
- [else if dan else](#else-if-dan-else)
- [switch](#switch)
- [for](#for)
- [while](#while)
- [do while](#do-while)
- [range-based for](#range-based-for)
- [break dan continue](#break-dan-continue)
- [fungsi](#fungsi)
- [parameter nilai, referensi, const ref](#parameter-nilai-referensi-const-ref)
- [overload dan default argument](#overload-dan-default-argument)
- [class](#class)
- [constructor](#constructor)
- [destructor](#destructor)
- [public dan private](#public-dan-private)
- [protected dan pewarisan singkat](#protected-dan-pewarisan-singkat)
- [this](#this)
- [member function const](#member-function-const)
- [struct](#struct)
- [namespace](#namespace)
- [try catch](#try-catch)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## if

**Tipe:** pernyataan kontrol

**Untuk apa:** menjalankan blok hanya jika kondisi `true`.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int stok = 2;

    if (stok <= 0) {
        std::cout << "Habis, jangan dijual\n";
    }

    if (stok > 0) {
        std::cout << "Masih ada " << stok << " unit\n";
    }
    return 0;
}
```

**Yang terjadi:** `stok` 2, jadi blok pertama dilewati dan baris kedua tercetak. Kondisi harus bisa menjadi `bool`. `if (stok)` juga “jalan” jika stok bukan 0 — kurang jelas dibanding `if (stok != 0)`.

**Biasanya digabungkan dengan:** `else`, operator `&&` `||`, fungsi yang mengembalikan `bool`.

**Jangan:** menaruh `;` langsung setelah `if (syarat);` — blok berikutnya selalu jalan. Jangan memakai assignment di kondisi (`if (x = 1)`) kecuali kamu benar-benar bermaksud.

## else if dan else

**Tipe:** pernyataan kontrol

**Untuk apa:** merangkai beberapa syarat yang saling menyingkir, plus cadangan.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int nilai = 78;

    if (nilai >= 85) {
        std::cout << "A\n";
    } else if (nilai >= 70) {
        std::cout << "B\n";
    } else if (nilai >= 55) {
        std::cout << "C\n";
    } else {
        std::cout << "Belum lulus\n";
    }
    return 0;
}
```

**Yang terjadi:** 78 memenuhi `>= 70` setelah gagal `>= 85`, jadi `B`. Syarat berikutnya tidak dicek. Urutan penting: jika `>= 55` ditulis lebih dulu, nilai 90 juga jatuh ke cabang itu.

`if` bisa dipakai sebagai ekspresi di C++ (bukan ternary saja): `int x = (nilai >= 70) ? 1 : 0;` — tetap jaga keterbacaan.

**Biasanya digabungkan dengan:** validasi form, status enum, early return di fungsi.

**Jangan:** menulis rantai `else if` puluhan cabang untuk enum — `switch` lebih jelas. Jangan mengulang syarat yang sudah mustahil (`else if (nilai >= 85)` setelah `if (nilai >= 90)` tanpa alasan).

## switch

**Tipe:** pernyataan kontrol

**Untuk apa:** memilih cabang berdasarkan nilai integral / enum, dibanding rantai `==`.

**Contoh implementasi:**

```cpp
#include <iostream>

enum class MetodeBayar { Tunai, Kartu, Transfer };

int main() {
    MetodeBayar m = MetodeBayar::Kartu;

    switch (m) {
        case MetodeBayar::Tunai:
            std::cout << "Siapkan kembalian\n";
            break;
        case MetodeBayar::Kartu:
            std::cout << "Gesek / tap\n";
            break;
        case MetodeBayar::Transfer:
            std::cout << "Tunggu notifikasi\n";
            break;
    }
    return 0;
}
```

**Yang terjadi:** `m` adalah `Kartu`, jadi hanya `Gesek / tap` tercetak. `break` mencegah *fall-through* ke `Transfer`. Tanpa `break`, case berikutnya ikut jalan — kadang disengaja, hampir selalu bug.

C++17 mengizinkan `if` dengan init (`if (int x = f(); x > 0)`). `switch` juga bisa punya init di C++17: `switch (int k = kode(); k) { ... }`.

Di Unreal, `switch` pada `EEndPlayReason` atau enum `UENUM` sangat umum.

**Biasanya digabungkan dengan:** `enum class`, state, menu angka.

**Jangan:** lupa `break` (kecuali komentar `[[fallthrough]]`). Jangan `switch` pada `std::string` (tidak bisa). Jangan memakai `default` kosong hanya untuk membungkam warning jika semua enum sudah lengkap — biarkan compiler mengingatkan case baru.

## for

**Tipe:** pernyataan loop

**Untuk apa:** mengulang dengan penghitung: indeks, N kali, langkah 2, mundur.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> harga{10000, 15000, 7000};

    for (int i = 0; i < static_cast<int>(harga.size()); ++i) {
        std::cout << "Item " << i << ": " << harga[i] << '\n';
    }

    int jumlah = 0;
    for (int n = 1; n <= 5; ++n) {
        jumlah += n;
    }
    std::cout << "1+...+5 = " << jumlah << '\n';
    return 0;
}
```

**Yang terjadi:** tiga baris harga tercetak dengan indeks 0..2. Loop kedua menambahkan 1 sampai 5 menjadi `15`. Bentuk `for (init; syarat; langkah)`: `init` sekali, lalu syarat → badan → langkah, berulang.

`++i` vs `i++` pada integer biasa hampir sama; kebiasaan C++: `++i` pada iterator.

**Biasanya digabungkan dengan:** `vector`, array, indeks yang dibutuhkan (bukan hanya nilai).

**Jangan:** mengubah `size()` dengan `push_back` di dalam loop indeks tanpa rencana — mudah skip atau invalid. Jangan `for(;;)` tanpa syarat keluar yang jelas.

## while

**Tipe:** pernyataan loop

**Untuk apa:** mengulang selama syarat benar, jika jumlah putaran tidak diketahui di awal.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int stok = 5;

    while (stok > 0) {
        std::cout << "Jual 1, sisa sebelum: " << stok << '\n';
        --stok;
    }

    std::cout << "Habis\n";
    return 0;
}
```

**Yang terjadi:** lima baris penjualan tercetak, `stok` turun 5→4→…→1, lalu syarat gagal, `Habis` tercetak. Jika syarat awal sudah false, badan tidak pernah jalan.

**Biasanya digabungkan dengan:** baca file sampai habis, antrian, `std::cin` gagal.

**Jangan:** lupa mengubah variabel syarat (infinite loop). Jangan memakai `while` jika `for` dengan indeks lebih jujur.

## do while

**Tipe:** pernyataan loop

**Untuk apa:** menjalankan badan **minimal sekali**, baru cek syarat — menu, validasi ulang.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int percobaan = 0;
    int kode = 0;

    do {
        ++percobaan;
        kode = (percobaan == 3) ? 42 : 0;  // simulasi: baru benar di ke-3
        std::cout << "Coba " << percobaan << ", kode=" << kode << '\n';
    } while (kode != 42);

    std::cout << "Berhasil\n";
    return 0;
}
```

**Yang terjadi:** loop jalan tiga kali meski `kode` awal 0. Output tiga baris percobaan, lalu `Berhasil`. Titik koma setelah `while (...)` **wajib**.

**Biasanya digabungkan dengan:** input berulang, generate-until-valid.

**Jangan:** memakai `do while` jika satu kali jalan saat syarat false adalah bug. Jangan lupa `;`.

## range-based for

**Tipe:** pernyataan loop (C++11)

**Untuk apa:** mengunjungi tiap elemen tanpa indeks, lebih sulit off-by-one.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> rak{"Buku", "Pensil", "Penghapus"};

    for (const std::string& nama : rak) {
        std::cout << "- " << nama << '\n';
    }

    for (std::string& nama : rak) {
        nama += "*";
    }
    std::cout << rak.front() << '\n';
    return 0;
}
```

**Yang terjadi:** tiga nama tercetak. Loop kedua mengubah elemen asli (`&`) sehingga `rak.front()` menjadi `Buku*`. `const auto&` adalah bentuk paling umum untuk baca. `auto` tanpa `&` menyalin tiap elemen — mahal untuk `string`.

Di Unreal: `for (AActor* A : Daftar)` atau `for (const auto& Item : TArray)`.

**Biasanya digabungkan dengan:** `vector`, `map` (`for (const auto& [k, v] : peta)` C++17), `string` (per karakter).

**Jangan:** `push_back` ke kontainer yang sedang di-range-for (iterator invalid). Jangan memakai salinan jika kamu ingin mengubah elemen.

## break dan continue

**Tipe:** pernyataan lompat di loop / `switch`

**Untuk apa:** `break` keluar dari loop terdalam; `continue` lompat ke iterasi berikutnya.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> angka{2, -1, 5, 0, 9};

    for (int n : angka) {
        if (n == 0) {
            std::cout << "ketemu 0, berhenti\n";
            break;
        }
        if (n < 0) {
            continue;
        }
        std::cout << n << '\n';
    }
    return 0;
}
```

**Yang terjadi:** `2` tercetak, `-1` dilewati, `5` tercetak, `0` memicu `break`, `9` tidak sempat diproses.

**Biasanya digabungkan dengan:** pencarian, validasi, `switch`.

**Jangan:** `break` hanya keluar satu tingkat — loop bersarang butuh flag atau `return`. Jangan menumpuk `continue` sampai alur sulit dibaca; pertimbangkan fungsi `bool layak(n)`.

## fungsi

**Tipe:** fungsi

**Untuk apa:** menamai urutan langkah, menghindari copy-paste, menguji potongan kecil.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int subtotal(int harga, int jumlah) {
    return harga * jumlah;
}

void cetakNota(const std::string& barang, int total) {
    std::cout << barang << " = " << total << '\n';
}

int main() {
    int t = subtotal(15000, 3);
    cetakNota("Pensil", t);
    return 0;
}
```

**Yang terjadi:** `subtotal` mengembalikan `45000`. `cetakNota` mencetak `Pensil = 45000`. Fungsi harus dideklarasikan sebelum dipanggil, atau punya *prototype* di atas. `main` mengembalikan `0` artinya sukses.

Di Unreal, fungsi yang ingin terlihat Blueprint / direplikasi memakai macro `UFUNCTION` (file 08). Fungsi C++ biasa tanpa macro tetap sah sebagai helper privat.

**Biasanya digabungkan dengan:** `const`, class method, header `.h` + definisi `.cpp`.

**Jangan:** fungsi 200 baris tanpa nama. Jangan mengandalkan urutan definisi antar `.cpp` tanpa header. Jangan membuat `UFUNCTION` untuk helper yang tidak perlu terlihat editor.

## parameter nilai, referensi, const ref

**Tipe:** aturan passing argumen

**Untuk apa:** memilih: salin murah (`int`), ubah asli (`T&`), baca tanpa salin (`const T&`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

void naikkan(int& skor) {
    skor += 10;
}

int tambahLima(int skor) {
    skor += 5;
    return skor;
}

void cetakNama(const std::string& nama) {
    std::cout << nama << '\n';
}

int main() {
    int nilai = 70;
    naikkan(nilai);
    int salinan = tambahLima(nilai);
    cetakNama("Haikal");
    std::cout << "nilai=" << nilai << " salinan=" << salinan << '\n';
    return 0;
}
```

**Yang terjadi:** `naikkan` mengubah `nilai` menjadi `80`. `tambahLima` bekerja pada salinan; `nilai` tetap `80`, `salinan` `85`. `cetakNama` tidak menyalin string panjang (di sini pendek, polanya sama).

Pointer dipakai jika argumen boleh kosong. `T&&` (rvalue ref) untuk *move* — lihat file 06.

**Biasanya digabungkan dengan:** `std::string`, `vector`, getter.

**Jangan:** `const T&` untuk `int`/`bool` kecil (lebih ribet, tidak lebih cepat). Jangan `T&` jika fungsi tidak mengubah — menyesatkan. Jangan passing `vector` by value “supaya aman” di loop panas.

## overload dan default argument

**Tipe:** aturan fungsi (nama sama, parameter beda)

**Untuk apa:** API yang nyaman: `cetak(int)` dan `cetak(string)`; argumen opsional.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

void cetakHarga(int harga) {
    std::cout << "Rp" << harga << '\n';
}

void cetakHarga(int harga, const std::string& mataUang) {
    std::cout << mataUang << harga << '\n';
}

int diskon(int harga, int persen = 10) {
    return harga - (harga * persen / 100);
}

int main() {
    cetakHarga(20000);
    cetakHarga(20000, "USD ");
    std::cout << diskon(20000) << '\n';
    std::cout << diskon(20000, 25) << '\n';
    return 0;
}
```

**Yang terjadi:** dua overload `cetakHarga` dipilih dari argumen. `diskon(20000)` memakai 10% → `18000`. Panggilan kedua 25% → `15000`. Default argument hanya di **deklarasi** (header), jangan diulang di definisi jika sudah ada di deklarasi.

**Biasanya digabungkan dengan:** class constructor overload, operator.

**Jangan:** overload yang hanya beda `int` vs `unsigned` — ambigu. Jangan default argument yang mengubah makna diam-diam di tengah kode lama.

## class

**Tipe:** class (tipe buatan pengguna)

**Untuk apa:** menggabungkan data (stok, nama) dengan perilaku (jual, isi) agar invariant terjaga.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

class Barang {
public:
    Barang(std::string nama, int stok)
        : nama_(std::move(nama)), stok_(stok) {}

    bool jual(int n) {
        if (n <= 0 || n > stok_) {
            return false;
        }
        stok_ -= n;
        return true;
    }

    int stok() const { return stok_; }
    const std::string& nama() const { return nama_; }

private:
    std::string nama_;
    int stok_ = 0;
};

int main() {
    Barang b{"Buku C++", 5};
    std::cout << b.jual(2) << " sisa " << b.stok() << '\n';
    std::cout << b.jual(10) << " sisa " << b.stok() << '\n';
    return 0;
}
```

**Yang terjadi:** objek `b` dibuat dengan stok 5. `jual(2)` berhasil (`1` / true), sisa 3. `jual(10)` gagal (`0` / false), sisa tetap 3. Data privat tidak bisa diubah dari `main` kecuali lewat method.

Di Unreal, `UCLASS()` class harus mewarisi `UObject` (langsung atau tidak) jika ingin refleksi. Class C++ biasa tanpa `UCLASS` tetap boleh untuk math helper.

**Biasanya digabungkan dengan:** constructor, `private`, `std::vector<Barang>`.

**Jangan:** class yang semua member `public` lalu method kosong — itu `struct` data. Jangan meletakkan logika dunia Unreal di class non-`UObject` jika kamu butuh `UPROPERTY` / GC.

## constructor

**Tipe:** fungsi khusus (membuat objek)

**Untuk apa:** menjamin objek lahir dalam keadaan sah: stok tidak negatif, nama tidak kosong, pointer komponen terpasang.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class Rekening {
public:
    Rekening(std::string pemilik, int saldoAwal)
        : pemilik_(std::move(pemilik)), saldo_(saldoAwal) {
        if (saldo_ < 0) {
            throw std::invalid_argument("saldo tidak boleh negatif");
        }
    }

    int saldo() const { return saldo_; }

private:
    std::string pemilik_;
    int saldo_;
};

int main() {
    Rekening r{"Haikal", 50000};
    std::cout << r.saldo() << '\n';
    return 0;
}
```

**Yang terjadi:** initializer list mengisi `pemilik_` dan `saldo_` sebelum badan constructor. Cek menolak saldo negatif. Program mencetak `50000`. Constructor default (tanpa argumen) dibuat compiler hanya jika kamu tidak menulis constructor lain — kecuali kamu `= default`.

Di Unreal, constructor `AActor` memakai `CreateDefaultSubobject` dan mengatur `PrimaryActorTick`. Jangan `GetWorld()` di constructor (file 07, 12).

**Biasanya digabungkan dengan:** initializer list, `explicit` (cegah konversi implisit), delegating ctor.

**Jangan:** pekerjaan berat / I/O di constructor jika objek bisa dibuat di tempat yang tidak siap. Jangan inisialisasi member di badan jika bisa di list (urutan inisialisasi = urutan deklarasi member, bukan urutan list!).

## destructor

**Tipe:** fungsi khusus (`~Nama`)

**Untuk apa:** melepaskan milik objek saat hidupnya berakhir: file, `new` mentah, handle.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

class CatatanSesi {
public:
    explicit CatatanSesi(std::string nama) : nama_(std::move(nama)) {
        std::cout << "buka " << nama_ << '\n';
    }

    ~CatatanSesi() {
        std::cout << "tutup " << nama_ << '\n';
    }

private:
    std::string nama_;
};

int main() {
    {
        CatatanSesi a{"kasir"};
        std::cout << "sedang bekerja\n";
    }
    std::cout << "blok selesai\n";
    return 0;
}
```

**Yang terjadi:** output berurutan: `buka kasir`, `sedang bekerja`, `tutup kasir`, `blok selesai`. Destructor `a` dipanggil otomatis saat keluar `{ }`. Ini jiwa **RAII** (file 06): sumber daya terikat umur objek.

Jika class punya destructor khusus, biasanya kamu harus pikirkan copy/move (rule of 5). Lebih baik biarkan member smart pointer yang menangani.

Unreal `UObject` **jangan** `delete` manual; destructor engine-managed. Jangan `delete this` di actor.

**Biasanya digabungkan dengan:** RAII, `unique_ptr`, file stream (stream sudah RAII).

**Jangan:** melempar exception dari destructor. Jangan `new` di ctor tanpa `delete` di dtor (lebih baik jangan `new`). Jangan destructor kosong hanya “supaya ada”.

## public dan private

**Tipe:** access specifier

**Untuk apa:** `public` = API yang boleh dipakai pemanggil; `private` = detail yang boleh berubah tanpa merusak pemanggil.

**Contoh implementasi:**

```cpp
#include <iostream>

class Penghitung {
public:
    void tambah() { ++n_; }
    int nilai() const { return n_; }

private:
    int n_ = 0;
};

int main() {
    Penghitung p;
    p.tambah();
    p.tambah();
    std::cout << p.nilai() << '\n';
    // p.n_ = 99;  // error: private
    return 0;
}
```

**Yang terjadi:** dua kali `tambah`, `nilai()` mencetak `2`. Akses `n_` dari `main` ditolak compiler. Default `class` adalah `private`; default `struct` adalah `public`.

Di Unreal, member yang ingin tampil di Details harus `UPROPERTY` dan biasanya di `public` atau `protected` + `meta = (AllowPrivateAccess = "true")` jika `private`.

**Biasanya digabungkan dengan:** getter/setter tipis, invariant.

**Jangan:** getter+setter kosong untuk setiap field tanpa aturan — kamu hanya menulis `public` dengan upacara. Jangan `private` lalu teman (`friend`) ke seluruh program.

## protected dan pewarisan singkat

**Tipe:** access specifier + hubungan class

**Untuk apa:** `protected` terlihat oleh class turunan, tidak oleh dunia luar. Pewarisan menambahkan perilaku khusus di atas class umum.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

class Produk {
public:
    explicit Produk(std::string nama) : nama_(std::move(nama)) {}
    virtual ~Produk() = default;

    virtual int hargaAkhir() const { return hargaDasar_; }

protected:
    void setHargaDasar(int h) { hargaDasar_ = h; }
    const std::string& nama() const { return nama_; }

private:
    std::string nama_;
    int hargaDasar_ = 0;
};

class ProdukDiskon : public Produk {
public:
    ProdukDiskon(std::string nama, int harga, int persen)
        : Produk(std::move(nama)) {
        setHargaDasar(harga);
        persen_ = persen;
    }

    int hargaAkhir() const override {
        return Produk::hargaAkhir() * (100 - persen_) / 100;
    }

private:
    int persen_ = 0;
};

int main() {
    ProdukDiskon p{"Buku", 100000, 20};
    std::cout << p.hargaAkhir() << '\n';
    return 0;
}
```

**Yang terjadi:** `ProdukDiskon` memakai `setHargaDasar` (protected). `hargaAkhir` di-override: 20% dari 100000 = `80000`. `virtual` + `override` memastikan pemanggilan lewat pointer base memakai versi anak.

Di Unreal, `AActor` → `APawn` → `ACharacter` adalah rantai pewarisan resmi. Pakai `UCLASS()` di tiap level yang direfleksikan. Selalu panggil `Super::BeginPlay()`.

**Biasanya digabungkan dengan:** `virtual`, `override`, `Super::` di Unreal.

**Jangan:** pewarisan hanya untuk memakai ulang 2 fungsi — komposisi (punya member) sering lebih sehat. Jangan mewarisi `std::vector`. Jangan lupa destructor `virtual` pada base yang dipakai secara polimorfik.

## this

**Tipe:** pointer ke objek yang sedang menjalankan method (`T*`)

**Untuk apa:** membedakan member dan parameter senama; mengembalikan `*this` untuk chaining; mengoper pointer ke API C / Unreal.

**Contoh implementasi:**

```cpp
#include <iostream>

class Titik {
public:
    Titik& setX(int x) {
        this->x_ = x;
        return *this;
    }

    Titik& setY(int y) {
        this->y_ = y;
        return *this;
    }

    void cetak() const {
        std::cout << x_ << ',' << y_ << '\n';
    }

private:
    int x_ = 0;
    int y_ = 0;
};

int main() {
    Titik t;
    t.setX(3).setY(4).cetak();
    return 0;
}
```

**Yang terjadi:** chaining mengatur `(3,4)` lalu mencetak `3,4`. `this->` opsional jika nama tidak bentrok, berguna saat parameter `x` menaungi member.

Di Unreal, `this` sering di-`Spawn` parameter owner, atau `AddOnScreenDebugMessage`. Di method `const`, tipe `this` adalah `const T*`.

**Biasanya digabungkan dengan:** method chaining, membandingkan alamat (`if (this == &lain)`).

**Jangan:** memakai `this` setelah objek hancur (callback async). Jangan `delete this` kecuali pola sangat khusus yang kamu kuasai — di Unreal, `Destroy()` pada actor.

## member function const

**Tipe:** method yang tidak mengubah objek (`void f() const`)

**Untuk apa:** boleh dipanggil pada objek `const`; menandai query (getter, hitung, cek).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

class Keranjang {
public:
    void tambah(int n) { total_ += n; }

    int total() const { return total_; }

    void cetak() const {
        std::cout << "Total: " << total_ << '\n';
    }

private:
    int total_ = 0;
};

void laporan(const Keranjang& k) {
    k.cetak();
    // k.tambah(1);  // error: tambah bukan const
}

int main() {
    Keranjang k;
    k.tambah(20);
    laporan(k);
    return 0;
}
```

**Yang terjadi:** `laporan` menerima `const&` jadi hanya method `const` yang boleh. Mencetak `Total: 20`. Compiler menegakkan janji.

`mutable` member boleh berubah di method `const` (cache). Pakai hemat.

**Biasanya digabungkan dengan:** getter, `const T&` parameter.

**Jangan:** method `const` yang mengubah state lewat pointer member tanpa alasan (logically non-const). Jangan lupa `const` pada getter — merusak rantai `const`.

## struct

**Tipe:** class dengan default public (agregat data)

**Untuk apa:** kumpulan field datar: titik 2D, record baris CSV, pasangan ID+jumlah.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

struct BarisNota {
    std::string nama;
    int jumlah;
    int hargaSatuan;
};

int main() {
    std::vector<BarisNota> nota{
        {"Pensil", 2, 3000},
        {"Buku", 1, 45000},
    };

    int total = 0;
    for (const BarisNota& b : nota) {
        total += b.jumlah * b.hargaSatuan;
        std::cout << b.nama << '\n';
    }
    std::cout << "Total: " << total << '\n';
    return 0;
}
```

**Yang terjadi:** dua baris tercetak, total `51000`. `struct` di C++ **bisa** punya method dan `private`; bedanya hanya default akses dan kebiasaan: data polos vs objek berinvariant.

Di Unreal: `USTRUCT(BlueprintType) struct FBarisNota { GENERATED_BODY(); ... }` agar Blueprint dan `UPROPERTY` mengerti.

**Biasanya digabungkan dengan:** `vector`, `map`, serialisasi.

**Jangan:** `struct` besar dengan invariant rumit tanpa constructor. Jangan mengira `struct` “lebih cepat” dari `class`.

## namespace

**Tipe:** ruang nama (mencegah tabrakan nama)

**Untuk apa:** mengelompokkan fungsi/tipe (`Toko::hitung`, `std::vector`).

**Contoh implementasi:**

```cpp
#include <iostream>

namespace toko {
int pajak(int harga) { return harga / 10; }

namespace gudang {
int kapasitas = 200;
}
}

int main() {
    std::cout << toko::pajak(50000) << '\n';
    std::cout << toko::gudang::kapasitas << '\n';
    return 0;
}
```

**Yang terjadi:** `5000` dan `200` tercetak. `using namespace std;` di `.cpp` kecil masih sering, tetapi **jangan** di header — merusak semua yang include.

Unreal memakai namespace jarang untuk `UCLASS` (UHT lebih suka prefix `A`, `U`, `F`, `E`). Helper C++ murni boleh ber-namespace.

**Biasanya digabungkan dengan:** header, `using` selektif (`using std::cout`).

**Jangan:** `using namespace std;` di header. Jangan namespace anonim di header (tiap TU beda objek).

## try catch

**Tipe:** penanganan exception

**Untuk apa:** memulihkan dari error yang *dilempar* (`throw`), misalnya `stoi` gagal, `at()` di luar batas.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

int bacaHarga(const std::string& teks) {
    try {
        return std::stoi(teks);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("harga bukan angka: " + teks);
    }
}

int main() {
    try {
        std::cout << bacaHarga("12000") << '\n';
        std::cout << bacaHarga("abc") << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Gagal: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
```

**Yang terjadi:** `12000` tercetak. `"abc"` membuat `stoi` melempar; dibungkus pesan jelas; `main` mencetak `Gagal: ...` ke `cerr` dan keluar `1`.

Unreal **tidak** memakai exception sebagai alur normal. Banyak build menonaktifkan atau tidak mengandalkan `try/catch` lintas engine. Di gameplay, pakai `check`, `ensure`, `IsValid`, return `bool`. Exception tetap ada di modul C++ murni jika kamu mengaktifkannya.

**Biasanya digabungkan dengan:** `stoi`, `vector::at`, RAII (stack unwind memanggil destructor).

**Jangan:** `catch (...)` kosong. Jangan exception untuk kontrol biasa (`if` lebih murah/jelas). Jangan andalkan exception sebagai desain Unreal gameplay.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menyingkat bug kontrol/class yang berulang.

**Contoh implementasi:**

```cpp
#include <iostream>

int bagiAman(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a / b;
}

int main() {
    int i = 0;
    // salah klasik: if (i = 1) selalu true + mengubah i
    if (i == 1) {
        std::cout << "tidak tercetak\n";
    }

    std::cout << bagiAman(10, 0) << '\n';
    std::cout << bagiAman(10, 2) << '\n';
    return 0;
}
```

**Yang terjadi:** `if (i == 1)` false. `bagiAman` menghindari division by zero, mencetak `0` lalu `5`.

**Biasanya digabungkan dengan:** semua kontrol di atas.

**Jangan:** `=` di kondisi; method tanpa `const`; mewarisi hanya untuk reuse; lupa `virtual` destructor pada base polimorfik; menulis logika `Tick` Unreal di class biasa tanpa dunia.
