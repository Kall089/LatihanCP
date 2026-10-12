# Interval dan exchange argument

[← README](README.md) · [Indeks CP](../README.md)

Banyak greedy yang benar dibuktikan dengan **menukar** dua elemen di jawaban optimal sampai ia identik dengan greedy. Interval adalah keluarga terbesar: urut `r` untuk memilih, urut `l` untuk menyapu. Kalau ada bobot, exchange sering rusak dan kamu kembali ke DP.

Day terkait: **072**. File saudara: [kapan-dp.md](kapan-dp.md) untuk counterexample, [konstruktif.md](konstruktif.md) untuk membangun objek.

## Daftar isi

- [Exchange argument](#exchange-argument)
- [Waktu proses terpendek](#waktu-proses-terpendek)
- [Activity selection](#activity-selection)
- [Menggabungkan interval](#menggabungkan-interval)
- [Menutup segmen](#menutup-segmen)
- [Ruangan minimum](#ruangan-minimum)
- [Fractional knapsack](#fractional-knapsack)
- [Penjadwalan deadline](#penjadwalan-deadline)
- [Peta keputusan](#peta-keputusan)

---

## Exchange argument

**Teori:** Empat langkah. (1) Ambil jawaban optimal yang **paling mirip** kriteria greedy. (2) Jika ia menyalahi kriteria, ada dua elemen berdampingan yang urutannya “salah”. (3) Tukar keduanya. (4) Biaya tidak memburuk, kontradiksi dengan “paling mirip”, atau kita bisa mengurutkan optimal sampai identik dengan greedy. Analoginya: kalau dua orang di antrean tertukar dan total tunggu tidak naik setelah dikembalikan ke urutan greedy, maka urutan greedy aman.

Kenapa **berdampingan**: menukar dua yang berjauhan mengubah banyak waktu mulai. Dua tetangga hanya saling menukar, jumlah durasi blok itu tetap, sisa antrean tidak berubah.

**Kapan:** kamu punya kriteria sort (`r` naik, rasio `t/w`, string gabungan). Wajib sebelum percaya komparator. Tidak dipakai jika kriteria lokal tidak ada — di situ DP / search. Lihat [kapan-dp.md](kapan-dp.md).

**Proses:** SPT, dua pekerjaan berdampingan `i` lalu `j`, durasi `t_i, t_j`. Waktu mulai blok = `T`.

Urutan i lalu j:

```text
C_i = T + t_i
C_j = T + t_i + t_j
jumlah blok = 2T + 2 t_i + t_j
```

Urutan j lalu i: jumlah `2T + 2 t_j + t_i`. Selisih (i dulu minus j dulu) = `t_i - t_j`. Jika `t_i > t_j`, menukar agar yang pendek dulu **menurunkan** jumlah. Optimal tanpa inversi = terurut naik.

Angka: `T = 10`, `t_i = 5`, `t_j = 2`.

```text
i lalu j: C = 15, 17  jumlah 32
j lalu i: C = 12, 17  jumlah 29
hemat 3 = 5-2
```

**Kode:** turunkan komparator dari dua elemen, bukan menebak.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Job {
    ll t, w;
};

bool lebih_dulu(const Job& x, const Job& y) {
    return x.t * y.w < y.t * x.w; // Σ w C, hindari bagi
}

ll biaya(vector<Job> a) {
    sort(a.begin(), a.end(), lebih_dulu);
    ll waktu = 0, sum = 0;
    for (auto j : a) {
        waktu += j.t;
        sum += j.w * waktu;
    }
    return sum;
}

int main() {
    FASTIO;
    vector<Job> a = {{5, 1}, {2, 1}, {3, 2}};
    cout << biaya(a) << '\n'; // 21
    return 0;
}
```

Urutan rasio `t/w`: `(3,2)=1.5`, `(2,1)=2`, `(5,1)=5`. `C = 3,5,10`, `Σ wC = 2*3 + 1*5 + 1*10 = 21`. Urutan lain `(2,1),(3,2),(5,1)` biaya 22.

**Jebakan:**
1. Komparator `double` bagi `t/w`.
2. `int * int` overflow, wajib `ll`.
3. `<=` di sort C++ melanggar *strict weak ordering*.
4. Menukar dua elemen jauh lalu menghitung seolah hanya dua yang berubah.

**Kompleksitas:** bukti `O(1)` di kertas. Kode sort `O(n log n)`.

---

## Waktu proses terpendek

**Teori:** Satu mesin, semua pekerjaan tersedia di waktu 0, minimalkan `Σ C_i`. Urutkan durasi naik. Sudah dibuktikan di exchange. Analoginya antrean printer: cetak yang tipis dulu supaya banyak orang selesai cepat.

**Kapan:** satu sumber daya, tidak ada deadline / prioritas lain. Ada bobot `w_i` → sort `t/w` (Smith), bukan `t` saja. Ada waktu rilis `r_i` → SPT murni bisa salah, sering DP atau heap “yang sudah datang”.

**Proses:** durasi `8, 1, 4, 2`.

```text
urut: 1, 2, 4, 8
C   : 1, 3, 7, 15
ΣC  = 26
```

Urutan terburuk LPT: `8,4,2,1` → `C = 8,12,14,15` jumlah `49`.

Counterexample SPT saat ada `r_i`: pekerjaan A durasi 5 rilis 0, B durasi 1 rilis 1. SPT mengabaikan rilis dan bisa menganggur salah. Itu sinyal DP/heap, bukan file ini.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<ll, vector<ll>> spt(vector<ll> t) {
    int n = (int)t.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (t[i] != t[j]) return t[i] < t[j];
        return i < j;
    });
    ll waktu = 0, sum = 0;
    vector<ll> C(n);
    for (int i : idx) {
        waktu += t[i];
        C[i] = waktu;
        sum += waktu;
    }
    return {sum, C};
}

int main() {
    FASTIO;
    auto [sum, C] = spt({8, 1, 4, 2});
    cout << sum << '\n'; // 26
    for (ll x : C) cout << x << ' ';
    cout << '\n'; // 15 1 7 3
    return 0;
}
```

**Jebakan:**
1. Sort nilai saja lalu kehilangan indeks pekerjaan.
2. `r_i` diabaikan.
3. Mengira LPT (terpanjang dulu) meminimalkan `Σ C_i`. LPT untuk tujuan lain.

**Kompleksitas:** `O(n log n)` waktu, `O(n)` memori.

---

## Activity selection

**Teori:** Pilih sebanyak mungkin interval saling lepas. Kriteria: **urut ujung `r` naik**, ambil jika `l` tidak menabrak interval terakhir yang diambil. Intuisi: yang selesai paling awal menyisakan sisa waktu terbanyak. Exchange: jika optimal mengambil interval yang selesai lebih lambat sebagai yang pertama, ganti dengan yang `r` lebih kecil — ia muat dan menyisakan ruang `>=` semula.

**Kapan:** “sebanyak mungkin kegiatan tanpa tabrakan”. “Buang sesedikit mungkin” = `n - jawaban greedy`. Ada **bobot** → bukan greedy, DP. Banyak mesin → seksi ruangan minimum.

**Proses:** `[1,4], [2,3], [3,5], [0,6], [5,7], [8,9], [5,9]`.

Urut `r`: `[2,3], [1,4], [3,5], [0,6], [5,7], [8,9], [5,9]`.

```text
ambil [2,3]   akhir=3
[1,4] skip
[3,5] sentuh tertutup skip
[0,6] skip
[5,7] ambil  akhir=7
[8,9] ambil  akhir=9
[5,9] skip
```

Jawaban 3: `[2,3], [5,7], [8,9]`.

Tiga kriteria salah:

| kriteria | contoh | greedy | optimal |
| --- | --- | ---: | ---: |
| urut `l` | `[1,100],[2,3],[4,5]` | 1 | 2 |
| durasi pendek | `[1,10],[9,12],[11,20]` | 1 | 2 |
| bobot | `[0,2]/1 + [1,4]/10` | 1 | 10 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int activity_tertutup(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) if (l > akhir) {
        hit++;
        akhir = r;
    }
    return hit;
}

int activity_setengah(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) { return x.second < y.second; });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) if (l >= akhir) {
        hit++;
        akhir = r;
    }
    return hit;
}

int main() {
    FASTIO;
    vector<pair<ll, ll>> a = {
        {1, 4}, {2, 3}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}
    };
    cout << activity_tertutup(a) << '\n'; // 3
    cout << activity_setengah({{1, 5}, {5, 9}}) << '\n'; // 2
    cout << activity_tertutup({{1, 5}, {5, 9}}) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `akhir = 0` padahal ada interval negatif.
2. `[l,r]` versus `[l,r)` satu karakter `>` versus `>=`.
3. Urut `l` karena kebiasaan.
4. Memakai greedy ini untuk max bobot.

**Kompleksitas:** `O(n log n)` sort, `O(n)` sapuan.

---

## Menggabungkan interval

**Teori:** Satukan interval yang beririsan atau bersentuhan menjadi blok. Urut menurut `l`. Jaga blok terakhir. Jika interval baru `l <= r_blok`, perpanjang `r_blok = max(r_blok, r_baru)`. Kalau tidak, buka blok baru. Kenapa cukup cek blok terakhir: setelah urut `l`, blok lama berakhir lebih kiri.

**Kapan:** “gabungkan rentang”, union panjang. Bukan untuk memilih subset lepas — itu activity (urut `r`).

**Proses:** `[1,5], [2,3], [6,8], [8,10], [15,18]`. Sentuh digabung.

```text
blok = [1,5]
[2,3]  2<=5  r = max(5,3)=5
[6,8]  blok baru
[8,10] r = 10
[15,18] blok baru
hasil [1,5] [6,10] [15,18]
```

Tanpa `max`: `[1,5]` ketemu `[2,3]` menjadi `[1,3]` — lubang palsu. Panjang union inklusif: `5+5+4 = 14`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<pair<ll, ll>> merge_interval(vector<pair<ll, ll>> a) {
    if (a.empty()) return {};
    sort(a.begin(), a.end());
    vector<pair<ll, ll>> res;
    res.push_back(a[0]);
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i].first <= res.back().second)
            res.back().second = max(res.back().second, a[i].second);
        else res.push_back(a[i]);
    }
    return res;
}

ll panjang_union_inklusif(const vector<pair<ll, ll>>& blok) {
    ll s = 0;
    for (auto [l, r] : blok) s += r - l + 1;
    return s;
}

int main() {
    FASTIO;
    auto b = merge_interval({{1, 5}, {2, 3}, {6, 8}, {8, 10}, {15, 18}});
    for (auto [l, r] : b) cout << l << ' ' << r << '\n';
    cout << panjang_union_inklusif(b) << '\n'; // 14
    return 0;
}
```

**Jebakan:**
1. `r_blok = r_baru` tanpa `max`.
2. Syarat `l < r_blok` padahal soal menggabungkan sentuhan.
3. Array kosong.
4. `r < l` interval terbalik tidak dibersihkan.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Menutup segmen

**Teori:** Tutupi `[S, T]` dengan interval yang sudah ada, pakai sebanyak mungkin sedikit. Greedy jangkauan: dari titik `sampai` yang sudah tertutup, di antara interval yang `l <= sampai`, pilih yang `r` **paling jauh**, lompat ke sana. Analoginya Wi-Fi di jalan. Kenapa benar: semua kandidat yang bisa dipakai sekarang setara untuk menutup titik `sampai`; yang `r` lebih jauh mendominasi.

**Kapan:** jump game, video stitching, minimum patch. Jangan ambil interval **pertama** yang muat. Kalau interval boleh digeser bebas, rumusnya lain.

**Proses:** tutup `[0, 8]`. Interval `[0,2], [1,5], [3,6], [4,9], [7,10]`.

```text
sampai=0 → [0,2] terjauh=2   hit=1
sampai=2 → [1,5] terjauh=5   hit=2
sampai=5 → [4,9] terjauh=9   hit=3 >= 8 selesai
```

Lubang: buang `[1,5]` dan `[3,6]`. Dari 2 tidak ada yang maju. Kembalikan `-1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int cover_interval(vector<pair<ll, ll>> a, ll S, ll T) {
    sort(a.begin(), a.end());
    int n = (int)a.size();
    int i = 0, hit = 0;
    ll sampai = S;
    while (sampai < T) {
        ll terjauh = sampai;
        while (i < n && a[i].first <= sampai) {
            terjauh = max(terjauh, a[i].second);
            i++;
        }
        if (terjauh == sampai) return -1;
        sampai = terjauh;
        hit++;
    }
    return hit;
}

int main() {
    FASTIO;
    vector<pair<ll, ll>> a = {{0, 2}, {1, 5}, {3, 6}, {4, 9}, {7, 10}};
    cout << cover_interval(a, 0, 8) << '\n'; // 3
    cout << cover_interval({{0, 2}, {4, 9}}, 0, 8) << '\n'; // -1
    return 0;
}
```

Penunjuk `i` **hanya maju**. Reset `i` tiap putaran membuat `O(n^2)`.

**Jebakan:**
1. Lupa `-1` lalu loop tak hingga.
2. Mengambil interval pertama.
3. Model kontinu versus bulat (`r+1`).
4. `S > T`.

**Kompleksitas:** `O(n log n)` sort plus `O(n)` sapuan.

---

## Ruangan minimum

**Teori:** Semua interval **harus** dijadwalkan. Berapa ruang minimum? Jawaban = **kedalaman maksimum** irisan. Sapuan event: `+1` di `l`, `-1` di `r`. Heap: urut `l`, simpan `r` yang sedang jalan. Analoginya lift: puncak penumpang = masuk minus keluar sampai saat itu.

Ini **bukan** activity selection. Activity memilih subset. Di sini semua wajib masuk. DP tidak membantu menghitung kedalaman; sapuan cukup. DP baru muncul jika tiap interval boleh ditolak dengan penalti.

**Kapan:** “berapa ruang rapat”, “minimum platform”. Bukan “pilih subset terbesar”.

**Proses:** `[1,4], [2,5], [3,6], [7,8]`. Tertutup, sentuh = tabrak, proses `+1` sebelum `-1`.

```text
t=1 +1 hidup=1 maks=1
t=2 +1 hidup=2 maks=2
t=3 +1 hidup=3 maks=3
t=4 -1 hidup=2
...
t=7 +1 hidup=1
```

Jawaban 3. `[1,4]` dan `[4,7]` tertutup butuh 2 ruang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int ruang_min_tertutup(const vector<pair<ll, ll>>& a) {
    vector<pair<ll, int>> ev;
    for (auto [l, r] : a) {
        ev.push_back({l, +1});
        ev.push_back({r, -1});
    }
    sort(ev.begin(), ev.end(), [](auto& x, auto& y) {
        if (x.first != y.first) return x.first < y.first;
        return x.second > y.second;
    });
    int hidup = 0, maks = 0;
    for (auto [t, d] : ev) {
        hidup += d;
        maks = max(maks, hidup);
    }
    return maks;
}

int ruang_min_heap(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    int maks = 0;
    for (auto [l, r] : a) {
        while (!pq.empty() && pq.top() < l) pq.pop();
        pq.push(r);
        maks = max(maks, (int)pq.size());
    }
    return maks;
}

int main() {
    FASTIO;
    vector<pair<ll, ll>> a = {{1, 4}, {2, 5}, {3, 6}, {7, 8}};
    cout << ruang_min_tertutup(a) << '\n'; // 3
    cout << ruang_min_heap(a) << '\n';     // 3
    cout << ruang_min_tertutup({{1, 4}, {4, 7}}) << '\n'; // 2
    return 0;
}
```

Kalau model `[l,r)` sentuh boleh: proses `-1` sebelum `+1`, heap `pq.top() <= l`.

**Jebakan:**
1. Urutan event saat waktu sama.
2. `priority_queue` default max-heap.
3. Menghitung `n` interval sebagai `n` ruang.
4. Menjawab activity (subset) padahal soal minta semua masuk.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Fractional knapsack

**Teori:** Barang boleh dipotong. Ambil rasio terbesar dulu, isi penuh, sisanya potong. Exchange: menukar satu gram barang mahal dengan satu gram barang murah menaikkan nilai. 0-1 **tidak** boleh potong — greedy rasio bisa salah, lihat [kapan-dp.md](kapan-dp.md).

**Kapan:** “boleh pecah”, minyak / serbuk. Jangan untuk barang utuh. Jangan sort `nilai` saja.

**Proses:** `W = 5`, `(w,v) = (2,10), (3,12), (4,16)` rasio `5, 4, 4`.

```text
ambil (2,10) penuh, sisa 3
ambil (3,12) penuh, sisa 0
nilai = 22
```

Ambil `(4,16)` dulu lalu potong `(2,10)` → 21, lebih buruk.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

double fraksional(vector<ll> w, vector<ll> v, ll W) {
    int n = (int)w.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return v[i] * w[j] > v[j] * w[i];
    });
    double nilai = 0;
    for (int i : idx) {
        if (W == 0) break;
        ll ambil = min(W, w[i]);
        nilai += (double)v[i] * ambil / w[i];
        W -= ambil;
    }
    return nilai;
}

int main() {
    FASTIO;
    cout << fixed << setprecision(6);
    cout << fraksional({2, 3, 4}, {10, 12, 16}, 5) << '\n'; // 22
    cout << fraksional({5}, {10}, 3) << '\n';               // 6
    return 0;
}
```

**Jebakan:**
1. Banding rasio `double`.
2. Overflow kali silang.
3. Memakai algoritma ini untuk 0-1.
4. `w[i] = 0`.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Penjadwalan deadline

**Teori:** Tiap pekerjaan `(durasi t, deadline d)`, satu mesin, mulai dari 0. Varian: selesaikan sebanyak mungkin sebelum deadline — urut `d` naik, ambil jika masih muat; jika tidak, buang pekerjaan terpanjang di antara yang sudah diambil (heap). Analoginya PR: kerjakan yang dikumpul paling cepat, tetapi kalau macet, batalkan PR paling gemuk.

Tanpa heap “buang terpanjang”, greedy naif bisa kalah. Itu masih greedy (exchange pada himpunan terpilih), bukan DP. DP muncul jika tiap pekerjaan punya nilai berbeda yang tidak monoton terhadap durasi.

**Kapan:** deadline plus satu mesin. Penalti linier aneh — cek exchange; sering jadi DP. Waktu rilis plus deadline = NP-hard, `n` kecil.

**Proses:** `(t,d)` = `(4,5), (3,5), (2,5)`.

Tanpa ganti:

```text
ambil 4 waktu=4<=5
3 → 7>5 skip
2 → 6>5 skip   jawaban 1
```

Dengan heap: saat 3 gagal, buang 4, waktu=3, 3 muat. Lalu 2: waktu=5. Jawaban 2: `{3,2}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int banyak_tepat_waktu(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end()); // {deadline, durasi}
    priority_queue<ll> pq;
    ll waktu = 0;
    for (auto [d, t] : a) {
        waktu += t;
        pq.push(t);
        if (waktu > d) {
            waktu -= pq.top();
            pq.pop();
        }
    }
    return (int)pq.size();
}

int main() {
    FASTIO;
    cout << banyak_tepat_waktu({{5, 4}, {5, 3}, {5, 2}}) << '\n'; // 2
    cout << banyak_tepat_waktu({{3, 2}, {3, 2}, {4, 1}, {5, 3}}) << '\n';
    return 0;
}
```

**Jebakan:**
1. Heap min padahal mau buang terpanjang.
2. Menambah `waktu` setelah pop salah.
3. `t > d` untuk satu pekerjaan: tetap dicoba, lalu dibuang.
4. Mengganti heap dengan DP `n = 1e5` tanpa perlu.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Peta keputusan

```text
Soal interval
├── sebanyak mungkin saling lepas     → urut r
├── gabungkan / union                 → urut l, merge + max
├── tutupi [S,T] minimum potong       → greedy jangkauan
├── semua harus masuk, berapa ruang   → event / heap
└── ada bobot                         → DP, kapan-dp.md

Soal jadwal satu mesin
├── Σ C_i                             → SPT
├── Σ w_i C_i                         → t/w, kali silang ll
├── sebanyak mungkin sebelum deadline → urut d + heap
└── ada r_i aneh                      → waspada, sering bukan greedy murni
```

| urutan | untuk |
| --- | --- |
| `r` naik | pilih subset lepas |
| `l` naik | merge, cover, ruang |
| `t` naik | SPT |
| `t/w` naik | Smith |
| rasio `v/w` | fractional saja |

Ringkasan: exchange dulu, baru sort. Interval: `r` untuk memilih, `l` untuk menyapu. Bobot = alarm DP.

Lanjut ke [konstruktif.md](konstruktif.md) jika soal minta objek, atau [../09-dp/README.md](../09-dp/README.md) jika exchange rusak.
