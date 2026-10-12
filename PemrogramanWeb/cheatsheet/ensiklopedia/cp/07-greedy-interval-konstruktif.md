# 07 — Greedy, interval, dan konstruktif

[← 06 rekursi](06-rekursi-subset-backtrack-memo.md) · [Indeks](README.md) · [Lanjut: sieve & modular →](08-number-sieve-gcd-modular.md)

Kurikulum: folder **06 — Greedy** di `DAFTAR-MATERI` (Day 071, 072, 075), plus konstruktif / invariant yang menempel di blok yang sama.

Latihan harian: `KULIAH/ComProgLearning/CP` Day-71 sampai Day-82.

> **Ide satu kalimat:** greedy mengambil pilihan yang kelihatan terbaik sekarang, dan itu sah hanya jika menukar pilihan itu dengan yang “lebih greedy” tidak pernah memperburuk jawaban.

## Daftar isi

- [Prinsip greedy](#prinsip-greedy)
- [Exchange argument](#exchange-argument)
- [Greedy versus DP](#greedy-versus-dp)
- [Waktu proses terpendek (SPT)](#waktu-proses-terpendek-spt)
- [Activity selection](#activity-selection)
- [Menggabungkan interval](#menggabungkan-interval)
- [Menutup segmen (interval covering)](#menutup-segmen-interval-covering)
- [Ruangan minimum](#ruangan-minimum)
- [Fractional knapsack](#fractional-knapsack)
- [Penjadwalan deadline](#penjadwalan-deadline)
- [Huffman: ide greedy plus heap](#huffman-ide-greedy-plus-heap)
- [Algoritma konstruktif](#algoritma-konstruktif)
- [Invariant dan paritas](#invariant-dan-paritas)
- [Stress test untuk membantah greedy](#stress-test-untuk-membantah-greedy)
- [Peta keputusan bab ini](#peta-keputusan-bab-ini)
- [Ringkasan folder 06](#ringkasan-folder-06)

## Prinsip greedy

**Teori:** greedy membangun jawaban langkah demi langkah. Di tiap langkah ia memilih kandidat yang paling menjanjikan menurut satu kriteria, lalu tidak menyesal. Dua syarat klasik: **greedy choice** (ada jawaban optimal yang memuat pilihan greedy pertama) dan **optimal substructure** (sisa soal setelah pilihan itu juga soal optimal yang sama bentuknya). Analoginya antrean kasir: kalau tujuanmu meminimalkan jumlah waktu tunggu, layani yang belanjanya paling sedikit dulu. Itu bukan “terasa adil”, itu rumus.

**Kapan:** kriteria lokal bisa dibuktikan (exchange argument), atau soal klasik yang sudah mapan: activity selection, fractional knapsack, Huffman, Kruskal, Dijkstra (bobot ≥ 0). Jangan hanya karena “ambil maksimum kelihatan benar”. Jangan jika ada kapasitas plus nilai yang saling tukar — itu knapsack DP.

**Proses:** tiga pekerjaan durasi `5, 1, 3`. Satu mesin, minimalkan jumlah waktu selesai `Σ C_i`.

Urutan 5, 1, 3:

```
C = 5, 6, 9
ΣC = 20
```

Urutan 1, 3, 5 (SPT):

```
C = 1, 4, 9
ΣC = 14
```

Urutan 3, 1, 5:

```
C = 3, 4, 9
ΣC = 16  (lebih buruk dari SPT)
```

Greedy “terpendek dulu” menang di contoh ini. Di seksi berikut kita buktikan kenapa selalu.

**Kode:** kerangka: sort menurut kriteria, sapu sekali.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll jumlah_selesai(vector<ll> dur) {
    sort(dur.begin(), dur.end());          // SPT
    ll waktu = 0, sum = 0;
    for (ll t : dur) {
        waktu += t;
        sum += waktu;
    }
    return sum;
}

int main() {
    cout << jumlah_selesai({5, 1, 3}) << '\n'; // 14
    cout << jumlah_selesai({2, 2, 2}) << '\n'; // 12
    return 0;
}
```

`{2,2,2}`: C = 2,4,6 jumlah 12. Semua urutan sama karena durasi identik.

**Jebakan:** meniru “ambil terbesar” dari soal lain; tidak menulis bukti / counterexample; overflow `Σ C_i` — `n = 1e5`, `t_i = 1e9` → pakai `ll`.

**Kompleksitas:** sort `O(n log n)`, sapuan `O(n)`, memori `O(n)`.

---

## Exchange argument

**Teori:** cara membuktikan greedy. Empat langkah. (1) Ambil jawaban optimal yang **paling mirip** kriteria greedy. (2) Jika ia menyalahi kriteria, ada dua elemen berdampingan yang urutannya “salah”. (3) Tukar keduanya. (4) Biaya tidak memburuk, kontradiksi dengan “paling mirip”, atau kita bisa mengurutkan optimal sampai identik dengan greedy. Analoginya: kalau dua orang di antrean tertukar dan total tunggu tidak naik setelah dikembalikan ke urutan greedy, maka urutan greedy aman.

Kenapa **berdampingan**: menukar dua yang berjauhan mengubah banyak waktu mulai. Dua tetangga hanya saling menukar, jumlah durasi blok itu tetap, sisa antrean tidak berubah.

**Kapan:** kamu punya kriteria sort (`r` naik, rasio `t/w`, string gabungan). Wajib sebelum percaya komparator. Tidak dipakai untuk soal yang kriteria lokalnya tidak ada — di situ DP / search.

**Proses:** SPT, dua pekerjaan berdampingan `i` lalu `j`, durasi `t_i, t_j`. Waktu mulai blok = `T`.

Urutan i lalu j:

```
C_i = T + t_i
C_j = T + t_i + t_j
jumlah blok = 2T + 2 t_i + t_j
```

Urutan j lalu i:

```
jumlah blok = 2T + 2 t_j + t_i
```

Selisih (i dulu minus j dulu) = `t_i - t_j`. Jika `t_i > t_j`, menukar agar yang pendek dulu **menurunkan** jumlah. Jadi setiap inversi “panjang sebelum pendek” bisa diperbaiki. Optimal tanpa inversi = terurut naik.

Contoh angka: `T = 10`, `t_i = 5`, `t_j = 2`.

```
i lalu j: C = 15, 17  jumlah 32
j lalu i: C = 12, 17  jumlah 29
hemat 3 = 5-2
```

**Kode:** turunkan komparator dari dua elemen, bukan menebak.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Job {
    ll t, w; // durasi, bobot
};

// minimalkan Σ w_i * C_i  →  t[i]/w[i] naik
// bukti dua elemen: t_i*w_j ? t_j*w_i  (hindari bagi)
bool lebih_dulu(const Job& x, const Job& y) {
    return x.t * y.w < y.t * x.w;
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
    vector<Job> a = {{5, 1}, {2, 1}, {3, 2}};
    cout << biaya(a) << '\n';
    // urut rasio t/w: (3,2)=1.5, (2,1)=2, (5,1)=5
    // C=3,5,10  ΣwC = 2*3 + 1*5 + 1*10 = 21
    return 0;
}
```

Cek manual urutan lain `(2,1),(3,2),(5,1)`: C=2,5,10, biaya `1*2+2*5+1*10=22` lebih buruk.

**Jebakan:** komparator pakai `double` bagi (`t/w`) — presisi; `int*int` overflow, wajib `ll`; `<=` di sort C++ melanggar *strict weak ordering* → crash / urutan aneh; menukar dua elemen **jauh** lalu menghitung seolah hanya dua yang berubah.

**Kompleksitas:** bukti `O(1)` di kertas. Kode sort `O(n log n)`.

---

## Greedy versus DP

**Teori:** keduanya memakai optimal substructure. Bedanya: greedy **membuang** semua pilihan kecuali satu, DP **mencoba semua** pilihan pada tiap state. Analoginya persimpangan: greedy pilih jalan yang kelihatan paling pendek sekarang; DP menghitung jarak lewat semua jalan lalu ambil min. Greedy salah ketika pilihan lokal menutup jalan yang belakangan jauh lebih hemat.

**Kapan pakai greedy:** bukti exchange ada, atau soal klasik, atau setelah stress test tidak ketemu counterexample **dan** n besar memaksa `O(n log n)`. **Kapan DP:** `n ≤ 20` bitmask, `n ≤ 100` plus kapasitas, “pilih paling banyak K dengan trade-off”, atau kamu menemukan satu counterexample.

**Proses:** 0-1 knapsack, barang `(berat, nilai) = (2,3), (3,4), (4,8)`, `W = 5`.

Greedy rasio nilai/berat: `4/3≈1.33`, `8/4=2`, `3/2=1.5` → ambil (4,8) dulu, sisa 1, tidak muat. Nilai 8.

Optimal: (2,3)+(3,4)=7? Lebih buruk. Tunggu, 8 menang. Ganti angka: `(2,3), (3,4), (4,5)`, `W=5`.

Rasio: `3/2=1.5`, `4/3≈1.33`, `5/4=1.25` → greedy ambil (2,3) lalu (3,4), nilai 7. Optimal juga 7. Belum membantah.

Counterexample klasik: `(1,1), (3,4), W=3`. Rasio: `1/1=1`, `4/3≈1.33` → greedy ambil (3,4)=4. Optimal 4. Masih pas.

Pakai: `(2,3), (3,4), W=3`. Rasio `1.5` vs `1.33` → greedy (2,3)=3. Optimal (3,4)=4. **Greedy kalah.**

Itu alasan 0-1 knapsack bukan greedy. Fractional (boleh potong) baru greedy.

Sinyal dari batasan:

| batasan | arah pikir |
| --- | --- |
| `n ≤ 20` | brute / bitmask, greedy sering umpan |
| `n ≤ 100`, ada `W ≤ 1e5` | DP knapsack |
| `n ≤ 1e5`, tidak ada kapasitas aneh | greedy / sort / struktur |
| jawaban monoton terhadap X | binary search on answer |

**Kode:** bandingkan greedy rasio vs DP 0-1 pada satu contoh.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll greedy_01(vector<ll> w, vector<ll> v, ll W) {
    int n = (int)w.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return v[i] * w[j] > v[j] * w[i];
    });
    ll sisa = W, nilai = 0;
    for (int i : idx) {
        if (w[i] <= sisa) {
            sisa -= w[i];
            nilai += v[i];
        }
    }
    return nilai;
}

ll dp_01(const vector<ll>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int cap = W; cap >= w[i]; cap--)
            dp[cap] = max(dp[cap], v[i] + dp[cap - (int)w[i]]);
    return dp[W];
}

int main() {
    vector<ll> w = {2, 3}, v = {3, 4};
    cout << "greedy " << greedy_01(w, v, 3)
         << " dp " << dp_01(w, v, 3) << '\n'; // 3 vs 4
    return 0;
}
```

**Jebakan:** lolos sampel lalu percaya greedy; mencontoh knapsack fraksional untuk 0-1; mengabaikan batasan `n` sebagai petunjuk penulis soal.

**Kompleksitas:** membedakan pendekatan adalah `O(1)` di kepala. Salah pilih algoritma = TLE atau WA, bukan “hampir benar”.

---

## Waktu proses terpendek (SPT)

**Teori:** satu mesin, semua pekerjaan tersedia di waktu 0, minimalkan `Σ C_i` atau rata-rata waktu selesai. Urutkan durasi naik. Sudah dibuktikan di exchange. Analoginya antrean printer: cetak yang tipis dulu supaya banyak orang selesai cepat.

**Kapan:** satu sumber daya, tidak ada deadline / prioritas lain. Ada bobot `w_i` → sort `t/w` (Smith's rule), bukan `t` saja. Ada waktu rilis `r_i` → SPT murni bisa salah, sering DP atau heap “yang sudah datang”.

**Proses:** durasi `8, 1, 4, 2`.

```
urut: 1, 2, 4, 8
C   : 1, 3, 7, 15
ΣC  = 26
```

Urutan terburuk (LPT): `8,4,2,1` → C=`8,12,14,15` Σ=`49`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    auto [sum, C] = spt({8, 1, 4, 2});
    cout << sum << '\n';                   // 26
    for (ll x : C) cout << x << ' ';
    cout << '\n';                          // 15 1 7 3
    return 0;
}
```

**Jebakan:** sort nilai saja lalu kehilangan indeks pekerjaan; `t` sama, urutan tidak stabil — biasanya tidak masalah untuk ΣC, masalah jika soal minta urutan leksikografis; `r_i` diabaikan.

**Kompleksitas:** `O(n log n)` waktu, `O(n)` memori.

---

## Activity selection

**Teori:** pilih sebanyak mungkin interval saling lepas. Kriteria: **urut ujung `r` naik**, ambil jika `l` tidak menabrak interval terakhir yang diambil. Intuisi: yang selesai paling awal menyisakan sisa waktu terbanyak. Exchange: jika optimal mengambil interval yang selesai lebih lambat sebagai yang pertama, ganti dengan yang `r` lebih kecil — ia muat (karena berakhir lebih awal) dan menyisakan ruang ≥ semula.

**Kapan:** “sebanyak mungkin kegiatan / rapat / segmen tanpa tabrakan”. “Buang sesedikit mungkin” = `n - jawaban greedy`. Ada **bobot** → bukan greedy, DP + `lower_bound`. Banyak mesin / ruangan → seksi ruangan minimum.

**Proses:** interval (tertutup) `[1,4], [2,3], [3,5], [0,6], [5,7], [8,9], [5,9]`.

Urut `r`: `[2,3], [1,4], [3,5], [0,6], [5,7], [8,9], [5,9]`.

```
ambil [2,3]   akhir=3
[1,4] l=1 tidak > 3  skip
[3,5] 3 > 3? tidak (tertutup, sentuh = tabrak) skip
[0,6] skip
[5,7] 5>3  ambil  akhir=7
[8,9] 8>7  ambil  akhir=9
[5,9] skip
```

Jawaban 3: `[2,3], [5,7], [8,9]`.

Tiga kriteria salah:

| kriteria | contoh | greedy | optimal |
| --- | --- | ---: | ---: |
| urut `l` | `[1,100],[2,3],[4,5]` | 1 | 2 |
| durasi pendek | `[1,10],[9,12],[11,20]` | 1 | 2 |
| konflik paling sedikit | susunan bertingkat | sering < | lebih |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int activity_tertutup(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });
    int hit = 0;
    ll akhir = LLONG_MIN;                  // BUKAN 0
    for (auto [l, r] : a) {
        if (l > akhir) {                   // tertutup [l,r]
            hit++;
            akhir = r;
        }
    }
    return hit;
}

int activity_setengah(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return x.second < y.second;
    });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) {
        if (l >= akhir) {                  // [l,r)
            hit++;
            akhir = r;
        }
    }
    return hit;
}

int main() {
    vector<pair<ll, ll>> a = {
        {1, 4}, {2, 3}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}
    };
    cout << activity_tertutup(a) << '\n';  // 3
    cout << activity_setengah({{1, 5}, {5, 9}}) << '\n'; // 2, sentuh boleh
    cout << activity_tertutup({{1, 5}, {5, 9}}) << '\n'; // 1, sentuh tabrak
    return 0;
}
```

**Jebakan:** `akhir = 0` padahal ada interval negatif; `[l,r]` vs `[l,r)` satu karakter `>` vs `>=`; urut `l` karena “kebiasaan”; interval `[1,10]` termuat di dalam lain — urut `r` tetap benar, urut durasi tidak.

**Kompleksitas:** `O(n log n)` sort, `O(n)` sapuan, `O(n)` memori.

---

## Menggabungkan interval

**Teori:** satukan interval yang beririsan atau bersentuhan menjadi blok. Urut menurut `l`. Jaga blok terakhir. Jika interval baru `l ≤ r_blok` (atau `<` tergantung sentuh), perpanjang `r_blok = max(r_blok, r_baru)`. Kalau tidak, buka blok baru. Kenapa cukup cek blok terakhir: setelah urut `l`, blok-blok lama berakhir lebih kiri, tidak mungkin menyentuh interval baru jika blok terakhir tidak.

**Kapan:** “gabungkan rentang”, “berapa blok terpisah”, union panjang. Bukan untuk memilih subset lepas — itu activity (urut `r`).

**Proses:** `[1,5], [2,3], [6,8], [8,10], [15,18]`. Sentuh digabung.

Urut `l` sudah hampir terurut.

```
blok = [1,5]
[2,3]  2≤5  r = max(5,3)=5     tetap [1,5]
[6,8]  6>5  blok baru          [1,5] [6,8]
[8,10] 8≤8  r = max(8,10)=10   [1,5] [6,10]
[15,18] 15>10 blok baru        [1,5] [6,10] [15,18]
```

Tanpa `max`: `[1,5]` ketemu `[2,3]` menjadi `[1,3]` — **salah**, lubang palsu.

Panjang union (bulat inklusif): `(5-1+1)+(10-6+1)+(18-15+1)=5+5+4=14`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<ll, ll>> merge_interval(vector<pair<ll, ll>> a) {
    if (a.empty()) return {};
    sort(a.begin(), a.end());              // urut l, lalu r
    vector<pair<ll, ll>> res;
    res.push_back(a[0]);
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i].first <= res.back().second) {
            res.back().second = max(res.back().second, a[i].second);
        } else {
            res.push_back(a[i]);
        }
    }
    return res;
}

ll panjang_union_inklusif(const vector<pair<ll, ll>>& blok) {
    ll s = 0;
    for (auto [l, r] : blok) s += r - l + 1;
    return s;
}

int main() {
    auto b = merge_interval({{1, 5}, {2, 3}, {6, 8}, {8, 10}, {15, 18}});
    for (auto [l, r] : b) cout << l << ' ' << r << '\n';
    // 1 5
    // 6 10
    // 15 18
    cout << panjang_union_inklusif(b) << '\n'; // 14
    return 0;
}
```

**Jebakan:** `r_blok = r_baru` tanpa `max`; syarat `l < r_blok` padahal soal menggabungkan sentuhan; array kosong; `r < l` interval terbalik tidak dibersihkan.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Menutup segmen (interval covering)

**Teori:** tutupi `[S, T]` dengan interval yang sudah ada, pakai **sebanyak mungkin sedikit**. Greedy jangkauan: dari titik `sampai` yang sudah tertutup, di antara interval yang `l ≤ sampai`, pilih yang `r` **paling jauh**, lompat ke sana. Analoginya Wi-Fi di jalan: dari posisi sekarang, pilih hotspot yang menjangkau paling kanan, asalkan sinyalnya masih ke sini. Kenapa benar: semua kandidat yang bisa dipakai sekarang setara untuk menutup titik `sampai`; yang `r` lebih jauh mendominasi.

**Kapan:** jump game, video stitching, “minimum tap / patch / segment untuk menutup [0,T]”. Interval ditempatkan bebas (boleh geser) biasanya rumus lain. Jangan ambil interval **pertama** yang muat.

**Proses:** tutup `[0, 8]`. Interval `[0,2], [1,5], [3,6], [4,9], [7,10]`.

```
sampai = 0
kandidat l≤0: [0,2] terjauh=2   hit=1  sampai=2
kandidat l≤2: [0,2][1,5] terjauh=5  hit=2  sampai=5
kandidat l≤5: [1,5][3,6][4,9] terjauh=9  hit=3  sampai=9 ≥ 8 selesai
```

Jawaban 3. Kalau ambil “pertama muat” dari 0: `[0,2]` lalu `[3,6]` lalu `[7,10]` juga 3, kebetulan. Ubah `[4,9]` jadi satu-satunya yang melewati 8 dari 5 — tetap 3.

Lubang: buang `[1,5]` dan `[3,6]`. Dari 2 tidak ada yang `l≤2` dan `r>2` selain `[0,2]`. `terjauh==sampai` → mustahil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cover_interval(vector<pair<ll, ll>> a, ll S, ll T) {
    sort(a.begin(), a.end());              // urut l
    int n = (int)a.size();
    int i = 0, hit = 0;
    ll sampai = S;
    while (sampai < T) {
        ll terjauh = sampai;
        while (i < n && a[i].first <= sampai) {
            terjauh = max(terjauh, a[i].second);
            i++;
        }
        if (terjauh == sampai) return -1;  // lubang
        sampai = terjauh;
        hit++;
    }
    return hit;
}

int main() {
    vector<pair<ll, ll>> a = {{0, 2}, {1, 5}, {3, 6}, {4, 9}, {7, 10}};
    cout << cover_interval(a, 0, 8) << '\n';   // 3
    cout << cover_interval({{0, 2}, {4, 9}}, 0, 8) << '\n'; // -1
    return 0;
}
```

Penunjuk `i` **hanya maju**. Reset `i` tiap putaran membuat `O(n^2)` dan TLE, serta logikanya tetap sama karena `sampai` membesar.

**Jebakan:** lupa `-1` → loop tak hingga jika kamu tidak naik `sampai`; mengambil interval pertama; model kontinu vs bulat (`r+1` kadang perlu); `S > T` edge.

**Kompleksitas:** `O(n log n)` sort + `O(n)` sapuan.

---

## Ruangan minimum

**Teori:** semua interval **harus** dijadwalkan. Berapa ruang / mesin / ruang kelas minimum? Jawaban = **kedalaman maksimum** irisan. Sapuan event: `+1` di `l`, `-1` di `r` (urut waktu; jika `l==r` dan setengah terbuka, proses `-1` dulu). Heap: urut `l`, simpan `r` yang sedang jalan, pop yang sudah selesai, ukuran heap = ruang terpakai. Analoginya lift: puncak penumpang = jumlah masuk minus keluar sampai saat itu.

**Kapan:** “berapa ruang rapat”, “minimum platform kereta”, “chromatic number interval graph”. Bukan “pilih subset terbesar” — itu activity, jawaban ≤ n, sering jauh lebih kecil.

**Proses:** `[1,4], [2,5], [3,6], [7,8]`. Tertutup, sentuh tidak berbagi ruang? `[1,4]` dan `[4,7]` — jika tertutup, butuh 2. Di contoh tidak ada sentuh.

Event (tertutup, keluar dulu saat waktu sama — hati-hati; jika sentuh tabrak, keluar **tidak** boleh dulu). Kita pakai model: sentuh = tabrak, jadi di waktu `t` masuk diproses sebelum keluar? Tidak: jika `[1,4][4,7]` tabrak, di `t=4` keduanya hidup. Proses `+1` sebelum `-1`.

```
t=1 +1  hidup=1  maks=1
t=2 +1  hidup=2  maks=2
t=3 +1  hidup=3  maks=3
t=4 -1  hidup=2
t=5 -1  hidup=1
t=6 -1  hidup=0
t=7 +1  hidup=1  maks=3
t=8 -1  hidup=0
```

Jawaban 3. Interval keempat tidak menambah puncak.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ruang_min_tertutup(const vector<pair<ll, ll>>& a) {
    vector<pair<ll, int>> ev;
    for (auto [l, r] : a) {
        ev.push_back({l, +1});
        ev.push_back({r, -1});
    }
    // sentuh tabrak: di waktu sama, +1 dulu ( +1 > -1 → sort descending tipe? )
    // pair (waktu, tipe): kita ingin +1 sebelum -1, jadi sort tipe descending
    sort(ev.begin(), ev.end(), [](auto& x, auto& y) {
        if (x.first != y.first) return x.first < y.first;
        return x.second > y.second;        // +1 sebelum -1
    });
    int hidup = 0, maks = 0;
    for (auto [t, d] : ev) {
        hidup += d;
        maks = max(maks, hidup);
    }
    return maks;
}

int ruang_min_heap(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end());              // urut l
    priority_queue<ll, vector<ll>, greater<ll>> pq; // r aktif
    int maks = 0;
    for (auto [l, r] : a) {
        while (!pq.empty() && pq.top() < l) pq.pop(); // tertutup: < bukan <=
        pq.push(r);
        maks = max(maks, (int)pq.size());
    }
    return maks;
}

int main() {
    vector<pair<ll, ll>> a = {{1, 4}, {2, 5}, {3, 6}, {7, 8}};
    cout << ruang_min_tertutup(a) << '\n'; // 3
    cout << ruang_min_heap(a) << '\n';     // 3
    cout << ruang_min_tertutup({{1, 4}, {4, 7}}) << '\n'; // 2
    return 0;
}
```

Kalau model `[l,r)` sentuh boleh: proses `-1` sebelum `+1`, dan heap `pq.top() <= l`.

**Jebakan:** urutan event saat waktu sama; `priority_queue` default max-heap — pakai `greater`; menghitung `n` interval sebagai `n` ruang.

**Kompleksitas:** event `O(n log n)`, heap `O(n log n)`, memori `O(n)`.

---

## Fractional knapsack

**Teori:** barang boleh dipotong. Ambil rasio `nilai/berat` terbesar dulu, isi penuh, sisanya potong. Exchange: menukar satu gram barang mahal dengan satu gram barang murah menaikkan nilai. 0-1 **tidak** boleh potong — greedy rasio bisa salah (seksi greedy vs DP).

**Kapan:** “boleh pecah”, minyak / serbuk / proporsi. Jangan untuk barang utuh. Jangan sort `nilai` saja (barang berat mahal tapi rasio jelek).

**Proses:** `W = 5`, barang `(w,v) = (2,10), (3,12), (4,16)` rasio `5, 4, 4`.

```
ambil (2,10) penuh, sisa 3
ambil (3,12) penuh, sisa 0
nilai = 22
```

Kalau ambil (4,16) dulu rasio 4, sisa 1, potong (2,10) → 5, total 21 < 22.

Dua rasio sama 4: boleh pilih mana saja, sisa 3 muat tepat salah satunya.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double fraksional(vector<ll> w, vector<ll> v, ll W) {
    int n = (int)w.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return v[i] * w[j] > v[j] * w[i];  // tanpa bagi
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
    cout << fixed << setprecision(6);
    cout << fraksional({2, 3, 4}, {10, 12, 16}, 5) << '\n'; // 22
    cout << fraksional({5}, {10}, 3) << '\n';               // 6
    return 0;
}
```

**Jebakan:** banding rasio pakai `double` (`1/3` vs `2/6`); overflow `v[i]*w[j]`; memakai algoritma ini untuk 0-1; `w[i]=0`.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Penjadwalan deadline

**Teori:** tiap pekerjaan `(durasi t, deadline d)`, satu mesin, mulai dari 0. Varian umum: **selesaikan sebanyak mungkin sebelum deadline** — urut `d` naik, ambil jika masih muat; jika tidak muat, buang pekerjaan terpanjang di antara yang sudah diambil (heap). Varian lain: semua harus masuk, minimalkan keterlambatan maksimum — juga urut `d` (Jackson’s rule). Analoginya PR: kerjakan yang dikumpul paling cepat, tetapi kalau macet, batalkan PR paling gemuk.

**Kapan:** deadline + satu mesin. Ada penalti linier berbeda-beda — cek apakah exchange masih jalan; sering jadi DP. Waktu rilis + deadline = NP-hard, `n` kecil.

**Proses:** pekerjaan `(t,d)`: `(2,3), (2,3), (3,5), (1,4)`.

Urut `d`: `(2,3), (2,3), (1,4), (3,5)`.

```
ambil (2,3) waktu=2 ≤3
ambil (2,3) waktu=4 >3  tidak muat
  heap durasi {2,2}, buang salah satu 2, waktu=2, lalu coba? 
  lebih sederhana versi "tanpa ganti": skip, waktu tetap 2
ambil (1,4) waktu=3 ≤4
ambil (3,5) waktu=6 >5 skip
```

Tanpa ganti: 2 pekerjaan. Dengan ganti di langkah kedua: setelah dua kali `(2,3)` gagal, buang satu, waktu 2, tetap tidak menambah yang gagal itu. Lanjut sama, 2 pekerjaan.

Contoh yang butuh “buang terpanjang”: `(4,5), (3,5), (2,5)`.

Tanpa ganti urut d sama:

```
ambil 4 waktu=4≤5
3 → waktu=7>5 skip
2 → waktu=6>5 skip   jawaban 1
```

Dengan heap: saat 3 gagal, buang 4 (lebih panjang), waktu=3, 3 muat. Lalu 2: waktu=5≤5. Jawaban 2: `{3,2}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int banyak_tepat_waktu(vector<pair<ll, ll>> a) {
    // a[i] = {deadline, durasi}
    sort(a.begin(), a.end());              // urut deadline
    priority_queue<ll> pq;                 // durasi, max-heap
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
    cout << banyak_tepat_waktu({{5, 4}, {5, 3}, {5, 2}}) << '\n'; // 2
    cout << banyak_tepat_waktu({{3, 2}, {3, 2}, {4, 1}, {5, 3}}) << '\n';
    return 0;
}
```

Pasangan di kode `{deadline, durasi}` supaya `sort` default urut `d`.

**Jebakan:** heap min padahal mau buang terpanjang; menambah `waktu` setelah pop salah; `t > d` untuk satu pekerjaan — tetap harus dicoba, lalu langsung dibuang.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Huffman: ide greedy plus heap

**Teori:** bangun pohon prefix-code biaya minimum. Selalu gabungkan dua pohon dengan frekuensi terkecil. Exchange: kode optimal punya dua simbol terjarang sebagai saudara di daun terdalam; menukar pasangan lain tidak lebih hemat. Analoginya packing kardus: satukan dua tumpukan paling ringan dulu.

**Kapan:** kompresi, “biaya gabung file / batu / slime” (varian: selalu gabung dua terkecil). Bukan untuk 0-1 knapsack. Bukan jika gabungan tidak asosiatif dengan biaya `f+g`.

**Proses:** frekuensi `A:3 B:3 C:4 D:5`.

```
heap: 3,3,4,5
gabung 3+3=6   heap: 4,5,6     biaya += 6
gabung 4+5=9   heap: 6,9       biaya += 9
gabung 6+9=15  heap: 15        biaya += 15
total 30
```

Pohon: `{A,B}` biaya 6, `{C,D}` biaya 9, akar 15. Panjang kode: A,B = 2, C,D = 2. Biaya `3*2+3*2+4*2+5*2=30`. Sama.

Jika gabung 3+4 dulu: lebih mahal (bisa dicek).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll biaya_huffman(vector<ll> f) {
    if (f.size() <= 1) return 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (ll x : f) pq.push(x);
    ll biaya = 0;
    while (pq.size() > 1) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        ll s = a + b;
        biaya += s;
        pq.push(s);
    }
    return biaya;
}

int main() {
    cout << biaya_huffman({3, 3, 4, 5}) << '\n'; // 30
    cout << biaya_huffman({1, 1, 1, 1}) << '\n'; // 8
    // 1+1=2, 1+1=2, 2+2=4  biaya 2+2+4=8
    return 0;
}
```

`{1,1,1,1}`: dua gabung 2, lalu 4, total 8. Empat simbol, pohon seimbang, panjang 2, biaya `4*2=8`.

**Jebakan:** max-heap; `n=1` biaya 0 bukan `f[0]`; overflow jumlah berulang — `ll`.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Algoritma konstruktif

**Teori:** soal minta **objek**, bukan angka: permutasi, matriks, pewarnaan, urutan operasi. Banyak jawaban benar, jadi membandingkan ke sampel tidak cukup. Tulis **pemeriksa** dulu: ukuran, rentang, syarat khusus. Lima strategi: pola dari `n` kecil, bangun `n` dari `n-1`, konstruk baku lalu perbaiki, buktikan mustahil (paritas / bound), greedy lalu tambal. Analoginya merakit furniture: cek “semua lubang terisi” sebelum memamerkan lemari.

**Kapan:** kata “construct”, “any permutation”, “print a sequence”, “yes and give example”. Jangan mengoptimalkan jika soal hanya minta salah satu yang sah. Jangan klaim `-1` tanpa menguji `n` kecil dengan brute.

**Proses:** susun `1..n` supaya `|a[i]-a[i+1]| ≠ 1`.

Coba ganjil dulu lalu genap:

```
n=5: 1 3 5 2 4     selisih 2,2,3,2  OK
n=6: 1 3 5 2 4 6   ... 5-2=3, 2-4=2, 4-6=2 OK
n=4: 1 3 2 4       3-2=1  GAGAL
```

Satu nilai `n` merusak pola. Genap dulu lalu ganjil:

```
n=4: 2 4 1 3       selisih 2,3,2  OK
n=5: 2 4 1 3 5     4-1=3, 1-3=2, 3-5=2 OK
n=2: 1 2           selisih 1  mustahil
n=3: 1 3 2         3-2=1; 2 1 3 → 1 dan 2; semua gagal
```

Mustahil: `n=2,3`. Untuk `n≥4` genap-lalu-ganjil, titik sambung genap terbesar ke 1: selisih `≥3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool sah_tidak_tetangga(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> ada(n + 1, 0);
    for (int x : a) {
        if (x < 1 || x > n || ada[x]) return false;
        ada[x] = 1;
    }
    for (int i = 0; i + 1 < n; i++)
        if (abs(a[i] - a[i + 1]) == 1) return false;
    return true;
}

vector<int> konstruk_tidak_tetangga(int n) {
    if (n == 1) return {1};
    if (n == 2 || n == 3) return {};       // mustahil
    vector<int> a;
    for (int x = 2; x <= n; x += 2) a.push_back(x);
    for (int x = 1; x <= n; x += 2) a.push_back(x);
    return a;
}

int main() {
    for (int n = 1; n <= 8; n++) {
        auto a = konstruk_tidak_tetangga(n);
        cout << n << ": ";
        if (a.empty() && n != 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for (int x : a) cout << x << ' ';
        cout << " cek=" << sah_tidak_tetangga(a) << '\n';
    }
    return 0;
}
```

Keluaran: `n=2,3` IMPOSSIBLE, `n=4` `2 4 1 3` cek=1, dst.

Pola konstruktif lain yang sering:

| pola | contoh |
| --- | --- |
| geser siklik | derangement `2,3,...,n,1` (`n≥2`) |
| belah ganjil/genap | selisih, pewarnaan |
| induk + sisipan | bangun `n` dari solusi `n-1` |
| ekstrem dulu | `n,1,n-1,2,...` |
| semua sama / berulang | kalau syarat mengizinkan |

**Jebakan:** menguji 3 nilai `n` lalu submit (gagal di titik sambung); pemeriksa lupa duplikat; mencetak `n` elemen 1-based padahal loop 0..n-2; klaim mustahil padahal `n=1` trivial.

**Kompleksitas:** konstruksi biasanya `O(n)`, pemeriksa `O(n)` atau `O(n log n)`.

---

## Invariant dan paritas

**Teori:** invariant adalah besaran yang **tidak berubah** oleh operasi soal. Jika target beda invariant dengan awal, mustahil. Yang paling sering: paritas jumlah, paritas jumlah tukar, warna papan catur, jumlah modulo `k`, XOR total. Monovariant **bergerak satu arah** (selalu turun) — dipakai untuk bukti berhenti / greedy. Analoginya puzzle 15: paritas permutasi plus kotak kosong.

**Kapan:** “operasi: tukar / geser / tambah ±1 di dua tempat”, constructive “yes/no”, game. Jangan mengandalkan invariant yang kamu belum cek di operasi — tulis Δ pada satu langkah.

**Proses:** array, operasi pilih `i`, lakukan `a[i]+=1`, `a[i+1]-=1`. Invariant: **jumlah total** tetap. Awal `{1,2,3}` jumlah 6. Target `{3,3,0}` jumlah 6, mungkin. Target `{4,4,0}` jumlah 8, mustahil.

Invariant lebih ketat: `a[0]` hanya bisa naik lewat operasi di 0? Operasi di 0: `a[0]+1, a[1]-1`. Operasi di 1: `a[1]+1, a[2]-1`. Jadi prefix `a[0]` bisa berubah. Prefix jumlah `a[0]+a[1]+...`? Coba prefix `s0=a[0]`: berubah. Jumlah seluruh = tetap.

Contoh lain: pewarnaan 2×2, tukar dua sel tetangga. Paritas jumlah hitam-putih? Lebih klasik: **15-puzzle**. Grid 4×4, ubin 1..15 plus kosong. Tulis permutasi 16 sel (kosong=16). Hitung inversi plus nomor baris kosong. Paritas itu invariant. Target terurut paritas genap; jika start ganjil, mustahil.

Angka kecil: barisan `2,1,3` (kosong tidak ada). Inversi: `(2,1)` satu, ganjil. Identitas 0 genap. Operasi “tukar tetangga” mengubah inversi ±1, **mengubah paritas**. Jadi bukan invariant. Operasi “putar tiga elemen” mengubah inversi genap — paritas inversi invariant.

`2,1,3` → putar posisi 0-1-2: `1,3,2` inversi 1, tetap ganjil. Tidak bisa ke `1,2,3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll jumlah(const vector<ll>& a) {
    ll s = 0;
    for (ll x : a) s += x;
    return s;
}

int paritas_inversi(const vector<int>& a) {
    int n = (int)a.size(), inv = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) inv++;
    return inv & 1;
}

bool maybe_jumlah(const vector<ll>& a, const vector<ll>& b) {
    return jumlah(a) == jumlah(b);
}

int main() {
    cout << maybe_jumlah({1, 2, 3}, {3, 3, 0}) << '\n'; // 1
    cout << maybe_jumlah({1, 2, 3}, {4, 4, 0}) << '\n'; // 0
    cout << paritas_inversi({2, 1, 3}) << '\n';         // 1
    cout << paritas_inversi({1, 2, 3}) << '\n';         // 0
    return 0;
}
```

**Jebakan:** invariant “terasa benar” tanpa uji satu operasi; paritas indeks 1-based vs 0-based pada papan; XOR vs jumlah tertukar; bilangan negatif modulo di C++ (file 08).

**Kompleksitas:** jumlah / XOR `O(n)`. Inversi naif `O(n^2)`, merge sort `O(n log n)` (file 05).

---

## Stress test untuk membantah greedy

**Teori:** sebelum submit greedy yang tidak terbukti, lawankan dengan brute untuk `n` kecil. Kalau beda, greedy salah — cetak kasusnya. Kalau sama sampai puluhan ribu tes, belum tentu benar, tetapi jauh lebih aman. Analoginya mencicipi masakan: satu sendok busuk cukup untuk tidak menyajikan porsi.

**Kapan:** selalu untuk greedy baru, constructive, dan rumus ad-hoc. Tidak menggantikan bukti, tetapi menggantikan harapan.

**Proses:** “ambil interval paling pendek”. Brute = enumerasi subset lepas maksimum.

Kasus `[1,10],[9,12],[11,20]`:

```
pendek: [9,12] saja → 1
optimal: [1,10]+[11,20] → 2
```

Stress ketemu dalam tes pertama jika generator menghasilkan pola ini.

**Kode:** kerangka banding greedy vs brute activity (n ≤ 18).

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int greedy_pendek(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return (x.second - x.first) < (y.second - y.first);
    });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) {
        if (l > akhir) {
            hit++;
            akhir = r;
        }
    }
    return hit;
}

int brute_activity(const vector<pair<ll, ll>>& a) {
    int n = (int)a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        int hit = 0;
        for (int i = 0; i < n && ok; i++) if (mask & (1 << i)) {
            for (int j = i + 1; j < n; j++) if (mask & (1 << j)) {
                ll L = max(a[i].first, a[j].first);
                ll R = min(a[i].second, a[j].second);
                if (L <= R) ok = false;    // tertutup irisan
            }
            hit++;
        }
        if (ok) best = max(best, hit);
    }
    return best;
}

int activity_benar(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto x, auto y) { return x.second < y.second; });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) if (l > akhir) {
        hit++;
        akhir = r;
    }
    return hit;
}

int main() {
    vector<pair<ll, ll>> a = {{1, 10}, {9, 12}, {11, 20}};
    cout << "pendek=" << greedy_pendek(a)
         << " brute=" << brute_activity(a)
         << " r=" << activity_benar(a) << '\n';
    // pendek=1 brute=2 r=2
    return 0;
}
```

Isi generator: `n` acak 1..12, `l` acak, `r = l + acak`. Loop 10000. Cetak saat `greedy != brute`.

**Jebakan:** brute salah (model irisan beda) sehingga greedy yang benar “kelihatan” salah; `n` tes terlalu kecil; tidak mengetes `n` khusus 1,2,4 (konstruktif).

**Kompleksitas:** satu tes brute `O(2^n n^2)`. 10^4 tes `n=12` masih hidup.

---

## Peta keputusan bab ini

```
Soal interval
├── sebanyak mungkin saling lepas     → urut r, activity
├── gabungkan / union                 → urut l, merge + max
├── tutupi [S,T] minimum potong       → greedy jangkauan
├── semua harus masuk, berapa ruang   → sapuan event / heap
└── ada bobot                         → DP, bukan greedy

Soal jadwal satu mesin
├── Σ C_i                             → SPT (t naik)
├── Σ w_i C_i                         → t/w naik, kali silang ll
├── sebanyak mungkin sebelum deadline → urut d + heap buang terpanjang
└── ada r_i aneh                      → waspada, sering bukan greedy murni

Soal “print any / construct”
├── cek mustahil (paritas, bound) dulu
├── tulis pemeriksa
├── pola n kecil, awasi titik sambung
└── stress n=1..30
```

| kriteria kelihatan pintar | status |
| --- | --- |
| interval urut `r` untuk max lepas | benar |
| interval urut `l` untuk max lepas | salah |
| interval urut durasi | salah |
| knapsack 0-1 rasio | salah |
| knapsack fraksional rasio | benar |
| Huffman dua terkecil | benar |
| Dijkstra negatif | salah (bukan bab ini, ingat) |

---

## Ringkasan folder 06

1. Greedy sah jika **exchange** (atau bukti dominasi) jalan. Tanpa itu, ia hanya tebakan.
2. Interval: **urut `r` untuk memilih**, **urut `l` untuk menyapu**. Jangan meniru file kemarin.
3. `[l,r]` vs `[l,r)` dan `akhir = LLONG_MIN` adalah sumber WA paling murah.
4. Konstruktif: pemeriksa dulu, mustahil dulu, titik sambung diuji untuk **semua** `n` kecil.
5. Paritas / jumlah / XOR sering menutup setengah kasus “NO” tanpa membangun apa pun.
6. Satu counterexample mengalahkan sepuluh sampel. Tulis stress sebelum submit.

Lanjut ke [08 sieve, GCD, modular](08-number-sieve-gcd-modular.md) untuk alat hitung sisa bagi, atau [09 CRT, Catalan, matrix, FFT](09-number-crt-catalan-matrix-fft.md) untuk aljabar lanjutan.
