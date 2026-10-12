# 05 — STL: iterator dan algoritma

[← map dan set](04-stl-map-set-unordered.md) · [README](README.md) · [Lanjut: memori dan smart pointer →](06-memory-smart-pointer.md)

Algoritma standar (`<algorithm>`, `<numeric>`) bekerja pada **rentang iterator** `[awal, akhir)`. Kamu tidak menulis loop mentah untuk sort, cari, hitung, ubah, atau jumlahkan — kecuali loop-nya memang lebih jelas.

Di Unreal, banyak padanan ada di namespace `Algo` (`Algo::Sort`, `Algo::Find`). Pola pikirnya sama.

## Daftar isi

- [iterator begin end](#iterator-begin-end)
- [kategori iterator](#kategori-iterator)
- [std::sort](#stdsort)
- [std::stable_sort](#stdstable_sort)
- [std::find](#stdfind)
- [std::find_if](#stdfind_if)
- [std::count](#stdcount)
- [std::count_if](#stdcount_if)
- [std::transform](#stdtransform)
- [std::accumulate](#stdaccumulate)
- [std::copy dan back_inserter](#stdcopy-dan-back_inserter)
- [std::fill dan generate](#stdfill-dan-generate)
- [std::reverse](#stdreverse)
- [std::unique dan erase](#stdunique-dan-erase)
- [remove_if erase idiom](#remove_if-erase-idiom)
- [std::min_element dan max_element](#stdmin_element-dan-max_element)
- [std::all_of any_of none_of](#stdall_of-any_of-none_of)
- [std::for_each](#stdfor_each)
- [std::binary_search](#stdbinary_search)
- [std::lower_bound pada vector](#stdlower_bound-pada-vector)
- [std::iota](#stdiota)
- [std::next prev distance](#stdnext-prev-distance)
- [lambda sebagai predikat](#lambda-sebagai-predikat)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## iterator begin end

**Tipe:** objek penunjuk posisi dalam kontainer

**Untuk apa:** menandai rentang yang dipahami algoritma. `begin()` elemen pertama, `end()` **satu di belakang terakhir** (bukan elemen valid).

**Contoh implementasi:**

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{10, 20, 30};
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    if (!v.empty()) {
        std::cout << "satu sebelum end: " << *std::prev(v.end()) << '\n';
    }
    return 0;
}
```

**Yang terjadi:** mencetak `10 20 30` lalu `30`. Dereference `end()` adalah undefined behavior. `cbegin()`/`cend()` memberi iterator const.

Pointer ke array C juga iterator: `std::sort(a, a + n)`.

**Biasanya digabungkan dengan:** semua algoritma di file ini, range-for (syntactic sugar).

**Jangan:** `*v.end()`. Jangan membandingkan iterator dari dua kontainer berbeda. Jangan memakai iterator setelah `insert`/`erase` yang meninvalidasinya.

## kategori iterator

**Tipe:** konsep / tag iterator

**Untuk apa:** memahami algoritma mana yang sah: `list` tidak bisa `sort` algoritma acak-akses (punya `list::sort` sendiri); `vector` bisa semuanya.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main() {
    std::vector<int> v{3, 1, 2};
    std::list<int> l{3, 1, 2};

    // random access: it + 2 sah
    auto itv = v.begin() + 2;
    std::cout << *itv << '\n';

    // bidirectional: ++ dan --
    auto itl = l.end();
    --itl;
    std::cout << *itl << '\n';

    // l.begin() + 2;  // error: list bukan random access
    return 0;
}
```

**Yang terjadi:** `vector` mendukung `+ 2` menuju elemen `2`. `list` hanya `--`/`++`; mencetak `2` (elemen terakhir). `std::sort` butuh random access iterator. `std::list::sort` mengurutkan list di tempat.

**Biasanya digabungkan dengan:** memilih kontainer, `std::advance`.

**Jangan:** memaksa `sort` pada `list` iterator. Jangan `it + n` pada `map` iterator.

## std::sort

**Tipe:** fungsi template (`<algorithm>`)

**Untuk apa:** mengurutkan rentang random-access. Default: naik, memakai `<`.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> harga{15000, 3000, 45000};
    std::sort(harga.begin(), harga.end());
    for (int n : harga) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    std::vector<std::string> nama{"Pensil", "Buku", "Pena"};
    std::sort(nama.begin(), nama.end(),
              [](const std::string& a, const std::string& b) {
                  return a.size() < b.size();
              });
    for (const std::string& s : nama) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** harga menjadi `3000 15000 45000`. Nama diurut panjang: `Buku Pena Pensil` (Buku dan Pena sama panjang — urutan relatif **tidak dijamin**; lihat `stable_sort`). Kompleksitas rata-rata `O(n log n)`.

Di Unreal: `Algo::Sort(Harga);` atau `Harga.Sort();` pada `TArray`.

**Biasanya digabungkan dengan:** `vector`, `array`, lambda comparator, `unique`.

**Jangan:** `sort` pada `list`/`map` (map sudah terurut). Jangan comparator `<=`. Jangan `sort` rentang yang iteratornya invalid.

## std::stable_sort

**Tipe:** fungsi template (`<algorithm>`)

**Untuk apa:** mengurutkan tetapi mempertahankan urutan relatif elemen yang “sama” menurut comparator.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Barang {
    std::string nama;
    int kategori;
};

int main() {
    std::vector<Barang> v{{"Buku", 1}, {"Pena", 2}, {"Penggaris", 1}};
    std::stable_sort(v.begin(), v.end(),
                     [](const Barang& a, const Barang& b) {
                         return a.kategori < b.kategori;
                     });
    for (const Barang& b : v) {
        std::cout << b.nama << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** kategori 1 dulu, tetap `Buku` sebelum `Penggaris` seperti input. Lalu `Pena`. `sort` biasa bisa menukar `Buku`/`Penggaris`. `stable_sort` memakai memori tambahan, sedikit lebih lambat — pakai jika kestabilan penting (peringkat, UI).

**Biasanya digabungkan dengan:** sort bertingkat (urut nama dulu, lalu stable_sort kategori).

**Jangan:** `stable_sort` default “supaya aman” di hot path tanpa butuh stabil.

## std::find

**Tipe:** fungsi template (`<algorithm>`)

**Untuk apa:** mencari nilai pertama yang `==` target. Linear `O(n)`.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> rak{"Buku", "Pensil", "Pena"};
    auto it = std::find(rak.begin(), rak.end(), "Pensil");
    if (it != rak.end()) {
        std::cout << "indeks " << (it - rak.begin()) << '\n';
    }

    it = std::find(rak.begin(), rak.end(), "Spidol");
    if (it == rak.end()) {
        std::cout << "tidak ada\n";
    }
    return 0;
}
```

**Yang terjadi:** `Pensil` di indeks 1. `Spidol` tidak ada. `it - rak.begin()` sah karena `vector` random access; pada `list` pakai `std::distance`.

Untuk `map`, pakai `map::find` (`O(log n)`), bukan `std::find` linear pada pasangan.

**Biasanya digabungkan dengan:** `vector` kecil, `string` (atau `s.find` member yang lebih cocok untuk substring).

**Jangan:** `std::find` pada `map` sebagai pengganti `m.find`. Jangan dereference iterator `end`.

## std::find_if

**Tipe:** fungsi template

**Untuk apa:** mencari elemen pertama yang memenuhi predikat (lambda/`bool(T)`).

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nilai{40, 55, 72, 90};
    auto it = std::find_if(nilai.begin(), nilai.end(), [](int n) {
        return n >= 70;
    });
    if (it != nilai.end()) {
        std::cout << "lulus pertama: " << *it << '\n';
    }
    return 0;
}
```

**Yang terjadi:** 40 dan 55 gagal, 72 memenuhi, tercetak `lulus pertama: 72`. `find_if_not` kebalikannya.

**Biasanya digabungkan dengan:** struct (cari nama), validasi, `end()` cek.

**Jangan:** predikat dengan side effect berat. Jangan menangkap referensi lokal yang mati jika lambda disimpan (di sini aman, dipakai langsung).

## std::count

**Tipe:** fungsi template

**Untuk apa:** menghitung berapa kali nilai muncul.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nilai{70, 80, 70, 90, 70};
    std::cout << std::count(nilai.begin(), nilai.end(), 70) << '\n';
    return 0;
}
```

**Yang terjadi:** mencetak `3`. Pada `set`, lebih baik `set::count`. Pada `vector` tidak terurut, linear wajib.

**Biasanya digabungkan dengan:** histogram sederhana, tes.

**Jangan:** `count` untuk “apakah ada” pada rentang besar jika kamu akan `break` — `find` berhenti lebih awal. (Untuk kejelasan “berapa”, `count` tetap benar.)

## std::count_if

**Tipe:** fungsi template

**Untuk apa:** menghitung elemen yang lolos syarat.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nilai{40, 55, 72, 90, 61};
    const auto lulus = std::count_if(nilai.begin(), nilai.end(), [](int n) {
        return n >= 70;
    });
    std::cout << "lulus: " << lulus << '\n';
    return 0;
}
```

**Yang terjadi:** 72 dan 90 → `lulus: 2`.

**Biasanya digabungkan dengan:** filter statistik, laporan.

**Jangan:** `count_if` lalu loop lagi untuk mengumpulkan — lebih baik satu loop atau `copy_if`.

## std::transform

**Tipe:** fungsi template

**Untuk apa:** menulis hasil fungsi tiap elemen ke tujuan (bisa kontainer lain, atau menimpa sendiri).

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> harga{10000, 20000, 15000};
    std::vector<int> pajak(harga.size());

    std::transform(harga.begin(), harga.end(), pajak.begin(), [](int h) {
        return h / 10;
    });

    for (int p : pajak) {
        std::cout << p << ' ';
    }
    std::cout << '\n';

    std::transform(harga.begin(), harga.end(), harga.begin(), [](int h) {
        return h + 500;
    });
    std::cout << harga[0] << '\n';
    return 0;
}
```

**Yang terjadi:** `pajak` menjadi `1000 2000 1500`. Transform kedua menimpa `harga[0]` menjadi `10500`. Tujuan harus cukup besar, atau pakai `back_inserter`.

Ada overload dua input (zip): `transform(a0,a1,b0,out, f)` memanggil `f(a,b)`.

**Biasanya digabungkan dengan:** `back_inserter`, lambda, `vector` ukuran sama.

**Jangan:** tujuan lebih pendek dari sumber (overflow). Jangan `transform` overlapping yang tidak dijamin kecuali in-place seperti contoh kedua (sumber=tujuan, aman untuk unary).

## std::accumulate

**Tipe:** fungsi template (`<numeric>`)

**Untuk apa:** melipat rentang jadi satu nilai: jumlah, produk, concat string.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::vector<int> harga{10000, 15000, 7000};
    const int total = std::accumulate(harga.begin(), harga.end(), 0);
    std::cout << "total " << total << '\n';

    const int produk = std::accumulate(harga.begin(), harga.end(), 1,
                                       [](int a, int b) { return a * (b / 1000); });
    std::cout << "produk kasar " << produk << '\n';

    std::vector<std::string> kata{"Belajar", "C++"};
    const std::string gabung = std::accumulate(
        std::next(kata.begin()), kata.end(), kata.front(),
        [](std::string a, const std::string& b) {
            return std::move(a) + ' ' + b;
        });
    std::cout << gabung << '\n';
    return 0;
}
```

**Yang terjadi:** total `32000`. Produk kasar dari `10*15*7` = `1050`. String `Belajar C++`. Nilai awal (`0`, `1`, `kata.front()`) menentukan tipe akumulator — `accumulate` pada `vector<double>` dengan `0` (`int`) bisa memotong; pakai `0.0`.

C++17 `std::reduce` bisa paralel, urutan tidak terjamin. Untuk jumlah uang/statistik berurutan, `accumulate` lebih prediktabel.

**Biasanya digabungkan dengan:** `vector<int>`, laporan, `inner_product`.

**Jangan:** `accumulate(..., 0)` pada `long long` besar — overflow `int`. Jangan akumulator `string` tanpa `move` di loop besar (banyak copy).

## std::copy dan back_inserter

**Tipe:** fungsi template + iterator adaptor (`<iterator>`)

**Untuk apa:** menyalin rentang; `back_inserter` memanggil `push_back` sehingga tujuan bisa tumbuh.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> sumber{1, 2, 3, 4};
    std::vector<int> tujuan;
    tujuan.reserve(sumber.size());

    std::copy(sumber.begin(), sumber.end(), std::back_inserter(tujuan));

    std::vector<int> genap;
    std::copy_if(sumber.begin(), sumber.end(), std::back_inserter(genap),
                 [](int n) { return n % 2 == 0; });

    for (int n : genap) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** `tujuan` menjadi salinan penuh. `genap` = `2 4`. Tanpa `back_inserter`, `copy` ke `tujuan.begin()` pada vector kosong adalah bug (tulis ke memori liar).

**Biasanya digabungkan dengan:** `copy_if`, `transform` + inserter, `reserve`.

**Jangan:** `copy` ke `begin()` kontainer kosong. Jangan lupa `reserve` jika jumlah besar.

## std::fill dan generate

**Tipe:** fungsi template

**Untuk apa:** `fill` mengisi nilai sama; `generate` mengisi dari fungsi (counter, random).

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a(5);
    std::fill(a.begin(), a.end(), 7);

    int n = 0;
    std::vector<int> b(5);
    std::generate(b.begin(), b.end(), [&n] { return n += 2; });

    for (int x : a) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    for (int x : b) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** `7 7 7 7 7` dan `2 4 6 8 10`. `fill_n(begin, count, value)` mengisi terhitung. `iota` (bawah) lebih jelas untuk 0,1,2,...

**Biasanya digabungkan dengan:** inisialisasi buffer, tes.

**Jangan:** `fill` pointer null. Jangan `generate` dengan state thread-unsafe jika paralel.

## std::reverse

**Tipe:** fungsi template

**Untuk apa:** membalik urutan di tempat.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string s = "kasur";
    std::reverse(s.begin(), s.end());
    std::cout << s << '\n';
    return 0;
}
```

**Yang terjadi:** `rusak`. Bekerja pada `vector`, `array`, `string`, `deque`. Pada `list` juga (bidirectional).

**Biasanya digabungkan dengan:** palindrome cek (`s == reversed` lebih baik salin dulu), undo urutan.

**Jangan:** `reverse` sebagian rentang tanpa sadar (`reverse(begin+1, end-1)`). Jangan mengira `string` UTF-8 multibyte aman dibalik per byte.

## std::unique dan erase

**Tipe:** fungsi template + member `erase`

**Untuk apa:** merapatkan **duplikat berurutan**. Harus `sort` dulu jika ingin unik global.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{3, 1, 1, 2, 3, 3};
    std::sort(v.begin(), v.end());                // 1,1,2,3,3,3
    auto baruAkhir = std::unique(v.begin(), v.end());
    v.erase(baruAkhir, v.end());

    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** setelah sort+unique+erase: `1 2 3`. `unique` **tidak** mengecilkan `size`; ia menggeser unik ke depan dan mengembalikan iterator “sampah mulai di sini”. Tanpa `erase`, size lama tetap, ekor sampah.

**Biasanya digabungkan dengan:** `sort`, `vector` sebagai set sederhana.

**Jangan:** `unique` tanpa sort jika duplikat tidak bersebelahan. Jangan lupa `erase`.

## remove_if erase idiom

**Tipe:** pola (`erase` + `std::remove_if`)

**Untuk apa:** menghapus semua elemen yang lolos predikat pada `vector`/`string` secara efisien.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 8, 3, 8, 5, 8};
    v.erase(std::remove(v.begin(), v.end(), 8), v.end());

    std::vector<int> w{10, 55, 70, 40, 90};
    w.erase(std::remove_if(w.begin(), w.end(), [](int n) { return n < 60; }),
            w.end());

    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    for (int n : w) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** `v` menjadi `1 3 5`. `w` menyisakan `70 90`. `remove` menggeser yang dipertahankan ke depan; `erase` memotong ekor. C++20: `std::erase(v, 8)` dan `std::erase_if(w, pred)`.

Pada `list`, ada `remove_if` member yang lebih cocok.

**Biasanya digabungkan dengan:** filter stok, hapus `nullptr` dari `vector<T*>`.

**Jangan:** `remove_if` tanpa `erase`. Jangan memakai idiom ini pada `map` (pakai iterate+erase). Jangan `remove` pada `vector<bool>`.

## std::min_element dan max_element

**Tipe:** fungsi template

**Untuk apa:** iterator ke elemen terkecil / terbesar.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{14, 3, 27, 9};
    auto mn = std::min_element(v.begin(), v.end());
    auto mx = std::max_element(v.begin(), v.end());
    std::cout << *mn << ' ' << *mx << '\n';

    auto [lo, hi] = std::minmax_element(v.begin(), v.end());
    std::cout << *lo << '..' << *hi << '\n';
    return 0;
}
```

**Yang terjadi:** `3 27` dan `3..27`. Pada rentang kosong, hasil `end()` — jangan di-`*`.

**Biasanya digabungkan dengan:** laporan, `distance` untuk indeks (`mn - v.begin()`).

**Jangan:** dereference jika `v.empty()`. Jangan banding custom tanpa `const` predikat yang ketat.

## std::all_of any_of none_of

**Tipe:** fungsi template

**Untuk apa:** pertanyaan Boolean pada seluruh rentang.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nilai{70, 80, 90};
    const bool semuaLulus = std::all_of(nilai.begin(), nilai.end(), [](int n) {
        return n >= 70;
    });
    const bool adaSeratus = std::any_of(nilai.begin(), nilai.end(), [](int n) {
        return n == 100;
    });
    const bool takAdaGagal = std::none_of(nilai.begin(), nilai.end(), [](int n) {
        return n < 70;
    });
    std::cout << semuaLulus << ' ' << adaSeratus << ' ' << takAdaGagal << '\n';
    return 0;
}
```

**Yang terjadi:** `1 0 1` (true, false, true). Pada rentang **kosong**, `all_of` dan `none_of` true, `any_of` false (logika predikat kosong).

**Biasanya digabungkan dengan:** validasi, early exit (algoritma berhenti saat jawaban sudah pasti).

**Jangan:** mengabaikan perilaku rentang kosong. Jangan predikat yang melempar.

## std::for_each

**Tipe:** fungsi template

**Untuk apa:** menjalankan fungsi pada tiap elemen. Range-for biasanya lebih jelas; `for_each` berguna jika functor punya state.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    int jumlah = 0;
    std::for_each(v.begin(), v.end(), [&](int n) { jumlah += n; });
    std::cout << jumlah << '\n';
    return 0;
}
```

**Yang terjadi:** `6`. C++20 ranges: `std::ranges::for_each`. Sehari-hari `for (int n : v) jumlah += n` atau `accumulate` lebih jujur.

**Biasanya digabungkan dengan:** functor stateful, paralel `std::for_each(std::execution::par, ...)` (C++17, hati-hati data race).

**Jangan:** `for_each` hanya karena terlihat “lebih STL”. Jangan execution par tanpa mutex pada capture.

## std::binary_search

**Tipe:** fungsi template

**Untuk apa:** cek keberadaan pada **rentang sudah terurut**, `O(log n)`.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end());
    std::cout << std::boolalpha;
    std::cout << std::binary_search(v.begin(), v.end(), 4) << '\n';
    std::cout << std::binary_search(v.begin(), v.end(), 2) << '\n';
    return 0;
}
```

**Yang terjadi:** `true` lalu `false`. Jika tidak di-sort, hasil **salah diam-diam**, bukan crash. Untuk posisi, pakai `lower_bound`.

**Biasanya digabungkan dengan:** `sort` sekali, banyak query.

**Jangan:** `binary_search` pada data tak terurut. Jangan comparator beda dengan yang dipakai `sort`.

## std::lower_bound pada vector

**Tipe:** fungsi template

**Untuk apa:** iterator ke elemen pertama yang tidak lebih kecil dari nilai; titik sisip agar tetap terurut.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 3, 5, 7};
    auto it = std::lower_bound(v.begin(), v.end(), 4);
    v.insert(it, 4);
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    std::cout << "indeks 5 = " << (std::lower_bound(v.begin(), v.end(), 5) - v.begin())
              << '\n';
    return 0;
}
```

**Yang terjadi:** sisip `4` di antara 3 dan 5 → `1 3 4 5 7`. Indeks `5` adalah 3. `upper_bound` menunjuk lewat elemen yang sama (setelah 5 jika ada duplikat).

**Biasanya digabungkan dengan:** vector terurut sebagai alternatif `set` jika sisip jarang.

**Jangan:** `lower_bound` tanpa urutan. Jangan `insert` di loop besar (jadi `O(n^2)`).

## std::iota

**Tipe:** fungsi template (`<numeric>`)

**Untuk apa:** mengisi 0,1,2,... atau nilai awal lalu +1 berulang.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> idx(5);
    std::iota(idx.begin(), idx.end(), 0);
    for (int n : idx) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

**Yang terjadi:** `0 1 2 3 4`. Berguna membuat indeks untuk `sort` tidak langsung (urut indeks menurut array lain).

**Biasanya digabungkan dengan:** permute, generate id lokal.

**Jangan:** `iota` pada tipe tanpa `++`. 

## std::next prev distance

**Tipe:** fungsi template (`<iterator>`)

**Untuk apa:** maju/mundur N langkah tanpa `+` (bekerja pada iterator non-random, meski `O(n)`); hitung jarak.

**Contoh implementasi:**

```cpp
#include <iostream>
#include <iterator>
#include <list>

int main() {
    std::list<int> l{10, 20, 30, 40};
    auto it = std::next(l.begin(), 2);
    std::cout << *it << '\n';
    std::cout << *std::prev(it) << '\n';
    std::cout << "jarak dari begin: " << std::distance(l.begin(), it) << '\n';
    return 0;
}
```

**Yang terjadi:** `30`, lalu `20`, jarak `2`. `std::advance(it, n)` mengubah `it` di tempat; `next` mengembalikan salinan.

**Biasanya digabungkan dengan:** `list`, `map` iterator, algoritma yang butuh “elemen + 1”.

**Jangan:** `prev(begin)`. Jangan `distance` besar pada `list` di Tick Unreal.

## lambda sebagai predikat

**Tipe:** ekspresi fungsi anonim

**Untuk apa:** menulis syarat/algoritma di tempat, menangkap variabel lokal.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const int ambang = 70;
    std::vector<int> v{50, 80, 60, 90};

    const auto n = std::count_if(v.begin(), v.end(), [ambang](int x) {
        return x >= ambang;
    });
    std::cout << n << '\n';
    return 0;
}
```

**Yang terjadi:** `2`. `[ambang]` capture by value. `[&]` semua by ref; `[=]` semua by value. `[this]` di method class.

Di Unreal, lambda sering di `BindAction` Enhanced Input (file 09) — hati-hati capture `this` vs `TWeakObjectPtr`.

**Biasanya digabungkan dengan:** `find_if`, `sort`, `remove_if`, `transform`.

**Jangan:** `[&]` lalu menyimpan lambda lebih lama dari variabel. Jangan capture `this` di Unreal tanpa rencanakan actor hancur.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menghindari rentang salah dan “algoritma diam-diam salah”.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{4, 1, 3};
    // salah: binary_search tanpa sort
    std::cout << "tanpa sort (bisa salah): "
              << std::binary_search(v.begin(), v.end(), 1) << '\n';

    std::sort(v.begin(), v.end());
    std::cout << "dengan sort: " << std::binary_search(v.begin(), v.end(), 1) << '\n';

    std::vector<int> kosong;
    auto it = std::max_element(kosong.begin(), kosong.end());
    std::cout << (it == kosong.end() ? "kosong aman\n" : "?\n");
    return 0;
}
```

**Yang terjadi:** hasil tanpa sort tidak diandalkan. Setelah sort, `1` ketemu. `max_element` pada kosong = `end`.

**Biasanya digabungkan dengan:** semua algoritma di atas.

**Jangan:** rentang `[end, begin)`; sort sebagian lalu binary_search seluruh; `unique` tanpa erase; copy ke vector kosong tanpa inserter.
