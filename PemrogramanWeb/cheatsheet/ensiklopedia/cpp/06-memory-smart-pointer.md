# 06 — Memori, RAII, dan smart pointer

[← Algoritma](05-stl-algorithm-iterator.md) · [README](README.md) · [Lanjut: UObject dan Actor →](07-unreal-uobject-actor.md)

C++ tidak punya garbage collector untuk objek biasa. Yang dialokasi di **heap** dengan `new` harus dilepas dengan `delete` — atau, jauh lebih baik, dilepas otomatis oleh **destructor** (RAII) lewat `unique_ptr` / `shared_ptr`.

Unreal **punya** garbage collector untuk `UObject`. Itu dunia terpisah: jangan `delete` actor. Bagian akhir file ini memisahkan keduanya.

## Daftar isi

- [stack vs heap](#stack-vs-heap)
- [new dan delete](#new-dan-delete)
- [new[] dan delete[]](#new-dan-delete-1)
- [RAII](#raii)
- [std::unique_ptr](#stdunique_ptr)
- [std::make_unique](#stdmake_unique)
- [std::move pada unique_ptr](#stdmove-pada-unique_ptr)
- [std::shared_ptr](#stdshared_ptr)
- [std::make_shared](#stdmake_shared)
- [std::weak_ptr](#stdweak_ptr)
- [siklus shared_ptr](#siklus-shared_ptr)
- [std::move objek biasa](#stdmove-objek-biasa)
- [dangling pointer](#dangling-pointer)
- [kapan new/delete dihindari](#kapan-newdelete-dihindari)
- [UObject vs smart pointer](#uobject-vs-smart-pointer)
- [TSharedPtr dan TWeakObjectPtr](#tsharedptr-dan-tweakobjectptr)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## stack vs heap

**Tipe:** konsep memori

**Untuk apa:** memilih tempat objek hidup. Stack: otomatis, cepat, sempit. Heap: fleksibel, kamu (atau smart pointer / GC) yang mengatur umur.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    int skor = 90;                 // stack
    std::vector<int> daftar(3, 7); // objek vector di stack; buffer isinya di heap

    std::cout << "skor stack=" << skor << '\n';
    std::cout << "buffer heap contoh=" << daftar[0] << '\n';
    return 0;
}
```

**Yang terjadi:** `skor` hilang saat `main` selesai. `vector` juga hancur otomatis, dan destructor-nya melepas buffer heap. Kamu tidak menulis `delete`. Variabel lokal besar (array 10 juta `int` di stack) bisa *stack overflow*.

**Biasanya digabungkan dengan:** `vector`/`string` (heap tersembunyi), `unique_ptr` untuk objek besar/polimorfik.

**Jangan:** mengembalikan alamat variabel lokal. Jangan array C raksasa di stack. Jangan mengira `vector` “tanpa heap”.

## new dan delete

**Tipe:** operator alokasi

**Untuk apa:** membuat objek di heap, mendapatkan pointer. Di kode baru, ini pilihan **terakhir**.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string* p = new std::string("sementara");
    std::cout << *p << '\n';
    delete p;
    p = nullptr;
    return 0;
}
```

**Yang terjadi:** string dibuat di heap, dicetak, dilepas. Jika `delete` lupa, kebocoran. Jika `delete` dua kali, undefined behavior. Jika exception muncul sebelum `delete`, bocor. Itulah alasan smart pointer.

`new` bisa melempar `std::bad_alloc`. `new (std::nothrow)` mengembalikan `nullptr`.

**Biasanya digabungkan dengan:** API C lama, latihan memahami heap — bukan pola aplikasi baru.

**Jangan:** `delete` yang bukan dari `new`. Jangan `delete` `UObject`. Jangan `delete` lalu dereference. Jangan `new` di Unreal untuk actor (`NewObject` / `SpawnActor`).

## new[] dan delete[]

**Tipe:** operator alokasi array

**Untuk apa:** array heap gaya C. Lebih baik `std::vector`.

**Contoh implementasi:**

```cpp
#include <iostream>

int main() {
    int* a = new int[4]{10, 20, 30, 40};
    std::cout << a[2] << '\n';
    delete[] a;
    a = nullptr;
    return 0;
}
```

**Yang terjadi:** mencetak `30`. `delete` (tanpa `[]`) pada memori `new[]` adalah undefined behavior. Ukuran tidak tersimpan di pointer yang kamu lihat — kamu harus ingat `4`.

**Biasanya digabungkan dengan:** interop C, buffer SIMD — jarang di aplikasi biasa.

**Jangan:** mencampur `new`/`delete[]` atau sebaliknya. Jangan `vector` + `delete[]` pada `&v[0]`.

## RAII

**Tipe:** pola desain (Resource Acquisition Is Initialization)

**Untuk apa:** mengikat sumber daya ke objek: constructor ambil, destructor lepas. Termasuk memori, file, lock.

**Contoh implementasi:**

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    {
        std::ofstream out("catatan_latihan.txt");
        if (!out) {
            std::cerr << "tidak bisa tulis\n";
            return 1;
        }
        out << "stok=12\n";
    }  // destructor menutup file di sini

    std::ifstream in("catatan_latihan.txt");
    std::string baris;
    std::getline(in, baris);
    std::cout << baris << '\n';
    return 0;
}
```

**Yang terjadi:** file ditulis, ditutup otomatis saat keluar blok, lalu dibaca kembali `stok=12`. Jika `return` di tengah atau exception, destructor tetap jalan (selama exception tidak dari destructor). `unique_ptr` adalah RAII untuk `new`.

**Biasanya digabungkan dengan:** `fstream`, `lock_guard`, smart pointer, class file 02.

**Jangan:** RAII + `new` mentah di luar. Jangan menutup file manual lalu biarkan destructor menutup lagi tanpa aturan (fstream aman). Jangan exception di destructor.

## std::unique_ptr

**Tipe:** class template (`<memory>`) — pemilik tunggal

**Untuk apa:** objek heap yang hanya punya **satu** pemilik. Pindah milik lewat `std::move`. Tidak bisa di-copy.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>
#include <string>

class MesinLaporan {
public:
    explicit MesinLaporan(std::string judul) : judul_(std::move(judul)) {}
    void cetak() const { std::cout << judul_ << '\n'; }

private:
    std::string judul_;
};

int main() {
    std::unique_ptr<MesinLaporan> p = std::make_unique<MesinLaporan>("Nota harian");
    p->cetak();
    std::cout << std::boolalpha << static_cast<bool>(p) << '\n';
    return 0;
}
```

**Yang terjadi:** objek hidup di heap, diakses dengan `->`. Di akhir `main`, `unique_ptr` destructor memanggil `delete`. `bool(p)` true selama tidak kosong. Tidak ada `delete` di `main`.

`p.get()` pointer mentah (tidak melepaskan milik). `p.reset()` hapus sekarang. `p.release()` lepas milik **tanpa** hapus (jarang, berbahaya).

**Biasanya digabungkan dengan:** `make_unique`, pabrik polimorfik (`unique_ptr<Base>`), `vector<unique_ptr<T>>`.

**Jangan:** dua `unique_ptr` pada alamat sama. Jangan `delete p.get()`. Jangan copy (`auto q = p` error). Jangan `unique_ptr` ke `UObject` Unreal (GC vs delete bentrok).

## std::make_unique

**Tipe:** fungsi template (C++14)

**Untuk apa:** membuat `unique_ptr` tanpa menulis `new`, exception-safe saat beberapa argumen.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>
#include <vector>

int main() {
    auto angka = std::make_unique<int>(42);
    auto deret = std::make_unique<int[]>(4);  // array, nilai default 0

    deret[0] = 7;
    std::cout << *angka << ' ' << deret[0] << '\n';

    std::vector<std::unique_ptr<int>> banyak;
    banyak.push_back(std::make_unique<int>(1));
    banyak.push_back(std::make_unique<int>(2));
    std::cout << banyak.size() << '\n';
    return 0;
}
```

**Yang terjadi:** mencetak `42 7` lalu `2`. `make_unique<int[]>(n)` ada di C++14; inisialisasi nilai perlu loop/`fill`. Lebih baik `vector` daripada `unique_ptr<T[]>`.

**Biasanya digabungkan dengan:** factory, pindah ke fungsi (`void pakai(std::unique_ptr<T>)`).

**Jangan:** `unique_ptr<T>(new T)` jika `make_unique` tersedia. Jangan `make_unique` pada tipe yang constructor-nya privat tanpa friend (kadang factory member).

## std::move pada unique_ptr

**Tipe:** cast ke rvalue (`<utility>`)

**Untuk apa:** memindahkan milik. Setelah move, sumber menjadi `nullptr`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>
#include <utility>

void terima(std::unique_ptr<int> milik) {
    std::cout << "terima " << *milik << '\n';
}

int main() {
    auto p = std::make_unique<int>(9);
    auto q = std::move(p);
    if (!p) {
        std::cout << "p kosong setelah move\n";
    }
    terima(std::move(q));
    std::cout << std::boolalpha << static_cast<bool>(q) << '\n';
    return 0;
}
```

**Yang terjadi:** `p` kosong, `q` punya `9`, `terima` mencetak `terima 9` lalu menghancurkan objek, `q` kosong (`false`). Fungsi yang menerima `unique_ptr` by value mengambil alih milik.

**Biasanya digabungkan dengan:** sink, pabrik, `vector.push_back(std::move(p))`.

**Jangan:** memakai `p` setelah `move` tanpa cek (kecuali menugaskan ulang). Jangan `move` lalu mengira kedua pointer valid.

## std::shared_ptr

**Tipe:** class template — pemilik bersama (reference count)

**Untuk apa:** beberapa pihak berbagi objek; objek hidup sampai **shared_ptr terakhir** mati.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> a = std::make_shared<int>(100);
    {
        std::shared_ptr<int> b = a;
        std::cout << "use_count " << a.use_count() << '\n';
        *b += 1;
    }
    std::cout << "nilai " << *a << " use_count " << a.use_count() << '\n';
    return 0;
}
```

**Yang terjadi:** di dalam blok, dua pemilik, `use_count` 2, nilai jadi 101. Setelah `b` mati, count 1, objek masih hidup. Di akhir `main`, count 0, `int` dihapus.

`shared_ptr` lebih mahal daripada `unique_ptr` (atomik count). Jangan jadi default.

**Biasanya digabungkan dengan:** `weak_ptr`, cache, graph yang memang berbagi.

**Jangan:** `shared_ptr` jika satu pemilik cukup. Jangan membuat dua `shared_ptr` terpisah dari `new` yang sama (`shared_ptr<int> a(p); shared_ptr<int> b(p);` double delete). Jangan siklus tanpa `weak_ptr`.

## std::make_shared

**Tipe:** fungsi template

**Untuk apa:** satu alokasi untuk objek + control block (lebih efisien daripada `shared_ptr<T>(new T)`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>
#include <string>

struct Profil {
    std::string nama;
    int umur;
    Profil(std::string n, int u) : nama(std::move(n)), umur(u) {}
};

int main() {
    auto p = std::make_shared<Profil>("Haikal", 21);
    std::cout << p->nama << ' ' << p->umur << '\n';
    return 0;
}
```

**Yang terjadi:** mencetak `Haikal 21`. `make_shared` exception-safe. Catatan: memori objek mungkin tertahan sampai `weak_ptr` terakhir juga mati (karena satu blok) — jarang masalah, perlu diketahui.

**Biasanya digabungkan dengan:** `shared_ptr` factory, `enable_shared_from_this`.

**Jangan:** `make_shared` + `unique_ptr` campur pada objek sama. Jangan `make_shared` array di C++17 (ada di C++20 `make_shared<T[]>`).

## std::weak_ptr

**Tipe:** class template — pengamat non-pemilik

**Untuk apa:** melihat `shared_ptr` tanpa menahan hidupnya. Mencegah siklus. Cache yang boleh hilang.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>

int main() {
    std::weak_ptr<int> w;
    {
        auto s = std::make_shared<int>(5);
        w = s;
        if (auto terkunci = w.lock()) {
            std::cout << "hidup " << *terkunci << '\n';
        }
    }
    std::cout << "expired " << std::boolalpha << w.expired() << '\n';
    if (auto terkunci = w.lock()) {
        std::cout << "tidak tercetak\n";
    } else {
        std::cout << "objek sudah mati\n";
    }
    return 0;
}
```

**Yang terjadi:** di dalam blok, `lock()` sukses, cetak `hidup 5`. Setelah `s` mati, `expired` true, `lock()` kosong. **Jangan** `w.lock()` lalu abaikan hasil; selalu pakai `shared_ptr` sementara dari `lock`.

**Biasanya digabungkan dengan:** observer, relasi parent↔child, cache, `enable_shared_from_this`.

**Jangan:** menyimpan hasil `get()` dari `lock()` setelah `shared_ptr` sementara mati. Jangan memakai `weak_ptr` tanpa `lock`.

## siklus shared_ptr

**Tipe:** jebakan kepemilikan

**Untuk apa:** memahami mengapa dua `shared_ptr` yang saling menunjuk tidak pernah mencapai `use_count` 0.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> parent;
    int id = 0;
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->id = 1;
    b->id = 2;
    a->next = b;
    b->parent = a;  // weak, bukan shared

    std::cout << "a use=" << a.use_count() << " b use=" << b.use_count() << '\n';
    if (auto p = b->parent.lock()) {
        std::cout << "parent id " << p->id << '\n';
    }
    return 0;
}
```

**Yang terjadi:** `a` menahan `b` lewat `next`. `b` hanya mengamati `a` lewat `weak_ptr`, jadi `a.use_count()` tetap 1 (variabel `a`). Jika `b->parent` juga `shared_ptr`, `a` dan `b` saling menahan: bocor meski `main` selesai menugaskan ulang. Output: use count kecil, `parent id 1`.

**Biasanya digabungkan dengan:** pohon, observer, graf.

**Jangan:** `shared_ptr` dua arah. Jangan “memperbaiki” bocor dengan `delete` mentah.

## std::move objek biasa

**Tipe:** cast / semantik pindah

**Untuk apa:** memindahkan isi `string`/`vector` (buffer steal) alih-alih deep copy saat sumber tidak dipakai lagi.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::string sumber = "teks yang agak panjang untuk latihan";
    std::string tujuan = std::move(sumber);
    std::cout << "tujuan: " << tujuan << '\n';
    std::cout << "sumber size setelah move: " << sumber.size() << '\n';

    std::vector<std::string> rak;
    rak.push_back(std::move(tujuan));
    std::cout << "rak0: " << rak[0] << '\n';
    return 0;
}
```

**Yang terjadi:** `tujuan` memegang teks. `sumber` dalam keadaan valid tetapi tidak ditentukan — sering kosong (`size` 0). Jangan andalkan isi lama. `push_back(std::move(tujuan))` menghindari copy string ke dalam vector.

`std::move` **tidak** memindahkan apa pun sendiri; ia menandai “boleh di-steal”. Tipe tanpa move constructor tetap di-copy.

**Biasanya digabungkan dengan:** constructor `T(std::string s)` + `member(std::move(s))`, `unique_ptr`, return by value (RVO sering tanpa `move` manual).

**Jangan:** `return std::move(lokal);` pada variabel lokal — bisa menghalangi NRVO. Jangan memakai sumber setelah move kecuali ditugaskan ulang. Jangan `move` objek yang masih dibutuhkan dua tempat.

## dangling pointer

**Tipe:** bug (pointer/referensi ke objek yang sudah mati)

**Untuk apa:** mengenali pola yang menghasilkan crash “kadang”.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    v.reserve(32);
    int& r = v[0];
    v.push_back(4);  // cap 32, r masih valid di contoh ini
    std::cout << "contoh aman karena reserve: " << r << '\n';

    std::string teks = "halo";
    std::string salin = teks;  // jangan simpan c_str lalu mutate
    teks += " dunia";
    std::cout << salin << " | " << teks << '\n';
    return 0;
}
```

**Yang terjadi:** dengan `reserve`, referensi `r` tetap sah, mencetak `1`. String disalin secara nilai sebelum diubah, jadi tidak ada `c_str` dangling. Pola berbahaya yang dihindari: return `&lokal`, referensi ke elemen `vector` lalu `push_back` tanpa kapasitas, `c_str()` setelah mutate.

**Biasanya digabungkan dengan:** return by value, `reserve`, smart pointer, `IsValid` di Unreal.

**Jangan:** memperbaiki dangling dengan “semoga belum ditimpa”. Jangan menyimpan `T*` ke elemen `TArray` yang bisa `Add` lagi tanpa jaminan.

## kapan new/delete dihindari

**Tipe:** aturan praktik

**Untuk apa:** memutuskan default: stack, kontainer, smart pointer — bukan `new`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>
#include <vector>

struct Item {
    int id = 0;
};

int main() {
    Item diStack;
    diStack.id = 1;

    std::vector<Item> daftar(10);
    daftar[0].id = 2;

    auto dinamik = std::make_unique<Item>();
    dinamik->id = 3;

    std::cout << diStack.id << ' ' << daftar[0].id << ' ' << dinamik->id << '\n';
    return 0;
}
```

**Yang terjadi:** tiga cara tanpa `delete` manual, mencetak `1 2 3`. Pakai `new` hanya jika API asing memaksa, atau latihan. Setelah `new`, bungkus segera ke smart pointer.

| Situasi | Pilihan |
| --- | --- |
| Objek kecil, umur = scope | stack |
| Daftar / teks | `vector` / `string` |
| Satu pemilik heap | `unique_ptr` |
| Berbagi disengaja | `shared_ptr` + mungkin `weak_ptr` |
| `UObject` Unreal | `NewObject` / `SpawnActor`, bukan `new`/`delete` |

**Biasanya digabungkan dengan:** RAII, factory.

**Jangan:** `new` “supaya bisa pointer”. Jangan `shared_ptr` sebagai default. Jangan `delete` object engine.

## UObject vs smart pointer

**Tipe:** perbandingan model umur (Unreal)

**Untuk apa:** tidak mencampur GC Unreal dengan `delete` C++.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ContohData.generated.h"

UCLASS()
class UContohData : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 Stok = 0;
};

inline UContohData* BuatData(UObject* Outer)
{
    UContohData* Data = NewObject<UContohData>(Outer);
    Data->Stok = 12;
    return Data;
}
```

**Yang terjadi:** `NewObject` mendaftarkan instance ke GC Unreal. `Outer` (sering `this` actor / package) memengaruhi lifetime. Selama ada `UPROPERTY` yang menunjuk ke `Data` (atau outer masih hidup sesuai aturan), GC tidak memungut. `delete Data` salah dan bisa merusak heap engine.

Pointer mentah `UContohData*` aman hanya jika GC tidak memungut — biasanya karena `UPROPERTY` di owner. Tanpa root, object bisa hilang; pointer menjadi dangling.

**Biasanya digabungkan dengan:** `UPROPERTY`, `IsValid`, `TWeakObjectPtr`, `SpawnActor` (file 07).

**Jangan:** `std::unique_ptr<UObject>`. Jangan `shared_ptr` membungkus `AActor*`. Jangan `new UContohData`.

## TSharedPtr dan TWeakObjectPtr

**Tipe:** class template Unreal

**Untuk apa:** `TSharedPtr` = shared pointer **non-UObject** (Slate, data murni). `TWeakObjectPtr<T>` = pengamat `UObject` tanpa menahan GC.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PengamatActor.generated.h"

UCLASS()
class APengamatActor : public AActor
{
    GENERATED_BODY()

public:
    TWeakObjectPtr<AActor> TargetLemah;

    UPROPERTY()
    TObjectPtr<AActor> TargetKuat;

    void Pasang(AActor* Target)
    {
        TargetKuat = Target;
        TargetLemah = Target;
    }

    virtual void Tick(float DeltaTime) override
    {
        Super::Tick(DeltaTime);
        if (AActor* Hidup = TargetLemah.Get())
        {
            (void)Hidup;
        }
    }
};
```

**Yang terjadi:** `Pasang` menyimpan dua jenis referensi. `TargetKuat` (`UPROPERTY` / `TObjectPtr`) menahan object dari GC. `TargetLemah` tidak menahan: jika target `Destroy()`, `Get()` menjadi `nullptr`. Di `Tick`, selalu `Get()` / `IsValid` dulu.

`TSharedPtr` dipakai pada objek non-`UObject` (banyak widget Slate). Jangan `TSharedPtr<AActor>`.

**Biasanya digabungkan dengan:** `IsValid`, `Destroy`, cache actor, input binding.

**Jangan:** `TSharedPtr` ke `UObject`. Jangan mengira `TWeakObjectPtr` memperpanjang hidup. Jangan field `AActor*` tanpa `UPROPERTY` jika object tidak punya root lain.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menyingkat double-free, bocor, dan campur GC.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(1);
    int* mentah = p.get();
    (void)mentah;
    // delete mentah;  // double free bersama unique_ptr

    std::shared_ptr<int> a = std::make_shared<int>(2);
    std::shared_ptr<int> b = a;
    std::cout << *a << ' ' << b.use_count() << '\n';
    return 0;
}
```

**Yang terjadi:** mencetak `2 2`. `b = a` berbagi control block — benar. `shared_ptr<int> c(a.get())` salah (control block kedua). `delete p.get()` salah. Di Unreal, analoginya `delete Actor`.

**Biasanya digabungkan dengan:** semua entri di atas, file 07 `IsValid`.

**Jangan:** `delete` pointer dari `.get()`; dua `shared_ptr` dari raw yang sama; `new` tanpa pemilik; smart pointer pada `UObject`; mengabaikan `weak_ptr::lock`.
