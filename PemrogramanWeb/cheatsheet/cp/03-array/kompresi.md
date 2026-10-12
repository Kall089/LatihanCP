# Kompresi Koordinat

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** nilai boleh 10⁹, tapi kalau n cuma 10⁵, beri mereka nomor kursi 0..n-1.

Day ComprogLearning: **038** kompresi koordinat. Semua 0-based. Fungsi modular. `ll` untuk nilai asli. Urutan hidup, jarak mati.

## Daftar isi

- [Kompresi koordinat](#kompresi-koordinat)
- [Mapping balik](#mapping-balik)
- [Frekuensi setelah kompresi](#frekuensi-setelah-kompresi)
- [Rank array](#rank-array)
- [Kompresi interval dan r+1](#kompresi-interval-dan-r1)
- [Sweep line terkompres](#sweep-line-terkompres)
- [Kompresi 2D](#kompresi-2d)
- [Kapan jangan kompres](#kapan-jangan-kompres)

---

## Kompresi koordinat

> **Ide satu kalimat:** tiket bertuliskan “kursi 1.000.000.007” tidak berguna jika hanya 5 orang datang.

### Kompresi koordinat

**Teori:** Analoginya bioskop: beri kursi 0..k-1 menurut urutan tiket. Idiom: `sort`, `unique+erase`, `lower_bound`. Alasan benar: urutan terjaga (`a<b` ⇒ `id[a]<id[b]`), **jarak hancur** (`b-a` bukan `id[b]-id[a]`). `unique` tanpa `erase` meninggalkan ekor sampah.

**Kapan:** Pakai Fenwick/segtree/array freq pada nilai 1e9. Jangan jika rumus butuh jarak asli. Jangan tanpa `erase`.

**Proses:** `a = [100, 1, 100, 50]`.

| nilai asli | setelah sort unik | id |
| ---: | ---: | ---: |
| 1 | 1 | 0 |
| 50 | 50 | 1 |
| 100 | 100 | 2 |

1. Salin, sort: `1,50,100,100`.
2. unique+erase: `1,50,100`.
3. 100 → 2, 1 → 0, 50 → 1.
4. Array terkompres: `2,0,2,1`.
5. `freq[3]` cukup, bukan `freq[101]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Kompres {
    vector<ll> v;
    void bangun(vector<ll> a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        v = a;
    }
    int id(ll x) const {
        return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
    }
    int size() const { return (int)v.size(); }
};

int main() {
    FASTIO;
    vector<ll> a = {100, 1, 100, 50};
    Kompres kp;
    kp.bangun(a);
    cout << kp.size() << '\n'; // 3
    cout << kp.id(100) << ' ' << kp.id(1) << ' ' << kp.id(50) << '\n';
    // 2 0 1
    return 0;
}
```

**Jebakan:**
1. `unique` tanpa `erase`.
2. `id` pada nilai yang tidak pernah di-`bangun`.
3. Mengira selisih id = selisih nilai.

**Kompleksitas:** bangun O(n log n), query O(log n), memori O(n).

---

## Mapping balik

> **Ide satu kalimat:** id adalah kursi; `v[id]` adalah nomor tiket asli.

### Mapping balik

**Teori:** Analoginya denah kursi: setelah menaruh orang di kursi 2, kamu masih harus tahu tiketnya 100. Simpan vector unik terurut `v`. `v[i]` = nilai yang mendapat id i. Alasan benar: jawaban soal sering minta nilai asli, bukan id. Tanpa mapping balik, kamu hanya punya nomor 0..k-1.

**Kapan:** Pakai saat output nilai, atau saat menghitung panjang asli `v[i+1]-v[i]`. Jangan mengira `id` reversibel tanpa `v`.

**Proses:** `a = [100, 1, 50]`.

| id | v[id] | dipakai untuk |
| ---: | ---: | --- |
| 0 | 1 | nilai terkecil |
| 1 | 50 | tengah |
| 2 | 100 | terbesar |

1. `id(50)=1`, `v[1]=50`.
2. Cetak “nilai ke-2 terkecil” = `v[1]`.
3. Jarak asli 100-1 = 99, jarak id 2-0 = 2. Berbeda.
4. Panjang celah `[v[i], v[i+1])` = `v[i+1]-v[i]`.
5. Mapping balik wajib untuk panjang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Kompres {
    vector<ll> v;
    void bangun(vector<ll> a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        v = a;
    }
    int id(ll x) const {
        return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
    }
    ll nilai(int i) const { return v[i]; }
};

int main() {
    FASTIO;
    Kompres kp;
    kp.bangun({100, 1, 50});
    cout << kp.nilai(kp.id(50)) << '\n'; // 50
    cout << kp.nilai(0) << ' ' << kp.nilai(2) << '\n'; // 1 100
    return 0;
}
```

**Jebakan:**
1. `nilai(i)` saat i = `v.size()`.
2. Menghitung panjang dengan selisih id.
3. `v` tidak terurut karena lupa sort.

**Kompleksitas:** bangun O(n log n), balik O(1), memori O(n).

---

## Frekuensi setelah kompresi

> **Ide satu kalimat:** `cnt[id(x)]++` menggantikan `cnt[x]` yang mustahil.

### Frekuensi setelah kompresi

**Teori:** Analoginya kotak suara: kamu tidak membuat 1e9 laci, hanya laci sebanyak calon. Setelah id ada, array `cnt[k]` sah. Alasan benar: Fenwick dan SegTree juga hidup di indeks 0..k-1. Urutan id mengikuti urutan nilai, jadi “prefix freq sampai nilai X” = jumlah `cnt[0..id(X)]` jika X ada, atau `cnt[0..lower_bound(X)-1]`.

**Kapan:** Pakai hitung kemunculan nilai 1e9, order statistic kasar. Jangan `cnt[x]` langsung.

**Proses:** `a = [100, 1, 100, 50, 1]`.

| id | nilai | freq |
| ---: | ---: | ---: |
| 0 | 1 | 2 |
| 1 | 50 | 1 |
| 2 | 100 | 2 |

1. k=3.
2. `cnt[0]=2`, `cnt[2]=2`.
3. Berapa nilai ≤ 50? `cnt[0]+cnt[1]=3`.
4. Berapa nilai ≤ 40? lower_bound(40)=id 1, jumlah `cnt[0]=2`.
5. Tanpa kompresi, `cnt[100]` butuh array 101.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<vector<ll>, vector<int>> freqTerkompres(const vector<ll>& a) {
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<int> cnt((int)v.size(), 0);
    for (ll x : a) {
        int i = (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
        cnt[i]++;
    }
    return {v, cnt};
}

int main() {
    FASTIO;
    auto [v, cnt] = freqTerkompres({100, 1, 100, 50, 1});
    cout << v.size() << '\n'; // 3
    cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << '\n'; // 2 1 2
    return 0;
}
```

**Jebakan:**
1. Membangun `v` dari subset query, lalu `id` data lain yang tidak masuk.
2. `int cnt[1000000001]`.
3. Prefix freq off-by-one pada nilai yang tidak ada.

**Kompleksitas:** O(n log n) bangun, O(1) akses freq, memori O(k).

---

## Rank array

> **Ide satu kalimat:** kadang dua tiket 100 harus tetap dua kursi berbeda.

### Rank array

**Teori:** Analoginya lomba: dua orang waktu sama boleh dapat peringkat sama (dense rank) atau peringkat berbeda menurut urutan daftar (ordinal). Dense rank = kompresi unik. Ordinal rank = posisi setelah sort, kembar tidak digabung. Alasan benar: soal “peringkat” tidak selalu membuang duplikat.

**Kapan:** Pakai dense untuk Fenwick nilai. Pakai ordinal jika setiap kemunculan punya identitas. Jangan campur keduanya di satu struktur.

**Proses:** `a = [100, 1, 100, 50]`.

| i | a[i] | dense id | ordinal (stabil) |
| ---: | ---: | ---: | ---: |
| 0 | 100 | 2 | 2 |
| 1 | 1 | 0 | 0 |
| 2 | 100 | 2 | 3 |
| 3 | 50 | 1 | 1 |

1. Dense: dua 100 berbagi id 2.
2. Ordinal: 100 pertama kursi 2, 100 kedua kursi 3.
3. Sort pair `{nilai, indeks}` untuk ordinal.
4. Fenwick “jumlah nilai ≤ x” butuh dense.
5. “elemen ke-k setelah sort” butuh ordinal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> denseRank(const vector<ll>& a) {
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<int> r(a.size());
    for (int i = 0; i < (int)a.size(); i++)
        r[i] = (int)(lower_bound(v.begin(), v.end(), a[i]) - v.begin());
    return r;
}

vector<int> ordinalRank(const vector<ll>& a) {
    int n = (int)a.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    vector<int> r(n);
    for (int p = 0; p < n; p++) r[idx[p]] = p;
    return r;
}

int main() {
    FASTIO;
    vector<ll> a = {100, 1, 100, 50};
    auto d = denseRank(a);
    auto o = ordinalRank(a);
    cout << d[0] << ' ' << d[2] << '\n'; // 2 2
    cout << o[0] << ' ' << o[2] << '\n'; // 2 3
    return 0;
}
```

**Jebakan:**
1. Ordinal tanpa pecah seri indeks — urutan tidak stabil.
2. Dense dipakai saat soal minta identitas tiap kemunculan.
3. `iota` lupa, idx acak.

**Kompleksitas:** O(n log n) waktu, O(n) memori.

---

## Kompresi interval dan r+1

> **Ide satu kalimat:** titik tutup interval harus punya kursi sendiri, atau sapuan `−1` menumpuk di hari yang masih aktif.

### Kompresi interval dan r+1

**Teori:** Analoginya hotel: tamu check-out pagi hari R+1, bukan malam R — kamar R masih terisi. Saat menandai `+1` di L dan `−1` di R+1 pada sumbu terkompres, **R+1 harus ada di daftar kursi**. Alasan WA: hanya memasukkan L dan R, lalu `id(R+1)` jatuh ke nilai berikutnya yang salah atau `end()`.

**Kapan:** Pakai sweep interval, count overlapping. Jangan kompres jika kamu menjumlah **panjang asli** tanpa mapping balik.

**Proses:** interval `[1,3]`, `[3,4]` inklusif.

| titik | alasan masuk daftar |
| ---: | --- |
| 1 | L pertama |
| 3 | R pertama dan L kedua |
| 4 | R kedua dan R pertama + 1 |
| 5 | R kedua + 1 |

1. `+1` di 1, `−1` di 4 untuk interval pertama.
2. `+1` di 3, `−1` di 5 untuk interval kedua.
3. Sweep: pos1:1, pos3:2, pos4:1, pos5:0.
4. Tanpa kursi 5, `−1` kedua hilang.
5. Inklusif versus setengah terbuka harus konsisten.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> titikPenting(const vector<pair<ll, ll>>& seg) {
    vector<ll> v;
    for (auto [L, R] : seg) {
        v.push_back(L);
        v.push_back(R);
        v.push_back(R + 1);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

int idOf(const vector<ll>& v, ll x) {
    return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
}

int main() {
    FASTIO;
    vector<pair<ll, ll>> seg = {{1, 3}, {3, 4}};
    auto v = titikPenting(seg);
    cout << v.size() << '\n'; // 4
    cout << idOf(v, 1) << ' ' << idOf(v, 5) << '\n'; // 0 3
    return 0;
}
```

**Jebakan:**
1. Lupa `R+1` di daftar.
2. Interval setengah terbuka versus inklusif tertukar.
3. `id(R+1)` = `v.size()` lalu menulis `d[size]` tanpa +1 cadangan.

**Kompleksitas:** O(n log n) bangun, memori O(n).

---

## Sweep line terkompres

> **Ide satu kalimat:** difference array pada kursi, lalu prefix; panjang asli hanya saat kamu membayar sewa.

### Sweep line terkompres

**Teori:** Analoginya satpam hotel menghitung tamu per “hari penting”, bukan per 1e9 hari. `d[id(L)]++`, `d[id(R+1)]--`, prefix. Jika soal minta “berapa unit ter-cover”, kalikan overlap dengan `v[i+1]-v[i]`. Alasan benar: dua tamu di hari 1 dan 100 tidak membuat 99 hari semu jika tidak ada event di antaranya — kecuali kamu butuh panjang, maka celah itu dibayar dengan selisih `v`.

**Kapan:** Pakai overlap count, union panjang interval. Jangan kalikan 1 jika soal minta panjang.

**Proses:** `[1,3]`, `[3,4]` inklusif, hitung overlap di tiap titik penting, dan union panjang integer.

| posisi v[i] | overlap setelah prefix | celah ke v[i+1] |
| ---: | ---: | ---: |
| 1 | 1 | 2 (hari 1,2) |
| 3 | 2 | 1 (hari 3) |
| 4 | 1 | 1 (hari 4) |
| 5 | 0 | - |

1. Union panjang integer = 4 (hari 1..4).
2. Tanpa kali celah, kamu hanya punya overlap di 4 titik.
3. Max overlap = 2.
4. `R+1` mematikan dengan benar.
5. Titik 5 overlap 0.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> titikPenting(const vector<pair<ll, ll>>& seg) {
    vector<ll> v;
    for (auto [L, R] : seg) {
        v.push_back(L);
        v.push_back(R + 1);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

int idOf(const vector<ll>& v, ll x) {
    return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
}

pair<int, ll> sapuUnion(const vector<pair<ll, ll>>& seg) {
    auto v = titikPenting(seg);
    vector<int> d((int)v.size() + 1, 0);
    for (auto [L, R] : seg) {
        d[idOf(v, L)]++;
        d[idOf(v, R + 1)]--;
    }
    int cur = 0, best = 0;
    ll panjang = 0;
    for (int i = 0; i + 1 < (int)v.size(); i++) {
        cur += d[i];
        best = max(best, cur);
        if (cur > 0) panjang += v[i + 1] - v[i];
    }
    return {best, panjang};
}

int main() {
    FASTIO;
    auto [best, panjang] = sapuUnion({{1, 3}, {3, 4}});
    cout << best << ' ' << panjang << '\n'; // 2 4
    return 0;
}
```

**Jebakan:**
1. Menjumlah overlap × 1 alih-alih × panjang asli.
2. Memasukkan R tetapi tidak R+1, lalu celah salah.
3. `int` untuk panjang 1e9.

**Kompleksitas:** O(n log n) bangun, O(n) sapuan, memori O(n).

---

## Kompresi 2D

> **Ide satu kalimat:** dua sumbu, dua kamus; kotak [x1,x2]×[y1,y2] jadi submatriks id.

### Kompresi 2D

**Teori:** Analoginya peta kota: nama jalan panjang, tetapi persimpangan yang dipakai hanya n. Kompres x dan y terpisah. Difference 2D hidup di grid k×k. Alasan benar: n=2000 titik, grid 2000×2000 muat; grid 1e9×1e9 tidak.

**Kapan:** Pakai rectangle add/query offline, titik di bidang 1e9. Jangan n=1e5 jika kamu membuat grid n×n (8e10 sel). Untuk n besar, pakai Fenwick 2D terkompres atau sweep + Fenwick 1D.

**Proses:** titik `(100,5)`, `(1,5)`, `(100,9)`.

| x asli | id x | y asli | id y |
| ---: | ---: | ---: | ---: |
| 1 | 0 | 5 | 0 |
| 100 | 1 | 9 | 1 |

1. Grid 2×2.
2. Tiga titik menempati (1,0), (0,0), (1,1).
3. Query persegi x∈[1,100], y∈[5,9] = seluruh grid.
4. Lupa kompres y → `cnt[5]` dan `cnt[9]` butuh array 10, kebetulan kecil, tetapi 1e9 gagal.
5. `R+1` / `x2+1` tetap wajib untuk difference.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Kompres {
    vector<ll> v;
    void bangun(vector<ll> a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        v = a;
    }
    int id(ll x) const {
        return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
    }
    int size() const { return (int)v.size(); }
};

int main() {
    FASTIO;
    vector<pair<ll, ll>> pt = {{100, 5}, {1, 5}, {100, 9}};
    vector<ll> xs, ys;
    for (auto [x, y] : pt) {
        xs.push_back(x);
        ys.push_back(y);
    }
    Kompres kx, ky;
    kx.bangun(xs);
    ky.bangun(ys);
    cout << kx.size() << ' ' << ky.size() << '\n'; // 2 2
    cout << kx.id(100) << ' ' << ky.id(5) << '\n'; // 1 0
    return 0;
}
```

**Jebakan:**
1. Satu kamus untuk x dan y campur — id kacau.
2. Grid n×n pada n=1e5.
3. Lupa `x2+1` di daftar x untuk cat persegi.

**Kompleksitas:** bangun O(n log n), grid O(kx · ky) memori.

---

## Kapan jangan kompres

> **Ide satu kalimat:** jika rumus butuh jarak, nomor kursi tidak menggantikan meteran.

### Kapan jangan kompres

**Teori:** Analoginya mengganti alamat rumah dengan nomor antrean pos: urutan tetangga benar, jarak kilometer hilang. Kompresi **bukan** hashing acak; ia monoton. Tetapi `id[b]-id[a]` bukan `b-a`. Binary search pada nilai asli tidak butuh kompresi. Array `a[i]` yang sudah 1..n tidak butuh kompresi.

**Kapan:** Jangan kompres untuk jarak geometri, waktu tempuh, atau modulus. Jangan kompres lalu memakai id sebagai bobot. Pakai nilai asli untuk rumus, id hanya untuk indeks struktur.

**Proses:** dua titik x=1 dan x=100.

| kebutuhan | alat | hasil |
| --- | --- | --- |
| siapa kiri | id | 0 lalu 1 |
| jarak | asli | 99 |
| Fenwick freq | id | 2 sel |
| `x % 7` | asli | 1 dan 2 |

1. Kompres menjawab “siapa”.
2. Tidak menjawab “seberapa jauh”.
3. Sweep union harus kali `v[i+1]-v[i]`.
4. SegTree posisi 1..n array biasa: jangan kompres.
5. Nilai negatif: sort tetap benar, id 0 adalah yang terkecil (paling negatif).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll jarakAsli(ll a, ll b) { return b - a; }

int jarakId(ll a, ll b, const vector<ll>& v) {
    int ia = (int)(lower_bound(v.begin(), v.end(), a) - v.begin());
    int ib = (int)(lower_bound(v.begin(), v.end(), b) - v.begin());
    return ib - ia;
}

int main() {
    FASTIO;
    vector<ll> v = {1, 100};
    cout << jarakAsli(1, 100) << '\n'; // 99
    cout << jarakId(1, 100, v) << '\n'; // 1, bukan jarak
    return 0;
}
```

**Jebakan:**
1. Mengganti semua `a[i]` dengan id di rumus selisih.
2. Kompresi sebagai “hash” lalu mengira tabrakan mustahil — itu bukan hash, itu rank.
3. Lupa nilai negatif; `lower_bound` tetap sah setelah sort.

**Kompleksitas:** perbandingan O(1); keputusan desain O(1).

---

## Pola kode yang dihafal

> **Ide satu kalimat:** tiga baris membangun kamus, satu baris menanya kursi.

### Pola kode yang dihafal

**Teori:** Analoginya stempel karet: jangan menulis ulang dari nol tiap kontes. Fungsi `bangun` dan `id` cukup. Semua titik yang akan ditanya harus masuk `bangun`. Alasan WA paling sering: query membawa nilai baru yang tidak dikumpulkan.

**Kapan:** Pakai pola ini di Fenwick, SegTree, difference. Jangan membangun kamus hanya dari update lalu menanya nilai lain.

**Proses:** data `{7, 2}`, query nilai 2 dan 7.

1. Kumpulkan 2 dan 7.
2. Sort unik.
3. id(2)=0, id(7)=1.
4. Jika query 5 tidak dikumpulkan, `id` bisa 1 (lower_bound ke 7) — arti “≥5”, bukan “=5”.
5. Bedakan `id` eksak (`find` harus ketemu) versus `id` lower_bound.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> bangunKamus(vector<ll> semua) {
    sort(semua.begin(), semua.end());
    semua.erase(unique(semua.begin(), semua.end()), semua.end());
    return semua;
}

int idEksak(const vector<ll>& v, ll x) {
    auto it = lower_bound(v.begin(), v.end(), x);
    if (it == v.end() || *it != x) return -1;
    return (int)(it - v.begin());
}

int main() {
    FASTIO;
    auto v = bangunKamus({7, 2, 7});
    cout << idEksak(v, 2) << '\n'; // 0
    cout << idEksak(v, 5) << '\n'; // -1
    return 0;
}
```

**Jebakan:**
1. `lower_bound` tanpa cek `*it == x`.
2. Kamus tidak memuat semua nilai query.
3. Multi tes: kamus tidak di-reset.

**Kompleksitas:** bangun O(n log n), tanya O(log n), memori O(n).

---

## Ringkasan

- Sort, unique, erase, lower_bound.
- Urutan hidup, jarak mati.
- Interval: masukkan `R+1`.
- Sweep panjang: kali `v[i+1]-v[i]`.
- Dense versus ordinal rank.
- 2D: dua kamus, hati-hati ukuran grid.
- Jangan kompres rumus jarak atau modulus.

Kembali ke [mono stack](mono-stack-deque.md) atau lanjut sorting: [folder 04](../04-sorting-searching/README.md).
