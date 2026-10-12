# KMP dan prefix function

[← Hashing](hashing.md) · [String](README.md) · [Z & Manacher →](z-manacher.md)

Day 213. `pi[i]` = border: prefiks terpanjang yang juga sufiks, bukan seluruh string.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Tanpa tabrakan hash. Jari di teks tidak mundur.

## Daftar isi

- [Prefix function](#prefix-function)
- [Mesin j](#mesin-j)
- [Cari pola](#cari-pola)
- [Gabung pola + teks](#gabung-pola--teks)
- [Border dan periode](#border-dan-periode)
- [Hitung kemunculan prefiks](#hitung-kemunculan-prefiks)
- [Automaton KMP](#automaton-kmp)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Prefix function

**Teori:** `pi[i]` = panjang prefiks terpanjang dari `s[0..i]` yang juga sufiks `s[0..i]`, **bukan** i+1.

Saat gagal di posisi j, turunkan j jadi `pi[j-1]`: sisa huruf masih cocok sebagai awalan.

Kenapa O(n): j naik (cocok) dan turun. j ≥ 0, total naik ≤ n, total turun ≤ n.

Analogi: mengeja `abab`, huruf berikutnya salah. Dua huruf terakhir `ab` = awal kata. Tidak ulang dari huruf pertama buku.

**Kapan:**

- Pakai: cari pola, periode, banyak kemunculan prefiks, kompresi string.
- Z-function sering lebih mudah untuk “LCP dengan awal”.
- Hash lebih pendek untuk “apakah sama”.

**Proses:** s = `"ababc"`.

```
i=0 "a"      pi=0
i=1 "ab"     a≠b          pi=0
i=2 "aba"    sufiks a     pi=1
i=3 "abab"   sufiks ab    pi=2
i=4 "ababc"  c ≠ a        pi=0
pi = [0,0,1,2,0]
```

**Kode:**

```cpp
vector<int> prefixFunction(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
```

**Jebakan:** `pi[0]` harus 0. `j = pi[i]` saat i belum diisi. `while` tanpa `j>0` akses `pi[-1]`. Mengira `pi[i]=i+1` legal.

**Kompleksitas:** O(n).

## Mesin j

**Teori:** j = panjang prefiks pola yang sedang cocok. Simulasi di atas:

```
i=2: 'a'==s[0], j: 0→1
i=3: 'b'==s[1], j: 1→2
i=4: 'c'!=s[2], j=pi[1]=0, 'c'!=s[0], j=0
```

**Kapan:** debug `pi` salah.

**Proses:** `"aaaa"`.

```
pi = [0,1,2,3]
setiap huruf menambah border
```

`"aaaab"`: pi `[0,1,2,3,0]`.

**Kode:** cetak jejak.

```cpp
void jejakPi(const string& s) {
    auto pi = prefixFunction(s);
    for (int i = 0; i < (int)s.size(); i++)
        cout << i << ' ' << s.substr(0, i + 1) << " pi=" << pi[i] << '\n';
}
```

**Jebakan:** `substr` mahal di n besar, hanya untuk n kecil.

**Kompleksitas:** O(n).

## Cari pola

**Teori:** jalankan mesin j pada teks. Saat j == m, ketemu di `i-m+1`. Lanjut `j = pi[j-1]` agar tumpang tindih dihitung.

**Kapan:** satu pola. Banyak pola → Aho ([sa-aho-sam.md](sa-aho-sam.md)).

**Proses:** pola `aba` (m=3), teks `abacaba`.

```
i  huruf  j sebelum  j sesudah  ketemu
0  a      0          1          -
1  b      1          2          -
2  a      2          3          YA di 0, j=pi[2]=1
3  c      1          0          c≠b, c≠a
4  a      0          1
5  b      1          2
6  a      2          3          YA di 4, j=1
posisi 0 dan 4
```

**Kode:**

```cpp
vector<int> kmpCari(const string& teks, const string& pola) {
    vector<int> ans;
    int m = (int)pola.size(), n = (int)teks.size();
    if (m == 0) return ans;
    vector<int> pi = prefixFunction(pola);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && teks[i] != pola[j]) j = pi[j - 1];
        if (teks[i] == pola[j]) j++;
        if (j == m) {
            ans.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}
```

**Jebakan:** `j = pi[j]` saat j==m tanpa −1. Pola kosong: tentukan konvensi (di sini tidak lapor). `pola[j]` saat j==m sebelum cek urutan — di kode ini cek `j==m` setelah increment, aman.

**Kompleksitas:** O(n+m).

## Gabung pola + teks

**Teori:** bangun `pi` pada `pola + SEP + teks`. Setiap `pi[i]==m` di bagian teks adalah kemunculan. SEP karakter yang **tidak** muncul (`'\1'`, bukan `'#'` jika `#` ada di input).

Posisi di teks:

```
startG = i - m + 1
pos = startG - (m + 1)
```

**Kapan:** suka satu fungsi `prefixFunction` saja.

**Proses:** g = `aba` + SEP + `abacaba`.

```
indeks g: 0 1 2  3   4 5 6 7 8 9 10
huruf:    a b a SEP  a b a c a b a
pi[6]=3, pi[10]=3
i=6  startG=4  teks 0
i=10 startG=8  teks 4
```

**Kode:**

```cpp
vector<int> kmpCariGabung(const string& teks, const string& pola) {
    const char SEP = 1;
    string g = pola + SEP + teks;
    vector<int> pi = prefixFunction(g), ans;
    int m = (int)pola.size();
    for (int i = m + 1; i < (int)g.size(); i++)
        if (pi[i] == m) {
            int startG = i - m + 1;
            ans.push_back(startG - (m + 1));
        }
    return ans;
}
```

**Jebakan:** SEP muncul di teks → mesin menyatu, WA. Rumus indeks: uji `aba` di `abacaba` harus `{0,4}`.

**Kompleksitas:** O(n+m).

## Border dan periode

**Teori:** rantai `n, pi[n-1], pi[pi[n-1]-1], ...` semua border. Periode terkecil **kandidat** `p = n - pi[n-1]`. Jika `n % p == 0`, maka p periode sejati (string = blok p diulang).

**Kapan:** CSES *Finding Periods/Borders*, kompresi.

**Proses:**

```
"ababab": pi akhir 4, p=6-4=2, 6%2==0 → periode 2
"ababa":  pi akhir 3, p=5-3=2, 5%2≠0 → periode sejati 5
"aaaa":   pi=3, p=1, 4%1==0 → 1
```

Border `"ababa"`: 3 (`aba`), lalu `pi[2]=1` (`a`).

**Kode:**

```cpp
int periodeTerkecil(const string& s) {
    int n = (int)s.size();
    if (n == 0) return 0;
    int p = n - prefixFunction(s)[n - 1];
    if (n % p == 0) return p;
    return n;
}

vector<int> semuaBorder(const string& s) {
    vector<int> pi = prefixFunction(s), b;
    int k = nSafe(s, pi);
    while (k > 0) {
        b.push_back(k);
        k = pi[k - 1];
    }
    return b;
}

int nSafe(const string& s, const vector<int>& pi) {
    return s.empty() ? 0 : pi.back();
}

vector<int> semuaPeriode(const string& s) {
    int n = (int)s.size();
    vector<int> pi = prefixFunction(s), ans;
    for (int len = 1; len <= n; len++)
        if (n % len == 0) {
            bool ok = true;
            for (int i = len; i < n; i++)
                if (s[i] != s[i - len]) {
                    ok = false;
                    break;
                }
            if (ok) ans.push_back(len);
        }
    return ans;
}
```

`semuaPeriode` naif O(n²) untuk cek. Periode dari KMP: jika `i+1` habis dibagi `(i+1-pi[i])` maka ada periode.

```cpp
vector<int> periodePrefiks(const string& s) {
    auto pi = prefixFunction(s);
    int n = (int)s.size();
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int p = (i + 1) - pi[i];
        if ((i + 1) % p == 0 && p < i + 1) ans.push_back(p);
    }
    return ans;                             // periode prefiks s[0..i], interpretasi hati-hati
}
```

Untuk soal “semua periode seluruh s”: `n-pi[n-1]` dan kelipatannya yang membagi n, atau Z.

**Jebakan:** memakai `p=n-pi[n-1]` tanpa cek `n%p`. `"ababa"` bukan periode 2.

**Kompleksitas:** O(n).

## Hitung kemunculan prefiks

**Teori:** `c[len]` = berapa kali prefiks panjang len muncul sebagai prefiks suatu `s[0..i]` (termasuk seluruh s). Rantai border: jika `pi[i]=len`, prefiks len muncul di i. Propagasi dari panjang besar ke kecil.

**Kapan:** “berapa kali awalan muncul”.

**Proses:** `"abab"`.

```
pi = [0,0,1,2]
c mentah pi: c[0],c[0],c[1],c[2] increment
lalu c[pi[i-1]] += c[i]
tiap prefiks +1 (dirinya)
```

**Kode:**

```cpp
vector<int> hitungPrefiks(const string& s) {
    vector<int> pi = prefixFunction(s);
    int n = (int)s.size();
    vector<int> c(n + 1, 0);
    for (int i = 0; i < n; i++) c[pi[i]]++;
    for (int i = n - 1; i > 0; i--) c[pi[i - 1]] += c[i];
    for (int i = 1; i <= n; i++) c[i]++;
    return c;                               // c[len]
}
```

**Jebakan:** `c[0]` tidak bermakna sebagai prefiks. Off-by-one `c[pi[i-1]]`.

**Kompleksitas:** O(n).

## Automaton KMP

**Teori:** `go[j][c]` = state setelah huruf c dari panjang j. Precompute alfabet kecil. Berguna jika banyak teks, satu pola, atau DP “berapa cara membentuk pola”.

**Kapan:** DP string + pola, alfabet 26.

**Proses:** pola `aba`. Dari j=2 (`ab`), huruf `a` → 3 (selesai / border 1 tergantung). Dari j=1, `c` → 0.

**Kode:**

```cpp
vector<array<int, 26>> bangunGo(const string& pola) {
    auto pi = prefixFunction(pola);
    int m = (int)pola.size();
    vector<array<int, 26>> go(m + 1);
    for (int j = 0; j <= m; j++) {
        for (int c = 0; c < 26; c++) {
            if (j < m && pola[j] == char('a' + c)) go[j][c] = j + 1;
            else if (j == 0) go[j][c] = 0;
            else go[j][c] = go[pi[j - 1]][c];
        }
    }
    return go;
}
```

Isi berurutan j naik supaya `go[pi[...]]` sudah siap — hati-hati: `go[j][c]` mereferensi `go[pi[j-1]]` yang j lebih kecil, OK.

**Jebakan:** huruf besar. State m = sudah cocok penuh: transisi lanjut pakai `pi[m-1]`.

**Kompleksitas:** O(m · 26).

## Uji naif

**Teori:** KMP vs `string::find` berulang vs hash.

**Kapan:** wajib untuk rumus gabung.

**Proses:**

```
periodeTerkecil("ababab")==2
periodeTerkecil("ababa")==5
kmpCari("aaaa","aa") == {0,1,2}
```

**Kode:**

```cpp
vector<int> cariNaif(const string& t, const string& p) {
    vector<int> a;
    if (p.empty()) return a;
    for (int i = 0; i + (int)p.size() <= (int)t.size(); i++)
        if (t.compare(i, p.size(), p) == 0) a.push_back(i);
    return a;
}

int main() {
    FASTIO;
    string t = "abacaba", p = "aba";
    auto a = kmpCari(t, p);
    auto b = kmpCariGabung(t, p);
    auto c = cariNaif(t, p);
    assert(a == b && b == c);
    assert((a == vector<int>{0, 4}));
    assert(periodeTerkecil("ababab") == 2);
    assert(periodeTerkecil("ababa") == 5);
    assert((kmpCari("aaaa", "aa") == vector<int>{0, 1, 2}));
    cout << "ok\n";
}
```

**Jebakan:** overlap `"aa"` di `"aaa"`: 0 dan 1, bukan hanya 0.

**Kompleksitas:** tes O(n m).

## KMP vs hash vs Z

**Teori:** tiga alat mencari pola. KMP dan Z pasti benar. Hash lebih pendek, ada tabrakan. Untuk periode ketat, KMP/`n%p` lebih bersih daripada “hash blok sama”.

**Kapan:** soal hack CF → KMP atau double hash. Soal periode → KMP atau Z. Soal “dua potongan sama” tanpa pola tetap → hash, bukan KMP.

**Proses:** teks `aaaa`, pola `aa`. KMP `{0,1,2}`. Hash jendela juga tiga posisi. Z pada `aa + SEP + aaaa` memberi `z>=2` di tiga tempat.

**Kode:**

```cpp
bool samaAlat(const string& t, const string& p) {
    return kmpCari(t, p) == kmpCariGabung(t, p);
}
```

**Jebakan:** membandingkan KMP dengan `find` yang tidak overlap (`pos += m`).

**Kompleksitas:** sama O(n+m) untuk KMP/Z.

## Ringkasan

1. `pi[i]` border, bukan seluruh string.
2. Mesin j tidak mundur di teks.
3. Ketemu: `j=m`, lalu `j=pi[m-1]`.
4. Periode kandidat `n-pi[n-1]`, cek `n%p==0`.
5. SEP tidak boleh muncul di input.
6. Banyak pola: Aho, bukan KMP ulang jika n×pola besar.

Latihan Day 213. Jangan salin latihan ComprogLearning.
