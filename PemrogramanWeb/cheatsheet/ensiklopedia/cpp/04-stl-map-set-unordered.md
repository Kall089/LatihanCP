# 04 — STL: map, set, dan unordered

[← vector dan string](03-stl-vector-string-array.md) · [README](README.md) · [Lanjut: algoritma dan iterator →](05-stl-algorithm-iterator.md)

`vector` bagus untuk daftar. Jika kamu sering bertanya “berapa harga **nama ini**?” atau “apakah ID ini sudah ada?”, pakai **asosiatif**: `map` / `set` (terurut, pohon) atau `unordered_map` / `unordered_set` (hash, rata-rata lebih cepat).

Di Unreal: `TMap`, `TSet`. Konsep sama, method `Add` / `Find` / `Contains`.

## Daftar isi

- [std::map](#stdmap)
- [operator[] vs insert vs try_emplace](#operator-vs-insert-vs-try_emplace)
- [find, count, contains](#find-count-contains)
- [erase pada map](#erase-pada-map)
- [iterasi map](#iterasi-map)
- [std::set](#stdset)
- [std::multimap](#stdmultimap)
- [std::multiset](#stdmultiset)
- [std::unordered_map](#stdunordered_map)
- [std::unordered_set](#stdunordered_set)
- [pair sebagai kunci](#pair-sebagai-kunci)
- [structured binding](#structured-binding)
- [lower_bound dan equal_range](#lower_bound-dan-equal_range)
- [custom comparator singkat](#custom-comparator-singkat)
- [TMap dan TSet (Unreal)](#tmap-dan-tset-unreal)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## std::map

**Tipe:** class template (`std::map<K, V>`, header `<map>`)

**Untuk apa:** kamus terurut menurut kunci. Tiap kunci unik. Cari / sisip `O(log n)`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> harga;
    harga["Buku"] = 45000;
    harga["Pensil"] = 3000;
    harga["Penghapus"] = 2000;

    std::cout << "Pensil: " << harga["Pensil"] << '\n';
    std::cout << "Jumlah jenis: " << harga.size() << '\n';
    return 0;
}
```

**Yang terjadi:** tiga pasangan tersimpan. Kunci `string` diurut leksikografis (Buku, Penghapus, Pensil). Mencetak `3000` dan `3`. `map` memakai pohon merah-hitam: iterasi selalu terurut, tidak acak.

Kunci bersifat `const` di dalam map. `V` boleh diubah. `K` harus bisa dibandingkan dengan `<` (atau comparator kustom).

**Biasanya digabungkan dengan:** `string` sebagai nama, `find` agar `[]` tidak membuat entri baru, loop terurut.

**Jangan:** memakai `map` jika urutan tidak penting dan n besar — `unordered_map` biasanya lebih cepat. Jangan `map` sebagai `UPROPERTY` — pakai `TMap`.

## operator[] vs insert vs try_emplace

**Tipe:** member function `map`

**Untuk apa:** `[]` akses-atau-buat; `insert` gagal jika kunci ada; `try_emplace` (C++17) membangun nilai hanya jika kunci baru.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> stok;
    stok["Buku"] = 5;                 // buat + isi
    stok["Buku"] = 7;                 // kunci ada: nilai diganti

    auto hasil = stok.insert({"Pensil", 10});
    std::cout << "insert Pensil baru? " << hasil.second << '\n';

    hasil = stok.insert({"Pensil", 99});
    std::cout << "insert Pensil lagi? " << hasil.second
              << " nilai=" << hasil.first->second << '\n';

    stok.try_emplace("Penghapus", 3);
    stok.try_emplace("Penghapus", 100);  // diabaikan

    std::cout << "Penghapus=" << stok["Penghapus"] << '\n';
    std::cout << "Spidol=" << stok["Spidol"] << '\n';  // hati-hati: membuat 0
    std::cout << "size=" << stok.size() << '\n';
    return 0;
}
```

**Yang terjadi:** `Buku` menjadi 7. Insert pertama `Pensil` sukses (`1`). Insert kedua gagal (`0`), nilai tetap 10. `try_emplace` kedua tidak menimpa 3. `stok["Spidol"]` **membuat** entri `Spidol → 0` hanya karena dibaca. `size` bertambah.

Ini bug klasik: cek keberadaan dengan `[]` justru menambah sampah.

**Biasanya digabungkan dengan:** `find`, `at` (lempar jika tidak ada), `insert_or_assign` (C++17, selalu tulis nilai).

**Jangan:** `if (m[k])` untuk “apakah ada”. Jangan `[]` pada `map<K, V>` jika `V` tidak default-constructible.

## find, count, contains

**Tipe:** member function pencarian

**Untuk apa:** mencari tanpa side-effect. `find` → iterator; `count` 0 atau 1 pada `map`/`set`; `contains` (C++20) boolean.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> harga{{"Buku", 45000}, {"Pensil", 3000}};

    auto it = harga.find("Buku");
    if (it != harga.end()) {
        std::cout << it->first << '=' << it->second << '\n';
    }

    std::cout << "ada Pena? count=" << harga.count("Pena") << '\n';

#if __cplusplus >= 202002L
    std::cout << std::boolalpha << harga.contains("Pensil") << '\n';
#else
    std::cout << (harga.find("Pensil") != harga.end()) << '\n';
#endif
    return 0;
}
```

**Yang terjadi:** mencetak `Buku=45000`, `ada Pena? count=0`, lalu true untuk Pensil. `find` tidak membuat kunci baru.

`count` pada `multimap` bisa > 1. Pada `map` cukup 0/1 — `contains` lebih berniat “apakah ada”.

**Biasanya digabungkan dengan:** early return, cache, indeks ID.

**Jangan:** `find` lalu `it->second` tanpa cek `end()`. Jangan memakai `count` di `unordered_map` sebagai “berapa kemunculan kunci duplikat” — kunci tetap unik.

## erase pada map

**Tipe:** member function

**Untuk apa:** menghapus satu kunci, atau rentang iterator.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> stok{{"A", 1}, {"B", 2}, {"C", 3}};

    std::size_t n = stok.erase("B");
    std::cout << "terhapus " << n << " size=" << stok.size() << '\n';

    n = stok.erase("Z");
    std::cout << "hapus Z: " << n << '\n';

    for (const auto& [k, v] : stok) {
        std::cout << k << ' ' << v << '\n';
    }
    return 0;
}
```

**Yang terjadi:** hapus `B` mengembalikan 1, size 2. Hapus `Z` mengembalikan 0. Sisa `A 1` dan `C 3` (terurut). Ada overload `erase(iterator)` yang mengembalikan iterator berikutnya — penting saat menghapus saat iterasi.

**Biasanya digabungkan dengan:** `find` lalu `erase(it)`, loop aman.

**Jangan:** `erase` iterator lalu memakai iterator lama. Jangan menghapus sambil `for (auto& p : map)` tanpa pola iterator.

## iterasi map

**Tipe:** pola (range-for + structured binding)

**Untuk apa:** menelusuri semua pasangan, sudah terurut naik menurut kunci.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> urut{{3, "c"}, {1, "a"}, {2, "b"}};

    for (const auto& [id, nama] : urut) {
        std::cout << id << ':' << nama << '\n';
    }
    return 0;
}
```

**Yang terjadi:** meski insert 3,1,2, output selalu `1:a` `2:b` `3:c`. Binding `const auto&` menghindari copy `string`. Tanpa C++17: `for (const auto& p : urut) { p.first; p.second; }`.

**Biasanya digabungkan dengan:** laporan terurut, `rbegin` untuk turun.

**Jangan:** mengandalkan urutan insert. Jangan mengubah kunci lewat referensi (kunci `const`).

## std::set

**Tipe:** class template (`std::set<T>`, `<set>`)

**Untuk apa:** kumpulan unik terurut. “Apakah sudah pernah?” + iterasi terurut.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <set>
#include <string>

int main() {
    std::set<std::string> tag;
    tag.insert("baru");
    tag.insert("diskon");
    tag.insert("baru");  // ditolak, sudah ada

    std::cout << "jumlah " << tag.size() << '\n';
    if (tag.count("diskon")) {
        std::cout << "ada diskon\n";
    }
    for (const std::string& t : tag) {
        std::cout << t << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** size `2`. `ada diskon` tercetak. Iterasi: `baru diskon` (alfabet). `insert` mengembalikan `pair<iterator,bool>` seperti map.

`std::set<int>` vs `vector` + `sort` + `unique`: set bagus jika sering sisip/hapus acak; vector lebih cepat jika isi sekali lalu hanya baca.

**Biasanya digabungkan dengan:** cek keanggotaan, irisan manual, `set_union` (file 05).

**Jangan:** `set` hanya untuk menghilangkan duplikat sekali — sering lebih murah `vector` + sort + unique. Jangan `set<T*>` tanpa comparator jika yang kamu ingin bandingkan adalah *isi* objek.

## std::multimap

**Tipe:** class template (`<map>`)

**Untuk apa:** satu kunci, banyak nilai. Contoh: nama kota → banyak toko; ID siswa → banyak nilai ujian.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::multimap<std::string, int> nilai;
    nilai.insert({"Haikal", 80});
    nilai.insert({"Haikal", 90});
    nilai.insert({"Siti", 88});

    auto [awal, akhir] = nilai.equal_range("Haikal");
    for (auto it = awal; it != akhir; ++it) {
        std::cout << it->second << ' ';
    }
    std::cout << '\n';
    std::cout << "count Haikal=" << nilai.count("Haikal") << '\n';
    return 0;
}
```

**Yang terjadi:** `80 90` (urutan nilai dengan kunci sama mengikuti aturan insert/ekivalen). `count` = 2. Tidak ada `operator[]` pada `multimap` — ambigu nilai mana.

**Biasanya digabungkan dengan:** `equal_range`, indeks sekunder.

**Jangan:** `[]` (tidak ada). Jangan mengira `find` mengembalikan semua — hanya satu, sisanya `equal_range`.

## std::multiset

**Tipe:** class template (`<set>`)

**Untuk apa:** banyak salinan nilai yang sama, tetap terurut. Tas (bag) terurut.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <set>

int main() {
    std::multiset<int> skor{70, 90, 70, 80};
    std::cout << "size " << skor.size() << '\n';
    std::cout << "70 muncul " << skor.count(70) << '\n';

    skor.erase(skor.find(70));  // hapus satu 70
    std::cout << "setelah hapus satu, count 70=" << skor.count(70) << '\n';

    skor.erase(70);  // hapus SEMUA 70 tersisa
    std::cout << "size akhir " << skor.size() << '\n';
    return 0;
}
```

**Yang terjadi:** size 4, `70` muncul 2. `erase(iterator)` menghapus satu. `erase(70)` (nilai) menghapus semua 70. Size akhir 2 (`80` dan `90`). Perbedaan overload `erase` ini sering mengejutkan.

**Biasanya digabungkan dengan:** statistik peringkat, antrian terurut dengan duplikat.

**Jangan:** `erase(nilai)` jika kamu hanya ingin hapus satu kemunculan — pakai `find` dulu.

## std::unordered_map

**Tipe:** class template (`<unordered_map>`)

**Untuk apa:** kamus hash: rata-rata `O(1)` cari/sisip, **tanpa** urutan kunci.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> stok;
    stok.reserve(16);
    stok["Buku"] = 5;
    stok["Pensil"] = 20;

    if (auto it = stok.find("Buku"); it != stok.end()) {  // C++17 if-init
        std::cout << it->second << '\n';
    }

    std::cout << "bucket " << stok.bucket_count()
              << " load " << stok.load_factor() << '\n';
    return 0;
}
```

**Yang terjadi:** mencetak `5`, lalu jumlah bucket dan load factor (rasio size/bucket). Iterasi **tidak** alfabetis. `reserve` mengurangi rehash saat banyak insert.

Kunci harus hashable: `int`, `string`, pointer, dll. `pair` tidak punya `std::hash` standar di semua bentuk — sering perlu hash kustom.

Di Unreal, `TMap` default juga hash-like (bukan pohon).

**Biasanya digabungkan dengan:** cache ID → objek, hitung frekuensi kata, `reserve`.

**Jangan:** mengandalkan urutan iterasi (bisa berubah setelah rehash). Jangan memakai tipe floating sebagai kunci hash tanpa sadar NaN. Jangan memodifikasi field yang memengaruhi hash pada kunci yang sudah masuk.

## std::unordered_set

**Tipe:** class template (`<unordered_set>`)

**Untuk apa:** keanggotaan unik, cek cepat, tidak peduli urutan.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::unordered_set<std::string> sudahDiproses;
    std::string id[] = {"A1", "B2", "A1", "C3"};

    for (const std::string& x : id) {
        if (!sudahDiproses.insert(x).second) {
            std::cout << "duplikat " << x << '\n';
        }
    }
    std::cout << "unik " << sudahDiproses.size() << '\n';
    return 0;
}
```

**Yang terjadi:** `A1` kedua tercetak sebagai duplikat. Unik = 3. `insert` mengembalikan `pair<iterator,bool>`; `false` = sudah ada.

**Biasanya digabungkan dengan:** filter ID, BFS visited set.

**Jangan:** `unordered_set` jika kamu butuh urutan laporan. Jangan pointer ke elemen set setelah banyak insert (rehash bisa pindah node tergantung implementasi — iterator biasanya tetap valid kecuali yang dihapus, tetapi pointer ke node hash tetap hati-hati saat rehash: iterator `unordered_*` invalid pada rehash).

## pair sebagai kunci

**Tipe:** pola (`map<pair<int,int>, V>`)

**Untuk apa:** kunci majemuk: koordinat petak, pasangan (angkatan, nim).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <utility>

int main() {
    std::map<std::pair<int, int>, std::string> petak;
    petak[{0, 0}] = "rumah";
    petak[{1, 2}] = "toko";

    auto kunci = std::make_pair(1, 2);
    if (auto it = petak.find(kunci); it != petak.end()) {
        std::cout << it->second << '\n';
    }
    return 0;
}
```

**Yang terjadi:** mencetak `toko`. `pair` punya `operator<` leksikografis, jadi sah sebagai kunci `map`. Untuk `unordered_map`, kamu perlu `std::hash` kustom untuk `pair` — lebih mudah bungkus `struct Petak { int x,y; }` + hash, atau pakai `map`.

**Biasanya digabungkan dengan:** grid 2D, indeks ganda.

**Jangan:** `unordered_map<pair<int,int>, ...>` tanpa hash. Jangan kunci `float` pasangan (equality goyah).

## structured binding

**Tipe:** fitur bahasa C++17

**Untuk apa:** membongkar `pair`, `tuple`, `struct` agregat, elemen map menjadi nama lokal.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> harga{{"Buku", 45000}};

    for (auto& [nama, nilai] : harga) {
        nilai += 1000;  // ubah nilai
        std::cout << nama << ' ' << nilai << '\n';
    }
    return 0;
}
```

**Yang terjadi:** `Buku 46000`. `auto&` memungkinkan mengubah `nilai`. `const auto&` untuk baca. Binding ke kunci map tetap tidak bisa mengubah kunci.

**Biasanya digabungkan dengan:** `map`, `tuple`, `insert` result (`auto [it, ok]`).

**Jangan:** `auto [a, b]` pada tipe yang tidak bisa dipecah. Jangan mengira binding menyalin selalu — tergantung `auto` vs `auto&`.

## lower_bound dan equal_range

**Tipe:** member function kontainer terurut / algoritma

**Untuk apa:** mencari posisi sisip atau rentang kunci sama pada `map`/`set`/`multimap` dalam `O(log n)`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> m{{10, "a"}, {20, "b"}, {30, "c"}};

    auto it = m.lower_bound(20);
    std::cout << it->first << '\n';  // 20

    it = m.lower_bound(25);
    std::cout << "sisip 25 sebelum " << it->first << '\n';  // 30

    auto [awal, akhir] = m.equal_range(20);
    std::cout << "jarak 20: " << std::distance(awal, akhir) << '\n';
    return 0;
}
```

**Yang terjadi:** `lower_bound(20)` menunjuk 20. `lower_bound(25)` menunjuk 30 (elemen pertama yang tidak lebih kecil dari 25). `equal_range(20)` panjang 1 pada `map` biasa.

**Biasanya digabungkan dengan:** `multimap`, hint insert, pencarian prefix (dengan comparator khusus).

**Jangan:** `lower_bound` pada `unordered_map` (tidak terurut; method ini tidak ada). Jangan `lower_bound` pada `vector` tak terurut — hasil salah diam-diam.

## custom comparator singkat

**Tipe:** template parameter / functor

**Untuk apa:** urutan bukan default: string case-insensitive, `map` descending, set pointer menurut isi.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

struct BandingPanjang {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        return a < b;
    }
};

int main() {
    std::map<std::string, int, BandingPanjang> m;
    m["Pensil"] = 1;
    m["Buku"] = 2;
    m["Pena"] = 3;

    for (const auto& [k, v] : m) {
        std::cout << k << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** urutan menurut panjang lalu alfabet: `Buku` (4), `Pena` (4, Pena < Buku? 'P' vs 'B' — `Buku` dulu), lalu `Pensil` (6). Output: `Buku Pena Pensil`. Comparator harus *strict weak ordering*: jangan `<=`.

**Biasanya digabungkan dengan:** `set`, `priority_queue` (comparator terbalik), sort file 05.

**Jangan:** comparator yang membaca data berubah-ubah. Jangan `return a <= b`. Jangan hash tidak konsisten dengan `==` pada unordered.

## TMap dan TSet (Unreal)

**Tipe:** class template Unreal (`TMap<K,V>`, `TSet<T>`)

**Untuk apa:** kamus/set yang bisa `UPROPERTY`, dikenali editor, dan dipakai API engine.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TokoHargaActor.generated.h"

UCLASS()
class ATokoHargaActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Toko")
    TMap<FName, int32> HargaBarang;

    UPROPERTY(EditAnywhere, Category = "Toko")
    TSet<FName> BarangHabis;

    virtual void BeginPlay() override
    {
        Super::BeginPlay();

        HargaBarang.Add(TEXT("Buku"), 45000);
        if (const int32* Ketemu = HargaBarang.Find(TEXT("Buku")))
        {
            UE_LOG(LogTemp, Log, TEXT("Harga Buku=%d"), *Ketemu);
        }

        BarangHabis.Add(TEXT("Pensil"));
        if (BarangHabis.Contains(TEXT("Pensil")))
        {
            UE_LOG(LogTemp, Warning, TEXT("Pensil habis"));
        }
    }
};
```

**Yang terjadi:** saat Play, `TMap` mendapat kunci `Buku`. `Find` mengembalikan pointer ke nilai (bukan iterator STL); jika tidak ada, `nullptr`. Log harga, lalu warning stok habis. Di Details, kamu bisa menambah pasangan secara visual.

`FindOrAdd` mirip `operator[]` STL (membuat default). `Contains` untuk set/map. Iterasi: `for (const TPair<FName, int32>& P : HargaBarang)`.

**Biasanya digabungkan dengan:** `FName` (cepat banding), `FString` (lebih fleksibel), `UPROPERTY`.

**Jangan:** `std::map` sebagai `UPROPERTY`. Jangan menyimpan `UObject*` di `TMap` tanpa `UPROPERTY` jika kamu mengandalkan GC (lihat file 06–07). Jangan mengandalkan urutan `TMap` seperti `std::map` terurut.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menghindari entri hantu, rehash, dan salah hapus.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> m{{"Buku", 1}};

    if (m["Pena"] == 0) {
        std::cout << "ini BUKAN 'Pena tidak ada' — Pena sudah dibuat!\n";
    }
    std::cout << "size=" << m.size() << '\n';

    if (m.find("Spidol") == m.end()) {
        std::cout << "Spidol benar-benar tidak ada, size tetap " << m.size() << '\n';
    }
    return 0;
}
```

**Yang terjadi:** `[]` membuat `Pena`. Size menjadi 2. `find("Spidol")` tidak menambah.

**Biasanya digabungkan dengan:** semua map/set di atas.

**Jangan:** `[]` untuk cek; hapus saat iterasi tanpa iterator baru; hash `pair` tanpa dukungan; kunci `std::string` yang dibuat berulang di loop panas tanpa perlu (pertimbangkan `string_view` C++20 transparent lookup, atau `FName` di Unreal).
