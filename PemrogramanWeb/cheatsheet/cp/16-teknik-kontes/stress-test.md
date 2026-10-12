# Stress test

[← Teknik kontes](README.md) · [Random & anti-hash →](random-antihash.md) · [Indeks CP](../README.md)

Day 250. Membandingkan **solusi cepat** dengan **brute yang jelas benar** pada input acak yang kamu buat sendiri. Ini alat belajar dan debug, bukan perangkat penyerangan, bukan malware, bukan generator tes untuk merusak sistem orang lain.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Hanya program **milikmu**, di mesin **lokal**, untuk soal kontes/latihan.

## Daftar isi

- [Tiga peran](#tiga-peran)
- [Brute vs cepat](#brute-vs-cepat)
- [Fungsi generator](#fungsi-generator)
- [Satu file loop](#satu-file-loop)
- [Skrip dua biner](#skrip-dua-biner)
- [Memperkecil kasus](#memperkecil-kasus)
- [Banyak jawaban sah](#banyak-jawaban-sah)
- [Kasus tepi wajib](#kasus-tepi-wajib)
- [Uji struktur data](#uji-struktur-data)
- [Ringkasan](#ringkasan)

## Tiga peran

**Teori:** 

1. **Generator** — fungsi yang mencetak atau mengembalikan tes legal.
2. **Brute** — O(n²) / rekursi lengkap, mudah dibuktikan.
3. **Cepat** — solusimu.

Jika output beda, kamu punya tes gagal. Perkecil, kerjakan tangan.

Analogi: kunci jawaban ujian dihitung manual 10 soal kecil. Kalau beda, biasanya yang “cepat” yang salah.

**Kapan:**

- Pakai: WA tidak ketemu, off-by-one, Fenwick, hash, geometri integer, DP transisi.
- Jangan: membandingkan konstruktif “sembarang array sah” tanpa checker properti.
- Jangan: generator yang tidak pernah membuat n=1, sudah terurut, semua sama.
- Jangan: memakai ini untuk menyerang judge, akun, atau peserta lain.

**Proses:** soal jumlah `[l,r]` + update. Brute = array. Cepat = BIT. 200 tes n≤20.

**Kode:** kerangka nama fungsi — isi di bagian berikut.

```cpp
vector<int> generateArray(int n, mt19937& rng);
ll bruteSum(const vector<ll>& a, int l, int r);
ll fastSum(...);
```

**Jebakan:** fast dan brute beda format (`Yes` vs `YES`) → diff palsu. Samakan printer.

**Kompleksitas:** brute menentukan n. n≤20, 2000 tes, O(n²) nyaman.

## Brute vs cepat

**Teori:** brute tidak boleh “salinan cepat yang disederhanakan”. Tulis ulang dengan loop yang kamu percaya. Contoh range sum: `for i=l..r`. Contoh inversi: dobel loop. Contoh LCA: naik ayah.

**Kapan:** selalu pisah fungsi `bruteX` dan `fastX`.

**Proses:** a=`[2,1,4]`, l=0,r=2. Brute 7. BIT `range(1,3)` harus 7. Jika 6, tes ketemu.

**Kode:**

```cpp
ll bruteRangeSum(const vector<ll>& a, int l, int r) {
    ll s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}

ll bruteInversi(const vector<ll>& a) {
    ll c = 0;
    int n = (int)a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) c++;
    return c;
}

int bruteMin(const vector<int>& a, int l, int r) {
    int ans = a[l];
    for (int i = l + 1; i <= r; i++) ans = min(ans, a[i]);
    return ans;
}
```

**Jebakan:** brute memakai `int` sementara cepat `ll` — overflow brute salah. Samakan tipe.

**Kompleksitas:** O(n) atau O(n²) disengaja.

## Fungsi generator

**Teori:** generator **bukan** virus, **bukan** fuzz terhadap layanan asing. Ia hanya `mt19937` + `uniform_int_distribution` yang mengisi array/pohon/string legal.

Seed berbeda tiap tes (`tc` atau argumen). Sertakan tepi: n=1, nilai negatif jika diizinkan, sudah terurut, semua sama.

**Kapan:** setiap stress. Parameter n max kecil.

**Proses:** n=1..8, nilai −5..5, q=10 update/query acak.

**Kode:**

```cpp
int randInt(mt19937& rng, int l, int r) {   // inklusif
    uniform_int_distribution<int> d(l, r);
    return d(rng);
}

vector<ll> genArray(mt19937& rng, int n, int lo, int hi) {
    vector<ll> a(n);
    for (ll& x : a) x = randInt(rng, lo, hi);
    return a;
}

string genString(mt19937& rng, int n, int sigma) {
    string s(n, 'a');
    for (char& c : s) c = char('a' + randInt(rng, 0, sigma - 1));
    return s;
}

vector<pair<int, int>> genPohon(mt19937& rng, int n) {
    vector<pair<int, int>> e;
    for (int i = 1; i < n; i++) {
        int p = randInt(rng, 0, i - 1);
        e.push_back({p, i});
    }
    return e;                               // pohon berakar tumbuh
}

void acakSisi(vector<pair<int, int>>& e, mt19937& rng) {
    for (auto& [a, b] : e)
        if (rng() & 1) swap(a, b);
    shuffle(e.begin(), e.end(), rng);
}
```

Pohon: simpul 0..n-1, n−1 sisi, terhubung. Bukan generator “serangan”.

**Jebakan:** `rng() % n` bias. `n=0`. Pohon n=1: nol sisi. String sigma=0.

**Kompleksitas:** O(n) generate.

## Satu file loop

**Teori:** praktis di kontes: satu `main` memanggil generate + brute + fast, 1000 kali. Tanpa file eksternal.

**Kapan:** 15 menit sebelum submit ulang.

**Proses:** 1000 tes BIT, seed 1..1000. Jika beda, cetak n, array, operasi.

**Kode:**

```cpp
// tempel struct BIT 1-based dari 10-struktur-data/fenwick.md

bool stressBitSatuTes(int seed) {
    mt19937 rng(seed);
    int n = randInt(rng, 1, 12);
    int q = randInt(rng, 1, 40);
    vector<ll> a = genArray(rng, n, -5, 5);
    BIT bit;
    bit.build(a);
    for (int i = 0; i < q; i++) {
        if (randInt(rng, 0, 1) == 0) {
            int p = randInt(rng, 0, n - 1);
            ll d = randInt(rng, -3, 3);
            a[p] += d;
            bit.update(p + 1, d);
        } else {
            int l = randInt(rng, 0, n - 1);
            int r = randInt(rng, 0, n - 1);
            if (l > r) swap(l, r);
            ll f = bit.range(l + 1, r + 1);
            ll b = bruteRangeSum(a, l, r);
            if (f != b) {
                cerr << "WA seed=" << seed << " n=" << n << "\n";
                cerr << "l,r=" << l << ' ' << r << " fast=" << f
                     << " brute=" << b << "\n";
                return false;
            }
        }
    }
    return true;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 1000; s++)
        if (!stressBitSatuTes(s)) return 0;
    cout << "lulus 1000 tes\n";
}
```

**Jebakan:** seed tetap 1 setiap kali. `endl` vs spasi di dua printer. Indeks 0 vs 1.

**Kompleksitas:** 1000 × q × n.

## Skrip dua biner

**Teori:** kadang brute dan fast sudah jadi program I/O lengkap. Generator cetak ke stdout. Skrip membandingkan file. Tetap **lokal**, dua program yang kamu compile.

**Kapan:** solusimu sudah `main` baca n,q. Jangan ubah jadi fungsi.

**Proses:** `./gen 42 > in.txt` lalu kedua biner.

**Kode:** generator program.

```cpp
int main(int argc, char** argv) {
    FASTIO;
    int seed = argc > 1 ? atoi(argv[1]) : 1;
    mt19937 rng(seed);
    int n = randInt(rng, 1, 8);
    int q = randInt(rng, 1, 10);
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; i++)
        cout << randInt(rng, 0, 6) << " \n"[i + 1 == n];
    for (int i = 0; i < q; i++) {
        int t = randInt(rng, 1, 2);
        if (t == 1) {
            int idx = randInt(rng, 1, n);
            int d = randInt(rng, -2, 2);
            cout << 1 << ' ' << idx << ' ' << d << '\n';
        } else {
            int l = randInt(rng, 1, n), r = randInt(rng, 1, n);
            if (l > r) swap(l, r);
            cout << 2 << ' ' << l << ' ' << r << '\n';
        }
    }
}
```

Skrip zsh **lokal**:

```bash
#!/bin/zsh
# bandingkan dua program milikmu di folder soal
g++ -std=c++17 -O2 -o fast fast.cpp
g++ -std=c++17 -O2 -o brute brute.cpp
g++ -std=c++17 -O2 -o gen gen.cpp
for i in {1..2000}; do
  ./gen $i > in.txt
  ./fast < in.txt > outf.txt
  ./brute < in.txt > outb.txt
  if ! cmp -s outf.txt outb.txt; then
    echo "BEDA seed=$i"
    cat in.txt
    echo "fast:"; cat outf.txt
    echo "brute:"; cat outb.txt
    exit 1
  fi
done
echo "lulus 2000 tes"
```

Ini membandingkan output edukatif, bukan memindai rahasia atau menembus sistem.

**Jebakan:** `cmp` ketat pada spasi akhir. Token-compare jika perlu. `endl` vs `'\n'` biasanya sama.

**Kompleksitas:** 2000 × waktu brute.

## Memperkecil kasus

**Teori:** tes n=40 sulit dibaca. Hapus satu elemen / satu query, jalankan lagi. Jika masih beda, tetap hapus. Sampai minimal (delta debugging kasar).

Turunkan nilai, ganti 0/1, urutkan ulang (kadang bug urutan).

**Kapan:** setelah stress ketemu tes. Jangan skip.

**Proses:** array 9 elemen, hapus dari belakang. Jika sudah sama, kembalikan, coba indeks lain.

**Kode:**

```cpp
// predikat: tes ini masih membuat fast ≠ brute
bool masihWA(const vector<int>& a);

vector<int> perkecilArray(vector<int> a) {
    bool berubah = true;
    while (berubah) {
        berubah = false;
        for (int i = 0; i < (int)a.size(); i++) {
            vector<int> b = a;
            b.erase(b.begin() + i);
            if (b.empty()) continue;
            if (masihWA(b)) {
                a.swap(b);
                berubah = true;
                break;
            }
        }
    }
    return a;
}

vector<int> perkecilNilai(vector<int> a) {
    for (int i = 0; i < (int)a.size(); i++) {
        int old = a[i];
        a[i] = 0;
        if (!masihWA(a)) a[i] = old;
    }
    return a;
}
```

**Jebakan:** `masihWA` terbalik (kamu menyimpan tes yang **lulus**). Setelah perkecil, cetak dan kerjakan tangan.

**Kompleksitas:** O(n²) percobaan × satu run.

## Banyak jawaban sah

**Teori:** konstruktif: “cetak sembarang array yang jumlahnya S”. `cmp` string gagal. Tulis `bool sah(input, output)` yang memeriksa properti, bukan kesamaan dengan brute.

Brute boleh menghasilkan satu contoh; fast contoh lain. Checker memutuskan.

**Kapan:** soal YES + konstruksi, permutasi sah, matching.

**Proses:** soal pecah S jadi n positif. Brute greedy. Fast lain. Keduanya sah jika jumlah S dan n elemen.

**Kode:**

```cpp
bool sahPartisi(int n, ll S, const vector<ll>& out) {
    if ((int)out.size() != n) return false;
    ll s = 0;
    for (ll x : out) {
        if (x <= 0) return false;
        s += x;
    }
    return s == S;
}

bool stressKonstruktif(int seed) {
    mt19937 rng(seed);
    int n = randInt(rng, 1, 5);
    ll S = randInt(rng, n, 20);
    vector<ll> fast = /* fungsi cepat */;
    return sahPartisi(n, S, fast);
}
```

**Jebakan:** memaksa `cmp` pada konstruktif. WA palsu.

**Kompleksitas:** sesuai checker.

## Kasus tepi wajib

**Teori:** generator acak sering menghindari n=1. Paksa daftar tepi.

**Kapan:** setiap soal.

**Proses:** n=1; semua a[i]=0; sudah sort; reverse sort; pohon rantai; pohon bintang; string `"aaaa"`; string karakter tunggal.

**Kode:**

```cpp
vector<vector<ll>> tesTepi() {
    return {
        {0},
        {5},
        {1, 2, 3, 4},
        {4, 3, 2, 1},
        {2, 2, 2, 2},
        {-1, 0, 1},
    };
}

bool jalaniTepi() {
    for (auto a : tesTepi()) {
        // banding brute vs fast pada a
        if (bruteRangeSum(a, 0, (int)a.size() - 1) !=
            bruteRangeSum(a, 0, (int)a.size() - 1))
            return false;
    }
    return true;
}
```

Ganti baris kedua dengan fungsi cepat.

**Jebakan:** tepi hanya di kepala, tidak dijalankan.

**Kompleksitas:** O(1) tes.

## Uji struktur data

**Teori:** pola sama untuk SegTree, lazy, hash, KMP. Brute = operasi pada array/string mentah.

**Kapan:** setelah menulis template baru.

**Proses:** lihat [fenwick.md](../10-struktur-data/fenwick.md) dan [segment-tree.md](../10-struktur-data/segment-tree.md).

**Kode:** KMP vs naif.

```cpp
bool stressKmp(int seed) {
    mt19937 rng(seed);
    string t = genString(rng, randInt(rng, 1, 20), 3);
    string p = genString(rng, randInt(rng, 1, 5), 3);
    vector<int> brute, fast;
    for (int i = 0; i + (int)p.size() <= (int)t.size(); i++)
        if (t.compare(i, p.size(), p) == 0) brute.push_back(i);
    // fast = kmpCari(t, p);
    fast = brute;                           // ganti dengan KMP milikmu
    return brute == fast;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 500; s++)
        if (!stressKmp(s)) {
            cout << "WA " << s << '\n';
            return 0;
        }
    cout << "ok\n";
}
```

**Jebakan:** pola lebih panjang dari teks: keduanya kosong. Pola kosong: tentukan konvensi.

**Kompleksitas:** O(n m) brute.

## Ringkasan

1. Stress = generator + brute + cepat, di mesin sendiri.
2. Bukan malware, bukan serangan judge, bukan anti-forensik.
3. Seed berjalan. Cetak tes saat beda.
4. Perkecil sebelum mikir 20 menit.
5. Konstruktif: checker properti.
6. Paksa n=1 dan semua-sama.

Latihan Day 250: stress-kan BIT milikmu. Jangan salin `exercise_*.cpp`.
