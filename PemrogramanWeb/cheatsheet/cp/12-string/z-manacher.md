# Z-function dan Manacher

[← KMP](kmp.md) · [String](README.md) · [Trie →](trie.md)

Day 215. LCP dengan awal string, dan radius palindrom linear.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Z-box dan Manacher-box satu semangat: “sudah terbukti, salin cermin, perpanjang jika perlu”.

## Daftar isi

- [Definisi Z](#definisi-z)
- [Algoritma Z-box](#algoritma-z-box)
- [Cari pola dengan Z](#cari-pola-dengan-z)
- [Periode lewat Z](#periode-lewat-z)
- [Ide Manacher](#ide-manacher)
- [Expand naif](#expand-naif)
- [Manacher d1 dan d2](#manacher-d1-dan-d2)
- [Jumlah palindrom](#jumlah-palindrom)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Definisi Z

**Teori:** `z[i]` = LCP antara `s` dan `s[i..n-1]`. Template ini `z[0]=0` (beberapa orang mengisi n; pilih satu dan konsisten).

**Kapan:**

- Pakai: cari pola (`pola+SEP+teks`, `z[i]>=|pola|`), border (`z[i]==n-i`), periode.
- KMP dan Z saling mengganti banyak soal. Hafalkan **satu** yang bisa kamu debug.

**Proses:** s = `"aabcaab"`.

```
i=1 "abcaab" vs "aabcaab"  LCP=1
i=2 "bcaab"                0
i=3 "caab"                 0
i=4 "aab"                  3
i=5 "ab"                   1
i=6 "b"                    0
z = [0,1,0,0,3,1,0]
```

**Kode:** belum Z-box, naif O(n²) untuk cek.

```cpp
vector<int> zNaif(const string& s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    for (int i = 1; i < n; i++)
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    return z;
}
```

**Jebakan:** `z[0]=n` lalu template Z-box memakai `z[i-l]` saat l=0 merusak.

**Kompleksitas:** naif O(n²), target O(n).

## Algoritma Z-box

**Teori:** Z-box `[l, r)` = segmen paling kanan yang sudah terbukti = awalan. Untuk i di dalam box, `z[i]` minimal `min(r-i, z[i-l])`, lalu diperpanjang. Setiap perpanjangan mendorong r maju, total O(n).

Konvensi: `r` **eksklusif**.

**Kapan:** selalu untuk n besar.

**Proses:** s=`"aabcaab"`, i=4: r maju ke 7. i=5 di dalam box: `z[5]=min(7-5, z[1])=min(2,1)=1`. Cocok, tidak perlu perpanjang.

**Kode:**

```cpp
vector<int> bangunZ(const string& s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;                       // [l, r)
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
```

**Jebakan:** campur `r` inklusif. `i+z[i] < n` wajib. Inisialisasi `r=0` bukan −1 jika eksklusif.

**Kompleksitas:** O(n).

## Cari pola dengan Z

**Teori:** `g = pola + SEP + teks`. Jika `z[i] >= m` pada bagian teks, pola mulai di `i-m-1`.

**Kapan:** pengganti KMP. SEP `char(1)`.

**Proses:** pola `aba`, teks `abacaba`.

```
g = aba + SEP + abacaba
z pada posisi teks 0 dan 4 ≥ 3
```

**Kode:**

```cpp
vector<int> cariZ(const string& teks, const string& pola) {
    vector<int> ans;
    int m = (int)pola.size();
    if (m == 0) return ans;
    string g = pola + char(1) + teks;
    vector<int> z = bangunZ(g);
    for (int i = m + 1; i < (int)g.size(); i++)
        if (z[i] >= m) ans.push_back(i - m - 1);
    return ans;
}
```

**Jebakan:** `'#'` di string yang berisi `#`. Rumus `i-m-1` vs `i-2*m` hanya jika |SEP|=1.

**Kompleksitas:** O(n+m).

## Periode lewat Z

**Teori:** i periode sejati jika `i + z[i] == n` dan `n % i == 0`. Yang terkecil adalah periode string.

Border: `z[i] == n-i` artinya sufiks i = prefiks panjang n-i.

**Kapan:** sama dengan KMP periode. Uji keduanya.

**Proses:** `"ababab"`:

```
z[2] = 4, 2+4=6, 6%2==0 → periode 2
```

`"ababa"`: tidak ada i < 5 dengan i|5 dan z penuh kecuali i=5.

**Kode:**

```cpp
int periodeZ(const string& s) {
    int n = (int)s.size();
    vector<int> z = bangunZ(s);
    for (int i = 1; i < n; i++)
        if (i + z[i] == n && n % i == 0) return i;
    return n;
}

vector<int> borderZ(const string& s) {
    int n = (int)s.size();
    vector<int> z = bangunZ(s), b;
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) b.push_back(n - i);
    sort(b.begin(), b.end());
    return b;
}
```

**Jebakan:** `i + z[i] == n` tanpa `n%i==0` hanya “sufiks = prefiks”, belum periode penuh jika n tidak kelipatan.

**Kompleksitas:** O(n).

## Ide Manacher

**Teori:** palindrom berpusat di titik, radius r berarti `s[c-r..c+r]` palindrom (ganjil). Naif O(n²). Manacher: jika sudah ada palindrom besar `[L,R]` berpusat C, maka i di dalam punya cermin `i' = 2C-i`. Radius di i minimal `min(radius[i'], R-i)`, lalu diperpanjang.

Sentinel `^#a#b#a#$` menyeragamkan pusat genap/ganjil. Boleh juga dua pass `d1`/`d2` tanpa sentinel.

Ide yang dibawa: **radius + cermin + kanan terjauh**.

**Kapan:**

- Pakai: longest palindromic substring, jumlah palindrom, radius tiap pusat.
- Jangan: satu pertanyaan `[l,r]` — hash dua arah cukup.
- Lupa rumus: binary search + hash O(n log n) sering lolos.

**Proses:** s=`"aba"`. Pusat `b`: radius 1 di asli (3 huruf). Pusat `a` kiri: radius 0 (satu huruf).

`"aaa"`: setelah pusat pertama panjang, pusat berikutnya menyalin.

**Kode:** belum penuh, cermin:

```cpp
int cermin(int i, int C) { return 2 * C - i; }
```

**Jebakan:** mencampur indeks string asli dan string ber-`#`.

**Kompleksitas:** target O(n).

## Expand naif

**Teori:** untuk setiap pusat ganjil dan genap, perluas selama sama. Mudah, O(n²) terburuk (`aaaa`).

**Kapan:** n ≤ 4000, atau cek Manacher.

**Proses:** `"abba"`.

```
pusat ganjil 0..3: palindrom 1
pusat genap antara 1-2: "bb" lalu "abba" → [0,3]
```

**Kode:**

```cpp
pair<int, int> palindromTerpanjang(const string& s) {
    int n = (int)s.size();
    int bestL = 0, bestR = 0;
    auto perluas = [&](int L, int R) {
        while (L >= 0 && R < n && s[L] == s[R]) {
            if (R - L > bestR - bestL) {
                bestL = L;
                bestR = R;
            }
            L--;
            R++;
        }
    };
    for (int i = 0; i < n; i++) {
        perluas(i, i);
        perluas(i, i + 1);
    }
    return {bestL, bestR};
}
```

**Jebakan:** `bestR-bestL` vs panjang; tie tidak penting jika soal salah satu.

**Kompleksitas:** O(n²) terburuk.

## Manacher d1 dan d2

**Teori:**

- `d1[i]` = radius ganjil: palindrom panjang `2*d1[i]-1` berpusat i. `d1[i]>=1`.
- `d2[i]` = radius genap: panjang `2*d2[i]`, pusat di antara i-1 dan i (implementasi di bawah: palindrom `s[i-d2[i] .. i+d2[i]-1]`).

**Kapan:** n 10^6, jumlah palindrom, longest.

**Proses:** `"aba"`.

```
d1 = [1,2,1]   pusat 1 radius 2 → "aba"
d2 = [0,0,0]
```

`"aa"`:

```
d1 = [1,1]
d2[1] = 1      "aa" indeks 0..1
```

**Kode:**

```cpp
void manacher(const string& s, vector<int>& d1, vector<int>& d2) {
    int n = (int)s.size();
    d1.assign(n, 0);
    d2.assign(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}

pair<int, int> terpanjangManacher(const string& s) {
    vector<int> d1, d2;
    manacher(s, d1, d2);
    int bestL = 0, bestR = 0;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        int L = i - d1[i] + 1, R = i + d1[i] - 1;
        if (R - L > bestR - bestL) {
            bestL = L;
            bestR = R;
        }
        if (d2[i]) {
            L = i - d2[i];
            R = i + d2[i] - 1;
            if (R - L > bestR - bestL) {
                bestL = L;
                bestR = R;
            }
        }
    }
    return {bestL, bestR};
}
```

**Jebakan:** campur d1/d2. Off-by-one genap sangat umum — uji `"aa"` dan `"abba"`. Setelah `d1[i]=k--`, `k` dipakai untuk perbarui `[l,r]`.

**Kompleksitas:** O(n).

## Jumlah palindrom

**Teori:** tiap radius menghitung banyak palindrom berpusat di situ. Ganjil: `d1[i]` buah (panjang 1,3,...,2 d1-1). Genap: `d2[i]` buah.

Substring palindrom **bukan** distinct. Distinct butuh hash set atau SA.

**Kapan:** “berapa subarray palindrom”.

**Proses:** `"aaa"`: pusat tengah d1=2 (a, aaa) plus lainnya. Total 6: 3 tunggal, 2 ganda, 1 triple.

**Kode:**

```cpp
ll jumlahPalindrom(const string& s) {
    vector<int> d1, d2;
    manacher(s, d1, d2);
    ll ans = 0;
    for (int x : d1) ans += x;
    for (int x : d2) ans += x;
    return ans;
}

int jumlahNaif(const string& s) {
    int n = (int)s.size(), c = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            bool ok = true;
            for (int a = i, b = j; a < b; a++, b--)
                if (s[a] != s[b]) {
                    ok = false;
                    break;
                }
            if (ok) c++;
        }
    return c;
}
```

**Jebakan:** double count distinct. Soal “berbeda sebagai string” ≠ jumlah pusat.

**Kompleksitas:** O(n) vs naif O(n³) atau O(n²) cek.

## Uji naif

**Teori:** Z vs zNaif. Cari vs KMP. Manacher vs expand vs jumlahNaif.

**Kapan:** setiap ganti `r` inklusif.

**Proses:** `"abacaba"`, `"aaaa"`, `"abba"`, `""`.

**Kode:**

```cpp
int main() {
    FASTIO;
    for (string s : {"", "a", "aa", "abba", "abacaba", "aaaa", "aabcaab"}) {
        if (bangunZ(s) != zNaif(s)) {
            cout << "Z WA " << s << '\n';
            return 0;
        }
        if (jumlahPalindrom(s) != jumlahNaif(s)) {
            cout << "pal WA " << s << '\n';
            return 0;
        }
        auto a = palindromTerpanjang(s);
        auto b = terpanjangManacher(s);
        if (a.second - a.first != b.second - b.first) {
            cout << "len WA " << s << '\n';
            return 0;
        }
    }
    string t = "abacaba", p = "aba";
    assert((cariZ(t, p) == vector<int>{0, 4}));
    assert(periodeZ("ababab") == 2);
    assert(periodeZ("ababa") == 5);
    cout << "ok\n";
}
```

**Jebakan:** string kosong: loop Z tidak jalan, jumlah 0. n=1: d1[0]=1.

**Kompleksitas:** tes O(n³) kumpulan kecil.

## Ringkasan

1. `z[i]` = LCP dengan awal. `z[0]=0` di sini.
2. Z-box `[l,r)` eksklusif. Salin `min(r-i, z[i-l])`.
3. Cari pola: `pola+SEP+teks`.
4. Manacher = cermin radius. d1 ganjil, d2 genap.
5. Lupa rumus: expand atau hash.
6. Jumlah palindrom = Σ d1 + Σ d2, bukan distinct.

Latihan Day 215. Jangan salin `exercise_*.cpp`.
