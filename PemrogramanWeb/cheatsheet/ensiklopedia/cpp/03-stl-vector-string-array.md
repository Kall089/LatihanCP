# 03 — STL: vector, string, array, dan kawan berurutan

[← Kontrol dan class](02-kontrol-fungsi-class.md) · [README](README.md) · [Lanjut: map dan set →](04-stl-map-set-unordered.md)

STL (*Standard Template Library*) menyediakan kontainer siap pakai. Yang paling sering: **`std::vector`** (daftar dinamis) dan **`std::string`**. Di Unreal, padanan harian adalah `TArray` dan `FString` — konsepnya mirip, nama method berbeda.

## Daftar isi

- [std::vector](#stdvector)
- [push_back dan emplace_back](#push_back-dan-emplace_back)
- [size, empty, capacity, reserve](#size-empty-capacity-reserve)
- [operator[] dan at](#operator-dan-at)
- [insert dan erase](#insert-dan-erase)
- [front, back, pop_back](#front-back-pop_back)
- [clear dan shrink_to_fit](#clear-dan-shrink_to_fit)
- [std::string method inti](#stdstring-method-inti)
- [std::getline dan stringstream](#stdgetline-dan-stringstream)
- [std::array](#stdarray)
- [std::deque](#stddeque)
- [std::list](#stdlist)
- [std::pair](#stdpair)
- [std::tuple](#stdtuple)
- [std::stack](#stdstack)
- [std::queue](#stdqueue)
- [std::priority_queue](#stdpriority_queue)
- [initializer_list](#initializer_list)
- [TArray vs vector (catatan Unreal)](#tarray-vs-vector-catatan-unreal)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## std::vector

**Tipe:** class template (`std::vector<T>`, header `<vector>`)

**Untuk apa:** daftar yang bisa bertambah di akhir dengan waktu rata-rata konstan; elemen berurutan di memori (ramah cache, cocok `[]`).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> harga;
    harga.push_back(10000);
    harga.push_back(15000);

    std::vector<std::string> nama{"Buku", "Pensil"};

    std::cout << "Dua harga, dua nama: " << harga.size() << ' ' << nama.size() << '\n';
    std::cout << nama[0] << " = " << harga[0] << '\n';
    return 0;
}
```

**Yang terjadi:** `harga` mulai kosong lalu berisi `{10000, 15000}`. `nama` langsung diisi dua string. Program mencetak ukuran `2 2` dan `Buku = 10000`. `vector` menyimpan elemen **berdempetan**; menambah di tengah lebih mahal daripada di akhir.

`T` harus bisa di-copy atau di-move. Jangan `vector<bool>` untuk bit — itu spesialisasi aneh, bukan `bool&` sungguhan. Pakai `vector<char>` atau `bitset`.

**Biasanya digabungkan dengan:** `sort`, range-for, `reserve`, class sebagai elemen.

**Jangan:** menyimpan pointer/referensi ke elemen lalu `push_back` tanpa `reserve` cukup — realokasi memindahkan buffer. Jangan `vector` di `UPROPERTY` — pakai `TArray`.

## push_back dan emplace_back

**Tipe:** member function `vector`

**Untuk apa:** `push_back` menambah salinan/move objek jadi; `emplace_back` membangun objek langsung di dalam vector dari argumen constructor.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <vector>

struct Barang {
    std::string nama;
    int stok;
    Barang(std::string n, int s) : nama(std::move(n)), stok(s) {}
};

int main() {
    std::vector<Barang> rak;
    rak.push_back(Barang{"Buku", 3});
    rak.emplace_back("Pensil", 10);

    for (const Barang& b : rak) {
        std::cout << b.nama << ' ' << b.stok << '\n';
    }
    return 0;
}
```

**Yang terjadi:** dua baris tercetak: `Buku 3` dan `Pensil 10`. `emplace_back("Pensil", 10)` memanggil constructor `Barang` di tempat. Untuk `int` atau `string` sederhana, `push_back` sudah cukup jelas. `emplace_back` bersinar pada tipe dengan constructor banyak argumen.

**Biasanya digabungkan dengan:** `reserve` (kurangi realokasi), tipe move-only (`unique_ptr`).

**Jangan:** `emplace_back` dengan tipe yang narrowing-nya membingungkan. Jangan `push_back` di dalam loop tanpa `reserve` jika jumlah sudah diketahui.

## size, empty, capacity, reserve

**Tipe:** member function `vector`

**Untuk apa:** `size` = jumlah elemen; `empty` = `size()==0`; `capacity` = slot sudah dialokasi; `reserve` minta slot di muka.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    std::cout << "awal size=" << v.size()
              << " cap=" << v.capacity()
              << " empty=" << v.empty() << '\n';

    v.reserve(8);
    std::cout << "setelah reserve cap=" << v.capacity() << '\n';

    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    std::cout << "size=" << v.size() << " cap=" << v.capacity() << '\n';
    return 0;
}
```

**Yang terjadi:** vector kosong: size 0, capacity 0 (lazim), `empty` 1. `reserve(8)` menaikkan capacity tanpa menambah elemen. Lima `push_back` membuat size 5; capacity tetap ≥ 8, jadi tidak ada realokasi di loop itu.

`shrink_to_fit` meminta capacity mendekati size (boleh diabaikan implementasi).

**Biasanya digabungkan dengan:** loop yang banyak `push_back`, hindari dangling pointer ke elemen.

**Jangan:** mengira `reserve` mengubah `size` (`v[0]` masih ilegal jika size 0). Jangan `resize` jika kamu hanya butuh kapasitas — `resize` membuat elemen.

## operator[] dan at

**Tipe:** member function akses elemen

**Untuk apa:** `[]` akses cepat tanpa cek; `at` cek batas dan lempar `std::out_of_range`.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> v{10, 20, 30};

    std::cout << v[1] << '\n';
    std::cout << v.at(2) << '\n';

    try {
        std::cout << v.at(9) << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "aman: " << e.what() << '\n';
    }
    return 0;
}
```

**Yang terjadi:** mencetak `20` dan `30`. `at(9)` melempar, ditangkap, pesan error tercetak. `v[9]` adalah *undefined behavior* — bisa crash atau angka sampah, **tanpa** exception.

Di Unreal, `TArray::operator[]` juga tidak ramah jika indeks liar; `IsValidIndex` dulu.

**Biasanya digabungkan dengan:** loop `i < size()`, `at` saat indeks dari input pengguna.

**Jangan:** `[]` pada indeks dari jaringan/file tanpa validasi. Jangan `at` di loop panas super ketat jika indeks sudah dijamin (biaya cek).

## insert dan erase

**Tipe:** member function `vector`

**Untuk apa:** sisip / hapus di posisi iterator. Elemen di kanan bergeser.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 3, 4};
    v.insert(v.begin() + 1, 2);   // {1,2,3,4}
    v.erase(v.begin() + 2);       // hapus 3 → {1,2,4}

    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** sisip `2` di indeks 1, hapus elemen yang saat itu `3`. Output: `1 2 4`. Geser elemen `O(n)` — pada vector besar di tengah, mahal. Iterator setelah `insert`/`erase` di titik itu **invalid**.

Hapus menurut syarat: `erase(remove_if(...), end())` — lihat file 05.

**Biasanya digabungkan dengan:** iterator, `begin()+i` (hanya kontainer random access).

**Jangan:** `erase` di range-for biasa (pakai idiom iterator). Jangan `insert` berulang di `begin()` pada puluhan ribu elemen — pertimbangkan `deque` atau susun ulang.

## front, back, pop_back

**Tipe:** member function `vector`

**Untuk apa:** melihat ujung; `pop_back` membuang elemen terakhir (tidak mengembalikan nilainya).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> tumpukan{7, 8, 9};
    std::cout << "depan " << tumpukan.front()
              << " belakang " << tumpukan.back() << '\n';

    tumpukan.pop_back();
    std::cout << "sekarang belakang " << tumpukan.back() << '\n';
    return 0;
}
```

**Yang terjadi:** `depan 7 belakang 9`, setelah pop `sekarang belakang 8`. `pop_back` pada vector kosong adalah undefined behavior — cek `!v.empty()` dulu.

**Biasanya digabungkan dengan:** stack sederhana, undo list.

**Jangan:** `front()`/`back()`/`pop_back()` pada kosong. Jangan mengira `pop_back` mengembalikan elemen (itu bukan `stack::pop` + top terpisah yang sama — `vector` memang tidak return).

## clear dan shrink_to_fit

**Tipe:** member function `vector`

**Untuk apa:** `clear` menghapus semua elemen (size 0, capacity sering tetap); `shrink_to_fit` meminta melepas kelebihan.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v(100, 1);
    std::cout << "size " << v.size() << " cap " << v.capacity() << '\n';

    v.clear();
    std::cout << "setelah clear size " << v.size()
              << " cap " << v.capacity() << '\n';

    v.shrink_to_fit();
    std::cout << "setelah shrink cap " << v.capacity() << '\n';
    return 0;
}
```

**Yang terjadi:** size 100, capacity ≥ 100. Setelah `clear`, size 0 tetapi capacity biasanya masih 100. Setelah `shrink_to_fit`, capacity sering 0 atau kecil (tidak dijamin standar, tetapi implementasi utama menaati permintaan).

**Biasanya digabungkan dengan:** reuse buffer tiap frame (justru *jangan* shrink jika kamu akan isi ulang — biarkan capacity).

**Jangan:** `shrink_to_fit` tiap frame di game loop. Jangan mengira `clear` men-zero memory untuk keamanan kriptografis.

## std::string method inti

**Tipe:** class (`std::string`)

**Untuk apa:** membangun, mencari, memotong, mengganti teks.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "Belajar C++ STL";
    std::cout << s.substr(8, 3) << '\n';          // C++
    std::cout << s.find("STL") << '\n';           // posisi
    std::cout << std::boolalpha << s.starts_with("Belajar") << '\n';  // C++20
    // C++17: bandingkan s.compare(0, 7, "Belajar") == 0

    s.replace(s.find("STL"), 3, "dasar");
    std::cout << s << '\n';

    s.erase(s.find(' '), 1);
    std::cout << s << '\n';
    return 0;
}
```

**Yang terjadi:** `substr` mengambil `"C++"`. `find` mengembalikan indeks `'S'`. `starts_with` (C++20) true. `replace` mengubah menjadi `Belajar C++ dasar`. `erase` satu spasi pertama. Jika compiler hanya C++17, ganti `starts_with` dengan `s.compare(0, 7, "Belajar") == 0`.

Method lain: `append`, `insert`, `rfind`, `find_first_of`, `empty`, `clear`, `c_str()` (pointer C, hidup selama string tidak merealokasi).

**Biasanya digabungkan dengan:** `stringstream`, `vector<string>`, file.

**Jangan:** menyimpan `c_str()` lalu mengubah string. Jangan `substr` berantai di loop panas (banyak alokasi) — pertimbangkan `string_view`.

## std::getline dan stringstream

**Tipe:** fungsi / class (`<string>`, `<sstream>`)

**Untuk apa:** baca satu baris utuh; pecah teks seperti CSV sederhana.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string baris = "Buku,2,45000";
    std::stringstream ss(baris);
    std::string potong;
    std::vector<std::string> kolom;

    while (std::getline(ss, potong, ',')) {
        kolom.push_back(potong);
    }

    std::cout << "Kolom: " << kolom.size() << '\n';
    std::cout << kolom[0] << " x" << kolom[1] << '\n';
    return 0;
}
```

**Yang terjadi:** teks dipotong pada koma menjadi 3 kolom. Mencetak `Kolom: 3` dan `Buku x2`. `getline(stream, string)` tanpa delimiter memakai newline. Ini **bukan** parser CSV yang mengerti tanda kutip.

**Biasanya digabungkan dengan:** `stoi` pada kolom, baca file `ifstream` + `getline`.

**Jangan:** mengira `>>` menjaga spasi di nama. Jangan `stoi` tanpa `try` jika input dari manusia.

## std::array

**Tipe:** class template (`std::array<T, N>`, `<array>`)

**Untuk apa:** array tetap ukuran *compile-time*, tetapi punya `.size()`, iterator, bisa dikembalikan dari fungsi (berbeda array C).

**Contoh implementasi:**

```cpp
#include <array>
#include <iostream>

int main() {
    std::array<int, 4> nilai{80, 75, 90, 70};
    int jumlah = 0;
    for (int n : nilai) {
        jumlah += n;
    }
    std::cout << "rata " << (jumlah / static_cast<double>(nilai.size())) << '\n';
    std::cout << "terakhir " << nilai.back() << '\n';
    return 0;
}
```

**Yang terjadi:** rata-rata `78.75`, terakhir `70`. `N` wajib konstan compile-time. Lebih aman daripada `int nilai[4]` karena tidak membus jadi pointer saat dikirim ke fungsi (tetap objek).

Di Unreal, `TStaticArray` / `TArray` lebih lazim. `std::array` bagus di math murni.

**Biasanya digabungkan dengan:** `std::sort(nilai.begin(), nilai.end())`, tuple unpack.

**Jangan:** `std::array` jika `N` baru diketahui saat runtime — pakai `vector`. Jangan mengira ia heap; ia di stack jika variabel lokal.

## std::deque

**Tipe:** class template (`<deque>`)

**Untuk apa:** antrian dua ujung: `push_front` dan `push_back` murah; indeks `[]` tetap ada, tetapi memori tidak satu blok utuh.

**Contoh implementasi:**

```cpp
#include <deque>
#include <iostream>

int main() {
    std::deque<int> antrian;
    antrian.push_back(2);
    antrian.push_back(3);
    antrian.push_front(1);

    std::cout << antrian.front() << " ... " << antrian.back() << '\n';
    antrian.pop_front();
    std::cout << "sekarang depan " << antrian.front() << '\n';
    return 0;
}
```

**Yang terjadi:** isi `[1,2,3]`, cetak `1 ... 3`, setelah `pop_front` depan menjadi `2`. Pointer ke elemen `deque` lebih stabil daripada `vector` saat push di ujung (blok-blok), tetapi tetap jangan andalkan saat insert di tengah.

**Biasanya digabungkan dengan:** BFS, antrian kerja, sliding window.

**Jangan:** `deque` sebagai default pengganti `vector` — `vector` lebih cepat untuk scan linear. Jangan `std::vector<bool>`-style asumsi kontigu.

## std::list

**Tipe:** class template (linked list, `<list>`)

**Untuk apa:** sisip/hapus di tengah *jika kamu sudah punya iterator* tanpa geser elemen; iterator tetap valid kecuali yang dihapus.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <list>
#include <string>

int main() {
    std::list<std::string> antre{"A", "C"};
    auto it = antre.end();
    --it;  // tunjuk "C"
    antre.insert(it, "B");

    for (const std::string& s : antre) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** `A B C` tercetak. `list` **tidak** punya `[]`. Melangkah ke elemen ke-n adalah `O(n)`. Di praktik modern, `vector` hampir selalu lebih cepat kecuali pola sisip-tengah + iterator stabil yang terbukti butuh.

**Biasanya digabungkan dengan:** splice antar list, LRU kasar.

**Jangan:** memakai `list` “karena sisip O(1)” tanpa iterator siap. Jangan `list` di hot path game.

## std::pair

**Tipe:** class template (`<utility>`)

**Untuk apa:** mengikat dua nilai: kunci+nilai, koordinat, hasil+status.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::pair<std::string, int> item{"Pensil", 20};
    std::cout << item.first << ' ' << item.second << '\n';

    std::vector<std::pair<int, int>> titik{{0, 0}, {1, 4}};
    for (const auto& [x, y] : titik) {  // C++17
        std::cout << x << ',' << y << '\n';
    }
    return 0;
}
```

**Yang terjadi:** `Pensil 20`, lalu `0,0` dan `1,4`. `map` menyimpan `pair<const Key, T>`. `std::make_pair` menebak tipe. C++17 structured binding merapikan `.first/.second`.

**Biasanya digabungkan dengan:** `map`, `minmax`, return dua nilai.

**Jangan:** `pair` bersarang dalam (`pair<int, pair<...>>`) — `tuple` atau `struct` bernama lebih jelas.

## std::tuple

**Tipe:** class template (`<tuple>`)

**Untuk apa:** lebih dari dua field tanpa membuat `struct` (sementara, atau return jamak).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int, bool> infoBarang() {
    return {"Buku", 45000, true};
}

int main() {
    auto [nama, harga, ada] = infoBarang();
    std::cout << nama << ' ' << harga << ' ' << ada << '\n';
    std::cout << std::get<1>(infoBarang()) << '\n';
    return 0;
}
```

**Yang terjadi:** `Buku 45000 1`, lalu `45000` lewat `get<1>`. Jika field punya makna jangka panjang, buat `struct` — nama member lebih baik daripada `get<2>`.

**Biasanya digabungkan dengan:** structured binding, `std::tie`, ignore `std::ignore`.

**Jangan:** tuple 6 elemen sebagai model domain. Jangan `get<N>` dengan N yang mudah tertukar.

## std::stack

**Tipe:** class template adaptor (`<stack>`)

**Untuk apa:** LIFO: undo, kurung seimbang, DFS eksplisit.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<std::string> undo;
    undo.push("ketik A");
    undo.push("ketik B");

    std::cout << undo.top() << '\n';
    undo.pop();
    std::cout << undo.top() << '\n';
    return 0;
}
```

**Yang terjadi:** `top` adalah `ketik B`, setelah `pop` menjadi `ketik A`. `pop` tidak mengembalikan nilai — ambil `top` dulu. Default container adalah `deque`.

**Biasanya digabungkan dengan:** parsing, backtracking.

**Jangan:** `top`/`pop` pada stack kosong. Jangan iterasi stack (tidak ada begin/end publik).

## std::queue

**Tipe:** class template adaptor (`<queue>`)

**Untuk apa:** FIFO: antrian cetak, BFS, tugas berurutan.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <queue>
#include <string>

int main() {
    std::queue<std::string> antrian;
    antrian.push("A");
    antrian.push("B");
    antrian.push("C");

    while (!antrian.empty()) {
        std::cout << antrian.front() << ' ';
        antrian.pop();
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** `A B C` tercetak berurutan. `front` + `pop`. Default container `deque`.

**Biasanya digabungkan dengan:** BFS, producer-consumer sederhana (masih butuh mutex jika multithread).

**Jangan:** `front` pada kosong. Jangan memakai `queue` jika kamu butuh sisip prioritas — itu `priority_queue`.

## std::priority_queue

**Tipe:** class template adaptor (`<queue>`)

**Untuk apa:** selalu mengambil elemen “terbesar” (default) dalam `O(log n)` sisip.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int> pq;
    pq.push(10);
    pq.push(50);
    pq.push(30);

    while (!pq.empty()) {
        std::cout << pq.top() << ' ';
        pq.pop();
    }
    std::cout << '\n';

    std::priority_queue<int, std::vector<int>, std::greater<int>> terkecil;
    terkecil.push(10);
    terkecil.push(50);
    std::cout << "min-top " << terkecil.top() << '\n';
    return 0;
}
```

**Yang terjadi:** default max-heap mencetak `50 30 10`. Versi `greater` membuat min-heap, `min-top 10`. Tidak ada iterator; bukan terurut penuh untuk ditelusuri.

**Biasanya digabungkan dengan:** Dijkstra sederhana, jadwal event, “ambil N terbesar”.

**Jangan:** mengira isi di dalam sudah terurut jika kamu dump sembarangan (kamu tidak bisa dump tanpa pop). Jangan ubah elemen lewat pointer ke dalam heap.

## initializer_list

**Tipe:** class template (`std::initializer_list<T>`)

**Untuk apa:** mengisi kontainer dengan `{1, 2, 3}`; constructor yang menerima daftar.

**Contoh implementasi:**

```cpp
#include <initializer_list>
#include <iostream>
#include <vector>

int jumlahkan(std::initializer_list<int> xs) {
    int s = 0;
    for (int n : xs) {
        s += n;
    }
    return s;
}

int main() {
    std::vector<int> v{1, 2, 3, 4};
    std::cout << jumlahkan({1, 2, 3}) << '\n';
    std::cout << v.size() << '\n';
    return 0;
}
```

**Yang terjadi:** `jumlahkan` menghasilkan `6`. Vector punya 4 elemen. Daftar `{...}` membuat `initializer_list` yang menunjuk ke array sementara.

Catatan: constructor `vector` punya overload `vector(size, value)` dan `vector{list}`. `vector<int> v(3, 1)` = tiga angka 1. `vector<int> v{3, 1}` = dua elemen 3 dan 1. Kurung biasa vs kurung kurawal **berbeda**.

**Biasanya digabungkan dengan:** constructor class, `vector`/`map` literal.

**Jangan:** menyimpan `initializer_list` lebih lama dari ekspresi (dangling). Jangan bingung `()` vs `{}` pada `vector`.

## TArray vs vector (catatan Unreal)

**Tipe:** perbandingan API (Unreal `TArray<T>` vs `std::vector<T>`)

**Untuk apa:** memilih kontainer yang cocok di modul Unreal agar `UPROPERTY` dan engine API menerima datamu.

**Contoh implementasi:**

```cpp
// Ini C++ biasa: analogi API, bukan file Unreal yang di-g++.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{4, 5, 6};
    v.push_back(7);  // padanan Unreal: TArray::Add
    std::cout << "size (di TArray: Num) = " << v.size() << '\n';
    return 0;
}
```

Tulisan di atas hanya pengingat `size`. Tabel padanan:

| std::vector | TArray |
| --- | --- |
| `push_back` / `emplace_back` | `Add` / `Emplace` |
| `size` / `empty` | `Num` / `IsEmpty` |
| `clear` | `Reset` atau `Empty` |
| `operator[]` | `operator[]` |
| `reserve` | `Reserve` |
| tidak ada | `IsValidIndex` |

Contoh Unreal yang masuk akal (compile di modul game, bukan `g++`):

```cpp
#include "CoreMinimal.h"

void ContohTArray()
{
    TArray<int32> Harga;
    Harga.Add(10000);
    Harga.Reserve(16);
    if (Harga.IsValidIndex(0))
    {
        UE_LOG(LogTemp, Log, TEXT("Harga0=%d Num=%d"), Harga[0], Harga.Num());
    }
}
```

**Yang terjadi:** di program `g++`, analogi mencetak `4` (size vector). Di Unreal, `TArray` mencatat satu harga dan log `Harga0=10000 Num=1`. `UPROPERTY() TArray<int32>` bisa diedit di Details; `std::vector` tidak.

**Biasanya digabungkan dengan:** `UPROPERTY`, `TMap`, `TSet`, `Algo::Sort`.

**Jangan:** menaruh `std::vector` sebagai `UPROPERTY`. Jangan mencampur iterator STL pada `TArray` seolah selalu identik (banyak algoritma Unreal di namespace `Algo`).

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menghindari crash kontainer dan salah pilih struktur.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    int* p = &v[0];
    v.push_back(4);  // mungkin merealokasi
    // jangan pakai p di sini

    std::vector<int> aman;
    aman.reserve(100);
    aman.push_back(1);
    int* q = &aman[0];
    aman.push_back(2);  // cap 100, q masih valid *selama* tidak melebihi cap
    std::cout << *q << ' ' << aman.size() << '\n';
    return 0;
}
```

**Yang terjadi:** `p` berbahaya setelah `push_back`. `q` masih sah dalam contoh reserve, mencetak `1 2`. Tetap lebih aman tidak menyimpan pointer ke dalam vector kecuali umur jelas.

**Biasanya digabungkan dengan:** `reserve`, iterator invalidate, file 05 `erase`.

**Jangan:** `vector<bool>`; `[]` liar; `pop` kosong; `list` sebagai default; pointer ke elemen yang bisa pindah.
