# Cheatsheet C++ dan Unreal

[← Daftar panduan](README.md) · [Ensiklopedia C++](ensiklopedia/cpp/README.md)

C++ mengolah **logika berkinerja** di native: program terminal, game, atau plugin. Unreal Engine memakai C++ plus Blueprint. Ini materi API belajar resmi, bukan cheat atau hack game.

Versi cepat ini pintu masuk. Detail tiap tipe, STL, dan makro Unreal ada di [ensiklopedia/cpp](ensiklopedia/cpp/README.md).

## Daftar isi

- [C++ biasa vs Unreal](#c-biasa-vs-unreal)
- [Tipe, variabel, referensi](#tipe-variabel-referensi)
- [Kondisi, loop, dan fungsi](#kondisi-loop-dan-fungsi)
- [Class](#class)
- [STL: vector dan string](#stl-vector-dan-string)
- [STL: map dan set](#stl-map-dan-set)
- [Algoritma STL](#algoritma-stl)
- [Smart pointer](#smart-pointer)
- [Unreal: UObject dan AActor](#unreal-uobject-dan-aactor)
- [UPROPERTY dan UFUNCTION](#uproperty-dan-ufunction)
- [Komponen dan input](#komponen-dan-input)
- [GameMode, Pawn, Controller](#gamemode-pawn-controller)
- [Blueprint vs C++](#blueprint-vs-c)
- [Kesalahan umum](#kesalahan-umum)

## C++ biasa vs Unreal

**Untuk apa:** membedakan tempat menulis kode, supaya tidak mencampur `std::cout` dengan `UE_LOG` di proyek yang salah.

```text
C++ latihan (g++ / MSVC)
  file .cpp → compile → program.exe / a.out

Unreal
  Unreal Editor + modul C++
  UCLASS / UPROPERTY → Blueprint dan editor
```

Latihan bahasa murni:

```bash
g++ -std=c++17 -Wall -o toko toko.cpp
./toko
```

Di Windows dengan MSVC, compile lewat Developer Command Prompt atau proyek Visual Studio. Proyek Unreal dibuka lewat Editor; tombol **Compile** membangun modul C++.

**Contoh implementasi:** tulis `toko.cpp` berisi `main` yang mencetak `"Halo toko"`. Setelah itu baru buka template Unreal **First Person** atau **Third Person** untuk C++.

**Biasanya digabungkan dengan:** README compiler vs Editor. Peta lengkap: [README ensiklopedia](ensiklopedia/cpp/README.md).

## Tipe, variabel, referensi

**Untuk apa:** menyimpan angka, teks, dan alamat data.

```cpp
#include <iostream>
#include <string>

int main() {
    int jumlah = 2;
    float diskon = 0.1f;
    double harga = 45000.0;
    bool tersedia = true;
    char kode = 'B';
    std::string nama = "Buku";
    const int pajak = 11;

    int& alias = jumlah;   // referensi: nama lain untuk jumlah
    int* p = &jumlah;      // pointer: menyimpan alamat
    auto salinan = nama;   // auto: tipe ditebak compiler

    std::cout << nama << " x " << *p << "\n";
    return 0;
}
```

`int` untuk hitungan, `float`/`double` untuk pecahan, `bool` benar/salah. `const` tidak boleh diganti. Referensi harus mengacu objek hidup. Pointer bisa `nullptr`; cek sebelum dipakai.

**Contoh implementasi:** variabel `stok` dan referensi `sisa` yang merujuk `stok`. Kurangi `sisa`, lalu cetak `stok` — keduanya berubah bersama.

**Biasanya digabungkan dengan:** fungsi yang menerima `const std::string&`. Tiap tipe: [01 — tipe dan variabel](ensiklopedia/cpp/01-dasar-tipe-variabel.md).

## Kondisi, loop, dan fungsi

**Untuk apa:** memilih jalan, mengulang, dan membungkus langkah.

```cpp
#include <iostream>
#include <vector>
#include <string>

int total(int harga, int jumlah = 1) {
    return harga * jumlah;
}

int main() {
    int stok = 5;
    if (stok > 0) {
        std::cout << "Bisa dibeli\n";
    } else {
        std::cout << "Habis\n";
    }

    std::vector<std::string> nama{"Buku", "Pensil", "Tas"};
    for (const auto& n : nama) {
        std::cout << n << "\n";
    }
    std::cout << total(45000, 2) << "\n";
    return 0;
}
```

Titik koma wajib. `for` berbasis rentang nyaman untuk `vector`. Argumen default ditulis di deklarasi. Prototipe fungsi diletakkan di header (`.h`) jika file terpisah.

**Contoh implementasi:** fungsi `label_stok(int stok)` mengembalikan `"tersedia"` atau `"habis"`, dipanggil di dalam loop daftar stok.

**Biasanya digabungkan dengan:** class dan STL. Kontrol lengkap: [02 — kontrol dan class](ensiklopedia/cpp/02-kontrol-fungsi-class.md).

## Class

**Untuk apa:** menggabungkan data dan perilaku menjadi satu tipe.

```cpp
#include <iostream>
#include <string>

class Produk {
public:
    Produk(std::string nama, int harga) : nama_(std::move(nama)), harga_(harga) {}

    const std::string& nama() const { return nama_; }
    int harga() const { return harga_; }

private:
    std::string nama_;
    int harga_;
};

int main() {
    Produk buku("Buku CSS", 40000);
    std::cout << buku.nama() << "\n";
    return 0;
}
```

`public` bisa dipanggil dari luar, `private` hanya dari dalam class. Constructor (`Produk(...)`) mengisi data saat objek dibuat. `const` di method menjanjikan tidak mengubah anggota.

**Contoh implementasi:** tambah method `int total(int jumlah) const` yang mengembalikan `harga_ * jumlah`, lalu cetak total 3 buku.

**Biasanya digabungkan dengan:** `vector<Produk>` dan inheritance Unreal (`AActor`). Class dasar: [02 — kontrol dan class](ensiklopedia/cpp/02-kontrol-fungsi-class.md).

## STL: vector dan string

**Untuk apa:** daftar dinamis dan teks yang aman.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <array>

int main() {
    std::string nama = "Buku tulis";
    std::cout << nama.size() << " " << nama.substr(0, 4) << "\n";

    std::vector<int> harga{45000, 5000, 90000};
    harga.push_back(12000);
    std::cout << harga[0] << " " << harga.back() << "\n";

    std::array<int, 3> tetap{1, 2, 3};
    std::cout << tetap.size() << "\n";
    return 0;
}
```

`vector` memanjang sendiri. `operator[]` tidak mengecek batas; `at()` melempar jika indeks liar. `array` berukuran tetap. `string` bukan array `char` mentah.

**Contoh implementasi:** `vector<string>` keranjang, `push_back` tiga nama, loop `for (const auto& item : keranjang)` untuk mencetak.

**Biasanya digabungkan dengan:** `sort` dan `find`. Vector/string: [03 — vector dan string](ensiklopedia/cpp/03-stl-vector-string-array.md).

## STL: map dan set

**Untuk apa:** pasangan kunci-nilai, atau kumpulan unik.

```cpp
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <string>

int main() {
    std::map<std::string, int> stok{{"Buku", 3}, {"Pensil", 0}};
    stok["Tas"] = 2;
    if (stok.count("Buku")) {
        std::cout << stok["Buku"] << "\n";
    }

    std::set<int> id{1, 2, 2, 3};          // 2 hanya sekali, terurut
    std::unordered_map<std::string, int> cepat{{"Buku", 3}};
    std::cout << id.size() << " " << cepat["Buku"] << "\n";
    return 0;
}
```

`map`/`set` terurut. `unordered_*` biasanya lebih cepat, tanpa urutan. `count` atau `find` lebih aman daripada `[]` jika kunci mungkin belum ada (`[]` bisa membuat entri baru).

**Contoh implementasi:** `map<string, int>` stok toko. Jika `stok[nama] == 0`, cetak `"habis"`.

**Biasanya digabungkan dengan:** inventory dan lookup ID. Map/set: [04 — map dan set](ensiklopedia/cpp/04-stl-map-set-unordered.md).

## Algoritma STL

**Untuk apa:** mengurut, mencari, menghitung, dan merangkum tanpa loop manual panjang.

```cpp
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> harga{45000, 5000, 90000};
    std::sort(harga.begin(), harga.end());

    auto it = std::find(harga.begin(), harga.end(), 5000);
    int ada = std::count(harga.begin(), harga.end(), 5000);
    int jumlah = std::accumulate(harga.begin(), harga.end(), 0);

    std::vector<int> dobel(harga.size());
    std::transform(harga.begin(), harga.end(), dobel.begin(),
                   [](int n) { return n * 2; });

    std::cout << ada << " " << jumlah << " " << *it << "\n";
    return 0;
}
```

Hampir semua algoritma memakai iterator `begin()`/`end()`. `sort` mengubah vector asli. Lambda `[](int n) { ... }` adalah fungsi singkat di tempat.

**Contoh implementasi:** sort harga naik, lalu `accumulate` untuk total keranjang.

**Biasanya digabungkan dengan:** `vector` dan lambda. Algoritma: [05 — algorithm](ensiklopedia/cpp/05-stl-algorithm-iterator.md).

## Smart pointer

**Untuk apa:** mengatur umur objek di heap tanpa `delete` manual.

```cpp
#include <memory>
#include <iostream>
#include <string>

struct Produk {
    std::string nama;
};

int main() {
    auto satu = std::make_unique<Produk>(Produk{"Buku"});
    std::cout << satu->nama << "\n";

    auto bersama = std::make_shared<Produk>(Produk{"Tas"});
    std::weak_ptr<Produk> lemah = bersama;
    if (auto hidup = lemah.lock()) {
        std::cout << hidup->nama << "\n";
    }
    return 0;
}
```

`unique_ptr` pemilik tunggal. `shared_ptr` berbagi kepemilikan. `weak_ptr` mengamati tanpa memperpanjang umur. Di Unreal, objek `UObject` dikelola engine (`UPROPERTY`), bukan `shared_ptr` biasa.

**Contoh implementasi:** fungsi `buat_produk` mengembalikan `unique_ptr<Produk>`, pemanggil tidak perlu `delete`.

**Biasanya digabungkan dengan:** pabrik objek dan cache. Memori: [06 — smart pointer](ensiklopedia/cpp/06-memory-smart-pointer.md).

## Unreal: UObject dan AActor

**Untuk apa:** membuat objek yang dikenali Unreal: bisa di-spawn, punya `BeginPlay` dan `Tick`.

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TokoActor.generated.h"

UCLASS()
class LATIHAN_API ATokoActor : public AActor
{
    GENERATED_BODY()

public:
    ATokoActor();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Toko")
    float Kecepatan = 100.f;
};
```

`UCLASS` mendaftarkan tipe ke refleksi Unreal. `GENERATED_BODY()` wajib. `AActor` hidup di dunia. `BeginPlay` sekali saat mulai, `Tick` tiap frame — jangan taruh kerja berat di Tick.

**Contoh implementasi:** di `BeginPlay`, `UE_LOG(LogTemp, Display, TEXT("Toko siap"));`. Di `Tick`, geser actor pelan dengan `AddActorWorldOffset`.

**Biasanya digabungkan dengan:** komponen mesh dan GameMode. Actor: [07 — UObject dan Actor](ensiklopedia/cpp/07-unreal-uobject-actor.md).

## UPROPERTY dan UFUNCTION

**Untuk apa:** mengekspos variabel dan fungsi ke Editor serta Blueprint.

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toko")
int32 Stok = 3;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toko")
FString NamaTampil = TEXT("Buku");

UFUNCTION(BlueprintCallable, Category = "Toko")
void KurangiStok(int32 Jumlah);

UFUNCTION(Server, Reliable)
void ServerCatatBeli();
```

`EditAnywhere` bisa diubah di Details. `VisibleAnywhere` terlihat tapi terkunci. `BlueprintReadOnly` dibaca BP, tidak ditulis. `BlueprintCallable` bisa dipanggil dari grafik Blueprint. `Server` untuk wewenang server (multiplayer), bukan untuk “menembus” aturan game.

**Contoh implementasi:** `KurangiStok` mengurangi `Stok` jika cukup, lalu Blueprint tombol UI memanggil fungsi itu.

**Biasanya digabungkan dengan:** widget Blueprint dan replikasi. Specifier: [08 — UPROPERTY dan UFUNCTION](ensiklopedia/cpp/08-unreal-uproperty-ufunction.md).

## Komponen dan input

**Untuk apa:** menempel mesh, kamera, dan membaca tombol lewat Enhanced Input.

```cpp
UPROPERTY(VisibleAnywhere)
TObjectPtr<UStaticMeshComponent> MeshToko;

UPROPERTY(VisibleAnywhere)
TObjectPtr<UCameraComponent> Kamera;

// di constructor:
MeshToko = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshToko"));
RootComponent = MeshToko;
```

`USceneComponent` punya transform. `UStaticMeshComponent` menampilkan mesh. Enhanced Input memakai `UInputAction` dan `UInputMappingContext`, bukan hardcoded `EKeys` di produksi.

**Contoh implementasi:** bind action `IA_Interaksi` ke fungsi `OnInteraksi` yang membuka UI toko saat pawn dekat actor.

**Biasanya digabungkan dengan:** Pawn dan Controller. Komponen: [09 — komponen dan input](ensiklopedia/cpp/09-unreal-komponen-input.md).

## GameMode, Pawn, Controller

**Untuk apa:** memisahkan aturan main, tubuh yang dikendalikan, dan yang memberi perintah.

```text
GameMode  → aturan: skor, siapa pawn yang di-spawn
Pawn      → tubuh di dunia (karakter, kendaraan)
Controller → otak: PlayerController atau AIController
```

GameMode hidup di server. Jangan menaruh aturan menang di mesh. Pawn punya mesh dan gerakan. Controller menerima input lalu memerintah Pawn.

**Contoh implementasi:** `ATokoGameMode` mengatur pawn default `APemainToko`. Saat beli berhasil, GameMode menambah skor, bukan komponen mesh.

**Biasanya digabungkan dengan:** `BeginPlay` spawn dan HUD. Alur ini: [10 — GameMode dan Pawn](ensiklopedia/cpp/10-unreal-gamemode-pawn-controller.md).

## Blueprint vs C++

**Untuk apa:** memilih alat yang lebih cepat untuk tugas itu.

- **C++:** tipe baru, loop ketat, jaringan, data besar, API yang dipakai banyak kelas.
- **Blueprint:** merakit event, UI, prototype, mengatur nilai di Editor.
- **Campuran paling umum:** class C++ + `UPROPERTY`/`UFUNCTION`, lalu desainer merangkai di Blueprint.

Ekspos ke BP hanya yang memang perlu. Jangan meniru seluruh game di Event Tick Blueprint jika logika sudah berat.

**Contoh implementasi:** `ATokoActor` di C++ punya `Kecepatan` dan `KurangiStok`. Blueprint anaknya mengatur mesh dan memanggil `KurangiStok` dari overlap.

**Biasanya digabungkan dengan:** parent C++ + child Blueprint. Perbandingan: [11 — Blueprint vs C++](ensiklopedia/cpp/11-unreal-blueprint-vs-cpp.md).

## Kesalahan umum

- **Lupa `#include` atau `.generated.h`:** compile Unreal gagal; include header yang menyediakan tipe.
- **Pakai pointer tanpa cek:** `if (MeshToko)` / `IsValid(Actor)` sebelum akses.
- **Tick berat:** hitung sekali, pakai timer, atau event; jangan raycast masif tiap frame.
- **`new`/`delete` pada UObject:** biarkan engine (`NewObject`, `SpawnActor`, `UPROPERTY`).
- **`vector[]` di luar batas:** pakai `at` saat ragu, atau cek `size`.
- **Mencampur `std::string` dan `FString` tanpa konversi:** Unreal memakai `FString` / `TEXT("...")`.

Resep actor bergerak dan error umum: [12 — resep dan kesalahan](ensiklopedia/cpp/12-resep-dan-kesalahan.md).

Latihan: program terminal `vector<Produk>` + `sort` harga; lalu di Unreal, actor yang bergerak pelan dan mengekspos `Kecepatan` ke Details.

## Peta ensiklopedia

| Ingin… | Buka |
| --- | --- |
| `int`, pointer | [01](ensiklopedia/cpp/01-dasar-tipe-variabel.md) |
| `if`, class | [02](ensiklopedia/cpp/02-kontrol-fungsi-class.md) |
| `vector` | [03](ensiklopedia/cpp/03-stl-vector-string-array.md) |
| `map` / `set` | [04](ensiklopedia/cpp/04-stl-map-set-unordered.md) |
| `sort` / `find` | [05](ensiklopedia/cpp/05-stl-algorithm-iterator.md) |
| `unique_ptr` | [06](ensiklopedia/cpp/06-memory-smart-pointer.md) |
| `AActor` | [07](ensiklopedia/cpp/07-unreal-uobject-actor.md) |
| `UPROPERTY` | [08](ensiklopedia/cpp/08-unreal-uproperty-ufunction.md) |
| mesh / input | [09](ensiklopedia/cpp/09-unreal-komponen-input.md) |
| GameMode | [10](ensiklopedia/cpp/10-unreal-gamemode-pawn-controller.md) |
| Blueprint | [11](ensiklopedia/cpp/11-unreal-blueprint-vs-cpp.md) |
| resep | [12](ensiklopedia/cpp/12-resep-dan-kesalahan.md) |

Referensi: [C++ reference](https://en.cppreference.com/) · [Unreal C++](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-programming-and-scripting).
