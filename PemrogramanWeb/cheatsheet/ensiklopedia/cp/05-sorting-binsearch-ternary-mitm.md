# 05 — Sorting, binary search, ternary, interaktif, MITM

[← Kadane dan mono](04-kadane-mono-stack-deque-compress.md) · [README dasar](README-dasar.md)

> **Ide satu kalimat:** pecah lalu gabung untuk mengurut dan menghitung inversi; potong ruang jika predikatnya monoton; belah 2^n menjadi dua kali 2^{n/2}.

Day ComprogLearning: **044** merge sort & inversi, **048** binary search & on answer, **050** ternary & unimodal, **052** soal interaktif, **054** meet in the middle.

Semua 0-based. Range D&C memakai `[l, r)` kecuali disebut. Fungsi modular. `ll` untuk inversi dan jumlah.

## Daftar isi

- [Merge sort](#merge-sort)
- [Menghitung inversi](#menghitung-inversi)
- [Binary search nilai pasti](#binary-search-nilai-pasti)
- [Lower bound manual](#lower-bound-manual)
- [Upper bound manual](#upper-bound-manual)
- [Kemunculan pertama dan terakhir](#kemunculan-pertama-dan-terakhir)
- [Binary search on answer](#binary-search-on-answer)
- [Binary search bilangan real](#binary-search-bilangan-real)
- [Soal interaktif dan flush](#soal-interaktif-dan-flush)
- [Ternary search real](#ternary-search-real)
- [Ternary search integer](#ternary-search-integer)
- [Binary search pada selisih](#binary-search-pada-selisih)
- [Meet in the middle](#meet-in-the-middle)
- [MITM knapsack dan prefix maksimum](#mitm-knapsack-dan-prefix-maksimum)
- [4-SUM sebagai MITM](#4-sum-sebagai-mitm)

---

## Merge sort

> **Ide satu kalimat:** pecah jadi dua antrian yang sudah rapi, lalu sisir dari depan seperti menggabungkan dua tumpukan kartu.

### Merge sort

**Teori:** Analoginya dua barisan siswa yang sudah urut tinggi, digabung oleh guru yang selalu mengambil yang lebih pendek di depan. Pecah `[l, r)` jadi `[l, mid)` dan `[mid, r)`, urutkan rekursif, gabungkan ke `tmp`. Alasan benar: setiap elemen pindah O(log n) level, tiap level O(n) kerja. Konvensi setengah terbuka menghapus off-by-one: basis `r-l <= 1`. `<=` saat merge membuatnya **stabil**; `<` menukar kembar.

**Kapan dipakai / kapan tidak.** Pakai jika kamu butuh stabil, atau menumpang hitung inversi. Jangan menulis merge sort di kontes hanya untuk mengurut — `std::sort` lebih pendek dan cepat. Jangan alokasi `tmp` di setiap rekursi (O(n log n) memori dan lambat).

**Proses:** `a = [3, 1, 4, 2]`, range `[0, 4)`.

1. Mid=2. Kiri `[3,1]` → pecah jadi `[3]` dan `[1]` → gabung `[1,3]`.
2. Kanan `[4,2]` → gabung `[2,4]`.
3. Merge: 1 vs 2 ambil 1; 3 vs 2 ambil 2; 3 vs 4 ambil 3; sisa 4.
4. Hasil `[1,2,3,4]`.
5. `tmp` diisi kiri-ke-kanan, lalu disalin balik ke `a[l..r)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void mergeRange(vector<ll>& a, vector<ll>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++]; // <= = stabil
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
    vector<ll> a = {3, 1, 4, 2};
    vector<ll> tmp(a.size());
    mergeSort(a, tmp, 0, (int)a.size());
    for (int i = 0; i < 4; i++) cout << a[i] << " \n"[i == 3]; // 1 2 3 4
    return 0;
}
```

**Jebakan:**
1. `(l+r)/2` overflow pada indeks besar — pakai `l+(r-l)/2`.
2. `tmp` dibuat di dalam fungsi rekursif.
3. Lupa menyalin sisa kiri atau kanan.

**Kompleksitas:** waktu O(n log n), memori O(n) untuk `tmp` plus O(log n) stack.

---

## Menghitung inversi

> **Ide satu kalimat:** kamu menulis merge sort bukan untuk mengurutkan, tapi untuk satu baris `inv += mid − i`.

### Menghitung inversi

**Teori:** Analoginya: saat guru mengambil siswa dari barisan kanan, semua yang masih antre di kiri lebih tinggi dan berdiri **sebelum** dia — masing-masing satu inversi. Inversi = pasangan `i < j` dan `a[i] > a[j]`. Saat merge, `a[j] < a[i]` berarti semua `a[i..mid)` lebih besar dari `a[j]`, jumlahnya `mid-i`. Alasan benar: setiap pasangan lintas belahan dihitung tepat sekali, pasangan dalam belahan sudah dihitung rekursif. Inversi = jumlah tukar berdampingan minimum untuk mengurutkan.

**Kapan dipakai / kapan tidak.** Pakai SPOJ INVCNT, “berapa swap berdampingan”. Varian `a[i] > 2·a[j]` butuh dua fase (hitung dulu, baru merge). Jangan O(n²) pada n=1e5. Jangan `inv += 1`.

**Proses:** `a = [3, 1, 2]`. Tiga pasangan: (3,1), (3,2) inversi; (1,2) bukan. Jawaban 2.

1. Kiri `[3]`, kanan `[1,2]` sudah urut.
2. Merge: 3 vs 1, ambil 1, `inv += 1-0` = 1 (sisa kiri: 3).
3. 3 vs 2, ambil 2, `inv += 1`. Total 2.
4. Ambil sisa 3.
5. Cek manual: 2 inversi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

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

ll inversiNaif(const vector<ll>& a) {
    ll inv = 0;
    int n = (int)a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) inv++;
    return inv;
}

int main() {
    vector<ll> a = {3, 1, 2};
    vector<ll> tmp(a.size()), b = a;
    cout << inversi(a, tmp, 0, 3) << '\n'; // 2
    cout << inversiNaif(b) << '\n';        // 2
    return 0;
}
```

**Jebakan:**
1. `inv += 1` alih-alih `mid-i`.
2. `int` untuk inversi: n=1e5 → 5·10^9.
3. `a[i] < a[j]` terbalik saat mengambil dari kanan.

**Kompleksitas:** waktu O(n log n), memori O(n). Naif O(n²) untuk stress test n kecil.

---

## Binary search nilai pasti

> **Ide satu kalimat:** tiap langkah buang setengah rak yang sudah pasti tidak memuat target.

### Binary search nilai pasti

**Teori:** Analoginya kamus kertas: buka tengah, kalau kata target lebih “kecil” buang kanan. Syarat: array **naik**. Alasan O(log n): ruang `n, n/2, n/4, …` sampai 1. `mid = lo + (hi-lo)/2` menghindari overflow `lo+hi`. Loop `lo <= hi`, maju `lo=mid+1` atau `hi=mid-1` supaya tidak menggantung.

**Kapan dipakai / kapan tidak.** Pakai cari ada/tidak pada array urut. Jangan array acak. Jangan `while (lo < hi)` campur `hi=mid-1` tanpa cek — mudah infinite atau lewat.

**Proses:** `a = [1,3,4,7,9]`, target 7.

1. lo=0, hi=4, mid=2, a[2]=4 < 7 → lo=3.
2. lo=3, hi=4, mid=3, a[3]=7 ketemu indeks 3.
3. Target 2: mid=2 (4>2) hi=1; mid=0 (1<2) lo=1; mid=1 (3>2) hi=0; lo>hi gagal.
4. Tidak pernah akses di luar `[0,n)`.
5. 5 elemen, paling ±3 langkah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int binsearch(const vector<ll>& a, ll target) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    vector<ll> a = {1, 3, 4, 7, 9};
    cout << binsearch(a, 7) << '\n'; // 3
    cout << binsearch(a, 2) << '\n'; // -1
    return 0;
}
```

**Jebakan:**
1. `(lo+hi)/2` overflow.
2. `lo = mid` tanpa +1 saat `a[mid] < target` → loop.
3. Array belum sort.

**Kompleksitas:** waktu O(log n), memori O(1).

---

## Lower bound manual

> **Ide satu kalimat:** cari kursi paling kiri yang orangnya sudah ≥ target; ruangnya `[lo, hi]` dengan `hi` boleh `n`.

### Lower bound manual

**Teori:** Analoginya “orang pertama yang tingginya cukup”. Invariant: jawaban ada di `[lo, hi]`, awal `hi=n` (boleh tidak ada). Jika `a[mid] >= x`, jawaban di kiri termasuk mid (`hi=mid`). Jika `a[mid] < x`, mid bukan kandidat (`lo=mid+1`). Berhenti `lo==hi`. Alasan benar: tiap langkah membuang sisi yang mustahil, dan `>=` menjaga elemen sama paling kiri.

**Kapan dipakai / kapan tidak.** Pakai first ≥, insert position. Jangan `hi=n-1` jika jawaban bisa “setelah akhir”.

**Proses:** `a = [1,3,3,6,8]`, x=3.

1. lo=0, hi=5.
2. mid=2, a[2]=3 ≥3 → hi=2.
3. mid=1, a[1]=3 ≥3 → hi=1.
4. mid=0, a[0]=1 <3 → lo=1.
5. lo=hi=1. Itu kemunculan pertama 3.

x=4: berakhir di 3 (nilai 6). x=9: berakhir di 5.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int lowerBoundManual(const vector<ll>& a, ll x) {
    int lo = 0, hi = (int)a.size(); // [0, n]
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << lowerBoundManual(a, 3) << '\n'; // 1
    cout << lowerBoundManual(a, 4) << '\n'; // 3
    cout << lowerBoundManual(a, 9) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. `hi = n-1` kehilangan jawaban `n`.
2. `if (a[mid] > x)` — itu upper bound.
3. `while (lo <= hi)` + `hi=mid` infinite saat lo=hi=mid.

**Kompleksitas:** O(log n) waktu, O(1) memori.

---

## Upper bound manual

> **Ide satu kalimat:** kursi pertama yang orangnya **lebih** dari target.

### Upper bound manual

**Teori:** Sama seperti lower, predikatnya `a[mid] > x`. Selisih `upper-lower` = frekuensi x. Alasan benar: semua x menempel setelah sort; ujung kanan jendela adalah first > x.

**Kapan dipakai / kapan tidak.** Pakai last occurrence (`upper-1` jika ada), hitung `<= x`. Jangan `*--it` tanpa cek `it==begin` di versi iterator.

**Proses:** `a = [1,3,3,6,8]`, x=3.

1. lo=0, hi=5, mid=2, 3>3? tidak → lo=3.
2. mid=4, 8>3 → hi=4.
3. mid=3, 6>3 → hi=3.
4. lo=hi=3. First > 3.
5. Frekuensi 3 = 3-1 = 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int upperBoundManual(const vector<ll>& a, ll x) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << upperBoundManual(a, 3) << '\n'; // 3
    cout << upperBoundManual(a, 8) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. Tertukar `>=` dan `>`.
2. Last = `upper-1` saat `upper==0`.
3. Banding `double` tanpa hati-hati (lebih aman di seksi real).

**Kompleksitas:** O(log n) waktu, O(1) memori.

---

## Kemunculan pertama dan terakhir

> **Ide satu kalimat:** dua bound, dua indeks; jika first > last, target tidak ada.

### Kemunculan pertama dan terakhir

**Teori:** Analoginya mencari halaman pertama dan terakhir bab yang sama. First = lower_bound, last = upper_bound − 1. Alasan benar: setelah sort, blok x kontigu. LC 34.

**Kapan dipakai / kapan tidak.** Pakai “posisi pertama/terakhir”. Jangan scan linear setelah `binary_search` yang hanya `bool`.

**Proses:** `a = [5,7,7,8,8,10]`, target 8.

1. lower=3, upper=5.
2. First 3, last 4.
3. Target 6: lower=1 (nilai 7), upper=1, tidak ada.
4. Target 10: first=last=5.
5. Target 4: lower=0, a[0]≠4.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

pair<int, int> firstLast(const vector<ll>& a, ll x) {
    int lo = (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
    int hi = (int)(upper_bound(a.begin(), a.end(), x) - a.begin());
    if (lo == hi) return {-1, -1};
    return {lo, hi - 1};
}

int main() {
    vector<ll> a = {5, 7, 7, 8, 8, 10};
    auto [f, l] = firstLast(a, 8);
    cout << f << ' ' << l << '\n'; // 3 4
    auto [f2, l2] = firstLast(a, 6);
    cout << f2 << ' ' << l2 << '\n'; // -1 -1
    return 0;
}
```

**Jebakan:**
1. Return `{lo, hi}` tanpa −1.
2. Array tidak urut.
3. `int` vs iterator.

**Kompleksitas:** O(log n) waktu, O(1) memori.

---

## Binary search on answer

> **Ide satu kalimat:** yang dicari bukan indeks, melainkan **angka jawaban**, asal predikat “apakah X cukup?” monoton.

### Binary search on answer

**Teori:** Analoginya mengatur thermostat: jika suhu X sudah membuat kue matang, suhu lebih tinggi juga matang. Predikat `ok(X)` berubah sekali dari false ke true (atau sebaliknya). Kita binary search X, bukan array. Alasan benar: ruang jawaban `[lo, hi]` integer, tiap tanya membuang setengah. Contoh: minimum kapasitas tas agar k hari cukup, minimum waktu, CSES Array Division.

**State:** `ok(x)` = “x layak”.
**Transisi:** jika `ok(mid)` coba lebih kecil (`hi=mid`), else `lo=mid+1`.

**Kapan dipakai / kapan tidak.** Pakai jika kamu bisa cek kandidat dalam O(n) dan monoton. Jangan jika `ok` naik-turun (itu unimodal → ternary / binsearch selisih). Jangan `hi` terlalu kecil sampai jawaban terpotong.

**Proses:** bagi `[7,2,5,10,8]` jadi 2 kelompok, minimize jumlah maksimum (CSES Array Division kecil).

1. lo=10 (max elemen), hi=32 (total).
2. mid=21: bisa? 7+2+5=14, 10+8=18, keduanya ≤21, 2 kelompok. Ya → hi=21.
3. mid=15: 7+2=9, 5, 10, 8 — butuh 4 kelompok >2. Tidak → lo=16.
4. Lanjut sampai lo=hi=18 (10+8).
5. Jawaban 18.

Cek `ok(18)`: `[7,2,5]=14`, `[10,8]=18`. `ok(17)`: 10+8=18>17 gagal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool muat(const vector<ll>& a, int k, ll batas) {
    int kelompok = 1;
    ll cur = 0;
    for (ll x : a) {
        if (x > batas) return false;
        if (cur + x > batas) {
            kelompok++;
            cur = 0;
        }
        cur += x;
    }
    return kelompok <= k;
}

ll minBeban(const vector<ll>& a, int k) {
    ll lo = 0, hi = 0;
    for (ll x : a) {
        lo = max(lo, x);
        hi += x;
    }
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (muat(a, k, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    vector<ll> a = {7, 2, 5, 10, 8};
    cout << minBeban(a, 2) << '\n'; // 18
    cout << muat(a, 2, 17) << '\n'; // 0
    return 0;
}
```

**Jebakan:**
1. `lo=0` padahal satu elemen >0 dan `ok` salah untuk x < max.
2. `hi=1e9` terlalu kecil (jumlah 2e5·1e9).
3. Predikat tidak monoton — binary search diam-diam WA.

**Kompleksitas:** waktu O(n log S) dengan S = selisih batas, memori O(1) di luar input.

---

## Binary search bilangan real

> **Ide satu kalimat:** potong interval real 80–100 kali; jangan kejar “sama”, kejar lebar cukup kecil.

### Binary search bilangan real

**Teori:** Analoginya menimbang beras: tiap kali bagi dua, galat tinggal setengah. `double` punya ±1e-15 relatif; loop tetap `for (int it=0; it<80; it++)` lebih aman dari `while (hi-lo>eps)` yang bisa menggantung. Alasan benar: 2^{-80} jauh lebih halus dari 1e-9. Predikat tetap harus monoton.

**Kapan dipakai / kapan tidak.** Pakai “minimum waktu real”, akar, geometri. Jangan banding `==` dua `double`. Jangan 20 iterasi jika butuh 1e-12.

**Proses:** akar 2, cari x≥0, x² ≥ 2, first such (secara real: sqrt).

1. lo=0, hi=2.
2. mid=1, 1<2 → lo=1.
3. mid=1.5, 2.25≥2 → hi=1.5.
4. Setelah 80 langkah, lo≈1.41421356.
5. Cek `lo*lo` dekat 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

double akar(double n) {
    double lo = 0, hi = max(1.0, n);
    for (int it = 0; it < 80; it++) {
        double mid = (lo + hi) / 2;
        if (mid * mid >= n) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(9);
    cout << akar(2) << '\n'; // 1.414213562
    return 0;
}
```

**Jebakan:**
1. `eps=1e-18` + while, loop tak berhenti.
2. `hi` awal 1 padahal n=100.
3. Overflow `mid*mid` untuk n besar — banding `mid >= n/mid` dengan jaga 0.

**Kompleksitas:** O(iter) evaluasi, di sini 80, memori O(1).

---

## Soal interaktif dan flush

> **Ide satu kalimat:** juri membaca tebakanmu **sekarang**; tanpa flush, ia menunggu, kamu juga menunggu.

### Soal interaktif dan flush

**Teori:** Analoginya telepon: kalau kamu bicara tanpa menekan “kirim”, lawan tidak mendengar. `endl` = newline + flush. `cout << x << '\n' << flush` sama. Fast I/O + `cin.tie(NULL)` **memutus** flush otomatis sebelum baca — di interaktif itu jebakan. Anggaran pertanyaan terbatas: binary search on answer adalah pola utama. Setelah jawaban akhir, sering ada format `! ans`.

**Kapan dipakai / kapan tidak.** Pakai soal “tanya-jawab”. Jangan buffer 100 query lalu flush sekali jika protokol minta sebaris-sebalik. Jangan `cerr` sebagai saluran juri.

**Proses:** juri memegang 6 di `[1,10]`. Kamu boleh tanya `? x`, dapat `<` atau `>=`.

1. lo=1, hi=10, mid=5. Tanya 5. Juri: `>=` (6≥5) → lo=5? Tergantung predikat.
   Pola first ≥ 6 dengan tanya “apakah ≥ mid”:
2. Lebih rapi: tebak ruang `[lo,hi]`, tanya mid, jika angka > mid, lo=mid+1, else hi=mid.
3. mid=5, angka 6>5 → lo=6.
4. mid=8, 6≤8 → hi=8. … sampai lo=hi=6.
5. Cetak `! 6` + flush.

Simulasi lokal di bawah meniru juri di proses yang sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// juri palsu untuk tes lokal
string juri(ll tebakan, ll rahasia) {
    if (rahasia <= tebakan) return "<=";
    return ">";
}

ll tebak(ll lo, ll hi, ll rahasia) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        // di soal nyata:
        // cout << "? " << mid << endl;
        // string res; cin >> res;
        string res = juri(mid, rahasia);
        if (res == ">") lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    // interaktif: jangan cin.tie(NULL) tanpa flush manual
    cout << tebak(1, 10, 6) << '\n' << flush; // 6
    return 0;
}
```

Di soal nyata, ganti `juri(...)` dengan `cout << "? " << mid << endl;` lalu `cin >> res`. Akhiri `cout << "! " << ans << endl;`.

**Jebakan:**
1. `'\n'` tanpa flush.
2. `cin.tie(NULL)` lalu baca respon yang belum terkirim.
3. Habis kuota karena linear search.
4. Off-by-one `lo=mid` infinite.

**Kompleksitas:** O(log (hi-lo)) query, memori O(1).

---

## Ternary search real

> **Ide satu kalimat:** satu titik tidak memberi arah, dua titik bisa membuang sepertiga ruang pada fungsi berpuncak satu.

### Ternary search real

**Teori:** Analoginya mendaki dalam kabut: bandingkan ketinggian dua patok. Fungsi **unimodal**: naik lalu turun (satu puncak) atau sebaliknya. Jika `f(m1) < f(m2)` pada pencarian maksimum, puncak ada di kanan m1. Alasan benar: tidak ada dua puncak, jadi sisi yang lebih rendah tidak bisa menyimpan puncak di luar. Binary search biasa gagal: satu nilai tidak bilang “masih naik atau sudah turun”.

**Kapan dipakai / kapan tidak.** Pakai domain real, f mahal sedikit, unimodal terbukti. Jangan fungsi bergelombang. Dataran (f konstan di interval) bisa membuang sisi yang salah. Untuk integer, sering lebih aman binary search pada selisih.

**Proses:** f(x)=−(x−3)²+10, puncak di 3, nilai 10. Cari di [0,6].

1. m1=2, m2=4. f(2)=9, f(4)=9. Simetris; buang sesuai implementasi (keduanya OK mendekat).
2. m1=2.0, m2=3.5: f(2)=9, f(3.5)=9.75 → puncak kanan m1, lo=m1.
3. Interval menyempit ke 3.
4. 80 iterasi cukup untuk 1e-9.
5. Cek f(3)=10.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

double fPuncak(double x) {
    return -(x - 3) * (x - 3) + 10;
}

double ternaryMax(double lo, double hi) {
    for (int it = 0; it < 80; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (fPuncak(m1) < fPuncak(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(6);
    double x = ternaryMax(0, 6);
    cout << x << ' ' << fPuncak(x) << '\n'; // ~3 ~10
    return 0;
}
```

**Jebakan:**
1. Membuang sisi terbalik (max vs min).
2. Dataran membuat `f(m1)==f(m2)` ambigu.
3. 20 iterasi pada interval 1e9.

**Kompleksitas:** O(iter) evaluasi, memori O(1).

---

## Ternary search integer

> **Ide satu kalimat:** ruang diskrit kecil di akhir harus disapu linier; `m1==m2` adalah jebakan.

### Ternary search integer

**Teori:** Analoginya tangga: sepertiga bisa jatuh di pijakan yang sama. Saat `hi-lo < 3`, mid bisa identik, loop tidak maju. Solusi: loop selama `hi-lo > 3`, lalu cek sisa 4 kandidat. Alasan banyak WA: menyalin kode real ke `int` apa adanya.

**Kapan dipakai / kapan tidak.** Pakai puncak pada indeks integer. Lebih sering: ganti ke binary search pada `f(i+1)-f(i)`. Jangan dataran lebar.

**Proses:** array unimodal `f = [1,3,7,6,2]`, puncak indeks 2 nilai 7.

1. lo=0, hi=4. m1=1 (3), m2=3 (6). 3<6 → lo=1.
2. lo=1, hi=4. m1=2 (7), m2=3 (6). 7>6 → hi=3.
3. hi-lo=2 ≤3, sapu 1..3: nilai 3,7,6. Puncak 7.
4. Tanpa sapu akhir, risiko `m1=m2`.
5. Jawaban indeks 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int puncakTernary(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (hi - lo > 3) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f[m1] < f[m2]) lo = m1;
        else hi = m2;
    }
    int best = lo;
    for (int i = lo; i <= hi; i++)
        if (f[i] > f[best]) best = i;
    return best;
}

int main() {
    vector<ll> f = {1, 3, 7, 6, 2};
    int i = puncakTernary(f);
    cout << i << ' ' << f[i] << '\n'; // 2 7
    return 0;
}
```

**Jebakan:**
1. Tidak menyapu sisa.
2. `m1` dan `m2` sama.
3. Dua puncak — unimodal palsu.

**Kompleksitas:** O(log n) evaluasi + O(1) sapu akhir, memori O(1).

---

## Binary search pada selisih

> **Ide satu kalimat:** “apakah sudah mulai turun?” adalah predikat monoton; itu binary search biasa.

### Binary search pada selisih

**Teori:** Analoginya: kamu tidak tanya ketinggian, kamu tanya “langkah berikutnya naik atau turun?”. Untuk integer unimodal, `ok(i) = (f[i+1] < f[i])` menjadi false, false, …, true. First true = puncak. Alasan ini hampir selalu lebih baik dari ternary integer: tidak ada `m1==m2`, alatnya sudah kamu punya dari Day 048.

**Kapan dipakai / kapan tidak.** Pakai peak index (LC 852, LC 162) jika ada **satu** puncak. Jangan jika ada dataran `f[i]==f[i+1]` tanpa aturan. Jangan array acak.

**Proses:** `f = [1,3,7,6,2]`.

1. i=0: 3>1, belum turun.
2. i=1: 7>3, belum.
3. i=2: 6<7, sudah turun. First true = 2.
4. i=3: 2<6, true.
5. Lower bound pada predikat “sudah turun”.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int puncakDariSelisih(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f[mid] > f[mid + 1]) hi = mid; // sudah turun, puncak di kiri/mid
        else lo = mid + 1;                 // masih naik
    }
    return lo;
}

int main() {
    vector<ll> f = {1, 3, 7, 6, 2};
    cout << puncakDariSelisih(f) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `f[mid] >= f[mid+1]` pada dataran.
2. `hi = n` lalu `f[mid+1]` out of bounds.
3. Memaksa ternary padahal selisih cukup.

**Kompleksitas:** O(log n) waktu, O(1) memori.

---

## Meet in the middle

> **Ide satu kalimat:** 2^40 mustahil, tapi 2^20 + 2^20 seketika — tukar perkalian menjadi penjumlahan.

### Meet in the middle

**Teori:** Analoginya dua tim merakit puzzle: masing-masing 20 keping (1 juta susunan), lalu dicocokkan, bukan 40 keping sekaligus (1 triliun). Bagi array jadi dua paruh, bangkitkan semua jumlah subset, sort satu paruh, untuk tiap jumlah kiri cari `X-s` di kanan. Alasan benar: setiap subset penuh = subset kiri ∪ subset kanan; kita tidak enumerasi 2^n pasangan secara buta, melainkan binary search.

Bangun subset O(2^k): `hasil[mask] = hasil[mask ^ (1<<b)] + a[b]` dengan `b = ctz(mask)`.

**Kapan dipakai / kapan tidak.** Pakai n≤40, “pilih subset jumlah X”. Jangan n≤20 (brute langsung). Jangan n=50. Jangan jika W kecil — DP knapsack O(nW) menang. Subset kosong: putuskan sesuai soal.

**Proses:** `a = [1,2,3,4]`, X=7, bagi 2+2.

1. Kiri `{1,2}`: jumlah `0,1,2,3`.
2. Kanan `{3,4}`: `0,3,4,7`.
3. Sort kanan: `0,3,4,7`.
4. s kiri=0 → cari 7 → ada. s=1 → 6 tidak. s=2 → 5 tidak. s=3 → 4 ada.
5. Dua subset: `{3,4}` dan `{1,2,4}`. (Dan `{1,2,4}` = 7.) `{1,2,4}`=7 ya. `{3,4}=7`. Jawaban 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> semuaJumlah(const vector<ll>& a) {
    int k = (int)a.size();
    vector<ll> res(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);
        res[mask] = res[mask ^ (1 << b)] + a[b];
    }
    return res;
}

ll hitungSubsetJumlah(const vector<ll>& a, ll X) {
    int n = (int)a.size();
    int mid = n / 2;
    vector<ll> kiri(a.begin(), a.begin() + mid);
    vector<ll> kanan(a.begin() + mid, a.end());
    auto A = semuaJumlah(kiri);
    auto B = semuaJumlah(kanan);
    sort(B.begin(), B.end());
    ll ans = 0;
    for (ll s : A) {
        auto lo = lower_bound(B.begin(), B.end(), X - s);
        auto hi = upper_bound(B.begin(), B.end(), X - s);
        ans += (hi - lo);
    }
    return ans;
}

int main() {
    vector<ll> a = {1, 2, 3, 4};
    cout << hitungSubsetJumlah(a, 7) << '\n'; // 2
    cout << hitungSubsetJumlah(a, 0) << '\n'; // 1 (kosong)
    return 0;
}
```

**Jebakan:**
1. Enumerasi O(2^k · k) padahal ada O(2^k).
2. `binary_search` hanya bool, padahal perlu kemunculan.
3. `int` untuk ans (bisa 2^{40}).
4. Lupa subset kosong.

**Kompleksitas:** waktu O(2^{n/2} · n), memori O(2^{n/2}). n=40 ≈ 2e6·20 aman; n=50 tidak.

---

## MITM knapsack dan prefix maksimum

> **Ide satu kalimat:** setelah diurutkan menurut berat, nilai terbaik untuk “berat ≤ sisa” adalah prefix maksimum, bukan satu titik.

### MITM knapsack dan prefix maksimum

**Teori:** Analoginya etalase yang diurut murah ke mahal: kalau uangmu cukup untuk barang ke-7, barang ke-5 yang lebih murah bisa jauh lebih berharga — jadi kamu ingin **nilai terbaik di antara semua yang muat**, bukan nilai barang persis di batas. Bangkitkan subset kiri `(berat, nilai)`, sort by berat, `pref[i] = max(nilai[0..i])`. Untuk subset kanan, `upper_bound` berat `W-s`, ambil `pref` di indeks itu. Tanpa prefix max, kamu hanya melihat satu subset yang beratnya paling dekat — itu **bug nomor satu** Day 054.

**Kapan dipakai / kapan tidak.** Pakai n≤40, berat dan nilai **terpisah**, kapasitas W besar (tidak muat DP `n·W`). Jangan jika W≤1e6 — DP lebih sederhana.

**Proses:** barang `(berat,nilai)`: `(2,3), (2,1), (3,5)`. W=4. Bagi 1+2.

Contoh minimal yang mematahkan tanpa prefix: kiri menghasilkan `(berat,nilai)` = `(0,0), (3,2), (4,1)` setelah sort berat. Cari sisa 4. `upper_bound` jatuh setelah 4, kandidat terakhir berat 4 nilai 1 — padahal berat 3 nilai 2 lebih baik. Prefix max: `[0,2,2]`.

Simulasi lengkap kecil:

1. Semua subset kanan+kiri digabung lewat sisa kapasitas.
2. Sort A by first (berat).
3. `pref[0]=A[0].second`, `pref[i]=max(pref[i-1], A[i].second)`.
4. Untuk s dari B, `it = upper_bound(A, {W-s, +∞})`, mundur satu, ambil pref.
5. Jaga `it==begin` (tidak ada yang muat).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<ll, ll>> subsetBeratNilai(const vector<pair<ll, ll>>& a) {
    int k = (int)a.size();
    vector<pair<ll, ll>> res(1 << k, {0, 0});
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);
        res[mask] = {res[mask ^ (1 << b)].first + a[b].first,
                     res[mask ^ (1 << b)].second + a[b].second};
    }
    return res;
}

ll knapsackMITM(const vector<pair<ll, ll>>& barang, ll W) {
    int n = (int)barang.size();
    int mid = n / 2;
    vector<pair<ll, ll>> L(barang.begin(), barang.begin() + mid);
    vector<pair<ll, ll>> R(barang.begin() + mid, barang.end());
    auto A = subsetBeratNilai(L);
    auto B = subsetBeratNilai(R);
    sort(A.begin(), A.end()); // berat naik
    vector<ll> pref(A.size());
    pref[0] = A[0].second;
    for (int i = 1; i < (int)A.size(); i++)
        pref[i] = max(pref[i - 1], A[i].second);
    ll best = 0;
    for (auto [w, val] : B) {
        if (w > W) continue;
        ll sisa = W - w;
        auto it = upper_bound(A.begin(), A.end(), make_pair(sisa, LLONG_MAX));
        if (it == A.begin()) {
            best = max(best, val); // hanya paruh B
            continue;
        }
        --it;
        int idx = (int)(it - A.begin());
        best = max(best, val + pref[idx]);
    }
    return best;
}

int main() {
    // (3,2) lebih berharga dari (4,1); W=4 harus pilih 2, bukan 1
    vector<pair<ll, ll>> a = {{3, 2}, {4, 1}};
    cout << knapsackMITM(a, 4) << '\n'; // 2
    vector<pair<ll, ll>> b = {{2, 3}, {2, 1}, {3, 5}};
    cout << knapsackMITM(b, 4) << '\n'; // 5 dari barang (3,5)
    return 0;
}
```

**Jebakan:**
1. Lupa prefix maksimum.
2. `upper_bound` pair tanpa `LLONG_MAX` di second — salah urutan.
3. Memori 2^20 pair ≈ 16 MB; hitung dulu.

**Kompleksitas:** waktu O(2^{n/2} n), memori O(2^{n/2}).

---

## 4-SUM sebagai MITM

> **Ide satu kalimat:** empat loop jadi dua kali dua loop: simpan semua jumlah pasangan, cari pelengkapnya.

### 4-SUM sebagai MITM

**Teori:** Analoginya dua orang masing-masing memilih 2 kartu, lalu mengecek apakah total 4 kartu nol. Enumerasi 4-loop O(n^4); MITM O(n² log n): semua `a[i]+a[j]`, sort, untuk tiap pasangan lain cari `-(c+d)`. Semangat yang sama dengan subset: pecah kerja jadi dua paruh. UVa 1152, SPOJ ABCDEF.

**Kapan dipakai / kapan tidak.** Pakai n≤4000 untuk 4 array, jumlah target. Jangan `unordered_map` telanjang di CF. Jangan n=1e5 (n² mati).

**Proses:** A=B=C=D=`[1, 0, -1]`, target 0. (sederhanakan satu array 4-sum)

Mini dua+dua: array `[1, 2, -2, -1]`, target 0.

1. Pasangan kiri (indeks 0,1): 1+2=3. Kanan (2,3): −2+−1=−3. 3+(−3)=0.
2. Semua pasangan posisi 2+2 jika n=4: juga 1+(−1)=0 dengan 2+(−2), dll.
3. Sort jumlah paruh kedua, binary search.
4. Hati-hati indeks tidak overlap jika satu array.
5. Soal 4 array terpisah lebih longgar (indeks bebas).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll empatJumlahNol(const vector<ll>& A, const vector<ll>& B,
                  const vector<ll>& C, const vector<ll>& D) {
    vector<ll> ab;
    for (ll x : A) for (ll y : B) ab.push_back(x + y);
    sort(ab.begin(), ab.end());
    ll ans = 0;
    for (ll x : C) for (ll y : D) {
        ll butuh = -(x + y);
        auto lo = lower_bound(ab.begin(), ab.end(), butuh);
        auto hi = upper_bound(ab.begin(), ab.end(), butuh);
        ans += (hi - lo);
    }
    return ans;
}

int main() {
    vector<ll> A = {1, 2}, B = {-2, -1}, C = {-1, 2}, D = {0, 2};
    // 1 + (-2) + (-1) + 2 = 0 → minimal satu
    cout << empatJumlahNol(A, B, C, D) << '\n';
    return 0;
}
```

Hitung: AB = {1-2, 1-1, 2-2, 2-1} = {-1,0,0,1}.
CD = {-1+0,-1+2,2+0,2+2} = {-1,1,2,4}.
Pasangan 0: CD butuh 0 tidak ada; butuh 1 ada (AB punya 1 sekali) untuk CD=-1; butuh -1 ada untuk CD=1. ans=1+1=2.

**Jebakan:**
1. Overflow jumlah pair.
2. Hash hack.
3. Indeks sama dipakai dua kali pada 4-sum satu array.

**Kompleksitas:** waktu O(n² log n), memori O(n²). n=1000 → 1e6, aman; n=5000 ketat.

---

## Ringkasan file 05

- Merge: `[l,r)`, `tmp` di luar, `<=` stabil.
- Inversi: `inv += mid-i`, bukan `+1`.
- Bound: `>=` lower, `>` upper, `hi` awal = n.
- On answer: predikat monoton + cek O(n).
- Real: 80 iterasi, bukan `==`.
- Interaktif: `endl` / `flush`, jaga kuota.
- Unimodal integer: binary search pada selisih, sapu sisa jika ternary.
- MITM: n≤40, sort + bound; knapsack wajib prefix max; 4-SUM = dua kali pasangan.

Kembali ke [README dasar](README-dasar.md) atau [file 00](00-template-io-kompleksitas.md).
