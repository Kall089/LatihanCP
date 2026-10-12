# Merge sort dan inversi

[← README](README.md) · [Indeks CP](../README.md)

Pecah rentang jadi dua antrian, urutkan masing-masing, lalu sisir dari depan. Itu merge sort. Alasan file ini ada di folder searching: saat dua antrian digabung, kamu bisa **menghitung inversi** tanpa loop `O(n^2)`.

Day ComprogLearning terkait: **044**. Latihan tetap di folder latihan, bukan di sini.

Semua indeks **0-based**. Rentang divide-and-conquer memakai `[l, r)` kecuali disebut lain. Jumlah inversi selalu `ll`.

## Daftar isi

- [Cara baca](#cara-baca)
- [Merge sort](#merge-sort)
- [Konvensi setengah terbuka](#konvensi-setengah-terbuka)
- [Kestabilan merge](#kestabilan-merge)
- [Menghitung inversi](#menghitung-inversi)
- [Inversi dan tukar berdampingan](#inversi-dan-tukar-berdampingan)
- [Varian ambang dua kali](#varian-ambang-dua-kali)
- [Stress test naif](#stress-test-naif)
- [Peta keputusan](#peta-keputusan)

## Cara baca

Tiap teknik memakai enam blok tetap.

1. **Teori** — analogi plus alasan langkahnya sah.
2. **Kapan** — dipakai atau tidak.
3. **Proses** — jejak angka kecil yang bisa dihitung di kertas.
4. **Kode** — fungsi terpisah, `main` hanya menguji.
5. **Jebakan** — kesalahan yang sering WA, RTE, atau TLE.
6. **Kompleksitas** — waktu dan memori.

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o tes tes.cpp && ./tes
```

Di macOS, `bits/stdc++.h` kadang tidak ada di `clang++`. Pakai `g++` Homebrew.

---

## Merge sort

**Teori:** Analoginya dua barisan siswa yang sudah urut tinggi. Guru selalu mengambil yang lebih pendek di depan kedua barisan, lalu menaruhnya ke barisan baru. Pecah `[l, r)` menjadi `[l, mid)` dan `[mid, r)`, urutkan rekursif, gabungkan ke `tmp`, salin balik. Alasan benar: setiap elemen pindah `O(log n)` level, tiap level mengerjakan `O(n)` perbandingan dan salinan. Basisnya `r - l <= 1`: satu elemen atau kosong sudah urut.

**Kapan:** kamu butuh pengurutan **stabil**, atau kamu menumpang hitung inversi / pasangan lintas belahan. Jangan menulis merge sort di kontes hanya untuk mengurut. `std::sort` lebih pendek, sering lebih cepat, dan sudah diuji. Jangan alokasi `tmp` di setiap panggilan rekursif.

**Proses:** `a = [3, 1, 4, 2]`, range `[0, 4)`.

1. `mid = 2`. Kiri `[3, 1]`, kanan `[4, 2]`.
2. Kiri pecah jadi `[3]` dan `[1]`, lalu gabung menjadi `[1, 3]`.
3. Kanan pecah jadi `[4]` dan `[2]`, lalu gabung menjadi `[2, 4]`.
4. Merge akhir: `1` lawan `2` ambil `1`; `3` lawan `2` ambil `2`; `3` lawan `4` ambil `3`; sisa `4`.
5. Hasil `[1, 2, 3, 4]`. `tmp` diisi kiri ke kanan, lalu disalin ke `a[0..4)`.

Pohon panggilan:

```text
[3,1,4,2]
   [3,1]          [4,2]
  [3] [1]        [4] [2]
   [1,3]          [2,4]
      [1,2,3,4]
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void mergeRange(vector<ll>& a, vector<ll>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++]; // <= membuat stabil
        else tmp[k++] = a[j++];
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
}

void mergeSort(vector<ll>& a, vector<ll>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;
    mergeSort(a, tmp, l, mid);
    mergeSort(a, tmp, mid, r);
    mergeRange(a, tmp, l, mid, r);
}

int main() {
    FASTIO;
    vector<ll> a = {3, 1, 4, 2};
    vector<ll> tmp(a.size());
    mergeSort(a, tmp, 0, (int)a.size());
    for (int i = 0; i < 4; i++) cout << a[i] << " \n"[i == 3];
    return 0;
}
```

Keluaran: `1 2 3 4`.

**Jebakan:**
1. `(l + r) / 2` overflow pada indeks besar. Pakai `l + (r - l) / 2`.
2. `tmp` dibuat di dalam fungsi rekursif: memori dan waktu meledak.
3. Lupa menyalin sisa kiri atau kanan, sehingga elemen hilang.
4. Menyalin `tmp` penuh `0..n` padahal hanya `[l, r)` yang valid.

**Kompleksitas:** waktu `O(n log n)`, memori `O(n)` untuk `tmp` plus `O(log n)` stack.

---

## Konvensi setengah terbuka

**Teori:** Range `[l, r)` berarti indeks `l, l+1, ..., r-1`. Panjangnya `r - l`. Titik tengah `mid` adalah awal belahan kanan, bukan elemen “tengah mistis”. Analoginya potong roti: pisau di `mid` tidak merobek elemen, hanya memisahkan dua tumpukan. Alasan benar: basis `r - l <= 1` menutup kosong dan tunggal tanpa cabang khusus `l == r` versus `l + 1 == r`.

**Kapan:** setiap divide-and-conquer pada array: merge, inversi, D&C DP nanti di folder 09. Jangan campur `[l, r]` inklusif di satu fungsi dan `[l, r)` di fungsi lain. Jangan memakai `r` sebagai indeks terakhir lalu tetap menulis `j < r` seolah `r` eksklusif.

**Proses:** array panjang 5, indeks `0..4`, panggilan `mergeSort(a, tmp, 0, 5)`.

1. `mid = 0 + 5/2 = 2`. Kiri `[0, 2)` = dua elemen. Kanan `[2, 5)` = tiga elemen.
2. Belahan tidak wajib sama panjang. Itu sah.
3. Basis kiri: `[0, 1)` dan `[1, 2)` masing-masing satu elemen.
4. Jika kamu memakai inklusif `[0, 4]`, mid mudah off-by-one saat `l == r` atau `l + 1 == r`.
5. Cek panjang: `5 = 2 + 3`. Tidak ada elemen yang masuk dua belahan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int panjang(int l, int r) { return r - l; }

int midEksklusif(int l, int r) { return l + (r - l) / 2; }

bool basisSatuAtauKosong(int l, int r) { return r - l <= 1; }

int main() {
    FASTIO;
    cout << panjang(0, 5) << '\n';                 // 5
    cout << midEksklusif(0, 5) << '\n';            // 2
    cout << basisSatuAtauKosong(2, 3) << '\n';     // 1
    cout << basisSatuAtauKosong(4, 4) << '\n';     // 1
    cout << basisSatuAtauKosong(0, 2) << '\n';     // 0
    return 0;
}
```

**Jebakan:**
1. Memanggil `mergeSort(..., 0, n-1)` lalu memakai loop `i < r` — elemen terakhir tidak diurut.
2. `mid = (l + r + 1) / 2` tanpa alasan, belahan jadi timpang terbalik dan mudah loop.
3. Mengakses `a[r]` padahal `r` eksklusif.

**Kompleksitas:** aritmetika indeks `O(1)`.

---

## Kestabilan merge

**Teori:** Pengurutan **stabil** menjaga urutan relatif elemen yang kuncinya sama. Saat merge, jika `a[i] == a[j]`, ambil dari kiri dulu (`<=`). Analoginya dua tumpukan kartu bernomor sama: kartu dari tumpukan kiri masuk lebih dulu karena ia sudah “lebih tua” di array asli. `std::stable_sort` juga stabil; `std::sort` tidak dijamin.

**Kapan:** kamu menyimpan pasangan `(kunci, indeks_asli)` dan butuh yang indeksnya lebih kecil menang saat kunci sama. Jangan mengandalkan `std::sort` untuk itu. Jangan memakai `<` di merge jika soal meminta stabil.

**Proses:** pasangan `(nilai, nama)`: `(3, A), (1, B), (3, C), (1, D)`.

1. Kunci adalah nilai. A muncul sebelum C, B sebelum D.
2. Setelah merge sort stabil: `(1, B), (1, D), (3, A), (3, C)`.
3. Jika merge memakai `<` lalu mengambil kanan saat sama, A dan C bisa terbalik.
4. Untuk inversi ketat `a[i] > a[j]`, pasangan sama **bukan** inversi. `<=` sudah sesuai definisi itu.
5. Cek: dua nilai `3` tetap A lalu C.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Item {
    ll kunci;
    int idx;
};

void mergeItem(vector<Item>& a, vector<Item>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i].kunci <= a[j].kunci) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
}

void sortItem(vector<Item>& a, vector<Item>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;
    sortItem(a, tmp, l, mid);
    sortItem(a, tmp, mid, r);
    mergeItem(a, tmp, l, mid, r);
}

int main() {
    FASTIO;
    vector<Item> a = {{3, 0}, {1, 1}, {3, 2}, {1, 3}};
    vector<Item> tmp(a.size());
    sortItem(a, tmp, 0, (int)a.size());
    for (auto x : a) cout << x.kunci << ':' << x.idx << ' ';
    cout << '\n'; // 1:1 1:3 3:0 3:2
    return 0;
}
```

**Jebakan:**
1. Membandingkan hanya `kunci` dengan `<`, lalu mengira urutan indeks otomatis terjaga.
2. Menyimpan nama di `string` lalu membandingkan nama, bukan indeks.
3. Mencampur `stable_sort` di satu tes dan `sort` di tes lain lalu heran hasilnya beda.

**Kompleksitas:** sama dengan merge sort: `O(n log n)` waktu, `O(n)` memori.

---

## Menghitung inversi

**Teori:** Inversi adalah pasangan indeks `i < j` dengan `a[i] > a[j]`. Analoginya: saat guru mengambil siswa dari barisan kanan, semua yang masih antre di kiri lebih tinggi dan berdiri **sebelum** dia. Masing-masing satu inversi. Saat merge, jika `a[j] < a[i]`, seluruh sisa kiri `a[i..mid)` lebih besar dari `a[j]`, jumlahnya `mid - i`. Alasan benar: pasangan dalam satu belahan sudah dihitung rekursif; pasangan lintas belahan dihitung tepat sekali saat mereka bertemu di merge.

**Kapan:** SPOJ INVCNT, “berapa swap berdampingan minimum”, menghitung ketidakteraturan. Jangan `O(n^2)` pada `n = 1e5`. Jangan menulis `inv += 1` saat mengambil dari kanan.

**Proses:** `a = [3, 1, 2]`. Tiga pasangan: `(3,1)` ya, `(3,2)` ya, `(1,2)` tidak. Jawaban `2`.

1. Kiri `[3]`, kanan `[1, 2]` sudah urut.
2. Merge: `3` lawan `1`, ambil `1`, `inv += 1 - 0 = 1` (sisa kiri hanya `3`).
3. `3` lawan `2`, ambil `2`, `inv += 1`. Total `2`.
4. Ambil sisa `3`. Array jadi `[1, 2, 3]`.
5. Cek manual: dua inversi, cocok.

Contoh lebih panjang `a = [4, 3, 1, 2]`:

```text
pasangan: (4,3) (4,1) (4,2) (3,1) (3,2)  → 5 inversi
(1,2) bukan inversi
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll mergeHitung(vector<ll>& a, vector<ll>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;
    ll inv = 0;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            inv += mid - i; // semua sisa kiri > a[j-1]
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
    return inv;
}

ll inversi(vector<ll>& a, vector<ll>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    return inversi(a, tmp, l, mid) + inversi(a, tmp, mid, r)
         + mergeHitung(a, tmp, l, mid, r);
}

int main() {
    FASTIO;
    vector<ll> a = {3, 1, 2};
    vector<ll> tmp(a.size());
    cout << inversi(a, tmp, 0, 3) << '\n'; // 2
    vector<ll> b = {4, 3, 1, 2};
    vector<ll> tmp2(b.size());
    cout << inversi(b, tmp2, 0, 4) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. `inv += 1` alih-alih `mid - i`.
2. `int` untuk inversi: `n = 1e5` terurut terbalik menghasilkan sekitar `5e9`.
3. Predikat terbalik: mengambil kanan saat `a[i] < a[j]`.
4. Memakai array yang sudah terurut di panggilan kedua tanpa menyalin ulang.

**Kompleksitas:** waktu `O(n log n)`, memori `O(n)`.

---

## Inversi dan tukar berdampingan

**Teori:** Satu tukar elemen berdampingan menghilangkan atau menambah **tepat satu** inversi. Jadi jumlah inversi = jumlah tukar berdampingan minimum untuk mengurutkan naik. Analoginya bubble sort: setiap kali dua tetangga salah urutan ditukar, satu inversi hilang. Alasan benar: pengurutan apa pun yang hanya menukar tetangga menghasilkan permutasi yang paritas inversinya berubah satu per tukar; jalur terpendek menghapus semua inversi tanpa membuat yang baru.

**Kapan:** soal “minimum adjacent swap”, “berapa langkah bubble sort”. Jangan menyamakan dengan tukar sebarang dua indeks: itu bisa menghapus banyak inversi sekaligus. Jangan mengira array dengan duplikat butuh rumus lain: pasangan sama bukan inversi, dan `<=` saat merge sudah benar.

**Proses:** `[3, 1, 2]` butuh dua tukar tetangga.

1. `3,1,2` → tukar `(3,1)` jadi `1,3,2`.
2. `1,3,2` → tukar `(3,2)` jadi `1,2,3`.
3. Selesai dalam 2 langkah, sama dengan 2 inversi.
4. `[4, 3, 1, 2]` tidak bisa selesai dalam 4 tukar tetangga jika kamu menghitung 5 inversi.
5. Permutasi identitas: 0 inversi, 0 tukar.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll bubbleHitung(vector<ll> a) {
    int n = (int)a.size();
    ll tukar = 0;
    bool gerak = true;
    while (gerak) {
        gerak = false;
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                tukar++;
                gerak = true;
            }
        }
    }
    return tukar;
}

int main() {
    FASTIO;
    cout << bubbleHitung({3, 1, 2}) << '\n';       // 2
    cout << bubbleHitung({4, 3, 1, 2}) << '\n';    // 5
    cout << bubbleHitung({1, 2, 3}) << '\n';       // 0
    return 0;
}
```

Bubble `O(n^2)` hanya untuk n kecil. Di kontes, kirim penghitung inversi merge.

**Jebakan:**
1. Menghitung swap `std::swap` sebarang pasangan sebagai “satu inversi”.
2. Memakai bubble di `n = 1e5`.
3. Duplikat: ` [2, 2, 1] ` punya 2 inversi, bukan 1.

**Kompleksitas:** bubble `O(n^2)` waktu, `O(1)` memori tambahan. Definisi matematika sama dengan merge `O(n log n)`.

---

## Varian ambang dua kali

**Teori:** Kadang yang dihitung bukan `a[i] > a[j]`, melainkan `a[i] > 2 * a[j]` atau `a[i] >= a[j] + k`. Satu fase merge **tidak** boleh mencampur hitung dan gabung jika predikatnya bukan perbandingan yang sama dengan urutan merge. Analoginya: kamu menghitung siswa yang tingginya lebih dari dua kali siswa kanan, lalu barulah merapikan barisan menurut tinggi biasa. Alasan benar: setelah kedua belahan terurut, dua pointer bisa menghitung predikat monoton tanpa merusak urutan merge.

**Kapan:** “important reverse pairs”, pasangan `i < j` dan `a[i] > 2 * a[j]`. Jangan menambah `inv` di cabang `else` merge biasa: itu menghitung inversi standar, bukan ambang dua kali.

**Proses:** `a = [1, 3, 2, 3, 1]`. Pasangan indeks `i < j` dengan `a[i] > 2 * a[j]`.

1. `(3, 1)` di posisi nilai: ada dua angka `3` di kiri sebuah `1` akhir. Itu dua pasangan.
2. Jejak D&C: belah `[1,3,2]` dan `[3,1]`.
3. Di kanan, `3` dan `1` memenuhi `3 > 2`. Tambah 1.
4. Lintas belahan: setelah kedua sisi terurut `[1,2,3]` dan `[1,3]`, geser pointer `j` untuk tiap `i`.
5. Total 2, sesuai enumerasi naif.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll hitungAmbang(vector<ll>& a, int l, int mid, int r) {
    ll inv = 0;
    int j = mid;
    for (int i = l; i < mid; i++) {
        while (j < r && a[i] > 2LL * a[j]) j++;
        inv += j - mid;
    }
    return inv;
}

void mergeBiasa(vector<ll>& a, vector<ll>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
}

ll reversePairs(vector<ll>& a, vector<ll>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    ll ans = reversePairs(a, tmp, l, mid) + reversePairs(a, tmp, mid, r);
    ans += hitungAmbang(a, l, mid, r);
    mergeBiasa(a, tmp, l, mid, r);
    return ans;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 3, 2, 3, 1};
    vector<ll> tmp(a.size());
    cout << reversePairs(a, tmp, 0, (int)a.size()) << '\n'; // 2
    return 0;
}
```

Hitung dulu, baru merge. Kalau digabung dalam satu loop yang sama, pointer `j` untuk ambang dan pointer merge saling merusak.

**Jebakan:**
1. `2 * a[j]` overflow `int`. Pakai `2LL * a[j]`.
2. Menghitung dan menggabungkan dalam satu `while` yang sama.
3. Syarat `>=` versus `>` tertukar.

**Kompleksitas:** waktu `O(n log n)`, memori `O(n)`.

---

## Stress test naif

**Teori:** Penghitung inversi mudah salah satu indeks. Cara paling murah: tulis versi `O(n^2)` yang jelas, lalu bandingkan pada array acak kecil. Analoginya mencicipi kuah: satu sendok berbeda cukup untuk tidak menyajikan panci. Alasan benar: untuk `n <= 200` naif pasti selesai, dan setiap pasangan dihitung apa adanya.

**Kapan:** sebelum submit, atau saat WA pada tes tersembunyi. Jangan mengirim naif ke `n = 1e5`. Jangan memakai generator yang hanya membuat array sudah urut.

**Proses:** bandingkan `[5, 2, 4, 1]` secara manual.

1. Pasangan: `(5,2) (5,4) (5,1) (2,1) (4,1)` = 5. `(2,4)` bukan.
2. Naif harus 5. Merge harus 5.
3. Array terurut `[1, 2, 3]` keduanya 0.
4. Array terbalik `[3, 2, 1]` keduanya 3.
5. Duplikat `[2, 2, 2]` keduanya 0.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll inversiNaif(const vector<ll>& a) {
    ll inv = 0;
    int n = (int)a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) inv++;
    return inv;
}

ll mergeHitung(vector<ll>& a, vector<ll>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;
    ll inv = 0;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            inv += mid - i;
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
    return inv;
}

ll inversi(vector<ll>& a, vector<ll>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    return inversi(a, tmp, l, mid) + inversi(a, tmp, mid, r)
         + mergeHitung(a, tmp, l, mid, r);
}

int main() {
    FASTIO;
    mt19937 rng(42);
    for (int tes = 0; tes < 20; tes++) {
        int n = 1 + (rng() % 8);
        vector<ll> a(n);
        for (int i = 0; i < n; i++) a[i] = (ll)(rng() % 7);
        vector<ll> b = a, tmp(n);
        ll x = inversiNaif(a);
        ll y = inversi(b, tmp, 0, n);
        if (x != y) {
            cout << "beda\n";
            return 0;
        }
    }
    cout << "lolos 20 tes\n";
    return 0;
}
```

**Jebakan:**
1. Generator selalu `n = 0`.
2. Membandingkan setelah kedua fungsi memodifikasi array yang sama.
3. Naif memakai `>=` sehingga duplikat dihitung.

**Kompleksitas:** naif `O(n^2)`, stress 20 tes `n <= 8` instan.

---

## Peta keputusan

```text
Butuh urut saja?
  → std::sort, bukan merge tulis tangan

Butuh stabil?
  → std::stable_sort atau merge dengan <=

Hitung i < j dan a[i] > a[j]?
  → inversi saat merge, inv += mid - i

Hitung a[i] > f(a[j]) monoton?
  → hitung dua pointer dulu, baru merge

n kecil dan ragu?
  → naif O(n^2) sebagai oracle
```

| n | naif | merge |
| ---: | ---: | --- |
| 20 | aman | aman |
| 2000 | masih hidup | aman |
| 1e5 | TLE | wajib |
| 1e6 | mustahil | ketat, jaga konstanta |

Ringkasan: `tmp` di luar rekursi, range `[l, r)`, inversi bertipe `ll`, hitung ambang terpisah dari merge.

Lanjut ke [binary-search.md](binary-search.md) jika predikatnya monoton, atau kembali ke [README folder](README.md).
