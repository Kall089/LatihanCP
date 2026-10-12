# Ensiklopedia C++ + STL + Unreal Engine

Katalog API dan pola C++ yang dipakai di program biasa **dan** di proyek Unreal Engine. Setiap entri menjawab: **tipe apa, untuk apa, kode utuh, apa yang terjadi, biasanya digabung dengan apa, dan apa yang jangan dilakukan.**

Bahasa Indonesia mudah. Contoh memakai toko, nilai ujian, daftar pemain, dan actor di dunia Unreal. Ini materi belajar resmi: bahasa C++, Standard Library, dan **API publik Unreal Engine**. Bukan cheat, hack, atau exploit game.

[← Daftar ensiklopedia](../README.md)

## Dua dunia yang tidak boleh dicampur mentah-mentah

| | C++ biasa (konsol / file `.cpp`) | Unreal Engine (modul game) |
| --- | --- | --- |
| Titik masuk | `int main()` | Editor + `UObject` / `AActor`, bukan `main` milikmu |
| Teks | `std::string`, `std::cout` | `FString`, `UE_LOG`, kadang `std::string` di utilitas non-UObject |
| Daftar | `std::vector<T>` | `TArray<T>` (STL boleh, tapi banyak API UE memakai `TArray`) |
| Object hidup | `new` / smart pointer / stack | `UObject` dikelola *garbage collection* Unreal |
| Build | `g++`, `clang++`, MSVC `cl` | UnrealBuildTool lewat Editor / Visual Studio / Xcode / Rider |
| File | `.h` + `.cpp` sesukamu | Class `UCLASS` wajib `*.generated.h` dan `GENERATED_BODY()` |

C++ biasa adalah fondasi. Unreal adalah *framework* di atas C++: macro (`UCLASS`, `UPROPERTY`, `UFUNCTION`), sistem objek, dunia, input, dan replikasi. Kode Unreal **tetap C++**, tetapi compiler-nya dipanggil oleh Unreal, dan banyak tipe (`FVector`, `AActor`) milik engine.

Jika kamu baru: baca file **01 → 06** sampai nyaman menulis program `g++`. Baru kemudian file **07 → 12**. Jangan langsung menempel `std::cout` di `Tick` actor lalu heran kenapa log tidak muncul di Output Log Unreal — di Unreal pakai `UE_LOG`.

## Cara memakai folder ini

1. Buka file sesuai topik, lalu cari nama di daftar isi.
2. Baca **Untuk apa** dulu, baru salin **Contoh implementasi**.
3. Contoh C++ biasa: simpan sebagai satu file, compile, jalankan. Contoh Unreal: letakkan di modul C++ proyek (header + `.cpp`), compile dari Editor.
4. Setelah menyalin, ubah satu nilai dan lihat akibatnya.
5. Jangan menempelkan semua contoh ke satu file. Tiap contoh adalah program atau class terpisah.

Urutan belajar: **01 tipe → 02 kontrol/class → 03 vector/string → 04 map/set → 05 algoritma → 06 memori → 07 UObject/Actor → 08 UPROPERTY/UFUNCTION → 09 komponen/input → 10 GameMode/Pawn → 11 Blueprint vs C++ → 12 resep**.

## Daftar file

| File | Isi |
| --- | --- |
| [01-dasar-tipe-variabel.md](01-dasar-tipe-variabel.md) | `int`, `float`, `double`, `bool`, `char`, `string`, `auto`, `const`, referensi, pointer |
| [02-kontrol-fungsi-class.md](02-kontrol-fungsi-class.md) | `if`, loop, fungsi, `class`, konstruktor, `public`/`private` |
| [03-stl-vector-string-array.md](03-stl-vector-string-array.md) | `vector`, `string`, `array`, `deque`, `pair` |
| [04-stl-map-set-unordered.md](04-stl-map-set-unordered.md) | `map`, `set`, `unordered_map`, `unordered_set` |
| [05-stl-algorithm-iterator.md](05-stl-algorithm-iterator.md) | iterator, `sort`, `find`, `count`, `transform`, `accumulate` |
| [06-memory-smart-pointer.md](06-memory-smart-pointer.md) | `unique_ptr`, `shared_ptr`, `weak_ptr`, kapan menghindari `new`/`delete` |
| [07-unreal-uobject-actor.md](07-unreal-uobject-actor.md) | `UObject`, `AActor`, `BeginPlay`, `Tick`, `SpawnActor` |
| [08-unreal-uproperty-ufunction.md](08-unreal-uproperty-ufunction.md) | specifier `UPROPERTY` / `UFUNCTION`, termasuk `Server` |
| [09-unreal-komponen-input.md](09-unreal-komponen-input.md) | `USceneComponent`, mesh, kamera, Enhanced Input |
| [10-unreal-gamemode-pawn-controller.md](10-unreal-gamemode-pawn-controller.md) | GameMode, Pawn, Character, PlayerController |
| [11-unreal-blueprint-vs-cpp.md](11-unreal-blueprint-vs-cpp.md) | kapan Blueprint, kapan C++, cara expose ke BP |
| [12-resep-dan-kesalahan.md](12-resep-dan-kesalahan.md) | resep actor bergerak; error include, `nullptr`, Tick berat |

## Compiler C++ biasa: g++ dan clang++

Di macOS dan Linux, compiler yang paling sering dipakai mahasiswa adalah **g++** (GCC) atau **clang++** (sering sudah ada di Mac lewat Xcode Command Line Tools).

```bash
# C++17, nama output "program"
g++ -std=c++17 -Wall -Wextra -o program main.cpp
./program

# Alternatif clang
clang++ -std=c++17 -Wall -Wextra -o program main.cpp
./program
```

| Bendera | Artinya |
| --- | --- |
| `-std=c++17` | Pakai standar C++17 (`std::optional`, structured binding, `if constexpr`). Unreal 5 biasanya C++17/20. |
| `-Wall -Wextra` | Nyalakan peringatan. Baca peringatannya; jangan diabaikan. |
| `-o program` | Nama file hasil compile. |
| `-g` | Sisipkan info debugger. |
| `-O2` | Optimasi rilis. Jangan dipakai saat masih mencari bug. |

Beberapa contoh di folder ini memakai header `<numeric>` atau `<unordered_map>`. Itu standar; tidak perlu library tambahan.

Jika compile gagal karena “command not found”:

- **macOS:** instal Xcode Command Line Tools, lalu `clang++ --version`.
- **Linux (Debian/Ubuntu):** `sudo apt install build-essential`.
- **Windows tanpa Unreal:** pakai MSVC, atau MinGW, atau WSL lalu `g++`.

Satu file `main.cpp` cukup untuk hampir semua contoh 01–06. Jika ada dua file (`Toko.h` + `Toko.cpp`), compile bersama:

```bash
g++ -std=c++17 -Wall -Wextra -o toko Toko.cpp main.cpp
```

## Compiler Windows: MSVC (`cl`)

Visual Studio memasang compiler **MSVC**. Buka *Developer Command Prompt for VS*, bukan PowerShell biasa (supaya `cl` ada di `PATH`).

```bat
cl /EHsc /std:c++17 /W4 main.cpp
main.exe
```

| Bendera | Artinya |
| --- | --- |
| `/EHsc` | Exception handling yang lazim untuk C++. |
| `/std:c++17` | Standar bahasa. |
| `/W4` | Peringatan ketat. |
| `/Fe:program.exe` | Nama file hasil (opsional). |

MSVC dan g++ sama-sama C++, tetapi pesan error berbeda. Jika contoh di ensiklopedia ini compile di g++ dan gagal di MSVC, biasanya karena ekstensi non-standar atau urutan include — perbaiki kodenya, jangan mengandalkan ekstensi compiler.

Di Windows, Unreal hampir selalu memakai **toolset MSVC** yang dipilih Unreal (bukan `g++`). Jadi latihan `cl` berguna, tetapi proyek game tetap di-build oleh UnrealBuildTool.

## Unreal Editor dan UnrealBuildTool

Unreal tidak dijalankan dengan `g++ main.cpp`. Alurnya:

1. Instal **Unreal Engine** (Epic Games Launcher atau sumber resmi Epic).
2. Buat proyek: **Games → Blank** (atau template lain), centang **C++**.
3. Editor membuka; Visual Studio / Rider / Xcode juga bisa terbuka.
4. **Tools → New C++ Class** untuk menambah class (`AActor`, `APawn`, …).
5. Unreal menulis `.h` + `.cpp` + memperbarui modul.
6. Compile: tombol **Compile** di Editor, atau build target di IDE.
7. Setelah sukses, class muncul di Content Browser. Blueprint bisa *parent*-nya class C++ itu.

Yang terjadi di balik tombol Compile:

- **Unreal Header Tool (UHT)** membaca macro `UCLASS`, `UPROPERTY`, `UFUNCTION`, lalu menulis `*.generated.h`.
- **UnrealBuildTool (UBT)** memanggil MSVC / clang dengan ratusan flag dan modul (`Core`, `Engine`, `EnhancedInput`, …).
- Hasilnya adalah modul game (`.dll` / `.dylib` / executable editor).

Karena itu:

- Jangan compile file Unreal dengan `g++ NamaActor.cpp`. Header engine tidak akan ketemu, dan `GENERATED_BODY()` belum diproses.
- Jangan hapus `#include "NamaActor.generated.h"` — file itu **harus baris include terakhir** di header class `UCLASS`.
- Modul yang dipakai harus didaftarkan di `NamaProyek.Build.cs` (`PublicDependencyModuleNames`). Enhanced Input, misalnya, butuh modul `"EnhancedInput"`.

**Live Coding** (Editor) mengompilasi ulang tanpa menutup PIE. Berguna, tetapi perubahan besar (ubah parent class, ubah `UCLASS` specifier berat) kadang tetap butuh restart Editor.

## Peta cepat: “Saya ingin…”

### Menyimpan angka dan teks (C++ biasa)

- Bilangan bulat: [01 — `int`](01-dasar-tipe-variabel.md#int)
- Pecahan: [01 — `float` / `double`](01-dasar-tipe-variabel.md#float)
- Teks: [01 — `std::string`](01-dasar-tipe-variabel.md#stdstring)
- Referensi tanpa salin: [01 — referensi](01-dasar-tipe-variabel.md#referensi)
- Alamat: [01 — pointer](01-dasar-tipe-variabel.md#pointer)

### Mengulang dan membungkus logika

- Cabang: [02 — `if`](02-kontrol-fungsi-class.md#if)
- Daftar: [02 — `for`](02-kontrol-fungsi-class.md#for)
- Fungsi: [02 — fungsi](02-kontrol-fungsi-class.md#fungsi)
- Object: [02 — `class`](02-kontrol-fungsi-class.md#class)

### Mengolah koleksi

- Daftar dinamis: [03 — `vector`](03-stl-vector-string-array.md#stdvector)
- Kamus terurut: [04 — `map`](04-stl-map-set-unordered.md#stdmap)
- Kamus cepat: [04 — `unordered_map`](04-stl-map-set-unordered.md#stdunordered_map)
- Urutkan: [05 — `sort`](05-stl-algorithm-iterator.md#stdsort)
- Jumlahkan: [05 — `accumulate`](05-stl-algorithm-iterator.md#stdaccumulate)

### Memori aman

- Satu pemilik: [06 — `unique_ptr`](06-memory-smart-pointer.md#stdunique_ptr)
- Banyak pemilik: [06 — `shared_ptr`](06-memory-smart-pointer.md#stdshared_ptr)
- Jangan dangling: [06 — `weak_ptr`](06-memory-smart-pointer.md#stdweak_ptr)

### Object di dunia Unreal

- Object dasar: [07 — `UObject`](07-unreal-uobject-actor.md#uobject)
- Yang bisa ditaruh di level: [07 — `AActor`](07-unreal-uobject-actor.md#aactor)
- Saat mulai main: [07 — `BeginPlay`](07-unreal-uobject-actor.md#beginplay)
- Munculkan actor: [07 — `SpawnActor`](07-unreal-uobject-actor.md#spawnactor)
- Properti di Details: [08 — `UPROPERTY`](08-unreal-uproperty-ufunction.md#uproperty)
- Fungsi ke Blueprint: [08 — `BlueprintCallable`](08-unreal-uproperty-ufunction.md#ufunction-blueprintcallable)
- Komponen mesh: [09 — `UStaticMeshComponent`](09-unreal-komponen-input.md#ustaticmeshcomponent)
- Input modern: [09 — Enhanced Input](09-unreal-komponen-input.md#enhanced-input)
- Aturan pertandingan: [10 — `AGameModeBase`](10-unreal-gamemode-pawn-controller.md#agamemodebase)
- Karakter dikendalikan: [10 — `APawn` / `ACharacter`](10-unreal-gamemode-pawn-controller.md#apawn)

## Aturan singkat yang sering dipakai

- Di C++ biasa: pakai `const` dan referensi untuk argumen besar; hindari `new` mentah — pakai smart pointer atau objek stack.
- Bandingkan pointer dengan `nullptr`, bukan `NULL` atau `0` (kode baru).
- `std::vector` menyimpan elemen berurutan; jangan menyimpan pointer ke elemennya lalu `push_back` lagi (bisa pindah alamat).
- Di Unreal: jangan `delete` `UObject`. Engine yang menghapus. Pakai `Destroy()` untuk actor, dan biarkan GC untuk object yang tidak direferensikan `UPROPERTY`.
- Jangan kerja berat di `Tick` (load file, query semua actor tiap frame) — lihat [12](12-resep-dan-kesalahan.md).
- `GetWorld()` bisa `nullptr` di konstruktor. Inisialisasi dunia-sensitif di `BeginPlay`.
- Ini API publik untuk membuat game/belajar. Jangan dipakai untuk cheat multiplayer, inject, atau merusak game orang lain.

## Contoh yang saling terkait

Bayangkan proyek latihan “Toko dan Lapangan”:

1. Stok barang adalah `int` dan `std::string` → file 01.
2. Diskon memakai `if` dan fungsi → file 02.
3. Daftar barang adalah `std::vector` → file 03.
4. Harga per nama adalah `std::map` → file 04.
5. Urutkan harga dengan `std::sort` → file 05.
6. Manajer stok memakai `unique_ptr` → file 06.
7. Di Unreal, kotak barang adalah `AActor` → file 07.
8. Harga kotak terlihat di Details lewat `UPROPERTY` → file 08.
9. Mesh kotak adalah `UStaticMeshComponent` → file 09.
10. Pemain adalah `ACharacter` + Enhanced Input → file 09 dan 10.
11. Desainer mengatur warna di Blueprint anak → file 11.
12. Resep actor yang bergerak ada di file 12.

## Versi dan ruang lingkup

- **C++:** contoh menargetkan **C++17**. Beberapa catatan menyebut C++20 jika berguna (`std::span`, ranges), tetapi kode utama tetap C++17.
- **STL:** `std::` dari header standar. Bukan Boost, bukan Qt.
- **Unreal:** API publik yang stabil di **Unreal Engine 5** (keluarga 5.3–5.5): `AActor`, `UObject`, `UPROPERTY`, Enhanced Input, `AGameModeBase`, `ACharacter`. Nama specifier bisa bertambah di versi baru; cocokkan dengan dokumentasi Epic untuk versi Editor-mu.
- Dokumentasi dirujuk pada **22 September 2026**.
- Tidak dibahas: anti-cheat, memory edit game tertutup, exploit server, atau reverse engineering.

## Cara compile cepat (ringkas)

```bash
# C++ biasa
g++ -std=c++17 -Wall -Wextra -o app 01_contoh.cpp && ./app
```

```text
Unreal: buka .uproject → Compile di Editor
atau: build target Editor di Visual Studio / Rider / Xcode
```

Mulai dari [01 — Dasar tipe dan variabel](01-dasar-tipe-variabel.md).
